
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      Sources/TLBoDP_Device_PCIe_L.c

// This file must be included into the DKMS package and be compiled at
// installation

// ===== Linux ==============================================================
#include <linux/pci.h>
#include <linux/types.h>

// ===== Includes ===========================================================
#include <TLBoDP_Assert_L.h>
#include <TLBoDP_Device_L.h>
#include <TLBoDP_Device_PCIe.h>

#include <TLBoDP_Device_PCIe_L.h>

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static void Interrupts_Prepare(TLBoDP_Device_PCIe* aThis);
static void Interrupts_Release(TLBoDP_Device_PCIe* aThis);

static void Memories_Prepare(TLBoDP_Device_PCIe* aThis);
static void Memories_Release(TLBoDP_Device_PCIe* aThis);

// ===== Entry points =======================================================

static int Interrupt_ISR(int aInterrupt, void * aContext);

static void Tasklet(uint64_t aContext);

// Functions
// //////////////////////////////////////////////////////////////////////////

TLBoDP_Device_PCIe* TLBoDP_Device_PCIe_From_pci_dev(struct pci_dev* aPciDev)
{
    printk(KERN_DEBUG "TLBoDP: %s(  )\n", __FUNCTION__);

    ASSERT(NULL != aPciDev);

    TLBoDP_Device* lResult = pci_get_drvdata(aPciDev);

    return (TLBoDP_Device_PCIe*)lResult;
}

TLBoDP_Result TLBoDP_Device_PCIe_New(unsigned int aSize_byte, struct pci_dev* aPciDev)
{
    printk(KERN_DEBUG "TLBoDP: %s( %u bytes,  )\n", __FUNCTION__, aSize_byte);

    ASSERT(NULL != aPciDev);

    unsigned int lSize_byte = sizeof(TLBoDP_Device_PCIe);

    if (0 < aSize_byte)
    {
        ASSERT(lSize_byte <= aSize_byte);

        lSize_byte = aSize_byte;
    }

    TLBoDP_Device* lBase;

    TLBoDP_Result lResult = TLBoDP_Device_New(lSize_byte, &lBase);
    if (TLBoDP_OK == lResult)
    {
        ASSERT(NULL != lBase);

        TLBoDP_Device_PCIe* lThis = (TLBoDP_Device_PCIe*)lBase;

        TLBoDP_Device_PCIe_Init(lThis);

        lThis->mPciDev= aPciDev;

        pci_set_drvdata(aPciDev, lThis);

        tasklet_init(&lThis->mLinux.mTasklet, (void*)Tasklet, (uint64_t)lThis);
    }

    return lResult;
}

void TLBoDP_Device_PCIe_Delete(TLBoDP_Device_PCIe* aThis)
{
    printk(KERN_DEBUG "TLBoDP: %s(  )\n", __FUNCTION__);

    tasklet_kill(&aThis->mLinux.mTasklet);

    pci_set_drvdata(aThis->mPciDev, NULL);

    TLBoDP_Device_Delete(&aThis->mBase);
}

void TLBoDP_Device_PCIe_SetModuleName(TLBoDP_Device_PCIe* aThis, const char* aModuleName)
{
    printk(KERN_DEBUG "TLBoDP: %s( , \"%s\" )\n", __FUNCTION__, aModuleName);

    aThis->mModuleName = aModuleName;
}

// TODO  Add a flag to indicate it the device is a PCIe master

TLBoDP_Result TLBoDP_Device_PCIe_PrepareHardware(TLBoDP_Device_PCIe* aThis)
{
    printk(KERN_DEBUG "TLBoDP: %s(  )\n", __FUNCTION__);

    ASSERT(NULL != aThis->mModuleName);

    TLBoDP_Result lResult = TLBoDP_NOT_INITIALIZED;

    struct pci_dev* lPciDev = aThis->mPciDev;
    ASSERT(NULL != lPciDev);

    int lRet = pci_enable_device_mem(lPciDev);
    if (0 == lRet)
    {
        int lRet = dma_set_mask_and_coherent(&lPciDev->dev, DMA_BIT_MASK(64));
        ASSERT(0 == lRet);
        (void)lRet;

        pci_set_master(lPciDev);

        Memories_Prepare(aThis);

        Interrupts_Prepare(aThis);

        lResult = TLBoDP_Device_PrepareHardware(&aThis->mBase);
    }
    else
    {
        printk(KERN_ERR "TLBoDP: %s - TLBoDP_ERROR_LINUX_PCI - %d\n", __FUNCTION__, lRet);
        lResult = TLBoDP_ERROR_LINUX_PCI;
    }

    return lResult;
}

void TLBoDP_Device_PCIe_ReleaseHardware(TLBoDP_Device_PCIe* aThis)
{
    printk(KERN_DEBUG "TLBoDP: %s(  )\n", __FUNCTION__);

    struct pci_dev* lPciDev = aThis->mPciDev;
    ASSERT(NULL != lPciDev);

    Interrupts_Release(aThis);

    Memories_Release(aThis);

    pci_disable_device(lPciDev);

    TLBoDP_Device_ReleaseHardware(&aThis->mBase);
}

// Static functions
/////////////////////////////////////////////////////////////////////////////

void Interrupts_Prepare(TLBoDP_Device_PCIe* aThis)
{
    printk(KERN_DEBUG "TLBoDP: %s(  )\n", __FUNCTION__);

    struct pci_dev* lPciDev = aThis->mPciDev;
    ASSERT(NULL != lPciDev);

    aThis->mInt_Type = TLBoDP_Device_PCIe_INTERRUPT_MSI_X;

    aThis->mInt_Count = pci_alloc_irq_vectors(lPciDev, 1, TLBoDP_Device_PCIe_INTERRUPT_QTY, PCI_IRQ_MSI | PCI_IRQ_MSIX);
    switch (aThis->mInt_Count)
    {
    case 0 :
        printk(KERN_INFO "TLBoDP: %s - pci_alloc_irq_vectors( , , ,  ) returned 0\n", __FUNCTION__);
        aThis->mInt_Count = 1;
        aThis->mInt_Type = TLBoDP_Device_PCIe_INTERRUPT_LEGACY;
        break;

    case -EINVAL:
        printk(KERN_INFO "TLBoDP: %s - pci_alloc_irq_vectors( , , ,  ) returned -EINVAL\n", __FUNCTION__);
        aThis->mInt_Count = 0;
        aThis->mInt_Type = TLBoDP_Device_PCIe_INTERRUPT_NONE;
        break;

    default:
        printk(KERN_INFO "TLBoDP: %s - pci_alloc_irq_vectors( , , ,  ) returned %d\n", __FUNCTION__, aThis->mInt_Count);
        if (TLBoDP_Device_PCIe_INTERRUPT_QTY < aThis->mInt_Count)
        {
            aThis->mInt_Count = 0;
            aThis->mInt_Type  = TLBoDP_Device_PCIe_INTERRUPT_NONE;
        }
    }

    for (unsigned int i = 0; i < aThis->mInt_Count; i ++)
    {
        int lRet;

        aThis->mInterrupts[i] = pci_irq_vector(lPciDev, i);

        lRet = request_irq(aThis->mInterrupts[i], (void *)Interrupt_ISR, 0, aThis->mModuleName, aThis);
        if (0 != lRet)
        {
            printk(KERN_ERR "TLBoDP: %s - request_irq( %u, ,  ) failed - %d\n", __FUNCTION__, aThis->mInterrupts[i], lRet);
            aThis->mInt_Count = i;
            break;
        }
    }
}

void Interrupts_Release(TLBoDP_Device_PCIe* aThis)
{
    printk(KERN_DEBUG "TLBoDP: %s(  )\n", __FUNCTION__);

    struct pci_dev* lPciDev = aThis->mPciDev;
    ASSERT(NULL != lPciDev);

    for (unsigned int i = 0; i < aThis->mInt_Count; i++)
    {
        free_irq(aThis->mInterrupts[i], aThis);
    }

    if (TLBoDP_Device_PCIe_INTERRUPT_MSI_X == aThis->mInt_Type)
    {
        pci_free_irq_vectors(lPciDev);
    }
}

void Memories_Prepare(TLBoDP_Device_PCIe* aThis)
{
    printk(KERN_DEBUG "TLBoDP: %s(  )\n", __FUNCTION__);

    ASSERT(NULL != aThis->mModuleName);

    struct pci_dev* lPciDev = aThis->mPciDev;
    ASSERT(NULL != lPciDev);

    if (0 == pci_request_mem_regions(lPciDev, aThis->mModuleName))
    {
        for (unsigned i = 0; i < 6; i ++)
        {
            if (IORESOURCE_MEM == (pci_resource_flags(lPciDev, i) & IORESOURCE_MEM))
            {
                phys_addr_t  lPA        = pci_resource_start(lPciDev, i);
                unsigned int lSize_byte = pci_resource_len  (lPciDev, i);

                volatile void * lKA = ioremap_uc(lPA, lSize_byte);
                if (NULL != lKA)
                {
                    printk(KERN_INFO "TLBoDP: %s - %u MEM 0x%llx %u bytes\n", __FUNCTION__, i, lPA, lSize_byte);

                    TLBoDP_Mapping_Set(aThis->mMemories + aThis->mMem_Count, lKA, lPA, lSize_byte);

                    aThis->mMem_Count ++;
                }
                else
                {
                    printk(KERN_ERR "TLBoDP: %s - ioremap_uc( 0x%llx, %u bytes ) failed\n", __FUNCTION__, lPA, lSize_byte);
                }
            }
        }
    }
}

void Memories_Release(TLBoDP_Device_PCIe* aThis)
{
    printk(KERN_DEBUG "TLBoDP: %s(  )\n", __FUNCTION__);

    struct pci_dev* lPciDev = aThis->mPciDev;
    ASSERT(NULL != lPciDev);

    for (unsigned int i = 0; i < aThis->mMem_Count; i++)
    {
        ASSERT(NULL != aThis->mMemories[i].mKernelAddress);

        iounmap(aThis->mMemories[i].mKernelAddress);
    }

    pci_release_mem_regions(lPciDev);
}

// ===== Entry points =======================================================

int Interrupt_ISR(int aInterrupt, void * aContext)
{
    printk(KERN_DEBUG "TLBoDP: %s( %u,  )\n", __FUNCTION__, aInterrupt);

    TLBoDP_Device_PCIe* lThis = aContext;

    tasklet_schedule(&lThis->mLinux.mTasklet);

    TLBoDP_Device_PCIe_Interrupt_0(lThis, aInterrupt);

    return IRQ_HANDLED;
}

void Tasklet(uint64_t aContext)
{
    TLBoDP_Device_PCIe* lThis = (TLBoDP_Device_PCIe*)aContext;

    TLBoDP_Device_PCIe_Interrupt_1(lThis, 0);
}

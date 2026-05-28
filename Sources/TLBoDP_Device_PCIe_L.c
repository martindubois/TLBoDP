
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      Sources/TLBoDP_Device_PCIe_L.c

// This file must be included into the DKMS package and be compiled at
// installation

// ===== Includes ===========================================================
#include <TLBoDP_Device_PCIe_L.h>

// Functions
// //////////////////////////////////////////////////////////////////////////

TLBoDP_Device_PCIe* TLBoDP_Device_PCIe_From_pci_dev(struct pci_dev* aPciDev)
{
    printk(KERN_DEBUG PREFIX "%s(  )\n", __FUNCTION__);

    ASSERT(NULL != aPciDev);

    TLBoDP_Device* lResult = pci_get_drvdata(aPciDev);
    ASSERT(NULL != lResult);

    return lResult;
}

TLBoDP_Result TLBoDP_Device_PCIe_New(struct pci_dev* aPciDev, unsigned int aContextSize_byte)
{
    printk(KERN_DEBUG PREFIX "%s( , %u bytes )\n", __FUNCTION__, aContextSize_byte);

    ASSERT(NULL != aPciDev);

    unsigned int lContextSize_byte = sizeof(TLBoDP_Device_PCIe);

    if (0 < aContextSize_byte)
    {
        ASSERT(sizeof(TLBoDP_Device_PCIe) <= aContextSize_byte);

        lContextSize_byte = aContextSize_byte;
    }

    TLBoDP_Device_PCIe* lThis = kmalloc(lContextSize_byte, GFP_KERNEL);
    ASSERT(NULL != lThis);

    lThis->mState = TLBoDP_DEVICE_CREATED;

    pci_set_drvdata(aPciDev, lThis);

    return TLBoDP_OK;
}

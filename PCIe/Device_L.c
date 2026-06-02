
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      PCIe/Device_L.c

#include "Component.h"

// ===== Linux ==============================================================
#include <linux/pci.h>

// ===== Includes ===========================================================
#include <TLBoDP_Device_PCIe.h>
#include <TLBoDP_Device_PCIe_L.h>
#include <TLBoDP_Result_L.h>

// ===== Local ==============================================================
#include "Device.h"

#include "Device_L.h"

// Functions
// //////////////////////////////////////////////////////////////////////////

// ===== Entry point ========================================================

int Device_Probe(struct pci_dev* aPciDev, const struct pci_device_id* aId)
{
    printk(KERN_DEBUG PREFIX "%s( ,  )\n", __FUNCTION__);

    TLBoDP_Result lRet = TLBoDP_Device_PCIe_New(0, aPciDev);
    if (TLBoDP_OK == lRet)
    {
        TLBoDP_Device_PCIe* lThis = TLBoDP_Device_PCIe_From_pci_dev(aPciDev);
        ASSERT(NULL != lThis);

        TLBoDP_Device_PCIe_SetModuleName(lThis, MODULE_NAME);

        lRet = Device_PrepareHardware(lThis);
        if (TLBoDP_OK == lRet)
        {
            lRet = Device_D0Entry(lThis);
            if (TLBoDP_OK != lRet)
            {
                Device_ReleaseHardware(lThis);
            }
        }

        if (TLBoDP_OK != lRet)
        {
            TLBoDP_Device_PCIe_Delete(lThis);
        }
    }

    return TLBoDP_Result_To_int(lRet);
}

void Device_Remove(struct pci_dev* aPciDev)
{
    printk(KERN_DEBUG PREFIX "%s(  )\n", __FUNCTION__);

    TLBoDP_Device_PCIe* lThis = TLBoDP_Device_PCIe_From_pci_dev(aPciDev);
    ASSERT(NULL != lThis);

    Device_D0Exit(lThis);

    Device_ReleaseHardware(lThis);

    TLBoDP_Device_PCIe_Delete(lThis);
}

int Device_Resume(struct pci_dev * aPciDev)
{
    printk(KERN_DEBUG PREFIX "%s(  )\n", __FUNCTION__);

    TLBoDP_Device_PCIe* lThis = TLBoDP_Device_PCIe_From_pci_dev(aPciDev);
    ASSERT(NULL != lThis);

    TLBoDP_Result lRet = Device_D0Entry(lThis);

    return TLBoDP_Result_To_int(lRet);
}

int Device_Suspend(struct pci_dev * aPciDev, pm_message_t aState)
{
    printk(KERN_DEBUG PREFIX "%s( ,  )\n", __FUNCTION__);

    TLBoDP_Device_PCIe* lThis = TLBoDP_Device_PCIe_From_pci_dev(aPciDev);
    ASSERT(NULL != lThis);

    Device_D0Exit(lThis);

    return 0;
}

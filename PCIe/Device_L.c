
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      PCIe/Device_L.c

#include "Component.h"

// ===== Local ==============================================================
#include "Device_L.h"

// Functions
// //////////////////////////////////////////////////////////////////////////

// ===== Entry point ========================================================

int Device_Probe (struct pci_dev* aPciDev, const struct pci_device_id* aId)
{
    printk(KERN_DEBUG PREFIX "%s( ,  )\n", __FUNCTION__);

    auto lRet = TLPoDP_Device_PCIe_New(aPciDev, 0);

    return TLBoDP_Result_To_int(lRet);
}

void Device_Remove(struct pci_dev* aPciDev)
{
    printk(KERN_DEBUG PREFIX "%s(  )\n", __FUNCTION__);

    TLBoDP_Device_PCIe* lThis = TLBoDP_Device_PCIe_From_pci_dev(aPciDev);
    ASSERT(NULL != lThis);

    TLBoDP_Device_PCIe_Delete(lThis);
}


// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      PCIe/Device_L.h

#pragma once

// Functions
// //////////////////////////////////////////////////////////////////////////

// ===== Entry points =======================================================
extern int  Device_Probe  (struct pci_dev * aPciDev, const struct pci_device_id * aId);
extern void Device_Remove (struct pci_dev * aPciDev);
extern int  Device_Resume (struct pci_dev * aPciDev);
extern int  Device_Suspend(struct pci_dev * aPciDev, pm_message_t aState);

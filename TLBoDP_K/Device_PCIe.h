
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      TLBoDP_K/Device_PCIe.h

#pragma once

// Functions
// //////////////////////////////////////////////////////////////////////////

extern void Device_PCIe_Init(TLBoDP_Device_PCIe* aThis);

extern void Device_PCIe_Interrupt_0(TLBoDP_Device_PCIe* aThis, void* aOSDep);
extern void Device_PCIe_Interrupt_1(TLBoDP_Device_PCIe* aThis, void* aOSDep);


// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      PCIe/Device.h

#pragma once

// ===== Includes ===========================================================
#include <TLBoDP_Device_PCIe.h>
#include <TLBoDP_Result.h>

#ifdef __cplusplus
    extern "C" {
#endif

// Functions
// //////////////////////////////////////////////////////////////////////////

extern TLBoDP_Result Device_D0Entry(TLBoDP_Device_PCIe* aThis);
extern void          Device_D0Exit (TLBoDP_Device_PCIe* aThis);

extern TLBoDP_Result Device_PrepareHardware(TLBoDP_Device_PCIe* aThis);
extern void          Device_ReleaseHardware(TLBoDP_Device_PCIe* aThis);

#ifdef __cplusplus
    }
#endif

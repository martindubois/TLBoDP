
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      Sources/TLBoDP_Device_L.c

// This file must be included into the DKMS package and be compiled at
// installation

// ===== Includes ===========================================================
#include <TLBoDP_Assert_L.h>
#include <TLBoDP_Device.h>

#include <TLBoDP_Device_L.h>

// Functions
// //////////////////////////////////////////////////////////////////////////

void TLBoDP_Device_Delete(TLBoDP_Device* aThis)
{
    printk(KERN_DEBUG PREFIX "%s( , %u bytes )\n", __FUNCTION__, aContextSize_byte);

    kfree(aThis);
}
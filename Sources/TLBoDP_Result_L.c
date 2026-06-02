
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      Sources/TLBoDP_Result_L.c

// This file must be included into the DKMS package and be compiled at
// installation

// ===== Linux ==============================================================
#include <linux/printk.h>
#include <linux/types.h>

// ===== Includes ===========================================================
#include <TLBoDP_Result_L.h>

// Functions
// //////////////////////////////////////////////////////////////////////////

int TLBoDP_Result_To_int(TLBoDP_Result aResult)
{
    printk(KERN_DEBUG "TLBoDP: %s( %u )\n", __FUNCTION__, aResult);

    int lResult = - __LINE__;

    switch (aResult)
    {
    case TLBoDP_OK: lResult = 0; break;

    default:
        printk(KERN_DEBUG "TLBoDP: %s - %u\n", __FUNCTION__, aResult);
        lResult = - __LINE__;
    }

    return lResult;
}

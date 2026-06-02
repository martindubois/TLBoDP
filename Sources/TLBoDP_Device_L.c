
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      Sources/TLBoDP_Device_L.c

// This file must be included into the DKMS package and be compiled at
// installation

// ===== Linux ==============================================================
#include <linux/slab.h>
#include <linux/types.h>

// ===== Includes ===========================================================
#include <TLBoDP_Assert_L.h>
#include <TLBoDP_Device.h>

#include <TLBoDP_Device_L.h>

// Functions
// //////////////////////////////////////////////////////////////////////////

TLBoDP_Result TLBoDP_Device_New(unsigned int aSize_byte, TLBoDP_Device** aDevice)
{
    printk(KERN_DEBUG "TLBoDP: %s( %u bytes,  )\n", __FUNCTION__, aSize_byte);

    ASSERT(NULL != aDevice);

    unsigned int lSize_byte = sizeof(TLBoDP_Device);

    if (0 < aSize_byte)
    {
        ASSERT(lSize_byte <= aSize_byte);

        lSize_byte = aSize_byte;
    }

    TLBoDP_Device* lThis = kmalloc(lSize_byte, GFP_KERNEL);
    ASSERT(NULL != lThis);

    TLBoDP_Device_Init(lThis);

    *aDevice = lThis;

    return TLBoDP_OK;
}

void TLBoDP_Device_Delete(TLBoDP_Device* aThis)
{
    printk(KERN_DEBUG "TLBoDP: %s(  )\n", __FUNCTION__);

    TLBoDP_Device_Uninit(aThis);

    kfree(aThis);
}

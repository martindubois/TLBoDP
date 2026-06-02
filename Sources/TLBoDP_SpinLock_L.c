
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      Sources/TLBoDP_SpinLock_L.c

// This file must be included into the DKMS package and be compiled at
// installation

// ===== Includes ===========================================================
#include <TLBoDP_SpinLock.h>

// Functions
// //////////////////////////////////////////////////////////////////////////

void TLBoDP_SpinLock_Init(TLBoDP_SpinLock* aThis, struct TLBoDP_Device_s* aDevice)
{
    printk(KERN_DEBUG "TLBoDP: %s( ,  )\n", __FUNCTION__);

    spin_lock_init(&aThis->mLinux.mSpinLock);
}

void TLBoDP_SpinLock_Lock(TLBoDP_SpinLock* aThis)
{
    printk(KERN_DEBUG "TLBoDP: %s(  )\n", __FUNCTION__);

    spin_lock_bh(&aThis->mLinux.mSpinLock);
}

void TLBoDP_SpinLock_Unlock(TLBoDP_SpinLock* aThis)
{
    printk(KERN_DEBUG "TLBoDP: %s(  )\n", __FUNCTION__);

    spin_unlock_bh(&aThis->mLinux.mSpinLock);
}

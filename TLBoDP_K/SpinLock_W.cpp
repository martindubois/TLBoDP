
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      TLBoDP_K/SpinLock_W.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <TLBoDP_Device.h>

#include <TLBoDP_SpinLock.h>

// Functions
// //////////////////////////////////////////////////////////////////////////

void TLBoDP_SpinLock_Init(TLBoDP_SpinLock* aThis, TLBoDP_Device* aDevice)
{
    // DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( ,  )\n");

    ASSERT(nullptr != aDevice);

    WDF_OBJECT_ATTRIBUTES lAttr;

    WDF_OBJECT_ATTRIBUTES_INIT(&lAttr);

    lAttr.ParentObject = aDevice->mDevice;

    auto lStatus = WdfSpinLockCreate(&lAttr, &aThis->mSpinLock);
    ASSERT(STATUS_SUCCESS == lStatus);
}

void TLBoDP_SpinLock_Lock(TLBoDP_SpinLock* aThis)
{
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "(  )\n");

    ASSERT(nullptr != aThis->mSpinLock);

    WdfSpinLockAcquire(aThis->mSpinLock);
}

void TLBoDP_SpinLock_Unlock(TLBoDP_SpinLock* aThis)
{
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "(  )\n");

    ASSERT(nullptr != aThis->mSpinLock);

    WdfSpinLockRelease(aThis->mSpinLock);
}

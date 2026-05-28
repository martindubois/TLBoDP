
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      TLBoDP_K/Device.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <TLBoDP_Device_PCIe.h>

// Functions
// //////////////////////////////////////////////////////////////////////////

TLBoDP_Result TLBoDP_Device_D0Entry(TLBoDP_Device* aThis)
{
    ASSERT((TLBoDP_DEVICE_PREPARED == aThis->mState) || (TLBoDP_DEVICE_OFF == aThis->mState));

    aThis->mState = TLBoDP_DEVICE_D0;

    return TLBoDP_OK;
}

void TLBoDP_Device_D0Exit(TLBoDP_Device* aThis)
{
    ASSERT(TLBoDP_DEVICE_D0 == aThis->mState);

    aThis->mState = TLBoDP_DEVICE_OFF;
}

TLBoDP_Result TLBoDP_Device_PrepareHardware(TLBoDP_Device* aThis)
{
    ASSERT(TLBoDP_DEVICE_CREATED == aThis->mState);

    aThis->mState = TLBoDP_DEVICE_PREPARED;

    return TLBoDP_OK;
}

void TLBoDP_Device_ReleaseHardware(TLBoDP_Device* aThis)
{
    ASSERT((TLBoDP_DEVICE_OFF == aThis->mState) || (TLBoDP_DEVICE_PREPARED == aThis->mState));

    aThis->mState = TLBoDP_DEVICE_RELEASED;
}

void Device_Init(TLBoDP_Device* aThis)
{
    aThis->mState = TLBoDP_DEVICE_CREATED;

    TLBoDP_Callback_List_Init(&aThis->mCallbacks, aThis);
}

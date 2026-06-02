
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      TLBoDP_K/Device_PCIe.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <TLBoDP_Callback.h>

// Static function declarations
// //////////////////////////////////////////////////////////////////////////

static bool IsFree    (TLBoDP_Callback* aThis);
static bool IsSelected(TLBoDP_Callback* aThis, void* aSender, uint32_t aType);
static bool IsSelected(TLBoDP_Callback* aThis, void* aSneder, uint32_t aTypes, TLBoDP_Callback_Function aFunction, void* aContext);
static bool IsSelected(TLBoDP_Callback* aThis,                uint32_t aType);

static void Register  (TLBoDP_Callback* aThis, void* aSender, uint32_t aTypes, TLBoDP_Callback_Function aFunction, void* aContext);
static void Unregister(TLBoDP_Callback* aThis);

static void List_Z0E(TLBoDP_Callback_List* aThis);
static void List_Z0L(TLBoDP_Callback_List* aThis);

// Functions
// //////////////////////////////////////////////////////////////////////////

void TLBoDP_Callback_Init(TLBoDP_Callback* aThis)
{
    aThis->mContext  = nullptr;
    aThis->mFunction = nullptr;
    aThis->mSender   = nullptr;
    aThis->mTypes    = 0;
}

TLBoDP_Result TLBoDP_Callback_Call(TLBoDP_Callback* aThis, uint32_t aType)
{
    ASSERT(0 != aType);

    auto lResult = TLBoDP_OK_NOT_REGISTERED;

    if (IsSelected(aThis, aType))
    {
        lResult = aThis->mFunction(aThis->mSender, aType, aThis->mContext);
    }

    return lResult;
}

bool TLBoDP_Callback_IsRegistered(TLBoDP_Callback* aThis)
{
    return nullptr != aThis->mFunction;
}

TLBoDP_Result TLBoDP_Callback_Register(TLBoDP_Callback* aThis, void* aSender, uint32_t aTypes, TLBoDP_Callback_Function aFunction, void* aContext)
{
    ASSERT(nullptr != aFunction);
    ASSERT(0 != aTypes);

    auto lResult = TLBoDP_ERROR_ALREADY_REGISTERED;

    if (IsFree(aThis))
    {
        Register(aThis, aSender, aTypes, aFunction, aContext);

        lResult = TLBoDP_OK;
    }

    return lResult;
}

TLBoDP_Result TLBoDP_Callback_Unregister(TLBoDP_Callback* aThis)
{
    auto lResult = TLBoDP_ERROR_NOT_REGISTERED;

    if (TLBoDP_Callback_IsRegistered(aThis))
    {
        Unregister(aThis);

        lResult = TLBoDP_OK;
    }

    return lResult;
}

void TLBoDP_Callback_List_Init(TLBoDP_Callback_List* aThis, struct TLBoDP_Device_s* aDevice)
{
    aThis->mActualDepth = 0;

    TLBoDP_SpinLock_Init(&aThis->mZone0, aDevice);
}

void TLBoDP_Callback_List_Uninit(TLBoDP_Callback_List* aThis)
{
    aThis->mActualDepth = 0;
}

TLBoDP_Result TLBoDP_Callback_List_Call(TLBoDP_Callback_List* aThis, void* aSender, uint32_t aType)
{
    ASSERT(0 != aType);

    auto lResult = TLBoDP_OK_NOT_REGISTERED;

    List_Z0E(aThis);
    {
        for (unsigned int i = 0; i < aThis->mActualDepth; i++)
        {
            auto lC = aThis->mCallbacks + i;

            if (IsSelected(lC, aSender, aType))
            {
                ASSERT(nullptr != lC->mFunction);

                auto lContext  = lC->mContext;
                auto lFunction = lC->mFunction;
                auto lSender   = lC->mSender;

                List_Z0L(aThis);
                {
                    lResult = lFunction(lSender, aType, lContext);
                }
                List_Z0E(aThis);

                if (TLBoDP_OK_STOP == lResult)
                {
                    lResult = TLBoDP_OK;
                    break;
                }

                if (TLBoDP_Result_IsError(lResult))
                {
                    break;
                }
            }
        }
    }
    List_Z0L(aThis);

    return lResult;
}

TLBoDP_Result TLBoDP_Callback_List_Call_FromISR(TLBoDP_Callback_List* aThis, void* aSender, uint32_t aType)
{
    ASSERT(0 != aType);

    auto lResult = TLBoDP_OK_NOT_REGISTERED;

    for (unsigned int i = 0; i < aThis->mActualDepth; i++)
    {
        auto lC = aThis->mCallbacks + i;

        if (IsSelected(lC, aSender, aType))
        {
            ASSERT(nullptr != lC->mFunction);

            lResult = lC->mFunction(lC->mSender, aType, lC->mContext);

            if (TLBoDP_OK_STOP == lResult)
            {
                lResult = TLBoDP_OK;
                break;
            }

            if (TLBoDP_Result_IsError(lResult))
            {
                break;
            }
        }
    }

    return lResult;
}

TLBoDP_Result TLBoDP_Callback_List_Register(TLBoDP_Callback_List* aThis, void* aSender, uint32_t aTypes, TLBoDP_Callback_Function aFunction, void* aContext)
{
    auto lResult = TLBoDP_ERROR_NOT_AVAILABLE;

    List_Z0E(aThis);
    {
        TLBoDP_Callback* lC = nullptr;

        for (unsigned int i = 0; i < aThis->mActualDepth; i++)
        {
            lC = aThis->mCallbacks + i;

            if (IsFree(lC))
            {
                lResult = TLBoDP_OK;
                break;
            }
        }

        if ((TLBoDP_ERROR_NOT_AVAILABLE == lResult) && (TLBoDP_CALLBACK_LIST_DEPTH > aThis->mActualDepth))
        {
            lC = aThis->mCallbacks + aThis->mActualDepth;

            aThis->mActualDepth++;

            TLBoDP_Callback_Init(lC);

            lResult = TLBoDP_OK;
        }

        if (TLBoDP_OK == lResult)
        {
            Register(lC, aSender, aTypes, aFunction, aContext);
        }
    }
    List_Z0L(aThis);

    return lResult;
}

TLBoDP_Result TLBoDP_Callback_List_Unregister(TLBoDP_Callback_List* aThis, void* aSender, uint32_t aTypes, TLBoDP_Callback_Function aFunction, void* aContext)
{
    auto lResult = TLBoDP_ERROR_NOT_REGISTERED;

    List_Z0E(aThis);
    {
        for (unsigned int i = 0; i < aThis->mActualDepth; i++)
        {
            auto lC = aThis->mCallbacks + i;

            if (IsSelected(lC, aSender, aTypes, aFunction, aContext))
            {
                Unregister(lC);

                lResult = TLBoDP_OK;

                break;
            }
        }
    }
    List_Z0L(aThis);

    return lResult;
}

// Static function declarations
// //////////////////////////////////////////////////////////////////////////

bool IsFree(TLBoDP_Callback* aThis)
{
    return nullptr == aThis->mFunction;
}

bool IsSelected(TLBoDP_Callback* aThis, void* aSender, uint32_t aType)
{
    return IsSelected(aThis, aType) && (aSender == aThis->mSender);
}

bool IsSelected(TLBoDP_Callback* aThis, void* aSender, uint32_t aTypes, TLBoDP_Callback_Function aFunction, void* aContext)
{
    ASSERT(nullptr != aFunction);
    ASSERT(0 != aTypes);

    return (aThis->mFunction == aFunction)
        && (aThis->mContext  == aContext)
        && (aThis->mSender   == aSender)
        && (aThis->mTypes    == aTypes);
}

bool IsSelected(TLBoDP_Callback* aThis, uint32_t aType)
{
    ASSERT(0 != aType);

    return (nullptr != aThis->mFunction) && (0 != (aThis->mTypes & aType));
}

void Register(TLBoDP_Callback* aThis, void* aSender, uint32_t aTypes, TLBoDP_Callback_Function aFunction, void* aContext)
{
    ASSERT(0 != aTypes);
    ASSERT(nullptr != aFunction);

    ASSERT(nullptr == aThis->mContext);
    ASSERT(nullptr == aThis->mFunction);
    ASSERT(nullptr == aThis->mSender);
    ASSERT(0 == aThis->mTypes);

    aThis->mContext  = aContext;
    aThis->mFunction = aFunction;
    aThis->mSender   = aSender;
    aThis->mTypes    = aTypes;
}

void Unregister(TLBoDP_Callback* aThis)
{
    ASSERT(nullptr != aThis->mFunction);
    ASSERT(0 != aThis->mTypes);

    aThis->mContext  = nullptr;
    aThis->mFunction = nullptr;
    aThis->mSender   = nullptr;
    aThis->mTypes    = 0;
}

void List_Z0E(TLBoDP_Callback_List* aThis) { TLBoDP_SpinLock_Lock  (&aThis->mZone0); }
void List_Z0L(TLBoDP_Callback_List* aThis) { TLBoDP_SpinLock_Unlock(&aThis->mZone0); }

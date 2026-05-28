
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      TLBoDP_K/Mapping.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <TLBoDP_Mapping.h>

// Functions
// //////////////////////////////////////////////////////////////////////////

void TLBoDP_Mapping_Init(TLBoDP_Mapping* aThis)
{
    aThis->mKernelAddress   = nullptr;
    aThis->mPhysicalAddress = TLBoDP_INVALID_PHYSICAL_ADDRESS;
    aThis->mSize_byte       = 0;
}

void TLBoDP_Mapping_Set(TLBoDP_Mapping* aThis, volatile void* aKernelAddress, uint64_t aPhysicalAddress, uint32_t aSize_byte)
{
    ASSERT(nullptr != aKernelAddress);
    ASSERT(0 != aPhysicalAddress);
    ASSERT(0 < aSize_byte);

    aThis->mKernelAddress   = aKernelAddress;
    aThis->mPhysicalAddress = aPhysicalAddress;
    aThis->mSize_byte       = aSize_byte;
}

volatile void* TLBoDP_Mapping_GetKernelAddress(TLBoDP_Mapping* aThis, uint32_t aOffset_byte, uint32_t aSize_byte)
{
    ASSERT(0 < aSize_byte);

    volatile void* lResult = nullptr;

    if ((nullptr != aThis->mKernelAddress) && (aThis->mSize_byte >= (aOffset_byte + aSize_byte)))
    {
        auto lBase = reinterpret_cast<volatile uint8_t*>(aThis->mKernelAddress);

        lResult = lBase + aOffset_byte;
    }

    return lResult;
}

uint64_t TLBoDP_Mapping_GetPhysicalAddress(TLBoDP_Mapping* aThis, uint32_t aOffset_byte, uint32_t aSize_byte)
{
    uint64_t lResult = TLBoDP_INVALID_PHYSICAL_ADDRESS;

    if ((TLBoDP_INVALID_PHYSICAL_ADDRESS != aThis->mPhysicalAddress) && (aThis->mSize_byte >= (aOffset_byte + aSize_byte)))
    {
        lResult = aThis->mPhysicalAddress + aOffset_byte;
    }

    return lResult;
}

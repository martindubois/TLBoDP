
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      TLBoDP_K/Device_PCIe.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <TLBoDP_Device_PCIe.h>

// Functions
// //////////////////////////////////////////////////////////////////////////

TLBoDP_Result TLBoDP_Device_PCIe_D0Entry(TLBoDP_Device_PCIe* aThis)
{
    return TLBoDP_Device_D0Entry(&aThis->mBase);
}

void TLBoDP_Device_PCIe_D0Exit(TLBoDP_Device_PCIe* aThis)
{
    TLBoDP_Device_D0Exit(&aThis->mBase);
}

void Device_PCIe_Init(TLBoDP_Device_PCIe* aThis)
{
    aThis->mInt_Count = 0;
    aThis->mMem_Count = 0;

    for (unsigned int i = 0; i < TLBoDP_DEVICE_PCIe_MEMORY_QTY; i++)
    {
        TLBoDP_Mapping_Init(aThis->mMemories + i);
    }
}

void Device_PCIe_Interrupt_0(TLBoDP_Device_PCIe* aThis, void* aOSDep)
{
    auto lResult = TLBoDP_Callback_List_Call_FromISR(&aThis->mBase.mCallbacks, aOSDep, TLBoDP_CALLBACK_INTERRUPT_0);
    (void)lResult;
}

void Device_PCIe_Interrupt_1(TLBoDP_Device_PCIe* aThis, void* aOSDep)
{
    auto lResult = TLBoDP_Callback_List_Call(&aThis->mBase.mCallbacks, aOSDep, TLBoDP_CALLBACK_INTERRUPT_1);
    (void)lResult;
}


// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      TLBoDP_K/Device_PCIe_W.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <TLBoDP_Device_PCIe.h>
#include <TLBoDP_Device_W.h>
#include <TLBoDP_Result_W.h>

#include <TLBoDP_Device_PCIe_W.h>

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static TLBoDP_Result PrepareInterrupt(TLBoDP_Device_PCIe* aThis, CM_PARTIAL_RESOURCE_DESCRIPTOR* aTranslated, CM_PARTIAL_RESOURCE_DESCRIPTOR* aRaw);
static TLBoDP_Result PrepareMemory   (TLBoDP_Device_PCIe* aThis, CM_PARTIAL_RESOURCE_DESCRIPTOR* aTranslated);

static void ReleaseMemories(TLBoDP_Device_PCIe* aThis);

// ===== Direct Windows entry points ========================================

EVT_WDF_INTERRUPT_DPC     Interrupt_DPC;
EVT_WDF_INTERRUPT_DISABLE Interrupt_Disable;
EVT_WDF_INTERRUPT_ENABLE  Interrupt_Enable;
EVT_WDF_INTERRUPT_ISR     Interrupt_ISR;

// Functions
// //////////////////////////////////////////////////////////////////////////

TLBoDP_Device_PCIe* TLBoDP_Device_PCIe_From_WDFDEVICE(WDFDEVICE aDevice)
{
    // DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "(  )\n");

    ASSERT(nullptr != aDevice);

    auto lResult = TLBoDP_Device_From_WDFDEVICE(aDevice);
    ASSERT(nullptr != lResult);

    return reinterpret_cast<TLBoDP_Device_PCIe*>(lResult);
}

TLBoDP_Device_PCIe* TLBoDP_Device_PCIe_From_WDFINTERRUPT(WDFINTERRUPT aInterrupt)
{
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "(  )\n");

    ASSERT(nullptr != aInterrupt);

    auto lDevice = WdfInterruptGetDevice(aInterrupt);

    auto lResult = TLBoDP_Device_PCIe_From_WDFDEVICE(lDevice);
    ASSERT(nullptr != lResult);

    return lResult;
}

TLBoDP_Result TLBoDP_Device_PCIe_New(unsigned int aSize_byte, WDFDEVICE_INIT* aDeviceInit, WDFDEVICE* aDevice)
{
    // DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( %u bytes, ,  )\n", aSize_byte);

    ASSERT(nullptr != aDevice);

    unsigned int lSize_byte = sizeof(TLBoDP_Device_PCIe);

    if (0 < aSize_byte)
    {
        ASSERT(lSize_byte <= aSize_byte);

        lSize_byte = aSize_byte;
    }

    WDFDEVICE lDevice;

    auto lResult = TLBoDP_Device_New(lSize_byte, aDeviceInit, &lDevice);
    if (TLBoDP_OK == lResult)
    {
        ASSERT(nullptr != lDevice);
        
        auto lThis = TLBoDP_Device_PCIe_From_WDFDEVICE(lDevice);

        TLBoDP_Device_PCIe_Init(lThis);

        *aDevice = lDevice;
    }

    return lResult;
}

TLBoDP_Result TLBoDP_Device_PCIe_PrepareHardware(TLBoDP_Device_PCIe* aThis)
{
    // DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "(  )\n");

    ASSERT(nullptr != aThis->mRaw);
    ASSERT(nullptr != aThis->mTranslated);

    auto lCount = WdfCmResourceListGetCount(aThis->mTranslated);

    auto lResult = TLBoDP_NOT_INITIALIZED;

    for (unsigned int i = 0; i < lCount; i++)
    {
        auto lDesc = WdfCmResourceListGetDescriptor(aThis->mTranslated, i);
        switch (lDesc->Type)
        {
        case CmResourceTypeInterrupt: lResult = PrepareInterrupt(aThis, lDesc, WdfCmResourceListGetDescriptor(aThis->mRaw, i)); break;
        case CmResourceTypeMemory   : lResult = PrepareMemory   (aThis, lDesc); break;
        }

        if (TLBoDP_OK != lResult)
        {
            break;
        }
    }

    if (TLBoDP_OK == lResult)
    {
        lResult = TLBoDP_Device_PrepareHardware(&aThis->mBase);
    }
    else
    {
        ReleaseMemories(aThis);
    }

    return lResult;
}

void TLBoDP_Device_PCIe_ReleaseHardware(TLBoDP_Device_PCIe* aThis)
{
    // DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "(  )\n");

    ReleaseMemories(aThis);

    TLBoDP_Device_ReleaseHardware(&aThis->mBase);
}

// ===== Direct Windows entry points ========================================

NTSTATUS TLBoDP_Device_PCIe_D0Entry_W(WDFDEVICE aDevice, WDF_POWER_DEVICE_STATE aPreviousState)
{
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( , %u )\n", aPreviousState);

    ASSERT(nullptr != aDevice);

    auto lThis = TLBoDP_Device_PCIe_From_WDFDEVICE(aDevice);
    ASSERT(nullptr != lThis);

    auto lRet = TLBoDP_Device_PCIe_D0Entry(lThis);

    return TLBoDP_Result_To_NTSTATUS(lRet);
}

NTSTATUS TLBoDP_Device_PCIe_D0Exit_W(WDFDEVICE aDevice, WDF_POWER_DEVICE_STATE aTargetState)
{
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( , %u )\n", aTargetState);

    ASSERT(nullptr != aDevice);

    auto lThis = TLBoDP_Device_PCIe_From_WDFDEVICE(aDevice);
    ASSERT(nullptr != lThis);

    TLBoDP_Device_PCIe_D0Exit(lThis);

    return STATUS_SUCCESS;
}

NTSTATUS TLBoDP_Device_PCIe_PrepareHardware_W(WDFDEVICE aDevice, WDFCMRESLIST aRaw, WDFCMRESLIST aTranslated)
{
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( , ,  )\n");

    auto lThis = TLBoDP_Device_PCIe_From_WDFDEVICE(aDevice);
    ASSERT(nullptr != lThis);

    TLBoDP_Device_PCIe_SetResourceLists(lThis, aRaw, aTranslated);

    auto lRet = TLBoDP_Device_PCIe_PrepareHardware(lThis);

    return TLBoDP_Result_To_NTSTATUS(lRet);
}

NTSTATUS TLBoDP_Device_PCIe_ReleaseHardware_W(WDFDEVICE aDevice, WDFCMRESLIST)
{
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( ,  )\n");

    auto lThis = TLBoDP_Device_PCIe_From_WDFDEVICE(aDevice);
    ASSERT(nullptr != lThis);

    TLBoDP_Device_PCIe_ReleaseHardware(lThis);

    return STATUS_SUCCESS;
}

// Static functions
/////////////////////////////////////////////////////////////////////////////

TLBoDP_Result PrepareInterrupt(TLBoDP_Device_PCIe* aThis, CM_PARTIAL_RESOURCE_DESCRIPTOR* aTranslated, CM_PARTIAL_RESOURCE_DESCRIPTOR* aRaw)
{
    // DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( , ,  )\n");

    ASSERT(nullptr != aTranslated);
    ASSERT(nullptr != aRaw);

    ASSERT(TLBoDP_DEVICE_PCIe_INTERRUPT_QTY > aThis->mInt_Count);

    WDF_INTERRUPT_CONFIG lConfig;

    WDF_INTERRUPT_CONFIG_INIT(&lConfig, Interrupt_ISR, Interrupt_DPC);

    lConfig.EvtInterruptDisable = Interrupt_Disable;
    lConfig.EvtInterruptEnable  = Interrupt_Enable;
    lConfig.InterruptRaw        = aRaw;
    lConfig.InterruptTranslated = aTranslated;

    auto lIndex = aThis->mInt_Count;

    auto lResult = TLBoDP_ERROR_WDF;

    auto lStatus = WdfInterruptCreate(aThis->mBase.mDevice, &lConfig, WDF_NO_OBJECT_ATTRIBUTES, aThis->mInterrupts + lIndex);
    if (STATUS_SUCCESS == lStatus)
    {
        ASSERT(nullptr != aThis->mInterrupts[lIndex]);

        aThis->mInt_Count++;

        lResult = TLBoDP_OK;
    }
    else
    {
        DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ " - TLBoDP_ERROR_WDF\n");
    }

    return lResult;
}

TLBoDP_Result PrepareMemory(TLBoDP_Device_PCIe* aThis, CM_PARTIAL_RESOURCE_DESCRIPTOR* aTranslated)
{
    // DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( ,  )\n");

    ASSERT(nullptr != aTranslated);

    ASSERT(TLBoDP_DEVICE_PCIe_MEMORY_QTY > aThis->mMem_Count);

    auto lIndex = aThis->mMem_Count;

    auto lPA        = aTranslated->u.Memory.Start;
    auto lSize_byte = aTranslated->u.Memory.Length;
    ASSERT(0 < lSize_byte);

    auto lKA = MmMapIoSpace(lPA, lSize_byte, MmNonCached);
    if (nullptr == lKA)
    {
        DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ " - TLBoDP_ERROR_WDM\n");

        return TLBoDP_ERROR_WDM;
    }

    auto lMapping = aThis->mMemories + lIndex;

    TLBoDP_Mapping_Set(lMapping, lKA, lPA.QuadPart, lSize_byte);

    aThis->mMem_Count++;

    return TLBoDP_OK;
}

void ReleaseMemories(TLBoDP_Device_PCIe* aThis)
{
    // DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "(  )\n");

    ASSERT(TLBoDP_DEVICE_PCIe_MEMORY_QTY > aThis->mMem_Count);

    for (unsigned int i = 0; i < aThis->mMem_Count; i++)
    {
        auto lMapping = aThis->mMemories + i;

        ASSERT(nullptr != lMapping->mKernelAddress);
        ASSERT(0 < lMapping->mSize_byte);

        MmUnmapIoSpace((void*)lMapping->mKernelAddress, lMapping->mSize_byte);

        TLBoDP_Mapping_Init(lMapping);
    }

    aThis->mMem_Count = 0;
}

// ===== Direct Windows entry points ========================================

void Interrupt_DPC(WDFINTERRUPT aInterrupt, WDFOBJECT aDevice)
{
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( ,  )\n");

    ASSERT(nullptr != aInterrupt);
    ASSERT(nullptr != aDevice);

    auto lThis = TLBoDP_Device_PCIe_From_WDFDEVICE(reinterpret_cast<WDFDEVICE>(aDevice));
    ASSERT(nullptr != lThis);

    Device_PCIe_Interrupt_1(lThis, aInterrupt);
}

NTSTATUS Interrupt_Disable(WDFINTERRUPT aInterrupt, WDFDEVICE aDevice)
{
    // DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( ,  )\n");

    ASSERT(nullptr != aInterrupt);
    ASSERT(nullptr != aDevice);

    auto lThis = TLBoDP_Device_PCIe_From_WDFDEVICE(aDevice);
    ASSERT(nullptr != lThis);

    // TODO

    return STATUS_SUCCESS;
}

NTSTATUS Interrupt_Enable(WDFINTERRUPT aInterrupt, WDFDEVICE aDevice)
{
    // DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( ,  )\n");

    ASSERT(nullptr != aInterrupt);
    ASSERT(nullptr != aDevice);

    auto lThis = TLBoDP_Device_PCIe_From_WDFDEVICE(aDevice);
    ASSERT(nullptr != lThis);

    // TODO

    return STATUS_SUCCESS;
}

BOOLEAN Interrupt_ISR(WDFINTERRUPT aInterrupt, ULONG aMessageId)
{
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( , 0x%08x )\n", aMessageId);

    ASSERT(nullptr != aInterrupt);

    WdfInterruptQueueDpcForIsr(aInterrupt);

    auto lThis = TLBoDP_Device_PCIe_From_WDFINTERRUPT(aInterrupt);
    ASSERT(nullptr != lThis);

    TLBoDP_Device_PCIe_Interrupt_0(lThis, aInterrupt);

    return TRUE;
}

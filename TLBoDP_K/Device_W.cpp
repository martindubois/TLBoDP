
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      TLBoDP_K/Device_W.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <TLBoDP_Device.h>
#include <TLBoDP_Result_W.h>

#include <TLBoDP_Device_W.h>

// ===== Local ==============================================================
#include "Device.h"

// Data type
// //////////////////////////////////////////////////////////////////////////

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(TLBoDP_Device, From_WDFDEVICE)

// Functions
// //////////////////////////////////////////////////////////////////////////

TLBoDP_Device* TLBoDP_Device_From_WDFDEVICE(WDFDEVICE aDevice)
{
    // DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "(  )\n");

    ASSERT(nullptr != aDevice);

    auto lResult = From_WDFDEVICE(aDevice);
    ASSERT(nullptr != lResult);

    return lResult;
}

TLBoDP_Result TLBoDP_Device_New(WDFDEVICE_INIT* aDeviceInit, unsigned int aContextSize_byte, WDFDEVICE* aDevice)
{
    // DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( , %u bytes )\n", aContextSize_byte);

    ASSERT(nullptr != aDeviceInit);
    ASSERT(nullptr != aDevice);

    WDF_OBJECT_ATTRIBUTES lAttr;

    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&lAttr, TLBoDP_Device);

    if (0 < aContextSize_byte)
    {
        ASSERT(sizeof(TLBoDP_Device) <= aContextSize_byte);

        lAttr.ContextSizeOverride = aContextSize_byte;
    }

    WDFDEVICE lDevice;

    auto lStatus = WdfDeviceCreate(&aDeviceInit, &lAttr, &lDevice);

    auto lResult = TLBoDP_Result_From_NTSTATUS(lStatus);
    if (TLBoDP_OK == lResult)
    {
        auto lThis = From_WDFDEVICE(lDevice);
        ASSERT(nullptr != lThis);

        lThis->mDevice = lDevice;

        TLBoDP_Device_Init(lThis);

        *aDevice = lDevice;
    }

    return lResult;
}

// ===== Direct Windows entry points ========================================

NTSTATUS TLBoDP_Device_D0Entry_W(WDFDEVICE aDevice, WDF_POWER_DEVICE_STATE aPreviousState)
{
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( , %u )\n", aPreviousState);

    ASSERT(nullptr != aDevice);

    auto lThis = From_WDFDEVICE(aDevice);
    ASSERT(nullptr != lThis);

    auto lRet = TLBoDP_Device_D0Entry(lThis);

    return TLBoDP_Result_To_NTSTATUS(lRet);
}

NTSTATUS TLBoDP_Device_D0Exit_W(WDFDEVICE aDevice, WDF_POWER_DEVICE_STATE aTargetState)
{
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( , %u )\n", aTargetState);

    ASSERT(nullptr != aDevice);

    auto lThis = From_WDFDEVICE(aDevice);
    ASSERT(nullptr != lThis);

    TLBoDP_Device_D0Exit(lThis);

    return STATUS_SUCCESS;
}

NTSTATUS TLBoDP_Device_PrepareHardware_W(WDFDEVICE aDevice, WDFCMRESLIST, WDFCMRESLIST)
{
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( , ,  )\n");

    auto lThis = From_WDFDEVICE(aDevice);
    ASSERT(nullptr != lThis);

    auto lRet = TLBoDP_Device_PrepareHardware(lThis);

    return TLBoDP_Result_To_NTSTATUS(lRet);
}

NTSTATUS TLBoDP_Device_ReleaseHardware_W(WDFDEVICE aDevice, WDFCMRESLIST)
{
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( ,  )\n");

    ASSERT(nullptr != aDevice);

    auto lThis = From_WDFDEVICE(aDevice);
    ASSERT(nullptr != lThis);

    TLBoDP_Device_ReleaseHardware(lThis);

    return STATUS_SUCCESS;
}


// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      PCIe/Device_W.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <TLBoDP_Device_PCIe.h>
#include <TLBoDP_Device_PCIe_W.h>
#include <TLBoDP_Device_W.h>
#include <TLBoDP_Result_W.h>

// ===== Local ==============================================================
#include "Device_W.h"

// Static function declarations
// //////////////////////////////////////////////////////////////////////////

// ===== Entry points =======================================================
static EVT_WDF_DEVICE_D0_ENTRY         D0Entry;
static EVT_WDF_DEVICE_D0_EXIT          D0Exit;
static EVT_WDF_DEVICE_PREPARE_HARDWARE PrepareHardware;
static EVT_WDF_DEVICE_RELEASE_HARDWARE ReleaseHardware;

// Functions
// //////////////////////////////////////////////////////////////////////////

// ===== Entry points =======================================================

#pragma alloc_text (PAGE, Device_Add)

NTSTATUS Device_Add(WDFDRIVER, PWDFDEVICE_INIT aDeviceInit)
{
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( ,  )\n");

    PAGED_CODE();

    ASSERT(nullptr != aDeviceInit);

    WDF_PNPPOWER_EVENT_CALLBACKS lPnpPowerEventCallbacks;

    WDF_PNPPOWER_EVENT_CALLBACKS_INIT(&lPnpPowerEventCallbacks);

    lPnpPowerEventCallbacks.EvtDeviceD0Entry = D0Entry;
    lPnpPowerEventCallbacks.EvtDeviceD0Exit  = D0Exit;

    lPnpPowerEventCallbacks.EvtDevicePrepareHardware = PrepareHardware;
    lPnpPowerEventCallbacks.EvtDeviceReleaseHardware = ReleaseHardware;

    WdfDeviceInitSetPnpPowerEventCallbacks(aDeviceInit, &lPnpPowerEventCallbacks);

    WDFDEVICE lDevice;

    auto lRet = TLBoDP_Device_PCIe_New(aDeviceInit, 0, &lDevice);
    ASSERT(nullptr != lDevice);
    (void)lDevice;

    return TLBoDP_Result_To_NTSTATUS(lRet);
}

// Static functions
// //////////////////////////////////////////////////////////////////////////

// ===== Entry points =======================================================

NTSTATUS D0Entry(WDFDEVICE aDevice, WDF_POWER_DEVICE_STATE aPreviousState)
{
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( , %u )\n", aPreviousState);

    ASSERT(nullptr != aDevice);

    auto lThis = TLBoDP_Device_PCIe_From_WDFDEVICE(aDevice);
    ASSERT(nullptr != lThis);

    // INSTRUCTION  Add the needed code here. If no code is needed, remove
    //              the D0Entry function and use
    //              TLBoDP_Device_PCIe_D0Entry_W.

    auto lRet = TLBoDP_Device_PCIe_D0Entry(lThis);

    return TLBoDP_Result_To_NTSTATUS(lRet);
}

NTSTATUS D0Exit(WDFDEVICE aDevice, WDF_POWER_DEVICE_STATE aTargetState)
{
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( , %u )\n", aTargetState);

    ASSERT(nullptr != aDevice);

    auto lThis = TLBoDP_Device_PCIe_From_WDFDEVICE(aDevice);
    ASSERT(nullptr != lThis);

    // INSTRUCTION  Add the needed code here. If no code is needed, remove
    //              the D0Exit function and use TLBoDP_Device_PCIe_D0Exit_W.

    TLBoDP_Device_PCIe_D0Exit(lThis);

    return STATUS_SUCCESS;
}

NTSTATUS PrepareHardware(WDFDEVICE aDevice, WDFCMRESLIST aRaw, WDFCMRESLIST aTranslated)
{
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( , ,  )\n");

    ASSERT(nullptr != aDevice);

    auto lThis = TLBoDP_Device_PCIe_From_WDFDEVICE(aDevice);
    ASSERT(nullptr != lThis);

    auto lRet = TLBoDP_Device_PCIe_PrepareHardware(lThis, aRaw, aTranslated);
    if (TLBoDP_OK == lRet)
    {
        // INSTRUCTION  Add the needed code here. If no code is needed,
        //              remove the PrepareHardware function and use
        //              TLBoDP_Device_PCIe_PrepareHardware_W.
    }

    return TLBoDP_Result_To_NTSTATUS(lRet);
}

NTSTATUS ReleaseHardware(WDFDEVICE aDevice, WDFCMRESLIST)
{
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( ,  )\n");

    ASSERT(nullptr != aDevice);

    auto lThis = TLBoDP_Device_PCIe_From_WDFDEVICE(aDevice);
    ASSERT(nullptr != lThis);

    // INSTRUCTION  Add the needed code here. If no code is needed, remove
    //              the ReleaseHardware function and use
    //              TLBoDP_Device_PCIe_ReleaseHardware_W.

    TLBoDP_Device_PCIe_ReleaseHardware(lThis);

    return STATUS_SUCCESS;
}

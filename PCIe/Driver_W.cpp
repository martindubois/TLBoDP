
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      PCIe/Driver_W.cpp

#include "Component.h"

// ===== Local ==============================================================
#include "Device_W.h"

// Entry points
// //////////////////////////////////////////////////////////////////////////

extern "C"
{
    DRIVER_INITIALIZE DriverEntry;
}

#pragma alloc_text (INIT, DriverEntry)

NTSTATUS DriverEntry(_DRIVER_OBJECT* aDriverObject, PUNICODE_STRING aRegistryPath)
{
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( ,  )\n");

    PAGED_CODE();

    ASSERT(nullptr != aDriverObject);
    ASSERT(nullptr != aRegistryPath);

    WDF_DRIVER_CONFIG lConfig;

    WDF_DRIVER_CONFIG_INIT(&lConfig, Device_Add);

    auto lResult = WdfDriverCreate(aDriverObject, aRegistryPath, WDF_NO_OBJECT_ATTRIBUTES, &lConfig, WDF_NO_HANDLE);
    if (STATUS_SUCCESS != lResult)
    {
        DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ " - WdfDriverCreate( , , , ,  ) failed - %08x\n", lResult);
    }

    return lResult;
}

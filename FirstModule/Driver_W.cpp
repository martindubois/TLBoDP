
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      FirstModule/Driver_W.cpp

#include "Component.h"

// ===== Local ==============================================================
#include "Driver.h"

// Static function declaration
// //////////////////////////////////////////////////////////////////////////

extern "C"
{
    static DRIVER_UNLOAD Unload;
}

// Entry points
// //////////////////////////////////////////////////////////////////////////

extern "C"
{
    DRIVER_INITIALIZE DriverEntry;
}

#pragma alloc_text (INIT, DriverEntry)

NTSTATUS DriverEntry(_DRIVER_OBJECT* aDriverObject, PUNICODE_STRING aRegistryPath)
{
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, __FUNCTION__ "( ,  )\n");

    ASSERT(nullptr != aDriverObject);

    (void)aRegistryPath;

    ASSERT(nullptr == aDriverObject->DriverUnload);

    aDriverObject->DriverUnload = Unload;

    return Driver_Load() ? STATUS_SUCCESS : STATUS_UNSUCCESSFUL;
}

// Static functions
// //////////////////////////////////////////////////////////////////////////

VOID Unload(_DRIVER_OBJECT* aDriverObject)
{
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, __FUNCTION__ "(  )\n");

    (void)aDriverObject;

    Driver_Unload();
}

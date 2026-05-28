
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      TLBoDP_K/Result_W.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <TLBoDP_Result_W.h>

// Functions
// //////////////////////////////////////////////////////////////////////////

TLBoDP_Result TLBoDP_Result_From_NTSTATUS(NTSTATUS aStatus)
{
    // DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( 0x%08x )\n", aStatus);

    auto lResult = TLBoDP_ERROR_UNEXPECTED_NTSTATUS;

    switch (aStatus)
    {
    case STATUS_SUCCESS: lResult = TLBoDP_OK; break;

    case STATUS_UNSUCCESSFUL: lResult = TLBoDP_ERROR; break;

    default: ASSERT(false);
    }

    return lResult;
}

NTSTATUS TLBoDP_Result_To_NTSTATUS(TLBoDP_Result aResult)
{
    // DbgPrintEx(DPFLTR_IHVDRIVER_ID, 0, PREFIX __FUNCTION__ "( %u )\n", aResult);

    auto lResult = STATUS_INVALID_PARAMETER;

    switch (aResult)
    {
    case TLBoDP_OK: lResult = STATUS_SUCCESS; break;

    case TLBoDP_ERROR: lResult = STATUS_UNSUCCESSFUL; break;

    default: ASSERT(false);
    }

    return lResult;
}
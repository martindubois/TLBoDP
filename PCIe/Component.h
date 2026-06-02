
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      PCIe/Component.h

#pragma once

#ifdef _TLBoDP_LINUX_

    // ===== Includes =======================================================
    #include <TLBoDP_Assert_L.h>
    #include <TLBoDP_StdTypes.h>

#endif

#ifdef _TLBoDP_WINDOWS_

    // ===== Windows ========================================================
    #include <ntddk.h>

    // ===== WDF ============================================================
    #include <wdf.h>

#endif

// Constants
// //////////////////////////////////////////////////////////////////////////

#define MODULE_NAME "PCIe"

#define PREFIX "PCIe: "

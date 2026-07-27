
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   GPL-2.0 https://opensource.org/license/gpl-2.0
// Product   TLBoDP
// File      Sources/TLBoDP_Trace_L.c

// This file must be included into the DKMS package and be compiled at
// installation

// ===== Linux ==============================================================
#include <linux/printk.h>

// ===== Includes ===========================================================
#include <TLBoDP_Trace.h>

// Functions
// //////////////////////////////////////////////////////////////////////////

void TLBoDP_Trace_Error(const char* aFile, const char* aFunction, unsigned int aLine, const char* aMessage, unsigned int aInfo)
{
    printk(KERN_ERR "TLBoDP: %s %s (%u) - %s (%u)\n", aFile, aFunction, aLine, aMessage, aInfo);
}

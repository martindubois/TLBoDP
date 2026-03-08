
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      FirstModule/Driver.h

#pragma once

#ifdef __cplusplus
    extern "C" {
#endif

// Functions
// //////////////////////////////////////////////////////////////////////////

// Return  false  Errro
//         true   OK
extern bool Driver_Load(void);

extern void Driver_Unload(void);

#ifdef __cplusplus
    }
#endif

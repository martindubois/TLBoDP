
// Product TLBoDP

/// \author    KMS - Martin Dubois, P. Eng.
/// \copyright Copyright &copy; 2026 KMS
/// \file      Includes/TLBoDP_StdTypes.h
/// \brief     Standard types

#pragma once

#ifdef __cplusplus
    extern "C" {
#endif

// Data types
// //////////////////////////////////////////////////////////////////////////

typedef int int32_t;

typedef unsigned char uint8_t;
typedef unsigned int  uint32_t;

#ifdef _TLBoDP_LINUX_
    #ifndef MODULE
        typedef unsigned long long uint64_t;
    #endif
#endif

#ifdef _TLBoDP_WINDOWS_
    typedef unsigned long long uint64_t;
#endif

#ifdef __cplusplus
    }
#endif

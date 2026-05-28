
// Product TLBoDP

/// \author    KMS - Martin Dubois, P. Eng.
/// \copyright Copyright &copy; 2026 KMS
/// \file      Includes/TLBoDP_Assert_L.h
/// \brief     ASSERT on Linux
///
/// To use in Linux C/C++ code
///
/// This file define ASSERT as the WDK define it for Windows driver.

#pragma once

// ===== Includes ===========================================================
#include <TLBoDP_Trace.h>

// Macros
// //////////////////////////////////////////////////////////////////////////

#ifdef MODULE

    /// \brief Assert
    /// \param C Condition
    ///
    /// To use in Linux C code.
    #define ASSERT(C)                                               \
        if (!(C))                                                   \
        {                                                           \
            printk(KERN_ERR PREFIX "%s %s (%u) - Assert failure\n", \
                __FILE__, __FUNCTION__, __LINE__);                  \
        }

#else

    /// \brief Assert
    /// \param C Condition
    ///
    /// To use in common code or C++ code on Linux.
    #define ASSERT(C)                                                                  \
        if (!(C))                                                                      \
        {                                                                              \
            TLBoDP_Trace_Error(__FILE__, __FUNCTION__, __LINE__, "Assert failure", 0); \
        }

#endif

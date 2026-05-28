
// Product TLBoDP

/// \author    KMS - Martin Dubois, P. Eng.
/// \copyright Copyright &copy; 2026 KMS
/// \file      Includes/TLBoDP_Trace.h
/// \brief     TLBoDP_Trace_...

#pragma once

#ifdef __cplusplus
    extern "C" {
#endif

// Functions
// //////////////////////////////////////////////////////////////////////////

/// \brief Add error information to trace
/// \param aFile     The source file name
/// \param aFunction The function name
/// \param aLine     The source line
/// \param aMessage  The error message
/// \param aInfo     An information
///
/// To use in common code or in Linux C++ code. Use printk in Linux C code.
/// Use DbgPrintEx in Windows code.
extern void TLBoDP_Trace_Error(const char* aFile, const char* aFunction, unsigned int aLine, const char* aMessage, unsigned int aInfo);

#ifdef __cplusplus
    }
#endif

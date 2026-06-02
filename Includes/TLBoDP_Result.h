
// Product TLBoDP

/// \author    KMS - Martin Dubois, P. Eng.
/// \copyright Copyright &copy; 2026 KMS
/// \file      Includes/TLBoDP_Result.h
/// \brief     TLBoDP_Result

#pragma once

#ifdef __cplusplus
    extern "C" {
#endif

// Data types
// //////////////////////////////////////////////////////////////////////////

/// \brief Result codes
typedef enum
{
    TLBoDP_OK = 0,

    TLBoDP_OK_COMPLETE,
    TLBoDP_OK_NOT_REGISTERED,
    TLBoDP_OK_PENDING,
    TLBoDP_OK_QUEUE,
    TLBoDP_OK_STOP,

    TLBoDP_OK_END,

    TLBoDP_ERROR = 0x0100,
    
    TLBoDP_ERROR_ALREADY_REGISTERED,
    TLBoDP_ERROR_INVALID_CONTEXT_SIZE,
    TLBoDP_ERROR_INVALID_FUNCTION,
    TLBoDP_ERROR_INVALID_TYPES,
    TLBoDP_ERROR_LINUX_PCI,
    TLBoDP_ERROR_NOT_AVAILABLE,
    TLBoDP_ERROR_NOT_IN_LIST,
    TLBoDP_ERROR_NOT_REGISTERED,
    TLBoDP_ERROR_UNEXPECTED_NTSTATUS,
    TLBoDP_ERROR_WDF,
    TLBoDP_ERROR_WDM,

    TLBoDP_ERROR_END,

    TLBoDP_NOT_INITIALIZED = 0xff00,
}
TLBoDP_Result;

// Inlines functions
// //////////////////////////////////////////////////////////////////////////

static inline bool TLBoDP_Result_IsError(TLBoDP_Result aIn) { return TLBoDP_ERROR <= aIn; }

#ifdef __cplusplus
    }
#endif

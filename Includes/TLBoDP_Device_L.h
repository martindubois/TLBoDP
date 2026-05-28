
// Product TLBoDP

/// \author    KMS - Martin Dubois, P. Eng.
/// \copyright Copyright &copy; 2026 KMS
/// \file      Includes/TLBoDP_Device_L.h
/// \brief     TLBoDP_Device on Linux
///
/// To be used in Liunx C code

#pragma once

// ===== Includes ===========================================================
#include <TLBoDP_Result.h>

#ifdef __cplusplus
    #error Do not use this header file in C++
#endif

struct TLBoDevice_s;

// Functions
// //////////////////////////////////////////////////////////////////////////

/// \brief Delete a TLBoDP_Device instance
/// \param aThis The TLBoDP_Device instance to delete
/// \see TLBoDP_Device_New
///
/// To use in Linux C code, from the Remove entry point
extern void TLBoDP_Device_Delete(struct TLBoDP_Device_s* aThis);


// Product TLBoDP

/// \author    KMS - Martin Dubois, P. Eng.
/// \copyright Copyright &copy; 2026 KMS
/// \file      Includes/TLBoDP_Result_L.h
/// \brief     TLBoDP_Result on Linux

#pragma once

// ===== Includes ===========================================================
#include <TLBoPD_Result.h>

#ifdef __cplusplus
    extern "C" {
#endif

// Functions
// //////////////////////////////////////////////////////////////////////////

/// \brief Convert a TLBoDP_Result value in a Linux return code
/// \param aResult The TLBoDP_Result value
/// \retval The converted value
///
/// To use in Linux code.
extern int TLBoDP_Result_To_int(TLBoDP_Result aResult);

#ifdef __cplusplus
    }
#endif

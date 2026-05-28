
// Product TLBoDP

/// \author    KMS - Martin Dubois, P. Eng.
/// \copyright Copyright &copy; 2026 KMS
/// \file      Includes/TLBoDP_Result_W.h
/// \brief     TLBoDP_Result on Windows

#pragma once

// ===== Includes ===========================================================
#include <TLBoDP_Result.h>

// Functions
// //////////////////////////////////////////////////////////////////////////

/// \brief Convert a NTSTATUS value into a TLBoDP_Result value
/// \param aStatus The NTSTATUS value to convert
/// \retval TLBoDP_ERROR_UNEXPECTED_NTSTATUS
/// \see TLBoDP_Result_To_NTSTATUS
///
/// To use in Windows code
extern TLBoDP_Result TLBoDP_Result_From_NTSTATUS(NTSTATUS aStatus);

/// \brief Convert a TLBoDP_Result value into a NTSTATUS value
/// \param aResult The TLBoDP_Result value to convert
/// \retval STATUS_INVALID_PARAMETER
/// \see TLBoDP_Result_From_NTSTATUS
///
/// To use in Windows code
extern NTSTATUS TLBoDP_Result_To_NTSTATUS(TLBoDP_Result aResult);


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

struct TLBoDP_Device_s;

// Functions
// //////////////////////////////////////////////////////////////////////////

/// \brief Create a new TLBoCP_Device instance
/// \param aSize_byte The context size
/// \param aDevice    The function return the new instance here
/// \retval TlBoDP_OK
/// \see TLBoDP_Device_Delete
///      TLBoDP_Device_PCIe_New
///
/// To use in Linux C code, from the probe entry point
extern TLBoDP_Result TLBoDP_Device_New(unsigned int aSize_byte, struct TLBoDP_Device_s** aDevice);

/// \brief Delete a TLBoDP_Device instance
/// \param aThis The TLBoDP_Device instance to delete
/// \see TLBoDP_Device_New
///
/// To use in Linux C code, from the Remove entry point
extern void TLBoDP_Device_Delete(struct TLBoDP_Device_s* aThis);

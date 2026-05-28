
// Product TLBoDP

/// \author    KMS - Martin Dubois, P. Eng.
/// \copyright Copyright &copy; 2026 KMS
/// \file      Includes/TLBoDP_Mapping.h
/// \brief     TLBoDP_Mapping

#pragma once

// ===== Includes ===========================================================
#include <TLBoDP_StdTypes.h>

#ifdef __cplusplus
    extern "C" {
#endif

// Data types
// //////////////////////////////////////////////////////////////////////////

/// \brief Invalid physical address
#define TLBoDP_INVALID_PHYSICAL_ADDRESS (0xffffffffffffffff)

/// \brief Memory mapping information
/// \see TLBoDP_Mapping_Init
///      TLBoDP_Mapping_Set
///      TLBoDP_Mapping_GetKernelAddress
///      TLBoDP_Mapping_GetPhysicalAddress
typedef struct TLBoDP_Mapping_s
{
    volatile void* mKernelAddress;
    uint64_t       mPhysicalAddress;

    uint32_t mSize_byte;
}
TLBoDP_Mapping;

// Functions
// //////////////////////////////////////////////////////////////////////////

/// \brief Initialize a TLBoDP_Mapping instance
/// \param aThis The TLBoDP_Mapping instance
extern void TLBoDP_Mapping_Init(TLBoDP_Mapping* aThis);

/// \brief Set a mapping using kernel address and a physical address
/// \param aThis            The TLBoDP_Mapping instance
/// \param aKernelAddress   The kernel address
/// \param aPhysicalAddress The physical address
/// \param aSize_byte       The size
extern void TLBoDP_Mapping_Set(TLBoDP_Mapping* aThis, volatile void* aKernelAddress, uint64_t aPhysicalAddress, uint32_t aSize_byte);

/// \brief Retrieve a kernel address
/// \param aThis        The TLBoDP_Mapping instance
/// \param aOffset_byte The offset into the mapping
/// \param aSize_byte   The needed size
/// \retval nullptr  Error
/// \retval Other    The requested address
extern volatile void* TLBoDP_Mapping_GetKernelAddress(TLBoDP_Mapping* aThis, uint32_t aOffset_byte, uint32_t aSize_byte);

/// \brief Retrieve a physical address
/// \param aThis        The TLBoDP_Mapping instance
/// \param aOffset_byte The offset into the mapping
/// \param aSize_byte   The needed size
/// \retval TLBoDP_INVALID_PHYSICAL_ADDRESS  Error
/// \retval Other                            The requested address
extern uint64_t TLBoDP_Mapping_GetPhysicalAddress(TLBoDP_Mapping* aThis, uint32_t aOffset_byte, uint32_t aSize_byte);

#ifdef __cplusplus
    }
#endif

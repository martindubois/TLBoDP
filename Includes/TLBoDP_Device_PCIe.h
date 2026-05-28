
// Product TLBoDP

/// \author    KMS - Martin Dubois, P. Eng.
/// \copyright Copyright &copy; 2026 KMS
/// \file      Includes/TLBoDP_Device_PCIe.h
/// \brief     TLBoDP_Device_PCIe

#pragma once

// ===== Includes ===========================================================
#include <TLBoDP_Device.h>
#include <TLBoDP_Mapping.h>
#include <TLBoDP_StdTypes.h>

#ifdef __cplusplus
    extern "C" {
#endif

// Constants
// //////////////////////////////////////////////////////////////////////////

/// \brief Callback type for low level interrupt handler (ISR)
#define TLBoDP_CALLBACK_INTERRUPT_0 (0x00000001)

/// \brief Callback type for high level interrupt handler (DPC / tasklet)
#define TLBoDP_CALLBACK_INTERRUPT_1 (0x00000002)

// Data types
// //////////////////////////////////////////////////////////////////////////

/// \brief Maximum number of hardware memory area (BAR) for a device
#define TLBoDP_DEVICE_PCIe_MEMORY_QTY (8)

#ifdef _TLBoDP_WINDOWS_
    /// \brief Maximum number of interrupt for a device
    #define TLBoDP_DEVICE_PCIe_INTERRUPT_QTY (32)
#endif

/// \brief PCIe device base context
/// \see TLBoDP_Device_PCIe_D0Entry
///      TLBoDP_Device_PCIe_D0Exit
///      TLBoDP_Device_PCIe_ReleaseHardware
typedef struct TLBoDP_Device_PCIe_s
{
    TLBoDP_Device mBase; ///< Base class

    unsigned int mInt_Count;
    unsigned int mMem_Count;

    TLBoDP_Mapping mMemories[TLBoDP_DEVICE_PCIe_MEMORY_QTY];

    #ifdef _TLBoDP_WINDOWS_
        WDFINTERRUPT mInterrupts[TLBoDP_DEVICE_PCIe_INTERRUPT_QTY];
    #endif
}
TLBoDP_Device_PCIe;

// Functions
// //////////////////////////////////////////////////////////////////////////

/// \brief Enter D0 state
/// \param aThis The TLBoDP_Device_PCIe instance
/// \retval TLBoDP_OK
extern TLBoDP_Result TLBoDP_Device_PCIe_D0Entry(TLBoDP_Device_PCIe* aThis);

/// \brief Leave D0 state
/// \param aThis The TLBoDP_Device_PCIe instance
extern void TLBoDP_Device_PCIe_D0Exit(TLBoDP_Device_PCIe* aThis);

/// \brief Release hardware resources
/// \param aThis The TLBoDP_Device_PCIe instance
extern void TLBoDP_Device_PCIe_ReleaseHardware(TLBoDP_Device_PCIe* aThis);

#ifdef __cplusplus
    }
#endif

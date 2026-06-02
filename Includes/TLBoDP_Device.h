
// Product TLBoDP

/// \author    KMS - Martin Dubois, P. Eng.
/// \copyright Copyright &copy; 2026 KMS
/// \file      Includes/TLBoDP_Device.h
/// \brief     TLBoDP_Device

#pragma once

// ===== Includes ===========================================================
#include <TLBoDP_Callback.h>
#include <TLBoDP_Result.h>

#ifdef __cplusplus
    extern "C" {
#endif

// Data types
// //////////////////////////////////////////////////////////////////////////

/// \brief State of a device
/// \code
/// --> CREATED ---error--------------------------+
///      |                                        |
///      +--> PREPARED ---error---+               |
///            |                  |               |
///            +--> D0 <--+       |               |
///                  |    |       |               |
///                  +--> OFF ----+==> RELEASED --+==> Deleted
/// \endcode
typedef enum
{
    TLBoDP_DEVICE_CREATED = 0,
    TLBoDP_DEVICE_D0,
    TLBoDP_DEVICE_OFF,
    TLBoDP_DEVICE_PREPARED,
    TLBoDP_DEVICE_RELEASED,
}
TLBoDP_Device_State;

/// \brief Base class for device object
/// \see TLBoDP_Device_New
///      TLBoDP_Device_D0Entry
///      TLBoDP_Device_D0Exit
///      TLBoDP_Device_PrepareHardware
///      TLBoDP_Device_PrepareHardware
typedef struct TLBoDP_Device_s
{
    TLBoDP_Device_State mState;

    TLBoDP_Callback_List mCallbacks;

    #ifdef _TLBoDP_WINDOWS_
        WDFDEVICE mDevice;
    #endif
}
TLBoDP_Device;

// Functions
// //////////////////////////////////////////////////////////////////////////

/// \brief Initialize an allocated TLBoDP_Device instance
/// \param aThis The TLBoDP_Device instance
/// \see TLBoDP_Device_New
///
/// This function is called from TLBoDP_Device_New and the driver code
/// should not call it directly.
extern void TLBoDP_Device_Init(TLBoDP_Device* aThis);

/// \brief Uninitialize a TLBoDP_Device instance
/// \param aThis The TLBoDP_Device instance
/// \see TLBoDP_Device_Delete
///
/// This function is called from TLBoDP_Device_Delete and the driver code
/// should not call it directly.
extern void TLBoDP_Device_Uninit(TLBoDP_Device* aThis);

/// \brief TLBoDP_STATE_PREPARED --> TLBoDP_STATE_D0
/// \param aThis The TLBoDP_Device instance
/// \retval TLPoDP_OK
/// \see TLBoDP_Device_D0Exit
///
/// To use in Linux C code or in Windows code
extern TLBoDP_Result TLBoDP_Device_D0Entry(TLBoDP_Device* aThis);

/// \brief TLBoDP_STATE_D0 --> TLBoDP_STATE_OFF
/// \param aThis The TLBoDP_Device instance
/// \see TLBoDP_Device_D0Entry
///
/// To use in Linux C code or in Windows code
extern void TLBoDP_Device_D0Exit(TLBoDP_Device* aThis);

/// \brief TLBoDP_STATE_CREATED --> TLBoDP_STATE_PREPARED
/// \param aThis The TLBoDP_Device instance
/// \retval TLPoDP_OK
/// \see TLBoDP_Device_ReleaseHardware
///
/// To use in Linux C code or in Windows code
extern TLBoDP_Result TLBoDP_Device_PrepareHardware(TLBoDP_Device* aThis);

/// \brief TLBoDP_STATE_OFF or TLBoDP_STATE_PREPARED --> TLBoDP_STATE_RELEASED
/// \param aThis The TLBoDP_Device instance
/// \see TLBoDP_Device_D0Entry
///      TLBoDP_Device_PrepareHardware
///
/// To use in Linux C code or in Windows code
extern void TLBoDP_Device_ReleaseHardware(TLBoDP_Device* aThis);

#ifdef __cplusplus
    }
#endif

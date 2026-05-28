
// Product TLBoDP

/// \author    KMS - Martin Dubois, P. Eng.
/// \copyright Copyright &copy; 2026 KMS
/// \file      Includes/TLBoDP_Device_W.h
/// \brief     TLBoDP_Device on Windows

#pragma once

// ===== Includes ===========================================================
#include <TLBoDP_Result.h>

#ifndef __cplusplus
    #error Do not use this header file in C
#endif

struct TLBoDevice_s;

// Functions
// //////////////////////////////////////////////////////////////////////////

/// \brief Retrieve a TLBoDP_Device instance from a WDFDEVICE instance
/// \param aDevice The WDFDEVICE instance
/// \retval The TLBoDP_Device instance
///
/// To use in Windows code
extern struct TLBoDP_Device_s* TLBoDP_Device_From_WDFDEVICE(WDFDEVICE aDevice);

/// \brief Create a new device
/// \param aDeviceInit       See WDFDEVICE_INIT
/// \param aContextSize_byte The context size or 0 is the TLBoDP_Device is
///                          used as context.
/// \param aDevice           The function return the WDFDEVICE instance here
/// \retval TLBoDP_OK
///
/// To use in Windows code from the EVT_WDF_DRIVER_DEVICE_ADD entry point
///
/// KMDF is reponsible for deleting the TLBoDP_Device instance.
extern TLBoDP_Result TLBoDP_Device_New(WDFDEVICE_INIT* aDeviceInit, unsigned int aContextSize_byte, WDFDEVICE* aDevice);

// ===== Direct Windows entry points ========================================

extern EVT_WDF_DEVICE_D0_ENTRY         TLBoDP_Device_D0Entry_W;
extern EVT_WDF_DEVICE_D0_EXIT          TLBoDP_Device_D0Exit_W;
extern EVT_WDF_DEVICE_PREPARE_HARDWARE TLBoDP_Device_PrepareHardware_W;
extern EVT_WDF_DEVICE_RELEASE_HARDWARE TLBoDP_Device_ReleaseHardware_W;

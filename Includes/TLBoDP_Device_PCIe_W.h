
// Product TLBoDP

/// \author    KMS - Martin Dubois, P. Eng.
/// \copyright Copyright &copy; 2026 KMS
/// \file      Includes/TLBoDP_Device_PCIe_W.h
/// \brief     TLBoDP_Device_PCIe on Windows
///
/// To be used in Windows code

#pragma once

// ===== Includes ===========================================================
#include <TLBoDP_Result.h>

#ifndef __cplusplus
    #error Do not use this header file in C
#endif

struct TLBoDP_Device_PCIe_s;

// Functions
// //////////////////////////////////////////////////////////////////////////

/// \brief Retrieve a TLBoDP_Device_PCIe instance from a WDFDEVICE instance
/// \param aDevice The WDFDEVICE instance
/// \retval The TLBoDP_Device_PCIe instance
///
/// To use in Windows code
extern struct TLBoDP_Device_PCIe_s* TLBoDP_Device_PCIe_From_WDFDEVICE(WDFDEVICE aDevice);

/// \brief Retrieve a TLBoDP_Device_PCIe instance from a WDFINTERRUPT
///        instance
/// \param aInterrupt The WDFINTERRUPT instance
/// \retval The TLBoDP_Device_PCIe instance
///
/// To use in Windows code
extern struct TLBoDP_Device_PCIe_s* TLBoDP_Device_PCIe_From_WDFINTERRUPT(WDFINTERRUPT aInterrupt);

/// \brief Create a new device
/// \param aSize_byte  The context size or 0 is the TLBoDP_Device_PCIe is
///                    used as context.
/// \param aDeviceInit See WDFDEVICE_INIT
/// \param aDevice     The function return the WDFDEVICE instance here
/// \retval TLBoDP_OK
/// \see TLBoDP_Device_New
///
/// To use in Windows code from the EVT_WDF_DRIVER_DEVICE_ADD entry point.
///
/// This function use TLBoDP_Device_New to create a TLBoDP_Device_PCIe
/// instance and after it initialize the new instance.
///
/// If the driver uses a class derived from TLBoDP_Device_PCIe, it must use
/// the aContextSize_byte argument to indicate the size of the derived class.
///
/// KMDF is reponsible for deleting the TLBoDP_Device instance.
extern TLBoDP_Result TLBoDP_Device_PCIe_New(unsigned int aSize_byte, WDFDEVICE_INIT* aDeviceInit, WDFDEVICE* aDevice);

/// \brief Store the resources list to be used by TLBoDP_Device_PCIe_Prepare
/// \param aThis       The TLBoDP_Device instance
/// \param aRaw        See EVT_WDF_DEVICE_PREPARE_HARDWARE
/// \param aTranslated See EVT_WDF_DEVICE_PREPARE_HARDWARE
/// \see TLBoDP_Device_PCIe_PrepareHardware
///
/// To use in Windows code from the EVT_WDF_DEVICE_PREPARE_HARDWARE entry
/// point before calling TLBoDP_Device_PCIe_PrepareHardware
extern TLBoDP_Result TLBoDP_Device_PCIe_SetResourceLists(struct TLBoDP_Device_PCIe_s* aThis, WDFCMRESLIST aRaw, WDFCMRESLIST aTranslated);

// ===== Direct Windows entry points ========================================

extern EVT_WDF_DEVICE_D0_ENTRY         TLBoDP_Device_PCIe_D0Entry_W;
extern EVT_WDF_DEVICE_D0_EXIT          TLBoDP_Device_PCIe_D0Exit_W;
extern EVT_WDF_DEVICE_PREPARE_HARDWARE TLBoDP_Device_PCIe_PrepareHardware_W;
extern EVT_WDF_DEVICE_RELEASE_HARDWARE TLBoDP_Device_PCIe_ReleaseHardware_W;

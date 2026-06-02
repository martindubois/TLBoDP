
// Product TLBoDP

/// \author    KMS - Martin Dubois, P. Eng.
/// \copyright Copyright &copy; 2026 KMS
/// \file      Includes/TLBoDP_Device_PCIe_L.h
/// \brief     TLBoDP_Device_PCIe on Linux

#pragma once

// ===== Includes ===========================================================
#include <TLBoDP_Result.h>

#ifdef __cplusplus
    #error Do not use this header file in C++
#endif

struct TLBoDP_Device_PCIe_s;

// Functions
// //////////////////////////////////////////////////////////////////////////

/// \brief Retrieve the TLBoDP_Device_PCIe instance from a struct pci_dev
///        instance
/// \param aPciDev The struct pci_dev instance
/// \retval The TLBoDP_Device instance
///
/// To use in Linux C code.
extern struct TLBoDP_Device_PCIe_s* TLBoDP_Device_PCIe_From_pci_dev(struct pci_dev* aPciDev);

/// \brief Create a new TLBoDP_Device_PCIe instance
/// \param aSize_byte The context size of 0 is the context type is
///                   TLBoDP_Device
/// \param aPciDev    The struct pci_dev instance
/// \retval TLPoDP_OK
/// \see TLBoDP_Device_Delete
///      TLBoDP_Device_PrepareHardware
///      TLBoDP_Device_PCIe_SetModuleName
///
/// To use in Linux C code from the Probe entry point.
extern TLBoDP_Result TLBoDP_Device_PCIe_New(unsigned int aSize_byte, struct pci_dev* aPciDev);

/// \brief Delete a TLBoDP_Device_PCIe instance
/// \param aThis The TLBoDP_Device_PCIe instance
///
/// To use in Linux C code from the Remove entry point.
extern void TLBoDP_Device_PCIe_Delete(struct TLBoDP_Device_PCIe_s* aThis);

/// \brief Set the module name
/// \param aThis       The TLBoDP_Device_PCIe instance
/// \param aModuleName The module name
/// \see TLBoDP_PCIe_PrepareHarware
///
/// To use in Linux C code from the Probe entry point before calling
/// TLBoDP_Device_PCIe_PrepareHardware
extern void TLBoDP_Device_PCIe_SetModuleName(struct TLBoDP_Device_PCIe_s* aThis, const char* aModuleName);
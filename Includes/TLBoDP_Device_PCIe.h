
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
#define TLBoDP_Device_PCIe_MEMORY_QTY (8)

/// \brief Maximum number of interrupt for a device
#define TLBoDP_Device_PCIe_INTERRUPT_QTY (32)

#define TLBoDP_Device_PCIe_INTERRUPT_NONE   (0)
#define TLBoDP_Device_PCIe_INTERRUPT_LEGACY (1)
#define TLBoDP_Device_PCIe_INTERRUPT_MSI_X  (2)

/// \brief PCIe device base context
/// \see TLBoDP_Device_PCIe_D0Entry
///      TLBoDP_Device_PCIe_D0Exit
///      TLBoDP_Device_PCIe_ReleaseHardware
typedef struct TLBoDP_Device_PCIe_s
{
    TLBoDP_Device mBase; ///< Base class

    unsigned int mInt_Count; ///< Interrupt count
    unsigned int mInt_Type ; ///< See TLBoDP_Device_PCIe_INTERRUPT_...
    unsigned int mMem_Count; ///< Memory zone count

    TLBoDP_Mapping mMemories[TLBoDP_Device_PCIe_MEMORY_QTY]; ///< Memory zones

    #ifdef _TLBoDP_LINUX_
        int         mInterrupts[TLBoDP_Device_PCIe_INTERRUPT_QTY];
        const char* mModuleName;

        #ifdef MODULE
            struct pci_dev* mPciDev;
        #else
            void* mPciDev;
        #endif

        union
        {
            #ifdef MODULE
                struct tasklet_struct mTasklet;
            #endif

            uint8_t mReserved0[128];
        }
        mLinux;
    #endif

    #ifdef _TLBoDP_WINDOWS_
        WDFINTERRUPT mInterrupts[TLBoDP_Device_PCIe_INTERRUPT_QTY];
        WDFCMRESLIST mRaw;
        WDFCMRESLIST mTranslated;
    #endif
}
TLBoDP_Device_PCIe;

// Functions
// //////////////////////////////////////////////////////////////////////////

/// \brief Initialize an allocated TLBoDP_Device_PCIe instance
/// \param aThis The TLBoDP_Device_PCIe instance
/// \see TLBoDP_Device_PCIe_New
///
/// This function is called from TLBoDP_Device_PCIe_New and the driver code
/// should not call it directly.
extern void TLBoDP_Device_PCIe_Init(TLBoDP_Device_PCIe* aThis);

/// \brief Enter D0 state
/// \param aThis The TLBoDP_Device_PCIe instance
/// \retval TLBoDP_OK
extern TLBoDP_Result TLBoDP_Device_PCIe_D0Entry(TLBoDP_Device_PCIe* aThis);

/// \brief Leave D0 state
/// \param aThis The TLBoDP_Device_PCIe instance
extern void TLBoDP_Device_PCIe_D0Exit(TLBoDP_Device_PCIe* aThis);

/// \brief Prepare hardware resources
/// \param aThis The TLBoDP_Device_PCIe instance
/// \retval TLBoDP_OK
/// \retval TLBoDP_ERROR_LINUX_PCI
extern TLBoDP_Result TLBoDP_Device_PCIe_PrepareHardware(TLBoDP_Device_PCIe* aThis);

/// \brief Release hardware resources
/// \param aThis The TLBoDP_Device_PCIe instance
extern void TLBoDP_Device_PCIe_ReleaseHardware(TLBoDP_Device_PCIe* aThis);

extern void TLBoDP_Device_PCIe_Interrupt_0(TLBoDP_Device_PCIe* aThis, uint64_t aOSDep);
extern void TLBoDP_Device_PCIe_Interrupt_1(TLBoDP_Device_PCIe* aThis, uint64_t aOSDep);

#ifdef __cplusplus
    }
#endif

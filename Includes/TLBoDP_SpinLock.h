
// Product TLBoDP

/// \author    KMS - Martin Dubois, P. Eng.
/// \copyright Copyright &copy; 2026 KMS
/// \file      Includes/TLBoDP_SpinLock.h
/// \brief     TLBoDP_SpinLock

#pragma once

#ifdef __cplusplus
    extern "C" {
#endif

struct TLBoDP_Device_s;

// Data types
// //////////////////////////////////////////////////////////////////////////

/// \brief A spinlock
/// \see TLBoDP_SpinLock_Init
///      TLBoDP_SpinLock_Lock
///      TLBoDP_SpinLock_Unlock
typedef struct TLBoDP_SpinLock_s
{
    #ifdef _TLBoDP_LINUX_
        union
        {
            #ifdef MODULE
                spinlock_t mSpinLock;
            #endif

            uint8_t mReserved0[128];
        }
        mLinux;
    #endif

    #ifdef _TLBoDP_WINDOWS_

        WDFSPINLOCK mSpinLock;

    #endif

}
TLBoDP_SpinLock;

// Functions
// //////////////////////////////////////////////////////////////////////////

/// \brief Initialize a spin lock
/// \param aThis   The TLBoDP_SpinLock instance to initialize
/// \param aDevice The TLBoDP_Device instance
/// \see TLBoDP_SpinLock_Lock
extern void TLBoDP_SpinLock_Init(TLBoDP_SpinLock* aThis, struct TLBoDP_Device_s* aDevice);

/// \brief Lock a spin lock
/// \param aThis The TLBoDP_SpinLock instance to lock
/// \note Do not call from an interrupt handler
/// \see TLBoDP_SpinLock_Init
///      TLBoDP_SpinLock_Unlock
/// \note Does not call from a interrupt handler
extern void TLBoDP_SpinLock_Lock(TLBoDP_SpinLock* aThis);

/// \brief Unlock a spin lock
/// \param aThis The TLBoDP_SpinLock instance to unlock
/// \see TLBoDP_SpinLock_Lock
/// \note Does not call from a interrupt handler
extern void TLBoDP_SpinLock_Unlock(TLBoDP_SpinLock* aThis);

#ifdef __cplusplus
    }
#endif

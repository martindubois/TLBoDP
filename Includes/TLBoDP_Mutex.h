
// Product TLBoDP

/// \author    KMS - Martin Dubois, P. Eng.
/// \copyright Copyright &copy; 2026 KMS
/// \file      Includes/TLBoDP_Mutex.h
/// \brief     TLBoDP_File

#pragma once

#ifdef __cplusplus
    extern "C" {
#endif

// Data types
// //////////////////////////////////////////////////////////////////////////

/// \brief Mutex
typedef struct TLBoDP_Mutex_s
{

    #ifdef _TLBoDP_LINUX_
        union
        {
            #ifdef MODULE
                struct mutex mMutex;
            #endif

            uint8_t mReserved0[128];
        }
        mLinux;
    #endif

    #ifdef _TLBoDP_WINDOWS_
        WDFWAITLOCK mWaitLock;
    #endif

}
TLBoDP_Mutex;

// Functions
// //////////////////////////////////////////////////////////////////////////

/// \brief Initialize a TLBoDP_Mutex instance
/// \param aThis   The TLBoDP_Mutex instance
/// \param aDevice The TLBoDP_Device instance the mutex is associated with
extern void TLBoDP_Mutex_Init(TLBoDP_Mutex* aThis, struct TLBoDP_Device_s* aDevice);

/// \brief Acquire the mutex
/// \param aThis The TLBoDP_Mutex instance
extern void TLBoDP_Mutex_Lock(TLBoDP_Mutex* aThis);

/// \brief Release the mutex
/// \param aThis The TLBoDP_Mutex instance
extern void TLBoDP_Mutex_Unlock(TLBoDP_Mutex* aThis);

#ifdef __cplusplus
    }
#endif


// Product TLBoDP

/// \author    KMS - Martin Dubois, P. Eng.
/// \copyright Copyright &copy; 2026 KMS
/// \file      Includes/TLBoDP_Callback.h
/// \brief     TLBoDP_Callback and TLBoDP_Callback_List

#pragma once

// ===== Includes ===========================================================
#include <TLBoDP_Result.h>
#include <TLBoDP_SpinLock.h>
#include <TLBoDP_StdTypes.h>

#ifdef __cplusplus
    extern "C" {
#endif

// Data types
// //////////////////////////////////////////////////////////////////////////

/// \brief Type of de callback function
/// \param aSender  The instance calling the callback
/// \param aType    The type (bitfield with a single bit set)
/// \param aContext The context passed to the callback
/// \retval TLBoDP_OK
/// \retval TLBoDP_OK_STOP    Do not continue to walk the callback list
/// \retval TLBoDP_ERROR_...  Report en error and stop walk the list
typedef TLBoDP_Result (*TLBoDP_Callback_Function)(void* aSender, uint32_t aType, void* aContext);

/// \brief Information about a callback
/// \see TLBoDP_Callback_Init
///      TLBoDP_Callback_Call
///      TLBoDP_Callback_IsRegisterd
///      TLBoDP_Callbacl_List
///      TLBoDP_Callback_Register
///      TLBoDP_Callback_Unregister
///
/// This class can be used alone when a single callback is needed. In this
/// case the class is not thread safe and the code using it is responsible
/// for protectection agains race condition.
///
/// This class is also used as item into the TLBoDP_Callback_List class.
typedef struct TLBoDP_Callback_s
{
    void                   * mContext;
    TLBoDP_Callback_Function mFunction;
    void                   * mSender;
    uint32_t                 mTypes;
}
TLBoDP_Callback;

#define TLBoDP_CALLBACK_LIST_DEPTH (128)

/// \brief Callback list
/// \see TLBoDP_Callback_List_Init
///      TLBoDP_Callback_List_Call
///      TLBoDP_Callback_List_Call_FromISR
///      TLBoDP_Callback_List_Register
///      TLBoDP_Callback_List_Unregister
///
/// This class is thread safe when all instruction are respected.
///
/// Each TLBoDP_Device instance contains a TLBoDP_Callback_List instance.
/// Often, no other instance are needed.
typedef struct TLBoDP_Callback_List_s
{
    // ===== Zone 0 =========================================================
    TLBoDP_SpinLock mZone0;

    TLBoDP_Callback mCallbacks[TLBoDP_CALLBACK_LIST_DEPTH];

    unsigned int mActualDepth;
}
TLBoDP_Callback_List;

// Functions
// //////////////////////////////////////////////////////////////////////////

/// \brief Initialize a TLBoDP_Callback instance
/// \param aThis The TLBoDP_Callback instance
extern void TLBoDP_Callback_Init(TLBoDP_Callback* aThis);

/// \brief Call the callback
/// \param aThis The TLBoDP_Callback instance
/// \param aType The callback type
/// \retval TLBoDP_OK
/// \retval TLBoDP_OK_NOT_REGISTERED  The instance is not valid of does not
///                                   accept this type of callback.
/// \retval TLBoDP_OK_STOP            Do not continue to walk the list
/// \retval TLBoDP_ERROR_...          The callback reported an error.
extern TLBoDP_Result TLBoDP_Callback_Call(TLBoDP_Callback* aThis, uint32_t aType);

/// \brief Is the callback registered?
/// \param aThis The TLBoDP_Callback instance
/// \retval false The instance is not registered
/// \retval true  The instance is registered
extern bool TLBoDP_Callback_IsRegisterd(TLBoDP_Callback* aThis);

/// \brief Register a callback
/// \param aThis     The TLBoDP_Callback instance
/// \param aSender   The instance sending the callback
/// \param aTypes    The type of the callback (bitfield)
/// \param aFunction The callback function
/// \param aContext  The context to pass to the callback function
/// \retval TLBoDP_OK
/// \retval TLBoDP_ERROR_INVALID_FUNCTION
/// \retval TLBoDP_ERROR_INVALID_TYPES
/// \retval TLBoDP_ERROR_NOT_AVAILABLE
/// \see TLBoDP_Callback_Unregister
extern TLBoDP_Result TLBoDP_Callback_Register(TLBoDP_Callback* aThis, void* aSender, uint32_t aTypes, TLBoDP_Callback_Function aFunction, void* aContext);

/// \brief Register a callback
/// \param aThis The TLBoDP_Callback instance
/// \retval TLBoDP_OK
/// \retval TLBoDP_ERROR_NOT_REGISTERED
/// \see TLBoDP_Callback_Register
extern TLBoDP_Result TLBoDP_Callback_Unregister(TLBoDP_Callback* aThis);

/// \brief Initialize a TLBoDP_Callback_List instance
/// \param aThis   The TLBoDP_Callback_List instance
/// \param aDevice The TLBoDP_Device instance the list is associated with
/// \see TLBoDP_Callback_List_Uninit
extern void TLBoDP_Callback_List_Init(TLBoDP_Callback_List* aThis, struct TLBoDP_Device_s* aDevice);

/// \brief Uninitialize a TLBoDP_Callback_List instance
/// \param aThis   The TLBoDP_Callback_List instance
/// \see TLBoDP_Callback_List_Init
extern void TLBoDP_Callback_List_Uninit(TLBoDP_Callback_List* aThis);

/// \brief Call callbacks
/// \param aThis   The TLBoDP_Callback_List instance
/// \param aSender The instance sending the callback
/// \param aType   The type of callback (bitfield with only on bit set)
/// \retval TLBoDP_OK
/// \retval TLBoDP_OK_NOT_REGISTERED
/// \note Do not call from an interrupt handler
extern TLBoDP_Result TLBoDP_Callback_List_Call(TLBoDP_Callback_List* aThis, void* aSender, uint32_t aType);

/// \brief Call callbacks
/// \param aThis   The TLBoDP_Callback_List instance
/// \param aSender The instance sending the callback
/// \param aType   The type of callback
/// \retval TLBoDP_OK
/// \retval TLBoDP_OK_NOT_REGISTERED
/// \retval TLBoDP_OK_STOP
/// \retval TLBoDP_ERROR_...
/// \see TLBoDP_Callback_List_Call
/// \note Only use from an interrupt handler
extern TLBoDP_Result TLBoDP_Callback_List_Call_FromISR(TLBoDP_Callback_List* aThis, void* aSender, uint32_t aType);

/// \brief Register a callback
/// \param aThis     The TLBoDP_Callback_List instance
/// \param aSender   The instance sending the callback
/// \param aTypes    The callback types (bitfield)
/// \param aFunction The callback function
/// \param aContext  The context to pass to the function
/// \retval TLBoDP_OK
/// \retval TLBoDP_ERROR_NO_AVAILABLE
/// \see TLBoDP_Callback_List_Unregister
/// \note Do not call from an interrupt handler
/// \note If the callback can be called from an ISR, the interrupt must be
///       disabled when this function is called.
extern TLBoDP_Result TLBoDP_Callback_List_Register(TLBoDP_Callback_List* aThis, void* aSender, uint32_t aTypes, TLBoDP_Callback_Function aFunction, void* aContext);

/// \brief Unregister a callback
/// \param aThis     The TLBoDP_Callback_List instance
/// \param aSender   The instance sending the callback
/// \param aTypes    The callback types (bitfield)
/// \param aFunction The callback function
/// \param aContext  The context to pass to the function
/// \retval TLBoDP_OK
/// \retval TLBoDP_ERROR_NOT_REGISTERED
/// \note Do not call from an interrupt handler
/// \note If the callback can be called from an ISR, the interrupt must be
///       disabled when this function is called.
extern TLBoDP_Result TLBoDP_Callback_List_Unregister(TLBoDP_Callback_List* aThis, void* aSender, uint32_t aTypes, TLBoDP_Callback_Function aFunction, void* aContext);

#ifdef __cplusplus
    }
#endif

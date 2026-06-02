
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      PCIe/Device.cpp

#include "Component.h"

// ===== Local ==============================================================
#include "Device.h"

// Functions
// //////////////////////////////////////////////////////////////////////////

TLBoDP_Result Device_D0Entry(TLBoDP_Device_PCIe* aThis)
{
    // INSTRUCTION  Here, a real driver completes the device power up. It
    //              also reconfigure what need to be reconfigured after a
    //              sleep or hybernation.

    return TLBoDP_Device_PCIe_D0Entry(aThis);
}

void Device_D0Exit(TLBoDP_Device_PCIe* aThis)
{
    // INSTRUCTION  Here, a real driver turn off the device. If needed, it
    //              also save information to be retored after a sleep or
    //              hybernation.

    return TLBoDP_Device_PCIe_D0Exit(aThis);
}

TLBoDP_Result Device_PrepareHardware(TLBoDP_Device_PCIe* aThis)
{
    auto lResult = TLBoDP_Device_PCIe_PrepareHardware(aThis);
    if (TLBoDP_OK == lResult)
    {
        // INSTRUCTION  Here, a real driver, retrieve memory address of
        //              registers and validate the device is well of the
        //              expected type.
    }

    return lResult;
}

void Device_ReleaseHardware(TLBoDP_Device_PCIe* aThis)
{
    // INSTRUCTION  Here, a real driver prepare the device for the computer
    //              shutdown, the device removal or the driver unloading.

    TLBoDP_Device_PCIe_ReleaseHardware(aThis);
}

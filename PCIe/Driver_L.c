
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      PCIe/Driver_L.c

#include "Component.h"

// ===== Linux kernel =======================================================
#include <linux/module.h>
#include <linux/pci.h>

// ===== Local ==============================================================
#include "Device_L.h"

// Constants
// //////////////////////////////////////////////////////////////////////////

static struct pci_device_id ID_TABLE[] =
{
    { PCI_DEVICE(0x8086, 0x15a1), },

    { 0, }
};

// Static function declarations
// //////////////////////////////////////////////////////////////////////////

// ===== Entry points =======================================================

static void __exit Exit(void);
static int  __init Init(void);

// Static variables
// //////////////////////////////////////////////////////////////////////////

static struct pci_driver sPciDriver =
{
    .name     = MODULE_NAME,
    .id_table = ID_TABLE,
    .probe    = Device_Probe,
    .remove   = Device_Remove,
    .resume   = Device_Resume,
    .suspend  = Device_Suspend,
};

// Static functions
// //////////////////////////////////////////////////////////////////////////

// ===== Entry points =======================================================

void Exit()
{
    printk(KERN_DEBUG PREFIX "%s()\n", __FUNCTION__);

    pci_unregister_driver(&sPciDriver);
}

module_exit(Exit);

int Init()
{
    printk(KERN_DEBUG PREFIX "%s()\n", __FUNCTION__);

    int lResult = pci_register_driver(&sPciDriver);
    if (0 != lResult)
    {
        printk(KERN_ERR PREFIX "%s - pci_register_driver(  ) failed - %d\n", __FUNCTION__, lResult);
    }

    return lResult;
}

module_init(Init);

// License
/////////////////////////////////////////////////////////////////////////////

MODULE_LICENSE("GPL");

MODULE_AUTHOR("KMS - Martin Dubois, P. Eng. <mdubois@kms-quebec.com>");
MODULE_DESCRIPTION("PCIe");

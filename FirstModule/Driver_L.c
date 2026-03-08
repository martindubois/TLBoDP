
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      FirstModule/Driver_L.c

#include "Component.h"

// ===== Linux kernel =======================================================
#include <linux/module.h>

// ===== Local ==============================================================
#include "Driver.h"

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

// ===== Entry points =======================================================

static void __exit Exit(void);
static int  __init Init(void);

// Static functions
/////////////////////////////////////////////////////////////////////////////

// ===== Entry points =======================================================

void Exit()
{
    printk(KERN_DEBUG "FirstModule: %s()\n", __FUNCTION__);

    Driver_Unload();
}

module_exit(Exit);

int Init()
{
    printk(KERN_DEBUG "FirstModule: %s()\n", __FUNCTION__);

    return Driver_Load();
}

module_init(Init);

// License
/////////////////////////////////////////////////////////////////////////////

MODULE_LICENSE("GPL");

MODULE_AUTHOR("KMS - Martin Dubois, P. Eng. <mdubois@kms-quebec.com>");
MODULE_DESCRIPTION("FirstModule");

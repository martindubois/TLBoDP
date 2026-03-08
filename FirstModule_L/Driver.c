
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2026 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TLBoDP
// File      FirstModule_L/Driver.c

// ===== Linux kernel =======================================================
#include <linux/module.h>

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
    printk(KERN_DEBUG "FirstModule_L: %s()\n", __FUNCTION__);

    // Some unitialization code
}

module_exit(Exit);

int Init()
{
    printk(KERN_DEBUG "FirstModule_L: %s()\n", __FUNCTION__);

    // Some initialization code

    return 0;
}

module_init(Init);

// License
/////////////////////////////////////////////////////////////////////////////

MODULE_LICENSE("GPL");

MODULE_AUTHOR("KMS - Martin Dubois, P. Eng. <mdubois@kms-quebec.com>");
MODULE_DESCRIPTION("FirstModule_L");

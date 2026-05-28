
# Author    KMS - Martin Dubois, P. Eng.
# Copyright (C) 2026 KMS
# License   http://www.apache.org/licenses/LICENSE-2.0
# Product   TLBoDP
# File      PCIe/Makefile

obj-m += PCIe.o

FirstModule-objs := Device_L.o Driver_L.o

ccflags-y := -D_TLBoDP_LINUX_

ldflags-y := --whole-archive PCIe_K.a

# ===== Target ==============================================================

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

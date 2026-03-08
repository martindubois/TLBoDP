
# Author    KMS - Martin Dubois, P. Eng.
# Copyright (C) 2026 KMS
# License   http://www.apache.org/licenses/LICENSE-2.0
# Product   TLBoDP
# File      FirstModule/Makefile

obj-m += FirstModule.o

FirstModule-objs := Driver_L.o

ldflags-y := --whole-archive FirstModule_K.a

# ===== Target ==============================================================

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

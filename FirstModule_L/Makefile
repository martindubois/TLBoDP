
# Author    KMS - Martin Dubois, P. Eng.
# Copyright (C) 2026 KMS
# License   http://www.apache.org/licenses/LICENSE-2.0
# Product   TLBoDP
# File      FirstModule_L/Makefile

obj-m += FirstModule_L.o

FirstModule_L-objs := Driver.o

# ===== Target ==============================================================

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

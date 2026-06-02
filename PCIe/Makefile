
# Author    KMS - Martin Dubois, P. Eng.
# Copyright (C) 2026 KMS
# License   http://www.apache.org/licenses/LICENSE-2.0
# Product   TLBoDP
# File      PCIe/Makefile

obj-m += PCIe.o

PCIe-objs := Device_L.o Driver_L.o TLBoDP_Device_L.o TLBoDP_Device_PCIe_L.o TLBoDP_Result_L.o TLBoDP_SpinLock_L.o TLBoDP_Trace_L.o

ccflags-y := -D_TLBoDP_LINUX_ -I../Includes

ldflags-y := --whole-archive PCIe_K.a --whole-archive ../Libraries/TLBoDP_K.a

# ===== Target ==============================================================

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

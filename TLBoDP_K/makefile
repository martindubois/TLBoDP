
# Author    KMS - Martin Dubois, P. Eng.
# Copyright (C) 2026 KMS
# License   http://www.apache.org/licenses/LICENSE-2.0
# Product   TLBoDP
# File      TLBoDP_K/makefile

CFLAGS = @../Args/Kernel.args -D_TLBoDP_LINUX_

INCLUDES = -I../Includes

OUTPUT = ../Libraries/TLBoDP_K.a

SOURCES = Callback.cpp    \
		  Device_PCIe.cpp \
		  Device.cpp      \
		  Mapping.cpp

# ===== Rules ===============================================================

.cpp.o:
	g++ -c $(CFLAGS) -fno-rtti -o $@ $(INCLUDES) $<

# ===== Macros ==============================================================

OBJECTS = $(SOURCES:.cpp=.o)

# ===== Targets =============================================================

$(OUTPUT) : $(OBJECTS)
	ar r $@ $^
	ranlib $@

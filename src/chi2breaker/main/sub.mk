# chi2breaker sub makefile

SUB_INCLUDES := -I $(COMMON_SOURCES_DIR)
SUB_INCLUDES += -I $(SUB_SOURCES_DIR)

SUB_SOURCES := main.c
SUB_SOURCES += Chi2Breaker.c
SUB_SOURCES += Chi2BreakerCLAP.c

SUB_EXECUTABLE := vi_chi2breaker
ifeq ($(OS), Windows_NT)
	SUB_EXECUTABLE := vi_chi2breaker.exe
endif
SUB_EXECUTABLE_DIR := build/bin/
SUB_EXECUTABLE_FP := $(addprefix $(SUB_EXECUTABLE_DIR),$(SUB_EXECUTABLE))

SUB_DEPS := $(COMMON_TARGET_NAME)

# encoder test sub makefile

SUB_INCLUDES := -I $(COMMON_SOURCES_DIR)
SUB_INCLUDES += -I $(ENCODER_SOURCES_DIR)
SUB_INCLUDES += -I $(ENCODER_TEST_SOURCES_DIR)

SUB_SOURCES :=

SUB_SOURCES := main.c
SUB_SOURCES += TestEncoder.c

SUB_EXECUTABLE := test_encoder
ifeq ($(OS), Windows_NT)
	SUB_EXECUTABLE := test_encoder.exe
endif
SUB_EXECUTABLE_DIR := build/testbin/
SUB_EXECUTABLE_FP := $(addprefix $(SUB_EXECUTABLE_DIR),$(SUB_EXECUTABLE))

SUB_DEPS := $(COMMON_TARGET_NAME)


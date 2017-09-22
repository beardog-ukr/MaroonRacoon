# decoder sub makefile

SUB_INCLUDES := -I $(COMMON_SOURCES_DIR)
SUB_INCLUDES += -I $(DECODER_SOURCES_DIR)

SUB_SOURCES := main.c
SUB_SOURCES += DecoderCLAP.c

SUB_EXECUTABLE := vi_decoder
ifeq ($(OS), Windows_NT)
	SUB_EXECUTABLE := vi_decoder.exe
endif
SUB_EXECUTABLE_DIR := build/bin/
SUB_EXECUTABLE_FP := $(addprefix $(SUB_EXECUTABLE_DIR),$(SUB_EXECUTABLE))

SUB_DEPS := $(COMMON_TARGET_NAME)

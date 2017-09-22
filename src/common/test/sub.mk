# common lib test sub makefile

SUB_INCLUDES := -I $(COMMON_SOURCES_DIR)

SUB_SOURCES =

SUB_SOURCES := main.c
SUB_SOURCES += TestAlphabetTransform.c
SUB_SOURCES += TestBasicDecode.c
SUB_SOURCES += TestChi2Decode.c
SUB_SOURCES += TestCommonCLAP.c
SUB_SOURCES += TestCosetFunctions.c
SUB_SOURCES += TestFileUtils.c
SUB_SOURCES += TestFrequencyInfo.c
SUB_SOURCES += TestIndexOfCoincidence.c

SUB_DEPS := 

SUB_EXECUTABLE := test_common
ifeq ($(OS), Windows_NT)
	SUB_EXECUTABLE := test_common.exe
endif
SUB_EXECUTABLE_DIR := build/testbin/
SUB_EXECUTABLE_FP := $(addprefix $(SUB_EXECUTABLE_DIR),$(SUB_EXECUTABLE))

#include $(MK_DIR)/folders.mk

include $(MK_DIR)/config.mk

COMMON_TARGET_NAME := common
COMMON_OBJ_FILES :=

ALL_TARGETS :=
ALL_CLEAN_TARGETS :=

###########################################################

include $(MK_DIR)/cleanOne.mk

SUB_NAME = Common
SUB_SOURCES_DIR = $(COMMON_SOURCES_DIR)
SUB_TARGET := $(COMMON_TARGET_NAME)
SUB_TARGET_CLEAN := clean_common

include $(MK_DIR)/makeOne.mk
COMMON_OBJ_FILES += $(SUB_OBJ_FP)

###########################################################
include $(MK_DIR)/cleanOne.mk
#SUB_OTHER_OBJ_FP = $(SUB_OBJ_FP)

SUB_NAME = CommonTest
SUB_SOURCES_DIR = $(COMMON_TEST_SOURCES_DIR)
SUB_TARGET := common_test
SUB_TARGET_CLEAN := clean_common_test
include $(MK_DIR)/makeOne.mk

###########################################################

include $(MK_DIR)/cleanOne.mk

SUB_NAME = Preprocessor
SUB_SOURCES_DIR = $(PREPROCESSOR_SOURCES_DIR)
SUB_TARGET := preprocessor
SUB_TARGET_CLEAN := clean_preprocessor

include $(MK_DIR)/makeOne.mk

###########################################################

include $(MK_DIR)/cleanOne.mk

SUB_NAME = Encoder
SUB_SOURCES_DIR = $(ENCODER_SOURCES_DIR)
SUB_TARGET := encoder
SUB_TARGET_CLEAN := clean_encoder

include $(MK_DIR)/makeOne.mk

SUB_OTHER_OBJ_FP = $(filter-out $(BUILD_DIR)/encoder_obj/main.o, $(SUB_OBJ_FP))

SUB_NAME = EncoderTest
SUB_SOURCES_DIR = $(ENCODER_TEST_SOURCES_DIR)
SUB_TARGET := encoder_test
SUB_TARGET_CLEAN := clean_encoder_test
include $(MK_DIR)/makeOne.mk

###########################################################

include $(MK_DIR)/cleanOne.mk

SUB_NAME = Decoder
SUB_SOURCES_DIR = $(DECODER_SOURCES_DIR)
SUB_TARGET := decoder
SUB_TARGET_CLEAN := clean_decoder

include $(MK_DIR)/makeOne.mk

###########################################################

include $(MK_DIR)/cleanOne.mk

SUB_NAME = Chi2breaker
SUB_SOURCES_DIR = $(CHI2BREAKER_SOURCES_DIR)
SUB_TARGET := chi2breaker
SUB_TARGET_CLEAN := clean_chi2breaker

include $(MK_DIR)/makeOne.mk

###########################################################

include $(MK_DIR)/cleanOne.mk

SUB_NAME = Breaker
SUB_SOURCES_DIR = $(BREAKER_SOURCES_DIR)
SUB_TARGET := breaker
SUB_TARGET_CLEAN := clean_breaker

include $(MK_DIR)/makeOne.mk

###########################################################

include $(MK_DIR)/cleanOne.mk



$(info all targets are $(ALL_TARGETS) )



# comes from includer file:
# SUB_NAME 
# SUB_SOURCES_DIR
# SUB_MAKEFILE
# GLOBAL_CFLAGS
# 

include $(SUB_SOURCES_DIR)/sub.mk

$(SUB_EXECUTABLE_FP): SUB_OTHER_OBJ_FP := $(SUB_OTHER_OBJ_FP)

SUB_SOURCES_FP := $(addprefix $(SUB_SOURCES_DIR),$(SUB_SOURCES))

SUB_OBJ_DIR := $(BUILD_DIR)/$(SUB_TARGET)_obj/
SUB_OBJ := $(addprefix $(SUB_OBJ_DIR),$(SUB_SOURCES))
SUB_OBJ_FP := $(SUB_OBJ:.c=.o)

#$(info "building " $(SUB_NAME) " sub" )
#$(info "will create: " $(SUB_OBJ_FP) " files in " $(SUB_OBJ_DIR) )

$(SUB_OBJ_DIR)%.o: $(SUB_SOURCES_DIR)%.c
	$(CC) -c $< $(CFLAGS) $(SUB_INCLUDES) -o $@ 

$(SUB_TARGET): SUB_DEPS := $(SUB_DEPS)
$(SUB_TARGET): SUB_OBJ_FP := $(SUB_OBJ_FP) 
$(SUB_TARGET): SUB_INCLUDES := $(SUB_INCLUDES) 

ifeq ($(SUB_EXECUTABLE_FP),)
$(SUB_TARGET): $(SUB_DEPS) $(SUB_OBJ_FP) 
else
$(SUB_TARGET): SUB_EXECUTABLE_FP := $(SUB_EXECUTABLE_FP) 
$(SUB_TARGET): $(SUB_DEPS) $(SUB_OBJ_FP) $(SUB_EXECUTABLE_FP)
$(SUB_EXECUTABLE_FP): SUB_INCLUDES := $(SUB_INCLUDES) 
$(SUB_EXECUTABLE_FP): SUB_OBJ_FP := $(SUB_OBJ_FP) 

$(SUB_EXECUTABLE_FP): $(SUB_OBJ_FP)
	$(CC) $(COMMON_OBJ_FILES) $(SUB_OBJ_FP) $(SUB_OTHER_OBJ_FP) -o $(SUB_EXECUTABLE_FP)
endif

$(SUB_TARGET_CLEAN): SUB_OBJ_FP := $(SUB_OBJ_FP)
$(SUB_TARGET_CLEAN):
	-$(RM) $(SUB_OBJ_FP)

ALL_TARGETS += $(SUB_TARGET)
ALL_CLEAN_TARGETS += $(SUB_TARGET_CLEAN)

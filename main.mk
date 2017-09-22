
#MAIN_DIR := $(dir $(mkfile_path))
MAIN_DIR := $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
include folders.mk

$(info "main folder is " $(MAIN_DIR) )

include mk/targets.init.mk

all: $(ALL_TARGETS)

clean: $(ALL_CLEAN_TARGETS)





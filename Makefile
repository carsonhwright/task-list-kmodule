# # tool macros
# CC = x86_64-linux-gnu-gcc-13# FILL: the compiler
# # CXX ?= # FILL: the compiler
# INCLUDES = -I include -pthread
# # LINKS = /usr/src/linux-headers-6.17.0-19-generic/include
# MODULES = /lib/modules/6.17.0-19-generic/build
# CFLAGS =-Wall -Wextra -g $(INCLUDES) -C ${MODULES} #-C ${LINKS}# FILL: compile flags
# #CFLAGS =-Wall -Wextra -g -pthread -L /usr/local/lib/libz $(INCLUDES)# FILL: compile flags
# # CXXFLAGS := # FILL: compile flags
# DBGFLAGS = -g
# COBJFLAGS = $(CFLAGS) -c
# # path macros
# BIN_PATH := bin
# OBJ_PATH := obj
# SRC_PATH := src
# DBG_PATH := debug

# # compile macros
# TARGET_NAME := simple_module # FILL: target name

# TARGET := $(BIN_PATH)/$(TARGET_NAME)
# TARGET_DEBUG := $(DBG_PATH)/$(TARGET_NAME)

# # src files & obj files
# SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
# OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
# OBJ_DEBUG := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# # clean files list
# DISTCLEAN_LIST := $(OBJ) \
#                   $(OBJ_DEBUG)
# CLEAN_LIST := $(TARGET) \
# 			  $(TARGET_DEBUG) \
# 			  $(DISTCLEAN_LIST)

# # default rule
# default: makedir all

# # non-phony targets
# $(TARGET): $(OBJ)
# 	$(CC) -o $@ $(OBJ) $(CFLAGS)

# $(OBJ_PATH)/%.o: $(SRC_PATH)/%.c*
# 	$(CC) $(COBJFLAGS) -o $@ $<

# $(DBG_PATH)/%.o: $(SRC_PATH)/%.c*
# 	$(CC) $(COBJFLAGS) $(DBGFLAGS) -o $@ $<

# $(TARGET_DEBUG): $(OBJ_DEBUG)
# 	$(CC) $(CFLAGS) $(DBGFLAGS) $(OBJ_DEBUG) -o $@

# # phony rules
# .PHONY: makedir
# makedir:
# 	@mkdir -p $(BIN_PATH) $(OBJ_PATH) $(DBG_PATH)

# .PHONY: all
# all: $(TARGET)

# .PHONY: debug
# debug: $(TARGET_DEBUG)

# .PHONY: clean
# clean:
# 	@echo CLEAN $(CLEAN_LIST)
# 	@rm -f $(CLEAN_LIST)

# .PHONY: distclean
# distclean:
# 	@echo CLEAN $(DISTCLEAN_LIST)
# 	@rm -f $(DISTCLEAN_LIST)


# FUCK THIS IF IT WORKS

# ifneq ($(KERNELRELEASE),)
#     # call from kernel build system
#     obj-m := simple.o
# else
#     # call from the command line
#     KERNELDIR ?= /lib/modules/$(uname -r)/build
#     PWD := $(pwd)
#     default:
# 		x86_64-linux-gnu-gcc-13 -C $(KERNELDIR) M=$(PWD) modules
# clean:
# 	rm -rf *.o *~ core .depend *.mod.o .*.cmd *.ko *.mod.c .tmp_versions *.markers modules.order
# endif
ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m := task-list.o
task-list-objs := src/main.o src/utils.o
# ccflags-y += -g
# CC := x86_64-linux-gnu-gcc-13
else
KDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)
BUILD_DIR := $(PWD)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD) MO=$(BUILD_DIR) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) MO=$(BUILD_DIR) clean
	rm -rf build

endif

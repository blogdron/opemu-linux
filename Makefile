# --force-vermagic
###################################################
MODULE_NAME := op_emu
###################################################
$(MODULE_NAME)-objs := opemu/sse3.o           \
                       opemu/ssse3.o          \
                       opemu/sse41.o          \
                       opemu/sse42.o          \
                       opemu/opemu.o          \
                       opemu/fpins.o          \
                       opemu/trap_hook.o      \
                       opemu/opemu_math.o     \
                       libudis86/syn.o        \
                       libudis86/itab.o       \
                       libudis86/decode.o     \
                       libudis86/udis86.o     \
                       libudis86/syn-att.o    \
                       libudis86/syn-intel.o  \
###################################################
obj-m += $(MODULE_NAME).o
###################################################
KBUILD_CFLAGS += -DDEBUG -g -O2 -march=native  \
                                -mtune=native  \
                                -mmmx          \
                                -msse          \
                                -msse2         \
###################################################
KERNEL_PATH ?= /lib/modules/$(shell uname -r)/build
###################################################
export KBUILD_CFLAGS
###################################################
all:
	make -C $(KERNEL_PATH) M=$(PWD)  modules
#	-rm ./*.order
#	-rm ./*.symvers
#	-rm ./*.mod
#	-rm ./*.o
#	-rm ./*.c
###################################################
clean:
	make -C $(KERNEL_PATH) M=$(PWD) clean
###################################################
load:
	sudo insmod ./op_emu.ko

unload:
	sudo rmmod ./op_emu.ko

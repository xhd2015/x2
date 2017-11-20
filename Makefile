
DEBUG := false
#Debug 用于决定gcc,g++编译器生成的二进制程序是否带有源代码的信息
#g++的选项:
# -g --gen-debug          generate debugging information

HOST := windows
#may be windows,linux

#if HOST=windows, then cygwin is assumed as the toolchain
#if HOST=linux, then linux itself is assumed as the toolchain

#注意，dir中不能含有空格
HOSTROOTDIR := C:\Users\13774\Desktop\old_desktop\bochs\devel\x2-system
TOOLSDIR := tools/bochs-run

#GEN contains 16,32 and 64(can be used in hosted environment )
GEN := gen
GEN16 := gen/16
GEN32 := gen/32
GEN32USER := gen/32user
GEN64 := gen/64
SRC := src
KERNEL_SRC := $(SRC)/kernel
EXPORTS := exports
BACKUP := backups
INCLUDE := include
STDC := stdc
STDCPP := stdc++



#deciding which files are compiled.
f16 := main libx2 PMLoader Descriptor IOProgramer
f32 := protected_main libx2  VirtualMemory PMLoader Descriptor TSS interrupts IOProgramer MemoryManager test List	AssociatedMemoryManager Process Kernel idleProcess Cache
f32user := UserProcess libx2
f64 := libx2 PMLoader Descriptor TSS MemoryManager List Locator AssociatedMemoryManager
#需要用到PMLoader中的一些常量

ld16 := image_16.ld
ld32 := image_32.ld

fbackup := $(INCLUDE) $(SRC) $(ld16) $(ld32) Makefile TODO README  $(STDC) $(STDCPP) test tools filesystem deprecated from-gcc

# CCFLAGS is for all, CCFLAGSXX for CODEXX
CCFLAGS :=  -fno-exceptions  -nostdinc -nostdinc++ -nostdlib -Winline --no-warnings -I ./include -std=c++11
CCFLAGS32 := -m32
CCFLAGS16 := -m32
DEPRECATED_CCFLAGS = -fpack-struct=1

# config sec numbers here
CONFIG_REAL_SECNUMS := 25
CONFIG_PROTECTED_SECNUMS := 400 #应当比2048小，因为CODE_LIMIT=0xfffff，恰好是2048个扇区
CONFIG_USER_PROCESS_SECNUMS := 35

#toolchains
CXX = g++
AS = as
ifeq ($(DEBUG),true)
	CXX += -g
	AS += -g
endif

DDFLAGS := conv=notrunc bs=1c

CCMACROS := -D CONFIG_PROTECTED_SECNUMS=$(CONFIG_PROTECTED_SECNUMS) -D CONFIG_REAL_SECNUMS=$(CONFIG_REAL_SECNUMS)
CCMACROS16 := -D CODE16
CCMACROS32 := -D CODE32
#CCMACROS32USER := -D CODE32USER

CCFLAGS64 := -m64 -I. -I./include -std=c++11
CCMACROS64 := -D CODE64

LDFLAGS :=    --print-gc-sections --no-gc-sections
UNUSED_CCFLAGS := -fkeep-inline-functions -fpermissive
#===Deprecated=====
#	CCMACROS16 != a=($(imageMacros));b=($(wordlist 1,$(argsLenMiddle1),$(imageValues)));for i in $$(seq 0 $(argsLenMiddle3));do echo -D $${a[$$i]}=$${b[$$i]};done
#	ASSYMS !=  a=($(imageSyms));b=($(wordlist $(argsLenMiddle2),$(argsLen),$(imageValues)));for i in $$(seq 0 $(argsLenMiddle4));do echo --defsym $${a[$$i]}=$${b[$$i]};done
# imageMacros := DRIVER SECSTART SECNUM CODESEG CODEOFF
# imageSyms := JMPSEG JMPOFF
#==================================================================================
.PHONY : dump16 dump default nothing help debug exportversion backup push all update-host-tools console
.ONESHELL:
.SECONDEXPANSION:
default:
	make $(GEN)/main.bimg
nothing:
	@
all:
	# nothing
debug:
	@echo	CCFLAGS 	'--->'		$(CCFLAGS)
	echo	args		'--->'		$(args)
	echo	CCMACROS	'--->'		$(CCMACROS)
	echo	imageMacros	'--->'		$(imageMacros)
	echo	ldfiles		'--->'		$(ld32) $(ld16)
help:
	@echo You can specify the args to make a PMLoader.@see PMLoader.h and main.cpp
	echo	make dump16 f=main_16.bimg
	echo	make dump opt="-m i8086" file=main_16.bimg
dump:
	@objdump -dS $(GEN32)/main.img -m i386|less
dump16:
	@objdump -dS $(GEN16)/main.img -m i8086 | less

update-host-tools:
ifeq ($(HOST),windows)
	mkdir -p '$(TOOLSDIR)/windows'
	echo 'cd $(HOSTROOTDIR)\tools\bochs-run && c: && bochs -q -f bochs2.6.9.bxrc' > '$(TOOLSDIR)/windows/run_bochs.cmd'
	echo 'cd $(HOSTROOTDIR)\tools\bochs-run && c: && bochsdbg -q -f bochs2.6.9.bxrc -rc debugger.rc' > '$(TOOLSDIR)/windows/start_bochs.cmd'
	echo 'cd $(HOSTROOTDIR)\tools\bochs-run && c: && bochsdbg -q -f bochs2.6.9.bxrc' > '$(TOOLSDIR)/windows/start_bochs_norc.cmd'
endif


#只有实现了make的非等待异步返回才能成功
#不知为何，只有bash --login才能成功， 只有 mintty & 后面的命令执行久一点才能成功，我不知为何。
console:
ifeq ($(HOST),windows)
	mintty -i -e bash --login -c 'cd $$(cygpath -p "$(HOSTROOTDIR)") ; mintty & i=20;while [ $$i != 0 ] ;do echo $$((i--));done '  #and then input ee
	#mintty -i -e bash --login -c 'cd devel;mintty & sleep 10'  #and then input ee
endif


#====================HOST  specific tools=================
#注意：你只有先cd到某个目录，才能执行explorer，explorer 路径不能成功。
ifeq ($(HOST),windows)
.PHONY: bochs_debug bochs_debug_rc bochs_run
bochs_debug_rc:
	-cmd /C 'cd $(HOSTROOTDIR)\tools\bochs-run && C: && explorer windows\start_bochs.cmd'
bochs_run:
	-cmd /C 'cd $(HOSTROOTDIR)\tools\bochs-run && C: && explorer windows\run_bochs.cmd'
bochs_debug:
	-cmd /C 'cd $(HOSTROOTDIR)\tools\bochs-run && C: && explorer windows\start_bochs_norc.cmd'
endif

exportversion:VERSION $(SRC) $(INCLUDE) Makefile start_bochs.cmd main.bimg
	@v=$$(cat VERSION)
	mkdir --parents $(EXPORTS)/$${v}
	cp  $^ -t $(EXPORTS)/$${v}
	echo VERSION:$${v}
backup:$(fbackup)
	@v=$$(cat VERSION)
	tar --xz -cf $(BACKUP)/x2-$${v}.tar.xz $^
push : 
	git push https://github.com/xhd2015/x2.git $(B)
#===================================================================================
.PHONY : lib64 clean clean32 clean64 clean16
lib64:$(GEN64)/lib64.a
	@echo Generated for host 64.
	
$(GEN64)/lib64.a:$(patsubst %,$(GEN64)/%.o,$(f64))
	ar -rs $@ $^	
$(GEN32)/main.img:$(patsubst %,$(GEN32)/%.o,$(f32))
	ld -Timage_32.ld $(LDFLAGS) $^ -o $@
$(GEN16)/main.img:$(patsubst %,$(GEN16)/%.o,$(f16))
	ld -Timage_16.ld $(LDFLAGS) $^ -o $@
	
$(GEN16)/main.bimg: $(GEN16)/main.img
	objcopy -g -j .secmbr -j .secmain -O binary $< $@
$(GEN32)/main.bimg: $(GEN32)/main.img
	objcopy -g -j .text -j .data -O binary $< $@
	

$(GEN32)/UserProcess2.img:$(patsubst %,$(GEN32)/%.o,$(f32user))
	ld -Timage_32_proc2.ld	$(LDFLAGS) $^ -o $@
$(GEN32)/UserProcess1.img:$(patsubst %,$(GEN32)/%.o,$(f32user))
	ld -Timage_32_proc1.ld	$(LDFLAGS) $^ -o $@
	
$(GEN32)/UserProcess1.bimg:$(GEN32)/UserProcess1.img
	objcopy -g -j .text -j .data -O binary $< $@
$(GEN32)/UserProcess2.bimg:$(GEN32)/UserProcess2.img
	objcopy -g -j .text -j .data -O binary $< $@

#16 sectors for each process code/data
$(GEN32)/UserProcess.bimg:$(GEN32)/UserProcess1.bimg $(GEN32)/UserProcess2.bimg
	if [ ! -f $@ ];then
		touch $@
	fi
	while [ ! -f $@ ];do :;done
	dd if=$(GEN32)/UserProcess1.bimg of=$@	bs=1c count=$$((16*512))	conv=notrunc &&\
	dd if=$(GEN32)/UserProcess2.bimg of=$@	seek=$$((512*16)) bs=1c count=$$((16*512))	conv=notrunc
	
#$(GEN)/main.bimg:partitions_table $(GEN16)/main.bimg $(GEN32)/main.bimg $(GEN32)/UserProcess.bimg
#if [ ! -f $@ ];then 
#cmd /C 'cd C:\Users\13774\Desktop\old_desktop\bochs\devel\x2^ system\tools\bochs^ run && explorer create_main_image.cmd'
#fi
#while [ ! -f $@ ];do :;done  #wait until that image file is created
##########DEPRECATED##################
# a host specific Makefile is not good Makefile
	
$(GEN)/main.bimg:partitions_table $(GEN16)/main.bimg $(GEN32)/main.bimg $(GEN32)/UserProcess.bimg
	cp $(TOOLSDIR)/main.bimg.clean gen/main.bimg
	dd if=$(GEN16)/main.bimg of=$@ bs=1c count=$$(( 512 * $(CONFIG_REAL_SECNUMS))) conv=notrunc &&\
	dd if=partitions_table of=$@  bs=1c conv=notrunc seek=$$((0x1BE)) count=$$((512  - 0x1BE)) &&\
	dd if=$(GEN32)/main.bimg of=$@ bs=1c conv=notrunc seek=$$((512  *  $(CONFIG_REAL_SECNUMS))) count=$$(( 512  * $(CONFIG_PROTECTED_SECNUMS))) \
	&&\
	dd if=$(GEN32)/UserProcess.bimg of=$@ bs=1c conv=notrunc seek=$$((512*$(CONFIG_PROTECTED_SECNUMS) + 512*$(CONFIG_REAL_SECNUMS))) count=$$((512 * $(CONFIG_USER_PROCESS_SECNUMS)))

# .s --> .o
$(GEN16)/%.o:$(GEN16)/%.s
	$(AS) $(ASSYMS) $< -o $@
$(GEN32)/%.o:$(GEN32)/%.s
	$(AS) $(ASSYMS) $< -o $@
$(GEN64)/%.o:$(SRC)/%.cpp
	$(CXX) $(CCFLAGS64) $(CCMACROS64) -c $< -o $@

# .cpp --> .s
$(GEN16)/%.s:$(SRC)/%.cpp
	$(CXX) $(CCFLAGS) $(CCFLAGS16) $(CCMACROS) $(CCMACROS16) -S $< -o $@
$(GEN32)/%.s:$(SRC)/%.cpp
	$(CXX) $(CCFLAGS) $(CCFLAGS32) $(CCMACROS) $(CCMACROS32) -S $< -o $@
#$(GEN64)/%.s:$(SRC)/%.cpp
#	$(CXX) $(CCFLAGS64) $(CCMACROS64) -S $< -o $@

#.h --> .cpp
$(SRC)/%.cpp:$(INCLUDE)/*
	@#nothing
# me --> .cpp .h  由我本人亲自操刀
.cpp .h:
	@echo Fulton is doing it.

#Keep the directory structure
clean:clean16 clean32 clean64
	#clean all
clean16:
	-rm -rf $(GEN16)/*
clean32:
	-rm -rf $(GEN32)/*
clean64:
	-rm -rf $(GEN64)/*

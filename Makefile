
dir = /home/Fulton Shaw/x2-devel
#GEN contains 16,32 and 64(can be used in hosted enviorenment)
GEN := gen
GEN16 := gen/16
GEN32 := gen/32
GEN64 := gen/64
SRC := src
EXPORTS := exports
BACKUP := backups
INCLUDE := include
STDC := stdc
STDCPP := stdc++

#control which files are compiled.
f16 := main libx2 PMLoader Descriptor
f32 := protected_main libx2 PMLoader Descriptor TSS interrupts IOProgramer Memory test List
f64 := libx2 PMLoader Descriptor TSS Memory List Locator


ld16 := image_16.ld
ld32 := image_32.ld

fbackup := $(INCLUDE) $(SRC) $(ld16) $(ld32) Makefile TODO README  $(STDC) $(STDCPP) test tools filesystem deprecated from-gcc
CCFLAGS :=  -fpack-struct=1 -fno-exceptions  -nostdinc -nostdinc++ -nostdlib -Winline --no-warnings -I ./include
CCFLAGS32 := -m32
CCFLAGS16 := -m32
CCMACROS := 
CCMACROS16 := -D CODE16
CCMACROS32 := -D CODE32



CCFLAGS64 := -m64 -I./include -std=c++11 -fpack-struct=1
CCMACROS64 := -D CODE64

LDFLAGS :=    --print-gc-sections --no-gc-sections
UNUSED_CCFLAGS := -fkeep-inline-functions -fpermissive
#===Deprecated=====
#	CCMACROS16 != a=($(imageMacros));b=($(wordlist 1,$(argsLenMiddle1),$(imageValues)));for i in $$(seq 0 $(argsLenMiddle3));do echo -D $${a[$$i]}=$${b[$$i]};done
#	ASSYMS !=  a=($(imageSyms));b=($(wordlist $(argsLenMiddle2),$(argsLen),$(imageValues)));for i in $$(seq 0 $(argsLenMiddle4));do echo --defsym $${a[$$i]}=$${b[$$i]};done
# imageMacros := DRIVER SECSTART SECNUM CODESEG CODEOFF
# imageSyms := JMPSEG JMPOFF
#==================================================================================
.PHONY : dump16 dump clean default nothing help debug start run export backup
.ONESHELL:
.SECONDEXPANSION:
default:
	make $(GEN)/main.bimg
nothing:
	@
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
	@objdump -D $(GEN32)/main.img -m i386|less
dump16:
	@objdump -D $(GEN16)/main.img -m i8086 | less
start:
	-@cmd /C 'cd C:\Users\13774\Desktop\bochs\devel\x2^ system\tools\bochs^ run && explorer start_bochs.cmd'
run:
	-@cmd /C 'cd C:\Users\13774\Desktop\bochs\devel\x2^ system\tools\bochs^ run && explorer run_bochs.cmd'
export:VERSION $(SRC) $(INCLUDE) Makefile start_bochs.cmd main.bimg
	@v=$$(cat VERSION)
	mkdir --parents $(EXPORTS)/$${v}
	cp  $^ -t $(EXPORTS)/$${v}
	echo VERSION:$${v}
backup:$(fbackup)
	@v=$$(cat VERSION)
	tar --xz -cf $(BACKUP)/x2-$${v}.tar.xz $^
#===================================================================================
.PHONY : lib64
lib64:$(GEN64)/lib64.a
	@echo Generated for host 64.
	
$(GEN64)/lib64.a:$(patsubst %,$(GEN64)/%.o,$(f64))
	ar -rs $@ $^	
$(GEN32)/main.img:$(patsubst %,$(GEN32)/%.o,$(f32))
	ld -Timage_32.ld $(LDFLAGS) $^ -o $@
$(GEN16)/main.img:$(patsubst %,$(GEN16)/%.o,$(f16))
	ld -Timage_16.ld $(LDFLAGS) $^ -o $@
$(GEN16)/main.bimg: $(GEN16)/main.img
	objcopy -g --pad-to $$((512*16)) -j .seclt -j .secld -j .seclb -j .secmain -j .lastsec -O binary $< $@
$(GEN32)/main.bimg: $(GEN32)/main.img
	objcopy -g --pad-to $$((512*60)) -j .text -j .data -O binary $< $@
$(GEN)/main.bimg : $(GEN16)/main.bimg $(GEN32)/main.bimg
	cat $^ > $@

# .s --> .o
$(GEN16)/%.o:$(GEN16)/%.s
	as $(ASSYMS) $< -o $@
$(GEN32)/%.o:$(GEN32)/%.s
	as $(ASSYMS) $< -o $@
$(GEN64)/%.o:$(GEN64)/%.s
	as $< -o $@

# .cpp --> .s
$(GEN16)/%.s:$(SRC)/%.cpp
	g++ $(CCFLAGS) $(CCFLAGS16) $(CCMACROS) $(CCMACROS16) -S $< -o $@
$(GEN32)/%.s:$(SRC)/%.cpp
	g++ $(CCFLAGS) $(CCFLAGS32) $(CCMACROS) $(CCMACROS32) -S $< -o $@
$(GEN64)/%.s:$(SRC)/%.cpp
	g++ $(CCFLAGS64) $(CCMACROS64) -S $< -o $@

#.h --> .cpp
$(SRC)/%.cpp:$(INCLUDE)/*
	@#nothing
# me --> .cpp .h  由我本人亲自操刀
.cpp .h:
	@echo Fulton is doing it.
#===特殊处理

#Keep the directory structure
clean:
	-rm -rf $(GEN16)/* $(GEN32)/* $(GEN64)/* $(GEN)/main.bimg

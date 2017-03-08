
dir = /home/Fulton Shaw/x2-devel
GEN := gen
SRC := src
EXPORTS := exports
BACKUP := backups
INCLUDE := include
STDC := stdc
STDCPP := stdc++
f16 = main libx2 PMLoader Descriptor
f32 = protected_main libx2 PMLoader Descriptor TSS interrupts IOProgramer Memory test List
fallh = libx2 PMLoader Descriptor TSS interrupts IOProgramer Memory test List

fallcpp = main libx2 PMLoader Descriptor protected_main TSS interrupts IOProgramer List

fhs = $(patsubst %,%.h,$(fallh))
fcpp = $(patsubst %,%.cpp,$(fallcpp))

f16s := $(patsubst %,%_16.s,$(f16))
f32s := $(patsubst %,%_32.s,$(f32))

f16o := $(patsubst %,%_16.o,$(f16))
f32o := $(patsubst %,%_32.o,$(f32))


ld16 := image_16.ld
ld32 := image_32.ld

fbackup := $(INCLUDE) $(SRC) $(ld16) $(ld32) Makefile TODO README  $(STDC) $(STDCPP) test tools filesystem deprecated from-gcc
CCFLAGS :=  -fpack-struct=1 -fpermissive -fno-exceptions  -nostdinc -nostdinc++ -nostdlib -Winline --no-warnings -I ./include
LDFLAGS :=    --print-gc-sections --no-gc-sections  
UNUSED_CCFLAGS := -fkeep-inline-functions 
CCMACROS16 := -D CODE16
CCMACROS32 := -D CODE32
RMFILES := $(f16o) $(f32o) $(f16s) $(f32s) main_32.img main_32.bimg main_16.img main_16.bimg

#===Deprecated=====
#	CCMACROS16 != a=($(imageMacros));b=($(wordlist 1,$(argsLenMiddle1),$(imageValues)));for i in $$(seq 0 $(argsLenMiddle3));do echo -D $${a[$$i]}=$${b[$$i]};done
#	ASSYMS !=  a=($(imageSyms));b=($(wordlist $(argsLenMiddle2),$(argsLen),$(imageValues)));for i in $$(seq 0 $(argsLenMiddle4));do echo --defsym $${a[$$i]}=$${b[$$i]};done
# imageMacros := DRIVER SECSTART SECNUM CODESEG CODEOFF
# imageSyms := JMPSEG JMPOFF
#==================================================================================
.PHONY : dump16 dump clean default nothing help debug start export backup
.ONESHELL:
.SECONDEXPANSION:
default:
	@
	make main.bimg
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
	@objdump -D $(GEN)/main_32.img|less
dump16:
	@objdump -D $(GEN)/main_16.img -m i8086 | less
start:
	-@cmd /C 'cd D:\ForNew10\Users\13774\Desktop\bochs\devel\x2^ system\tools\bochs^ run && explorer start_bochs.cmd'
export:VERSION $(SRC) $(INCLUDE) Makefile start_bochs.cmd main.bimg
	@v=$$(cat VERSION)
	mkdir --parents $(EXPORTS)/$${v}
	cp  $^ -t $(EXPORTS)/$${v}
	echo VERSION:$${v}
backup:$(fbackup)
	@v=$$(cat VERSION)
	tar --xz -cf $(BACKUP)/x2-$${v}.tar.xz $^
#===================================================================================
$(GEN)/main_32.img $(GEN)/main_16.img:$$(patsubst %,$(GEN)/%, $$($$(patsubst $(GEN)/main_%.img,f%o,$$@)) )
	ld -T$(patsubst $(GEN)/main_%.img,image_%.ld,$@) $(LDFLAGS) $^ -o $@
$(GEN)/main_16.bimg: $(GEN)/main_16.img
	objcopy -g --pad-to $$((512*16)) -j .seclt -j .secld -j .seclb -j .secmain -j .lastsec -O binary $< $@
$(GEN)/main_32.bimg: $(GEN)/main_32.img
	objcopy -g --pad-to $$((512*60)) -j .text -j .data -O binary $< $@
main.bimg : $(GEN)/main_16.bimg $(GEN)/main_32.bimg
	cat $^ > $@

# .s --> .o
$(patsubst %,$(GEN)/%,$(f16o) $(f32o)):$$(patsubst %.o,%.s,$$@)
	as $(ASSYMS) $< -o $@

# .cpp --> .s
$(patsubst %,$(GEN)/%,$(f16s)):$$(patsubst $(GEN)/%_16.s,$(SRC)/%.cpp,$$@)
	g++ $(CCFLAGS) $(CCMACROS) $(CCMACROS16) -S $< -o $@

$(patsubst %,$(GEN)/%,$(f32s)):$$(patsubst $(GEN)/%_32.s,$(SRC)/%.cpp,$$@)
	g++ $(CCFLAGS) $(CCMACROS) $(CCMACROS32) -S $< -o $@

#.h --> .cpp
$(patsubst,%,$(SRC)/%,$(fcpp)):$(patsubst,%,$(INCLUDE)/%,$(fhs))
	@#nothing
# me --> .cpp .h  由我本人亲自操刀
.cpp .h:
	@echo Fulton is doing it.
#===特殊处理

clean:
	@#
	#-cd $(GEN)
	#rm $(RMFILES)
	#rm ../main.bimg
	-rm $(GEN)/* main.bimg

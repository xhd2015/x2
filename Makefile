
# args="0 0 0 0 1 2 3"
dir = /home/Fulton Shaw/x2-devel
f16 = main libx2 PMLoader Descriptor
f32 = protected_main libx2 PMLoader Descriptor TSS interrupts IOProgramer Memory test

fall = main libx2 PMLoader Descriptor protected_main TSS interrupts IOProgramer

fh = $(patsubst %,%.h,$(fall))
fcpp = $(patsubst %,%.cpp,$(fall))

f16s := $(patsubst %,%_16.s,$(f16))
f32s := $(patsubst %,%_32.s,$(f32))

f16o := $(patsubst %,%_16.o,$(f16))
f32o := $(patsubst %,%_32.o,$(f32))

ld16 := image_16.ld
ld32 := image_32.ld

imageMacros := DRIVER SECSTART SECNUM CODESEG CODEOFF
imageSyms := JMPSEG JMPOFF
CCFLAGS :=  -fpack-struct=1 -fpermissive -fno-exceptions  -nostdinc -nostdinc++ -nostdlib -Winline
LDFLAGS :=    --print-gc-sections --no-gc-sections  
UNUSED_CCFLAGS := -fkeep-inline-functions --no-warnings
CCMACROS16 := -D CODE16
CCMACROS32 := -D CODE32
RMFILES := $(f16o) $(f32o) $(f16s) $(f32s) main_32.img main_32.bimg main_16.img main_16.bimg main.bimg

#===Deprecated=====
#	CCMACROS16 != a=($(imageMacros));b=($(wordlist 1,$(argsLenMiddle1),$(imageValues)));for i in $$(seq 0 $(argsLenMiddle3));do echo -D $${a[$$i]}=$${b[$$i]};done
#	ASSYMS !=  a=($(imageSyms));b=($(wordlist $(argsLenMiddle2),$(argsLen),$(imageValues)));for i in $$(seq 0 $(argsLenMiddle4));do echo --defsym $${a[$$i]}=$${b[$$i]};done
#==================================================================================
.PHONY : dump16 dump clean default nothing help debug start
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
	@objdump -D main_32.img|less
dump16:
	@objdump -D main_16.img -m i8086 | less
start:
	-@cmd /C 'cd C:\Users\Fulton\Desktop\bochs\devel\x2^ system && explorer start_bochs.cmd'
#===================================================================================
main_32.img main_16.img:$$($$(patsubst main_%.img,f%o,$$@))
	ld -T$(patsubst main_%.img,image_%.ld,$@) $(LDFLAGS) $^ -o $@  
main_16.bimg: main_16.img
	objcopy -g --pad-to $$((512*16)) -j .seclt -j .secld -j .seclb -j .secmain -j .lastsec -O binary $< $@
main_32.bimg: main_32.img
	objcopy -g --pad-to $$((512*60)) -j .text -j .data -O binary $< $@
main.bimg : main_16.bimg main_32.bimg
	cat $^ > main.bimg

# .s --> .o
$(f16o) $(f32o):$$(patsubst %.o,%.s,$$@)
	as $(ASSYMS) $< -o $@

# .cpp --> .s
$(f16s):$$(patsubst %_16.s,%.cpp,$$@)
	g++ $(CCFLAGS) $(CCMACROS) $(CCMACROS16) -S $< -o $@

$(f32s):$$(patsubst %_32.s,%.cpp,$$@)
	g++ $(CCFLAGS) $(CCMACROS) $(CCMACROS32) -S $< -o $@

# me --> .cpp .h  由我本人亲自操刀
.cpp .h:
	@echo Fulton is doing it.
#===特殊处理

clean:
	-rm $(RMFILES)

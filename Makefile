
# args="0 0 0 0 1 2 3"
dir = /home/Fulton Shaw/x2-devel
f16 = main libx2 PMLoader Descriptor
f32 = protected_main libx2 Descriptor TSS interrupts IOProgramer Memory

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
argsLen != echo $$(( $(words $(imageSyms)) + $(words $(imageMacros)) ))
argsLenMiddle1 := $(words $(imageMacros))
argsLenMiddle2 != echo -n $$(( $(argsLenMiddle1) + 1 ))
argsLenMiddle3 != echo -n $$(( $(argsLenMiddle1) - 1 ))
argsLenMiddle4 != echo -n $$(( $(words $(imageSyms)) -1 ))
imageValues := $(args)
ifneq ($(words $(imageValues)),$(argsLen))
	imageValues := 0 16 34 0 0 0x10
	imageValues := $(imageValues) 0x800 0x10000	#采用默认参数,参见设计文件，16~99属于保护模式代码.跳转代码到GDT[2]:4*512处
endif
CCFLAGS :=  -fpack-struct=1 -fpermissive -fno-exceptions  -nostdinc -nostdinc++ -nostdlib -Winline
UNUSED_CCFLAGS := -fkeep-inline-functions --no-warnings
CCMACROS := -D IDT_START=0x9c00 -D IDT_SIZE=400 -D GDT_START=0x9d90 -D GDT_SIZE=800
CCMACROS16 != a=($(imageMacros));b=($(wordlist 1,$(argsLenMiddle1),$(imageValues)));for i in $$(seq 0 $(argsLenMiddle3));do echo -D $${a[$$i]}=$${b[$$i]};done
CCMACROS32 := -D TSS_MIN_SIZE=104 -D TSS_AREA_START=0x4400 -D TSS_AREA_SIZE=1040
ASSYMS !=  a=($(imageSyms));b=($(wordlist $(argsLenMiddle2),$(argsLen),$(imageValues)));for i in $$(seq 0 $(argsLenMiddle4));do echo --defsym $${a[$$i]}=$${b[$$i]};done
LDFLAGS :=    --print-gc-sections --no-gc-sections  
RMFILES := $(f16o) $(f32o) $(f16s) $(f32s) main_32.img main_32.bimg main_16.img main_16.bimg main.bimg

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
	echo	make args="0 0 0 0 0" main.s
	echo	make dump16 f=main_16.bimg
	echo	make dump opt="-m i8086" file=main_16.bimg
dump:
	@objdump -D main_32.img|less
dump16:
	@objdump -D main_16.img | less
start:
	-@cmd /C 'cd C:\Users\Fulton\Desktop\bochs\devel\x2^ system && explorer start_bochs.cmd'
#===================================================================================
main_32.img main_16.img:$$($$(patsubst main_%.img,f%o,$$@))
	ld -T$(patsubst main_%.img,image_%.ld,$@) $(LDFLAGS) $^ -o $@  
main_16.bimg: main_16.img
	objcopy -g --pad-to $$((512*16)) -j .seclt -j .secld -j .seclb -j .secmain -j .lastsec -O binary $< $@
main_32.bimg: main_32.img
	objcopy -g --pad-to $$((512*34)) -j .stack -j .text -j .data -O binary $< $@
main.bimg : main_16.bimg main_32.bimg
	cat $^ > main.bimg

# .s --> .o
$(f16o) $(f32o):$$(patsubst %.o,%.s,$$@)
	as $(ASSYMS) $< -o $@

# .cpp --> .s
$(f16s):$$(patsubst %_16.s,%.cpp,$$@)
	g++ $(CCFLAGS) $(CCMACROS) $(CCMACROS16) -D SEG_CURRENT=0x10000 -D CODE16 -S $< -o $@

$(f32s):$$(patsubst %_32.s,%.cpp,$$@)
	g++ $(CCFLAGS) $(CCMACROS) $(CCMACROS32) -D SEG_CURRENT=0x10000 -D CODE32 -S $< -o $@

# me --> .cpp .h  由我本人亲自操刀
.cpp .h:
	@echo Fulton is doing it.
#===特殊处理

clean:
	-rm $(RMFILES)

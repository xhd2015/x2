
# args="0 0 0 0 1 2 3"
f16 = main libx2 PMLoader Descriptor
f32 = protected_main libx2 Descriptor

f16s := $(patsubst %,%_16.s,$(f16))
f32s := $(patsubst %,%.s,$(f32))

f16o := $(patsubst %,%_16.o,$(f16))
f32o := $(patsubst %,%.o,$(f32))

ld16 := image_16.ld
ld32 := image_32.ld

imageMacros := Driver Head Cylinder SecStart SecNum CodeSeg CodeOff
imageValues := $(args)
CCFLAGS := -fpermissive -fno-exceptions
CCMACROS := $(shell a=($(imageMacros));b=($(imageValues));for i in $$(seq 0 $$(( 7 - 1 )));do echo -D $${a[$$i]}=$${b[$$i]};done)
.PHONY : dump16 dump32 clear default

.ONESHELL:
.SECONDEXPANSION:
default:
	@
	make args="0 0 0 0 1 0 0" x

main_16.bimg: main_16.img
	@objcopy -j .seclt -j .secld -j .seclb -j .secmain -j .lastsec -O binary main_16.img main_16.bimg

#.o:.s
$(f16o) $(f32o):$$(patsubst %.o,%.s,$$@)
	as $< -o $@
$(f16s) $(f32s):$$(patsubst %.s,%.cpp,$$@)
	g++ $(CCFLAGS) -S $$< -o $$@


main_16.img: $(ld16) $(f16.o)
	
	a=(main libx2 PMLoader Descriptor)
	CCFLAGS="-fpermissive -fno-exceptions"
	LDFILE=image_16.ld
	b=
	for i in $${a[@]}
	do
		g++ -S -D CODE16 -D Driver=0 -D Head=0 -D Cylinder=0 -D SecStart=0 -D SecNum=5 -D CodeSeg=0 \
	-D CodeOff=0 $$CCFLAGS $${i}.cpp -o $${i}_16.s
		as $${i}_16.s -o $${i}_16.o;b="$$b $$i_16.o"
	done
	ld -T image_16.ld $$b -o main_16.img
	objcopy -j .seclt -j .secld -j .seclb -j .secmain -j .lastsec -O binary main_16.img main_16.bimg

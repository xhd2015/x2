
GEN := gen
GEN64 := ../../gen/64
LIB64 := 64
LIBTHIS := fs

x2src := File MallocToSimple 

.PHONY : default mkfs.x2fs clean

.ONESHELL:
.SECONDARYEXPANSION:

default:
	make mkfs.x2fs
	
mkfs.x2fs:$(GEN)/mkfs.x2fs.exe
	# make mkfs.x2fs.exe
$(GEN)/mkfs.x2fs.exe:$(GEN)/mkfs.x2fs.o $(GEN64)/lib$(LIB64).a $(GEN)/lib$(LIBTHIS).a
	g++  $< -o $@ -D CODE64 -std=c++11 -L$(GEN) -L$(GEN64) -l$(LIBTHIS) -l$(LIB64) -I../../include -fpack-struct=1
$(GEN)/lib$(LIBTHIS).a:$(patsubst %,%.cpp,$(x2src))
	@
	for i in $^;do g++ -c -I../../include -fpack-struct=1 -D CODE64 -std=c++11 $$i -o $$(basename -s .cpp $$i).o;done
	ar crs $(GEN)/lib$(LIBTHIS).a *.o
	rm *.o
$(GEN)/%.o:%.cpp
	g++ -c $< -o $@ -I../../include -D CODE64 -std=c++11 -fpack-struct=1
clean:
	-rm $(GEN)/*	
	



DEBUG := false

GEN := gen
GEN64 := ../../gen/64
LIB64 := 64
LIBTHIS := fs
GEN64LIB := $(GEN64)/lib$(LIB64).a
GENFSLIB := $(GEN)/lib$(LIBTHIS).a

x2src := File ../../src/64/MallocToSimple 
CCFLAGS := -D CODE64 -std=c++11 -fpack-struct=1 -I../../include -L$(GEN64) -L$(GEN)

CXX = g++
AS = as
ifeq ($(DEBUG),true)
	CXX += -g
	AS += -g
endif

.PHONY : default mkfs.x2fs listf newf clean compile


#=============================
.ONESHELL:
.SECONDARYEXPANSION:

default:
	make listf
help:
	#you can set Makefile variable DEBUG to true by '-e DEBUG=true' to enable debugging mode.
	#target compile to compile file, denoted by '-e CFILE=..', no suffix.
	#REMEMBER:-e can be ignored when it has the format A=B
	#HISOTRY: make DEBUG=true CFILE=test compile

all:
	# nothing
listf:$(GEN)/listf.exe
	# make gen/listf.exe
newf:$(GEN)/newf.exe
	# make gen/newf.exe

ifneq ($(CFILE),)
compile:
	$(CXX) $(CFILE).cpp -o $(GEN)/$(CFILE).exe $(CCFLAGS) -Wl,'-(' -l$(LIB64) -l$(LIBTHIS) -Wl,'-)' -static
endif

$(GEN)/newf.exe:newFile.cpp $(GEN64LIB) $(GENFSLIB)
	$(CXX) $< -o $@ $(CCFLAGS) -Wl,'-(' -l$(LIB64) -l$(LIBTHIS) -Wl,'-)' -static
	
$(GEN)/listf.exe:listFile.cpp $(GEN64LIB) $(GENFSLIB)
	$(CXX) $< -o $@ $(CCFLAGS) -Wl,'-(' -l$(LIB64) -l$(LIBTHIS) -Wl,'-)' -static
	
mkfs.x2fs:$(GEN)/mkfs.x2fs.exe
	# make gen/mkfs.x2fs.exe
$(GEN)/mkfs.x2fs.exe:$(GEN)/mkfs.x2fs.o $(GEN64)/lib$(LIB64).a $(GEN)/lib$(LIBTHIS).a
	$(CXX) $< -o $@ -D CODE64 -std=c++11 -L$(GEN64) -L$(GEN) -Wl,-\( -l$(LIB64) -l$(LIBTHIS) -Wl,-\) -I../../include -fpack-struct=1 -static
$(GEN)/lib$(LIBTHIS).a:$(patsubst %,%.cpp,$(x2src))
	# make gen/libfs.a
	# 上面的语句表示在所有的x2src后缀添加.cpp
	@
	for i in $^;do $(CXX) -c -I../../include -fpack-struct=1 -D CODE64 -std=c++11 $$i -o $$(basename -s .cpp $$i).o;done
	ar crs $(GEN)/lib$(LIBTHIS).a *.o
	#上面这句表示生成.a静态库
	
	rm *.o
$(GEN)/%.o:%.cpp
	$(CXX) -c $< -o $@ -I../../include -D CODE64 -std=c++11 -fpack-struct=1
clean:
	-rm $(GEN)/*	
	


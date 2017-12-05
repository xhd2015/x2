cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
project("x2")

set(MY_CCFLAGS -std=c++17 -Werror -Wall -fmax-errors=20 -finput-charset=utf8  -save-temps -Weffc++ -Wreorder  -Wnon-virtual-dtor -Wmisleading-indentation -Wnarrowing  -Wold-style-cast -Wlogical-not-parentheses
 -Winvalid-pch  -Wignored-qualifiers -Wfloat-equal)


#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Werror -Wall -fmax-errors=20 -finput-charset=utf8  -save-temps -Weffc++ -Wreorder  -Wnon-virtual-dtor -Wmisleading-indentation -Wnarrowing  -Wold-style-cast -Wlogical-not-parentheses
# -Winvalid-pch  -Wignored-qualifiers -Wfloat-equal")


add_library(lib64 STATIC src/libx2.cpp src/PMLoader.cpp src/Descriptor.cpp src/TSS.cpp src/MemoryManager.cpp src/List src/Locator.cpp src/AssociatedMemoryManager.cpp)

target_include_directories(lib64 PRIVATE include)
target_compile_definitions(lib64 PRIVATE CODE64)

# for hello
add_executable(hello src/cmake/hello.cpp)
target_link_libraries(hello c)

add_executable(conceptual_test_serialize src/conceptual/all.cpp)
target_include_directories(conceptual_test_serialize PRIVATE include)
target_compile_options(conceptual_test_serialize PRIVATE ${MY_CCFLAGS})
target_compile_definitions(conceptual_test_serialize PRIVATE CODE64 CMDUTIL=test_serialize.cpp)



####===============================


#add_library(lib64 STATIC src/libx2.cpp src/PMLoader.cpp src/Descriptor.cpp src/TSS.cpp src/MemoryManager.cpp src/List src/Locator.cpp src/AssociatedMemoryManager.cpp)
#target_include_directories()
#
#include_directories(include)
#target_compile_definitions(CODE64)
#target_compile_definitions(CMDUTIL test_serialize.cpp)
#add_executable(conceptual_test_serialize src/conceptual/all.cpp)
#target_include_directories(conceptual_test_serialize include)

#add_custom_command(OUTPUT gen/64/conceptual_test_serialize.o
#        COMMAND g++ --help -v
#        )
#
#add_custom_target(hello
#        COMMAND g++ ${MY_CCFLAGS} -I../include -D CODE64 -D CMDUTIL=test_serialize.cpp ../src/conceptual/all.cpp -o gen/64/conceptual_test_serialize.exe
#        USES_TERMINAL
#        SOURCES ../src/File.cpp
#        )
#target_include_directories(hello PRIVATE include)





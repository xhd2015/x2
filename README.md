# What is x2?
At first there is no x2, but under the introduction by my teacher, who instructed to me write an operating system that can run on ARM, which can be later used for my graduation, I proposed to write an OS using complete c++.
Well, then I wrote a program like linux0.00,it runs under bochs well,but has changed the way that a task runs(There are two tasks continuously changing a character on the screen, which becomes different with linux0.00), and also changed the way the code is written by -- it is completely written in c++ and completely compiled successfully using g++.Then as it proceeds, more and more issues have been raised,such as memory management, file system and process etc, and the kernel is getting more and more complicated.
So 'x2' is proposed as a name of this operating system,which has 2 remarkable features: completely written in c++ & the core is completely built from ground without using any existing.

# Can I get involved into development?
Of course you can(though currently there is no other person except me).

# How can I get started to develop x2?
Just as any other projects is developed by community, Copy, Compile, Debug, Modify & Push a request to
fix bugs.

# About source code reading
Src/ and include/ are the two most important folders that contains fully kernel codes.
src/main.cpp 			a real mode program,which loads the protected mode code as kernel into memory.
src/protected_main.cpp 		the protected mode kernel starting code.
include/PMLoader.h src/PMLoader.cpp		mainProcess() describes how the kernel was loaded
include/List.h src/List.cpp	containing two useful data structures : LinkedList & Tree
include/Memory.h src/Memory.cpp describes how memory management was developed
...
 


# Some Hint for developers
1.There are multiple kinds of codes
	16 only
	32 only
	16,32,64 compitable
if one block of code is only supported by a certain length of bits,say XX,then should CODEXX be defined and encloses that block only if it is defined.
Check the code to see if you have done this.



If two classes does have less or weak or zero connection with each other,do not combine them by explicit usage


This set of work is bound to be working under 64-bit

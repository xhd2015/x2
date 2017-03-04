this is the complete c interfaces,do not add anything to it.

please take  note that, you cannot directly use this directory as your standard c library interfaces as it is not fully defined.For instance,take a look at stdio.h,where FILE is not well defined.

You should copy this directory to your development directory and modify them,to make it cooperate with your kernel or your own c-runtime


What drives this collection of interfaces is this concept:
	compiler provides syntax
	standard library provides full functions
	and I provide the way you provide standard library
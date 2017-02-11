x1 = 1 2 3
x2 = 3 4 5
x3 :=$(shell  a=($(x1));b=($(x2));for i in $$(seq 0 $$(( $(words $(x1)) - 1 )));do echo $${a[$$i]}.$${b[$$i]};done)

.PHONY: default testOneShell realone 

.ONESHELL:
default:
	@
	echo my
	echo $(x3)

realone:
	@
	if [ a = a ];then
		echo yes
	fi

testOneShell:
	@
	if ((1));then
		echo no
	fi
.PHONY: realtwo testSE realtwo.s testSE.s
.SECONDEXPANSION:
realtwo.s testSE.s:
	@
	echo me $@
realtwo x:$$(patsubst %,%.s,$$@)
	@
	echo 1 $@ $<
testSE:$$(patsubst %,%.s,$$@)
	@
	echo $@
	


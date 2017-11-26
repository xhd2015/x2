
# 规则 ： 所有的变量名必须以CONFIG_开头，CONFIG_ARGS用于获取CONFIG_ARGS之前已经定义的该类变量

#CONFIG_ARGS := CONFIG_REAL_SECNUMS CONFIG_PROTECTED_SECNUMS CONFIG_USER_PROCESS_SECNUMS CONFIG_USER_PROCESS_EACH_SECNUMS \
#				CONFIG_INPUT_BUFFER_SIZE CONFIG_KERNEL_PDE_NUM	CONFIG_KERNEL_PTE_0_NUM	CONFIG_KERNEL_PTE_1_NUM	\
#				CONFIG_GDT_ITEM_NUM	CONFIG_IDE_ITEM_NUM	CONFIG_KERNEL_MMNODE_NUM

include gen/32/Config.prefixsize.makefile

# config sec numbers here
CONFIG_REAL_SECNUMS := 25

# MBR扇区的分区表起始位置
CONFIG_MBR_PARTITION_START := $(shell echo $$((0x1BE)))

# 
#CONFIG_VBR

#应当比2048小，因为CODE_LIMIT=0xfffff，恰好是2048个扇区
#250目前是正确的
CONFIG_PROTECTED_SECNUMS := 250

CONFIG_USER_PROCESS_SECNUMS := 35

#每个进程占用空间16个
CONFIG_USER_PROCESS_EACH_SECNUMS := 16

#输入缓冲区占据512个双字节
CONFIG_INPUT_BUFFER_SIZE := 512

# 注：初始栈的大小至少是4个扇区，小于此则可能发生错误
# 注：依据经验，目前设置成10个会不够用（溢出）
CONFIG_INIT_STACK_SIZE := $(shell echo $$((15*512)))

# 实模式下初始栈的大小，相对于0x7c0段而言
# 注：当你修改此变量时，必须对image_16.ld文件进行同步
CONFIG_REAL_INIT_STACK_SIZE := $(shell echo $$((2*512)))

# 下面两项分别设置了内核代码的大小和可用内存的大小，加起来刚好4MB，形成一个PDE
# 它们之后就是进程空间
CONFIG_KERNEL_CODE_SIZE := $(shell echo $$((1*1024*1024)))
CONFIG_KERNEL_FREE_MEM_SIZE = $(shell echo $$((3*1024*1024)))

CONFIG_PROCESS_MEM_SIZE = $(shell echo $$((20*1024*1024)))


# PDE的项数
CONFIG_KERNEL_PDE_NUM := 10

# PTE_0的项数
# 注意：该数字*4*1024必须大于等于整个内核的代码
# 但是最好能够将4MB的空间(1个PDE)包括在内
CONFIG_KERNEL_PTE_0_NUM := 1024

# PTE_1用于自由分配，preparePhysicalMap等函数
CONFIG_KERNEL_PTE_1_NUM := 100

# GDT的项数
CONFIG_GDT_ITEM_NUM := 80

# IDT的项数
CONFIG_IDT_ITEM_NUM := 80


# 内核用于管理内存的树节点的项数
# 该节点数必须足够使用才行
CONFIG_KERNEL_MMNODE_NUM := 200

# 在实模式下加载保护模式代码时，需要加载的扇区数
# 注意：必须在下面定义的常数的扇区内将第二次加载的代码加载进来
# 注意：这个值不能超过0x7c00,也就是保护模式的开始
# 一般设置为代码开始处到0x7c00的最大长度
ifeq ($(CONFIG_PREFIX_SIZE),)
CONFIG_REAL_LOAD_PROTECTED_SECNUM := 40
else
CONFIG_REAL_LOAD_PROTECTED_SECNUM := $(shell echo $$((  (0x7c00-$(CONFIG_PREFIX_SIZE))/512  )))
endif


########=========It should be the end of this file=======#################


CONFIG_ARGS := $(filter CONFIG_%,$(.VARIABLES))
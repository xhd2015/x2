.code16gcc

STARTSEG = 0x7c0
STACK = 512

ljmp $STARTSEG,$STARTOFF
STARTOFF:
mov $STARTSEG,%ax
mov %ax,%ds
mov %ax,%ss
mov %ax,%es
#设置段寄存器
mov $STACK,%ax
mov %ax,%sp

#打印字符
mov $message,%ax
mov %ax,%bp #es:bp为基地址
mov $0x7,%bl #背景色
xor %bh,%bh  #页
mov $0x13,%ah #0x13表示打印字符串中断
mov $0,%al  #包含属性与否，光标移动与否

mov $msglen,%cx #长度
xor %dx,%dx  #行列 dh，dl
int $0x10
here:
jmp here

message:
.ascii "Hello world"
msglen = . - message
.org 510
.word 0xaa55

__asm__("movzwl %ax,%eax\n\t");

extern "C" void int0x24()
{
    __asm__(
    "INT_24: \n\t"
    );   
    
    __asm__(
     "iret \n\t"
    );
}
__asm__(
".set _int0x24,INT_24 \n\t" //将int0x24的值设为中断起点
);

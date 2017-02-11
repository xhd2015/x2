#ifdef CODE32
__asm__(".code32 \n\t");

__attribute__((section(".test_section"))) void protectedEntryHolder()
{
      __asm__(
    ".global PROTECTED_SEL,PROTECTED_ENTRY \n\t"
    "PROTECTED_SEL = 0b10000 \n\t"
    "PROTECTED_ENTRY: \n\t"
    );  
}

#endif
/*
MEMORY {
	m_int (rx) : o = 0, len = 256
	m_master : o = 0, len = 512
}
*/
SECTIONS {
	/*
	.stack 0 : {
		. = 512*4;*/  /*栈占有4个扇区*/ /*

	}
	*/ /*This is discarded by objcopy even said -j .stack*/
	.stack 0 : {
		protected_main_32.o(.stack)
	}
	.text : { 
		*(.text)
	}
	.data : {
		*(.rdata .data .bss)
	}
	
	/DISCARD/ : {
		*( ".rdata$zzz" )
	}

}

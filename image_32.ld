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
	.data 512*14: {
		*(.rdata .data .bss)
	}
	.text 512*(14+10): { 
		 /*PROVIDE( _CODE_START = ABSOLUTE(.) );*/
		*(.text)
	}
	
	/DISCARD/ : {
		*( ".rdata$zzz" )
	}

}

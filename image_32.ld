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
	/*最终数据被放在了0处，但是偏移仍然是32个扇区*/
	.data 512*32: {
		*(.rdata .data .bss)
	}
	.text 512*(32+10): { 
		 /*PROVIDE( _CODE_START = ABSOLUTE(.) );*/
		*(.text)
	}
	
	/DISCARD/ : {
		*( ".rdata$zzz" )
	}

}

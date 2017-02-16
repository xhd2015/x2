/*
MEMORY {
	m_int (rx) : o = 0, len = 256
	m_master : o = 0, len = 512
}
*/
SECTIONS {
	.seclt 0:{
		main_16.o(.text)
	}
	.secld :{
		main_16.o(.rdata)
	}
	.secle :{
		main_16.o(.data)
	}
	.seclb :{
		main_16.o(.bss)
	}
	.secmain 1024:{
		main_16.o(.test_section) *(.text)	*(.data) *(.rdata)	*(.bss)
		. = 16*512-1024; /*共占有16个扇区*/
	}
	.lastsec 508: { /*lastsection长度有限制，只能使用lastsec*/
		main_16.o( .last_section )
	}
	/DISCARD/ : {
		*( ".rdata$zzz" ) *(.free)
	}

}

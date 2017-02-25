/*
MEMORY {
	m_int (rx) : o = 0, len = 256
	m_master : o = 0, len = 512
}
*/
SECTIONS {
	.seclt 0:{
		gen/main_16.o(.text)
	}
	.secld :{
		gen/main_16.o(.rdata)
	}
	.secle :{
		gen/main_16.o(.data)
	}
	.seclb :{
		gen/main_16.o(.bss)
	}
	.secmain 1024:{
		gen/main_16.o(.test_section) *(.text)	*(.data) *(.rdata)	*(.bss)
		. = 16*512-1024; /*共占有16个扇区*/
	}
	.lastsec 508: { /*lastsection长度有限制，只能使用lastsec*/
		gen/main_16.o( .last_section )
	}
	/DISCARD/ : {
		*( ".rdata$zzz" ) *(.free)
	}

}

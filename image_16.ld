/*
MEMORY {
	m_int (rx) : o = 0, len = 256
	m_master : o = 0, len = 512
}
*/
SECTIONS {
	.seclt 0:{
		gen/16/main.o(.text)
	}
	.secld :{
		gen/16/main.o(.rdata)
	}
	.secle :{
		gen/16/main.o(.data)
	}
	.seclb :{
		gen/16/main.o(.bss)
	}
	.secmain 1024:{
		gen/16/main.o(.test_section) *(.text)	*(.data) *(.rdata)	*(.bss)
		. = 16*512-1024; /*共占有16个扇区*/
	}
	.lastsec 508: { /*lastsection长度有限制，只能使用lastsec*/
		gen/16/main.o( .last_section )
	}
	/DISCARD/ : {
		*( ".rdata$zzz" ) *(.free)
	}

}

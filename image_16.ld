/*
MEMORY {
	m_int (rx) : o = 0, len = 256
	m_master : o = 0, len = 512
}
*/
SECTIONS {
	.secmbr :{
		gen/16/main.o(.text)
	}
	.secmain 1024:{
		gen/16/main.o(.test_section) *(.data) *(.rdata)	*(.bss)	*(.text)
		. = 25*512-1024;/*共占有25个扇区*/
	}
	/DISCARD/ : {
		*( ".rdata$zzz" ) *(.free)
	}

}

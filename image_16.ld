/*
MEMORY {
	m_int (rx) : o = 0, len = 256
	m_master : o = 0, len = 512
}
*/
SECTIONS {
	.seclt 0:{
		main.o(.text)
	}
	.secld :{
		main.o(.rdata)
	}
	.secle :{
		main.o(.data)
	}
	.seclb :{
		main.o(.bss)
	}
	.secmain 1024:{
		main.o(.test_section) *(.text)	*(.data) *(.rdata)	*(.bss)
	}
	.lastsec 508: { /*lastsection长度有限制，只能使用lastsec*/
		main.o( .last_section )
	}
	/DISCARD/ : {
		*( ".rdata$zzz" )
	}

}

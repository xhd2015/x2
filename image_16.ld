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
	.secmain :{
		*(.data) *(.rdata)	*(.bss)	*(.text)
	}
	/DISCARD/ : {
		*( ".rdata$zzz" )
	}

}

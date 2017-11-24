/*
MEMORY {
	m_int (rx) : o = 0, len = 256
	m_master : o = 0, len = 512
}
*/
SECTIONS {
	.secmbr :{
		gen/16/MBRmain.o(textmbr)
	}
	.secmain :{
		*(.data) *(.rdata)	*(.bss)	*(.text)
	}
	/DISCARD/ : {
		*( ".rdata$zzz" )
	}

}

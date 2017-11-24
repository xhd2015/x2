SECTIONS {
	textvbr :{
		*(textvbr)
	}
	data :{
		*(.data) *(.rdata)	*(.bss)
	}
	textmain : {
		*(textmain)
	}
	
	/DISCARD/ : {
		*( ".rdata$zzz" ) *(.text)
		*(.ctors)
	}

}

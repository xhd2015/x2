SECTIONS {
	.text 512*4: { 
		*(.proc2 .text)
	}
	.data : {
		*(.rdata .data .bss)
	}
	
	/DISCARD/ : {
		*( ".rdata$zzz" ) *(".proc1")
	}

}

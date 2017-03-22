SECTIONS {
	.text 512*4: { /*1 sectors for stack*/
		*(".proc1" .text)
	}
	.data  : {
		*(.rdata .data .bss)
	}
	
	/DISCARD/ : {
		*(".rdata$zzz" ) *(".proc2")
	}

}

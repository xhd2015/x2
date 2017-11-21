SECTIONS {
	/*3 sectors for kernel data */
	/*1 sectors for stack*/
	.text 512*4: { 
		*(".proc1" .text)
	}
	.data  : {
		*(.rdata .data .bss)
	}
	
	/DISCARD/ : {
		*(".rdata$zzz" ) *(".proc2")
	}

}

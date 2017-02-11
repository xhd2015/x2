/*
MEMORY {
	m_int (rx) : o = 0, len = 256
	m_master : o = 0, len = 512
}
*/
SECTIONS {
	/DISCARD/ : {
		*( ".rdata$zzz" )
	}

}

# lui
# Format:
#	    LUI RD, IMM

	.text			    
	.global	_start		

_start:
	lui x5, 0x12345		# int x5 = 0x12345 << 12
	addi x5, x5, 0x678	# x5 = x5 + 0x678
stop:
	j stop			    # Infinite loop to stop execution

	.end			    # End of file

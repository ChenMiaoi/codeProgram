# Add Upper Immediate to PC
# Format:
#	    AUIPC RD, IMM

	.text			    # Define beginning of text section
	.global	_start		# Define entry _start

_start:
	auipc x5, 0x12345	# x5 = PC + (0x12345 << 12)
	auipc x6, 0		    # x6 = PC, to obtain the current PC
stop:
	j stop			

	.end			

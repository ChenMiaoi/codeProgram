SECTION_Arithmetic = \
	add \

SECTION = \
	${SECTION_Arithmetic} \

.DEFALT_GOAL := all
all:
	@echo "begin compile all asm code"
	for dir in ${SECTION}; do ${MAKE} -C $$dir || exit "$$?"; done
	@echo "compile all asm code finished successfully!"

.PHONY: clean
clean:
	for dir in ${SECTION}; do ${MAKE} -C $$dir clean || exit "$$?"; done
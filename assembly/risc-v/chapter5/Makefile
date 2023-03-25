# 算术操作符目录
SECTION_Arithmetic = \
	add 	\
	add2	\
	addi 	\
	sub 	\
	lui		\
	auipc	\

# 伪指令操作目录
SCETION_Pseudoorder = \
	neg 	\
	mv		\
	nop		\
	li		\
	la		\

# 总编译文件目录
SECTION = \
	${SECTION_Arithmetic} 	\
	${SCETION_Pseudoorder} 	\

# 默认的编译目标
# 循环遍历每一个文件夹进行编译
.DEFALT_GOAL := all
all:
	@echo "begin compile all asm code"
	for dir in ${SECTION}; do ${MAKE} -C $$dir || exit "$$?"; done
	@echo "compile all asm code finished successfully!"

.PHONY: clean
clean:
	for dir in ${SECTION}; do ${MAKE} -C $$dir clean || exit "$$?"; done

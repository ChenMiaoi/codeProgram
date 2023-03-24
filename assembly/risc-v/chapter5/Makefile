# 算术操作符目录
SECTION_Arithmetic = \
	add \

# 总编译文件目录
SECTION = \
	${SECTION_Arithmetic} \

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

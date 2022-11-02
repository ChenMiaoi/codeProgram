all:test test1
test:test.c
	gcc -o $@ $^
test1:test1.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -rf test test1

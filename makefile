# Produces the executable from the .c file
# Runs the scanner and output the list
MyScanner: list.c scanner.c
	clang list.c scanner.c -o MyScanner

# Tests for the inputs and outputs of the scanner
test: test1 test2

test1:
	./MyScanner > listTest.txt

test2:
	./MyScanner > sample.c

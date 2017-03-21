# Produces the executable from the .c files
# Runs the scanner and redirecs the input
# Both files are aware of the data structure
# implementation through linking 
MyScanner: list.c scanner.c
	clang list.c scanner.c -o MyScanner

# Tests for the inputs and outputs of the scanner
test: test1 test2

test1:
	./MyScanner sample.c > listTest.txt

test2:
	./MyScanner sample.c >> sample.c

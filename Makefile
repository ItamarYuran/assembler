assembler: main.o first.o second.o dataimage.o symbols.o build_outputs.o macro.o
	gcc -g -ansi -pedantic -Wall  main.o first.o second.o dataimage.o symbols.o build_outputs.o macro.o -o assembler -lm
first.o: first.c data.h
	gcc  -g -c -ansi -pedantic -Wall  first.c -o first.o -lm
macro.o: macro.c data.h
	gcc  -g -c -ansi -pedantic -Wall  macro.c -o macro.o 
symbols.o: symbols.c data.h
	gcc  -g -c -ansi -pedantic -Wall  symbols.c -o symbols.o
main.o: main.c data.h
	gcc  -g -c -ansi -pedantic -Wall  main.c -o main.o 
dataimage.o: dataimage.c data.h
	gcc  -g -c -ansi -pedantic -Wall  dataimage.c -o dataimage.o

second.o: second.c data.h
	gcc  -g -c -ansi -pedantic -Wall  second.c -o second.o
build_outputs.o: build_outputs.c data.h
	gcc  -g -c -ansi -pedantic -Wall  build_outputs.c -o build_outputs.o    	


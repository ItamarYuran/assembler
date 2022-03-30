# assembler
Proud to present you with a project I made at a C course I took at the Open University.
The task was, to build an assembler for an imaginary computer. The assembler gets files contain assembly code as input, and outputs a file containing 
binary code (and two more files i'll explain about later).

The assembly code, consists of sixteen actions, each of which, gets between zero and two operands. The operand could be a piece of data (strings or integers),
an imagenery computer register that holds data, a symbol, that has been defined or will be later on, that stores pieces of code to be used.

The program is divided to several files, each one is responsible for a specific task.

"macro.c" - the first iteration over the code. it gets a code containing macro definitions of code, and each time it sees a reference to that macro, it 
replaces it by the code defined earlier.

"first.c" - here, the machine code starts to form. At this stage, the assembler knows how to "translate" only part of the code it sees. for example,
it can not yet translate pieces of code containing symbols that haven't been defined yet. Each line of assembly code, will eventually be coded to one up to
six lines of bits, twenty bits per line. The way it is coded, is too messy to write here, so i added the task description if you'd like to take a deeper look.
basically, few groups of bits every line is entitled of different information, such as the addressing method the code has been coded in, 
and the source and destination registers of the computer that will store the data. in addition, at this stage, each symbol the program runs into, 
is being analyzed and stored at a table for further encounters with that symbol.

"second.c" - this part completes the translation with final iteration over the code. This time, the program is familiar with all symbols, so each time 
it meets up with a line containing a symbol, it checks the table I mentioned for the data it needs and and completes the machine code.

"build_outputs.c" is incharge of generating three outputs for every input file. The first is "file_name.ob" it contains the machine code, 
converted to hexadecimal redix. "file_name.ent" and "file_name.ext" holds information of all symbols used in this source code, 
and are either defined on another file, or will be used in another file.

As you can see, there are several more files. These incharge of subjects such as data structures iv'e built for the task or the data the program requires.

For more information, you'r more than welcome to contact me :)

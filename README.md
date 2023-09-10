# Solutions to the exercises of K&R's "The C Programming Language" book

The solutions don't use any features of C that are not covered by the book up to the point of each exercise

## Running the solutions

To compile a C program use the `cc program_path -o output_path` command in the terminal (replace the program_path and output_path with your .c file's path and the file name and path you want it to be copmiled to, respectively)
To run the compiled program enter the `output_path` in the terminal. To run programs which use getchar() to read an input, put your desired input in a file, and then use the `cat input_path | output_path` command. For example, to compile and run the tail program, assuming you've cloned the repository into your home directory, use these commands:
`cc ~/K&R_Exercise_Solutions/CHAPTER_5_POINTERS_AND_ARRAYS/5_13_tail/tail.c -o ~/tail`
`cat ~/K&R_Exercise_Solutions/CHAPTER_5_POINTERS_AND_ARRAYS/5_13_tail/tail.c | ~/tail`

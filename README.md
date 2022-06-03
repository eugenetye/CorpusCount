## Project Specification
This is a C program that counts the number of words in a file. This is similar to the common Linux tool `wc` (word count). In fact, you can check that your program is functioning correctly by running `wc -w` on the provided corpus files.

### Buffering Own I/O

Raw file I/O must be used in this program, which means a buffer of 1024 bytes will be filled using the `read()` system call and then parsing text out of that buffer. `strsep()` should be used to parse the text by space or newline character. This will result in a series of non-whitespace tokens that need to be saved in an **array of structs.** When the end of this series of tokens is reached, two things might happen:

1. The filled buffer ends on a word boundary **OR**
2. The filled buffer ends in the middle of a word 

Because this may happen, **the final token in the buffer cannot be trusted to be complete.** The (potentially) partial token must be moved to the front of the buffer and then fill the buffer starting from where that token ends (so the information is not overwritten). If this is not done, the resulting word count will be incorrect.

### Array of Structs

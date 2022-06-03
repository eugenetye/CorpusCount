## Project Specification
This is a C program that counts the number of words in a file. This is similar to the common Linux tool `wc` (word count). In fact, you can check that your program is functioning correctly by running `wc -w` on the provided corpus files.

### Buffering Own I/O

Raw file I/O must be used in this program, which means a buffer of 1024 bytes will be filled using the `read()` system call and then parsing text out of that buffer. `strsep()` should be used to parse the text by space or newline character. This will result in a series of non-whitespace tokens that need to be saved in an **array of structs.** When the end of this series of tokens is reached, two things might happen:

1. The filled buffer ends on a word boundary **OR**
2. The filled buffer ends in the middle of a word 

Because this may happen, **the final token in the buffer cannot be trusted to be complete.** The (potentially) partial token must be moved to the front of the buffer and then fill the buffer starting from where that token ends (so the information is not overwritten). If this is not done, the resulting word count will be incorrect.

### Array of Structs
In this program, an **array of structs** named `WORD_T` is used, where the struct is a data structure that consists of the word and the number of times it occurs in the file. An array of these elements is declared as `words` and the size of that array is being tracked with `total_words`. When a word from the file is encountered [complete token], a linear search of the array should be performed to see if that word has already been encountered:

1. If it has, the `.count` field from the struct is incremented.
2. If this is the first time the word has been countered, the array must be **resized** (using `realloc()`) and add the word and the count of 1 to the end of the array.

### Restrictions
- No file stream functions such as `fopen()`, `fread()` or `fclose()` can be used. 
- Usage of `lseek()` or file pointer reposition [other than by calling `read()`] is not allowed.
- The buffer size must be 1024 bytes.

## Example Output
<img src= "https://user-images.githubusercontent.com/105037989/171901229-fa4b900b-2007-4972-8319-eb1707d21ed1.png" width="400" height="70000">

> The `$` character represents the terminal prompt.

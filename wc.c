#include <fcntl.h>
#include <search.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFSIZE 1024

typedef struct {
	char word[42];
	unsigned count;
} WORD_T;

WORD_T *words = NULL;
size_t total_words = 0;

void print_and_free(WORD_T*, size_t, char*);
int comparator(const void *a, const void *b) {
    return strcmp(a,(*((WORD_T *)b)).word);
}
 

int main(int argc, char **argv) {
    
    // make sure the number of arguments passed is 2
	if (argc != 2) return -1;

	char *infile = argv[1];
	// TODO: open the file O_RDONLY
	int fd = open(infile, O_RDONLY);
	if (fd == -1){
	    perror("open()");
	}

	// initialize buffer and number of bytes to be skipped 
	char buf[BUFSIZE];
	int next = 0;
	
	while (1){
	    
	    // number of bytes to be read into buffer
		int size = ((BUFSIZE -1) - next);
		
		// read into buffer and return actual number of bytes read 
		int bytes = read(fd, buf + next, size);
		
		// let last byte of buffer be null pointer
		buf[bytes + next] = 0;

        // character pointers, token and stringp
		char *token, *stringp = buf;
        

		while (stringp != NULL) {
		    
		    // split the text in the buffer on newlines and spaces
	    	token = strsep(&stringp, "\n ");
	    	
            // last word reached here
			if (stringp == NULL){
			    
			    // get the length of the last word 
				next = strlen(token);
				 
				// move the last word at the end of the buffer to beginning of the buffer
				memmove(buf, token, next);
			}

			else{
			    
			    // we have a valid word here
				if (strlen(token) != 0){
				    
				    //  search the `words` array to see if that word has already been added 
					WORD_T *result = lfind(token, words, &total_words, sizeof(WORD_T), comparator);

                    // if word has already been added, increment the count
					if (result != NULL){
						(*result).count++;
					}
					else{
					    
					    // if not, add a new WORD_T struct to the end of the array of structs `words`
						words = (WORD_T *) realloc(words, sizeof(WORD_T) * (total_words + 1));
                		strcpy(words[total_words].word, token);
                		
                		// set the count to be 1
                		words[total_words++].count = 1;
					}
				}
			}
		} 
        
        // break out of the loop if all content of file has been read
		if(bytes < size){
			break;
		}
	}
	print_and_free(words, total_words, infile);
	// TODO: close the file
    close(fd);
	return 0;
	
}

void print_and_free(WORD_T *words, size_t total_words, char *infile) {
	int sum = 0;
	for (int i = 0; i < total_words; ++i) {
		if (words[i].count > 1)
			printf("%s: %u\n", words[i].word, words[i].count);
		sum += words[i].count;
	}
	printf("\n%d %s\n", sum, infile);

	free(words);
}


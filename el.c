// el - Extension lookup

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "el.h"

int listMatches(const char *ext){
	const size_t ext_len = strlen(ext);
	// extdes from el.h
	const size_t extdes_len = strlen(extdes);
	size_t j = 0;
	int found = 0;
	// Loop over all extensions
	for(size_t i=0; i<extdes_len; ++i){
		if(extdes[i] != ext[j]){ // Mismatch, seek further after the next newline
			while(i<extdes_len && extdes[i] != 10)
				++i;
			j = 0;
			continue;
		}

		// Character match
		if(j == ext_len - 1 && i + 2 < extdes_len && extdes[i+1] == 9){ // Full match
			++found;
			printf(".%s: ", ext);
			while(extdes[++i+1] != 10)
				printf("%c", extdes[i+1]);
			printf("\n");
			j = 0;
			continue;
		}

		++j;
	}
	return found;
}

int main(const int argc, const char *argv[]){
	if(argc != 2){
		fprintf(stderr, "Error: require a single filename or extension\n");
		return 1;
	}

	const char *filename = argv[1];
	size_t file_len = strlen(filename);
	char *file = malloc(file_len * sizeof(char));
	// Convert to lowercase
	for(size_t i = 0; i < file_len; ++i)
		file[i] = tolower(filename[i]);
	char *lasttried = file;
	size_t i = 0;
	int found = 0;
	while(i < file_len){ // Check from the beginning and after every dot
		if(listMatches(file+i) > 0)  // List all matches
			found = 1;
		++i;
		while(file[i] != '.' && i < file_len)
			++i;
		if(i < file_len){ // Skip the dot
			++i;
			lasttried = file+i;
		}
	}
	if(!found){
		if(strlen(lasttried) == 0 || (strlen(lasttried) == 1 && lasttried[0] == '.')){
			printf("Empty Extension\n");
		}else{
			printf(".%s: Unknown Extension\n", lasttried);
		}
		return 2;
	}
}

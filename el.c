// el - Extension lookup

#include "el.h"

char *getext(const char *filename){
	size_t k = 0;
	size_t lenfile = strlen(filename);
	char *ext = malloc(lenfile * sizeof(char));
	for(size_t i = lenfile - 1; ; i--)
		if(filename[i] == '.' || i == 0){
			size_t j = 0;
			if (filename[i] == '.')
				j = i + 1;
			for (; j < lenfile; j++, k++)
				if (isalpha(filename[j]))
					ext[k] = tolower(filename[j]);
				else
					ext[k] = filename[j];
			ext[k + 1] = '\0';
			break;
		}
	return ext;
}

int main(int argc, const char *argv[]){
	if(argc != 2){
		printf("Error: require a single filename\n");
		return 1;
	}

	const char *ext = getext(argv[1]);
	const size_t extlen = strlen(ext);
	const size_t extdescrlen = strlen(extdescr);
	size_t j = 0;
	int found = 0;
	for(size_t i=0; i<extdescrlen; ++i){
		if(extdescr[i] != ext[j]){ // Mismatch, seek after the next newline
			while(i<extdescrlen && extdescr[i] != 10)
				++i;
			j = 0;
			continue;
		}

		// Character match
		if(j == extlen - 1 && i + 2 < extdescrlen && extdescr[i+1] == 9){ // Full match
			found = 1;
			printf(".%s: ", ext);
			while(extdescr[++i+1] != 10)
				printf("%c", extdescr[i+1]);
			printf("\n");
			j = 0;
			continue;
		}

		++j;
	}
	if(!found)
		printf(".%s: Unknown Extension\n", ext);
	return 2;
}

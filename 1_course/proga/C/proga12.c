#include <stdio.h>

int main(int argc, char* argv[]){
	int i;
	FILE* input = fopen("MyFile.txt","w+");
	for(i = 1; i < argc; i++){
		char* str = argv[i];
		FILE* in = fopen(str,"a");
		fprintf(input, "%d. %s\n", i, argv[i]);
	}
}
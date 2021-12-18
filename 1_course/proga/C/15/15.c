#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main(int argc, char** argv){
	char name_file[100];
	setlocale(LC_ALL, "Rus");
	if(strcmp(argv[1], "--file") == 0){
		snprintf(name_file, sizeof(name_file), "%s", argv[2]);
		printf("%s\n", name_file);
		FILE* put = fopen(name_file, "wb");
		char** NAME = (char**) malloc(sizeof(char*) * 128);
		for(int i = 0; i < 128; i++){
			NAME[i] = (char*) malloc (sizeof(char) * 128);
		}
		int Arr[256] = {0};
		char* c;
		if(strcmp(argv[3], "--create") == 0){
			for(int i = 4; i < argc; i++){
				printf("%s\n", argv[i]);//фигня
				for(int j = 0; j < strlen(argv[i]); j++){
				printf("l");
					//NAME[i - 4][j] = argv[i][j];
				}
				//Arr[i-4] = argv[i];
				FILE* in = fopen(argv[i], "rb");
				if(in == NULL){
					printf("ERROR\n");
				}else{
					while(fread(&c, 1, 1, in)){
						//printf("%s\n", c);//
						int lol = (int)c - 1998028800;
						Arr[lol]++;
						printf("%d\n", lol);//
						fwrite(&c, 1, 1, put);//
					}
				}
				fclose(in);
			}
		}
		fclose(put);
	}else{
		printf("BAD file");
	}
	
	
	return 0;
}
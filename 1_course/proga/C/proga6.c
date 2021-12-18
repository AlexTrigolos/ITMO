#include <stdio.h>
#include <stdlib.h>

int main(){
	int i;
	char Arr[4] = {'W','O','R','K'};
	char *p = Arr;
	for(i = 0; i < 4; ++i){
		printf("%d = %c\t", i, *(p + i));
	}
	printf("\n");
	
	int n = 4;
	char *b;
	b = (char *) malloc(n * sizeof(char));
	b[0] = 'W';
	b[1] = 'O';
	b[2] = 'R';
	b[3] = 'K';
	for(i = 0; i < 4; ++i){
		printf("%d = %c\t", i, b[i]);
	}
	free(b);
	return 0;
}
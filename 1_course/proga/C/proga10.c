#include <stdio.h>
#include <string.h>

int nod(int a, int b){
	int max = 1;
	if(a == b){
		max = a;
	} else if(a<b){
		for(int i = 2; i <= a; i++){
			if(a % i == 0 && b % i == 0){
				max = i;
			}
		}
	} else {
		for(int i = 2; i <= b; i++){
			if(a % i == 0 && b % i == 0){
				max = i;
			}
		}
	}
	return max;
}

int nok(int a, int b){
	int min = 0;
	int i;
	if (a == b){
		min = a;
	} else if(a > b){
		i = a;
		while(i % b != 0 || i % a != 0){
			i++;
		}
		min = i;
	} else {
		i = b;
		while(i % a != 0 || i % b != 0){
			i++;
		}
		min = i;
	}
	return min;
}

void DeleteSpace(char *str, int ind, int norm){
	int i;
	if (str[ind] ==' ')
		DeleteSpace(str, ind + 1, norm);
	for (i = norm; i < strlen(str)-1; i++){
		str[i] = str[i+1];
	}
	str[i]=0;
}



int main(){
	int a, b;
	int i;
	scanf("%d %d", &a, &b);
	printf("NOD = %d\nNOK = %d\n", nod(a, b), nok(a, b));
	char str[100];
	scanf("\n\n");
	int norm;
	fgets(str, 100, stdin);
	for (i = 0;i < strlen(str); i++){
		if (str[i] == ' ' && str[i + 1] == ' ')
			DeleteSpace(str, i + 2, i + 2);
		if (str[i] == '.' && str[i + 2] == ' ')
			DeleteSpace(str, i + 2, i + 2);
		if (str[i] == '(' && str[i + 1] == ' ')
			DeleteSpace(str, i + 1, i + 1);
		if (str[i] == '[' && str[i + 1] == ' ')
			DeleteSpace(str, i + 1, i + 1);
		if (str[i] == '{' && str[i + 1] == ' ')
			DeleteSpace(str, i + 1, i + 1);
	}
	printf("%s", str);
	return 0;
}



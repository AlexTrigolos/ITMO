#include <stdio.h>
#include <string.h>

int main(){

	char string1[100], string2[100], string3[200], n, *p, str1[100], str2[100], *l, s[100];
	int c, m=0, max=0, i, b=1;
	printf("enter string 1\n");
	scanf("%s", &string1);
	printf("enter string 2\n");
	scanf("%s", &string2);
	printf("enter number\n");
	scanf("%d", &c);
	for(i=0;i<101;i++){
		str1[i]=string1[i];
		s[i]=string1[i];
		str2[i]=string2[i];
	}

	printf("\nZadanie 2 \n");
	strncat(string1,string2,c);
	printf("%s \n",string1);

	printf("\nZadanie 5 \n");
	printf("%s\n",strncpy (s,string2,c));

	printf("\nZadanie 8 \n");
	printf("The character 'i' is at position: %d\n", (strchr(string1,'i')-string1+1));
		
	printf("\nZadanie 11 \n");
	for(p = str1; *p; ++p){
		if(strchr(str2, *p)){
			m++;
		} else {
			max=(m>max)?m:max;
			m=0;
		}
	}
	printf("%d\n", max);
	
	m=0;
	
	printf("\nZadanie 13 \n");
	for(p=str1; *p; p++){
		for(l=str2; *l; l++){
			if(strchr(l, *p)){
				m++;
			}
		}
		if(m==0){
			printf("%c", *p);
			b=0;
		} else if(b==0){
			printf(" ");
			b++;
		}
		m=0;
	}
	return 0;
}









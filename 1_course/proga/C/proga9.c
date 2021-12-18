#include <stdio.h>
 
int main(){ 
	char a[80] = {'\0'}; 
	int num = 0, upp = 0, low = 0;
	scanf("%s", &a);
	for (int n = 0; n < 80; n++){ 
		if (a[n] >= '0' && a[n] <= '9')
			num++; 
		else if (a[n] >= 'A' && a[n] <= 'Z')
			upp++; 
		else if (a[n] >= 'a' && a[n] <= 'z')
			low++; 
	}
	printf("Number = %d\nUpper = %d\nLower = %d\n", num, upp, low); 
	
	int i, m, p;
	float s;
	scanf("%d%f%d", &m, &s, &p);
	for(i=1;i<=m;i++){
		s=s-s*10/100;
		if(s>0.009){
			printf("month = %d, count = %.2f\n", i, s);
		} else {
			printf("No money");
			break;
		}
	}
	return 0;
}
#include<stdio.h>

int main(){
	FILE* in=fopen("lol.txt","r");
	int k, i, m=0;
	for(i=0;i<128;i++){
		fscanf(in, "%d", &k);
		if(k==200){
			printf("01");
			m+=2;
		} else if(k==220){
			printf("10");
			m+=2;
		} else if(k==160){
			printf("11");
			m+=2;
		} else if(k==140){
			m+=3;
			printf("000");
		} else if(k==180){
			printf("0010");
			m+=4;
		} else if(k==100){
			printf("00110");
			m+=5;
		} else if(k==120){
			printf("00111");
			m+=5;
		} else{
			printf("aswdefwgrthykuytrgefdwenttredwfegred");
		}
	}
	printf("\n%d\n", m);
	fclose(in);
	return 0;
}
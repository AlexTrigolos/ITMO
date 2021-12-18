#include <stdio.h>

struct child{
	int id;
	int num;
	int rar;
};

 func(int n, int idone, int idtwo, int idthree, int idfour){
	int one = 0, two = 0, three = 0, four = 0;
	int i = 1, sum1 = 0, sum2 = 0, sum3 =0, sum4 = 0, id;
	float maxid;
	int max1 = -1, max2 = -1, max3 = -1, max4 = -1, num1, num2, num3, num4;
	while(i <= n){
		if(i.id == idone){
			one++;
			if(i.rar > max1){
				max1 = i.rar;
				num1 = i.num;//
			}
			sum1+=i.rar;
		} else if(i.id == idtwo){
			two++;
			if(i.rar > max2){
				max2 = i.rar;
				num2 = i.num;//
			}
			sum2+=i.rar;
		} else if(i.id == idthree){
			three++;
			if(i.rar > max3){
				max3 = i.rar;
				num3 = i.num;//
			}
			sum3+=i.rar;
		} else {
			four++;
			if(i.rar > max4){
				max4 = i.rar;
				num4 = i.num;//
			}
			sum4+=i.rar;
		}
	}
	float s1 = sum1/one;//
	float s2 = sum2/one;//
	float s3 = sum3/one;//
	float s4 = sum4/one;//
	i = 1;
	if(s1 > s2 && s1> s3 && s1> s4){
		maxid = s1;
	} else if(s2 > s1 && s2> s3 && s2> s4){
		maxid = s2;
	} else if(s3 > s2 && s3> s1 && s3> s4){
		maxid = s3;
	} else{
		maxid = s4;
	}
	
	
 }
 
 
 
 
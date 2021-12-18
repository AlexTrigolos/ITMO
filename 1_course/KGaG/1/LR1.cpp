#include <iostream>
#include <fstream>

using namespace std;

struct head{
	char p;
	short i56;
	int height;
	int width;
	short rast;
	~head(){
		p = 0;
		i56 = 0;
		height = 0;
		width = 0;
		rast = 0;
	}
};

enum lol{
	invert,
	vert,
	goriz,
	pov90,
	pov_90
};

head readhead(FILE* fin){
	head rar;
	fscanf(fin, "%c%d%d%d%d", &rar.p, &rar.i56, &rar.width, &rar.height, &rar.rast);
	return rar;
}

int main(int argc, char* argv[]){
	FILE* fin = fopen(argv[1], "rb");
	if(fin == NULL){
		cout << "ERROR1" << endl;
		return 1;
	}
	head my = readhead(fin);
	if(my.i56 != 5 && my.i56 != 6){
		cout << "ERROR2" << endl;
		return 2;
	}
	int k;
	if(my.i56 == 5){
		k = 1;
	}else{
		k = 3;
	}
	char c;
	fread(&c, 1, 1, fin);
	char** mas = new char* [my.height];
	for(int i = 0; i < my.height; i++){
		mas[i] = new char [my.width * k];
	}
	for(int i = 0; i < my.height; i++){
		for(int j = 0; j < my.width * k; j++){
			fread(&mas[i][j], 1, 1, fin);
		}
	}
	if(feof(fin) != 0){
		printf("ERROR3");
		return 3;
	}
	
	FILE* fout = fopen(argv[2], "wb");
	if(fout == NULL){
		cout << "ERROR4" << endl;
		return 4;
	}
	int num = atoi(argv[3]);
	switch(num){
		case (invert):{
			fprintf(fout, "%c%d\n%d %d\n%d\n", my.p, my.i56, my.width, my.height, my.rast);
			for(int i = 0; i < my.height; i++){
				for(int j = 0; j < my.width * k; j++){
					fprintf(fout, "%c", (char)(my.rast - (int)mas[i][j]));
				}
			}
			break;
		}
		case (vert):{
			fprintf(fout, "%c%d\n%d %d\n%d\n", my.p, my.i56, my.width, my.height, my.rast);
			for(int i = my.height - 1; i >= 0; i--){
				for(int j = 0; j < my.width * k; j++){
					fprintf(fout, "%c", mas[i][j]);
				}
			}
			break;
		}
		case (goriz):{
			fprintf(fout, "%c%d\n%d %d\n%d\n", my.p, my.i56, my.width, my.height, my.rast);
			for(int i = 0; i < my.height; i++){
				for(int j = my.width * k - 1; j >= 0 ; j -= k){
					for(int l = 0; l < k; l++){
						fprintf(fout, "%c", mas[i][j - k + l + 1]);
					}
				}
			}
			break;
		}
		case (pov90):{
			fprintf(fout, "%c%d\n%d %d\n%d\n", my.p, my.i56, my.height, my.width, my.rast);
			for(int j = 0; j < my.width * k; j += k){
				for(int i = my.height - 1; i >= 0; i--){
					for(int l = 0; l < k; l++){
						fprintf(fout, "%c", mas[i][j + l]);
					}
				}
			}
			break;
		}
		case (pov_90):{
			fprintf(fout, "%c%d\n%d %d\n%d\n", my.p, my.i56, my.height, my.width, my.rast);
			for(int j = my.width * k - 1; j >= 0; j -= k){
				for(int i = 0; i < my.height; i++){
					for(int l = 0; l < k; l++){
						fprintf(fout, "%c", mas[i][j - k + l + 1]);
					}
				}
			}
			break;
		}
		default:{
			printf("ERROR5");
			return 5;
		}
	}
	my.~head();
	delete(mas);
	cout << "FINISH" << endl;
	return 0;
}
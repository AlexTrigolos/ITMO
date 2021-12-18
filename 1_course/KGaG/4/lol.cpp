#include <iostream>

using namespace std;

int main(){
	FILE* fin = fopen("vay.pnm", "rb");
	char p, c;
	int i5, width, height, rast;
	fscanf(fin, "%c%d%d%d%d", &p, &i5, &width, &height, &rast);
	unsigned char** mas = new unsigned char* [height];
	for(int i = 0; i < height; i++){
		mas[i] = new unsigned char [3 * width];
	}
	fread(&c, 1, 1, fin);
	for(int i = 0; i < height; i++){
		for(int j = 0; j < 3 * width; j++){
			fread(&mas[i][j], 1, 1, fin);
		}
	}
	fclose(fin);
	FILE* fout = fopen("vay_1.pnm", "wb");
	fprintf(fout, "%c5\n%d %d\n%d\n", p, width, height, rast);
	for(int i = 0; i < height; i++){
		for(int j = 0; j < 3 * width; j += 3){
			fprintf(fout, "%c", mas[i][j]);
		}
	}
	fclose(fout);
	FILE* fout1 = fopen("vay_2.pnm", "wb");
	fprintf(fout1, "%c5\n%d %d\n%d\n", p, width, height, rast);
	for(int i = 0; i < height; i++){
		for(int j = 1; j < 3 * width; j += 3){
			fprintf(fout1, "%c", mas[i][j]);
		}
	}
	fclose(fout1);
	FILE* fout2 = fopen("vay_3.pnm", "wb");
	fprintf(fout2, "%c5\n%d %d\n%d\n", p, width, height, rast);
	for(int i = 0; i < height; i++){
		for(int j = 2; j < 3 * width; j += 3){
			fprintf(fout2, "%c", mas[i][j]);
		}
	}
	fclose(fout2);
	return 0;
}
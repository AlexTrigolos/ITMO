#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int gam(double point, float gamma, int rast){
	if(gamma == 0){
		if(point / rast <= 0.0031308){
			return round(12.92 * point);
		}else{
			return round((1.055 * pow(point / rast, 1.0 / 2.4) - 0.055) * rast);
		}
	}else{
		return (int)(pow((point / rast), 1 / gamma) * rast);
	}
}

int print(int point, int bit, int rast){
	int min = 1000, i = 1, u = 0, res, dob = (int)(rast / (pow(2, bit) - 1));
	for(; i <= pow(2, bit) ; i++){
		if(min > abs(u - point)){
			min = abs(u - point);
			res = u;
		}
		u += dob;
		if(u > rast){
			u = rast;
		}
	}
	return res;
}

int check(int c,int rast){
	if(c > rast){
		c = rast;
	}else if(c < 0){
		c = 0;
	}
	return c;
}

int find(int point, int bit, int rast){
	int min = 1000, i = 1, u = 0, raz, dob = (int)(rast / (pow(2, bit) - 1));
	for(; i <= pow(2, bit) ; i++){
		if(min > abs(u - point)){
			min = abs(u - point);
			raz = point - u;
		}
		u += dob;
		if(u > rast){
			u = rast;
		}
	}
	return raz;
}

enum lol{
	Without,
	Ordered8x8,
	Random,
	Floyd_Steinberg,
	Jarvis_Judice_Ninke,
	Sierra_3,
	Atkinson,
	Halftone4x4
};

int find7(int point){
	return point % 2;
}

int main(int argc, char** argv){
	char c;
	char* input = argv[1];
	char* output = argv[2];
	int grad = atoi(argv[3]);
	int dizer = atoi(argv[4]);
	int bit = atoi(argv[5]);
	float gamma = atof(argv[6]);
	FILE* fin = fopen(input, "rb");
	FILE* fout = fopen(output, "wb");
	if(fin == NULL){
		cerr << "ERROR input\n";
		return 1;
	}else if(fout == NULL){
		cerr << "ERROR output\n";
		return 1;
	}else if(grad != 0 && grad != 1){
		cerr << "ERROR grad\n";
		return 1;
	}else if(dizer < 0 || dizer > 7){
		cerr << "ERROR dizer\n";
		return 1;
	}else if(bit < 1 || bit > 8){
		cerr << "ERROR bit\n";
		return 1;
	}else if(gamma < 0){
		cerr << "ERROR gamma\n";
		return 1;
	}
	char p;
	int i5, width, height, rast;
	fscanf(fin, "%c%d%d%d%d", &p, &i5, &width, &height, &rast);
	unsigned char** mas = new unsigned char* [height];
	for(int i = 0; i < height; i++){
		mas[i] = new unsigned char [width];
	}
	if(grad == 0){
		fread(&c, 1, 1, fin);
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				fread(&mas[i][j], 1, 1, fin);
			}
		}
	}else{
		float k = 255.0 / width;
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				if(j * k <= 255){
					mas[i][j] = (int)(j * k);
				}else{
					mas[i][j] = 255;
				}
			}
		}
	}
	int raz;
	switch(dizer){
		case(Ordered8x8):{
			int** Arr = new int* [8];
			for(int i = 0; i < 8; i++){
				Arr[i] = new int [8];
			}
			Arr[0][0] = 0; Arr[0][1] = 192;  Arr[0][2] = 48; Arr[0][3] = 240; Arr[0][4] = 12; Arr[0][5] = 204; Arr[0][6] = 60; Arr[0][7] = 252;
			Arr[1][0] = 128; Arr[1][1] = 64;  Arr[1][2] = 176; Arr[1][3] = 112; Arr[1][4] = 140; Arr[1][5] = 76; Arr[1][6] = 188; Arr[1][7] = 124;
			Arr[2][0] = 32; Arr[2][1] = 224;  Arr[2][2] = 16; Arr[2][3] = 208; Arr[2][4] = 44; Arr[2][5] = 236; Arr[2][6] = 28; Arr[2][7] = 220;
			Arr[3][0] = 160; Arr[3][1] = 96;  Arr[3][2] = 144; Arr[3][3] = 80; Arr[3][4] = 172; Arr[3][5] = 108; Arr[3][6] = 156; Arr[3][7] = 92;
			Arr[4][0] = 8; Arr[4][1] = 200;  Arr[4][2] = 56; Arr[4][3] = 248; Arr[4][4] = 4; Arr[4][5] = 196; Arr[4][6] = 52; Arr[4][7] = 244;
			Arr[5][0] = 136; Arr[5][1] = 72;  Arr[5][2] = 184; Arr[5][3] = 120; Arr[5][4] = 132; Arr[5][5] = 68; Arr[5][6] = 180; Arr[5][7] = 116;
			Arr[6][0] = 40; Arr[6][1] = 232;  Arr[6][2] = 24; Arr[6][3] = 216; Arr[6][4] = 36; Arr[6][5] = 228; Arr[6][6] = 20; Arr[6][7] = 212;
			Arr[7][0] = 168; Arr[7][1] = 104;  Arr[7][2] = 152; Arr[7][3] = 88; Arr[7][4] = 164; Arr[7][5] = 100; Arr[7][6] = 148; Arr[7][7] = 84;
			for(int i = 0; i < height; i += 8){
				for(int j = 0; j < width; j += 8){
					for(int k = 0; k < 8; k++){
						for(int l = 0; l < 8; l++){
							if(i + k < height && j + l < width){
								if(mas[i + k][j + l] < Arr[k][l]){
									mas[i + k][j + l] = 0;
								}else{
									mas[i + k][j + l] = rast;
								}
							}
						}
					}
				}
			}
			delete(Arr);
			break;
		}
		case(Random):{
			int random = 0;
			for(int i = 0; i < height; i++){
				for(int j = 0; j < width; j++){
					int a = rand() % rast;
					if(mas[i][j] < random){
						mas[i][j] = 0;
					}else{
						mas[i][j] = rast;
					}
				}
			}
			break;
		}
		case(Floyd_Steinberg):{
			for(int i = 0; i < height; i++){
				if(bit == 8){
					break;
				}
				for(int j = 0; j < width; j++){
					if(bit < 7){
						raz = find(gam((double)mas[i][j], gamma, rast), bit, rast);
					}else if(bit == 7){
						raz = find7(gam((double)mas[i][j], gamma, rast));
					}
					if(j < width - 1){
						mas[i][j + 1] += check(raz / 16 * 7, rast);
					}
					if(i < height - 1){
						mas[i + 1][j] += check(raz / 16 * 5, rast);
					}
					if(i < height - 1 && j < width - 1){
						mas[i + 1][j + 1] += check(raz / 16 * 1, rast);
					}
					if(i < height - 1 && j > 0){
						mas[i + 1][j - 1] += check(raz / 16 * 3, rast);
					}
				}
			}
			break;
		}
		case(Jarvis_Judice_Ninke):{
			for(int i = 0; i < height; i++){
				if(bit == 8){
					break;
				}
				for(int j = 0; j < width; j++){
					if(bit < 7){
						raz = find(gam((double)mas[i][j], gamma, rast), bit, rast);
					}else if(bit == 7){
						raz = find7(gam((double)mas[i][j], gamma, rast));
					}
					if(j < width - 1){
						mas[i][j + 1] += check(raz / 48 * 7, rast);
					}
					if(i < height - 1){
						mas[i + 1][j] += check(raz / 48 * 7, rast);
					}
					if(i < height - 1 && j < width - 1){
						mas[i + 1][j + 1] += check(raz / 48 * 5, rast);
					}
					if(i < height - 1 && j > 0){
						mas[i + 1][j - 1] += check(raz / 48 * 5, rast);
					}
					if(j < width - 2){
						mas[i][j + 1] += check(raz / 48 * 5, rast);
					}
					if(i < height - 2){
						mas[i + 1][j] += check(raz / 48 * 5, rast);
					}
					if(i < height - 1 && j < width - 2){
						mas[i + 1][j + 1] += check(raz / 48 * 3, rast);
					}
					if(i < height - 1 && j > 1){
						mas[i + 1][j - 1] += check(raz / 48 * 3, rast);
					}
					if(i < height - 2 && j < width - 1){
						mas[i + 1][j + 1] += check(raz / 48 * 3, rast);
					}
					if(i < height - 2 && j > 0){
						mas[i + 1][j - 1] += check(raz / 48 * 3, rast);
					}
					if(i < height - 2 && j < width - 2){
						mas[i + 1][j + 1] += check(raz / 48 * 1, rast);
					}
					if(i < height - 2 && j > 1){
						mas[i + 1][j - 1] += check(raz / 48 * 1, rast);
					}
				}
			}
			break;
		}
		case(Sierra_3):{
			for(int i = 0; i < height; i++){
				if(bit == 8){
					break;
				}
				for(int j = 0; j < width; j++){
					if(bit < 7){
						raz = find(gam((double)mas[i][j], gamma, rast), bit, rast);
					}else if(bit == 7){
						raz = find7(gam((double)mas[i][j], gamma, rast));
					}
					if(j < width - 1){
						mas[i][j + 1] += check(raz / 32 * 5, rast);
					}
					if(i < height - 1){
						mas[i + 1][j] += check(raz / 32 * 5, rast);
					}
					if(i < height - 1 && j < width - 1){
						mas[i + 1][j + 1] += check(raz / 32 * 4, rast);
					}
					if(i < height - 1 && j > 0){
						mas[i + 1][j - 1] += check(raz / 32 * 4, rast);
					}
					if(j < width - 2){
						mas[i][j + 1] += check(raz / 32 * 3, rast);
					}
					if(i < height - 2){
						mas[i + 1][j] += check(raz / 32 * 3, rast);
					}
					if(i < height - 1 && j < width - 2){
						mas[i + 1][j + 1] += check(raz / 32 * 2, rast);
					}
					if(i < height - 1 && j > 1){
						mas[i + 1][j - 1] += check(raz / 32 * 2, rast);
					}
					if(i < height - 2 && j < width - 1){
						mas[i + 1][j + 1] += check(raz / 32 * 2, rast);
					}
					if(i < height - 2 && j > 0){
						mas[i + 1][j - 1] += check(raz / 32 * 2, rast);
					}
				}
			}
			break;
		}
		case(Atkinson):{
			for(int i = 0; i < height; i++){
				if(bit == 8){
					break;
				}
				for(int j = 0; j < width; j++){
					if(bit < 7){
						raz = find(gam((double)mas[i][j], gamma, rast), bit, rast);
					}else if(bit == 7){
						raz = find7(gam((double)mas[i][j], gamma, rast));
					}
					if(j < width - 1){
						mas[i][j + 1] += check(raz / 8 * 1, rast);
					}
					if(i < height - 1){
						mas[i + 1][j] += check(raz / 8 * 1, rast);
					}
					if(i < height - 1 && j < width - 1){
						mas[i + 1][j + 1] += check(raz / 8 * 1, rast);
					}
					if(i < height - 1 && j > 0){
						mas[i + 1][j - 1] += check(raz / 8 * 1, rast);
					}
					if(j < width - 2){
						mas[i][j + 1] += check(raz / 8 * 1, rast);
					}
					if(i < height - 2){
						mas[i + 1][j] += check(raz / 8 * 1, rast);
					}
				}
			}
			break;
		}
		case(Halftone4x4):{
			int** Arr = new int* [4];
			for(int i = 0; i < 4; i++){
				Arr[i] = new int [4];
			}
			Arr[0][0] = 48; Arr[0][1] = 80;  Arr[0][2] = 128; Arr[0][3] = 0;
			Arr[1][0] = 112; Arr[1][1] = 240;  Arr[1][2] = 192; Arr[1][3] = 160;
			Arr[2][0] = 176; Arr[2][1] = 208;  Arr[2][2] = 224; Arr[2][3] = 96;
			Arr[3][0] = 16; Arr[3][1] = 144;  Arr[3][2] = 64; Arr[3][3] = 32;
			
			for(int i = 0; i < height; i += 4){
				for(int j = 0; j < width; j += 4){
					for(int k = 0; k < 4; k++){
						for(int l = 0; l < 4; l++){
							if(i + k < height && j + l < width){
								if(mas[i + k][j + l] < Arr[k][l]){
									mas[i + k][j + l] = 0;
								}else{
									mas[i + k][j + l] = rast;
								}
							}
						}
					}
				}
			}
			delete(Arr);
			break;
		}
	}
	fprintf(fout, "%c%d\n%d %d\n%d\n", p, i5, width, height, rast);
	if(dizer == 0){
		bit = 8;
	}
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			if(bit < 7){
				fprintf(fout, "%c", print(mas[i][j], bit, rast));
			}else if(bit == 7){
				fprintf(fout, "%c", mas[i][j] - mas[i][j] % 2);
			}else{
				fprintf(fout, "%c", mas[i][j]);
			}
		}
	}
	delete(mas);
	return 0;
	fclose(fin);
	fclose(fout);
}
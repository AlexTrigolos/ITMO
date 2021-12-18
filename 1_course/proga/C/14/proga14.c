#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma pack(1)
#include <direct.h>

struct bmp{
	unsigned short bm;
	unsigned int sizefile;
	unsigned short rez;
	unsigned short rez2;
	unsigned int sizetoimg;
};

struct ti{
	unsigned int sizestrct;
	int width;
	int height;
	unsigned short ed;
	unsigned short bitpxl;
	unsigned int sjatie;
	unsigned int sizeimg;
	int gor;
	int ver;
	unsigned int indxpal;
	unsigned int needpal;
};

void print(struct bmp input, struct ti rtp, char* ch, short** Pole, int height, int width, int ijn, int padding, char* argv, int q){
	char file[100];
	char* dop = "\\";
	char* C = "c:";
	char* gen = "gen";
	char num[10];
	itoa(q, num, 10);
	char* bm = ".bmp";
	snprintf(file, sizeof(file), "%s%s%s%s%s%s%s", C, dop, argv, dop, gen, num, bm);
	FILE* end = fopen(file,"wb");
	input.sizefile = abs(height) * abs(width + padding * 8) / 8 + sizeof(input) + ijn + sizeof(rtp);
	fwrite(&input, sizeof(input), 1, end);
	int i, j, k, c;
	rtp.width = width;
	fwrite(&rtp, sizeof(rtp), 1, end);
	for(i = 0; i < ijn; i++){
		fwrite(&ch[i], 1, 1, end);
	}
	for(i = height - 1; i >= 0; i--){
		for(j = 0; j < width; j += 8){
			for(int m = 0; m < 8; m++){
			}
			c = Pole[i][j] * 128 + Pole[i][j + 1] * 64 + Pole[i][j + 2] * 32 + Pole[i][j + 3] * 16 + Pole[i][j + 4] * 8 + Pole[i][j + 5] * 4 + Pole[i][j + 6] * 2 + Pole[i][j + 7];
			fwrite(&c, 1, 1, end);
		}
		if(padding != 0){
			c = 0;
			for(k = 0; k < padding; k++){
				fwrite(&c, 1, 1, end);
			}
		}
	}
	fclose(end);
}

int check(short** Pole, int width, int height, short*** All, int k){
	int index = 0;
	int flag = 0;
	while(index < k){
		for(int i = 0; i < height; i++){
			for(int j = 0; j <= width; j++){
				if(All[index][i][j] != Pole[i][j]){
					flag = 1;
					break;
				}
			}
			if(flag == 1){
				break;
			}
		}
		if(flag == 0){
			return 0;
		}
		index++;
		flag = 0;
	}
	return 1;
}

void game(short** Pole, int width, int height, int N, int q, int rex, char* argv, struct bmp input, struct ti rtp, char* ch, int ijn, int padding, short*** All){
	short Arr[height][width];
	int sum, i, j, k = 1, h;
	while(k != N + 1){
		for(i = height - 1; i >= 0; i--){
			for(j = 0; j < width; j++){
				sum = 0;
				for(h = 0; h < rex; h++){
					if(j != 0 && j != width - 1 && i != height - 1 && i != 0){//середина
						if(Pole[i][j] == 1){
							sum = Pole[i + 1][j + 1] + Pole[i + 1][j] + Pole[i + 1][j - 1] + Pole[i - 1][j - 1] + Pole[i - 1][j] + Pole[i - 1][j + 1] + Pole[i][j + 1] + Pole[i][j - 1];
							if(sum == 5){
								Arr[i][j] = 0;
							}else{
								Arr[i][j] = 1;
							}
						}else if(Pole[i][j] == 0){
							sum = Pole[i + 1][j + 1] + Pole[i + 1][j] + Pole[i + 1][j - 1] + Pole[i - 1][j - 1] + Pole[i - 1][j] + Pole[i - 1][j + 1] + Pole[i][j + 1] + Pole[i][j - 1];
							if(sum == 5 || sum == 6){
								Arr[i][j] = 0;
							}else{
								Arr[i][j] = 1;
							}
						}
					}else if(j == 0 && j != width - 1 && i != height - 1 && i != 0){//левый ряд
						if(Pole[i][j] == 1){
							sum = Pole[i + 1][j + 1] + Pole[i + 1][j] + Pole[i + 1][width - 1] + Pole[i - 1][width - 1] + Pole[i - 1][j] + Pole[i - 1][j + 1] + Pole[i][j + 1] + Pole[i][width - 1];
							if(sum == 5){
								Arr[i][j] = 0;
							}else{
								Arr[i][j] = 1;
							}
						}else if(Pole[i][j] == 0){
							sum = Pole[i + 1][j + 1] + Pole[i + 1][j] + Pole[i + 1][width - 1] + Pole[i - 1][width - 1] + Pole[i - 1][j] + Pole[i - 1][j + 1] + Pole[i][j + 1] + Pole[i][width - 1];
							if(sum == 5 || sum == 6){
								Arr[i][j] = 0;
							}else{
								Arr[i][j] = 1;
							}
						}
					}else if(j != 0 && j == width - 1 && i != height - 1 && i != 0){//правый ряд
						if(Pole[i][j] == 1){
							sum = Pole[i + 1][0] + Pole[i + 1][j] + Pole[i + 1][j - 1] + Pole[i - 1][j - 1] + Pole[i - 1][j] + Pole[i - 1][0] + Pole[i][0] + Pole[i][j - 1];
							if(sum == 5){
								Arr[i][j] = 0;
							}else{
								Arr[i][j] = 1;
							}
						}else if(Pole[i][j] == 0){
							sum = Pole[i + 1][0] + Pole[i + 1][j] + Pole[i + 1][j - 1] + Pole[i - 1][j - 1] + Pole[i - 1][j] + Pole[i - 1][0] + Pole[i][0] + Pole[i][j - 1];
							if(sum == 5 || sum == 6){
								Arr[i][j] = 0;
							}else{
								Arr[i][j] = 1;
							}
						}
					}else if(j != 0 && j != width - 1 && i == height - 1 && i != 0){//верхний ряд
						if(Pole[i][j] == 1){
							sum = Pole[0][j + 1] + Pole[0][j] + Pole[0][j - 1] + Pole[i - 1][j - 1] + Pole[i - 1][j] + Pole[i - 1][j + 1] + Pole[i][j + 1] + Pole[i][j - 1];
							if(sum == 5){
								Arr[i][j] = 0;
							}else{
								Arr[i][j] = 1;
							}
						}else if(Pole[i][j] == 0){
							sum = Pole[0][j + 1] + Pole[0][j] + Pole[0][j - 1] + Pole[i - 1][j - 1] + Pole[i - 1][j] + Pole[i - 1][j + 1] + Pole[i][j + 1] + Pole[i][j - 1];
							if(sum == 5 || sum == 6){
								Arr[i][j] = 0;
							}else{
								Arr[i][j] = 1;
							}
						}
					}else if(j != 0 && j != width - 1 && i != height - 1 && i == 0){//нижний ряд
						if(Pole[i][j] == 1){
							sum = Pole[i + 1][j + 1] + Pole[i + 1][j] + Pole[i + 1][j - 1] + Pole[height - 1][j - 1] + Pole[height - 1][j] + Pole[height - 1][j + 1] + Pole[i][j + 1] + Pole[i][j - 1];
							if(sum == 5){
								Arr[i][j] = 0;
							}else{
								Arr[i][j] = 1;
							}
						}else if(Pole[i][j] == 0){
							sum = Pole[i + 1][j + 1] + Pole[i + 1][j] + Pole[i + 1][j - 1] + Pole[height - 1][j - 1] + Pole[height - 1][j] + Pole[height - 1][j + 1] + Pole[i][j + 1] + Pole[i][j - 1];
							if(sum == 5 || sum == 6){
								Arr[i][j] = 0;
							}else{
								Arr[i][j] = 1;
							}
						}
					}else if(j == 0 && j != width - 1 && i == height - 1 && i != 0){//левый верхний угол
						if(Pole[i][j] == 1){
							sum = Pole[0][j + 1] + Pole[0][j] + Pole[0][width - 1] + Pole[i - 1][width - 1] + Pole[i - 1][j] + Pole[i - 1][j + 1] + Pole[i][j + 1] + Pole[i][width - 1];
							if(sum == 5){
								Arr[i][j] = 0;
							}else{
								Arr[i][j] = 1;
							}
						}else if(Pole[i][j] == 0){
							sum = Pole[0][j + 1] + Pole[0][j] + Pole[0][width - 1] + Pole[i - 1][width - 1] + Pole[i - 1][j] + Pole[i - 1][j + 1] + Pole[i][j + 1] + Pole[i][width - 1];
							if(sum == 5 || sum == 6){
								Arr[i][j] = 0;
							}else{
								Arr[i][j] = 1;
							}
						}
					}else if(j == 0 && j != width - 1 && i != height - 1 && i == 0){//левый нижний угол
						if(Pole[i][j] == 1){
							sum = Pole[i + 1][j + 1] + Pole[i + 1][j] + Pole[i + 1][width - 1] + Pole[height - 1][width - 1] + Pole[height - 1][j] + Pole[height - 1][j + 1] + Pole[i][j + 1] + Pole[i][width - 1];
							if(sum == 5){
								Arr[i][j] = 0;
							}else{
								Arr[i][j] = 1;
							}
						}else if(Pole[i][j] == 0){
							sum = Pole[i + 1][j + 1] + Pole[i + 1][j] + Pole[i + 1][width - 1] + Pole[height - 1][width - 1] + Pole[height - 1][j] + Pole[height - 1][j + 1] + Pole[i][j + 1] + Pole[i][width - 1];
							if(sum == 5 || sum == 6){
								Arr[i][j] = 0;
							}else{
								Arr[i][j] = 1;
							}
						}
					}else if(j != 0 && j == width - 1 && i == height - 1 && i != 0){//правый верхний угол
						if(Pole[i][j] == 1){
							sum = Pole[0][0] + Pole[0][j] + Pole[0][j - 1] + Pole[i - 1][j - 1] + Pole[i - 1][j] + Pole[i - 1][0] + Pole[i][0] + Pole[i][j - 1];
							if(sum == 5){
								Arr[i][j] = 0;
							}else{
								Arr[i][j] = 1;
							}
						}else if(Pole[i][j] == 0){
							sum = Pole[0][0] + Pole[0][j] + Pole[0][j - 1] + Pole[i - 1][j - 1] + Pole[i - 1][j] + Pole[i - 1][0] + Pole[i][0] + Pole[i][j - 1];
							if(sum == 5 || sum == 6){
								Arr[i][j] = 0;
							}else{
								Arr[i][j] = 1;
							}
						}
					}else if(j != 0 && j == width - 1 && i != height - 1 && i == 0){//правый нижний угол
						if(Pole[i][j] == 1){
							sum = Pole[i + 1][0] + Pole[i + 1][j] + Pole[i + 1][j - 1] + Pole[height - 1][j - 1] + Pole[height - 1][j] + Pole[height - 1][0] + Pole[i][0] + Pole[i][j - 1];
							if(sum == 5){
								Arr[i][j] = 0;
							}else{
								Arr[i][j] = 1;
							}
						}else if(Pole[i][j] == 0){
							sum = Pole[i + 1][0] + Pole[i + 1][j] + Pole[i + 1][j - 1] + Pole[height - 1][j - 1] + Pole[height - 1][j] + Pole[height - 1][0] + Pole[i][0] + Pole[i][j - 1];
							if(sum == 5 || sum == 6){
								Arr[i][j] = 0;
							}else{
								Arr[i][j] = 1;
							}
						}
					}
				}
			}
		}
		printf("%d\n", k);
		for(i = height - 1; i >= 0; i--){
			for(j = 0; j < width; j++){
				Pole[i][j] = Arr[i][j];
				All[k][i][j] = Arr[i][j];
			}
		}
		if(k % q == 0){
			print(input, rtp, ch, All[k], rtp.height, rtp.width, ijn, padding, (char*)argv, k);
		}
		int stop = check(All[k], width, height, All, k);
		if(!stop){
			printf("repeat");
			break;
		}
		k++;
	}
	printf(":0");
}

void readik(FILE* start, int N, int q, char* argv){
	int i, j, k;
	struct bmp input;
	struct ti rtp;
	fread(&input, sizeof(input), 1, start);
	fread(&rtp, sizeof(rtp), 1, start);
	int c = 0;
	int ijn = input.sizetoimg - 14 - rtp.sizestrct;
	char* ch = (char*)malloc(ijn);
	for(i = 0; i < ijn; i++){
		fread(&ch[i], 1, 1, start);
	}
	int padding = 0;
	int changewidth = rtp.width;
	while(rtp.width % 8 != 0){
		rtp.width++;
	}
	if(rtp.width % 32 != 0){
		padding = 4 - (rtp.width % 32) / 8;
	}
	int rex = rtp.width / 32;
	short **Pole = (short **) malloc(sizeof(short *) * rtp.height);
    for (int i = 0; i < rtp.height; i++) {
        Pole[i] = (short *) malloc(sizeof(short) * rtp.width);
    }
	for(i = abs(rtp.height) - 1; i >= 0; i--){
		for(j = 0; j < abs(rtp.width); j += 8){
			fread(&c, 1, 1, start);
			for(k = 7; k >= 0; k--){
				if(j - k + 7 < changewidth){
					Pole[i][j - k + 7] = c / (int)pow(2, k);
					c %= (int)pow(2, k);
				}else{
					Pole[i][j - k + 7] = 1;
				}
			}
		}
		if(padding != 0){
			for(k = 0; k < padding; k++){
				fread(&c, 1, 1, start);
			}
		}
	}
	short ***All = (short ***) malloc(sizeof(short **) * N);
	for(int i = 0; i < N+1; i++){
		All[i] = (short **) malloc(sizeof(short *) * rtp.height);
		for (int j = 0; j < rtp.height; j++){
			All[i][j] = (short *) malloc(sizeof(short) * rtp.width);
		}
	}
	All[0] = Pole;
	print(input, rtp, ch, Pole, rtp.height, rtp.width, ijn, padding, (char*)argv, 0);
	game(Pole, rtp.width, rtp.height, N, q, rex, (char*)argv, input, rtp, ch, ijn, padding, All);
}

int main(int argc, char** argv){
	char dir_name[1000];
	char* dop = "\\";
	int N = 2500;
	int q = 1;
	if(strcmp(argv[1], "--input") == 0){
		if(strcmp(argv[3], "--output") == 0){
			snprintf(dir_name, sizeof(dir_name), "%s%s", dop, argv[4]);
		}else{
			printf("ERROR - output");
			return 2;
		}
		if(strcmp(argv[5], "--max_iter") == 0){
			if(atoi(argv[6]) == 0){
				printf("MISTAKE - infinity program(max_iter = 0)\n");
			}else{
				N = atoi(argv[6]);
				if(strcmp(argv[7], "--dump_freq") == 0){
					q = atoi(argv[8]);
				}else{
					printf("CONST ");
				}
			}
		}else{
			printf("MISTAKE - infinity program(haven't max_iter)\n");
			if(strcmp(argv[7], "--dump_freq") == 0){
				q = atoi(argv[8]);
			}else{
				printf("CONST ");
			}
		}
		char* d = argv[4];
		printf("FREQ = %d\n", q);
		int result = mkdir(dir_name);
		FILE* first = fopen(argv[2], "rb");
		fseek(first, 0, SEEK_SET);
		readik(first, N, q, d);
		fclose(first);
	}else{
		printf("ERROR - input");
		return 1;
	}
	
	
	return 0;
}
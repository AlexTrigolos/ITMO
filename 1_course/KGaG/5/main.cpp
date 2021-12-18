#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

void YCbCr6(unsigned char** mas, int height, int width, int o){
	if(o == 0){
		float R, G, B, Y, Cb, Cr;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j +=3) {
				R = (float)mas[i][j] / 255.0;
				G = (float)mas[i][j + 1] / 255.0;
				B = (float)mas[i][j + 2] / 255.0;

				Y = 16 + (65.481 * R + 128.533 * G + 24.966 * B);
				Cb = 128 + (-37.797 * R - 74.203 * G + 112.0 * B);
				Cr = 128 + (112.0 * R - 93.786 * G - 18.214 * B);

				mas[i][j] = Y;
				mas[i][j + 1] = Cb;
				mas[i][j + 2] = Cr;
			}
		}
	}else{
		float R, G, B, Y, Cb, Cr;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j += 3){
				Y = (float)mas[i][j];
				Cb = (float)mas[i][j + 1];
				Cr = (float)mas[i][j + 2];

				R = 1.164*(Y - 16) + 1.596*(Cr - 128);
				G = 1.164*(Y - 16) - 0.813*(Cr - 128) - 0.392*(Cb - 128);
				B = 1.164*(Y - 16) + 2.017*(Cb - 128);

				if (R > 255) R = 255;
				if (G > 255) G = 255;
				if (B > 255) B = 255;
				
				if (R < 0) R = 0;
				if (G < 0) G = 0;
				if (B < 0) B = 0;

				mas[i][j] = R;
				mas[i][j + 1] = G;
				mas[i][j + 2] = B;
			}
		}
	}
}

void func(unsigned char** mas, const int offset, const double multiplier, int height, int width){
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			int y = mas[i][j];
			y = (y - offset) * multiplier;
			if(y < 0){
				y = 0;
			}else if(y > 255){
				y = 255;
			}
			mas[i][j] = y;
		}
	}
}

void func2(unsigned char** mas, const int offset, const double multiplier, int height, int width){
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j += 3){
			int y = mas[i][j];
			y = (y - offset) * multiplier;
			if(y < 0){
				y = 0;
			}else if(y > 255){
				y = 255;
			}
			mas[i][j] = y;
		}
	}
}

int main(int argc, char* argv[]){
	char p, c;
	int	i56, width, height, rast;
	int i, j, k = 1, _min = 256, _max = -1;
	char* input;
	char* output;
	int action;
	int offset = 0;
	double multiplier = 0;
	input = argv[1];
	output = argv[2];
	action = argv[3][0] - 48;
	if(action == 0 || action == 1){
		for(int i = 0; i < strlen(argv[4]); i++){
			if(argv[4][0] == '-' && i > 0){
				offset = 10 * offset - argv[4][i] + 48;
			}else if(argv[4][0] != '-'){
				offset = 10 * offset + argv[4][i] - 48;
			}
		}
		bool flag = false;
		j = 1;
		for(int i = 0; i < strlen(argv[5]); i++){
			if(argv[5][i] != '.'){
				if(flag == false){
					multiplier = 10 * multiplier + argv[5][i] - 48;
				}else{
					multiplier = multiplier + (argv[5][i] - 48) * pow(10, -j);
					j++;
				}
			}else if(argv[5][i] == '.'){
				if(flag == false){
					flag = true;
				}else{
					cerr << "ERROR multiplier.\n";
					return 1;
				}
			}
		}
	}
	//cout << input << " " << output << " " << action << " " << offset << " " << multiplier << "\n";
	FILE* fin = fopen(input, "rb");
	if(fin == NULL){
		cerr << "ERROR fail.";
		return 1;
	}
	fscanf(fin, "%c%d%d%d%d", &p, &i56, &width, &height, &rast);
	if(i56 == 5){
		k = 1;
	}else if(i56 == 6){
		k = 3;
	}else{
		cerr << "ERROR i56.\n";
	}
	if(p != 'P'){
		cerr << "ERROR P.\n";
	}
	fread(&c, 1, 1, fin);
	int pot[256] = {0};
	float prots;
	if(action == 4){
		prots = 3 * width * height / 100 * 0.39;
	}else if(action == 5){
		prots = width * height / 100 * 0.39;
	}
	unsigned char** mas = (unsigned char**)malloc(height * sizeof(unsigned char*));
	for(i = 0; i < height; i++){
		mas[i] = (unsigned char*)malloc(width * k * sizeof(unsigned char));
		for(j = 0; j < k * width; j++){
			fread(&mas[i][j], 1, 1, fin);
			if(action == 2){
				if(mas[i][j] < _min){
					_min = mas[i][j];
				}
				if(mas[i][j] > _max){
					_max = mas[i][j];
				}
			}else if(action == 3 && j % 3 == 0){
				if(mas[i][j] < _min){
					_min = mas[i][j];
				}
				if(mas[i][j] > _max){
					_max = mas[i][j];
				}
			}else if(action == 4){
				pot[mas[i][j]] += 1;
			}else if(action == 5 && j % 3 == 0){
				pot[mas[i][j]] += 1;
			}
		}
	}
	int sum = 0;
	if(action == 4){
		for(i = 0; i < 256; i++){
			if(sum + pot[i] >= prots){
				_max = i;
			}else{
				sum += pot[i];
			}
		}
		sum = 0;
		for(i = 255; i >= 0; i--){
			if(sum + pot[i] >= prots){
				_min = i;
			}else{
				sum += pot[i];
			}
		}
	}else if(action == 5){
		for(i = 0; i < 256; i++){
			if(sum + pot[i] >= prots){
				_max = i;
			}else{
				sum += pot[i];
			}
		}
		sum = 0;
		for(i = 255; i >= 0; i--){
			if(sum + pot[i] >= prots){
				_min = i;
			}else{
				sum += pot[i];
			}
		}
	}
	fclose(fin);
	switch(action){
		case 0:
			func(mas, offset, multiplier, height, k * width);
			break;
		case 1:
			if(i56 == 6){
				func2(mas, offset, multiplier, height, k * width);
				YCbCr6(mas, height, k * width, 1);
			}else{
				cerr << "ERROR it's not YCbCr.\n";
				return 1;
			}
			break;
		case 2:
			func(mas, _min, 255/(_max - _min), height, k * width);
			break;
		case 3:
			if(i56 == 6){
				func2(mas, _min, 255/(_max - _min), height, k * width);
				YCbCr6(mas, height, k * width, 1);
			}else{
				cerr << "ERROR it's not YCbCr.\n";
				return 1;
			}
			break;
		case 4:
			func(mas, _min, 255/(_max - _min), height, k * width);
			break;
		case 5:
			if(i56 == 6){
				func2(mas, _min, 255/(_max - _min), height, k * width);
				YCbCr6(mas, height, k * width, 1);
			}else{
				cerr << "ERROR it's not YCbCr.\n";
				return 1;
			}
			break;
	}
	FILE* fout = fopen(output, "wb");
	if(fout == NULL){
		cerr << "ERROR outfail.";
		return 1;
	}
	fprintf(fout, "%c%d\n%d %d\n%d\n", p, i56, width, height, rast);
	for(i = 0; i < height; i++){
		for(j = 0; j < k * width; j++){
			fprintf(fout, "%c", mas[i][j]);
		}
	}
	fclose(fout);
	delete(mas);
	return 0;
}
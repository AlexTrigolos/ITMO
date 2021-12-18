#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

void CMY(unsigned char** mas, int height, int width){
	for(int i = 0; i < height; i++){
		for(int j = 0; j < 3 * width; j += 3){
			mas[i][j] = 255 - mas[i][j];
			mas[i][j + 1] = 255 - mas[i][j + 1];
			mas[i][j + 2] = 255 - mas[i][j + 2];
		}
	}
}

void HSV(unsigned char** mas, int height, int width, int o){
	if(o == 0){
		int R, G, B, minimum, maximum;
		unsigned char H, S, V;
		for(int i = 0; i < height; i++){
			for(int j = 0; j < 3 * width; j += 3){
				R = mas[i][j];
				G = mas[i][j + 1];
				B = mas[i][j + 2];
				minimum = fmin(fmin(R, G), B);
				maximum = fmax(fmax(R, G), B);
				if(maximum == minimum){
					H = 0;
				}else if(maximum == R && G >= B){
					H = ((60.0 * (float)(G - B) / ((float)maximum - (float)minimum)) / 360.0) * 255.0;
				}else if(maximum == R && G < B){
					H = ((60.0 * (float)(G - B) / ((float)maximum - (float)minimum) + 360.0) / 360.0) * 255.0;
				}else if(maximum == G){
					H = ((60.0 * (float)(B - R) / ((float)maximum - (float)minimum) + 120.0) / 360.0) * 255.0;
				}else if(maximum == B){
					H = ((60.0 * (float)(R - G) / ((float)maximum - (float)minimum) + 240.0) / 360.0) * 255.0;
				}
				if(maximum == 0){
					S = 0;
				}else{
					S = (1.0 - (float)minimum/(float)maximum)*255;
				}
				V = maximum;
				mas[i][j] = H;
				mas[i][j + 1] = S;
				mas[i][j + 2] = V;
			}
		}
	}else{
		float H, S, V;
		int hi, vmin, a, vinc, vdec;
		for(int i = 0; i < height; i++){
			for(int j = 0; j < 3 * width; j += 3){
				H = ((float)mas[i][j] / 255.0) * 360.0;
				S = ((float)mas[i][j] / 255.0) * 100.0;
				V = ((float)mas[i][j] / 255.0) * 100.0;
				hi = (int)floor(H/60.0) % 6;
				vmin = ((100.0 - S) * V) / 100.0;
				a = (V - vmin)*((float)((int)H % 60)/60.0);
				vinc = vmin + a;
				vdec = V - a;
				V = (V * 255.0) / 100.0;
				vinc = ((float)vinc * 255.0) / 100.0;
				vdec = ((float)vdec * 255.0) / 100.0;
				vmin = ((float)vmin * 255.0) / 100.0;
				if(hi == 0){
					mas[i][j] = V;
					mas[i][j + 1] = vinc;
					mas[i][j + 2] = vmin; 
				}else if(hi == 1){
					mas[i][j] = vdec;
					mas[i][j + 1] = V;
					mas[i][j + 2] = vmin;
				}else if(hi == 2){
					mas[i][j] = vmin;
					mas[i][j + 1] = V;
					mas[i][j + 2] = vinc;
				}else if(hi == 3){
					mas[i][j] = vmin;
					mas[i][j + 1] = vdec;
					mas[i][j + 2] = V;
				}else if(hi == 4){
					mas[i][j] = vinc;
					mas[i][j + 1] = vmin;
					mas[i][j + 2] = V;
				}else if(hi == 5){
					mas[i][j] = V;
					mas[i][j + 1] = vmin;
					mas[i][j + 2] = vdec;
				}
			}
		}
	}
}

void HSLV(unsigned char** mas, int height, int width, int o){
	if(o == 0){
		for(int i = 0; i < height; i++){
			for(int j = 0; j < 3 * width; j += 3){
				float Sv = mas[i][j + 1] / 255.0;
				float V = mas[i][j + 2] / 255.0;
				float L = V * (1 - Sv / 2);
				float Sl;
				if(L == 0 || L == 1){
					Sl = 0;
				}else{
					Sl = (V - L) / min(L, 1 - L);
				}
				mas[i][j + 1] = L * 255;
				mas[i][j + 2] = Sl * 255;
			}
		}
	}else{
		for(int i = 0; i < height; i++){
			for(int j = 0; j < 3 * width; j += 3){
				float Sl = mas[i][j + 1] / 255.0;
				float L = mas[i][j + 2] / 255.0;
				float V = L + Sl * min(L, 1 - L);
				float Sv;
				if(V == 0){
					Sv = 0;
				}else{
					Sv = 2 * (1 - L / V);
				}
				mas[i][j + 1] = L * 255;
				mas[i][j + 2] = Sl * 255;
			}
		}
	}
}

void HSL(unsigned char** mas, int h, int w, int o){
	if(o == 0){
		int R_n, G_n, B_n, C_max, C_min, dC;
		unsigned char H, S, L;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j += 3) {
				R_n = (*(*(mas + i) + j));
				G_n = (*(*(mas + i) + j + 1));
				B_n = (*(*(mas + i) + j + 2));
				C_min = fmin(fmin(R_n, G_n), B_n);
				C_max = fmax(fmax(R_n, G_n), B_n);
				dC = C_max - C_min;

				if (dC == 0) {
					H = 0;
				} else if (C_max == R_n && G_n >= B_n) {
					H = ((60.0 * (float)(G_n - B_n)/(float)dC)/360.0) * 255.0;
				} else if (C_max == R_n && G_n < B_n) {
					H = ((60.0 * (float)(G_n - B_n)/(float)dC + 360.0)/360.0) * 255.0;
				} else if (C_max == G_n) {
					H = ((60.0 * (float)(B_n - R_n)/(float)dC + 120.0)/360.0) * 255.0;
				} else if (C_max == B_n) {
					H = ((60.0 * (float)(R_n - G_n)/(float)dC + 240.0)/360.0) * 255.0;
				}

				S = 255.0*(((float)C_max/255.0 - (float)C_min/255.0)/(1 - fabs(1 - ((float)C_max/255.0 + (float)C_min/255.0))));

				L = 0.5*(C_max + C_min);

				*(*(mas + i) + j) = H;
				*(*(mas + i) + j + 1) = S;
				*(*(mas + i) + j + 2) = L;
				
			}
		}
	}else{
		float Q, P, Hi, L, T_R, T_G, T_B, H, S, R, G, B;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j += 3) {
				Hi = (float)(*(*(mas + i) + j)) / 255.0;
				S = (float)(*(*(mas + i) + j + 1)) / 255.0;
				L = (float)(*(*(mas + i) + j + 2)) / 255.0;

				if (L < 0.5) {
					Q = L * (1.0 + S);
				} else {
					Q = L + S - (L * S);
				}

				P = 2.0 * L - Q;

				T_R = Hi + 1.0/3.0;
				T_G = Hi;
				T_B = Hi - 1.0/3.0;

				if (T_R < 0) T_R += 1.0;
				if (T_G < 0) T_G += 1.0;
				if (T_B < 0) T_B += 1.0;
				
				if (T_R > 1) T_R -= 1.0;
				if (T_G > 1) T_G -= 1.0;
				if (T_B > 1) T_B -= 1.0;
				
				if (T_R < 1.0/6.0) {
					R = 255.0 * (P + ((Q - P) * 6.0 * T_R));
				} else if (T_R >= 1.0/6.0 && T_R < 0.5) {
					R = 255.0 * Q;
				} else if (T_R >= 0.5 && T_R < 2.0/3.0) {
					R = 255.0 * (P + ((Q - P) * (2.0/3.0 - T_R) * 6.0));
				} else {
					R = 255.0 * P;
				}

				if (T_G < 1.0/6.0) {
					G = 255.0 * (P + ((Q - P) * 6.0 * T_G));
				} else if (T_G >= 1.0/6.0 && T_G < 0.5) {
					G = 255.0 * Q;
				} else if (T_G >= 0.5 && T_G < 2.0/3.0) {
					G = 255.0 * (P + ((Q - P) * (2.0/3.0 - T_G) * 6.0));
				} else {
					G = 255.0 * P;
				}

				if (T_B < 1.0/6.0) {
					B = 255.0 * (P + ((Q - P) * 6.0 * T_B));
				} else if (T_B >= 1.0/6.0 && T_B < 0.5) {
					B = 255.0 * Q;
				} else if (T_B >= 0.5 && T_B < 2.0/3.0) {
					B = 255.0 * (P + ((Q - P) * (2.0/3.0 - T_B) * 6.0));
				} else {
					B = 255.0 * P;
				}

				*(*(mas + i) + j) = R;
				*(*(mas + i) + j + 1) = G;
				*(*(mas + i) + j + 2) = B;
				
			}
		}
	}
}

void YCbCr6(unsigned char** mas, int height, int width, int o){
	if(o == 0){
		float R, G, B, Y, Cb, Cr;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < 3 * width; j += 3) {
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
			for (int j = 0; j < 3 * width; j += 3) {
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

void YCbCr7(unsigned char** mas, int height, int width, int o){
	if(o == 0){
		float R, G, B, Y, Cb, Cr;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < 3 * width; j += 3) {
				R = (float)(mas[i][j]) / 255.0;
				G = (float)(mas[i][j + 1]) / 255.0;
				B = (float)(mas[i][j + 2]) / 255.0;
				Y  = 0.2126 * R + 0.7152 * G + 0.0722 * B;
				Cb = (B - Y) / 1.8556 + 0.5;
				Cr = (R - Y) / 1.5748 + 0.5;
				if (Cb > 1) Cb = 1;
				if (Cr > 1) Cr = 1;
				mas[i][j] = Y * 255.0;
				mas[i][j + 1] = Cb * 255.0;
				mas[i][j + 2] = Cr * 255.0;
			}
		}
	}else{
		float R, G, B, Y, Cb, Cr;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < 3 * width; j += 3) {
				Y = (float)(mas[i][j]) / 255.0;
				Cb = (float)(mas[i][j + 1]) / 255.0 - 0.5;
				Cr = (float)(mas[i][j + 2]) / 255.0 - 0.5;

				R = 255.0*(Y + 1.5748 * Cr);
				B = 255.0*(Y + 1.8556 * Cb);

				G = 255.0*((Y - R*0.2126/255.0 - B*0.0722/255.0)/0.7152);

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

void YCoCg(unsigned char** mas, int height, int width, int o){
	if(o == 0){
		for(int i = 0; i < height; i++){
			for(int j = 0; j < 3 * width; j +=3){
				float R = (float)mas[i][j] / 255.0;
				float G = (float)mas[i][j + 1] / 255.0;
				float B = (float)mas[i][j + 2] / 255.0;
				float Y = 0.25 * B + 0.5 * G + 0.25 * R;
				float Co = 0.5 * R - 0.5 * B + 0.5;
				float Cg = -0.25 * B + 0.5 * G - 0.25 * R + 0.5;
				if (Co > 1) Co = 1;
				if (Cg > 1) Cg = 1;
				mas[i][j] = Y * 255.0;
				mas[i][j + 1] = Co * 255.0;
				mas[i][j + 2] = Cg * 255.0;
			}
		}
	}else{
		for(int i = 0; i < height; i++){
			for(int j = 0; j < 3 * width; j += 3){
				float Y = (float)mas[i][j] / 255.0;
				float Co = (float)mas[i][j + 1] / 255.0 - 0.5;
				float Cg = (float)mas[i][j + 2] / 255.0 - 0.5;
				if (Co < 0) Co = 0;
				if (Cg < 0) Cg = 0;
				float R = 255.0 * (Y + Co - Cg);
				float G = 255.0 * (Cg + Y);
				float B = 255.0 * (Y - Co - Cg);
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

void init(unsigned char*** mas, int height, int width){
	*mas = (unsigned char**)malloc(sizeof(unsigned char*) * height);
	for(int i = 0; i < height; i++){
		*(*mas + i) = (unsigned char*)malloc(sizeof(unsigned char) * 3 * width);
	}
}

int main(int argc, char* argv[]){
	char c;
	int i, j, infile, outfile;
	char* from;
	char* to;
	char* input;
	char* output;
	for(i = 1; i <= 10; i++){
		char* ch = argv[i];
		if(ch[0] == '-' && ch[1] == 'f' && strlen(ch) == 2){
			from = argv[i + 1];
			if(strcmp(from, "RGB") != 0 && strcmp(from, "HSL") != 0 && strcmp(from, "HSV") != 0 && strcmp(from, "YCbCr.601") != 0 && strcmp(from, "YCbCr.709") != 0 && strcmp(from, "CMY") != 0 && strcmp(from, "YCoCg") != 0){
				cerr << "ERROR input color spase.";
				return 1;
			}
		}else if(ch[0] == '-' && ch[1] == 't' && strlen(ch) == 2){
			to = argv[i + 1];
			if(strcmp(to, "RGB") != 0 && strcmp(to, "HSL") != 0 && strcmp(to, "HSV") != 0 && strcmp(to, "YCbCr.601") != 0 && strcmp(to, "YCbCr.709") != 0 && strcmp(to, "CMY") != 0 && strcmp(to, "YCoCg") != 0){
				cerr << "ERROR output color spase.";
				return 1;
			}
		}else if(ch[0] == '-' && ch[1] == 'i' && strlen(ch) == 2){
			if(argv[i + 1][0] == '1'){
				infile = 1;
			}else if(argv[i + 1][0] == '3'){
				infile = 3;
			}else{
				cerr << "ERROR count in.\n";
				return 1;
			}
			input = argv[i + 2];
		}else if(ch[0] == '-' && ch[1] == 'o' && strlen(ch) == 2){
			if(argv[i + 1][0] == '1'){
				outfile = 1;
			}else if(argv[i + 1][0] == '3'){
				outfile = 3;
			}else{
				cerr << "ERROR count out.\n";
				return 1;
			}
			output = argv[i + 2];
		}
	}
	char p;
	char* one;
	char* two;
	char* three;
	one = (char*)malloc(strlen(input) + 3);
	strcpy(one, input);
	*(one + strlen(input) - 4) = '_';
	*(one + strlen(input) - 3) = '1';
	*(one + strlen(input) - 2) = '.';
	*(one + strlen(input) - 1) = 'p';
	*(one + strlen(input)) = 'g';
	*(one + strlen(input) + 1) = 'm';
	*(one + strlen(input) + 2) = '\0';
	two = (char*)malloc(strlen(input) + 3);
	strcpy(two, input);
	*(two + strlen(input) - 4) = '_';
	*(two + strlen(input) - 3) = '2';
	*(two + strlen(input) - 2) = '.';
	*(two + strlen(input) - 1) = 'p';
	*(two + strlen(input)) = 'g';
	*(two + strlen(input) + 1) = 'm';
	*(two + strlen(input) + 2) = '\0';
	three = (char*)malloc(strlen(input) + 3);
	strcpy(three, input);
	*(three + strlen(input) - 4) = '_';
	*(three + strlen(input) - 3) = '3';
	*(three + strlen(input) - 2) = '.';
	*(three + strlen(input) - 1) = 'p';
	*(three + strlen(input)) = 'g';
	*(three + strlen(input) + 1) = 'm';
	*(three + strlen(input) + 2) = '\0';
	int i5, width, height, rast;
	if(infile == 1){
		FILE* fin = fopen(input, "rb");
		if(fin == NULL){
			cerr << "ERROR fail.";
			return 1;
		}
		fscanf(fin, "%c%d%d%d%d", &p, &i5, &width, &height, &rast);
		if(p != 'P' || i5 != 6){
			cerr << "ERROR fail.";
			return 1;
		}
		fclose(fin);
	}else if(infile == 3){
		FILE* fin = fopen(one, "rb");
		if(fin == NULL){
			cerr << "ERROR fail.";
			return 1;
		}
		fscanf(fin, "%c%d%d%d%d", &p, &i5, &width, &height, &rast);
		if(p != 'P' || i5 != 5){
			cerr << "ERROR fail.";
			return 1;
		}
		fclose(fin);
	}else{
		cerr << "ERROR infile.";
		return 1;
	}
	unsigned char** mas;
	init(&mas, height, width);
	if(infile == 1){
		FILE* fin = fopen(input, "rb");
		if(fin == NULL){
			cerr << "ERROR fail.";
			return 1;
		}
		fscanf(fin, "%c%d%d%d%d", &p, &i5, &width, &height, &rast);
		if(p != 'P' || i5 != 6){
			cerr << "ERROR fail.";
			return 1;
		}
		fread(&c, 1, 1, fin);
		for(int i = 0; i < height; i++){
			for(int j = 0; j < 3 * width; j++){
				fread(&mas[i][j], 1, 1, fin);
			}
		}
		fclose(fin);
	}else{
		int lolh, lolw, lolr;
		for(int k = 0; k < 3; k++){
			FILE* fin;
			if(k == 0){
				fin = fopen(one, "rb");
			}else if(k == 1){
				fin = fopen(two, "rb");
			}else{
				fin = fopen(three, "rb");
			}
			if(fin == NULL){
				cerr << "ERROR fail.";
				return 1;
			}
			fscanf(fin, "%c%d%d%d%d", &p, &i5, &width, &height, &rast);
			if(p != 'P' || i5 != 5){
				cerr << "ERROR fail.";
				return 1;
			}
			if(k == 0){
				lolw = width;
				lolh = height;
				lolr = rast;
			}else{
				if(height != lolh || width != lolw || rast != lolr){
					cerr << "Diferent fail.\n";
					return 1;
				}
			}
			fread(&c, 1, 1, fin);
			for(i = 0; i < height; i++){
				for(j = 0 + k; j < 3 * width; j += 3){
					fread(&mas[i][j], 1, 1, fin);
				}
			}
			fclose(fin);
		}
	}
	if(strcmp(from, "RGB") == 0 && strcmp(to, "HSV") == 0){
		HSV(mas, height, width, 0);
	}else if(strcmp(from, "HSV") == 0 && strcmp(to, "RGB") == 0){
		HSV(mas, height, width, 1);
	}else if(strcmp(from, "RGB") == 0 && strcmp(to, "HSL") == 0){
		HSL(mas, height, width, 0);
	}else if(strcmp(from, "HSL") == 0 && strcmp(to, "RGB") == 0){
		HSL(mas, height, width, 1);
	}else if(strcmp(from, "RGB") == 0 && strcmp(to, "YCbCr.601") == 0){
		YCbCr6(mas, height, width, 0);
	}else if(strcmp(from, "YCbCr.601") == 0 && strcmp(to, "RGB") == 0){
		YCbCr6(mas, height, width, 1);
	}else if(strcmp(from, "RGB") == 0 && strcmp(to, "YCbCr.709") == 0){
		YCbCr7(mas, height, width, 0);
	}else if(strcmp(from, "YCbCr.709") == 0 && strcmp(to, "RGB") == 0){
		YCbCr7(mas, height, width, 1);
	}else if(strcmp(from, "RGB") == 0 && strcmp(to, "YCoCg") == 0){
		YCoCg(mas, height, width, 0);
	}else if(strcmp(from, "YCoCg") == 0 && strcmp(to, "RGB") == 0){
		YCoCg(mas, height, width, 1);
	}else if(strcmp(from, "RGB") == 0 && strcmp(to, "CMY") == 0){
		CMY(mas, height, width);
	}else if(strcmp(from, "CMY") == 0 && strcmp(to, "RGB") == 0){
		CMY(mas, height, width);
	}else if(strcmp(from, "HSV") == 0 && strcmp(to, "HSL") == 0){
		HSV(mas, height, width, 1);
		HSL(mas, height, width, 0);
	}else if(strcmp(from, "HSV") == 0 && strcmp(to, "YCbCr.709") == 0){
		HSV(mas, height, width, 1);
		YCbCr7(mas, height, width, 0);
	}else if(strcmp(from, "HSV") == 0 && strcmp(to, "YCbCr.601") == 0){
		HSV(mas, height, width, 1);
		YCbCr6(mas, height, width, 0);
	}else if(strcmp(from, "HSV") == 0 && strcmp(to, "YCoCg") == 0){
		HSV(mas, height, width, 1);
		YCoCg(mas, height, width, 0);
	}else if(strcmp(from, "HSV") == 0 && strcmp(to, "CMY") == 0){
		HSV(mas, height, width, 1);
		CMY(mas, height, width);
	}else if(strcmp(from, "HSL") == 0 && strcmp(to, "HSV") == 0){
		HSL(mas, height, width, 1);
		HSV(mas, height, width, 0);
	}else if(strcmp(from, "HSL") == 0 && strcmp(to, "YCbCr.601") == 0){
		HSL(mas, height, width, 1);
		YCbCr6(mas, height, width, 0);
	}else if(strcmp(from, "HSL") == 0 && strcmp(to, "YCbCr.709") == 0){
		HSL(mas, height, width, 1);
		YCbCr7(mas, height, width, 0);
	}else if(strcmp(from, "HSL") == 0 && strcmp(to, "YCoCg") == 0){
		HSL(mas, height, width, 1);
		YCoCg(mas, height, width, 0);
	}else if(strcmp(from, "HSL") == 0 && strcmp(to, "CMY") == 0){
		HSL(mas, height, width, 1);
		CMY(mas, height, width);
	}else if(strcmp(from, "YCbCr.601") == 0 && strcmp(to, "HSV") == 0){
		YCbCr6(mas, height, width, 1);
		HSV(mas, height, width, 0);
	}else if(strcmp(from, "YCbCr.601") == 0 && strcmp(to, "HSL") == 0){
		YCbCr6(mas, height, width, 1);
		HSL(mas, height, width, 0);
	}else if(strcmp(from, "YCbCr.601") == 0 && strcmp(to, "YCbCr.709") == 0){
		YCbCr6(mas, height, width, 1);
		YCbCr7(mas, height, width, 0);
	}else if(strcmp(from, "YCbCr.601") == 0 && strcmp(to, "YCoCg") == 0){
		YCbCr6(mas, height, width, 1);
		YCoCg(mas, height, width, 0);
	}else if(strcmp(from, "YCbCr.601") == 0 && strcmp(to, "CMY") == 0){
		YCbCr6(mas, height, width, 1);
		CMY(mas, height, width);
	}else if(strcmp(from, "YCbCr.709") == 0 && strcmp(to, "HSV") == 0){
		YCbCr7(mas, height, width, 1);
		HSV(mas, height, width, 0);
	}else if(strcmp(from, "YCbCr.709") == 0 && strcmp(to, "HSL") == 0){
		YCbCr7(mas, height, width, 1);
		HSL(mas, height, width, 0);
	}else if(strcmp(from, "YCbCr.709") == 0 && strcmp(to, "YCbCr.601") == 0){
		YCbCr7(mas, height, width, 1);
		YCbCr6(mas, height, width, 0);
	}else if(strcmp(from, "YCbCr.709") == 0 && strcmp(to, "YCoCg") == 0){
		YCbCr7(mas, height, width, 1);
		YCoCg(mas, height, width, 0);
	}else if(strcmp(from, "YCbCr.709") == 0 && strcmp(to, "CMY") == 0){
		YCbCr7(mas, height, width, 1);
		CMY(mas, height, width);
	}else if(strcmp(from, "YCoCg") == 0 && strcmp(to, "HSV") == 0){
		YCoCg(mas, height, width, 1);
		HSV(mas, height, width, 0);
	}else if(strcmp(from, "YCoCg") == 0 && strcmp(to, "HSL") == 0){
		YCoCg(mas, height, width, 1);
		HSL(mas, height, width, 0);
	}else if(strcmp(from, "YCoCg") == 0 && strcmp(to, "YCbCr.601") == 0){
		YCoCg(mas, height, width, 1);
		YCbCr6(mas, height, width, 0);
	}else if(strcmp(from, "YCoCg") == 0 && strcmp(to, "YCbCr.709") == 0){
		YCoCg(mas, height, width, 1);
		YCbCr7(mas, height, width, 0);
	}else if(strcmp(from, "YCoCg") == 0 && strcmp(to, "CMY") == 0){
		YCoCg(mas, height, width, 1);
		CMY(mas, height, width);
	}else if(strcmp(from, "CMY") == 0 && strcmp(to, "HSV") == 0){
		CMY(mas, height, width);
		HSV(mas, height, width, 0);
	}else if(strcmp(from, "CMY") == 0 && strcmp(to, "HSL") == 0){
		CMY(mas, height, width);
		HSL(mas, height, width, 0);
	}else if(strcmp(from, "CMY") == 0 && strcmp(to, "YCbCr.601") == 0){
		CMY(mas, height, width);
		YCbCr6(mas, height, width, 0);
	}else if(strcmp(from, "CMY") == 0 && strcmp(to, "YCbCr.709") == 0){
		CMY(mas, height, width);
		YCbCr7(mas, height, width, 0);
	}else if(strcmp(from, "CMY") == 0 && strcmp(to, "YCoCg") == 0){
		CMY(mas, height, width);
		YCoCg(mas, height, width, 0);
	}
	
	if(outfile == 1){
		FILE* fout = fopen(output, "wb");
		if(fout == NULL){
			cerr << "ERROR outfail.";
			return 1;
		}
		fprintf(fout, "%c6\n%d %d\n%d\n", p, width, height, rast);
		for(int i = 0; i < height; i++){
			for(int j = 0; j < 3 * width; j++){
				fprintf(fout, "%c", mas[i][j]);
			}
		}
	}else if(outfile == 3){
		one = (char*)malloc(strlen(output) + 3);
		strcpy(one, output);
		*(one + strlen(output) - 4) = '_';
		*(one + strlen(output) - 3) = '1';
		*(one + strlen(output) - 2) = '.';
		*(one + strlen(output) - 1) = 'p';
		*(one + strlen(output)) = 'g';
		*(one + strlen(output) + 1) = 'm';
		*(one + strlen(output) + 2) = '\0';
		two = (char*)malloc(strlen(output) + 3);
		strcpy(two, output);
		*(two + strlen(output) - 4) = '_';
		*(two + strlen(output) - 3) = '2';
		*(two + strlen(output) - 2) = '.';
		*(two + strlen(output) - 1) = 'p';
		*(two + strlen(output)) = 'g';
		*(two + strlen(output) + 1) = 'm';
		*(two + strlen(output) + 2) = '\0';
		three = (char*)malloc(strlen(output) + 3);
		strcpy(three, output);
		*(three + strlen(output) - 4) = '_';
		*(three + strlen(output) - 3) = '3';
		*(three + strlen(output) - 2) = '.';
		*(three + strlen(output) - 1) = 'p';
		*(three + strlen(output)) = 'g';
		*(three + strlen(output) + 1) = 'm';
		*(three + strlen(output) + 2) = '\0';
		for(int k = 0; k < 3; k++){
			FILE* fout;
			if(k == 0){
				fout = fopen(one, "wb");
			}else if(k == 1){
				fout = fopen(two, "wb");
			}else{
				fout = fopen(three, "wb");
			}
			if(fout == NULL){
				cerr << "ERROR outfail.";
				return 1;
			}
			fprintf(fout, "%c5\n%d %d\n%d\n", p, width, height, rast);
			for(int i = 0; i < height; i++){
				for(int j = 0 + k; j < 3 * width; j += 3){
					fprintf(fout, "%c", mas[i][j]);
				}
			}
			fclose(fout);
		}
	}else{
		cerr << "ERROR outfile.";
		return 1;
	}
	delete(one);
	delete(two);
	delete(three);
	delete(mas);
	return 0;
}
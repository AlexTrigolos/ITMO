#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

typedef struct {
	unsigned char R;
	unsigned char G;
	unsigned char B;
} RGB_pixel;

void fread_c(void * ptr, size_t size, size_t nitems, FILE *file) {
size_t read = fread(ptr, size, nitems, file);
	if (read < nitems) {
		if (feof(file)) {
			printf("Unexpected eof. Probably wrong format.");
			exit(1);
		}
		if (ferror(file)) {
			printf("Unexpected error(%d) while reading from file", errno);
			exit(1);
		}
	}
}

void fwrite_c(void * ptr, size_t size, size_t nitems, FILE *file) {
	size_t write = fwrite(ptr, size, nitems, file);
	if (write < nitems) {
		if (feof(file)) {
			printf("Unexpected eof. Probably wrong format.");
			exit(1);
		}
		if (ferror(file)) {
			printf("Unexpected error(%d) while reading from file", errno);
			exit(1);
		}
	}
}


int readFile(char *fn, unsigned char *type, int *w, int *h, int *z, unsigned char ***pixels, RGB_pixel ***RGB_pixels) {
	FILE *f = fopen(fn, "rb");
	if (f == NULL) {
		perror("Error");
		return -2;
	}
	unsigned char filetype[3];
	unsigned char buf;
	fread_c(&filetype, 1, 2, f);
	filetype[2] = '\0';
	fread_c(&buf, 1, 1, f); //pass \n
	if (buf != '\n') { 
		printf("Error: invalid file header.");
		fclose(f);
		return -1;
	}
	fscanf(f, "%d", w);
	fscanf(f, "%d", h);
	fscanf(f, "%d", z);
	fread_c(&buf, 1, 1, f); //pass \n
	if (buf != '\n') {
		printf("Error: invalid file header.");
		fclose(f);
		return -1;
	}
	if (filetype[0] == 'P' && (filetype[1] == '6' || filetype[1] == '5')) {
		*type = filetype[1];
		if (filetype[1] == '5') { // w&b pic 
			*pixels = (unsigned char**)malloc(sizeof(unsigned char*) * (*h));
			for (int i = 0; i < *h; i++) {
				*(*pixels + i) = (unsigned char*)malloc(sizeof(unsigned char) * (*w));
				for (int j = 0; j < *w; j++) {
					fread_c((*(*pixels + i) + j), 1, 1, f);
				}
			}
			fclose(f);
		} else { //rgb pic
			*RGB_pixels = (RGB_pixel**)malloc(sizeof(RGB_pixel*) * (*h));
			for (int i = 0; i < *h; i++) {
				*(*RGB_pixels + i) = (RGB_pixel*)malloc(sizeof(RGB_pixel) * (*w));
				for (int j = 0; j < *w; j++) {
					fread_c((*(*RGB_pixels + i) + j), 3, 1, f);
				}
			}
			fclose(f);
		}
	} else {
		printf("Error: incorrect file type.");
		fclose(f);
		return -1; //incorrect filetype
	}
	return 0;
}

int check_model(char *model) {
	if (!strcmp(model, "RGB")) {
		return 0;
	}
	if (!strcmp(model, "HSL")) {
		return 1;
	}
	if (!strcmp(model, "HSV")) {
		return 2;
	}
	if (!strcmp(model, "YCbCr.601")) {
		return 3;
	}
	if (!strcmp(model, "YCbCr.709")) {
		return 4;
	}
	if (!strcmp(model, "YCoCg")) {
		return 5;
	}
	if (!strcmp(model, "CMY")) {
		return 6;
	}
	return -1;
}

int check_input(char *model1, char *model2, int count1, int count2) {
	if (check_model(model1) < 0 || check_model(model2) < 0) {
		return -1;
	} else {
		if ((check_model(model1) > 0 && count1 == 1) || (check_model(model2) > 0 && count2 == 1)) {
			return -1;
		}
	}

	return 0;
}

void init_arrays(int v, RGB_pixel ***pixels, unsigned char ***channel1, unsigned char ***channel2, unsigned char ***channel3, int w, int h) {
	if (v) {
		*channel1 = (unsigned char**)malloc(sizeof(unsigned char*) * h);
		*channel2 = (unsigned char**)malloc(sizeof(unsigned char*) * h);
		*channel3 = (unsigned char**)malloc(sizeof(unsigned char*) * h);

		for (int i = 0; i < h; i++) {
			*(*channel1 + i) = (unsigned char*)malloc(sizeof(unsigned char) * w);
			*(*channel2 + i) = (unsigned char*)malloc(sizeof(unsigned char) * w);
			*(*channel3 + i) = (unsigned char*)malloc(sizeof(unsigned char) * w);
		}
	} else {
		*pixels = (RGB_pixel**)malloc(sizeof(RGB_pixel*) * h);
	

		for (int i = 0; i < h; i++) {
			*(*pixels + i) = (RGB_pixel*)malloc(sizeof(RGB_pixel) * w);
		}
	}
}

void RGB_RGB(RGB_pixel ***pixels, unsigned char ***channel1, unsigned char ***channel2, unsigned char ***channel3, int w, int h, int mode) {
	if (mode == 0) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				(*(*(*pixels + i) + j)).R = *(*(*channel1 + i) + j);
				(*(*(*pixels + i) + j)).G = *(*(*channel2 + i) + j);
				(*(*(*pixels + i) + j)).B = *(*(*channel3 + i) + j);
			}
		}
	} else {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				*(*(*channel1 + i) + j) = (*(*(*pixels + i) + j)).R;
				*(*(*channel2 + i) + j) = (*(*(*pixels + i) + j)).G;
				*(*(*channel3 + i) + j) = (*(*(*pixels + i) + j)).B;
			}
		}
	}
}

void RGB_CMY(RGB_pixel **pixels, unsigned char ***channel1, unsigned char ***channel2, unsigned char ***channel3, int w, int h) {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			*(*(*channel1 + i) + j) = 255 - (*(*(pixels + i) + j)).R;
			*(*(*channel2 + i) + j) = 255 - (*(*(pixels + i) + j)).G;
			*(*(*channel3 + i) + j) = 255 - (*(*(pixels + i) + j)).B;
		}
	}
}

void CMY_RGB(RGB_pixel ***pixels, unsigned char **channel1, unsigned char **channel2, unsigned char **channel3, int w, int h) {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			(*(*(*pixels + i) + j)).R = 255 - *(*(channel1 + i) + j);
			(*(*(*pixels + i) + j)).G = 255 - *(*(channel2 + i) + j);
			(*(*(*pixels + i) + j)).B = 255 - *(*(channel3 + i) + j);
		}
	}
}


void RGB_HSV(RGB_pixel **pixels, unsigned char ***channel1, unsigned char ***channel2, unsigned char ***channel3, int w, int h) {
	int R_n, G_n, B_n, C_max, C_min, dC;
	unsigned char H, S, V;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			R_n = (*(*(pixels + i) + j)).R;
			G_n = (*(*(pixels + i) + j)).G;
			B_n = (*(*(pixels + i) + j)).B;
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

			if (C_max == 0) {
				S = 0;
			} else {
				S = (1.0 - (float)C_min/(float)C_max)*255;
			}

			V = C_max;

			*(*(*channel1 + i) + j) = H;
			*(*(*channel2 + i) + j) = S;
			*(*(*channel3 + i) + j) = V;
			
		}
	}
}

void HSV_RGB(RGB_pixel ***pixels, unsigned char **channel1, unsigned char **channel2, unsigned char **channel3, int w, int h) {
	float H, V, S;
	int Hi, V_min, a, V_inc, V_dec;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			H = ((float)(*(*(channel1 + i) + j))/255.0)*360.0;
			S = ((float)(*(*(channel2 + i) + j))/255.0)*100.0;
			V = ((float)(*(*(channel3 + i) + j))/255.0)*100.0;

			Hi = (int)floor(H/60.0) % 6;

			V_min = ((100.0 - S)*V)/100.0;
			a = (V - V_min)*((float)((int)H % 60)/60.0);
			V_inc = V_min + a;
			V_dec = V - a;

			V = (V*255.0)/100.0;
			V_inc = ((float)V_inc * 255.0)/100.0;
			V_dec = ((float)V_dec * 255.0)/100.0;
			V_min = ((float)V_min * 255.0)/100.0;

			if (Hi == 0) {
				(*(*(*pixels + i) + j)).R = V;
				(*(*(*pixels + i) + j)).G = V_inc;
				(*(*(*pixels + i) + j)).B = V_min;
			} else if (Hi == 1) {
				(*(*(*pixels + i) + j)).R = V_dec;
				(*(*(*pixels + i) + j)).G = V;
				(*(*(*pixels + i) + j)).B = V_min;
			} else if (Hi == 2) {
				(*(*(*pixels + i) + j)).R = V_min;
				(*(*(*pixels + i) + j)).G = V;
				(*(*(*pixels + i) + j)).B = V_inc;
			} else if (Hi == 3) {
				(*(*(*pixels + i) + j)).R = V_min;
				(*(*(*pixels + i) + j)).G = V_dec;
				(*(*(*pixels + i) + j)).B = V;
			} else if (Hi == 4) {
				(*(*(*pixels + i) + j)).R = V_inc;
				(*(*(*pixels + i) + j)).G = V_min;
				(*(*(*pixels + i) + j)).B = V;
			} else if (Hi == 5) {
				(*(*(*pixels + i) + j)).R = V;
				(*(*(*pixels + i) + j)).G = V_min;
				(*(*(*pixels + i) + j)).B = V_dec;
			}
		}
	}
}


void RGB_HSL(RGB_pixel **pixels, unsigned char ***channel1, unsigned char ***channel2, unsigned char ***channel3, int w, int h) {
	int R_n, G_n, B_n, C_max, C_min, dC;
	unsigned char H, S, L;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			R_n = (*(*(pixels + i) + j)).R;
			G_n = (*(*(pixels + i) + j)).G;
			B_n = (*(*(pixels + i) + j)).B;
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

			*(*(*channel1 + i) + j) = H;
			*(*(*channel2 + i) + j) = S;
			*(*(*channel3 + i) + j) = L;
			
		}
	}
}

void HSL_RGB(RGB_pixel ***pixels, unsigned char **channel1, unsigned char **channel2, unsigned char **channel3, int w, int h) {
	float Q, P, Hi, L, T_R, T_G, T_B, H, S, R, G, B;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			L = (float)(*(*(channel3 + i) + j)) / 255.0;
			S = (float)(*(*(channel2 + i) + j)) / 255.0;
			Hi = (float)(*(*(channel1 + i) + j)) / 255.0;

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

			(*(*(*pixels + i) + j)).R = R;
			(*(*(*pixels + i) + j)).G = G;
			(*(*(*pixels + i) + j)).B = B;
			
		}
	}
}

void RGB_YCoCg(RGB_pixel **pixels, unsigned char ***channel1, unsigned char ***channel2, unsigned char ***channel3, int w, int h) {
	float R, G, B, Y, Co, Cg;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			R = (float)((*(*(pixels + i) + j)).R) / 255.0;
			G = (float)((*(*(pixels + i) + j)).G) / 255.0;
			B = (float)((*(*(pixels + i) + j)).B) / 255.0;

			Y = 0.25*B + 0.5*G + 0.25*R;
			Co = 0.5*R - 0.5*B + 0.5;
			Cg = -0.25*B + 0.5*G - 0.25*R + 0.5;

			if (Co > 1) Co = 1;
			if (Cg > 1) Cg = 1;

			*(*(*channel1 + i) + j) = Y * 255.0;
			*(*(*channel2 + i) + j) = Co * 255.0;
			*(*(*channel3 + i) + j) = Cg * 255.0;
			
		}
	}
}

void YCoCg_RGB(RGB_pixel ***pixels, unsigned char **channel1, unsigned char **channel2, unsigned char **channel3, int w, int h) {
	float Y, Co, Cg, R, G, B;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			Y = (float)(*(*(channel1 + i) + j))/255.0;
			Co = (float)(*(*(channel2 + i) + j))/255.0 - 0.5;
			Cg = (float)(*(*(channel3 + i) + j))/255.0 - 0.5;

			if (Co < 0) Co = 0;
			if (Cg < 0) Cg = 0;

			R = 255.0*(Co - Cg + Y);
			G = 255.0*(Cg + Y);
			B = 255.0*(-Co - Cg + Y);

			if (R > 255) R = 255;
			if (G > 255) G = 255;
			if (B > 255) B = 255;
			
			if (R < 0) R = 0;
			if (G < 0) G = 0;
			if (B < 0) B = 0;
			

			(*(*(*pixels + i) + j)).R = R;
			(*(*(*pixels + i) + j)).G = G;
			(*(*(*pixels + i) + j)).B = B;
		}
	}
}

void RGB_YCbCr601(RGB_pixel **pixels, unsigned char ***channel1, unsigned char ***channel2, unsigned char ***channel3, int w, int h) {
	float R, G, B, Y, Cb, Cr, K_B = 0.114, K_R =0.299;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			R = (float)((*(*(pixels + i) + j)).R) / 255.0;
			G = (float)((*(*(pixels + i) + j)).G) / 255.0;
			B = (float)((*(*(pixels + i) + j)).B) / 255.0;

			Y = 16 + (65.481 * R + 128.533 * G + 24.966 * B);
			Cb = 128 + (-37.797 * R - 74.203 * G + 112.0 * B);
			Cr = 128 + (112.0 * R - 93.786 * G - 18.214 * B);

			*(*(*channel1 + i) + j) = Y;
			*(*(*channel2 + i) + j) = Cb;
			*(*(*channel3 + i) + j) = Cr;
		}
	}
}

void YCbCr601_RGB(RGB_pixel ***pixels, unsigned char **channel1, unsigned char **channel2, unsigned char **channel3, int w, int h) {
	float R, G, B, Y, Cb, Cr, K_B = 0.114, K_R = 0.299;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			Y = (float)(*(*(channel1 + i) + j));
			Cb = (float)(*(*(channel2 + i) + j));
			Cr = (float)(*(*(channel3 + i) + j));

			R = 1.164*(Y - 16) + 1.596*(Cr - 128);
			G = 1.164*(Y - 16) - 0.813*(Cr - 128) - 0.392*(Cb - 128);
			B = 1.164*(Y - 16) + 2.017*(Cb - 128);

			if (R > 255) R = 255;
			if (G > 255) G = 255;
			if (B > 255) B = 255;
			
			if (R < 0) R = 0;
			if (G < 0) G = 0;
			if (B < 0) B = 0;

			(*(*(*pixels + i) + j)).R = R;
			(*(*(*pixels + i) + j)).G = G;
			(*(*(*pixels + i) + j)).B = B;
		}
	}
}


void RGB_YCbCr709(RGB_pixel **pixels, unsigned char ***channel1, unsigned char ***channel2, unsigned char ***channel3, int w, int h) {
	float R, G, B, Y, Cb, Cr, K_B = 0.0722, K_R =0.2126;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			R = (float)((*(*(pixels + i) + j)).R) / 255.0;
			G = (float)((*(*(pixels + i) + j)).G) / 255.0;
			B = (float)((*(*(pixels + i) + j)).B) / 255.0;

			Y  = 0.2126 * R + 0.7152 * G + 0.0722 * B;
			Cb = (B - Y) / 1.8556 + 0.5;
			Cr = (R - Y) / 1.5748 + 0.5;

			if (Cb > 1) Cb = 1;
			if (Cr > 1) Cr = 1;

			*(*(*channel1 + i) + j) = Y * 255.0;
			*(*(*channel2 + i) + j) = Cb * 255.0;
			*(*(*channel3 + i) + j) = Cr * 255.0;
		}
	}
}

void YCbCr709_RGB(RGB_pixel ***pixels, unsigned char **channel1, unsigned char **channel2, unsigned char **channel3, int w, int h) {
	float R, G, B, Y, Cb, Cr, K_B = 0.722, K_R = 0.2126;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			Y = (float)(*(*(channel1 + i) + j)) / 255.0;
			Cb = (float)(*(*(channel2 + i) + j)) / 255.0 - 0.5;
			Cr = (float)(*(*(channel3 + i) + j)) / 255.0 - 0.5;

			R = 255.0*(Y + 1.5748 * Cr);
			B = 255.0*(Y + 1.8556 * Cb);

			G = 255.0*((Y - R*0.2126/255.0 - B*0.0722/255.0)/0.7152);

			if (R > 255) R = 255;
			if (G > 255) G = 255;
			if (B > 255) B = 255;
			
			if (R < 0) R = 0;
			if (G < 0) G = 0;
			if (B < 0) B = 0;

			(*(*(*pixels + i) + j)).R = R;
			(*(*(*pixels + i) + j)).G = G;
			(*(*(*pixels + i) + j)).B = B;
		}
	}
}

int main(int argc, char *argv[]) {
	int w, h, z;
	unsigned char type;

	char *fname;
	unsigned char **channel1;
	unsigned char **channel2;
	unsigned char **channel3;
	unsigned char **tmp;

	RGB_pixel **RGB_pixels;

	int model_in;
	int model_out;
	int count_in;
	int count_out;
	
	// RGB / HSL / HSV / YCbCr.601 / YCbCr.709 / YCoCg / CMY
	// 0 / 1 / 2/ 3 / 4 / 5 / 6

	if (argc != 11) {
		printf("Error: invalid arguments. (use: ./program -f <from_color_space> -t <to_color_space> -i <count> <input_file_name> -o <count> <output_file_name>)");
		return -1; 
	} else {
		
		if (!check_input(*(argv + 2), *(argv + 4), atoi(*(argv + 6)), atoi(*(argv + 9)))) {
			model_in = check_model(*(argv + 2));
			model_out = check_model(*(argv + 4));
			count_in = atoi(*(argv + 6));
			count_out = atoi(*(argv + 9));

			if (count_in == 1) {
				readFile(*(argv + 7), &type, &w, &h, &z, &tmp, &RGB_pixels);
				init_arrays(1, &RGB_pixels, &channel1, &channel2, &channel3, w, h);
			} else {
				
				fname = (char*)malloc(strlen(*(argv + 7)) + 3);
				strcpy(fname, *(argv + 7));
				*(fname + strlen(*(argv + 7)) - 4) = '_';
				*(fname + strlen(*(argv + 7)) - 3) = '1';
				*(fname + strlen(*(argv + 7)) - 2) = '.';
				*(fname + strlen(*(argv + 7)) - 1) = 'p';
				*(fname + strlen(*(argv + 7))) = 'g';
				*(fname + strlen(*(argv + 7)) + 1) = 'm';
				*(fname + strlen(*(argv + 7)) + 2) = '\0';
				
				readFile(fname, &type, &w, &h, &z, &channel1, &RGB_pixels);
				if (type != '5') {
					perror("Error");
					return -1;
				}

				*(fname + strlen(*(argv + 7)) - 3) = '2';

				readFile(fname, &type, &w, &h, &z, &channel2, &RGB_pixels);
				if (type != '5') {
					perror("Error");
					return -1;
				}

				*(fname + strlen(*(argv + 7)) - 3) = '3';

				readFile(fname, &type, &w, &h, &z, &channel3, &RGB_pixels);
				if (type != '5') {
					perror("Error");
					return -1;
				}

				init_arrays(0, &RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			// PROCESSING BEGIN

			if (model_in == 0 && model_out == 0 && count_out == 3) { // RGB-RGB
				RGB_RGB(&RGB_pixels, &channel1, &channel2, &channel3, w, h, 1);
			}

			if (model_in == 0 && model_out == 0 && count_out == 1) { 
				RGB_RGB(&RGB_pixels, &channel1, &channel2, &channel3, w, h, 0);
			}

			if (model_in == 0 && model_out == 6) {
				RGB_CMY(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}
			if (model_in == 6 && model_out == 0) { // CMY-RGB
				CMY_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
			} 

			if (model_in == 0 && model_out == 2) {
				RGB_HSV(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 2 && model_out == 0) { // HSV-RGB
				HSV_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
			}

			if (model_in == 0 && model_out == 1) {
				RGB_HSL(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 1 && model_out == 0) { // HSL-RGB
				HSL_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
			}

			if (model_in == 0 && model_out == 5) {
				RGB_YCoCg(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 5 && model_out == 0) { // YCoCg-RGB
				YCoCg_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
			}

			if (model_in == 0 && model_out == 3) {
				RGB_YCbCr601(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 3 && model_out == 0) { // YCbCr.601-RGB
				YCbCr601_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
			}

			if (model_in == 0 && model_out == 4) {
				RGB_YCbCr709(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 4 && model_out == 0) { // YCbCr.709-RGB
				YCbCr709_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
			}

			// combinations w/o RGB
				// HSL - any
			if (model_in == 1 && model_out == 2) {
				HSL_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_HSV(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 1 && model_out == 3) {
				HSL_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_YCbCr601(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 1 && model_out == 4) {
				HSL_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_YCbCr709(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 1 && model_out == 5) {
				HSL_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_YCoCg(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 1 && model_out == 6) {
				HSL_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_CMY(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}			

				//HSV - any

			if (model_in == 2 && model_out == 1) {
				HSV_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_HSL(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 2 && model_out == 3) {
				HSV_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_YCbCr601(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 2 && model_out == 4) {
				HSV_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_YCbCr709(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 2 && model_out == 5) {
				HSV_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_YCoCg(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 2 && model_out == 6) {
				HSV_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_CMY(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}			

				//YCbCr.601 - any

			if (model_in == 3 && model_out == 1) {
				YCbCr601_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_HSL(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 3 && model_out == 2) {
				YCbCr601_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_HSV(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 3 && model_out == 4) {
				YCbCr601_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_YCbCr709(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 3 && model_out == 5) {
				YCbCr601_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_YCoCg(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 3 && model_out == 6) {
				YCbCr601_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_CMY(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

				//YCbCr.709 - any

			if (model_in == 4 && model_out == 1) {
				YCbCr709_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_HSL(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 4 && model_out == 2) {
				YCbCr709_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_HSV(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 4 && model_out == 3) {
				YCbCr709_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_YCbCr601(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 4 && model_out == 5) {
				YCbCr709_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_YCoCg(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 4 && model_out == 6) {
				YCbCr709_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_CMY(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

				//YCoCg - any

			if (model_in == 5 && model_out == 1) {
				YCoCg_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_HSL(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 5 && model_out == 2) {
				YCoCg_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_HSV(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 5 && model_out == 3) {
				YCoCg_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_YCbCr601(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 5 && model_out == 4) {
				YCoCg_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_YCbCr709(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 5 && model_out == 6) {
				YCoCg_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_CMY(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

				//CMY - any

			if (model_in == 6 && model_out == 1) {
				CMY_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_HSL(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 6 && model_out == 2) {
				CMY_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_HSV(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 6 && model_out == 3) {
				CMY_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_YCbCr601(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 6 && model_out == 4) {
				CMY_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_YCbCr709(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			if (model_in == 6 && model_out == 5) {
				CMY_RGB(&RGB_pixels, channel1, channel2, channel3, w, h);
				RGB_YCoCg(RGB_pixels, &channel1, &channel2, &channel3, w, h);
			}

			// PROCESSING END

			if (count_out == 1) {
				FILE *o = fopen(*(argv + 10), "wb");
				if (o == NULL) {
					perror("Error");
					return -1;
				}
				fprintf(o, "P6\n%d %d\n%d\n", w, h, z);
				for (int i = 0; i < h; i++)
					for (int j = 0; j < w; j++)
						fwrite_c((*(RGB_pixels + i) + j), 3, 1, o);
				fclose(o);
		
			} else {
				fname = (char*)malloc(strlen(*(argv + 10)) + 3);
				strcpy(fname, *(argv + 10));
				*(fname + strlen(*(argv + 10)) - 4) = '_';
				*(fname + strlen(*(argv + 10)) - 3) = '1';
				*(fname + strlen(*(argv + 10)) - 2) = '.';
				*(fname + strlen(*(argv + 10)) - 1) = 'p';
				*(fname + strlen(*(argv + 10))) = 'g';
				*(fname + strlen(*(argv + 10)) + 1) = 'm';
				*(fname + strlen(*(argv + 10)) + 2) = '\0';

				FILE *o1 = fopen(fname, "wb");
				if (o1 == NULL) {
					perror("Error");
					return -1;
				}
				fprintf(o1, "P5\n%d %d\n%d\n", w, h, z);
				for (int i = 0; i < h; i++)
					for (int j = 0; j < w; j++)
						fwrite_c((*(channel1 + i) + j), 1, 1, o1);
				fclose(o1);

				*(fname + strlen(*(argv + 10)) - 3) = '2';

				FILE *o2 = fopen(fname, "wb");
				if (o2 == NULL) {
					perror("Error");
					return -1;
				}
				fprintf(o2, "P5\n%d %d\n%d\n", w, h, z);
				for (int i = 0; i < h; i++)
					for (int j = 0; j < w; j++)
						fwrite_c((*(channel2 + i) + j), 1, 1, o2);
				fclose(o2);

				*(fname + strlen(*(argv + 10)) - 3) = '3';

				FILE *o3 = fopen(fname, "wb");
				if (o3 == NULL) {
					perror("Error");
					return -1;
				}
				fprintf(o3, "P5\n%d %d\n%d\n", w, h, z);
				for (int i = 0; i < h; i++)
					for (int j = 0; j < w; j++)
						fwrite_c((*(channel3 + i) + j), 1, 1, o3);
				fclose(o3);

			}
		} else {
			perror("Error");
			return -1;
		}

	}
		
		return 0;
}
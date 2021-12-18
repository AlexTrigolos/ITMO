#include <iostream>
#include <fstream>
#include <string.h>
#include <Math.h>

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

head readhead(FILE* fin){
	head rar;
	fscanf(fin, "%c%d%d%d%d", &rar.p, &rar.i56, &rar.width, &rar.height, &rar.rast);
	return rar;
}

void plot(int x, int y, char** mas, short rast){
	mas[y][x] = rast;
}

void line1(int x0, int x1, int y0, int y1, char** mas, short rast){
    int deltax = abs(x1 - x0);
    int deltay = abs(y1 - y0);
    int error = 0;
    int deltaerr = (deltay + 1);
    int diry = y1 - y0;
    if (diry > 0)
        diry = 1;
    if (diry < 0)
        diry = -1;
	if(x0 < x1){
		int y = y0;
		for (int x = x0; x < x1; x++){
			plot(x, y, mas, rast);
			error = error + deltaerr;
			if (error >= (deltax + 1)){
				y = y + diry;
				error = error - (deltax + 1);
			}
		}
	}else{//если конец меньше начала
		int y = y1;
		for (int x = x1; x < x0; x++){
			plot(x, y, mas, rast);
			error = error + deltaerr;
			if (error >= (deltax + 1)){
				y = y - diry;
				error = error - (deltax + 1);
			}
		}
	}
}

void line2(int x0, int x1, int y0, int y1, char** mas, short rast){
    int deltax = abs(x1 - x0);
    int deltay = abs(y1 - y0);
    int error = 0;
    int deltaerr = (deltax + 1);
    int diry = x1 - x0;
    if (diry > 0)
        diry = 1;
    if (diry < 0)
        diry = -1;
	if(y0 < y1){
		int x = x0;
		for (int y = y0; y < y1; y++){
			plot(x, y, mas, rast);
			error = error + deltaerr;
			if (error >= (deltay + 1)){
				x = x + diry;
				error = error - (deltay + 1);
			}
		}
	}else{//если конец меньше начала
		int x = x1;
		for (int y = y1; y < y0; y++){
			plot(x, y, mas, rast);
			error = error + deltaerr;
			if (error >= (deltay + 1)){
				x = x - diry;
				error = error - (deltay + 1);
			}
		}
	}
}

int main(int argc, char* argv[]){
	FILE* fin = fopen(argv[1], "rb");
	if(fin == NULL){
		cout << "ERROR1" << endl;
		return 1;
	}
	head my = readhead(fin);
	if(my.i56 != 5){
		cout << "ERROR2" << endl;
		return 2;
	}
	char c;
	fread(&c, 1, 1, fin);
	char** mas = new char* [my.height];
	for(int i = 0; i < my.height; i++){
		mas[i] = new char [my.width];
	}
	for(int i = 0; i < my.height; i++){
		for(int j = 0; j < my.width; j++){
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
	fprintf(fout, "%c%d\n%d %d\n%d\n", my.p, my.i56, my.width, my.height, my.rast);
	if(abs(atoi(argv[5]) - atoi(argv[7])) >= abs(atoi(argv[6]) - atoi(argv[8])))
		line1(atoi(argv[5]), atoi(argv[7]), atoi(argv[6]), atoi(argv[8]), mas, atoi(argv[3]));
	else line2(atoi(argv[5]), atoi(argv[7]), atoi(argv[6]), atoi(argv[8]), mas, atoi(argv[3]));
	for(int i = 0; i < my.height; i++){
		for(int j = 0; j < my.width; j++){
			fprintf(fout, "%c", mas[i][j]);
		}
	}
	return 0;
}
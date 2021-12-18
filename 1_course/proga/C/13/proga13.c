#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#pragma pack(1)

struct ID3v2{
	char tag[3];
	char maj_v;
	char rev_v;
	char flag;
	int tag_size;
};


struct ID3V2frame{
	char header[4];
	int size;
	char flags[2];
};


int bit7(int size){
	int res = 0;
	int deg = 0;
	int i = 0;
	while(size){
		if(i % 8 != 7){
			res += (size & 1) * pow(2, deg);
			deg++;
		}
		i++;
		size >>= 1;
	}
	return res;
}


void getStr(char *dest, char *src, int size, int un_size){
    for(int i = 0; i < size; i++){
        dest[i] = src[i + un_size];
    }
}


int changeEndian(int number){
	return ((number >> 24) & 0xff) | ((number << 8) & 0xff0000) | ((number >> 8) & 0xff00) | ((number << 24) & 0xff000000);//0xff == 0x000000ff
}

void show(FILE *file){
	printf("  Name frames\t\t\tFrame value");
	struct ID3v2 ror;
	fread(&ror, sizeof(ror), 1, file);
	int sizelt = changeEndian(ror.tag_size);
	int asd = bit7(sizelt);
	char *crn = malloc(4);
	int j = 0;
	while(j <= asd){
		struct ID3V2frame frame;
		fread(&frame, sizeof(frame), 1, file);
		int size = changeEndian(frame.size);
		for(int i = 0; i < 4; i++){
			crn[i] = frame.header[i];
		}
		if(frame.header[0] == 'T'){
			printf("\n     %s\t\t", frame.header);
			for(int i = 0; i < size; i++){
				char c;
				fread(&c, 1, 1, file);
				if(i>2){
					printf("%c", c);
				}
			}
		}else{
			for(int i = 0; i < size; i++){
				char c;
				fread(&c, 1, 1, file);
			}
		}
		j = j + size + 10;
		//j = j + 9 * size;
	}
}


void get(FILE *file, char *prop){
	char *crn = malloc(4);

	while(strcmp(crn, prop)){
		struct ID3V2frame frame;
		fread(&frame, sizeof(frame), 1, file);
		int size = changeEndian(frame.size);

		for(int i = 0; i < 4; i++){
			crn[i] = frame.header[i];
		}
		if(!strcmp(crn, prop)){
			printf(" ");
			for(int i = 0; i < size; i++){
				char c;
				fread(&c, 1, 1, file);
				if(i>2){
					printf("%c", c);
				}
			}
		}else{
			for (int i = 0; i < size; i++) {
				char c;
				fread(&c, 1, 1, file);
			}
		}
	}
}


void set(FILE *file, char *prop, char *value, FILE *secfile){
	char *crn = malloc(4);
	char crem;
	struct ID3v2 data;
	fread(&data.tag, sizeof(data.tag), 1, file);
	fread(&data.maj_v, sizeof(data.maj_v), 1, file);
	fread(&data.rev_v, sizeof(data.rev_v), 1, file);
	fread(&data.flag, sizeof(data.flag), 1, file);
	fread(&data.tag_size, sizeof(data.tag_size), 1, file);
	
	for(int i = 0; i < 3; i++){
		crem = data.tag[i];
		fwrite(&crem, 1, 1, secfile);
	}
	crem = data.maj_v;
	fwrite(&crem, 1, 1, secfile);
	crem = data.rev_v;
	fwrite(&crem, 1, 1, secfile);
	crem = data.flag;
	fwrite(&crem, 1, 1, secfile);
	int dfg;
	dfg = data.tag_size;
	fwrite(&dfg, sizeof(int), 1, secfile);
	
	
	while(strcmp(crn, prop) != 0){
		struct ID3V2frame frame;
		fread(&frame, sizeof(frame), 1, file);
		int size = changeEndian(frame.size);
		int right_size = bit7(size);
		for(int i = 0; i < 4; i++){
			crn[i] = frame.header[i];
		}
		if (!strcmp(crn, prop)){
			int length = strlen(value);
			char Arr;
			fwrite(&frame.header, sizeof(frame.header), 1, secfile);
			char t = 0x00;
			int fors = 2 * length + 3;
			size = changeEndian(fors);
			fwrite(&size, 4, 1, secfile);
			for(int i = 0; i < 2; ++i){
				fwrite(&t, 1, 1, secfile);
			}
			char d = 0x01;
			fwrite(&d, 1, 1, secfile);
			char x = 0xff;
			fwrite(&x, 1, 1, secfile);
			x = 0xfe;
			fwrite(&x, 1, 1, secfile);
			for(int i = 0; i < length; i++){
				Arr = value[i];
				fwrite(&Arr, 1, 1, secfile);
				fwrite(&t, 1, 1, secfile);
			}
			for(int i = 0; i < right_size; i++){
				char c;
				fread(&c, 1, 1, file);
			}
		}else{
			char t = 0x00;
			fwrite(&frame.header, sizeof(frame.header), 1, secfile);
			fwrite(&frame.size, 4, 1, secfile);
			for(int i = 0; i < 2; ++i){
				fwrite(&t, 1, 1, secfile);
			}
			for(int i = 0; i < right_size; i++){
				char c;
				fread(&c, 1, 1, file);
				fwrite(&c, 1, 1, secfile);
	}
		}
	}
	while(!feof(file)){
		char c;
		fread(&c, 1, 1, file);
		fwrite(&c, 1, 1, secfile);
	}
}

int main(int argc, char **argv){
	setlocale(LC_ALL, "Rus");
	char *name_file = malloc(strlen(argv[1]) - 11);
	getStr(name_file, argv[1], strlen(argv[1]) - 11, 11);
	FILE *audio = fopen(name_file, "rb+");
	FILE *new = fopen("lol.mp3","wb+");
	if(!strcmp(argv[2], "--show")){
		show(audio);
		fclose(audio);
		fclose(new);
		remove("lol.mp3");
		printf("\n");
	}else{
		char cmd[6];
		for (int i = 0; i < 5; i++){
			cmd[i] = argv[2][i];
		}
		char *prop_name = malloc(strlen(argv[2]) - 6);
		getStr(prop_name, argv[2], strlen(argv[2]) - 6, 6);
		if(!strcmp(cmd, "--get")){
			fseek(audio, 10, SEEK_SET);
			get(audio, prop_name);
			fclose(audio);
			fclose(new);
			remove("lol.mp3");
			printf("\n");
		}else if(!strcmp(cmd, "--set")){
			char *prop_value = malloc(strlen(argv[3]) - 6);
			getStr(prop_value, argv[3], strlen(argv[3]) - 6, 6);
			set(audio, prop_name, prop_value, new);
			fclose(audio);
			fclose(new);
			remove(name_file);
			rename("lol.mp3",name_file);
		}
	}
	return 0;
}
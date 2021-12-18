#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>
#include <direct.h>

#pragma pack(1)

struct BMP {
    unsigned short type;
    unsigned int size_file;
    unsigned short res1;
    unsigned short res2;
    unsigned int offset;

    unsigned int size;
    int width;
    int height;
    unsigned short planes;
    unsigned short byte_count;

    unsigned int compression;
    unsigned int size_image;
    int xpels_per_meter;
    int ypels_per_meter;
    unsigned int colors_used;
    unsigned int color_important;
};

int countLives(int y, int x, short **generation, struct BMP header) {
    int count_lives = 0;
    for (int i = y - 1; i <= y + 1; i++) {
        for (int j = x - 1; j <= x + 1; j++) {
            if (i == y && j == x) {
                continue;
            }
            int new_y = i;
            int new_x = j;
            if (i < 0) {
                new_y = header.height - 1;
            }
            if (i > header.height - 1) {
                new_y = 0;
            }
            if (j < 0) {
                new_x = header.width - 1;
            }
            if (j > header.width - 1) {
                new_x = 0;
            }

            if (generation[new_y][new_x] == 0) {
                count_lives++;
            }
        }
    }
    return count_lives;
}


short **createNewGeneration(struct BMP header, short **generation) {
    short **new_generation = (short **) malloc(sizeof(short *) * header.height);
    for (int i = 0; i < header.height; i++) {
        new_generation[i] = (short *) malloc(sizeof(short) * header.width);
    }

    for (int x = 0; x < header.height; x++) {
        for (int y = 0; y < header.width; y++) {
            new_generation[x][y] = generation[x][y];

        }
    }


    for (int y = 0; y < header.height; y++) {
        for (int x = 0; x < header.width; x++) {
            int count_lives = countLives(y, x, generation, header);
            if (generation[y][x] == 1) {
                if (count_lives == 3) {
                    new_generation[y][x] = 0;
                }
            } else {
                if (count_lives < 2 || count_lives > 3) {
                    new_generation[y][x] = 1;
                }
            }
        }
    }
    return new_generation;
}


void writeNewBMP(char file[], short **new_generation, struct BMP header, char* gap, int gap_length) {
    FILE *newGen = fopen(file, "wb");
    fwrite(&header, sizeof(header), 1, newGen);
    for (int i = 0; i < gap_length; i++) {
        fwrite(&gap[i], 1, 1, newGen);
    }

    for (int x = header.height - 1; x >= 0; x--) {
        for (int y = 0; y < header.width; y += 8) {
            unsigned char pixel = 0;
            short colors8[8];
            for (int i = 0; i < 8; i++) {
                colors8[i] = new_generation[x][y + i];
                pixel += colors8[i] * pow(2, 7 - i);
            }

            fwrite(&pixel, 1, 1, newGen);
        }
        int res = ((32 - (header.width % 32)) / 8) % 4;
        for (int i = 0; i < res; i++) {
            unsigned char padding = '\0';
            fwrite(&padding, 1, 1, newGen);
        }
    }
    fclose(newGen);
}


int checkNewGeneration(short*** game, short** generation, int index, struct BMP header) {
    int i = 0;
    int flag = 0;
    while (i < index) {
        for (int x = 0; x < header.height; x++) {
            for (int y = 0; y < header.width; y++) {
                if (game[i][x][y] != generation[x][y]) {
                    flag = 1;
                    break;
                }
            }
            if (flag) {
                break;
            }

        }
        if (!flag) {
            return 0;
        }
        flag = 0;
        i++;
    }
    return 1;
}


int main(int argc, char *argv[]) {
    FILE *image = fopen(argv[2], "rb");
    int max_iter = 1024;
    int dump_freq = 1;
    
   
    char dir[100];
    snprintf(dir, sizeof(dir), "%s", argv[4]);
    if (argc > 6) {
        max_iter = atoi(argv[6]);
        if (argc > 8) {
            dump_freq = atoi(argv[8]);
        }
    }
     
    struct BMP header;
    fread(&header, sizeof(header), 1, image);
//    printf("Type - %d\n", header.type);
//    printf("File size - %d\n", header.size_file);
//    printf("Offset to pixels- %d\n", header.offset);
//
//    printf("Header size- %d\n", header.size);
//    printf("Width -%d\n", header.width);
    header.width = abs(header.width);
//    printf("Height - %d\n", header.height);
    header.height = abs(header.height);
//    printf("Byte per pixel - %d\n", header.byte_count);
//    printf("Image size - %d\n", header.size_image);
//
//    printf("Method to store pixels - %d\n", header.compression);
//    printf("Pixel per meter (x) - %d\n", header.xpels_per_meter);
//    printf("Pixel per meter  (y) - %d\n", header.ypels_per_meter);
//    printf("Size color table - %d\n", header.colors_used);
//    printf("Colors - %d\n", header.color_important);

    // printf("%d", header.offset);
    int gap_length = header.offset - header.size - 14;
    char* gap = malloc(gap_length);
    for (int i = 0; i < gap_length; i++) {
        fread(&gap[i], 1, 1, image);
    }



    int index = 0;
    short ***game = (short ***) malloc(sizeof(short **) * max_iter);
    for (int i = 0; i < 1024; i++) {
        game[i] = (short **) malloc(sizeof(short *) * header.height);
        for (int j = 0; j < header.height; j++) {
            game[i][j] = (short *) malloc(sizeof(short) * header.width);
        }
    }

    short **generation = (short **) malloc(sizeof(short *) * header.height);
    for (int i = 0; i < header.height; i++) {
        generation[i] = (short *) malloc(sizeof(short) * header.width);
    }


    int n = 0;
    for (int x = header.height - 1; x >= 0; x--) {
        for (int y = 0; y < header.width / 8; y++) {
            unsigned char pixel;
            fread(&pixel, 1, 1, image);
            short colors8[8];
            for (int i = 0; i < 8; i++) {
                colors8[i] = (pixel >> (7 - i)) & 1;
                generation[x][y * 8 + i] = colors8[i];
                if (!colors8[i]) {
                    n++;
                }
            }
        }
        int res = ((32 - (header.width % 32)) / 8) % 4;
        for (int i = 0; i < res; i++) {
            char padding;
            fread(&padding, 1, 1, image);
        }
    }
    game[index] = generation;

    
    fclose(image);
    char name[] = "gen";
    char exp[] = ".bmp";
    char path[100];
    snprintf(path, sizeof(path), "%s/%s", dir, name);
    int res = _mkdir(dir);
     //mkdir(dir, 0777);
	 printf("\n%d ", max_iter);
    for (int i = 0; i < max_iter; i++) {
		printf("\n%d", i);
        index++;
        game[index] = createNewGeneration(header, game[index - 1]);
        char *number = malloc(4);
        sprintf(number, "%d", index);
        char file[100];
        snprintf(file, sizeof(file), "%s%s%s", path, number, exp);
        if (i % dump_freq == 0) {
            writeNewBMP(file, game[index], header, gap, gap_length);
        }
        int isValid = checkNewGeneration(game, game[index], index, header);
        if (!isValid) {
            break;
        }
    }
	
    return 0;
}

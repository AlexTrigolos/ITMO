#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void Right(unsigned char** kub, int turn){
	unsigned char c;
	c = kub[turn][0];
	kub[turn][0] = kub[turn][6];
	kub[turn][6] = kub[turn][8];
	kub[turn][8] = kub[turn][2];
	kub[turn][2] = c;
	c = kub[turn][1];
	kub[turn][1] = kub[turn][3];
	kub[turn][3] = kub[turn][7];
	kub[turn][7] = kub[turn][5];
	kub[turn][5] = c;
}

void Left(unsigned char** kub, int turn){
	unsigned char c;
	c = kub[turn][0];
	kub[turn][0] = kub[turn][2];
	kub[turn][2] = kub[turn][8];
	kub[turn][8] = kub[turn][6];
	kub[turn][6] = c;
	c = kub[turn][1];
	kub[turn][1] = kub[turn][5];
	kub[turn][5] = kub[turn][7];
	kub[turn][7] = kub[turn][3];
	kub[turn][3] = c;
}

void YR(unsigned char** kub){
	unsigned char c;
	Right(kub, 0);
	c = kub[5][6];
	kub[5][6] = kub[1][2];
	kub[1][2] = kub[2][2];
	kub[2][2] = kub[3][2];
	kub[3][2] = c;
	c = kub[5][8];
	kub[5][8] = kub[1][0];
	kub[1][0] = kub[2][0];
	kub[2][0] = kub[3][0];
	kub[3][0] = c;
	c = kub[5][7];
	kub[5][7] = kub[1][1];
	kub[1][1] = kub[2][1];
	kub[2][1] = kub[3][1];
	kub[3][1] = c;
}

void YL(unsigned char** kub){
	unsigned char c;
	Left(kub, 0);
	c = kub[5][6];
	kub[5][6] = kub[3][2];
	kub[3][2] = kub[2][2];
	kub[2][2] = kub[1][2];
	kub[1][2] = c;
	c = kub[5][8];
	kub[5][8] = kub[3][0];
	kub[3][0] = kub[2][0];
	kub[2][0] = kub[1][0];
	kub[1][0] = c;
	c = kub[5][7];
	kub[5][7] = kub[3][1];
	kub[3][1] = kub[2][1];
	kub[2][1] = kub[1][1];
	kub[1][1] = c;
}

void RR(unsigned char** kub){
	unsigned char c;
	Right(kub, 1);
	c = kub[0][0];
	kub[0][0] = kub[5][0];
	kub[5][0] = kub[4][0];
	kub[4][0] = kub[2][0];
	kub[2][0] = c;
	c = kub[0][6];
	kub[0][6] = kub[5][6];
	kub[5][6] = kub[4][6];
	kub[4][6] = kub[2][6];
	kub[2][6] = c;
	c = kub[0][3];
	kub[0][3] = kub[5][3];
	kub[5][3] = kub[4][3];
	kub[4][3] = kub[2][3];
	kub[2][3] = c;
}

void RL(unsigned char** kub){
	unsigned char c;
	Left(kub, 1);
	c = kub[0][0];
	kub[0][0] = kub[2][0];
	kub[2][0] = kub[4][0];
	kub[4][0] = kub[5][0];
	kub[5][0] = c;
	c = kub[0][6];
	kub[0][6] = kub[2][6];
	kub[2][6] = kub[4][6];
	kub[4][6] = kub[5][6];
	kub[5][6] = c;
	c = kub[0][3];
	kub[0][3] = kub[2][3];
	kub[2][3] = kub[4][3];
	kub[4][3] = kub[5][3];
	kub[5][3] = c;
}

void GR(unsigned char** kub){
	unsigned char c;
	Right(kub, 2);
	c = kub[0][6];
	kub[0][6] = kub[1][8];
	kub[1][8] = kub[4][2];
	kub[4][2] = kub[3][0];
	kub[3][0] = c;
	c = kub[0][8];
	kub[0][8] = kub[1][2];
	kub[1][2] = kub[4][0];
	kub[4][0] = kub[3][6];
	kub[3][6] = c;
	c = kub[0][7];
	kub[0][7] = kub[1][5];
	kub[1][5] = kub[4][1];
	kub[4][1] = kub[3][3];
	kub[3][3] = c;
}

void GL(unsigned char** kub){
	unsigned char c;
	Left(kub, 2);
	c = kub[0][6];
	kub[0][6] = kub[3][0];
	kub[3][0] = kub[4][2];
	kub[4][2] = kub[1][8];
	kub[1][8] = c;
	c = kub[0][8];
	kub[0][8] = kub[3][6];
	kub[3][6] = kub[4][0];
	kub[4][0] = kub[1][2];
	kub[1][2] = c;
	c = kub[0][7];
	kub[0][7] = kub[3][3];
	kub[3][3] = kub[4][1];
	kub[4][1] = kub[1][5];
	kub[1][5] = c;
}

void OR(unsigned char** kub){
	unsigned char c;
	Right(kub, 3);
	c = kub[0][2];
	kub[0][2] = kub[2][2];
	kub[2][2] = kub[4][2];
	kub[4][2] = kub[5][2];
	kub[5][2] = c;
	c = kub[0][8];
	kub[0][8] = kub[2][8];
	kub[2][8] = kub[4][8];
	kub[4][8] = kub[5][8];
	kub[5][8] = c;
	c = kub[0][5];
	kub[0][5] = kub[2][5];
	kub[2][5] = kub[4][5];
	kub[4][5] = kub[5][5];
	kub[5][5] = c;
}

void OL(unsigned char** kub){
	unsigned char c;
	Left(kub, 3);
	c = kub[0][2];
	kub[0][2] = kub[5][2];
	kub[5][2] = kub[4][2];
	kub[4][2] = kub[2][2];
	kub[2][2] = c;
	c = kub[0][8];
	kub[0][8] = kub[5][8];
	kub[5][8] = kub[4][8];
	kub[4][8] = kub[2][8];
	kub[2][8] = c;
	c = kub[0][5];
	kub[0][5] = kub[5][5];
	kub[5][5] = kub[4][5];
	kub[4][5] = kub[2][5];
	kub[2][5] = c;
}

void WR(unsigned char** kub){
	unsigned char c;
	Right(kub, 4);
	c = kub[5][0];
	kub[5][0] = kub[3][8];
	kub[3][8] = kub[2][8];
	kub[2][8] = kub[1][8];
	kub[1][8] = c;
	c = kub[5][2];
	kub[5][2] = kub[3][6];
	kub[3][6] = kub[2][6];
	kub[2][6] = kub[1][6];
	kub[1][6] = c;
	c = kub[5][1];
	kub[5][1] = kub[3][7];
	kub[3][7] = kub[2][7];
	kub[2][7] = kub[1][7];
	kub[1][7] = c;
}

void WL(unsigned char** kub){
	unsigned char c;
	Left(kub, 4);
	c = kub[5][0];
	kub[5][0] = kub[1][8];
	kub[1][8] = kub[2][8];
	kub[2][8] = kub[3][8];
	kub[3][8] = c;
	c = kub[5][2];
	kub[5][2] = kub[1][6];
	kub[1][6] = kub[2][6];
	kub[2][6] = kub[3][6];
	kub[3][6] = c;
	c = kub[5][1];
	kub[5][1] = kub[1][7];
	kub[1][7] = kub[2][7];
	kub[2][7] = kub[3][7];
	kub[3][7] = c;
}

void BR(unsigned char** kub){
	unsigned char c;
	Right(kub, 5);
	c = kub[0][0];
	kub[0][0] = kub[3][2];
	kub[3][2] = kub[4][8];
	kub[4][8] = kub[1][6];
	kub[1][6] = c;
	c = kub[0][2];
	kub[0][2] = kub[3][8];
	kub[3][8] = kub[4][6];
	kub[4][6] = kub[1][0];
	kub[1][0] = c;
	c = kub[0][1];
	kub[0][1] = kub[3][5];
	kub[3][5] = kub[4][7];
	kub[4][7] = kub[1][3];
	kub[1][3] = c;
}

void BL(unsigned char** kub){
	unsigned char c;
	Left(kub, 5);
	c = kub[0][0];
	kub[0][0] = kub[1][6];
	kub[1][6] = kub[4][8];
	kub[4][8] = kub[3][2];
	kub[3][2] = c;
	c = kub[0][2];
	kub[0][2] = kub[1][0];
	kub[1][0] = kub[4][6];
	kub[4][6] = kub[3][8];
	kub[3][8] = c;
	c = kub[0][1];
	kub[0][1] = kub[1][3];
	kub[1][3] = kub[4][7];
	kub[4][7] = kub[3][5];
	kub[3][5] = c;
}

void checkmas(int* mas, unsigned char c){
	if(c == 'y'){
		mas[0]++;
	}else if(c == 'r'){
		mas[1]++;
	}else if(c == 'g'){
		mas[2]++;
	}else if(c == 'o'){
		mas[3]++;
	}else if(c == 'w'){
		mas[4]++;
	}else if(c == 'b'){
		mas[5]++;
	}
}

bool checkcol(unsigned char a, unsigned char b){
	if((a == 'w' && b == 'y') || (a == 'y' && b == 'w') || (a == 'b' && b == 'g') || (a == 'g' && b == 'b') || (a == 'r' && b == 'o') || (a == 'o' && b == 'r') || a == b){
		return true;
	}
	return false; 
}

bool checkcen(vector<unsigned char>& cen, unsigned char a, bool flag, int* mas){
	if(flag == true){
		for(unsigned int i = 0; i < cen.size(); i++){
			if(cen[i] == a){
				return false;
			}
		}
		checkmas(mas, a);
		cen.push_back(a);
		return true;
	}else{
		return false;
	}
}

bool checkreb(vector<pair<unsigned char, unsigned char>>& reb, unsigned char a, unsigned char b, bool flag, int* mas){
	if(flag == true){
		for(unsigned int i = 0; i < reb.size(); i++){
			if((reb[i].first == a && reb[i].second == b) || (reb[i].first == b && reb[i].second == a) || checkcol(a, b)){
				return false;
			}
		}
		checkmas(mas, a);
		checkmas(mas, b);
		reb.push_back({a, b});
		return true;
	}else{
		return false;
	}
}

bool checkcor(vector<pair<unsigned char, pair<unsigned char, unsigned char>>>& cor, unsigned char a, unsigned char b, unsigned char c, bool flag, int* mas){
	if(flag == true){
		for(unsigned int i = 0; i < cor.size(); i++){
			pair<unsigned char, unsigned char> now = cor[i].second;
			unsigned char first = cor[i].first, second = now.first, third = now.second;
			if((first == a && second == b && third == c) || (first == a && second == c && third == b) || (first == b && second == a && third == c) || (first == b && second == c && third == a) || (first == c && second == a && third == b) || (first == c && second == b && third == a) || checkcol(a, b) || checkcol(a, c) || checkcol(b, c)){
				return false;
			}
		}
		checkmas(mas, a);
		checkmas(mas, b);
		checkmas(mas, c);
		cor.push_back({a, {b, c}});
		return true;
	}else{
		return false;
	}
}

bool check(unsigned char** kub){
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 9; j++){
			if(kub[i][j] != 'r' && kub[i][j] != 'o' && kub[i][j] != 'g' && kub[i][j] != 'b' && kub[i][j] != 'y' && kub[i][j] != 'w'){
				return false;
			}
		}
	}
	int* mas = new int[6];
	for(int i = 0; i < 6; i++){
		mas[i] = 0;
	}
	bool flag = true;
	vector<pair<unsigned char, unsigned char>> reb;
	flag = checkreb(reb, kub[0][7], kub[2][1], flag, mas);
	flag = checkreb(reb, kub[0][5], kub[3][1], flag, mas);
	flag = checkreb(reb, kub[0][1], kub[5][7], flag, mas);
	flag = checkreb(reb, kub[0][3], kub[1][1], flag, mas);
	flag = checkreb(reb, kub[1][5], kub[2][3], flag, mas);
	flag = checkreb(reb, kub[2][5], kub[3][3], flag, mas);
	flag = checkreb(reb, kub[3][5], kub[5][5], flag, mas);
	flag = checkreb(reb, kub[5][3], kub[1][3], flag, mas);
	flag = checkreb(reb, kub[4][1], kub[2][7], flag, mas);
	flag = checkreb(reb, kub[4][3], kub[1][7], flag, mas);
	flag = checkreb(reb, kub[4][5], kub[3][7], flag, mas);
	flag = checkreb(reb, kub[4][7], kub[5][1], flag, mas);
	vector<pair<unsigned char, pair<unsigned char, unsigned char>>> cor;
	flag = checkcor(cor, kub[0][6], kub[1][2], kub[2][0], flag, mas);
	flag = checkcor(cor, kub[0][8], kub[2][2], kub[3][0], flag, mas);
	flag = checkcor(cor, kub[1][8], kub[2][6], kub[4][0], flag, mas);
	flag = checkcor(cor, kub[2][8], kub[3][6], kub[4][2], flag, mas);
	flag = checkcor(cor, kub[0][2], kub[3][2], kub[5][8], flag, mas);
	flag = checkcor(cor, kub[0][0], kub[1][0], kub[5][6], flag, mas);
	flag = checkcor(cor, kub[1][6], kub[4][6], kub[5][0], flag, mas);
	flag = checkcor(cor, kub[3][8], kub[4][8], kub[5][2], flag, mas);
	vector<unsigned char> cen;
	flag = checkcen(cen, kub[0][4], flag, mas);
	flag = checkcen(cen, kub[1][4], flag, mas);
	flag = checkcen(cen, kub[2][4], flag, mas);
	flag = checkcen(cen, kub[3][4], flag, mas);
	flag = checkcen(cen, kub[4][4], flag, mas);
	flag = checkcen(cen, kub[5][4], flag, mas);
	if(flag == false){
		return flag;
	}else{
		for(int i = 0; i < 6; i++){
			if(mas[i] > 9){
				return false;
			}
		}
		return flag;
	}
}

int menu(){
	system("cls");
	cout << "1. Save or read file." << endl;
	cout << "2. Normal?" << endl;
	cout << "3. Show kubik." << endl;
	cout << "4. Spin turn." << endl;
	cout << "5. Scrol." << endl;
	cout << "6. Find result." << endl;
	cout << "7. Exit." << endl;
	cout << "8. BIG check." << endl;
	int var;
	cin >> var;
	return var;
}

int secmenu(){
	cout << "1. Save." << endl;
	cout << "2. Read." << endl;
	int znach;
	cin >> znach;
	return znach;
}

void show(unsigned char** kub){
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 9; j += 3){
			if(i == 0 || i == 4 || i == 5){
				cout << "        ";
			}
			if(i == 1){
				cout << kub[i][j] << " " << kub[i][j + 1] << " " << kub[i][j + 2] << " | " << kub[i + 1][j] << " " << kub[i + 1][j + 1] << " " << kub[i + 1][j + 2] << " | "<< kub[i + 2][j] << " " << kub[i + 2][j + 1] << " " << kub[i + 2][j + 2] << "\n" << kub[i][j + 3] << " " << kub[i][j + 4] << " " << kub[i][j + 5] << " | " << kub[i + 1][j + 3] << " " << kub[i + 1][j + 4] << " " << kub[i + 1][j + 5] << " | "<< kub[i + 2][j + 3] << " " << kub[i + 2][j + 4] << " " << kub[i + 2][j + 5] << "\n" << kub[i][j + 6] << " " << kub[i][j + 7] << " " << kub[i][j + 8] << " | " << kub[i + 1][j + 6] << " " << kub[i + 1][j + 7] << " " << kub[i + 1][j + 8] << " | "<< kub[i + 2][j + 6] << " " << kub[i + 2][j + 7] << " " << kub[i + 2][j + 8] << "\n";
				i += 2;
				break;
			}else{
				cout << kub[i][j] << " " << kub[i][j + 1] << " " << kub[i][j + 2] << "\n";
			}
		}
		if(i == 0 || i == 3 || i == 4){
			cout << "        - - -\n";
		}
	}
}

void save(unsigned char** kub){
	ofstream fout("rubik.out");
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 9; j += 3){
			if(i == 0 || i == 4 || i == 5){
				fout << "        ";
			}
			if(i == 1){
				fout << kub[i][j] << " " << kub[i][j + 1] << " " << kub[i][j + 2] << " | " << kub[i + 1][j] << " " << kub[i + 1][j + 1] << " " << kub[i + 1][j + 2] << " | "<< kub[i + 2][j] << " " << kub[i + 2][j + 1] << " " << kub[i + 2][j + 2] << "\n" << kub[i][j + 3] << " " << kub[i][j + 4] << " " << kub[i][j + 5] << " | " << kub[i + 1][j + 3] << " " << kub[i + 1][j + 4] << " " << kub[i + 1][j + 5] << " | "<< kub[i + 2][j + 3] << " " << kub[i + 2][j + 4] << " " << kub[i + 2][j + 5] << "\n" << kub[i][j + 6] << " " << kub[i][j + 7] << " " << kub[i][j + 8] << " | " << kub[i + 1][j + 6] << " " << kub[i + 1][j + 7] << " " << kub[i + 1][j + 8] << " | "<< kub[i + 2][j + 6] << " " << kub[i + 2][j + 7] << " " << kub[i + 2][j + 8] << "\n";
				i += 2;
				break;
			}else{
				fout << kub[i][j] << " " << kub[i][j + 1] << " " << kub[i][j + 2] << "\n";
			}
		}
		if(i == 0 || i == 3 || i == 4){
			fout << "        - - -\n";
		}
	}
}

void read(unsigned char** kub){
	ifstream fin("rubik.in");
	char c;
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 9; j++){
			fin >> c;
			if(c == '-' || c == '|'){
				j--;
			}else if(i == 0 || i == 4 || i == 5){
				kub[i][j] = c;
			}else if(i == 1){
				kub[i][j] = c;
				fin >> c;
				kub[i][j + 1] = c;
				fin >> c;
				kub[i][j + 2] = c;
				fin >> c;
				fin >> c;
				kub[i + 1][j] = c;
				fin >> c;
				kub[i + 1][j + 1] = c;
				fin >> c;
				kub[i + 1][j + 2] = c;
				fin >> c;
				fin >> c;
				kub[i + 2][j] = c;
				fin >> c;
				kub[i + 2][j + 1] = c;
				fin >> c;
				kub[i + 2][j + 2] = c;
				fin >> c;
				kub[i][j + 3] = c;
				fin >> c;
				kub[i][j + 4] = c;
				fin >> c;
				kub[i][j + 5] = c;
				fin >> c;
				fin >> c;
				kub[i + 1][j + 3] = c;
				fin >> c;
				kub[i + 1][j + 4] = c;
				fin >> c;
				kub[i + 1][j + 5] = c;
				fin >> c;
				fin >> c;
				kub[i + 2][j + 3] = c;
				fin >> c;
				kub[i + 2][j + 4] = c;
				fin >> c;
				kub[i + 2][j + 5] = c;
				fin >> c;
				kub[i][j + 6] = c;
				fin >> c;
				kub[i][j + 7] = c;
				fin >> c;
				kub[i][j + 8] = c;
				fin >> c;
				fin >> c;
				kub[i + 1][j + 6] = c;
				fin >> c;
				kub[i + 1][j + 7] = c;
				fin >> c;
				kub[i + 1][j + 8] = c;
				fin >> c;
				fin >> c;
				kub[i + 2][j + 6] = c;
				fin >> c;
				kub[i + 2][j + 7] = c;
				fin >> c;
				kub[i + 2][j + 8] = c;
				i += 2;
				break;
			}
		}
	}
}

void scrol(unsigned char** kub){
	int count = rand() % 1000 + 200;
	//cout << count << "\n";
	for(int i = 0; i < count; i++){
		int now = rand() % 12;
		//cout << now << " ";
		if(now == 0){
			YR(kub);
		}else if(now == 1){
			YL(kub);
		}else if(now == 2){
			RR(kub);
		}else if(now == 3){
			RL(kub);
		}else if(now == 4){
			GR(kub);
		}else if(now == 5){
			GL(kub);
		}else if(now == 6){
			OR(kub);
		}else if(now == 7){
			OL(kub);
		}else if(now == 8){
			WR(kub);
		}else if(now == 9){
			WL(kub);
		}else if(now == 10){
			BR(kub);
		}else if(now == 11){
			BL(kub);
		}
	}
}

void goodw(unsigned char** kub, int a){
	while(kub[4][a] == 'w'){
		WR(kub);
	}
}

void findkrest(unsigned char** kub){
	for(int i = 0; i < 6; i++){
		if(i != 4){
			for(int j = 1; j < 9; j += 2){
				if(kub[i][j] == 'w'){
					if(i == 0){
						if(j == 1){
							goodw(kub, 7);
							BR(kub);
							BR(kub);
						}else if(j == 3){
							goodw(kub, 3);
							RR(kub);
							RR(kub);
						}else if(j == 5){
							goodw(kub, 5);
							OR(kub);
							OR(kub);
						}else if(j == 7){
							goodw(kub, 1);
							GR(kub);
							GR(kub);
						}
					}else if(i == 1){
						if(j == 1){
							goodw(kub, 3);
							RR(kub);
							WR(kub);
							GL(kub);
						}else if(j == 3){
							goodw(kub, 7);
							BR(kub);
						}else if(j == 5){
							goodw(kub, 1);
							GL(kub);
						}else if(j == 7){
							RL(kub);
							WR(kub);
							GL(kub);
						}
					}else if(i == 2){
						if(j == 1){
							goodw(kub, 1);
							GR(kub);
							WR(kub);
							OL(kub);
						}else if(j == 3){
							goodw(kub, 3);
							RR(kub);
						}else if(j == 5){
							goodw(kub, 5);
							OL(kub);
						}else if(j == 7){
							GL(kub);
							WR(kub);
							OL(kub);
						}
					}else if(i == 3){
						if(j == 1){
							goodw(kub, 5);
							OR(kub);
							WR(kub);
							BL(kub);
						}else if(j == 3){
							goodw(kub, 1);
							GR(kub);
						}else if(j == 5){
							goodw(kub, 7);
							BL(kub);
						}else if(j == 7){
							OL(kub);
							WR(kub);
							BL(kub);
						}
					}else if(i == 5){
						if(j == 1){
							BR(kub);
							WL(kub);
							OR(kub);
						}else if(j == 3){
							goodw(kub, 3);
							RL(kub);
						}else if(j == 5){
							goodw(kub, 5);
							OR(kub);
						}else if(j == 7){
							goodw(kub, 7);
							BL(kub);
							WL(kub);
							OR(kub);
						}
					}
				}
			}
		}
	}
}

void krest(unsigned char** kub){
	while(true){
		if(kub[4][1] == 'w' && kub[4][3] == 'w' && kub[4][5] == 'w' && kub[4][7] == 'w'){
			break;
		}else{
			findkrest(kub);
		}
	}
}

int count_edge_krest(unsigned char** kub){
	int count = 0;
	if(kub[2][4] == kub[2][7]){
		count++;
	}
	if(kub[1][4] == kub[1][7]){
		count++;
	}
	if(kub[3][4] == kub[3][7]){
		count++;
	}
	if(kub[5][4] == kub[5][1]){
		count++;
	}
	return count;
}

void edgekrest(unsigned char** kub){
	int count = count_edge_krest(kub);
	while(count < 2){
		WR(kub);
		count = count_edge_krest(kub);
	}
	if(count == 2){
		if(kub[2][4] == kub[2][7] && kub[5][4] == kub[5][1]){
			OR(kub);
			WR(kub);
			WR(kub);
			OL(kub);
			WL(kub);
			WL(kub);
			OR(kub);
		}else if(kub[1][4] == kub[1][7] && kub[3][4] == kub[3][7]){
			GR(kub);
			WR(kub);
			WR(kub);
			GL(kub);
			WL(kub);
			WL(kub);
			GR(kub);
		}else if(kub[3][4] == kub[3][7] && kub[5][4] == kub[5][1]){
			GR(kub);
			WR(kub);
			GL(kub);
			WL(kub);
			GR(kub);
		}else if(kub[3][4] == kub[3][7] && kub[2][4] == kub[2][7]){
			RR(kub);
			WR(kub);
			RL(kub);
			WL(kub);
			RR(kub);
		}else if(kub[1][4] == kub[1][7] && kub[2][4] == kub[2][7]){
			BR(kub);
			WR(kub);
			BL(kub);
			WL(kub);
			BR(kub);
		}else if(kub[1][4] == kub[1][7] && kub[5][4] == kub[5][1]){
			OR(kub);
			WR(kub);
			OL(kub);
			WL(kub);
			OR(kub);
		}
	}
}

void cornerwhile(unsigned char** kub, int var){
	if(var == 0){
		while(kub[4][0] != 'w' || kub[2][6] != 'g'){
			GR(kub);
			YR(kub);
			GL(kub);
			YL(kub);
		}
	}else if(var == 2){
		while(kub[4][2] != 'w' || kub[3][6] != 'o'){
			OR(kub);
			YR(kub);
			OL(kub);
			YL(kub);
		}
	}else if(var == 6){
		while(kub[4][6] != 'w' || kub[1][6] != 'r'){
			RR(kub);
			YR(kub);
			RL(kub);
			YL(kub);
		}
	}else{
		while(kub[4][8] != 'w' || kub[5][2] != 'b'){
			BR(kub);
			YR(kub);
			BL(kub);
			YL(kub);
		}
	}
}

void R6perebor(unsigned char** kub){
	RR(kub);
	YR(kub);
	RL(kub);
	YL(kub);
}

void G6perebor(unsigned char** kub){
	GR(kub);
	YR(kub);
	GL(kub);
	YL(kub);
}

void O6perebor(unsigned char** kub){
	OR(kub);
	YR(kub);
	OL(kub);
	YL(kub);
}

void B6perebor(unsigned char** kub){
	BR(kub);
	YR(kub);
	BL(kub);
	YL(kub);
}

void find_corner(unsigned char** kub){
	for(int i = 0; i < 6; i++){
		if(i != 4){
			for(int j = 0; j < 9; j += 2){
				if(kub[i][j] == 'w'){
					if(i == 0){
						if(j == 0){
							if(kub[1][0] == 'b'){
								cornerwhile(kub, 6);
							}else if(kub[1][0] == 'r'){
								YL(kub);
								cornerwhile(kub, 0);
							}else if(kub[1][0] == 'o'){
								YR(kub);
								cornerwhile(kub, 8);
							}else{
								YR(kub);
								YR(kub);
								cornerwhile(kub, 2);
							}
						}else if(j == 2){
							if(kub[3][2] == 'b'){
								cornerwhile(kub, 8);
							}else if(kub[3][2] == 'o'){
								YR(kub);
								cornerwhile(kub, 2);
							}else if(kub[3][2] == 'r'){
								YL(kub);
								cornerwhile(kub, 6);
							}else{
								YR(kub);
								YR(kub);
								cornerwhile(kub, 0);
							}
						}else if(j == 6){
							if(kub[2][0] == 'r'){
								cornerwhile(kub, 0);
							}else if(kub[2][0] == 'g'){
								YL(kub);
								cornerwhile(kub, 2);
							}else if(kub[2][0] == 'b'){
								YR(kub);
								cornerwhile(kub, 6);
							}else{
								YR(kub);
								YR(kub);
								cornerwhile(kub, 8);
							}
						}else if(j == 8){
							if(kub[2][2] == 'o'){
								cornerwhile(kub, 2);
							}else if(kub[2][2] == 'g'){
								YR(kub);
								cornerwhile(kub, 0);
							}else if(kub[2][2] == 'b'){
								YL(kub);
								cornerwhile(kub, 8);
							}else{
								YR(kub);
								YR(kub);
								cornerwhile(kub, 6);
							}
						}
					}else if(i == 1){
						if(j == 0){
							if(kub[0][0] == 'r'){
								cornerwhile(kub, 6);
							}else if(kub[0][0] == 'b'){
								YR(kub);
								cornerwhile(kub, 8);
							}else if(kub[0][0] == 'g'){
								YL(kub);
								cornerwhile(kub, 0);
							}else{
								YR(kub);
								YR(kub);
								cornerwhile(kub, 2);
							}
						}else if(j == 2){
							if(kub[0][6] == 'r'){
								cornerwhile(kub, 0);
							}else if(kub[0][6] == 'g'){
								YL(kub);
								cornerwhile(kub, 2);
							}else if(kub[0][6] == 'b'){
								YR(kub);
								cornerwhile(kub, 6);
							}else{
								YR(kub);
								YR(kub);
								cornerwhile(kub, 8);
							}
						}else if(j == 6){
							if(kub[4][6] == 'b'){
								cornerwhile(kub, 6);
							}else if(kub[4][6] == 'r'){
								R6perebor(kub);
								YL(kub);
								cornerwhile(kub, 0);
							}else if(kub[4][6] == 'o'){
								R6perebor(kub);
								YR(kub);
								cornerwhile(kub, 8);
							}else{
								R6perebor(kub);
								YR(kub);
								YR(kub);
								cornerwhile(kub, 2);
							}
						}else if(j == 8){
							if(kub[2][6] == 'r'){
								cornerwhile(kub, 0);
							}else if(kub[2][6] == 'g'){
								G6perebor(kub);
								YL(kub);
								cornerwhile(kub, 2);
							}else if(kub[2][6] == 'b'){
								G6perebor(kub);
								YR(kub);
								cornerwhile(kub, 6);
							}else{
								G6perebor(kub);
								YR(kub);
								YR(kub);
								cornerwhile(kub, 8);
							}
						}
					}else if(i == 2){
						if(j == 0){
							if(kub[0][6] == 'g'){
								cornerwhile(kub, 0);
							}else if(kub[0][6] == 'r'){
								YR(kub);
								cornerwhile(kub, 6);
							}else if(kub[0][6] == 'o'){
								YL(kub);
								cornerwhile(kub, 2);
							}else{
								YR(kub);
								YR(kub);
								cornerwhile(kub, 8);
							}
						}else if(j == 2){
							if(kub[0][8] == 'g'){
								cornerwhile(kub, 2);
							}else if(kub[0][8] == 'r'){
								YR(kub);
								cornerwhile(kub, 0);
							}else if(kub[0][8] == 'o'){
								YL(kub);
								cornerwhile(kub, 8);
							}else{
								YR(kub);
								YR(kub);
								cornerwhile(kub, 6);
							}
						}else if(j == 6){
							if(kub[4][0] == 'r'){
								cornerwhile(kub, 0);
							}else if(kub[4][0] == 'g'){
								G6perebor(kub);
								YL(kub);
								cornerwhile(kub, 2);
							}else if(kub[4][0] == 'b'){
								G6perebor(kub);
								YR(kub);
								cornerwhile(kub, 6);
							}else{
								G6perebor(kub);
								YR(kub);
								YR(kub);
								cornerwhile(kub, 8);
							}
						}else if(j == 8){
							if(kub[4][2] == 'o'){
								cornerwhile(kub, 2);
							}else if(kub[4][2] == 'g'){
								O6perebor(kub);
								YR(kub);
								cornerwhile(kub, 0);
							}else if(kub[4][2] == 'b'){
								O6perebor(kub);
								YL(kub);
								cornerwhile(kub, 8);
							}else{
								O6perebor(kub);
								YR(kub);
								YR(kub);
								cornerwhile(kub, 6);
							}
						}
					}else if(i == 3){
						if(j == 0){
							if(kub[2][2] == 'g'){
								cornerwhile(kub, 2);
							}else if(kub[2][2] == 'r'){
								YR(kub);
								cornerwhile(kub, 0);
							}else if(kub[2][2] == 'o'){
								YL(kub);
								cornerwhile(kub, 8);
							}else{
								YR(kub);
								YR(kub);
								cornerwhile(kub, 6);
							}
						}else if(j == 2){
							if(kub[0][2] == 'o'){
								cornerwhile(kub, 8);
							}else if(kub[0][2] == 'g'){
								YR(kub);
								cornerwhile(kub, 2);
							}else if(kub[0][2] == 'b'){
								YL(kub);
								cornerwhile(kub, 6);
							}else{
								YR(kub);
								YR(kub);
								cornerwhile(kub, 0);
							}
						}else if(j == 6){
							if(kub[2][8] == 'o'){
								cornerwhile(kub, 2);
							}else if(kub[2][8] == 'g'){
								O6perebor(kub);
								YR(kub);
								cornerwhile(kub, 0);
							}else if(kub[2][8] == 'b'){
								O6perebor(kub);
								YL(kub);
								cornerwhile(kub, 8);
							}else{
								O6perebor(kub);
								YR(kub);
								YR(kub);
								cornerwhile(kub, 6);
							}
						}else if(j == 8){
							if(kub[4][8] == 'b'){
								cornerwhile(kub, 8);
							}else if(kub[4][8] == 'o'){
								B6perebor(kub);
								YR(kub);
								cornerwhile(kub, 2);
							}else if(kub[4][8] == 'r'){
								B6perebor(kub);
								YL(kub);
								cornerwhile(kub, 6);
							}else{
								B6perebor(kub);
								YR(kub);
								YR(kub);
								cornerwhile(kub, 0);
							}
						}
					}else if(i == 5){
						if(j == 0){
							if(kub[4][6] == 'r'){
								cornerwhile(kub, 6);
							}else if(kub[4][6] == 'g'){
								R6perebor(kub);
								YL(kub);
								cornerwhile(kub, 0);
							}else if(kub[4][6] == 'b'){
								R6perebor(kub);
								YR(kub);
								cornerwhile(kub, 8);
							}else{
								R6perebor(kub);
								YR(kub);
								YR(kub);
								cornerwhile(kub, 2);
							}
						}else if(j == 2){
							if(kub[4][8] == 'o'){
								cornerwhile(kub, 8);
							}else if(kub[4][8] == 'b'){
								B6perebor(kub);
								YL(kub);
								cornerwhile(kub, 6);
							}else if(kub[4][8] == 'g'){
								B6perebor(kub);
								YR(kub);
								cornerwhile(kub, 2);
							}else{
								B6perebor(kub);
								YR(kub);
								YR(kub);
								cornerwhile(kub, 0);
							}
						}else if(j == 6){
							if(kub[1][0] == 'r'){
								cornerwhile(kub, 6);
							}else if(kub[1][0] == 'b'){
								YR(kub);
								cornerwhile(kub, 8);
							}else if(kub[1][0] == 'g'){
								YL(kub);
								cornerwhile(kub, 0);
							}else{
								YR(kub);
								YR(kub);
								cornerwhile(kub, 2);
							}
						}else if(j == 8){
							if(kub[3][2] == 'o'){
								cornerwhile(kub, 8);
							}else if(kub[3][2] == 'b'){
								YL(kub);
								cornerwhile(kub, 6);
							}else if(kub[3][2] == 'g'){
								YR(kub);
								cornerwhile(kub, 2);
							}else{
								YR(kub);
								YR(kub);
								cornerwhile(kub, 0);
							}
						}
					}
				}
			}
		}
	}
	if(kub[1][6] != 'r'){
		RR(kub);
		YR(kub);
		RL(kub);
		YL(kub);
	}else if(kub[2][6] != 'g'){
		GR(kub);
		YR(kub);
		GL(kub);
		YL(kub);
	}else if(kub[3][6] != 'o'){
		OR(kub);
		YR(kub);
		OL(kub);
		YL(kub);
	}else if(kub[5][2] != 'b'){
		BR(kub);
		YR(kub);
		BL(kub);
		YL(kub);
	}
}

void Bedge(unsigned char** kub){
	if(kub[0][1] == 'o'){
		YL(kub);
		OL(kub);
		YR(kub);
		OR(kub);
		YR(kub);
		BR(kub);
		YL(kub);
		BL(kub);
	}else{
		YR(kub);
		RR(kub);
		YL(kub);
		RL(kub);
		YL(kub);
		BL(kub);
		YR(kub);
		BR(kub);
	}
}

void Redge(unsigned char** kub){
	if(kub[0][3] == 'b'){
		YL(kub);
		BL(kub);
		YR(kub);
		BR(kub);
		YR(kub);
		RR(kub);
		YL(kub);
		RL(kub);
	}else{
		YR(kub);
		GR(kub);
		YL(kub);
		GL(kub);
		YL(kub);
		RL(kub);
		YR(kub);
		RR(kub);
	}
}

void Gedge(unsigned char** kub){
	if(kub[0][7] == 'r'){
		YL(kub);
		RL(kub);
		YR(kub);
		RR(kub);
		YR(kub);
		GR(kub);
		YL(kub);
		GL(kub);
	}else{
		YR(kub);
		OR(kub);
		YL(kub);
		OL(kub);
		YL(kub);
		GL(kub);
		YR(kub);
		GR(kub);
	}
}

void Oedge(unsigned char** kub){
	if(kub[0][5] == 'g'){
		YL(kub);
		GL(kub);
		YR(kub);
		GR(kub);
		YR(kub);
		OR(kub);
		YL(kub);
		OL(kub);
	}else{
		YR(kub);
		BR(kub);
		YL(kub);
		BL(kub);
		YL(kub);
		OL(kub);
		YR(kub);
		OR(kub);
	}
}

void find_edge(unsigned char** kub){
	for(int j = 1; j < 9; j += 2){
		if(kub[0][1] != 'y' && kub[5][7] != 'y'){
			if(kub[5][7] == 'g'){
				YR(kub);
				YR(kub);
				Gedge(kub);
			}else if(kub[5][7] == 'r'){
				YL(kub);
				Redge(kub);
			}else if(kub[5][7] == 'o'){
				YR(kub);
				Oedge(kub);
			}else{
				Bedge(kub);
			}
		}else if(kub[0][5] != 'y' && kub[3][1] != 'y'){
			if(kub[3][1] == 'g'){
				YR(kub);
				Gedge(kub);
			}else if(kub[3][1] == 'r'){
				YR(kub);
				YR(kub);
				Redge(kub);
			}else if(kub[3][1] == 'o'){
				Oedge(kub);
			}else{
				YL(kub);
				Bedge(kub);
			}
		}else if(kub[0][3] != 'y' && kub[1][1] != 'y'){
			if(kub[1][1] == 'g'){
				YL(kub);
				Gedge(kub);
			}else if(kub[1][1] == 'r'){
				Redge(kub);
			}else if(kub[1][1] == 'o'){
				YR(kub);
				YR(kub);
				Oedge(kub);
			}else{
				YR(kub);
				Bedge(kub);
			}
		}else if(kub[0][7] != 'y' && kub[2][1] != 'y'){
			if(kub[2][1] == 'g'){
				Gedge(kub);
			}else if(kub[2][1] == 'r'){
				YR(kub);
				Redge(kub);
			}else if(kub[2][1] == 'o'){
				YL(kub);
				Oedge(kub);
			}else{
				YR(kub);
				YR(kub);
				Bedge(kub);
			}
		}
	}
	if((kub[1][5] != 'r' || kub[2][3] != 'g') && kub[1][5] != 'y' && kub[2][3] != 'y'){
		GR(kub);
		YL(kub);
		GL(kub);
		YL(kub);
		RL(kub);
		YR(kub);
		RR(kub);
	}else if((kub[2][5] != 'g' || kub[3][3] != 'o') && kub[2][5] != 'y' && kub[3][3] != 'y'){
		OR(kub);
		YL(kub);
		OL(kub);
		YL(kub);
		GL(kub);
		YR(kub);
		GR(kub);
	}else if((kub[3][5] != 'o' || kub[5][5] != 'b') && kub[3][5] != 'y' && kub[5][5] != 'y'){
		BR(kub);
		YL(kub);
		BL(kub);
		YL(kub);
		OL(kub);
		YR(kub);
		OR(kub);
	}else if((kub[5][3] != 'b' || kub[1][3] != 'r') && kub[5][3] != 'y' && kub[1][3] != 'y'){
		RR(kub);
		YL(kub);
		RL(kub);
		YL(kub);
		BL(kub);
		YR(kub);
		BR(kub);
	}
}

void firstsloi(unsigned char** kub){
	while(true){
		if(kub[4][0] == 'w' && kub[4][2] == 'w' && kub[4][6] == 'w' && kub[4][8] == 'w' && kub[1][6] == 'r' && kub[1][8] == 'r' && kub[2][6] == 'g' && kub[2][8] == 'g' && kub[3][6] == 'o' && kub[3][8] == 'o' && kub[5][0] == 'b' && kub[5][2] == 'b'){
			break;
		}else{
			find_corner(kub);
		}
	}
}

void secondsloi(unsigned char** kub){
	while(true){
		if(kub[2][3] == 'g' && kub[2][5] == 'g' && kub[1][3] == 'r' && kub[1][5] == 'r' && kub[3][3] == 'o' && kub[3][5] == 'o' && kub[5][3] == 'b' && kub[5][5] == 'b'){
			break;
		}else{
			find_edge(kub);
		}
	}
}

void ykrestG(unsigned char** kub, int count){
	for(int i = 0; i < count; i++){
		GR(kub);
		OR(kub);
		YR(kub);
		OL(kub);
		YL(kub);
		GL(kub);
	}
}

void ykrestR(unsigned char** kub, int count){
	for(int i = 0; i < count; i++){
		RR(kub);
		GR(kub);
		YR(kub);
		GL(kub);
		YL(kub);
		RL(kub);
	}
}

bool ykrest(unsigned char** kub){
	if(kub[0][1] != 'y' && kub[0][3] != 'y' && kub[0][5] != 'y' && kub[0][7] != 'y'){
		ykrestR(kub, 2);
		ykrestG(kub, 1);
	}else if(kub[0][1] == 'y' && kub[0][3] == 'y' && kub[0][5] != 'y' && kub[0][7] != 'y'){
		YR(kub);
		ykrestR(kub, 2);
	}else if(kub[0][1] == 'y' && kub[0][3] != 'y' && kub[0][5] == 'y' && kub[0][7] != 'y'){
		ykrestR(kub, 2);
	}else if(kub[0][1] != 'y' && kub[0][3] != 'y' && kub[0][5] == 'y' && kub[0][7] == 'y'){
		YL(kub);
		ykrestR(kub, 2);
	}else if(kub[0][1] != 'y' && kub[0][3] == 'y' && kub[0][5] != 'y' && kub[0][7] == 'y'){
		YR(kub);
		YR(kub);
		ykrestR(kub, 2);
	}else if(kub[0][1] == 'y' && kub[0][3] != 'y' && kub[0][5] != 'y' && kub[0][7] == 'y'){
		ykrestR(kub, 1);
	}else if(kub[0][1] != 'y' && kub[0][3] == 'y' && kub[0][5] == 'y' && kub[0][7] != 'y'){
		YR(kub);
		ykrestR(kub, 1);
	}else if(kub[0][1] == 'y' && kub[0][3] == 'y' && kub[0][5] == 'y' && kub[0][7] == 'y'){
		
	}else{
		return false;
	}
	return true;
}

void vertolet(unsigned char** kub){
	OR(kub);
	YL(kub);
	YL(kub);
	OL(kub);
	OL(kub);
	YL(kub);
	OR(kub);
	OR(kub);
	YL(kub);
	OL(kub);
	OL(kub);
	YL(kub);
	YL(kub);
	OR(kub);
}

void ushki(unsigned char** kub){
	GR(kub);
	OR(kub);
	BL(kub);
	OL(kub);
	GL(kub);
	OR(kub);
	BR(kub);
	OL(kub);
}

void nos(unsigned char** kub){
	OL(kub);
	GL(kub);
	RL(kub);
	GR(kub);
	OR(kub);
	GL(kub);
	RR(kub);
	GR(kub);
}

void glazki(unsigned char** kub){
	OR(kub);
	OR(kub);
	WR(kub);
	OL(kub);
	YR(kub);
	YR(kub);
	OR(kub);
	WL(kub);
	OL(kub);
	YR(kub);
	YR(kub);
	OL(kub);
}

void triplpifpaf(unsigned char** kub){
	GR(kub);
	for(int i = 0; i < 3; i++){
		OR(kub);
		YR(kub);
		OL(kub);
		YL(kub);
	}
	GL(kub);
}

void Rriba(unsigned char** kub){
	OR(kub);
	YR(kub);
	OL(kub);
	YR(kub);
	OR(kub);
	YR(kub);
	YR(kub);
	OL(kub);
}

void Lriba(unsigned char** kub){
	RL(kub);
	YL(kub);
	RR(kub);
	YL(kub);
	RL(kub);
	YL(kub);
	YL(kub);
	RR(kub);
}

bool ycor(unsigned char** kub){
	if(kub[1][0] == 'y' && kub[1][2] == 'y' && kub[2][2] == 'y' && kub[5][8] == 'y'){
		vertolet(kub);
	}else if(kub[3][0] == 'y' && kub[1][2] == 'y' && kub[5][6] == 'y' && kub[5][8] == 'y'){
		YL(kub);
		vertolet(kub);
	}else if(kub[1][0] == 'y' && kub[2][0] == 'y' && kub[2][2] == 'y' && kub[3][2] == 'y'){
		YR(kub);
		vertolet(kub);
	}else if(kub[3][0] == 'y' && kub[3][2] == 'y' && kub[2][0] == 'y' && kub[5][6] == 'y'){
		YR(kub);
		YR(kub);
		vertolet(kub);
	}else if(kub[1][2] == 'y' && kub[3][0] == 'y' && kub[0][0] == 'y' && kub[0][2] == 'y'){
		ushki(kub);
	}else if(kub[2][2] == 'y' && kub[5][8] == 'y' && kub[0][0] == 'y' && kub[0][6] == 'y'){
		YR(kub);
		ushki(kub);
	}else if(kub[5][6] == 'y' && kub[2][0] == 'y' && kub[0][8] == 'y' && kub[0][2] == 'y'){
		YL(kub);
		ushki(kub);
	}else if(kub[3][2] == 'y' && kub[1][0] == 'y' && kub[0][8] == 'y' && kub[0][6] == 'y'){
		YR(kub);
		YR(kub);
		ushki(kub);
	}else if(kub[5][8] == 'y' && kub[1][2] == 'y' && kub[0][0] == 'y' && kub[0][8] == 'y'){
		nos(kub);
	}else if(kub[1][0] == 'y' && kub[2][2] == 'y' && kub[0][2] == 'y' && kub[0][6] == 'y'){
		YR(kub);
		nos(kub);
	}else if(kub[5][6] == 'y' && kub[3][0] == 'y' && kub[0][2] == 'y' && kub[0][6] == 'y'){
		YL(kub);
		nos(kub);
	}else if(kub[2][0] == 'y' && kub[3][2] == 'y' && kub[0][0] == 'y' && kub[0][8] == 'y'){
		YR(kub);
		YR(kub);
		nos(kub);
	}else if(kub[2][0] == 'y' && kub[2][2] == 'y' && kub[0][0] == 'y' && kub[0][2] == 'y'){
		glazki(kub);
	}else if(kub[3][0] == 'y' && kub[3][2] == 'y' && kub[0][0] == 'y' && kub[0][6] == 'y'){
		YR(kub);
		glazki(kub);
	}else if(kub[1][0] == 'y' && kub[1][2] == 'y' && kub[0][8] == 'y' && kub[0][2] == 'y'){
		YL(kub);
		glazki(kub);
	}else if(kub[5][6] == 'y' && kub[5][8] == 'y' && kub[0][6] == 'y' && kub[0][8] == 'y'){
		YR(kub);
		YR(kub);
		glazki(kub);
	}else if(kub[5][6] == 'y' && kub[5][8] == 'y' && kub[2][0] == 'y' && kub[2][2] == 'y'){
		triplpifpaf(kub);
	}else if(kub[1][0] == 'y' && kub[1][2] == 'y' && kub[3][0] == 'y' && kub[3][2] == 'y'){
		YR(kub);
		triplpifpaf(kub);
	}else if(kub[0][6] == 'y' && kub[2][2] == 'y' && kub[3][2] == 'y' && kub[5][6] == 'y'){
		Rriba(kub);
	}else if(kub[0][8] == 'y' && kub[1][2] == 'y' && kub[3][2] == 'y' && kub[5][6] == 'y'){
		YR(kub);
		Rriba(kub);
	}else if(kub[0][0] == 'y' && kub[2][2] == 'y' && kub[3][2] == 'y' && kub[1][2] == 'y'){
		YL(kub);
		Rriba(kub);
	}else if(kub[0][2] == 'y' && kub[2][2] == 'y' && kub[1][2] == 'y' && kub[5][6] == 'y'){
		YR(kub);
		YR(kub);
		Rriba(kub);
	}else if(kub[0][8] == 'y' && kub[2][0] == 'y' && kub[1][0] == 'y' && kub[5][8] == 'y'){
		Lriba(kub);
	}else if(kub[0][2] == 'y' && kub[2][0] == 'y' && kub[1][0] == 'y' && kub[3][0] == 'y'){
		YR(kub);
		Lriba(kub);
	}else if(kub[0][6] == 'y' && kub[3][0] == 'y' && kub[1][0] == 'y' && kub[5][8] == 'y'){
		YL(kub);
		Lriba(kub);
	}else if(kub[0][0] == 'y' && kub[2][0] == 'y' && kub[3][0] == 'y' && kub[5][8] == 'y'){
		YR(kub);
		YR(kub);
		Lriba(kub);
	}else if(kub[0][6] == 'y' && kub[0][2] == 'y' && kub[0][0] == 'y' && kub[0][8] == 'y'){
		
	}else{
		return false;
	}
	return true;
}

void havepair(unsigned char** kub){
	GR(kub);
	YR(kub);
	GL(kub);
	YL(kub);
	GL(kub);
	RR(kub);
	GR(kub);
	GR(kub);
	YL(kub);
	GL(kub);
	YL(kub);
	GR(kub);
	YR(kub);
	GL(kub);
	RL(kub);
}

void notpair(unsigned char** kub){
	RR(kub);
	GR(kub);
	YL(kub);
	GL(kub);
	YL(kub);
	GR(kub);
	YR(kub);
	GL(kub);
	RL(kub);
	GR(kub);
	YR(kub);
	GL(kub);
	YL(kub);
	GL(kub);
	RR(kub);
	GR(kub);
	RL(kub);
}

void lastcor(unsigned char** kub){
	if(kub[5][6] == kub[5][8] && kub[1][0] != kub[1][2]){
		havepair(kub);
	}else if(kub[1][0] == kub[1][2] && kub[2][0] != kub[2][2]){
		YR(kub);
		havepair(kub);
	}else if(kub[3][0] == kub[3][2] && kub[2][0] != kub[2][2]){
		YL(kub);
		havepair(kub);
	}else if(kub[2][0] == kub[2][2] && kub[1][0] != kub[1][2]){
		YR(kub);
		YR(kub);
		havepair(kub);
	}else if(kub[1][0] == kub[1][2] && kub[3][0] == kub[3][2]){
		
	}else{
		notpair(kub);
	}
}

void lastgl(unsigned char** kub){
	RL(kub);
	YR(kub);
	RL(kub);
	YL(kub);
	RL(kub);
	YL(kub);
	RL(kub);
	YR(kub);
	RR(kub);
	YR(kub);
	RR(kub);
	RR(kub);
}

void lastgr(unsigned char** kub){
	OR(kub);
	YL(kub);
	OR(kub);
	YR(kub);
	OR(kub);
	YR(kub);
	OR(kub);
	YL(kub);
	OL(kub);
	YL(kub);
	OL(kub);
	OL(kub);
}

void lastol(unsigned char** kub){
	GL(kub);
	YR(kub);
	GL(kub);
	YL(kub);
	GL(kub);
	YL(kub);
	GL(kub);
	YR(kub);
	GR(kub);
	YR(kub);
	GR(kub);
	GR(kub);
}

void lastor(unsigned char** kub){
	BR(kub);
	YL(kub);
	BR(kub);
	YR(kub);
	BR(kub);
	YR(kub);
	BR(kub);
	YL(kub);
	BL(kub);
	YL(kub);
	BL(kub);
	BL(kub);
}

void lastbl(unsigned char** kub){
	OL(kub);
	YR(kub);
	OL(kub);
	YL(kub);
	OL(kub);
	YL(kub);
	OL(kub);
	YR(kub);
	OR(kub);
	YR(kub);
	OR(kub);
	OR(kub);
}

void lastbr(unsigned char** kub){
	RR(kub);
	YL(kub);
	RR(kub);
	YR(kub);
	RR(kub);
	YR(kub);
	RR(kub);
	YL(kub);
	RL(kub);
	YL(kub);
	RL(kub);
	RL(kub);
}

void lastrl(unsigned char** kub){
	BL(kub);
	YR(kub);
	BL(kub);
	YL(kub);
	BL(kub);
	YL(kub);
	BL(kub);
	YR(kub);
	BR(kub);
	YR(kub);
	BR(kub);
	BR(kub);
}

void lastrr(unsigned char** kub){
	GR(kub);
	YL(kub);
	GR(kub);
	YR(kub);
	GR(kub);
	YR(kub);
	GR(kub);
	YL(kub);
	GL(kub);
	YL(kub);
	GL(kub);
	GL(kub);
}

bool lastedge(unsigned char** kub){
	if(kub[2][1] == 'r' && kub[1][1] == 'o' && kub[3][1] == 'g' && kub[5][7] == 'b'){
		lastgl(kub);
	}else if(kub[2][1] == 'o' && kub[1][1] == 'g' && kub[3][1] == 'r' && kub[5][7] == 'b'){
		lastgr(kub);
	}else if(kub[2][1] == 'b' && kub[1][1] == 'r' && kub[3][1] == 'g' && kub[5][7] == 'o'){
		lastol(kub);
	}else if(kub[2][1] == 'o' && kub[1][1] == 'r' && kub[3][1] == 'b' && kub[5][7] == 'g'){
		lastor(kub);
	}else if(kub[2][1] == 'g' && kub[1][1] == 'o' && kub[3][1] == 'b' && kub[5][7] == 'r'){
		lastbr(kub);
	}else if(kub[2][1] == 'g' && kub[1][1] == 'b' && kub[3][1] == 'r' && kub[5][7] == 'o'){
		lastbl(kub);
	}else if(kub[2][1] == 'r' && kub[1][1] == 'b' && kub[3][1] == 'o' && kub[5][7] == 'g'){
		lastrl(kub);
	}else if(kub[2][1] == 'b' && kub[1][1] == 'g' && kub[3][1] == 'o' && kub[5][7] == 'r'){
		lastrr(kub);
	}else if(kub[1][1] == 'o' && kub[2][1] == 'b' && kub[3][1] == 'r' && kub[5][7] == 'g'){
		lastol(kub);
		lastgl(kub);
	}else if(kub[1][1] == 'g' && kub[2][1] == 'r' && kub[3][1] == 'b' && kub[5][7] == 'o'){
		lastor(kub);
		lastgr(kub);
	}else if(kub[1][1] == 'b' && kub[2][1] == 'o' && kub[3][1] == 'g' && kub[5][7] == 'r'){
		lastol(kub);
		lastbl(kub);
	}else if(kub[1][1] == 'r' && kub[2][1] == 'g' && kub[3][1] == 'o' && kub[5][7] == 'b'){
		
	}else{
		return false;
	}
	return true;
}

bool find(unsigned char** kub){
	krest(kub);
	edgekrest(kub);
	firstsloi(kub);
	secondsloi(kub);
	bool flag = ykrest(kub);
	if(flag == true){
		flag = ycor(kub);
		if(flag == true){
			lastcor(kub);
			while(kub[2][0] != 'g'){
				YR(kub);
			}
			flag = lastedge(kub);
		}
	}
	//show(kub);
	return flag;
}

void myspin(unsigned char** kub){
	cout << "Choose a color from the list (r, b, o, g, w, y), only small characters and choose the direction of rotation (r, l)." << endl;
	cout << "For example: rr, bl, or, gr, yl, wl" << endl;
	cout << "if you're done, enter only it '.'" << endl;
	char c, d;
	while(true){
		cin >> c;
		if(c == '.'){
			break;
		}else{
			cin >> d;
			if(c == 'r'){
				if(d == 'r'){
					RR(kub);
				}else if(d == 'l'){
					RL(kub);
				}
			}else if(c == 'b'){
				if(d == 'r'){
					BR(kub);
				}else if(d == 'l'){
					BL(kub);
				}
			}else if(c == 'g'){
				if(d == 'r'){
					GR(kub);
				}else if(d == 'l'){
					GL(kub);
				}
			}else if(c == 'o'){
				if(d == 'r'){
					OR(kub);
				}else if(d == 'l'){
					OL(kub);
				}
			}else if(c == 'y'){
				if(d == 'r'){
					YR(kub);
				}else if(d == 'l'){
					YL(kub);
				}
			}else if(c == 'w'){
				if(d == 'r'){
					WR(kub);
				}else if(d == 'l'){
					WL(kub);
				}
			}else{
				cout << "Bad color." << endl;
			}
			if(d != 'r' && d != 'l'){
				cout << "Bad rotation." << endl;
			}
			
		}
		show(kub);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////как cube.cpp, но здесь куб решается, а не находится его решение с сохранением данным нам кубом. В cube.cpp мы находим решение для нашего куба и возвращем его в положение начальное(до того как начали искать решение). Всё выше описанное влияет только на функцию find.
int main(){
	int i, j;
	unsigned char** kub = new unsigned char* [6];
	for(i = 0; i < 6; i++){
		kub[i] = new unsigned char [9];
		for(j = 0; j < 9; j++){
			if(i == 0){
				kub[i][j] = 'y';
			}else if(i == 1){
				kub[i][j] = 'r';
			}else if(i == 2){
				kub[i][j] = 'g';
			}else if(i == 3){
				kub[i][j] = 'o';
			}else if(i == 4){
				kub[i][j] = 'w';
			}else{
				kub[i][j] = 'b';
			}
		}
	}
	int var;
	bool flag = true;
	do{
		var = menu();
		if(var == 1){
			int znach;
			znach = secmenu();
			if(znach == 1){
				save(kub);
			}else{
				read(kub);
			}
		}else if(var == 2){
			flag = check(kub);
			if(flag == false){
				cout << "VERY BBAAAaaadd KKUUUuuubb." << endl;
			}else{
				flag = find(kub);
				if(flag == true){
					cout << "OK" << endl;
				}else{
					cout << "BBAAAaaadd KKUUUuuubb." << endl;
				}
			}
		}else if(var == 3){
			show(kub);
		}else if(var == 4){
			myspin(kub);
		}else if(var == 5){
			scrol(kub);
		}else if(var == 6){
			flag = check(kub);
			if(flag == true){
				flag = find(kub);
				if(flag == true){
					cout << "GGWP." << endl;
				}else{
					cout << "Bad angle or edge." << endl;
				}
			}else{
				cout << "Take new kub." << endl;
			}
		}else if(var == 8){
			int count = 0;
			for(i = 0; i < 100000; i++){
				cout << i << endl;
				read(kub);
				scrol(kub);
				find(kub);
				for(j = 0; j < 9; j++){
					if(kub[0][j] != 'y' || kub[1][j] != 'r' || kub[2][j] != 'g' || kub[3][j] != 'o' || kub[4][j] != 'w' || kub[5][j] != 'b'){
						count++;
						break;
					}
				}
			}
			cout << "\n\nResult = " << count << "\n\n";
		}
		if(var != 7){
			system("pause");
		}
	}while(var != 7);
	delete kub;
	return 0;
}
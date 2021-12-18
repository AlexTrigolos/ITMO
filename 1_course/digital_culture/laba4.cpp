#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int comparison(string::value_type letter1, string::value_type letter2)
{
	if (letter1 == letter2)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int edit_distance(string const& from, string const& to)
{
	int** Table = new int*[from.length() + 1];
	for (int i = 0; i < from.length() + 1; i++)
	{
		Table[i] = new int[to.length() + 1]; //создаём двумерный динамический массив, где кол-во строк, это длина слова 
	}										 // c потенциальной ошибкой + 1, а кол-во столбцов, это длина слова из словаря + 1
	Table[0][0] = 0; 

	for (int j = 0; j != to.length(); ++j) 
	{
		Table[0][j + 1] = Table[0][j] + 1; //заполняем первую строку последовательностью целых чисел начиная с 0
	}

	for (int i = 0; i != from.length(); ++i) 
	{
		Table[i + 1][0] = Table[i][0] + 1;

		for (int j = 0; j != to.length(); ++j)  // Здесь реализован алгоритм Левенштейна, на вставку пробела я проверяю в основной функции
		{
			Table[i + 1][j + 1] = min(min(Table[i + 1][j] + 1, Table[i][j + 1] + 1), Table[i][j] + comparison(from[i], to[j]));
		}
	}

	int m = Table[from.length()][to.length()];
	for (int i = 0; i < from.length() + 1; i++)
	{
		delete[] Table[i]; //удаляем динамический массив
	}
	return m;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); // это чтобы быстрее считывался текст
	setlocale(LC_ALL, "RU");
	ifstream fin;
	ofstream fout;
	fin.open("brain092.txt");
	fout.open("help.txt");
	char text; // вспомогательная переменная
	while (fin.get(text))
	{
		if (text == ',' or text == '!' or text == '?' or text == ';' or text == ':' or text == '.' or text == '!' or text == '«' or text == '»' or text == '(' or text == ')')
		{
			continue;
		}
		text = tolower(text);
		fout << text; // это я удалил знаки препинания, понизил регистр и записал их в текстовый файл help
	}
	fin.close();
	fout.close();

	////////////////////////////////////////////Выполнена предобработка текста/////////////////////////////////////////////////////////
	fin.open("help.txt");
	int i = 0 , f; // вспомогательная переменная
	bool flag; // вспомогательная переменная
	int slovaform = 0;        // тут будет хранится общее количество разных словаформ
	int coincidences = 0;     // тут будет хранится общее количество совпадений со словарём
	string processed_text[2000];           // в этом массиве хранится обработанный текст
	string unique_word[2000];              // в этом массиве хранятся уникальные словаформы
	while (fin >> processed_text[i])
	{
		flag = false;
		for (int j = 0; j < i; j++)
		{
			if (processed_text[i] == processed_text[j])
			{
				flag = true;
				continue;
			}
		}
		if (!flag)
		{
			unique_word[slovaform] = processed_text[i];
			slovaform++;
		}
		i++;
	} // это алгоритм выявления словаформ и  различных словаформ
	cout << /*"Кол-во словоформ в тексте - " <<*/ i << endl;
	cout << /*"\nКол-во разных словоформ в тексте - " <<*/ slovaform << endl;
	fin.close();
	f = i;
	fin.open("dict1.txt");
	string dictionary[4774]; // в этом массиве будет хранится слово из словаря
	int frequence[4774]; // в этом массиве будет хранится частота этих слов
	string problems[100]; // в этом массиве будут храниться неправильные слова
	int number[100];
	//int number[100]; // в этом массиве будут храниться индексы неправильных слов в тексте
	i = 0;
	int k = 0; // счётчик количества потенциальных ошибок
	while (fin >> dictionary[i])
	{
		fin >> frequence[i];
		i++;
	}
	fin.close();

	for (int i = 0; i < slovaform; i++)
	{
		for (int j = 0; j < 4774; j++)
		{
			if (unique_word[i] == dictionary[j])
			{
				coincidences++;
				break;
			}
		}
	}
	for (int i = 0; i < 2000; i++)
	{
		flag = false;
		for (int j = 0; j < 4774; j++)
		{
			if (processed_text[i] == dictionary[j])
			{
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			number[k] = i;
			problems[k] = processed_text[i];
			k++;
		}
	}
	cout << /*"Кол-во разных словоформ из моего текста, присутствующих в словаре - " <<*/ coincidences << endl;


	////////////////////////////////////////////Выполнены первичные расчёты/////////////////////////////////////////////////////////

	cout << /*"Кол-во потенциальных ошибок - " <<*/ slovaform - coincidences << endl;

	for (int i = 0; i < k; i++)
	{
		int min = edit_distance(problems[0], dictionary[0]);   //просто инициализирую мин
		int index = 0;
		flag = true;
		for (int j = 0; j < 4774; j++)                             // здесь я нахожу редакторское расстояние между словом с ошибкой
		{														   // и всеми словами из словаря 
			if (min > edit_distance(problems[i], dictionary[j]))   // нахожу минимальное расстояние, если минимальное расстояние снова 
			{													   // встречается, то уже сравниваю частоту появления
				min = edit_distance(problems[i], dictionary[j]);
				index = j;
			}

			if (min == edit_distance(problems[i], dictionary[j]))
			{
				if (frequence[index] <= frequence[j])
				{
					min = edit_distance(problems[i], dictionary[j]);
					index = j;
				}
			}
		}

		bool flag1 = false, flag2 = false;
		for (int c = 1; c <= problems[i].size(); c++) // я отдаю приоритет вставке пробела, то есть, если слово можно исправить,
		{											  // вставив пробел, то будет вставлен пробел, даже если расстояние Левейштейна будет равно 1
			flag1 = false, flag2 = false;
			string str1, str2, str;
			str = problems[i];						  // здесь я вставляю пробел во все места и ищу есть ли получившиеся слова в словаре
			int index1 = 0, index2 = 0;
			str.insert(c, " ");
			str1 = str.substr(0, c);
			str2 = str.substr(c + 1, str.size());
			for (int n = 0; n < 4774; n++)
			{
				if (str1 == dictionary[n])
				{
					flag1 = true;
					index1 = n;
				}
				if (str2 == dictionary[n])
				{
					flag2 = true;
					index2 = n;
				}
				if (flag1 and flag2)
				{
					break;
				}
			}
			if (flag1 and flag2)
			{
				cout << problems[i] << " " << dictionary[index1] << " " << dictionary[index2] << " - 1" << endl;
				problems[i] = dictionary[index1] + " " + dictionary[index2];
				break;
			}
		}

		if (!(flag1 and flag2))                            // вывожу неправильное слово, затем правильное и редакторское расстояние
		{
			if (min > 2)
			{
				cout << problems[i] << "  не найдено - >2" << endl;
			}
			else
			{
				cout << problems[i] << " " << dictionary[index] << " - " << min << endl;
				problems[i] = dictionary[index];
			}
		}
	}

	/////////////////////////////////////////////Поиск и исправление ошибок//////////////////////////////////////////////////

	fout.open("help.txt");
	k = 0;
	for (int h = 0; h < 2000; h++)
	{
		if (h == number[k])
		{
			fout << problems[k] << " "; // заменяем неправильные слова на правильные и вывожу исправленный текст в файл help
			k++;
		}
		else
		{
			fout << processed_text[h] << " ";
		}
	}
	fout.close();

	fin.open("help.txt");
	i = 0; 
	slovaform = 0;        // тут будет хранится общее количество словаформ в исправленном тексте
	coincidences = 0;     // тут будет хранится общее количество совпадений со словарём в исправленном тексте
	string processed_text2[2000];           // в этом массиве хранится исправленный текст
	string unique_word2[2000];              // в этом массиве хранятся уникальные словаформы исправленного текста
	while (fin >> processed_text2[i])
	{
		flag = false;
		for (int j = 0; j < i; j++)
		{
			if (processed_text2[i] == processed_text2[j])
			{
				flag = true;
				continue;
			}
		}
		if (!flag)
		{
			unique_word2[slovaform] = processed_text2[i];
			slovaform++;
		}
		i++;
	} // это алгоритм выявления словаформ и  различных словаформ в исправленном тексте
	cout << /*"\n\nКол-во словоформ в  исправленном тексте - " <<*/ i << endl;
	cout << /*"\nКол-во разных словоформ в исправленном тексте - " <<*/ slovaform << endl;
	for (int i = 0; i < slovaform; i++)
	{
		flag = false;
		for (int j = 0; j < 4774; j++)
		{
			if (unique_word2[i] == dictionary[j])
			{
				flag = true;
				coincidences++;
				break;
			}
		}
	}
	cout << /*"Кол-во разных словоформ из исправленного текста, присутствующих в словаре - " <<*/ coincidences << endl;
	fin.close();
}


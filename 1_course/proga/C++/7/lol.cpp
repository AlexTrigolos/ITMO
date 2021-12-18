#include <iostream>

using namespace std;

void menu(){
	system("cls");
	cout << "Enter number." << endl;
	cout << "1. Add or delete end." << endl;
	cout << "2. Add or delete start." << endl;
	cout << "3. Add or delete your place(iterator)." << endl;
	cout << "4. Access start or end." << endl;
	cout << "5. Access for index." << endl;
	cout << "6. Change capacity." << endl;
	cout << "7. Cout All." << endl;
	cout << "8. Exit." << endl;
}

void check(int& point, const int capacity){
	if(point < 0){
		point = capacity - 1;
	}
	if(point == capacity){
		point = 0;
	}
}

template <typename T>
void pushend(T* Arr, const T element, int& start, int& end, int& size, const int capacity){
	if(end == start && size != 0){
		start++;
		check(start, capacity);
	}
	Arr[end] = element;
	end++;
	check(end, capacity);
	if(size < capacity){
		size++;
	}
}

void deleteend(const int capacity, int& end, int& size){
	if(size > 0){
		end--;
		check(end, capacity);
		size--;
	}else{
		cout << "Empty.\n";
	}
}

template <typename T>
void pushstart(T* Arr, const T element, int& start, int& size, const int capacity, int& end){
	if(start == end && size != 0){
		end--;
		check(end, capacity);
	}
	start--;
	check(start, capacity);
	Arr[start] = element;
	if(size < capacity){
		size++;
	}
}

void deletestart(const int capacity, int& start, int& size){
	if(size > 0){
		start++;
		check(start, capacity);
		size--;
	}else{
		cout << "Empty.\n";
	}
}

template <typename T>
void print(const T* Arr, const int start, const int end, const int capacity, const int size){
	if(size > 0){
		int i = 0;
		while(i < size){
			cout << Arr[(i + start) % capacity] << " ";
			i++;
		}
		cout << endl;
	}else{
		cout << "Empty." << endl;
	}
}

void secmenu(){
	cout << "1. Add." << endl;
	cout << "2. Delete." << endl;
}

template <typename T>
void pushiterator(T* Arr, T element, int& start, int& end, int& size, const int capacity, const int iterator){
	T k;
	int i;
	if(size == capacity && start == end){
		int j = 0;
		while(j < capacity){
			k = Arr[(j + start + iterator) % capacity];
			Arr[(j + start + iterator) % capacity] = element;
			element = k;
			j++;
		}
	}else{
		for(i = start + iterator; i % capacity != end; i++){
			k = Arr[i % capacity];
			Arr[i % capacity] = element;
			element = k;
		}
		if(size != capacity){
			Arr[end] = element;
			end++;
			if(end == capacity){
				end = 0;
			}
			size++;
		}
	}
}

template <typename T>
void deleteiterator(T* Arr, const int capacity, int& start, int& size, const int iterator, int& end){
	end--;
	if(end == -1){
		end = capacity - 1;
	}
	for(int i = start + iterator; i % capacity != end; i++){
		Arr[i % capacity] = Arr[(i + 1) % capacity];
	}
	size--;
}

template <typename T>
void take(const T* Arr, int iterator){
	cout << Arr[iterator] << endl;
}

template <typename T>
void take(const T* Arr, const int iterator, const int start, const int capacity){
	cout << Arr[(start + iterator) % capacity] << endl;
}

template <typename T>
T* changecapacity(const int now, const T* Arr, int& start, int& end, int& old, int& size){
	T* Arr2 = (T*)malloc(now * sizeof(T));
	int k = 0;
	for(int i = start; (i - start) != size && k < now; i++, k++){
		Arr2[k] = Arr[i % old];
	}
	start = 0;
	end = k % now;
	if(now < old){
		size = now;
	}
	delete[] Arr;
	old = now;
	return Arr2;
}

int main(){
	int iterator, var, num, start = 0, end = 0, size = 0, capacity = 5;
	int* Arr = (int*)malloc(5 * sizeof(int));
	do{
		menu();
		cin >> var;
		switch(var){
			case 1:
				secmenu();
				cin >> num;
				if(num == 1){
					cout << "Number" << endl;
					cin >> num;
					pushend(Arr, num, start, end, size, capacity);
				}else if(num == 2){
					deleteend(capacity, end, size);
				}
				break;
			case 2:
				secmenu();
				cin >> num;
				if(num == 1){
					cout << "Number" << endl;
					cin >> num;
					pushstart(Arr, num, start, size, capacity, end);
				}else if(num == 2){
					deletestart(capacity, start, size);
				}
				break;
			case 3:
				secmenu();
				cin >> num;
				cout << "Give iterator." << endl;
				cin >> iterator;
				if(num == 1){
					if((size < capacity && iterator < size + 1 && iterator >= 0) || (size == capacity && iterator < size && iterator >= 0)){
						cout << "Number" << endl;
						cin >> num;
						pushiterator(Arr, num, start, end, size, capacity, iterator);
					}else{
						cout << "ERROR Number" << endl;
					}
				}else if(num == 2){
					if(size > 0 && iterator >= 0 && iterator < size){
						deleteiterator(Arr, capacity, start, size, iterator, end);
					}else{
						cout << "ERROR Number" << endl;
					}
				}
				break;
			case 4:
				cout << "1. Start." << endl;
				cout << "2. End." << endl;
				cin >> num;
				if(num == 1){
					take(Arr, start);
				}else if(num == 2){
					if(end != 0){
						take(Arr, end - 1);
					}else{
						take(Arr, capacity - 1);
					}
				}
				break;
			case 5:
				cout << "Iterator" << endl;
				cin >> iterator;
				if(iterator >= 0 && iterator < size){
					take(Arr, iterator, start, capacity);
				}else{
					cout << "ERROR" << endl;
				}
				break;
			case 6:
				cout << "New capacity." << endl;
				cin >> num;
				if(num > 0){
					Arr = changecapacity(num, Arr, start, end, capacity, size);
				}else{
					cout << "Error\n";
				}
				break;
			case 7:
				print(Arr, start, end, capacity, size);
				break;
		}
		print(Arr, start, end, capacity, size);
		if(var != 8){
			system("pause");
		}
	}while(var != 8);
	return 0;
}
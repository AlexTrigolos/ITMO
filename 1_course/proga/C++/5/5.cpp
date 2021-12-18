#include <iostream>

using namespace std;

template <typename T>
class Queue{
private:
	T *Mas;
	int size;
	int max;
	T first;
	T last;
public:
	Queue(int = 10);
	void push(const T  );
	void pop();
	void printStack();
};
 
class Exception
{
private:
	string m_error;
public:
	Exception(string error)
		: m_error(error)
	{}
	const char* getError() {
		return m_error.c_str();
	}
};
 
int main(){
	int a;
	int b;
	cout << "Enter integer a = , b = .\n";
	cin >> a >> b;
	swap(a, b);
	cout << "swap" << endl;
	cout << "a = " << a << ", b = " << b << ".\n";
	cout << "Enter double c = , d = .\n";
	double c;
	double d;
	cin >> c >> d;
	swap(c, d);
	cout << "swap" << endl;
	cout << "c = " << c << ", d = " << d << ".\n";
	int N;
	cout << "Give N\n";
	cin >> N;
	Queue <int> myqueue(N);
	int var;
	int temp;
	system("pause");
	do{
		system("cls");
		cout << "1. Push." << endl;
		cout << "2. Pop." << endl;
		cout << "3. List." << endl;
		cout << "4. Exit." << endl;
		cin >> var;
		if(var == 1){
			cout << "Give me - ";
			cin >> temp;
			try{
				myqueue.push(temp);
			}
			catch (Exception& exception){
				cout << exception.getError() << endl;
			}
		}else if(var == 2){
			try{
				myqueue.pop();
			}
			catch (Exception& exception){
				cout << exception.getError() << endl;
			}
		}else if(var == 3){
			myqueue.printStack();
		}
		if(var != 4){
			system("pause");
		}
	}while(var != 4);
	return 0;
}

template <typename T>
Queue<T>::Queue(int s){
	max = (s > 0) ? s: 10;
	Mas = new T[max];
	first = -1;
	size = 0;
	last = -1;
}
 
template <typename T>
void Queue<T>::push(const T value){
	if (size == max)
	{
		throw Exception("Queue is full");
	}
	if(first == -1)
		first = 0;
	size++;
	last++;
	if(last == max)
		last = 0;
	Mas[last] = value;
	cout << "GOOD\n";    
}
 
template <typename T>
void Queue<T>::pop(){
	if (size == 0){
		throw Exception("Queue is empty");
	}
	Mas[first] = 0;
	first++;
	if(first == max)
		first = 0;
	size--;
	cout << "GOOD\n";
}

template <typename T>
void Queue<T>::printStack(){
	for(int i = 0; i < size; i++){
		if(i + first < max){
			cout << Mas[i + first] << " ";
		}else{
			cout << Mas[(i + first) % max] << " ";
		}
	}
	cout << endl;
}
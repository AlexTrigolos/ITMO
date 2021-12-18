#include <iostream>
#include <vector>

using namespace std;

bool Numbers(int x){
    return x > 0;
}

bool Increase(int first, int second){
    return first > second;
}

//1
template <typename T, typename Function>
bool all_of(const T& begin, const T& end, Function function){
    for (T iterator = begin; iterator != end; iterator++) {
        if (function(*iterator) == false) {
            return false;
        }
    }
    return true;
}

//5
template <typename T, typename Function>
bool is_sorted(const T& begin, const T& end, Function function){
    for (T iterator = begin + 1; iterator != end; iterator++) {
        if (!function(*iterator, *(iterator - 1))) {
            return false;
        }
    }
    return true;
}

//8
template <typename T, typename Element>
Element find_backward(const T& begin, const T& end, Element element){
    for (T iterator = end - 1; iterator != begin; iterator--) {
        if (*iterator == element) {
            return *iterator;
        }
    }
    return *end;
}

template <typename T>
void printArray(const T& begin, const T& end){
    for (T iter = begin; iter != end; iter++) {
        cout << *iter << " ";
    }
    cout << endl;
}

int main(){
    vector<int> v = {1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "ALL_OF = " << (all_of(v.begin(), v.end(), Numbers) ? "True" : "False") << endl;
    cout << "IS_SORTED = " << (is_sorted(v.begin(), v.end(), Increase) ? "True" : "False") << endl;
    cout << "FIND_BACKWARD(9) = " << find_backward(v.begin(), v.end(), 9) << endl;
	printArray(v.begin(), v.end());
    return 0;
}
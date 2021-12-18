#include <iostream>
#include "1.h"

using namespace std;

//все действия выполняются дважды. первый раз через указатели, второй через ссылки.
int main(int argc, char** argv){
	
	cout << "Enter two number\n"; 
	double first, second;
	cin >> first >> second;
	double *my1 = &first, *my2 = &second;
	func1(my1, my2);
	double &my3 = first, &my4 = second;
	func1(my3, my4);
	cout << "\n";
	
	cout << "Enter one number\n";
	double now;
	cin >> now;
	double *my5 = &now, &my6 = now;
	func3(my5);
	func3(my6);
	cout << "\n";
	
	cout << "Input a and b for z = a + b * i\n";
	double x, y;
	cin >> x >> y;
	double *x1 = &x, *y1 = &y, &x2 = x, &y2 = y;
	func5(x1, y1);
	func5(x2, y2);
	cout << "\n";
	cout << "\n"; 	
	
	cout << "Input matrix\n";
	cout << "a b c" << "\n";
	cout << "d e f" << "\n";
	cout << "g h i" << "\n";
	cout << "And input real number\n";
	double a, b, c, d, e, f, g, h, i, k;
	cin >> a >> b >> c >> d >> e >> f >> g >> h >> i >> k;
	double *a1 = &a, *b1 = &b, &a2 = a, &b2 = b, *c1 = &c, &c2 = c, *d1 = &d, &d2 = d, *e1 = &e, &e2 = e, *f1 = &f, &f2 = f, *g1 = &g, &g2 = g, *h1 = &h, &h2 = h, *i1 = &i, &i2 = i, *k1 = &k, &k2 = k;
	cout << "\n";
	func7(a1, b1, c1, d1, e1, f1, g1, h1, i1, k1);
	cout << "\n";
	func7(a2, b2, c2, d2, e2, f2, g2, h2, i2, k2);
	
	return 0;
}

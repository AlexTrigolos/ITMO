#pragma once
#include <iostream>

using namespace std;

void func1(double* x, double* y){
	*x += *y;
	cout << *x << "\n";
}

void func1(double& x, double& y){
	x += y;
	cout << x << "\n";
}

void func3(double* x){
	*x *= -1;
	cout << *x << "\n";
}

void func3(double& x){
	x *= -1;
	cout << x << "\n";
}

void func5(double* x, double* y){
	*y *= -1;
	cout << "z* = " << *x << " + " << *y << " * i" << "\n";
}

void func5(double& x, double& y){
	y *= -1;
	cout << "z = " << x << " + " << y << " * i" << "\n";
}

void func7(double* a, double* b, double* c, double* d, double* e, double* f, double* g, double* h, double* i, double* k){
	*a *= *k;
	*b *= *k;
	*c *= *k;
	*d *= *k;
	*e *= *k;
	*f *= *k;
	*g *= *k;
	*h *= *k;
	*i *= *k;
	cout << *a << " " << *b << " " << *c << "\n" << *d << " " << *e << " " << *f << "\n" << *g << " " << *h << " " << *i << "\n";
}

void func7(double& a, double& b, double& c, double& d, double& e, double& f, double& g, double& h, double& i, double& k){
	a *= k;
	b *= k;
	c *= k;
	d *= k;
	e *= k;
	f *= k;
	g *= k;
	h *= k;
	i *= k;
	cout << a << " " << b << " " << c << "\n" << d << " " << e << " " << f << "\n" << g << " " << h << " " << i << "\n";
}

#include <iostream>
using namespace std;

int main(){

	int x, y;
	
	x = 2;
	y = 4;
	
	// Somme, différence, produit, quotient
	double a, b, c, d;
	a = x + y;
	b = x - y;
	c = x * y;
	d = x / y;
	
	cout << "x = " << x << " et y = " << y << endl << endl
		 << "Somme : " << a << endl
		 << "Différence : " << b << endl
		 << "Produit : " << c << endl
		 << "Quotient : " << d << endl;
	
}

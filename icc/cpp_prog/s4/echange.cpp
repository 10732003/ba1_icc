#include <iostream>
using namespace std;

void echange(int& x, int& y);

int main()
{
	
	int i(10);
	int j(55);

	cout << "Avant: i=" << i << " et j=" << j << endl;
	echange(i,j);
	cout << "Après: i=" << i << " et j=" << j << endl;

	
	return 0;
}

void echange(int& x, int& y)
{
	int tmp(x);
	x = y;
	y = tmp;
	
	return;
}
#include <iostream>
using namespace std;

int demander_nombre(int min, int max);

int main()
{
	int b;
	cout << "Entrez un min : ";
	cin >> b;
	
	int c;
	cout << "Entrez un max : ";
	cin >> c;
	
	cout << demander_nombre(b, c);
	
	return 0;
}

int demander_nombre(int min, int max)
{
	int a;
	
	bool max_min(true);
	if (max < min){max_min = false;}
	
	do {
	cout << "Entrez un int : ";
	cin >> a;
	} while (a < min or (a > max and max_min));
	
	return a;
}

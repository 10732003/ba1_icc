#include <iostream>
#include <cmath>
using namespace std;

double factorielle(int k);
double somme_partielle(double x, int n);
double demander_nbr();


int main(){
	
	cout.precision(10);
	
	double a(demander_nbr());
	
	int n;
	do {
		cout << "Entrez N : ";
		cin >> n;
	} while (n > 85);
		
	double cos(somme_partielle(a, n));
	
	cout << "Le cosinus vaut : " << cos;
	
		
	return 0;
}


// fct def


// factorielle
double factorielle(int k)
{
	if (k > 85){k = 85;}

	double result(1);
	for (int i(1); i <= k; ++i)
		{result *= i;}
		
	return result;
}


// somme_partielle
double somme_partielle(double x, int n)
{
	double result(0.);
	double x_tmp(1.);
	
	for (int i(0); i < n; ++i)
	{	
		if (i%2 == 0){
			result += x_tmp / factorielle(2*i);
		
		} else {
			result -= x_tmp / factorielle(2*i);
		}
		
		x_tmp *= x * x;
	}
		
	
	return result;
}


// demander_nbr
double demander_nbr()
{
	cout << "Entrez un angle en degré : ";
	double a;
	cin >> a;
	
	while (a >= 360){a -= 360;} 
	while (a < 0){a += 360;}
	
	a = (a * 2.0 * M_PI)/ 360.0;
	
	return a;
}

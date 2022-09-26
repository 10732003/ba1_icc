#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	double a(0.0);
	double b(0.0);
	double c(0.0);
	
	string msg_erreur("Ce n'est pas une équation du deuxième degré");
	
	cout << "Entrez une valeur non nulle pour a : ";
	cin >> a;
	if (a == 0.0) {
		// cerr est comme cout, mais pour les messages d'erreur.
		cerr << msg_erreur << endl;
		return 1; // On quitte le programme 
	}
	
	cout << "Entrez une valeur pour b:";
	cin >> b;
	cout << "Entrez une valeur pour c:";
	cin >> c;
	
	double delta(b*b-4.0*a*c);
	
	if (delta < 0.0) {
		cout << "Pas de solutions réelles." << endl;
	} else if (delta > 0.0) {
		cout << "Deux solutions : " << (-b-sqrt(delta))/(2.0*a)
		<< " et " << (-b+sqrt(delta))/(2.0*a) << endl;
	} else {
		cout << "Une solution unique : " << -b/(2.0*a) << endl;
	}

	return 0;
}

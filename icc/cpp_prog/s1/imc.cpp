#include <iostream>
using namespace std;

int main(){
	
	double poids(70);
	double taille(1.75);
	
	cout << "Entrez votre poids (en kg) : ";
	cin >> poids;
	cout << "Entrez votre taille (en m) : ";
	cin >> taille;
	
	double imc(poids / (taille * taille));
	
	cout << "Pour " << poids
		 << "kg et " << taille
		 << " m, l'IMC est de " << imc
		 << endl;
	
	return 0;
}

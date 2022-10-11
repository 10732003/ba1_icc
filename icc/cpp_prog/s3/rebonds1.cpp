#include <iostream>
#include <cmath>
using namespace std;

int main(){
	
	// déclaration des constantes
	constexpr float g(9.81);
	
	// consigne
	cout<< "Pour savoir à quelles hauteurs va rebondir votre balle "
		<< "après un certain nombre de rebonds, veuillez compléter "
		<< "les informations suivantes :"
		<< endl; 
	
	// recup h0 et verifier si valide
	cout << "Hauteur initiale h0 : ";
	double h0;
	cin >> h0;
	if (h0 <= 0)
	{
		cout << "La hauteur initiale doit être plus grande que 0";
		return 1;
	}
	
	
	// recup eps et verifier si valide
	cout << "Valeur d'epsilon : ";
	double eps;
	cin >> eps;
	if (eps < 0 or eps > 1)
	{
		cout << "Epsilon doit appartenir à [0; 1[";
		return 1;
	}
	
	
	// recup nbr_rebonds et verifier si valide
	cout << "Nombre de rebonds : ";
	double nbr_rebonds;
	cin >> nbr_rebonds;
	if (nbr_rebonds <= 0)
	{
		cout << "Le nombre de rebonds doit être plus grand que 0";
		return 1;
	}
	
	// calcul
	double h(h0);
	double v(0);
	
	for (int i(0); i < nbr_rebonds; ++i)
	{
		v = sqrt(2*h*g); 	// v avant le rebond
		v *= eps; 			// v après le rebond
		h = v*v/(2*g);		// h après le rebond
	}

	cout<< "La balle va rebondir à "
		<< h
		<< " metre après "
		<< nbr_rebonds
		<< " pour les paramètres suivants : epsilon = "
		<< eps
		<< " et h0 = "
		<< h0;
	
	return 0;
}

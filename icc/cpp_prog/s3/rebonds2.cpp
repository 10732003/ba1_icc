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
	
	
	// recup h_fin et verifier si valide
	cout << "Hauteur de fin : ";
	double h_fin;
	cin >> h_fin;
	if (h_fin <= 0 or h_fin >= h0)
	{
		cout<< "Le nombre de rebonds doit être plus grand que 0 "
			<< "et plus petit que la hauteur initiale.";
		return 1;
	}
	
	// calcul
	int nbr_rebonds(0);
	double v;
	double h(h0);

	do{
		v = sqrt(2*h*g); 	// v avant le rebond
		v *= eps; 			// v après le rebond
		h = v*v/(2*g);		// h après le rebond
		++nbr_rebonds;
	} while (h > h_fin);
		
	
	cout<< "La balle fera "
		<< nbr_rebonds
		<< " rebonds.";
	
	return 0;
}

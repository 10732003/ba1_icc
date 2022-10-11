#include <iostream>
using namespace std;

int main(){
	
	double pret;
	cout << "Entrez le montant du prêt : ";
	cin >> pret;
	if (pret <= 0){
		cout << "Montant du prêt <= 0";
		return 1;
	}
	
	double mensualite;
	cout << "Entrez le montant remboursé chaque mois : ";
	cin >> mensualite;
	if (mensualite <= 0){
		cout << "Montant à rembourser <= 0";
		return 1;
	}
	
	double taux_interet;
	cout << "Entrez le taux d'interêt (en pourcent) : ";
	cin >> taux_interet;
	taux_interet = taux_interet/100;
	if (taux_interet < 0 or taux_interet > 1){
		cout << "Les interets peuvent aller de 0 à 100%";
		return 1;
	}
	
	double montant_interet(0);
	int mois(0);
	double dette(pret);
	
	while (dette > 0){
		montant_interet += dette * taux_interet;
		dette -= mensualite;
		++mois;
	}
	
	cout<< "La somme des intérêts encaissés (sur "
		<< mois
		<< " mois) est alors de "
		<< montant_interet
		<< " euros.";
	
	return 0;
}

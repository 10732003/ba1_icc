#include <iostream>
using namespace std;

int main()
{
	cout << "Donnez l'heure de début de la location (un entier) : ";
	int debut;
	cin >> debut;

	cout << "Donnez l'heure de fin de la location (un entier) : ";
	int fin;
	cin >> fin;

  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/

	// gestion des erreurs
	if (debut < 0 or debut > 24 or fin < 0 or fin > 24){
		cout << "Les heures doivent être comprises entre 0 et 24 !" << endl;
		return 1;
	}
	
	if (debut == fin){
		cout << "Bizarre, vous n'avez pas loué votre vélo bien longtemps !" << endl;
		return 1;
	}
	
	if (debut > fin){
		cout << "Bizarre, le début de la location est après la fin ..." << endl;
		return 1;
	}
	
	// calculs du prix
	int prix(0);
	int heure_1CHF(0);
	int heure_2CHF(0);
	int chf_hr_1(1);
	int chf_hr_2(2);
	
	// heure_1CHF matin
	if (debut < 7){
		if (fin < 7){
			heure_1CHF = fin - debut;
		} else {
			heure_1CHF = 7 - debut;
		}
	}
	
	// heure_1CHF soirée
	if (fin > 17){
		if (debut > 17){
			heure_1CHF += fin - debut;
		} else {
			heure_1CHF += fin - 17;
		}
	}
	
	// heure 2CHF
	if (fin <= 17 and debut >= 7){
		heure_2CHF = fin - debut;
	} 
	else if (fin <= 17 and fin > 7 and debut < 7){
		heure_2CHF = fin - 7;
	}
	else if (fin > 17 and debut >= 7 and debut < 17){
		heure_2CHF = 17 - debut;
	}
	else if (fin >= 17 and debut <= 7){
		heure_2CHF = 17 - 7;
	}
	
	prix = chf_hr_1*heure_1CHF + chf_hr_2*heure_2CHF;
	
	cout << "Vous avez loué votre vélo pendant" << endl;

	if (heure_1CHF != 0){
		cout << heure_1CHF <<" heure(s) au tarif horaire de " << chf_hr_1
         << " franc(s)" << endl;
	 }
	 
	if (heure_2CHF != 0){
		cout << heure_2CHF << " heure(s) au tarif horaire de " << chf_hr_2
         << " franc(s)" << endl;
	}
	
	cout<< "Le montant total à payer est de " 
		<< prix
        << " franc(s)." << endl;
         

  /*******************************************
   * Ne rien modifier après cette ligne.
   *******************************************/

  return 0;
}

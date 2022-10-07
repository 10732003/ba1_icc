#include <iostream>
using namespace std;

int main(){

	cout<< "Pensez à  un champignon : amanite tue-mouches, pied bleu, girolle," << endl
		<< "cèpe de Bordeaux, coprin chevelu ou agaric jaunissant." << endl << endl;
  
	// les questions
	string q_lamelle("Est-ce que votre champignon a des lamelles (1 : oui, 0 : non) ? ");
	string q_anneau("Est-ce que votre champignon a un anneau (1 : oui, 0 : non) ? ");
	string q_chapeau("Est-ce que votre champignon a un chapeau convexe (1 : oui, 0 : non) ? ");
	string q_foret("Est-ce que votre champignon vit en forêt (1 : oui, 0 : non) ? ");

	string champi("Erreur");

	int reponse;
	
	cout << q_anneau;
	cin >> reponse;
	
	if (reponse == 1){ 
		// si anneaux
		
		cout << q_foret;
		cin >> reponse;
		
		if (reponse == 1){
			// si anneaux et foret
			champi = "l'amanite tue-mouches";
			
			} else {
				// si anneaux et pas foret
				
				cout << q_chapeau;
				cin >> reponse;
				
				if (reponse == 1){
					// si anneaux et pas foret et chapeau
					champi = "l'agaric jaunissant";
				
				} else {
					// si anneaux et pas foret et pas chapeau
					champi = "le coprin chevelu";
				}
			}
	
	} else { 
		// si pas d'anneau
		
		cout << q_lamelle;
		cin >> reponse;
				
		if (reponse == 1){
			// si pas d'anneau et lamelle
			
			cout << q_chapeau;
			cin >> reponse;
				
			if (reponse == 1){
				// si pas d'anneau et lamelle et chapeau
				champi = "le pied bleu";
				
			} else {
				// si pas d'anneau et lamelle et pas chapeau
				champi = "la girolle";
			}
			
		} else {
			// si pas d'anneau et pas lamelle
			champi = "le cèpe de Bordeaux";
		}	
	}
	

	cout<< "==> Le champignon auquel vous pensez est " 
		<< champi << endl;
		
	return 0;
}

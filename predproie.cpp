#include <iostream>
#include <iomanip> // pour setprecision()
using namespace std;

int main()
{
  // Réduire le format d'affichage
  cout << setprecision(4);

  // Paramètres
  double taux_croissance_lapins(0.3);
  double taux_attaque(0.01);
  double taux_croissance_renards(0.008);
  double taux_mortalite(0.1);
  int duree(50);

  double renards_i(0.0);
  double lapins_i(0.0);

  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/

  // ===== PARTIE 1 =====
  // Saisie des populations initiales

  do {
	cout << "Combien de renards au départ (>= 2) ? ";
	cin >> renards_i;
  } while (renards_i < 2);

  do {
	cout << "Combien de lapins au départ  (>= 5) ? ";
	cin >> lapins_i;
  } while (lapins_i < 5);

  // ===== PARTIE 2 =====
  // Première simulation
  cout<< endl << "***** Le taux d'attaque vaut "
	<< taux_attaque * 100 << "%" <<  endl;
	
  double nb_lapins(lapins_i);
  double nb_renards(renards_i);
  double nb_lapins_avant(nb_lapins);
		
  for (int i(1); i <= duree; i++)
	{
		nb_lapins = nb_lapins * (1.0 + taux_croissance_lapins - taux_attaque * nb_renards);
		nb_renards = nb_renards * (1.0 + taux_attaque * nb_lapins_avant * taux_croissance_renards - taux_mortalite);
		
		nb_lapins_avant = nb_lapins;
		
		if (nb_lapins <= 0){nb_lapins = 0;}
		if (nb_renards <= 0){nb_renards = 0;}
		
		cout << "Après "<< i << " mois, il y a "<< nb_lapins << " lapins et "
		<< nb_renards << " renards" << endl;
	}

  // ===== PARTIE 3 =====
  // Variation du taux d'attaque
  cout << endl;

  double att_0, att_1;
  do {cout << "taux d'attaque au départ en % (entre 0.5 et 6) ? ";
	  cin >> att_0;
	  } while (att_0<0.5 or att_0>6.0);
  do {cout<< "taux d'attaque à la fin  en % (entre " << att_0 << " et 6) ? ";
	  cin >> att_1;
	  } while (att_1<=att_0 or att_1>6.0); 

	att_0 = att_0 / 100;
	att_1 = att_1 / 100;
	
  do {
	  bool ext_lap(false), ext_ren(false);
	  bool lap_rip (false), ren_rip(false);
	  
	  nb_lapins = lapins_i;
	  nb_renards = renards_i;
	  nb_lapins_avant = nb_lapins;
	  
	  int i(0); 
	  do {
			nb_lapins = nb_lapins * (1.0 + taux_croissance_lapins - att_0 * nb_renards);
			nb_renards = nb_renards * (1.0 + att_0 * nb_lapins_avant * taux_croissance_renards - taux_mortalite);
			
			nb_lapins_avant = nb_lapins;
			
			if (nb_lapins < 2){nb_lapins = 0; lap_rip = true;}
			if (nb_lapins < 5){ext_lap = true;}
			
			if (nb_renards < 2){nb_renards = 0; ren_rip = true;}
			if (nb_renards < 5){ext_ren = true;}
			++i;
			if (nb_lapins == 0 and nb_renards == 0){break;}
			
		} while (i < duree);
		
		cout<< endl << "***** Le taux d'attaque vaut "
		<< att_0 * 100 << "%" <<  endl;
		
		cout << "Après " << i << " mois, il y a "<< nb_lapins << " lapins et "
			<< nb_renards << " renards" << endl;
		
		if (ext_ren){
			cout << "Les renards ont été en voie d’extinction"<<endl;
			if (nb_renards > 5){cout << "mais la population est remontée ! Ouf !" << endl;}
			if (ren_rip){cout << "et les renards ont disparu :-("<<endl;}
			}
			
		if (ext_lap){
			cout << "Les lapins ont été en voie d’extinction"<<endl;
			if (nb_lapins > 5){cout << "mais la population est remontée ! Ouf !" << endl;}
			if (lap_rip){cout << "et les lapins ont disparu :-("<<endl;}
			}

		if (not ext_lap and not ext_ren){cout << "Les lapins et les renards ont des populations stables." << endl;}
		att_0 = att_0 + 0.01;

  } while (att_0 <= att_1);
/*
  cout << "taux d'attaque au départ en % (entre 0.5 et 6) ? ";

  cout << "taux d'attaque à la fin  en % (entre ";
  cout << " et 6) ? ";

  cout << "Les renards ont été en voie d'extinction" << endl;
  cout << "mais la population est remontée ! Ouf !" << endl;
  cout << "et les renards ont disparu :-(" << endl;
  cout << "Les lapins ont été en voie d'extinction" << endl;
  cout << "mais la population est remontée ! Ouf !" << endl;
  cout << "et les lapins ont disparu :-(" << endl;
  cout << "Les lapins et les renards ont des populations stables." << endl;
  */

  /*******************************************
   * Ne rien modifier après cette ligne.
   *******************************************/

  return 0;
}

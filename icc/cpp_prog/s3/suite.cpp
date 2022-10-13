#include <iostream>
using namespace std;

int main()
{
  int debut(0);
  do {
    cout << "de (>= 1) ? ";
    cin >> debut;
  } while (debut < 1);

  int fin(0);
  do {
    cout << "a (>= " << debut << ") ? ";
    cin >> fin;
  } while (fin < debut);

  /*******************************************
   * Completez le programme a partir d'ici.
   *******************************************/

	for (int i(debut); i <= fin; ++i)
	{
		int n(0); // nbr de répétitions
		int u(i); // valeur de la suite
		
		do{
			// si ce nombre est divisible par 3, on lui ajoute 4 
			if (u%3 == 0){u += 4;}
			// s’il n’est pas divisible par 3 mais divisible par 4
			//on le divise par 2
			else if (u%4 == 0){u = u/2;}
			//’il n’est divisible ni par 3, ni par 4, on lui soustrait 1
			else {u -= 1;}
			
			n++;
		} while (u != 0);
		
		// Affchage de: i -> n
		cout<< i
			<< " -> " 
			<< n
			<< endl;
	}

  /*******************************************
   * Ne rien modifier apres cette ligne.
   *******************************************/

  return 0;
}

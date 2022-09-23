#include <iostream>
using namespace std;

int main(){

	const int BASE(4);
	
	int nbr_convives(4);
	
	double fromage(800);
	double eau(2);
	double ail(2);
	double pain(400);
	
	cout << "Entrez le nombre de personne(s) conviée à la fondue : ";
	cin >> nbr_convives;
	
	fromage = fromage * nbr_convives / BASE;
	eau = eau * nbr_convives / BASE;
	ail = ail * nbr_convives / BASE;
	pain = pain * nbr_convives / BASE;
	
	cout << "Pour faire une fondue pour "
		 << nbr_convives
		 << " personnes, il vous faut :"
		 << endl
		 
		 << "- "
		 << fromage
		 << "grammes de fromages"
		 << endl
		 
		 << "- "
		 << eau
		 << "dl d'eau"
		 << endl
		 
		 << "- "
		 << ail
		 << "gousse(s) d'ail"
		 << endl
		 
		 << "- "
		 << pain
		 << "grammes de pain"
		 << endl
		 
		 << "- "
		 << "du poivre et du blanc pour ceux qui veulent."
		 << endl;
	
	return 0;
}

#include <iostream>
#include <cmath>
using namespace std;

int main(){

	int n;
	cout << "Entrez un nombre : ";
	cin >> n;
	cout << endl;
	
	bool prime(true);
	int x;
	
	if (n%2 == 0 and n != 2){
		x = n/2;
		prime = false;
	}
	
	if (prime){
		
		int i(3);
		
		do{
			
			if (n%i == 0){
				x = n/i;
				prime = false;
			}
			
			++i;
			
		} while (i <= sqrt(n) and prime);
	}
	
	if (prime){
		cout<< n
			<< " est un nombre premier.";
	
	} else {
		cout<< n
			<< " n'est pas un nombre premier."
			<< endl
			<< "Il est divisible par "
			<< x
			<< ".";
	}
	
	return 0;
}

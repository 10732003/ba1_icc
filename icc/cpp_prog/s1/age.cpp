#include <iostream>
using namespace std;

int main(){
	
	int age(40);
	int annee(1982);

	cout << "Entrez votre âge ? ";
	cin >> age;
	
	annee = 2022 - age;
	cout << "Votre année de naissance est "
		 << annee
		 << "." 
		 << endl;
	
	return 0;
}

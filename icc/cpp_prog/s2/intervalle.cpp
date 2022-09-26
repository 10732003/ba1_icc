#include <iostream>
using namespace std;

int main()
{
	cout << "Soit I l'intervalle [-1;1]." << endl;
	
	double x(0);
	cout << "Entrez un réel x : ";
	cin >> x;
	
	if (x>=-1 and x<1){
		cout << "x appartient à I.";
	} else {
		cout << "x n'appartient pas à I";
	}
	
	return 0;
}

#include <iostream>
using namespace std;

int main()
{
	cout << "Soit I l'intervalle [2;3[ U ]0;1] U [-10;-2]." << endl;
	
	double x(0);
	cout << "Entrez un réel x : ";
	cin >> x;
	
	string msg("");
	
	if (	(not (x<2) and x<3)
			or 	((x<1 and 0<x) or x == 1)
			or 	((not (x<-10) and x<-2) or x == -2)
		){
		msg = "x appartient à I.";
	} else {
		msg = "x n'appartient pas à I";
	}
	
	cout << msg << endl;
	
	return 0;
}

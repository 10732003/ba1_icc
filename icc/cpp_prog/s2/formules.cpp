#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	double x(0);
	cout << "Entrez une valeur de x : ";
	cin >> x;
	
	// Expression 1
	string text("Expression 1 = Erreur");
	double val(0);
	bool display_val(false);
	if (x == 0.0){
		text = "Expression 1 : indéfinie";
	} else {
		text = "Expression 1 = "; 
		val = x/(1-exp(x)); 
		display_val = true;
	}
	cout << text;
	if (display_val){
		cout << val;
	}
	cout << endl;
	
	
	// Expression 2
	text = "Expression 2 = Erreur";
	display_val = false;
	if (x <= 0 or x == 1){
		text = "Expression 2 : indéfinie";
	} else {
		text = "Expression 2 = "; 
		val = x*log(x)*exp(2*(x-1)); 
		display_val = true;
	}
	cout << text;
	if (display_val){
		cout << val;
	}
	cout << endl;
	
	
	// Expression 3
	text = "Expression 3 = Erreur";
	display_val = false;
	if (x <= 1 or (sin(x)-x/20)<0){
		text = "Expression 3 : indéfinie";
	} else {
		text = "Expression 3 = "; 
		val = sqrt((sin(x)-x/20)*log(x*x-1/x)); 
		display_val = true;
	}
	cout << text;
	if (display_val){
		cout << val;
	}
	cout << endl;
	
	return 0;
}

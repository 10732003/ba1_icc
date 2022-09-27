#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	// z^3 + a2*z^2 + a1*z^1 + a0 = 0
	double a0(0);
	double a1(0);
	double a2(0);
	
	cout<< "Soit l'équation de degré 3 de la forme suivante "
		<< "z^3 + a2*z^2 + a1*z^1 + a0 = 0" << endl
		<< "Entrez la valeur de a2 : ";
	cin >> a2;
	cout << "Entrez la valeur de a1 : ";
	cin >> a1;
	cout << "Entrez la valeur de a0 : ";
	cin >> a0;

	const double Q((3 * a1 - a2 * a2) / 9.0);
	const double R((9.0 * a2 * a1 -27.0 * a0 -2.0 * a2 * a2 * a2) / 54.0);
	const double D(Q*Q*Q+R*R);
	
	double t(0);

	double z1(0);
	double z2(0);
	double z3(0);

	if (D<0)
	{
		t = acos(R / (sqrt(-Q*Q*Q)));
		z1 = 2.0 * sqrt(-Q) * cos(t/3.0)			-a2/3.0;
		z2 = 2.0 * sqrt(-Q) * cos((t+2.0*M_PI)/3.0)	-a2/3.0;
		z3 = 2.0 * sqrt(-Q)	* cos((t+4.0*M_PI)/3.0)	-a2/3.0;
		
		cout<< "Les solutions sont :" << endl 
			<< "z1 = " << z1 << endl 
			<< "z2 = " << z2 << endl
			<< "z3 = " << z3 << endl;

	} else {
		double S(0.0);
		double s(R+sqrt(D));
		if 		(s < 0.0)	{ S =-pow(-s, 1.0/3.0);}
		else if (s > 0.0)	{ S = pow( s, 1.0/3.0);}
		
		double T(0.0);
		s = R-sqrt(D);
		if 		(s < 0.0)	{ T =-pow(-s, 1.0/3.0);}
		else if (s > 0.0)	{ T = pow( s, 1.0/3.0);}
		
		z1 = -a2 / 3.0 + S + T;
		
		if (D == 0 and S+T != 0){
			z2 = -a2 / 3.0 - (S + T) / 2.0;
			
			cout<< "Les solutions sont :" << endl 
			<< "z1 = " << z1 << endl 
			<< "z2 = " << z2 << " (racine double)" << endl;
		
		} else {
			z1 = S + T 		- a2/3.0;
			cout<< "La solution est :" << endl 
				<< "z1 = " << z1 << " (racine unique)" << endl ;
		
		}
	}
	
	return 0;
}

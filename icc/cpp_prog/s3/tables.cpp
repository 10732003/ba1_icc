#include <iostream>
using namespace std;

int main(){
	
	for (int i(1); i <= 10; ++i)
	{
		
		cout << "Table de " << i << " :" << endl;
		
		for (int k(1); k <= 10; ++k)
		{
			cout << i << " * " << k << " = " << i*k << endl;
		}
		
		cout << endl;
		
	}
	
	return 0;
}

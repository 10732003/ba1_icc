#include <iostream>
using namespace std;

int Fibonacci(int n);

int main(){
	
	cout << Fibonacci(7);
	
	return 0;
}


/*** fct def  ***/

// fibonacci
int Fibonacci(int n)
{
	int f0(0);
	int f1(1);
	
	if (n == 0){return f0;}
	if (n == 1){return f1;}
	
	return Fibonacci(n-1) + Fibonacci(n-2);
}

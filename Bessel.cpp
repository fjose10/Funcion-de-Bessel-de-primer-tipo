/* Este código muestra los valores de las funciones de Bessel de primer tipo de orden entero 
	para argumentos arbitrarios entre 0 y 25.*/

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <unistd.h>
#include <cmath>
#include <ctime>
#include <string>
#include "math.h"
#include <fstream>
#include "locale.h"
#include <cstdlib>
#include <stdlib.h> 
#include <ctype.h>
#include <stdio.h>
#define ACC 40.0 
#define BIGNO 1.0e10
#define BIGNI 1.0e-10


using namespace std;

// Declaración de funciones 

long double factorial(int n); // Calcula el factorial de un entero n 
long double fgamma(int p); // Calcula la función Gamma de un entero p

// Rutinas de Numerical Recipes 
double bessj0(float x); // Calcula la función de Bessel de orden 0 
double bessj1(float x); // Calcula la función de Bessel de orden 1 
double bessjn(int n, float x); // Calcula la función de Bessel de orden n 

// Cálculo de la función con la sumatoria dada
double Bessj(int parametro_n, float x);  

int main() {
	// Configuracion del sistema 
	system("color 2F");
	setlocale(LC_CTYPE,"Spanish");
	
	// Tabla de datos y creacion de los archivos 
	fstream datos("Funcion de Bessel.txt",ios::out|ios::trunc);
	datos << setw(5) << "x" << "\t" << setw(15) << "Valor de la sumatoria" << "\t" << setw(15) << "Valor de Numerical Recipes" << endl;

	// Declaracion de las variables 
	int inc, parametro_n;
	double Bessn, bess0, bess1, bessn, valor;
	float k = 0;
	
	// Aleatorización del incremento crear intervalos arbitrarios 
	srand(time(NULL));
	inc = rand()%11; // %11 limita a la función rand a dar valores entre 0 y 10 
	
	cout << "\n Bienvenido al programa para calcular la n-esima funcion de Bessel de primer tipo. " << endl;
	
	cout << "\n Por favor introduzca el orden (mayor o igual a 0) de la funcion que desee calcular (1,2,3...):" << endl;
	
	cin >> parametro_n;   // Se especifica el orden de la funcion de Bessel 
	
I:	while(cin.fail()){ 	// Bucle para evitar que se introduzcan letras y se tenga un error 
	cin.clear(); 	// Limpia la variable parametro_n 
	cin.ignore(100, '\n'); 	// De no especificarse este paso, se evaluaria cada uno de los caracteres introducidos 
	cout << "Solo se permiten numeros. Introduzca el valor de nuevo por favor:" << endl;
	cin >> parametro_n;
	}
	
	if (parametro_n < 0){
	cout << "El numero introducido debe ser mayor o igual a 0. Introduzca el valor de nuevo, por favor:" << endl;
	cin >> parametro_n;
	goto I;
	}	
	cout << "El orden introducido es: " << " " << parametro_n << endl;
	
	if (inc == 0) { 	// Preveniendo que el incremento sea 0 
	inc = 5;
	cout << "El valor de su incremento es: " << inc << endl;  
	}
	else {
	cout << "El valor de su incremento es: " << inc << endl;
	}
	cout << "\n" << setw(5) << "x" << setw(35) << "Valor de la sumatoria" << setw(45) << "Valor de Numerical Recipes" << endl; 
	
	while(k <= 25){  // Bucle para calcular las funciones para los diferentes argumentos incrementados
		
	valor = Bessj(parametro_n,k); // Devuelve el valor de Bessj 
	inc = 1;	
	if (parametro_n == 0) {
		bess0 = bessj0(k);  // Devuelve el valor de bessj0
			
		// Impresión de resultados 
		datos << setw(5) << k << "\t" << setw(15) << valor << "\t" << setw(30) << bess0 << endl;
		cout << "\n" << setw(5) << k << setw(30) << valor << setw(40) << bess0 << endl;
		usleep(50000); // Espera 0.05 segundos para imprimir cada valor
		}
		
	if (parametro_n == 1) {
		bess1 = bessj1(k);  // Devuelve el valor de bessj1
			
		// Impresión de resultados 	
		datos << setw(5) << k << setw(30) << valor << setw(40) << bess1 << endl;
		cout << "\n" << setw(5) << k << setw(30) << valor << setw(40) << bess1 << endl;
		usleep(50000);
		}
	
	if (parametro_n > 1) {
		bessn = bessjn(parametro_n,k); // Devuelve el valor de bessjn 
			
		// Impresión de resultados 	
		datos << setw(5) << k << setw(30) << valor << setw(40) << bessn << endl;
		cout << "\n" << setw(5) << k << setw(30) << valor << setw(40) << bessn << endl;	
		usleep(50000);	  
		}
	k = k + inc;
	}
	cout << "\n" "Fue un placer trabajar con usted." << endl;
	cout << "Si desea calcular otros intervalos, reinicie el programa por favor.";
	getch();
}

// Cuerpo de funciones 

long double fgamma(int p) {
	return factorial(p-1);
}

long double factorial(int p){ 
	long double producto = 1,k;
	if (p<0) {
		return 0;
	} 
	for(k = 1; k <= p; k++) {
		producto= producto*k;
		}	 
	return producto;
}

double Bessj(int n, float x) {
	int k = 0;
	double suma = 0.0, division, producto;
	while (k <= 50) {
		division= pow(-1.0,k)/(factorial(k)*fgamma(k+n+1));
		producto= pow(x/2,2*k+n);
		suma = suma + division*producto;
		k++;
	} 
	return suma;
}

// Rutinas de Numerical Recipes 

double bessj0(float x) {
float ax,z;
double xx,y,ans,ans1,ans2; 
if ((ax=fabs(x)) < 8.0) { 
y=x*x;
ans1=57568490574.0+y*(-13362590354.0+y*(651619640.7
+y*(-11214424.18+y*(77392.33017+y*(-184.9052456)))));
ans2=57568490411.0+y*(1029532985.0+y*(9494680.718
+y*(59272.64853+y*(267.8532712+y*1.0))));
ans=ans1/ans2;
} else { 
z=8.0/ax;
y=z*z;
xx=ax-0.785398164;
ans1=1.0+y*(-0.1098628627e-2+y*(0.2734510407e-4
+y*(-0.2073370639e-5+y*0.2093887211e-6)));
ans2 = -0.1562499995e-1+y*(0.1430488765e-3
+y*(-0.6911147651e-5+y*(0.7621095161e-6
-y*0.934935152e-7)));
ans=sqrt(0.636619772/ax)*(cos(xx)*ans1-z*sin(xx)*ans2);
}
return ans;
}

double bessj1(float x) {
float ax,z;
double xx,y,ans,ans1,ans2; 
if ((ax=fabs(x)) < 8.0) { 
y=x*x;
ans1=x*(72362614232.0+y*(-7895059235.0+y*(242396853.1
+y*(-2972611.439+y*(15704.48260+y*(-30.16036606))))));
ans2=144725228442.0+y*(2300535178.0+y*(18583304.74
+y*(99447.43394+y*(376.9991397+y*1.0))));
ans=ans1/ans2;
} else { 
z=8.0/ax;
y=z*z;
xx=ax-2.356194491;
ans1=1.0+y*(0.183105e-2+y*(-0.3516396496e-4
+y*(0.2457520174e-5+y*(-0.240337019e-6))));
ans2=0.04687499995+y*(-0.2002690873e-3
+y*(0.8449199096e-5+y*(-0.88228987e-6
+y*0.105787412e-6)));
ans=sqrt(0.636619772/ax)*(cos(xx)*ans1-z*sin(xx)*ans2);
if (x < 0.0) ans = -ans;
}
return ans;
}

double bessjn(int n, float x) {
	int j,jsum,m;
	double ax,bj,bjm,bjp,sum,tox,ans;
	ax=fabs(x);
	if (ax == 0.0)
	return 0.0;
	else if (ax > (float) n) {
		tox=2.0/ax;
		bjm=bessj0(ax);
		bj=bessj1(ax);
		for (j=1;j<n;j++) {
			bjp=j*tox*bj-bjm;
			bjm=bj;
			bj=bjp;
		}
		ans=bj;
		}	else {
			tox = 2.0/ax;
			m=2*((n+(int) sqrt(ACC*n))/2);
			jsum=0; 
			bjp=ans=sum=0.0;
			bj=1.0;
			for (j=m;j>0;j--) {
				bjm=j*tox*bj-bjp;
				bjp=bj;
				bj=bjm;
				if (fabs(bj) > BIGNO) { 
					bj *= BIGNI;
					bjp *= BIGNI;
					ans *= BIGNI;
					sum *= BIGNI;
				}
				if (jsum) sum += bj; 
				jsum=!jsum; 
				if (j == n) ans=bjp;
			}
			sum=2.0*sum-bj; 
			ans /= sum; 
		}
	return x < 0.0 && (n & 1) ? -ans : ans;
}

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define TAM 11
/*
Estudiante: Ulises López Díaz
Tema: Agentes reactivos

Introducción:

En este problema, se programaron dos agentes distintos:

-Uno el cual evita obstaculos, en el cual cada vez que el agente recibe la señal de los sensores S, debe repasar
ordenadamente el conjunto de reglas o condiciones establecidad hasta que
encuentre alguna en la que se cumpla la condición, debiendo realizar la 
acción correspondiente. El repaso se detiene hasta después de que se active
la primera regla

-El otro agente el cual sigue los bordes de un mapa, en el cual el agente seguidor de bordes
 verifica la condición de cada una de las reglas establecidad, seleccionando los pesos 
 y umbrales adecuados para cada caso
 
 El ambiente utilizado es lleno de ceros y unos (0,1), 0 dando a entender que es un espacio
 vacio, 1 da a entender que es un espacio ocupado (el cual despues se transforma en el simbolo "-"),
 y nuestro agente estara representado con un "*", el cual recorrera el mapa dependiendo de el 
 algoritmo que se le especifique en el main.

*/



int mapa[12][12] = {
	{1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1,1},
	{1,0,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,0,0,0,0,0,1,1},
	{1,1,0,0,1,0,0,0,0,1,1},
	{1,0,0,0,1,1,0,0,0,1,1},
	{1,0,0,0,1,1,1,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1},


	

};


int x,y;
bool flag = true;

/*Estudiante: Ulises López Díaz
Tema: Agentes reactivos

Funcion que imprime por pantalla el mapa
cambiando en las coordenaadas indicadas en donde se 
encuentre el agente (coordenadas en donde el valor sea igual a 2)
*/
void print(){
	
	int i,j;
	for(i=0; i<TAM; i++){
		for(j=0;j<TAM;j++){
			if(mapa[i][j] == 2){
				printf("* ");
			}
			else if(mapa[i][j]){
				printf("- ");
				
			}else printf("%d ",mapa[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	
	
	
	
	
}



bool eConcava(){
	return false;
}

// Función que marca la posición en donde se encuntra el agente reactivo
void mover_Agente(){
	mapa[x][y] = 2;
}

// Función que elimina al agente de la posición en donde se encuentre
void resetear_Agente(){
	mapa[x][y] = 0;
}

/*
Estudiante: Ulises López Díaz
Tema: Agentes reactivos

Función TLU para definir el comportamiento del
agente seguidor de bordes, dependiendo de  los pesos y umbrales especificados para cada caso


*/
int TLU(int s[], int dir, float teta){
	int Xn = 0, nXn = 0, respuesta = 0;
	switch(dir){
		case 1:
			if( (s[1] || s[2]) ) {
				Xn = s[1] + s[2];
				nXn = (s[3] * (-2)) + (s[4]*(-2));
				respuesta = Xn + nXn;
			}
			break;
		case 2:
			if( (s[3] || s[4]) ){
				Xn = s[3] + s[4];
				nXn = (s[5]*(-2)) + (s[6]*(-2));
				respuesta = Xn + nXn;
			}
			break;
		case 3:
			if( (s[5] || s[6] ) ){
				Xn = s[5] + s[6];
				nXn = (s[7]*(-2)) + (s[0]*(-2));
				respuesta = Xn + nXn;
			}
			break;
		case 4:
			if( (s[7] || s[0] ) ){
				Xn = s[7] + s[0];
				nXn = (s[1]*(-2)) + (s[2]*(-2));
				respuesta = Xn + nXn;
			}
			break;
	}
	
	
	if(respuesta > teta){
		return 1;
		
	}else return 0;
}


/*
Estudiante: Ulises López Díaz
Tema: Agentes reactivos

Cada vez que el agente recibe la señal de los sensores S, debe repasar
ordenadamente el conjunto de reglas o condiciones establecidad hasta que
encuentre alguna en la que se cumpla la condición, debiendo realizar la 
acción correspondiente. El repaso se detiene hasta después de que se active
la primera regla

*/

bool evitar_Obstaculos(int S[], float teta){
	
	// Si S[2] entonces norte
	if(!S[1]){
		//mover coordenadas del  Agente al Norte
		resetear_Agente();
		x = x - 1;
		y = y;
		mover_Agente();
	}else if(!S[3]){
		// equivalente a Si S4 entonces Este
		// mover coordenadas del Agente al Este
		resetear_Agente();
		x = x;
		y = y + 1;
		mover_Agente();
	}else if(!S[5]){
		// equivalente a Si S6 entonces sur
		//mover coordenadas del Agente al Sur
		resetear_Agente();
		x = x + 1;
		y = y;
		mover_Agente();
	}else if(!S[7]){
		// equivalente a Si S8 entonces oeste
		//mover coordenads del Agente al Oeste
		resetear_Agente();
		x = x;
		y = y - 1;
		mover_Agente();
	}else flag = false;
	
	
}

/*
Estudiante: Ulises López Díaz

Para la función del agente seguidor de bordes se verifica la condición de cada una de las reglas, 
seleccionando los pesos y umbrales adecuados para cada caso
*/

bool seguir_Bordes(int S[], float teta){

	printf("siguiente: ");
	if(TLU(S,1,teta)){
		//mover coordenadas del Agente al Este
		resetear_Agente();
		printf("este\n");
		x = x;
		y = y +1;
		mover_Agente();
	}else if(TLU(S,2,teta)){
		//mover coordenadas del Agente al Sur
		printf("sur\n");
		resetear_Agente();
		x = x + 1;
		y = y;
		mover_Agente();
	}else if(TLU(S,3,teta)){
		// mover coordenadas del Agente al Oeste
		printf("oeste\n");
		resetear_Agente();
		x = x;
		y = y - 1;
		mover_Agente();
	}else if(TLU(S,4,teta)){
		//mover coordenadas del Agente al Norte
		resetear_Agente();
		printf("norte\n");
		x = x - 1;
		y = y;
		mover_Agente();
	}else{
		//mover coordenadas del Agente al Norte
		resetear_Agente();
		printf("nortedefault\n");
		x = x - 1;
		y = y;
		mover_Agente();
	}
	
	
}

/*
Estudiante: Ulises López Díaz
Tema: Agentes reactivos

Con la unidad lógica umbralizada,en cada problema, el agente tiene la capacidad de sensar
el estado de las ocho celdas más cercanas de la que se encuentra,
con esta información, se genera una señal de ocho componentes
binarias que indican cuales celdas están ocupadas a su alrededor.
*/

int Unidad_Logica_Umbralizada(int opcion){
	// S = [S1,S2,S3,S4,S5,S6,S7,S8]
	int S[] = {mapa[x-1][y-1],
			   mapa[x-1][y],
			   mapa[x-1][y+1],
			   mapa[x][y+1],
			   mapa[x+1][y+1],
			   mapa[x+1][y],
			   mapa[x+1][y-1],
			   mapa[x][y-1]};
	
/* Programador: Ulises López Díaz
Con estos condicionales, el agente es capaz de responder
correctamente a cualquiera de las dos acciones indicadas
*/
	if(opcion == 1){
		evitar_Obstaculos(S,0.5);
	}else if(opcion == 2){
		seguir_Bordes(S,0.5);
	}
}

// Inicializa el agente y guarda la posicion actual del mismo
void inicializar_Agente(){
	mapa[TAM/4][TAM/4] = 2;
	x = TAM/4;
	y = TAM/4;
}

/*
Estudiante: Ulises López Díaz
Tema: Agentes reactivos

*/

int main(){
	printf("\t.:Agente que evita obstaculos:.\n");
		inicializar_Agente();
	for(int i=0;i<20;i++){
		printf("Agente que evita obstaculos\n}");
		printf("iteracion: %d\n",i);
		Unidad_Logica_Umbralizada(1);
		print();
		system("pause");
	}
	printf("\n\n");
	resetear_Agente();
	
	printf("\n---------------------------------------------------------\n");
	printf("\t.:Agente seguidor de bordes:.\n");
		inicializar_Agente();
	for(int i=0;i<30;i++){
		printf("iteracion: %d\n",i);
		Unidad_Logica_Umbralizada(2);
		print();
		system("pause");
	}

	
	return 0;
}

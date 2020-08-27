#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define TAM 11
//using namespace std;



int mapa[12][12] = {
	{1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,1,0,0,0,0,0,1},
	{1,0,0,0,1,1,0,0,0,0,1},
	{1,0,0,0,1,1,1,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1},


	

};


int x,y;
bool flag = true;


void print(){
	int i,j;
	for(i=0; i<TAM; i++){
		for(j=0;j<TAM;j++){
			if(mapa[i][j] == 2){
				printf("* ");
			}else if(mapa[i][j]){
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

void mover_Agente(){
	mapa[x][y] = 2;
}

void resetear_Agente(){
	mapa[x][y] = 0;
}

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





bool evitar_Obstaculos(int S[], float teta){
	
	if(!S[1]){
		//mover coordenadas del  Agente al Norte
		resetear_Agente();
		x = x - 1;
		y = y;
		mover_Agente();
	}else if(!S[3]){
		// mover coordenadas del Agente al Este
		resetear_Agente();
		x = x;
		y = y + 1;
		mover_Agente();
	}else if(!S[5]){
		//mover coordenadas del Agente al Sur
		resetear_Agente();
		x = x + 1;
		y = y;
		mover_Agente();
	}else if(!S[7]){
		//mover coordenads del Agente al Oeste
		resetear_Agente();
		x = x;
		y = y - 1;
		mover_Agente();
	}else flag = false;
	
	
}


bool seguir_Bordes(int S[], float teta){
	
	/*
	if(eConcava()){
		flag = false;
		
	*/
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


int Unidad_Logica_Umbralizada(int opcion){
	
	int S[] = {mapa[x-1][y-1],
			   mapa[x-1][y],
			   mapa[x-1][y+1],
			   mapa[x][y+1],
			   mapa[x+1][y+1],
			   mapa[x+1][y],
			   mapa[x+1][y-1],
			   mapa[x][y-1]};
	
	// Aqui ira el while (flag)
	if(opcion == 1){
		evitar_Obstaculos(S,0.5);
	}else if(opcion == 2){
		seguir_Bordes(S,0.5);
	}
}

// Inicializar el Agente y guardar la posicion
void inicializar_Agente(){
	mapa[TAM/4][TAM/4] = 2;
	x = TAM/4;
	y = TAM/4;
}



int main(){
	printf("\t.:Agente que evita obstaculos:.\n");
		inicializar_Agente();
	for(int i=0;i<20;i++){
		printf("iteracion: %d\n",i);
		Unidad_Logica_Umbralizada(1);
		print();
		system("pause");
	}
	printf("\n\n");
	resetear_Agente();
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct tablaHash TablaHash;
typedef struct clase Clase;
typedef struct arbol Arbol;
typedef struct nodoArbol NodoArbol;

FILE* abrirArchivo(char* nombre);
TablaHash* crearTabla();
Clase* crearClase();
NodoArbol* crearNodoArbol(int identificador);
Arbol* crearArbol();
NodoArbol* buscar(NodoArbol* raiz, int identificador);
void rotarIzq(Arbol* a, NodoArbol* z);
void rotarDer(Arbol* a, NodoArbol* z);
int altura(NodoArbol* z);
int diferenciaAlturas(NodoArbol* z);
void balancear(Arbol* a, NodoArbol* z);
void insertarArbol(Arbol* a, NodoArbol* z);
NodoArbol* extraerMinimo(NodoArbol* x);
void transplantar(Arbol* a, NodoArbol* u, NodoArbol* v);
void borrarDato(Arbol* a, NodoArbol* z);
int limpiarStdin();
void vaciarArbol(NodoArbol* raiz);
int funcionHash(int id);
void vaciarHash(TablaHash* tabla);


typedef struct tablaHash{
	Clase* hash;
}TablaHash;

typedef struct clase{
	Arbol* arbolID ;
}Clase;

typedef struct arbol{
	NodoArbol* raiz;
}Arbol;

typedef struct nodoArbol{
	NodoArbol* padre;
	NodoArbol* hijoD;
	NodoArbol* hijoI;
	int id;
}NodoArbol;

//Funcion que abre un archivo en formato .txt para su lectura
//Entrada: nombre     Salida: FILE*
FILE* abrirArchivo(char* nombre){
	FILE* archivo;
	archivo= fopen(nombre,"r");
	if(archivo==NULL){
		printf("Archivo nulo. \n");
	}
	return archivo;
}

//Funcion que crea una Tabla hash.
//Entrada:            Salida: TablaHash
TablaHash* crearTabla(){
	TablaHash* tabla;
	tabla=(TablaHash*)malloc(sizeof(TablaHash));
	if(tabla == NULL){
		printf("No se ha podido asignar memoria a la tabla. \n");
	}
	tabla->hash=crearClase();
	return tabla;
}

//Funcion que crea un arreglo de Clases.
//Entrada:          Salida: Clase
Clase* crearClase(){
	Clase* clase;
	clase= (Clase*) malloc(sizeof(Clase)* 997);
	if(clase==NULL){
		printf("No se pudo asignar memoria a la clase. \n");
	}
	int x;
	for(x=0; x<997; x++){
		clase[x].arbolID=crearArbol();
	}
	return clase;
}

//Funcion que crea un NodoArbol.
//Entrada: Identificador   Salida: NodoArbol
NodoArbol* crearNodoArbol(int identificador){
	NodoArbol* nodo;
	nodo= (NodoArbol*)malloc(sizeof(NodoArbol));
	if(nodo==NULL){
		printf("No se pudo asignar memoria para el nodo\n");
	}
	nodo->padre=NULL;
	nodo->hijoI=NULL;
	nodo->hijoD=NULL;
	nodo->id= identificador;
	return nodo;
}

//Funcion que crea un arbol.
//Entrada:       Salida: arbol
Arbol* crearArbol(){
	Arbol* arbol;
	arbol=(Arbol*)malloc(sizeof(Arbol));
	if (arbol==NULL){
		printf("No se pudo asignar memoria al arbol\n");
	}
	arbol->raiz= NULL;
	return arbol;
}
//Funcion que busca un nodoArbol a partir de un identificador.
//Entrada: identificador     Salida: nodoArbol
NodoArbol* buscar(NodoArbol* raiz, int identificador){
	while((raiz!= NULL) && (identificador != raiz->id)){
		if(identificador< raiz->id){
			raiz= raiz->hijoI;
		}
		else{
			raiz= raiz->hijoD;
		}
	}
	return raiz;
}

//Funcion que genera una rotacion hacia la izquierda entre los NodoArboles de un arbol.
//Entrada: arbol, nodoArbol     Salida:
void rotarIzq(Arbol* a, NodoArbol* z){
	NodoArbol* raiz;
	raiz= z->hijoD;
	if(z->padre ==NULL){
		a->raiz= raiz;
	}
	else{
		if (z->id == z->padre->hijoI->id){
			z->padre->hijoI = raiz;
		}
		else{
			z->padre->hijoD= raiz;
		}
	}
	z->hijoD=raiz->hijoI;
	raiz->hijoI= z;
	raiz->padre= z->padre;
	raiz->hijoI->padre=raiz;
	if(raiz->hijoD!= NULL){
		raiz->hijoD->padre= raiz;
	}
}

//Funcion que genera una rotacion hacia la derecha entre los NodoArboles de un arbol.
//Entrada: arbol, nodoArbol     Salida:
void rotarDer(Arbol* a, NodoArbol* z){
	NodoArbol* raiz;
	raiz= z->hijoI;
	if(z->padre ==NULL){
		a->raiz=raiz;
	}
	else{
		if(z->id == z->padre->hijoI->id){
			z->padre->hijoI=raiz;
		}
		else{
			z->padre->hijoD=raiz;
		}
	}
	z->hijoI= raiz->hijoD;
	raiz->hijoD= z;
	raiz->padre= z->padre;
	raiz->hijoD->padre= raiz;
	if(raiz->hijoI !=NULL){
		raiz->hijoI->padre= raiz;
	}
}

//Funcion que a partir de un NodoArbol, calcula la altura de dicho nodo.
//Entrada: NodoArbol      Salida: altura
int altura(NodoArbol* z){
	int HI;
	int HD;
	if((z->hijoD ==NULL) && (z->hijoI ==NULL))
		return 0;
	if(z->hijoD == NULL)
		HD=0;
	else
		HD=altura(z->hijoD);
	if(z->hijoI ==NULL)
		HI=0;
	else
		HI= altura(z->hijoI);
	if(HI > HD)
		return HI+ 1;
	else 
		return HD +1;
}

//Funcion que calcula la diferencia de alturas presente en un nodoArbol.
//Entrada: NodoArbol     Salida: diferencia de altura (entero)
int diferenciaAlturas(NodoArbol* z){
	int HI;
	int HD;
	if((z->hijoD !=NULL) || (z->hijoI !=NULL)){
		if((z->hijoD != NULL) && (z->hijoI != NULL)){
			HI= altura(z->hijoI);
			HD= altura(z->hijoD);
			return HI - HD;
		}
		if(z->hijoD == NULL){
			return 1+altura(z->hijoI);
		}
		if(z->hijoI ==NULL){
			return 0 - (1 + altura(z->hijoD)); 
		}
		return 0;
	}
	else{
		return 0;
	}
}

//Funcion que contiene todo el proceso logico para generar el balanceo de los nodos de un arbol.
//Entrada: arbol, nodoArbol    Salida:
void balancear(Arbol* a, NodoArbol* z){
	int diferencia1;
	int diferencia2;
	diferencia1= diferenciaAlturas(z);
	if(diferencia1 >1){
		diferencia2= diferenciaAlturas(z->hijoI);
		if(diferencia2 <0){
			rotarIzq(a,z->hijoI);
		}
		rotarDer(a,z);
	}
	if(diferencia1 <-1){
		diferencia2= diferenciaAlturas(z->hijoD);
		if(diferencia2 >0){
			rotarDer(a,z->hijoD);
		}
		rotarIzq(a,z);
	}
}

//Funcion con la cual se inserta un nodoArbol al arbol y ademas se generan los procesos para que dicho arbol permanesca balanceado.
//Entrada: arbol, nodoArbol    Salida: 
void insertarArbol(Arbol* a, NodoArbol* z){
	NodoArbol* y;
	NodoArbol* x;
	if(a->raiz ==NULL){
		a->raiz= z;
		return;
	}
	else{
		x= a->raiz;
		while(x!= NULL){
			y=x;
			if(z->id < x->id){
				x=x->hijoI;
			}
			else{
				x= x->hijoD;
			}
		}
		if(z->id < y->id){
			y->hijoI= z;
		}
		else{
			y->hijoD= z;
		}
		z->padre=y;
		while(y!=NULL){
			balancear(a,y);
			y=y->padre;
		}
	}
	
}

//Funcion que obtiene el minimo de un nodo.
//Entrada: NodoArbol    Salida: NodoArbol
NodoArbol* extraerMinimo(NodoArbol* x){
	while(x->hijoI != NULL){
		x= x->hijoI;
	}
	return x;
}

//Funcion que "transplanta" los sub-arboles de un NodoArbol hacia una nueva posicion dentro del arbol.
//Entrada: arbol, NodoArbol, NodoArbol     Salida: 
void transplantar(Arbol* a, NodoArbol* u, NodoArbol* v){
	if(u->padre == NULL){
		a->raiz = v;
	}
	else if(u->id == u->padre->hijoI->id){
		u->padre->hijoI=v;
	}
	else{
		u->padre->hijoD=v;
	}
	if(v != NULL){
		v->padre= u->padre;
	}
}

//Funcion que borra un NodoArbol del arbol.
//Entrada: arbol, NodoArbol     Salida: 
void borrarDato(Arbol* a, NodoArbol* z){
	if(z->hijoI ==NULL){
		transplantar(a,z,z->hijoD);
	}
	else if(z->hijoD ==NULL){
		transplantar(a,z,z->hijoI);
	}
	else{
		NodoArbol* y;
		y= extraerMinimo(z->hijoD);
		if(z->id != y->padre->id){
			transplantar(a,y,y->hijoD);
			y->hijoD= z->hijoD;
			y->hijoD->padre=y;
		}
		transplantar(a,z,y);
		y->hijoI= z->hijoI;
		y->hijoI->padre=y;
	}
}

//Funcion que se encarga de correr el cursor de lectura.
//Entrada:              Salida: 1 
int limpiarStdin(){
    while (getchar()!='\n');
    return 1;
}

//Funcion que libera la memoria utilizada en el Arbol y todos sus componentes
//Entrada: raiz         Salida: 
void vaciarArbol(NodoArbol* raiz){
	if(raiz!= NULL){
		vaciarArbol(raiz->hijoI);
		vaciarArbol(raiz->hijoD);
		free(raiz);
	}
}

//Funcion que calcula el modulo de el entero ingresado
//Entrada: id      Salida: resultado
int funcionHash(int id){
	int resultado;
	resultado= abs(id% 997);
	return resultado;
}

//Funcion que vacia la memoria asignada durante la ejecucion del programa.
//Entrada: tabla     Salida: 
void vaciarHash(TablaHash* tabla){
	int x;
	for(x=0; x<997; x++){
		vaciarArbol(tabla->hash[x].arbolID->raiz);
		free(tabla->hash[x].arbolID);
	}
	free(tabla->hash);
	free(tabla);
}
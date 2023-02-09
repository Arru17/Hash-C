#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct tablaHash TablaHash;
typedef struct clase Clase;
typedef struct lista Lista;
typedef struct nodo Nodo;

FILE* abrirArchivo(char* nombre);
TablaHash* crearTabla();
Clase* crearClase();
Lista* crearLista();
Nodo* crearNodo(int identificador);
Nodo* revisarLista(Lista* lista, int identificador);
int limpiarStdin();
void eliminarID(Lista* lista, int identificador);
void vaciarLista(Lista* lista);
void insertarEnLista(Lista* lista, Nodo* nodo);
int funcionHash(int id);
void vaciarHash(TablaHash* tabla);

typedef struct tablaHash{
	Clase* hash;
}TablaHash;

typedef struct clase{
	Lista* listaID;
}Clase;

typedef struct lista{
	Nodo* primero;
	Nodo* ultimo;
	int largo;
}Lista;

typedef struct nodo{
	Nodo* siguiente;
	int id;
}Nodo;

//Funcion que abre un archivo en formato .txt para su lectura
//Entrada: nombre     Salida: FILE*
FILE* abrirArchivo(char* nombre){
	FILE* archivo;
	archivo= fopen(nombre,"r");
	return archivo;
}

//Funcion que crea una tabla hash.
//Entrada:        Salida: tabla
TablaHash* crearTabla(){
	TablaHash* tabla;
	tabla=(TablaHash*)malloc(sizeof(TablaHash));
	if(tabla ==NULL){
		printf("No se pudo asignar memoria a la tabla Hash. \n");
	}
	tabla->hash= crearClase();
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
		clase[x].listaID=crearLista();
	}
	return clase;
}

//Funcion que crea una lista.
//Entrada:           Salida: lista
Lista* crearLista(){
	Lista* lista;
	lista=(Lista*)malloc(sizeof(Lista));
	if(lista==NULL){
		printf("No se pudo asignar memoria a la lista.\n");
		return NULL;
	}
	lista->primero=NULL;
	lista->ultimo=NULL;
	lista->largo=0;
	return lista;
}

//Funcion que crea un nodo con su respectivo id.
//Entrada: identificador        Salida: nodo
Nodo* crearNodo(int identificador){
	Nodo* nodo;
	nodo=(Nodo*)malloc(sizeof(Nodo));
	if(nodo== NULL){
		printf("No se pudo asignar memoria al nodo.\n");
	}
	nodo->siguiente= NULL;
	nodo->id= identificador;
	return nodo;
}

//Funcion que busca un Nodo a partir de un identificador.
//Entrada: lista, identificador    Salida: Nodo
Nodo* revisarLista(Lista* lista, int identificador){
	Nodo* auxiliar;
	Nodo* retorno= NULL;
	auxiliar= lista->primero;
	while(auxiliar != NULL){
		if(identificador == auxiliar->id){
			retorno = auxiliar;
		}else{
			
		}
		auxiliar= auxiliar->siguiente;
	}
	return retorno;
}

//Funcion que se encarga de correr el cursor de lectura.
//Entrada:              Salida: 1 
int limpiarStdin(){
    while (getchar()!='\n');
    return 1;
}

//Funcion que elimina un registro en una lista.
//Entrada: lista, identificador       Salida:
void eliminarID(Lista* lista, int identificador){
	Nodo* auxiliar;
	Nodo* aux2;
	Nodo* aux3;
	auxiliar= lista->primero;
	int contador =0;
	while(auxiliar != NULL){
		contador= (contador+1);
		if(auxiliar->id == identificador){
			if(contador==1){
				lista->primero= auxiliar->siguiente;
				if(auxiliar->siguiente==NULL){
					lista->ultimo= auxiliar->siguiente;
				}
				aux2=auxiliar;
				auxiliar= auxiliar->siguiente;
				free(aux2);
			}else{
				aux2->siguiente= auxiliar->siguiente;
				aux3=auxiliar;
				auxiliar=auxiliar->siguiente;
				free(aux3);
			}
		}
		else if(contador == (lista->largo - 1)){
			lista->ultimo= auxiliar;
			aux2= auxiliar->siguiente;
			auxiliar->siguiente= NULL;
			auxiliar=auxiliar->siguiente;
			free(aux2);
		}	
		else{
			aux2= auxiliar;
			auxiliar= auxiliar->siguiente;
		}
	}
}

//Funcion que libera la memoria de una lista.
//Entrada: Lista     Salida:
void vaciarLista(Lista* lista){
	Nodo* auxiliar;
	auxiliar=lista->primero;
	while(auxiliar!=NULL){
	    Nodo* aux2=auxiliar; 
		auxiliar=auxiliar->siguiente;
		free(aux2);
	}
	free(lista);
}

//Funcion que inserta un nodo en una lista.
//Entrada: lista, Nodo      Salida: 
void insertarEnLista(Lista* lista, Nodo* nodo){
	if(lista->primero==NULL){
		lista->primero=nodo;
		lista->ultimo=nodo;
		lista->ultimo->siguiente=NULL;
		lista->largo=(lista->largo +1);
	}else{
		lista->ultimo->siguiente=nodo;
		lista->ultimo=nodo;
		nodo->siguiente=NULL;
		lista->largo=(lista->largo +1);
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
		vaciarLista(tabla->hash[x].listaID);
	}
	free(tabla->hash);
	free(tabla);
}
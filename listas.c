#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesLab4Listas.h"
#include <time.h>

int main(){
	int dato;
	char nombreArchivo1[10]= "datos.txt";
	FILE* archivo= abrirArchivo(nombreArchivo1);
	TablaHash* tabla= crearTabla();
	while(feof(archivo)==0){
		fscanf(archivo, "%d", &dato);
		int posicion;
		posicion= funcionHash(dato);
		Nodo* registro;
		registro= revisarLista(tabla->hash[posicion].listaID, dato);
		if (registro==NULL){ //Se revisa si es que el id ya estaba ingresado con anterioridad.
			Nodo* nodo;
			nodo= crearNodo(dato);
			insertarEnLista(tabla->hash[posicion].listaID, nodo);
		}
		else{
			
		}
		if (fgetc(archivo) == '\r') {
			fgetc(archivo);
		}
	}
	char nombreArchivo2[16]= "operaciones.txt";
	char operacion;
	int identificadorOperacion;
	FILE* operaciones;
	operaciones= abrirArchivo(nombreArchivo2);
	while(feof(operaciones)==0){
		fscanf(operaciones,"%c %d", &operacion, &identificadorOperacion);
		int posicionDato;
		Nodo* individuo;
		time_t comienzo;
		time_t termino;
		if((int)operacion == (int)'B'){
			comienzo= time(NULL);
			posicionDato= funcionHash(identificadorOperacion);
			individuo= revisarLista(tabla->hash[posicionDato].listaID, identificadorOperacion);
			if(individuo==NULL){
				termino= time(NULL);
				printf("N/E, %f \n", difftime(termino, comienzo));
			}
			else{
				termino= time(NULL);
				printf("TRUE, %f \n", difftime(termino, comienzo));
			}
		}else if((int)operacion == (int)'E'){
			comienzo= time(NULL);
			posicionDato= funcionHash(identificadorOperacion);
			individuo= revisarLista(tabla->hash[posicionDato].listaID,identificadorOperacion);
			if(individuo==NULL){
				termino= time(NULL);
				printf("FALSE, %f \n", difftime(termino, comienzo));
			}
			else{
				eliminarID(tabla->hash[posicionDato].listaID, identificadorOperacion);
				termino= time(NULL);
				printf("TRUE, %f \n", difftime(termino, comienzo));
			}
		}else if((int)operacion == (int)'A'){
			comienzo= time(NULL);
			posicionDato= funcionHash(identificadorOperacion);
			individuo = revisarLista(tabla->hash[posicionDato].listaID, identificadorOperacion);
			if(individuo==NULL){
				Nodo* nuevoDato;
				nuevoDato= crearNodo(identificadorOperacion);
				insertarEnLista(tabla->hash[posicionDato].listaID, nuevoDato);
				termino= time(NULL);
				printf("TRUE, %f \n", difftime(termino, comienzo));
			}
			else{
				termino= time(NULL);
				printf("FALSE, %f \n", difftime(termino, comienzo));
			}
		}else{
			
		}
	}
	vaciarHash(tabla);
		
	return 1;
}
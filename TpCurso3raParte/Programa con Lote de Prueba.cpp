// TP2018Algoritmos con Lote de Prueba

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <fstream>
#include <wchar.h>
#include <locale.h>
#include <windows.h> 
using namespace std;

//VARIABLES GLOBALES
const int cantCaracteres = 30;
const int cantCandidatos = 25;
const int cantListas = 5;
const int cantBancas = 13;
int cantTotalVotosValidos = 0;
int cantTotalVotosEnBlanco = 0;
int cantTotalVotosNulos = 0;
const int cantVotosTotales = 300;
const int cantTotalParticipantes = 65;
const char* ARCHIVO_LISTAS = "listas.bin";
const char* ARCHIVO_VOTOS = "votos.bin";

// STRUCTS
struct sVotos {
	int numeroLista;
	int	tipoVoto; // numero entre 1 y 7 , 0 es blanco y otro es nulo
	char sexo[cantCaracteres];
	int edad;
}votos[cantVotosTotales];

struct sListas {
	int numeroLista;
	char nombreLista[cantCaracteres]; // palabra de 20 letras maximo
	char candidatos[cantCandidatos][cantCaracteres]; //array de 25 palabras
	int cantVotosTotales;
	int cantVotosValidos;
	int porcentajeVotosValidos;
	int hasta18; //cantidad de votos de menores de 18 aï¿½os
	int hasta30; //cantidad de votos > 18 y < 30
	int hasta50; //cantidad de votos > 30 y < 50
	int mas50; //cantidad de votos mayores de 50 aï¿½os;
}listas[cantListas];

struct sBancas
{
	int cantBanca1;
	int cantBanca2;
	int cantBanca3;
	int cantBanca4;
	int cantBanca5;
	int cantBanca6;
	int cantBanca7;
	int cantBanca8;
	int cantBanca9;
	int cantBanca10;
	int cantBanca11;
	int cantBanca12;
	int cantBanca13;

}bancas[cantListas];

struct sGanadores
{
	int numBanca;
	int numLista;
	int cantVotos;
	char candidato[cantCaracteres];
}ganadores[cantTotalParticipantes];

//LISTAS ENLAZADAS
struct nodoVotos //sublista
{
	sVotos voto;
	int clave; // usamos la edad como clave
	nodoVotos *siguiente;
};
struct nodoListasVotadas //lista con sublista
{
	sListas lista;
	int clave; // usamos el num_lista como clave
	nodoVotos *infoVoto;
	nodoListasVotadas *siguiente;
};


//PROTOTIPOS
void inicializarGanador(sGanadores & ganador);
void inicializarGanadores();
void inicializarBanca(sBancas & banca);
void inicializarBancas();
void inicializarVoto(sVotos & voto);
void inicializarLista(sListas & lista);
void inicializarListas();
void cargarListas();
void cargarCandidatos(sListas & auxLista);
void cargarVotos();
void leerListas();
void procesarVotos(nodoListasVotadas * & raizListas);
void asignarBancas(nodoListasVotadas * & raizListas);
void ordenarListas(sListas lista[cantListas]);
void mostrarTabla();
void guardarParticipantes();
void ordenarParticipantes(sGanadores ganadores[cantTotalParticipantes]);
void mostrarListasPorEdad();
void setearColor(int rgb);
void mostrarLoteDePrueba(nodoListasVotadas * & raizListas);
// PROTOTIPOS LISTAS ENLAZADAS
bool buscarEnLista(nodoListasVotadas * raiz,nodoListasVotadas * & aux,int clave);
void insertarOrdenadoListaVotadas(nodoListasVotadas * & raiz,sListas lista,int clave);
void insertarOrdenadoVotos(nodoVotos * & raiz,sVotos voto,int clave);

// func for debug 
void mostrarLista(sListas lista){ 
	 
	printf("<-------- DEBUGGING -------->\n"); 
	printf("Nombre lista: %s\n",lista.nombreLista); 
	printf("numeroLista: %d\n",lista.numeroLista); 
	printf("votos tot: %d\n",lista.cantVotosTotales); 
	printf("votos val: %d\n",lista.cantVotosValidos); 
	printf("% votos val: %d\n",lista.porcentajeVotosValidos); 
	printf("votos hasta 18: %d\n",lista.hasta18); 
	printf("votos hasta 30: %d\n",lista.hasta30); 
	printf("votos hasta 50: %d\n",lista.hasta50); 
	printf("votos mas de 50: %d\n",lista.mas50); 
	
	
	printf("Candidatos:\n"); 
	 
  
	for (int f = 0; f < cantCandidatos; f++)  
	{  
		printf("--> %s\n",lista.candidatos[f]); 
	}   
} 
void mostrarVoto(sVotos voto){
	printf("Voto lista: %d\n",voto.numeroLista);
	printf("Voto tipo: %d\n",voto.tipoVoto);
	printf("Voto sexo: %s\n",voto.sexo);
	printf("Voto edad: %d\n",voto.edad);
}
void mostrarArchivos(){ 

	sListas lista;
	sVotos voto;
	 
	printf("<-------- DEBUGGING LISTA -------->\n"); 
	
	FILE * a = fopen(ARCHIVO_LISTAS,"rb");
	fread(&lista,sizeof(sListas),1,a);
	while(!feof(a)){
		
		mostrarLista(lista);
		
		fread(&lista,sizeof(sListas),1,a);
	}
	
	fclose(a);
	
	
	printf("<-------- DEBUGGING VOTOS -------->\n"); 
	
	FILE * b = fopen(ARCHIVO_VOTOS,"rb");
	fread(&voto,sizeof(sVotos),1,b);
	while(!feof(b)){
		
		mostrarVoto(voto);
		
		fread(&voto,sizeof(sVotos),1,b);
	}
	fclose(b);
} 

int main()
{	
	setlocale(LC_ALL, ""); //habilita caracteres latinos
	
	nodoListasVotadas * listadoListas = NULL;

	inicializarListas();

	cargarListas();

	cargarVotos();

	procesarVotos(listadoListas);
	
	mostrarLoteDePrueba(listadoListas);

	asignarBancas(listadoListas);

	ordenarListas(listas);

	guardarParticipantes();

	ordenarParticipantes(ganadores);

	mostrarTabla();

	mostrarListasPorEdad();

	system("pause");

	return 0;
}

//METODOS LISTAS ENLAZADAS

bool buscarLista(nodoListasVotadas * raiz,nodoListasVotadas * & aux,int clave)
{
	nodoListasVotadas *actual = raiz;

	while (actual != NULL && actual->clave != clave)
	{
		actual = actual->siguiente;
	}
	
	if(actual == NULL){
		return false;
	} else {
		aux = actual;
		return true;
	}
}

void insertarOrdenadoListaVotadas(nodoListasVotadas * & raiz,sListas lista,int clave)
{
	nodoListasVotadas * aux = new nodoListasVotadas();
	
	aux->clave = clave;
	aux->lista = lista;
	aux->infoVoto = NULL;
	
	// Si la lista esta vacia
	if(raiz == NULL) {
		aux->siguiente = NULL;
		raiz = aux;
	} else {
		// Si debe ir primero
		if (raiz->clave > clave){
			aux->siguiente = raiz;
			raiz = aux;
		} else {
			// Si debe ir despues del primero
			nodoListasVotadas * aux2 = raiz;
			while(aux2->siguiente != NULL && aux2->siguiente->clave <= clave) {
				aux2 = aux2->siguiente;
			}
			
			aux->siguiente = aux2->siguiente;
			aux2->siguiente = aux;
		}
	}
	
}

void insertarOrdenadoVotos(nodoVotos * & raiz,sVotos voto,int clave)
{
	nodoVotos * aux = new nodoVotos();
	
	aux->clave = clave;
	aux->voto = voto;
	
	// Si la lista esta vacia
	if(raiz == NULL) {
		aux->siguiente = NULL;
		raiz = aux;
	} else {
		// Si debe ir primero
		if (raiz->clave > clave){
			aux->siguiente = raiz;
			raiz = aux;
		} else {
			// Si debe ir despues del primero
			nodoVotos * aux2 = raiz;
			while(aux2->siguiente != NULL && aux2->siguiente->clave <= clave) {
				aux2 = aux2->siguiente;
			}
			
			aux->siguiente = aux2->siguiente;
			aux2->siguiente = aux;
		}
	}
	
}
//////////

void inicializarGanador(sGanadores & ganador) {
	ganador.numBanca = 0;
	ganador.numLista = 0;
	ganador.cantVotos = 0;
	memset(ganador.candidato, ' ', cantCaracteres);
	ganador.candidato[cantCaracteres] = '\0';
}
void inicializarGanadores() {
	for(int i=0; i<cantTotalParticipantes; i++) {
		inicializarGanador(ganadores[i]);
	}
}
void inicializarVoto(sVotos & voto) {
	voto.numeroLista = 0;
	voto.tipoVoto = 0;
	
	memset(voto.sexo, ' ', cantCaracteres);
	voto.sexo[cantCaracteres] = '\0';
	
	voto.edad = 0;
}
void inicializarBanca(sBancas & banca) {
	banca.cantBanca1 = 0;
	banca.cantBanca2 = 0;
	banca.cantBanca3 = 0;
	banca.cantBanca4 = 0;
	banca.cantBanca5 = 0;
	banca.cantBanca6 = 0;
	banca.cantBanca7 = 0;
	banca.cantBanca8 = 0;
	banca.cantBanca9 = 0;
	banca.cantBanca10 = 0;
	banca.cantBanca11 = 0;
	banca.cantBanca12 = 0;
	banca.cantBanca13 = 0;
}
void inicializarBancas() {
	for(int i=0; i<cantListas; i++){
		inicializarBanca(bancas[i]);
	}
}
void inicializarLista(sListas & lista) {
	memset(lista.nombreLista, ' ', cantCaracteres);
	lista.nombreLista[cantCaracteres] = '\0';
	lista.hasta18 = 0;
	lista.hasta30 = 0;
	lista.hasta50 = 0;
	lista.mas50 = 0;
	lista.cantVotosTotales = 0;
	lista.cantVotosValidos = 0;
	lista.numeroLista = 0;
	lista.porcentajeVotosValidos = 0;

	for (int f = 0; f < cantCandidatos; f++)
	{
		memset(lista.candidatos[f], ' ', cantCaracteres);
		lista.candidatos[f][cantCaracteres] = '\0';
	}
}
void inicializarListas(){
	for (int i = 0; i < cantListas; i++)
	{
		inicializarLista(listas[i]);
	}
}

// carga el nombre de los 25 candidatos hechos automaticamente en la lista pasada por parametro 
void cargarCandidatos(sListas & auxLista) 
{
	char auxCand[cantCaracteres];
	int b = 0;
	
	for (int a = 0; a < cantCandidatos; a++)
	{
		memset(auxCand, ' ', cantCaracteres); 
		auxCand[cantCaracteres] = '\0'; 
		
		b = a+1;
		sprintf(auxCand,"candidato%d/Lista%d",b,auxLista.numeroLista);

		strcpy(auxLista.candidatos[a], auxCand);
	}
}

// Se guardan en un archivo los datos de todas las listas.
void cargarListas()
{
	sListas auxLista;

	FILE * a = fopen(ARCHIVO_LISTAS,"wb");

	for (int i = 0; i < cantListas; i++)
	{		
		// Inicializamos la lista auxiliar en cada vuelta para vaciarla antes de cargarle datos
		inicializarLista(auxLista);
		
		auxLista.numeroLista = i+1;
		
		switch(i){
			case 0: strcpy(auxLista.nombreLista,"BLANCA"); break;
			case 1: strcpy(auxLista.nombreLista,"VERDE"); break;
			case 2: strcpy(auxLista.nombreLista,"ROJA"); break;
			case 3: strcpy(auxLista.nombreLista,"AZUL"); break;
			case 4: strcpy(auxLista.nombreLista,"VIOLETA"); break;
		}

		cargarCandidatos(auxLista);
		
		fwrite(&auxLista,sizeof(sListas),1,a);
	}
	fclose(a);
}

void cargarVotos()
{		
	// inicializo cada voto
	for (int z=0; z<cantVotosTotales; z++){
		inicializarVoto(votos[z]);
	}
	
	// hardcodeo los votos
	votos[0].numeroLista = 2; votos[0].tipoVoto = 5; strcpy(votos[0].sexo,"Masculino"); votos[0].edad = 64;
	votos[1].numeroLista = 3; votos[1].tipoVoto = 4; strcpy(votos[1].sexo,"Femenino"); votos[1].edad = 48;
	votos[2].numeroLista = 1; votos[2].tipoVoto = 2; strcpy(votos[2].sexo,"Masculino"); votos[2].edad = 44;
	votos[3].numeroLista = 5; votos[3].tipoVoto = 5; strcpy(votos[3].sexo,"Masculino"); votos[3].edad = 56;
	votos[4].numeroLista = 3; votos[4].tipoVoto = 8; strcpy(votos[4].sexo,"Masculino"); votos[4].edad = 18;
	votos[5].numeroLista = 2; votos[5].tipoVoto = 6; strcpy(votos[5].sexo,"Masculino"); votos[5].edad = 39;
	votos[6].numeroLista = 4; votos[6].tipoVoto = 5; strcpy(votos[6].sexo,"Femenino"); votos[6].edad = 17;
	votos[7].numeroLista = 1; votos[7].tipoVoto = 0; strcpy(votos[7].sexo,"Femenino"); votos[7].edad = 26;
	votos[8].numeroLista = 4; votos[8].tipoVoto = 8; strcpy(votos[8].sexo,"Masculino"); votos[8].edad = 41;
	votos[9].numeroLista = 4; votos[9].tipoVoto = 7; strcpy(votos[9].sexo,"Masculino"); votos[9].edad = 62;
	votos[10].numeroLista = 2; votos[10].tipoVoto = 5; strcpy(votos[10].sexo,"Femenino"); votos[10].edad = 42;
	votos[11].numeroLista = 4; votos[11].tipoVoto = 7; strcpy(votos[11].sexo,"Femenino"); votos[11].edad = 36;
	votos[12].numeroLista = 5; votos[12].tipoVoto = 6; strcpy(votos[12].sexo,"Femenino"); votos[12].edad = 33;
	votos[13].numeroLista = 5; votos[13].tipoVoto = 5; strcpy(votos[13].sexo,"Masculino"); votos[13].edad = 62;
	votos[14].numeroLista = 1; votos[14].tipoVoto = 2; strcpy(votos[14].sexo,"Masculino"); votos[14].edad = 63;
	votos[15].numeroLista = 2; votos[15].tipoVoto = 2; strcpy(votos[15].sexo,"Femenino"); votos[15].edad = 68;
	votos[16].numeroLista = 1; votos[16].tipoVoto = 7; strcpy(votos[16].sexo,"Masculino"); votos[16].edad = 62;
	votos[17].numeroLista = 1; votos[17].tipoVoto = 0; strcpy(votos[17].sexo,"Masculino"); votos[17].edad = 23;
	votos[18].numeroLista = 3; votos[18].tipoVoto = 7; strcpy(votos[18].sexo,"Femenino"); votos[18].edad = 52;
	votos[19].numeroLista = 4; votos[19].tipoVoto = 6; strcpy(votos[19].sexo,"Femenino"); votos[19].edad = 32;
	votos[20].numeroLista = 3; votos[20].tipoVoto = 1; strcpy(votos[20].sexo,"Femenino"); votos[20].edad = 55;
	votos[21].numeroLista = 5; votos[21].tipoVoto = 2; strcpy(votos[21].sexo,"Femenino"); votos[21].edad = 38;
	votos[22].numeroLista = 5; votos[22].tipoVoto = 8; strcpy(votos[22].sexo,"Masculino"); votos[22].edad = 33;
	votos[23].numeroLista = 5; votos[23].tipoVoto = 8; strcpy(votos[23].sexo,"Femenino"); votos[23].edad = 40;
	votos[24].numeroLista = 1; votos[24].tipoVoto = 2; strcpy(votos[24].sexo,"Femenino"); votos[24].edad = 50;
	votos[25].numeroLista = 2; votos[25].tipoVoto = 2; strcpy(votos[25].sexo,"Femenino"); votos[25].edad = 46;
	votos[26].numeroLista = 2; votos[26].tipoVoto = 0; strcpy(votos[26].sexo,"Femenino"); votos[26].edad = 35;
	votos[27].numeroLista = 1; votos[27].tipoVoto = 4; strcpy(votos[27].sexo,"Femenino"); votos[27].edad = 48;
	votos[28].numeroLista = 5; votos[28].tipoVoto = 4; strcpy(votos[28].sexo,"Masculino"); votos[28].edad = 56;
	votos[29].numeroLista = 5; votos[29].tipoVoto = 5; strcpy(votos[29].sexo,"Femenino"); votos[29].edad = 53;
	votos[30].numeroLista = 3; votos[30].tipoVoto = 0; strcpy(votos[30].sexo,"Masculino"); votos[30].edad = 50;
	votos[31].numeroLista = 1; votos[31].tipoVoto = 4; strcpy(votos[31].sexo,"Masculino"); votos[31].edad = 27;
	votos[32].numeroLista = 4; votos[32].tipoVoto = 7; strcpy(votos[32].sexo,"Masculino"); votos[32].edad = 75;
	votos[33].numeroLista = 2; votos[33].tipoVoto = 4; strcpy(votos[33].sexo,"Femenino"); votos[33].edad = 22;
	votos[34].numeroLista = 4; votos[34].tipoVoto = 0; strcpy(votos[34].sexo,"Masculino"); votos[34].edad = 18;
	votos[35].numeroLista = 5; votos[35].tipoVoto = 5; strcpy(votos[35].sexo,"Masculino"); votos[35].edad = 34;
	votos[36].numeroLista = 5; votos[36].tipoVoto = 1; strcpy(votos[36].sexo,"Femenino"); votos[36].edad = 72;
	votos[37].numeroLista = 1; votos[37].tipoVoto = 5; strcpy(votos[37].sexo,"Masculino"); votos[37].edad = 43;
	votos[38].numeroLista = 3; votos[38].tipoVoto = 2; strcpy(votos[38].sexo,"Femenino"); votos[38].edad = 42;
	votos[39].numeroLista = 2; votos[39].tipoVoto = 7; strcpy(votos[39].sexo,"Femenino"); votos[39].edad = 45;
	votos[40].numeroLista = 4; votos[40].tipoVoto = 7; strcpy(votos[40].sexo,"Masculino"); votos[40].edad = 41;
	votos[41].numeroLista = 4; votos[41].tipoVoto = 5; strcpy(votos[41].sexo,"Masculino"); votos[41].edad = 42;
	votos[42].numeroLista = 4; votos[42].tipoVoto = 4; strcpy(votos[42].sexo,"Femenino"); votos[42].edad = 63;
	votos[43].numeroLista = 4; votos[43].tipoVoto = 5; strcpy(votos[43].sexo,"Masculino"); votos[43].edad = 24;
	votos[44].numeroLista = 5; votos[44].tipoVoto = 0; strcpy(votos[44].sexo,"Masculino"); votos[44].edad = 73;
	votos[45].numeroLista = 4; votos[45].tipoVoto = 7; strcpy(votos[45].sexo,"Masculino"); votos[45].edad = 61;
	votos[46].numeroLista = 4; votos[46].tipoVoto = 3; strcpy(votos[46].sexo,"Masculino"); votos[46].edad = 33;
	votos[47].numeroLista = 3; votos[47].tipoVoto = 3; strcpy(votos[47].sexo,"Masculino"); votos[47].edad = 37;
	votos[48].numeroLista = 4; votos[48].tipoVoto = 3; strcpy(votos[48].sexo,"Masculino"); votos[48].edad = 49;
	votos[49].numeroLista = 1; votos[49].tipoVoto = 3; strcpy(votos[49].sexo,"Masculino"); votos[49].edad = 17;
	votos[50].numeroLista = 4; votos[50].tipoVoto = 1; strcpy(votos[50].sexo,"Masculino"); votos[50].edad = 43;
	votos[51].numeroLista = 1; votos[51].tipoVoto = 1; strcpy(votos[51].sexo,"Femenino"); votos[51].edad = 33;
	votos[52].numeroLista = 2; votos[52].tipoVoto = 3; strcpy(votos[52].sexo,"Masculino"); votos[52].edad = 71;
	votos[53].numeroLista = 5; votos[53].tipoVoto = 2; strcpy(votos[53].sexo,"Femenino"); votos[53].edad = 34;
	votos[54].numeroLista = 5; votos[54].tipoVoto = 5; strcpy(votos[54].sexo,"Masculino"); votos[54].edad = 70;
	votos[55].numeroLista = 2; votos[55].tipoVoto = 2; strcpy(votos[55].sexo,"Femenino"); votos[55].edad = 67;
	votos[56].numeroLista = 2; votos[56].tipoVoto = 4; strcpy(votos[56].sexo,"Femenino"); votos[56].edad = 50;
	votos[57].numeroLista = 1; votos[57].tipoVoto = 3; strcpy(votos[57].sexo,"Masculino"); votos[57].edad = 73;
	votos[58].numeroLista = 5; votos[58].tipoVoto = 6; strcpy(votos[58].sexo,"Femenino"); votos[58].edad = 57;
	votos[59].numeroLista = 1; votos[59].tipoVoto = 5; strcpy(votos[59].sexo,"Masculino"); votos[59].edad = 46;
	votos[60].numeroLista = 1; votos[60].tipoVoto = 3; strcpy(votos[60].sexo,"Masculino"); votos[60].edad = 61;
	votos[61].numeroLista = 1; votos[61].tipoVoto = 0; strcpy(votos[61].sexo,"Masculino"); votos[61].edad = 40;
	votos[62].numeroLista = 2; votos[62].tipoVoto = 5; strcpy(votos[62].sexo,"Femenino"); votos[62].edad = 58;
	votos[63].numeroLista = 2; votos[63].tipoVoto = 1; strcpy(votos[63].sexo,"Masculino"); votos[63].edad = 51;
	votos[64].numeroLista = 3; votos[64].tipoVoto = 3; strcpy(votos[64].sexo,"Femenino"); votos[64].edad = 55;
	votos[65].numeroLista = 2; votos[65].tipoVoto = 0; strcpy(votos[65].sexo,"Femenino"); votos[65].edad = 35;
	votos[66].numeroLista = 2; votos[66].tipoVoto = 2; strcpy(votos[66].sexo,"Masculino"); votos[66].edad = 36;
	votos[67].numeroLista = 3; votos[67].tipoVoto = 6; strcpy(votos[67].sexo,"Femenino"); votos[67].edad = 52;
	votos[68].numeroLista = 4; votos[68].tipoVoto = 0; strcpy(votos[68].sexo,"Masculino"); votos[68].edad = 20;
	votos[69].numeroLista = 2; votos[69].tipoVoto = 7; strcpy(votos[69].sexo,"Femenino"); votos[69].edad = 68;
	votos[70].numeroLista = 4; votos[70].tipoVoto = 7; strcpy(votos[70].sexo,"Masculino"); votos[70].edad = 59;
	votos[71].numeroLista = 3; votos[71].tipoVoto = 5; strcpy(votos[71].sexo,"Femenino"); votos[71].edad = 61;
	votos[72].numeroLista = 4; votos[72].tipoVoto = 0; strcpy(votos[72].sexo,"Masculino"); votos[72].edad = 54;
	votos[73].numeroLista = 3; votos[73].tipoVoto = 1; strcpy(votos[73].sexo,"Femenino"); votos[73].edad = 59;
	votos[74].numeroLista = 4; votos[74].tipoVoto = 2; strcpy(votos[74].sexo,"Masculino"); votos[74].edad = 24;
	votos[75].numeroLista = 5; votos[75].tipoVoto = 2; strcpy(votos[75].sexo,"Femenino"); votos[75].edad = 68;
	votos[76].numeroLista = 3; votos[76].tipoVoto = 1; strcpy(votos[76].sexo,"Masculino"); votos[76].edad = 55;
	votos[77].numeroLista = 2; votos[77].tipoVoto = 3; strcpy(votos[77].sexo,"Femenino"); votos[77].edad = 49;
	votos[78].numeroLista = 3; votos[78].tipoVoto = 1; strcpy(votos[78].sexo,"Femenino"); votos[78].edad = 25;
	votos[79].numeroLista = 1; votos[79].tipoVoto = 8; strcpy(votos[79].sexo,"Masculino"); votos[79].edad = 30;
	votos[80].numeroLista = 5; votos[80].tipoVoto = 5; strcpy(votos[80].sexo,"Femenino"); votos[80].edad = 16;
	votos[81].numeroLista = 3; votos[81].tipoVoto = 5; strcpy(votos[81].sexo,"Femenino"); votos[81].edad = 32;
	votos[82].numeroLista = 3; votos[82].tipoVoto = 8; strcpy(votos[82].sexo,"Femenino"); votos[82].edad = 32;
	votos[83].numeroLista = 4; votos[83].tipoVoto = 3; strcpy(votos[83].sexo,"Masculino"); votos[83].edad = 74;
	votos[84].numeroLista = 2; votos[84].tipoVoto = 1; strcpy(votos[84].sexo,"Femenino"); votos[84].edad = 49;
	votos[85].numeroLista = 2; votos[85].tipoVoto = 4; strcpy(votos[85].sexo,"Masculino"); votos[85].edad = 47;
	votos[86].numeroLista = 5; votos[86].tipoVoto = 1; strcpy(votos[86].sexo,"Masculino"); votos[86].edad = 62;
	votos[87].numeroLista = 5; votos[87].tipoVoto = 8; strcpy(votos[87].sexo,"Masculino"); votos[87].edad = 27;
	votos[88].numeroLista = 2; votos[88].tipoVoto = 3; strcpy(votos[88].sexo,"Femenino"); votos[88].edad = 39;
	votos[89].numeroLista = 3; votos[89].tipoVoto = 6; strcpy(votos[89].sexo,"Femenino"); votos[89].edad = 34;
	votos[90].numeroLista = 1; votos[90].tipoVoto = 1; strcpy(votos[90].sexo,"Femenino"); votos[90].edad = 67;
	votos[91].numeroLista = 3; votos[91].tipoVoto = 7; strcpy(votos[91].sexo,"Femenino"); votos[91].edad = 31;
	votos[92].numeroLista = 3; votos[92].tipoVoto = 3; strcpy(votos[92].sexo,"Masculino"); votos[92].edad = 26;
	votos[93].numeroLista = 5; votos[93].tipoVoto = 5; strcpy(votos[93].sexo,"Femenino"); votos[93].edad = 50;
	votos[94].numeroLista = 1; votos[94].tipoVoto = 5; strcpy(votos[94].sexo,"Femenino"); votos[94].edad = 16;
	votos[95].numeroLista = 4; votos[95].tipoVoto = 7; strcpy(votos[95].sexo,"Masculino"); votos[95].edad = 70;
	votos[96].numeroLista = 5; votos[96].tipoVoto = 8; strcpy(votos[96].sexo,"Femenino"); votos[96].edad = 46;
	votos[97].numeroLista = 3; votos[97].tipoVoto = 4; strcpy(votos[97].sexo,"Femenino"); votos[97].edad = 43;
	votos[98].numeroLista = 3; votos[98].tipoVoto = 6; strcpy(votos[98].sexo,"Femenino"); votos[98].edad = 44;
	votos[99].numeroLista = 5; votos[99].tipoVoto = 8; strcpy(votos[99].sexo,"Masculino"); votos[99].edad = 54;
	votos[100].numeroLista = 3; votos[100].tipoVoto = 0; strcpy(votos[100].sexo,"Femenino"); votos[100].edad = 75;
	votos[101].numeroLista = 5; votos[101].tipoVoto = 7; strcpy(votos[101].sexo,"Femenino"); votos[101].edad = 19;
	votos[102].numeroLista = 2; votos[102].tipoVoto = 0; strcpy(votos[102].sexo,"Femenino"); votos[102].edad = 35;
	votos[103].numeroLista = 4; votos[103].tipoVoto = 8; strcpy(votos[103].sexo,"Masculino"); votos[103].edad = 71;
	votos[104].numeroLista = 3; votos[104].tipoVoto = 7; strcpy(votos[104].sexo,"Femenino"); votos[104].edad = 50;
	votos[105].numeroLista = 1; votos[105].tipoVoto = 1; strcpy(votos[105].sexo,"Femenino"); votos[105].edad = 34;
	votos[106].numeroLista = 5; votos[106].tipoVoto = 4; strcpy(votos[106].sexo,"Masculino"); votos[106].edad = 45;
	votos[107].numeroLista = 2; votos[107].tipoVoto = 0; strcpy(votos[107].sexo,"Femenino"); votos[107].edad = 63;
	votos[108].numeroLista = 3; votos[108].tipoVoto = 1; strcpy(votos[108].sexo,"Masculino"); votos[108].edad = 54;
	votos[109].numeroLista = 1; votos[109].tipoVoto = 6; strcpy(votos[109].sexo,"Masculino"); votos[109].edad = 38;
	votos[110].numeroLista = 3; votos[110].tipoVoto = 0; strcpy(votos[110].sexo,"Masculino"); votos[110].edad = 17;
	votos[111].numeroLista = 3; votos[111].tipoVoto = 8; strcpy(votos[111].sexo,"Masculino"); votos[111].edad = 49;
	votos[112].numeroLista = 3; votos[112].tipoVoto = 3; strcpy(votos[112].sexo,"Masculino"); votos[112].edad = 46;
	votos[113].numeroLista = 2; votos[113].tipoVoto = 4; strcpy(votos[113].sexo,"Masculino"); votos[113].edad = 60;
	votos[114].numeroLista = 4; votos[114].tipoVoto = 2; strcpy(votos[114].sexo,"Masculino"); votos[114].edad = 29;
	votos[115].numeroLista = 4; votos[115].tipoVoto = 2; strcpy(votos[115].sexo,"Masculino"); votos[115].edad = 52;
	votos[116].numeroLista = 1; votos[116].tipoVoto = 4; strcpy(votos[116].sexo,"Femenino"); votos[116].edad = 48;
	votos[117].numeroLista = 4; votos[117].tipoVoto = 1; strcpy(votos[117].sexo,"Masculino"); votos[117].edad = 51;
	votos[118].numeroLista = 4; votos[118].tipoVoto = 7; strcpy(votos[118].sexo,"Masculino"); votos[118].edad = 25;
	votos[119].numeroLista = 2; votos[119].tipoVoto = 7; strcpy(votos[119].sexo,"Masculino"); votos[119].edad = 41;
	votos[120].numeroLista = 5; votos[120].tipoVoto = 7; strcpy(votos[120].sexo,"Femenino"); votos[120].edad = 36;
	votos[121].numeroLista = 1; votos[121].tipoVoto = 3; strcpy(votos[121].sexo,"Femenino"); votos[121].edad = 56;
	votos[122].numeroLista = 3; votos[122].tipoVoto = 1; strcpy(votos[122].sexo,"Femenino"); votos[122].edad = 55;
	votos[123].numeroLista = 2; votos[123].tipoVoto = 3; strcpy(votos[123].sexo,"Femenino"); votos[123].edad = 49;
	votos[124].numeroLista = 4; votos[124].tipoVoto = 5; strcpy(votos[124].sexo,"Masculino"); votos[124].edad = 57;
	votos[125].numeroLista = 3; votos[125].tipoVoto = 1; strcpy(votos[125].sexo,"Femenino"); votos[125].edad = 68;
	votos[126].numeroLista = 5; votos[126].tipoVoto = 7; strcpy(votos[126].sexo,"Femenino"); votos[126].edad = 25;
	votos[127].numeroLista = 4; votos[127].tipoVoto = 4; strcpy(votos[127].sexo,"Femenino"); votos[127].edad = 68;
	votos[128].numeroLista = 1; votos[128].tipoVoto = 7; strcpy(votos[128].sexo,"Masculino"); votos[128].edad = 65;
	votos[129].numeroLista = 3; votos[129].tipoVoto = 1; strcpy(votos[129].sexo,"Masculino"); votos[129].edad = 53;
	votos[130].numeroLista = 5; votos[130].tipoVoto = 3; strcpy(votos[130].sexo,"Masculino"); votos[130].edad = 30;
	votos[131].numeroLista = 2; votos[131].tipoVoto = 1; strcpy(votos[131].sexo,"Femenino"); votos[131].edad = 70;
	votos[132].numeroLista = 2; votos[132].tipoVoto = 3; strcpy(votos[132].sexo,"Masculino"); votos[132].edad = 40;
	votos[133].numeroLista = 4; votos[133].tipoVoto = 7; strcpy(votos[133].sexo,"Masculino"); votos[133].edad = 35;
	votos[134].numeroLista = 3; votos[134].tipoVoto = 8; strcpy(votos[134].sexo,"Masculino"); votos[134].edad = 30;
	votos[135].numeroLista = 1; votos[135].tipoVoto = 6; strcpy(votos[135].sexo,"Femenino"); votos[135].edad = 70;
	votos[136].numeroLista = 5; votos[136].tipoVoto = 1; strcpy(votos[136].sexo,"Femenino"); votos[136].edad = 52;
	votos[137].numeroLista = 5; votos[137].tipoVoto = 1; strcpy(votos[137].sexo,"Masculino"); votos[137].edad = 37;
	votos[138].numeroLista = 2; votos[138].tipoVoto = 4; strcpy(votos[138].sexo,"Femenino"); votos[138].edad = 55;
	votos[139].numeroLista = 2; votos[139].tipoVoto = 0; strcpy(votos[139].sexo,"Masculino"); votos[139].edad = 20;
	votos[140].numeroLista = 2; votos[140].tipoVoto = 1; strcpy(votos[140].sexo,"Masculino"); votos[140].edad = 30;
	votos[141].numeroLista = 3; votos[141].tipoVoto = 0; strcpy(votos[141].sexo,"Masculino"); votos[141].edad = 17;
	votos[142].numeroLista = 1; votos[142].tipoVoto = 2; strcpy(votos[142].sexo,"Femenino"); votos[142].edad = 30;
	votos[143].numeroLista = 1; votos[143].tipoVoto = 8; strcpy(votos[143].sexo,"Masculino"); votos[143].edad = 70;
	votos[144].numeroLista = 4; votos[144].tipoVoto = 2; strcpy(votos[144].sexo,"Masculino"); votos[144].edad = 44;
	votos[145].numeroLista = 3; votos[145].tipoVoto = 7; strcpy(votos[145].sexo,"Femenino"); votos[145].edad = 38;
	votos[146].numeroLista = 3; votos[146].tipoVoto = 5; strcpy(votos[146].sexo,"Femenino"); votos[146].edad = 64;
	votos[147].numeroLista = 2; votos[147].tipoVoto = 5; strcpy(votos[147].sexo,"Femenino"); votos[147].edad = 36;
	votos[148].numeroLista = 3; votos[148].tipoVoto = 5; strcpy(votos[148].sexo,"Masculino"); votos[148].edad = 22;
	votos[149].numeroLista = 4; votos[149].tipoVoto = 2; strcpy(votos[149].sexo,"Femenino"); votos[149].edad = 73;
	votos[150].numeroLista = 2; votos[150].tipoVoto = 0; strcpy(votos[150].sexo,"Masculino"); votos[150].edad = 46;
	votos[151].numeroLista = 5; votos[151].tipoVoto = 2; strcpy(votos[151].sexo,"Masculino"); votos[151].edad = 72;
	votos[152].numeroLista = 4; votos[152].tipoVoto = 6; strcpy(votos[152].sexo,"Masculino"); votos[152].edad = 42;
	votos[153].numeroLista = 2; votos[153].tipoVoto = 7; strcpy(votos[153].sexo,"Masculino"); votos[153].edad = 40;
	votos[154].numeroLista = 2; votos[154].tipoVoto = 3; strcpy(votos[154].sexo,"Masculino"); votos[154].edad = 52;
	votos[155].numeroLista = 4; votos[155].tipoVoto = 1; strcpy(votos[155].sexo,"Femenino"); votos[155].edad = 57;
	votos[156].numeroLista = 4; votos[156].tipoVoto = 0; strcpy(votos[156].sexo,"Masculino"); votos[156].edad = 36;
	votos[157].numeroLista = 3; votos[157].tipoVoto = 7; strcpy(votos[157].sexo,"Femenino"); votos[157].edad = 52;
	votos[158].numeroLista = 1; votos[158].tipoVoto = 5; strcpy(votos[158].sexo,"Femenino"); votos[158].edad = 24;
	votos[159].numeroLista = 4; votos[159].tipoVoto = 2; strcpy(votos[159].sexo,"Femenino"); votos[159].edad = 43;
	votos[160].numeroLista = 2; votos[160].tipoVoto = 1; strcpy(votos[160].sexo,"Masculino"); votos[160].edad = 30;
	votos[161].numeroLista = 1; votos[161].tipoVoto = 4; strcpy(votos[161].sexo,"Femenino"); votos[161].edad = 30;
	votos[162].numeroLista = 3; votos[162].tipoVoto = 1; strcpy(votos[162].sexo,"Femenino"); votos[162].edad = 30;
	votos[163].numeroLista = 2; votos[163].tipoVoto = 0; strcpy(votos[163].sexo,"Masculino"); votos[163].edad = 45;
	votos[164].numeroLista = 3; votos[164].tipoVoto = 2; strcpy(votos[164].sexo,"Masculino"); votos[164].edad = 16;
	votos[165].numeroLista = 3; votos[165].tipoVoto = 7; strcpy(votos[165].sexo,"Femenino"); votos[165].edad = 69;
	votos[166].numeroLista = 4; votos[166].tipoVoto = 6; strcpy(votos[166].sexo,"Femenino"); votos[166].edad = 68;
	votos[167].numeroLista = 5; votos[167].tipoVoto = 8; strcpy(votos[167].sexo,"Femenino"); votos[167].edad = 48;
	votos[168].numeroLista = 5; votos[168].tipoVoto = 7; strcpy(votos[168].sexo,"Femenino"); votos[168].edad = 60;
	votos[169].numeroLista = 2; votos[169].tipoVoto = 7; strcpy(votos[169].sexo,"Masculino"); votos[169].edad = 18;
	votos[170].numeroLista = 1; votos[170].tipoVoto = 5; strcpy(votos[170].sexo,"Femenino"); votos[170].edad = 18;
	votos[171].numeroLista = 3; votos[171].tipoVoto = 2; strcpy(votos[171].sexo,"Femenino"); votos[171].edad = 17;
	votos[172].numeroLista = 1; votos[172].tipoVoto = 5; strcpy(votos[172].sexo,"Femenino"); votos[172].edad = 44;
	votos[173].numeroLista = 4; votos[173].tipoVoto = 6; strcpy(votos[173].sexo,"Femenino"); votos[173].edad = 45;
	votos[174].numeroLista = 4; votos[174].tipoVoto = 3; strcpy(votos[174].sexo,"Masculino"); votos[174].edad = 17;
	votos[175].numeroLista = 1; votos[175].tipoVoto = 6; strcpy(votos[175].sexo,"Femenino"); votos[175].edad = 47;
	votos[176].numeroLista = 2; votos[176].tipoVoto = 6; strcpy(votos[176].sexo,"Masculino"); votos[176].edad = 22;
	votos[177].numeroLista = 1; votos[177].tipoVoto = 7; strcpy(votos[177].sexo,"Masculino"); votos[177].edad = 31;
	votos[178].numeroLista = 5; votos[178].tipoVoto = 0; strcpy(votos[178].sexo,"Masculino"); votos[178].edad = 71;
	votos[179].numeroLista = 3; votos[179].tipoVoto = 1; strcpy(votos[179].sexo,"Femenino"); votos[179].edad = 17;
	votos[180].numeroLista = 4; votos[180].tipoVoto = 8; strcpy(votos[180].sexo,"Femenino"); votos[180].edad = 60;
	votos[181].numeroLista = 1; votos[181].tipoVoto = 4; strcpy(votos[181].sexo,"Femenino"); votos[181].edad = 49;
	votos[182].numeroLista = 2; votos[182].tipoVoto = 0; strcpy(votos[182].sexo,"Femenino"); votos[182].edad = 66;
	votos[183].numeroLista = 5; votos[183].tipoVoto = 3; strcpy(votos[183].sexo,"Femenino"); votos[183].edad = 55;
	votos[184].numeroLista = 3; votos[184].tipoVoto = 5; strcpy(votos[184].sexo,"Femenino"); votos[184].edad = 73;
	votos[185].numeroLista = 1; votos[185].tipoVoto = 4; strcpy(votos[185].sexo,"Femenino"); votos[185].edad = 47;
	votos[186].numeroLista = 1; votos[186].tipoVoto = 0; strcpy(votos[186].sexo,"Masculino"); votos[186].edad = 54;
	votos[187].numeroLista = 4; votos[187].tipoVoto = 7; strcpy(votos[187].sexo,"Femenino"); votos[187].edad = 54;
	votos[188].numeroLista = 5; votos[188].tipoVoto = 7; strcpy(votos[188].sexo,"Masculino"); votos[188].edad = 24;
	votos[189].numeroLista = 2; votos[189].tipoVoto = 2; strcpy(votos[189].sexo,"Femenino"); votos[189].edad = 62;
	votos[190].numeroLista = 1; votos[190].tipoVoto = 3; strcpy(votos[190].sexo,"Femenino"); votos[190].edad = 74;
	votos[191].numeroLista = 5; votos[191].tipoVoto = 4; strcpy(votos[191].sexo,"Femenino"); votos[191].edad = 51;
	votos[192].numeroLista = 5; votos[192].tipoVoto = 2; strcpy(votos[192].sexo,"Masculino"); votos[192].edad = 63;
	votos[193].numeroLista = 5; votos[193].tipoVoto = 3; strcpy(votos[193].sexo,"Femenino"); votos[193].edad = 31;
	votos[194].numeroLista = 3; votos[194].tipoVoto = 7; strcpy(votos[194].sexo,"Femenino"); votos[194].edad = 27;
	votos[195].numeroLista = 1; votos[195].tipoVoto = 5; strcpy(votos[195].sexo,"Masculino"); votos[195].edad = 22;
	votos[196].numeroLista = 5; votos[196].tipoVoto = 2; strcpy(votos[196].sexo,"Femenino"); votos[196].edad = 36;
	votos[197].numeroLista = 1; votos[197].tipoVoto = 3; strcpy(votos[197].sexo,"Femenino"); votos[197].edad = 44;
	votos[198].numeroLista = 5; votos[198].tipoVoto = 6; strcpy(votos[198].sexo,"Masculino"); votos[198].edad = 67;
	votos[199].numeroLista = 3; votos[199].tipoVoto = 5; strcpy(votos[199].sexo,"Femenino"); votos[199].edad = 63;
	votos[200].numeroLista = 2; votos[200].tipoVoto = 6; strcpy(votos[200].sexo,"Femenino"); votos[200].edad = 38;
	votos[201].numeroLista = 2; votos[201].tipoVoto = 8; strcpy(votos[201].sexo,"Femenino"); votos[201].edad = 44;
	votos[202].numeroLista = 1; votos[202].tipoVoto = 0; strcpy(votos[202].sexo,"Femenino"); votos[202].edad = 56;
	votos[203].numeroLista = 5; votos[203].tipoVoto = 6; strcpy(votos[203].sexo,"Masculino"); votos[203].edad = 45;
	votos[204].numeroLista = 3; votos[204].tipoVoto = 2; strcpy(votos[204].sexo,"Masculino"); votos[204].edad = 64;
	votos[205].numeroLista = 4; votos[205].tipoVoto = 2; strcpy(votos[205].sexo,"Femenino"); votos[205].edad = 52;
	votos[206].numeroLista = 3; votos[206].tipoVoto = 0; strcpy(votos[206].sexo,"Masculino"); votos[206].edad = 37;
	votos[207].numeroLista = 4; votos[207].tipoVoto = 2; strcpy(votos[207].sexo,"Femenino"); votos[207].edad = 46;
	votos[208].numeroLista = 4; votos[208].tipoVoto = 5; strcpy(votos[208].sexo,"Masculino"); votos[208].edad = 64;
	votos[209].numeroLista = 2; votos[209].tipoVoto = 6; strcpy(votos[209].sexo,"Femenino"); votos[209].edad = 33;
	votos[210].numeroLista = 2; votos[210].tipoVoto = 2; strcpy(votos[210].sexo,"Femenino"); votos[210].edad = 38;
	votos[211].numeroLista = 2; votos[211].tipoVoto = 1; strcpy(votos[211].sexo,"Masculino"); votos[211].edad = 46;
	votos[212].numeroLista = 2; votos[212].tipoVoto = 3; strcpy(votos[212].sexo,"Masculino"); votos[212].edad = 69;
	votos[213].numeroLista = 2; votos[213].tipoVoto = 6; strcpy(votos[213].sexo,"Femenino"); votos[213].edad = 31;
	votos[214].numeroLista = 2; votos[214].tipoVoto = 2; strcpy(votos[214].sexo,"Femenino"); votos[214].edad = 24;
	votos[215].numeroLista = 4; votos[215].tipoVoto = 7; strcpy(votos[215].sexo,"Femenino"); votos[215].edad = 42;
	votos[216].numeroLista = 2; votos[216].tipoVoto = 0; strcpy(votos[216].sexo,"Femenino"); votos[216].edad = 26;
	votos[217].numeroLista = 1; votos[217].tipoVoto = 3; strcpy(votos[217].sexo,"Masculino"); votos[217].edad = 43;
	votos[218].numeroLista = 2; votos[218].tipoVoto = 3; strcpy(votos[218].sexo,"Femenino"); votos[218].edad = 23;
	votos[219].numeroLista = 1; votos[219].tipoVoto = 3; strcpy(votos[219].sexo,"Femenino"); votos[219].edad = 70;
	votos[220].numeroLista = 4; votos[220].tipoVoto = 3; strcpy(votos[220].sexo,"Femenino"); votos[220].edad = 70;
	votos[221].numeroLista = 2; votos[221].tipoVoto = 2; strcpy(votos[221].sexo,"Masculino"); votos[221].edad = 50;
	votos[222].numeroLista = 3; votos[222].tipoVoto = 6; strcpy(votos[222].sexo,"Femenino"); votos[222].edad = 33;
	votos[223].numeroLista = 4; votos[223].tipoVoto = 1; strcpy(votos[223].sexo,"Masculino"); votos[223].edad = 69;
	votos[224].numeroLista = 1; votos[224].tipoVoto = 0; strcpy(votos[224].sexo,"Masculino"); votos[224].edad = 65;
	votos[225].numeroLista = 2; votos[225].tipoVoto = 4; strcpy(votos[225].sexo,"Masculino"); votos[225].edad = 66;
	votos[226].numeroLista = 2; votos[226].tipoVoto = 0; strcpy(votos[226].sexo,"Masculino"); votos[226].edad = 52;
	votos[227].numeroLista = 5; votos[227].tipoVoto = 2; strcpy(votos[227].sexo,"Masculino"); votos[227].edad = 68;
	votos[228].numeroLista = 2; votos[228].tipoVoto = 1; strcpy(votos[228].sexo,"Masculino"); votos[228].edad = 69;
	votos[229].numeroLista = 3; votos[229].tipoVoto = 0; strcpy(votos[229].sexo,"Femenino"); votos[229].edad = 69;
	votos[230].numeroLista = 5; votos[230].tipoVoto = 5; strcpy(votos[230].sexo,"Femenino"); votos[230].edad = 20;
	votos[231].numeroLista = 3; votos[231].tipoVoto = 8; strcpy(votos[231].sexo,"Femenino"); votos[231].edad = 62;
	votos[232].numeroLista = 4; votos[232].tipoVoto = 0; strcpy(votos[232].sexo,"Masculino"); votos[232].edad = 39;
	votos[233].numeroLista = 1; votos[233].tipoVoto = 2; strcpy(votos[233].sexo,"Masculino"); votos[233].edad = 23;
	votos[234].numeroLista = 2; votos[234].tipoVoto = 1; strcpy(votos[234].sexo,"Masculino"); votos[234].edad = 57;
	votos[235].numeroLista = 2; votos[235].tipoVoto = 3; strcpy(votos[235].sexo,"Masculino"); votos[235].edad = 41;
	votos[236].numeroLista = 2; votos[236].tipoVoto = 2; strcpy(votos[236].sexo,"Femenino"); votos[236].edad = 41;
	votos[237].numeroLista = 2; votos[237].tipoVoto = 2; strcpy(votos[237].sexo,"Masculino"); votos[237].edad = 32;
	votos[238].numeroLista = 3; votos[238].tipoVoto = 3; strcpy(votos[238].sexo,"Masculino"); votos[238].edad = 23;
	votos[239].numeroLista = 1; votos[239].tipoVoto = 8; strcpy(votos[239].sexo,"Masculino"); votos[239].edad = 23;
	votos[240].numeroLista = 3; votos[240].tipoVoto = 5; strcpy(votos[240].sexo,"Femenino"); votos[240].edad = 47;
	votos[241].numeroLista = 5; votos[241].tipoVoto = 6; strcpy(votos[241].sexo,"Femenino"); votos[241].edad = 51;
	votos[242].numeroLista = 2; votos[242].tipoVoto = 6; strcpy(votos[242].sexo,"Femenino"); votos[242].edad = 18;
	votos[243].numeroLista = 3; votos[243].tipoVoto = 7; strcpy(votos[243].sexo,"Masculino"); votos[243].edad = 62;
	votos[244].numeroLista = 1; votos[244].tipoVoto = 5; strcpy(votos[244].sexo,"Masculino"); votos[244].edad = 41;
	votos[245].numeroLista = 3; votos[245].tipoVoto = 2; strcpy(votos[245].sexo,"Masculino"); votos[245].edad = 19;
	votos[246].numeroLista = 3; votos[246].tipoVoto = 0; strcpy(votos[246].sexo,"Femenino"); votos[246].edad = 69;
	votos[247].numeroLista = 4; votos[247].tipoVoto = 3; strcpy(votos[247].sexo,"Femenino"); votos[247].edad = 41;
	votos[248].numeroLista = 4; votos[248].tipoVoto = 2; strcpy(votos[248].sexo,"Masculino"); votos[248].edad = 43;
	votos[249].numeroLista = 2; votos[249].tipoVoto = 5; strcpy(votos[249].sexo,"Femenino"); votos[249].edad = 54;
	votos[250].numeroLista = 2; votos[250].tipoVoto = 5; strcpy(votos[250].sexo,"Masculino"); votos[250].edad = 71;
	votos[251].numeroLista = 3; votos[251].tipoVoto = 1; strcpy(votos[251].sexo,"Femenino"); votos[251].edad = 25;
	votos[252].numeroLista = 1; votos[252].tipoVoto = 0; strcpy(votos[252].sexo,"Masculino"); votos[252].edad = 68;
	votos[253].numeroLista = 5; votos[253].tipoVoto = 8; strcpy(votos[253].sexo,"Masculino"); votos[253].edad = 73;
	votos[254].numeroLista = 3; votos[254].tipoVoto = 5; strcpy(votos[254].sexo,"Masculino"); votos[254].edad = 66;
	votos[255].numeroLista = 5; votos[255].tipoVoto = 8; strcpy(votos[255].sexo,"Masculino"); votos[255].edad = 73;
	votos[256].numeroLista = 5; votos[256].tipoVoto = 2; strcpy(votos[256].sexo,"Femenino"); votos[256].edad = 19;
	votos[257].numeroLista = 5; votos[257].tipoVoto = 4; strcpy(votos[257].sexo,"Masculino"); votos[257].edad = 32;
	votos[258].numeroLista = 4; votos[258].tipoVoto = 2; strcpy(votos[258].sexo,"Masculino"); votos[258].edad = 50;
	votos[259].numeroLista = 2; votos[259].tipoVoto = 1; strcpy(votos[259].sexo,"Femenino"); votos[259].edad = 27;
	votos[260].numeroLista = 5; votos[260].tipoVoto = 7; strcpy(votos[260].sexo,"Femenino"); votos[260].edad = 46;
	votos[261].numeroLista = 2; votos[261].tipoVoto = 4; strcpy(votos[261].sexo,"Femenino"); votos[261].edad = 27;
	votos[262].numeroLista = 3; votos[262].tipoVoto = 8; strcpy(votos[262].sexo,"Femenino"); votos[262].edad = 64;
	votos[263].numeroLista = 4; votos[263].tipoVoto = 0; strcpy(votos[263].sexo,"Femenino"); votos[263].edad = 26;
	votos[264].numeroLista = 5; votos[264].tipoVoto = 8; strcpy(votos[264].sexo,"Femenino"); votos[264].edad = 16;
	votos[265].numeroLista = 2; votos[265].tipoVoto = 0; strcpy(votos[265].sexo,"Femenino"); votos[265].edad = 21;
	votos[266].numeroLista = 4; votos[266].tipoVoto = 8; strcpy(votos[266].sexo,"Masculino"); votos[266].edad = 24;
	votos[267].numeroLista = 3; votos[267].tipoVoto = 6; strcpy(votos[267].sexo,"Masculino"); votos[267].edad = 27;
	votos[268].numeroLista = 3; votos[268].tipoVoto = 1; strcpy(votos[268].sexo,"Femenino"); votos[268].edad = 23;
	votos[269].numeroLista = 1; votos[269].tipoVoto = 8; strcpy(votos[269].sexo,"Masculino"); votos[269].edad = 65;
	votos[270].numeroLista = 4; votos[270].tipoVoto = 7; strcpy(votos[270].sexo,"Masculino"); votos[270].edad = 74;
	votos[271].numeroLista = 4; votos[271].tipoVoto = 0; strcpy(votos[271].sexo,"Masculino"); votos[271].edad = 25;
	votos[272].numeroLista = 3; votos[272].tipoVoto = 6; strcpy(votos[272].sexo,"Femenino"); votos[272].edad = 30;
	votos[273].numeroLista = 5; votos[273].tipoVoto = 6; strcpy(votos[273].sexo,"Femenino"); votos[273].edad = 68;
	votos[274].numeroLista = 2; votos[274].tipoVoto = 1; strcpy(votos[274].sexo,"Masculino"); votos[274].edad = 30;
	votos[275].numeroLista = 3; votos[275].tipoVoto = 1; strcpy(votos[275].sexo,"Femenino"); votos[275].edad = 21;
	votos[276].numeroLista = 4; votos[276].tipoVoto = 2; strcpy(votos[276].sexo,"Femenino"); votos[276].edad = 49;
	votos[277].numeroLista = 2; votos[277].tipoVoto = 3; strcpy(votos[277].sexo,"Masculino"); votos[277].edad = 29;
	votos[278].numeroLista = 2; votos[278].tipoVoto = 2; strcpy(votos[278].sexo,"Masculino"); votos[278].edad = 70;
	votos[279].numeroLista = 2; votos[279].tipoVoto = 5; strcpy(votos[279].sexo,"Femenino"); votos[279].edad = 38;
	votos[280].numeroLista = 4; votos[280].tipoVoto = 7; strcpy(votos[280].sexo,"Femenino"); votos[280].edad = 65;
	votos[281].numeroLista = 5; votos[281].tipoVoto = 4; strcpy(votos[281].sexo,"Femenino"); votos[281].edad = 53;
	votos[282].numeroLista = 1; votos[282].tipoVoto = 1; strcpy(votos[282].sexo,"Femenino"); votos[282].edad = 63;
	votos[283].numeroLista = 2; votos[283].tipoVoto = 7; strcpy(votos[283].sexo,"Femenino"); votos[283].edad = 69;
	votos[284].numeroLista = 3; votos[284].tipoVoto = 2; strcpy(votos[284].sexo,"Masculino"); votos[284].edad = 23;
	votos[285].numeroLista = 5; votos[285].tipoVoto = 6; strcpy(votos[285].sexo,"Masculino"); votos[285].edad = 69;
	votos[286].numeroLista = 4; votos[286].tipoVoto = 2; strcpy(votos[286].sexo,"Masculino"); votos[286].edad = 34;
	votos[287].numeroLista = 5; votos[287].tipoVoto = 6; strcpy(votos[287].sexo,"Masculino"); votos[287].edad = 20;
	votos[288].numeroLista = 5; votos[288].tipoVoto = 8; strcpy(votos[288].sexo,"Masculino"); votos[288].edad = 39;
	votos[289].numeroLista = 5; votos[289].tipoVoto = 5; strcpy(votos[289].sexo,"Masculino"); votos[289].edad = 37;
	votos[290].numeroLista = 1; votos[290].tipoVoto = 2; strcpy(votos[290].sexo,"Femenino"); votos[290].edad = 45;
	votos[291].numeroLista = 3; votos[291].tipoVoto = 6; strcpy(votos[291].sexo,"Femenino"); votos[291].edad = 48;
	votos[292].numeroLista = 4; votos[292].tipoVoto = 1; strcpy(votos[292].sexo,"Masculino"); votos[292].edad = 16;
	votos[293].numeroLista = 1; votos[293].tipoVoto = 2; strcpy(votos[293].sexo,"Femenino"); votos[293].edad = 54;
	votos[294].numeroLista = 3; votos[294].tipoVoto = 3; strcpy(votos[294].sexo,"Femenino"); votos[294].edad = 46;
	votos[295].numeroLista = 3; votos[295].tipoVoto = 7; strcpy(votos[295].sexo,"Masculino"); votos[295].edad = 61;
	votos[296].numeroLista = 1; votos[296].tipoVoto = 6; strcpy(votos[296].sexo,"Femenino"); votos[296].edad = 54;
	votos[297].numeroLista = 5; votos[297].tipoVoto = 3; strcpy(votos[297].sexo,"Femenino"); votos[297].edad = 31;
	votos[298].numeroLista = 1; votos[298].tipoVoto = 0; strcpy(votos[298].sexo,"Masculino"); votos[298].edad = 50;
	votos[299].numeroLista = 1; votos[299].tipoVoto = 5; strcpy(votos[299].sexo,"Femenino"); votos[299].edad = 58;

	
	FILE * a = fopen(ARCHIVO_VOTOS,"wb");
	
	// guardo en archivo los votos correspondientes a cada lista
	for (int d=0; d<cantVotosTotales; d++){
		fwrite(&votos[d],sizeof(sVotos),1,a);
	}
	
	fclose(a);	
}

// Guarda en una lista enlazada las listas desde un archivo
void leerListas(nodoListasVotadas * & raizListas)
{
	sListas lista;
	
	// leer archivo LISTAS
	FILE *a = fopen(ARCHIVO_LISTAS,"rb");
	
	fread(&lista,sizeof(sListas),1,a);
	
	while(!feof(a)){
		
		// Inserto en la lista ordenada por numero de lista
		insertarOrdenadoListaVotadas(raizListas,lista,lista.numeroLista);
		
		fread(&lista,sizeof(sListas),1,a);
	}
	
	fclose(a);
}

// calcula los votos validos de cada lista, del total de listas y porcentaje
void procesarVotos(nodoListasVotadas * & raizListas)
{
	leerListas(raizListas);
	
	sVotos voto;
	nodoListasVotadas * aux ;
	nodoListasVotadas * auxPorcentaje = raizListas; // Puntero auxiliar para recorrer y guardar porcentaje de votos votados
	
	// leer archivo votos
	FILE *a = fopen(ARCHIVO_VOTOS,"rb");
	
	fread(&voto,sizeof(sVotos),1,a);
	
	while(!feof(a)){
		
		// Busco el nodoLista correspondiente
		if ( buscarLista(raizListas,aux,voto.numeroLista-1) )
		{
			// procesar votos totales por lista.
			aux->lista.cantVotosTotales++;
			
			// Proceso de votos validos
			if (voto.tipoVoto >= 1 && voto.tipoVoto <= 7) {
				aux->lista.cantVotosValidos++;
				
				// Guardo el voto en la lista de votos para esa lista.
				insertarOrdenadoVotos(aux->infoVoto,voto,voto.edad);
				
				// guardar en variable global cantTotalVotosValidos
				cantTotalVotosValidos++;
				
				// guardo edades
				if(voto.edad < 18) aux->lista.hasta18++;
				if(voto.edad >= 18 && voto.edad < 30) aux->lista.hasta30++;
				if(voto.edad >= 30 && voto.edad < 50) aux->lista.hasta50++;
				if(voto.edad >= 50) aux->lista.mas50++;
				
			} else {
			
				// Proceso votos en blanco
				if (voto.tipoVoto == 0) {
					cantTotalVotosEnBlanco++;
				}
				
				// Proceso votos nulos
				if (voto.tipoVoto < 0 || voto.tipoVoto > 7) {
					cantTotalVotosNulos++;
				}
				
			}
			
		}
		
		
		
		fread(&voto,sizeof(sVotos),1,a);
	}
	
	fclose(a);
	
	// Proceso porcentaje de votos por lista.
	while (auxPorcentaje != NULL)
	{
		auxPorcentaje->lista.porcentajeVotosValidos = (100 * auxPorcentaje->lista.cantVotosValidos) / cantTotalVotosValidos;
		auxPorcentaje = auxPorcentaje->siguiente;
	}
}

void asignarBancas(nodoListasVotadas * & raizListas) {
	
	nodoListasVotadas * & aux = raizListas;
	
	while(aux != NULL){
		if (aux->lista.porcentajeVotosValidos >= 3) // solo entran a banca los que superen el 3% de votos
		{
			bancas[aux->lista.numeroLista - 1].cantBanca1 = aux->lista.cantVotosValidos; // la primera banca tiene la mismca cantidad de votos
	
			bancas[aux->lista.numeroLista - 1].cantBanca2 = aux->lista.cantVotosValidos / 2;
			bancas[aux->lista.numeroLista - 1].cantBanca3 = aux->lista.cantVotosValidos / 3;
			bancas[aux->lista.numeroLista - 1].cantBanca4 = aux->lista.cantVotosValidos / 4;
			bancas[aux->lista.numeroLista - 1].cantBanca5 = aux->lista.cantVotosValidos / 5;
			bancas[aux->lista.numeroLista - 1].cantBanca6 = aux->lista.cantVotosValidos / 6;
			bancas[aux->lista.numeroLista - 1].cantBanca7 = aux->lista.cantVotosValidos / 7;
			bancas[aux->lista.numeroLista - 1].cantBanca8 = aux->lista.cantVotosValidos / 8;
			bancas[aux->lista.numeroLista - 1].cantBanca9 = aux->lista.cantVotosValidos / 9;
			bancas[aux->lista.numeroLista - 1].cantBanca10 = aux->lista.cantVotosValidos / 10;
			bancas[aux->lista.numeroLista - 1].cantBanca11 = aux->lista.cantVotosValidos / 11;
			bancas[aux->lista.numeroLista - 1].cantBanca12 = aux->lista.cantVotosValidos / 12;
			bancas[aux->lista.numeroLista - 1].cantBanca13 = aux->lista.cantVotosValidos / 13;
		}
		
		aux=aux->siguiente;
	}

	
}


void mostrarTabla()
{
	setearColor(6);
	cout << "\n\n+----------------------------------------------------------------------------------------------------------------------------+\n";
	cout << "|                                                    RESULTADOS OBTENIDOS                                                    |\n";
	cout << "+----------+------+-------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------------------+\n";
	setearColor(7);
	printf("|%-10s|%-6s|%-7s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-20s|\n",
		"LISTAS",
		"Cant.",
		"% Votos",
		"Banca",
		"Banca",
		"Banca",
		"Banca",
		"Banca",
		"Banca",
		"Banca",
		"Banca",
		"Banca",
		"Banca",
		"Banca",
		"Banca",
		"Banca",
		"Ganan");
	printf("|%-10s|%-6s|%-7s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-20s|\n",
		"",
		"Votos",
		"Validos",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"10",
		"11",
		"12",
		"13",
		"");
	cout << "+----------+------+-------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------------------+\n";

	for (int i = 0;i < cantListas; i++)
	{
		printf("|%d %-8s|%-6d|%-7d|%-5d|%-5d|%-5d|%-5d|%-5d|%-5d|%-5d|%-5d|%-5d|%-5d|%-5d|%-5d|%-5d|%-20s|\n",
			listas[i].numeroLista,
			listas[i].nombreLista,
			listas[i].cantVotosValidos,
			listas[i].porcentajeVotosValidos,
			bancas[i].cantBanca1,
			bancas[i].cantBanca2,
			bancas[i].cantBanca3,
			bancas[i].cantBanca4,
			bancas[i].cantBanca5,
			bancas[i].cantBanca6,
			bancas[i].cantBanca7,
			bancas[i].cantBanca8,
			bancas[i].cantBanca9,
			bancas[i].cantBanca10,
			bancas[i].cantBanca11,
			bancas[i].cantBanca12,
			bancas[i].cantBanca13,
			"");

		for (int j = 0; j < 13; j++)
		{
			if (listas[i].numeroLista == ganadores[j].numLista)
			{
				printf("|%-10s|%-6s|%-7s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-20s|\n",
					"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ganadores[j].candidato);
			}
			if (listas[i].porcentajeVotosValidos < 3 && j == 0)
				printf("|%-10s|%-6s|%-7s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-20s|\n",
					"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "OBTUVO MENOS DEL 3%");
		}
		cout << "+----------+------+-------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------------------+\n";
	}
	printf("|%-10s|%-6d|%-7s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-20s|\n",
		"VOTOS EN", cantTotalVotosEnBlanco, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "");
	printf("|%-10s|%-6s|%-7s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-20s|\n",
		"BLANCO", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "");
	cout << "+----------+------+-------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------------------+\n";
	printf("|%-10s|%-6d|%-7s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-20s|\n",
		"VOTOS", cantTotalVotosNulos, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "");
	printf("|%-10s|%-6s|%-7s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-20s|\n",
		"NULOS", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "");
	cout << "+----------+------+-------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------------------+\n";

}


//  metodo burbuja para ordenar de mayor a menor
void ordenarListas(sListas lista[cantListas]) 
{
	sListas temporal;
	inicializarLista(temporal);

	sBancas temporalBancas;
	inicializarBanca(temporalBancas);

	for (int i = 0; i < cantListas; i++) {
		for (int j = 0; j < cantListas - 1; j++) {
			if (lista[j].cantVotosValidos < lista[j + 1].cantVotosValidos) {
				temporal = lista[j];
				lista[j] = lista[j + 1];
				lista[j + 1] = temporal;

				//tambien se ordenan las bancas para que coincida con cada lista
				temporalBancas = bancas[j]; 
				bancas[j] = bancas[j + 1];
				bancas[j + 1] = temporalBancas;
			}
		}
	}
}

// metodo burbuja para ordenar de mayor a menor
void ordenarParticipantes(sGanadores ganadores[cantTotalParticipantes]) 
{
	sGanadores temporal;
	inicializarGanador(temporal);

	for (int i = 0;i < cantTotalParticipantes; i++) {
		for (int j = 0; j < cantTotalParticipantes - 1; j++) {
			if (ganadores[j].cantVotos < ganadores[j + 1].cantVotos) {
				temporal = ganadores[j];
				ganadores[j] = ganadores[j + 1];
				ganadores[j + 1] = temporal;
			}
		}
	}
}

void guardarParticipantes()
{
	inicializarGanadores();
	int numBancas = 0;
	int numLista = 0;
	int j = 1;
	int cantParticipantes = cantListas * cantBancas;

	for (int i = 0; i < cantParticipantes; i++) {

		if (numBancas == cantBancas) numBancas = 0;

		ganadores[i].numLista = listas[numLista].numeroLista;
		ganadores[i].numBanca = j;
		switch (numBancas) {
		case 0:ganadores[i].cantVotos = bancas[numLista].cantBanca1;break;
		case 1:ganadores[i].cantVotos = bancas[numLista].cantBanca2;break;
		case 2:ganadores[i].cantVotos = bancas[numLista].cantBanca3;break;
		case 3:ganadores[i].cantVotos = bancas[numLista].cantBanca4;break;
		case 4:ganadores[i].cantVotos = bancas[numLista].cantBanca5;break;
		case 5:ganadores[i].cantVotos = bancas[numLista].cantBanca6;break;
		case 6:ganadores[i].cantVotos = bancas[numLista].cantBanca7;break;
		case 7:ganadores[i].cantVotos = bancas[numLista].cantBanca8;break;
		case 8:ganadores[i].cantVotos = bancas[numLista].cantBanca9;break;
		case 9:ganadores[i].cantVotos = bancas[numLista].cantBanca10;break;
		case 10:ganadores[i].cantVotos = bancas[numLista].cantBanca11;break;
		case 11:ganadores[i].cantVotos = bancas[numLista].cantBanca12;break;
		case 12:ganadores[i].cantVotos = bancas[numLista].cantBanca13;break;

		};
		strcpy(ganadores[i].candidato, listas[numLista].candidatos[numBancas]);
		numBancas++;
		j++;
		if (j == 14) j = 1;
		if (numBancas == 13) numLista++;
	}

}

void mostrarListasPorEdad()
{
	setearColor(6);
	cout << "\n\n+----------------------------------------------------------------------------------------------------------------------------+\n";
	cout << "|                                           CANTIDAD DE VOTOS POR RANGO DE EDADES                                            |\n";

	for (int i = 0; i < cantListas; i++)
	{
		setearColor(6);
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
		printf("| Numero de Lista |   %-42d|    Nombre de Lista |  %-37s|\n", listas[i].numeroLista, listas[i].nombreLista);
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
		setearColor(7);
		printf("| %61s | %58d |\n", "Cantidad votos de menores de 18 anos", listas[i].hasta18);
		printf("| %61s | %58d |\n", "Cantidad votos de mayores a 18 y menores o iguales a 30 anos", listas[i].hasta30);
		printf("| %61s | %58d |\n", "Cantidad votos de mayores a 30 y menores o iguales a 50 anos", listas[i].hasta50);
		printf("| %61s | %58d |\n", "Cantidad votos de mayores a 50 anos", listas[i].mas50);
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
	}



}

void setearColor(int rgb)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), rgb);
}


void mostrarLoteDePrueba(nodoListasVotadas * & raizListas)
{
	nodoListasVotadas * aux = raizListas;
	nodoListasVotadas * aux2 = raizListas;
	nodoVotos * auxVotos = NULL;
	
	setearColor(6);
	cout << "\n\n+----------------------------------------------------------------------------------------------------------------------------+\n";
	cout << "|                                                         LOTE DE PRUEBA                                                     |\n";

	cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
	cout << "|                SE INGRESO EL NOMBRE, EL NUMERO DE LISTA Y EL NOMBRE DE LOS 25 CANDIDATOS EN EL SIGUIENTE ORDEN:            |\n";
	while (aux != NULL)
	{
		setearColor(6);
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
		printf("| Numero de Lista |   %-42d|    Nombre de Lista |  %-37s|\n", aux->lista.numeroLista, aux->lista.nombreLista);
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
		setearColor(7);
		for (int j = 0; j < cantCandidatos; j++)
		{
			printf("|%59s %-2d | %58s |\n", "Nombre del Candidato num",j+1, aux->lista.candidatos[j]);
		}
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
		
		aux = aux->siguiente;
	}
	
	
	setearColor(6);
	cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
	cout << "|                                             INFORMACIÓN DE VOTOS INGRESADOS:                                               |\n";
	cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
	while (aux2 != NULL)
	{
		setearColor(6);
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
		printf("| Numero de Lista |   %-43d|    Nombre de Lista |  %-36s|\n", aux2->lista.numeroLista, aux2->lista.nombreLista);
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
		printf("| Cantidad de Votos Ingresados |   %-30d| Cantidad de Votos Validos |  %-29d|\n", aux2->lista.cantVotosTotales, aux2->lista.cantVotosValidos);
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
		setearColor(7);
		auxVotos = aux2->infoVoto;
		int i = 1;
		while(auxVotos != NULL)
		{
			printf("|%28s %-3d : %28d |%28s :%28d |\n", "Voto num", i, auxVotos->voto.tipoVoto,"Edad del Votante", auxVotos->voto.edad);
			auxVotos = auxVotos->siguiente;
			i++;
		}
		
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
		aux2 = aux2->siguiente;
	}
	
}




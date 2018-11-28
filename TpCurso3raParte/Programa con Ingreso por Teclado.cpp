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
void ordenarListas(nodoListasVotadas * & raizListas);
void mostrarTabla(nodoListasVotadas * raizListas);
void guardarParticipantes(nodoListasVotadas * raizListas);
void ordenarParticipantes(sGanadores ganadores[cantTotalParticipantes]);
void mostrarListasPorEdad(nodoListasVotadas * raizListas);
void setearColor(int rgb);
void mostrarLoteDePrueba(nodoListasVotadas * & raizListas);
void mostrarVotosPorSexoYlista(nodoListasVotadas * listasVotadas);
void mostrarVotosPorEdad(nodoListasVotadas *listadoListas);
// PROTOTIPOS LISTAS ENLAZADAS
bool buscarEnLista(nodoListasVotadas * raiz,nodoListasVotadas * & aux,int clave);
void insertarOrdInvertidoListaVotadas(nodoListasVotadas * & raiz,sListas lista,int clave);
void insertarOrdenadoListaVotadas(nodoListasVotadas * & raiz,sListas lista,int clave);
void insertarOrdenadoVotos(nodoVotos * & raiz,sVotos voto,int clave);
bool sacarPrimero(nodoListasVotadas * & raiz,nodoListasVotadas * & nodo);

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
	
	
//	printf("Candidatos:\n"); 
//	 
//  
//	for (int f = 0; f < cantCandidatos; f++)  
//	{  
//		printf("--> %s\n",lista.candidatos[f]); 
//	}   
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
void mostrarListadoListas(nodoListasVotadas * raiz){
	nodoListasVotadas * aux = raiz;
	nodoVotos * votoAux;
	
	while(aux != NULL){
		mostrarLista(aux->lista);
		
		votoAux = aux->infoVoto;
		while(votoAux != NULL){
			mostrarVoto(votoAux->voto);
			votoAux=votoAux->siguiente;
		}
		
		aux=aux->siguiente;
	}
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

	guardarParticipantes(listadoListas);

	ordenarListas(listadoListas);

	ordenarParticipantes(ganadores);

	mostrarTabla(listadoListas);

	mostrarListasPorEdad(listadoListas);
	
	mostrarVotosPorEdad(listadoListas);

	system("pause");

	return 0;
}

//EJERCICIO 5
void mostrarVotosPorEdad(nodoListasVotadas *listadoListas){
	
	nodoVotos* nodoVotosAux;
	nodoVotos* nodoVotosPorEdad = NULL;
	
	while(listadoListas != NULL){
		
		nodoVotosAux = listadoListas->infoVoto;
		
		while(nodoVotosAux != NULL){
			
			insertarOrdenadoVotos(nodoVotosPorEdad, nodoVotosAux->voto, nodoVotosAux->voto.edad);
			
			nodoVotosAux = nodoVotosAux->siguiente;
		}
		
		listadoListas = listadoListas->siguiente;
	}
	
	setearColor(6);
	cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
	cout << "|                                              MOSTRAR VOTOS ORDENADOS POR EDAD                                              |\n";
	cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
	
	cout << "|                            EDAD                              |                             SEXO                            |\n";
	cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
	
	
	while(nodoVotosPorEdad != NULL){
		
		setearColor(7);
		//cout << "|                           " << nodoVotosPorEdad->voto.edad << "                              |                          " << nodoVotosPorEdad->voto.sexo << "|" <<endl;  
		printf("|%62d|%61s|\n",nodoVotosPorEdad->voto.edad, nodoVotosPorEdad->voto.sexo);
		nodoVotosPorEdad = nodoVotosPorEdad->siguiente;
	}
	
	cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
	
}

//EJERCICIO 4.
void mostrarVotosPorSexoYlista(nodoListasVotadas * listasVotadas)
{
	int votosVarones = 0;
	int votosMujeres = 0;

	while (listasVotadas != NULL) {
		int auxClave =listasVotadas->clave;
		while (auxClave == listasVotadas->clave)
		{

			while (listasVotadas->infoVoto != NULL) {
				if (strcmp("Masculino", listasVotadas->infoVoto->voto.sexo) == 0) {
					 votosVarones = votosVarones + 1;
				}
				else {
					 votosMujeres = votosMujeres + 1;
				}
				listasVotadas->infoVoto = listasVotadas->infoVoto->siguiente;
			}

			cout << "Votos Mujeres Lista " << listasVotadas->lista.nombreLista << " : " << votosMujeres << endl;
			cout << "Votos Varones Lista " << listasVotadas->lista.nombreLista << " : " << votosVarones << endl;
			votosVarones = 0;
			votosMujeres = 0;
			listasVotadas = listasVotadas->siguiente;
		}
	}
}
//METODOS LISTAS ENLAZADAS

bool buscarEnLista(nodoListasVotadas * raiz,nodoListasVotadas * & aux,int clave)
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

void insertarOrdInvertidoListaVotadas(nodoListasVotadas * & raiz,sListas lista,int clave)
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
		if (raiz->clave < clave){
			aux->siguiente = raiz;
			raiz = aux;
		} else {
			// Si debe ir despues del primero
			nodoListasVotadas * aux2 = raiz;
			while(aux2->siguiente != NULL && aux2->siguiente->clave >= clave) {
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

bool sacarPrimero(nodoListasVotadas * & raiz,nodoListasVotadas * & nodo)
{
	nodoListasVotadas * aux = NULL;
	if(raiz == NULL) 
	{
		return false;	
	} else {
		nodo = raiz;
		aux = raiz;
		raiz = raiz->siguiente;
		delete (aux);
		
		return true;
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

// carga el nombre de los 25 candidatos ingresados por teclado en la lista pasada por parametro
void cargarCandidatos(sListas & auxLista)
{
	for (int j = 0; j < cantCandidatos; j++)
	{
		
		cout << endl<<"Ingrese el Nombre del Candidato " << j + 1 << " de la Lista:";
		
		cin.getline(auxLista.candidatos[j], cantCaracteres);
	}
}

// Pide por consola que ingrese los datos de todas las listas
// y lo guarda en un archivo
void cargarListas()
{
	sListas auxLista;

	FILE * a = fopen(ARCHIVO_LISTAS,"wb");

	for (int i = 0; i < cantListas; i++)
	{		
		// Inicializamos la lista auxiliar en cada vuelta para vaciarla antes de cargarle datos
		inicializarLista(auxLista);
		
		auxLista.numeroLista = i+1;

		cout << endl<< "Ingrese Nombre de Lista "<< auxLista.numeroLista << ": ";
		
		cin.getline(auxLista.nombreLista, cantCaracteres);

		cargarCandidatos(auxLista);

		fwrite(&auxLista,sizeof(sListas),1,a);
	}
	fclose(a);
}

void cargarVotos()
{	
	sVotos voto;
	
	FILE * a = fopen(ARCHIVO_VOTOS,"wb");
	
	// Ingreso tipo, sexo y edad de cada voto. Para cada lista
	for (int i = 0; i < cantListas; i++)
	{		
		inicializarVoto(voto);
		printf("\n#############################\n");
		printf("### Votos para la Lista %d ###\n",i+1);
		printf("#############################\n");
		
		while(voto.tipoVoto != 99) {
			// Inicializo el voto en cada vuelta para limpiarlo.
			voto.tipoVoto = 0;
			voto.numeroLista = i+1;
			voto.edad = 0;
			memset(voto.sexo,' ',cantCaracteres);
			voto.sexo[cantCaracteres] = '\0';
			
			int sexo = 9;
			
			printf("Ingrese el tipo de Voto (0 para voto en Blanco, de 1 a 7 para Valido y otro para Nulo, 99 = FIN): \n");
			cin >> voto.tipoVoto;
			
			if (voto.tipoVoto != 99) {
				while( !(sexo == 0 || sexo == 1) ) {
					printf("Ingrese el sexo del votante (0 para Hombre, 1 para Mujer) :\n");
					cin >> sexo;
					
					if(sexo == 0) {
						strcpy(voto.sexo,"Masculino");
					} else {
						strcpy(voto.sexo,"Femenino");
					}
				}
				
				printf("Ingrese la edad del votante:\n");
				cin >> voto.edad;
				
				printf("Voto guardado con exito!\n\n");
				fwrite(&voto,sizeof(sVotos),1,a);			
			}
		}
		
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
		if ( buscarEnLista(raizListas,aux,voto.numeroLista) )
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
	
	nodoListasVotadas * aux = raizListas;
	
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


void mostrarTabla(nodoListasVotadas * raizListas)
{
	nodoListasVotadas * aux = raizListas;
	
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

	while (aux!=NULL)
	{
		printf("|%d %-8s|%-6d|%-7d|%-5d|%-5d|%-5d|%-5d|%-5d|%-5d|%-5d|%-5d|%-5d|%-5d|%-5d|%-5d|%-5d|%-20s|\n",
			aux->lista.numeroLista,
			aux->lista.nombreLista,
			aux->lista.cantVotosValidos,
			aux->lista.porcentajeVotosValidos,
			bancas[aux->lista.numeroLista].cantBanca1,
			bancas[aux->lista.numeroLista].cantBanca2,
			bancas[aux->lista.numeroLista].cantBanca3,
			bancas[aux->lista.numeroLista].cantBanca4,
			bancas[aux->lista.numeroLista].cantBanca5,
			bancas[aux->lista.numeroLista].cantBanca6,
			bancas[aux->lista.numeroLista].cantBanca7,
			bancas[aux->lista.numeroLista].cantBanca8,
			bancas[aux->lista.numeroLista].cantBanca9,
			bancas[aux->lista.numeroLista].cantBanca10,
			bancas[aux->lista.numeroLista].cantBanca11,
			bancas[aux->lista.numeroLista].cantBanca12,
			bancas[aux->lista.numeroLista].cantBanca13,
			"");

		for (int j = 0; j < 13; j++)
		{
			if (aux->lista.numeroLista == ganadores[j].numLista)
			{
				printf("|%-10s|%-6s|%-7s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-20s|\n",
					"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ganadores[j].candidato);
			}
			if (aux->lista.porcentajeVotosValidos < 3 && j == 0)
				printf("|%-10s|%-6s|%-7s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-20s|\n",
					"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "OBTUVO MENOS DEL 3%");
		}
		cout << "+----------+------+-------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------------------+\n";
		aux=aux->siguiente;
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


//  se usa lista enlazada auxiliar para ordenar las listas segun la cantidad de votos validos.
void ordenarListas(nodoListasVotadas * & raizListas) 
{
	nodoListasVotadas * aux = raizListas;
	nodoListasVotadas * aux2 = NULL;
	nodoListasVotadas * aux3 = NULL;
	nodoListasVotadas * auxFinal = NULL;
	
	while(aux != NULL)
	{
		// Saco el primer elemento de la lista
		sacarPrimero(aux,aux2);
		
		// Lo inserto ordenado en la lista auxiliar final
		insertarOrdInvertidoListaVotadas(auxFinal,aux2->lista,aux2->lista.cantVotosValidos);
		
		// Busco el nodo dentro de la lista final, para luego agregarle la informacion de los votos
		buscarEnLista(auxFinal,aux3,aux2->lista.cantVotosValidos);
		aux3->infoVoto = aux2->infoVoto;
		
	}
	raizListas = auxFinal;
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

void guardarParticipantes(nodoListasVotadas * raizListas)
{
	inicializarGanadores();
	int numBancas = 0;
	int numLista = 0;
	int j = 1;
	int cantParticipantes = cantListas * cantBancas;
	nodoListasVotadas * listaAux = NULL;

	for (int i = 0; i < cantParticipantes; i++) {

		if (numBancas == cantBancas) numBancas = 0;
		buscarEnLista(raizListas,listaAux,numLista+1);

		ganadores[i].numLista = numLista+1;
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
		strcpy(ganadores[i].candidato, listaAux->lista.candidatos[numBancas]);
		numBancas++;
		j++;
		if (j == 14) j = 1;
		if (numBancas == 13) numLista++;
	}
}

void mostrarListasPorEdad(nodoListasVotadas * raizListas)
{
	nodoListasVotadas * aux = raizListas;
	
	setearColor(6);
	cout << "\n\n+----------------------------------------------------------------------------------------------------------------------------+\n";
	cout << "|                                           CANTIDAD DE VOTOS POR RANGO DE EDADES                                            |\n";

	while(aux!=NULL)
	{
		setearColor(6);
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
		printf("| Numero de Lista |   %-42d|    Nombre de Lista |  %-37s|\n", aux->lista.numeroLista, aux->lista.nombreLista);
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
		setearColor(7);
		printf("| %61s | %58d |\n", "Cantidad votos de menores de 18 anos", aux->lista.hasta18);
		printf("| %61s | %58d |\n", "Cantidad votos de mayores a 18 y menores o iguales a 30 anos", aux->lista.hasta30);
		printf("| %61s | %58d |\n", "Cantidad votos de mayores a 30 y menores o iguales a 50 anos", aux->lista.hasta50);
		printf("| %61s | %58d |\n", "Cantidad votos de mayores a 50 anos", aux->lista.mas50);
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
		aux=aux->siguiente;
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




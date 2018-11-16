// TP2018Algoritmos con Lote de Prueba

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <fstream>
#include <wchar.h>
#include <locale.h>
#include<Windows.h>

using namespace std;

//VARIABLES GLOBALES
const int cantCaracteres = 30;
const int cantCandidatos = 25;
const int cantListas = 5;
const int cantBancas = 13;
int cantTotalVotosValidos = 0;
int cantTotalVotosEnBlanco = 0;
int cantTotalVotosNulos = 0;
const int cantVotosMaximo = 200;
const int cantTotalParticipantes = 65;
// STRUCTS
struct sVotos {
	int	tipoVoto; // numero entre 1 y 7 , 0 es blanco y otro es nulo
	char sexo[cantCaracteres];
	int edad;
};

struct sListas {
	int numeroLista;
	char nombreLista[cantCaracteres]; // palabra de 20 letras maximo
	char candidatos[cantCandidatos][cantCaracteres]; //array de 25 palabras
	sVotos infoVotos[cantVotosMaximo];
	int cantVotosTotales;
	int cantVotosValidos;
	int porcentajeVotosValidos;
	int hasta18; //cantidad de votos de menores de 18 años
	int hasta30; //cantidad de votos > 18 y < 30
	int hasta50; //cantidad de votos > 30 y < 50
	int mas50; //cantidad de votos mayores de 50 años;
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


//PROTOTIPOS
void inicializarListas();
void cargarNombreNumeroListas();
void guardarNombreNumeroLista(int numero, char nombre[cantCaracteres]);
void cargarCandidatos();
void cargarVotos();
void procesarVotos();
int cantVotosValidos(sListas lista, int cantVotosTotales);
int calcularPorcentajeVotosValidos(int cantValidos, int cantTotal);
void asignarBancas(sListas lista);
void ordenarListas(sListas lista[cantListas]);
void mostrarTabla();
void guardarParticipantes();
void ordenarParticipantes(sGanadores ganadores[cantTotalParticipantes]);
void imprimirLineaHorizontal();
void mostrarListasPorEdad();
void setearColor(int rgb);
void mostrarLoteDePrueba();

int main()
{

	setlocale(LC_ALL, "");

	inicializarListas();

	cargarNombreNumeroListas();

	cargarCandidatos();

	cargarVotos();

	procesarVotos();

	mostrarLoteDePrueba();

	for (int i = 0; i < cantListas; i++)
	{
		asignarBancas(listas[i]);
	}

	ordenarListas(listas);

	guardarParticipantes();

	ordenarParticipantes(ganadores);

	mostrarTabla();

	mostrarListasPorEdad();



	getchar();
	return 0;
}


void cargarCandidatos()
{
	{
		strcpy(listas[0].candidatos[0], "candidato1/Lista1");
		strcpy(listas[0].candidatos[1], "candidato2/Lista1");
		strcpy(listas[0].candidatos[2], "candidato3/Lista1");
		strcpy(listas[0].candidatos[3], "candidato4/Lista1");
		strcpy(listas[0].candidatos[4], "candidato5/Lista1");
		strcpy(listas[0].candidatos[5], "candidato6/Lista1");
		strcpy(listas[0].candidatos[6], "candidato7/Lista1");
		strcpy(listas[0].candidatos[7], "candidato8/Lista1");
		strcpy(listas[0].candidatos[8], "candidato9/Lista1");
		strcpy(listas[0].candidatos[9], "candidato10/Lista1");
		strcpy(listas[0].candidatos[10], "candidato11/Lista1");
		strcpy(listas[0].candidatos[11], "candidato12/Lista1");
		strcpy(listas[0].candidatos[12], "candidato13/Lista1");
		strcpy(listas[0].candidatos[13], "candidato14/Lista1");
		strcpy(listas[0].candidatos[14], "candidato15/Lista1");
		strcpy(listas[0].candidatos[15], "candidato16/Lista1");
		strcpy(listas[0].candidatos[16], "candidato17/Lista1");
		strcpy(listas[0].candidatos[17], "candidato18/Lista1");
		strcpy(listas[0].candidatos[18], "candidato19/Lista1");
		strcpy(listas[0].candidatos[19], "candidato20/Lista1");
		strcpy(listas[0].candidatos[20], "candidato21/Lista1");
		strcpy(listas[0].candidatos[21], "candidato22/Lista1");
		strcpy(listas[0].candidatos[22], "candidato23/Lista1");
		strcpy(listas[0].candidatos[23], "candidato24/Lista1");
		strcpy(listas[0].candidatos[24], "candidato25/Lista1");
	}

	{
		strcpy(listas[1].candidatos[0], "candidato1/Lista2");
		strcpy(listas[1].candidatos[1], "candidato2/Lista2");
		strcpy(listas[1].candidatos[2], "candidato3/Lista2");
		strcpy(listas[1].candidatos[3], "candidato4/Lista2");
		strcpy(listas[1].candidatos[4], "candidato5/Lista2");
		strcpy(listas[1].candidatos[5], "candidato6/Lista2");
		strcpy(listas[1].candidatos[6], "candidato7/Lista2");
		strcpy(listas[1].candidatos[7], "candidato8/Lista2");
		strcpy(listas[1].candidatos[8], "candidato9/Lista2");
		strcpy(listas[1].candidatos[9], "candidato10/Lista2");
		strcpy(listas[1].candidatos[10], "candidato11/Lista2");
		strcpy(listas[1].candidatos[11], "candidato12/Lista2");
		strcpy(listas[1].candidatos[12], "candidato13/Lista2");
		strcpy(listas[1].candidatos[13], "candidato14/Lista2");
		strcpy(listas[1].candidatos[14], "candidato15/Lista2");
		strcpy(listas[1].candidatos[15], "candidato16/Lista2");
		strcpy(listas[1].candidatos[16], "candidato17/Lista2");
		strcpy(listas[1].candidatos[17], "candidato18/Lista2");
		strcpy(listas[1].candidatos[18], "candidato19/Lista2");
		strcpy(listas[1].candidatos[19], "candidato20/Lista2");
		strcpy(listas[1].candidatos[20], "candidato21/Lista2");
		strcpy(listas[1].candidatos[21], "candidato22/Lista2");
		strcpy(listas[1].candidatos[22], "candidato23/Lista2");
		strcpy(listas[1].candidatos[23], "candidato24/Lista2");
		strcpy(listas[1].candidatos[24], "candidato25/Lista2");
	}

	{
		strcpy(listas[2].candidatos[0], "candidato1/Lista3");
		strcpy(listas[2].candidatos[1], "candidato2/Lista3");
		strcpy(listas[2].candidatos[2], "candidato3/Lista3");
		strcpy(listas[2].candidatos[3], "candidato4/Lista3");
		strcpy(listas[2].candidatos[4], "candidato5/Lista3");
		strcpy(listas[2].candidatos[5], "candidato6/Lista3");
		strcpy(listas[2].candidatos[6], "candidato7/Lista3");
		strcpy(listas[2].candidatos[7], "candidato8/Lista3");
		strcpy(listas[2].candidatos[8], "candidato9/Lista3");
		strcpy(listas[2].candidatos[9], "candidato10/Lista3");
		strcpy(listas[2].candidatos[10], "candidato11/Lista3");
		strcpy(listas[2].candidatos[11], "candidato12/Lista3");
		strcpy(listas[2].candidatos[12], "candidato13/Lista3");
		strcpy(listas[2].candidatos[13], "candidato14/Lista3");
		strcpy(listas[2].candidatos[14], "candidato15/Lista3");
		strcpy(listas[2].candidatos[15], "candidato16/Lista3");
		strcpy(listas[2].candidatos[16], "candidato17/Lista3");
		strcpy(listas[2].candidatos[17], "candidato18/Lista3");
		strcpy(listas[2].candidatos[18], "candidato19/Lista3");
		strcpy(listas[2].candidatos[19], "candidato20/Lista3");
		strcpy(listas[2].candidatos[20], "candidato21/Lista3");
		strcpy(listas[2].candidatos[21], "candidato22/Lista3");
		strcpy(listas[2].candidatos[22], "candidato23/Lista3");
		strcpy(listas[2].candidatos[23], "candidato24/Lista3");
		strcpy(listas[2].candidatos[24], "candidato25/Lista3");
	}

	{
		strcpy(listas[3].candidatos[0], "candidato1/Lista4");
		strcpy(listas[3].candidatos[1], "candidato2/Lista4");
		strcpy(listas[3].candidatos[2], "candidato3/Lista4");
		strcpy(listas[3].candidatos[3], "candidato4/Lista4");
		strcpy(listas[3].candidatos[4], "candidato5/Lista4");
		strcpy(listas[3].candidatos[5], "candidato6/Lista4");
		strcpy(listas[3].candidatos[6], "candidato7/Lista4");
		strcpy(listas[3].candidatos[7], "candidato8/Lista4");
		strcpy(listas[3].candidatos[8], "candidato9/Lista4");
		strcpy(listas[3].candidatos[9], "candidato10/Lista4");
		strcpy(listas[3].candidatos[10], "candidato11/Lista4");
		strcpy(listas[3].candidatos[11], "candidato12/Lista4");
		strcpy(listas[3].candidatos[12], "candidato13/Lista4");
		strcpy(listas[3].candidatos[13], "candidato14/Lista4");
		strcpy(listas[3].candidatos[14], "candidato15/Lista4");
		strcpy(listas[3].candidatos[15], "candidato16/Lista4");
		strcpy(listas[3].candidatos[16], "candidato17/Lista4");
		strcpy(listas[3].candidatos[17], "candidato18/Lista4");
		strcpy(listas[3].candidatos[18], "candidato19/Lista4");
		strcpy(listas[3].candidatos[19], "candidato20/Lista4");
		strcpy(listas[3].candidatos[20], "candidato21/Lista4");
		strcpy(listas[3].candidatos[21], "candidato22/Lista4");
		strcpy(listas[3].candidatos[22], "candidato23/Lista4");
		strcpy(listas[3].candidatos[23], "candidato24/Lista4");
		strcpy(listas[3].candidatos[24], "candidato25/Lista4");
	}

	{
		strcpy(listas[4].candidatos[0], "candidato1/Lista5");
		strcpy(listas[4].candidatos[1], "candidato2/Lista5");
		strcpy(listas[4].candidatos[2], "candidato3/Lista5");
		strcpy(listas[4].candidatos[3], "candidato4/Lista5");
		strcpy(listas[4].candidatos[4], "candidato5/Lista5");
		strcpy(listas[4].candidatos[5], "candidato6/Lista5");
		strcpy(listas[4].candidatos[6], "candidato7/Lista5");
		strcpy(listas[4].candidatos[7], "candidato8/Lista5");
		strcpy(listas[4].candidatos[8], "candidato9/Lista5");
		strcpy(listas[4].candidatos[9], "candidato10/Lista5");
		strcpy(listas[4].candidatos[10], "candidato11/Lista5");
		strcpy(listas[4].candidatos[11], "candidato12/Lista5");
		strcpy(listas[4].candidatos[12], "candidato13/Lista5");
		strcpy(listas[4].candidatos[13], "candidato14/Lista5");
		strcpy(listas[4].candidatos[14], "candidato15/Lista5");
		strcpy(listas[4].candidatos[15], "candidato16/Lista5");
		strcpy(listas[4].candidatos[16], "candidato17/Lista5");
		strcpy(listas[4].candidatos[17], "candidato18/Lista5");
		strcpy(listas[4].candidatos[18], "candidato19/Lista5");
		strcpy(listas[4].candidatos[19], "candidato20/Lista5");
		strcpy(listas[4].candidatos[20], "candidato21/Lista5");
		strcpy(listas[4].candidatos[21], "candidato22/Lista5");
		strcpy(listas[4].candidatos[22], "candidato23/Lista5");
		strcpy(listas[4].candidatos[23], "candidato24/Lista5");
		strcpy(listas[4].candidatos[24], "candidato25/Lista5");
	}
}

void cargarNombreNumeroListas() {

	char nomLista1[cantCaracteres] = "BLANCA";
	char nomLista2[cantCaracteres] = "VERDE";
	char nomLista3[cantCaracteres] = "ROJA";
	char nomLista4[cantCaracteres] = "AZUL";
	char nomLista5[cantCaracteres] = "VIOLETA";

	guardarNombreNumeroLista(1, nomLista1);

	guardarNombreNumeroLista(2, nomLista2);

	guardarNombreNumeroLista(3, nomLista3);

	guardarNombreNumeroLista(4, nomLista4);

	guardarNombreNumeroLista(5, nomLista5);

}

// Carga numero y nombre de lista en la lista que se pasa
void guardarNombreNumeroLista(int numero, char nombre[cantCaracteres]) {

	switch (numero)
	{
	case 1:
		listas[0].numeroLista = numero;
		strcpy(listas[0].nombreLista, nombre);
		break;
	case 2:
		listas[1].numeroLista = numero;
		strcpy(listas[1].nombreLista, nombre);
		break;
	case 3:
		listas[2].numeroLista = numero;
		strcpy(listas[2].nombreLista, nombre);
		break;
	case 4:
		listas[3].numeroLista = numero;
		strcpy(listas[3].nombreLista, nombre);
		break;
	case 5:
		listas[4].numeroLista = numero;
		strcpy(listas[4].nombreLista, nombre);
		break;
	}
}

void procesarVotos() {

	for (int i = 0; i < cantListas; i++)
	{
		listas[i].cantVotosValidos = cantVotosValidos(listas[i], listas[i].cantVotosTotales);
	}
	for (int i = 0; i < cantListas; i++)
	{
		cantTotalVotosValidos = cantTotalVotosValidos + listas[i].cantVotosValidos;
	}
	for (int i = 0; i < cantListas; i++)
	{
		listas[i].porcentajeVotosValidos = calcularPorcentajeVotosValidos(listas[i].cantVotosValidos, cantTotalVotosValidos);

	}

}

// Recibe una lista para usar el tipoVoto de cada propiedad infoVoto y cantidad de votos
// Devuelve cantidad de votos validos
int cantVotosValidos(sListas lista, int cantVotosTotales) {

	int cantValidos = 0;

	for (int i = 0; i < cantVotosTotales; i++)
	{
		if (lista.infoVotos[i].tipoVoto >= 1 && lista.infoVotos[i].tipoVoto <= 7) // si es valido
		{
			cantValidos++;

		}
		else if (lista.infoVotos[i].tipoVoto == 0) // si es en blanco
		{
			cantTotalVotosEnBlanco++;
		}
		else if (lista.infoVotos[i].tipoVoto < 0 || lista.infoVotos[i].tipoVoto > 7) // si es nulo
		{
			cantTotalVotosNulos++;
		}
	}

	return cantValidos;
}

int calcularPorcentajeVotosValidos(int cantValidos, int cantTotal) {

	int porcentajeValidos = (100 * cantValidos) / cantTotal;

	return porcentajeValidos;
}

void asignarBancas(sListas lista) {

	if (lista.porcentajeVotosValidos >= 3) // solo entran a banca los que superen el 3% de votos
	{
		bancas[lista.numeroLista - 1].cantBanca1 = lista.cantVotosValidos; // la primera banca tiene la mismca cantidad de votos

		bancas[lista.numeroLista - 1].cantBanca2 = lista.cantVotosValidos / 2;
		bancas[lista.numeroLista - 1].cantBanca3 = lista.cantVotosValidos / 3;
		bancas[lista.numeroLista - 1].cantBanca4 = lista.cantVotosValidos / 4;
		bancas[lista.numeroLista - 1].cantBanca5 = lista.cantVotosValidos / 5;
		bancas[lista.numeroLista - 1].cantBanca6 = lista.cantVotosValidos / 6;
		bancas[lista.numeroLista - 1].cantBanca7 = lista.cantVotosValidos / 7;
		bancas[lista.numeroLista - 1].cantBanca8 = lista.cantVotosValidos / 8;
		bancas[lista.numeroLista - 1].cantBanca9 = lista.cantVotosValidos / 9;
		bancas[lista.numeroLista - 1].cantBanca10 = lista.cantVotosValidos / 10;
		bancas[lista.numeroLista - 1].cantBanca11 = lista.cantVotosValidos / 11;
		bancas[lista.numeroLista - 1].cantBanca12 = lista.cantVotosValidos / 12;
		bancas[lista.numeroLista - 1].cantBanca13 = lista.cantVotosValidos / 13;
	}
}



void cargarVotos() {

	// en lista 1:
	listas[0].cantVotosTotales = 2;
	{
		listas[0].infoVotos[0].tipoVoto = 1;/* valido*/ listas[0].infoVotos[0].edad = 17;
		listas[0].infoVotos[1].tipoVoto = 7;/* valido*/ listas[0].infoVotos[1].edad = 17;
	}
	// en lista 2:
	listas[1].cantVotosTotales = 200;
	{
		for (int i = 0; i < 200; i++)
		{
			listas[1].infoVotos[i].tipoVoto = 1;/* valido*/ listas[1].infoVotos[i].edad = 60;
		}
	}
	// en lista 3:	
	listas[2].cantVotosTotales = 80;
	{
		listas[2].infoVotos[0].tipoVoto = 1;/* valido*/ listas[2].infoVotos[0].edad = 40;
		listas[2].infoVotos[1].tipoVoto = 7;/* valido*/ listas[2].infoVotos[1].edad = 40;
		listas[2].infoVotos[2].tipoVoto = 7;/* valido*/	listas[2].infoVotos[2].edad = 40;
		listas[2].infoVotos[3].tipoVoto = 7;/* valido*/	listas[2].infoVotos[3].edad = 40;
		listas[2].infoVotos[4].tipoVoto = 7;/* valido*/	listas[2].infoVotos[4].edad = 40;
		listas[2].infoVotos[5].tipoVoto = 7;/* valido*/	listas[2].infoVotos[5].edad = 40;
		listas[2].infoVotos[6].tipoVoto = 7;/* valido*/	listas[2].infoVotos[6].edad = 40;
		listas[2].infoVotos[7].tipoVoto = 7;/* valido*/	listas[2].infoVotos[7].edad = 40;
		listas[2].infoVotos[8].tipoVoto = 7;/* valido*/	listas[2].infoVotos[8].edad = 40;
		listas[2].infoVotos[9].tipoVoto = 7;/* valido*/	listas[2].infoVotos[9].edad = 40;
		listas[2].infoVotos[10].tipoVoto = 1;/* valido*/listas[2].infoVotos[10].edad = 40;
		listas[2].infoVotos[11].tipoVoto = 7;/* valido*/listas[2].infoVotos[11].edad = 40;
		listas[2].infoVotos[12].tipoVoto = 7;/* valido*/listas[2].infoVotos[12].edad = 40;
		listas[2].infoVotos[13].tipoVoto = 7;/* valido*/listas[2].infoVotos[13].edad = 40;
		listas[2].infoVotos[14].tipoVoto = 7;/* valido*/listas[2].infoVotos[14].edad = 40;
		listas[2].infoVotos[15].tipoVoto = 7;/* valido*/listas[2].infoVotos[15].edad = 40;
		listas[2].infoVotos[16].tipoVoto = 7;/* valido*/listas[2].infoVotos[16].edad = 40;
		listas[2].infoVotos[17].tipoVoto = 7;/* valido*/listas[2].infoVotos[17].edad = 40;
		listas[2].infoVotos[18].tipoVoto = 7;/* valido*/listas[2].infoVotos[18].edad = 40;
		listas[2].infoVotos[19].tipoVoto = 7;/* valido*/listas[2].infoVotos[19].edad = 40;
		listas[2].infoVotos[20].tipoVoto = 1;/* valido*/listas[2].infoVotos[20].edad = 65;
		listas[2].infoVotos[21].tipoVoto = 7;/* valido*/listas[2].infoVotos[21].edad = 65;
		listas[2].infoVotos[22].tipoVoto = 7;/* valido*/listas[2].infoVotos[22].edad = 65;
		listas[2].infoVotos[23].tipoVoto = 7;/* valido*/listas[2].infoVotos[23].edad = 65;
		listas[2].infoVotos[24].tipoVoto = 7;/* valido*/listas[2].infoVotos[24].edad = 65;
		listas[2].infoVotos[25].tipoVoto = 7;/* valido*/listas[2].infoVotos[25].edad = 65;
		listas[2].infoVotos[26].tipoVoto = 7;/* valido*/listas[2].infoVotos[26].edad = 65;
		listas[2].infoVotos[27].tipoVoto = 7;/* valido*/listas[2].infoVotos[27].edad = 65;
		listas[2].infoVotos[28].tipoVoto = 7;/* valido*/listas[2].infoVotos[28].edad = 65;
		listas[2].infoVotos[29].tipoVoto = 7;/* valido*/listas[2].infoVotos[29].edad = 65;
		listas[2].infoVotos[30].tipoVoto = 1;/* valido*/listas[2].infoVotos[30].edad = 65;
		listas[2].infoVotos[31].tipoVoto = 7;/* valido*/listas[2].infoVotos[31].edad = 65;
		listas[2].infoVotos[32].tipoVoto = 7;/* valido*/listas[2].infoVotos[32].edad = 65;
		listas[2].infoVotos[33].tipoVoto = 7;/* valido*/listas[2].infoVotos[33].edad = 65;
		listas[2].infoVotos[34].tipoVoto = 7;/* valido*/listas[2].infoVotos[34].edad = 65;
		listas[2].infoVotos[35].tipoVoto = 7;/* valido*/listas[2].infoVotos[35].edad = 65;
		listas[2].infoVotos[36].tipoVoto = 7;/* valido*/listas[2].infoVotos[36].edad = 65;
		listas[2].infoVotos[37].tipoVoto = 7;/* valido*/listas[2].infoVotos[37].edad = 65;
		listas[2].infoVotos[38].tipoVoto = 7;/* valido*/listas[2].infoVotos[38].edad = 65;
		listas[2].infoVotos[39].tipoVoto = 7;/* valido*/listas[2].infoVotos[39].edad = 65;
		listas[2].infoVotos[40].tipoVoto = 1;/* valido*/listas[2].infoVotos[40].edad = 65;
		listas[2].infoVotos[41].tipoVoto = 7;/* valido*/listas[2].infoVotos[41].edad = 65;
		listas[2].infoVotos[42].tipoVoto = 7;/* valido*/listas[2].infoVotos[42].edad = 65;
		listas[2].infoVotos[43].tipoVoto = 7;/* valido*/listas[2].infoVotos[43].edad = 65;
		listas[2].infoVotos[44].tipoVoto = 7;/* valido*/listas[2].infoVotos[44].edad = 65;
		listas[2].infoVotos[45].tipoVoto = 7;/* valido*/listas[2].infoVotos[45].edad = 65;
		listas[2].infoVotos[46].tipoVoto = 7;/* valido*/listas[2].infoVotos[46].edad = 65;
		listas[2].infoVotos[47].tipoVoto = 7;/* valido*/listas[2].infoVotos[47].edad = 65;
		listas[2].infoVotos[48].tipoVoto = 7;/* valido*/listas[2].infoVotos[48].edad = 65;
		listas[2].infoVotos[49].tipoVoto = 7;/* valido*/listas[2].infoVotos[49].edad = 65;
		listas[2].infoVotos[50].tipoVoto = 1;/* valido*/listas[2].infoVotos[50].edad = 65;
		listas[2].infoVotos[51].tipoVoto = 7;/* valido*/listas[2].infoVotos[51].edad = 65;
		listas[2].infoVotos[52].tipoVoto = 7;/* valido*/listas[2].infoVotos[52].edad = 65;
		listas[2].infoVotos[53].tipoVoto = 7;/* valido*/listas[2].infoVotos[53].edad = 65;
		listas[2].infoVotos[54].tipoVoto = 7;/* valido*/listas[2].infoVotos[54].edad = 65;
		listas[2].infoVotos[55].tipoVoto = 7;/* valido*/listas[2].infoVotos[55].edad = 65;
		listas[2].infoVotos[56].tipoVoto = 7;/* valido*/listas[2].infoVotos[56].edad = 65;
		listas[2].infoVotos[57].tipoVoto = 7;/* valido*/listas[2].infoVotos[57].edad = 65;
		listas[2].infoVotos[58].tipoVoto = 7;/* valido*/listas[2].infoVotos[58].edad = 65;
		listas[2].infoVotos[59].tipoVoto = 7;/* valido*/listas[2].infoVotos[59].edad = 65;
		listas[2].infoVotos[60].tipoVoto = 1;/* valido*/listas[2].infoVotos[60].edad = 16;
		listas[2].infoVotos[61].tipoVoto = 7;/* valido*/listas[2].infoVotos[61].edad = 16;
		listas[2].infoVotos[62].tipoVoto = 7;/* valido*/listas[2].infoVotos[62].edad = 16;
		listas[2].infoVotos[63].tipoVoto = 7;/* valido*/listas[2].infoVotos[63].edad = 16;
		listas[2].infoVotos[64].tipoVoto = 7;/* valido*/listas[2].infoVotos[64].edad = 16;
		listas[2].infoVotos[65].tipoVoto = 7;/* valido*/listas[2].infoVotos[65].edad = 16;
		listas[2].infoVotos[66].tipoVoto = 7;/* valido*/listas[2].infoVotos[66].edad = 16;
		listas[2].infoVotos[67].tipoVoto = 7;/* valido*/listas[2].infoVotos[67].edad = 16;
		listas[2].infoVotos[68].tipoVoto = 7;/* valido*/listas[2].infoVotos[68].edad = 16;
		listas[2].infoVotos[69].tipoVoto = 7;/* valido*/listas[2].infoVotos[69].edad = 16;
		listas[2].infoVotos[70].tipoVoto = 1;/* valido*/listas[2].infoVotos[70].edad = 16;
		listas[2].infoVotos[71].tipoVoto = 7;/* valido*/listas[2].infoVotos[71].edad = 16;
		listas[2].infoVotos[72].tipoVoto = 7;/* valido*/listas[2].infoVotos[72].edad = 16;
		listas[2].infoVotos[73].tipoVoto = 7;/* valido*/listas[2].infoVotos[73].edad = 16;
		listas[2].infoVotos[74].tipoVoto = 7;/* valido*/listas[2].infoVotos[74].edad = 16;
		listas[2].infoVotos[75].tipoVoto = 7;/* valido*/listas[2].infoVotos[75].edad = 16;
		listas[2].infoVotos[76].tipoVoto = 7;/* valido*/listas[2].infoVotos[76].edad = 16;
		listas[2].infoVotos[77].tipoVoto = 7;/* valido*/listas[2].infoVotos[77].edad = 16;
		listas[2].infoVotos[78].tipoVoto = 7;/* valido*/listas[2].infoVotos[78].edad = 16;
		listas[2].infoVotos[79].tipoVoto = 7;/* valido*/listas[2].infoVotos[79].edad = 16;
	}
	// en lista 4:	
	listas[3].cantVotosTotales = 102; // 2 nulos
	{
		listas[3].infoVotos[0].tipoVoto = 10;/* nulo*/   listas[3].infoVotos[0].edad = 18;
		listas[3].infoVotos[1].tipoVoto = 70;/* nulo */  listas[3].infoVotos[1].edad = 18;
		listas[3].infoVotos[2].tipoVoto = 7;/* valido*/  listas[3].infoVotos[2].edad = 18;
		listas[3].infoVotos[3].tipoVoto = 7;/* valido*/  listas[3].infoVotos[3].edad = 18;
		listas[3].infoVotos[4].tipoVoto = 7;/* valido*/  listas[3].infoVotos[4].edad = 18;
		listas[3].infoVotos[5].tipoVoto = 7;/* valido*/  listas[3].infoVotos[5].edad = 18;
		listas[3].infoVotos[6].tipoVoto = 7;/* valido*/  listas[3].infoVotos[6].edad = 18;
		listas[3].infoVotos[7].tipoVoto = 7;/* valido*/  listas[3].infoVotos[7].edad = 18;
		listas[3].infoVotos[8].tipoVoto = 7;/* valido*/  listas[3].infoVotos[8].edad = 18;
		listas[3].infoVotos[9].tipoVoto = 7;/* valido*/  listas[3].infoVotos[9].edad = 18;
		listas[3].infoVotos[10].tipoVoto = 1;/* valido*/ listas[3].infoVotos[10].edad = 18;
		listas[3].infoVotos[11].tipoVoto = 7;/* valido*/ listas[3].infoVotos[11].edad = 18;
		listas[3].infoVotos[12].tipoVoto = 7;/* valido*/ listas[3].infoVotos[12].edad = 18;
		listas[3].infoVotos[13].tipoVoto = 7;/* valido*/ listas[3].infoVotos[13].edad = 18;
		listas[3].infoVotos[14].tipoVoto = 7;/* valido*/ listas[3].infoVotos[14].edad = 18;
		listas[3].infoVotos[15].tipoVoto = 7;/* valido*/ listas[3].infoVotos[15].edad = 18;
		listas[3].infoVotos[16].tipoVoto = 7;/* valido*/ listas[3].infoVotos[16].edad = 18;
		listas[3].infoVotos[17].tipoVoto = 7;/* valido*/ listas[3].infoVotos[17].edad = 18;
		listas[3].infoVotos[18].tipoVoto = 7;/* valido*/ listas[3].infoVotos[18].edad = 18;
		listas[3].infoVotos[19].tipoVoto = 7;/* valido*/ listas[3].infoVotos[19].edad = 18;
		listas[3].infoVotos[20].tipoVoto = 1;/* valido*/ listas[3].infoVotos[20].edad = 18;
		listas[3].infoVotos[21].tipoVoto = 7;/* valido*/ listas[3].infoVotos[21].edad = 18;
		listas[3].infoVotos[22].tipoVoto = 7;/* valido*/ listas[3].infoVotos[22].edad = 18;
		listas[3].infoVotos[23].tipoVoto = 7;/* valido*/ listas[3].infoVotos[23].edad = 18;
		listas[3].infoVotos[24].tipoVoto = 7;/* valido*/ listas[3].infoVotos[24].edad = 18;
		listas[3].infoVotos[25].tipoVoto = 7;/* valido*/ listas[3].infoVotos[25].edad = 18;
		listas[3].infoVotos[26].tipoVoto = 7;/* valido*/ listas[3].infoVotos[26].edad = 18;
		listas[3].infoVotos[27].tipoVoto = 7;/* valido*/ listas[3].infoVotos[27].edad = 18;
		listas[3].infoVotos[28].tipoVoto = 7;/* valido*/ listas[3].infoVotos[28].edad = 18;
		listas[3].infoVotos[29].tipoVoto = 7;/* valido*/ listas[3].infoVotos[29].edad = 18;
		listas[3].infoVotos[30].tipoVoto = 1;/* valido*/ listas[3].infoVotos[30].edad = 18;
		listas[3].infoVotos[31].tipoVoto = 7;/* valido*/ listas[3].infoVotos[31].edad = 18;
		listas[3].infoVotos[32].tipoVoto = 7;/* valido*/ listas[3].infoVotos[32].edad = 18;
		listas[3].infoVotos[33].tipoVoto = 7;/* valido*/ listas[3].infoVotos[33].edad = 18;
		listas[3].infoVotos[34].tipoVoto = 7;/* valido*/ listas[3].infoVotos[34].edad = 18;
		listas[3].infoVotos[35].tipoVoto = 7;/* valido*/ listas[3].infoVotos[35].edad = 18;
		listas[3].infoVotos[36].tipoVoto = 7;/* valido*/ listas[3].infoVotos[36].edad = 18;
		listas[3].infoVotos[37].tipoVoto = 7;/* valido*/ listas[3].infoVotos[37].edad = 18;
		listas[3].infoVotos[38].tipoVoto = 7;/* valido*/ listas[3].infoVotos[38].edad = 18;
		listas[3].infoVotos[39].tipoVoto = 7;/* valido*/ listas[3].infoVotos[39].edad = 18;
		listas[3].infoVotos[40].tipoVoto = 1;/* valido*/ listas[3].infoVotos[40].edad = 18;
		listas[3].infoVotos[41].tipoVoto = 7;/* valido*/ listas[3].infoVotos[41].edad = 18;
		listas[3].infoVotos[42].tipoVoto = 7;/* valido*/ listas[3].infoVotos[42].edad = 18;
		listas[3].infoVotos[43].tipoVoto = 7;/* valido*/ listas[3].infoVotos[43].edad = 18;
		listas[3].infoVotos[44].tipoVoto = 7;/* valido*/ listas[3].infoVotos[44].edad = 18;
		listas[3].infoVotos[45].tipoVoto = 7;/* valido*/ listas[3].infoVotos[45].edad = 18;
		listas[3].infoVotos[46].tipoVoto = 7;/* valido*/ listas[3].infoVotos[46].edad = 18;
		listas[3].infoVotos[47].tipoVoto = 7;/* valido*/ listas[3].infoVotos[47].edad = 18;
		listas[3].infoVotos[48].tipoVoto = 7;/* valido*/ listas[3].infoVotos[48].edad = 18;
		listas[3].infoVotos[49].tipoVoto = 7;/* valido*/ listas[3].infoVotos[49].edad = 18;
		listas[3].infoVotos[50].tipoVoto = 1;/* valido*/ listas[3].infoVotos[50].edad = 18;
		listas[3].infoVotos[51].tipoVoto = 7;/* valido*/ listas[3].infoVotos[51].edad = 18;
		listas[3].infoVotos[52].tipoVoto = 7;/* valido*/ listas[3].infoVotos[52].edad = 18;
		listas[3].infoVotos[53].tipoVoto = 7;/* valido*/ listas[3].infoVotos[53].edad = 18;
		listas[3].infoVotos[54].tipoVoto = 7;/* valido*/ listas[3].infoVotos[54].edad = 18;
		listas[3].infoVotos[55].tipoVoto = 7;/* valido*/ listas[3].infoVotos[55].edad = 18;
		listas[3].infoVotos[56].tipoVoto = 7;/* valido*/ listas[3].infoVotos[56].edad = 18;
		listas[3].infoVotos[57].tipoVoto = 7;/* valido*/ listas[3].infoVotos[57].edad = 18;
		listas[3].infoVotos[58].tipoVoto = 7;/* valido*/ listas[3].infoVotos[58].edad = 18;
		listas[3].infoVotos[59].tipoVoto = 7;/* valido*/ listas[3].infoVotos[59].edad = 18;
		listas[3].infoVotos[60].tipoVoto = 1;/* valido*/ listas[3].infoVotos[60].edad = 18;
		listas[3].infoVotos[61].tipoVoto = 7;/* valido*/ listas[3].infoVotos[61].edad = 18;
		listas[3].infoVotos[62].tipoVoto = 7;/* valido*/ listas[3].infoVotos[62].edad = 18;
		listas[3].infoVotos[63].tipoVoto = 7;/* valido*/ listas[3].infoVotos[63].edad = 18;
		listas[3].infoVotos[64].tipoVoto = 7;/* valido*/ listas[3].infoVotos[64].edad = 18;
		listas[3].infoVotos[65].tipoVoto = 7;/* valido*/ listas[3].infoVotos[65].edad = 18;
		listas[3].infoVotos[66].tipoVoto = 7;/* valido*/ listas[3].infoVotos[66].edad = 18;
		listas[3].infoVotos[67].tipoVoto = 7;/* valido*/ listas[3].infoVotos[67].edad = 18;
		listas[3].infoVotos[68].tipoVoto = 7;/* valido*/ listas[3].infoVotos[68].edad = 18;
		listas[3].infoVotos[69].tipoVoto = 7;/* valido*/ listas[3].infoVotos[69].edad = 18;
		listas[3].infoVotos[70].tipoVoto = 1;/* valido*/ listas[3].infoVotos[70].edad = 18;
		listas[3].infoVotos[71].tipoVoto = 7;/* valido*/ listas[3].infoVotos[71].edad = 18;
		listas[3].infoVotos[72].tipoVoto = 7;/* valido*/ listas[3].infoVotos[72].edad = 18;
		listas[3].infoVotos[73].tipoVoto = 7;/* valido*/ listas[3].infoVotos[73].edad = 18;
		listas[3].infoVotos[74].tipoVoto = 7;/* valido*/ listas[3].infoVotos[74].edad = 18;
		listas[3].infoVotos[75].tipoVoto = 7;/* valido*/ listas[3].infoVotos[75].edad = 18;
		listas[3].infoVotos[76].tipoVoto = 7;/* valido*/ listas[3].infoVotos[76].edad = 18;
		listas[3].infoVotos[77].tipoVoto = 7;/* valido*/ listas[3].infoVotos[77].edad = 18;
		listas[3].infoVotos[78].tipoVoto = 7;/* valido*/ listas[3].infoVotos[78].edad = 18;
		listas[3].infoVotos[79].tipoVoto = 7;/* valido*/ listas[3].infoVotos[79].edad = 18;
		listas[3].infoVotos[80].tipoVoto = 1;/* valido*/ listas[3].infoVotos[80].edad = 18;
		listas[3].infoVotos[81].tipoVoto = 7;/* valido*/ listas[3].infoVotos[81].edad = 18;
		listas[3].infoVotos[82].tipoVoto = 7;/* valido*/ listas[3].infoVotos[82].edad = 18;
		listas[3].infoVotos[83].tipoVoto = 7;/* valido*/ listas[3].infoVotos[83].edad = 18;
		listas[3].infoVotos[84].tipoVoto = 7;/* valido*/ listas[3].infoVotos[84].edad = 18;
		listas[3].infoVotos[85].tipoVoto = 7;/* valido*/ listas[3].infoVotos[85].edad = 18;
		listas[3].infoVotos[86].tipoVoto = 7;/* valido*/ listas[3].infoVotos[86].edad = 18;
		listas[3].infoVotos[87].tipoVoto = 7;/* valido*/ listas[3].infoVotos[87].edad = 18;
		listas[3].infoVotos[88].tipoVoto = 7;/* valido*/ listas[3].infoVotos[88].edad = 18;
		listas[3].infoVotos[89].tipoVoto = 7;/* valido*/ listas[3].infoVotos[89].edad = 18;
		listas[3].infoVotos[90].tipoVoto = 1;/* valido*/ listas[3].infoVotos[90].edad = 18;
		listas[3].infoVotos[91].tipoVoto = 7;/* valido*/ listas[3].infoVotos[91].edad = 18;
		listas[3].infoVotos[92].tipoVoto = 7;/* valido*/ listas[3].infoVotos[92].edad = 18;
		listas[3].infoVotos[93].tipoVoto = 7;/* valido*/ listas[3].infoVotos[93].edad = 18;
		listas[3].infoVotos[94].tipoVoto = 7;/* valido*/ listas[3].infoVotos[94].edad = 18;
		listas[3].infoVotos[95].tipoVoto = 7;/* valido*/ listas[3].infoVotos[95].edad = 18;
		listas[3].infoVotos[96].tipoVoto = 7;/* valido*/ listas[3].infoVotos[96].edad = 18;
		listas[3].infoVotos[97].tipoVoto = 7;/* valido*/ listas[3].infoVotos[97].edad = 18;
		listas[3].infoVotos[98].tipoVoto = 7;/* valido*/ listas[3].infoVotos[98].edad = 18;
		listas[3].infoVotos[99].tipoVoto = 7;/* valido*/ listas[3].infoVotos[99].edad = 18;
	}

	// lista 5:	
	listas[4].cantVotosTotales = 10;
	{
		listas[4].infoVotos[0].tipoVoto = 1;/* valido*/ listas[4].infoVotos[0].edad = 18;
		listas[4].infoVotos[1].tipoVoto = 7;/* valido*/ listas[4].infoVotos[1].edad = 19;
		listas[4].infoVotos[2].tipoVoto = 7;/* valido*/ listas[4].infoVotos[2].edad = 25;
		listas[4].infoVotos[3].tipoVoto = 7;/* valido*/	listas[4].infoVotos[3].edad = 50;
		listas[4].infoVotos[4].tipoVoto = 7;/* valido*/	listas[4].infoVotos[4].edad = 45;
		listas[4].infoVotos[5].tipoVoto = 10;/* nulo*/  listas[4].infoVotos[5].edad = 60;
		listas[4].infoVotos[6].tipoVoto = 10;/* nulo*/  listas[4].infoVotos[6].edad = 70;
		listas[4].infoVotos[7].tipoVoto = 10;/* nulo*/  listas[4].infoVotos[7].edad = 18;
		listas[4].infoVotos[8].tipoVoto = 10;/* nulo*/	listas[4].infoVotos[8].edad = 17;
		listas[4].infoVotos[9].tipoVoto = 0;/* blanco*/ listas[4].infoVotos[9].edad = 80;
	}
}

//  metodo burbuja para ordenar de mayor a menor
void ordenarListas(sListas lista[cantListas]) {
	sListas temporal;

	sBancas temporalBancas;

	for (int i = 0;i < cantListas; i++) {
		for (int j = 0; j < cantListas - 1; j++) {
			if (lista[j].cantVotosValidos < lista[j + 1].cantVotosValidos) {
				temporal = lista[j];
				lista[j] = lista[j + 1];
				lista[j + 1] = temporal;

				temporalBancas = bancas[j];
				bancas[j] = bancas[j + 1];
				bancas[j + 1] = temporalBancas;
			}
		}
	}
}

// metodo burbuja para ordenar de mayor a menor
void ordenarParticipantes(sGanadores ganadores[cantTotalParticipantes]) {
	sGanadores temporal;

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
	int numBancas = 0;
	int numListas = 0;
	int numero = 1;

	for (int i = 0; i < 65; i++) {

		if (numBancas == 13) numBancas = 0;

		ganadores[i].numLista = listas[numListas].numeroLista;
		ganadores[i].numBanca = numero;
		switch (numBancas) {
		case 0:ganadores[i].cantVotos = bancas[numListas].cantBanca1;break;
		case 1:ganadores[i].cantVotos = bancas[numListas].cantBanca2;break;
		case 2:ganadores[i].cantVotos = bancas[numListas].cantBanca3;break;
		case 3:ganadores[i].cantVotos = bancas[numListas].cantBanca4;break;
		case 4:ganadores[i].cantVotos = bancas[numListas].cantBanca5;break;
		case 5:ganadores[i].cantVotos = bancas[numListas].cantBanca6;break;
		case 6:ganadores[i].cantVotos = bancas[numListas].cantBanca7;break;
		case 7:ganadores[i].cantVotos = bancas[numListas].cantBanca8;break;
		case 8:ganadores[i].cantVotos = bancas[numListas].cantBanca9;break;
		case 9:ganadores[i].cantVotos = bancas[numListas].cantBanca10;break;
		case 10:ganadores[i].cantVotos = bancas[numListas].cantBanca11;break;
		case 11:ganadores[i].cantVotos = bancas[numListas].cantBanca12;break;
		case 12:ganadores[i].cantVotos = bancas[numListas].cantBanca13;break;

		};
		strcpy(ganadores[i].candidato, listas[numListas].candidatos[numBancas]);
		numBancas++;
		numero++;
		if (numero == 14) numero = 1;
		if (numBancas == 13) numListas++;
	}

}
void mostrarLoteDePrueba()
{
	setearColor(6);
	cout << "\n\n+----------------------------------------------------------------------------------------------------------------------------+\n";
	cout << "|                                                         LOTE DE PRUEBA                                                     |\n";

	cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
	cout << "|                SE INGRESÓ EL NOMBRE, EL NUMERO DE LISTA Y EL NOMBRE DE LOS 25 CANDIDATOS EN EL SIGUIENTE ORDEN:            |\n";
	for (int i = 0; i < cantListas; i++)
	{
		setearColor(6);
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
		printf("| Numero de Lista |   %-42d|    Nombre de Lista |  %-37s|\n", listas[i].numeroLista, listas[i].nombreLista);
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
		setearColor(7);
		for (int j = 0; j < cantCandidatos; j++)
		{
			printf("|%59s %-2d | %58s |\n", "Nombre del Candidato n°",j+1, listas[i].candidatos[j]);
		}
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
	}
	
	
	setearColor(6);
	cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
	cout << "|                                             INFORMACIÓN DE VOTOS INGRESADOS:                                               |\n";
	cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
	for (int i = 0; i < cantListas; i++)
	{
		setearColor(6);
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
		printf("| Numero de Lista |   %-43d|    Nombre de Lista |  %-36s|\n", listas[i].numeroLista, listas[i].nombreLista);
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
		printf("| Cantidad de Votos Ingresados |   %-30d| Cantidad de Votos Válidos |  %-29d|\n", listas[i].cantVotosTotales, listas[i].cantVotosValidos);
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
		setearColor(7);
		for (int j = 0; j < listas[i].cantVotosTotales; j++)
		{
			printf("|%28s %-3d : %28d |%28s :%28d |\n", "Voto n°", j + 1, listas[i].infoVotos[j].tipoVoto,"Edad del Votante", listas[i].infoVotos[j].edad);
		}
		
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
	}
	
}
void mostrarListasPorEdad()
{
	for (int i = 0; i < cantListas; i++)
	{
		for (int j = 0; j < listas[i].cantVotosTotales; j++)
		{
			if (listas[i].infoVotos[j].edad <= 18) listas[i].hasta18++;
			else if (listas[i].infoVotos[j].edad > 18 && listas[i].infoVotos[j].edad <= 30) listas[i].hasta30++;
			else if (listas[i].infoVotos[j].edad > 30 && listas[i].infoVotos[j].edad <= 50) listas[i].hasta50++;
			else if (listas[i].infoVotos[j].edad > 50) listas[i].mas50++;
		}

	}

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
		printf("| %61s | %58d |\n", "Cantidad votos de menores de 18 años", listas[i].hasta18);
		printf("| %61s | %58d |\n", "Cantidad votos de mayores a 18 y menores o iguales a 30 años", listas[i].hasta30);
		printf("| %61s | %58d |\n", "Cantidad votos de mayores a 30 y menores o iguales a 50 años", listas[i].hasta50);
		printf("| %61s | %58d |\n", "Cantidad votos de mayores a 50 años", listas[i].mas50);
		cout << "+----------------------------------------------------------------------------------------------------------------------------+\n";
	}
	


}

void mostrarTabla()
{
	setearColor(6);
	cout << "\n\n+----------------------------------------------------------------------------------------------------------------------------+\n";
	cout <<     "|                                                    RESULTADOS OBTENIDOS                                                    |\n";
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
		"Válidos",
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
	printf("|%-10s|%-6S|%-7s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-20s|\n",
		"BLANCO", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "");
	cout << "+----------+------+-------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------------------+\n";
	printf("|%-10s|%-6d|%-7s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-20s|\n",
		"VOTOS", cantTotalVotosNulos, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "");
	printf("|%-10s|%-6S|%-7s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-5s|%-20s|\n",
		"NULOS", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "");
	cout << "+----------+------+-------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+--------------------+\n";

}
void inicializarListas()
{
	for (int i = 0; i < cantListas; i++)
	{
		listas[i].hasta18 = 0;
		listas[i].hasta30 = 0;
		listas[i].hasta50 = 0;
		listas[i].mas50 = 0;
		listas[i].cantVotosTotales = 0;
		listas[i].cantVotosValidos = 0;
		listas[i].numeroLista = 0;
		listas[i].porcentajeVotosValidos = 0;
	}
}


void setearColor(int rgb)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), rgb);
}




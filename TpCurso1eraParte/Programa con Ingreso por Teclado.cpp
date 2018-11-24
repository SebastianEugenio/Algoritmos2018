// TPAlgoritmos version ingreso de usuario por teclado

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
void mostrarListasPorEdad();
void setearColor(int rgb);

int main()
{
	setlocale(LC_ALL, ""); //habilita caracteres latinos

	inicializarListas();

	cargarNombreNumeroListas();

	cargarCandidatos();

	cargarVotos();

	procesarVotos();

	for (int i = 0; i < cantListas; i++)
	{
		asignarBancas(listas[i]);
	}

	ordenarListas(listas);

	guardarParticipantes();

	ordenarParticipantes(ganadores);

	mostrarTabla();

	mostrarListasPorEdad();

	system("pause");
	return 0;
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

// carga el nombre de los 25 candidatos ingresados por teclado en cada lista
void cargarCandidatos()
{
	for (int i = 0; i < cantListas; i++) {
		for (int j = 0; j < cantCandidatos; j++)
		{
			
			cout << endl<<"Ingrese el Nombre del Candidato " << j + 1 << " de la Lista numero " << listas[i].numeroLista << " " << listas[i].nombreLista << ": ";
			
			cin.getline(listas[i].candidatos[j], cantCaracteres);
		}
	}
}

// carga el nombre y el numero de cada lista ingresado por teclado
void cargarNombreNumeroListas()
{
	int numLista = 0;
	char nomLista[cantCaracteres];

	for (int i = 0; i < cantListas; i++)
	{		
		cout << endl << "Ingrese Número de Lista: ";
		cin >> numLista;

		cin.ignore(); // para el cin anterior no interfiera con el getline

		cout << endl<< "Ingrese Nombre de Lista "<< numLista << ": ";
		
		cin.getline(nomLista, cantCaracteres);


		guardarNombreNumeroLista(numLista, nomLista);
	}
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

void cargarVotos()
{
	for (int i = 0; i < cantListas; i++)
	{
		cout << endl<< "Ingrese la cantidad de votos de la Lista " << listas[i].nombreLista<< ": ";
		cin >> listas[i].cantVotosTotales;
	}
	for (int i = 0; i < cantListas; i++)
	{
		cout << endl << "Ingrese la Información de los " << listas[i].cantVotosTotales << "Votos de la lista " << listas[i].nombreLista<<": ";

		for (int j = 0; j < listas[i].cantVotosTotales; j++)
		{
			cout << endl << "Voto " << j + 1 << ": ";
			cout << endl << "Ingrese el tipo de Voto (0 para voto en Blanco, de 1 a 7 para Válido y otro para Nulo): ";
			cin >> listas[i].infoVotos[j].tipoVoto;
			
			cin.ignore(); // para el cin anterior no interfiera con el getline
			cout << endl << "Ingrese el Sexo del Votante: ";
			
			cin.getline(listas[i].infoVotos[j].sexo, cantCaracteres);

			cout << endl << "Ingrese la Edad del Votante en años: " ;
			cin >> listas[i].infoVotos[j].edad;
		}
	}			
}

// calcula los votos validos de cada lista, del total de listas y porcentaje
void procesarVotos()
{
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
int cantVotosValidos(sListas lista, int cantVotosTotales) 
{
	int cantValidos = 0;

	for (int i = 0; i < cantVotosTotales; i++)
	{
		if (lista.infoVotos[i].tipoVoto >= 1 && lista.infoVotos[i].tipoVoto <= 7) // si es valido
		{
			cantValidos++;

		}
		if (lista.infoVotos[i].tipoVoto == 0) // si es en blanco
		{
			cantTotalVotosEnBlanco++;
		}
		if (lista.infoVotos[i].tipoVoto < 0 || lista.infoVotos[i].tipoVoto > 7) // si es nulo
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
		bancas[lista.numeroLista - 1].cantBanca1 = lista.cantVotosValidos; // la primera banca tiene la misma cantidad de votos

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

//  metodo burbuja para ordenar de mayor a menor
void ordenarListas(sListas lista[cantListas]) 
{
	sListas temporal;

	sBancas temporalBancas;

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

void setearColor(int rgb)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), rgb);
}








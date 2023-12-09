/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion.
	(c) Ponga su nombre y numero de cuenta aqui.

	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.

******************************************************************************************************************/

#include <ctype.h>
#include "stdafx.h"
#include <string.h>
#include "corrector.h"
#define DEPURAR 1

//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario
	char	szPalabras[][TAMTOKEN]	:	szPalabraseglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	szPalabraseglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void	Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{
	FILE* fpDicc;
	char linea[10000];
	char mayu;
	char palabraDetectada[TAMTOKEN];
	int i;
	int indicePD;
	int pasada, comp;
	char aux[TAMTOKEN];
	int aux2;
	int conta, p = 0, j = 0;
	int esta;
	iNumElementos = 0;
	// abrir el achivo
	if (DEPURAR == 1)
		printf("%s", szNombre);

	fopen_s(&fpDicc, szNombre, "r");
	if (fpDicc != NULL)
	{

		if (DEPURAR == 1)
			printf("\nSi lo pude abrir");

		indicePD = 0;
		while (!feof(fpDicc))
		{
			fgets(linea, sizeof(linea), fpDicc);


			for (i = 0; i < strlen(linea); i++)
			{
				// Detectar una palabra
				if (linea[i] == ' ' || linea[i] == '\t')
				{
					if (linea[i + 1] != ' ' && linea[i+1] != '\t')
					{

						palabraDetectada[indicePD] = '\0';
						strcpy_s(szPalabras[iNumElementos], TAMTOKEN, palabraDetectada);
						iEstadisticas[iNumElementos] = 1;
						if (DEPURAR == 1)
							indicePD = 0;
						iNumElementos++;
						// eliminar los espacios en blanco
						// tabuladores y saltos de linea consecutivos

					}
				}
				else
				{
					if (linea[i] != '(' && linea[i] != ')' && linea[i] != ',' && linea[i] != '.')
					{
						mayu = towlower(linea[i]);
						palabraDetectada[indicePD] = mayu;
						indicePD++;
					}
				}
			}




			// burbujazo
			if (DEPURAR == 1)

				for (pasada = 0; pasada < iNumElementos - 1; pasada++) {
					conta = 0;
					for (comp = 0; comp < iNumElementos - 1; comp++) {

						if (DEPURAR == 1)

							if (strcmp(szPalabras[comp], szPalabras[comp + 1]) == 1)
							{

								strcpy_s(aux, TAMTOKEN, szPalabras[comp]);
								strcpy_s(szPalabras[comp], TAMTOKEN, szPalabras[comp + 1]);
								strcpy_s(szPalabras[comp + 1], TAMTOKEN, aux);

								aux2 = iEstadisticas[comp];
								iEstadisticas[comp] = iEstadisticas[comp + 1];
								iEstadisticas[comp + 1] = aux2;


							}
					}
				}


			for (int i = 1; i < iNumElementos; i++)
			{
				if (strcmp(szPalabras[i - 1], szPalabras[i]) != 0)
				{
					j++;
					// Copiar palabra y estadística si no es duplicada
					strcpy_s(szPalabras[j], TAMTOKEN, szPalabras[i]);
					iEstadisticas[j] = iEstadisticas[i];
				}
				else
				{
					// Fusionar estadísticas si es duplicada
					iEstadisticas[j] += iEstadisticas[i];
				}
			}

			// Actualizar el número de elementos después de eliminar duplicados
			iNumElementos = j + 1;

			if (DEPURAR == 1)
				printf("\n%i\n", iNumElementos);

		}

		fclose(fpDicc);
	}
	else
	{
		if (DEPURAR == 1)
			printf("\nNo lo pude abrir");
	}





}

/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int& iNumLista)							    //Numero de elementos en la szListaFinal
{

	iNumLista = 0;
	for (int i = 0; i < iNumSugeridas; i++) {
		for (int j = 0; j < iNumElementos; j++) {


			if (strcmp(szPalabrasSugeridas[i], szPalabras[j]) == 0) {
				bool bandera = false;
				for (int k = 0; k < iNumLista && !bandera; k++)
					if (strcmp(szListaFinal[k], szPalabras[j]) == 0)
						bandera = true;
				if (bandera) continue;
				strcpy_s(szListaFinal[iNumLista], szPalabrasSugeridas[i]);
				iPeso[iNumLista++] = iEstadisticas[j];
			}
		}
	}

	for (int i = 0; i < iNumLista; i++) {
		for (int j = 0; j < iNumLista - 1; j++) {
			if (iPeso[j] < iPeso[j + 1]) {
				int iaux; char caux[50];
				strcpy_s(caux, szListaFinal[j + 1]); iaux = iPeso[j + 1];
				strcpy_s(szListaFinal[j + 1], szListaFinal[j]); iPeso[j + 1] = iPeso[j];
				strcpy_s(szListaFinal[j], caux); iPeso[j] = iaux;
			}
		}
	}
}


/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						//Palabra a clonar   palabra
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char* szPalabraLeida,						// Palabra a clonar
	char  szPalabrasSugeridas[][TAMTOKEN], 	    //Lista de palabras clonadas
	int& iNumSugeridas)						    //Numero de elementos en la lista
{
	char abc[36] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'ñ', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'á', 'é', 'í', 'ó', 'ú' };
	char aux[TAMTOKEN]; iNumSugeridas = 0;
	int k, j, i, contador;


	strcpy_s(aux, szPalabraLeida);
	for (int i = 0; i < strlen(szPalabraLeida); i++) {

		for (int j = 0; j < 32; j++) {
			aux[i] = abc[j];
			strcpy_s(szPalabrasSugeridas[iNumSugeridas++], aux);
		} aux[i] = szPalabraLeida[i];
	}


	for (k = 1; k < strlen(szPalabraLeida) + 1; k++) {
		aux[k] = szPalabraLeida[k - 1];


	} aux[k] = '\0';

	for (i = 0; i < strlen(szPalabraLeida) + 1; i++) {

		for (j = 0; j < 36; j++) {
			aux[i] = abc[j];

			strcpy_s(szPalabrasSugeridas[iNumSugeridas++], aux);
		}
		aux[i] = szPalabraLeida[i];
	}

	contador = 0;
	for (i = 0; i < strlen(szPalabraLeida) && strlen(szPalabraLeida) != 1; i++) {

		for (j = 0; j < strlen(szPalabraLeida); j++) {
			if (j != i)
				aux[contador++] = szPalabraLeida[j];


		} aux[contador] = '\0';


		strcpy_s(szPalabrasSugeridas[iNumSugeridas++], aux);


		strcpy_s(aux, szPalabraLeida);

		contador = 0;
	}

	for (i = 0; i < strlen(szPalabraLeida) - 1; i++) {
		aux[i] = szPalabraLeida[i + 1];
		aux[i + 1] = szPalabraLeida[i];


		strcpy_s(szPalabrasSugeridas[iNumSugeridas++], aux);

		strcpy_s(aux, szPalabraLeida);
	}
	strcpy_s(szPalabrasSugeridas[iNumSugeridas++], szPalabraLeida);



	for (j = 0; j < iNumSugeridas - 1; j++) {

		for (i = j + 1; i < iNumSugeridas; i++) {

			if (strcmp(szPalabrasSugeridas[j], szPalabrasSugeridas[i]) > 0) {
				strcpy_s(aux, szPalabrasSugeridas[j]);
				strcpy_s(szPalabrasSugeridas[j], szPalabrasSugeridas[i]);
				strcpy_s(szPalabrasSugeridas[i], aux);
			}
		}
	}


}



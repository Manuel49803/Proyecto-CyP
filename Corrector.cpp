/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion. 
	(c) Ponga su nombre y numero de cuenta aqui.
	
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
	
******************************************************************************************************************/


#include "stdafx.h"
#include <string.h>
#include "corrector.h"
#define DEPURAR 1

//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
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
					if (linea[i + 1] != ' ' && linea[i + 1] != '\t')
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
					// Copiar palabra y estad�stica si no es duplicada
					strcpy_s(szPalabras[j], TAMTOKEN, szPalabras[i]);
					iEstadisticas[j] = iEstadisticas[i];
				}
				else
				{
					// Fusionar estad�sticas si es duplicada
					iEstadisticas[j] += iEstadisticas[i];
				}
			}

			// Actualizar el n�mero de elementos despu�s de eliminar duplicados
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
void	ListaCandidatas		(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
{

	//Sustituya estas lineas por su c�digo
	strcpy(szListaFinal[0], szPalabrasSugeridas[ 0] ); //la palabra candidata
	iPeso[0] = iEstadisticas[0];			// el peso de la palabra candidata
	
	iNumLista = 1;							//Una sola palabra candidata
}

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
{
	//Sustituya estas lineas por su c�digo
	strcpy(szPalabrasSugeridas[0], szPalabraLeida); //lo que sea que se capture, es sugerencia
	iNumSugeridas = 1;							//Una sola palabra sugerida
}

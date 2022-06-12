#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Passenger.h"
#include "parser.h"

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromText(FILE* pFile , LinkedList* pArrayListPassenger)
{
	int retorno = -1;
	Passenger* auxPassenger;
	int r;
	//float var4;
	char var1[4096], var2[4096], var3[4096], var4[4096], var5[4096], var6[4096], var7[4096];

	if(pFile != NULL && pArrayListPassenger != NULL)
	{
		do
		{
			//,%[^\n]
			//id,name,lastname,price,flycode,typePassenger,statusFlight
			r = fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", var1, var2, var3, var4, var5, var6, var7);
			//Passenger_newParametros(char* idStr, char* nombreStr, char* apellidoStr, float precio, char* codigoVuelo, char* tipoPasajeroStr)

			auxPassenger = Passenger_newParametros(var1, var2, var3, var4, var5, var6, var7);
			if(auxPassenger != NULL)
			{
				if(r == 7)
				{
					ll_add(pArrayListPassenger, auxPassenger);
					retorno = 0;
				}
				else
				{
					Passenger_delete(auxPassenger);
				}
			}
		}while(!feof(pFile));
	}
	return retorno;
}

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromBinary(FILE* pFile, LinkedList* pArrayListPassenger)
{

	int retorno = -1;
	Passenger* auxPassenger;
	int r;

	if(pFile != NULL && pArrayListPassenger != NULL)
	{
		do
		{
			auxPassenger = Passenger_new();
			r = fread(auxPassenger, sizeof(Passenger), 1, pFile);
			if(auxPassenger != NULL)
			{
				if(r == 1)
				{
					ll_add(pArrayListPassenger, auxPassenger);
					retorno = 0;
				}
				else
				{
					Passenger_delete(auxPassenger);
				}
			}
		}while(!feof(pFile));
	}
	return retorno;
}

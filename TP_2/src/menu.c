/*
 * menu.c
 *
 *  Created on: 14 may. 2022
 *      Author: Blanco Julián Agustín
 */




#include <stdio.h>
#include "utn_biblioteca.h"
#include "menu.h"
#define CANT_REINTENTOS 2

/*
 * \ brief - Muestra el menu, pide ingresar una opción y devuelve el dato por medio de un puntero.
 * \ param - int* pOption, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ param - Employee* list, Es el puntero al array de empleados.
 * \ param - int len, indica la longitud del array.
 */
void showMenu(int* pOption, Passenger* list, int len)
{
	int option;
	if(pOption != NULL && list != NULL && len > 0)
	{
		if(utn_getNumberInt(&option, "***Menu de opciones***\n\n"
										 "1- Alta de pasajero.\n"
										 "2- Modificar pasajero.\n"
										 "3- Baja de pasajero.\n"
										 "4- Informar:\n"
										 "\t1. Listado de pasajeros.\n"
										 "\t2. Total y promedio de los precios, y cuantos pasajeros superan el precio promedio.\n"
										 "\t3. Listado de pasajeros por Código de vuelo y estados de vuelos ‘ACTIVO’\n"
										 "5- Salir.\n\n"
										 "Ingrese la opcion: ", "Opcion ingresada invalida.\n", 1, OPTION_MENU, CANT_REINTENTOS) == 0)
		{
			if(option > 1 && option < 5 && isEmptyArrayPassangers(list, len) == 1)
			{
				printf("Se debe cargar un pasajero para usar estas funciones.\n\n");
				*pOption = 0;
			}
			else
			{

				*pOption = option;

			}
		}
	}
}

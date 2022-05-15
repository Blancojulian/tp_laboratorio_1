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
 * \ param - int* pOptionMenu, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ param - int* pOptionReport, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ param - int* pOptionModify, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ param - Employee* list, Es el puntero al array de empleados.
 * \ param - int len, indica la longitud del array.
 */
void showMenu(int* pOptionMenu, int* pOptionReport, int* pOptionModify, Passenger* list, int len)
{
	int optionMenu;
	int optionReport;
	int optionModify;

	if(pOptionMenu != NULL && pOptionModify != NULL && pOptionReport != NULL && list != NULL && len > 0)
	{
		if(utn_getNumberInt(&optionMenu, "***Menu de opciones***\n\n"
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
			system("cls");
			if(optionMenu != 1 && isEmptyArrayPassangers(list, len) != 1)
			{
				printf("Se debe cargar un empleado para usar estas funciones.\n\n");
				*pOptionMenu = 0;
			}
			else
			{
				*pOptionMenu = optionMenu;
				switch (optionMenu)
				{
					case 2:
						if(utn_getNumberInt(&optionModify, "1 - Cambiar el nombre del pasajero.\n"
                            "2 - Cambiar el apellido del empleado.\n"
                            "3 - Cambiar el precio del viaje.\n"
                            "4 - Cambiar el tipo de pasajero.\n"
                            "5 - Cambiar el codigo de vuelo (AAA-000000).\n"
							"Ingrese la opcion: ", "Opcion ingresada invalida.\n", 1, OPTION_MODIFY, CANT_REINTENTOS) == 0)
						{
							*pOptionModify = optionModify;
						}
						break;
					case 4:
						if(utn_getNumberInt(&optionReport, "***Menu de informe***\n\n"
														   "1. Listado de pasajeros(ordenado por Apellido y Tipo de pasajero).\n"
														   "2. Total y promedio de los precios, y cuantos pasajeros superan el precio promedio.\n"
														   "3. Listado de pasajeros por Código de vuelo y estados de vuelos ‘ACTIVO’\n"
														   "Ingrese la opcion: ", "Opcion ingresada invalida.\n", 1, OPTION_REPORT, CANT_REINTENTOS) == 0)
						{
							*pOptionReport = optionReport;
						}
						break;
				}
			}
		}
	}
}

/*
 ============================================================================
 Name        : TP_2.c
 Author      : Blanco Julián Agustín
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <string.h>
#include "utn_biblioteca.h"
//#include "arrayPassenger.h"
#include "menu.h"
#include "flight.h"
#define LEN_ARRAY_PASSENGER 2000
#define LEN_ARRAY_FLIGHT 2000

int main(void) {
	setbuf(stdout, NULL);
	Passenger auxPassenger;
	Passenger listPassengers[LEN_ARRAY_PASSENGER];
	Flight auxFlight;
	Flight listFlights[LEN_ARRAY_FLIGHT];
	int optionMenu;
	int optionReport;
	int optionModify;
	int idRemove;
	//int indexRemove;
	int idModify;
	int indexModify;
	int order;
	float accumulator;
	float average;
	int counter;
	int flagPause = 0;

	//array tipos de pasajeros
	TypePassenger arrayTypePassanger[LEN_ARRAY_TYPE_PASSENGER] = {
	    {EJECUTIVA, "Ejecutiva"},
	    {ECONOMICA, "Economica"},
	    {TURISTA, "Turista"}
	};

	if(initPassengers(listPassengers, LEN_ARRAY_PASSENGER) == 0 &&
		initFlight(listFlights, LEN_ARRAY_FLIGHT) == 0)
	{
		do
		{
			if(flagPause)
			{
				system("pause");
				system("cls");
			}
			showMenu(&optionMenu, &optionReport, &optionModify, listPassengers, LEN_ARRAY_PASSENGER);
				switch (optionMenu)
				{
					case 1://addPassenger(Passenger* list, int len, int id, char name[], char lastName[],float price,int typePassenger, char flycode[])
						if( requestDataPassenger(&auxPassenger) == 0 &&
							requestDataFlight(&auxFlight) == 0 &&
							addFlight(listFlights, LEN_ARRAY_FLIGHT, auxFlight.statusFlight, auxFlight.flyCode) == 0 &&
							addPassenger(listPassengers, LEN_ARRAY_PASSENGER, auxPassenger.id, auxPassenger.name,
							auxPassenger.lastName, auxPassenger.price, auxPassenger.typePassenger, auxFlight.flyCode) == 0)
						{
							printf("El pasajero fue cargado correctamente.\n");
						}
						break;
					case 2:
						if( printPassengers(listPassengers, LEN_ARRAY_PASSENGER) == 0 &&
							utn_getNumberInt(&idModify, "Ingrese el id del pasajero que quiere dar de baja: ", "Error.\n", 1, INT_MAX, 2) == 0)
						{
							indexModify = findPassengerById(listPassengers, LEN_ARRAY_PASSENGER, idModify);
							if( indexModify >= 0 &&
								modifyPassenger(listPassengers, LEN_ARRAY_PASSENGER, indexModify, optionModify) == 0)
							{
								printf("El pasajero se modifico correctamente.\n");
							}
							else
							{
								printf("No hay datos ingresados en ese id.\n");
							}
						}
						break;
					case 3:
						if( printPassengers(listPassengers, LEN_ARRAY_PASSENGER) == 0 &&
							utn_getNumberInt(&idRemove, "Ingrese el id del empleado que quiere dar de baja: ", "Error.\n", 1, INT_MAX, 2) == 0)
						{
							if( removePassenger(listPassengers, LEN_ARRAY_PASSENGER, idRemove) == 0)
							{
								printf("Se dio de baja al pasajero.\n");
							}
							else
							{
								printf("No hay datos ingresados en ese id.\n");
							}
						}
						break;
					case 4:
						switch (optionReport)
						{
							case 1:
								if( utn_getNumberInt(&order, "Indiqué el orden de los pasajeros (1 - Ascendente / 0 - Descendente): ", "Error.\n", 0, 1, 2) == 0 &&
									sortPassengers(listPassengers, LEN_ARRAY_PASSENGER, order) == 0)
								{
									printf("El listado fue ordenado correctamente.\n");
									printPassengers(listPassengers, LEN_ARRAY_PASSENGER);
								}
								break;
							case 2:
								if( AcumularPromediarPrecio(listPassengers, LEN_ARRAY_PASSENGER, &accumulator, &average) == 0 &&
									calculatePassengerOverAveragePrice(listPassengers, LEN_ARRAY_PASSENGER, &counter, average) == 0)
								{
									printf("El total de precios es: %.2f. El promedio de los precios es: %.2f.\n", accumulator, average);
									printf("Hay %d pasajeros que pagaron mas del precio promedio.\n", counter);
								}
								break;
							case 3:

								break;
						}
						break;
				}
				flagPause = 1;
		}while(optionMenu != 5);
	}
	return EXIT_SUCCESS;
}

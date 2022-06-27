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
#include <ctype.h>
#include "utn_biblioteca.h"
#include "arrayPassenger.h"
#include "menu.h"
#include "flight.h"
#define LEN_ARRAY_PASSENGER 2000
#define LEN_ARRAY_FLIGHT 2000

#define DECENDENTE 0
#define ASCENDENTE 1
#define CANT_REINTENTOS 2

int main(void) {
	setbuf(stdout, NULL);
	Passenger auxPassenger;
	Passenger listPassengers[LEN_ARRAY_PASSENGER];
	//Flight auxFlight;
	Flight listFlights[LEN_ARRAY_FLIGHT];
	int option;
	int idRemove;
	int idModify;


	if(initPassengers(listPassengers, LEN_ARRAY_PASSENGER) == 0 &&
		initFlight(listFlights, LEN_ARRAY_FLIGHT) == 0)
	{
		//(AAA-000000)
		//ACTIVO 1
		//CANCELADO 2
		//DEMORADO 3
		Flight_altaForzada(listFlights, LEN_ARRAY_FLIGHT, ACTIVO, "BBA-123456");
		Flight_altaForzada(listFlights, LEN_ARRAY_FLIGHT, DEMORADO, "ABC-333444");
		Flight_altaForzada(listFlights, LEN_ARRAY_FLIGHT, ACTIVO, "MDQ-987654");
		Flight_altaForzada(listFlights, LEN_ARRAY_FLIGHT, CANCELADO, "MDP-555555");

		//EJECUTIVA 1
		//ECONOMICA 2
		//TURISTA 3
		//Para usar Passenger_altaForzada tiene que estar cargado el codigo de vuelo, usar Flight_altaForzada para cargarlo
		Passenger_altaForzada(listPassengers, LEN_ARRAY_PASSENGER, listFlights, LEN_ARRAY_FLIGHT, "Jorge", "Esteban", 10000, EJECUTIVA, "ABC-333444");
		Passenger_altaForzada(listPassengers, LEN_ARRAY_PASSENGER, listFlights, LEN_ARRAY_FLIGHT, "Juan", "Diaz", 30000, EJECUTIVA, "MDQ-987654");

		do{
			showMenu(&option, listPassengers, LEN_ARRAY_PASSENGER);

			switch (option)
			{
				case 1:
					if( requestDataPassenger(&auxPassenger, listFlights, LEN_ARRAY_FLIGHT) == 0 &&
						addPassenger(listPassengers, LEN_ARRAY_PASSENGER, auxPassenger.id, auxPassenger.name,
						auxPassenger.lastName, auxPassenger.price, auxPassenger.typePassenger, auxPassenger.flyCode) == 0)
					{
						printf("El pasajero fue cargado correctamente.\n");
					}
					break;
				case 2:
					if( sortPassengersById(listPassengers, LEN_ARRAY_PASSENGER, DECENDENTE) == 0 &&
						printPassengers(listPassengers, LEN_ARRAY_PASSENGER, listFlights, LEN_ARRAY_FLIGHT) == 0 &&
						utn_getNumberInt(&idModify, "Ingrese el id del pasajero que quiere modificar: ", "Error.\n", 1, INT_MAX, CANT_REINTENTOS) == 0)
					{
						if( idModify > 0 &&
							modifyPassenger(listPassengers, LEN_ARRAY_PASSENGER, idModify, listFlights, LEN_ARRAY_FLIGHT) == 0)
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
					if( sortPassengersById(listPassengers, LEN_ARRAY_PASSENGER, DECENDENTE) == 0 &&
						printPassengers(listPassengers, LEN_ARRAY_PASSENGER, listFlights, LEN_ARRAY_FLIGHT) == 0 &&
						utn_getNumberInt(&idRemove, "Ingrese el id del pasajero que quiere dar de baja: ", "Error.\n", 1, INT_MAX, CANT_REINTENTOS) == 0)
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
					informesPassenger(listPassengers, LEN_ARRAY_PASSENGER, listFlights, LEN_ARRAY_FLIGHT);
					break;
			}


		}while(option != 5);
	}
	return EXIT_SUCCESS;
}

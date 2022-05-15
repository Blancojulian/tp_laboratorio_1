/*
 * flight.h
 *
 *  Created on: 14 may. 2022
 *      Author: Blanco Julián Agustín
 */

#ifndef FLIGHT_H_
#define FLIGHT_H_

#include <stdio.h>
#include <stdlib.h>
#define LEN_STRING 51
#define LEN_FLY_CODE 11

#define ACTIVO 1
#define CANCELADO 2
#define DEMORADO 3

#define LEN_ARRAY_TYPE_PASSENGER 3
#define EJECUTIVA 1
#define ECONOMICA 2
#define TURISTA 3


typedef struct{
    char flyCode[LEN_FLY_CODE];
    int statusFlight;
    int isEmpty;
}Flight;

typedef struct{
    int idTypePassenger;
    char description[LEN_STRING];
}TypePassenger;

int initFlight(Flight* list, int len);
int requestDataFlight(Flight* auxFlight);
int searchFreeIndexFlight(Flight* list, int len, int* pIndex);
int modifyStatusFlight(Flight* list, int len, int index);
int printFlights(Flight* list, int len);
int findFlightByFlyCode(Flight* list, int len,char* flyCode);
int removeFlight(Flight* list, int len, char* flyCode);
int addFlight(Flight* list, int len, int statusFlight, char flyCode[]);


#endif /* FLIGHT_H_ */

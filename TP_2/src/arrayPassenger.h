/*
 * arrayPassenger.h
 *
 *  Created on: 14 may. 2022
 *      Author: Blanco Julián Agustín
 */

#ifndef ARRAYPASSENGER_H_
#define ARRAYPASSENGER_H_

#define LEN_STRING 51
#define LEN_FLY_CODE 11
#define MAX_PRICE 500000


typedef struct{
    int id;
    char name[LEN_STRING];
    char lastName[LEN_STRING];
    float price;
    char flyCode[LEN_FLY_CODE];
    int typePassenger;
    int isEmpty;
}Passenger;

int initPassengers(Passenger* list, int len);
int addPassenger(Passenger* list, int len, int id, char name[], char lastName[],float price,int typePassenger, char flyCode[]);
int searchFreeIndex(Passenger* list, int len, int* pIndex);
int findPassengerById(Passenger* list, int len,int id);
int removePassenger(Passenger* list, int len, int id);
int sortPassengers(Passenger* list, int len, int order);
int printPassengers(Passenger* list, int len);
int requestDataPassenger(Passenger* auxPassenger);
int modifyPassenger(Passenger* list, int len, int index, int field);
int isEmptyArrayPassangers(Passenger* list, int len);

int AcumularPromediarPrecio(Passenger* list, int len, float* pAccumulator, float* pAverage);
int calculatePassengerOverAveragePrice(Passenger* list, int len, int* pCounter, float average);



#endif /* ARRAYPASSENGER_H_ */

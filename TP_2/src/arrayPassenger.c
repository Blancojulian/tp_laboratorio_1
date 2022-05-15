/*
 * arrayPassenger.c
 *
 *  Created on: 14 may. 2022
 *      Author: Blanco Julián Agustín
 */


#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <string.h>
#include "utn_biblioteca.h"
#include "arrayPassenger.h"
#define CANT_REINTENTOS 2

static int generateNewId(void);

/**
 * \brief Incrementa el id y lo retorna.
 * \return Retorna el id
 */
static int generateNewId(void)
{
	static int id = 0;

	id++;
	return id;
}

/**
 * \brief Inicializa el array de pasajeros.
 * \param Passenger* list, Es el puntero al array de pasajeros.
 * \param int len, es el limite de array.
 * \return (-1) Error / (0) Ok
 */
int initPassengers(Passenger* list, int len)
{
    int retorno = -1;
    int i;
    if(list != NULL && len > 0)
    {
        for(i = 0; i < len; i++)
        {
            list[i].isEmpty = 1;
        }
        retorno = 0;
    }
    return retorno;
}

/**
 * \brief Realiza el alta de un pasajero solo si el indice corresponde a un espacio vacio (isEmpty == 1)
 * \param Passenger* list, Es el puntero al array de pasajeros.
 * \param int len, es el limite de array.
 * \param int id, indica el id del pasajero.
 * \param char* name, indica el nombre del pasajero.
 * \param char* lastName, indica el apellido del pasajero.
 * \param float price, indica el salario del pasajero.
 * \param int sector, indica el sector del pasajero.
 * \param int typePassenger, indica el tipo de pasajero.
 * \param char* flycode, indica el nombre del codigo de vuelo.
 * \return (-1) Error / (0) Ok
 */
int addPassenger(Passenger* list, int len, int id, char name[], char lastName[], float price, int typePassenger, char flyCode[])
{
    int retorno = -1;
    int index;
    if(list != NULL && len > 0 && id > 0 && name != NULL && lastName != NULL && price > 0 &&
        typePassenger > 0 && flyCode != NULL)
    {
        if(searchFreeIndex(list, len, &index) == 0 && index < len)
        {
            //list[index].id = generateNewId();
            strncpy(list[index].name, name, LEN_STRING);
            strncpy(list[index].lastName, lastName, LEN_STRING);
            list[index].price = price;
            strncpy(list[index].flyCode, flyCode, LEN_FLY_CODE);
            list[index].typePassenger = typePassenger;
            list[index].isEmpty = 0;

            retorno = 0;
        }
        else
		{
			printf("No hay espacios libres para dar de alta.");
		}
    }


    return retorno;
}
/**
 * \brief Busca un espacio libre en el array de pasajeros.
 * \param Passenger* list, Es el puntero al array de pasajeros.
 * \param int len, es el limite de array.
 * \param int* index, Es el puntero al index del espacio libre.
 * \return (-1) Error / (0) Ok
 */
int searchFreeIndex(Passenger* list, int len, int* pIndex)
{
    int retorno = -1;

    if(list != NULL && len > 0 && pIndex != NULL)
    {
        int i = 0;
        while(i < len)
        {
            if(list[i].isEmpty == 1)
            {
                *pIndex = i;
                retorno = 0;
                break;
            }
            i++;
        }
    }
    return retorno;
}
/**
 * \brief Busca el pasajero por id y retorna su indice.
 * \param Passenger* list, Es el puntero al array de pasajeros.
 * \param int len, es el limite de array.
 * \param int id, id que será buscado.
 * \return Retorna el indice
 */
int findPassengerById(Passenger* list, int len, int id)
{
    int retorno = -1;

    if(list != NULL && len > 0 && id > 0)
    {
        int i = 0;
        while(i < len)
        {
            if(id == list[i].id)
            {
                retorno = i;
                break;
            }
            i++;
        }
    }
    return retorno;
}

/**
 * \brief Realiza baja logica de un pasajero si el indice no está vacio.
 * \param Passenger* list, Es el puntero al array de pasajeros.
 * \param int len, es el limite de array.
 * \return (-1) Error / (0) Ok
 */
int removePassenger(Passenger* list, int len, int id)
{
    int retorno = -1;
    int index;
    if(list != NULL && len > 0 && id > 0)
    {
        index = findPassengerById(list, len, id);
        if(list[index].isEmpty == 0 && index > 0)
        {
            list[index].isEmpty = 1;
            retorno = 0;
        }
    }
    return retorno;
}

//strncmp
//if Return value < 0 then it indicates str1 is less than str2.
//if Return value > 0 then it indicates str2 is less than str1.
//if Return value = 0 then it indicates str1 is equal to str2.

/*
 * \ brief - Ordena array de pasajeros por apellido y tipo de pasajero de manera ascendente o descendente.
 * \ param - Passenger* list, recibe el array a utilizar.
 * \ param - int len, indica la longitud del array.
 * \ param - int order, indica el orden de los elementos. 1 en caso de ascendente y 0 en caso de descendente.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
int sortPassengers(Passenger* list, int len, int order)
{
    Passenger aux;
    int retorno = -1;
    int flagSwap = 0;
    int i = 0;

    if(list != NULL && len > 0 && (order == 0 || order == 1))
    {
        do
        {
            flagSwap = 0;
            len--;
            for(i = 0; i < len; i++)
            {
                // 0 - orden descendente
                // 1 - orden ascendente
                if((order == 0 && strncmp(list[i].lastName, list[i+1].lastName, LEN_STRING) < 0) ||
                    (order == 1 && strncmp(list[i].lastName, list[i+1].lastName, LEN_STRING) > 0) ||
                    (strncmp(list[i].lastName, list[i+1].lastName, LEN_STRING) == 0 &&
                    ((order == 0 && list[i].typePassenger < list[i+1].typePassenger) ||
                    (order == 1 && list[i].typePassenger > list[i+1].typePassenger))))
                {
                    aux = list[i+1];
                    list[i+1] = list[i];
                    list[i] = aux;
                    flagSwap = 1;
                }
            }
        }while(flagSwap);
        retorno = 0;
    }
    return retorno;
}

/**
 * \brief Imprime los pasajeros cargados.
 * \param Passenger* list, Es el puntero al array de pasajeros.
 * \param int len, es el limite de array
 * \return (-1) Error / (0) Ok
 */
int printPassengers(Passenger* list, int len)
{
	int retorno = -1;
	int i;

	if(list != NULL && len > 0)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0)
			{
				printf( "Id: %d - Nombre: %s - Apellido: %s - Precio: %.2f - Codigo de vuelo: %s - Tipo de pasajero: %d.\n"
						,list[i].id , list[i].name, list[i].lastName, list[i].price, list[i].flyCode, list[i].typePassenger);
			}
		}
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief Modifica datos de un pasajero si el indice no está vacio.
 * \param Passenger* list, Es el puntero al array de pasajeros.
 * \param int len, es el limite de array.
 * \param Passenger aux, recibe un dato del tipo Passenger.
 * \param int index, es el indice donde se cargara el pasajero.
 * \param int field, indica el campo que será modificado.
 * \return (-1) Error / (0) Ok
 */
int modifyPassenger(Passenger* list, int len, int index, int field)
{
	int retorno = -1;
	Passenger aux;

	if(list != NULL && len > 0 && index >= 0 && list[index].isEmpty == 0)
	{
	    aux = list[index];
		if( (field == 1 && utn_getName(aux.name, "Ingrese el nombre del empleado: ", "Nombre invalido.\n", CANT_REINTENTOS, LEN_STRING) == 0) ||
			(field == 2 && utn_getName(aux.lastName, "Ingrese el apellido del empleado: ", "Apellido invalido.\n", CANT_REINTENTOS, LEN_STRING) == 0) ||
			(field == 3 && utn_getNumberFloat(&aux.price, "Ingrese el precio del viaje: ", "Precio invalido.\n", 1, MAX_PRICE, CANT_REINTENTOS) == 0) ||
			(field == 4 && utn_getNumberInt(&aux.typePassenger, "\n1) Ejecutiva\n2) Economica\n3) Turista\nIngrese tipo de cliente: ", "Tipo de cliente invalido.\n", 1, 3, CANT_REINTENTOS) == 0) ||
			(field == 5 && utn_getFlyCode(aux.flyCode, "\nIngrese codigo de vuelo (AAA-000000): ", "Codigo invalido.\n", CANT_REINTENTOS, LEN_FLY_CODE) == 0))
		{
			aux.isEmpty = 0;
			list[index] = aux;
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief Solicita los datos del pasajero al usuario.
 * \param Passenger* passenger, Es el puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int requestDataPassenger(Passenger* auxPassenger)
{
	int retorno = -1;
	Passenger aux;

	if(auxPassenger != NULL)
	{
		if(utn_getName(aux.name, "\nIngrese el nombre del empleado: ", "Nombre invalido.\n", CANT_REINTENTOS, LEN_STRING) == 0 &&
		    utn_getName(aux.lastName, "\nIngrese el apellido del empleado: ", "Apellido invalido.\n", CANT_REINTENTOS, LEN_STRING) == 0 &&
			utn_getNumberFloat(&aux.price, "\nIngrese el precio del viaje: ", "Precio invalido.\n", 1, 500000, CANT_REINTENTOS) == 0 &&
			utn_getNumberInt(&aux.typePassenger, "\n1) Ejecutiva\n2) Economica\n3) Turista\nIngrese tipo de cliente: ", "Tipo de cliente invalido.\n", 1, 3, CANT_REINTENTOS) == 0)
		{
		    aux.id = generateNewId();
			*auxPassenger = aux;
			retorno = 0;
		}
		else
		{
			printf("Error al ingresar los datos.");
		}
	}
	return retorno;
}

/**
 * \brief Controla si el array tiene pasajeros cargados.
 * \param Passanger* list, Es el puntero al array de pasajeros.
 * \param int len, es el limite de array.
 * \return (1) true, esta vacio / (0) false, tiene pasajeros cargados
 */
int isEmptyArrayPassangers(Passenger* list, int len)
{
	int retorno = 1;
	int i = 0;

	if (list != NULL && len > 0)
	{
	    while(i < len)
	    {
	        if(list[i].isEmpty == 0)
			{
				retorno = 0;
				break;
			}
			i++;
	    }
	}
	return retorno;
}

//REFACTORIZAR

/**
 * \brief Acumula salario total, calcula el promedio y devuelve ambos como valores.
 * \param Passenger* list, Es el puntero al array de pasajeros.
 * \param int len, es el limite de array.
 * \param float* pAccumulator, puntero a espacio de memoria.
 * \param float* pAverage, puntero a espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int AcumularPromediarPrecio(Passenger* list, int len, float* pAccumulator, float* pAverage)
{
	int retorno = -1;
	int i;
	float accumulator = 0;
	int counter = 0;

	if (list != NULL && len > 0 && pAccumulator != NULL && pAverage != NULL)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0)
			{
				accumulator += list[i].price;
				*pAccumulator = accumulator;
				counter++;
				retorno = 0;
			}
		}
		*pAverage = accumulator / counter;
	}
	return retorno;
}
/**
 * \brief Calcula la cantidad de pasajeros que estan sobre el salario promedio.
 * \param Passenger* list, Es el puntero al array de pasajeros.
 * \param int len, es el limite de array.
 * \param int* pAccumulator, puntero a espacio de memoria.
 * \param float average, recibe el dato del salario promedio.
 * \return (-1) Error / (0) Ok
 */
int calculatePassengerOverAveragePrice(Passenger* list, int len, int* pCounter, float average)
{
	int retorno = -1;
	int i;
	int counter = 0;

	if (list != NULL && len > 0 && pCounter != NULL && average > 0)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0 && list[i].price > average)
			{
				counter++;
			}
		}
		*pCounter = counter;
		retorno = 0;
	}
	return retorno;
}

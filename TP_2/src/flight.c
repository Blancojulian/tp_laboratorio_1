/*
 * flight.c
 *
 *  Created on: 14 may. 2022
 *      Author: Blanco Julián Agustín
 */


#include <string.h>
#include <ctype.h>
#include "flight.h"
#include "utn_biblioteca.h"
#define CANT_REINTENTOS 2

/**
 * \brief Inicializa el array de vuelos.
 * \param Flight* list, Es el puntero al array de vuelos.
 * \param int len, es el limite de array.
 * \return (-1) Error / (0) Ok
 */
int initFlight(Flight* list, int len)
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
 * \brief Solicita los datos del vuelo al usuario.
 * \param Flight* auxFlight, Es el puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int requestDataFlight(Flight* auxFlight)
{
	int retorno = -1;
	Flight aux;

	if(auxFlight != NULL)
	{
		if(utn_getFlyCode(aux.flyCode, "\nIngrese codigo de vuelo (AAA-000000): ", "Codigo invalido.\n", CANT_REINTENTOS, LEN_FLY_CODE) == 0)
		{
		    aux.statusFlight = ACTIVO;
		    aux.isEmpty = 0;
			*auxFlight = aux;
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
 * \brief Busca un espacio libre en el array de vuelos.
 * \param Flight* list, Es el puntero al array de vuelos.
 * \param int len, es el limite de array.
 * \param int* index, Es el puntero al index del espacio libre.
 * \return (-1) Error / (0) Ok
 */
int searchFreeIndexFlight(Flight* list, int len, int* pIndex)
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
 * \brief Modifica el estado de un vuelo si el indice no está vacio.
 * \param Flight* list, Es el puntero al array de pasajeros.
 * \param int len, es el limite de array.
 * \param int index, es el indice donde se modificara el estado.
 * \return (-1) Error / (0) Ok
 */
int modifyStatusFlight(Flight* list, int len, int index)
{
	int retorno = -1;
	Flight aux;

	if(list != NULL && len > 0 && index >= 0 && list[index].isEmpty == 0)
	{
	    aux = list[index];
		if(utn_getNumberInt(&aux.statusFlight, "\n1) Activo\n2) Cancelado\n3) Demorado\nIngrese el estado del vuelo:", "Estado de vuelo invalido.\n", ACTIVO, DEMORADO, CANT_REINTENTOS) == 0)
		{
			aux.isEmpty = 0;
			list[index] = aux;
			retorno = 0;
		}
	}
	return retorno;
}


/**
 * \brief Imprime los vuelos cargados.
 * \param Flight* list, Es el puntero al array de vuelos.
 * \param int len, es el limite de array
 * \return (-1) Error / (0) Ok
 */
int printFlights(Flight* list, int len)
{
	int retorno = -1;
	int i;
	char auxStatus[LEN_STRING];

	if(list != NULL && len > 0)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0 && Flight_getTextEstadoVueldo(list[i].statusFlight, auxStatus) == 0)
			{
				printf( "Codigo de vuelo: %s - Estado de vuelo: %d)%s.\n"
						,list[i].flyCode , list[i].statusFlight, auxStatus);
			}
		}
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Busca el empleado por id y retorna su indice.
 * \param Flight* list, Es el puntero al array de vuelos
 * \param int len, es el limite de array.
 * \param char* flyCode, codigo de vuelo que será buscado.
 * \return Retorna el indice
 */
int findFlightByFlyCode(Flight* list, int len, char* flyCode)
{
    int retorno = -1;

    if(list != NULL && len > 0 && flyCode != NULL)
    {
        int i = 0;
        while(i < len)
        {
            if(strncmp(list[i].flyCode, flyCode, LEN_FLY_CODE) == 0)
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
 * \brief Busca el empleado por id y retorna su indice.
 * \param Flight* list, Es el puntero al array de vuelos
 * \param int len, es el limite de array.
 * \param char* flyCode, codigo de vuelo que será buscado.
 * \return Retorna el indice
 */
int findStatusFlightByFlyCode(Flight* list, int len, char* flyCode)
{
    int retorno = -1;

    if(list != NULL && len > 0 && flyCode != NULL)
    {
        int i = 0;
        while(i < len)
        {
            if(strncmp(list[i].flyCode, flyCode, LEN_FLY_CODE) == 0)
            {
                retorno = list[i].statusFlight;
                break;
            }
            i++;
        }
    }
    return retorno;
}
/**
 * \brief Realiza baja logica de un vuelo si el indice no está vacio.
 * \param Flight* list, Es el puntero al array de vuelos.
 * \param int len, es el limite de array.
 * \param char* flyCode, codigo de vuelo del vuelo que será eliminado.
 * \return (-1) Error / (0) Ok
 */
int removeFlight(Flight* list, int len, char* flyCode)
{
    int retorno = -1;
    int index;
    if(list != NULL && len > 0 && flyCode != NULL)
    {
        index = findFlightByFlyCode(list, len, flyCode);
        if(list[index].isEmpty == 0 && index > 0)
        {
            list[index].isEmpty = 1;
            retorno = 0;
        }
    }
    return retorno;
}
/**
 * \brief Realiza el alta de un vuelo solo si el indice corresponde a un espacio vacio (isEmpty == 1)
 * \param Flight* list, Es el puntero al array de vuelos.
 * \param int len, es el limite de array.
 * \param int statusFlight, indica el estado del vuelo.
 * \param char flycode[], indica el codigo del vuelo.
 * \return (-1) Error / (0) Ok
 */
int addFlight(Flight* list, int len, int statusFlight, char flyCode[])
{
    int retorno = -1;
    int index;
    if(list != NULL && len > 0 && statusFlight >= ACTIVO && statusFlight <= DEMORADO && flyCode != NULL)
    {
        if(searchFreeIndexFlight(list, len, &index) == 0 && index < len)
        {
            list[index].statusFlight = statusFlight;
            strncpy(list[index].flyCode, flyCode, LEN_FLY_CODE);
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
 * \brief Controla si el array tiene vuelos cargados.
 * \param Flight* list, Es el puntero al array de vuelos.
 * \param int len, es el limite de array.
 * \return (1) true, esta vacio / (0) false, tiene pasajeros cargados
 */
int isEmptyArrayFlights(Flight* list, int len)
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



int Flight_getTextEstadoVueldo(int estadoVuelo, char* estadoVueloStr)
{
	int retorno = -1;

	if((estadoVuelo >= ACTIVO && estadoVuelo <= DEMORADO) && estadoVueloStr != NULL)
	{
		switch(estadoVuelo)
		{
			case ACTIVO:
				strncpy(estadoVueloStr, "Activo", LEN_STRING);
				retorno = 0;
				break;
			case CANCELADO:
				strncpy(estadoVueloStr, "Cancelado", LEN_STRING);
				retorno = 0;
				break;
			case DEMORADO:
				strncpy(estadoVueloStr, "Demorado", LEN_STRING);
				retorno = 0;
				break;
		}
	}
	return retorno;
}


/**
 * \brief Realiza el alta de un vuelo solo si el indice corresponde a un espacio vacio (isEmpty == 1)
 * \param Flight* list, Es el puntero al array de vuelos.
 * \param int len, es el limite de array.
 * \param int statusFlight, indica el estado del vuelo.
 * \param char flycode[], indica el codigo del vuelo, "AAA-000000".
 * \return (-1) Error / (0) Ok
 */
int Flight_altaForzada(Flight* list, int len, int statusFlight, char* flyCode)
{
    int retorno = -1;
    int index;
    char auxStr[LEN_FLY_CODE];
    strncpy(auxStr, flyCode, LEN_FLY_CODE);
    //"BBA-123456"

    if(list != NULL && len > 0 && statusFlight >= ACTIVO && statusFlight <= DEMORADO &&
    	flyCode != NULL && isFlyCode(auxStr, LEN_FLY_CODE) == 1)
    {
        if(searchFreeIndexFlight(list, len, &index) == 0 && index < len)
        {
            list[index].statusFlight = statusFlight;
            strncpy(list[index].flyCode, auxStr, LEN_FLY_CODE);
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

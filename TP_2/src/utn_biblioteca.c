/*
 * utn_biblioteca.c
 *
 *  Created on: 14 may. 2022
 *      Author: Blanco Juli�n Agust�n
 */


#include "utn_biblioteca.h"

static int myGets(char* cadena, int longitud);
static int getInt(int* cadena);
static int isInt(char* cadena, int limite);
static int getFloat(float* cadena);
static int isFloat(char* cadena, int limite);
static int getText(char* pResultado, int len);
static int isName(char* cadena, int len);
static int isFlyCode(char* cadena, int len);


/**
 * \brief	Lee el stdin hasta que encuentra un '\0' o hasta que haya copiado en cadena
 * 			un maximo de 'len - 1' caracteres.
 * \param	char* cadena, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \param	char longitud, Define el tama�o de la cadena.
 * \return	Retorna 0 (exito) si se obtiene una cadena y -1 (error) si no se obtiene.
 */
static int myGets(char* cadena, int longitud)
{
	int retorno = -1;
	char bufferString[LONG_BUFFER];

	if(cadena != NULL && longitud > 0)
	{

		fflush(stdin);
		if(fgets(bufferString, sizeof(bufferString), stdin) != NULL)
		{

			if(bufferString[strnlen(bufferString,sizeof(bufferString)) - 1] == '\n')
			{
				bufferString[strnlen(bufferString,sizeof(bufferString)) - 1] = '\0';
			}
			if(strnlen(bufferString,sizeof(bufferString)) <= longitud)
			{

				fflush(stdin);
				strncpy(cadena, bufferString, longitud);
				retorno = 0;
			}
		}
	}
	return retorno;
}

/*
 * \ brief - Verifica una cadena recibida como parametro para determinar
 * 	         si es un entero valido.
 * \ param - char* cadena, cadena a analizar.
 * \ param - int limite, indica la cantidad de numeros maximas de la cadena.
 * \ return - (1) Indica que es un entero valido / (0) Indica que no es un entero valido.
 */
static int isInt(char* cadena, int limite)
{
	int retorno = 1;
	int i = 0;
	if(cadena != NULL)
	{
		while(cadena[i]!= '\0' && i < limite)
		{
			if(i == 0 && (cadena[i] == '-' || cadena[i] == '+'))
			{
				i++;
			}
			if(cadena[i] < '0' || cadena[i] > '9')
			{
				retorno = 0;
				break;
			}
			i++;
		}
	}
	return retorno;
}

/*
 * \ brief - Obtiene un numero entero.
 * \ param - int* pResultado, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
static int getInt(int* pResultado){
	int retorno = -1;
	char buffer[LONG_BUFFER];
	if(myGets(buffer, sizeof(buffer)) == 0 && isInt(buffer, sizeof(buffer)) == 1){
		*pResultado = atoi(buffer);
		retorno = 0;
	}
	return retorno;
}

/*
 * \ brief - Solicita un numero entero al usuario y, luego de verificarlo, devuelve el resultado.
 * \ param - char* mensaje, Mensaje a ser mostrado al usuario para solicitarle el dato.
 * \ param - char* mensajeError, Mensaje a ser mostrado al usuario para indicarle que el valor ingresado no es correcto.
 * \ param - int* pResultado, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ param - int reintentos, Cantidad de oportunidades para ingresar el dato.
 * \ param - int minimo, valor minimo admitido.
 * \ param - int maximo, valor maximo admitido.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
int utn_getNumberInt(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	int retorno = -1;
	int bufferInt;

	do
	{
		printf("%s", mensaje);
		if(getInt(&bufferInt) == 0 && bufferInt >= minimo && bufferInt <= maximo)
		{
			retorno = 0;
			*pResultado = bufferInt;
			break;
		}
		printf("%s", mensajeError);
		reintentos--;
	}while(reintentos >= 0);

	return retorno;
}

/*
 * \ brief - Verifica una cadena recibida como parametro para determinar
 * 	         si es un flotante valido.
 * \ param - char* cadena, cadena a analizar.
 * \ param - int limite, indica la cantidad de numeros maximas de la cadena.
 * \ return - (1) Indica que es un flotante valido / (0) Indica que no es un flotante valido.
 */
static int isFloat(char* cadena, int limite)
{
	int retorno = 1;
	int i = 0;
	int flagDot = 0;
	if(cadena != NULL)
	{
		while(cadena[i]!= '\0' && i < limite)
		{
			if(i == 0 && (cadena[i] == '-' || cadena[i] == '+'))
			{
				i++;
			}
			if(flagDot == 0 && cadena[i] == '.')
			{
				flagDot++;
				i++;
			}
			if(cadena[i] < '0' || cadena[i] > '9')
			{
				retorno = 0;
				break;
			}
			i++;
		}
	}
	return retorno;
}

/*
 * \ brief - Obtiene un Flotante.
 * \ param - char* pResultado, puntero a direcci�n de memoria.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
static int getFloat(float* pResultado){
	int retorno = -1;
	char buffer[LONG_BUFFER];
	if(myGets(buffer, sizeof(buffer)) == 0 && isFloat(buffer, sizeof(buffer)) == 1){
		*pResultado = atof(buffer);
		retorno = 0;
	}
	return retorno;
}

/*
 * \ brief - Solicita un flotante al usuario y, luego de verificarlo, devuelve el resultado.
 * \ param - char* mensaje, Mensaje a ser mostrado al usuario para solicitarle el dato.
 * \ param - char* mensajeError, Mensaje a ser mostrado al usuario para indicarle que el valor ingresado no es correcto.
 * \ param - int* pResultado, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ param - int reintentos, Cantidad de oportunidades para ingresar el dato.
 * \ param - int minimo, valor minimo admitido.
 * \ param - int maximo, valor maximo admitido.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
int utn_getNumberFloat(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos)
{
	int retorno = -1;
	float bufferFloat;

	do
	{
		printf("%s", mensaje);
		if(getFloat(&bufferFloat) == 0 && bufferFloat >= minimo && bufferFloat <= maximo)
		{
			retorno = 0;
			*pResultado = bufferFloat;
			break;
		}
		printf("%s", mensajeError);
		reintentos--;
	}while(reintentos >= 0);

	return retorno;
}

/*
 * \ brief - Obtiene un texto.
 * \ param - int* pResultado, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
static int getText(char* pResultado, int len)
{
	int retorno = -1;
	char bufferString[LONG_BUFFER];
	if(pResultado != NULL && len > 0)
	{
		fflush(stdin);
		if(	myGets(bufferString,sizeof(bufferString)) == 0)
		{
			strncpy(pResultado,bufferString,len);
			retorno = 0;
		}
	}
	return retorno;
}

/*
 * \ brief - Solicita un texto al usuario.
 * \ param - char* mensaje, Mensaje a ser mostrado al usuario para solicitarle el dato.
 * \ param - char* mensajeError, Mensaje a ser mostrado al usuario para indicarle que el valor ingresado no es correcto.
 * \ param - char* pResultado, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ param - int reintentos, Cantidad de oportunidades para ingresar el dato.
 * \ param - int len, indica la cantidad de letras maxima del texto.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
int utn_getText(char *pResultado, char *mensaje, char *mensajeError, int reintentos, int len)
{
	int retorno = -1;
	char bufferString[LONG_BUFFER];

	if( 	pResultado != NULL &&
			mensaje != NULL &&
			mensajeError != NULL &&
			reintentos >= 0 &&
			len > 1)
	{
		do
		{
			printf("%s",mensaje);
			fflush(stdin);
			if(	getText(bufferString, LONG_BUFFER) == 0 &&
				strnlen(bufferString, sizeof(bufferString)-1) <= len)
			{
				retorno = 0;
				strncpy(pResultado, bufferString, len);
				break;
			}
			else
			{
				printf("%s", mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

/*
 * \ brief - Verifica una cadena recibida como parametro para determinar
 * 	         si es un nombre valido.
 * \ param - char* cadena, cadena a analizar.
 * \ param - int limite, indica la cantidad de numeros maximas de la cadena.
 * \ return - (1) Indica que es un nombre valido / (0) Indica que no es un nombre valido.
 */
static int isName(char* cadena, int len)
{
    int retorno = 1;
    int i = 0;


    while(cadena[i] != '\0' && i < len)
    {
        if((cadena[i] < 'A' || cadena[i] > 'Z' ) &&
			(cadena[i] < 'a' || cadena[i] > 'z' ))
        {
            retorno = 0;
            break;
        }
        i++;
    }
    return retorno;
}

/*
 * \ brief - Solicita un nombre al usuario.
 * \ param - char* mensaje, Mensaje a ser mostrado al usuario para solicitarle el dato.
 * \ param - char* mensajeError, Mensaje a ser mostrado al usuario para indicarle que el valor ingresado no es correcto.
 * \ param - char* pResultado, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ param - int reintentos, Cantidad de oportunidades para ingresar el dato.
 * \ param - int len, indica la cantidad de letras maxima del texto.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
int utn_getName(char* pResultado, char* mensaje, char* mensajeError, int reintentos, int len)
{
	int retorno = -1;
	char bufferString[LONG_BUFFER];

	if( 	pResultado != NULL &&
			mensaje != NULL &&
			mensajeError != NULL &&
			reintentos >= 0 &&
			len > 1)
	{
		do
		{
			printf("%s",mensaje);
			fflush(stdin);
			if(	getText(bufferString, LONG_BUFFER) == 0 &&
			    isName(bufferString, sizeof(bufferString)) &&
				strnlen(bufferString, sizeof(bufferString)-1) <= len)
			{
				retorno = 0;
				strncpy(pResultado, bufferString, len);
				break;
			}
			else
			{
				printf("%s", mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

/*
 * \ brief - Verifica una cadena recibida como parametro para determinar
 * 	         si es un codigo numerico valido.
 * \ param - char* cadena, cadena a analizar.
 * \ param - int limite, indica la cantidad de numeros maximas de la cadena.
 * \ return - (1) Indica que es un nombre valido / (0) Indica que no es un nombre valido.
 */
static int isFlyCode(char* cadena, int len)
{
    int retorno = 1;
    int i = 0;


    while(cadena[i] != '\0' && i < len)
    {
        cadena[i] = toupper(cadena[i]);
		if((i <= 2 && (cadena[i] < 'A' || cadena[i] > 'Z')) ||
		    (i == 3 && cadena[i] != '-') ||
    	    (i >= 4 && (cadena[i] < '0' || cadena[i] > '9')))
        {
            retorno = 0;
            break;
        }
        i++;
    }
    return retorno;
}
/*
 * \ brief - Solicita un nombre al usuario.
 * \ param - char* mensaje, Mensaje a ser mostrado al usuario para solicitarle el dato.
 * \ param - char* mensajeError, Mensaje a ser mostrado al usuario para indicarle que el valor ingresado no es correcto.
 * \ param - char* pResultado, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ param - int reintentos, Cantidad de oportunidades para ingresar el dato.
 * \ param - int len, indica la cantidad de letras maxima del texto.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */

int utn_getFlyCode(char* pResultado, char* mensaje, char* mensajeError, int reintentos, int len)
{
	int retorno = -1;
	char bufferString[LONG_BUFFER];

	if( 	pResultado != NULL &&
			mensaje != NULL &&
			mensajeError != NULL &&
			reintentos >= 0 &&
			len > 1)
	{
		do
		{
			printf("%s",mensaje);
			fflush(stdin);
			if(	getText(bufferString, LONG_BUFFER) == 0 &&
			    isFlyCode(bufferString, sizeof(bufferString)) &&
				strnlen(bufferString, sizeof(bufferString)-1) <= len)
			{
				retorno = 0;
				strncpy(pResultado, bufferString, len);
				break;
			}
			else
			{
				printf("%s", mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

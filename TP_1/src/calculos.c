/*
 * calculos.c
 *
 *  Created on: 16 abr. 2022
 *      Author: Blanco Julián Agustín
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BTC_PRICE 4606954.55


static int dividirFloat(float* pResultado, float a, float b);

/// @brief Divive a por b
///
/// @param a dividendo
/// @param b divisor
/// @return (-1) en caso de error / (0) en caso de funcionar.
static int dividirFloat(float* pResultado, float a, float b)
{
    int retorno = 0;
    if(b != 0){
			*pResultado = a / b;
		}else{
			printf("\nERROR. No se puede dividir por 0");
			retorno = -1;
		}
	return retorno;
}

/*
 * \ brief - Recibe kilometros, precio y flag de la aerolínea y devuelve los costos.
 * \ param - int flagAerolinea, bandera para saber si se ingreso el precio de la aerolínea.
 * \ param - float* priceDebit, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ param - float* priceCredit, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ param - float* priceBtc, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ param - float* priceKm, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ param - float priceAerolinea, precio de la aerolínea.
 * \ param - float kmIngresados, cantidad de kilometros ingresada.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
int calculos_calcularCostos(int flagAerolinea, float* priceDebit, float* priceCredit, float* priceBtc, float* priceKm, float priceAerolinea, float kmIngresados)
{
	int retorno = -1;
	if(flagAerolinea == 1 && priceDebit != NULL && priceCredit != NULL && priceBtc != NULL && priceKm != NULL && priceAerolinea >= 0 && kmIngresados >= 0)
	{
	    *priceDebit = priceAerolinea * 0.90;
	    *priceCredit = priceAerolinea * 1.25;
	    dividirFloat(priceBtc, priceAerolinea, BTC_PRICE);
	    dividirFloat(priceKm, priceAerolinea, kmIngresados);
	    retorno = 0;
	}

	return retorno;
}
/*
 * \ brief - Recibe kilometros, precio y costos de la aerolínea y los muestra al usuario por consola.
 * \ param - char* nombreAerolinea, Nombre de la aerolinea a ser mostrado al usuario.
 * \ param - int flagAerolinea, Bandera para saber si se calcularon los costos de la aerolínea.
 * \ param - float priceDebit, Valor a ser mostrado al usuario.
 * \ param - float priceCredit, Valor a ser mostrado al usuario.
 * \ param - float priceBtc, Valor a ser mostrado al usuario.
 * \ param - float priceKm, Valor a ser mostrado al usuario.
 * \ param - float priceAerolinea, Valor a ser mostrado al usuario.
 * \ param - float kmIngresados, Valor a ser mostrado al usuario.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
int calculos_mostrarCostos(char* nombreAerolinea, int flagAerolinea, float priceDebit, float priceCredit, float priceBtc, float priceKm, float priceAerolinea, float kmIngresados)
{
    int retorno = -1;
	if(flagAerolinea == 1 && nombreAerolinea != NULL  && priceAerolinea >= 0 && kmIngresados >= 0)
	{
	    printf("\nKMs Ingresados: %.2f km"
	            "\nPrecio %s: $ %.2f"
    			"\na) Precio con tarjeta de debito: $ %.2f"
    			"\nb) Precio con tarjeta de credito: $ %.2f"
    			"\nc) Precio pagando con bitcoin: %f BTC"
    			"\nd) Mostrar precio unitario: $ %.2f",kmIngresados, nombreAerolinea, priceAerolinea, priceDebit, priceCredit, priceBtc, priceKm);

	    retorno = 0;
	}

	return retorno;

}

/*
 * \ brief - Calcula la diferencia de precio en las aerolíneas (Latam - Aerolíneas).
 * \ param - float* diferenciaPrecio, Puntero al espacio de memoria donde se dejara el valor obtenido.
 * \ param - int flagLatam, bandera para saber si se ingreso el precio de Latam.
 * \ param - int flagAerolinea, bandera para saber si se ingreso el precio de Aerolíneas Argentina.
 * \ param - float priceAerolinea, precio de Aerolíneas Argentinas.
 * \ param - float priceLatam, precio de Latam.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
int calculos_calcularDiferencia(float* diferenciaPrecio, int flagLatam, int flagAerolinea, float priceLatam, float priceAerolinea)
{
    int retorno = -1;
    if(diferenciaPrecio != NULL && priceAerolinea >= 0 && priceLatam >= 0)
    {
        if(flagLatam == 0 || flagAerolinea == 0)
        {
            printf("\nNo se ingreso el precio de las dos aerolíneas");
        }else
        {
            *diferenciaPrecio = priceLatam - priceAerolinea;

        }
        retorno = 0;
    }
    return retorno;
}


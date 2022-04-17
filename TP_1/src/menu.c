/*
 * menu.c
 *
 *  Created on: 16 abr. 2022
 *      Author: Blanco Julián Agustín
 */
#include "menu.h"

void showMenu()
{
    int option;
    float kmIngresados = -1;
    float priceAerolinea;
    float priceLatam;
    int flagAerolinea = 0;
    int flagLatam = 0;
    int flagCalculosAerolinea = 0;
    int flagCalculosLatam = 0;
    float diferenciaPrecio;

    //Aerolinea Argentinas
    float priceDebitAerolinea;
    float priceCreditAerolinea;
    float priceBtcAerolinea;
    float priceKmAerolinea;
    //Latam
    float priceDebitLatam;
    float priceCreditLatam;
    float priceBtcLatam;
    float priceKmLatam;


    do
    {
        if(utn_getNumberInt(&option, "\n1. Ingresar Kilómetros: ( km=x)\n"
        "2. Ingresar Precio de Vuelos\n"
        "3. Calcular todos los costos\n"
        "4. Informar Resultados\n"
        "5. Carga forzada de datos\n"
        "6. Salir\n",
        "Opcion invalida\n", 1, 6, 2)==0)
        {

            switch(option)
            {
                case 1:
                    utn_getNumberFloat(&kmIngresados, "\nIngrese la cantidad de kilometros a recorrer(maximo 250000.00 km)", "\nNumero invalido", 1, 250000.00, CANT_REINTENTOS);
                    break;
                case 2:
                    showMenuAerolineas(&priceAerolinea, &priceLatam, &flagAerolinea, &flagLatam, &flagCalculosAerolinea, &flagCalculosLatam);
                    break;
                case 3:
                    if(kmIngresados >= 0)
                    {
                        printf("\na) Tarjeta de débito (descuento 10%%)\n"
                        "b) Tarjeta de crédito (interés 25%%)\n"
                        "c) Bitcoin (1 BTC -> 4606954.55 Pesos Argentinos)\n"
                        "d) Mostrar precio por km (precio unitario)\n"
                        "e) Mostrar diferencia de precio ingresada (Latam - Aerolíneas)\n");
                        if(flagAerolinea==1)
                        {
                            calculos_calcularCostos(flagAerolinea, &priceDebitAerolinea, &priceCreditAerolinea, &priceBtcAerolinea, &priceKmAerolinea, priceAerolinea, kmIngresados);
                            flagCalculosAerolinea = 1;
                        }else
                        {
                            printf("\nNo ingreso datos para Aerolíneas Argentinas, no se realizaron calculos");
                        }

                        if(flagLatam==1)
                        {
                            calculos_calcularCostos(flagLatam, &priceDebitLatam, &priceCreditLatam, &priceBtcLatam, &priceKmLatam, priceLatam, kmIngresados);
                            flagCalculosLatam = 1;
                        }else
                        {
                            printf("\nNo ingreso datos para Latam, no se realizaron calculos");
                        }
                        calculos_calcularDiferencia(&diferenciaPrecio, flagLatam, flagAerolinea, priceLatam, priceAerolinea);


                    }else
                    {
                        printf("\nNo se ingreso la cantidad de kilometros");
                    }

                    break;
                case 4:
                    if(kmIngresados >= 0)
                    {
                        if(flagCalculosAerolinea == 1)
                        {
                            calculos_mostrarCostos("Aerolíneas Argentinas", flagCalculosAerolinea, priceDebitAerolinea, priceCreditAerolinea, priceBtcAerolinea, priceKmAerolinea, priceAerolinea, kmIngresados);
                        }else
                        {
                            printf("\nNo se realizaron calculos para Aerolíneas Argentinas");
                        }

                        if(flagCalculosLatam == 1)
                        {
                            calculos_mostrarCostos("Latam", flagCalculosLatam, priceDebitLatam, priceCreditLatam, priceBtcLatam, priceKmLatam, priceLatam, kmIngresados);
                        }else
                        {
                            printf("\nNo se realizaron calculos datos para Latam");
                        }

                        if(flagCalculosLatam == 0 || flagCalculosAerolinea == 0)
                        {
                            printf("\nNo se ingreso el precio de las dos aerolíneas para calcular la diferencia");
                        }else
                        {
                            printf("\nLa diferencia de precio es: $ %.2f",diferenciaPrecio);
                        }

                    }else
                    {
                        printf("\nNo ingreso datos para Latam, no se realizaron calculos");
                    }
                    break;
                case 5:

                    kmIngresados = ALTA_KM;
                    priceAerolinea = ALTA_PRECIO;
                    priceLatam = ALTA_PRECIO;
                    flagAerolinea = 1;
                    flagLatam = 1;

                    calculos_calcularCostos(flagAerolinea, &priceDebitAerolinea, &priceCreditAerolinea, &priceBtcAerolinea, &priceKmAerolinea, priceAerolinea, kmIngresados);
                    calculos_calcularCostos(flagLatam, &priceDebitLatam, &priceCreditLatam, &priceBtcLatam, &priceKmLatam, priceLatam, kmIngresados);

                    calculos_calcularDiferencia(&diferenciaPrecio, flagLatam, flagAerolinea, priceAerolinea, priceLatam);

                    flagCalculosAerolinea = 1;
					flagCalculosLatam = 1;

                    calculos_mostrarCostos("Aerolíneas Argentinas", flagAerolinea, priceDebitAerolinea, priceCreditAerolinea, priceBtcAerolinea, priceKmAerolinea, priceAerolinea, kmIngresados);
                    calculos_mostrarCostos("Latam", flagLatam, priceDebitLatam, priceCreditLatam, priceBtcLatam, priceKmLatam, priceLatam, kmIngresados);
                    printf("\nLa diferencia de precio es: $ %.2f",diferenciaPrecio);
                    break;
                case 6:
                    printf("\nEligio salir del programa");
                    break;
            }
        }else
        {
            printf("\nSe acabaron los reintentos");
            break;
        }
    }while(option != 6);
    printf("\nAdios");
}


void showMenuAerolineas(float* priceAerolinea, float* priceLatam, int* flagAerolinea, int* flagLatam, int* flagCalculosAerolinea, int* flagCalculosLatam)
{
    //int retorno;
    int option;

    do
    {
        if(utn_getNumberInt(&option, "\nIngrese aerolinea:\n"
        "1. Aerolíneas Argentinas\n"
        "2. Latam\n"
        "3. Volver al menu anterior\n",
        "Opcion invalida\n", 1, 3, CANT_REINTENTOS)==0){


            switch(option)
            {
                case 1:
                    utn_getNumberFloat(priceAerolinea, "\nIngrese precio (max 300000.00): ", "\nMonto invalido", 1, 300000, CANT_REINTENTOS);
                    *flagAerolinea = 1;
                    *flagCalculosAerolinea = 0;
                    break;
                case 2:
                    utn_getNumberFloat(priceLatam, "\nIngrese precio (max 300000.00): ", "\nMonto invalido", 1, 300000, CANT_REINTENTOS);
                    *flagLatam = 1;
                    *flagCalculosLatam = 0;
                    break;
                case 3:
                    printf("\nEligio volver al menu anterior");
                    break;
            }
        }else
        {
            printf("\nSe acabaron los reintentos");
            break;
        }
    }while(option != 3);

}


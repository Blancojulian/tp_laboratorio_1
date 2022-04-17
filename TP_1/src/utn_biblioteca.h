/*
 * utn_biblioteca.h
 *
 *  Created on: 16 abr. 2022
 *      Author: Blanco Julián Agustín
 */

#ifndef UTN_BIBLIOTECA_H_
#define UTN_BIBLIOTECA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LONG_BUFFER 4096

int utn_getNumberInt(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int utn_getNumberFloat(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos);
int utn_getText(char *pResultado, char *mensaje, char *mensajeError, int reintentos, int len);
int isValidCaracter(char caracter, char minimo, char maximo);

#endif /* UTN_BIBLIOTECA_H_ */

/*
 * menu.h
 *
 *  Created on: 16 abr. 2022
 *      Author: Blanco Julián Agustín
 */

#ifndef MENU_H_
#define MENU_H_

#include <stdio.h>
#include <stdlib.h>
#include "utn_biblioteca.h"
#include "calculos.h"

#define CANT_REINTENTOS 2
#define ALTA_PRECIO 150000
#define ALTA_KM 10000

void showMenu();
void showMenuAerolineas(float* priceAerolinea, float* priceLatam, int* flagAerolinea, int* flagLatam, int* flagCalculosAerolinea, int* flagCalculosLatam);


#endif /* MENU_H_ */

/*
 * menu.h
 *
 *  Created on: 14 may. 2022
 *      Author: Blanco Julián Agustín
 */

#ifndef MENU_H_
#define MENU_H_

#include <stdio.h>
#include <stdlib.h>
#include "arrayPassenger.h"

#define OPTION_MENU 5
#define OPTION_REPORT 3
#define OPTION_MODIFY 4

void showMenu(int* pOptionMenu, int* pOptionReport, int* pOptionModify, Passenger* list, int len);

#endif /* MENU_H_ */

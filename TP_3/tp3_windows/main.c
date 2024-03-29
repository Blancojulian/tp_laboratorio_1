#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Passenger.h"
#include "utn_biblioteca.h"
#include "parser.h"
#include "menu.h"

#define CANT_REINTENTOS 2

/****************************************************
    Menu:
     1. Cargar los datos de los pasajeros desde el archivo data.csv (modo texto).
     2. Cargar los datos de los pasajeros desde el archivo data.csv (modo binario).
     3. Alta de pasajero
     4. Modificar datos de pasajero
     5. Baja de pasajero
     6. Listar pasajeros
     7. Ordenar pasajeros
     8. Guardar los datos de los pasajeros en el archivo data.csv (modo texto).
     9. Guardar los datos de los pasajeros en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/



int main() {
	setbuf(stdout, NULL);

	int option = 0;
	LinkedList* listPassenger = ll_newLinkedList();

	if(listPassenger != NULL)
	{
		do
		{
			option = 0;
			utn_showMenu(&option, listPassenger);
			switch(option)
			{
				case 1:
					if(getConfirm("\nSe borrara los datos actuales y se cargaran los pasajeros desde el archivo."
						"\n�Desea realizar la carga?", "\nError", CANT_REINTENTOS) == 1 &&
						controller_clearList(listPassenger) == 0 &&
						controller_loadFromText("data.csv", listPassenger) == 0)
					{
						printf("Los datos se cargaron correctamente.\n");
					}
					break;
				case 2:
					if(getConfirm("\nSe borrara los datos actuales y se cargaran los pasajeros desde el archivo."
						"\n�Desea realizar la carga?", "\nError", CANT_REINTENTOS) == 1 &&
						controller_clearList(listPassenger) == 0 &&
						controller_loadFromBinary("data.bin",listPassenger) == 0)
					{
						printf("Los datos se cargaron correctamente.\n");
					}
					break;
				case 3:
					if(controller_addPassenger(listPassenger) == 0)
					{
						printf("El pasajero se cargo correctamente.\n");
					}
					break;
				case 4:
					if(controller_editPassenger(listPassenger) == 0)
					{
						printf("El pasajero se modifico correctamente.\n");
					}
					break;
				case 5:
					if(controller_removePassenger(listPassenger) == 0)
					{
						printf("El pasajero se elimino correctamente.\n");
					}
					break;
				case 6:
					if(controller_ListPassenger(listPassenger) == 0)
					{
						printf("La lista se mostro correctamente.\n");
					}
					else
					{
						printf("Error al mostrar la lista.\n");
					}
					break;
				case 7:
					if(controller_sortPassenger(listPassenger) == 0)
					{
						printf("La lista se ordeno correctamente.\n");
					}
					break;
				case 8:
					if(controller_saveAsText("data.csv", listPassenger) == 0)
					{
						printf("Los datos se guardaron correctamente en el archivo de texto.\n");
					}
					break;
				case 9:
					if(controller_saveAsBinary("data.bin", listPassenger) == 0)
					{
						printf("Los datos se guardaron correctamente en el archivo binario.\n");
					}
					break;
				case 10:
					printf("Adios.\n");
					break;
			}
		}while(option != OPTIONS);

	}
    return 0;
}


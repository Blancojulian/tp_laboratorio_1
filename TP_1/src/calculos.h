/*
 * calculos.h
 *
 *  Created on: 16 abr. 2022
 *      Author: Blanco Julián Agustín
 */

#ifndef CALCULOS_H_
#define CALCULOS_H_

int calculos_calcularCostos(int flagAerolinea, float* priceDebit, float* priceCredit, float* priceBtc, float* priceKm, float priceAerolinea, float kmIngresados);
int calculos_mostrarCostos(char* nombreAerolinea, int flagAerolinea, float priceDebit, float priceCredit, float priceBtc, float priceKm, float priceAerolinea, float kmIngresados);
int calculos_calcularDiferencia(float* diferenciaPrecio, int flagLatam, int flagAerolinea, float priceLatam, float priceAerolinea);

#endif /* CALCULOS_H_ */

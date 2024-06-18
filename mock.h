#ifndef MOCK_H_INCLUDED
#define MOCK_H_INCLUDED
#include "movimientos.h"
#include "cuenta.h"

void getDayMonthYeard(stMovimientos* M);
void idCuenta(stMovimientos* M, char nombreArchivoCu[]);
void eliminado(stMovimientos* M);
void importeydetalle(stMovimientos* M);
void mockArchivo (char nombreArchivoMov[], char nombreArchivoCu[], int cantidad);


#endif // MOCK_H_INCLUDED

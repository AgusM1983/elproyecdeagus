#ifndef GENERALES_H_INCLUDED
#define GENERALES_H_INCLUDED

int cuentaRegistrosGral(char nombreArchivo[], int tamanioUnSt);
int cuentaRegistrosGralFILE(FILE* archivo, int tamanioUnSt);

int esBisiesto(int anio); // Función para determinar si un año es bisiesto, (respuesta 1 no es, 0 es)

#endif // GENERALES_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "generales.h"
#include "cliente.h"
#include "cuenta.h"
#include "movimientos.h"

int cuentaRegistrosGral(char nombreArchivo[], int tamanioUnSt)
{
    int cantidad=0;
    FILE* archivo = fopen(nombreArchivo,"rb");
    if(archivo)
    {
    fseek(archivo,0,2);
    cantidad = ftell(archivo)/tamanioUnSt;
    fclose(archivo);
    }
    return cantidad;
}

int cuentaRegistrosGralFILE(FILE* archivo, int tamanioUnSt)
{
    int cantidad=0;
    if(archivo)
    {
    fseek(archivo,0,2);
    cantidad = ftell(archivo)/tamanioUnSt;
    }
    return cantidad;
}


int esBisiesto(int anio) // Función para determinar si un año es bisiesto, (respuesta 1 no es, 0 es)
{
    int respuesta=1;
    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))
// Un año es bisiesto si es divisible por 4 salvo que sea divisible por 100. Por eso &&
// Pero los años divisibles por 400 sí son bisiestos. Por eso ||
    {
        respuesta = 0; //devuelve 0 si es bisiesto
    }
    return respuesta; // devuelve 1 si no es bisiesto
}

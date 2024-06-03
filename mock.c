#include <stdio.h>
#include <stdlib.h>
#include "estructuras.h"
#include <string.h>


void getDayMonthYeard(stMovimientos* M)
{
    M->anio= -((rand()%100)-2024);

    M->mes = (rand()%12)+1;
    if(M->mes==4 || M->mes== 6|| M->mes==9 || M->mes==11)
    {
        M->dia= (rand()%30)+1;
    }
    if(M->mes==2)
    {
        if (esBisiesto(M->anio)==0)
        {
            M->dia = (rand()%29)+1;
        }
        M->dia= (rand()%28)+1;
    }
    else
    {
        M->dia = (rand()%31)+1;
    }
}

void idCuenta(stMovimientos* M, int validos2ArreglosCuentas)
{
    M->idCuenta = rand()%(validos2ArreglosCuentas+1);
}

void eliminado(stMovimientos* M)
{
    M->eliminado = (rand()%2);
}

void importeydetalle(stMovimientos* M)

{
    char detallePositivos[10][100] = {"Mensaje +1","Mensaje +2","Mensaje +3","Mensaje +4","Mensaje +5","Mensaje +6","Mensaje +7","Mensaje +8","Mensaje +9","Mensaje +10"};
    char detalleNegatitivos[10][100] = {"Mensaje -1","Mensaje -2","Mensaje -3","Mensaje -4","Mensaje -5","Mensaje -6","Mensaje -7","Mensaje -8","Mensaje -9","Mensaje -10"};
    int numAzar;
    numAzar = rand()%10;
//generar importe entre -300mil y 300mil
    if (numAzar%2==0) // si es par genera positivos
    {
    M->importe = (rand() % 300001);
    }
    else // si es impar genera negativos
    {
    M->importe = -1*(rand() % 300001);
    }

//generar detalle
    if(M->importe > 0)
    {
        strcpy(M->detalle, detallePositivos[numAzar]); /// hacer un generador al azar
    }
    if(M->importe==0)
    {
        strcpy(M->detalle, "Movimiento nulo");
    }
    if(M->importe<0)
    {
        strcpy(M->detalle, detalleNegatitivos[numAzar]); /// hacer un generador al azar
    }
}

int mockArreglo (stMovimientos M[],int numero, int validos2ArreglosCuentas, stCuentas C[])
{

    int i;
    for( i=0; i < numero ; i++ )
    {
    getDayMonthYeard(&M[i]);
    idCuenta(&M[i],validos2ArreglosCuentas); //validos2ArreglosCuentas es el numeros de cuentas que hay, asi genera hasta ese numero
    eliminado(&M[i]);
    importeydetalle(&M[i]);
    if(M[i].eliminado==0)
    {
    C[M[i].idCuenta].saldo = C[M[i].idCuenta].saldo + M[i].importe;
    }
    M[i].id=i;
    }
    return i;
}


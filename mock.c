
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "generales.h"
#include "cliente.h"
#include "cuenta.h"
#include "movimientos.h"

///clientes

void cargaMock80Cliente(char nombreCliente[])
{
    stCliente clie;

    FILE * archivo = fopen(nombreCliente,"ab");
    if(archivo)
    {
    for(int i=0; i <30;i++)
    {
    sprintf(clie.dni, "%d", i);
    clie.nroCliente=i;
    clie.id=i;

        fwrite(&clie,sizeof(stCliente),1,archivo);
    }
        fclose(archivo);
    }
}


/// cuentas
void cargaMock80Cuenta(char nombre[])
{
    stCuentas cuenta;
    FILE* archivo= fopen(nombre,"ab");
    if(archivo)
    {
        for(int i=0; i <30;i++)
        {
        cuenta.costoMensual=30;
        cuenta.eliminado = 0;
        cuenta.id=i;
        cuenta.idCliente=i;
        cuenta.nroCuenta=i;
        cuenta.saldo=0;
        cuenta.tipoDeCuenta=1;
        fwrite(&cuenta,sizeof(stCuentas),1,archivo);
        }

        fclose(archivo);
    }

}
///movimientos

void getDayMonthYeard(stMovimientos* M)
{
/// para limitar a la fecha actual

    time_t tiempo_actual = time(NULL);
    struct tm *tiempo_local = localtime(&tiempo_actual);
    /// printf("Año: %d\n", tiempo_local->tm_year + 1900); // tm_year cuenta desde 1900
    /// printf("Mes: %d\n", tiempo_local->tm_mon + 1); // tm_mon cuenta desde 0 (enero = 0)
    /// printf("Día: %d\n", tiempo_local->tm_mday);


    M->anio = ((tiempo_local->tm_year + 1900)-(rand()%100));

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

void idCuenta(stMovimientos* M, char nombreArchivoCu[])
{

    M->idCuenta = rand()%(cuentaRegistrosGral(nombreArchivoCu,sizeof(stCuentas)));
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

void mockArchivo (char nombreArchivoMov[], char nombreArchivoCu[], int cantidad)
{
    int i;
    for (i=0; i<cantidad; i++)
    {
        stMovimientos movimiento;
        getDayMonthYeard(&movimiento);
        idCuenta(&movimiento,nombreArchivoCu);
        importeydetalle(&movimiento);
        eliminado(&movimiento);
        if(movimiento.eliminado==1)
        {
            buscarCuentaModificarSaldo(nombreArchivoCu,movimiento.idCuenta,movimiento.importe);
        }
        movimiento.id=cuentaRegistrosGral(nombreArchivoMov,sizeof(stMovimientos));
        cargarUnMovimientoArchivo(nombreArchivoMov,nombreArchivoCu,movimiento);
    }
}





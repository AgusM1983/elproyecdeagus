
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "generales.h"
#include "cliente.h"
#include "cuenta.h"
#include "movimientos.h"

void muestraUnaCuenta(stCuentas cuenta)
{
    printf("\n IdCuenta: %d",cuenta.id);
    printf("| IdCliente: %d",cuenta.idCliente);
    printf("| costo mensual: %f", cuenta.costoMensual);
    printf("| eliminado: %d",cuenta.eliminado);
    printf("| Nro Cuenta: %d",cuenta.nroCuenta);
    printf("| Saldo: %f",cuenta.saldo);
    printf("| Tipo cuenta: %d",cuenta.tipoDeCuenta);
}

void mostrarArchivoCuenta(char nombreCuenta[])
{
    stCuentas cuenta;
    FILE* archivo = fopen(nombreCuenta,"rb");
    if (archivo)
    {
        while (fread(&cuenta,sizeof(stCuentas),1,archivo)>0)
        {
            muestraUnaCuenta(cuenta);
        }
        fclose(archivo);
    }
}

void mostrarCuentasxIdCliente(char archivoCuenta[], int idCliente)
{
    stCuentas cuenta;
    FILE * archivo = fopen(archivoCuenta,"rb");
    if(archivo)
    {
        while(fread(&cuenta,sizeof(stCuentas),1,archivo)>0)
        {
            if(cuenta.idCliente==idCliente)
            {
                muestraUnaCuenta(cuenta);
            }
        }
        fclose(archivo);
    }
}

int verificarNroDeCuenta(int numeroCuenta, char nombreCuenta[]) /// -1 si no y nroCuenta si esta
{
    int nroCuenta = -1;
    stCuentas cuenta;
    FILE* archivo = fopen(nombreCuenta,"rb");
    if (archivo)
    {
        while (nroCuenta == -1 && fread(&cuenta,sizeof(stCuentas),1,archivo)>0)
        {

            if(cuenta.nroCuenta==numeroCuenta)
            {
                nroCuenta=cuenta.nroCuenta;
            }
        }

        fclose(archivo);
    }
    return nroCuenta;
}

int traducirNroCuentaIdCuenta(int nroCuenta, char nombreCuenta[])
{
    int idCuenta = -1;
    stCuentas cuenta;
    FILE* archivo = fopen(nombreCuenta,"rb");
    if (archivo)
    {
        while (idCuenta == -1 && fread(&cuenta,sizeof(stCuentas),1,archivo)>0)
        {

            if(cuenta.nroCuenta==nroCuenta)
            {
                idCuenta=cuenta.id;
            }
        }

        fclose(archivo);
    }

    return idCuenta;

}

void buscarCuentaModificarSaldo(char nombreArchivoCu[],int idCuenta, float importe)
{


    stCuentas cuenta;
    FILE * archivo = fopen(nombreArchivoCu,"r+b");
    if( archivo)
    {
        fseek(archivo,(idCuenta)*sizeof(stCuentas),0);
        fread(&cuenta,sizeof(stCuentas),1,archivo);

        cuenta.saldo = cuenta.saldo+importe;

        fseek(archivo,(idCuenta)*sizeof(stCuentas),0);
        fwrite(&cuenta,sizeof(stCuentas),1,archivo);
        fclose(archivo);
    }

}


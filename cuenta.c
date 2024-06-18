#include "movimientos.h"
#include "cuenta.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>

stCuentas cargaManualUnaCuenta(char nombre[])
{
    int cuentanumero;
    stCuentas cuenta;
    printf("\n costo mensual: ");
    fflush(stdin);
    scanf("%f",&cuenta.costoMensual);
    printf("\n eliminado");
    fflush(stdin);
    scanf("%d",&cuenta.eliminado);
    cuenta.id=-1;
    printf("\n IdCliente: ");
    fflush(stdin);
    scanf("%d",&cuenta.idCliente);
    printf("\n Nro Cuenta: ");
    fflush(stdin);
    scanf("%d",&cuenta.nroCuenta);
    cuentanumero = *buscarCuentaxNumerodeCta(nombre , cuenta.nroCuenta);
    while(cuentanumero == cuenta.nroCuenta)
    {
        printf("\n Ya existe ese numero de cuenta ingrese una cuenta mayor a %d",2*cuentaregistroscuentas(nombre)+1);
        fflush(stdin);
        scanf("%d",&cuenta.nroCuenta);
        cuentanumero = *buscarCuentaxNumerodeCta(nombre , cuenta.nroCuenta);
    }
    printf("\n Saldo");
    fflush(stdin);
    scanf("%f",&cuenta.saldo);
    printf("\n Tipo cuenta");
    fflush(stdin);
    scanf("%d",&cuenta.tipoDeCuenta);

    printf("\n ----------------");
    muestraUnaCuenta(cuenta);
}

void cargaMockunaCuenta(char nombre[])
{
    stCuentas cuenta;
    FILE* archivo= fopen(nombre,"ab");
    if(archivo)
    {
        for (int i = 0; i < 80; i++)
        {
        cuenta.costoMensual=30;
        cuenta.eliminado = 1;
        cuenta.id=i;
        cuenta.idCliente=i*2;
        cuenta.nroCuenta=2*i+1;
        cuenta.saldo=0;
        cuenta.tipoDeCuenta=1;
        fwrite(&cuenta,sizeof(stCuentas),1,archivo);
        }

        fclose(archivo);
    }

}

void muestraUnaCuenta(stCuentas cuenta)
{
        printf("\n costo mensual: %f", cuenta.costoMensual);
        printf("\n eliminado: %d",cuenta.eliminado);
        printf("\n IdCuenta: %d",cuenta.id);
        printf("\n IdCliente: %d",cuenta.idCliente);
        printf("\n Nro Cuenta: %d",cuenta.nroCuenta);
        printf("\n Saldo: %f",cuenta.saldo);
        printf("\n Tipo cuenta: %d",cuenta.tipoDeCuenta);
                printf("\n ----------------");
}

int* buscarCuentaxNumerodeCta(char nombre[], int numero)
{
    int *nroCuenta = (int*) malloc(sizeof(int));
    stCuentas cuenta;
    int bandera=0;
    FILE* archivo = fopen(nombre,"rb");


    if (archivo)
    {
        while (bandera == 0 && fread(&cuenta,sizeof(stCuentas),1,archivo)>0)
        {

            if(cuenta.nroCuenta==numero)
            {

                bandera=1;
                *nroCuenta = cuenta.nroCuenta;
                muestraUnaCuenta(cuenta);
            }
        }

        fclose(archivo);
    }
    if(bandera==0)
    {
        nroCuenta=NULL;
    }
return nroCuenta;
}

int cuentaregistroscuentas(char nombreArchivo[])
{
    int cantidad=0;
    FILE* archivo = fopen(nombreArchivo,"rb");
    if(archivo)
    {
    fseek(archivo,0,2);
    cantidad = ftell(archivo);
    fclose(archivo);
    }
    return cantidad;
}


void agregarcuentasychequearquenumeronoeste(char nombreArchivo[])
{
    stCuentas cuentaborrador;
///    cuentaborrador=cargaManualUnaCuenta();



/// abrir archivo y pasar a arreglo del tamaño del archivo + 4
/// cerrar archivo
/// buscar en un arreglo
/// cargar arreglo hasta basta (redimencionar arreglo con realloc cada cuatro entradas)
/// pasar arreglo a archivo
}



/*
void agregarcuentasychequearquenumeronoeste(char nombreArchivo[])
{
    stCuentas cuentaborrador;
    int registros=cuentaregistroscuentas(nombreArchivo);
    int i;
    stCuentas arreglo[registros+4];
    FILE* archivo = fopen(nombreArchivo,"rb");
    if(archivo)
    {
        for (int i = 0; i<registros; i++)
        {
                fread(&arreglo[i],sizeof(stCuentas),1,archivo);
        }
    cantidad = ftell(archivo);
    fclose(archivo);
    }
    cuentaborrador=cargaManualUnaCuenta();



/// abrir archivo y pasar a arreglo del tamaño del archivo + 4
/// cerrar archivo
/// buscar en un arreglo
/// cargar arreglo hasta basta (redimencionar arreglo con realloc cada cuatro entradas)
/// pasar arreglo a archivo
}
*/

void buscarcuentaymodificarsaldo(char nombreArchivoCu[],int idCuenta, float importe)
{


    stCuentas cuenta;
    FILE * archivo = fopen(nombreArchivoCu,"r+b");
    if( archivo != NULL)
    {
        fseek(archivo,(idCuenta-1)*sizeof(stCuentas),0);
        fread(&cuenta,sizeof(stCuentas),1,archivo);
        cuenta.saldo = cuenta.saldo+importe;
        fseek(archivo,(idCuenta-1)*sizeof(stCuentas),0);
        fwrite(&cuenta,sizeof(stCuentas),1,archivo);
        fseek(archivo,(idCuenta-1)*sizeof(stCuentas),0);
        fread(&cuenta,sizeof(stCuentas),1,archivo);
        fclose(archivo);
    }

}

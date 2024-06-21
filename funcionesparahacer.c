
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "general.h"

/// Funciones de clientes:

stCliente cargaUnCliente()
{

}
void cargaClienteEnArchivo(char nombreArchivo[])
{


}

void muestraUnClienteId(char nombreArchivo[],int idCliente)
{
    
}

void muestraUnCliente(stCliente cliente)
{
    
}

void modificaClientePorId(char nombreArchivo[],int idCliente)
{
    
}

void mostrarClientes(char nombreArchivo[],int cantDeClientes)
{
    /// mostrar los clientes en linea de listado
}

int ingresarDniClienteValido(char nombreArchivo[])
{
    int idCliente;
    char dni[10];
    int opcion=1;
    printf("Ingrese DNI del cliente");
    scanf("%s",&dni);
    idCliente=traducirDniaIdCliente(nombreArchivo,dni);
    while(idCliente==-1)
    {
        printf("\nNro de DNI no valido, ingrese Nro de DNI");
        scanf("%s",&dni);
        idCliente=verificarNroDeCuenta(dni, nombreArchivo);
        if(idCliente==-1)
        {
            printf("\nNro de Cuenta no valido, desea probar con otro Nro de cuenta? \n1. Si, quiero probar con otro Nro Cuenta \n2. No, quiero volver al menu anterior\n Opcion: ");
            scanf("%d",&opcion);
            if(opcion = 2)
            {
                idCliente=-2;
            }
        }/// dar opcion de escape y resultado -2 para que sepa que esta escapando
    }
    return idCliente;
}



int traducirDniaIdCliente(char archivoCliente[],char dni[])/// si retorna -1 no esta, si retorna menores esta repetido, positivos es el id
{
    int id =-1;
    int bandera=0;
    stCliente cliente;
    FILE * archivo = fopen(archivoCliente,"rb");

    if(archivo)
    {

        while(fread(&cliente,sizeof(stCliente),1,archivo)>0)

            if(strcmp(cliente.dni,dni)==0)
            {
                id=cliente.id;

                bandera=bandera-1;

            }
        fclose(archivo);
    }
    if(bandera<-1)
    {
        return bandera;
    }

    return id;
}



/// funcion de Cuenta
stCuentas cargaUnaCuenta(char nombreArchivo[])
{

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



int ingresarNroCuentaValido(char nombreArchivo[])
{
    int idCuenta;
    int nroCuenta;
    int opcion=1;
    printf("Ingrese Nro de Cuenta");
    scanf("%d",&nroCuenta);
    idCuenta=verificarNroDeCuenta(nroCuenta, nombreArchivo);
    while(idCuenta==-1)
    {
        printf("\nNro cuenta no valido, ingrese Nro de Cuenta");
        scanf("%d",&nroCuenta);
        idCuenta=verificarNroDeCuenta(nroCuenta, nombreArchivo);
        if(idCuenta==-1)
        {
            printf("\nNro de Cuenta no valido, desea probar con otro Nro de cuenta? \n1. Si, quiero probar con otro Nro Cuenta \n2. No, quiero volver al menu anterior\n Opcion: ");
            scanf("%d",&opcion);
            if(opcion = 2)
            {
                idCuenta=-2;
            }
        }/// dar opcion de escape y resultado -2 para que sepa que esta escapando
    }
    return idCuenta;
}



void cargaCuentaArch(char nombreArchivo[], stCuentas cuenta)
{

}

void cambiarEstadoCuenta(char nombreArchivo[], int idCuenta, int estado)
{

}

void modificarCuenta(char nombreArchivo[], int idCuenta)
{

}

void muestraUnaCuenta(stCuenta)
{

}
void muestraPorIdCuenta(char nombreArchivo[], int idCuenta)
{

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


/// funciones de movimiento

stMovimientos cargaManualMovimiento(char ArchivoCuentas[], char ArchivoCliente[])
{
    stMovimientos movimiento;
    stCliente cliente;
    int opcion=0;
    int nroCuenta;
    int idCliente;
    movimiento.id=-1; /// aun no cargado en el archivo de movimientos

    printf("\n Conoce el Nro de Cuenta del Movimiento\n 1. Si\n 2. No \n Eleccion?: ");
    fflush(stdin);
    scanf("%d",&opcion);
    if(opcion==2)
    {
        printf("\n Ingrese el DNI del cliente: ");
        fflush(stdin);
        scanf("%s",&cliente.dni);
        idCliente=traducirDniaIdCliente(ArchivoCliente,cliente.dni);
        while(idCliente==-1)/// funcion que muestra los Nro de cuentas del cliente o que no hay cliente con ese DNI devuelve -1
        {
            printf("\n Ingrese un DNI del cliente valido: ");
            fflush(stdin);
            scanf("%s",&cliente.dni);
        }
        if(idCliente<-1)/// mismo DNI mas de un cliente
        {
            idCliente=mostrarClientesDNIDevolverId(ArchivoCliente,cliente.dni);
        }
        mostrarCuentasxIdCliente(ArchivoCuentas, idCliente);
    }
    printf("\n Ingrese el Nro de Cuenta: ");
    scanf("%d",&nroCuenta);
    while (verificarNroDeCuenta(nroCuenta,ArchivoCuentas)==-1)
    {
        printf("\n Ingrese un Nro de Cuenta valido: ");
        scanf("%d",&nroCuenta);
    }
    movimiento.idCuenta=traducirNroCuentaIdCuenta(nroCuenta,ArchivoCuentas); /// funcion devuelve el IdCuenta para un NroCuenta

    printf("\n Ingrese el detalle de la operacion: ");
    fflush(stdin);
    gets(movimiento.detalle);

    printf("\n Ingrese el importe del movimiento: ");
    scanf("%f",& movimiento.importe);
    printf("\n Ingrese el anio: "); /// cargar validador de año y la ñ
    scanf("%d",& movimiento.anio);

    printf("\n Ingrese el mes: "); /// cargar validador de mes 1-12
    scanf("%d",& movimiento.mes);

    printf("\n Ingrese el dia: "); /// cargar validador de dia
    scanf("%d",& movimiento.dia);

    printf("\n Ingrese el estado (0 si está activo - 1 si está eliminado): "); /// corregir el acento
    scanf("%d",& movimiento.eliminado);

    return movimiento;
}

void cargarUnMovimientoArchivo(char ArchivoMovimientos[], char ArchivoCuentas[], stMovimientos movimiento)
{
    movimiento.id=cuentaRegistrosGral(ArchivoMovimientos,sizeof(stMovimientos)); /// asigna el id incremental
    FILE *archivo = fopen(ArchivoMovimientos, "ab");
    if(archivo)
    {
        fwrite(&movimiento,sizeof(stMovimientos), 1, archivo);
        buscarCuentaModificarSaldo(ArchivoCuentas,movimiento.idCuenta,movimiento.importe);
        fclose(archivo);
    }
}

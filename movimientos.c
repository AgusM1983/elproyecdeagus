
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "generales.h"
#include "cliente.h"
#include "cuenta.h"
#include "movimientos.h"



stMovimientos cargaManualMovimiento(char ArchivoCuentas[], char ArchivoCliente[])
{
    stMovimientos movimiento;
    stCliente cliente;
    int opcion=0;
    int nroCuenta;
    int idCliente;
    movimiento.id=-1; /// aun no cargado en el archivo de movimientos

    printf("\n Conoce el Nro de Cuenta del Movimiento\n 1. No\n 2. Si \n Eleccion?: ");
    fflush(stdin);
    scanf("%d",&opcion);
    if(opcion==1)
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

void mostrarEncabezadoMovimiento()
{

    printf("\nId del Mov | ");


    printf("Id de Cuenta | ");

    printf("Importe del Movimiento | ");


    printf("   Fecha   | ");

    printf("Estado | "); /// corregir el acento

    printf("Detalle de la operacion ");

}
void mostrarUnMovimiento(stMovimientos movimiento)
{


    printf("\n%04d       | ", movimiento.id);


    printf("%06d       | ", movimiento.idCuenta);

    printf("$ %20.2f | ", movimiento.importe);



    printf("%02d/%02d/%04d |",movimiento.dia, movimiento.mes, movimiento.anio);


    printf("    %d   | ", movimiento.eliminado); /// corregir el acento

    printf("%s", movimiento.detalle);

}

void mostrarArchivoMovimiento(char ArchivoMovimientos[],int i)
{
    FILE *archivo = fopen(ArchivoMovimientos,"rb");
    int contador=0;

    if(archivo !=NULL)
    {
        stMovimientos aux;

        while( (fread(&aux, sizeof(stMovimientos),1,archivo) ) >0)
        {
            if(contador%i==0)
            {
                printf("\n");
                system("pause");
                mostrarEncabezadoMovimiento();
            }
            mostrarUnMovimiento(aux);
            contador++;
        }
        fclose(archivo);
    }
}

void buscarImprimirMovimientoxId(char ArchivoMovimientos[], int IdMovimiento)
{
    int bandera =0;
    FILE* archivo = fopen(ArchivoMovimientos, "rb");
    if(archivo!=NULL)
    {
        stMovimientos aux;
        while(fread(&aux, sizeof(stMovimientos),1, archivo)>0 && bandera==0)
        {
            if(aux.id==IdMovimiento)
            {
                mostrarEncabezadoMovimiento();
                mostrarUnMovimiento(aux);
                bandera =1;
            }
        }
        fclose(archivo);
    }

    if (bandera==0)
    {
        printf("\n no existe ese movimiento");
    }

}

void buscarImprimirMovimientoxfecha(char ArchivoMovimientos[], int anioi, int mesi, int diai, int aniof, int mesf, int diaf)
{

    stMovimientos aux;
    FILE* archivo = fopen(ArchivoMovimientos,"rb");
    if (archivo != NULL)
    {
        while(fread(&aux,sizeof(stMovimientos),1,archivo)>0)
        {
            if (aux.anio<aniof && aux.anio>anioi)
            {
                if(aux.mes<mesf && aux.mes>mesi)
                {
                    if(aux.dia<diaf && aux.dia>diai)
                    {
                        mostrarEncabezadoMovimiento();
                        mostrarUnMovimiento(aux);
                    }
                }
            }

            fclose(archivo);
        }
    }

}



void modificarRegistroDeUnMovimiento(char ArchivoMovimientos[], int numeroDeRegistro, char nombreArchivoCu[])
{
    printf("\n---------------------\n modificar movimiento");
    stMovimientos arreglo[2];
    FILE * archivo = fopen(ArchivoMovimientos,"r+b"); /// tengo que lograr esto y listo
    if( archivo != NULL)
    {
        fseek(archivo,(numeroDeRegistro)*sizeof(stMovimientos),0);
        fread(&arreglo[0],sizeof(stMovimientos),1,archivo);
        mostrarxModificarMovimiento(arreglo);
        buscarCuentaModificarSaldo(nombreArchivoCu,arreglo[0].idCuenta,-arreglo[0].importe);
        buscarCuentaModificarSaldo(nombreArchivoCu,arreglo[1].idCuenta,+arreglo[1].importe);
        fseek(archivo,(numeroDeRegistro)*sizeof(stMovimientos),0);
        fwrite(&arreglo[1],sizeof(stMovimientos),1,archivo);
        fclose(archivo);
    }
}


void mostrarxModificarMovimiento(stMovimientos arregloMovimiento[]) /// arregloMovimiento[0] original, arregloMovimiento[1] resultado
{
    int opcion=0;
    arregloMovimiento[1]=arregloMovimiento[0];
    mostrarEncabezadoMovimiento();
    mostrarUnMovimiento(arregloMovimiento[0]);
    printf("\nDesea modificar el idCuenta del movimiento\n 1: Si\n 2:\No \n: "); /// ver de mejorar la opcion
    fflush(stdin);
    scanf("%d",&opcion);
    if( opcion == 1)
    {
        printf("\n Ingrese el Id de Cuenta: ");
        scanf("%d",& arregloMovimiento[1].idCuenta);
    }

    printf("\nDesea modificar el detalle de la operacion\n 1: Si\n 2:\nNo "); /// ver de mejorar la opcion
    scanf("%d",&opcion);
    if( opcion == 1)
    {
        printf("\n Ingrese el detalle de la operacion: ");
        fflush(stdin);
        gets(arregloMovimiento[1].detalle);
    }

    printf("\nDesea modificar el importe del movimiento\n 1: Si\n 2:\No"); /// ver de mejorar la opcion
    scanf("%d",&opcion);
    if( opcion == 1)
    {
        printf("\n Ingrese el importe del movimiento: ");
        scanf("%f",& arregloMovimiento[1].importe);

    }

    printf("\nDesea modificar el anio del movimiento\n 1: Si\n 2:\No"); /// ver de mejorar la opcion
    scanf("%d",&opcion);
    if( opcion == 1)
    {
        printf("\n Ingrese el anio: "); /// cargar validador de año y la ñ
        scanf("%d",& arregloMovimiento[1].anio);
    }

    printf("\nDesea modificar el mes del movimiento\n 1: Si\n 2:\No"); /// ver de mejorar la opcion
    scanf("%d",&opcion);
    if( opcion == 1)
    {
        printf("\n Ingrese el mes: "); /// cargar validador de mes 1-12
        scanf("%d",& arregloMovimiento[1].mes);
    }

    printf("\nDesea modificar el dia del movimiento\n 1: Si\n 2:\No"); /// ver de mejorar la opcion
    scanf("%d",&opcion);
    if( opcion == 1)
    {
        printf("\n Ingrese el dia: "); /// cargar validador de dia
        scanf("%d",& arregloMovimiento[1].dia);
    }

    printf("\nDesea modificar el estado del movimiento\n 1: Si\n 2:\No"); /// ver de mejorar la opcion
    scanf("%d",&opcion);
    if( opcion == 1)
    {
        printf("\n Ingrese el estado (0 si está activo - 1 si está eliminado): "); /// corregir el acento
        scanf("%d",& arregloMovimiento[1].eliminado);
    }
}

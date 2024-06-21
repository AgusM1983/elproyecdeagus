#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "generales.h"
#include "cliente.h"
#include "cuenta.h"
#include "movimientos.h"

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

void mostrarUnaCliente(stCliente cliente)
{
    printf("\n IdCliente: %i",cliente.id);
    printf("| Dni: %s",cliente.dni);
    printf("| NroCliente: %i",cliente.nroCliente);



}

void mostrarArchivoCliente(char nombreCliente[])
{
    stCliente cliente;
    FILE* archivo = fopen(nombreCliente,"rb");
    if (archivo)
    {
        while (fread(&cliente,sizeof(stCliente),1,archivo)>0)
        {
            mostrarUnaCliente(cliente);
        }
        fclose(archivo);
    }
}


int mostrarClientesDNIDevolverId(char archivoCliente[], char dni[])
{

    int id =-1;
    int* ids = (int*)malloc(sizeof(int));
    int validos=0;
    int opcion;
    stCliente cliente;
    FILE * archivo = fopen(archivoCliente,"rb");

    if(archivo)
    {


        while(fread(&cliente,sizeof(stCliente),1,archivo)>0)
        {

            if(strcmp(cliente.dni,dni)==0)
            {
                ids[validos]=cliente.id;
                validos=validos+1;
                printf("\n%d. Cliente: ",validos);
                mostrarUnaCliente(cliente);
                ids = (int*)realloc(ids,(validos+1)*sizeof(int));
            }
        }
        fclose(archivo);
    }
    printf("\nSeleccione el N de Cliente: ");
    fflush(stdin);
    scanf("%d",&opcion);
    while (opcion>validos || opcion < 1)
    {
        printf("\nSeleccione una opcion valida entre 1 y %d: ",validos);
        fflush(stdin);
        scanf("%d",&opcion);
    }
    id=ids[opcion-1];
    return id;
}

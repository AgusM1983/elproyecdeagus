#include "movimientos.h"
#include "cuenta.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>


stMovimientos cargaManualMovimiento(char ArchivoCuentas[])
{
    stMovimientos movimiento;

    movimiento.id=-1; /// aun no cargado en el archivo de movimientos

    printf("\n Ingrese el Id de Cuenta: ");
    scanf("%d",& movimiento.idCuenta);
    while (movimiento.idCuenta>cuentaElementosArchivo(ArchivoCuentas))
    {
        printf("\n Ingrese un Id de Cuenta valido: ");
        scanf("%d",& movimiento.idCuenta);
    }

    printf("\n Ingrese el detalle de la operacion: ");
    fflush(stdin);
    gets(movimiento.detalle);

    printf("\n Ingrese el importe del movimiento: ");
    scanf("%f",& movimiento.importe);
    buscarcuentaymodificarsaldo(ArchivoCuentas,movimiento.idCuenta,movimiento.importe);

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

void mostrarUnMovimiento(stMovimientos movimiento)
{

    printf("\n Id del Movimiento: %d", movimiento.id);

    printf("\n Id de cuenta: %d", movimiento.idCuenta);

    printf("\n Detalle de la operacion: %s", movimiento.detalle);

    printf("\n Importe del movimiento: $%.2f", movimiento.importe);

    printf("\n Fecha: %d/%d/%d ",movimiento.dia, movimiento.mes, movimiento.anio);

    printf("\n Estado (0 si está activo - 1 si está eliminado): %d", movimiento.eliminado); /// corregir el acento

    printf("\n ---------------------- ");
    ;
}


void cargarUnMovimientoArchivo(char ArchivoMovimientos[], char ArchivoCuentas[], stMovimientos movimiento)
{
    movimiento.id=cuentaElementosArchivo(ArchivoMovimientos)+1; /// asigna el id incremental
    FILE *archivo = fopen(ArchivoMovimientos, "ab");
    if(archivo != NULL)
    {
        fwrite(&movimiento,sizeof(stMovimientos), 1, archivo);
        buscarcuentaymodificarsaldo(ArchivoCuentas,movimiento.idCuenta,movimiento.importe);
        fclose(archivo);
    }
}

void mostrarArchivoMovimiento(char ArchivoMovimientos[])
{
    FILE *archivo = fopen(ArchivoMovimientos,"rb");

    if(archivo !=NULL)
    {
        stMovimientos aux;

        printf("\nContenido del archivo:\n\n");

        while( (fread(&aux, sizeof(stMovimientos),1,archivo) ) >0)
        {
            mostrarUnMovimiento(aux);
        }
        fclose(archivo);
    }
}

int cuentaElementosArchivo(char ArchivoMovimientos[])
{

    FILE* archivo= fopen(ArchivoMovimientos, "rb");
    int rta= 0;

    if(archivo!=NULL)
    {
        stMovimientos aux;

        while(fread(&aux, sizeof(stMovimientos), 1, archivo)>0) // contamos los registros leyendolos uno por uno
        {
            rta++;
        }
        fclose(archivo);

    }
    return rta;
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

int pasarArchivoMovimientoaArregloMovimiento(char ArchivoMovimientos[], stMovimientos arreglo[])
{

    int i=0;
    FILE * archivo = fopen(ArchivoMovimientos,"rb");
    if(archivo != NULL)
    {
        while (fread(&arreglo[i],sizeof(stMovimientos),1,archivo)>0)
        {
            i=i++;
        }
    }
    return i;

}

stMovimientos* archivoCompleto2arregloMovimiento(char nombreArchivo[], int* v) ///pasa a puntero arreglo
{
    *v = cuentaElementosArchivo(nombreArchivo);
    FILE* archivo = fopen(nombreArchivo, "rb");
    stMovimientos* a;
    a = (stMovimientos*) malloc(sizeof(stMovimientos)*(*v));
    if(archivo){
        fread(a, sizeof(stMovimientos), *v, archivo);
        fclose(archivo);
    }
    return a; /// devuelve el arreglo completo en a
}


/// ejemplo de realloc para redimencionar un arreglo
/*
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr;
    int initial_size = 5;
    int new_size = 10;

    // Asignar memoria para un array de 5 enteros
    arr = (int *)malloc(initial_size * sizeof(int));
    if (arr == NULL) {
        printf("Error en la asignación de memoria.\n");
        return 1;
    }

    // Inicializar el array
    for (int i = 0; i < initial_size; i++) {
        arr[i] = i + 1;
    }

    // Redimensionar el array a 10 enteros
    arr = (int *)realloc(arr, new_size * sizeof(int));
    if (arr == NULL) {
        printf("Error en la reasignación de memoria.\n");
        return 1;
    }

    // Inicializar los nuevos elementos del array
    for (int i = initial_size; i < new_size; i++) {
        arr[i] = i + 1;
    }

    // Imprimir el array redimensionado
    for (int i = 0; i < new_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Liberar memoria
    free(arr);

    return 0;
}

*/


void insertarEnArreglodeMovimientoOrdenado(stMovimientos arreglo[], stMovimientos movimiento, int cantidadDeMovimiento)
{
    int i = cantidadDeMovimiento -1;
    int bandera=0;
    while (bandera == 0 && i>=0)
    {
        if (arreglo[i].idCuenta<movimiento.idCuenta)
        {
            arreglo[i+1]=movimiento;
            bandera=1;
        }
        else
        {
            arreglo[i+1]=arreglo[i];
        }
        i--;
    }
    if (bandera ==0)
    {
        arreglo[0] = movimiento;
    }
}

void ordenarEnArreglodeMovimientoxCuenta(stMovimientos arreglo[], int validos)
{
    int i;
    for (i=1; i < validos; i++)
    {
        insertarEnArreglodeMovimientoOrdenado(arreglo,arreglo[i],i);
    }
}

void ordenarxCuenta(char ArchivoMovimientos[], stMovimientos arreglo[], int * validos)
{
    *validos = pasarArchivoMovimientoaArregloMovimiento(ArchivoMovimientos, arreglo);
    ordenarEnArreglodeMovimientoxCuenta(arreglo,*validos);
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
                        mostrarUnMovimiento(aux);
                    }
                }
            }

            fclose(archivo);
        }
    }

}

float buscarMayorImporteArchivoDeMovimientos(char ArchivoMovimiento[]) /// ver que pasa si esta vacio
{

    float importeMayor;
    stMovimientos aux;
    FILE* archivo = fopen(ArchivoMovimiento, "rb");
    if(archivo != NULL)
    {
        fread(&aux,sizeof(stMovimientos),1,archivo);
        importeMayor = aux.importe;
        while(fread(&aux,sizeof(stMovimientos),1,archivo)>0)
            if(aux.importe > importeMayor)
            {
                importeMayor = aux.importe;
            }

        fclose(archivo);
    }
return importeMayor;
}

void mostrarxModificarMovimiento(stMovimientos arregloMovimiento[]) /// arregloMovimiento[0] original, arregloMovimiento[1] resultado
{
    int opcion=0;
    arregloMovimiento[1]=arregloMovimiento[0];
    mostrarUnMovimiento(arregloMovimiento[0]);
    printf("\nDesea modificar el idCuenta del movimiento\n 1: Si\n 2:\No \n: "); /// ver de mejorar la opcion
    fflush(stdin);
    scanf("%d",&opcion);
    if( opcion == 1)
    {
    printf("\n Ingrese el Id de Cuenta: ");
    scanf("%d",& arregloMovimiento[1].idCuenta);
    }

    printf("\nDesea modificar el detalle de la operacion\n 1: Si\n 2:\No"); /// ver de mejorar la opcion
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

void modificarRegistroDeUnMovimiento(char ArchivoMovimientos[], int numeroDeRegistro)
{
    printf("\n---------------------\n modificar movimiento");
    stMovimientos arreglo[2];
    FILE * archivo = fopen(ArchivoMovimientos,"r+b"); /// tengo que lograr esto y listo
    if( archivo != NULL)
    {
        fseek(archivo,(numeroDeRegistro-1)*sizeof(stMovimientos),0);
        fread(&arreglo[0],sizeof(stMovimientos),1,archivo);
        mostrarxModificarMovimiento(arreglo);
        fseek(archivo,(numeroDeRegistro-1)*sizeof(stMovimientos),0);
        fwrite(&arreglo[1],sizeof(stMovimientos),1,archivo);
        fclose(archivo);
    }
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




void invierteOrdenArchivoMovimientos(char nombreDelArchivoMovimiento [])
{
    stMovimientos inicio;
    stMovimientos fin;
    int posinicio=0;
    int posfinal = cuentaElementosArchivo(nombreDelArchivoMovimiento)-1;
    FILE* archivo = fopen(nombreDelArchivoMovimiento,"r+b");
    if(archivo)
    {
        while(posinicio<posfinal)
        {

        fseek(archivo,posinicio*sizeof(stMovimientos),0); // voy al principio
        fread(&inicio, sizeof(stMovimientos),1,archivo);
        fseek(archivo,posfinal*sizeof(stMovimientos),3);
        fread(&fin,sizeof(stMovimientos),1,archivo);
        fseek(archivo,posinicio*sizeof(stMovimientos),0);
        fwrite(&fin,sizeof(stMovimientos),1,archivo);
        fseek(archivo,posfinal*sizeof(stMovimientos),0);
        fwrite(&inicio,sizeof(stMovimientos),1,archivo);
                printf("\n llegamos hasta aca");

        posfinal= posfinal-1;
        posinicio= posinicio+1;
        }
        fclose(nombreDelArchivoMovimiento);
    }

}


///Crear una función que retorne la cantidad de registros que tiene el archivo. Usar fseek y ftell.
///Puede pensar la función para uso genérico, que sirva para averiguar la cantidad de registros de cualquier archivo.

///Dado un archivo de alumnos, que tenga al menos 10 registros, hacer una función que muestre el contenido de un registro,
///cuyo número (entre 0 y 9) se pase por parámetro. Controlar no sobrepasar los límites del archivo.

///Realice una (o varias) funciones que permitan modificar un registro existente en el archivo de alumnos.
///La misma debe permitir modificar uno o todos los campos de la estructura y sobreescribir el registro existente en el archivo.

///Dado un archivo de alumnos, hacer una función que invierta los elementos del mismo.
///No se puede usar otro archivo auxiliar ni un arreglo auxiliar. Debe trabajar sobre el archivo. Puede utilizar variables de tipo alumno auxiliares.


/// hacer algo equivalente para movimiento y cargar en el main
stMovimientos* buscarMovimientoPorId(char nombreArchivoMovimiento[], int Id)
{
    stMovimientos* M = (stMovimientos*) malloc(sizeof(stMovimientos));
    stMovimientos movimiento;
    int bandera=0;
    FILE* archivo = fopen(nombreArchivoMovimiento,"rb");
    if(archivo)
    {
    while(bandera == 0 && fread(&movimiento,sizeof(stMovimientos),1,archivo)>0)
    {
        if(movimiento.id==Id)
        {
            bandera=1;
            *M = movimiento;
        }
    }
    fclose(archivo);
    }
    if (bandera== 0)
    {
        stMovimientos* M= NULL;
    }
return M;
}


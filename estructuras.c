#include <stdio.h>
#include <stdlib.h>
#include "estructuras.h"
#include <string.h>


stMovimientos cargaUnMovimientomanual()
{
    stMovimientos M;

    M.id = -1; // id de movimiento no valido (se crea con este numero y cuando se ingresa a arreglo de movimientos se le asigna el numero correlativo)
    int diasPorMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // dias para años no bisiestos

    printf("\n Ingrese nro de Cuenta, si no lo sabe presione F3 para abrir el buscador de cuentas: "); //Tendria que agregarse una funcion ayuda para buscar cuentas y por otro lado este dato se verifica al final
    scanf("%d", &M.idCuenta);

    printf("\n Cargue detalles: ");
    fflush(stdin);
    scanf("%s", M.detalle);

    printf("\n Ingrese el monto: ");
    scanf("%f", &M.importe);

    printf("\n Ingrese a%co: ",164);
    scanf("%d", &M.anio);
    if(esBisiesto(M.anio)==1)
    {
        diasPorMes[1] =  28;
    }

    printf("\n Ingrese mes: ");
    scanf("%d", &M.mes);
    while(M.mes<1 || M.mes>12)
    {
        printf("\n Numero de mes no valido!!!");
        printf("\n Ingrese un mes dentro del rango 1-12: ");
        scanf("%d", &M.mes);
    }

    printf("\n Ingrese dia ");
    scanf("%d", &M.dia);
    while(M.dia>diasPorMes[M.mes-1])
    {
        printf("\n Numero de dia supera los dias del mes!!!");
        printf("\n Ingrese un dia dentro del rango 1 - %d: ",diasPorMes[M.mes-1]);
        scanf("%d", &M.dia);
    }
    printf("\n Ingrese el estado de Activo (1) o Eliminado (0)");
    scanf("%d", &M.eliminado);
    while(M.eliminado!=0 && M.eliminado!=1)
    {
        printf("\n Estado invalido!!!");
        printf("\n Ingrese el estado de Activo (1) o Eliminado (0)");
        scanf("%d", &M.eliminado);
    }
    return M;

}

void incorporarMovimientoManual(stMovimientos M[],int* validosMovimiento, stMovimientos Movimiento, stCuentas C[], int validosCuentas)
{
    char respuesta= 'n';

    while (buscarNumeroCuenta(C,Movimiento.idCuenta,validosCuentas)==1) //escribir una funcion buscar que devuelva 1 o 0
    {
        printf("\n No existe esa cuenta");
        printf("\n Modifique numero de cuenta");
    }
    Movimiento.id = *validosMovimiento; // asigno el valor correlativo de Movimientos.id
    printf("\n Se va a incorporar un nuevo Movimiento en la cuenta %d", Movimiento.idCuenta);
    muestraUnMovimiento(Movimiento);
    printf("\n Desea cargar ese movimiento? (s/n): "); // Si o no hacer opción
    fflush(stdin);
    scanf("%c",&respuesta);
    if (respuesta == 's' || respuesta == 'S')
    {
        M[*validosMovimiento] = Movimiento;
        *validosMovimiento = *validosMovimiento + 1;
    }
    else
    {
        printf("\n No se cargo el movimiento");
    }
}

void muestraUnMovimiento(stMovimientos a)
{
    printf("\n -----------------------------------");
    printf("\n Numero de movimiento: %d",a.id);
    printf("\n Numero de cuenta: %d",a.idCuenta);
    printf("\n Estado: %d", a.eliminado); //poner un if para que quede mas lindo donde devuelva eliminado o activo
    printf("\n Fecha: %d / %d / %d",a.dia,a.mes,a.anio);
    printf("\n Detalle: %s",a.detalle);
    printf("\n Importe: $ %.2f",a.importe);
    printf("\n -----------------------------------");
}


int buscarNumeroCuenta(stCuentas C[], int idCuenta, int validos)
{
    return 0;
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
    return respuesta; // devuelve 1 si es bisiesto
}


int cargarManualArregloDeMovimientos(stMovimientos M[],stCuentas C[], int validosCuenta)
{
    int opcion=28;
    int validos=0;
    stMovimientos Movimiento;
    while (opcion!=27)
    {
        Movimiento = cargaUnMovimientomanual();
        incorporarMovimientoManual(M,&validos,Movimiento,C,validosCuenta);
        printf("\n Presione 27 para salir o cualquier otra letra para continuar: ");
        fflush(stdin);
        scanf("%d",&opcion);
    }
return validos;
}

void mostrarArregloDeMovimientos(stMovimientos M[], int validos)
{
    int i;
    for (i=0;i<validos;i++)
    {
        muestraUnMovimiento(M[i]);
    }
}

void imprimirMovimientos(stMovimientos M[], int validos)
{
    int anio=0;
    int mes=0;
    int dias=0;
    int idCuenta=-1;
    int importe=0;
    char detalle[100];
    int estado=0;
    float saldo=0;

    int i=0; // contador del for

    int numero=0; // opcion del menu

    int arreglorecoge[validos]; // arreglo que recoge los numeros de cuenta que coincidan
    char arregloRecogeChar[validos]; // arreglo que recoge los numeros de cuenta que coincidan
    int validosarreglorecoge;
    int b=0; // contador del arreglo que recoge

    printf("\n Que variable quiere buscar?");
    printf("\n 1: para buscar por año");
    printf("\n 2: para buscar por año y mes");
    printf("\n 3: para buscar por año, mes y dia");
    printf("\n 4: para buscar por cuenta");
    printf("\n 5: para buscar por importe");
    printf("\n 6: para buscar por estado");
    printf("\n 7: para buscar por detalle");
    printf("\n otro: para salir");
    printf("\n Opcion: ");
    fflush(stdin);
    scanf("%i",&numero);

    switch (numero)
    {
    case 1:
        printf("\n buscar por año");
        printf("\n ingrese el año a buscar: ");
        scanf("%d",&anio);
        for (i=0; i<validos; i++)
        {
            if(M[i].anio==anio)
            {


                printf("\n Movimiento: %d | Fecha: %.2d/%.2d/%.4d | Importe:$ %2.f ",M[i].id, M[i].dia, M[i].mes, M[i].anio, M[i].importe);
                arreglorecoge[b]=M[i].id;
                if(M[i].eliminado==0)
                {
                saldo= saldo + M[i].importe;
                }
                b=b+1;
            }
        }
        printf("\n Se encontraron %d coincidencias, con un saldo de:$ %2.f ",b, saldo);
        break;
    case 2:
        printf("\n buscar por año y mes");
        printf("\n ingrese el año a buscar: ");
        scanf("%d",&anio);
        printf("\n ingrese el mes a buscar: ");
        scanf("%d",&mes);
        for (i=0; i<validos; i++)
        {
            if(M[i].anio==anio)
            {
                if(M[i].mes==mes)
                {
                    printf("\n Movimiento: %d | Fecha: %.2d/%.2d/%.4d | Importe:$ %2.f ",M[i].id, M[i].dia, M[i].mes, M[i].anio, M[i].importe);
                    arreglorecoge[b]=M[i].id;
                if(M[i].eliminado==0)
                {
                saldo= saldo + M[i].importe;
                }

                    b=b+1;
                }
            }
        }
        printf("\n Se encontraron %d coincidencias, con un saldo de:$ %2.f ",b, saldo);
        break;
    case 3:
        printf("\n buscar por año, mes y dia");
        printf("\n ingrese el año a buscar: ");
        scanf("%d",&anio);
        printf("\n ingrese el mes a buscar: ");
        scanf("%d",&mes);
        printf("\n ingrese el dia a buscar: ");
        scanf("%d",&dias);
        for (i=0; i<validos; i++)
        {
            if(M[i].anio==anio)
            {
                if(M[i].mes=mes)
                {
                    if(M[i].dia=dias)
                    {
                        printf("\n Movimiento: %d | Fecha: %.2d/%.2d/%.4d | Importe:$ %2.f ",M[i].id, M[i].dia, M[i].mes, M[i].anio, M[i].importe);
                        arreglorecoge[b]=M[i].id;
                if(M[i].eliminado==0)
                {
                saldo= saldo + M[i].importe;
                }
                        b=b+1;
                    }
                }
            }
        }
        printf("\n Se encontraron %d coincidencias, con un saldo de:$ %2.f ",b, saldo);
        break;
    case 4:
        printf("\n Buscar por cuenta");
        printf("\n ingrese el numero de cuenta a buscar: ");
        scanf("%d",&idCuenta);
        for (i=0; i<validos; i++)
        {
            if(M[i].idCuenta==idCuenta)
            {
                printf("\n Movimiento: %.6d | Fecha: %.2d/%.2d/%.4d | Importe:$ %2.f ",M[i].id, M[i].dia, M[i].mes, M[i].anio, M[i].importe);
                arreglorecoge[b]=M[i].id;
                if(M[i].eliminado==0)
                {
                if(M[i].eliminado==0)
                {
                saldo= saldo + M[i].importe;
                }
                }
                b=b+1;
            }
        }
        printf("\n Se encontraron %d coincidencias, con un saldo de:$ %2.f ",b, saldo);
        break;
    case 5:
        printf("\n Buscar por importe");
        printf("\n ingrese el importe a buscar: ");
        scanf("%d",&importe);
        for (i=0; i<validos; i++)
        {
            if(M[i].importe==importe)
            {
                printf("\n Movimiento: %d | Fecha: %.2d/%.2d/%.4d | Importe:$ %2.f ",M[i].id, M[i].dia, M[i].mes, M[i].anio, M[i].importe);
                arreglorecoge[b]=M[i].id;
                if(M[i].eliminado==0)
                {
                saldo= saldo + M[i].importe;
                }
                b=b+1;
            }
        }
        printf("\n Se encontraron %d coincidencias, con un saldo de:$ %2.f ",b, saldo);
        break;
    case 6:
        printf("\n Buscar por estado");
        printf("\n ingrese el estado a buscar: ");
        scanf("%d",&estado);
        for (i=0; i<validos; i++)
        {
            if(M[i].eliminado==estado)
            {
                printf("\n Movimiento: %d | Fecha: %.2d/%.2d/%.4d | Importe:$ %2.f ",M[i].id, M[i].dia, M[i].mes, M[i].anio, M[i].importe);
                arreglorecoge[b]=M[i].id;
                if(M[i].eliminado==0)
                {
                saldo= saldo + M[i].importe;
                }
                b=b+1;
            }
        }
        printf("\n Se encontraron %d coincidencias, con un saldo de: %2.f ",b, saldo);
        break;
    case 7:
        printf("\n Buscar por detalle: ");
        fflush(stdin);
        gets(detalle); //ver de poner mensaje tipo de detalles
        printf("\n Ingreso: %s",detalle);
        for (i=0; i<validos; i++)
        {
            if(stricmp(M[i].detalle,detalle)==0)
            {
                printf("\n Movimiento: %4.d | Fecha: %.2d/%.2d/%.4d | Importe:$ %20.2f | Detalle: %s",M[i].id, M[i].dia, M[i].mes, M[i].anio, M[i].importe, M[i].detalle);
                arregloRecogeChar[b]=M[i].detalle;
                if(M[i].eliminado==0)
                {
                saldo= saldo + M[i].importe;
                }
                b=b+1;
            }
        }
        printf("\n Se encontraron %d coincidencias, con un saldo de: %2.f ",b, saldo);
        break;
    default:
        printf("\n Volviendo al menu principal");
        system("pause");
    }
}
void modificarEstado2Movimiento(stMovimientos* M, int estado)
{
    M->eliminado = estado;
}

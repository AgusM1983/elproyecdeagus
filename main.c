#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "cuenta.h"
#include "movimientos.h"
#include "generales.h"
#include "mock.h"

int main() {
    /// eleccion de menu y clave??
    menuEmpleados();
    menuClientes();

    return 0;
}



void menuEmpleados() {
    int opcion;
    char archivoClientes[] = "clientes.dat";
    char archivoCuentas[] = "cuentas.dat";
    char archivoMovimientos[] = "movimientos.dat";

    do {
        printf("\nMenu Empleados:\n");
        printf("1. Alta Cliente\n");
        printf("2. Baja Cliente\n");
        printf("3. Modificar Cliente\n");
        printf("4. Consultar Cliente\n");
        printf("5. Listar Clientes\n");
        printf("6. Alta Cuenta\n");
        printf("7. Baja Cuenta\n");
        printf("8. Modificar Cuenta\n");
        printf("9. Consultar Cuenta\n");
        printf("10. Listar Cuentas por Cliente\n");
        printf("11. Alta Movimiento\n");
        printf("12. Baja Movimiento\n");
        printf("13. Modificar Movimiento\n");
        printf("14. Consultar Movimiento\n");
        printf("15. Listar Movimientos por Cuenta\n");
        printf("16. Listar Movimientos por Fecha\n");
        printf("17. Cargar Movimientos Aleatorios\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                // Función para alta de cliente
                break;
            case 2:
                // Función para baja de cliente
                break;
            case 3:
                // Función para modificar cliente
                break;
            case 4:
                // Función para consultar cliente
                break;
            case 5:
                mostrarArchivoCliente(archivoClientes);
                break;
            case 6:
                // Función para alta de cuenta
                break;
            case 7:
                // Función para baja de cuenta
                break;
            case 8:
                // Función para modificar cuenta
                break;
            case 9:
                // Función para consultar cuenta
                break;
            case 10:
                // Función para listar cuentas por cliente
                break;
            case 11:
                // Función para alta de movimiento
                break;
            case 12:
                // Función para baja de movimiento
                break;
            case 13:
                // Función para modificar movimiento
                break;
            case 14:
                // Función para consultar movimiento
                break;
            case 15:
                // Función para listar movimientos por cuenta
                break;
            case 16:
                // Función para listar movimientos por fecha
                break;
            case 17:
                // Función para cargar movimientos aleatorios
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida\n");
        }
    } while (opcion != 0);
}

void menuClientes() {
    int opcion;
    char archivoClientes[] = "clientes.dat";
    char archivoCuentas[] = "cuentas.dat";
    char archivoMovimientos[] = "movimientos.dat";
    char dni[10];
    int idCliente, idCuenta;

    printf("Ingrese su DNI: ");
    scanf("%s", dni);
    idCliente = traducirDniaIdCliente(archivoClientes, dni);

    if (idCliente < 0) {
        printf("DNI no encontrado o múltiples clientes con el mismo DNI\n");
        return;
    }

    do {
        printf("\nMenu Clientes:\n");
        printf("1. Consultar mis datos\n");
        printf("2. Listar mis cuentas\n");
        printf("3. Listar movimientos de una cuenta\n");
        printf("4. Buscar movimientos por fecha\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                // Función para consultar datos del cliente
                break;
            case 2:
                mostrarCuentasxIdCliente(archivoCuentas, idCliente);
                break;
            case 3:
                printf("Ingrese el ID de la cuenta: ");
                scanf("%d", &idCuenta);
                // Función para listar movimientos de una cuenta
                break;
            case 4:
                // Función para buscar movimientos por fecha
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida\n");
        }
    } while (opcion != 0);
}


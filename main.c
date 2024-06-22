#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "general.h"

void menuEmpleados();

int main() 
{
menuEmpleados();
return 0;
}


void menuEmpleados() {
    int opcion;
    char archivoClientes[] = "clientes.dat";
    char archivoCuentas[] = "cuentas.dat";
    char archivoMovimientos[] = "movimientos.dat";
    stCliente cliente;
    stMovimientos movimiento;
    stCuentas cuenta;
    int idCliente;
    int idCuenta;
    int idMovimiento;

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
        printf("10. Listar Cuentas por Cliente\n"); /// tengo la funcion
        printf("11. Alta Movimiento\n"); /// tengo la funcion
        printf("12. Baja Movimiento\n"); /// usar funcion modificar movimiento pero solo de 0 a 1
        printf("13. Modificar Movimiento\n"); /// tengo la funcion
        printf("14. Consultar Movimiento\n"); /// tengo la funcion
        printf("15. Listar Movimientos por Cuenta\n");
        printf("16. Listar Movimientos por Fecha\n"); /// tengo la funcion
        printf("17. Cargar Movimientos Aleatorios\n"); /// mock ver el tema de las cuotas
        printf("18. Proceso de salvar datos\n");
        printf("19. Proceso cargar cuotas mensuales datos\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);


        switch (opcion) {
            case 1:
                cliente=cargaUnCliente();
                cargaClienteEnArchivo(archivoClientes, cliente);
                // Función para alta de cliente
                break;
            case 2:
                idCliente=ingresarDniClienteValido(archivoClientes);
                if(idCliente!=-2)
                {

                }

                // Función para baja de cliente
                break;
            case 3:
                idCliente=ingresarDniClienteValido(archivoClientes);
                if(idCliente!=-2)
                {
                modificaClientePorId(archivoClientes,idCliente);
                }                
                // Función para modificar cliente
                break;
            case 4:
                idCliente=ingresarDniClienteValido(archivoClientes);
                if(idCliente!=-2)
                {
                muestraUnClienteId(archivoClientes,idCliente);                    
                }
                // Función para consultar cliente
                break;
            case 5:
                mostrarClientes(archivoClientes, cantidad);
                // Función para consultar cliente
                break;
            case 6:

                cuenta=cargaUnaCuenta(archivoClientes);
                cargaCuentaArch(archivoCuentas,cuenta);
                // Función para alta de cuenta
                break;
            case 7:
                idCuenta=ingresarNroCuentaValido(archivoCuentas);
                if(idCuenta!=-2)
                {
                cambiarEstadoCuenta(archivoCuentas, idCuenta,1);
                }
                // Función para baja de cuenta
                break;
            case 8:
                idCuenta=ingresarNroCuentaValido(archivoCuentas);
                if(idCuenta!=-2)
                {
                modificarCuenta(archivoCuentas, idCuenta);
                }
                // Función para modificar cuenta
                break;
            case 9:
                idCuenta=ingresarNroCuentaValido(archivoCuentas);
                if(idCuenta!=-2)
                {
                muestraPorIdCuenta(archivoCuentas,idCuenta);
                }

                // Función para consultar cuenta
                break;
            case 10:
                idCliente=ingresarDniClienteValido(archivoClientes);
                if(idCliente!=-2)
                {
                mostrarCuentasxIdCliente(archivoCuentas,idCliente);
                }
                // Función para listar cuentas por cliente
                break;
            
            /// movimientos
            
            case 11:
                movimiento=cargaManualMovimiento(archivoCuentas);
                cargarUnMovimientoArchivo(archivoMovimientos,archivoCuentas,movimiento);
                // Función para alta de movimiento
                break;
            case 12:
                idCuenta=ingresarNroCuentaValido(archivoCuentas);
                if(idCuenta!=-2)
                {
                muestraMovimientoPorNroCuenta(archivoMovimientos,idCuenta,30)
                }
                
                idMovimiento=ingresarIdMovValido(archivoMovimientos);
                if(idCuenta!=-2)
                {
                modificarEstadoIdMovimiento(archivoMovimientos, idMovimiento,1);
                }
                // Función para baja de movimiento
                break;
            case 13:
                idCuenta=ingresarNroCuentaValido(archivoCuentas);
                if(idCuenta!=-2)
                {
                muestraMovimientoPorNroCuenta(archivoMovimientos,idCuenta,30)
                }
                
                idMovimiento=ingresarIdMovValido(archivoMovimientos);
                if(idMovimiento!=-2)
                {
                modificarRegistroDeUnMovimiento(archivoMovimientos,idMovimiento,archivoCuentas);
                }
                
                // Función para modificar movimiento
                break;
            case 14: /// no tiene sentido
                
                // Función para consultar movimiento
                break;
            case 15:
                idCuenta=ingresarNroCuentaValido(archivoCuentas);
                if(idCuenta!=-2)
                {
                muestraMovimientoPorNroCuenta(archivoMovimientos,idCuenta,30)
                }
                // Función para listar movimientos por cuenta
                break;
            case 16:
                idCuenta=ingresarNroCuentaValido(archivoCuentas);
                if(idCuenta!=-2)
                {
                muestraMovimientoPorNroCuentaPorFecha(archivoMovimientos,idCuenta,anio0,mes0,dia0,aniof,mesf,diaf,30)
                }
                
                // Función para listar movimientos por fecha
                break;
            case 17: /// no tiene sentido
                
                // Función para cargar movimientos aleatorios
                break;
            case 18: /// no tiene sentido
                printf("18. Proceso de salvar datos\n");
 
                // Función para cargar movimientos aleatorios
                break;
            case 19: /// no tiene sentido                
            printf("19. Proceso cargar cuotas mensuales datos\n");
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida\n");
        }
    } while (opcion != 0);
}

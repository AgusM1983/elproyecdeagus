#ifndef CUENTA_H_INCLUDED
#define CUENTA_H_INCLUDED
#include "movimientos.h"
typedef struct {
    int id; /// campo único y autoincremental
    int idCliente; /// Id del Cliente dueño de la Cuenta;
    int nroCuenta;
    int tipoDeCuenta; /// 1. Caja de Ahorro en Pesos, 2. Caja de Ahorro en Dólares, 3. Cta Cte en $
    float costoMensual; /// Costo de mantenimiento del producto;
    float saldo; /// Debe actualizarse al modidificar o cargar un movimiento.
    int eliminado; /// 0 si está activo - 1 si está eliminado

} stCuentas;

stCuentas cargaManualUnaCuenta(char nombre[]);
void buscarcuentaymodificarsaldo(char nombreArchivoCu[],int idCuenta, float importe);
void cargaMockunaCuenta(char nombre[]);
void muestraUnaCuenta(stCuentas cuenta);
int* buscarCuentaxNumerodeCta(char nombre[], int numero);
int cuentaregistroscuentas(char nombreArchivo[]);
#endif // CUENTA_H_INCLUDED

#ifndef CUENTA_H_INCLUDED
#define CUENTA_H_INCLUDED

typedef struct {
    int id; /// campo único y autoincremental
    int idCliente; /// Id del Cliente dueño de la Cuenta;
    int nroCuenta;
    int tipoDeCuenta; /// 1. Caja de Ahorro en Pesos, 2. Caja de Ahorro en Dólares, 3. Cta Cte en $
    float costoMensual; /// Costo de mantenimiento del producto;
    float saldo; /// Debe actualizarse al modidificar o cargar un movimiento.
    int eliminado; /// 0 si está activo - 1 si está eliminado

} stCuentas;

void muestraUnaCuenta(stCuentas cuenta);
void mostrarArchivoCuenta(char nombreCuenta[]);
void mostrarCuentasxIdCliente(char archivoCuenta[], int idCliente);
int verificarNroDeCuenta(int numeroCuenta, char nombreCuenta[]); /// -1 si no y nroCuenta si esta
int traducirNroCuentaIdCuenta(int nroCuenta, char nombreCuenta[]);
void buscarCuentaModificarSaldo(char nombreArchivoCu[],int idCuenta, float importe);

#endif // CUENTA_H_INCLUDED

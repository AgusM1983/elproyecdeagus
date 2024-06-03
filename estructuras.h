#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

typedef struct {
int id; /// campo �nico y autoincremental
int idCuenta; /// Id de la cuenta
char detalle[100];
float importe;
int anio;
int mes; /// 1 a 12
int dia; /// 1 a � dependiendo del mes
int eliminado; /// 0 si est� activo - 1 si est� eliminado

} stMovimientos;

typedef struct {
    int id; /// campo �nico y autoincremental
    int idCliente; /// Id del Cliente due�o de la Cuenta;
    int nroCuenta;
    int tipoDeCuenta; /// 1. Caja de Ahorro en Pesos, 2. Caja de Ahorro en D�lares, 3. Cta Cte en $
    float costoMensual; /// Costo de mantenimiento del producto;
    float saldo; /// Debe actualizarse al modidificar o cargar un movimiento.
    int eliminado; /// 0 si est� activo - 1 si est� eliminado

} stCuentas;


stMovimientos cargaUnMovimientomanual();
void muestraUnMovimiento(stMovimientos a);
void incorporarMovimientoManual(stMovimientos M[],int* validosMovimiento, stMovimientos Movimiento, stCuentas C[], int validosCuentas);
void imprimirMovimientos(stMovimientos M[], int validos);
int cargarManualArregloDeMovimientos(stMovimientos M[],stCuentas C[], int validosCuenta);
void mostrarArregloDeMovimientos(stMovimientos M[], int validos);
void modificarEstado2Movimiento(stMovimientos* M, int estado);


int buscarNumeroCuenta(stCuentas C[], int idCuenta, int validos);

//auxiliares

int esBisiesto(int anio);

#endif // ESTRUCTURAS_H_INCLUDED

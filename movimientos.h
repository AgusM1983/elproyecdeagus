#ifndef MOVIMIENTOS_H_INCLUDED
#define MOVIMIENTOS_H_INCLUDED
#include "cuenta.h"

typedef struct {

int id; /// campo único y autoincremental
int idCuenta; /// Id de la cuenta
char detalle[100];
float importe;
int anio;
int mes; /// 1 a 12
int dia; /// 1 a … dependiendo del mes
int eliminado; /// 0 si está activo - 1 si está eliminado

}stMovimientos;


stMovimientos cargaManualMovimiento(char ArchivoCuentas[]);
void mostrarUnMovimiento(stMovimientos movimiento);
void cargarUnMovimientoArchivo(char ArchivoMovimientos[], char ArchivoCuentas[], stMovimientos movimiento);
void mostrarArchivoMovimiento(char ArchivoMovimientos[]);
int cuentaElementosArchivo(char ArchivoMovimientos[]);
void buscarImprimirMovimientoxId(char ArchivoMovimiento[], int IdMovimiento);
int pasarArchivoMovimientoaArregloMovimiento(char ArchivoMovimientos[], stMovimientos arreglo[]);
stMovimientos* archivoCompleto2arregloMovimiento(char nombreArchivo[], int* v); ///pasa a puntero arreglo
void insertarEnArreglodeMovimientoOrdenado(stMovimientos arreglo[], stMovimientos movimiento, int cantidadDeMovimiento);
void ordenarEnArreglodeMovimientoxCuenta(stMovimientos arreglo[], int validos);
void ordenarxCuenta(char ArchivoMovimientos[], stMovimientos arreglo[], int * validos);
void buscarImprimirMovimientoxfecha(char ArchivoMovimientos[], int anioi, int mesi, int diai, int aniof, int mesf, int diaf);
float buscarMayorImporteArchivoDeMovimientos(char ArchivoMovimiento[]);
void mostrarxModificarMovimiento(stMovimientos arregloMovimiento[]); /// arregloMovimiento[0] original, arregloMovimiento[1] resultado
void modificarRegistroDeUnMovimiento(char ArchivoMovimientos[], int numeroDeRegistro);

int esBisiesto(int anio);

void invierteOrdenArchivoMovimientos(char nombreDelArchivoMovimiento []);
stMovimientos* buscarMovimientoPorId(char nombreArchivoMovimiento[], int Id);

#endif // MOVIMIENTOS_H_INCLUDED

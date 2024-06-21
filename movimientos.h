#ifndef MOVIMIENTOS_H_INCLUDED
#define MOVIMIENTOS_H_INCLUDED

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

stMovimientos cargaManualMovimiento(char ArchivoCuentas[], char ArchivoCliente[]);
void cargarUnMovimientoArchivo(char ArchivoMovimientos[], char ArchivoCuentas[], stMovimientos movimiento);
void mostrarEncabezadoMovimiento();
void mostrarUnMovimiento(stMovimientos movimiento);
void mostrarArchivoMovimiento(char ArchivoMovimientos[],int i);
void buscarImprimirMovimientoxId(char ArchivoMovimientos[], int IdMovimiento);
void buscarImprimirMovimientoxfecha(char ArchivoMovimientos[], int anioi, int mesi, int diai, int aniof, int mesf, int diaf);
void modificarRegistroDeUnMovimiento(char ArchivoMovimientos[], int numeroDeRegistro, char nombreArchivoCu[]);
void mostrarxModificarMovimiento(stMovimientos arregloMovimiento[]);/// el arreglo es de dos movimientos [0] original y [1]devuelve
#endif // MOVIMIENTOS_H_INCLUDED

#ifndef MOCK_H_INCLUDED
#define MOCK_H_INCLUDED

/// cliente
void cargaMock80Cliente(char nombreCliente[]);
/// cuenta
void cargaMock80Cuenta(char nombre[]);

/// movimiento
void getDayMonthYeard(stMovimientos* M);
void idCuenta(stMovimientos* M, char nombreArchivoCu[]);
void eliminado(stMovimientos* M);
void importeydetalle(stMovimientos* M);
void mockArchivo (char nombreArchivoMov[], char nombreArchivoCu[], int cantidad);

#endif // MOCK_H_INCLUDED

#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

typedef struct{
    int id; /// campo único y autoincremental
    int nroCliente;
    char nombre[30];
    char apellido[30];
    char dni[10];
    char email[30]; ///stDomicilio domicilio;
    char telefono[12];
    int eliminado;
}stCliente;

int traducirDniaIdCliente(char archivoCliente[],char dni[]);
void mostrarUnaCliente(stCliente cliente);
void mostrarArchivoCliente(char nombreCliente[]);
int mostrarClientesDNIDevolverId(char archivoCliente[], char dni[]);

#endif // CLIENTE_H_INCLUDED

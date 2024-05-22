#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#include <stdio.h> /* Gestiona entrada/salida de datos estándar. */
#include <string.h> /* Funciones para cadenas de caracteres C. */
#include <string> /* Clase de cadena de caracteres en C++. */
#include <stdlib.h> /* Funciones de utilidad general, memoria, conversiones. */
#include <locale.h> /* Configuración regional, formateo según idioma/ubicación. */
#include <cmath> /* Funciones matemáticas avanzadas, exponenciales, logaritmos. */
#include <cctype> /* Funciones para probar tipos de caracteres y conversión. */
#include <algorithm> /* Algoritmos para operaciones comunes, ordenamiento, búsqueda. */
#include <sstream> /* Flujo de entrada/salida para cadenas de texto. */
#include <iostream> /* Entrada/salida de flujo para consola/archivos. */
#include <fstream> /* Lectura/escritura de datos en archivos. */
#include <limits> /* Límites y propiedades de tipos de datos. */
using namespace std;
 
#define MAX 80
#define VAL -1

double TasaDolar;

class deudas{
	public:
		int cedula;
		char nombre[MAX];
		char Apellido[MAX];
		float debe;
		char descripcion[MAX];
};

typedef struct deudas Deudas; 

/* Funcion para obtener un cliente del archivo binario */
Deudas *obtenerClientes(int *n); 
/*Funcion para Busca si existe el cliente en el archivo binario */
char ExisteCliente(int codigoCedula, Deudas *registro);
/*Funcion para Inserta si existe el cliente en el archivo binario */ 
char InsertarCliente(Deudas registro); 
/* Menu modificar un cliente */
void ModificarEnArchivoBinario();
/* Crear un archivo TXT con la lista de los clientes para poder imprimirla */
char guardarReporte(); 



/* Procedimiento del Menu principal */
void menuPrincipal();
 
/* OJO Importante - Lectura de cadenas */
int leercadena(char *cad, int n);
 
void GuardarEnBinarioTasa();
void LeerValorDesdeElBinario();

/* Titulo del Desarrollo */
void Titulo();
/* Menu para insertar */
void InsertarEnBinario();
/* Menu para buscar */
void BuscarEnBinario();
/* Menu Eliminar un clientes */
void EliminarEnBinario();
/* Menu mostrar Lista de clientes */
void ListadoDeArchivoBinario();
 
char linea[MAX];
 
int main()
{
	system("color 71");
	menuPrincipal();
 
	return 0;
}
 
void menuPrincipal()
{
	char repite = 1;
	int opcion = -1;
	double tasa = TasaDolar;
 
	do {
		system(CLEAR);
		Titulo();
		LeerValorDesdeElBinario();
		printf("\n\t\t\tTasa Del Dolar = Bs %.2f\n", TasaDolar);

 
		printf("\n\t\t\t MENU PRINCIPAL \n");
		printf("\n\t\t[1]. Registrar clientes\n");
		printf("\t\t[2]. Mostrar listado de clientes\n");
		printf("\t\t[3]. Buscar cliente. \n");
		printf("\t\t[4]. Modificar deuda de cliente\n");
		printf("\t\t[5]. Eliminar cliente\n");
		printf("\t\t[6]. Modificar Tasa del dolar\n");
		printf("\t\t[7]. Salir\n");
		printf("\n\t\t Ingrese su opcion: [ ]\b\b");
 
		/* Lectura segura de un entero */
		leercadena(linea, MAX);
		sscanf(linea, "%d", &opcion);
 
		switch (opcion) {
 
			case 1:
				/* Insertar cliente */
				InsertarEnBinario();
				break;
 
			case 2:
				/* Mostrar listado clientes */
				ListadoDeArchivoBinario();
				break;
			case 3:
				/* Buscar cliente */
                BuscarEnBinario();
				break;
			case 4:
				/* Modificar cliente */
				ModificarEnArchivoBinario();
				break;
			case 5:
				/* Eliminar cliente */
				EliminarEnBinario();
				break;
			case 6:
				/* Tasa Bs */
				GuardarEnBinarioTasa();
				break;
			case 7:
			    /*Salir*/
				repite = 0;
				break;
		}
	} while (repite);
}
int leercadena(char *cad, int n)
{
	int i, c;
	c = getchar();
	if (c == EOF) {
		cad[0] = '\0';
		return 0;
	}
	if (c == '\n') {
		i = 0;
	} else {
		cad[0] = c;
		i = 1;
	}
	for (; i < n - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
		cad[i] = c;
	}
	cad[i] = '\0';
	if (c != '\n' && c != EOF) 
		while ((c = getchar()) != '\n' && c != EOF);
	return 1;
}
void Titulo()
{
	int i;
	printf("\n   ================================================================================\n\n");

	printf("\t\t\t     Control de Prestamos \n");
	printf("\t\t\t     Bodega Sra. Doriana\n");
	printf("\t\t   Copyright UNEFA 2024 | Estudiantes UNEFA \n\n");

	printf("   ================================================================================\n\n");
 
	i = 0;
	putchar('\n');
	printf("     ");
	for (; i < 76; i++) {
		putchar('-');
	}
	printf("\n");
}
void InsertarEnBinario()
{
	Deudas deuda;
	int codigodeuda = 0;
	char repite = 1;
	char respuesta[MAX];
 
	do {
		system(CLEAR);
		Titulo();
		printf("\n\t\t\t==> REGISTRAR CLIENTES <==\n");
 
		/* cedula del cliente a insertar */
		printf("\n\tCedula del cliente: ");
		leercadena(linea, MAX);
		sscanf(linea, "%d", &codigodeuda);
 
		/* Se verifica que el cliente no exista en el archivo binario */
		if (!ExisteCliente(codigodeuda, &deuda)) {
 
			deuda.cedula = codigodeuda;
 
			/* Se piden los demas datos  a insertar */
			printf("\tNombres del cliente: ");
			leercadena(deuda.nombre, MAX);
 			
 			printf("\tApellidos del cliente: ");
			leercadena(deuda.Apellido, MAX);
 			
 			printf("\tPrecio de la deuda del cliente: ");
			leercadena(linea, MAX);
			sscanf(linea, "%f", &deuda.debe);

			printf("\tDescripcion del articulos en deuda: ");
			leercadena(deuda.descripcion, MAX);
 
			/* Se inserta el cliente en el archivo */
			if (InsertarCliente(deuda)) {
				printf("\n\tEl cliente fue registrado exitosamente.\n");
 
			} else {
				printf("\n\tOcurrio un error al intentar insertar el cliente\n");
				printf("\tIntentelo mas tarde\n");
			}
		} else {
			/* El cliente ya existe, no puede ser insertado. */
			printf("\n\tEl cliente de cedula %d ya existe.\n", codigodeuda);
		}
 
		printf("\n\tDesea seguir registrando clientes? [S/N]: ");
		leercadena(respuesta, MAX);
 
		if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
		}
 
	} while (repite);
}
char ExisteCliente(int cedulaCli, Deudas *cliente)
{
	FILE *archivo;
	char existe;
 
	/* Abrimos el archivo binario en modo lectura */
	archivo = fopen("registroClientes.dat", "rb");
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo binario, el valor de archivo es NULL */
		existe = 0;
 
	} else {
		existe = 0;
 
		/* Se busca el cliente cuyo cedula coincida con codigocliente */
		fread(&(*cliente), sizeof(*cliente), 1, archivo);
		while (!feof(archivo)) {
			if ((*cliente).cedula == cedulaCli) {
				existe = 1;
				break;
			}
			fread(&(*cliente), sizeof(*cliente), 1, archivo);
		}
 
		/* Cerramos el archivo */
		fclose(archivo);
	}
 
	return existe;
}




















void GuardarEnBinarioTasa() {
    double valor;
    bool entradaValida = false;

    // Ciclo para pedir el valor hasta que sea correcto
    do {
		system(CLEAR);
		Titulo();
		printf("\n\t\t\t==> ACTUALIZAR TASA DEL DOLAR <==\n");
        cout << "\n\n\n\tIngresar valor del dolar: ";
        cin >> valor;

        // Verifica si la entrada es un valor numérico válido
        if (cin.good() && cin.peek() == '\n') {
            entradaValida = true;
        } else {
            // Limpia el estado de 'cin' y descarta la entrada hasta el final de la línea
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Por favor, marca un valor numérico correcto." << endl;
        }
    } while (!entradaValida);

    // Abre el archivo en modo binario
    ofstream miArchivo("datos.bin", ios::binary);
    if (miArchivo.is_open()) {
        miArchivo.write(reinterpret_cast<const char*>(&valor), sizeof(valor));
        miArchivo.close();
        cout << "Valor guardado en datos.bin" << endl;
    } else {
        cout << "Error al abrir el archivo" << endl;
    }
}

// Función para leer el valor desde el archivo binario
void LeerValorDesdeElBinario() {
    ifstream miArchivo("datos.bin", ios::binary);
    if (miArchivo.is_open()) {
        miArchivo.read(reinterpret_cast<char*>(&TasaDolar), sizeof(TasaDolar));
        miArchivo.close();
    } else {
    }
}














char InsertarCliente(Deudas cliente)
{
	FILE *archivo;
	char insercion;
 
	/* Abre el archivo para agregar datos al final */
	archivo = fopen("registroClientes.dat", "ab");	/* Añade datos al final */
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		insercion = 0;
 
	} else {
		fwrite(&cliente, sizeof(cliente), 1, archivo);
		insercion = 1;
 
		/* Cerramos el archivo */
		fclose(archivo);
	}
 
	return insercion;
}

void BuscarEnBinario()
{
	Deudas deudas;
	int codigodeudas;
	char repite = 1;
	char respuesta[MAX];
 
	do {
		system(CLEAR);
		Titulo();
		printf("\n\t\t\t==> BUSCAR CLIENTE POR CEDULA <==\n");
 
		/* cedula del cliente a buscar */
		printf("\n\tCedula del cliente: ");
		leercadena(linea, MAX);
		sscanf(linea, "%d", &codigodeudas);
 
		/* Se verifica que el cliente a buscar, exista */
		if (ExisteCliente(codigodeudas, &deudas)) {
			
        LeerValorDesdeElBinario();
 
			/* Se muestran los datos del cliente */
			printf("\n\tCedula Del Cliente: %d\n", deudas.cedula);
			printf("\tNombre del cliente: %s\n", deudas.nombre);			
			printf("\tApellido del cliente: %s \n", deudas.Apellido);
			printf("\tDeudas del cliente: $ %.1f\n", deudas.debe);
			printf("\tTasa Del Dolar: Bs %.2f\n", TasaDolar);
			printf("\tTotal a pagar en Bs: Bs %.2f\n", deudas.debe*TasaDolar);
			printf("\tDescripcion de deudas: %s\n", deudas.descripcion);
 
		} else {
			/* El cliente no existe */
			printf("\n\tEl cliente de cedula %d no existe.\n", codigodeudas);
		}
 
		printf("\n\tDesea seguir revisando algun cliente? [S/N]: ");
		leercadena(respuesta, MAX);
 
		if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
		}
 
	} while (repite);
}








char modificarDeuda(deudas cliente)
{
	FILE *archivo;
	char modifica;
	Deudas cliente2;
 
	/* Abre el archivo para lectura/escritura */
	archivo = fopen("RegistroClientes.dat", "rb+");
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		modifica = 0;
 
	} else {
		modifica = 0;
		fread(&cliente2, sizeof(cliente2), 1, archivo);
		while (!feof(archivo)) {
			if (cliente2.cedula == cliente.cedula) {
				fseek(archivo, ftell(archivo) - sizeof(cliente), SEEK_SET);
				fwrite(&cliente, sizeof(cliente), 1, archivo);
				modifica = 1;
				break;
			}
			fread(&cliente2, sizeof(cliente2), 1, archivo);
		}
 
		fclose(archivo);
	}
 
	/* Cierra el archivo */
	return modifica;
}
void ModificarEnArchivoBinario()
{
	Deudas deuda;
	int codigodeuda;
	char repite = 1;
	char respuesta[MAX];
 
	do {
		system(CLEAR);
		Titulo();
		printf("\n\t\t\t==> MODIFICAR DEUDA DE CLIENTE <==\n");
 
		/* Se pide el cedula del cliente a modificar */
		printf("\n\tCedula del cliente: ");
		leercadena(linea, MAX);
		sscanf(linea, "%d", &codigodeuda);
 
		/* Se verifica que el cliente a buscar exista */
		if (ExisteCliente(codigodeuda, &deuda)) {
 
			/* Se muestran los datos del cliente */
			printf("\n\tNombre del cliente : %s\n", deuda.nombre);
			printf("\tApellido del cliente : %s\n", deuda.Apellido);
			printf("\tPrecio del cliente ($): %.1f\n", deuda.debe);
			printf("\tDescripcion de la deuda: %S\n", deuda.descripcion);
 
			printf("\n\tElija los datos a modificar\n");
 
			/* Modificar el nombre del cliente */
			printf("\n\tDeuda del cliente actual : %.1f\n", deuda.debe);
			printf("\tDesea modificar la deuda del cliente? [S/N]: ");
			leercadena(respuesta, MAX);
			if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
				printf("\tNueva Deuda del cliente: ");
				leercadena(linea, MAX);
				sscanf(linea, "%f", &deuda.debe);
			}
 
			/* Modificar el costo del cliente */
			printf("\n\tDescripcion actual de la deuda: %s\n", deuda.descripcion);
			printf("\tDesea modificar la descripcion de la deuda? [S/N]: ");
			leercadena(respuesta, MAX);
			if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
				printf("\tNuevo costo del cliente: ");
				leercadena(deuda.descripcion, MAX);
			}
 
			printf("\n\tEsta seguro que desea modificar los datos de la deuda? [S/N]: ");
			leercadena(respuesta, MAX);
 
			if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
				/* Se modifica el cliente en el archivo */
				if (modificarDeuda(deuda)) {
					printf("\n\tDeuda del cliente %d, fue modificada correctamente\n",codigodeuda);
 
				} else {
					printf("\n\tOcurrio un error al intentar modificar la deuda\n");
					printf("\tIntentelo mas tarde\n");
				}
			}
		} else {
			/* El cliente no existe */
			printf("\n\tEl cliente de cedula %d no existe.\n", codigodeuda);
		}
 
		printf("\n\tDesea modificar algun otro cliente? [S/N]: ");
		leercadena(respuesta, MAX);
 
		if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
		}
 
	} while (repite);
}







char eliminarcliente(int codigoCedula)
{
	FILE *archivo;
	FILE *auxiliar;
	Deudas deuda;
	char elimina;
 
	/* Abre el archivo para leer */
	archivo = fopen("RegistroClientes.dat", "r+b");	/* Modo lectura/escritura. Si el archivo no existe, es creado */
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		elimina = 0;
 
	} else {
		/* Se busca el registro que se quiere borrar. Cuando se encuentra, se sitúa en esa posición mediante la 
		función fseek y luego se modifica el campo clave de ese registro mediante algún valor temporal, eso se logra 
		con fwrite. Hasta allí se ha logrado una eliminación LÓGICA. Porque el registro sigue ocupando espacio en el archivo físico */
		elimina = 0;
		fread(&deuda.cedula, sizeof(deuda), 1, archivo);
		while (!feof(archivo)) {
			if (deuda.cedula == codigoCedula) {
				fseek(archivo, ftell(archivo) - sizeof(deuda), SEEK_SET);
				deuda.cedula = VAL;
				fwrite(&deuda, sizeof(deuda), 1, archivo);
				elimina = 1;
				break;
			}
			fread(&deuda, sizeof(deuda), 1, archivo);
		}
 
		/* Cierra el archivo */
		fclose(archivo);
	}
 
	return elimina;
}
void EliminarEnBinario()
{
	Deudas deuda;
	int codigoCedula;
	char repite = 1;
	char respuesta[MAX];
 
	do {
		system(CLEAR);
		Titulo();
		printf("\n\t\t\t==> ELIMINAR CLIENTE POR CEDULA <==\n");
 
		/* Se pide el cedula del cliente a eliminar */
		printf("\n\tCedula del cliente: ");
		leercadena(linea, MAX);
		sscanf(linea, "%d", &codigoCedula);
 
		/* Se verifica que el cliente a buscar, exista */
		if (ExisteCliente(codigoCedula, &deuda)) {
			/* Se muestran los datos del cliente */
			printf("\n\tCedula del cliente: %d \n", deuda.cedula);
			printf("\tNombres del cliente: %s \n", deuda.nombre);		
			printf("\tApellidos del cliente: %s \n", deuda.Apellido);			
			printf("\tDeuda del cliente: %.1f $\n", deuda.debe);
			printf("\tDescripcion de deuda: %s \n", deuda.descripcion);
 
			printf("\n\tSeguro que desea eliminar este cliente? [S/N]: ");
			leercadena(respuesta, MAX);
			if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
				if (eliminarcliente(codigoCedula)) {
					printf("\n\tEl cliente por cedula: %d , fue eliminado satisfactoriamente.\n", codigoCedula);
				} else {
					printf("\n\tEl cliente no pudo ser eliminado\n");
				}
			}
 
		} else {
			/* El cliente no existe */
			printf("\n\tLa cedula %d no existe.\n", codigoCedula);
		}
 
		printf("\n\tDesea eliminar otro cliente? [S/N]: ");
		leercadena(respuesta, MAX);
 
		if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
			repite = 0;
		}
 
	} while (repite);
}








void ListadoDeArchivoBinario()
{
	Deudas *deudas;
	int numeroClientes;
	int i;
	float DeudaTotal;
	int cantidadTotal;
	char respuesta[MAX];
 
	system(CLEAR);
	Titulo();
	deudas = obtenerClientes(&numeroClientes); /* Retorna un vector dinamico de los clientes */
 
	if (numeroClientes == 0) {
		printf("\n\tEl archivo esta vacio!!\n");
		getchar();
 
	} else {
		printf("\n\t\t    ==> LISTADO DE CLIENTES REGISTRADOS <==\n");
		printf(" ----------------------------------------------------------------------------------------------------------------\n");
		printf("%8s\t%s%22s%29s%21s\n", "CEDULA", "NOMBRE","APELLIDO", "DEUDA $", "DESCRIPCION");
		printf(" ----------------------------------------------------------------------------------------------------------------\n");
 
		/* Se recorre el vector dinamico de los clientes */
		DeudaTotal = 0;
		cantidadTotal = 0;
		for (i = 0; i < numeroClientes; i++) {
			if (deudas[i].cedula != VAL) {
				printf("%7d \t%-20.20s%-20.25s%15.1f%17.40s\n", deudas[i].cedula, deudas[i].nombre, deudas[i].Apellido, deudas[i].debe, deudas[i].descripcion);
				DeudaTotal += deudas[i].debe;
			}
		}
		printf(" ----------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t      DEUDA TOTAL: %15.1f\n", DeudaTotal);
 
		printf("\n\tDesea guardar el reporte en un archivo de texto? [S/N]: ");
		leercadena(respuesta, MAX);
 		if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
			if (guardarReporte()) {
				printf("\n\tEl reporte fue guardado con exito\n");
			} else {
				printf("\n\tOcurrio un error al guardar el reporte\n");
			}
 
			getchar();
		}

	}
}


Deudas *obtenerClientes(int *n)
{
	FILE *archivo;
	Deudas deuda;
	Deudas *deudas; /* Vector dinamico de clientes */
	int i;
 
	/* Abre el archivo en modo lectura */
	archivo = fopen("RegistroClientes.dat", "rb");
 
	if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
		*n = 0; /* No se pudo abrir. Se considera n  */
		deudas = NULL;
 
	} else {
 
		fseek(archivo, 0, SEEK_END); /* Posiciona el cursor al final del archivo */
		*n = ftell(archivo) / sizeof(deuda); /* # de clientes almacenados en el archivo. (# de registros) */
		deudas = (Deudas *)malloc((*n) * sizeof(Deudas)); /* Se reserva memoria para todos los clientes almacenados en el archivo binario */
 
		/* Se recorre el archivo secuencialmente */
		fseek(archivo, 0, SEEK_SET); /* Posiciona el cursor al principio del archivo */
		fread(&deuda, sizeof(deuda), 1, archivo);
		i = 0;
		while (!feof(archivo)) {
			deudas[i++] = deuda;
			fread(&deuda, sizeof(deuda), 1, archivo);
		}
 
		/* Cerramos el archivo */
		fclose(archivo);
	}
 
	return deudas;
}


char guardarReporte()
{
	FILE *reportes;
	char guardado;
	Deudas *deudas;
	int numeroClientes;
	int i;
	float DeudaTotal;
	int cantidadTotal;
 
	deudas = obtenerClientes(&numeroClientes); /* Retorna un vector dinamico de clientes */
 
	if (numeroClientes == 0) {
		guardado = 0;
 
	} else {
		/* Abre el archivo en modo texto para escritura */
		reportes = fopen("reporte.txt", "w");
 
		if (reportes == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
			guardado = 0;
 
		} else {
		fprintf(reportes,"\n\t\t    ==> LISTADO DE DEUDAS DE CLIENTES <==\n");
		fprintf(reportes," ----------------------------------------------------------------------------------------------------------------\n");
		fprintf(reportes,"%8s\t%s%22s%29s%21s\n", "CEDULA", "NOMBRE","APELLIDO", "DEUDA $", "DESCRIPCION");
		fprintf(reportes," ----------------------------------------------------------------------------------------------------------------\n");
 
		/* Se recorre el vector dinamico de los clientes */
		DeudaTotal = 0;
		cantidadTotal = 0;
		for (i = 0; i < numeroClientes; i++) {
			if (deudas[i].cedula != VAL) {
				fprintf(reportes,"%7d \t%-20.20s%-20.25s%15.1f%17.40s\n", deudas[i].cedula, deudas[i].nombre, deudas[i].Apellido, deudas[i].debe, deudas[i].descripcion);
				DeudaTotal += deudas[i].debe;
			}
		}
		fprintf(reportes," ----------------------------------------------------------------------------------------------------------------\n");
		fprintf(reportes,"\t\t\t\t      DEUDA TOTAL: %15.1f\n", DeudaTotal);
 
			guardado = 1;
 
			/* Cierra el archivo */
			fclose(reportes);
		}
	}
	
	free(deudas);
	deudas = NULL;
 
	return guardado;
}

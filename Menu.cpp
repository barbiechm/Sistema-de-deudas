#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#include <iostream>
#include <string>
#include <conio.h>
#include <map>
#include <vector>
using namespace std;

#define MAX 80

char linea[MAX];
int leercadena(char *cad, int n) {
  cin.getline(cad, n); // Utiliza getline para leer toda la línea
  return cin.good(); // Indica si la lectura fue exitosa
}


struct Cliente {
    string cedula;
    string nombre;
    string apellido;
    double deuda;
	string articulos;
};
vector<Cliente> clientes;
void RegistrarUsuario() {
    Cliente nuevoCliente;

    cout << "Ingresar la cedula del cliente: ";
    cin >> nuevoCliente.cedula;
    cout << "Ingresar el nombre del cliente: ";
    cin >> nuevoCliente.nombre;
    cout << "Ingresar el apellido del cliente: ";
    cin >> nuevoCliente.apellido;
    nuevoCliente.deuda = 0.0;
	nuevoCliente.articulos = " Sin Deuda ";
    clientes.push_back(nuevoCliente);
    cout << "Cliente agregado satisfactoriamente. \n";
    cout << "Presione cualquier tecla para continuar \n";
    getch();
}
void eliminarCliente() {
    string cedulaABuscar;
    cout << "Ingrese la cedula del cliente a eliminar: ";
    cin >> cedulaABuscar;
    for (auto i = clientes.begin(); i != clientes.end(); ++i) {
        if (i->cedula == cedulaABuscar) {
            clientes.erase(i);
            cout << "Cliente eliminado exitosamente." << endl;
			getch();
            return;
        }
    }
    cout << "No se encontro un cliente con esa cedula." << endl;
    cout << "Presione ENTER para continuar" << endl;
    getch();
}
void agregarDeuda() {
    string cedulaABuscar;
    double montoDeuda;
	string Articulo;
    int nada;
    cout << "Ingrese la cedula del cliente al que se le va a agregar deuda: ";
    cin >> cedulaABuscar;
    for (auto& cliente : clientes) {
        if (cliente.cedula == cedulaABuscar) {
            cout << "Ingresar descripcion de articulo: ";
            cin >> Articulo;
			cout << "Ingresar monto de deudas: ";
            cin >> montoDeuda;
            cliente.deuda += montoDeuda;
			cliente.articulos = Articulo;
            cout << "Deuda agregada exitosamente." << endl;
            return;
        }
    }
    cout << "No se encontro un cliente con esa cedula." << endl;
    cout << "Presione ENTER para continuar" << endl;
    cin >> nada;
}
void consultarDeuda() {
    string cedulaABuscar;
    cout << "Ingresar la cedula del usuario a consultar su Deuda : ";
    cin >> cedulaABuscar;
    for (const auto& cliente : clientes) {
        if (cliente.cedula == cedulaABuscar) {
            cout << "La deuda del cliente " << cliente.nombre << " " << cliente.apellido << " es: " << cliente.deuda << "$" << endl<< "Articulos en Deuda : " << cliente.articulos << endl;
            getch();
            return;
        }
    }
    cout << "No se encontro un cliente con esa cedula." << endl;
    cout << "Presione cualquier tecla para continuar" << endl;
    getch();
}

void mostrarClientes() {
    cout << "Lista de clientes y sus deudas:" << endl;
        for (const auto& cliente : clientes) {
            cout << "Cedula: " << cliente.cedula << ", Nombre: " << cliente.nombre << " " << cliente.apellido << ", Deuda: " << cliente.deuda << "$" <<endl;
        }
    cout << "Presione ENTER para continuar" << endl;
    getch();
}
void PagarDeuda() {
    string cedulaABuscar;
    double montoAbono;
    string ArticulosDeuda;
    cout << "Ingrese la cedula del cliente al que se le va a abonar deuda: ";
    cin >> cedulaABuscar;
    for (auto& cliente : clientes) {
        if (cliente.cedula == cedulaABuscar) {
            cout << "Ingrese el monto del abono: ";
            cin >> montoAbono;
            if (montoAbono > cliente.deuda) {
                cout << "El monto del pago no puede ser mayor a la deuda del cliente." << endl;
                return;
            }
            cliente.deuda -= montoAbono;
            cout << "Actualizar deuda de articulos : ";
            cin >> ArticulosDeuda;
            cliente.articulos = ArticulosDeuda;
            cout << "Pago realizado de manera Exitosa." << endl;
            getch();
            return;
        }
    }
    cout << "No se encontro un cliente con esa cedula." << endl;
    cout << "Presione ENTER para continuar" << endl;
    getch();
}
void espacio(int cantidadEspacios, char caracter = ' ') {
    for (int i = 0; i < cantidadEspacios; i++) {
        cout << caracter;
    }
}
void titulo (string title)
{
    int i;
    int val;
    val = title.length();
    val = val + 20;
    for(i=0; i <= val; i++)
    {
        cout <<"-";
    }
    cout << "\n \n";
         for (i = 0; i <= val; i++) {
        espacio(2); // Imprime 5 espacios
        if (i == 5) {
            cout << title << "\n\n\n";
            espacio(5);
            cout << "1 - Agregar Cliente. \n\n";
            espacio(5);
            cout << "2 - Eliminar Cliente. \n\n";
            espacio(5);
            cout << "3 - Anadir deuda a cliente. \n\n";
            espacio(5);
            cout << "4 - Pagar deuda de cliente. \n\n";
            espacio(5);
            cout << "5 - Mostrar Lista de clientes. \n\n";
            espacio(5);
            cout << "6 - Mostrar deudas de clientes. \n\n";
            espacio(5);
            cout << "7 - Salida. \n\n";
        }
    }
    cout << "\n \n";
        for(i=0; i <= val; i++)
    {
        cout <<"-";
    }
    cout << "\n \n";
};


int leercadena(char *cad, int n)
{
	int m, c;
	c = getchar();
	if (c == EOF) {
		cad[0] = '\0';
		return 0;
	}
	if (c == '\n') {
		m = 0;
	} else {
		cad[0] = c;
		m = 1;
	}
	for (; m < n - 1 && (c = getchar()) != EOF && c != '\n'; m++) {
		cad[m] = c;
	}
	cad[m] = '\0';
	if (c != '\n' && c != EOF) 
		while ((c = getchar()) != '\n' && c != EOF);
	return 1;
}










main()
{
	int desi;
	    do {
		system("cls");
        titulo(" LISTADO DE OPCIONES ");
        leercadena(linea, MAX);
		sscanf(linea, "%d", &desi);

        switch (desi) {
        case 1:
		RegistrarUsuario();
            break;
        case 2:
        eliminarCliente();
            break;
        case 3:
        agregarDeuda();
            break;
        case 4:
        PagarDeuda();
            break;
        case 5:
        mostrarClientes();
            break;
        case 6:
        consultarDeuda();
            break;
        case 7:
            cout <<"";
            break;
        default:
            cout << "Opcion incorrecta, colocar valor correcto." << endl;
			getch();
            break;
        }
    } while (desi != 7);
    cout << "Presione cualquier caracter para cerrar el programa" << endl;
    getch();
    return 0;
}

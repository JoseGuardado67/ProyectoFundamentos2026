#include <iostream>
#include <vector> //un vector es mas eficiente que un arreglo, pues un vector no tiene limite
#include <fstream>
#include <string>
using namespace std;

string usuarioadmin = "admin", contraadmin = "123";
string usuarioIntento, contraIntento;
int contador = 1;
bool regresarMenuPrincipal = false;
string archivoTiendaActiva = "";

struct producto
{
    string nombre;
    int diaExp;
    int mesExp;
    int anioExp;
    double precio;
    int cantidad;
    double precioOferta;
    bool tieneDescuento;
    float porcentaje;
    double ahorro;
};

void menuPrincipal(int &opcionPrincipal)//jose
{
    cout << "\n===Bienvenido al sistema de comida universitaria===\n";
    cout << "1. Entrar como Dueno del local\n";
    cout << "2. Entrar como Cliente\n";
    cout << "3. Salir del juego\n";
    cout << "Opcion: ";
    cin >> opcionPrincipal;
}

void menuDueno(int &opcionDueno)//jose
{
    cout << "\n============ Menu del Dueno =============\n";
    cout << "1. Agregar productos\n";
    cout << "2. Ver inventario\n";
    cout << "3. Modificar algun elemento del inventario\n";
    cout << "4. Descuentos.\n";
    cout << "5. Volver al menu principal\n";
    cout << "Opcion: ";
    cin >> opcionDueno;
}


producto agregarProducto(vector<producto> &inventario)//jose
{
    int opSeguir = 0;
    producto a;

    while (opSeguir != 2)
    {

        cout << "Ingrese nombre del producto: ";
        getline(cin >> ws, a.nombre);

        
        cout << "Ingrese fecha de vencimiento (Dia, Mes, Anio): ";
        cin >> a.diaExp >> a.mesExp >> a.anioExp;

        cout << "Ingrese precio del producto: ";
        cin >> a.precio;
        cout << "Ingrese la cantidad disponible del producto: ";
        cin >> a.cantidad;

        a.precioOferta = a.precio;
        a.tieneDescuento = false;
        a.porcentaje = 0.0;
        a.ahorro = 0.0;

        // linea 77 sirve para guardar lo qu epreviamente ingreso la persona antes de esto
        inventario.push_back(a);
        cout << "Producto agregado exitosamente!\n";

    
        cout << "\n Desea agregar otro producto? \n";
        cout << "1. Si\n";
        cout << "2. No\n";
        cout << "Opcion: ";
        cin >> opSeguir;

        while (opSeguir <= 0 || opSeguir > 2)
        {
            cout << "\nERROR elija una opcion, pulse 2 para regresar al menu dueno\n";

            cout << "\n Desea agregar otro producto? \n";
            cout << "1. Si\n";
            cout << "2. No\n";
            cout << "Opcion: ";
            cin >> opSeguir;
        }

    }
    cout<<"Regresando al menu de dueno...";
    return a;
}

// const Si por error dentro de esta función intentas borrar un producto o cambiar un precio, el compilador te dará un error y no te dejará correr el programa.
void mostrarInventario(const vector<producto> &inventario)//walter
{
    cout << "==========================Inventario actual==========================\n";
    if (inventario.empty())
    {
        cout << "El inventario esta vacio.\n";
    }
    else
    {
        for (int i = 0; i < inventario.size(); i++)
        {
            cout << i + 1 << ". Nombre: " << inventario[i].nombre;

            // Si no, muestra el precio normal de siempre
            cout << " || Precio: $" << inventario[i].precio;

            cout << " || Vence: " << inventario[i].diaExp << "-" << inventario[i].mesExp << "-" << inventario[i].anioExp
                 << " || Stock: " << inventario[i].cantidad;

            if (inventario[i].tieneDescuento)
            {
                cout << " || >>> OFERTA " << inventario[i].porcentaje << " %!: $" << inventario[i].precioOferta << endl;
            }

            else
            {
                cout << endl;
            }
        }
    }
    cout << "===================================================================\n";
}



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

void Descuentos(vector<producto> &inventario)//austin
{
    int opciondescuentos;
    int elemento;
    float porcentaje;
    bool tieneDescuento = false;

    cout << "\n--Selecione una opcion.\n";
    cout << "1. Ingresar Promocion.\n";
    cout << "2. Eliminar una Promocion.\n";
    cout << "3. Regresar al menu anterio.\n";
    cout << "Opcion: ";
    cin >> opciondescuentos;

    if (opciondescuentos == 1)
    {
        if (inventario.empty())
        {
            cout << "No hay productos a los cuales se les pueda aplicar un descuento.";
        }

        else
        {
            mostrarInventario(inventario);

            cout << "Ingrese el producto al cual desea aplicarle un descuento: ";
            cin >> elemento;
            elemento--;

            if (elemento >= 0 && elemento < inventario.size())
            {
                cout << "Ingrese el porcentaje de descuento que desea aplicar a " << inventario[elemento].nombre << ": " << endl;
                cin >> porcentaje;
                inventario[elemento].porcentaje = porcentaje;

                // calcular el descuento
                inventario[elemento].precioOferta = inventario[elemento].precio * ((100.0 - porcentaje) / 100.0);
                inventario[elemento].tieneDescuento = true;

                cout << "Nuevo precio de oferta: $" << inventario[elemento].precioOferta << endl;
            }
            else
            {
                cout << "Numero de producto no valido.\n";
            }
        }
    }

    else if (opciondescuentos == 2)
    {
        mostrarInventario(inventario);

        cout << "\nIngrese el numero del producto al cual desea quitarle la promocion: ";
        cin >> elemento;
        elemento--;

        if (elemento >= 0 && elemento < inventario.size())
        {
            if (inventario[elemento].tieneDescuento)
            {
                //aqui se elimina el bool de descuento en el producto
                inventario[elemento].tieneDescuento = false;                 
                inventario[elemento].precioOferta = inventario[elemento].precio; // Restauro el precio a sin oferta
                cout << "----->El producto '" << inventario[elemento].nombre << "' volvio a su precio original de $" << inventario[elemento].precio << endl;
            }
            else
            {
                cout << "Este producto no tiene ningun descuento.\n";
            }
        }
        else
        {
            cout << "Numero de producto no valido.\n";
        }
    }

    else{
        cout<<"ERROR";
    }
}

void modificarProducto(vector<producto> &inventario)//jose
{

    mostrarInventario(inventario);

    int Opcioncambio;
    cout << "Ingrese el numero del producto que desea gestionar: ";
    cin >> Opcioncambio;
    Opcioncambio--;

    if (Opcioncambio >= 0 && Opcioncambio < inventario.size())
    {
        int opModificar = 0;

        do
        {
            cout << "\n---Gestionando: " << inventario[Opcioncambio].nombre << " ---\n";
            cout << "1. Modificar Nombre\n";
            cout << "2. Modificar Fecha de Caducidad\n";
            cout << "3. Modificar Precio\n";
            cout << "4. Modificar Cantidad (Stock)\n";
            cout << "5. ELIMINAR ESTE PRODUCTO\n";
            cout << "6. Volver atras\n";
            cout << "Opcion: ";
            cin >> opModificar;

            if (opModificar == 1)
            {
                cout << "Ingrese el nuevo nombre: ";
                getline(cin >> ws, inventario[Opcioncambio].nombre);
                cout << "Nombre actualizado!\n";
            }
            else if (opModificar == 2)
            {
                int dia, mes, anio;
                cout << "Ingrese la nueva fecha de caducidad: ";
                cin >> dia >> mes >> anio;

                cin >> inventario[Opcioncambio].diaExp >> inventario[Opcioncambio].mesExp >> inventario[Opcioncambio].anioExp;
                cout << "Fecha actualizada!\n";
            }
            else if (opModificar == 3)
            {
                // modificar precio si es que tiene descuento
                if (inventario[Opcioncambio].tieneDescuento)
                {
                    int QuiereDescuento = 0;

                    cout << "\n======================================================\n";
                    cout << "Este producto tiene un " << inventario[Opcioncambio].porcentaje << "% de descuento activo.\n";
                    cout << "======================================================\n";

                    cout << "Ingrese el nuevo precio: ";
                    cin >> inventario[Opcioncambio].precio;

                    while (QuiereDescuento != 2)
                    {
                
                        cout << "\nDesea que se le aplique el descuento antes declarado?: " << endl;
                        cout << "1. Si.\n";
                        cout << "2. No.\n";
                        cout << "Opcion: ";
                        cin >> QuiereDescuento;

                        if (QuiereDescuento == 1)
                        {
                            inventario[Opcioncambio].precioOferta = inventario[Opcioncambio].precio * ((100.0 - inventario[Opcioncambio].porcentaje) / 100.0);
                            cout << "Actualizando precio de " << inventario[Opcioncambio].nombre << "....\n";
                            cout << "Nuevo precio de oferta recalculado: $" << inventario[Opcioncambio].precioOferta << "\n";
                            break;
                        }

                        else if (QuiereDescuento == 2)
                        {
                            cout << "Eliminando descuento...\n";
                            inventario[Opcioncambio].tieneDescuento = false;                         // quito la oferta
                            inventario[Opcioncambio].precioOferta = inventario[Opcioncambio].precio; // Restauro el precio a sin oferta
                            cout << "----->El producto " << inventario[Opcioncambio].nombre << " actualizo el precio a $" << inventario[Opcioncambio].precio << endl;
                            break;
                        }

                        else
                        {
                            cout << "\nERROR Elija una opcion\n";
                        }
                    }
                }
                
                //y si no tiene descuento, solo actualizar el precio
                else
                {
                    cout << "Ingrese el nuevo precio: ";
                    cin >> inventario[Opcioncambio].precio;
                    cout << "Precio actualizado!\n";
                }
            }
            else if (opModificar == 4)
            {
                cout << "Ingrese la nueva cantidad: ";
                cin >> inventario[Opcioncambio].cantidad;
                cout << "Stock actualizado!\n";
            }
            else if (opModificar == 5)
            { 
                //podemos modificar esta parte, o directamente decir que es ia
                string seguro;
                cout << "Esta completamente seguro de eliminar '" << inventario[Opcioncambio].nombre << "'? (s= si/n= no): ";
                cin >> seguro;

                if (seguro == "s" || seguro == "S") //raro
                {
                    // Borramos el producto usando el iterador del vector
                    inventario.erase(inventario.begin() + Opcioncambio);
                    cout << "Producto eliminado exitosamente del inventario!\n";
                    break;
                }
                else
                {
                    cout << "Eliminacion cancelada.\n";
                }
            }
            else if (opModificar == 6)
            {
                cout << "Regresando al menu del dueno...\n";
            }
            else
            {
                cout << "Opcion no valida. Intente de nuevo.\n";
            }

        } while (opModificar != 6);
    }
    else
    {
        cout << "Numero de producto no valido.\n";
    }
}

void menuCliente(int &opcionCliente)//persona 1
{
    cout << "\n============Bienvenido al menu del Cliente=============\n";
    cout << "1. Agregar productos al carrito.\n";
    cout << "2. Ver carrito Y proceder con el pago.\n";
    cout << "3. Volver al menu principal.\n";
    cout << "Opcion: ";
    cin >> opcionCliente;
}




void verCarrito(const vector<producto> &carrito)//persona 1
{
    // 1. Declaramos la variable para el gran total aquí arriba.
    // Empezamos en 0.0 porque el carrito está limpio.
    float totalPagar = 0.0;

    if (carrito.empty())
    {
        cout << "======== El carrito se encuentra vacio ========\n";
    }
    else
    {
        cout << "==========Productos Agregados==========\n";
        for (int i = 0; i < carrito.size(); i++)
        {
            cout << i + 1 << ". " << carrito[i].nombre << " || ";
            cout << "Cantidad: " << carrito[i].cantidad;

            if (carrito[i].tieneDescuento)
            {
                cout << " || Precio con Oferta: $" << carrito[i].precioOferta << endl;

                totalPagar = totalPagar + (carrito[i].precioOferta * carrito[i].cantidad);
            }
            else
            {
                cout << " || Precio por unidad: $" << carrito[i].precio << endl;

                totalPagar = totalPagar + (carrito[i].precio * carrito[i].cantidad);
            }
        }

        cout << "=======================================\n";
        cout << " TOTAL A PAGAR: $" << totalPagar << "\n";
        cout << "=======================================\n";
    }
}
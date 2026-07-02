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

void guardarInventarioEnArchivo(const vector<producto> &inventario, string nombreArchivo)
{
    ofstream archivo(nombreArchivo);
    
    if (archivo.is_open())
    {
        // Guardamos el numero de productos en la primera linea
        archivo << inventario.size() << endl;

        for (int i = 0; i < inventario.size(); i++)
        {
            // LINEA 1: El nombre del producto va solo en su propia linea (soporta espacios)
            archivo << inventario[i].nombre << endl;
            
            // LINEA 2: Todos los numeros van abajo separados por un espacio simple
            archivo << inventario[i].diaExp << " "
                    << inventario[i].mesExp << " "
                    << inventario[i].anioExp << " "
                    << inventario[i].precio << " "
                    << inventario[i].cantidad << " "
                    << inventario[i].precioOferta << " "
                    << inventario[i].tieneDescuento << " "
                    << inventario[i].porcentaje << " "
                    << inventario[i].ahorro << endl;
        }
        archivo.close();
    }
}


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

producto agregarCarrito(vector<producto> &carrito, vector<producto> &inventario)//persona 2
{
    producto b;
    int Opcion = 0;
    int seleccion = 0;
    int agregados = 0;

    mostrarInventario(inventario);

    while (Opcion != 2)
    {
        bool encontrado = false;
        cout << "Que producto desea agregar?\n";
        cout << "Ingrese el numero del producto: \n";

        cin >> seleccion;

        for (int i = 0; i < inventario.size(); i++)
        {
            if (i == seleccion - 1)
            {

                cout << "Que tanta/s " << inventario[i].nombre << " desea llevar?: ";
                cin >> agregados;
                if (agregados <= 0 || agregados > inventario[i].cantidad)
                {
                    cout << "La cantidad ingresada no es valida\n";
                    cout << "Ingrese nuevamente la cantidad: \n";
                    cin >> agregados;
                }
                else
                {
                    inventario[i].cantidad -= agregados;

                    producto productoParaCarrito;
                    productoParaCarrito.nombre = inventario[i].nombre;
                    productoParaCarrito.diaExp = inventario[i].diaExp;
                    productoParaCarrito.mesExp = inventario[i].mesExp;
                    productoParaCarrito.anioExp = inventario[i].anioExp;
                    productoParaCarrito.cantidad = agregados;
                    productoParaCarrito.precio = inventario[i].precio;
                    productoParaCarrito.precioOferta = inventario[i].precioOferta;

                    // CORRECCIÓN AQUÍ: Guardar si tiene o no descuento en el carrito
                    productoParaCarrito.tieneDescuento = inventario[i].tieneDescuento;
                    productoParaCarrito.porcentaje = inventario[i].porcentaje;

                    bool existe = false;
                    for (int j = 0; j < carrito.size(); j++)
                    {
                        if (productoParaCarrito.nombre == carrito[j].nombre)
                        {
                            carrito[j].cantidad += productoParaCarrito.cantidad;
                            existe = true;
                            cout << "Se actualizo correctamente la cantidad de " << carrito[j].nombre << "!\n";
                            break;
                        }
                    }
                    if (!existe)
                    {
                        carrito.push_back(productoParaCarrito);
                        cout << "Opcion agregada correctamente\n";
                    }
                    encontrado = true;
                }
            }
        }

        if (encontrado == false)
        {
            cout << "No se encontro el producto deseado\n";
        }

        cout << "Desea volver a ingresar otro producto al carrito?\n";
        cout << "1. Si\n";
        cout << "2. No\n";

        cin >> Opcion;

        if (Opcion == 1)
        {
            mostrarInventario(inventario);
        }
        else if (Opcion != 1 && Opcion != 2)
        {
            cout << "ERROR: Opcion invalida\n";
            cout << "Regresando nuevamente al menu para seleccionar productos...\n";
        }
    }

    return b;
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

void modificarCarrito(vector<producto> &carrito, vector<producto> &inventario)//persona 2
{
    int opcion = 0;
    int cambio = 0;
    int seleccion = 0;
    int cantidad = 0;
    bool encontrado = false;
    string seguro;

    if (carrito.empty())
    {
        cout << "El carrito se encuentra vacio en este momento\n";
    }
    else
    {
        cout << "Ingrese el numero del producto que desea modificar: \n";
        cin >> opcion;

        opcion--; // Ajustamos al índice de C++ (0, 1, 2...)

        // Validamos que el número ingresado esté dentro del rango actual del carrito
        if (opcion >= 0 && opcion < carrito.size())
        {
            cout << "Del producto: " << carrito[opcion].nombre << " ¿que desea hacer?: \n";
            cout << "1. Cambiar el producto por otro\n";
            cout << "2. Eliminar producto\n";
            cout << "Opcion: ";
            cin >> cambio;

            if (cambio == 1)
            {
                mostrarInventario(inventario);

                cout << "¿Que producto desea agregar?: \n";
                cin >> seleccion;

                seleccion--; // Ajustamos al índice de C++

                // Validamos que la selección exista en el inventario global
                if (seleccion >= 0 && seleccion < inventario.size())
                {
                    cout << "¿Cuanto/s " << inventario[seleccion].nombre << " desea llevar?\n";
                    cin >> cantidad;

                    // Validamos si hay suficiente stock disponible en la tienda
                    if (cantidad > 0 && cantidad <= inventario[seleccion].cantidad)
                    {
                        // 1. Opcional pero recomendado: Devolvemos al inventario el stock del producto que vamos a quitar
                        for (int j = 0; j < inventario.size(); j++)
                        {
                            if (inventario[j].nombre == carrito[opcion].nombre)
                            {
                                inventario[j].cantidad += carrito[opcion].cantidad;
                                break;
                            }
                        }

                        // 2. Aplicamos tu idea: Sobreescribimos los datos del struct en la misma posición
                        carrito[opcion].nombre = inventario[seleccion].nombre;
                        carrito[opcion].diaExp = inventario[seleccion].diaExp;
                        carrito[opcion].mesExp = inventario[seleccion].mesExp;
                        carrito[opcion].anioExp = inventario[seleccion].anioExp;
                        carrito[opcion].cantidad = cantidad;

                        // Validamos si el nuevo producto seleccionado tiene descuento activo
                        if (inventario[seleccion].tieneDescuento)
                        {
                            carrito[opcion].precio = inventario[seleccion].precioOferta;
                        }
                        else
                        {
                            carrito[opcion].precio = inventario[seleccion].precio;
                        }

                        // 3. Descontamos las nuevas unidades del inventario global
                        inventario[seleccion].cantidad -= cantidad;

                        cout << "Producto reemplazado exitosamente en el carrito.\n";
                        encontrado = true;
                    }
                    else
                    {
                        cout << "Cantidad no valida o stock insuficiente en el inventario.\n";
                    }
                }

                if (!encontrado)
                {
                    cout << "No se pudo realizar el cambio de producto.\n";
                }
            }
            else if (cambio == 2)
            {
                cout << "Esta completamente seguro de eliminar '" << carrito[opcion].nombre << "' del carrito? (s/n): ";
                cin >> seguro;

                if (seguro == "s" || seguro == "S")
                {
                    // Devolvemos las unidades al inventario antes de borrar el elemento del carrito
                    for (int j = 0; j < inventario.size(); j++)
                    {
                        if (inventario[j].nombre == carrito[opcion].nombre)
                        {
                            inventario[j].cantidad += carrito[opcion].cantidad;
                            break;
                        }
                    }

                    // Borramos definitivamente la posición del carrito (el vector se encoge automáticamente)
                    carrito.erase(carrito.begin() + opcion);
                    cout << "Producto eliminado exitosamente del carrito.\n";
                }
                else
                {
                    cout << "Eliminacion cancelada.\n";
                }
            }
            else
            {
                cout << "ERROR: Opcion no valida.\n";
            }
        }
        else
        {
            cout << "Numero de producto no valido.\n";
        }
    }
}

void procederPago(vector<producto> &carrito, vector<producto> &inventario)//persona 1
{
    if (carrito.empty())
    {
        cout << "El carrito esta vacio. No hay nada que pagar.\n";
        return;
    }

    double totalNormal = 0;
    double totalPagar = 0;

    cout << "\n=============================================\n";
    cout << "                   RESUMEN                    \n";
    cout << "=============================================\n";

    // que es size t
    for (size_t i = 0; i < carrito.size(); i++)
    {
        double precioFinal;

        if (carrito[i].tieneDescuento == true)
        {

            precioFinal = carrito[i].precioOferta;
        }
        else
        {

            precioFinal = carrito[i].precio;
        }

        double subtotal = precioFinal * carrito[i].cantidad;

        totalNormal += (carrito[i].precio * carrito[i].cantidad);
        totalPagar += subtotal;

        cout << carrito[i].nombre << " x" << carrito[i].cantidad << endl;
        if (carrito[i].tieneDescuento)
        {
            cout << "  Original: $" << carrito[i].precio << " | Oferta!: $" << carrito[i].precioOferta << endl;
        }

        else
        {
            cout << "  Unitario: $" << carrito[i].precio << endl;
        }
        cout << "  Subtotal: $" << subtotal << "\n\n";
    }

    double totalAhorrado = totalNormal - totalPagar;

    cout << "---------------------------------------------\n";
    cout << "Total Sin Descuentos: $" << totalNormal << endl;
    cout << "Total Ahorrado:       $" << totalAhorrado << endl;
    cout << "TOTAL A PAGAR:        $" << totalPagar << endl;
    cout << "=============================================\n";

    double dineroIngresado = 0;
    cout << "Ingrese la cantidad de dinero con la que va a pagar: $";
    cin >> dineroIngresado;

    if (dineroIngresado >= totalPagar)
    {
        double cambio = dineroIngresado - totalPagar;
        cout << "\n¡Pago Exitoso!\n";
        cout << "Su cambio es: $" << cambio << "\n";

        ofstream factura("factura.txt");
        if (factura.is_open())
        {
            factura << "=============================================\n";
            factura << "       SISTEMA DE COMIDA UNIVERSITARIA       \n";
            factura << "              FACTURA DE COMPRA              \n";
            factura << "=============================================\n";
            for (size_t i = 0; i < carrito.size(); i++)
            {
                double pf; 

                if (carrito[i].tieneDescuento == true)
                {
                    pf = carrito[i].precioOferta;
                }
                else
                {
                    pf = carrito[i].precio; 
                }

                factura << carrito[i].nombre << " x" << carrito[i].cantidad << " -> Subtotal: $" << (pf * carrito[i].cantidad) << "\n";
            }
            factura << "---------------------------------------------\n";
            factura << "Total Sin Ofertas:    $" << totalNormal << "\n";
            factura << "Total Ahorrado:       $" << totalAhorrado << "\n";
            factura << "TOTAL NETO PAGADO:    $" << totalPagar << "\n";
            factura << "Dinero Recibido:      $" << dineroIngresado << "\n";
            factura << "Cambio Entregado:     $" << cambio << "\n";  //es necesario el cambio?
            factura << "=============================================\n";
            factura.close();
            cout << "Factura impresa con exito en 'factura.txt'!\n";
        }
        carrito.clear();
    }
    else
    {
        cout << "\n[ERROR]: Dinero insuficiente. Le faltan $" << (totalPagar - dineroIngresado) << ".\n";
    }
}

int main()
{
    int escoger = 0;
    vector<producto> inventario;
    vector<producto> carrito;

    //gestionInicialTiendas(inventario);

    while (escoger != 3)
    {
        menuPrincipal(escoger);

        if (escoger == 1)
        {
            int contador = 1; // vuelvo a declarar cada que quiera volver a entrar
            bool accesoConcedido = false;

            while (contador <= 5 && !accesoConcedido)
            {

                cout << "PorFavor, Inicie Sesion: " << endl;
                cout << "Ingrese el usuario: " << endl;
                cin >> usuarioIntento;

                cout << "Ingrese la contrasena: " << endl;
                cin >> contraIntento;

                if (usuarioIntento == usuarioadmin && contraIntento == contraadmin)
                {

                    cout << "\n************* Bienvenido ***********" << endl;
                    accesoConcedido = true;
                    int seleccionDueno = 0;

                    // Menu de dueño inicio
                    while (seleccionDueno != 5)
                    {
                        menuDueno(seleccionDueno);

                        if (seleccionDueno == 1)
                        {
                            agregarProducto(inventario);
                            //guardarInventarioEnArchivo(inventario, archivoTiendaActiva);
                        }
                        else if (seleccionDueno == 2)
                        {
                            mostrarInventario(inventario);
                        }

                        // Modificar inv
                        else if (seleccionDueno == 3)
                        {
                        
                            modificarProducto(inventario);
                            //guardarInventarioEnArchivo(inventario, archivoTiendaActiva);
                        }

                        else if (seleccionDueno == 4)
                        {

                            Descuentos(inventario);
                            //guardarInventarioEnArchivo(inventario, archivoTiendaActiva);
                        }
                    }
                    break;
                }

                else
                {
                    cout << "\nERROR: LAS CREDENCIALES NO COINCIDEN." << endl;
                    if (contador == 5)
                    {
                        cout << "Has llegado al limite maximo de intentos permitidos.\n";
                    }

                    // en esta parte voy a preguntarle a la parsona que si despues de 3 intentos ya no quiere seguir intentando y mejor quiere retirarse
                    // aparecera cada que la persona intente seguir iniciando sesion, esto puede modificarse para que solo aparezca cuando especificamente este en el intento 3

                    else if (contador >= 2)
                    {
                        int opEscape;
                        cout << "\n Desea Regresar al menu principal?\n";
                        cout << "1. Seguir intentando\n";
                        cout << "2. Regresar al menu principal\n";
                        cout << "Opcion: ";
                        cin >> opEscape;

                        if (opEscape == 2)
                        {
                            regresarMenuPrincipal = true;
                            cout << "Regresando al menu principal...\n";
                            break;
                        }
                    }
                    else
                    {
                        cout << "Intentelo de nuevo.\n";
                    }
                    contador++;
                }
            }
        }
        else if (escoger == 2)
        {
            int seleccionCliente = 0;

            while (seleccionCliente != 3)
            {
                menuCliente(seleccionCliente);

                if (seleccionCliente == 1)
                {
                    agregarCarrito(carrito, inventario);
                }
                else if (seleccionCliente == 2)
                {
                    int OpCarrito;
                    int OpModificar;
                    verCarrito(carrito);

                    cout << "Proceder con el pago?\n";
                    cout << "1. si\n";
                    cout << "2. no\n";
                    cout << "opcion: ";
                    cin >> OpCarrito;

                    switch (OpCarrito)
                    {
                    case 1:

                        procederPago(carrito, inventario);
                        break;

                    case 2:
                        cout << "Desea modificar el carrito?\n";
                        cout << "1. si." << endl;
                        cout << "2. No, regresar al menu cliente." << endl;
                        cin >> OpModificar;

                        if (OpModificar == 1)
                        {
                            modificarCarrito(carrito, inventario);
                        }
                        break;

                    default:
                        cout << "Regresando al menu cliente...";
                        break;
                    }
                }

                else
                {
                    cout << "Error seleccione una opcion.";
                }
            }
        }
    }

    cout << "Gracias por usarme!\n";
    return 0;
}
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include "Personaje.hpp"
#include "Ejercito.hpp"
#include "Batalla.hpp"

using namespace std;

int main()
{
    srand(time(nullptr)); // semilla para numeros aleatorios

    try
    {
        // Puede lanzar std::runtime_error si el archivo no existe
        vector<string> nombres = Ejercito::cargarNombres("names.txt");

        // El constructor de Ejercito puede lanzar std::invalid_argument
        // si maxUnidades <= 0
        Ejercito ejercitoNorte(6, "Ejercito del Norte");
        Ejercito ejercitoSur(6, "Ejercito del Sur");

        // Los constructores de Guerrero/Arquero/Mago (llamados dentro de
        // poblarAleatoriamente) pueden lanzar std::invalid_argument si
        // algun atributo generado quedara fuera de rango
        ejercitoNorte.poblarAleatoriamente(nombres);
        ejercitoSur.poblarAleatoriamente(nombres);

        cout << "== Composicion inicial ==" << endl;
        ejercitoNorte.mostrarComposicion();
        ejercitoNorte.listarElementos();

        ejercitoSur.mostrarComposicion();
        ejercitoSur.listarElementos();

        // El constructor de Batalla puede lanzar std::invalid_argument
        // si algun ejercito quedo vacio (por ejemplo, si names.txt no
        // tenia suficientes nombres para poblar ni un ejercito)
        Batalla batalla(ejercitoNorte, ejercitoSur);
        batalla.iniciar();
    }
    catch (const invalid_argument& e)
    {
        // Datos de entrada invalidos: algo que el programa recibio y no
        // deberia haber aceptado (ej. vida <= 0, maxUnidades <= 0)
        cerr << "Error de datos invalidos: " << e.what() << endl;
        return 1;
    }
    catch (const runtime_error& e)
    {
        // Fallo de algo externo al programa (ej. no se pudo abrir un archivo)
        cerr << "Error en tiempo de ejecucion: " << e.what() << endl;
        return 1;
    }
    catch (const exception& e)
    {
        // Cualquier otra excepcion estandar no prevista arriba
        cerr << "Error inesperado: " << e.what() << endl;
        return 1;
    }

    return 0;
}
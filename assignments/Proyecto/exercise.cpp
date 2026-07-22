#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Personaje.hpp"
#include "Ejercito.hpp"
#include "Batalla.hpp"

using namespace std;

int main()
{
    srand(time(nullptr)); // semilla para numeros aleatorios

    // Carga la lista de nombres una sola vez; se comparte entre ambos
    // ejercitos para que no se repitan nombres entre ellos.
    vector<string> nombres = Ejercito::cargarNombres("names.txt");

    Ejercito ejercitoNorte(6, "Ejercito del Norte");
    Ejercito ejercitoSur(6, "Ejercito del Sur");

    ejercitoNorte.poblarAleatoriamente(nombres);
    ejercitoSur.poblarAleatoriamente(nombres);

    cout << "== Composicion inicial ==" << endl;
    ejercitoNorte.mostrarComposicion();
    ejercitoNorte.listarElementos();

    ejercitoSur.mostrarComposicion();
    ejercitoSur.listarElementos();

    Batalla batalla(ejercitoNorte, ejercitoSur);
    batalla.iniciar();

    return 0;
}
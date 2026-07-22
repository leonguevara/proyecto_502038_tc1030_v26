#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Personaje.hpp"

using namespace std;

int main()
{
    srand(time(nullptr)); // semilla para numeros aleatorios

    Personaje p1("Thoren", 100, 20, 3);
    Personaje p2("Lyra", 90, 18, 4);

    cout << "Estado inicial:" << endl;
    p1.imprimir();
    p2.imprimir();

    cout << endl << "== Ronda de combate ==" << endl;
    p1.atacar(p2);
    p2.imprimir();

    p2.atacar(p1);
    p1.imprimir();

    return 0;
}
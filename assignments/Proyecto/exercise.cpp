#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Personaje.hpp"
#include "Guerrero.hpp"
#include "Arquero.hpp"
#include "Mago.hpp"

using namespace std;

int main()
{
    srand(time(nullptr)); // semilla para numeros aleatorios

    Guerrero guerrero("Thoren", 120, 20, 3, 40);
    Arquero arquero("Lyra", 90, 18, 4, 35.0f);
    Mago mago("Elowen", 80, 22, 3, 100);

    cout << "== Estado inicial ==" << endl;
    guerrero.imprimir();
    arquero.imprimir();
    mago.imprimir();

    cout << endl << "== Guerrero ataca a Arquero ==" << endl;
    guerrero.atacar(arquero);
    arquero.imprimir();

    cout << endl << "== Arquero ataca a Mago ==" << endl;
    arquero.atacar(mago);
    mago.imprimir();

    cout << endl << "== Mago ataca a Guerrero ==" << endl;
    mago.atacar(guerrero);
    guerrero.imprimir();

    return 0;
}
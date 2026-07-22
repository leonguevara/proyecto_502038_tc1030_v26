#include <iostream>
#include <vector>
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

    // Vector de apuntadores a la clase base (Personaje es abstracta,
    // asi que solo puede contener instancias de las clases derivadas)
    vector<Personaje*> combatientes;

    // Creacion dinamica: un objeto de cada clase derivada
    combatientes.push_back(new Guerrero("Thoren", 120, 20, 3, 40));
    combatientes.push_back(new Arquero("Lyra", 90, 18, 4, 35.0f));
    combatientes.push_back(new Mago("Elowen", 80, 22, 3, 100));

    cout << "== Estado inicial ==" << endl;
    for (Personaje* p : combatientes)
    {
        p->imprimir(); // polimorfismo: cada quien imprime lo suyo
    }

    cout << endl << "== Ronda de combate ==" << endl;
    // El primero ataca al segundo y al tercero (llamadas polimorficas:
    // internamente cada uno usa SU version de calculaAtaque/recibeAtaque)
    combatientes[0]->atacar(*combatientes[1]);
    combatientes[1]->imprimir();

    combatientes[0]->atacar(*combatientes[2]);
    combatientes[2]->imprimir();

    cout << endl << "== Segunda ronda (para forzar mas dano) ==" << endl;
    combatientes[1]->atacar(*combatientes[0]);
    combatientes[0]->imprimir();

    combatientes[2]->atacar(*combatientes[1]);
    combatientes[1]->imprimir();

    cout << endl << "== Prueba de la sobrecarga de operador << ==" << endl;
    // *combatientes[i] obtiene el objeto al que apunta el puntero
    cout << *combatientes[0] << endl;
    cout << *combatientes[1] << endl;
    cout << *combatientes[2] << endl;

    // Liberar la memoria reservada dinamicamente
    for (Personaje* p : combatientes)
    {
        delete p;
    }

    return 0;
}
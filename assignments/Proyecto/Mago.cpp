#include "Mago.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

Mago::Mago() : Personaje()
{
    mana = 100;
    yaRevivio = false;
}

Mago::Mago(string nombre, int vida, int ataque, int nivel, int mana)
    : Personaje(nombre, vida, ataque, nivel)
{
    this->mana = mana;
    yaRevivio = false;
}

int Mago::getMana() const { return mana; }
void Mago::setMana(int mana) { this->mana = mana; }

int Mago::calculaAtaque(Personaje& objetivo)
{
    int danioBase = Personaje::calculaAtaque(objetivo);

    if (mana > 0)
    {
        // A mas mana, mayor probabilidad de hechizo fuerte
        int probabilidad = mana / 2; // ej. mana=100 -> 50% de probabilidad
        int tiro = rand() % 100;

        if (tiro < probabilidad)
        {
            cout << "  >> ¡Hechizo fuerte!" << endl;
            danioBase *= 2;
            mana -= 20;
            if (mana < 0) mana = 0;
        }
    }

    return danioBase;
}

void Mago::recibeAtaque(int ptosAtaque)
{
    // Reduccion escalonada segun nivel y mana disponible (ejemplo del PDF)
    int danioFinal = ptosAtaque;

    if (getNivel() >= 4 && mana > 80)
        danioFinal = ptosAtaque / 3;
    else if (getNivel() >= 3 && mana > 85)
        danioFinal = ptosAtaque / 2;
    else if (getNivel() <= 2 && mana == 100)
        danioFinal = (ptosAtaque * 3) / 4;

    Personaje::recibeAtaque(danioFinal);

    // Despues de aplicar el dano, se evalua si debe revivir o si murio
    revive();
}

void Mago::atacar(Personaje& objetivo)
{
    // Reutiliza el flujo base
    Personaje::atacar(objetivo);

    // Si el objetivo murio en este ataque, el mago recupera algo de mana
    if (objetivo.getSalud() == 0 && mana < 100)
    {
        mana += 15;
        if (mana > 100) mana = 100;
        cout << "  >> El mago absorbe energia y recupera mana." << endl;
    }
}

void Mago::imprimir() const
{
    Personaje::imprimir();
    cout << "Clase: Mago | Mana: " << mana << endl;
}

void Mago::revive()
{
    if (getSalud() > 0) return; // sigue con vida, no hay nada que evaluar

    if (!yaRevivio && mana > 50)
    {
        yaRevivio = true;
        int vidaRecuperada = getVida() / 5; // 20% de la vida maxima
        setSalud(vidaRecuperada);
        mana -= 50; // el costo: gasta la mitad de su reserva de mana
        if (mana < 0) mana = 0;

        cout << "  >> ¡" << getNombre() << " revive gracias a su ultima reserva de mana! ("
             << vidaRecuperada << " HP)" << endl;
    }
    else
    {
        cout << "  >> " << getNombre() << " ha caido en batalla." << endl;
    }
}

ostream& Mago::mostrar(ostream& os) const
{
    Personaje::mostrar(os);
    os << " | Mana:" << mana;
    return os;
}
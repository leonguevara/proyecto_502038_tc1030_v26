#include "Guerrero.hpp"
#include <iostream>

using namespace std;

Guerrero::Guerrero() : Personaje()
{
    fuerza = 10;
    yaRevivio = false;
}

Guerrero::Guerrero(string nombre, int vida, int ataque, int nivel, int fuerza)
    : Personaje(nombre, vida, ataque, nivel)
{
    this->fuerza = fuerza;
    yaRevivio = false;
}

int Guerrero::getFuerza() const { return fuerza; }
void Guerrero::setFuerza(int fuerza) { this->fuerza = fuerza; }

int Guerrero::calculaAtaque(Personaje& objetivo)
{
    // Reutiliza el calculo base de Personaje y le suma un bono por fuerza
    int danioBase = Personaje::calculaAtaque(objetivo);
    int bono = fuerza / 5;
    return danioBase + bono;
}

void Guerrero::recibeAtaque(int ptosAtaque)
{
    // La fuerza actua como armadura: reduce el dano recibido (tope 60%)
    int reduccion = fuerza / 4;
    if (reduccion > 60) reduccion = 60;

    int danioFinal = ptosAtaque - (ptosAtaque * reduccion / 100);
    if (danioFinal < 0) danioFinal = 0;

    Personaje::recibeAtaque(danioFinal);

    // Despues de aplicar el dano, se evalua si debe revivir o si murio
    revive();
}

void Guerrero::imprimir() const
{
    Personaje::imprimir();
    cout << "Clase: Guerrero | Fuerza: " << fuerza << endl;
}

void Guerrero::revive()
{
    if (getSalud() > 0) return; // sigue con vida, no hay nada que evaluar

    if (!yaRevivio && fuerza >= 25)
    {
        yaRevivio = true;
        int vidaRecuperada = getVida() / 5; // 20% de la vida maxima
        setSalud(vidaRecuperada);
        fuerza /= 2; // el costo: pierde la mitad de su fuerza

        cout << "  >> ¡" << getNombre() << " se levanta con furia de batalla! ("
             << vidaRecuperada << " HP)" << endl;
    }
    else
    {
        cout << "  >> " << getNombre() << " ha caido en batalla." << endl;
    }
}

ostream& Guerrero::mostrar(ostream& os) const
{
    Personaje::mostrar(os);
    os << " | Fuerza:" << fuerza;
    return os;
}
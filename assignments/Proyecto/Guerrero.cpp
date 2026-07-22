#include "Guerrero.hpp"
#include <iostream>

using namespace std;

Guerrero::Guerrero() : Personaje()
{
    fuerza = 10;
}

Guerrero::Guerrero(string nombre, int vida, int ataque, int nivel, int fuerza)
    : Personaje(nombre, vida, ataque, nivel)
{
    this->fuerza = fuerza;
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
}

void Guerrero::imprimir() const
{
    Personaje::imprimir();
    cout << "Clase: Guerrero | Fuerza: " << fuerza << endl;
}

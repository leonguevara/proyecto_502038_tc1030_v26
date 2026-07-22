#include "Arquero.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

Arquero::Arquero() : Personaje()
{
    precision = 20.0f;
    yaRevivio = false;
}

Arquero::Arquero(string nombre, int vida, int ataque, int nivel, float precision)
    : Personaje(nombre, vida, ataque, nivel)
{
    this->precision = precision;
    yaRevivio = false;
}

float Arquero::getPrecision() const { return precision; }
void Arquero::setPrecision(float precision) { this->precision = precision; }

int Arquero::calculaAtaque(Personaje& objetivo)
{
    int danioBase = Personaje::calculaAtaque(objetivo);

    float tiro = rand() % 100; // 0-99
    bool critico = tiro < precision;

    if (critico)
    {
        cout << "  >> ¡Golpe critico!" << endl;
        danioBase = static_cast<int>(danioBase * 1.5f);
    }

    return danioBase;
}

void Arquero::recibeAtaque(int ptosAtaque)
{
    float tiro = rand() % 100;
    bool esquiva = tiro < (precision / 2.0f);

    int danioFinal = ptosAtaque;
    if (esquiva)
    {
        cout << "  >> ¡El arquero esquiva parte del ataque!" << endl;
        danioFinal = ptosAtaque / 2;
    }

    Personaje::recibeAtaque(danioFinal);

    // Despues de aplicar el dano, se evalua si debe revivir o si murio
    revive();
}

void Arquero::imprimir() const
{
    Personaje::imprimir();
    cout << "Clase: Arquero | Precision: " << precision << "%" << endl;
}

void Arquero::revive()
{
    if (getSalud() > 0) return; // sigue con vida, no hay nada que evaluar

    if (!yaRevivio && precision >= 30.0f)
    {
        yaRevivio = true;
        int vidaRecuperada = getVida() / 5; // 20% de la vida maxima
        setSalud(vidaRecuperada);
        precision /= 2.0f; // el costo: pierde la mitad de su precision

        cout << "  >> ¡" << getNombre() << " esquiva la muerte por pura precision! ("
             << vidaRecuperada << " HP)" << endl;
    }
    else
    {
        cout << "  >> " << getNombre() << " ha caido en batalla." << endl;
    }
}

ostream& Arquero::mostrar(ostream& os) const
{
    Personaje::mostrar(os);
    os << " | Precision:" << precision << "%";
    return os;
}
#pragma once
#include "Personaje.hpp"

// Arquero: unidad de ataque a distancia. Su precision le da probabilidad
// de golpes criticos, y tambien de esquivar ataques enemigos.
class Arquero : public Personaje
{
private:
    float precision; // 0.0 a 100.0, probabilidad en %

public:
    Arquero();
    Arquero(std::string nombre, int vida, int ataque, int nivel, float precision);

    float getPrecision() const;
    void setPrecision(float precision);

    // Con probabilidad = precision, el ataque es critico (x1.5 dano)
    int calculaAtaque(Personaje& objetivo) override;

    // Con probabilidad = precision/2, esquiva y solo recibe la mitad del dano
    void recibeAtaque(int ptosAtaque) override;

    void imprimir() const override;
};

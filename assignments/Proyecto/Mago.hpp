#pragma once
#include "Personaje.hpp"

// Mago: unidad magica. Su mana puede potenciar su ataque (hechizo fuerte)
// y tambien reducir el dano que recibe, pero el mana se va gastando.
class Mago : public Personaje
{
private:
    int mana; // 0 a 100

public:
    Mago();
    Mago(std::string nombre, int vida, int ataque, int nivel, int mana);

    int getMana() const;
    void setMana(int mana);

    // Con probabilidad segun el mana, lanza un hechizo fuerte (x2 dano)
    // y consume mana al usarlo
    int calculaAtaque(Personaje& objetivo) override;

    // Reduce el dano recibido de forma escalonada segun nivel + mana
    void recibeAtaque(int ptosAtaque) override;

    // Sobreescribe atacar para recuperar algo de mana si el objetivo muere
    void atacar(Personaje& objetivo) override;

    void imprimir() const override;
};

#pragma once
#include "Personaje.hpp"

// Mago: unidad magica. Su mana puede potenciar su ataque (hechizo fuerte)
// y tambien reducir el dano que recibe, pero el mana se va gastando.
class Mago : public Personaje
{
private:
    int mana; // 0 a 100
    bool yaRevivio; // controla que revivir por mana solo pase una vez

public:
    Mago();

    // Ademas de lo que valida Personaje, lanza std::invalid_argument si
    // mana esta fuera del rango 0 a 100.
    Mago(std::string nombre, int vida, int ataque, int nivel, int mana);

    int getMana() const;
    void setMana(int mana);

    // Con probabilidad segun el mana, lanza un hechizo fuerte (x2 dano)
    // y consume mana al usarlo
    int calculaAtaque(Personaje& objetivo) override;

    // Reduce el dano recibido de forma escalonada segun nivel + mana;
    // si la salud llega a 0, se evalua revive()
    void recibeAtaque(int ptosAtaque) override;

    // Sobreescribe atacar para recuperar algo de mana si el objetivo muere
    void atacar(Personaje& objetivo) override;

    void imprimir() const override;

    // Si tiene mana > 50 y no ha revivido antes, usa su ultima reserva
    // de energia magica para levantarse con algo de vida
    void revive() override;

    // Agrega el mana a la representacion usada por operator<<
    std::ostream& mostrar(std::ostream& os) const override;
};
#pragma once
#include "Personaje.hpp"

// Arquero: unidad de ataque a distancia. Su precision le da probabilidad
// de golpes criticos, y tambien de esquivar ataques enemigos.
class Arquero : public Personaje
{
private:
    float precision; // 0.0 a 100.0, probabilidad en %
    bool yaRevivio;  // controla que revivir por precision solo pase una vez

public:
    Arquero();
    Arquero(std::string nombre, int vida, int ataque, int nivel, float precision);

    float getPrecision() const;
    void setPrecision(float precision);

    // Con probabilidad = precision, el ataque es critico (x1.5 dano)
    int calculaAtaque(Personaje& objetivo) override;

    // Con probabilidad = precision/2, esquiva y solo recibe la mitad del dano;
    // si la salud llega a 0, se evalua revive()
    void recibeAtaque(int ptosAtaque) override;

    void imprimir() const override;

    // Si tiene precision >= 30 y no ha revivido antes, esquiva la muerte
    // y se levanta con algo de vida, a cambio de perder la mitad de su precision
    void revive() override;

    // Agrega la precision a la representacion usada por operator<<
    std::ostream& mostrar(std::ostream& os) const override;
};
#pragma once
#include "Personaje.hpp"

// Guerrero: unidad cuerpo a cuerpo. Su fuerza aumenta su daño de ataque
// y reduce el daño que recibe (actúa como una especie de armadura).
class Guerrero : public Personaje
{
private:
    int fuerza;
    bool yaRevivio; // controla que "furia de batalla" solo se use una vez

public:
    Guerrero();
    Guerrero(std::string nombre, int vida, int ataque, int nivel, int fuerza);

    int getFuerza() const;
    void setFuerza(int fuerza);

    // Sobreescribe el ataque base y le suma un bonus segun la fuerza
    int calculaAtaque(Personaje& objetivo) override;

    // Sobreescribe la recepcion de dano: la fuerza reduce el dano recibido,
    // y si la salud llega a 0, se evalua revive()
    void recibeAtaque(int ptosAtaque) override;

    // Sobreescribe la impresion para mostrar tambien la fuerza
    void imprimir() const override;

    // Si tiene fuerza >= 25 y no ha revivido antes, se levanta con algo
    // de vida a cambio de perder la mitad de su fuerza
    void revive() override;

    // Agrega la fuerza a la representacion usada por operator<<
    std::ostream& mostrar(std::ostream& os) const override;
};
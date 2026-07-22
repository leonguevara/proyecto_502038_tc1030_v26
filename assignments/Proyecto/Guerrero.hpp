#pragma once
#include "Personaje.hpp"

// Guerrero: unidad cuerpo a cuerpo. Su fuerza aumenta su daño de ataque
// y reduce el daño que recibe (actúa como una especie de armadura).
class Guerrero : public Personaje
{
private:
    int fuerza;

public:
    Guerrero();
    Guerrero(std::string nombre, int vida, int ataque, int nivel, int fuerza);

    int getFuerza() const;
    void setFuerza(int fuerza);

    // Sobreescribe el ataque base y le suma un bonus segun la fuerza
    int calculaAtaque(Personaje& objetivo) override;

    // Sobreescribe la recepcion de dano: la fuerza reduce el dano recibido
    void recibeAtaque(int ptosAtaque) override;

    // Sobreescribe la impresion para mostrar tambien la fuerza
    void imprimir() const override;
};

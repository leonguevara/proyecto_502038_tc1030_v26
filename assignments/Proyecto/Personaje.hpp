#pragma once
#include <string>

// Clase base para las unidades de combate del simulador de batallas.
// Guerrero, Arquero y Mago heredarán de esta clase (siguiente avance).
class Personaje
{
private:
    std::string nombre;   // atributo extra, útil para identificar al personaje
    int vida;             // puntos de vida MAXIMOS
    int salud;            // puntos de vida ACTUALES
    int ataque;           // puntos de ataque MAXIMOS
    int nivel;            // nivel del personaje

public:
    // Constructores
    Personaje();
    Personaje(std::string nombre, int vida, int ataque, int nivel);

    // Getters
    std::string getNombre() const;
    int getVida() const;
    int getSalud() const;
    int getAtaque() const;
    int getNivel() const;

    // Setters
    void setNombre(std::string nombre);
    void setVida(int vida);
    void setSalud(int salud);
    void setAtaque(int ataque);
    void setNivel(int nivel);

    // Calcula el % de salud actual (0-100) en base a vida y salud
    int porcentajeSalud() const;

    // Imprime una barra de 20 caracteres representando el % de salud
    void imprimeBarra() const;

    // Calcula cuántos puntos de daño se le harán a 'objetivo' según niveles
    int calculaAtaque(Personaje& objetivo);

    // Descuenta ptosAtaque a la salud actual, nunca queda negativa
    void recibeAtaque(int ptosAtaque);

    // Ataca a 'objetivo': calcula el daño y se lo aplica
    void atacar(Personaje& objetivo);

    // Imprime en pantalla los datos del personaje y su barra de vida
    void imprimir() const;
};
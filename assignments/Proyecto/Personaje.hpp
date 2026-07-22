#pragma once
#include <string>
#include <iostream>

// Clase base para las unidades de combate del simulador de batallas.
// Es abstracta: revive() es virtual puro, asi que no se puede instanciar
// directamente, solo a traves de sus clases derivadas (Guerrero, Arquero, Mago).
class Personaje
{
private:
    std::string nombre; // atributo extra, útil para identificar al personaje
    int vida;            // puntos de vida MAXIMOS
    int salud;            // puntos de vida ACTUALES
    int ataque;           // puntos de ataque MAXIMOS
    int nivel;            // nivel del personaje

public:
    // Constructores
    Personaje();
    Personaje(std::string nombre, int vida, int ataque, int nivel);

    // Destructor virtual: obligatorio al usar herencia con punteros a la base
    virtual ~Personaje() = default;

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
    virtual int calculaAtaque(Personaje& objetivo);

    // Descuenta ptosAtaque a la salud actual, nunca queda negativa
    virtual void recibeAtaque(int ptosAtaque);

    // Ataca a 'objetivo': calcula el daño y se lo aplica
    virtual void atacar(Personaje& objetivo);

    // Imprime en pantalla los datos del personaje y su barra de vida
    virtual void imprimir() const;

    // Virtual puro: si el personaje se queda en 0 de salud, cada clase
    // derivada decide (segun su atributo especial) si "revive" con algo
    // de vida o si se queda muerto. Al ser puro, Personaje es abstracta.
    virtual void revive() = 0;

    // Escribe una representacion breve del personaje en el stream 'os'.
    // Cada clase derivada la sobreescribe para agregar su atributo especial.
    // Se usa desde el operator<< sobrecargado para que funcione polimorficamente.
    virtual std::ostream& mostrar(std::ostream& os) const;

    // Sobrecarga del operador de flujo de salida: permite hacer "cout << personaje"
    // (o "cout << *punteroAPersonaje") y que se despliegue correctamente sin
    // importar la subclase real del objeto.
    friend std::ostream& operator<<(std::ostream& os, const Personaje& p);
};
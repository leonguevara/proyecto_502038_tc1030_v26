#include "Personaje.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

// --- Constructores ---

Personaje::Personaje()
{
    nombre = "Sin nombre";
    vida = 100;
    salud = vida;   // al crearse, la salud actual es igual a la vida maxima
    ataque = 10;
    nivel = 1;
}

Personaje::Personaje(string nombre, int vida, int ataque, int nivel)
{
    this->nombre = nombre;
    this->vida = vida;
    this->salud = vida; // arranca con salud al maximo
    this->ataque = ataque;
    this->nivel = nivel;
}

// --- Getters ---

string Personaje::getNombre() const { return nombre; }
int Personaje::getVida() const { return vida; }
int Personaje::getSalud() const { return salud; }
int Personaje::getAtaque() const { return ataque; }
int Personaje::getNivel() const { return nivel; }

// --- Setters ---

void Personaje::setNombre(string nombre) { this->nombre = nombre; }
void Personaje::setVida(int vida) { this->vida = vida; }
void Personaje::setSalud(int salud) { this->salud = salud; }
void Personaje::setAtaque(int ataque) { this->ataque = ataque; }
void Personaje::setNivel(int nivel) { this->nivel = nivel; }

// --- Metodos de comportamiento ---

int Personaje::porcentajeSalud() const
{
    if (vida <= 0) return 0; // evita division entre 0
    int porcentaje = (salud * 100) / vida;
    if (porcentaje < 0) porcentaje = 0;
    if (porcentaje > 100) porcentaje = 100;
    return porcentaje;
}

void Personaje::imprimeBarra() const
{
    int porcentaje = porcentajeSalud();
    int llenos = porcentaje / 5; // 20 caracteres -> cada uno vale 5%
    int vacios = 20 - llenos;

    cout << "[";
    for (int i = 0; i < llenos; i++) cout << "%";
    for (int i = 0; i < vacios; i++) cout << "=";
    cout << "] " << porcentaje << "%" << endl;
}

int Personaje::calculaAtaque(Personaje& objetivo)
{
    int danio;
    if (objetivo.getNivel() > this->nivel)
    {
        // objetivo mas fuerte: solo ataco entre 1 y la mitad de mi ataque
        int mitad = ataque / 2;
        if (mitad < 1) mitad = 1;
        danio = 1 + (rand() % mitad);
    }
    else
    {
        // objetivo igual o mas debil: ataco entre la mitad y el total
        int mitad = ataque / 2;
        int rango = ataque - mitad;
        if (rango < 1) rango = 1;
        danio = mitad + (rand() % (rango + 1));
    }
    return danio;
}

void Personaje::recibeAtaque(int ptosAtaque)
{
    salud -= ptosAtaque;
    if (salud < 0) salud = 0;
}

void Personaje::atacar(Personaje& objetivo)
{
    int danio = calculaAtaque(objetivo);
    cout << nombre << " ataca a " << objetivo.getNombre()
         << " con " << danio << " puntos de danio." << endl;
    objetivo.recibeAtaque(danio);
}

void Personaje::imprimir() const
{
    cout << "--------------------------------" << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Nivel: " << nivel << endl;
    cout << "Ataque: " << ataque << endl;
    cout << "Salud: " << salud << " / " << vida << endl;
    imprimeBarra();
    cout << "--------------------------------" << endl;
}
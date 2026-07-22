#include "Ejercito.hpp"
#include "Guerrero.hpp"
#include "Arquero.hpp"
#include "Mago.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

namespace
{
    // Entero aleatorio en el rango [minVal, maxVal], ambos inclusive
    int aleatorioEntre(int minVal, int maxVal)
    {
        return minVal + rand() % (maxVal - minVal + 1);
    }
}

Ejercito::Ejercito(int maxUnidades, string nombreEjercito)
{
    this->maxUnidades = maxUnidades;
    this->nombreEjercito = nombreEjercito;
    numGuerreros = 0;
    numArqueros = 0;
    numMagos = 0;
    combatienteActual = nullptr;
}

Ejercito::~Ejercito()
{
    for (Personaje* p : unidades)
    {
        delete p;
    }
    unidades.clear();
}

void Ejercito::contarTipo(Personaje* p, int signo)
{
    if (dynamic_cast<Guerrero*>(p))      numGuerreros += signo;
    else if (dynamic_cast<Arquero*>(p))  numArqueros += signo;
    else if (dynamic_cast<Mago*>(p))     numMagos += signo;
}

void Ejercito::poblarAleatoriamente(vector<string>& nombresDisponibles)
{
    for (int i = 0; i < maxUnidades; i++)
    {
        if (nombresDisponibles.empty())
        {
            cout << "Aviso: se acabaron los nombres disponibles; " << nombreEjercito
                 << " se quedo con " << unidades.size() << " unidades." << endl;
            break;
        }

        // Elige y remueve un nombre al azar de la lista compartida (para no repetir)
        int idxNombre = rand() % nombresDisponibles.size();
        string nombre = nombresDisponibles[idxNombre];
        nombresDisponibles.erase(nombresDisponibles.begin() + idxNombre);

        int nivel = aleatorioEntre(1, 5);
        int vida = aleatorioEntre(60, 150);
        int ataque = aleatorioEntre(10, 30);

        int tipo = rand() % 3; // 0 = Guerrero, 1 = Arquero, 2 = Mago
        Personaje* nuevo = nullptr;

        if (tipo == 0)
        {
            int fuerza = aleatorioEntre(10, 50);
            nuevo = new Guerrero(nombre, vida, ataque, nivel, fuerza);
        }
        else if (tipo == 1)
        {
            float precision = static_cast<float>(aleatorioEntre(10, 50));
            nuevo = new Arquero(nombre, vida, ataque, nivel, precision);
        }
        else
        {
            int mana = aleatorioEntre(50, 100);
            nuevo = new Mago(nombre, vida, ataque, nivel, mana);
        }

        unidades.push_back(nuevo);
        contarTipo(nuevo, +1);
    }
}

Personaje* Ejercito::elegirAleatorio() const
{
    if (unidades.empty()) return nullptr;
    int idx = rand() % unidades.size();
    return unidades[idx];
}

void Ejercito::eliminarSiMuerto(Personaje* p)
{
    if (p == nullptr || p->getSalud() > 0) return;

    for (size_t i = 0; i < unidades.size(); i++)
    {
        if (unidades[i] == p)
        {
            contarTipo(p, -1);
            delete p;
            unidades.erase(unidades.begin() + i);
            break;
        }
    }
}

Personaje* Ejercito::obtenerCombatiente()
{
    // Si el combatiente actual ya murio (y su revive() no lo salvo), se elimina
    if (combatienteActual != nullptr && combatienteActual->getSalud() == 0)
    {
        eliminarSiMuerto(combatienteActual);
        combatienteActual = nullptr;
    }

    // Si no hay combatiente activo, se elige uno nuevo al azar
    if (combatienteActual == nullptr)
    {
        combatienteActual = elegirAleatorio(); // nullptr si el ejercito ya esta vacio
    }

    return combatienteActual;
}

void Ejercito::mostrarComposicion() const
{
    cout << "== Composicion de " << nombreEjercito << " ==" << endl;
    cout << "Guerreros: " << numGuerreros << endl;
    cout << "Arqueros:  " << numArqueros << endl;
    cout << "Magos:     " << numMagos << endl;
    cout << "Total:     " << unidades.size() << endl;
}

void Ejercito::listarElementos() const
{
    cout << "== Elementos de " << nombreEjercito << " ==" << endl;
    for (Personaje* p : unidades)
    {
        cout << *p << endl;
    }
}

int Ejercito::getNumGuerreros() const { return numGuerreros; }
int Ejercito::getNumArqueros() const { return numArqueros; }
int Ejercito::getNumMagos() const { return numMagos; }
int Ejercito::getTotalUnidades() const { return static_cast<int>(unidades.size()); }
bool Ejercito::estaVacio() const { return unidades.empty(); }
string Ejercito::getNombreEjercito() const { return nombreEjercito; }

vector<string> Ejercito::cargarNombres(const string& rutaArchivo)
{
    vector<string> nombres;
    ifstream archivo(rutaArchivo);

    if (!archivo.is_open())
    {
        cout << "Aviso: no se pudo abrir el archivo de nombres: " << rutaArchivo << endl;
        return nombres;
    }

    string linea;
    while (getline(archivo, linea))
    {
        if (!linea.empty())
        {
            nombres.push_back(linea);
        }
    }

    archivo.close();
    return nombres;
}
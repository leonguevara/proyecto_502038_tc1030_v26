#pragma once
#include <vector>
#include <string>
#include "Personaje.hpp"

// Ejercito: contenedor dinamico de Personaje* (Guerreros, Arqueros, Magos).
// Se puebla aleatoriamente hasta un maximo de unidades, lleva la cuenta de
// cuantos hay de cada tipo, y administra quien es el "combatiente actual"
// que sigue peleando ronda tras ronda hasta que muere.
class Ejercito
{
private:
    std::string nombreEjercito;
    int maxUnidades;
    std::vector<Personaje*> unidades;

    int numGuerreros;
    int numArqueros;
    int numMagos;

    Personaje* combatienteActual; // quien esta peleando actualmente por este ejercito

    // Identifica el tipo real de 'p' (via dynamic_cast) y ajusta los contadores.
    // signo = +1 al agregar una unidad, -1 al quitarla.
    void contarTipo(Personaje* p, int signo);

public:
    explicit Ejercito(int maxUnidades, std::string nombreEjercito = "Ejercito");
    ~Ejercito();

    // El Ejercito es dueño de sus punteros (los libera en su destructor),
    // asi que no se permite copiarlo, para evitar un doble delete.
    Ejercito(const Ejercito&) = delete;
    Ejercito& operator=(const Ejercito&) = delete;

    // Puebla el ejercito con hasta 'maxUnidades' unidades aleatorias
    // (Guerrero/Arquero/Mago, tipo y estadisticas al azar). Los nombres se
    // toman de 'nombresDisponibles' y se eliminan de ahi para que no se
    // repitan entre este ejercito y el rival.
    void poblarAleatoriamente(std::vector<std::string>& nombresDisponibles);

    // Elige un elemento al azar de entre los que siguen con vida
    Personaje* elegirAleatorio() const;

    // Devuelve el combatiente que sigue peleando por este ejercito. Si el
    // anterior ya murio (y no pudo revivir), lo elimina del vector y elige
    // uno nuevo al azar. Devuelve nullptr si el ejercito ya no tiene elementos.
    Personaje* obtenerCombatiente();

    // Si 'p' tiene 0 de salud (murio definitivamente), lo elimina del vector,
    // ajusta los contadores y libera su memoria.
    void eliminarSiMuerto(Personaje* p);

    // Muestra cuantos Guerreros/Arqueros/Magos tiene el ejercito actualmente
    void mostrarComposicion() const;

    // Lista, uno por uno, todos los elementos que siguen en el ejercito
    void listarElementos() const;

    int getNumGuerreros() const;
    int getNumArqueros() const;
    int getNumMagos() const;
    int getTotalUnidades() const;
    bool estaVacio() const;
    std::string getNombreEjercito() const;

    // Utilidad: carga nombres desde un archivo de texto (uno por linea)
    static std::vector<std::string> cargarNombres(const std::string& rutaArchivo);
};
#pragma once
#include <string>
#include "Ejercito.hpp"

// Batalla: orquesta el combate por turnos entre dos Ejercito, alternando
// quien ataca, hasta que alguno de los dos se quede sin elementos.
class Batalla
{
private:
    Ejercito& ejercito1;
    Ejercito& ejercito2;
    int turno;        // 1 o 2: indica a que ejercito le toca atacar
    int numeroRonda;
    std::string archivoSalida; // nombre del archivo donde se guarda el detalle de la batalla

public:
    // Lanza std::invalid_argument si alguno de los dos ejercitos ya esta
    // vacio: no hay batalla que correr sin al menos un elemento por bando.
    Batalla(Ejercito& ejercito1, Ejercito& ejercito2);

    // Corre la batalla completa, ronda por ronda, hasta que un ejercito
    // se quede sin elementos. La composicion inicial y el ganador final se
    // muestran en pantalla; el detalle ronda por ronda se guarda en un
    // archivo "simulacion_<timestamp>.txt".
    void iniciar();

    // true si alguno de los dos ejercitos ya no tiene elementos
    bool haTerminado() const;

    // Imprime el resultado final: ejercito ganador (o empate si ambos
    // quedaron vacios en la misma ronda)
    void mostrarGanador() const;

    // Nombre del archivo donde quedo guardado el detalle de la ultima batalla
    std::string getArchivoSalida() const;
};
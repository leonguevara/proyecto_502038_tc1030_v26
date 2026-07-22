#include "Batalla.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <stdexcept>

using namespace std;

namespace
{
    // Genera un timestamp tipo AAAAMMDD_HHMMSS a partir de la hora actual
    string generarTimestamp()
    {
        time_t ahora = time(nullptr);
        tm* horaLocal = localtime(&ahora);

        ostringstream oss;
        oss << put_time(horaLocal, "%Y%m%d_%H%M%S");
        return oss.str();
    }

    // Guarda RAII: mientras el objeto vive, cout escribe hacia 'destino'.
    // Al destruirse (aunque sea por una excepcion), restaura el buffer
    // original de cout automaticamente. Evita dejar a cout "atrapado"
    // escribiendo al archivo si algo falla a media batalla.
    class RedireccionCout
    {
    private:
        streambuf* bufferOriginal;

    public:
        explicit RedireccionCout(streambuf* destino)
        {
            bufferOriginal = cout.rdbuf();
            if (destino != nullptr)
            {
                cout.rdbuf(destino);
            }
        }

        ~RedireccionCout()
        {
            cout.rdbuf(bufferOriginal);
        }
    };
}

Batalla::Batalla(Ejercito& ejercito1, Ejercito& ejercito2)
    : ejercito1(ejercito1), ejercito2(ejercito2)
{
    if (ejercito1.estaVacio() || ejercito2.estaVacio())
    {
        throw invalid_argument(
            "Batalla: ambos ejercitos deben tener al menos un elemento ("
            + ejercito1.getNombreEjercito() + ": " + to_string(ejercito1.getTotalUnidades())
            + ", " + ejercito2.getNombreEjercito() + ": " + to_string(ejercito2.getTotalUnidades()) + ")");
    }

    turno = 1; // el ejercito 1 empieza atacando
    numeroRonda = 1;
    archivoSalida = "";
}

bool Batalla::haTerminado() const
{
    return ejercito1.estaVacio() || ejercito2.estaVacio();
}

void Batalla::iniciar()
{
    // Lo que pasa antes y despues de la redireccion se ve en pantalla:
    // la composicion inicial de ambos ejercitos.
    cout << endl << "########## INICIA LA BATALLA ##########" << endl;
    ejercito1.mostrarComposicion();
    ejercito2.mostrarComposicion();

    archivoSalida = "simulacion_" + generarTimestamp() + ".txt";
    ofstream archivo(archivoSalida);

    if (!archivo.is_open())
    {
        cout << "Aviso: no se pudo crear " << archivoSalida
             << ", el detalle se mostrara en pantalla." << endl;
    }
    else
    {
        cout << "Guardando el detalle ronda por ronda en: " << archivoSalida << endl;
    }

    // --- Redireccion de cout hacia el archivo ---
    // Mientras 'redireccion' este viva, todo cout << (incluyendo los que
    // estan dentro de imprimir(), atacar(), revive(), operator<<, etc.)
    // escribe automaticamente al archivo en vez de a la pantalla. Al salir
    // de este bloque, su destructor restaura cout hacia la pantalla solo.
    {
        RedireccionCout redireccion(archivo.is_open() ? archivo.rdbuf() : nullptr);

        while (!haTerminado())
        {
            Ejercito& atacanteEjercito = (turno == 1) ? ejercito1 : ejercito2;
            Ejercito& defensorEjercito  = (turno == 1) ? ejercito2 : ejercito1;

            // Si el combatiente de cada ejercito murio en la ronda anterior,
            // obtenerCombatiente() automaticamente elige uno nuevo al azar
            Personaje* atacante = atacanteEjercito.obtenerCombatiente();
            Personaje* defensor = defensorEjercito.obtenerCombatiente();

            // Seguridad: si algun ejercito se quedo sin elementos justo aqui, se termina
            if (atacante == nullptr || defensor == nullptr) break;

            cout << endl << "-- Ronda " << numeroRonda << ": "
                 << atacanteEjercito.getNombreEjercito() << " ataca --" << endl;
            cout << *atacante << "  VS  " << *defensor << endl;

            atacante->atacar(*defensor);
            defensor->imprimir();

            turno = (turno == 1) ? 2 : 1; // alterna el turno
            numeroRonda++;
        }
    } // aqui el destructor de 'redireccion' ya restauro cout hacia la pantalla

    if (archivo.is_open())
    {
        archivo.close();
        cout << "Detalle de la batalla guardado en: " << archivoSalida << endl;
    }

    mostrarGanador();
}

void Batalla::mostrarGanador() const
{
    cout << endl << "########## FIN DE LA BATALLA ##########" << endl;

    bool vacio1 = ejercito1.estaVacio();
    bool vacio2 = ejercito2.estaVacio();

    if (vacio1 && vacio2)
    {
        cout << "¡Empate! Ambos ejercitos se quedaron sin elementos." << endl;
    }
    else if (vacio1)
    {
        cout << "¡" << ejercito2.getNombreEjercito() << " gana la batalla!" << endl;
    }
    else
    {
        cout << "¡" << ejercito1.getNombreEjercito() << " gana la batalla!" << endl;
    }
}

string Batalla::getArchivoSalida() const { return archivoSalida; }
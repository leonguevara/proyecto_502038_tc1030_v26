# Diagrama UML - Simulador de Batallas

```mermaid
classDiagram
    class Personaje {
        <<abstract>>
        -string nombre
        -int vida
        -int salud
        -int ataque
        -int nivel
        +Personaje()
        +Personaje(nombre: string, vida: int, ataque: int, nivel: int)
        +getNombre() string
        +getVida() int
        +getSalud() int
        +getAtaque() int
        +getNivel() int
        +setNombre(nombre: string) void
        +setVida(vida: int) void
        +setSalud(salud: int) void
        +setAtaque(ataque: int) void
        +setNivel(nivel: int) void
        +porcentajeSalud() int
        +imprimeBarra() void
        +calculaAtaque(objetivo: Personaje&) int
        +recibeAtaque(ptosAtaque: int) void
        +atacar(objetivo: Personaje&) void
        +imprimir() void
        +mostrar(os: ostream&) ostream&
        +revive()* void
    }

    class Guerrero {
        -int fuerza
        -bool yaRevivio
        +Guerrero()
        +Guerrero(nombre: string, vida: int, ataque: int, nivel: int, fuerza: int)
        +getFuerza() int
        +setFuerza(fuerza: int) void
        +calculaAtaque(objetivo: Personaje&) int
        +recibeAtaque(ptosAtaque: int) void
        +imprimir() void
        +revive() void
        +mostrar(os: ostream&) ostream&
    }

    class Arquero {
        -float precision
        -bool yaRevivio
        +Arquero()
        +Arquero(nombre: string, vida: int, ataque: int, nivel: int, precision: float)
        +getPrecision() float
        +setPrecision(precision: float) void
        +calculaAtaque(objetivo: Personaje&) int
        +recibeAtaque(ptosAtaque: int) void
        +imprimir() void
        +revive() void
        +mostrar(os: ostream&) ostream&
    }

    class Mago {
        -int mana
        -bool yaRevivio
        +Mago()
        +Mago(nombre: string, vida: int, ataque: int, nivel: int, mana: int)
        +getMana() int
        +setMana(mana: int) void
        +calculaAtaque(objetivo: Personaje&) int
        +recibeAtaque(ptosAtaque: int) void
        +atacar(objetivo: Personaje&) void
        +imprimir() void
        +revive() void
        +mostrar(os: ostream&) ostream&
    }

    class Ejercito {
        -string nombreEjercito
        -int maxUnidades
        -vector~Personaje*~ unidades
        -int numGuerreros
        -int numArqueros
        -int numMagos
        -Personaje* combatienteActual
        +Ejercito(maxUnidades: int, nombreEjercito: string)
        +poblarAleatoriamente(nombresDisponibles: vector~string~&) void
        +elegirAleatorio() Personaje*
        +obtenerCombatiente() Personaje*
        +eliminarSiMuerto(p: Personaje*) void
        +mostrarComposicion() void
        +listarElementos() void
        +getNumGuerreros() int
        +getNumArqueros() int
        +getNumMagos() int
        +getTotalUnidades() int
        +estaVacio() bool
        +getNombreEjercito() string
        +cargarNombres(rutaArchivo: string)$ vector~string~
    }

    class Batalla {
        -Ejercito& ejercito1
        -Ejercito& ejercito2
        -int turno
        -int numeroRonda
        +Batalla(ejercito1: Ejercito&, ejercito2: Ejercito&)
        +iniciar() void
        +haTerminado() bool
        +mostrarGanador() void
    }

    Personaje <|-- Guerrero
    Personaje <|-- Arquero
    Personaje <|-- Mago
    Ejercito o-- "0..*" Personaje : unidades
    Batalla o-- "2" Ejercito
```

> `Personaje` es una clase **abstracta**: `revive()` es virtual puro (marcado con `*` en el diagrama), por lo que no puede instanciarse directamente, solo a través de `Guerrero`, `Arquero` o `Mago`.
>
> `cargarNombres()` está marcado con `$` porque es un método **estático**: no depende de una instancia particular de `Ejercito`, se usa para cargar la lista de nombres una sola vez antes de poblar los ejércitos.

## Descripción de los métodos de `Personaje` (clase base)

- **porcentajeSalud()**: calcula qué porcentaje de vida le queda al personaje, comparando `salud` (vida actual) contra `vida` (vida máxima). Devuelve un entero entre 0 y 100.
- **imprimeBarra()**: dibuja una barra de 20 caracteres. Cada carácter representa 5% de vida; usa `%` para la parte que aún tiene y `=` para la parte perdida.
- **calculaAtaque(objetivo)**: si el objetivo tiene un nivel mayor, el daño es aleatorio entre 1 y la mitad del ataque propio (penalización por pelear "hacia arriba"). Si el objetivo tiene nivel igual o menor, el daño es aleatorio entre la mitad y el total del ataque propio.
- **recibeAtaque(ptosAtaque)**: resta los puntos de daño a la salud actual; nunca deja la salud en negativo (mínimo 0). Cada clase derivada la sobreescribe para modificar el daño según su atributo especial, y al final llama a `revive()` para evaluar si el personaje se levanta o queda definitivamente muerto.
- **atacar(objetivo)**: calcula el daño con `calculaAtaque` y se lo aplica al objetivo llamando a su `recibeAtaque`. Es `virtual`, así que las clases derivadas pueden decidir un flujo distinto (por ejemplo, `Mago` lo usa para recuperar maná tras un ataque letal).
- **imprimir()**: muestra en pantalla nombre, nivel, ataque, salud actual/máxima y la barra de vida. Es `virtual` para que cada clase derivada agregue su propia información.
- **revive()**: método **virtual puro**. Decide, según la salud actual y el atributo especial de cada subclase, si el personaje se levanta con algo de vida o queda muerto definitivamente. Al no tener implementación en `Personaje`, obliga a cada clase derivada a definir su propia regla y hace que `Personaje` sea abstracta.
- **mostrar(os)**: escribe una representación breve del personaje (nombre, nivel, salud, ataque) en el stream recibido. Es el método que usa polimórficamente la sobrecarga del operador `<<` para imprimir cualquier `Personaje*` sin importar su subclase real.

## Sobrecarga de operador

Se sobrecargó el operador de flujo de salida `<<` (`operator<<`) como función `friend` de `Personaje`. Permite escribir `cout << personaje` o `cout << *punteroAPersonaje` y que se despliegue correctamente la información según la subclase real del objeto, gracias a que internamente delega en el método virtual `mostrar()`. Es el operador más útil para el proyecto porque se usa constantemente al recorrer el vector de combatientes durante las batallas.

## Descripción de los métodos de `Guerrero`

El Guerrero es una unidad cuerpo a cuerpo cuya `fuerza` funciona como potenciador de ataque y como armadura.

- **calculaAtaque(objetivo)**: reutiliza `Personaje::calculaAtaque` para el daño base y le suma un bono fijo de `fuerza / 5`.
- **recibeAtaque(ptosAtaque)**: la `fuerza` reduce el daño recibido en un porcentaje (`fuerza / 4`, con un tope máximo de 60% de reducción, para que nunca se vuelva invulnerable). Al final llama a `revive()`.
- **imprimir()**: llama a `Personaje::imprimir()` y agrega la línea con la clase y el valor de `fuerza`.
- **revive()**: si la salud llegó a 0, la `fuerza` es `>= 25` y no ha revivido antes, se levanta con 20% de la vida máxima a cambio de perder la mitad de su `fuerza` (mensaje: *"se levanta con furia de batalla"*). El flag `yaRevivio` asegura que esto solo pase una vez; en cualquier otro caso, el personaje queda muerto.
- **mostrar(os)**: reutiliza `Personaje::mostrar()` y agrega el valor de `fuerza`.

## Descripción de los métodos de `Arquero`

El Arquero es una unidad a distancia cuya `precision` (0.0 a 100.0, en %) determina probabilidad de golpes críticos y de esquivar ataques.

- **calculaAtaque(objetivo)**: reutiliza `Personaje::calculaAtaque` para el daño base. Con probabilidad igual a `precision`%, el golpe es crítico y el daño se multiplica por 1.5.
- **recibeAtaque(ptosAtaque)**: con probabilidad igual a `precision / 2`%, el arquero esquiva parcialmente el ataque y solo recibe la mitad del daño; si no esquiva, recibe el daño completo. Al final llama a `revive()`.
- **imprimir()**: llama a `Personaje::imprimir()` y agrega la línea con la clase y el valor de `precision`.
- **revive()**: si la salud llegó a 0, la `precision` es `>= 30` y no ha revivido antes, esquiva la muerte y se levanta con 20% de la vida máxima a cambio de perder la mitad de su `precision`. El flag `yaRevivio` limita esto a una sola vez; en cualquier otro caso, el personaje queda muerto.
- **mostrar(os)**: reutiliza `Personaje::mostrar()` y agrega el valor de `precision`.

## Descripción de los métodos de `Mago`

El Mago es una unidad mágica cuyo `mana` (0 a 100) puede potenciar su ataque y reducir el daño recibido, pero se va gastando con el uso.

- **calculaAtaque(objetivo)**: reutiliza `Personaje::calculaAtaque` para el daño base. Si tiene maná disponible, existe una probabilidad (`mana / 2`%) de lanzar un "hechizo fuerte" que duplica el daño y consume 20 puntos de maná (nunca queda negativo).
- **recibeAtaque(ptosAtaque)**: reduce el daño recibido de forma escalonada según nivel y maná disponible: nivel ≥4 con maná >80 reduce el daño a un tercio; nivel ≥3 con maná >85 lo reduce a la mitad; nivel ≤2 con maná al 100% lo reduce a 3/4 partes. Fuera de esos umbrales, recibe el daño completo. Al final llama a `revive()`.
- **atacar(objetivo)**: reutiliza el flujo de `Personaje::atacar()` y, si el objetivo queda con 0 de salud tras el ataque (es decir, murió de verdad y no revivió), el mago "absorbe energía" y recupera 15 puntos de maná (tope 100).
- **imprimir()**: llama a `Personaje::imprimir()` y agrega la línea con la clase y el valor de `mana`.
- **revive()**: si la salud llegó a 0, el `mana` es `> 50` y no ha revivido antes, usa su última reserva de energía mágica para levantarse con 20% de la vida máxima, a cambio de gastar 50 puntos de `mana`. El flag `yaRevivio` limita esto a una sola vez; en cualquier otro caso, el personaje queda muerto.
- **mostrar(os)**: reutiliza `Personaje::mostrar()` y agrega el valor de `mana`.

## Descripción de los métodos de `Ejercito`

`Ejercito` es dueño de un `vector<Personaje*>` (relación de **composición**: cuando el ejército se destruye, libera la memoria de todos sus integrantes). No se puede copiar (`Ejercito(const Ejercito&) = delete`), precisamente para evitar que dos ejércitos terminen apuntando a los mismos personajes y se intente liberar la misma memoria dos veces.

- **Constructor `Ejercito(maxUnidades, nombreEjercito)`**: guarda el límite de unidades y el nombre del ejército; el vector empieza vacío, se puebla después con `poblarAleatoriamente()`.
- **poblarAleatoriamente(nombresDisponibles)**: crea hasta `maxUnidades` personajes de tipo aleatorio (Guerrero/Arquero/Mago, con probabilidad igual entre los tres) y estadísticas aleatorias dentro de rangos razonables. Cada personaje toma un nombre al azar de `nombresDisponibles` y lo **elimina** de esa lista, para que dos ejércitos que comparten la misma lista de nombres nunca se repitan un nombre entre sí. Si la lista de nombres se agota antes de llegar a `maxUnidades`, el ejército se queda con menos unidades y se imprime un aviso.
- **elegirAleatorio()**: regresa un puntero a un elemento aleatorio del vector (o `nullptr` si el ejército está vacío).
- **obtenerCombatiente()**: regresa el combatiente que sigue peleando por este ejército. Si el combatiente anterior ya tiene 0 de salud (y su `revive()` no lo salvó), lo elimina del vector y elige uno nuevo al azar. Así, un mismo personaje sigue peleando ronda tras ronda hasta que muere de verdad.
- **eliminarSiMuerto(p)**: si `p` tiene 0 de salud, lo quita del vector, ajusta los contadores por tipo y libera su memoria (`delete`).
- **mostrarComposicion()**: imprime cuántos Guerreros, Arqueros y Magos tiene el ejército actualmente, y el total.
- **listarElementos()**: imprime, uno por uno (usando el `operator<<` sobrecargado), todos los elementos que siguen en el ejército.
- **cargarNombres(rutaArchivo)** *(método estático)*: lee un archivo de texto con un nombre por línea (como `names.txt`) y regresa un `vector<string>`. Se llama una sola vez antes de poblar los ejércitos, y el vector resultante se comparte entre ambos.

## Descripción de los métodos de `Batalla`

`Batalla` **no es dueña** de los ejércitos: los recibe por referencia (`Ejercito&`), ya que ambos existen fuera de la batalla (por ejemplo, en `main`) y deben seguir vivos mientras dura el combate.

- **Constructor `Batalla(ejercito1, ejercito2)`**: guarda las referencias a ambos ejércitos, inicia el turno en el ejército 1 y el contador de rondas en 1.
- **iniciar()**: corre el ciclo principal de la batalla. Primero muestra en pantalla la composición inicial de ambos ejércitos. Luego, mientras dura el ciclo de combate, redirige `cout` hacia un archivo `simulacion_<timestamp>.txt` (ver sección siguiente), así que todo el detalle ronda por ronda queda documentado ahí en vez de saturar la pantalla. En cada ronda, el ejército en turno obtiene su combatiente (que puede ser uno nuevo si el anterior murió), lo mismo el ejército rival, y el atacante ejecuta `atacar()` sobre el defensor. El turno se alterna después de cada ronda. El ciclo continúa hasta que `haTerminado()` sea verdadero; al terminar, `cout` vuelve a la pantalla y se llama `mostrarGanador()`.
- **haTerminado()**: regresa `true` si cualquiera de los dos ejércitos se quedó sin elementos (`estaVacio()`).
- **mostrarGanador()**: al terminar la batalla, imprime cuál ejército ganó (el que no se quedó vacío), o un empate si ambos se vaciaron en la misma ronda.
- **getArchivoSalida()**: regresa el nombre del archivo donde quedó guardado el detalle de la última batalla corrida (por ejemplo, `simulacion_20260722_220248.txt`).

## Redirección de la salida ronda por ronda hacia un archivo

Para que la pantalla no se sature con decenas de rondas de combate, `Batalla::iniciar()` solo muestra en pantalla la **composición inicial** de ambos ejércitos y, al final, el **ejército ganador**. Todo el detalle intermedio (cada ataque, cada `imprimir()`, cada mensaje de golpe crítico/esquive/hechizo fuerte/revive) se guarda en un archivo de texto llamado `simulacion_<timestamp>.txt` (por ejemplo `simulacion_20260722_220248.txt`), donde el timestamp se genera con la hora local del sistema en el momento de iniciar la batalla.

**¿Cómo se logra sin modificar `Personaje`, `Guerrero`, `Arquero`, `Mago` ni `Ejercito`?** `std::cout` es un objeto que escribe hacia un "buffer" (`std::streambuf`) interno; normalmente ese buffer está conectado a la terminal. `cout.rdbuf(otroBuffer)` permite cambiar ese buffer en tiempo de ejecución, de modo que cualquier `cout <<` posterior —sin importar en qué función o clase esté— empieza a escribir hacia donde apunte el nuevo buffer. Como todos los métodos del proyecto ya usaban `cout <<` internamente, no hizo falta tocarlos: basta con redirigir el buffer antes del ciclo de combate y restaurarlo después.

Para hacer esa redirección seguros, se usa el patrón **RAII** (*Resource Acquisition Is Initialization*) con una clase auxiliar `RedireccionCout` (definida dentro de `Batalla.cpp`, en un namespace anónimo):

- Su **constructor** guarda el buffer original de `cout` y lo cambia hacia el archivo.
- Su **destructor** restaura el buffer original.

Como en C++ los destructores se ejecutan automáticamente al salir de un bloque `{ }` —incluso si algo lanza una excepción a la mitad de la batalla—, `cout` siempre termina apuntando de vuelta a la pantalla de forma garantizada, sin importar cómo se salga del bloque de combate.

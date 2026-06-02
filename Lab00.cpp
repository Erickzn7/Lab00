// ============================================================
//  TRES EN RAYA Tic-Tac-Toe
// ============================================================

#include <iostream>
#include <string>
using namespace std;

//  CLASE: Tablero
//  Responsabilidad: gestionar el estado del tablero de juego.
//  Propiedades: matriz 3x3 de caracteres.
//  Metodos: inicializar, mostrar, marcar casilla, verificar estado.
class Tablero {
private:
    // Propiedad: matriz 3x3 que representa las casillas del tablero.
    // Cada celda puede contener ' ' (vacia), 'X' o 'O'.
    char casillas[3][3];

public:
    //  Constructor: se ejecuta al crear un objeto Tablero.
    //  Llama a inicializar() para dejar todas las casillas vacias.
    Tablero() {
        inicializar();
    }
    //  Metodo: inicializar
    //  Rellena todas las casillas con espacio (' ') = vacia.
    // --------------------------------------------------------
    void inicializar() {
        for (int fila = 0; fila < 3; fila++) {
            for (int col = 0; col < 3; col++) {
                casillas[fila][col] = ' ';
            }
        }
    }

    //  Metodo: mostrar
    //  Imprime el tablero en consola con bordes visuales.
    //  Los numeros de posicion (1-9) se muestran si la casilla esta vacia.
    void mostrar() const {
        cout << "\n";
        cout << "   1   2   3 " << "\n";
        cout << " +---+---+---+" << "\n";

        for (int fila = 0; fila < 3; fila++) {
            // Muestra el numero de fila (1, 2 o 3) al inicio
            cout << fila + 1 << "|";
            for (int col = 0; col < 3; col++) {
                // Si la casilla esta vacia, muestra un punto para orientar al jugador
                if (casillas[fila][col] == ' ') {
                    cout << " . |";
                }
                else {
                    cout << " " << casillas[fila][col] << " |";
                }
            }
            cout << "\n";
            cout << " +---+---+---+" << "\n";
        }
        cout << "\n";
    }
    //  Metodo: marcarCasilla
    //  Parametros: fila (0-2), col (0-2), simbolo ('X' o 'O')
    //  Retorna: true si la casilla estaba vacia y se marco,
    //           false si ya estaba ocupada (movimiento invalido).
    bool marcarCasilla(int fila, int col, char simbolo) {
        if (casillas[fila][col] == ' ') {
            casillas[fila][col] = simbolo;
            return true;  // Movimiento valido
        }
        return false;     // Casilla ocupada
    }
    //  Metodo: hayGanador
    //  Verifica si el simbolo dado completa una linea ganadora:
    //  - Las 3 filas horizontales
    //  - Las 3 columnas verticales
    //  - Las 2 diagonales
    //  Retorna: true si ese simbolo ha ganado, false si no.
    bool hayGanador(char simbolo) const {
        // Verificar filas
        for (int fila = 0; fila < 3; fila++) {
            if (casillas[fila][0] == simbolo &&
                casillas[fila][1] == simbolo &&
                casillas[fila][2] == simbolo) {
                return true;
            }
        }
        // Verificar columnas
        for (int col = 0; col < 3; col++) {
            if (casillas[0][col] == simbolo &&
                casillas[1][col] == simbolo &&
                casillas[2][col] == simbolo) {
                return true;
            }
        }

        // Verificar diagonal principal (top-left a bottom-right)
        if (casillas[0][0] == simbolo &&
            casillas[1][1] == simbolo &&
            casillas[2][2] == simbolo) {
            return true;
        }

        // Verificar diagonal secundaria (top-right a bottom-left)
        if (casillas[0][2] == simbolo &&
            casillas[1][1] == simbolo &&
            casillas[2][0] == simbolo) {
            return true;
        }

        return false;
    }
    //  Metodo: tableroLleno
    //  Recorre todas las casillas: si encuentra alguna vacia
    //  retorna false (aun hay movimientos posibles).
    //  Si todas estan ocupadas, retorna true (empate).
    bool tableroLleno() const {
        for (int fila = 0; fila < 3; fila++) {
            for (int col = 0; col < 3; col++) {
                if (casillas[fila][col] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }
};

//  CLASE: Jugador
//  Responsabilidad: representar a un participante del juego.
//  Propiedades: nombre y simbolo asignado ('X' u 'O').
//  Metodos: obtener nombre, obtener simbolo, pedir movimiento.
class Jugador {
private:
    string nombre;   // Propiedad: nombre del jugador
    char   simbolo;  // Propiedad: simbolo que usa en el tablero

public:
    //  Constructor: inicializa nombre y simbolo del jugador.
    Jugador(string nombre, char simbolo) {
        this->nombre = nombre;
        this->simbolo = simbolo;
    }

    //  Metodo getter: getNombre
    //  Retorna el nombre del jugador (solo lectura).
    string getNombre() const {
        return nombre;
    }

    //  Metodo getter: getSimbolo
    //  Retorna el simbolo del jugador (solo lectura).
    char getSimbolo() const {
        return simbolo;
    }

    //  Metodo: pedirMovimiento
    //  Solicita al jugador que ingrese fila y columna (1-3).
    //  Convierte los valores a indices 0-2 para la matriz interna.
    //  Parametros de salida: fila y col (pasados por referencia).
    void pedirMovimiento(int& fila, int& col) const {
        cout << nombre << " (" << simbolo << "), ingresa tu movimiento:" << "\n";
        cout << "  Fila   (1-3): ";
        cin >> fila;
        cout << "  Columna(1-3): ";
        cin >> col;

        // Convertir de notacion 1-3 a indices 0-2
        fila--;
        col--;
    }
};

//  CLASE: Juego
//  Responsabilidad: coordinar la logica completa de la partida.
//  Propiedades: objeto Tablero, dos objetos Jugador, turno actual.
//  Metodos: iniciar, ejecutar turno, verificar fin, anunciar resultado.
class Juego {
private:
    Tablero tablero;       // Propiedad: el tablero de juego
    Jugador jugador1;      // Propiedad: primer jugador  (X)
    Jugador jugador2;      // Propiedad: segundo jugador (O)
    int     turnoActual;   // Propiedad: 1 = jugador1, 2 = jugador2

public:
    //  Constructor: recibe los nombres de ambos jugadores,
    //  crea los objetos Jugador con sus simbolos y comienza en turno 1.
    Juego(string nombre1, string nombre2)
        : jugador1(nombre1, 'X'),
        jugador2(nombre2, 'O'),
        turnoActual(1) {
    }

    //  Metodo: obtenerJugadorActual
    //  Retorna una referencia al jugador cuyo turno es activo.
    Jugador& obtenerJugadorActual() {
        if (turnoActual == 1) return jugador1;
        else                  return jugador2;
    }

    //  Metodo: cambiarTurno
    //  Alterna el turno entre jugador 1 y jugador 2.
    void cambiarTurno() {
        turnoActual = (turnoActual == 1) ? 2 : 1;
    }

    //  Metodo: ejecutarTurno
    //  Maneja un turno completo:
    //  1. Muestra el tablero.
    //  2. Pide movimiento al jugador activo.
    //  3. Valida que el movimiento sea legal (dentro de rango y celda libre).
    //  4. Marca la casilla.
    //  Retorna: true si el jugador activo gano tras este movimiento,
    //           false si el juego continua.
    bool ejecutarTurno() {
        tablero.mostrar();
        Jugador& jugadorActual = obtenerJugadorActual();

        int fila, col;
        bool movimientoValido = false;

        // Repetir hasta obtener un movimiento valido
        while (!movimientoValido) {
            jugadorActual.pedirMovimiento(fila, col);

            // Validar rango (0-2 tras la conversion interna)
            if (fila < 0 || fila > 2 || col < 0 || col > 2) {
                cout << "  >> Posicion fuera de rango. Intenta de nuevo.\n";
                continue;
            }

            // Intentar marcar: marcarCasilla devuelve false si ya estaba ocupada
            movimientoValido = tablero.marcarCasilla(fila, col, jugadorActual.getSimbolo());

            if (!movimientoValido) {
                cout << "  >> Casilla ocupada. Elige otra.\n";
            }
        }

        // Verificar si el movimiento produce una victoria
        return tablero.hayGanador(jugadorActual.getSimbolo());
    }

    //  Metodo: iniciar
    //  Bucle principal del juego:
    //  - Ejecuta turnos alternos hasta que haya ganador o empate.
    //  - Muestra el resultado final.
    void iniciar() {
        cout << "\n========================================\n";
        cout << "   TRES EN RAYA - ¡Que comience el juego!\n";
        cout << "========================================\n";
        cout << jugador1.getNombre() << " juega con X\n";
        cout << jugador2.getNombre() << " juega con O\n";

        bool juegoTerminado = false;

        while (!juegoTerminado) {
            // Ejecutar turno del jugador activo
            bool gano = ejecutarTurno();

            if (gano) {
                // Mostrar tablero final con la jugada ganadora
                tablero.mostrar();
                cout << "  *** " << obtenerJugadorActual().getNombre()
                    << " GANA! Felicidades! ***\n\n";
                juegoTerminado = true;
            }
            else if (tablero.tableroLleno()) {
                // No hay ganador y no quedan casillas
                tablero.mostrar();
                cout << "  *** EMPATE! Gran partida. ***\n\n";
                juegoTerminado = true;
            }
            else {
                // Continuar: cambiar turno al otro jugador
                cambiarTurno();
            }
        }
    }
};

//  FUNCION PRINCIPAL: main
//  Punto de entrada del programa
//  Solicita nombres, crea el objeto Juego e inicia la partida
//  Al terminar, ofrece jugar de nuevo
int main() {
    char jugarDeNuevo;

    do {
        string nombre1, nombre2;

        cout << "\n--- TRES EN RAYA ---\n";
        cout << "Nombre del Jugador 1 (X): ";
        cin >> nombre1;
        cout << "Nombre del Jugador 2 (O): ";
        cin >> nombre2;

        // Crear objeto Juego con los nombres ingresados
        Juego juego(nombre1, nombre2);

        // Iniciar la partida (bucle principal)
        juego.iniciar();

        cout << "Quieres jugar de nuevo? (s/n): ";
        cin >> jugarDeNuevo;

    } while (jugarDeNuevo == 's' || jugarDeNuevo == 'S');

    cout << "\nGracias por jugar. Hasta luego!\n";
    return 0;
}

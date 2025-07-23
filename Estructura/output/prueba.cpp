#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class TableroReinas {
private:
    int N; // Tamaño del tablero
    int* posiciones; // posiciones[fila] = columna
    ofstream archivo;
    int paso;

public:
    TableroReinas(int tamano) : N(tamano), paso(0) {
        posiciones = new int[N];
        for (int i = 0; i < N; ++i) posiciones[i] = -1;

        archivo.open("movimientos.txt");
        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo.\n";
            exit(1);
        }
    }

    ~TableroReinas() {
        delete[] posiciones;
        archivo.close();
    }

    void resolver() {
        cout << "\n=== RESOLVIENDO 8 REINAS ===\n";
        if (colocarReina(0))
            cout << "¡Solución encontrada!\n";
        else
            cout << "No hay solución.\n";
    }

private:
    bool colocarReina(int fila) {
        if (fila == N) return true;

        for (int col = 0; col < N; ++col) {
            if (esSeguro(fila, col)) {
                posiciones[fila] = col;
                guardarEstado(fila, col, true);
                paso++;

                if (colocarReina(fila + 1)) return true;

                // Backtracking
                guardarEstado(fila, col, false);
                posiciones[fila] = -1;
                paso++;
            }
        }
        return false;
    }

    bool esSeguro(int fila, int col) {
        for (int i = 0; i < fila; ++i) {
            if (posiciones[i] == col || 
                posiciones[i] - i == col - fila || 
                posiciones[i] + i == col + fila)
                return false;
        }
        return true;
    }

    void mostrarTablero() {
        for (int f = 0; f < N; ++f) {
            for (int c = 0; c < N; ++c) {
                if (posiciones[f] == c)
                    cout << " Q ";
                else
                    cout << " . ";
            }
            cout << "\n";
        }
    }

    void guardarEstado(int fila, int col, bool colocando) {
        archivo << "Paso " << paso << ": "
                << (colocando ? "Coloca " : "Quita ") << "reina en ("
                << fila << "," << col << ")\n";

        for (int f = 0; f < N; ++f) {
            for (int c = 0; c < N; ++c) {
                archivo << (posiciones[f] == c ? "Q " : ". ");
            }
            archivo << "\n";
        }
        archivo << "\n";
    }
};

int main() {
    int tamano = 8;
    TableroReinas juego(tamano);
    juego.resolver();
    return 0;
}

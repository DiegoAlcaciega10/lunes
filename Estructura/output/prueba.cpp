#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int TAMANO = 8;

void mostrarTablero(const vector<int>& posiciones) {
    for (int fila = 0; fila < TAMANO; ++fila) {
        for (int col = 0; col < TAMANO; ++col) {
            bool esReina = (posiciones[fila] == col);
            bool esCuadroOscuro = ((fila + col) % 2 == 1);

            if (esReina) {
                cout << "\033[31m♛ \033[0m";
            } else {
                if (esCuadroOscuro) {
                    cout << "\033[100m  \033[0m";
                } else {
                    cout << "\033[47m  \033[0m";
                }
            }
        }
        cout << "\n";
    }
}

// Mover cursor arriba n líneas
void moverCursorArriba(int n) {
    cout << "\033[" << n << "A";
}

bool esSeguro(const vector<int>& posiciones, int fila, int col) {
    for (int i = 0; i < fila; ++i) {
        int reinaCol = posiciones[i];
        if (reinaCol == col || 
            reinaCol - i == col - fila ||
            reinaCol + i == col + fila)
            return false;
    }
    return true;
}

bool resolverReinas(int fila, vector<int>& posiciones, ofstream& archivo, int& paso, bool primerPaso) {
    if (fila == TAMANO) {
        return true;
    }

    for (int col = 0; col < TAMANO; ++col) {
        if (esSeguro(posiciones, fila, col)) {
            posiciones[fila] = col;
            paso++;

            if (!primerPaso) {
                moverCursorArriba(TAMANO);
            }
            cout << "Paso " << paso << ": Colocando reina en fila " << fila << ", columna " << col << "\n";
            mostrarTablero(posiciones);
            cout << "\nPresiona ENTER para continuar...\n";
            cin.get();

            // Guardar
            archivo << "Paso " << paso << ":\n";
            for (int f = 0; f < TAMANO; ++f) {
                for (int c = 0; c < TAMANO; ++c) {
                    archivo << ((posiciones[f] == c) ? "Q " : ". ");
                }
                archivo << "\n";
            }
            archivo << "\n";

            if (resolverReinas(fila + 1, posiciones, archivo, paso, false)) {
                return true;
            }

            posiciones[fila] = -1;
            paso++;

            moverCursorArriba(TAMANO);
            cout << "Paso " << paso << ": Retrocediendo en fila " << fila << ", columna " << col << "\n";
            mostrarTablero(posiciones);
            cout << "\nPresiona ENTER para continuar...\n";
            cin.get();

            archivo << "Paso " << paso << ":\n";
            for (int f = 0; f < TAMANO; ++f) {
                for (int c = 0; c < TAMANO; ++c) {
                    archivo << ((posiciones[f] == c) ? "Q " : ". ");
                }
                archivo << "\n";
            }
            archivo << "\n";
        }
    }
    return false;
}

int main() {
    vector<int> posiciones(TAMANO, -1);
    ofstream archivo("movimientos_reinas.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir archivo\n";
        return 1;
    }
    int paso = 0;
    cout << "\n\n\n\n\n\n\n\n";  // Imprime líneas vacías para reservar espacio inicial (8 líneas)

    bool exito = resolverReinas(0, posiciones, archivo, paso, true);

    if (exito) {
        cout << "¡Solución encontrada!\n";
    } else {
        cout << "No hay solución.\n";
    }

    archivo.close();
    return 0;
}

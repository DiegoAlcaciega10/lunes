#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

using namespace std;

class Grafo {
private:
    int numCiudades;
    vector<vector<int>> matriz;
    vector<string> nombres;

public:
    Grafo(int n) : numCiudades(n) {
        matriz.resize(n, vector<int>(n, 0));
        nombres.resize(n);
    }

    void ingresarNombres() {
        cout << "\nIngrese el nombre de cada ciudad:\n";
        for (int i = 0; i < numCiudades; ++i) {
            cout << "Ciudad " << i << ": ";
            cin >> nombres[i];
        }
    }

    void ingresarDistancias() {
        cout << "\nIngrese las distancias entre ciudades (0 si es la misma):\n";
        for (int i = 0; i < numCiudades; ++i) {
            for (int j = 0; j < numCiudades; ++j) {
                if (i != j) {
                    cout << "Distancia de " << nombres[i] << " a " << nombres[j] << ": ";
                    cin >> matriz[i][j];
                } else {
                    matriz[i][j] = 0;
                }
            }
        }
    }

    void resolverTSP() {
        vector<int> ruta;
        for (int i = 1; i < numCiudades; ++i) ruta.push_back(i);

        int mejorCosto = INT_MAX;
        vector<int> mejorRuta;

        do {
            int costo = 0;
            int desde = 0;

            for (int i = 0; i < ruta.size(); ++i) {
                int hacia = ruta[i];
                costo += matriz[desde][hacia];
                desde = hacia;
            }
            costo += matriz[desde][0]; // regresar al inicio

            if (costo < mejorCosto) {
                mejorCosto = costo;
                mejorRuta = ruta;
            }
        } while (next_permutation(ruta.begin(), ruta.end()));

        // Mostrar resultados
        cout << "\nRuta más corta: ";
        cout << nombres[0] << " -> ";
        for (int i : mejorRuta) {
            cout << nombres[i] << " -> ";
        }
        cout << nombres[0] << endl;

        cout << "Distancia total: " << mejorCosto << " km" << endl;
    }
};

int main() {
    int n;
    cout << "Ingrese el número de ciudades: ";
    cin >> n;

    Grafo mapa(n);
    mapa.ingresarNombres();
    mapa.ingresarDistancias();
    mapa.resolverTSP();

    return 0;
}

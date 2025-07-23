#include <iostream>
#include <climits>
#include <string>

using namespace std;

class Grafo {
private:
    int numCiudades;
    int** matriz;         // Matriz dinámica de distancias
    string* nombres;      // Arreglo dinámico de nombres

public:
    Grafo(int n) {
        numCiudades = n;

        // Reservar memoria para matriz
        matriz = new int*[numCiudades];
        for (int i = 0; i < numCiudades; ++i) {
            matriz[i] = new int[numCiudades];
        }

        // Reservar memoria para nombres
        nombres = new string[numCiudades];
    }

    ~Grafo() {
        for (int i = 0; i < numCiudades; ++i) {
            delete[] matriz[i];
        }
        delete[] matriz;
        delete[] nombres;
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
                if (i == j) {
                    matriz[i][j] = 0;
                } else {
                    cout << "Distancia de " << nombres[i] << " a " << nombres[j] << ": ";
                    cin >> matriz[i][j];
                }
            }
        }
    }

    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

    bool nextPermutation(int* arr, int n) {
        int i = n - 2;
        while (i >= 0 && arr[i] >= arr[i + 1]) i--;
        if (i < 0) return false;

        int j = n - 1;
        while (arr[j] <= arr[i]) j--;
        swap(arr[i], arr[j]);

        int left = i + 1, right = n - 1;
        while (left < right) swap(arr[left++], arr[right--]);

        return true;
    }

    void resolverTSP() {
        int* ruta = new int[numCiudades - 1];
        for (int i = 0; i < numCiudades - 1; ++i) {
            ruta[i] = i + 1;  // Empezamos desde ciudad 1, ya que 0 es origen
        }

        int mejorCosto = INT_MAX;
        int* mejorRuta = new int[numCiudades - 1];

        do {
            int costo = 0;
            int desde = 0;
            for (int i = 0; i < numCiudades - 1; ++i) {
                int hacia = ruta[i];
                costo += matriz[desde][hacia];
                desde = hacia;
            }
            costo += matriz[desde][0];  // Regresar al inicio

            if (costo < mejorCosto) {
                mejorCosto = costo;
                for (int i = 0; i < numCiudades - 1; ++i) {
                    mejorRuta[i] = ruta[i];
                }
            }
        } while (nextPermutation(ruta, numCiudades - 1));

        // Mostrar resultados
        cout << "\nRuta más corta: ";
        cout << nombres[0] << " -> ";
        for (int i = 0; i < numCiudades - 1; ++i) {
            cout << nombres[mejorRuta[i]] << " -> ";
        }
        cout << nombres[0] << endl;
        cout << "Distancia total: " << mejorCosto << " km" << endl;

        delete[] ruta;
        delete[] mejorRuta;
    }
};

int main() {
    int n;
    cout << "Ingrese el número de ciudades: ";
    cin >> n;

    Grafo g(n);
    g.ingresarNombres();
    g.ingresarDistancias();
    g.resolverTSP();

    return 0;
}

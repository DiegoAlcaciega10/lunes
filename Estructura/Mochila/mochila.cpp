#include <iostream>
#include <string>
using namespace std;

class Objeto {
public:
    string nombre;
    int peso;
    int valor;

    Objeto() {}
    Objeto(string n, int p, int v) : nombre(n), peso(p), valor(v) {}
};

class Mochila {
private:
    int capacidad;
    int cantidadObjetos;
    Objeto* objetos;

public:
    Mochila(int cap, int cant) {
        capacidad = cap;
        cantidadObjetos = cant;
        objetos = new Objeto[cantidadObjetos];
    }

    ~Mochila() {
        delete[] objetos;
    }

    void ingresarObjetos() {
        for (int i = 0; i < cantidadObjetos; ++i) {
            string nombre;
            int peso, valor;
            cout << "\nObjeto " << (i + 1) << ":\n";
            cout << "Nombre: ";
            cin >> nombre;
            cout << "Peso (kg): ";
            cin >> peso;
            cout << "Valor ($): ";
            cin >> valor;
            objetos[i] = Objeto(nombre, peso, valor);
        }
    }

    void resolverMochila() {
        // Crear matriz dinámica DP
        int** dp = new int*[cantidadObjetos + 1];
        for (int i = 0; i <= cantidadObjetos; ++i) {
            dp[i] = new int[capacidad + 1];
            for (int j = 0; j <= capacidad; ++j) {
                dp[i][j] = 0;
            }
        }

        // Programación dinámica
        for (int i = 1; i <= cantidadObjetos; ++i) {
            for (int w = 0; w <= capacidad; ++w) {
                if (objetos[i - 1].peso <= w) {
                    dp[i][w] = max(dp[i - 1][w],
                                   dp[i - 1][w - objetos[i - 1].peso] + objetos[i - 1].valor);
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }

        cout << "\nValor máximo que puedes llevar: " << dp[cantidadObjetos][capacidad] << " $\n";

        // Mostrar objetos seleccionados
        cout << "Objetos seleccionados:\n";
        int w = capacidad;
        for (int i = cantidadObjetos; i > 0; --i) {
            if (dp[i][w] != dp[i - 1][w]) {
                cout << "- " << objetos[i - 1].nombre
                     << " (Peso: " << objetos[i - 1].peso
                     << ", Valor: " << objetos[i - 1].valor << ")\n";
                w -= objetos[i - 1].peso;
            }
        }

        // Liberar memoria
        for (int i = 0; i <= cantidadObjetos; ++i) {
            delete[] dp[i];
        }
        delete[] dp;
    }
};

int main() {
    int capacidad, cantidad;

    cout << "Ingrese la capacidad de la mochila (kg): ";
    cin >> capacidad;

    cout << "Ingrese el número de objetos disponibles: ";
    cin >> cantidad;

    Mochila m(capacidad, cantidad);
    m.ingresarObjetos();
    m.resolverMochila();

    return 0;
}

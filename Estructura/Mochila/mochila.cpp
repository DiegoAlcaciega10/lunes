#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Objeto {
public:
    string nombre;
    int peso;
    int valor;

    Objeto(string n, int p, int v) : nombre(n), peso(p), valor(v) {}
};

class Mochila {
private:
    int capacidad;
    vector<Objeto> objetos;

public:
    Mochila(int cap) : capacidad(cap) {}

    void agregarObjeto(const Objeto& obj) {
        objetos.push_back(obj);
    }

    void resolver() {
        int n = objetos.size();
        vector<vector<int>> dp(n + 1, vector<int>(capacidad + 1, 0));

        // Programación dinámica
        for (int i = 1; i <= n; ++i) {
            for (int w = 0; w <= capacidad; ++w) {
                if (objetos[i - 1].peso <= w) {
                    dp[i][w] = max(dp[i - 1][w],
                                   dp[i - 1][w - objetos[i - 1].peso] + objetos[i - 1].valor);
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }

        // Mostrar resultado
        cout << "\nValor máximo que puedes llevar: " << dp[n][capacidad] << endl;

        // Opcional: Mostrar objetos seleccionados
        cout << "Objetos seleccionados:\n";
        int w = capacidad;
        for (int i = n; i > 0; --i) {
            if (dp[i][w] != dp[i - 1][w]) {
                cout << "- " << objetos[i - 1].nombre << " (Peso: "
                     << objetos[i - 1].peso << ", Valor: "
                     << objetos[i - 1].valor << ")\n";
                w -= objetos[i - 1].peso;
            }
        }
    }
};
int main() {
    int capacidad, cantidad;

    cout << "Ingrese la capacidad de la mochila (kg): ";
    cin >> capacidad;

    cout << "Ingrese el número de objetos disponibles: ";
    cin >> cantidad;

    Mochila mochila(capacidad);

    for (int i = 0; i < cantidad; ++i) {
        string nombre;
        int peso, valor;

        cout << "\nObjeto " << (i + 1) << ":\n";
        cout << "Nombre: ";
        cin >> nombre;
        cout << "Peso (kg): ";
        cin >> peso;
        cout << "Valor ($): ";
        cin >> valor;

        mochila.agregarObjeto(Objeto(nombre, peso, valor));
    }

    mochila.resolver();

    return 0;
}

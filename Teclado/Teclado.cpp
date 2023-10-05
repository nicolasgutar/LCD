#include "Teclado.h"
#include <iostream>

using namespace std;

Teclado::Teclado() {
    DigitalIn row[] = {D8, D9, D10, D11};
    DigitalOut col[] = {D12, D14, D15};
    this->filas = row;
    this->columnas = col;
    this->teclado = {
        {"1", "2", "3"},
        {"4", "5", "6"},
        {"7", "8", "9"},
        {"*", "0", "#"}
    };
    this->numeroFilas = teclado.size();
    this->numeroColumnas = teclado[0].size();
}

Teclado::Teclado(DigitalIn filas[], DigitalOut columnas[], vector<vector<string>> teclado) {
    this->filas = filas;
    this->columnas = columnas;
    this->teclado = teclado;
    this->numeroFilas = teclado.size();
    this->numeroColumnas = teclado[0].size();
}

string Teclado::tecladoMatricial() {
    for (int i = 0; i < numeroColumnas; i++) {
        columnas[i] = 0;

        for (int j = 0; j < numeroFilas; j++) {
            if (filas[j] == 0) {
                while (filas[j] == 0);
                columnas[i] = 1;
                return teclado[j][i];
            }
        }

        columnas[i] = 1;
    }

    return "";
}

string Teclado::escribir() {
    string tecla = "";
    string input = "";

    while (tecla != "*") {
        tecla = tecladoMatricial();

        if (tecla != "") {
            if (tecla == "#") {
                if (input.size() != 0) input.pop_back();
                cout << endl << input;
            } else {
                input += tecla;
                cout << tecla;
            }
            cout.flush();
        }
    }

    cout << endl;

    return input;
}

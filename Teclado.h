#ifndef TECLADO_H
#define TECLADO_H

#include "mbed.h"
#include <string>
#include <vector>

using namespace std;

class Teclado {
    public:
        Teclado();
        Teclado(DigitalIn filas[], DigitalOut columnas[], vector<vector<string>> teclado = {});
        string escribir();

    private:
        string tecladoMatricial();
        DigitalIn* filas;
        DigitalOut* columnas;
        int numeroFilas;
        int numeroColumnas;
        vector<vector<string>> teclado;
};

#endif // TECLADO_H

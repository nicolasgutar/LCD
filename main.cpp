
/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <iostream>
#include <string>
#include "TextLCD.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     300ms

// Objeto para establecer la comunicación serial con el Pc
UnbufferedSerial serial(USBTX, USBRX, 9600);

// Objeto pa leer la matriz numerica
TextLCD display(D2,D3,D4,D5,D6,D7,TextLCD::LCD16x2);

DigitalIn filas[] = {D8, D9, D10, D11};
DigitalOut columnas[] = {D12, D14, D15};

using namespace std;

string teclado[][3] = {
    {"1", "2", "3"},
    {"4", "5", "6"},
    {"7", "8", "9"},
    {"*", "0", "#"}
};

void escribirLCD(string s) {
    display.cls();
    display.printf("%s", s.c_str());
    wait_us(2000000);
}

string tecladoMatricial() {
    for (int i=0; i<3; i++) {
        columnas[i] = 0;

        for (int j=0; j<4; j++) {
            if (filas[j]==0) {
                while (filas[j]==0);
                columnas[i] = 1;
                return teclado[j][i];
            }
        }

        columnas[i] = 1;
    }

    return "";
}

string escribir() {
    string tecla = "";
    string input = "";

    while (tecla!="*") {
        tecla = tecladoMatricial();

        if (tecla!="") {
            if (tecla=="#") {
                if (input.size()!=0) input.pop_back();
                cout << endl << input;
            } else {
                input += tecla;
                cout << tecla << endl;
            }
            cout.flush();
        }
    }
    
    cout << endl;

    return input;
}

void raices() {
    float CA,CB,CC;
    cout << "Dada la forma del polinomio AX^2 + BX + C" << endl;
    cout << "Introduzca el coeficiente A" << endl;
    escribirLCD("Polinomio AX^2 + BX + C");
    escribirLCD("Coeficiente A: ");
    CA = stoi(escribir());
    cout << "Introduzca el coeficiente B" << endl;
    escribirLCD("Coeficiente B: ");
    CB = stoi(escribir());
    cout << "Introduzca el coeficiente C" << endl;
    escribirLCD("Coeficiente C: ");
    CC = stoi(escribir());

    float R1, R2;
    R2 = CB*CB - 4*CA*CC;

    if (R2 < 0){
        escribirLCD("No tiene raices reales");
    } else {
        R1 = (-1*CB + sqrt(R2))/(2*CA);
        R2 = (-1*CB - sqrt(R2))/(2*CA);
        cout << "Raiz 1 = " << R1 << endl;
        cout << "Raiz 2 = " << R2 << endl;
        escribirLCD("Raiz 1 = "+to_string(R1));
        escribirLCD("Raiz 2 = "+to_string(R2));
    }
}

void calificacion() {
    escribirLCD("Introduzca nota de 0-10: ");
    int nota = stoi(escribir());
    string calificacion;
    if (nota <= 3) {
        calificacion = "A";
    } else if (nota <= 4) {
        calificacion = "B";
    } else if (nota <= 5) {
        calificacion = "C";
    } else if (nota <= 7) {
        calificacion = "D";
    } else if (nota < 9) {
        calificacion = "E";
    } else if (nota <= 10) {
        calificacion = "F";
    } else {
        calificacion = "La nota no es válida";
    }

    escribirLCD("La nota es: "+calificacion);
    cout << calificacion << endl;
}

void Leds() {
    // Inicializando leds
    PwmOut ledR(LED1);
    PwmOut ledG(LED2);
    PwmOut ledB(LED3);

    // Determinar periodo de los leds
    ledR.period(0.01);
    ledG.period(0.01);
    ledB.period(0.01);
    
    // Obtener los colores
    escribirLCD("Intensidad rojo (R):");
    float red = stoi(escribir());

    while (red>255) {
        escribirLCD("Rango (0-255): ");
        red = stoi(escribir());
    }

    escribirLCD("Intensidad verde (G):");
    float green = stoi(escribir());

    while (green>255) {
        escribirLCD("Rango (0-255): ");
        green = stoi(escribir());
    }
    escribirLCD("Intensidad azul (B):");
    float blue = stoi(escribir());

    while (blue>255) {
        escribirLCD("Rango (0-255): ");
        blue = stoi(escribir());
    }

    // Calcular valor de color
    float scaledRed = red / 255;
    float scaledGreen = green / 255;
    float scaledBlue = blue / 255;

    // Asignar valor de color a los leds
    ledR = 1 - scaledRed;
    ledG = 1 - scaledGreen;
    ledB = 1 - scaledBlue;
}

void menu() {
    int opcion;
    cout << "Escoja opcion" << endl;
    cout << "1)raices" << endl;
    cout << "2)nota" << endl;
    cout << "3)LED con RGB" << endl;
    escribirLCD("Escoja opcion");
    escribirLCD("1)raices");
    display.locate(0,1);
    escribirLCD("2)nota");
    escribirLCD("3)LED con RGB");
    opcion = stoi(escribir());

    while (opcion < 1 || opcion >3){
        cout << "Ingrese opcion valida" << endl;
        escribirLCD("Ingrese opcion valida");
        opcion = stoi(escribir());
    }

    if (opcion == 1){
        raices();
    } else if (opcion == 2){
        calificacion();
    } else if(opcion == 3){
        Leds();
    }
}

int main() {
    while (true) {
        cout << "-----------------------" << endl;
        cout << "Para dar enter oprimir *" << endl;
        cout << "Para eliminar oprimir #" << endl;
        cout << "-----------------------" << endl;
        escribirLCD("Enter *");
        escribirLCD("Eliminar #");
        menu();
        cout << endl << "===============================" << endl << endl;
    }
}
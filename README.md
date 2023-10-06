
Se conmienza importando las librerias e inicializando las conexiones como siempre.

La librería del LCD tuvo que ser debugueada para que pudiera compilar, los tiempos con los que venia se 
cambiaron de ms a us.

#include "mbed.h"
#include <iostream>
#include <string>
#include "TextLCD.h"
#include "Teclado.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     300ms

using namespace std;

// Objeto para establecer la comunicación serial con el Pc
UnbufferedSerial serial(USBTX, USBRX, 9600);
// Objeto pa leer la matriz numerica
TextLCD display(D2,D3,D4,D5,D6,D7,TextLCD::LCD16x2);

Teclado teclado;


Lo unico que tuvimos que hacer de especial fue modificar los pines asignados al teclado y al LCD para que no tuvieran conflictos entre si.



Utilizando los metodos de la librería del LCD, desarrollamos el metodo escribirLCD() que limpia lo que haya en pantalla y muestra la cadena de texto

Como se tenía un espacio mas restringido, tuvimos que adaptar lo que se tenía previamente para que fuera más corto. Además, dejamos que se muestre
un par de segundos, suficiente para que el usuario lea el mensaje, y se muestre la parte restante.

void escribirLCD(string s) {
    display.cls();
    display.printf("%s", s.c_str());
    wait_us(2000000);
}


De ahí para adelante el codigo es practicamente lo mismo que el del parcial. Simplemente se cambian los couts por escribirLCD() pues
el funcionamiento es el mismo, simplemente se muestra en la pantallaLCD en vez de terminal
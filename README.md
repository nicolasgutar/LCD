Este codigo es una continuación del proyecto para el parcial de arquitectura de hardware, este trataba de una aplicación de consola con 3 opciones.
1. Busqueda de raices de un polinomio de grado 2 (Fórmula cuadrática).
2. Metodo de calificación (Se asigna una letra segun la calificación ingresada).
3. Cambiar el color de un led con sus respectivos valores R-G-B.

*Link proyecto parcial:* https://github.com/DavidBetancurRamirez/teclado_matricial

## Documentación de codigo 
### LCD

La librería del LCD tuvo que ser debugueada para que pudiera compilar, los tiempos con los que venia se cambiaron de ms a us.

    TextLCD display(D2,D3,D4,D5,D6,D7,TextLCD::LCD16x2);

Utilizando los metodos de la librería del LCD, desarrollamos el metodo escribirLCD() que limpia lo que haya en pantalla y muestra la cadena de texto

    void escribirLCD(string s) {
        display.cls();
        display.printf("%s", s.c_str());
        wait_us(2000000);
    }

Como se tenía un espacio mas restringido, fue necesario adaptar los mensajes por unos más cortos. Además, dejamos que se muestre un par de segundos, suficiente para que el usuario lea el mensaje, y se muestre la parte restante.

---

### Teclado
Todo lo relacionado con el teclado matricial fue separado del codigo e importado a este en modo de libreria, denominada *Teclado*, por lo cual con crear un objeto teclado es suficiente para usar sus metodos.

    Teclado teclado;

Se crearon 2 opciones para crear un objeto teclado:

**3X4**

Viene por defecto

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

**Cualquier tamaño**

Se le deben pasar los pines de filas y columnas, ademas de la posicion de las teclas.

    Teclado::Teclado(DigitalIn filas[], DigitalOut columnas[], vector<vector<string>> teclado) {
        this->filas = filas;
        this->columnas = columnas;
        this->teclado = teclado;
        this->numeroFilas = teclado.size();
        this->numeroColumnas = teclado[0].size();
    }

Los demás metodos son relativamente los mismos a los anteriores, se les añadio una mayor flexibilidad para el caso de que el teclado sea diferente al 3x4.

---

### Resto de codigo
De ahí para adelante el codigo es practicamente lo mismo que el del parcial. Simplemente **se cambian los couts por escribirLCD()**, ya que se muestra en la pantallaLCD en vez de terminal.

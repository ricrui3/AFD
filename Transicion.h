//
// Created by rubik on 26/05/15.
//

#ifndef AFD_TRANSICION_H
#define AFD_TRANSICION_H

#include "iostream"
#include "Estado.h"

using namespace std;

class Estado;

class Transicion {
private:
    string nombre;
    Estado* estado1;
    Estado* estado2;
    char simbolo;

public:
    Transicion();

    Transicion(string name, Estado * state1, Estado * state2, char simbol);

    const string &getNombre() const { return nombre; }

    void setNombre(const string &nombre) { Transicion::nombre = nombre; }

    Estado *getEstado1() const { return estado1; }

    void setEstado1(Estado * estado1) { Transicion::estado1 = estado1; }

    Estado *getEstado2() const { return estado2; }

    void setEstado2(Estado * estado2) { Transicion::estado2 = estado2; }

    char getSimbolo() const { return simbolo; }

    void setSimbolo(char simbolo) { Transicion::simbolo = simbolo; }
};


#endif //AFD_TRANSICION_H

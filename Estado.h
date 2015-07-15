//
// Created by rubik on 26/05/15.
//

#ifndef AFD_ESTADO_H
#define AFD_ESTADO_H


#include "Transicion.h"
#include <iostream>
#include <vector>

using namespace std;

class Transicion;

class Estado {
private:
    string nombre;
    bool inicial;
    bool final;


public:
    Estado();

    Estado(string name, bool ini, bool fin);

    string getNombre() const { return nombre; }

    void setNombre(string nombre) { Estado::nombre = nombre; }

    bool getInicial() const { return inicial; }

    void setInicial(bool inicial) { Estado::inicial = inicial; }

    bool getFinal() const { return final; }

    void setFinal(bool final) { Estado::final = final; }
};


#endif //AFD_ESTADO_H

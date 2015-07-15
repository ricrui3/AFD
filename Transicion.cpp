//
// Created by rubik on 26/05/15.
//

#include "Transicion.h"

Transicion::Transicion() {
    setNombre("noname");
    setEstado1(NULL);
    setEstado2(NULL);
}

Transicion::Transicion(string name, Estado * state1, Estado * state2, char simbol) {
    setNombre(name);
    setEstado1(state1);
    setEstado2(state2);
    setSimbolo(simbol);
}

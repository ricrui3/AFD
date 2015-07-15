//
// Created by rubik on 26/05/15.
//

#include "Estado.h"

Estado::Estado() {
    setNombre("noname");
    setInicial(false);
    setFinal(false);
}

Estado::Estado(string name, bool ini, bool fin) {
    setNombre(name);
    setInicial(ini);
    setFinal(fin);
}

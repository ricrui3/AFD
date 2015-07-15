#include <iostream>
#include <vector>
#include <algorithm>
#include "Estado.h"
#include <fstream>

using namespace std;
class Estado;

void menu();
void ingresarEstados(vector<Estado>* Estados);
bool evaluaNombres(vector<string>& nombres, string nombreE);
void leeEstados(vector<Estado>& Estados);
void tablaSimbolos(vector<char>* Simbolos);
bool evaluaSimbolos(vector<char>&simbolos, char simbolo);
void leeSimbolos(vector<char>& Simbolos);
void tablaDeTransiciones(vector<Transicion>* Transciones, vector<Estado>& Estados, vector<char>& Simbolos);
Estado * evaluaEstados(vector<Estado>& Estados, string state);
bool evaluaCadena(vector<Estado>& Estados, vector<char>&simbolos, vector<Transicion>& Transiciones, string cadena);
void dibujarAFD(vector<Estado>& Estados, vector<Transicion>& Transiciones);

int main()
{
    vector<Estado> Estados; // vector que guarda el nombre y si es inicial y/o final de cada uno de los estados del AFD
    vector<char> Simbolos; // vector que guarda los simbolos que se usan en el AFD
    vector<Transicion> TablaTrans; // Tabla de transiciones de cada uno de los estados
    string cadena;

    bool automataIngresado = false;  // Aun no se ha ingresado automata

    int op;

    do{
        menu(); //Muestra el menu con las opciones;
        cin>>op;
        fflush(stdin);
        switch(op){

            case 1:
                Estados.clear();//-----
                Simbolos.clear();//----Limpia la Tabla de transiciones, estados y simbolos
                TablaTrans.clear();//--

                ingresarEstados(&Estados);// Permite al usuario ingresar los estados del AFD
                leeEstados(Estados); // Lee todos los estados ingresados por el usuario

                tablaSimbolos(&Simbolos); // Pregunta por los simbolos a usar y los almacena
                leeSimbolos(Simbolos); //Muestra los simbolos ingresados
                
                tablaDeTransiciones(&TablaTrans,Estados,Simbolos);

                dibujarAFD(Estados, TablaTrans);

                automataIngresado = true;
                break;

            case 2:
                if(automataIngresado){
                    cout << endl << "Ingrese la cadena a evaluar (escriba \"vacia\" en caso dado): " << endl;
                    cin >> cadena;
                    if (evaluaCadena(Estados, Simbolos, TablaTrans, cadena)){
                        cout << "Cadena aceptada, Felicidades!" << endl;
                    }
                    else {
                        cout << "Parece que no hubo tanta suerte" << endl;
                    }
                }
                else
                    cout << endl << "\t\tNo hay automata ingresado" << endl;
                break;

            case 3:
                cout << "caso 3";
                exit(0);

            case 4:
                if(automataIngresado){
                    system("shotwell Grafo.png&");
                }
                else{
                    cout << "No se ha ingresado un atomata!";
                }
            default:
                cout << "\n\tOpcion incorrecta..!\n";
        }

        //cout << "\n\n"; system("pause"); system("cls");

    }while(op!=3);
    return 0;
}
//--------------------------------------------------------------------------------------------------------
void menu(){                                          //Imprime el menu en la pantalla
    cout << "\n\t\t AUTOMATA FINITO DETERMINISTA\n\n";
    cout << "\t 1. Ingresar Automata \n";
    cout << "\t 2. Verificar palabra              \n";
    cout << "\t 3. Salir                          \n";
    cout << "\t 4. Mostrar dibujo del automata\n";
    cout << "\t Ingrese opcion: ";
}

void ingresarEstados(vector<Estado>* Estados){
    Estado aux;
    int noEstados;
    bool inicial = false, final = false, corroboracion, inicialFlag = false;
    string nombreEstado, Sinicial, Sfinal;
    vector<string> nombres;

    cout << "Cuantos Estados desea ingresar?: "; // Recibe el numero estados
    cin >> noEstados;

    for (int i = 0; i < noEstados; ++i) {
        cout << endl <<"Nombre del estado " << i+1 << ": ";
        cin >> nombreEstado;

        if (evaluaNombres(nombres, nombreEstado) || i == 0) {  //Evalua que no haya nombres repetidos
            nombres.push_back(nombreEstado);
            if(!inicialFlag) {
                corroboracion = false;
                while (!corroboracion) {
                    cout << endl << "Es estado inicial? (Y = si, N = no)";
                    cin >> Sinicial;
                    if (Sinicial == "Y" || Sinicial == "y" || Sinicial == "s" || Sinicial == "S") {
                        inicial = true;
                        corroboracion = true;
                        inicialFlag = true;
                    }
                    else if (Sinicial == "N" || Sinicial == "n") {
                        inicial = false;
                        corroboracion = true;
                    }
                    else {
                        cout << "Error! opcion equivocada!";
                        corroboracion = false;
                    }
                }
            }
            else{
                cout << endl << "\t Ya existe un estado inicial!" << endl;
                inicial = false;
            }

            corroboracion = false;

            while(!corroboracion) {
                cout << endl << "Es estado final? (Y = si, N = no)";
                cin >> Sfinal;
                if(Sfinal == "Y" || Sfinal == "y" || Sfinal == "s" || Sfinal == "S") {
                    final = true;
                    corroboracion = true;
                }
                else if(Sfinal == "N" || Sfinal == "n") {
                    final = false;
                    corroboracion = true;
                }
                else{
                    cout << "Error! opcion equivocada!";
                    corroboracion = false;
                }
            }
            aux = Estado(nombreEstado,inicial,final);
            Estados->push_back(aux);
        }
        else{
            cout << "Ya existe un estado con el mismo nombre, ingrese otro nombre.";
            i--;
        }
    }
    Estados -> push_back(Estado("nulo", 0, 0));
}

bool  evaluaNombres(vector<string>& nombres, string nombreE){
    for (int i = 0; i < nombres.size(); ++i) {
        if(nombres.at(i) == nombreE)
            return false;
    }
    return true;
}

void leeEstados(vector<Estado>& Estados) {
    cout << "\nEstados:";
    for (int i = 0; i < Estados.size(); ++i) {
        cout << endl;
        cout << "\t\tNombre: " << Estados.at(i).getNombre();
        cout << "\tInicial: " << Estados.at(i).getInicial();
        cout << "\tFinal: " << Estados.at(i).getFinal() << endl;
    }
}

void tablaSimbolos(vector<char>* Simbolos){
    int noSimbolos;
    char simbolo;

    cout << "\nCuantos simbolos desea ingresar?";
    cin >> noSimbolos;

    for (int i = 0; i < noSimbolos; ++i) {
        cout << "\n\tCual es el simbolo que desea ingresar?";
        cin >> simbolo;
        if(evaluaSimbolos(*Simbolos, simbolo) || i == 0){
            Simbolos->push_back(simbolo);
        }
        else{
            cout << "Ya existe ese simbolo, INTENTE DE NUEVO!";
            i--;
        }
    }
}

bool  evaluaSimbolos(vector<char>& simbolos, char simbolo){
    for (int i = 0; i < simbolos.size(); ++i) {
        if(simbolos.at(i) == simbolo)
            return false;
    }
    return true;
}

void leeSimbolos(vector<char>& Simbolos) {
    cout << "Simbolos:" << endl;
    for (int j = 0; j < Simbolos.size(); ++j) {
        cout << "\t "<<Simbolos.at(j);
    }
    cout << endl;
}

void tablaDeTransiciones(vector<Transicion>* Transciones,vector<Estado>& Estados, vector<char>& Simbolos){
    string sigEstado, nomAux;
    char auxC;

    cout << "\n";
    Estado* aux;

    for (int i = 0; i < Estados.size(); ++i) {
        for (int j = 0; j < Simbolos.size(); ++j) {
            if (Estados.at(i).getNombre() != "nulo") {
                auxC = Simbolos.at(j);
                cout << "\nIngrese el siguiente estado para el estado " << Estados.at(i).getNombre() << " con el simbolo " << auxC << "\n(Ingrese \"nulo\" si no desea ir a ningun estado):";
                cin >> sigEstado;
                if(sigEstado == "nulo" || sigEstado == "\"nulo\""){
                    nomAux = Estados.at(i).getNombre() + Simbolos.at(j);
                    Transciones->push_back(Transicion( nomAux, &Estados.at(i), evaluaEstados( Estados, sigEstado), auxC));
                }
                else if(evaluaEstados(Estados,sigEstado) == NULL){
                    cout << "\n\tNo existe ese estado, por favor ingrese un estado valido" << endl;
                    leeEstados(Estados);
                    j--;
                }
                else{
                    nomAux = Estados.at(i).getNombre() + Simbolos.at(j);
                    Transciones->push_back(Transicion(nomAux,&Estados.at(i),evaluaEstados(Estados,sigEstado),auxC));
                }
            } else {
                nomAux = Estados.at(i).getNombre() + Simbolos.at(j);
                Transciones->push_back(Transicion(nomAux,&Estados.at(i),evaluaEstados(Estados,sigEstado),auxC));
            }
        }
    }
    cout << "\n";
}

Estado * evaluaEstados(vector<Estado>& Estados, string state){
    for (int k = 0; k < Estados.size(); ++k) {
        if(Estados.at(k).getNombre() == state){
            return &Estados.at(k);
        }
    }
    return NULL;
}

bool evaluaCadena(vector<Estado>& Estados, vector<char>&simbolos, vector<Transicion>& Transiciones, string cadena){
    Estado * aux = NULL;

    string string1, string2;
    char char1, char2;

    char caracAct;
    for (int j = 0; j < Estados.size(); ++j) {
        if(Estados.at(j).getInicial() == 1){
            aux = &Estados.at(j);
            break;
        }
    }
    if(cadena == "vacia" || "VACIA" && aux->getFinal() == 1){
        return 1;
    }
    for (int i = 0; i < cadena.size(); ++i) {
        caracAct = cadena.at(i);
        if(evaluaSimbolos(simbolos,caracAct)){
            cout << "Cadena no aceptada por contener caracter erroneo. ";
            return 0;
        }
        for (int j = 0; j < Transiciones.size(); ++j) {
            string1 = Transiciones.at(j).getEstado1()->getNombre();
            string2 = aux->getNombre();
            char1 = caracAct;
            char2 = Transiciones.at(j).getSimbolo();
            if(string1 == string2 && char1 == char2){
                aux = Transiciones.at(j).getEstado2();
                break;
            }
        }
    }
    if(aux->getFinal())
        return 1;
    else
        return 0;
}

void dibujarAFD(vector<Estado>& Estados, vector<Transicion>& Transiciones){
    char data[100];

    // open a file in write mode.
    ofstream outfile;
    outfile.open("Grafo.dot");

    // write inputted data into the file.
    outfile << "digraph AFD{" << endl;
    outfile << "\tnode [shape = point ]; qi" << endl;

    for (int i = 0; i < Estados.size(); ++i) {
        if(Estados.at(i).getFinal() == 1)
            outfile << "\t" << Estados.at(i).getNombre() << "[shape = doublecircle];" << endl;
        else {
            if(Estados.at(i).getNombre() != "nulo")
                outfile << "\t" << Estados.at(i).getNombre() << "[shape = circle];" << endl;
        }
    }

    for (int j = 0; j < Estados.size(); ++j) {
        if(Estados.at(j).getInicial() == 1){
            outfile << "\n\t" << "qi->"<< Estados.at(j).getNombre() << endl;
        }
    }


    for (int k = 0; k < Transiciones.size(); ++k) {
        if (Transiciones.at(k).getEstado2()->getNombre() != "nulo" && Transiciones.at(k).getEstado1()->getNombre() != "nulo") {
            //Escribe el comando para trancisiones en el archivo .dot------------------------------------
            outfile << "\t" << Transiciones.at(k).getEstado1()->getNombre() <<"->";
            outfile << Transiciones.at(k).getEstado2()->getNombre() << "[label =";
            outfile << Transiciones.at(k).getSimbolo() <<"];" << endl;
            //-------------------------------------------------------------------------------------------
        }
    }

    outfile << "}";
    // close the opened file.
    outfile.close();

    system("dot Grafo.dot -Tpng > Grafo.png");
    system("shotwell Grafo.png& ");
}
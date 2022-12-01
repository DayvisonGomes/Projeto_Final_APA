#include "../include/treno.h"

Treno::Treno(int id, int capacidade){
    this->id = id;
    this->capacidade = capacidade;
}

Treno::~Treno(){}

void Treno::set_capacidade(int new_capacidade){
    this->capacidade = new_capacidade;
}

int Treno::get_capacidade(){
    return this->capacidade;
}

void Treno::print_itens(){

    for (int i = 0; i < itens.size(); i++){
        if (itens[i] != 0){
            cout << "Treno: " << id + 1 << " Item: " << itens[i] << " Peso: " << pesos[i] << endl;  

        }
    }
}
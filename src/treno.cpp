#include "../include/treno.h"

Treno::Treno(int capacidade){
    this->capacidade = capacidade;
}

Treno::~Treno(){}

void Treno::set_capacidade(int new_capacidade){
    this->capacidade = new_capacidade;
}

int Treno::get_capacidade(){
    return this->capacidade;
}

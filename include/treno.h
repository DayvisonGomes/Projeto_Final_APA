#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <typeinfo>

using namespace std;

class Treno {
    
private:

    int capacidade;
    
public:

    int id;
    vector<int> itens;
    vector<int> pesos;

    Treno(int id, int capacidade);
    ~Treno();

    void set_capacidade(int new_capacidade);
    int get_capacidade();

    void print_itens();

};

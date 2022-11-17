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

    vector<int> itens;

    Treno(int capacidade);
    ~Treno();

    void set_capacidade(int new_capacidade);
    int get_capacidade();

};

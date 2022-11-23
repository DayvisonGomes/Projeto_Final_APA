#include "treno.h"

void ler_arquivo(string path, vector<int> &info, vector<int> &vetor_p, vector<int> &vetor_L);
void guloso(vector<Treno*> *trenos, int numero_presentes, int capacidade, int k,vector<int> &vetor_p, vector<int> &vetor_L);
void insertion_sort(vector<int> &p);
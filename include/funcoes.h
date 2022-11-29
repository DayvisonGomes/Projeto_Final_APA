#include "treno.h"

void ler_arquivo(string path, vector<int> &info, vector<int> &vetor_p, vector<int> &vetor_L);
int solucao(vector<Treno*> &trenos, int numero_presentes, int print);
void guloso(vector<Treno*> *trenos, int numero_presentes, int capacidade, int k,vector<int> &vetor_p, vector<int> &vetor_L);
void insertion_sort(vector<int> &p);
void treno_furado(vector<Treno*> &trenos, vector<int> &vetor_L);
void swap(vector<Treno*> &trenos, vector<int> &vetor_L, int capacidade_maxima);
int verificar_tuplas(Treno *treno, int item, vector<int> &vetor_l);
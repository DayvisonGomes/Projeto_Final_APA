#include "treno.h"

void ler_arquivo(string path, vector<string> *info, vector<string> *vetor_p, vector<string> *vetor_L);
void troca_tipo(vector<string> &vetor_p, vector<string> &vetor_L, vector<int> *aux_vetor_p, vector<int> *aux_vetor_L);
void preenche(int numero_presentes, int capacidade, int k, vector<int> aux_p);
void guloso(Treno treno,int numero_presentes, int capacidade, vector<int> aux_p);

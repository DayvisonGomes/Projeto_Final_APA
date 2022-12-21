#include "treno.h"

void ler_arquivo(string path, vector<int> &info, vector<int> &vetor_p, vector<vector<int>> &vetor_L);
int solucao(vector<Treno*> &trenos, int numero_presentes, int print);
void guloso(vector<Treno*> *trenos, int numero_presentes, int capacidade, int k,vector<int> &vetor_p, vector<vector<int>> &vetor_L);
void insertion_sort(vector<int> &p);
int saco_vazio(vector<Treno*> &trenos, vector<vector<int>> &vetor_L);
int swap(vector<Treno*> &trenos, vector<vector<int>> &vetor_L, int capacidade_maxima);
int verificar_tuplas(Treno *treno, int item, vector<vector<int>> &vetor_L);
void vnd(vector<Treno*> &trenos, vector<vector<int>> &vetor_L, int capacidade_maxima, int numero_presentes, int r, int s0);
void ils(vector<Treno*> &trenos, vector<vector<int>> &vetor_L, int capacidade_maxima, int numero_presentes, int r, int s0);
int swap_pertubacao(vector<Treno*> &trenos, vector<vector<int>> &vetor_L, int capacidade_maxima);
void copia_vetor_guloso(vector<Treno*> &trenos, vector<Treno*> &trenos_guloso);

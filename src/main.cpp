#include "../include/funcoes.h"

int main(){
  vector<string> info, vetor_p, vetor_L;
  vector<int> aux_p, aux_L;
  string path = "../instancias/instancia1.txt";

  ler_arquivo(path, &info, &vetor_p, &vetor_L);
  
  int numero_presentes = stoi(info[0]);
  int k = stoi(info[1]);
  int Q = stoi(info[2]);
  int numero_elementos_em_L = stoi(info[3]);
  int solucao_final = 0;

  troca_tipo(vetor_p, vetor_L, &aux_p, &aux_L);

  


  
  return 0;

}
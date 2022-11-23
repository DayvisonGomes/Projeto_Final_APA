#include "../include/funcoes.h"

int main(){
  vector<int> vetor_p, vetor_L, info;
  vector<Treno*> trenos;
  string path = "../instancias/n40_k150_C.txt";

  ler_arquivo(path, info, vetor_p, vetor_L);
  
  int numero_presentes = info[0];
  int k = info[1];
  int Q = info[2];
  int numero_elementos_em_L = info[3];
  
  guloso(&trenos, numero_presentes, Q, k, vetor_p, vetor_L);

  int count = 0;
  int count2 = 0;

  for (int i = 0; i < trenos.size(); i++){
    if (!trenos[i]->itens.empty()){
      trenos[i]->print_itens();
      count += 1;

    }
  }

  for (int i = 0; i < trenos.size(); i++){
    if (!trenos[i]->itens.empty()){

      for (int j = 0; j < trenos[i]->itens.size(); j++){
        count2 += 1;
      }

    }
    
  }

  cout << "Solucao: " << count << endl;
  
  return 0;

}
#include "../include/funcoes.h"

int main(){
  vector<int> vetor_p, vetor_L;
  vector<string> info;

  vector<Treno*> trenos;
  string path = "../instancias/instancia1.txt";

  ler_arquivo(path, info, vetor_p, vetor_L);
  
  int numero_presentes = stoi(info[0]);
  int k = stoi(info[1]);
  int Q = stoi(info[2]);
  int numero_elementos_em_L = stoi(info[3]);

  guloso(&trenos, numero_presentes, Q, k, vetor_p, vetor_L);

  trenos[0]->print_itens();
  cout << "" << endl;
  trenos[1]->print_itens();

  return 0;

}
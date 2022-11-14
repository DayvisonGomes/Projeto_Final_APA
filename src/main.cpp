#include "../include/funcoes.h"

int main(){
  vector<string> info, vetor_p, vetor_L;
  string path = "../instancias/instancia1.txt";
  
  ler_arquivo(path, &info, &vetor_p, &vetor_L);

  cout << typeid(info[0]).name() << endl;
  cout << info[0] << endl;

  return 0;
}


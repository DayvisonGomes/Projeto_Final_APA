#include "../include/funcoes.h"

int main(){

  vector<string> instancias = {
    "n30_k150_A","n30_k150_B","n30_k150_C",
    "n40_k150_A","n40_k150_B","n40_k150_C",
    "n40_k200_A","n40_k200_B",
    "n60_k130_A","n60_k130_B","n60_k130_C",
    "n60_k150_A","n60_k150_B",
    "n80_k130_A","n80_k130_B","n80_k130_C",
    "n120_k150_A","n120_k150_B"
  };

  vector<int> vetor_solu_otimos = {
    12,12,13,16,16,16,12,12,30,30,30,25,25,39,39,39,48,48
  };

  int i = 17;

  cout << "Algoritimo Guloso\n" << endl;

  vector<int> vetor_p, vetor_L, info;
  vector<Treno*> trenos;
  string path = "../instancias/" + instancias[i] + ".txt";
    
  ler_arquivo(path, info, vetor_p, vetor_L);
    
  int numero_presentes = info[0];
  int k = info[1];
  int Q = info[2];
  int numero_elementos_em_L = info[3];
  int solu_viavel = 0, best_solution = 1000;
  int iteracoes_vnd = 50;

  clock_t tInicio, tFim, tDecorrido;

  tInicio = clock();

  guloso(&trenos, numero_presentes, Q, k, vetor_p, vetor_L);
  solu_viavel = solucao(trenos, numero_presentes, 0);

  tFim = clock();
  tDecorrido = ((tFim - tInicio) / (CLOCKS_PER_SEC / 1000));

  cout << "Instancia: " << instancias[i] << endl;
  cout << "Solucao gulosa: " << solu_viavel << endl;
  cout << "Solucao otima: " << vetor_solu_otimos[i] << endl;
  cout << "Tempo em ms: " << tDecorrido << endl;
  cout << endl;

  cout << "Vnd\n" << endl;
  vnd(trenos, vetor_L, Q, numero_presentes, iteracoes_vnd);
  solu_viavel = solucao(trenos, numero_presentes, 1);
  cout << "Solucao vnd: " << solu_viavel << endl;    
  
  return 0;

}
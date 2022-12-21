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

  vector<string> instancias_grandes = {
    "n400_k200_A", "n400_k200_B",
    "n500_k200_A", "n500_k200_B",
    "n1000_k200_A", "n1000_k200_B"
  };

  vector<int> vetor_solu_otimos = {
    12,12,13,16,16,16,12,12,30,30,30,25,25,39,39,39,48,48
  };

  int i = 5;

  cout << "Algoritimo Guloso\n" << endl;

  vector<int> vetor_p, info;
  vector<Treno*> trenos, trenos_copia;
  string path = "../instancias_grandes/" + instancias_grandes[i] + ".txt";

  vector<vector<int>> vetor_L(1001, vector<int>(1001));

  ler_arquivo(path, info, vetor_p, vetor_L);

  int numero_presentes = info[0];
  int k = info[1];
  int Q = info[2];
  int numero_elementos_em_L = info[3];
  int solu_guloso = 0, best_solution = 1000;
  int solu_vnd, solu_ils;
  int r = 2;

  clock_t tInicio, tFim, tDecorrido;

  tInicio = clock();

  guloso(&trenos, numero_presentes, Q, k, vetor_p, vetor_L);
  solu_guloso = solucao(trenos, numero_presentes, 0);

  tFim = clock();
  tDecorrido = ((tFim - tInicio) / (CLOCKS_PER_SEC / 1000));

  copia_vetor_guloso(trenos,trenos_copia);

  // cout << "Instancia: " << instancias[i] << endl;
  cout << "Instancia: " << instancias_grandes[i] << endl;
  cout << "Solucao gulosa: " << solu_guloso << endl;
  // cout << "Solucao otima: " << vetor_solu_otimos[i] << endl;
  cout << "Tempo em ms: " << tDecorrido << endl;
  cout << endl;

  cout << "Vnd\n" << endl;

  tInicio = clock();

  vnd(trenos, vetor_L, Q, numero_presentes, r, solu_guloso);
  solu_vnd = solucao(trenos, numero_presentes, 0);

  tFim = clock();
  tDecorrido = ((tFim - tInicio) / (CLOCKS_PER_SEC / 1000));

  cout << "Solucao VND: " << solu_vnd << endl;
  cout << "Tempo em ms VND: " << tDecorrido << endl;

  cout << "\nILS\n" << endl;

  tInicio = clock();
  ils(trenos_copia, vetor_L, Q, numero_presentes, r, solu_guloso);
  solu_ils = solucao(trenos_copia, numero_presentes, 0);

  tFim = clock();
  tDecorrido = ((tFim - tInicio) / (CLOCKS_PER_SEC / 1000));

  cout << "Solucao ILS: " << solu_ils << endl;
  cout << "Tempo em ms ILS: " << tDecorrido << endl;

  return 0;

}
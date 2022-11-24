#include "../include/funcoes.h"

void ler_arquivo(string path, vector<int> &info, vector<int> &vetor_p, vector<int> &vetor_L){
    
    ifstream arq(path); 
    string temp;
    int t;
    arq >> temp;

    for (int i = 0; i < 4; i++){
        arq >> t;
        info.push_back(t); 
    }
    
    for (int i = 0; i < info[0] - 1; i++){
        arq >> t;
        vetor_p.push_back(t);
    }

    for (int i = 0; i < info[3] * 2; i++){
        arq >> t;
        vetor_L.push_back(t);
    }

}

void insertion_sort(vector<int> &p){
    
    int pivo = 0;
    int j = 0;

    for( int i = 1; i < p.size(); i++){
        pivo = p[i];
        j = i - 1;

        while ( j >= 0 && p[j] < pivo  ){
            p[j + 1] = p[j];
            j = j - 1;
        }
    
        p[j + 1] = pivo;
    }
}

int solucao(vector<Treno*> &trenos, int numero_presentes, int print){
    
    int count = 0;
    int sum = 0;


    for (int i = 0; i < trenos.size(); i++){
        if (!trenos[i]->itens.empty()){
            if (print == 1){
                trenos[i]->print_itens();
            }
            count += 1;
            sum += trenos[i]->itens.size();
        }
    }

    if (print == 1){

        cout << endl;
        cout << "Presentes adicionados: " << sum << " - Numero de presentes: " << numero_presentes - 1 << endl;
        
    }
    
    return count;
}


void guloso(vector<Treno*> *trenos,int numero_presentes, int capacidade, int k, vector<int> &vetor_p, vector<int> &vetor_L){

    int maior_peso, indice, it;
    int tamanho = vetor_L.size();
    int coloca;
    int contador = 0;
    vector<int> p_ordenado, aux_p;
    
    for (int i = 0; i < vetor_p.size(); i++){
        p_ordenado.push_back(vetor_p[i]);
        aux_p.push_back(vetor_p[i]);
        contador += 1;
    }

    insertion_sort(p_ordenado);

    for (int j = 0; j < k; j++){

        Treno *treno;
        treno = new Treno(j, capacidade);

        for (int i = 0; i < vetor_p.size(); i++){
            maior_peso = p_ordenado[i];

            if (treno->get_capacidade() >= maior_peso & maior_peso > 0){
                coloca = 1;

                for (int m = 0; m < vetor_p.size(); m++){
                    if (vetor_p[m] == maior_peso & aux_p[m] > 0){
                        indice = m + 1;
                    }
                }

                if (!treno->itens.empty()){

                    for (int l = 2; l < tamanho; l = l + 2){
                        if (vetor_L[l-2] == indice){

                            for (int k = 0; k < treno->itens.size(); k++){
                                if (treno->itens[k] == vetor_L[l-1]){
                                    coloca = 0;
                                    break;
                                }
                            }
                        
                        }else{
                            if (vetor_L[l-1] == indice){

                                for (int k = 0; k < treno->itens.size(); k++){
                                    if (treno->itens[k] == vetor_L[l-2]){
                                        coloca = 0;
                                        break;
                                    }
                                }

                            }
                            
                        }

                        if (coloca == 0){
                            break;
                        }

                    }

                }
                
                if (coloca == 0){
                    continue;

                }else{
                    treno->itens.push_back(indice);
                    treno->set_capacidade(treno->get_capacidade() - maior_peso);
                    treno->pesos.push_back(maior_peso);
                    p_ordenado[i] = 0;
                    aux_p[indice - 1] = 0;
                }

            }

        }

        trenos->push_back(treno);

        int sum;
        sum = 0;

        for (int i = 0; i < p_ordenado.size(); i++){
            if (p_ordenado[i] == 0){
                sum += 1;
            }
        }


        if (sum == p_ordenado.size() ){
            break;
        }

        if (treno->itens.empty()){
            break;
        }
     
    }

}



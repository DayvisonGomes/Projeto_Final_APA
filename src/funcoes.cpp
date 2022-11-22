#include "../include/funcoes.h"

void ler_arquivo(string path, vector<string> &info, vector<int> &vetor_p, vector<int> &vetor_L){
    
    ifstream arq(path); 
    string ch;
    int cont = 1, aux;

    while(getline(arq, ch)){

        if (cont == 6){
            for (int i = 0; i < ch.length(); i++){

                if (ch[i] == ' '){
                    continue;
                }else{
                    vetor_p.push_back(ch[i] - 48);
                }
            }
            
        }else if (cont >= 8){
            for (int i = 0; i < ch.length(); i++){

                if (ch[i] == ' '){
                    continue;
                }else{
                    vetor_L.push_back(ch[i] - 48);
                }   
            
            }

        }else if (cont != 5){
            info.push_back(ch);
        }

        cont += 1;

    }
    
}

void insertion_sort(vector<int> &p){
    
    int pivo = 0;
    int j = 0;

    for( int i = 1; i <= p.size(); i++){
        pivo = p[i];
        j = i - 1;

        while ( j >= 0 && p[j] < pivo  ){
            p[j + 1] = p[j];
            j = j - 1;
        }
    
        p[j + 1] = pivo;
    }
}

void guloso(vector<Treno*> *trenos,int numero_presentes, int capacidade, int k, vector<int> &vetor_p, vector<int> &vetor_L){

    int maior_peso, indice, it, tamanho;
    vector<int> p_ordenado;
    
    for (int i = 0; i < vetor_p.size(); i++){
        p_ordenado.push_back(vetor_p[i]);
    }
    
    insertion_sort(p_ordenado);

    for (int j = 0; j < k; j++){

        Treno *treno;
        treno = new Treno(j,capacidade);
        it = 0;

        while (it < numero_presentes){
            maior_peso = p_ordenado[it];
            
            if (treno->get_capacidade() >= maior_peso){

                for (int i = 0; i < vetor_p.size(); i++){
                    if (vetor_p[i] == maior_peso){
                        indice = i + 1;
                    }
                }

                // tamanho = aux_L.size() / 2;
                // for (int m = 0; m < tamanho; m++){
                //     if (treno->itens[indice] == NULL){
                //         break;
                //     }

                //     if (m == 0){
                //         if (indice == aux_L[m] || indice == aux_L[m+1]){
                            
                //         }

                //     }else{
                //         aux_L[m+1] aux_L[m+2]
                //     }
                // }

                treno->itens.push_back(indice);
                treno->set_capacidade(treno->get_capacidade() - maior_peso);
                treno->pesos.push_back(maior_peso);
                p_ordenado.erase(p_ordenado.begin() + it);
                it = 0;

            }else{
                it += 1;
            }
        }   
        
        trenos->push_back(treno);
                
    }
        
}



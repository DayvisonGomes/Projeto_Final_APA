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
    
    for (int i = 0; i < info[0]; i++){
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
        
        if (print == 1){
            trenos[i]->print_itens();
        }

        count += 1;
        sum += trenos[i]->itens.size();
        
    }

    if (print == 1){

        cout << endl;
        cout << "Presentes adicionados: " << sum << " - Numero de presentes: " << numero_presentes << endl;
        
    }
    
    return count;
}

int verificar_tuplas(int tamanho_tuplas, Treno *treno, int item, vector<int> &vetor_l){

    int coloca = 1;

    for (int l = 2; l < tamanho_tuplas; l = l + 2){
        if (vetor_l[l-2] == item){

            for (int k = 0; k < treno->itens.size(); k++){
                if (treno->itens[k] == vetor_l[l-1]){
                    coloca = 0;
                    break;
                }
            }
                        
        }else{
            if (vetor_l[l-1] == item){

                for (int k = 0; k < treno->itens.size(); k++){
                    if (treno->itens[k] == vetor_l[l-2]){
                        coloca = 0;
                        break;
                    }
                }

            }
                            
        }
 
    }

    return coloca;

}


void guloso(vector<Treno*> *trenos,int numero_presentes, int capacidade, int k, vector<int> &vetor_p, vector<int> &vetor_L){

    int maior_peso, indice;
    int sum;
    int tamanho = vetor_L.size();
    int coloca;
    
    vector<int> p_ordenado, aux_p;
    
    for (int i = 0; i < vetor_p.size(); i++){
        p_ordenado.push_back(vetor_p[i]);
        aux_p.push_back(vetor_p[i]);
    }

    insertion_sort(p_ordenado);

    for (int j = 0; j < k; j++){

        Treno *treno;
        treno = new Treno(j, capacidade);

        for (int i = 0; i < numero_presentes; i++){
            maior_peso = p_ordenado[i];

            if (treno->get_capacidade() >= maior_peso & maior_peso > 0){
                coloca = 1;

                for (int m = 0; m < vetor_p.size(); m++){
                    if (vetor_p[m] == maior_peso & aux_p[m] > 0){
                        indice = m + 1;
                    }
                }

                if (!treno->itens.empty()){
                    coloca = verificar_tuplas(tamanho, treno, indice, vetor_L);
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
        
        if (treno->itens.empty()){
            break;
        }

        trenos->push_back(treno);

        sum = 0;

        for (int i = 0; i < p_ordenado.size(); i++){
            if (p_ordenado[i] == 0){
                sum += 1;
            }
        }


        if (sum == p_ordenado.size() ){
            break;
        }

        
     
    }

}


void re_insertion(vector<Treno*> &trenos, vector<int> &vetor_L, int capacidade_maxima){

 //minimizar o quao longe da capacidade maxima está
    
    int folga, melhor_folga = 1000;
    int peso_um, peso_dois;

    for (int i = 0; i < trenos.size(); i++){

        for (int j = 0; j < trenos[i]->itens.size(); j++){
            
            peso_um = trenos[i]->pesos[j];


            for (int k = 0; k < trenos.size(); k++){

                if (k==i){
                    continue;
                }


                for (int l = 0; l < trenos[k]->itens.size(); l++){

                    folga = 0;

                    peso_dois = trenos[k]->pesos[l];


                    if ( (trenos[i]->get_capacidade() - peso_um + peso_dois <= capacidade_maxima) & (trenos[k]->get_capacidade() - peso_dois + peso_um <= capacidade_maxima) ){
                        folga = (2*capacidade_maxima) - (trenos[i]->get_capacidade() - peso_um + peso_dois) - (trenos[k]->get_capacidade() - peso_dois + peso_um);

                    }
                    
                    if (folga < melhor_folga){
                        melhor_folga = folga;
                    }

                }


            }

        }


    }

}




// void treno_furado(vector<Treno*> &trenos, vector<int> &vetor_L){

//     vector<int> inds_itens, trenos_remover;
//     int coloca;


//     for (int i = 0; i < trenos.size(); i++){
//         trenos[i]->print_itens();

//         if (!inds_itens.empty()){
//             inds_itens.clear();

//         }

//         for (int j = 0; j < trenos[i]->itens.size(); j++){
//             inds_itens.push_back(trenos[i]->itens[j]);
//         }

//         for (int l = 0; l < inds_itens.size(); l++){

//             for (int k = 0; k < trenos.size(); k++){
//                 if (k == i){
//                     continue;
//                 }

//                 if(trenos[k]->get_capacidade() >= trenos[k]->pesos[l]){
//                     coloca = 1;

//                     for (int h = 2; h < vetor_L.size(); h = h + 2){
//                         if (vetor_L[h-2] == inds_itens[l]){

//                             for (int m = 0; m < trenos[k]->itens.size(); m++){
//                                 if (trenos[k]->itens[m] == vetor_L[h-1]){
//                                     coloca = 0;
//                                     break;
//                                 }
//                             }
                        
//                         }else{
//                             if (vetor_L[h-1] == inds_itens[l]){

//                                 for (int n = 0; n < trenos[k]->itens.size(); n++){
//                                     if (trenos[k]->itens[n] == vetor_L[h-2]){
//                                         coloca = 0;
//                                         break;
//                                     }
//                                 }

//                             }
                            
//                         }

//                         if (coloca == 0){
//                             break;
//                         }

//                     }

//                     if (coloca == 0){
//                         continue;

//                     }else{
//                         trenos[k]->itens.push_back(inds_itens[l]);
//                         trenos[k]->set_capacidade(trenos[k]->get_capacidade() - trenos[k]->pesos[l]);
//                         trenos[k]->pesos.push_back(trenos[k]->pesos[l]);
                        
//                         trenos[i]->set_capacidade(trenos[k]->get_capacidade() + trenos[i]->pesos[l]);
//                         trenos[i]->itens.erase(trenos[i]->itens.begin() + l);
//                         trenos[i]->pesos.erase(trenos[i]->pesos.begin() + l);

//                         if (trenos[i]->itens.size() == 0){
//                             trenos_remover.push_back(i);
//                         }

//                         break;
//                     }

//                 }   
        
                
//             }
        
//         }


        
        
//     }

//     cout << "ROI" << endl;
//     cout << trenos_remover.size() << endl;
//     for (int i = 0; i < trenos_remover.size(); i++){
//         cout << i << endl;
//     }
    
// }


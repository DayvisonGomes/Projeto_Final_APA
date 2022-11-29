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

int verificar_tuplas(Treno *treno, int item, vector<int> &vetor_l){

    int coloca = 1;

    for (int l = 2; l < vetor_l.size(); l = l + 2){
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
                    coloca = verificar_tuplas(treno, indice, vetor_L);
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


void swap(vector<Treno*> &trenos, vector<int> &vetor_L, int capacidade_maxima){

 //minimizar o quao longe da capacidade maxima está
    
    int folga, melhor_folga = 1000;
    int peso_um, peso_dois;
    int indice_treno_um = 0, indice_treno_dois = 0;
    int coloca_um, coloca_dois;
    int item_um = 0, item_dois = 0;
    int indice_item_um = 0, indice_item_dois = 0;
    int peso_aux_um = 0, peso_aux_dois = 0;

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


                    if ( (trenos[i]->get_capacidade() + peso_um - peso_dois <= capacidade_maxima) & (trenos[k]->get_capacidade() + peso_dois - peso_um <= capacidade_maxima) ){
                        
                        coloca_um = verificar_tuplas(trenos[i], trenos[k]->itens[l], vetor_L);
                        coloca_dois = verificar_tuplas(trenos[k], trenos[i]->itens[j], vetor_L);
                        
                        if (coloca_um == 1 & coloca_dois == 1){
                            folga = (2*capacidade_maxima) - (trenos[i]->get_capacidade() + peso_um - peso_dois) - (trenos[k]->get_capacidade() + peso_dois - peso_um);
                        }

                    }
                    
                    if (folga < melhor_folga){
                        melhor_folga = folga;
                        indice_treno_um = i;
                        indice_treno_dois = k;
                        indice_item_um = j;
                        indice_item_dois = l;
                        item_um = trenos[i]->itens[j];
                        item_dois = trenos[k]->itens[l];

                    }

                }

            }

        }   

    }

    peso_aux_um = trenos[indice_treno_um]->pesos[indice_item_um];
    peso_aux_dois = trenos[indice_treno_dois]->pesos[indice_item_dois];

    if (peso_aux_um == 0 & peso_aux_dois == 0){
        cout << "Nao foi feito o swap" << endl;
    
    }else{

        trenos[indice_treno_um]->set_capacidade(trenos[indice_treno_um]->get_capacidade() + peso_aux_um - trenos[indice_treno_dois]->pesos[indice_item_dois]);
        trenos[indice_treno_um]->itens[indice_item_um] = item_dois;
        trenos[indice_treno_um]->pesos[indice_item_um] = peso_aux_dois;

        trenos[indice_treno_dois]->set_capacidade(trenos[indice_treno_dois]->get_capacidade() + peso_aux_dois - trenos[indice_treno_um]->pesos[indice_item_um]);
        trenos[indice_treno_dois]->itens[indice_item_dois] = item_um;
        trenos[indice_treno_dois]->pesos[indice_item_dois] = peso_aux_um;

    }

    
}


void treno_furado(vector<Treno*> &trenos, vector<int> &vetor_L){

    vector<int> inds_itens, trenos_remover;
    int coloca;


    for (int i = 0; i < trenos.size(); i++){
        trenos[i]->print_itens();

        if (!inds_itens.empty()){
            inds_itens.clear();

        }

        for (int j = 0; j < trenos[i]->itens.size(); j++){
            inds_itens.push_back(trenos[i]->itens[j]);
        }

        for (int l = 0; l < inds_itens.size(); l++){

            for (int k = 0; k < trenos.size(); k++){
                if (k == i){
                    continue;
                }

                if(trenos[k]->get_capacidade() >= trenos[i]->pesos[l]){
                    coloca = 1;

                    coloca = verificar_tuplas(trenos[k], inds_itens[l], vetor_L);

                    if (coloca == 0){
                        continue;

                    }else{
                        trenos[k]->set_capacidade(trenos[k]->get_capacidade() - trenos[i]->pesos[l]);
                        trenos[k]->itens.push_back(inds_itens[l]);
                        trenos[k]->pesos.push_back(trenos[i]->pesos[l]);
                        
                        trenos[i]->set_capacidade(trenos[i]->get_capacidade() + trenos[i]->pesos[l]);
                        trenos[i]->itens[l] = 0;
                        trenos[i]->pesos[l] = 0;
                        
                        int soma = 0;
                        for (int n = 0; n < trenos[i]->itens.size(); n++){
                            if (trenos[i]->itens[n] == 0){
                                soma += 1;
                            }
                        }
                        
                        if (soma == trenos[i]->itens.size()){
                            trenos_remover.push_back(i);
                        }

                        break;
                    }

                }   
        
                
            }
        
        }       
        
    }

    for (int i = 0; i < trenos_remover.size(); i++){
        trenos.erase(trenos.begin() + trenos_remover[i] - i);
    }
    
}


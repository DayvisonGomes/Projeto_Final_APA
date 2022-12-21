#include "../include/funcoes.h"

void ler_arquivo(string path, vector<int> &info, vector<int> &vetor_p, vector<vector<int>> &vetor_L){
    
    ifstream arq(path); 
    string temp;
    int t,t2;
    arq >> temp;

    for (int i = 0; i < 4; i++){
        arq >> t;
        info.push_back(t); 
    }
    
    for (int i = 0; i < info[0]; i++){
        arq >> t;
        vetor_p.push_back(t);
    }

    
    for (int i = 0; i < info[0]; i++){
        for (int j = 0; j < info[0]; j++){
            vetor_L[i].push_back(0);
        }
    }


    for (int i = 0; i < info[3]; i++){
        arq >> t;
        arq >> t2;
        vetor_L[t-1][t2-1] = 1;
        vetor_L[t2-1][t-1] = 1;

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

            for (int j = 0; j < trenos[i]->itens.size(); j++){
                if (trenos[i]->itens[j] > 0){
                    sum += 1;

                }
            }
        
        }
    }

    if (print == 1){

        cout << endl;
        cout << "Presentes adicionados: " << sum << " - Numero de presentes: " << numero_presentes << endl;
        
    }
    
    return count;
}

int verificar_tuplas(Treno *treno, int item, vector<vector<int>> &vetor_L){

    int coloca = 1;

    for (int i = 0; i < vetor_L[0].size(); i++){
        if (vetor_L[item - 1][i] == 1){
            for (int j = 0; j < treno->itens.size(); j++){
                if (i + 1 == treno->itens[j]){
                    coloca = 0;
                    break;
                }
            }

            if (coloca == 0){
                break;
            }
        
        }
        
    }

    return coloca;

}


void guloso(vector<Treno*> *trenos,int numero_presentes, int capacidade, int k, vector<int> &vetor_p, vector<vector<int>> &vetor_L){

    int maior_peso, indice = 0;
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
     
    }

}


void copia_vetor_guloso(vector<Treno*> &trenos, vector<Treno*> &trenos_guloso){

    for (int i = 0; i < trenos.size(); i++){
        if (!trenos[i]->itens.empty()){
            trenos_guloso.push_back(trenos[i]);
        }
        
    }

}


int swap_pertubacao(vector<Treno*> &trenos, vector<vector<int>> &vetor_L, int capacidade_maxima){

    unsigned seed = time(0);
    int random_treno = 0;
    int random_treno2 = 0, item_um = 0, item_dois = 0;
    int count = 0;
    int peso_um = 0, peso_dois = 0, peso_aux_um = 0, peso_aux_dois = 0;
    int cap1 = 0,cap2 = 0, var = 0;
    int coloca1, coloca2;
       

    while(true){

        srand(seed);
        random_treno = rand() % trenos.size();
        srand(seed);
        random_treno2 = rand() % trenos.size();

        if (random_treno == random_treno2){
            continue;
        }

        item_um = rand() % trenos[random_treno]->itens.size();
        item_dois = rand() % trenos[random_treno2]->itens.size();

        peso_um = trenos[random_treno]->pesos[item_um];
        peso_dois = trenos[random_treno2]->pesos[item_dois];

        cap1 = trenos[random_treno]->get_capacidade() + peso_um - peso_dois;
        cap2 = trenos[random_treno2]->get_capacidade() + peso_dois - peso_um;

        if ( peso_um > 0 & peso_dois > 0 & cap1 >= 0 & cap2 >= 0 & cap1 <= capacidade_maxima & cap2 <= capacidade_maxima){

            coloca1 = verificar_tuplas(trenos[random_treno], trenos[random_treno2]->pesos[item_dois], vetor_L);
            coloca2 = verificar_tuplas(trenos[random_treno2], trenos[random_treno]->itens[item_um], vetor_L);

            if (coloca1 == 1 & coloca2 == 1){

                peso_aux_um = trenos[random_treno]->pesos[item_um];
                peso_aux_dois = trenos[random_treno2]->pesos[item_dois];

                trenos[random_treno]->set_capacidade(trenos[random_treno]->get_capacidade() + peso_aux_um - peso_aux_dois);
                trenos[random_treno]->itens[item_um] = trenos[random_treno2]->itens[item_dois];
                trenos[random_treno]->pesos[item_um] = peso_aux_dois;

                trenos[random_treno2]->set_capacidade(trenos[random_treno2]->get_capacidade() + peso_aux_dois - peso_aux_um);
                trenos[random_treno2]->itens[item_dois] = trenos[random_treno]->itens[item_um];
                trenos[random_treno2]->pesos[item_dois] = peso_aux_um;

                return 1;
            
            }
        
        }
        
        var = swap(trenos, vetor_L, capacidade_maxima);
        return 1;
        

    }

    return 0;

}

    


int saco_vazio(vector<Treno*> &trenos, vector<vector<int>> &vetor_L){

    vector<int> inds_itens, trenos_remover;
    int coloca, peso = 0;
    int para = 0;

    for (int i = 0; i < trenos.size(); i++){
        if (trenos[i]->itens.empty()){
            continue;
        }

        if (!inds_itens.empty()){
            inds_itens.clear();

        }

        for (int j = 0; j < trenos[i]->itens.size(); j++){
            inds_itens.push_back(trenos[i]->itens[j]); 
        }

        for (int l = 0; l < inds_itens.size(); l++){

            for (int k = 0; k < trenos.size(); k++){
                if ( (k == i) || (trenos[k]->itens.empty()) ){
                    continue;
                }

                if(trenos[k]->get_capacidade() >= trenos[i]->pesos[l] & trenos[i]->pesos[l] > 0){
                    coloca = 1;

                    coloca = verificar_tuplas(trenos[k], inds_itens[l], vetor_L);

                    if (coloca == 0){
                        continue;

                    }else{

                        peso = trenos[i]->pesos[l];
                        trenos[k]->set_capacidade(trenos[k]->get_capacidade() - peso);
                        trenos[k]->itens.push_back(inds_itens[l]);
                        trenos[k]->pesos.push_back(peso);
                        
                        trenos[i]->set_capacidade(trenos[i]->get_capacidade() + peso);
                        trenos[i]->itens[l] = 0;
                        trenos[i]->pesos[l] = 0;
                        
                        int soma = 0;
                        for (int n = 0; n < trenos[i]->itens.size(); n++){
                            if (trenos[i]->itens[n] == 0){
                                soma += 1;
                            }
                        }
                        
                        if (soma == trenos[i]->itens.size()){
                            trenos[i]->itens.clear();
                            trenos[i]->pesos.clear();

                            return 1;
                        }
                        
                    }

                }   
        
            }
            
        }     

    }

    return 0;
}

void vnd(vector<Treno*> &trenos, vector<vector<int>> &vetor_L, int capacidade_maxima, int numero_presentes, int r, int s0){
    int it = 1, solu_viavel = 0, var = 0;

    while (it <= r){

        if (it == 1){
            
            var = swap(trenos, vetor_L, capacidade_maxima);
            solu_viavel = solucao(trenos, numero_presentes, 0);
        }

        if (it == 2){

            var = saco_vazio(trenos, vetor_L);
            solu_viavel = solucao(trenos, numero_presentes, 0);

        }

        if (solu_viavel < s0){
            s0 = solu_viavel;
            it = 1;

        }else{
            it += 1;
        }

    }
}

void ils(vector<Treno*> &trenos, vector<vector<int>> &vetor_L, int capacidade_maxima, int numero_presentes, int r, int s0){
    int solu_vnd = 0, solu_vnd_2, it = 0, max = 100, var = 0;

    vnd(trenos, vetor_L, capacidade_maxima, numero_presentes, r, s0);
    solu_vnd = solucao(trenos, numero_presentes, 0);

    while (it < max){
        var = swap(trenos, vetor_L, capacidade_maxima);
        vnd(trenos, vetor_L, capacidade_maxima, numero_presentes, r, s0);
        solu_vnd_2 = solucao(trenos, numero_presentes, 0);

        if (solu_vnd_2 < solu_vnd){
            solu_vnd = solu_vnd_2;
        
        }else{
            it += 1;
        }

    }   

}

int swap(vector<Treno*> &trenos, vector<vector<int>> &vetor_L, int capacidade_maxima){
    
    int peso_um, peso_dois;
    int indice_treno_um = 0, indice_treno_dois = 0;
    int coloca_um, coloca_dois;
    int item_um = 0, item_dois = 0;
    int indice_item_um = 0, indice_item_dois = 0;
    int peso_aux_um = 0, peso_aux_dois = 0;
    int verificar = 0;
    int cap1 = 0, cap2 = 0;
    int count = 0;

    for (int i = 0; i < trenos.size(); i++){

        if (trenos[i]->itens.empty()){
            continue;
        }

        for (int j = 0; j < trenos[i]->itens.size(); j++){

            for (int k = 0; k < trenos.size(); k++){

                if ( (k==i) || (trenos[k]->itens.empty()) ){
                    continue;
                }


                for (int l = 0; l < trenos[k]->itens.size(); l++){

                    peso_dois = trenos[k]->pesos[l];
                    peso_um = trenos[i]->pesos[j];

                    cap1 = trenos[i]->get_capacidade() + peso_um - peso_dois;
                    cap2 = trenos[k]->get_capacidade() + peso_dois - peso_um;

                    if (peso_um > 0 & peso_dois > 0 & cap1 >= 0 & cap2 >= 0 & cap1 <= capacidade_maxima & cap2 <= capacidade_maxima){

                        coloca_um = 1;
                        coloca_dois = 1;

                        coloca_um = verificar_tuplas(trenos[i], trenos[k]->itens[l], vetor_L);
                        coloca_dois = verificar_tuplas(trenos[k], trenos[i]->itens[j], vetor_L);
                        
                        if (coloca_um == 1 & coloca_dois == 1){
                            item_um = trenos[i]->itens[j];
                            item_dois = trenos[k]->itens[l];

                            peso_aux_um = trenos[i]->pesos[j];
                            peso_aux_dois = trenos[k]->pesos[l];

                            trenos[i]->set_capacidade(trenos[i]->get_capacidade() + peso_aux_um - peso_aux_dois);
                            trenos[i]->itens[j] = item_dois;
                            trenos[i]->pesos[j] = peso_aux_dois;

                            trenos[k]->set_capacidade(trenos[k]->get_capacidade() + peso_aux_dois - peso_aux_um);
                            trenos[k]->itens[l] = item_um;
                            trenos[k]->pesos[l] = peso_aux_um;
                            
                            count += 1;
                            
                            if (count == 300){
                                return 1;
                            }
                            

                        }

                    }        

                }

            }

        }   

    }

    return 0;
    
}

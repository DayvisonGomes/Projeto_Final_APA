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

    int maior_peso, indice, it;
    int tamanho = vetor_L.size();
    int coloca;
    vector<int> p_ordenado, aux_p;
    
    for (int i = 0; i < vetor_p.size(); i++){
        p_ordenado.push_back(vetor_p[i]);
        aux_p.push_back(vetor_p[i]);
    }
    
    insertion_sort(p_ordenado);

    for (int j = 0; j <= k; j++){

        Treno *treno;
        treno = new Treno(j, capacidade);

        for (int i = 0; i <= numero_presentes; i++){
            maior_peso = p_ordenado[i];

            if (treno->get_capacidade() >= maior_peso & maior_peso > 0){
                coloca = 1;

                for (int i = 0; i <= vetor_p.size(); i++){
                    if (vetor_p[i] == maior_peso & aux_p[i] > 0){
                        indice = i + 1;
                    }
                }

                if (!treno->itens.empty()){

                    for (int i = 2; i <= tamanho; i = i + 2){
                        if (vetor_L[i-2] == indice){

                            for (int k = 0; k < treno->itens.size(); k++){
                                if (treno->itens[k] == vetor_L[i-1]){
                                    coloca = 0;
                                    break;
                                }
                            }
                        
                        }else{
                            if (vetor_L[i-1] == indice){

                                for (int k = 0; k < treno->itens.size(); k++){
                                    if (treno->itens[k] == vetor_L[i-2]){
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
        int teste;
        int indiceee;

        sum = 0;
        teste = 0;
        indiceee = 0;

        for (int i = 0; i <= p_ordenado.size(); i++){
            if (p_ordenado[i] == 0){
                sum += 1;
            }
        }

        for (int i = 0; i <= p_ordenado.size(); i++){
            if (p_ordenado[i] != 0){
                teste += 1;
                indiceee = i;
            }
        }

        
        if (sum == p_ordenado.size()){
            
            cout << "Presentes adicionados: " << sum + 1 << endl;
            cout << "Faltou quantos presentes: " << teste << endl;
            cout << "Quem e: " << p_ordenado[indiceee] << endl;

            break;

        }
     
    }
        
}



#include "../include/funcoes.h"

void ler_arquivo(string path, vector<string> *info, vector<string> *vetor_p, vector<string> *vetor_L){
    ifstream arq(path); 
    string ch,temp;
    int cont = 1;

    while(getline(arq, ch)){

        if (cont == 6){
            for (int i = 0; i < ch.length(); i++){
                temp = "";

                if (ch[i] == ' '){
                    continue;
                }else{
                    temp = temp + ch[i];
                    vetor_p->push_back(temp);
                }
            }
            
        }else if (cont >= 8){
            for (int i = 0; i < ch.length(); i++){
                temp = "";
                if (ch[i] == ' '){
                    continue;
                }else{
                    temp = temp + ch[i];
                    vetor_L->push_back(temp);
                }   
            
            }

        }else if (cont != 5){
            
            info->push_back(ch);
            
        }

        cont += 1;

    }
    
}

void troca_tipo(vector<string> &vetor_p, vector<string> &vetor_L, vector<int> *aux_vetor_p, vector<int> *aux_vetor_L){

    for (int i = 0; i < vetor_p.size(); i++){
        aux_vetor_p->push_back(stoi(vetor_p[i]));
    }

    for (int i = 0; i < vetor_L.size(); i++){
        aux_vetor_L->push_back(stoi(vetor_L[i]));
    }

}


void preenche(int numero_presentes, int capacidade, int k, vector<int> aux_p){

    // vector<Treno*> trenos;

    
    Treno* treno;
    treno = new Treno(capacidade);
    int maior_peso = 0;

    for (int i = 0; i < numero_presentes; i++){
        
        maior_peso = max(aux_p);

        }       
    
}

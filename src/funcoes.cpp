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

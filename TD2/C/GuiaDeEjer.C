// ejercicio 1 con strings 
#include <stdio.h>
int len(char* s){
    int contador = 0;
    int i = 0; // interador 
    while (1 ==1){
        char caracter = s[i];

        if (caracter == 0 ){
            return contador;
        } 
        contador = contador + 1;
    }
        
}
char* copy(char* s){// toma un str y genera una copia del mismo
    char* ret;
    for (int i = 0; i< len(s);i++){
        char caracter = s[i];
        ret[i] = caracter; 
    }
    return ret;
    }

void replaceChar(char* s, char old, char nuevow){
    for (int i = 0; i< len(s);i++){
        char caracter = s[i];
        if (caracter == old){
            s[i] = nuevow;
        } 
    }
}

int main(){

}

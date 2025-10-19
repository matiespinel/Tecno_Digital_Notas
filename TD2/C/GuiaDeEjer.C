// ejercicio 1 con strings 
#include <stdio.h>
// EJER 1
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

char* concatenate(char* s1, char* s2){// preguntar lo de liberar memoria. 
    char* ret = s1;

    for (int i = 0; i< len(s2);i++){
        char caracter = s2[i];
        ret[i + len(ret)] = caracter; 
    }
    return ret; 
    }

// Ejercicio 2
int* merge(int* A, int sizeA, int* B, int sizeB){
    int* ret;
    for (int i = 0; i < sizeA && i < sizeB; i++){
        int num1 = A[i];
        int num2 = B[i];
        if (num1 > num2){
            ret[i] = num2;
            ret[i+1] = num1;
        }else {
            ret[i] = num1;
            ret[i+1] = num2;
        }

    }
}


int main(){

}

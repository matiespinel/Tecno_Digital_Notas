// ejercicio 1 con strings 
#include <stdio.h>
#include <stdlib.h>
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
    ret[len(ret)] = 0;
    free(s1);
    free(s2);
    return ret; 
    }

// Ejercicio 2
int* merge(int* A, int sizeA, int* B, int sizeB){
    int* ret;
    int cont;
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
        cont= i;

    }
    if (cont== sizeA && cont == sizeB){ return ret;}else{
        if(cont < sizeA){
            for(int i = cont; i < sizeA; i++){
                int num1 = A[i];
                ret[i+1] = num1;
            }
            return ret; 
        }else{
            for(int i = cont; i < sizeB; i++){
                int num1 = A[i];
                ret[i+1] = num1;
            }
            return ret; 

        } }
}
float* mergefloat(float* A, int sizeA, float* B, int sizeB){
    float* ret;
    int cont;
    for (int i = 0; i < sizeA && i < sizeB; i++){
        float num1 = A[i];
        float num2 = B[i];
        if (num1 > num2){
            ret[i] = num2;
            ret[i+1] = num1;
        }else {
            ret[i] = num1;
            ret[i+1] = num2;
        }
        cont= i;

    }
    if (cont== sizeA && cont == sizeB){ return ret;}else{
        if(cont < sizeA){
            for(int i = cont; i < sizeA; i++){
                float num1 = A[i];
                ret[i] = num1;
            }
            return ret; 
        }else{
            for(int i = cont; i < sizeB; i++){
                float num1 = A[i];
                ret[i] = num1;
            }
            return ret; 

        } }
}
// Ejercicio 3
char* longest(char* v[], int size){
    char* ret = v[0];
    for (int i =1; i < size; i++){
        if (len(v[i]) > len(ret)){
            ret = v[i];
        }
    }
    return ret;
}
char* superConcatenate(char* v[], int size){
    int cont = 0;
    for (int i =0; i < size; i++){
        cont += len(v[i]);
    }
    char* ret = (char*)malloc(sizeof(char) * (cont + 1));
    for(int i =0; i < size-1;i++){
        ret = concatenate(v[i],v[i+1]);
    }
    return ret;
}
char* superConcatenateWithSep(char* v[], int size, char* s){
    char* ret = v[0];
    for(int i =1; i < size;i++){
        ret = concatenate(ret, s);
        ret = concatenate(ret, v[i]);
    }
    return ret;
}

void pairOfEquals(char v[], int size, char** a, char** b) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (v[i] == v[j]) {
                *a = &v[i];
                *b = &v[j];
                return;
            }
        }
    }
    *a = NULL;
    *b = NULL;
}

struct list {
    struct node* primero; // indica a memoria donde inicia la lista
    int size;
};
struct node {
    int data;
    struct node* next;
};
void getLast(struct list* twoLists, struct node** a, struct node** b){
    struct node* lista1 = twoLists[0].primero;
    struct node* lista2 = twoLists[1].primero;

    if (lista1 == NULL) {
        *a = NULL;
    } else {
        while (lista1->next != NULL) {
            lista1 = lista1->next;
        }
        *a = lista1;
    }

    if (lista2 == NULL) {
        *b = NULL;
    } else {
        while (lista2->next != NULL) {
            lista2 = lista2->next;
        }
        *b = lista2;
    }

 
}

int main(){
    
    char s[] = "hola";
    char s2[] = "mundo";
    char* joined = concatenate(s, s2);
    printf("Concatenate: %s\n", joined);
    free(joined);

    char* arr[] = {"uno", "dos", "tres"};
    char* joinedSep = superConcatenateWithSep(arr, 3, "-");
    printf("superConcatenateWithSep: %s\n", joinedSep);
    free(joinedSep);

    int A[] = {1, 3, 5};
    int B[] = {2, 4, 6, 7};
    int* merged = merge(A, 3, B, 4);
    printf("Merge: ");
    for (int i = 0; i < 7; i++) printf("%d ", merged[i]);
    printf("\n");
    free(merged);

    return 0;
}




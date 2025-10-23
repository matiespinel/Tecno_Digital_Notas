    #include <stdio.h>
    #include <stdlib.h>
//funciones 
char* strDuplicate(char* src){
    int contador = 0; 
    while (src[contador] != '\0') { // me fijo cuando termina el str 
        contador++;// longitud del src
    }
    char* ret = (char*)malloc(sizeof(char) * (contador + 1)); // +1 para el \0?
    for(int i =0; i <contador; i++){
        ret[i] = src[i];
    }
    ret[contador] = '\0';
    return ret;
}
//comparacion lexicografica
int strCompareASCII(char* s1, char* s2){ // esto es una comparacion ASCII
    //idea general; segun ACCII las letras tienen un valor numerico el cual asciende desde la a hasta la z, por ende puedo sumar todos los caracters de uno y ver si son mayores o menores al otro
    int i =0;
    int cont1 =0;
    int cont2 =0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        cont1 += s1[i];
        cont2 += s2[i];
        i++;
    }
    //miro si ambos terminaron o si alguno quedo antes
    //
    if (s1[i] == '\0') {
        while (s2[i] != '\0') {
        cont2 += s2[i];
        i++;
    }
    }// s1 termino antes que s2   
    else if (s2[i] == '\0') {// s2 termino antes que s1
        while (s1[i] != '\0') {
        cont1 += s1[i];
        i++;
        }
    }
    if(cont1 < cont2){
            return -1;
    }
    else if (cont1 > cont2){
        return 1;
    }
    else{
        return 0;
        }
}
int strCompare(char* s1, char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] < s2[i]) return -1;  // s1 es menor
        if (s1[i] > s2[i]) return 1;   // s1 es mayor
        i++;
    }

    // Si uno terminó antes que el otro
    if (s1[i] == '\0' && s2[i] == '\0') return 0;  // iguales
    if (s1[i] == '\0') return -1;  // s1 más corto → menor
    return 1;                      // s2 más corto → mayor
}

char* strConcatenate(char* src1, char* src2){
    int len1 =0;
    int len2 =0;
    while (src1[len1] != '\0'){
        len1++;
    }
    while (src2[len2] != '\0'){
        len2++;
    }
    char* ret = (char*) malloc (sizeof(char) * (len1 + len2 +1)); // +1 para el \0?
    for(int i =0; i < len1; i++){
        ret[i] = src1[i];
    }
    for(int j =0; j < len2; j++){
        ret[len1 + j] = src2[j];
    }
    ret[len1 + len2] = '\0';
    free(src1);
    free(src2);
    return ret;
}

//main
int main(){
    return 0;
}
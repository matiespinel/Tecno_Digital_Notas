    #include <stdio.h>
    #include <stdlib.h>
//funciones 
char* strDuplicate(char* src){
    int contador = 0; 
    while (src[contador] != '\0') { // me fijo cuando termina el str 
        contador++;// longitud del src
        printf("contador: %d\n", contador);//para ver que este andno bien
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
//strDuplicate:
char* original = "Hola, Mundo!";
printf("Original: %s\n", original);
char* copia = strDuplicate(original);
printf("Copia: %s\n", copia);
free(copia);

//1. String vac ́ıo.
char* vacio = "";
char* copiaVacio = strDuplicate(vacio);
printf("Original: %s\n", vacio);
printf("Copia: %s\n", copiaVacio);
free(copiaVacio);

//2. String de un car ́acter.
char* unCaracter = "A";
char* copiaUnCaracter = strDuplicate(unCaracter);
printf("Original: %s\n", unCaracter);
printf("Copia: %s\n", copiaUnCaracter);
free(copiaUnCaracter);
//3. String que incluya todos los caracteres v ́alidos distintos de cero.
char* todosCaracteres = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+-=[]{}|;':\",.<>/?`~ ";
char* copiaTodosCaracteres = strDuplicate(todosCaracteres);
printf("Original: %s\n", todosCaracteres);
printf("Copia: %s\n", copiaTodosCaracteres);
free(copiaTodosCaracteres);

//strCompare:
//1. Dos string vac ́ıos.
char* vacio1 = "";
char* vacio2 = "";
printf("Comparacion de dos strings vacios: %d\n", strCompare(vacio1, vacio2)); // Esperado: 0
printf("Comparacion de dos strings vacios: %d\n", strCompareASCII(vacio1, vacio2)); // Esperado: 0

//2. Dos string de un car ́acter.
char* charA = "A";
char* charB = "B";
printf("Comparacion de 'A' y 'B': %d\n", strCompare(charA, charB)); // Esperado: -1
printf("Comparacion de 'A' y 'B': %d\n", strCompareASCII(charA, charB)); // Esperado: -1
//3. Strings iguales hasta un car ́acter (hacer cmpStr(s1,s2) y cmpStr(s2,s1)).
char* s1 = "HelloX";
char* s2 = "HelloY";
printf("Comparacion de '%s' y '%s': %d\n", s1, s2, strCompare(s1, s2)); // Esperado: -1
printf("Comparacion de '%s' y '%s': %d\n", s2, s1, strCompare(s2, s1)); // Esperado: 1
printf("Comparacion ASCII de '%s' y '%s': %d\n", s1, s2, strCompareASCII(s1, s2)); // Esperado: -1
printf("Comparacion ASCII de '%s' y '%s': %d\n", s2, s1, strCompareASCII(s2, s1)); // Esperado: 1
//4. Dos strings diferentes (hacer cmpStr(s1,s2) y cmpStr(s2,s1)).
char* diff1 = "Sistema Operativo para para teclado";
char* diff2 = "Pileta redonda en dias de lluvia";
printf("Comparacion de '%s' y '%s': %d\n", diff1, diff2, strCompare(diff1, diff2)); // Esperado: 1
printf("Comparacion de '%s' y '%s': %d\n", diff2, diff1, strCompare(diff2, diff1)); // Esperado: -1
printf("Comparacion ASCII de '%s' y '%s': %d\n", diff1, diff2, strCompareASCII(diff1, diff2)); // Esperado: depende del contenido
printf("Comparacion ASCII de '%s' y '%s': %d\n", diff2, diff1, strCompareASCII(diff2, diff1)); // Esperado: depende del contenido
//strConcatenate:
//1. Un string vac ́ıo y un string de 3 caracteres.
char* vacioConcat = "";
char* tresCaracteres = "abc";
char* resultadoConcat1 = strConcatenate(strDuplicate(vacioConcat), strDuplicate(tresCaracteres));//el duplicado ya que la funcion deja libre la memoria
printf("Concatenacion de vacio y 'abc': %s\n", resultadoConcat1);
//2. Un string de 3 caracteres y un string vac ́ıo.
char* resultadoConcat2 = strConcatenate(strDuplicate(tresCaracteres), strDuplicate(vacioConcat));
printf("Concatenacion de 'abc' y vacio: %s\n", resultadoConcat2);
//3. Dos strings de 1 caracter.
char* charX = "X";
char* charY = "Y";
char* resultadoConcat3 = strConcatenate(strDuplicate(charX), strDuplicate(charY));
//4. Dos strings de 5 caracteres.
char* cincoX = "ABCDE";
char* cincoY = "FGHIJ";
char* resultadoConcat4 = strConcatenate(strDuplicate(cincoX), strDuplicate(cincoY));
printf("Concatenacion de '%s' y '%s': %s\n", cincoX, cincoY, resultadoConcat4);
return 0;
}
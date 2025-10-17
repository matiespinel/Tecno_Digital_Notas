#include <stdio.h>
int main() {
    printf("Hello, World!\n");
    // arreglos
    int ar[10]; // arreglo de 10 enteros
    ar[0] = 1;
    int a[5];
    a[0] = 42;
    a[1] = a[0] + 3;
    a[3] = a[0] - a[1];

    return 0;
    //struct
    struct Persona {
        char* nombre;
        int edad;};
    struct Persona p;
    p.nombre = "Juan";
    p.edad = 20;
    int valor = (2<<10) -1; // 2^10 -1 = 1023

    //punteros
    char a2;
    char *b;
    a2 = 35;
    b = &a2; // b apunta a la direccion de a2
    *b = 20; // cambia el valor de a2 a 20

    }



// Depndiendo que quieras escribir que tipo de print se pone %d, %f, %c
// %d -> entero
// %f -> float
// %c -> char
// %lf -> double
// %u -> unsigned int


// Funciones 
int suma(int a, int b) {
    return a + b;
}
int esPar(int a) {
    return !(a & 1);
}
// for

int print10() {
    for (int i = 0; i < 10; i++) {
    printf("%d\n", i);
    return 0;
}}
// while y do while
int print10While() {
    int i = 0;
    while (i < 10) {
        printf("%d\n", i);
        i++;
    }
    return 0;
}
int print10DoWhile() {
    int i = 0;
    do {
        printf("%d\n", i);
        i++;
    } while (i < 10);
    return 0;
}


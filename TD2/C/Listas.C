//Nodos enlazados con un puntero, cada nodo contiende datos y un puntero al siguiente nodo
// una lista termina cuadno su ultimo nodo apunta a null
// para crear una lista se pone que es el primer nodo, el tamanio y su tipo. 
// Se puede hacer doblemente enlazada, es decir un puntero que apunta al siguiente y otro al nodo previo (se apuntan el uno al otro
#include <stdio.h>
#include <stdlib.h>
struct lista{
    struct node *primero; //indica a memoria donde inicia la lista
};
struct node
{
    int data;
    struct node *next;
};
struct node* addFirst (struct node *p, int data){
    struct node *newNode = (struct node*) malloc(sizeof(struct node));
    newNode -> data = data;
    newNode->next =p;
    return newNode;
}
int main(){
    struct node *n = NULL;
    n = addFirst(n, 10);
    n = addFirst(n, 20);
    n = addFirst(n, 30);
    return 0; 
}

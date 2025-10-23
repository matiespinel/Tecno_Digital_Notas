#include <stdio.h>
#include <math.h>
int arregloCon5(int arr[], int size) {
    for(int i = 0; i < size; i++){
        int a = arr[i];
        if(a == 5){
            return 1;
        }
    
    }
    return 0;
}

void mult3(int arr[], int size){

    for(int i = 0; i < size; i++){
    
        int a = arr[i];
        if (a%3 == 0){
            printf("%d\n", a);
        } 
    }
}
typedef struct 
{
    float x;
    float y;
} vector_t;
float distance(vector_t*v1, vector_t*v2){
    float dx = v2 ->x - v1->x;//(*v2).x
    float dy =v2 ->y - v1->y;//(*v2).x
    return sqrt((dx * dx) + (dy * dy));
}
int* arrayswap(int* v, int size){
    int* ret;
    for(int i = size-1; i>=0; i--){
        ret[size-1 -i] = v[i];
    }
    return ret;
}
char* stringToUpper(char* s, int size){
    for(int i =0; i < size; i++){
        s[i] = s[i]- ("a" - "A");
    } 
    return s;
}
struct node {
int data;
struct node *next;
};
struct node* addFirst(struct node *p, int data) {
    struct node *newNode = (struct node*) malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = p;
    return newNode;
}



int main(){
int size = 10;
int arr[10] = {0,1,2,3,4,5,6,7,8,9};
printf("%d\n", arregloCon5(arr, 10));
mult3(arr, 10);
vector_t puntoA = {.x = 1.0, .y = 1.0};
vector_t puntoA = {.x = 4.0, .y= 5.0};


}


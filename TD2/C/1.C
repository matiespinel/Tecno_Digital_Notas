#include <stdio.h>

int main(){
int size = 10;
int arr[10] = {0,1,2,3,4,5,6,7,8,9};
printf("%d\n", arregloCon5(arr, 10));
printf("%d\n", mult3(arr, 10));
}
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

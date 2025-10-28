    #include <stdio.h>
    #include <stdlib.h>
int x;
int y = 35;
// void *malloc(size_t size)
// void free(void *pointer)
//como solicitar memoria dinamica para un vector de 100 enteros de 32 bita
//int* v = (int*) malloc(sizeof(int) *100)
void initZero(float* data, int size){
    for (int i =1 ; i < size; i++){
        data[i]= 0.0;
    }
}
void diffusionStep(float* data, int size){
    for (int i =1 ; i < size-1; i++){
        data[i]= (data[i-1] + data[i] + data[i + 1])/3.0;
    }
}
int main (){
int v[5];
int *p = v;
int *p = &(v[0]);
int* v = (int*) malloc(sizeof(int) *100);
free(v);
int size = 10;
float* data = (float*) malloc(sizeof(float)*size);
initZero(data, size);
data[0] = 200.0;
data[size-1] = 25.0;
for(int step = 0; step <300; step ++){
    diffusionStep(data, size);
    //printf(data, size);
}
free(data);
return 0;
}
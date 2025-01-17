main.c
#include<stdio.h>
void ordenacaoBolha(int v[], int n){
    int i, j;
    for (i = 0; i < n -1; i++){
        if(j = 0; j < n - i - 1; j++){
            int temp = v[j];{
            v[j] = v[j + 1];
            v[j + 1] = temp;
            trocou;
            }
        }
        if(trocou == 0){
            break;
        }
    }
}

int main(){
    int v[7] = {1,4,6,11,18,3};
    ordenacaoBolha(v, 7);
    return 0;
}
#include <stdio.h>

#define mask 0x1

int qnt_set(int num){
    int qnt = 0, aux = mask;
    for(int i = 0; i < 32; i++){
        if(num & aux){
            qnt++;
        }
        aux = aux << 1;
    }
    return qnt;
}

void splits(long int num){
    int i;
    int values[8];
    
    for (i = 7; i >= 0; i--) {
        values[i] = (num >> (i*4)) & 0x0F; // isola os 4 bits menos significativos
        printf("%x ", values[i]);
    }
}

int main(){
    int num;
    scanf("%d", &num);
    printf("Quantidade de sets: %d\n\n", qnt_set(num));

    long int num2 = 0xA23F5678; // exemplo de um número de 32 bits
    printf("Numero particionado:");
    splits(num2);
}
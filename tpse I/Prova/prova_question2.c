#include <stdio.h>
#include <stdbool.h>

#define mask 0x1
#define mask_i(i) (mask << i) //função para pegar um máscara de 0's e 1 apenas em i

void shiftLeft(unsigned int num){
    int count_set = 0, index_set = 0;//count_set serve para saber a quantidade de bits 1
                                    //index_set serve para saber a posição do último bit 1
    
    for(int i = 0; i < 32; i++){//laço para olhar cada bit do número
        if(num & mask_i(i)){
            count_set++;
            index_set = i;
        }
    }

    while (index_set % 4 != 0) {//laço para tornar o index múltiplo de 4, e assim
        index_set++;            //imprimir no final pacotes de 4 bits
    }
    
    for(int i = index_set , j = count_set; j > 0; i--, j--){
        num |= mask_i(i);   //devemos setar count_set bits 
    }

    for(int i = index_set - count_set; i > 0; i--){
        num &= ~mask_i(i); //devemos zerar os bits restantes
    }

    for(int i = index_set; i > 0; i--){ //imprimir o número dentro do 
        bool aux = num & mask_i(i);     //intervalo em binario
        printf("%d", aux);
    }
}

int main(){
    unsigned int num;
    scanf("%u", &num);
    shiftLeft(num);
}
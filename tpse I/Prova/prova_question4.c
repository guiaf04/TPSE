#include <stdio.h>
#include <stdbool.h>

#define mask 0x1
#define mask_i(i) (mask << i)

int setBits(bool w, unsigned int i, unsigned int j, unsigned int value){
    if(i <= j && i <= 31 && j <= 31){//não é necessário checar se i e j são maiores que 0 pois são unsigned
        if(w){
            for(unsigned int k = i; k <= j; k++){
                value = value | mask_i(k);
            }
        }else{
            for(unsigned int k = i; k <= j; k++){
                value = value & (~mask_i(k));
            }
        }
    }

    return value;
}

int main(){
    unsigned int w ,i, j, value;
    scanf("%u %u %u %u", &w, &i, &j, &value);
    printf("%d", setBits(w, i, j, value)); 
}
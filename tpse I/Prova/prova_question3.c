#include <stdio.h>

#define mask 0x1

#define mask_i(i) (mask << i)

int countBits(int w, unsigned int value){
    int cont_on = 0, cont_off = 0;

    for(unsigned int i = 0; i < 32; i++){
        if(value & mask_i(i)){
            //printf("opa ");
            cont_on++;
        }else{
            //printf("ue ");
            cont_off++;
        }
    }

    if(w == 1){
        return cont_on;
    }else{
        return cont_off;
    }
}

int main() {
    unsigned int value;
    int w;
    scanf("%d %u", &w, &value);

    printf("%d", countBits(w, value));
} 

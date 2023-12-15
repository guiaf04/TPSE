#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int pwm_configure(int pwm){
    int f = open("/sys/class/pwm/pwmchip0/export", O_WRONLY);

    switch (pwm)
    {
    case 0:
        write(f,"0",1);
        break;
    case 1:
        write(f,"1",1);
        break;
    case 2:
        write(f,"2",1);
        break;
    case 3:
        write(f,"3",1);
        break;
    case 4:
        write(f,"4",1);
        break;
    default:
        break;
    }
    close(f);
}

int pwm_set(int frequency, float duty_cycle){
    int a = open("/sys/class/pwm/pwmchip0/pwm0/enable", O_WRONLY);
    write(a,"0",1);
    close(a);

    float period = 1.0 / frequency; 
    period = period * 1000000000;
    int f = open("/sys/class/pwm/pwmchip0/pwm0/period", O_WRONLY);
    char buf[10];
    sprintf(buf, "%.0f", period);
    write(f, buf, sizeof(buf));
    close(f);

    duty_cycle = duty_cycle * period / 100;
    f = open("/sys/class/pwm/pwmchip0/pwm0/duty_cycle", O_WRONLY);
    sprintf(buf, "%.0f", duty_cycle);
    write(f, buf, sizeof(buf));
    close(f);

    f = open("/sys/class/pwm/pwmchip0/pwm0/enable", O_WRONLY);
    write(f,"1",1);
    close(f);

    a = open("/sys/class/pwm/pwmchip0/pwm0/enable", O_WRONLY);
    write(a,"1",1);
    close(a);

    return 0;
}

int main(){
    int freq;
    float duty_cycle;

    printf("Digite a frequência do PWM: ");
    scanf("%d", &freq);
    printf("Digite o duty cycle do PWM: ");
    scanf("%f", &duty_cycle);

    pwm_configure(0);
    pwm_set(freq, duty_cycle);
}
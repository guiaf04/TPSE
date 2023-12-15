#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define LOOP 5


int main(){

    int f = 0;
	
	
	for(int i = 0; i <= 3; i++){
        const char* path;
        switch (i)
        {
            case 0:
            path = "/sys/class/leds/beaglebone:green:usr0/brightness";
            break;
            case 1:
            path = "/sys/class/leds/beaglebone:green:usr1/brightness";
            break;
            case 2:
            path = "/sys/class/leds/beaglebone:green:usr2/brightness";
            break;
            case 3:
            path = "/sys/class/leds/beaglebone:green:usr3/brightness";
            break;
        }

        f=open(path, O_WRONLY);
        write(f,"0",1);
        close(f);
    }
		
    for(int i = 0; i <= 3; i++){
        const char* path;
        switch (i)
        {
            case 0:
            path = "/sys/class/leds/beaglebone:green:usr0/brightness";
            break;
            case 1:
            path = "/sys/class/leds/beaglebone:green:usr1/brightness";
            break;
            case 2:
            path = "/sys/class/leds/beaglebone:green:usr2/brightness";
            break;
            case 3:
            path = "/sys/class/leds/beaglebone:green:usr3/brightness";
            break;
        }

        f=open(path, O_WRONLY);
        write(f,"1",1);
        sleep(1);
        // LED off;
        write(f,"0",1);
        sleep(1);
        close(f);
    }
    
    printf("\nLED Blink Program is terminated !!!");
}

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DIRECTION_MAX 64
#define VALUE_MAX 5 

static int read_adc_value(int adc_number) {
    char path[DIRECTION_MAX];
    char value_str[VALUE_MAX];
    int fd;

    snprintf(path, DIRECTION_MAX, "/sys/bus/iio/devices/iio:device0/in_voltage%d_raw", adc_number);

    fd = open(path, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Failed to open ADC value file for reading!\n");
        return -1;
    }

    if (read(fd, value_str, VALUE_MAX) < 0) {
        fprintf(stderr, "Failed to read ADC value!\n");
        close(fd);
        return -1;
    }

    close(fd);

    return atoi(value_str);
}

int main() {
    int adc_value;
    float temperature;
    char input;

    // Enable ADC cape
    // int f = open("sys/devices/bone_capemgr.*/slots", O_WRONLY);
    // if(f < 0) {
    //     fprintf(stderr, "Failed to open slots file!\n");
    //     return -1;
    // }
    // write(f, "cape-bone-iio", 13);
    // close(f);

    do {
        adc_value = read_adc_value(1);
        if (adc_value < 0) {
            fprintf(stderr, "Failed to read ADC value!\n");
            return -1;
        }

        temperature = (adc_value * 1.8) / 4096.0;
        printf("Temperature: %.2f C\n", temperature);

        float fahrenheit = (temperature * 1.8) + 32;
        printf("Temperature: %.2f F\n", fahrenheit);

        printf("Press 'q' to quit or any other key to continue: ");
        scanf(" %c", &input);
    } while (input != 'q');

    return 0;
}

//# Compile your code
//arm-linux-gnueabi-gcc -o outputfile main.c
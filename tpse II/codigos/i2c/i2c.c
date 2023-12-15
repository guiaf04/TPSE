#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define I2C_BUS "/dev/i2c-2"
#define ADS1115_ADDR 0x48
#define LM35_CHANNEL 0

float read_lm35_temperature() {
    int i2c_fd;
    char buf[3];
    float voltage, temperature;

    // Inicialize a comunicação I2C com o ADS1115
    i2c_fd = open(I2C_BUS, O_RDWR);
    if (i2c_fd < 0) {
        perror("Falha ao abrir o barramento I2C");
        exit(1);
    }

    if (ioctl(i2c_fd, I2C_SLAVE, ADS1115_ADDR) < 0) {
        perror("Falha ao configurar o endereço do ADS1115");
        exit(1);
    }

    // Configure o ADS1115 para ler o canal analógico conectado ao LM35
    buf[0] = 0x01; // Config register
    buf[1] = 0xC3; // 0b11000011
    buf[2] = 0x83; // 0b10000011
    if (write(i2c_fd, buf, 3) != 3) {
        perror("Falha ao escrever no registrador de configuração do ADS1115");
        exit(1);
    }

    // Leia os dados do ADS1115
    buf[0] = 0x00; // Conversão de registro
    if (write(i2c_fd, buf, 1) != 1) {
        perror("Falha ao escrever no registrador de conversão do ADS1115");
        exit(1);
    }

    if (read(i2c_fd, buf, 2) != 2) {
        perror("Falha ao ler os dados do ADS1115");
        exit(1);
    }

    close(i2c_fd);

    // Converta os dados lidos em temperatura usando a fórmula adequada
    voltage = (buf[0] << 8 | buf[1]) * 4.096 / 32767.0;
    temperature = voltage * 100.0;

    return temperature;
}

int main() {
    char input;
    while(1){
        float temperature = read_lm35_temperature();
        printf("Temperatura lida: %.2f\n", temperature);
    } 
    return 0;
}

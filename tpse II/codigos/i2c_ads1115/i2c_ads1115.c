#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define I2C_BUS "/dev/i2c-2"
#define ADS1115_ADDR 0x48
#define LM35_CHANNEL 0

#define CONFIG_REG_OS_SINGLE    	(0x8000)
#define CONFIG_REG_OS_BUSY      	(0x0000)
#define CONFIG_REG_OS_NOTBUSY   	(0x8000)

#define CONFIG_REG_MUX_MASK     	(0x7000)
#define CONFIG_REG_MUX_DIFF_0_1		(0x0000) // default
#define CONFIG_REG_MUX_DIFF_0_3		(0x1000)
#define CONFIG_REG_MUX_DIFF_1_3		(0x2000)
#define CONFIG_REG_MUX_DIFF_2_3		(0x3000)
#define CONFIG_REG_MUX_CHAN_0 		(0x4000)
#define CONFIG_REG_MUX_CHAN_1 		(0x5000)
#define CONFIG_REG_MUX_CHAN_2 		(0x6000)
#define CONFIG_REG_MUX_CHAN_3 		(0x7000)

#define CONFIG_REG_PGA_6_144V   	(0x0000) // +/-6.144V range
#define CONFIG_REG_PGA_4_096V   	(0x0200) // +/-4.096V range
#define CONFIG_REG_PGA_2_048V   	(0x0400) // +/-2.048V range // default
#define CONFIG_REG_PGA_1_024V   	(0x0600) // +/-1.024V range
#define CONFIG_REG_PGA_0_512V   	(0x0800) // +/-0.512V range
#define CONFIG_REG_PGA_0_256V   	(0x0A00) // +/-0.256V range

#define CONFIG_REG_MODE_CONTIN		(0x0000)
#define CONFIG_REG_MODE_SINGLE		(0x0100) // default

#define CONFIG_REG_DR_8SPS			(0x0000)
#define CONFIG_REG_DR_16SPS			(0x0020)
#define CONFIG_REG_DR_32SPS			(0x0040)
#define CONFIG_REG_DR_64SPS			(0x0060)
#define CONFIG_REG_DR_128SPS		(0x0080) // default
#define CONFIG_REG_DR_250SPS		(0x00A0)
#define CONFIG_REG_DR_475SPS		(0x00C0)
#define CONFIG_REG_DR_860SPS		(0x00E0)

#define CONFIG_REG_CMODE_TRAD		(0x0000) // default
#define CONFIG_REG_CMODE_WINDOW		(0x0010)

#define CONFIG_REG_CPOL_ACTIV_LOW	(0x0000) // default
#define CONFIG_REG_CPOL_ACTIV_HIGH	(0x0080)

#define CONFIG_REG_CLATCH_NONLATCH	(0x0000) // default
#define CONFIG_REG_CLATCH_LATCH		(0x0040)

#define CONFIG_REG_CQUE_1CONV		(0x0000)
#define CONFIG_REG_CQUE_2CONV		(0x0001)
#define CONFIG_REG_CQUE_4CONV		(0x0002)
#define CONFIG_REG_CQUE_NONE		(0x0003) // default

unsigned char writeBuf[3] = {0};
int i2cFile;

// float read_lm35_temperature() {
//     int i2c_fd;
//     char buf[3];
//     float voltage, temperature;

//     // Inicialize a comunicação I2C com o ADS1115
//     i2c_fd = open(I2C_BUS, O_RDWR);
//     if (i2c_fd < 0) {
//         perror("Falha ao abrir o barramento I2C");
//         exit(1);
//     }

//     if (ioctl(i2c_fd, I2C_SLAVE, ADS1115_ADDR) < 0) {
//         perror("Falha ao configurar o endereço do ADS1115");
//         exit(1);
//     }

//     // Configure o ADS1115 para ler o canal analógico conectado ao LM35
//     buf[0] = 0x01; // Config register
//     buf[1] = 0xC3; // 0b11000011
//     buf[2] = 0x83; // 0b10000011
//     if (write(i2c_fd, buf, 3) != 3) {
//         perror("Falha ao escrever no registrador de configuração do ADS1115");
//         exit(1);
//     }

//     // Leia os dados do ADS1115
//     buf[0] = 0x00; // Conversão de registro
//     if (write(i2c_fd, buf, 1) != 1) {
//         perror("Falha ao escrever no registrador de conversão do ADS1115");
//         exit(1);
//     }

//     if (read(i2c_fd, buf, 2) != 2) {
//         perror("Falha ao ler os dados do ADS1115");
//         exit(1);
//     }

//     close(i2c_fd);

//     // Converta os dados lidos em temperatura usando a fórmula adequada //Específico para LM35
//     voltage = (buf[0] << 8 | buf[1]) * 4.096 / 32767.0;
//     temperature = voltage * 100.0;

//     return temperature;
// }

int openI2CBus(char *bus)
{
	if ((i2cFile = open(bus, O_RDWR)) < 0)
	{
		printf("Failed to open the bus. \n");
		return -1;
	} else {
		printf("Bus open \n");
		return 1;
	}
}

int setI2CSlave(unsigned char deviceAddr)
{
	if(ioctl(i2cFile, I2C_SLAVE, deviceAddr) < 0)
	{
		printf("Failed to set I2C_SLAVE at address: 0x%x. \n", deviceAddr);
		return -1;
	} else {
		printf("I2C_SLAVE set at address: 0x%x \n", deviceAddr);
		return 1;
	}

}

float readVoltage(int channel)
{
	unsigned char readBuf[2] = {0};
	unsigned int analogVal;
	float voltage;
	unsigned int config = 0;

	config = 	CONFIG_REG_OS_SINGLE		|
				CONFIG_REG_PGA_4_096V 		|
				CONFIG_REG_MODE_SINGLE 		|
				CONFIG_REG_DR_128SPS 		|
				CONFIG_REG_CMODE_TRAD 		|
				CONFIG_REG_CPOL_ACTIV_LOW 	|
				CONFIG_REG_CLATCH_NONLATCH 	|
				CONFIG_REG_CQUE_NONE;

	void configDevice(unsigned int config)
	{
		writeBuf[0] = 0x01;
		writeBuf[1] = config >> 8;
		writeBuf[2] = config & 0xFF;
		write(i2cFile, writeBuf, 3);
	}

	switch (channel) {
		case 0:
			config |= CONFIG_REG_MUX_CHAN_0;
			break;
		case 1:
			config |= CONFIG_REG_MUX_CHAN_1;
			break;
		case 2:
			config |= CONFIG_REG_MUX_CHAN_2;
			break;
		case 3:
			config |= CONFIG_REG_MUX_CHAN_3;
			break;
		default:
			printf("Give a channel between 0-3\n");
	}
	configDevice(config);
	
	while (readBuf[0] >> 7 != 1) {
        	read(i2cFile, readBuf, 2);
        }
	
	writeBuf[0] = 0x00;
	write(i2cFile, writeBuf, 1);

	if(read(i2cFile, readBuf, 2) != 2) // read data and check error
	{
		printf("Error : Input/Output Error \n");
	}
	else
	{
		analogVal = readBuf[0] << 8 | readBuf[1];
		voltage = (float)analogVal*4.096/32767.0;
	}

	return voltage;
}

int main() {
    if(openI2CBus("/dev/i2c-2") == -1)
	{
		return EXIT_FAILURE;
	}
	setI2CSlave(0x48);

    int temperature;

	while(1)
	{
		printf("CH_0 = %.2f V | ", readVoltage(0));
		printf("CH_1 = %.2f V | ", readVoltage(1));
		printf("CH_2 = %.2f V \n", readVoltage(2));
        temperature = readVoltage(0) * 100;
        printf("Temperature = %d °C \n", temperature);
        sleep(1);
	}   
    
    return 0;
}

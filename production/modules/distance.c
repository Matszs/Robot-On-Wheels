
#include  <stdio.h>
#include  <unistd.h>
#include  "rpiGpio.h"
#include  <wiringPi.h>
#include  <softPwm.h>

void *distancePerformRead(void *arg);
uint8_t distanceValue = 50;

void distanceInit() {
	pthread_t distanceThread;
	pthread_create(&distanceThread, NULL, distancePerformRead, NULL);
}

uint8_t distanceRead() {
	return distanceValue;
}

void *distancePerformRead(void *arg) {
    uint8_t TxData1[2] = {00, 81}; //add second array element; read the datasheet of the srf02
    uint8_t TxData2[1] = {0x03}; //What is the function of memory location 3?; see datasheet srf02

    if (gpioSetup()!= OK)
           dbgPrint(DBG_INFO, "gpioSetup failed.\n");

    else if (gpioI2cSetup() != OK)
            dbgPrint(DBG_INFO, "gpioI2cSetup failed.\n");

    if (gpioI2cSet7BitSlave(0x70) != OK)
            dbgPrint(DBG_INFO, "gpioI2cSet7BitSlave failed.\n");

    while(1) {
       gpioI2cWriteData(&TxData1[0], 2);
       usleep(100000);  //give the sensor time for measurement

       gpioI2cWriteData(&TxData2[0], 1);  //ask for the lower order byte of the range
       gpioI2cReadData(&distanceValue, 1);

       //printf("DIST: %d \n", distanceValue);

       usleep(2000000);
     }

    gpioI2cCleanup();
    gpioCleanup();
}



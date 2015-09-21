//
//  main.c
//  Robot
//
//  Created by Patrick Hendriks on 14-09-15.
//  Copyright (c) 2015 Patrick Hendriks. All rights reserved.
//

#include <stdio.h>
#include <sys/socket.h>
#include <pthread.h>
#include "control.h"

/////////

#include "rpiGpio.h"
#include <pthread.h>

void Motorinit()
{
    uint8_t Totalpower[2]={4,250};     // power between 0 and 255
    uint8_t Softstart[3]={0x91,23,0};  // add explanation
    
    
    if (gpioSetup()!= OK)
        dbgPrint(DBG_INFO, "gpioSetup failed\n");
    else if (gpioI2cSetup() != OK)
        dbgPrint(DBG_INFO, "gpioI2cSetup failed\n");
    
    if (gpioI2cSet7BitSlave(0x32) != OK)
        dbgPrint(DBG_INFO, "gpioI2cSet7BitSlave failed.\n");
    
    if (gpioI2cWriteData(&Totalpower[0], 2) != OK)
        dbgPrint(DBG_INFO, "gpioI2cWriteData failed\n");
    
    gpioI2cWriteData(&Softstart[0],3);   //number of bytes = 3
    //What is a soft start?
}

void Motorcontrol(uint8_t voorachterLinks, uint8_t SnelheidLinks, uint8_t voorachterRechts, uint8_t SnelheidRechts){
    //printf("%d %d, %d %d\n", voorachterLinks, SnelheidLinks, voorachterRechts, SnelheidRechts);
    uint8_t richtingLinks = (voorachterLinks == 1) ? 2 : 3;
    uint8_t richtingRechts = (voorachterRechts == 1) ? 2 : 3;

    uint8_t MotorHF[7] = {7,3,SnelheidLinks,richtingLinks,3,SnelheidRechts,richtingRechts};
    gpioI2cWriteData(MotorHF[0],7);
}

int main(int argc, const char * argv[]) {
    
    void (*motorCallback)(uint8_t,uint8_t,uint8_t,uint8_t) = Motorcontrol;
    
    
    movement direction;
    
    
    unpackMovement(238, &direction);
    MotorControl(&direction, *motorCallback);
    
    usleep(8000);
    
    unpackMovement(102, &direction);
    MotorControl(&direction, *motorCallback);
    
    usleep(8000);
    
    unpackMovement(0, &direction);
    MotorControl(&direction, *motorCallback);
    
    return 0;
}

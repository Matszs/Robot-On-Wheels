//
//  main.c
//  Robot
//
//  Created by Patrick Hendriks on 14-09-15.
//  Copyright (c) 2015 Patrick Hendriks. All rights reserved.
//

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
//// custom imports
#include "control.h"
#include "control.c"
/////////
#include "rpiGpio.h"


void Motorinit()
{
    uint8_t Totalpower[2]={4,250};
    uint8_t Softstart[3]={0x91,23,0};
    
    if (gpioSetup()!= OK)
        dbgPrint(DBG_INFO, "gpioSetup failed\n");
    else if (gpioI2cSetup() != OK)
        dbgPrint(DBG_INFO, "gpioI2cSetup failed\n");
    
    if (gpioI2cSet7BitSlave(0x32) != OK)
        dbgPrint(DBG_INFO, "gpioI2cSet7BitSlave failed.\n");
    
    if (gpioI2cWriteData(&Totalpower[0], 2) != OK)
        dbgPrint(DBG_INFO, "gpioI2cWriteData failed\n");
    
    gpioI2cWriteData(&Softstart[0],3);
}

void MotorcontrolMovement(uint8_t voorachterLinks, uint8_t SnelheidLinks, uint8_t voorachterRechts, uint8_t SnelheidRechts){

    uint8_t richtingLinks = (voorachterLinks == 1) ? 1 : 2;
    uint8_t richtingRechts = (voorachterRechts == 1) ? 1 : 2;
    uint8_t MotorC[7];
    
    //Wanneer commando stop oftwel 0 gegeven wordt over de socket.
    if(richtingLinks == 2 && richtingRechts == 2 && SnelheidLinks == 0 && SnelheidRechts == 0)
    {
        
        MotorC[0] = 7;
        MotorC[1] = 0;
        MotorC[2] = 0;
        MotorC[3] = 0;
        MotorC[4] = 0;
        MotorC[5] = 0;
        MotorC[6] = 0;

    }
    else
    {

        MotorC[0] = 7;
        MotorC[1] = 3;
        MotorC[2] = speedTable[SnelheidLinks];
        MotorC[3] = richtingLinks;
        MotorC[4] = 3;
        MotorC[5] = speedTable[SnelheidRechts];
        MotorC[6] = richtingRechts;

    }
    gpioI2cWriteData(&MotorC[0],7);

}

int main(int argc, const char * argv[]) {
    
    void (*motorCallback)(uint8_t,uint8_t,uint8_t,uint8_t) = MotorcontrolMovement;
    Motorinit();
    
    movement direction;
    
    printf("Movement 1 (vooruit)\n");
    unpackMovement(238, &direction);
    MotorControl(&direction, *motorCallback);
    
    sleep(3);
    
    printf("Movement 2 (achteruit)\n");
    unpackMovement(102, &direction);
    MotorControl(&direction, *motorCallback);
    
    sleep(3);
    
    printf("Movement 3 (stop)\n");
    unpackMovement(0, &direction);
    MotorControl(&direction, *motorCallback);
    
    return 0;
}

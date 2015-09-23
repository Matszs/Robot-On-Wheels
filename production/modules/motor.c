//
//  control.c
//  Robot
//
//  Created by Patrick Hendriks on 14-09-15.
//  Copyright (c) 2015 Patrick Hendriks. All rights reserved.
//  Toegestaan om voor het Project Robot on Wheels vrij te gebruiken en of aan te passen.
//  Edited by Ekko Scholtens on 22-09-15.
//  Edited by Mats Otten on 22-09-15.
//

#include "motor.h"
int fd;

void writeData(uint8_t * data, int lenght){
    int i;
	for (i = 0; i < lenght; i++)
		wiringPiI2CWrite(fd, data[i]);
}

void unpackMovement(uint8_t input, movement *direction){
    direction->Left = input >> 4;
    direction->Right = (input << 4) >> 4;
}

void MotorControl(movement *direction, void (*motorCallback)(uint8_t,uint8_t,uint8_t,uint8_t)){
   // 0000 (links)  		0000 (rechts)
   // ^ richting			^ richting
   //  ^^^ snelheid			 ^^^ snelheid

   // 0001 0001

    uint8_t rotationDirectionLeft = direction->Left >> 3 & 1;
    uint8_t rotationDirectionRight = direction->Right >> 3 & 1;
    uint8_t rotationSpeedLeft = direction->Left & 7;
    uint8_t rotationSpeedRight = direction->Right & 7;

	if(DEBUG) {
		printf("direction->Left:        %d\n", direction->Left);
		printf("direction->Right:       %d\n", direction->Right);
		printf("rotationDirectionLeft:  %d\n", rotationDirectionLeft);
		printf("rotationDirectionRight: %d\n", rotationDirectionRight);
		printf("rotationSpeedLeft:      %d\n", rotationSpeedLeft);
		printf("rotationSpeedRight:     %d\n\n", rotationSpeedRight);
    }

    motorCallback(rotationDirectionLeft, rotationSpeedLeft, rotationDirectionRight, rotationSpeedRight);
}

void MotorcontrolMovement(uint8_t rotationDirectionLeft, uint8_t rotationSpeedLeft, uint8_t rotationDirectionRight, uint8_t rotationSpeedRight){

    uint8_t richtingLinks = (rotationDirectionLeft == 1) ? 1 : 2;
    uint8_t richtingRechts = (rotationDirectionRight == 1) ? 1 : 2;
    uint8_t MotorC[7];

    // No speed, no direction so stop moving.
    if(richtingLinks == 2 && rotationSpeedLeft == 0 && richtingRechts == 2 && rotationSpeedRight == 0) {
    	if(DEBUG)
    		printf("STOP!\n");
		MotorC[0] = 7;
		MotorC[1] = 0;
		MotorC[2] = 0;
		MotorC[3] = 0;
		MotorC[4] = 0;
		MotorC[5] = 0;
		MotorC[6] = 0;
    } else {
		MotorC[0] = 7;
		MotorC[1] = 3;
		MotorC[2] = speedTable[rotationSpeedLeft];
		MotorC[3] = (rotationSpeedLeft == 0 ? 0 : richtingLinks);
		MotorC[4] = 3;
		MotorC[5] = speedTable[rotationSpeedRight];
		MotorC[6] = (rotationSpeedRight == 0 ? 0 : richtingRechts);
    }
	writeData(&MotorC[0], 7);
}

void MotorInit() {
	uint8_t Totalpower[2]={4,250};
	uint8_t Softstart[3]={0x91,23,0};
	fd = wiringPiI2CSetup(0x32);
	if (fd < 0)
		printf("wiringPiI2CSetup failed.\n");
	writeData(&Totalpower[0], 2);
	writeData(&Softstart[0], 3);
}
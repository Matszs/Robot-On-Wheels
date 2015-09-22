//
//  main.c
//  row-server
//
//  Created by Mats Otten on 14-09-15.
//  Copyright (c) 2015 Mats Otten. All rights reserved.

// sudo gcc -o project project.c -L/usr/local/lib  -lwiringPi -lwiringPiDev -lpthread -lm -lrpigpio
//

#define PORT_NUMBER	1212

#include <stdio.h>
#include <string.h> //strlen
#include <unistd.h> // write
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <pthread.h> // threads

#include "rpiGpio.h"
#include "socket.c"
#include "modules/motor.c"


int main() {
    setvbuf(stdout, NULL, _IONBF, 0); // display printf's
    
    init();
    run();
    return 0;
}

void run() {
	MotorInit();
	
    while(1) {
       
    }
}

void onCommand(char *commandData) {

	void (*motorCallback)(uint8_t,uint8_t,uint8_t,uint8_t) = MotorcontrolMovement;
	movement direction;

	printf("%d", (uint8_t)commandData[0]);

	if((uint8_t)commandData[0] == 113) {
		unpackMovement(0, &direction);
        MotorControl(&direction, *motorCallback);
	} else {

		unpackMovement((uint8_t)commandData[0], &direction);
		MotorControl(&direction, *motorCallback);
    }

	// TODO: add engine ...
}

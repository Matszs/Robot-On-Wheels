//
//  main.c
//  row-server
//
//  Created by Mats Otten on 14-09-15.
//  Copyright (c) 2015 Mats Otten. All rights reserved.

// sudo gcc -o project project.c -L/usr/local/lib  -lwiringPi -lwiringPiDev -lpthread -lm -lrpigpio
//

#define PORT_NUMBER	1212
#define DEBUG	0

#include <stdio.h>
#include <string.h> //strlen
#include <unistd.h> // write
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <pthread.h> // threads
#include <wiringPi.h>

#include  "rpiGpio.h"
#include  <softPwm.h>

#include "modules/socket.c"
#include "modules/motor.c"
#include "modules/distance.c"

int main() {
    setvbuf(stdout, NULL, _IONBF, 0); // display printf's

    run();
    return 0;
}

void run() {
	socketInit();
	MotorInit();
	distanceInit();
	
    while(1) {
       printf("afstand: %d\n", distanceRead());
       usleep(1000000);
    }
}

void onCommand(char *commandData) {

	void (*motorCallback)(uint8_t,uint8_t,uint8_t,uint8_t) = MotorcontrolMovement;
	movement direction;

	// The next line clears the input if commandData[0] = 10;
	//commandData[strcspn(commandData, "\r\n")] = 0; // find location of \r\n and 'removes' it.

	unpackMovement((uint8_t)commandData[0], &direction);
	MotorControl(&direction, *motorCallback);

	// TODO: add engine ...
}

//
//  main.c
//  row-server
//
//  Created by Mats Otten on 14-09-15.
//  Copyright (c) 2015 Mats Otten. All rights reserved.
//

#define PORT_NUMBER	1212

#include <stdio.h>
#include <string.h> //strlen
#include <unistd.h> // write
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <pthread.h> // threads

#include "socket.c"

int main() {
    setvbuf(stdout, NULL, _IONBF, 0); // display printf's
    
    init();
    run();
    return 0;
}

void run() {
    // TODO: add runnable ...
	
    while(1) {
       
    }
}

void onCommand(char *commandData) {
	size_t ln = strlen(commandData);
	if (commandData[ln - 1] == '\n')
		commandData[ln - 1] = '\0';
	if (commandData[ln - 2] == '\r')
		commandData[ln - 2] = '\0';

    printf("%s\n", commandData);

	// TODO: add engine ...
}

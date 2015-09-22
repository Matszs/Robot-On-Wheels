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


void init();
void *listenForConnections(void *arg);
void run();

struct sockaddr_in server;
int socketConnection;
int userSocket; // only one user can connect at the same time

pthread_t socketConnectionThread;	// this is our thread identifier

int main() {
    setvbuf(stdout, NULL, _IONBF, 0); // display printf's

    init();
    run();
    return 0;
}

void run() {
    // add inits of sub systems

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

	// TODO: Add motor management
}

void init() {
    socketConnection = socket(AF_INET , SOCK_STREAM , 0);

    if (socketConnection == -1)
        printf("Could not creeate socket");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( PORT_NUMBER );

    // Make is possible to re-use ports.
    int yes = 1;
    if ( setsockopt(socketConnection, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1 )
        printf("Error so_reusaddr");

    //Bind
    if( bind(socketConnection,(struct sockaddr *)&server , sizeof(server)) == -1)
        printf("Couln't bind to socket, port already in use?");

    //Listen
    listen(socketConnection , 3);

    //start listening in other thread
    pthread_create(&socketConnectionThread, NULL, listenForConnections, NULL);
}

void *listenForConnections(void *arg) {
    while(1) {
        int c;
        long read_size;
        struct sockaddr_in client;
        char client_message[1024];

        c = sizeof(struct sockaddr_in);

        int tmpUserSocket;

        tmpUserSocket = accept(socketConnection, (struct sockaddr *)&client, (socklen_t*)&c);
        if (userSocket == -1) {
            printf("accept failed");
        }

        if(userSocket >= 0) // if there is already a socket connected, disconnect
            close(userSocket);

        userSocket = tmpUserSocket;

        char * sendBuff = "Connection established.";

        write(userSocket, sendBuff, strlen(sendBuff));

        printf("Connected!");

        while( (read_size = recv(userSocket, client_message, 1024, 0)) > 0 ){
            onCommand(client_message);
			for (int i = 0; i < read_size; i++) {
				client_message[i] = '\0';
			}
        }

        if(read_size == 0) {
            close(userSocket);
            printf("Client disconnected");
        }
        else if(read_size == -1) {
            close(userSocket);
            printf("Client error");
        }
    }
}
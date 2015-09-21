//
//  control.c
//  Robot
//
//  Created by Patrick Hendriks on 14-09-15.
//  Copyright (c) 2015 Patrick Hendriks. All rights reserved.
//  Toegestaan om voor het Project Robot on Wheels vrij te gebruiken en of aan te passen.
//  

#include "control.h"

uint8_t speedTable[7] = {0,70,89,108,127,146,165};



void unpackMovement(uint8_t getal, movement *direction){
    uint8_t links, rechts;
    
    
    links = getal >> 4 & 15;
    rechts = getal & 15;
    direction->Left = links;
    direction->Right = rechts;
}



void MotorControl(movement *direction, void (*motorCallback)(uint8_t,uint8_t,uint8_t,uint8_t)){
    
    uint8_t RijrichtingLinks = direction->Left & 8;
    uint8_t RijrichtingRechts = direction->Right & 8;
    uint8_t SnelheidLinks = direction->Left & 7;
    uint8_t SnelheidRechts = direction->Right & 7;
    
    uint8_t voorachterLinks = RijrichtingLinks ? 1 : 0;
    uint8_t voorachterRechts = RijrichtingRechts ? 1 : 0;
    
    
    motorCallback(voorachterLinks, SnelheidLinks, voorachterRechts, SnelheidRechts);
    
}
//
//  control.h
//  Robot
//
//  Created by Patrick Hendriks on 14-09-15.
//  Copyright (c) 2015 Patrick Hendriks. All rights reserved.
//

#ifndef __Robot__control__
#define __Robot__control__

#include <stdio.h>


typedef struct {
    uint8_t Left:4;
    uint8_t Right:4;
} movement;

void unpackMovement(uint8_t getal, movement *direction);

void MotorControl(movement *direction, void (*motorCallback)(uint8_t,uint8_t,uint8_t,uint8_t));



#endif /* defined(__Robot__control__) */

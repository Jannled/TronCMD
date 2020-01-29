/*
 * gamepad_lib.h
 *
 * Created: 28.01.2020 16:21:59
 *  Author: mmicha
 */ 


#ifndef GAMEPAD_LIB_H_
#define GAMEPAD_LIB_H_

#include <stdint.h>

//NES Controller Button-masks
#define B 0x1
#define Y 0x2
#define Select 0x4
#define Start 0x8
#define Up 0x10
#define Down 0x20
#define Left 0x40
#define Right 0x80
#define A 0x100
#define X 0x200
#define ShoulderL 0x400
#define ShoulderR 0x800

//Game pad Pin out defines
#define P_DATA  PC5
#define P_LATCH PC6
#define P_CLOCK PC7

typedef uint16_t Gamepad;

Gamepad gamepad1;

/**
 * \brief Game pad initializer
 * set's Game pad specific Input modes do pins
 */
void initGamepad();

void updateGamepadState();

/**
 * \brief read Game pad state
 * does the necessary manipulations to shift all values out of the Game pad and returns it
 * 
 * \return the Game pad state as uint16_t
 */
uint16_t getGamepadState();


#endif /* GAMEPAD_LIB_H_ */
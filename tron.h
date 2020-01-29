#ifndef TRON_H_
#define TRON_H_

#include "bitmap.h"
#include "gamepad_lib.h"
#include "usart_lib.h"


typedef struct {
	unsigned char x;
	unsigned char y;
} vec2;


//Player "class" values
typedef struct {
	char direction;
	char lastDir;
	vec2 pos;
	Bitmap bmap;
} Player;

//game states
#define START 0
#define DRIVING 1
#define ENDE 2

//Playable area
#define AREA_WIDTH  BITMAP_WIDTH
#define AREA_HEIGHT BITMAP_HEIGHT

/**
 * \brief Tron initializer
 * set's player positions and directions
 * 
 */
void tronInit();


/**
 * \brief A fancy start Screen
 * 
 */
void startScreen();


/**
 * \brief Actual Game loop
 * Move players, update position, draw trails etc. 
 */
void drive();

/**
 * \brief An end Screen
 * prints who won and to restart game
 */
void endScreen();


/**
 * \brief Clears the terminal
 *	helper function to clear the terminal
 */
void clearScreen();

/**
 * \brief Draws border around the playable area
 * helper function to draw a border
 */
void drawBorder();

/**
 * \brief Changes player position
 * check for collisions with border to wrap around, moves player in selected direction
 */
void movePlayer(Player *p);

/**
 * \brief The main loop
 * the loop that runs the game
 */
void tronGameloop();

#endif /* TRON_H_ */
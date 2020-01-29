#include "gamepad_lib.h"
#include "usart_lib.h"

#include <stdio.h>

void initGamepad()
{
	gamepad1 = 0;
}

void updateGamepadState()
{
	

	char c = usartGetchar();
	switch (c)
	{
		case '\e':
			if(usartGetchar() == '[')
			switch(usartGetchar())
			{
				case 'D': // ARROW UP
					gamepad1 |= Left;
					break;
				case 'C': // ARROW DOWN
					gamepad1 |= Right;
					break;
				case 'A': // ARROW LEFT
					gamepad1 |= Up;
					break;
				case 'B': // AROW RIGHT
					gamepad1 |= Down;
					break;
			}
			break;
		
		case 'a': // A
			gamepad1 |= Y;
			break;

		case 'd': // D
			gamepad1 |= A;
			break;

		case 'w': // W
			gamepad1 |= X;
			break;

		case 's': // S
			gamepad1 |= B;
			break;

		case 10: // ENTER as Start
			printf("Start");
			gamepad1 |= Start;
			break;

		case 32: // SPACE as Select
			gamepad1 |= Select;
			break;

		default:
			break;
	}
	//printf("Input: %d\n", c);
}

uint16_t getGamepadState()
{
	Gamepad gp = gamepad1;
	gamepad1 = 0;
	return gp;
}
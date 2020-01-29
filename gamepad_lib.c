#include "gamepad_lib.h"
#include "usart_lib.h"

#include <stdio.h>


#include <termios.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

void initGamepad()
{
	gamepad1 = 0;
}

//Stores terminal options
struct termios org_opts, new_opts;
int res=0;

void updateGamepadState()
{
	//Source: CptPicard #2 https://ubuntuforums.org/showthread.php?t=554845
	//-----  store old settings -----------
	res=tcgetattr(STDIN_FILENO, &org_opts);
	assert(res==0);
	//---- set new terminal parms --------
	memcpy(&new_opts, &org_opts, sizeof(new_opts));
	new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ICRNL); //Could also capture ISIG, then now signals are send like CTRL+C
	new_opts.c_cc[VMIN] = 0;
	new_opts.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);

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

	//------  restore old settings ---------
	res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
	assert(res==0);
}

uint16_t getGamepadState()
{
	Gamepad gp = gamepad1;
	gamepad1 = 0;
	return gp;
}
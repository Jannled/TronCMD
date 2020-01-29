#define _DEFAULT_SOURCE

#include "tron.h"

#include "bitmap.h"

#include <stdbool.h>
#include <signal.h>
#include <unistd.h>

bool running = true;

void exitus()
{
	running = false;
	usartShowCursor(true); //Unhide the cursor
	clearScreen();
}

void main(int argc, char** argv)
{
	signal(SIGINT, exitus);
	signal(SIGTERM, exitus);

	initGamepad();
	tronInit();

	usartShowCursor(false);
	
	while(running)
	{
		tronGameloop();
		updateGamepadState();
		usleep(30000);
	}

	usartShowCursor(true);
}
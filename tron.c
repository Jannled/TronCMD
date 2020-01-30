#include "tron.h"

#define STARTSCREEN_WIDTH 57
#define STARTSCREEN_HEIGHT 11

char startScreenArt[STARTSCREEN_HEIGHT][STARTSCREEN_WIDTH] = {
	{"       _            _           _            _          "},
	{"      /\\ \\         /\\ \\        /\\ \\         /\\ \\     _  "},
	{"      \\_\\ \\       /  \\ \\      /  \\ \\       /  \\ \\   /\\_\\"},
	{"      /\\__ \\     / /\\ \\ \\    / /\\ \\ \\     / /\\ \\ \\_/ / /"},
	{"     / /_ \\ \\   / / /\\ \\_\\  / / /\\ \\ \\   / / /\\ \\___/ / "},
	{"    / / /\\ \\ \\ / / /_/ / / / / /  \\ \\_\\ / / /  \\/____/  "},
	{"   / / /  \\/_// / /__\\/ / / / /   / / // / /    / / /   "},
	{"  / / /      / / /_____/ / / /   / / // / /    / / /    "},
	{" / / /      / / /\\ \\ \\  / / /___/ / // / /    / / /     "},
	{"/_/ /      / / /  \\ \\ \\/ / /____\\/ // / /    / / /      "},
	{"\\_\\/       \\/_/    \\_\\/\\/_________/ \\/_/     \\/_/       "}
};

Player p1;
Player p2;

int gameState = START;

void tronInit()
{
	clearScreen();
	
	p1.direction = 'L';
	p1.pos.x = AREA_WIDTH/2 - 10;
	p1.pos.y = AREA_HEIGHT/2;
	clearBitmap(p1.bmap);

	p2.direction = 'R';
	p2.pos.x = AREA_WIDTH/2 + 10;
	p2.pos.y = AREA_HEIGHT/2;
	clearBitmap(p2.bmap);
}

void startScreen()
{
	uint16_t gamepad = getGamepadState();
	if(gamepad & Start)
	{	
		gameState = DRIVING;
		tronInit();
		return;
	}
	
	for(int i=0; i<STARTSCREEN_HEIGHT; i++)
	{
		usartSetCursor(10, 5+i);
		usartPutstring(startScreenArt[i]);
	}
	
	usartSetCursor(30, 30);
	usartPutstring("PRESS START TO BEGIN");
}


void movePlayer(Player *p)
{
	//save to bitmap
	setBit(p->bmap, p->pos.x, p->pos.y);
	
	//Don't move inside me
	switch(p->direction)
	{
		case 'L':
		if(p->lastDir == 'R')
		p->direction = p->lastDir;
		break;
		
		case 'R':
		if(p->lastDir == 'L')
		p->direction = p->lastDir;
		break;
		
		case 'U':
		if(p->lastDir == 'D')
		p->direction = p->lastDir;
		break;
		
		case 'D':
		if(p->lastDir == 'U')
		p->direction = p->lastDir;
		break;
	}
	
	//Move player
	switch(p->direction)
	{
		case 'L':
		p->pos.x--;
		break;
		
		case 'R':
		p->pos.x++;
		break;
		
		case 'U':
		p->pos.y--;
		break;
		
		case 'D':
		p->pos.y++;
		break;
	}
	
	//Check if out of bounds
	if(p->pos.x <= 0) p->pos.x = AREA_WIDTH-1;
	if(p->pos.y <= 0) p->pos.y = AREA_HEIGHT-1;

	if(p->pos.x >= AREA_WIDTH) p->pos.x = 0;
	if(p->pos.y >= AREA_HEIGHT) p->pos.y = 0;
}


void drive()
{
	uint16_t gamepad = getGamepadState();
	
	p1.lastDir = p1.direction;
	p2.lastDir = p2.direction;
	
	//Player 1
	if(gamepad & Left)
		p1.direction = 'L';
	if(gamepad & Right)
		p1.direction = 'R';
	if(gamepad & Up)
		p1.direction = 'U';
	if(gamepad & Down)
		p1.direction = 'D';
	
	//Player 2
	if(gamepad & Y)
		p2.direction = 'L';
	if(gamepad & A)
		p2.direction = 'R';
	if(gamepad & X)
		p2.direction = 'U';
	if(gamepad & B)
		p2.direction = 'D';
	
	movePlayer(&p1);
	movePlayer(&p2);
	
	//collision
	if((p1.pos.x == p2.pos.x) && (p1.pos.y == p2.pos.y))
	{
		gameState = ENDE+1;
	}
	else if(getBit(p1.bmap, p1.pos.x, p1.pos.y))
	{
		gameState = ENDE+2;
	}
	else if(getBit(p2.bmap, p2.pos.x, p2.pos.y))
	{
		gameState = ENDE+3;
	}
	else if(getBit(p2.bmap, p1.pos.x, p1.pos.y))
	{
		gameState = ENDE+4;
	}
	else if(getBit(p1.bmap, p2.pos.x, p2.pos.y))
	{
		gameState = ENDE+5;
	}

	usartSetCursor(p1.pos.x+1, p1.pos.y+1);
	usartPutstring("\e[46m");
	usartPutchar(' ');
	
	usartSetCursor(p2.pos.x+1, p2.pos.y+1);
	usartPutstring("\e[45m");
	usartPutchar(' ');
}

void endScreen()
{
	char gameover[][53] = {
		"Das nennt man Vollkontakt!",
		"Spieler 1 hat sich selbst getötet!",
		"Spieler 2 hat sich selbst getötet!",
		"Spieler 1 ist durch die Spur von Spieler 2 gefahren!",
		"Spieler 2 ist durch die Spur von Spieler 1 gefahren!"
	};

	usartSetCursor(15, AREA_HEIGHT / 2 - 10);
	usartPutstring(gameover[gameState - ENDE - 1]);
	usartSetCursor(10, (AREA_HEIGHT / 2));
	usartPutstring("press SELECT to reset");
	
	uint16_t gamepad = getGamepadState();
	if(gamepad & Select)
	{
		clearScreen();
		
		gameState = START;
	}
}

void drawBorder()
{
	usartSetCursor(0, 0);
	for(int i=0; i<AREA_WIDTH+2; i++)
	usartPutchar(' ');
	
	usartSetCursor(AREA_HEIGHT+2, 0);
	for(int i=0; i<AREA_WIDTH+2; i++)
	usartPutchar(' ');
	
	for(int i=0; i<AREA_HEIGHT+2; i++)
	{
		usartSetCursor(0, i);
		usartPutchar(' ');
		
		usartSetCursor(AREA_WIDTH+2, i);
		usartPutchar(' ');
	}
}

void clearScreen()
{
	//usartPutstring("\e[47m"); //Background white
	usartPutstring("\e[40m"); //Background black
	usartPutstring("\e[2J");  //Clear screen
}

void tronGameloop()
{
	usartPutstring("\e[40m"); //Background black
	
	switch(gameState)
	{	
		case START:
			startScreen();
			break;
		case DRIVING:
			drive();
			break;
		default:
			endScreen();
			break;
	}
	
	usartPutstring("\e[H");   //Home cursor
}

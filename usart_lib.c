#include "usart_lib.h"

#ifdef _WIN32
#include <conio.h>
#elif __linux__
#define getch() getchar()
#endif

#include <stdio.h>

int usartGetchar()
{
	return getch();
}

void usartPutchar(unsigned char c)
{
	printf("%c", c);
}

void usartPutstring(char *string)
{
	printf("%s", string);
}

void usartSetCursor(int x, int y) //"\e[%d;%df" erster eintrag ist line aka y zweiter colum aka x
{
	printf("\e[%d;%df", y, x);
}

void usartShowCursor(bool show)
{
	printf("\e[?25%s", show ? "h" : "l");
}
#include "usart_lib.h"

#ifdef _WIN32
#include <conio.h>

#elif __linux__
#include <termios.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

//Stores terminal options
struct termios org_opts, new_opts;
int res=0;

#define getch() getchar()
#endif

#include <stdio.h>

int usartGetchar()
{
	#ifdef __linux__
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
	#endif

	char c = getch();

	#ifdef __linux__
	//------  restore old settings ---------
	res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
	assert(res==0);
	#endif

	return c;
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
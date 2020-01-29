/*
 * usart_lib.h
 *
 * Created: 28.01.2020 16:14:43
 *  Author: mmicha
 */ 


#ifndef USART_LIB_H_
#define USART_LIB_H_

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
	disabled  = 0b00,
	reserverd = 0b01,
	even      = 0b10,
	odd       = 0b11
} Parity;

typedef enum
{
	bit5 = 0b00,
	bit6 = 0b01,
	bit7 = 0b10,
	bit8 = 0b11
} Databits;

/**
 * \brief USART initializer
 * a function to initialize the USART protocol with selected parameters
 * 
 * \param bitrate the data rate for the USART communication
 * \param databits how many databits should be send
 * \param parity if parity should be enabled or how many parity-bits should be used
 * \param stopbits how many stop-bits should be in use
 * 
 */
void initUsart(uint32_t bitrate, uint8_t databits, Parity parity, uint8_t stopbits);

/**
 * \brief read char from USART input
 * gets the char from the USART input
 * 
 * \return char as int
 */
int usartGetchar(void);

/**
 * \brief output char to USART
 * sends a char to USART
 * 
 * \param char the char to send
 */
void usartPutchar(unsigned char c);

/**
 * \brief outputs string to USART
 * sends a string to USART using usartPutchar()
 * 
 * \param char* the string to send
 */
void usartPutstring(char *string);

/**
 * \brief setts the terminal courser
 * a function to set the terminal courser position to x,y
 * 
 * \param x int x coordinate
 * \param y int y coordinate
 */
void usartSetCursor(int x, int y);

void usartShowCursor(bool show);

#endif /* USART_LIB_H_ */
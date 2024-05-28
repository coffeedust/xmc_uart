/*
 * main.c
 *
 *  Created on: 2024 May 27 13:33:41
 *  Author: Administrator
 */




#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <stdio.h>
#include <stdbool.h>

#define UartRxBufferMax 255
uint8_t UartRxBuffer[UartRxBufferMax];
int			UartRxBufferGp;	// Get pointer, Read
int			UartRxBufferPp; // Put pointer, Write

bool TxEnd = false;

// printf 재정의
int _write(int file, char *p, int len) {
	UART_Transmit(&UART_0, p, len);
	return len;
}

void callbackTransmit() {
	TxEnd = true;
}

void callbackReceive() {
	UartRxBuffer[UartRxBufferPp++] = UART_GetReceivedWord(&UART_0);
	UartRxBufferPp %= UartRxBufferMax;
	UART_ClearFlag(&UART_0, XMC_UART_CH_STATUS_FLAG_RECEIVE_INDICATION | XMC_UART_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION);
}

uint16_t	getChar() {
	uint16_t result = -1;
	if(UartRxBufferGp == UartRxBufferPp) return result;
	result = UartRxBuffer[UartRxBufferGp++];
	UartRxBufferGp %= UartRxBufferMax;
	return result;
}

char *getMessage() {
	static char result[100];
	static int pos = 0;
	uint16_t ch = getChar();
	if(ch != -1) {
		if(ch == '\n') {
			memset(result, 0, 100);
			pos = 0;
		}
		else {
			result[pos++] = ch;
		}
	}
	return result;
}

int delay1000;

// 1ms
void callback() {
	if(delay1000 > 0)
		delay1000--;

}

void delay(int d) {
	delay1000 = d;
	while(delay1000 > 0)
		;
}

static bool isFlag = false;
static int angle = 0;
float sinValue;
float cosValue;
char *msg;

int main(void)
{
  DAVE_STATUS_t status;

  status = DAVE_Init();           /* Initialization of DAVE APPs  */

  if (status != DAVE_STATUS_SUCCESS)
  {
    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
    XMC_DEBUG("DAVE APPs initialization failed\n");

    while(1U)
    {

    }
  }

  int id = SYSTIMER_CreateTimer(1000, SYSTIMER_MODE_PERIODIC, callback, NULL);
  SYSTIMER_StartTimer(id);

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {
  	if(isFlag) angle++;
  	if(angle >= 360) angle = 0;
  	sinValue = sin(angle * 3.14 / 180);
  	cosValue = cos(angle * 3.14 / 180);
  	printf("%f, %f\n", sinValue, cosValue);
  	msg = getMessage();
  	if(strlen(msg) >= 5)
			if(strncmp(msg, "START", 5) == 0) {
				isFlag = true;
			}
  	if(strlen(msg) >= 4)
  	if(strncmp(msg, "STOP", 4) == 0) {
  		isFlag = false;
  	}
  	delay(10);
  }
}

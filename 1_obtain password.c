///////////////////////////////////////////////////////////////
// University of Tehran - Summer 2020
// Microcontrollers Lab - Lab 4
// Y. Parhizkar, R. Ghoroghchian, M. Haghifam
// 
// Part 1/3
// Description: Obtains and displays the password of our group's account on the server.
///////////////////////////////////////////////////////////////

#include "adc.h"
#include "uart.h"
#include "lcd.h"
#include "timer.h"


int main()
{
	char strArr[12] = "GROUP 08\n";
	char passwordArr[9] = "1234567\n";
	int i;
	SystemInit();
	LCD_SetUp(P0_0, P0_1, P0_2, P_NC, P_NC, P_NC, P_NC, P0_4,P0_5,P0_6, P0_7);
	LCD_Init(2, 16);
	LCD_Clear();
	UART2_Init(9600);
	UART2_TxString(strArr);
 	i = UART2_RxString(passwordArr);
	passwordArr[7] = NULL;
	LCD_GoToLine(0);
	strArr[8] = NULL;
	LCD_DisplayString(strArr);
	LCD_GoToLine(1);
	LCD_DisplayString(passwordArr);
	while(1);
	return 0;
}

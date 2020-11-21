///////////////////////////////////////////////////////////////
// University of Tehran - Summer 2020
// Microcontrollers Lab - Lab 4
// Y. Parhizkar, R. Ghoroghchian, M. Haghifam
// 
// Part 3/3
// Description: Sends sensor values to the server every 10 seconds for 10 times
// 	       and receives and displays the server's answer for each transmission.
// 	       The server sends '#' if the transmission is successful and '!' otherwise.
///////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adc.h"
#include "uart.h"
#include "lcd.h"
#include "timer.h"


int flag = 0;
int voltageSensor(){
//voltage: 
	int voltage;
	voltage = ADC_GetAdcValue(0);
	return( (voltage *3300));
}

int lightSensor(){
//light: 
	int light;
	light = ADC_GetAdcValue(1);
	return (10000 - (light * 9990 / 4095 ));

}

int tempSensor(){
//Temp: 
	int temp;
	temp = ADC_GetAdcValue(2);
	return ( (temp * 330 / 4095));

}


int humSensor(){
//humid: 
	int hum;

	hum = ADC_GetAdcValue(3);
	return( (3300 - (hum * 3300 / 4095)) );
}

void intrFunc() {
	char r_char[2]=" ";
	flag+=1;
	if(flag<=10){
		char s_string[30]="8-3085073-";
		int v;
		int l;
		int t;
		int h;
		v=voltageSensor();
		l=lightSensor();
		t=tempSensor();
		h=humSensor();
		
		sprintf(s_string,"8-3085073-%d-%d-%d-%d-%d\n",flag,v,l,t,h);
		UART2_TxString(s_string);
		UART2_RxString(r_char);
		LCD_Clear();
		LCD_GoToLine(0);
		LCD_DisplayString(r_char);
		LCD_GoToLine(1);
		LCD_DisplayString(s_string);
		
	}
	else
		TIMER_Stop(TIMER_1);
}

int main(void) {
	void (*fp) (void) = intrFunc;
	SystemInit();
	LCD_SetUp(P0_0, P0_1, P0_2, P_NC, P_NC, P_NC, P_NC, P0_4,P0_5,P0_6, P0_7);
	LCD_Init(2, 16);
	LCD_Clear();
	ADC_Init();
	TIMER_Init(TIMER_1, 10000000);
	TIMER_AttachInterrupt(TIMER_1, fp);
	TIMER_Start(TIMER_1);
	UART2_Init(9600);
	while(1);
	return 0;
}






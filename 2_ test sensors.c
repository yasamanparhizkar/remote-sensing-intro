///////////////////////////////////////////////////////////////
// University of Tehran - Summer 2020
// Microcontrollers Lab - Lab 4
// Y. Parhizkar, R. Ghoroghchian, M. Haghifam
// 
// Part 2/3
// Description: Displays sensor values on the LCD without sending them to the server
//				to check if the sensors work correctly.
///////////////////////////////////////////////////////////////

#include "adc.h"
#include "uart.h"
#include "lcd.h"
#include "timer.h"


int flag = 0;
void voltageSensor(){
//voltage: 
	int voltage;
	

	LCD_Clear();
	LCD_GoToLine(0);

	voltage = ADC_GetAdcValue(0);
	LCD_DisplayString("VOLT   ");
	LCD_DisplayString("ADC:");
	LCD_DisplayNumber(10, voltage, 4);
	LCD_GoToLine(1);
	LCD_DisplayString(" = ");
	LCD_DisplayNumber(10, (voltage *3300) / 4095, 4);
	LCD_DisplayString("   mv");
}

void lightSensor(){
//light: 
	int light;
	

	LCD_Clear();
	LCD_GoToLine(0);

	light = ADC_GetAdcValue(1);
	LCD_DisplayString("LIGHT   ");
	LCD_DisplayString("ADC:");
	LCD_DisplayNumber(10, light, 4);
	LCD_GoToLine(1);
	LCD_DisplayString(" = ");
	LCD_DisplayNumber(10, 10000 - (light * 9990 / 4095 + 10), 4);
	LCD_DisplayString("   lx");
}

void tempSensor(){
//Temp: 
	int temp;
	

	LCD_Clear();
	LCD_GoToLine(0);

	temp = ADC_GetAdcValue(2);
	LCD_DisplayString("TEMP   ");
	LCD_DisplayString("ADC:");
	LCD_DisplayNumber(10, temp, 4);
	LCD_GoToLine(1);
	LCD_DisplayString(" = ");
	LCD_DisplayNumber(10, (temp * 330 / 4095) - 50, 4);
	LCD_DisplayString("   'C");
}


void humSensor(){
//humid: 
	int hum;
	

	LCD_Clear();
	LCD_GoToLine(0);

	hum = ADC_GetAdcValue(3);
	LCD_DisplayString("HUM   ");
	LCD_DisplayString("ADC:");
	LCD_DisplayNumber(10, hum, 4);
	LCD_GoToLine(1);
	LCD_DisplayString(" = ");
	LCD_DisplayNumber(10, (3300 - (hum * 3300 / 4095)) , 4);
	LCD_DisplayString("   %");
}

void intrFunc() {
	if(flag == 0) {
		voltageSensor();
		flag = 1;
	}
	else if( flag == 1) {
		lightSensor();
		flag = 2;
	}
	else if( flag == 2) {
		tempSensor();
		flag = 3;
	}
	else if(flag == 3) {
		humSensor();
		flag = 0;
	}
}

int main(void) {

	void (*fp) (void) = intrFunc;
	SystemInit();
	LCD_SetUp(P0_0, P0_1, P0_2, P_NC, P_NC, P_NC, P_NC, P0_4,P0_5,P0_6, P0_7);
	LCD_Init(2, 16);
	ADC_Init();
	TIMER_Init(TIMER_1, 65000);

	TIMER_AttachInterrupt(TIMER_1, fp);
	TIMER_Start(TIMER_1);
	while(1);
	return 0;
}

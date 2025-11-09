#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Mode1.h"
#include "Mode2.h"
#include "Key.h"
#include "Motor.h"
#include "Encoder.h"
#include "Timer.h"
#include "Serial.h"
#include <stdio.h>
uint8_t S=1;
int16_t Speed1;
int16_t Speed2;
int main(void)
{
	Key_Init();
	OLED_Init();
	Motor_Init();
	Timer1_Init();
	Serial_Init();
	Encoder1_Init();	
	Encoder2_Init();
	while (1)
	{
		if(S==1)
		{
			OLED_Clear();
			OLED_ShowString(1,6,"Mode1");
			OLED_ShowString(2,1,"Speed:");
			S=Mode1();
		}
		else if (S==2)
		{
			OLED_Clear();
			OLED_ShowString(1,6,"Mode2");
			S=Mode2();
		}
		
	}
}



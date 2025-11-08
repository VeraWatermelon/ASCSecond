#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Mode1.h"
#include "Mode2.h"
#include "Key.h"

uint8_t S=1;
int main(void)
{
	Key_Init();
	OLED_Init();
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

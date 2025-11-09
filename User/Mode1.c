#include "stm32f10x.h"                  // Device header
#include "Serial.h"
#include "OLED.h"
#include <stdio.h>
#include "Key.h"
#include "Motor.h"
#include "Encoder.h"
#include <math.h>
uint8_t KeyNum,Count;
extern int16_t Speed1;
extern int16_t Speed2;
float TargetA, ActualA, ActualA1, OutA,Difout;
float KpA, KiA, KdA;
float ErrorA0, ErrorA1, ErrorA2;
uint8_t Mode1(void)
{
	KpA=0.9;
	KiA=0.26;
	KdA=0;
	while(1)
	{
		static int16_t v;
		static int16_t i;	
		if (Serial_RxFlag == 1)	
		{
			v=0;
			i=0;
			if(Serial_RxPacket[0]=='-')i=1;
			while(Serial_RxPacket[i]!='\0')
			{
				v*=10;
				v+=Serial_RxPacket[i]-'0';
				i++;
			}
			
			if(Serial_RxPacket[0]=='-')
			{
				v=-v;
			}
			OLED_ShowSignedNum(4,1,OutA,5);
			TargetA=v;
			//OLED_ShowString(3,1,Serial_RxPacket);
			Serial_RxFlag = 0;
		}
		
		KeyNum=Key_GetNum();
		if(KeyNum==1)
		{
			return 2;
		}
	}	
}

void TIM1_UP_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
	{
			
			ActualA = Encoder1_Get();
			
			ErrorA2 = ErrorA1;
			ErrorA1 = ErrorA0;
			ErrorA0 = TargetA - ActualA;
			
			OutA += KpA * (ErrorA0 - ErrorA1) + KiA * ErrorA0
					+ KdA * (ErrorA0 - 2 * ErrorA1 + ErrorA2);
			
			if (OutA > 100) {OutA = 100;}
			if (OutA < -100) {OutA = -100;}
			Motor_SetSpeed(OutA);
		
		//printf("%d,%d\n",6,6);		//串口发送printf打印的格式化字符串
		//printf("%d,%d\n",5,5);
		printf("%f,%f\n",ActualA,TargetA);	
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	
	}

}


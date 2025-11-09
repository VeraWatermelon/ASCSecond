#include "stm32f10x.h"                  // Device header
#include "Serial.h"
#include "OLED.h"
#include <stdio.h>
#include "Key.h"
#include "Motor.h"
#include "Encoder.h"
#include <math.h>
extern uint8_t S;
uint8_t KeyNum,Count;
extern int16_t Speed1;
extern int16_t Speed2;
float TargetA, ActualA,OutA,ActualB1,ActualB2,TargetB,OutB;
float KpA,KiA,KdA,KpB,KiB,KdB;
float ErrorA0, ErrorA1, ErrorA2,ErrorB0, ErrorB1, ErrorB2;
uint8_t Mode1(void)
{
	KpA=0.9;
	KiA=0.26;
	KdA=0;
	KpB=0;
	KiB=0;
	KdB=0;
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
			if(S==1)
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
				printf("%f,%f\n",ActualA,TargetA);	
				
			}
			else if(S==2)
			{
				TargetB += Encoder2_Get();
				ActualB1 += Encoder1_Get();
				ErrorB2 = ErrorB1;
				ErrorB1 = ErrorB0;
				ErrorB0 = TargetB - ActualB1;
				
				OutB += KpB * (ErrorB0 - ErrorB1) + KiB * ErrorB0
						+ KdB * (ErrorB0 - 2 * ErrorB1 + ErrorB2);
				
				if (OutB > 100) {OutB = 100;}
				if (OutB < -100) {OutB = -100;}
				Motor_SetSpeed(OutB);
				printf("%f,%f\n",ActualB1,TargetB);	
			
			}
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	
	}

}


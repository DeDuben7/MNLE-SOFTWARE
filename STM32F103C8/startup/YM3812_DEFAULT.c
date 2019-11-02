#include "includes.h"

void YM_RESET()
{
	int i;

	for(i=1; i< 0xF6; i++)
	{
		YM_WRITE_Databus(1,0,i);
		YM_WRITE_Databus(1,1,0);
	}

}

uint8_t op1[9] = {0,1,2,8,9,10,16,17,18};
uint8_t op2[9] = {3,4,5,11,12,13,19,20,21};

void YM_SET_Def()
{
	int i;

	for(i=0;i<9;i++)
	{

		YM_WRITE_Databus(1,0,0x20 + op1[i]);
		YM_WRITE_Databus(1,1,0x01);
		YM_WRITE_Databus(1,0,0x40 + op1[i]);
		YM_WRITE_Databus(1,1,0x10);
		YM_WRITE_Databus(1,0,0x60 + op1[i]);
		YM_WRITE_Databus(1,1,0xF0);
		YM_WRITE_Databus(1,0,0x80 + op1[i]);
		YM_WRITE_Databus(1,1,0x77);

		YM_WRITE_Databus(1,0,0x20 + op2[i]);
		YM_WRITE_Databus(1,1,0x01);
		YM_WRITE_Databus(1,0,0x40 + op2[i]);
		YM_WRITE_Databus(1,1,0x01);
		YM_WRITE_Databus(1,0,0x60 + op2[i]);
		YM_WRITE_Databus(1,1,0xF0);
		YM_WRITE_Databus(1,0,0x80 + op2[i]);
		YM_WRITE_Databus(1,1,0x77);

	}
}

void YM_SET_Def_OFF()
{
//	HAL_UART_Transmit_IT(&huart2,"ben in functie",15);
	YM_WRITE_Databus(1,0,0xB0);
	YM_WRITE_Databus(1,1,0x11);
}

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

void YM_SET_Def()
{
	YM_WRITE_Databus(1,0,0x20);
	YM_WRITE_Databus(1,1,0x01);
	YM_WRITE_Databus(1,0,0x40);
	YM_WRITE_Databus(1,1,0x00);
	YM_WRITE_Databus(1,0,0x60);
	YM_WRITE_Databus(1,1,0xF0);
	YM_WRITE_Databus(1,0,0x80);
	YM_WRITE_Databus(1,1,0x77);
	//YM_WRITE_Databus(1,0,0xA0);
	//YM_WRITE_Databus(1,1,0x98);

	YM_WRITE_Databus(1,0,0x23);
	YM_WRITE_Databus(1,1,0x01);
	YM_WRITE_Databus(1,0,0x43);
	YM_WRITE_Databus(1,1,0x00);
	YM_WRITE_Databus(1,0,0x63);
	YM_WRITE_Databus(1,1,0xF0);
	YM_WRITE_Databus(1,0,0x83);
	YM_WRITE_Databus(1,1,0x77);
	//YM_WRITE_Databus(1,0,0xB0);
	//YM_WRITE_Databus(1,1,0x31);

}

void YM_SET_Def_OFF()
{
//	HAL_UART_Transmit_IT(&huart2,"ben in functie",15);
	YM_WRITE_Databus(1,0,0xB0);
	YM_WRITE_Databus(1,1,0x11);
}


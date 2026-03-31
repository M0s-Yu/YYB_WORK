#include <REGX52.H>
#include "Key.h"
#include "AT24C02.h"
#include "UART.h"
void Delay(unsigned int xms);
unsigned char KeyNum;


void main()
{	int Data;
	UART_Init();
	//这里是开机后发送数据，不知道什么原因关机时会发送00数据。
	Data=AT24C02_ReadByte(0);			//将EEPROM数据低八位赋值给Data
	Data|=AT24C02_ReadByte(1)<<8;		//将EEPROM数据高八位赋值给Data
	UART_SendByte(Data);			//串口发送数据
while(1){
	KeyNum=Key();
	//这里是开机后实现按键3或4按下后发送信息至电脑。
	//至于为什么不用按键1或2，可能因为引脚冲突，按下1后会先发送00数据，再发送原数据。
	//而按下按键2后会发送一遍原数据，不知什么原因触发串口中断，导致数据重置。
	if(KeyNum==3 | KeyNum==4)
	{             
		Data=AT24C02_ReadByte(0);
		Data|=AT24C02_ReadByte(1)<<8;
		UART_SendByte(Data);             //同上

	}
	
		}}	



void UART_Routine() interrupt 4 
{
    if(RI==1){
	AT24C02_WriteByte(0,SBUF%256);
	Delay(5);
	AT24C02_WriteByte(1,SBUF/256);
	Delay(5);
	RI=0;
	}
}


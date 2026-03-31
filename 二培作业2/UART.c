#include <REGX52.H>
void Delay(unsigned int xms);

void UART_Init(){
	SCON=0x50;
	PCON |=0x80;
	TMOD &= 0x0F;
	TMOD |= 0x20;
	TL1 = 0xF4;			//设置定时初始值
	TH1 = 0xF4;			//设置定时重载值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
	EA=1;
	ES=1;
}


void UART_SendByte(unsigned char Byte){
	SBUF=Byte;
	while(TI==0); 
	TI=0;

}

#include <REGX52.H>
#include <INTRINS.H>
void Delayx00us(unsigned int x00us)	//@11.0592MHz
{
	unsigned char data i;
	while(x00us){
		_nop_();
		i = 43;
		while (--i);
		x00us--;}
}


sbit Buzzer=P2^5;

void Buzzer_Time(unsigned int ms){
	unsigned char i;
	for (i=0;i<ms*2;i++)
		{Buzzer=!Buzzer;Delayx00us(5);}
	
}

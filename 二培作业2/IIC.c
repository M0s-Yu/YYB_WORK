#include <REGX52.H>

sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;


void I2C_Start()//I2C开始
{
	I2C_SDA=1;
	I2C_SCL=1;
	I2C_SDA=0;
	I2C_SCL=0;
	
}
void I2C_Stop()//I2C停止
{
	I2C_SDA=0;
	I2C_SCL=1;
	I2C_SDA=1;
	
}

void I2C_SendByte(unsigned char Byte)//I2C发送一个字节
{	unsigned char i;
	for(i=0;i<8;i++)
	{	I2C_SDA=Byte&(0x80>>i);
		I2C_SCL=1;
		I2C_SCL=0;
	}
}

unsigned char I2C_ReceiveByte()//I2C接收一个字节
{	unsigned char Byte=0x00;
	unsigned char i;
	I2C_SDA=1;
	for(i=0;i<8;i++)
	{	
		I2C_SCL=1;	
		if (I2C_SDA){Byte|=(0x80>>i);}
		I2C_SCL=0;
	}
	

	return Byte;
}
 
void I2C_SendAck(unsigned char AckBit)//I2C发送应答    AckBit为应答位，0为应答，1为非应答 
{
	I2C_SDA=AckBit;
	I2C_SCL=1;
	I2C_SCL=0;

}
unsigned  char I2C_ReceiveAck()//I2C接收应答    AckBit为应答位，0为应答，1为非应答 
{	
	unsigned char AckBit;
	I2C_SDA=1;
	I2C_SCL=1;
	AckBit=I2C_SDA;
	I2C_SCL=0;
	return AckBit;
}
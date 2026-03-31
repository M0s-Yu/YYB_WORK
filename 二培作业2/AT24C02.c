#include <REGX52.H>
#include "IIC.h"
#define AT24C02_ADDRESS  0xA0
void AT24C02_WriteByte(unsigned char WordAddress,Data)//AT24C02写入一个字节   WordAddress 要写入字节的地址   Data 要写入的数据
{
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_SendByte(Data);
	I2C_ReceiveAck();
	I2C_Stop();

}

unsigned char AT24C02_ReadByte(unsigned char WordAddress)//AT24C02读取一个字节      WordAddress 要读出字节的地址
{
	unsigned char Data;
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS| 0x01);
	I2C_ReceiveAck();
	Data=I2C_ReceiveByte();
	I2C_SendAck(1);
	I2C_Stop();
	return Data;
}












#ifndef __IIC_H__
#define __IIC_H__

void I2C_Start();
void I2C_Stop();
void I2C_SendByte(unsigned char Byte);
unsigned char I2C_ReceiveByte();
void I2C_SendAck(unsigned char AckBit);
unsigned  char I2C_ReceiveAck();

#endif
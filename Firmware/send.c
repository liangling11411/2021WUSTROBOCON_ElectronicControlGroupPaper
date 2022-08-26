#include <REGX52.H>
#include "I2C.h"

#define ADDRESS   0x40

/**
  * @brief   发送一个字节 
	* @param 	Data 要写入的数据
  * @retval 无
  */
void SendByte(unsigned char Data)
	
{
	I2C_Start();
	I2C_SendByte(ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(Data);
	I2C_ReceiveAck();
	I2C_Stop();
}

/**
  * @brief  发送字符串
  * @param 	p 字符串首地址
  * @retval 无
  */
void SendString(unsigned char *p)
{
	while(*p)
	{
		SendByte(*p);
		p++;
	}

}
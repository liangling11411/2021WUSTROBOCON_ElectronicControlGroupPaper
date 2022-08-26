#include <REGX52.H>


sbit I2C_SCL=P1^1;
sbit I2C_SDA=P1^0;

/**
  * @brief  I2C开始
  * @param 无
  * @retval 无
  */
void I2C_Start(void)
{
	I2C_SDA=1;	//确保为1
	I2C_SCL=1;	//确保为1
	I2C_SDA=0;	//这就是为了满足时序图 拉低
	I2C_SCL=0;	//特意为了置0，为了好拼接
}


/**
  * @brief  I2C停止
  * @param 	无
  * @retval 无
  */
void I2C_Stop(void)
{
	I2C_SDA=0;
	I2C_SCL=1;
	I2C_SDA=1;

}


/**
  * @brief  I2C发送一个字节
  * @param 	Byte 要发送的字节
  * @retval 无
  */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		I2C_SDA=Byte&(0x80>>i);
		I2C_SCL=1;
		I2C_SCL=0;

	}
}	


/**
  * @brief  I2C接收一个字节
  * @param 无
  * @retval 接收到的一个字节数据
  */
unsigned char I2C_ReceiveByte(void)
{
	unsigned char i,Byte=0x00;
	I2C_SDA=1;//释放总线
	
	for(i=0;i<8;i++)
	{
		I2C_SCL=1;
		if(I2C_SDA){Byte|=(0x80>>i);}//如果SDA为1，置1；为0，默认不处理
		I2C_SCL=0;
	}
	
	return Byte;
}


/**
  * @brief  I2C发送应答
	* @param AckBit应答位，0为应答，1为非应答
  * @retval 无
  */
void I2C_SendAck(unsigned char AckBit)//也可定义为bit类型，一个字节
{
	I2C_SDA=AckBit;
	I2C_SCL=1;
	I2C_SCL=0;
}

/**
  * @brief  I2C接收应答位
  * @param 无
  * @retval 接受到的应答位，0为应答，1为非应答
  */
unsigned char I2C_ReceiveAck(void)
{
	unsigned char  AckBit;
	I2C_SDA=1;							//主机释放SDA
	I2C_SCL=1;
	AckBit=I2C_SDA;					//从机SDA
	I2C_SCL=0;
	return AckBit;
}

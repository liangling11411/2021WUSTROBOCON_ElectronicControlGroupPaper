#include<IIC.h>
#include<reg52.h>
sbit IIC_SCL=P1^0;//SCL时钟线
sbit IIC_SDA=P1^1;//SDA数据线

//延时函数，ten_us=1时，大约延时10us
void Delay_10us(unsigned int ten_us)
{
    while(ten_us--);
}

//产生IIC起始信号
void iic_start(void)
{
    IIC_SDA=1; 
    Delay_10us(1);
    IIC_SCL=1;
    Delay_10us(1);
    IIC_SDA=0; 
    Delay_10us(1);
    IIC_SCL=0; 
    Delay_10us(1);
}
// 函数功能: 产生IIC停止信号   
void iic_stop(void)
{
    IIC_SDA=0; 
     Delay_10us(1);
    IIC_SCL=1;
    Delay_10us(1);
    IIC_SDA=1; 
     Delay_10us(1);
}
//函数功能: 产生ACK应答  
void iic_ack(void)
{
    IIC_SCL=0;
    IIC_SDA=0; //SDA为低电平
    	Delay_10us(1);
    IIC_SCL=1;
    Delay_10us(1);
    IIC_SCL=0;
}
// 函数功能: 产生NACK非应答  
void iic_nack(void)
{
    IIC_SCL=0;
    IIC_SDA=1; //SDA为高电平
     Delay_10us(1);
    IIC_SCL=1;
    Delay_10us(1);
    IIC_SCL=0;
}
// 函数功能: 等待应答信号到来   
u8 iic_wait_ack(void)
{
    u8 time_temp=0;

    IIC_SCL=1;
    Delay_10us(1);
    while(IIC_SDA) 
    {
        time_temp++;
        if(time_temp>100) 
        {
            iic_stop();
            return 1;
        }
    }
    IIC_SCL=0;
    return 0;
}
//函数功能: IIC发送一个字节 
// 输出: 1，接收应答失败，0，接收应答成功
void iic_write_byte(u8 dat)
{
    u8 i=0;

    IIC_SCL=0;
    for(i=0;i<8;i++) 
    {
        if((dat&0x80)>0)
            IIC_SDA=1;
        else
            IIC_SDA=0;
        dat<<=1;
        delay_10us(1);
        IIC_SCL=1;
        delay_10us(1);
        IIC_SCL=0;
        delay_10us(1);
    }
}
//函数功能: IIC读一个字节 
//输    入: ack=1时，发送ACK，ack=0，发送nACK 
//输    出: 应答或非应答
u8 iic_read_byte(u8 ack)
{
    unsigned char i=0,receive=0;

    for(i=0;i<8;i++ )
    {
        IIC_SCL=0;
        Delay_10us(1);
        IIC_SCL=1;
        receive<<=1;
        if(IIC_SDA)receive++;
        Delay_10us(1);
    }
    if (!ack)
        iic_nack();
    else
        iic_ack();

    return receive;
}




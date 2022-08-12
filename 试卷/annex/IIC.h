#ifndef __IIC_H_
#define __IIC_H_
typedef u8 unsigned char

void Delay_10us(unsigned int ten_us);
void iic_start(void);
void iic_stop(void);
void iic_ack(void);
void iic_nack(void);
u8 iic_wait_ack(void);
void iic_write_byte(u8 dat);
u8 iic_read_byte(u8 ack);


#endif
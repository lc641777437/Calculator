#include "includes.h" 		 //1602.c
sbit RS = P2^4;				 //����˿� ��������ѡ�� H/L 	 
sbit RW = P2^5; 			//��д H/L 
sbit EN = P2^6; 			//ʹ�� 
extern unsigned char sk; 
#define RS_CLR RS=0 
#define RS_SET RS=1 
#define RW_CLR RW=0 
#define RW_SET RW=1 
#define EN_CLR EN=0 
#define EN_SET EN=1 
/******************************************************************/ 
						/* д������� */ 
/******************************************************************/ 
void LCD_write_com(unsigned char com) { 
	RS_CLR; 
	RW_CLR; 
	EN_SET; 
	P0 = com; 
	delay_us(5); 
	EN_CLR; 
} 
/******************************************************************/
						/* д�����ݺ��� */ 
/******************************************************************/ 
void LCD_write_Data(unsigned char Data) { 
	RS_SET; 
	RW_CLR; 
	EN_SET; 
	P0 = Data; 
	delay_us(5); 
	EN_CLR; 
}
/******************************************************************/ 
						/* �������� */ 
/******************************************************************/ 
void LCD_clear(void) { 
	LCD_write_com(0x01); 
	delay_ms(5);
	if(sk == 1) { 
		LCD_write_char(0,1,0xde); 
		LCD_write_com(0x80); 
	} 
	else { 
		LCD_write_char(0,1,0x20); 
		LCD_write_com(0x80); 
	} 
} 
/******************************************************************/ 
						/* д���ַ������� */ 
/******************************************************************/ 
void LCD_write_str(unsigned char x,unsigned char y,unsigned char *s) { 
	unsigned char i,j; 
	if (y == 0) { LCD_write_com(0x80 + x); 
	} 
	else { 
		LCD_write_com(0xC0 + x); 
	} 
	for(i=4;i>0;i--) { 
		if(s[14] == '0' || s[14] == '.') { 
			for(j=14;j>1;j--) { 
				s[j] = s[j-1]; 
			} 
		} 
		else break; 
	} 
	while (*s) { 
	LCD_write_Data(*s); 
	s++; 
	} 
} 
/******************************************************************/ 
						/* д���ֽں��� */
/******************************************************************/ 
void LCD_write_char(unsigned char x,unsigned char y,unsigned char Data) { 
	if (y == 0) { 
		LCD_write_com(0x80 + x); 
	} 
	else { 
		LCD_write_com(0xC0 + x); 
		} 
	LCD_write_Data(Data); 
} 
/******************************************************************/ 
						/* ��ʼ������ */ 
/******************************************************************/ 
void LCD_init(void) { 
	LCD_write_com(0x38); /*��ʾģʽ����*/ 
	delay_ms(5); 
	LCD_write_com(0x38); 
	delay_ms(5); 
	LCD_write_com(0x38); 
	delay_ms(5); 
	LCD_write_com(0x38); 
	LCD_write_com(0x08); /*��ʾ�ر�*/ 
	LCD_write_com(0x01); /*��ʾ����*/ 
	LCD_write_com(0x06); /*��ʾ����ƶ�����*/ 
	delay_ms(5); 
	LCD_write_com(0x0C); /*��ʾ�����������*/ 
}

#include "includes.h" 		 //1602.c
sbit RS = P2^4;				 //定义端口 数据命令选择 H/L 	 
sbit RW = P2^5; 			//读写 H/L 
sbit EN = P2^6; 			//使能 
extern unsigned char sk; 
#define RS_CLR RS=0 
#define RS_SET RS=1 
#define RW_CLR RW=0 
#define RW_SET RW=1 
#define EN_CLR EN=0 
#define EN_SET EN=1 
/******************************************************************/ 
						/* 写入命令函数 */ 
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
						/* 写入数据函数 */ 
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
						/* 清屏函数 */ 
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
						/* 写入字符串函数 */ 
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
						/* 写入字节函数 */
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
						/* 初始化函数 */ 
/******************************************************************/ 
void LCD_init(void) { 
	LCD_write_com(0x38); /*显示模式设置*/ 
	delay_ms(5); 
	LCD_write_com(0x38); 
	delay_ms(5); 
	LCD_write_com(0x38); 
	delay_ms(5); 
	LCD_write_com(0x38); 
	LCD_write_com(0x08); /*显示关闭*/ 
	LCD_write_com(0x01); /*显示清屏*/ 
	LCD_write_com(0x06); /*显示光标移动设置*/ 
	delay_ms(5); 
	LCD_write_com(0x0C); /*显示开及光标设置*/ 
}

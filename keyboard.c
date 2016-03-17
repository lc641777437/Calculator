#include "includes.h" 	//keyboard.c
extern unsigned char sk; 
sbit key0=P2^0; 
sbit key1=P2^1; 
sbit key2=P2^2; 
sbit key3=P2^3;
sbit speak=P2^7; 
unsigned char KeyProcess(void) { 
	unsigned char key; 
	unsigned char keyvalue = 16; 
	key=keyscan(); 			//调用键盘扫描 
	switch(key) { 
		case 0xee:keyvalue = 0;break; //0 按下相应的键显示相对应的码值 
		case 0xde:keyvalue = 1;break; //1 按下相应的键显示相对应的码值 
		case 0xbe:keyvalue = 2;break; //2 
		case 0x7e:keyvalue = 3;break; //3 
		case 0xed:keyvalue = 5;break; //4 
		case 0xdd:keyvalue = 6;break; //5 
		case 0xbd:keyvalue = 7;break; //6 
		case 0x7d:keyvalue = 8;break; //7 
		case 0xeb:keyvalue = 10;break; //8 
		case 0xdb:keyvalue = 11;break; //9 
		case 0xbb:keyvalue = 12;break; //10 
		case 0x7b:keyvalue = 13;break; //11 
		case 0xe7:keyvalue = 15;break; //12 
		case 0xd7:keyvalue = 16;break; //13 
		case 0xb7:keyvalue = 17;break; //14 
		case 0x77:keyvalue = 18;break; //15 
		case 0x00:keyvalue = 4;break; //key0 
		case 0x01:keyvalue = 9;break; //key1 
		case 0x02:keyvalue = 14;break; //key2 
		case 0x03:keyvalue = 19;break; //key3 
		case 0xff:keyvalue = 20;break; 
		default: keyvalue = 20;break; 
	} 
	return keyvalue; 
} 
unsigned char keyscan(void){		//键盘扫描函数，使用行列反转扫描法 
	unsigned char cord_h,cord_l; 	//行列值中间变量 
	P3=0x0f; 	//行线输出全为 1,列线输出全为 0 
	cord_h=P3&0x0f; 	//读入行线值 
	if(cord_h!=0x0f) 	//先检测有无按键按下 
	{ 
		delay_us(100); 	//去抖 
		if(cord_h!=0x0f) { 
			cord_h=P3&0x0f; 	//读入行线值
			P3=cord_h|0xf0; 	//输出当前行线值
			cord_l=P3&0xf0; 	//读入列线值
			while(P3 != 0x0f) { 
				P3 = 0x0f; 
				speak = !sk; 
			} 
			speak=1; 
			delay_ms(20); 
			return(cord_h+cord_l); 	//键盘最后组合码值
		} 
	} 
	if(key0 == 0) { 
		delay_us(100); 
		if(key0==0) { 
			while(key0 == 0) { 
				speak = !sk; 
			} speak = 1; 
			delay_ms(3); 
			return 0x00; 
		} 
	} 
	if(key1 == 0) { 
		delay_us(100); 
		if(key1==0) { 
			while(key1 == 0) { 
				speak = !sk; 
			} 
			speak = 1; 
			delay_ms(3); 
			return 0x01; 
		} 
	} 
	if(key2 == 0) { 
		delay_us(100); 
		if(key2==0)  { 
			while(key2 == 0) { 
				speak = !sk; 
			} 
			speak = 1; 
			delay_ms(3); 
			return 0x02; 
		} 
	} 
	if(key3 == 0) { 
		delay_us(100); 
		if(key3==0) { 
			while(key3 == 0) { 
				speak = !sk; 
			} 
			speak = 1; 
			delay_ms(3); 
			return 0x03; 
		} 
	} 
	return(0xff); 		//返回该值
}
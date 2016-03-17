#include "includes.h" //main.c
unsigned char code uckey[20] = {
	0x37,0x38,0x39,0x28,0x29, 
	0x34,0x35,0x36,0x2b,0x2d, 
	0x31,0x32,0x33,0x2a,0x2f,
	0x30,0x2e,0x64,0xde,0x3d
}; 
char idata TR[20]; 
double idata ND[20]; 
void dispdouble(double value); 
double AccProcess(char *s); 
char getonechar(void); 
unsigned char keycount=0; 
unsigned char sk=0; void ErrorProcess(void); 
void main(void) { 
	double value; 
	unsigned char keyvalue; 
	unsigned char ipos = 0; 
	char s[32]; 
	P2 = 0xff; 
	delay_ms(100); 
	LCD_init(); 
	LCD_clear(); 
	while(1) { 
		while(1) { 
			keyvalue = getonechar(); 
			if(uckey[keyvalue] == '=') { 
				s[ipos++] = '#'; 
				break; 
			} 
			else { 
				if(uckey[keyvalue] == 'd') { 
					s[--ipos] = '0'; 
				} 
				else if(uckey[keyvalue] == 0xde) { 
					sk = !sk; 
					keycount--; 
					if(sk == 1) { 
						LCD_write_char(0,1,0xde);
						LCD_write_com(0x80 + keycount); 
					} 
					else { 
						LCD_write_char(0,1,0x20); 
						LCD_write_com(0x80 + keycount); 
					} 
				} 
				else { 
					s[ipos++] = uckey[keyvalue]; 
				} 		
			} 
		} 
		while(keycount >= 16) { 
			LCD_write_com(0x1c); 
			delay_ms(5); 
			keycount--; 
		} 
		s[ipos] = '\0'; 
		ipos = 0; 
		keycount = 0; 
		value = AccProcess(s); 
		dispdouble(value); 
	} 
} 
void dispdouble(double value) { 
	char text[15]; 
	sprintf(text,"%15.3f",value); 
	LCD_write_str(1,1,text); 
} 
double AccProcess(char *s) { 
	OPTR str; //符号栈 
	OPND snd; //数据栈 
	char flagnum = 0; 
	char flagdp = 0; 
	char i=0; 
	char c,theta; 
	double num1,num2,num; 
	Init_OPND(&snd,&ND[0]);
	Init_OPTR(&str,&TR[0]); 
	PUSH_OPTR(&str,'#'); 
	flagnum = 0; 
	c = *(s++); 
	while(c!='#' || (*(str.rtop-1) != '#')) { 
		if(c>='0' && c<= '9') { 
			c = c - 0x30; 
			if(flagdp ==0) { 
				if(flagnum ==0) { 
					PUSH_OPND(&snd,(double)c); 
					flagnum++; 
				} 
				else { 
					Pushnum(&snd,c); 
					flagnum++; 
				} 
			} 
			if(flagdp == 1) { 
				Pushdp(&snd,flagnum,c); 
				flagnum++; 
			} 
			c=*(s++); 
		} 
		else if(c=='.') { 
			flagdp = 1; 
			if(flagnum ==0 ) { 
				PUSH_OPND(&snd,0x00); 
			} 
			flagnum = 1; 
			c=*(s++); 
		} 
		else 
			switch(Precede(*(str.rtop-1),c)) { 
				case 0: if(flagnum == 0 && c != '(') 
						ErrorProcess(); 
						PUSH_OPTR(&str,c);
						c=*(s++);
						flagnum = 0; 
						flagdp = 0; 
						break;
				case 1:	POP_OPTR(&str);
						c=*(s++); 
						break; 
				case 2: theta = POP_OPTR(&str); 
						num2 = POP_OPND(&snd); 
						num1 = POP_OPND(&snd); 
						num = (double)(Operate(num1,theta,num2)); 
						PUSH_OPND(&snd,num);
						break;
				case 3: ErrorProcess(); 
						break;
				default:break;
			} 
		}
	
	while(*s) { 
		*s = '\0'; 
		s++; 
	} 
	return (*(snd.dtop - 1)); 
} 
char getonechar() { 
	unsigned char key1 = 20; 
	keycount++; 
	while(key1 == 20) { 
		key1 = KeyProcess(); 
		if(keycount==1 && key1==17) { 
			key1=20; 
		} 
	} 
	if(keycount == 1) { 
		LCD_clear(); 
	} 
	if(keycount >= 16) { 
		LCD_write_com(0x18); //内容左移 
	} 
	if(keycount == 33) { 
		ErrorProcess(); 
	} 
	if(key1 == 17) { 
		LCD_write_char(keycount-2,0,0x20); 
		delay_ms(2); 
		LCD_write_com(0x80+keycount-2); 
		keycount -= 2; 
	} 
	else if(key1 == 18) {
		;
	} 
	else { 
		LCD_write_Data(uckey[key1]); 
	} 
	return key1; 
} 
void ErrorProcess(void) { 
	LCD_clear(); 
	LCD_write_str(4,1,"ERROR!"); 
	LCD_write_char(10,1,'!'); 
	while(KeyProcess() == 20); 
	ISP_CONTR = 0x20; 
} //软件复位 
#include "delay.h"
void delay_us(unsigned int cnt) { 
	while(--cnt);
} 
void delay_ms(unsigned int cnt) { 
	unsigned int i, j; 
	for (i = 0; i < cnt; i++) { 
		for (j = 0;j < 65; j++) { 
			delay_us(1); 
		} 
	} 
}
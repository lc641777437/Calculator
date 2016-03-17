#include "includes.h" 		//¶ÑÕ» stack.c
unsigned char code yxj[7][7] = {  	// + - * / ( ) #
	2,2,0,0,0,2,2, // + 
	2,2,0,0,0,2,2, // -
	2,2,2,2,0,2,2, // * 
	2,2,2,2,0,2,2, // / 
	0,0,0,0,0,1,3, // ( 
	2,2,2,2,3,2,2, // ) 
	0,0,0,0,0,3,1, // # 
}; 
void Init_OPTR( OPTR *s,char *TR1 ) { 
	s->rbase = TR1; 
	s->rtop = s->rbase; 
} 
void PUSH_OPTR(OPTR *s,char elem) {
	* (s->rtop) = elem; 
	s->rtop ++; 
} 
char POP_OPTR(OPTR *s) { 
	char temp; 
	s->rtop--; 
	temp= *(s->rtop); 
	return temp; 
} 
void Init_OPND(OPND *s,double *ND1) { 
	s->dbase = ND1; 
	s->dtop = s->dbase; 
} 
void PUSH_OPND(OPND *s,double elem) { 
	* (s->dtop) = elem;
	s->dtop ++; 
} 
double POP_OPND(OPND *s) { 
	double temp; 
	s->dtop--; 
	temp= *(s->dtop); 
	return temp; 
} 
char Precede(char a,char b) { 
	char i,j; 
	switch(a) { 
		case '+':i=0;break; 
		case '-':i=1;break; 
		case '*':i=2;break; 
		case '/':i=3;break; 
		case '(':i=4;break; 
		case ')':i=5;break; 
		case '#':i=6;break; 
		default :i=0;break; 
	} 
	switch(b) { 
		case '+':j=0;break; 
		case '-':j=1;break; 
		case '*':j=2;break; 
		case '/':j=3;break; 
		case '(':j=4;break; 
		case ')':j=5;break; 
		case '#':j=6;break; 
		default :j=0;break; 
	} 
	return yxj[i][j]; 
} 
double Operate(double num1,char theta,double num2) { 
	double num3; 
	switch(theta) { 
		case '+':num3 = num1 + num2;break; 
		case '-':num3 = num1 - num2;break;
		case '*':num3 = num1 * num2;break; 
		case '/':num3 = num1 / num2;break; 
	} 
	return num3; 
} 
void Pushnum(OPND *sq,double c) { 
	double temp1,temp2; 
	temp1 = POP_OPND(sq); 
	temp2 = temp1 * 10 + c; 
	PUSH_OPND(sq,temp2); 
} 
void Pushdp(OPND *sq,char flag,double c) { 
	double temp3,temp4; 
	char i; 
	double j = 1; 
	for(i=0;i<flag;i++) { 
		j = j * 0.1; 
	} 
	temp3 = POP_OPND(sq); 
	temp4 = temp3 + c * j; 
	PUSH_OPND(sq,temp4); 
}
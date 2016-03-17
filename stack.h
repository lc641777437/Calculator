#ifndef __STACK_H //��ջ stack.h
#define __STACK_H 
typedef struct { char *rbase; char *rtop; }OPTR; 	//����ջ 
typedef struct { double *dbase; double *dtop; }OPND; 	//����ջ 
void Init_OPTR(OPTR *s,char *TR1); 
void PUSH_OPTR(OPTR *s,char elem); 
char POP_OPTR(OPTR *s); 
void Init_OPND(OPND *s,double *ND1); 
void PUSH_OPND(OPND *s,double elem);
double POP_OPND(OPND *s); 
char Precede(char a,char b); 
double Operate(double num1,char theta,double num2); 
void Pushnum(OPND *sq,double c); 
void Pushdp(OPND *sq,char flag,double c); 
#endif
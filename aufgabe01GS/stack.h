#ifndef STACK_H
#define	STACK_H

#define MAXSIZE 		8
#define TRUE 				1
#define FALSE 			0

extern unsigned int Empty(void);
extern unsigned int Full(void);
extern int stackTop(void);
extern int take(void);
extern void put(int data);
extern void clearStack(void);
extern void putOnStack (void);
extern void printStack (void);
extern void printTopStack (void);
extern void replaceOnStack (int data);
extern void swapPosition (void);



#endif	/* STACK_H */

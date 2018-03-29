#define STACK_SIZE 8
#define INPUT_POS 1,1
#define CURR_STACK 1,2
#define COMP_STACK 1,3

extern int stack[];
extern void addDigit(int digit);
extern int getCurrentStack(void);
extern int getPointer(void);
extern void setStack(float value);
extern void push(void);
extern int pop(void);
extern void printFirst(void);
extern void printStack(void);
extern void clear(void);
extern void duplicate(void);
extern void swapPos(void);

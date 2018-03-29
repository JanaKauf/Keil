#define STACK_SIZE 8
#define INPUT_POS 1,1
#define COMP_STACK_POS 1,5
#define CURR_STACK_POS 1,3
#define STATUS_POS 1,8

extern int stack[STACK_SIZE];
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

#ifndef STACK_H
#define STACK_H

stack* stack_initialization();
GLdouble* peak(stack* s);
void stack_add(stack *s, int code, char egoera, char aldaketa);
void pop(stack* s);
void redo(stack* s);



#endif // STACK_H

#ifndef STACK_H
#define STACK_H

stack* stack_initialization();
GLdouble* peak(stack* s);
void stack_add(stack *s, int code, char egoera, char aldaketa);
void pop(stack* s);
void redo(stack* s);
void matrix_into_stack(GLdouble* m1, GLdouble* m2, stack* s,char aldaketa);

#endif // STACK_H

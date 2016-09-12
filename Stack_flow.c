#include <stdio.h>
#include <string.h>
int n=20;
struct StackItems{
    int x;
    int y;
    int d;
};
struct stack
{
    int top;
    struct StackItems stackitems[20];    
}s;
void push(int, int ,int);
struct StackItems pop(void);

int main(){
    struct StackItems Test;
    s.top = -1;
    push(2,21,24);
    printf( "%d %d %d \n", s.stackitems[s.top].x, s.stackitems[s.top].y, s.stackitems[s.top].d);
    push(5,31,88);
    push(9,31,88);
    Test = pop();
    printf( "%d %d %d \n", Test.x, Test.y, Test.d);
    push(24,31,88);
    Test = pop();
    printf( "%d %d %d \n", Test.x, Test.y, Test.d);
    return 0;
}

void push (int x,int y,int d)
{
    if ( s.top >= n )
    {
        printf ("Stack is Full\n");
        return;
    }
    else
    {
        s.top = s.top + 1;
        s.stackitems[s.top].x = x;
        s.stackitems[s.top].y = y;
        s.stackitems[s.top].d = d;
    }
    return;
}
struct StackItems pop()
{
    struct StackItems Test;
    if (s.top <= - 1)
    {
        printf ("Stack is Empty\n");
        return (s.stackitems[s.top]);
    }
    else
    {
        Test.x = s.stackitems[s.top].x;
        Test.y = s.stackitems[s.top].y;
        Test.d = s.stackitems[s.top].d;
        s.top = s.top - 1;
    }
    return (Test);
}
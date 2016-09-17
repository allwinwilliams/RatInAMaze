#include <stdio.h>
#define SIZE 20
#include <stdlib.h>
#include <unistd.h>
struct StackItems{
    int x;
    int y;
    int dir;
};
struct stack
{
    int top;
    struct StackItems stackitems[SIZE];    
}s;
void push(int, int ,int);
struct StackItems pop(void);
int main()
{
    int maze[SIZE][SIZE],mark[SIZE][SIZE],stack[SIZE][3];
    int move[8][2]={-1,0,-1,1,0,1,1,1,1,0,1,-1,0,-1,-1,-1};
    int i,j,m,n,top,d,g,h,p;
    struct StackItems InstStkI;
    printf("enter size");
    scanf("%d%d",&m,&n);
    //Initializing mark - all value to 0.
    // for(i=1;i<=m;i++){
    //     for(j=1;j<=n;j++){
            
    //     }
    // }
    //Input for maze
    for(i=1;i<=m;i++){
        for(j=1;j<=n;j++){
            mark[i][j]=0;
            scanf("%d",&maze[i][j]);
        }
    }
    //Outer wall - horizontal
    for(i=0;i<=n+1;i++){
        maze[0][i]=1;
        maze[m+1][i]=1;
    }
    //Outer wall - vertical
    for(i=0;i<=m+1;i++){
        maze[i][0]=1;
        maze[i][n+1]=1;
    }
    //Print grid
    for(i=0;i<=m+1;i++){
        for(j=0;j<=n+1;j++){
            printf(" %d ",maze[i][j]);
        }
        printf("\n");
    }

    mark[1][1]=1;

    s.top = -1;
    push(1,1,2);
    

    stack[0][0]=0;
    stack[0][1]=0;
    // stack[0][2]=2;
    stack[0][2]=-1;
    top=0;  
    while(s.top!=-1){
        InstStkI = pop();
        InstStkI.x = InstStkI.x + 1;
        InstStkI.y = InstStkI.y + 1;
        InstStkI.dir = InstStkI.dir + 1;
        i=stack[top][0]+1;
        j=stack[top][1]+1;
        d=stack[top][2]+1;
        top = top - 1;
        while(d<8){
            g = i + move[d][0];
            h = j + move[d][1];
            if( g == m && h == n ){
                top = top + 1;
                stack[top][0] = i; stack[top][1] = j; stack[top][2] = d;
                top = top + 1;
                stack[top][0] = m; stack[top][1] = n; stack[top][2] = 8;
                push(i,j,d);
                push(m,n,8);
                for( p=0 ; p<=top ; p++){
                    printf("\nstack arr:  %d %d %d\n",stack[p][0],stack[p][1],stack[p][2]);
                    InstStkI = pop();
                    printf("stack:  %d %d %d\n",InstStkI.x, InstStkI.y, InstStkI.dir);    
                    //Print grid
                    usleep(900000);
                    for(i=0;i<=m+1;i++){
                        for(j=0;j<=n+1;j++){
                            if( i == stack[p][0] && j == stack[p][1] )
                                printf(" X ");
                            else
                                printf(" %d ",maze[i][j]);
                        }
                        printf("\n");
                    }
                    
                }
                printf("\n the path is \n");
                for(i=0;i<=m+1;i++){
                    for(j=0;j<=n+1;j++){
                        for( p=0 ; p<=top ; p++){
                            if(i==stack[p][0] && j==stack[p][1]){
                                printf(" * ");
                                break;
                            }
                        }
                        if(!(i==stack[p][0] && j==stack[p][1])){
                            printf(" %d ",maze[i][j]);
                        }
                    }
                    printf("\n");
                }
                return 0;
            }

            if( maze[g][h]==0 && mark[g][h]==0 ){
                
                mark[g][h]=1;
                
                push(i,j,d);
                top = top + 1;
                stack[top][0]=i;
                stack[top][1]=j;
                stack[top][2]=d;

                i=g;
                j=h;
                d=0;
            }//end if
            d=d+1; 
        }//end while d<8
    }//end while top==0
    printf("No path found");
    return 0;
}
void push (int x,int y,int dir)
{
    if ( s.top > SIZE )
    {
        printf ("Stack is Full\n");
        return;
    }
    else
    {
        s.top = s.top + 1;
        s.stackitems[s.top].x = x;
        s.stackitems[s.top].y = y;
        s.stackitems[s.top].dir = dir;
    }
    return;
}
struct StackItems pop()
{
    struct StackItems Test;
    Test.x = Test.y = Test.dir = 0;
    if (s.top <= -1)
    {
        printf ("Stack is Empty\n");
        return (Test);
    }
    else
    {
        Test.x = s.stackitems[s.top].x;
        Test.y = s.stackitems[s.top].y;
        Test.dir = s.stackitems[s.top].dir;
        s.top = s.top - 1;
    }
    return (Test);
}
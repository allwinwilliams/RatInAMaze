#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "time.h"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
#define MAX 50
struct StackItems{
    int x;
    int y;
    int dir;
};
struct stack
{
    int top;
    struct StackItems stackitems[MAX];    
}s;
void push(int, int ,int);
struct StackItems pop(void);
int main(){
    int maze[MAX][MAX],mark[MAX][MAX],stack[MAX * MAX][3];
    int move[8][2]={-1,0,-1,1,0,1,1,1,1,0,1,-1,0,-1,-1,-1};
    int i,j,m,n,top,d,g,h,p,k;
    struct StackItems InstStkI;
    printf("enter size- row and column");
    if(scanf("%d%d",&m,&n) !=2){
        printf("Invalid input\n");
        return(0);
    }
    if( m < 0 || n< 0 || m >50 || n>50){
        printf("Invalid input\n");
        return(0);
    }
    //Initializing mark - all value to 0.
    // for(i=1;i<=m;i++){
    //     for(j=1;j<=n;j++){
            
    //     }
    // }
    //Input for maze
    srand(time(NULL));
    for(i=1;i<=m;i++){
        for(j=1;j<=n;j++){
            mark[i][j]=0;
            // if( (i==1&&j==1) || (i==m&&j==n) )
            //     maze[i][i]=0;
            //else
                maze[i][j] = (rand()%2==0)?1:0;
            // if(rand() % 2)
            //     maze[i][j] = 1;
            // else
            //     maze[i][j] = 0;
            //scanf("%d",&maze[i][j]);
        }
    }
    maze[1][1]=0;
    maze[m][n]=0;
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
            if(i==  0||i==m+1||j==0||j==n+1)
                printf(" %s%d%s ",CYN,maze[i][j],WHT);
            else{
                if(maze[i][j]==0)
                    printf(" %d ",maze[i][j]);
                else
                    printf(" %s%d%s ",BLU,maze[i][j],WHT);
            }
        }
        printf("\n");
    }

    mark[1][1]=1;

    s.top = 0;
    push(1,1,2);
    

    stack[0][0]=1;
    stack[0][1]=1;
    // stack[0][2]=2;
    stack[0][2]=2;
    top=0;  
    while(s.top!=0){
        InstStkI = pop();
        InstStkI.x = InstStkI.x ;
        InstStkI.y = InstStkI.y ;
        InstStkI.dir = InstStkI.dir ;
        i=stack[top][0];
        j=stack[top][1];
        d=stack[top][2];
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
                     
                    //Print grid
                    usleep(900000);
                    for(i=0;i<=m+1;i++){
                        for(j=0;j<=n+1;j++){
                            if( i == stack[p][0] && j == stack[p][1] )
                                printf(" %sX%s ",RED,WHT);
                            else{
                                if(i==0||i==m+1||j==0||j==n+1)
                                    printf(" %s%d%s ",CYN,maze[i][j],WHT);
                                else{
                                    for(k=0;k<=top;k++){
                                        if(i== stack[k][0]&& j==stack[k][1])
                                            break;
                                    }
                                    if ( mark[i][j]==1 && k== top+1 )
                                        printf(" %s%d%s ",YEL,maze[i][j],WHT);
                                    else{

                                        if(mark[i][j]==1){
                                            printf(" %s%d%s ",MAG,maze[i][j],WHT);
                                        } 
                                        else{  
                                            if(maze[i][j]==0){
                                                printf(" %d ",maze[i][j]);
                                            }
                                            else
                                                printf(" %s%d%s ",BLU,maze[i][j],WHT);
                                        }
                                    }

                                }
                            }
                        }
                        printf("\n");
                    }    
                    printf("\nstack arr:  %d %d %d\n",stack[p][0],stack[p][1],stack[p][2]);
                    InstStkI = pop();
                    printf("stack:  %d %d %d\n",InstStkI.x, InstStkI.y, InstStkI.dir);   
                }
                printf("\n the path is \n");
                for(i=0;i<=m+1;i++){
                    for(j=0;j<=n+1;j++){
                        for( p=0 ; p<=top ; p++){
                            if(i==stack[p][0] && j==stack[p][1]){

                                printf(" %s*%s ",GRN,WHT);
                                break;
                            }
                            if(p==top){
                                if(i==  0||i==m+1||j==0||j==n+1)
                                    printf(" %s%d%s ",CYN,maze[i][j],WHT);
                                else{
                                    for(k=0;k<=top;k++){
                                        if(i== stack[k][0]&& j==stack[k][1])
                                            break;
                                    }
                                    if ( mark[i][j]==1 && k== top+1 )
                                        printf(" %s%d%s ",YEL,maze[i][j],WHT);
                                    else{
                                        if(maze[i][j]==0)
                                            printf(" %d ",maze[i][j]);
                                        else
                                            printf(" %s%d%s ",BLU,maze[i][j],WHT);
                                        
                                    }                                    
                                }
                            }
                        }
                        // if(!(i==stack[p][0] && j==stack[p][1])){
                        //     printf(" %d ",maze[i][j]);
                        // }
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
                d=-1;
            }//end if
            d=d+1; 
        }//end while d<8
    }//end while top==0
    printf("No path found");
    return 0;
}
void push (int x,int y,int dir)
{
    if ( s.top > MAX*MAX )
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
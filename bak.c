
#include <stdio.h>
#define SIZE 20
#include <stdlib.h>
int main()
{
    int maze[SIZE][SIZE],mark[SIZE][SIZE],stack[SIZE][3];
    int move[8][2]={-1,0,-1,1,0,1,1,1,1,0,1,-1,0,-1,-1,-1};
    int i,j,m,n,top,d,g,h,p;
    printf("enter size");
    scanf("%d%d",&m,&n);
    //Initializing mark - all value to 0.
    for(i=1;i<=m;i++){
        for(j=1;j<=n;j++){
            mark[i][j]=0;
        }
    }
    //Input for maze
    for(i=1;i<=m;i++){
        for(j=1;j<=n;j++){
            scanf("%d",&maze[i][j]);
        }
    }
    //Outer wall - horizontal
    for(i=0;i<=n+1;i++){
        maze[0][i]=1;
        maze[m+1][i]=1;
    }
    //Outer wall - vertacal
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
    stack[0][0]=1;
    stack[0][1]=1;
    stack[0][2]=2;
    top=1;
    while(top!=0){
        i=stack[top][0]+1;
        j=stack[top][1]+1;
        d=stack[top][2]+1;
        top=top-1;
        while(d<=8){
            g=i+move[d][0];
            h=j+move[d][1];
            if( g==m && h==n ){
                for(p=1;p<=top;p++){
                    printf("\n%d %d %d",stack[p][0],stack[p][1],stack[p][2]);
                }
                printf("\ni:%d j:%d d:%d",i,j,d); 
                printf("\nm:%d n:%d ",m,n);
                return 0;
            }
            if( mark[g][h]==0 && maze[g][h]==0){
                mark[g][h]=1;
                top = top+1;
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

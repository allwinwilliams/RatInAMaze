#include "stdio.h"
#define SIZE 50
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
struct Position{
	int row;
	int col;
}start, finish,temp, here, neighbour,offset[4],path[SIZE];
struct Queue
{
	int front;
	int rear;
	struct Position pos[SIZE * SIZE];
}q;
int i,j,p,k,l,flag,m,n,pathlength,flag,grid[SIZE][SIZE];
int addQueue(struct Position);
struct Position deleteQuene(void);
int isEmpty(void);
void showGrid(void);
void makeGrid(void);
void getGrid(void);
void showPath(void);
int findPath(void);
int analyseGrid(void);
int main(){
	pathlength=0;
	q.front = 0; q.rear = 0;
	start.row = 1; start.col = 1;
	printf("enter grid size - rows and columns\n");
	if(scanf("%d%d",&m,&n) !=2){
        printf("Invalid input\n");
        return(0);
    }
    if( m < 0 || n< 0 || m >50 || n>50){
        printf("Invalid input\n");
        return(0);
    }
	finish.row = m; finish.col = n;
	makeGrid();
	showGrid();
	getchar();
	if(!analyseGrid()){
		printf("NO PATH FOUND\n");
	}
   	else{
   		printf("the shorteshest path lenth is %d\n",pathlength );
   	}
   	//show grid 
	showGrid();
	
	return 0;
}

void makeGrid(){
	getGrid();
	//create wall around grid
	for(i = 0; i <= n+1; i++) {
		grid[0][i]= grid[m+1][i]=1;
	}
	for (i = 0; i <= m+1 ; i++){
		grid[i][0]=grid[i][n+1]=1;
	}
}
void getGrid(){
	//get grid
	//randomize();
	srand(time(NULL));
	for(i=1;i<=m;i++){
        for(j=1;j<=n;j++){
            if( (i==start.row&&j==start.col) || (i==finish.row&&j==finish.col) )
                grid[i][i]=0;
            else
                grid[i][j] = (rand()%3==0)?1:0;
            //scanf("%d",&grid[i][j]);
        }
    }
    grid[1][1]=0;
    grid[m][n]=0;
}
int analyseGrid(){

 	//    if( (start.row == finish.row) && (start.col == finish.col) ){
	// 	pathlength = 0;
	// 	printf("starting point is ending point.\n");
	// 	return 0;
	// }

	offset[0].row = 0; offset[0].col = 1; //right
	offset[1].row = 1; offset[1].col = 0; //down
	offset[2].row = 0; offset[2].col = -1; //left
	offset[3].row = -1; offset[3].col = 0; //up
	//here indicate current location
	here = start;

	grid[start.row][start.col] = 2;
	while(1){
		for( i = 0; i <= 3 ; i++){
			neighbour.row = here.row + offset[i].row;
			neighbour.col = here.col + offset[i].col;
			if(grid[neighbour.row][neighbour.col] == 0){
				grid[neighbour.row][neighbour.col] = grid[here.row][here.col] + 1;
				addQueue(neighbour);
				if( (neighbour.row == finish.row) && (neighbour.col == finish.col) ){
					break;
				}
			}	
		}
		if((neighbour.row == finish.row) && (neighbour.col == finish.col)){
			break;
		}
		
		if( isEmpty() ){
			printf("No possible path found.\n");
			return 0;
		}
		here = deleteQuene();
	}
	findPath();
	return 1;
}
int findPath(){
	pathlength = grid[finish.row][finish.col]-2;
	here = finish;
	for(j = pathlength-1; j >= 0 ;j--){
		path[j].row = here.row;
		path[j].col = here.col;
		for (i = 0; i <= 3; i++){
			neighbour.row = here.row + offset[i].row;
			neighbour.col = here.col + offset[i].col;
			if(grid[neighbour.row][neighbour.col] == j+2){
				break;	
			}
		}
		here = neighbour;
		printf("%d %d\n", path[j].row, path[j].col );
		//printf("path is \n");
		
	    // for(i=0;i<=m+1;i++){
	    //     for(k=0;k<=n+1;k++){
	    //         if( (i == path[(pathlength-1)-j].row) && (k == path[(pathlength-1)-j].col) )
	    //             printf(" X ");
	    //         else
	    //             printf(" %d ",(grid[i][k]==1)?1:0);
	    //     }
	    //     printf("\n");
	    // }
	    // usleep(900000);		
	}
	showPath();
	return pathlength;	
}
void showPath(){	
	printf("path map \n");
	for(i=0;i<=m+1;i++){
        for(j=0;j<=n+1;j++){
            for(k = pathlength-1; k >= 0 ;k--){

            	if(i == path[k].row && j == path[k].col  ){
            		printf(" %s*%s ",GRN,WHT);
            		break;
            	}
            }
            // if((i == path[k].row && j == path[k].col))
            if(k==-1){
            	if(i==0||i==m+1||j==0||j==n+1)
            		printf(" %s%d%s ",BLU,( (grid[i][j]==1)?1:0 ),WHT);
            	else	
            		printf(" %d ", ( (grid[i][j]==1)?1:0 ) );
        	}
        }
        printf("\n");
    }
}
int addQueue(struct Position pos){
	if (q.rear == SIZE * SIZE){
		printf("Queue Full\n");
		return 0;
	}
	q.rear = q.rear+1;
	q.pos[q.rear] = pos;
	return 0;
}
struct Position deleteQuene(){
	struct Position i;
	if(q.front == q.rear){
		printf("Queue Empty\n");
		return q.pos[q.front];
	}
	i = q.pos[q.front];
	q.front = q.front+1;
	return i;
}
struct Position valueInFront(){
	struct Position i;
	if(q.front == q.rear){
		printf("Queue Empty\n");
		return q.pos[q.front];
	}
	i = q.pos[q.front];
	return i;
}
int isEmpty(){
	if(q.front == q.rear){
		return 1;
	}
	return 0;
}
void showGrid(){
	for(i=0;i<=m+1;i++){
        for(j=0;j<=n+1;j++){
            if(i==0||i==m+1||j==0||j==n+1)
            	printf(" %s%2d%s ",BLU,grid[i][j],WHT);
			else           
            	printf(" %2d ",grid[i][j]);

        }
        printf("\n");
    }
}
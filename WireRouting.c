#include <stdio.h>
#define SIZE 20
#define SIZE_SIZE 40
#include <stdlib.h>
// #include "GRAPHICS.H"

struct Position{
	int row;
	int col;
}start, finish,temp, here, neighbour,offset[4],path[SIZE];
struct Queue
{
	int front;
	int rear;
	struct Position pos[SIZE_SIZE];
}q;

int i,j,k,flag,m,n,pathlength,flag,grid[10][10];

int addQueue(struct Position);
struct Position deleteQuene(void);
int isEmpty(void);
void showGrid(void);
int findPath();
int analyseGrid();
int main(){

	pathlength=0;
	q.front = 0;q.rear = 0;
	start.row = 1;start.col = 1;
	printf("enter grid size - rows and columns\n");
	scanf("%d",&m);
	scanf("%d",&n);
	finish.row = m; finish.col = n;

	
	//get grid
	for(i=1;i<=m;i++){
        for(j=1;j<=n;j++){
            scanf("%d",&grid[i][j]);
        }
    }
	//create wall around grid
	for(i = 0; i <= m+1; i++) {
		grid[0][i] = grid[m+1][i]=1;
		
	}
	for (i = 0; i < n+1 ; i++){
		grid[i][0]=grid[i][n+1]=1;
	}
	showGrid();

	if(!analyseGrid()){
		printf("NO PATH FOUND\n");
	}
   	else{
   	printf("the shorteshest path lenth is %d\n",findPath() );
   	}

	printf("process finished\n");
	//show grid 
	showGrid();
	printf("path is \n");
	for(i=0;i<=m+1;i++){
        for(j=0;j<=n+1;j++){
            for(k = pathlength-1; k >= 0 ;k--){
            	if(i == path[k].row && j == path[k].col  ){
            		printf(" * ");
            		break;
            	}
            }
            if(!(i == path[k].row && j == path[k].col))
            	printf(" %d ", ( (grid[i][j]==1)?1:0 ) );
        }
        printf("\n");
    }
	
	
	return 0;
}
int analyseGrid(){

    if( (start.row == finish.row) && (start.col == finish.col) ){
		pathlength = 0;
		printf("starting point is ending point.\n");
		return 0;
	}

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
				if((neighbour.row == finish.row) && (neighbour.col == finish.col)){
					break;
				}
				
			}	
		}
		if((neighbour.row == finish.row) && (neighbour.col == finish.col)){
			break;
		}
		
		if(isEmpty()){
			return 0;
		}
		
		here = deleteQuene();
	}	
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
	}
	return pathlength;	
}
int addQueue(struct Position pos){
	if (q.rear == SIZE_SIZE){
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
int isEmpty(){
	if(q.front == q.rear){
		return 1;
	}
	return 0;
}
void showGrid(){
	for(i=0;i<=m+1;i++){
        for(j=0;j<=n+1;j++){
            printf(" %d ",grid[i][j]);
        }
        printf("\n");
    }
}
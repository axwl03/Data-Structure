#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randomWalk(int n, int m, int ibug, int jbug);

int main(){
	srand(time(NULL));
	printf("Experiment 1:\n");
	randomWalk(15, 15, 10, 10);
	printf("Experiment 2:\n");
	randomWalk(39, 19, 1, 1);
	return 0;
}
void randomWalk(int n, int m, int ibug, int jbug){
	int count[n][m], completedPos = 0, imove[8] = {-1,0,1,1,1,0,-1,-1}, jmove[8] = {1,1,1,0,-1,-1,-1,0}, increment_i, increment_j, totalMoves = 0;
	
	/*initializie count to zero*/
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			count[i][j] = 0;
		}
	}
	
	/*count in start position*/
	++count[ibug][jbug];
	++completedPos;
	
	/*experiment*/
	while(completedPos < n*m){
		
		/*maximum step to walk*/
		if(totalMoves >= 50000)
			break;
		totalMoves++;
		
		/*test whether exceed boundary*/
		increment_i = imove[rand()%8];
		increment_j = jmove[rand()%8];
		while(ibug + increment_i < 0 || ibug + increment_i >= n || jbug + increment_j < 0 || jbug + increment_j >= m){
			increment_i = imove[rand()%8];
			increment_j = jmove[rand()%8];
		}
		
		/*success combination*/
		ibug += increment_i;
		jbug += increment_j;
		
		/*record new position*/
		if(count[ibug][jbug] == 0)
			++completedPos;
		++count[ibug][jbug];
	}
	
	/*print out result*/
	printf("Total moves: %d\n", totalMoves);
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			printf("%5d", count[i][j]);
			if(j == m-1)
				printf("\n");
		}
	}
}
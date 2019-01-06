#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INF 1000
#define MAX_SIZE 20

int stack[MAX_SIZE];
int cost[MAX_SIZE][MAX_SIZE];
bool mcst[MAX_SIZE][MAX_SIZE]; //stand for minimum cost spanning tree
int edgeSelected = 0, maxVertex = 0, top = -1;
void sollin();
void push(int e);
int pop();
void maintain();
int countEdge();

int main(){
	/*initializing*/
	for(int i = 0; i < MAX_SIZE; ++i){
		for(int j = 0; j < MAX_SIZE; ++j){
			mcst[i][j] = 0;
			if(i == j)
				cost[i][j] = 0;
			else cost[i][j] = INF;
		}
	}
	int n = 0, u, v;
	scanf("%d", &n);
	for(int i = 0; i < n; ++i){
		scanf("%d %d", &u, &v);
		scanf("%d", &cost[u][v]);
		while(u >= MAX_SIZE || v >= MAX_SIZE){
			printf("error input, try again\n");
			scanf("%d %d", &u, &v);
			scanf("%d", &cost[u][v]);
		}
		if(u > maxVertex)
			maxVertex = u;
		if(v > maxVertex)
			maxVertex = v;
		cost[v][u] = cost[u][v];
	}
	
	/*generating mcst*/
	sollin();
	
	/*output mcst*/
	printf("Output:\n");
	for(u = 0; u <= maxVertex; u++){
		for(v = u+1; v <= maxVertex; v++){
			if(mcst[u][v])
				printf("%d %d %d\n", u, v, cost[u][v]);
		}
	}
	return 0;
}
void sollin(){
	int u, v; //next edge to be joined
	int n = 0, temp;
	bool checked[maxVertex + 1];
	for(int i = 0; i <= maxVertex; ++i)
		checked[i] = 0;
	while(n < maxVertex-1){
		for(int i = 0; i <= maxVertex; ++i){
			if(checked[i] == 1)
				continue;
			u = 0;
			v = 0;
			checked[i] = 1;
			for(int j = 0; j <= maxVertex; ++j){
				if(i == j)
					continue;
				if(mcst[i][j] && checked[j] == 0)
					push(j);
				else{
					if((cost[i][j] < cost[u][v] || cost[u][v] == 0) && mcst[i][j] != 1){
						u = i;
						v = j;
					}
				}
			}
			while(top >= 0){
				temp = pop();
				if(checked[temp] == 1)
					continue;
				checked[temp] = 1;
				for(int j = 0; j <= maxVertex; ++j){
					if(temp == j)
						continue;
					if(mcst[temp][j] && checked[j] == 0)
						push(j);
					else{
						if(cost[temp][j] < cost[u][v] && mcst[temp][j] != 1){
							u = temp;
							v = j;
						}
					}
				}
			}
			mcst[u][v] = 1;
		}
		for(int m = 0; m <= maxVertex; m++)
			checked[m] = 0;
		maintain();
		n = countEdge();
	}
}
void maintain(){
	for(int i = 0; i <= maxVertex; ++i)
		for(int j = 0; j <= maxVertex; ++j)
			if(mcst[i][j] == 1)
				mcst[j][i] = 1;
}
int countEdge(){
	int count = 0;
	for(int i = 0; i <= maxVertex; ++i)
		for(int j = 0; j <= maxVertex; ++j)
			if(mcst[i][j] == 1)
				count++;
	return count/2;
}
void push(int e){
	if(top < MAX_SIZE)
		stack[++top] = e;
	else{
		printf("stack is full\n");
		exit(1);
	}
}
int pop(){
	if(top < 0){
		printf("stack is empty\n");
		exit(1);
	}
	else return stack[top--];
}
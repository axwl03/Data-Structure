#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

struct node{
	int vertex, dur, act;
	struct node *link;
};
typedef struct node node;
typedef struct{
	int count;
	node *link;
} hdnode;
hdnode graph[MAX_SIZE];
int early[MAX_SIZE], late[MAX_SIZE], maxVertex = 0, top = -1, maxAct = 0;
int stack[MAX_SIZE], stackTop = -1;

void insert(node **ptr, int act, int v, int dur);
void getEarlyLate();
void push(int vertex);
int pop();

int main(){
	/*initializing*/
	for(int i = 0; i < MAX_SIZE; ++i){
		graph[i].link = NULL;
		graph[i].count = 0;
		early[i] = 0;
	}
	
	/*input graph*/
	int n, u, v, act, dur;
	node *ptr;
	scanf("%d", &n);
	for(int i = 0; i < n; ++i){
		scanf("%d %d %d %d", &act, &u, &v, &dur);
		if(v > maxVertex)
			maxVertex = v;
		if(act > maxAct)
			maxAct = act;
		if(graph[u].link == NULL)
			insert(&graph[u].link, act, v, dur);
		else{
			ptr = graph[u].link;
			while(ptr->link != NULL)
				ptr = ptr->link;
			insert(&ptr->link, act, v, dur);
		}
		graph[v].count++;
	}
	/*get early time and late time*/
	getEarlyLate();
	
	/*output*/
	printf("Output:\n");
	printf("act.\te\tl\tslack\tcritical\n");
	for(int i = 1; i <= maxAct; ++i){
		printf("%-d\t%-d\t%-d\t%-d\t", i, early[i], late[i], late[i]-early[i]);
		if(late[i]-early[i] == 0)
			printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
void insert(node **ptr, int act, int v, int dur){
	node *temp = malloc(sizeof(node));
	if(temp == NULL){
		printf("allocation failed\n");
		exit(1);
	}
	temp->link = NULL;
	temp->act = act;
	temp->dur = dur;
	temp->vertex = v;
	*ptr = temp;
}	
void getEarlyLate(){
	int j, ee[maxVertex+1], le[maxVertex+1], k, dur;
	node *ptr;
	/*initializing*/
	for(int i = 0; i <= maxVertex; ++i)
		ee[i] = 0;
	/*earliest event time*/
	for(int i = 0; i <= maxVertex; ++i){
		if(graph[i].count == 0){
			graph[i].count = top;
			top = i;
		}
	}
	for(int i = 0; i <= maxVertex; ++i){
		if(top == -1){
			printf("error\n");
			exit(1);
		}
		else{
			j = top; //pop
			top = graph[j].count;
			push(j);
			for(ptr = graph[j].link; ptr != NULL; ptr = ptr->link){
				if(ee[j] + ptr->dur > ee[ptr->vertex]) //calculate ee time
					ee[ptr->vertex] = ee[j] + ptr->dur;
				graph[ptr->vertex].count--;
				if(graph[ptr->vertex].count == 0){ //push
					graph[ptr->vertex].count = top;
					top = ptr->vertex;
				}
			}
		}
	}
	/*earliest time*/
	for(int i = 0; i <= maxVertex; ++i){
		ptr = graph[i].link;
		while(ptr != NULL){
			early[ptr->act] = ee[i];
			ptr = ptr->link;
		}
	}
	/*latest time & latest event time*/
	for(int i = 0; i <= maxVertex; ++i)
		le[i] = ee[maxVertex];
	pop();
	while(stackTop >= 0){
		k = pop();
		ptr = graph[k].link;
		while(ptr != NULL){
			if(le[k] > le[ptr->vertex] - ptr->dur)
				le[k] = le[ptr->vertex] - ptr->dur;
			late[ptr->act] = le[ptr->vertex] - ptr->dur;
			ptr = ptr->link;
		}
	}
}
void push(int vertex){
	if(top == MAX_SIZE-1){
		printf("stack full\n");
		exit(1);
	}
	else stack[++stackTop] = vertex;
}
int pop(){
	if(stackTop < 0){
		printf("stack empty\n");
		exit(1);
	}
	else return stack[stackTop--];
}
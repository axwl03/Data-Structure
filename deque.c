#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

int deque[MAX_SIZE];
int front = MAX_SIZE/2, rear = MAX_SIZE/2 - 1;
int isEmpty();
void push_front(int n);
void push_back(int n);
int pop_front();
int pop_back();
void show();

int main(){
	char command[15];
	int n, count = 50;
	while(count){
		scanf(" %s", command);
		if(strcmp(command, "push_front") == 0){
			if(scanf("%d", &n) == 0){
				printf("Please specify the number you wanted to push\n");
				fflush(stdin);
				continue;
			}
			push_front(n);
		}
		else if(strcmp(command, "push_back") == 0){
			if(scanf("%d", &n) == 0){
				printf("Please specify the number you wanted to push\n");
				fflush(stdin);
				continue;
			}
			push_back(n);
		}
		else if(strcmp(command, "pop_front") == 0){
			pop_front();
		}
		else if(strcmp(command, "pop_back") == 0){
			pop_back();
		}
		else if(strcmp(command, "show") == 0){
			show();
		}
		else{
			printf("Not valid command, try again\n");
			fflush(stdin);
		}
		count--;
	}
	return 0;
}
int isEmpty(){
	if(front > rear)
		return 1;
	return 0;
}
void push_front(int n){
	if(front - 1 >= 0)
		front--;
	else{
		printf("Front is full\n");
		return;
	}
	deque[front] = n;
}
void push_back(int n){
	if(rear + 1 <= MAX_SIZE - 1)
		rear++;
	else{
		printf("Rear is full\n");
		return;
	}
	deque[rear] = n;
}
int pop_front(){
	if(isEmpty())
		printf("Deque is empty\n");
	if(front + 1 >= MAX_SIZE){
		printf("Could not pop front, front reach end of the array\n");
		return 0;
	}	
	return deque[front++];
}
int pop_back(){
	if(isEmpty())
		printf("Deque is empty\n");
	if(rear - 1 < 0){
		printf("Could not pop back, rear reach front of the array\n");
		return 0;
	}	
	return deque[rear--];
}
void show(){
	if(isEmpty()){
		printf("Deque is empty\n");
		return;
	}
	for(int i = front; i <= rear; i++){
		printf("%d ", deque[i]);
	}printf("\n");
}
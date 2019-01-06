#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct{
	int key;
} element;
element heap[MAX_SIZE];
int n = 0;

void push(int i);
void display();
int search(int key);
void change(int key1, int key2);

int main(){
	int temp = 0;
	/*input max heap element*/
	scanf("%d", &temp);
	push(temp);
	while(getchar() != '\n'){
		scanf("%d", &temp);
		push(temp);
	}
	/*change key1 to key2*/
	int key1, key2;
	scanf("%d %d", &key1, &key2);
	change(key1, key2);
	while(getchar() != '\n'){
		scanf("%d %d", &key1, &key2);
		change(key1, key2);
	}
	/*output*/
	display();
	return 0;
}
void push(int i){
	heap[++n].key = i;
}
void display(){
	if(n <= 0){
		printf("Heap is empty\n");
		return;
	}
	for(int i = 1; i <= n; ++i)
		printf("%d ", heap[i]);
	printf("\n");
}
int search(int key){
	if(n <= 0){
		printf("Empty heap\n");
		exit(1);
	}
	for(int i = 1; i <= n; ++i){
		if(heap[i].key == key)
			return i;
	}
	/*not found*/
	printf("Element is not in the heap\n");
	exit(1);
}
void change(int key1, int key2){
	int temp = search(key1), largeElement;
	heap[temp].key = key2;
	for(int i = temp;;){
		/*larger than parent*/
		if(i/2 >= 1){
			if(heap[i].key > heap[(int)i/2].key){
				temp = heap[(int)i/2].key;
				heap[(int)i/2].key = heap[i].key;
				heap[i].key = temp;
				i = i/2;
				continue;
			}
		}
		/*smaller than child*/
		if(2*i+1 <= n){
			if(heap[i].key < heap[i*2].key && heap[i].key < heap[i*2+1].key){
				if(heap[i*2].key > heap[i*2+1].key)
					largeElement = i*2;
				else largeElement = i*2+1;
				temp = heap[largeElement].key;
				heap[largeElement].key = heap[i].key;
				heap[i].key = temp;
				i = largeElement;
			}
			else if(heap[i].key < heap[i*2].key && heap[i].key > heap[i*2+1].key){
				temp = heap[i*2].key;
				heap[i*2].key = heap[i].key;
				heap[i].key = temp;
				i = i*2;
			}
			else if(heap[i].key > heap[i*2].key && heap[i].key < heap[i*2+1].key){
				temp = heap[i*2+1].key;
				heap[i*2+1].key = heap[i].key;
				heap[i].key = temp;
				i = i*2+1;
			}
			/*correct position*/
			else break;
		}
		else if(2*i+1 > n){
			if(heap[i].key < heap[i*2].key){
				temp = heap[i*2].key;
				heap[i*2].key = heap[i].key;
				heap[i].key = temp;
				i = i*2;
			}
			/*correct position*/
			else break;
		}
	}
}
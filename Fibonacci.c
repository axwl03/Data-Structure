#include <stdio.h>
#include <stdlib.h>

int recursive(int i);
int iterative(int i);

int main(){
	int test_case, i;
	printf("number of test: ");
	scanf("%d", &test_case);
	/*check whether test_case is larger than 0*/
	for(; test_case < 1;){
		printf("number of test case must be larger than 0\n");
		printf("try again: ");
		scanf("%d", &test_case);
	}
	/*output recursive version and iterative version*/
	for(int n = 0; n < test_case; ++n){
		scanf("%d", &i);
		printf("%d %d\n", recursive(i), iterative(i));
	}
	return 0;
}

int recursive(int i){
	if(i == 0)
		return 0;
	else if(i == 1)
		return 1;
	else
		return recursive(i-1)+recursive(i-2);
}
int iterative(int i){
	int n1 = 0, n2 = 1, temp;
	if(i == 0)
		return 0;
	if(i == 1)
		return 1;
	for(int n = 0; n <= i-2; ++n){
		temp = n1 + n2;
		n1 = n2;
		n2 = temp;
	}
	return n2;
}

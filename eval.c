#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#define MAX_SIZE 50

int stack[MAX_SIZE];
int top = -1;
void push(int n);
int pop();
bool isNumber(char ch);
typedef enum{plus, minus, times, divide, mod, and, or, equal, notEqual, less, greater, lessEqual, greaterEqual} token;
token getToken(char *sptr);

int main(){
	char str[MAX_SIZE];
	fgets(str, sizeof(str), stdin);

	/*count the number of characters in str except '\0'*/
	int n; 
	for(n = 0; str[n] != '\0'; ++n){
		if(str[n] == '\n'){
			str[n] = '\0';
			break;
		}
	}

	/*preprocess*/
	bool isSpace[n];
	for(int i = 0; i < n; ++i){
		if(str[i] == ' ')
			isSpace[i] = true;
		else isSpace[i] = false;
	}
	
	/*evaluate*/
	int number, degree, op1, op2, length;
	char operator[3];
	for(int i = n - 1; i >= 0; --i){
		if(str[i] == ' ')
			continue;
		/*operator*/
		if(isNumber(str[i]) == false){
			length = 0;
			while(isSpace[i] == false && i >= 0){
				i--;
				length += 1;
			}
			for(int j = 0; j < length; j++)
				operator[j] = str[i+j+1];
			operator[length] = '\0';
			op1 = pop();
			op2 = pop();
			switch(getToken(operator)){
			case plus: push(op1+op2);
				break;
			case minus: push(op1-op2);
				break;
			case times: push(op1*op2);
				break;
			case divide: push(op1/op2);
				break;
			case mod: push(op1%op2);
				break;
			case and: push(op1&&op2);
				break;
			case or: push(op1||op2);
				break;
			case equal: push(op1==op2);
				break;
			case notEqual: push(op1!=op2);
				break;
			case less: push(op1<op2);
				break;
			case greater: push(op1>op2);
				break;
			case lessEqual: push(op1<=op2);
				break;
			case greaterEqual: push(op1>=op2);
				break;
			}
		}
		/*number*/
		else{
			number = 0;
			degree = 0;
			while(isSpace[i] == false && i >= 0){
				number += (str[i] - '0') * (int)pow(10.000, degree++);
				--i;
			}
			push(number);
		}
	}
	/*print result*/
	printf("%d\n", pop());
	return 0;
}
void push(int n){
	if(top + 1 >= MAX_SIZE)
		printf("Stack is full\n");
	else stack[++top] = n;
}
int pop(){
	if(top - 1 < -1){
		printf("Stack is empty\n");
		exit(1);
	}
	return stack[top--];
}
bool isNumber(char ch){
	if(ch >= '0' && ch <= '9')
		return true;
	else return false;
}
token getToken(char *sptr){
	if(strcmp(sptr, "+") == 0)
		return plus;
	else if(strcmp(sptr, "-") == 0)
		return minus;
	else if(strcmp(sptr, "*") == 0)
		return times;
	else if(strcmp(sptr, "/") == 0)
		return divide;
	else if(strcmp(sptr, "%") == 0)
		return mod;
	else if(strcmp(sptr, "&&") == 0)
		return and;
	else if(strcmp(sptr, "||") == 0)
		return or;
	else if(strcmp(sptr, "==") == 0)
		return equal;
	else if(strcmp(sptr, "!=") == 0)
		return notEqual;
	else if(strcmp(sptr, "<") == 0)
		return less;
	else if(strcmp(sptr, ">") == 0)
		return greater;
	else if(strcmp(sptr, "<=") == 0)
		return lessEqual;
	else if(strcmp(sptr, ">=") == 0)
		return greaterEqual;
}

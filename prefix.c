#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#define MAX_SIZE 50

typedef struct {
	bool isNumber;
	int value;
} term; 
term stack[MAX_SIZE];//for storing prefix expression
term stack2[MAX_SIZE];//for storing operator
int top = -1, top2 = -1;
void push(bool isNumber, int n);
term pop();
void push2(bool isNumber, int n);
term pop2();

bool isNumber(char ch);
typedef enum{lparen, rparen, plus, minus, times, divide, mod, and, or, equal, notEqual, less, greater, lessEqual, greaterEqual} token;
int getPrecedence(token t);
token getToken(char *sptr);
void show(term t);

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
	
	/*start transform*/
	int number, degree, length;
	char operator[3];
	term temp;
	for(int i = n-1; i >= 0;){
		if(str[i] == ' '){
			--i;
			continue;
		}
		/*number*/
		if(isNumber(str[i])){
			number = 0;
			degree = 0;
			while(isNumber(str[i]) && i >= 0){
				number += (str[i] - '0') * (int)pow(10.0, degree++);
				--i;
			}
			push(true, number);
		}
		/*operator*/
		else{
			/*parenthesis*/
			if(str[i] == ')'){
				push2(false, rparen);
				i--;
				continue;
			}
			if(str[i] == '('){
				i--;
				temp = pop2();
				while(temp.value != rparen){
					push(false, temp.value);
					temp = pop2();
				}continue;
			}
			/*other operator*/
			length = 0;
			while(isNumber(str[i]) == false && i >= 0 && str[i] != ')' && str[i] != ' '){
				i--;
				length += 1;
			}
			for(int j = 0; j < length; j++)
				operator[j] = str[i+j+1];
			operator[length] = '\0';
			if(top2 < 0)
				push2(false, getToken(operator));
			else if(getPrecedence(getToken(operator)) < getPrecedence(stack2[top2].value)){
				while(top2 >= 0 && getPrecedence(getToken(operator)) < getPrecedence(stack2[top2].value)){
					temp = pop2();
					push(temp.isNumber, temp.value);
				}push2(false, getToken(operator));
			}
			else{
				push2(false, getToken(operator));
			}
		}
	}
	while(top2 >= 0){
		temp = pop2();
		push(temp.isNumber, temp.value);
	}
	/*show*/
	while(top >= 0){
		show(pop());
		printf(" ");
	}printf("\n");
	return 0;
}
bool isNumber(char ch){
	if(ch >= '0' && ch <= '9')
		return true;
	else return false;
}
void push(bool isNumber, int n){
	if(top + 1 >= MAX_SIZE){
		printf("Stack is full\n");
		exit(1);
	}
	else {
		stack[++top].isNumber = isNumber;
		stack[top].value = n;
	}
}
term pop(){
	if(top - 1 < -1){
		printf("Stack is empty\n");
		exit(1);
	}
	return stack[top--];
}
void push2(bool isNumber, int n){
	if(top2 + 1 >= MAX_SIZE){
		printf("Stack2 is full\n");
		exit(1);
	}
	else {
		stack2[++top2].isNumber = isNumber;
		stack2[top2].value = n;
	}
}
term pop2(){
	if(top2 - 1 < -1){
		printf("Stack is empty\n");
		exit(1);
	}
	return stack2[top2--];
}
int getPrecedence(token t){
	switch(t){
	case lparen: return 17;
	case rparen: return 0;
	case plus: return 12;
	case minus: return 12;
	case times: return 13;
	case divide: return 13;
	case mod: return 13;
	case and: return 5;
	case or: return 4;
	case equal: return 9;
	case notEqual: return 9;
	case less: return 10;
	case greater: return 10;
	case lessEqual: return 10;
	case greaterEqual: return 10;
	}
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
	else {
		printf("Exist operator unable to process.\n");
		exit(1);
	}
}
void show(term t){
	if(t.isNumber)
		printf("%d", t.value);
	else{
		switch(t.value){
		case plus: putchar('+');
			break;
		case minus: putchar('-');
			break;
		case times: putchar('*');
			break;
		case divide: putchar('/');
			break;
		case mod: putchar('%');
			break;
		case and: fputs("&&", stdout);
			break;
		case or: fputs("||", stdout);
			break;
		case equal: fputs("==", stdout);
			break;
		case notEqual: fputs("!=", stdout);
			break;
		case less: putchar('<');
			break;
		case greater: putchar('>');
			break;
		case lessEqual: fputs("<=", stdout);
			break;
		case greaterEqual: fputs(">=", stdout);
			break;
		}
	}
	printf("%");
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MALLOC(p, s) \
	if(!(p = malloc(s))){ \
		printf("allocation failed\n"); \
		exit(1); \
	}
typedef struct element{
	int row, column, value;
	struct element *next;
} element;
element *insert(element **first, element *x, int row, int column, int value);
void mread(element **first);
void mwrite(element *ptr);
element *mmult(element *m1, element *m2);
element *mtranspose(element *first);
void rearrange(element *first);
void clear(element **first);
bool isEmpty(element *first);

int main(){
	element *m1_first = NULL, *m2_first = NULL;
	mread(&m1_first);
	mread(&m2_first);
	printf("b transpose:\n");
	mwrite(mtranspose(m2_first));
	printf("a * b transpose:\n");
	mwrite(mmult(m1_first, mtranspose(m2_first)));
	return 0;
}
element *insert(element **first, element *x, int row, int column, int value){
	element *temp;
	MALLOC(temp, sizeof(element));
	temp->row = row;
	temp->column = column;
	temp->value = value;
	if(*first != NULL){
		temp->next = x->next;
		x->next = temp;
		return temp;
	}
	else{
		temp->next = NULL;
		*first = temp;
		return temp;
	}
}
void mwrite(element *ptr){
	if(ptr != NULL){
		printf("numRows = %d, numCols = %d\nThe matrix by row, column and value:\n", ptr->row, ptr->column);
		ptr = ptr->next;
		while(ptr != NULL){
			printf("%d %d %d\n", ptr->row, ptr->column, ptr->value);
			ptr = ptr->next;
		}
	}
	else printf("null matrix\n");
}
void mread(element **first){
	int nonzero, row, column, value, rowTerm, columnTerm;
	element *ptr;
	printf("Input matrix\n");
	scanf("%d %d %d", &rowTerm, &columnTerm, &nonzero);
	ptr = insert(first, NULL, rowTerm, columnTerm, nonzero);
	while(nonzero != 0){
		scanf("%d %d %d", &row, &column, &value);
		if(row > rowTerm-1 || column > columnTerm-1 || row < 0 || column < 0){
			printf("exceed matrix's range, try again\n");
			continue;
		}
		insert(first, ptr, row, column, value);
		ptr = ptr->next;
		nonzero--;
	}
	rearrange(*first);
}
element *mtranspose(element *first){
	element *temp = NULL, *ptr, *ptr_t;
	ptr = first;
	insert(&temp, NULL, ptr->column, ptr->row, ptr->value);
	ptr = ptr->next;
	ptr_t = temp;
	while(ptr != NULL){
		insert(&temp, ptr_t, ptr->column, ptr->row, ptr->value);
		ptr = ptr->next;
		ptr_t = ptr_t->next;
	}
	rearrange(temp);
	return temp;
}
void rearrange(element *first){
	int row = first->row;
	element *rowPtr[row];
	for(int i = 0; i < row; ++i)
		rowPtr[i] = NULL;
	/*rearrange*/
	element *p1 = first;
	element *p2 = first->next;
	element *temp;
	while(p2 != NULL){
		p1->next = p2->next;
		if(rowPtr[p2->row] == NULL){
			rowPtr[p2->row] = p2;
			p2->next = NULL;
		}
		else{ 
			temp = rowPtr[p2->row];
			if(p2->column < temp->column){
				p2->next = temp;
				rowPtr[p2->row] = p2;
			}
			else{
				if(temp->next != NULL){
					while(temp->next->column < p2->column){
						temp = temp->next;
						if(temp->next == NULL)
							break;
					}
				}
				p2->next = temp->next;
				temp->next = p2;
			}
		}
		p2 = p1->next;                                                                                                                 
	}
	/*recombination*/
	p1->next = rowPtr[0];
	for(int i = 0; i < row-1; ++i){
		if(rowPtr[i] == NULL)
			continue;
		temp = rowPtr[i];
		while(temp->next != NULL){
			temp = temp->next;
		}
		while(i < row-1 && rowPtr[i+1] == NULL)
			i++;
		temp->next = rowPtr[i+1];
	}
}
void clear(element **first){
	element *p1 = *first, *p2 = (*first)->next;
	while(p2 != NULL){
		free(p1);
		p1 = p2;
		p2 = p2->next;
	}free(p1);
	*first = NULL;
}
bool isEmpty(element *first){
	if(first == NULL)
		return true;
	else return false;
}
element *mmult(element *m1, element *m2){
	if(isEmpty(m1) || isEmpty(m2)){
		printf("Both matrices must not be empty\n");
		exit(1);
	}
	if(m1->column != m2->row){
		printf("matrices dimensions must agree\n");
		exit(1);
	}
	element *result = NULL, *ptr, *m2_trans = mtranspose(m2), *m1_p, *m2_p;
	insert(&result, NULL, m1->row, m2->column, 0);
	ptr = result;
	
	int sum[result->row][result->column], nonzero = 0;
	for(int i = 0; i < result->row; ++i)
		for(int j = 0; j < result->column; j++)
			sum[i][j] = 0;
	m1_p = m1->next;
	m2_p = m2_trans->next;

	for(; m1_p != NULL; m1_p = m1_p->next){
		for(m2_p = m2_trans->next; m2_p != NULL; m2_p = m2_p->next){
			if(m1_p->column == m2_p->column)
				sum[m1_p->row][m2_p->row] += m1_p->value * m2_p->value;
		}
	}
	for(int i = 0; i < result->row; i++){
		for(int j = 0; j < result->column; j++){
			if(sum[i][j] != 0){
				insert(&result, ptr, i, j, sum[i][j]);
				nonzero++;
			}
		}
	}result->value = nonzero;
	rearrange(result);
	return result;
}
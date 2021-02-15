#include<stdio.h>
#include "list.h"

STRUCT_LIST(int, ListInt)

int main(int argc, char* argv){
	ListInt* list = ListInt_new();
	
	int next = 1;
	//loop until user enters 0 or something that isn't a number
	printf("Enter numbers(0 to finish): ");
	while (next) {
		if (scanf(" %d", &next) != 1) break;
		ListInt_add(list, next);
	}
	
	printf("List: ");
	for (int i = 0; i < ListInt_size(list); i++){
		printf("%d ", ListInt_get(list, i));
	}
	printf("\n");
	
	return 0;
}
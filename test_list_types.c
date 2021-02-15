#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list_types.h"

STRUCT_LIST(int, List_name)
//STRUCT_LIST(int, ListInt)
//STRUCT_LIST(char, ListChar)

void printList(const List_name* list);
void printIntList(const ListInt* list);
void printCharList(const ListChar* list);

int main(int argc, char* argv[]){
	ListInt* listi = ListInt_new();
	printf("Creation ");
	printIntList(listi);
	printf("\n");
	
	ListInt_delete(listi);
	listi = NULL;
	printf("Deleted ");
	printIntList(listi);
	printf("\n");
	
	ListChar* listc = ListChar_newa("Hello", 5);
	printf("Creation ");
	printCharList(listc);
	printf("\n");
	
	ListChar_delete(listc);
	listc = NULL;
	printf("Deleted ");
	printCharList(listc);
	printf("\n");
	
	
	
	//copy of TestList.c main
	List_name* list = List_name_news(10);
	printf("Start ");
	printList(list);
	printf("\n");
	
	for (int i = 0; i < DEFAULT_SIZE; i++){
		List_name_add(list, i + 5);
	}
	printf("Add 5-12 ");
	printList(list);
	printf("\n");
	
	List_name_add(list, 10);
	printf("Add 10 ");
	printList(list);
	printf("\n");
	
	List_name_insert(list, 1, 2);
	List_name_insert(list, 2, 4);
	List_name_insert(list, 3, 6);
	List_name_insert(list, 4, 8);
	List_name_insert(list, 0, 10);
	List_name_insert(list, 1, 2);
	List_name_insert(list, 1, 2);
	List_name_insert(list, 1, 2);
	List_name_insert(list, 1, 2);
	List_name_insert(list, 8, 0);
	printf("Insert ");
	printList(list);
	printf("\n");
	
	*List_name_at(list, 2) = 4;
	*List_name_at(list, 3) = *List_name_at(list, 0);
	*List_name_at(list, 4) = 4;
	List_name_set(list, List_name_get(list, 17), 0);
	printf("At, Get, Set ");
	printList(list);
	printf("\n");
	
	List_name_enlarge(list);
	List_name_enlarge(list);
	printf("Enlarge ");
	printList(list);
	printf("\n");
	
	List_name_remove_last(list);
	List_name_remove_last(list);
	List_name_remove(list, 0);
	List_name_remove(list, 14);
	List_name_remove(list, 3);
	printf("Remove ");
	printList(list);
	printf("\n");
	
	List_name* listCopy = List_name_newa(list->_arr, list->_size);
	printf("Copy ");
	printList(listCopy);
	printf("\n");
	
	int* arr = List_name_toNewArray(list);
	size_t arrSize = List_name_size(list);
	for (int i = 0; i < arrSize; i++){
		printf(" %d", arr[i]);
	}
	printf("\n");
	
	#define N 10
	int arr2[N];
	List_name_toArray(list, arr2, N);
	for (int i = 0; i < N; i++){
		printf(" %d", arr2[i]);
	}
	printf("\n");
	
	List_name_delete(list);
	list = NULL;
	printf("Deleted ");
	printList(list);
	printf("\n");
	
	List_name_delete(listCopy);
	listCopy = NULL;
	printf("Deleted ");
	printList(listCopy);
	printf("\n");
	
	list = List_name_newa(arr2 + 3, 3);
	printf("Create ");
	printList(list);
	printf("\n");
	
	List_name_addArray(list, arr, arrSize);
	printf("Add Array ");
	printList(list);
	printf("\n");
	
	int arrTemp[] = {20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40};
	List_name_insertArray(list, arrTemp, 21, 3);
	printf("Insert Array ");
	printList(list);
	printf("\n");
	
	List_name_delete(list);
	list = NULL;
	printf("Deleted ");
	printList(list);
	printf("\n");
	
	free(arr);
	
}

/* Print list to stdout
 * list: A pointer to the list */
void printCharList(const ListChar* list){
	if (!list) {
		printf("List: NULL\n");
		return;
	}
	
	printf("List:\n\t");
	printf("_arr: ");
	for (int i = 0; i < list->_size; i++){
		printf("%c ", list->_arr[i]);
	}
	printf("\n\t");
	printf("_size:\t%d\n\t", list->_size);
	printf("_maxSize:\t%d\n", list->_maxSize);
}

/* Print list to stdout
 * list: A pointer to the list */
void printList(const List_name* list){
	if (!list) {
		printf("List: NULL\n");
		return;
	}
	
	printf("List:\n\t");
	printf("_arr: ");
	for (int i = 0; i < list->_size; i++){
		printf("%d ", list->_arr[i]);
	}
	printf("\n\t");
	printf("_size:\t%d\n\t", list->_size);
	printf("_maxSize:\t%d\n", list->_maxSize);
}

/* Print list to stdout
 * list: A pointer to the list */
void printIntList(const ListInt* list){
	if (!list) {
		printf("List: NULL\n");
		return;
	}
	
	printf("List:\n\t");
	printf("_arr: ");
	for (int i = 0; i < list->_size; i++){
		printf("%d ", list->_arr[i]);
	}
	printf("\n\t");
	printf("_size:\t%d\n\t", list->_size);
	printf("_maxSize:\t%d\n", list->_maxSize);
}
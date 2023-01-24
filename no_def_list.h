#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>


typedef int type;

#ifndef __LIST_name__
#define __LIST_name__

#define DEFAULT_SIZE 8

typedef struct List_name {
	type* _arr;
	size_t _size;
	size_t _maxSize;
} List_name;

/* Initializes a list.
 *   Will not free memory! If the list is already initialized, free before calling
 * list: The pointer to the list
 * size: The initial size of the list*/
void List_name_init(List_name* list, size_t size){
	list->_arr = (type*)malloc(size * sizeof(type));
	if (!list->_arr){
		fprintf(stderr, "Error at List_name_init: malloc returned NULL\n");
		exit(EXIT_FAILURE);
	}
	list->_size = 0;
	list->_maxSize = size;
}
/* Create a new list with a given size
 *   The list can be of bigger size, but never smaller
 * Returns: A new(malloc'd) list
 * size: The initial size of the list*/
List_name* List_name_news(size_t size){
	List_name* list = (List_name*)malloc(sizeof(List_name));
	if (!list){
		fprintf(stderr, "Error at List_name_news: malloc returned NULL\n");
		exit(EXIT_FAILURE);
	}
	List_name_init(list, size);
	return list;
}
/* Create a new list from an array
 *   The list can be of bigger size, but never smaller
 * Returns: A new(malloc'd) list initialized to a copy of 'arr'
 * arr: A pointer to an array to initialize the list with
 * size: The size of the array, or how many elements to copy*/
List_name* List_name_newa(const type* arr, size_t size){
	//find the next 2^n after 'size'
	size_t nextSize = 2;
	size_t temp = size;
	while (temp /= 2) nextSize *= 2;
	
	List_name* list = List_name_news(nextSize);
	memcpy(list->_arr, arr, size * sizeof(type));
	list->_size = size;
	return list;
}
/* Create a new list with the default size(See 'DEFAULT_SIZE')
 * Returns: A new(malloc'd) list*/
List_name* List_name_new(){
	return List_name_news(DEFAULT_SIZE);
}
/* Returns the amount of elements in the array
 * Returns: The size of the array
 * list: The pointer to the list*/
size_t List_name_size(List_name* list){ return list->_size; }
/* Returns the size of the array, the maximum amount of elements the list can store before resizing
 * Returns: The maximum size of the array
 * list: The pointer to the list*/
size_t List_name_maxSize(List_name* list){ return list->_maxSize; }
/* Returns the internal array pointer of a list
 * Returns: A pointer to the list's array
 * list: The pointer to the list*/
type* List_name_getArrayPtr(List_name* list){ return list->_arr;}
/* Returns a pointer to an element at a given index
 * Returns: A pointer to the element at 'index'
 * list: The pointer to the list
 * index: The index of the element to return*/
type* List_name_at(List_name* list, size_t index){
	if (index >= list->_size){
		fprintf(stderr, "Error at List_name_at: index(%d) is out of bounds(%d)\n",
			index, list->_size);
		exit(EXIT_FAILURE);
		return NULL;
	}
	return list->_arr + index; // = &list->_arr[index]
}
/* Returns an element at a given index
 * Returns: The element at 'index'
 * list: The pointer to the list
 * index: The index of the element to return*/
type List_name_get(const List_name* list, size_t index){
	if (index >= list->_size){
		fprintf(stderr, "Error at List_name_get: index(%d) is out of bounds(%d)\n",
			index, list->_size);
		exit(EXIT_FAILURE);
	}
	return list->_arr[index];
}
/* Sets an element at a given index
 * list: The pointer to the list
 * element: The element to place at 'index'
 * index: The index of the element to set*/
void List_name_set(List_name* list, type element, size_t index){
	if (index >= list->_size){
		fprintf(stderr, "Error at List_name_set: index(%d) is out of bounds(%d)\n",
			index, list->_size);
		exit(EXIT_FAILURE);
		return;
	}
	list->_arr[index] = element;
}
/* Enlarge the maximum size of the list if it's full enough
 *   This implementation doubles the list's size if the list is more than half-full.
 * list: The pointer to the list*/
void List_name_enlarge(List_name* list){
	//if list is less then half full, don't enlarge
	if (list->_size * 2 < list->_maxSize) return;
	list->_maxSize *= 2;
	
	type* newArr = (type*)malloc(sizeof(type) * list->_maxSize);
	if (!newArr){
		fprintf(stderr, "Error at List_name_enlarge: malloc returned NULL\n");
		exit(EXIT_FAILURE);
	}
	memcpy(newArr, list->_arr, list->_size * sizeof(type));
	
	
	free(list->_arr);
	list->_arr = newArr;
}
/* Adds an element to the end of the list
 * list: The pointer to the list
 * element: The element to add to the list*/
void List_name_add(List_name* list, type element){
	if (list->_size == list->_maxSize) List_name_enlarge(list);
	list->_arr[list->_size++] = element;
}
/* Copies an array to the end of the list
 * list: The pointer to the list
 * arr: The array to copy to the end of the list
 * size: The size of the array, or the amount of elements to copy*/
void List_name_addArray(List_name* list, const type* arr, size_t size){
	size_t totalSize = list->_size + size;
	if (totalSize >= list->_maxSize){
		while (totalSize >= list->_maxSize) list->_maxSize *= 2;
		
		type* newArr = (type*)malloc(sizeof(type) * list->_maxSize);
		if (!newArr){
			fprintf(stderr, "Error at List_name_addAray: malloc returned NULL\n");
			exit(EXIT_FAILURE);
		}
		memcpy(newArr, list->_arr, list->_size * sizeof(type));
		
		free(list->_arr);
		list->_arr = newArr;
	}
	
	memcpy(list->_arr + list->_size, arr, size * sizeof(type));
	list->_size += size;
}
/* Removes an element at a given index
 * list: The pointer to the list
 * index: The index of the element to remove*/
void List_name_remove(List_name* list, size_t index){
	if (index >= list->_size){
		fprintf(stderr, "Error at List_name_remove: index(%d) is out of bounds(%d)\n",
			index, list->_size);
		exit(EXIT_FAILURE);
		return;
	}
	if (!list->_size) return;
	for(int i = index; i < list->_size - 1; i++){
		list->_arr[i] = list->_arr[i + 1];
	}
	list->_size--;
}
/* Removes the last element from the list
 * list: The pointer to the list */
void List_name_remove_last(List_name* list){
	if (list->_size) list->_size--;
}
/* Inserts an element to a given index in the list
 * list: The pointer to the list
 * element: The element to insert to the list
 * index: The index of the element to insert*/
void List_name_insert(List_name* list, type element, size_t index){
	if (index > list->_size){ //insert at _size is allowed, same as List_name_add
		fprintf(stderr, "Error at List_name_insert: index(%d) is out of bounds(%d)\n",
			index, list->_size);
		exit(EXIT_FAILURE);
		return;
	}
	int enlarge = list->_size == list->_maxSize;
	type* dest = list->_arr;
	
	if (enlarge){
		list->_maxSize *= 2;
		dest = (type*)malloc(sizeof(type)*list->_maxSize);
		if (!dest){
			fprintf(stderr, "Error at List_name_insert: malloc returned NULL\n");
			exit(EXIT_FAILURE);
		}
		memcpy(dest, list->_arr, sizeof(type)*index);
	}
	
	for(int i = list->_size; i > index; i--) {
		dest[i] = list->_arr[i - 1];
	}
	dest[index] = element;
	list->_size++;
	
	if (enlarge){
		free(list->_arr);
		list->_arr = dest;
	}
}
/* Copies an array to a given index in the list
 * list: The pointer to the list
 * arr: The array to copy to the list
 * size: The size of the array, or the amount of elements to copy
 * index: The index at which to copy the array to*/
void List_name_insertArray(List_name* list, const type* arr, size_t size, size_t index){
	if (index > list->_size){ //insert at _size is allowed, same as List_name_add
		fprintf(stderr, "Error at List_name_insertArray: index(%d) is out of bounds(%d)\n",
			index, list->_size);
		exit(EXIT_FAILURE);
		return;
	}
	
	size_t totalSize = list->_size + size;
	int enlarge = totalSize >= list->_maxSize;
	type* dest = list->_arr;
	if (enlarge){
		while (totalSize >= list->_maxSize) list->_maxSize *= 2;
		
		dest = (type*)malloc(sizeof(type) * list->_maxSize);
		if (!dest){
			fprintf(stderr, "Error at List_name_insertArray: malloc returned NULL\n");
			exit(EXIT_FAILURE);
		}
		memcpy(dest, list->_arr, index * sizeof(type));
	}
	
	memmove(dest + index + size, list->_arr + index, (list->_size - index) * sizeof(type));
	memcpy(dest + index, arr, size * sizeof(type));
	list->_size += size;
	
	if (enlarge) {
		free(list->_arr);
		list->_arr = dest;
	}
}
/* Copies contents of the list into an array.
 * Returns: The array 'arr'
 * list: The pointer to the list
 * arr: A pointer to an array to copy the list into
 * size: The size of the array, or the amount of elements to copy */
type* List_name_toArray(const List_name* list, type* arr, size_t size){
	if (list->_size < size) size = list->_size;
	memcpy(arr, list->_arr, size * sizeof(type));
	return arr;
}
/* Copies contents of the list into a new array.
 * Returns: A new allocated array, with the same size as the list
 * list: The pointer to the list*/
type* List_name_toNewArray(const List_name* list){
	type* array = (type*)malloc(list->_size * sizeof(type));
	return List_name_toArray(list, array, list->_size);
}
/* Free all the memory used by the list.
 *   Do not call with lists that aren't malloc'd! Call `free(list->_arr)` instead
 * list: The pointer to the list*/
void List_name_delete(List_name* list){
	free(list->_arr);
	list->_arr = NULL;
	free(list);
}

#endif
#ifndef __LIST_H__
#define __LIST_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DEFAULT_SIZE 8

/* ========================= DECLARATIONS ========================= */

#define List_struct_declare(List_name) typedef struct List_name List_name;

#define List_new_declare(List_name, type) \
/** \
 * Create a new list with the default size(See 'DEFAULT_SIZE'). \
 * @return A new(malloc'd) list. \
*/ \
List_name* List_name##_new();

#define List_news_declare(List_name) \
/** \
 * Create a new list with a given size. \
 * The list can be of bigger size, but never smaller. \
 * @param size The initial size of the list. \
 * @return A new(malloc'd) list. \
*/ \
List_name* List_name##_news(size_t size);

#define List_newa_declare(List_name, type) \
/** \
 * Create a new list from an array. \
 * The list can be of bigger size, but never smaller. \
 * @param arr A pointer to an array to initialize the list with. \
 * @param size The size of the array, or how many elements to copy. \
 * @return A new(malloc'd) list initialized to a copy of 'arr'. \
*/ \
List_name* List_name##_newa(const type* arr, size_t size);

#define List_init_declare(List_name) \
/** \
 * Initializes a list. \
 * @note not free memory! If the list is already initialized, free before calling. \
 * @param list The pointer to the list. \
 * @param size The initial size of the list. \
*/ \
void List_name##_init(List_name* list, size_t size);

#define List_size_declare(List_name) \
/** \
 * Returns the amount of elements in the array. \
 * @param list The pointer to the list. \
 * @returns The size of the array. \
*/ \
size_t List_name##_size(List_name* list);

#define List_maxSize_declare(List_name) \
/** \
 * Returns the size of the array, the maximum amount of elements the list can store before resizing. \
 * @param list The pointer to the list. \
 * @return The maximum size of the array. \
*/ \
size_t List_name##_maxSize(List_name* list);

#define List_getArrayPtr_declare(List_name, type) \
/** \
 * Returns the internal array pointer of a list. \
 * @param list The pointer to the list. \
 * @return A pointer to the list's array. \
*/ \
type* List_name##_getArrayPtr(List_name* list);

#define List_at_declare(List_name, type) \
/** \
 * Returns a pointer to an element at a given index. \
 * @param list The pointer to the list. \
 * @param index The index of the element to return. \
 * @return A pointer to the element at 'index'. \
*/ \
type* List_name##_at(List_name* list, size_t index);

#define List_get_declare(List_name, type) \
/** \
 * Returns an element at a given index. \
 * @param list The pointer to the list. \
 * @param index The index of the element to return. \
 * @return The element at 'index'. \
*/ \
type List_name##_get(const List_name* list, size_t index);

#define List_set_declare(List_name, type) \
/** \
 * Sets an element at a given index. \
 * @param list The pointer to the list. \
 * @param element The element to place at 'index'. \
 * @param index The index of the element to set. \
*/ \
void List_name##_set(List_name* list, type element, size_t index);

#define List_enlarge_declare(List_name) \
/** \
 * Enlarge the maximum size of the list if it's full enough. \
 * This implementation doubles the list's size if the list is more than half-full. \
 * @param list The pointer to the list. \
*/ \
void List_name##_enlarge(List_name* list);

#define List_add_declare(List_name, type) \
/** \
 * Adds an element to the end of the list. \
 * @param list The pointer to the list. \
 * @param element The element to add to the list. \
*/ \
void List_name##_add(List_name* list, type element);

#define List_addArray_declare(List_name, type) \
/** \
 * Copies an array to the end of the list. \
 * @param list The pointer to the list. \
 * @param arr The array to copy to the end of the list. \
 * @param size The size of the array, or the amount of elements to copy. \
*/ \
void List_name##_addArray(List_name* list, const type* arr, size_t size);

#define List_remove_declare(List_name) \
/** \
 * Removes an element at a given index. \
 * @param list The pointer to the list. \
 * @param index The index of the element to remove. \
*/ \
void List_name##_remove(List_name* list, size_t index);

#define List_remove_last_declare(List_name) \
/** \
 * Removes the last element from the list. \
 * @param list The pointer to the list . \
*/ \
void List_name##_remove_last(List_name* list);

#define List_insert_declare(List_name, type) \
/** \
 * Inserts an element to a given index in the list. \
 * @param list The pointer to the list. \
 * @param element The element to insert to the list. \
 * @param index The index of the element to insert. \
*/ \
void List_name##_insert(List_name* list, type element, size_t index);

#define List_insertArray_declare(List_name, type) \
/** \
 * Copies an array to a given index in the list. \
 * @param list The pointer to the list. \
 * @param arr The array to copy to the list. \
 * @param size The size of the array, or the amount of elements to copy. \
 * @param index The index at which to copy the array to. \
*/ \
void List_name##_insertArray(List_name* list, const type* arr, size_t size, size_t index);

#define List_toArray_declare(List_name, type) \
/** \
 * Copies contents of the list into an array. \
 * @param list The pointer to the list. \
 * @param arr A pointer to an array to copy the list into. \
 * @param size The size of the array, or the amount of elements to copy . \
 * @return The array 'arr'. \
*/ \
type* List_name##_toArray(const List_name* list, type* arr, size_t size);

#define List_toNewArray_declare(List_name, type) \
/** \
 * Copies contents of the list into a new array. \
 * @param list The pointer to the list. \
 * @return A new allocated array, with the same size as the list. \
*/ \
type* List_name##_toNewArray(const List_name* list);

#define List_delete_declare(List_name) \
/** \
 * Free all the memory used by the list. \
 * @param list The pointer to the list. \
 * @note Do not call with lists that aren't malloc'd! Call `free(list->_arr)` instead. \
*/ \
void List_name##_delete(List_name* list);


/* ========================= DEFINITIONS ========================= */


#define List_struct_define(List_name, type) \
struct List_name { \
	type* _arr; \
	size_t _size; \
	size_t _maxSize; \
};

#define List_new_define(List_name) \
List_name* List_name##_new() { \
	return List_name##_news(DEFAULT_SIZE); \
}

#define List_news_define(List_name) \
List_name* List_name##_news(size_t size) { \
	List_name* list = (List_name*)malloc(sizeof(List_name)); \
	if (!list){ \
		fprintf(stderr, "Error at List_name##_news: malloc returned NULL\n"); \
		exit(EXIT_FAILURE); \
	} \
	List_name##_init(list, size); \
	return list; \
}

#define List_newa_define(List_name, type) \
List_name* List_name##_newa(const type* arr, size_t size) { \
	/*find the next 2^n after 'size'*/ \
	size_t nextSize = 2; \
	size_t temp = size; \
	while (temp /= 2) nextSize *= 2; \
 \
	List_name* list = List_name##_news(nextSize); \
	memcpy(list->_arr, arr, size * sizeof(type)); \
	list->_size = size; \
	return list; \
}

#define List_init_define(List_name, type) \
void List_name##_init(List_name* list, size_t size) { \
	list->_arr = (type*)malloc(size * sizeof(type)); \
	if (!list->_arr){ \
		fprintf(stderr, "Error at List_name##_init: malloc returned NULL\n"); \
		exit(EXIT_FAILURE); \
	} \
	list->_size = 0; \
	list->_maxSize = size; \
}

#define List_size_define(List_name) \
size_t List_name##_size(List_name* list) { return list->_size; }

#define List_maxSize_define(List_name) \
size_t List_name##_maxSize(List_name* list) { return list->_maxSize; }

#define List_getArrayPtr_define(List_name, type) \
type* List_name##_getArrayPtr(List_name* list) { return list->_arr;}

#define List_at_define(List_name, type) \
type* List_name##_at(List_name* list, size_t index) { \
	if (index >= list->_size){ \
		fprintf(stderr, "Error at List_name##_at: index(%d) is out of bounds(%d)\n", \
			index, list->_size); \
		exit(EXIT_FAILURE); \
		return NULL; \
	} \
	return list->_arr + index; /* = &list->_arr[index]	*/ \
}

#define List_get_define(List_name, type) \
type List_name##_get(const List_name* list, size_t index) { \
	if (index >= list->_size){ \
		fprintf(stderr, "Error at List_name##_get: index(%d) is out of bounds(%d)\n", \
			index, list->_size); \
		exit(EXIT_FAILURE); \
	} \
	return list->_arr[index]; \
}

#define List_set_define(List_name, type) \
void List_name##_set(List_name* list, type element, size_t index) { \
	if (index >= list->_size){ \
		fprintf(stderr, "Error at List_name##_set: index(%d) is out of bounds(%d)\n", \
			index, list->_size); \
		exit(EXIT_FAILURE); \
		return; \
	} \
	list->_arr[index] = element; \
}

#define List_enlarge_define(List_name, type) \
void List_name##_enlarge(List_name* list) { \
	/*if list is less then half full, don't enlarge*/ \
	if (list->_size * 2 < list->_maxSize) return; \
	list->_maxSize *= 2; \
 \
	type* newArr = (type*)malloc(sizeof(type) * list->_maxSize); \
	if (!newArr){ \
		fprintf(stderr, "Error at List_name##_enlarge: malloc returned NULL\n"); \
		exit(EXIT_FAILURE); \
	} \
	memcpy(newArr, list->_arr, list->_size * sizeof(type)); \
 \
 \
	free(list->_arr); \
	list->_arr = newArr; \
}

#define List_add_define(List_name, type) \
void List_name##_add(List_name* list, type element) { \
	if (list->_size == list->_maxSize) List_name##_enlarge(list); \
	list->_arr[list->_size++] = element; \
}

#define List_addArray_define(List_name, type) \
void List_name##_addArray(List_name* list, const type* arr, size_t size) { \
	size_t totalSize = list->_size + size; \
	if (totalSize >= list->_maxSize){ \
		while (totalSize >= list->_maxSize) list->_maxSize *= 2; \
 \
		type* newArr = (type*)malloc(sizeof(type) * list->_maxSize); \
		if (!newArr){ \
			fprintf(stderr, "Error at List_name##_addArray: malloc returned NULL\n"); \
			exit(EXIT_FAILURE); \
		} \
		memcpy(newArr, list->_arr, list->_size * sizeof(type)); \
 \
		free(list->_arr); \
		list->_arr = newArr; \
	} \
 \
	memcpy(list->_arr + list->_size, arr, size * sizeof(type)); \
	list->_size += size; \
}

#define List_remove_define(List_name) \
void List_name##_remove(List_name* list, size_t index) { \
	if (index >= list->_size){ \
		fprintf(stderr, "Error at List_name##_remove: index(%d) is out of bounds(%d)\n", \
			index, list->_size); \
		exit(EXIT_FAILURE); \
		return; \
	} \
	if (!list->_size) return; \
	for(int i = index; i < list->_size - 1; i++){ \
		list->_arr[i] = list->_arr[i + 1]; \
	} \
	list->_size--; \
}

#define List_remove_last_define(List_name) \
void List_name##_remove_last(List_name* list) { \
	if (list->_size) list->_size--; \
}

#define List_insert_define(List_name, type) \
void List_name##_insert(List_name* list, type element, size_t index) { \
	if (index > list->_size){ /*insert at _size is allowed, same as List_name##_add*/ \
		fprintf(stderr, "Error at List_name##_insert: index(%d) is out of bounds(%d)\n", \
			index, list->_size); \
		exit(EXIT_FAILURE); \
		return; \
	} \
	int enlarge = list->_size == list->_maxSize; \
	type* dest = list->_arr; \
 \
	if (enlarge){ \
		list->_maxSize *= 2; \
		dest = (type*)malloc(sizeof(type)*list->_maxSize); \
		if (!dest){ \
			fprintf(stderr, "Error at List_name##_insert: malloc returned NULL\n"); \
			exit(EXIT_FAILURE); \
		} \
		memcpy(dest, list->_arr, sizeof(type)*index); \
	} \
 \
	for(int i = list->_size; i > index; i--) { \
		dest[i] = list->_arr[i - 1]; \
	} \
	dest[index] = element; \
	list->_size++; \
 \
	if (enlarge){ \
		free(list->_arr); \
		list->_arr = dest; \
	} \
}

#define List_insertArray_define(List_name, type) \
void List_name##_insertArray(List_name* list, const type* arr, size_t size, size_t index) { \
	if (index > list->_size){ /*insert at _size is allowed, same as List_name##_add*/ \
		fprintf(stderr, "Error at List_name##_insert: index(%d) is out of bounds(%d)\n", \
			index, list->_size); \
		exit(EXIT_FAILURE); \
		return; \
	} \
 \
	size_t totalSize = list->_size + size; \
	int enlarge = totalSize >= list->_maxSize; \
	type* dest = list->_arr; \
	if (enlarge){ \
		while (totalSize >= list->_maxSize) list->_maxSize *= 2; \
 \
		dest = (type*)malloc(sizeof(type) * list->_maxSize); \
		if (!dest){ \
			fprintf(stderr, "Error at List_name##_insertArray: malloc returned NULL\n"); \
			exit(EXIT_FAILURE); \
		} \
		memcpy(dest, list->_arr, index * sizeof(type)); \
	} \
 \
	memmove(dest + index + size, list->_arr + index, (list->_size - index) * sizeof(type)); \
	memcpy(dest + index, arr, size * sizeof(type)); \
	list->_size += size; \
 \
	if (enlarge) { \
		free(list->_arr); \
		list->_arr = dest; \
	} \
}

#define List_toArray_define(List_name, type) \
type* List_name##_toArray(const List_name* list, type* arr, size_t size) { \
	if (list->_size < size) size = list->_size; \
	memcpy(arr, list->_arr, size * sizeof(type)); \
	return arr; \
}

#define List_toNewArray_define(List_name, type) \
type* List_name##_toNewArray(const List_name* list) { \
	type* array = (type*)malloc(list->_size * sizeof(type)); \
	return List_name##_toArray(list, array, list->_size); \
}

#define List_delete_define(List_name) \
void List_name##_delete(List_name* list) { \
	free(list->_arr); \
	list->_arr = NULL; \
	free(list); \
}


/* ========================= ALL ========================= */


#define List_declare(List_name, type) \
List_struct_declare(List_name) \
List_new_declare(List_name, type) \
List_news_declare(List_name) \
List_newa_declare(List_name, type) \
List_init_declare(List_name) \
List_size_declare(List_name) \
List_maxSize_declare(List_name) \
List_getArrayPtr_declare(List_name, type) \
List_at_declare(List_name, type) \
List_get_declare(List_name, type) \
List_set_declare(List_name, type) \
List_enlarge_declare(List_name) \
List_add_declare(List_name, type) \
List_addArray_declare(List_name, type) \
List_remove_declare(List_name) \
List_remove_last_declare(List_name) \
List_insert_declare(List_name, type) \
List_insertArray_declare(List_name, type) \
List_toArray_declare(List_name, type) \
List_toNewArray_declare(List_name, type) \
List_delete_declare(List_name)

#define List_define(List_name, type) \
List_struct_define(List_name, type) \
List_new_define(List_name) \
List_news_define(List_name) \
List_newa_define(List_name, type) \
List_init_define(List_name, type) \
List_size_define(List_name) \
List_maxSize_define(List_name) \
List_getArrayPtr_define(List_name, type) \
List_at_define(List_name, type) \
List_get_define(List_name, type) \
List_set_define(List_name, type) \
List_enlarge_define(List_name, type) \
List_add_define(List_name, type) \
List_addArray_define(List_name, type) \
List_remove_define(List_name) \
List_remove_last_define(List_name) \
List_insert_define(List_name, type) \
List_insertArray_define(List_name, type) \
List_toArray_define(List_name, type) \
List_toNewArray_define(List_name, type) \
List_delete_define(List_name)

#define STRUCT_LIST(type, List_name) \
List_declare(List_name, type) \
List_define(List_name, type)

#endif
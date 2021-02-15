# list.h
A very cursed generic list for C

## Summary
This is a small header that can generate a list for any data type with a single simple macro: <br>
`STRUCT_LIST(type, List_name)` <br>
type - The data type of the list to generate
List_name - The name to give the list structure
So for example, `STRUCT_LIST(int, ListInt)` will generate a struct and methods for a list of `int`s and the struct's name will be ListInt

## Usage
### Import
Everything needed is in `list.h` file, no prerequisites required, copy file and `#import "list.h"`
### Generate
Write the `STRUCT_LIST(type, List_name)` macro at the top. Since the macro declars and defines the list struct and functions, the macro needs to be above any usage
### Write
The list structure will have the name you gave it in `List_name` and all functions will have it as a prefix, the naming convention is List_name_nameOfMethod.
For example, if the list was decleared as `STRUCT_LIST(char, ListChar)` then a variable decleration would look like: `ListChar* list`
and calling a function would look like: `ListChar_insert(list, value, index)` <br>
All functions, except for `List_name_new()`, `List_name_news(size)`, and `List_name_newa(array, size)` take a list pointer as first argument

## Misc
### list_types.h
A file that generates list definitions for all common data types
### The list structure
The list structure is defined as:
```c
typedef struct List_name{
  type* _arr;
  size_t _size;
  size_t _maxSize;
} List_name;
```
`_arr` - The internal array that holds the list <br>
`_size` - The current size of the array, i.e. how many elements are in the array right now <br>
`_maxSize` - The maximum size of the array, i.e. how many elements can be added before resizing, in other words, capacity <br>
These values should not be changed manually, unless you know what you're doing, but can be viewed without problems, the official way to read them is through
`List_name_size()`, `List_name_maxSize()`, and `List_name_getArrayPtr()`, but they just return them directly so no difference. `_arr` can be changed without caution
between indices 0 and `_size`(exclusively). Since the list is dynamic and resizes itself, storing pointers to the array or elements, will eventually lead to
corrupted or leaked memory. So don't do that.

## Program example
```c
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
```

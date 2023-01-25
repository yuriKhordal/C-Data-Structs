// builder.h - A library for building large strings with lots of concatenations
#ifndef __BUILDER_H__
#define __BUILDER_H__

#include<stddef.h>

#define STRING_BUILDER_DEFAULT_SIZE 16
#define STRING_BUILDER_MINIMAL_SIZE 16

//A structure that holds a growing string buffer
typedef struct StringBuilder{
  char* _buffer;
  size_t _size;
  size_t _capacity;
} StringBuilder;

//Allocates an empty StringBuilder of default size and returns a pointer to it.
StringBuilder* StringBuilder_new();
/*Allocates an empty StringBuilder of specified size and returns a pointer to
 * it. If 'size' is smaller then 'STRING_BUILDER_MINIMAL_SIZE', it will be used
 * instead. */
StringBuilder* StringBuilder_news(size_t size);
/*Allocates a StringBuilder, copies 'n' chars from 'buffer' and returns a
 * pointer to it. */
StringBuilder* StringBuilder_newa(const char* str, size_t n);

//Get the pointer to the string buffer inside of StringBuilder.
char* const StringBuilder_getBuffPtr(const StringBuilder* builder);
/*Get the amount of characters currently in the StringBuilder, excluding null
 * terminator. */
size_t StringBuilder_getSize(const StringBuilder* builder);
//Get the size of the internal buffer.
size_t StringBuilder_getCapacity(const StringBuilder* builder);

/*Get the character at a specific index of the StringBuilder, returns 0 when 
 * index is out of range. */
char StringBuilder_charAt(const StringBuilder* builder, size_t index);
/*Set a character at the specified index of the StringBuilder to a different
 * one.*/
void StringBuilder_set(StringBuilder* builder, char c, size_t index);

//Append 'n' characters from a string to the StringBuilder.
void StringBuilder_append(StringBuilder* builder, const char* str, size_t n);
//Append 'n' characters from a string to the StringBuilder multiple times.
void StringBuilder_appendMultiple(StringBuilder* builder, const char* str,
  size_t n, size_t times);
//Append a characters to the StringBuilder.
void StringBuilder_appendChar(StringBuilder* builder, char c);
//Append a characters to the StringBuilder multiple times.
void StringBuilder_appendChars(StringBuilder* builder, char c, size_t times);

//Insert 'n' characters from a string to the StringBuilder at a specific index.
void StringBuilder_insert(StringBuilder* builder, size_t index, const char* str,
  size_t n);
/*Insert 'n' characters from a string to the StringBuilder at a specific index
 * multiple times. */
void StringBuilder_insertMultiple(StringBuilder* builder, size_t index,
  const char* str, size_t n, size_t times);
//Insert a characters to the StringBuilder at a specific index.
void StringBuilder_insertChar(StringBuilder* builder, size_t index, char c);
//Insert a characters to the StringBuilder at a specific index multiple times.
void StringBuilder_insertChars(StringBuilder* builder, size_t index, char c,
  size_t times);

/*Returns the first occurance of the first 'n' characters of a specified string
 * in the StringBuilder. If no such occurance is found, returns the size of the
 * StringBuilder. */
size_t StringBuilder_indexOf(const StringBuilder* builder, char* str, size_t n);
/*Returns the first occurance of a character in the StringBuilder. If no such
 * occurance is found, returns the size of the StringBuilder. */
size_t StringBuilder_indexOfChar(const StringBuilder* builder, char c);
/*Returns the lasr occurance of the first 'n' characters of a specified string
 * in the StringBuilder. If no such occurance is found, returns the size of the
 * StringBuilder. */
size_t StringBuilder_lastIndexOf(const StringBuilder* builder, char* str,
  size_t n);
/*Returns the last occurance of a character in the StringBuilder. If no such
 * occurance is found, returns the size of the StringBuilder. */
size_t StringBuilder_lastIndexOfChar(const StringBuilder* builder, char c);

/*Replace the first occurance of the first 'n' characters of a specified string
 * from the StringBuilder. */
void StringBuilder_replace(StringBuilder* builder, const char* str, size_t nstr,
  const char* newStr, size_t nnewStr);
/*Replace all occurances of the first 'n' characters of a specified string
 * from the StringBuilder. */
void StringBuilder_replaceAll(StringBuilder* builder, const char* str,
  size_t nstr, const char* newStr, size_t nnewStr);
//Replace the first occurance of a character from the StringBuilder.
void StringBuilder_replaceChar(StringBuilder* builder, char c, char newc);
//Replace all occurances of a character from the StringBuilder.
void StringBuilder_replaceAllChar(StringBuilder* builder, char c, char newc);

/*Remove the first occurance of the first 'n' characters of a string from the
 * StringBuilder. */
void StringBuilder_remove(StringBuilder* builder, const char* str, size_t n);
// Remove the first occurance of a character from the StringBuilder.
void StringBuilder_removeChar(StringBuilder* builder, char chr);
/*Remove all occurances of the first 'n' characters of a string from the
 * StringBuilder. */
void StringBuilder_removeAll(StringBuilder* builder, const char* str, size_t n);
//Remove all occurances of a character from the StringBuilder.
void StringBuilder_removeAllChar(StringBuilder* builder, char chr);
//Remove a character at a specified index from the StringBuilder.
void StringBuilder_removeAt(StringBuilder* builder, size_t index);
/*Remove 'n' characters starting from 'index' from the StringBuilder.
 * If 'n' is too large, simple remove everything starting from 'index'.*/
void StringBuilder_removeRange(StringBuilder* builder, size_t index, size_t n);

/*Allocates a new string, with the same size(not capacity) as the StringBuilder,
 * and copies the internal string buffer into it. */
char* StringBuilder_buildString(const StringBuilder* builder);
/*Allocates a new string, of size 'n', and copies 'n' characters from the
 * specified index of the internal string buffer into it. If 'n' is too large,
 * simply copies until the end of the StringBuilder. The size of the allocated
 * string will still be 'n'.*/
char* StringBuilder_buildSubString(const StringBuilder* builder, size_t index,
  size_t n);

/*Clear the StringBuilder's internal buffer and resets it's size, but does not
 * shrink it, capacity remains the same.*/
void StringBuilder_clear(StringBuilder* builder);

//Free all of the memory used by the list, returns NULL.
StringBuilder* StringBuilder_free(StringBuilder* ptr);

#endif
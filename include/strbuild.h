#ifndef __BUILDER_H__
#define __BUILDER_H__

/**
 * @file strbuild.h
 * @author Yuri Khordal.
 * @brief A library for building large strings with lots of concatenations.
*/

#include<stddef.h>

/**The default size of the buffer if not specified.*/
#define STRING_BUILDER_DEFAULT_SIZE 16
/**The minimum size of the buffer.*/
#define STRING_BUILDER_MINIMAL_SIZE 16

/**A structure that holds a growing string buffer*/
typedef struct StringBuilder{
  /**The buffer that holds the string.*/
  char* _buffer;
  /**The amount of characters in the buffer.*/
  size_t _size;
  /**The current capacity of the buffer.*/
  size_t _capacity;
} StringBuilder;

/**
 * Allocates an empty StringBuilder of default size and returns a pointer to it.
 * @return A pointer to a new StringBuilder.
 * @note Don't forget to free!
*/
StringBuilder* StringBuilder_new();

/**
 * Allocates an empty StringBuilder of specified size and returns a pointer to
 * it. If 'size' is smaller then 'STRING_BUILDER_MINIMAL_SIZE', it will be used
 * instead.
 * @param size The initial size of the string.
 * @return A pointer to a new StringBuilder.
 * @note Don't forget to free!
*/
StringBuilder* StringBuilder_news(size_t size);

/**
 * Allocates a StringBuilder, copies 'n' chars from 'buffer' and returns a
 * pointer to it.
 * @param str The string to copy from.
 * @param n The amount of characters to copy.
 * @return A pointer to a new StringBuilder.
 * @note Don't forget to free!
*/
StringBuilder* StringBuilder_newa(const char* str, size_t n);

/**
 * Get the pointer to the string buffer inside of StringBuilder.
 * @param builder A pointer to the builder.
 * @return A pointer to the internal buffer.
 * @note Don't touch unless you know what you're doing.
*/
char* const StringBuilder_getBuffPtr(const StringBuilder* builder);

/**
 * Get the amount of characters currently in the StringBuilder, excluding null
 * terminator.
 * @param builder A pointer to the builder.
 * @return The size of the string currently in the buffer.
*/
size_t StringBuilder_getSize(const StringBuilder* builder);

/**
 * Get the size of the internal buffer.
 * @param builder A pointer to the builder.
 * @return The size of the internal buffer.
*/
size_t StringBuilder_getCapacity(const StringBuilder* builder);

/**
 * Get the character at a specific index of the StringBuilder, returns 0 if 
 * index is out of range.
 * @param builder A pointer to the builder.
 * @param index The index of the character to get.
 * @return The character at the the given index, or 0 if out of range.
*/
char StringBuilder_charAt(const StringBuilder* builder, size_t index);

/**
 * Set a character at the specified index of the StringBuilder to a different
 * one.
 * @param builder A pointer to the builder.
 * @param c The new character to set.
 * @param index The index of the character to set.
*/
void StringBuilder_set(StringBuilder* builder, char c, size_t index);

/**
 * Append 'n' characters from a string to the StringBuilder.
 * @param builder A pointer to the builder.
 * @param str The string to append.
 * @param n The amount of characters to append.
*/
void StringBuilder_append(StringBuilder* builder, const char* str, size_t n);

/**
 * Append 'n' characters from a string to the StringBuilder multiple times.
 * @param builder A pointer to the builder.
 * @param str The string to append.
 * @param n The amount of characters to append.
 * @param times The amount of times to append the string.
*/
void StringBuilder_appendMultiple(StringBuilder* builder, const char* str,
size_t n, size_t times);

/**
 * Append a characters to the StringBuilder.
 * @param builder A pointer to the builder.
 * @param c The character to append.
*/
void StringBuilder_appendChar(StringBuilder* builder, char c);

/**
 * Append a characters to the StringBuilder multiple times.
 * @param builder A pointer to the builder.
 * @param c The character to append.
 * @param times The amount of times to append the character.
*/
void StringBuilder_appendChars(StringBuilder* builder, char c, size_t times);

/**
 * Insert 'n' characters from a string to the StringBuilder at a specific index.
 * @param builder A pointer to the builder.
 * @param index The position at which to insert the string.
 * @param str The string to insert.
 * @param n The amount of characters to insert.
*/
void StringBuilder_insert(StringBuilder* builder, size_t index, const char* str,
size_t n);

/**
 * Insert 'n' characters from a string to the StringBuilder at a specific index
 * multiple times.
 * @param builder A pointer to the builder.
 * @param index The position at which to insert the string.
 * @param str The string to insert.
 * @param n The amount of characters to insert.
 * @param times The amount of times to insert the string.
*/
void StringBuilder_insertMultiple(StringBuilder* builder, size_t index,
const char* str, size_t n, size_t times);

/**
 * Insert a characters to the StringBuilder at a specific index.
 * @param builder A pointer to the builder.
 * @param index The position at which to insert the character.
 * @param c The character to insert.
*/
void StringBuilder_insertChar(StringBuilder* builder, size_t index, char c);

/**
 * Insert a characters to the StringBuilder at a specific index multiple times.
 * @param builder A pointer to the builder.
 * @param index The position at which to insert the character.
 * @param c The character to insert.
 * @param times The amount of times to insert the character.
*/
void StringBuilder_insertChars(StringBuilder* builder, size_t index, char c,
size_t times);

/**
 * Returns the first occurance of the first 'n' characters of a specified string
 * in the StringBuilder. If no such occurance is found, returns the size of the
 * StringBuilder.
 * @param builder A pointer to the builder.
 * @param str The string to search for.
 * @param n The amount of characters to search for.
 * @return The index of the string in the buffer, or the size of the builder
 * if the string is not in the buffer.
*/
size_t StringBuilder_indexOf(const StringBuilder* builder, char* str, size_t n);

/**
 * Returns the first occurance of a character in the StringBuilder. If no such
 * occurance is found, returns the size of the StringBuilder.
 * @param builder A pointer to the builder.
 * @param c The character to search for.
 * @return The character of the string in the buffer, or the size of the builder
 * if the character is not in the buffer.
*/
size_t StringBuilder_indexOfChar(const StringBuilder* builder, char c);

/**
 * Returns the lasr occurance of the first 'n' characters of a specified string
 * in the StringBuilder. If no such occurance is found, returns the size of the
 * StringBuilder.
 * @param builder A pointer to the builder.
 * @param str The string to search for.
 * @param n The amount of characters to search for.
 * @return The index of the string in the buffer, or the size of the builder
 * if the string is not in the buffer.
*/
size_t StringBuilder_lastIndexOf(const StringBuilder* builder, char* str,
size_t n);

/**
 * Returns the last occurance of a character in the StringBuilder. If no such
 * occurance is found, returns the size of the StringBuilder.
 * @param builder A pointer to the builder.
 * @param c The character to search for.
 * @return The character of the string in the buffer, or the size of the builder
 * if the character is not in the buffer.
*/
size_t StringBuilder_lastIndexOfChar(const StringBuilder* builder, char c);

/**
 * Replace the first occurance of the first 'nstr' characters of a specified
 * string from the StringBuilder with `nnewStr` characters from a another string.
 * @param builder A pointer to the builder.
 * @param str The string to replace.
 * @param nstr The size of the string to replace.
 * @param newStr The new string to replace the original with.
 * @param nnewStr The size of the new string to replace the original with.
*/
void StringBuilder_replace(StringBuilder* builder, const char* str, size_t nstr,
const char* newStr, size_t nnewStr);

/**
 * Replace all occurances of the first 'nstr' characters of a specified
 * string from the StringBuilder with `nnewStr` characters from a another string.
 * @param builder A pointer to the builder.
 * @param str The string to replace.
 * @param nstr The size of the string to replace.
 * @param newStr The new string to replace the original with.
 * @param nnewStr The size of the new string to replace the original with.
*/
void StringBuilder_replaceAll(StringBuilder* builder, const char* str,
size_t nstr, const char* newStr, size_t nnewStr);

/**
 * Replace the first occurance of a character from the StringBuilder.
 * @param builder A pointer to the builder.
 * @param c The character to replace.
 * @param newc The new character to replace the original with.
*/
void StringBuilder_replaceChar(StringBuilder* builder, char c, char newc);

/**
 * Replace all occurances of a character from the StringBuilder.
 * @param builder A pointer to the builder.
 * @param c The character to replace.
 * @param newc The new character to replace the original with.
*/
void StringBuilder_replaceAllChar(StringBuilder* builder, char c, char newc);

/**
 * Remove the first occurance of the first 'n' characters of a string from the
 * StringBuilder.
 * @param builder A pointer to the builder.
 * @param str The string to remove.
 * @param n The size of the string to remove.
*/
void StringBuilder_remove(StringBuilder* builder, const char* str, size_t n);

/**
 * Remove the first occurance of a character from the StringBuilder.
 * @param builder A pointer to the builder.
 * @param chr The character to remove.
*/
void StringBuilder_removeChar(StringBuilder* builder, char chr);

/**
 * Remove all occurances of the first 'n' characters of a string from the
 * StringBuilder.
 * @param builder A pointer to the builder.
 * @param str The string to remove.
 * @param n The size of the string to remove.
*/
void StringBuilder_removeAll(StringBuilder* builder, const char* str, size_t n);

/**
 * Remove all occurances of a character from the StringBuilder.
 * @param builder A pointer to the builder.
 * @param chr The character to remove.
*/
void StringBuilder_removeAllChar(StringBuilder* builder, char chr);

/**
 * Remove a character at a specified index from the StringBuilder.
 * @param builder A pointer to the builder.
 * @param index The index of the character to remove.
*/
void StringBuilder_removeAt(StringBuilder* builder, size_t index);

/**
 * Remove 'n' characters starting from 'index' from the StringBuilder.
 * If 'n' is too large, simple remove everything starting from 'index'.
 * @param builder A pointer to the builder.
 * @param index The index of the range to remove.
 * @param n The amount of characters to remove.
*/
void StringBuilder_removeRange(StringBuilder* builder, size_t index, size_t n);

/**
 * Allocates a new string, with the same size(not capacity) as the StringBuilder,
 * and copies the internal string buffer into it.
 * @param builder A pointer to the builder.
 * @return A pointer to a new string.
 * @note The string is allocated, so don't forget to free.
*/
char* StringBuilder_buildString(const StringBuilder* builder);

/**
 * Allocates a new string, of size 'n', and copies 'n' characters from the
 * specified index of the internal string buffer into it. If 'n' is too large,
 * simply copies until the end of the StringBuilder. The size of the allocated
 * string will still be 'n'.
 * @param builder A pointer to the builder.
 * @param index The index of the substring to return.
 * @param n The size of the substring.
 * @return A pointer to a new string.
 * @note The string is allocated, so don't forget to free.
*/
char* StringBuilder_buildSubString(const StringBuilder* builder, size_t index,
size_t n);

/**
 * Clear the StringBuilder's internal buffer and resets it's size, but does not
 * shrink it, capacity remains the same.
 * @param builder A pointer to the builder.
 */
void StringBuilder_clear(StringBuilder* builder);

/**
 * Free all of the memory used by the list, returns NULL.
 * @param builder A pointer to the builder.
*/
StringBuilder* StringBuilder_free(StringBuilder* ptr);

#endif
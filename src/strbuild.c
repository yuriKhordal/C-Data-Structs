#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "strbuild.h"

void enlarge(StringBuilder* builder);
void enlargeTo(StringBuilder* builder, size_t size);
char* resize(char* buff, size_t cap);

StringBuilder* StringBuilder_new() {
  return StringBuilder_news(STRING_BUILDER_DEFAULT_SIZE);
}

StringBuilder* StringBuilder_news(size_t size) {
  StringBuilder* builder = malloc(sizeof(StringBuilder));
  if (!builder) {
    fprintf(stderr, "Error at StringBuilder_news: Failed allocating a \
StringBuilder pointer.\n");
    fprintf(stderr, "%s\n", strerror(errno));
    return NULL;
  }

  size_t temp = STRING_BUILDER_MINIMAL_SIZE;
  while (temp < size) temp <<= 1;
  size = temp;
  builder->_buffer = calloc(size, sizeof(char));
  if (!builder->_buffer) {
    fprintf(stderr, "Error at StringBuilder_news: Failed allocating \
StringBuilder's char buffer pointer.\n");
    fprintf(stderr, "%s\n", strerror(errno));
    return NULL;
  }

  builder->_size = 0;
  builder->_capacity = size;
}

StringBuilder* StringBuilder_newa(const char* str, size_t n) {
  if (!str) {
    fprintf(stderr, "Error at StringBuilder_newa: argument 'str' is \
NULL.\n");
    return NULL;
  }
  
  StringBuilder* builder = StringBuilder_news(n + 1);
  if (!builder) return NULL; //StringBuilder_news already prints the error

  memcpy(builder->_buffer, str, n);
  builder->_buffer[n] = '\0';
  builder->_size = n;
}


char* const StringBuilder_getBuffPtr(const StringBuilder* builder) {
  return builder->_buffer;
}

size_t StringBuilder_getSize(const StringBuilder* builder) {
  return builder->_size;
}

size_t StringBuilder_getCapacity(const StringBuilder* builder) {
  return builder->_capacity;
}

char StringBuilder_charAt(const StringBuilder* builder, size_t index) {
  if (index >= builder->_size) return 0;
  return builder->_buffer[index];
}

void StringBuilder_set(StringBuilder* builder, char c, size_t index) {
  if (index < builder->_size) builder->_buffer[index] = c;
}


void StringBuilder_append(StringBuilder* builder, const char* str, size_t n) {
  if (!str) {
    fprintf(stderr, "Error at StringBuilder_append: 'str' argument is null\n");
    return;
  }

  // +1 for null terminator.
  if (builder->_size + n + 1 >= builder->_capacity)
    enlargeTo(builder, builder->_size + n + 1);

  /*for (size_t i = 0; i < n; i++)
    builder->_buffer[builder->_size++] = str[i];*/
  memcpy(builder->_buffer + builder->_size, str, sizeof(char) * n);

  builder->_size += n;
}

void StringBuilder_appendMultiple(StringBuilder* builder, const char* str,
    size_t n, size_t times) {
  if (!str) {
    fprintf(stderr, "Error at StringBuilder_appendMultiple: 'str' argument \
is null\n");
    return;
  }

  if (builder->_size + n * times + 1 >= builder->_capacity)
    enlargeTo(builder, builder->_size + n * times + 1);

  /*while (times--) for (size_t i = 0; i < n; i++)
    builder->_buffer[builder->_size++] = str[i];*/
  for (size_t i = 0; i < times; i++)
    memcpy(builder->_buffer + builder->_size + (i * n), str, sizeof(char) * n);
    
  builder->_size += n * times;
}

void StringBuilder_appendChar(StringBuilder* builder, char c) {
  builder->_buffer[builder->_size++] = c;
  if (builder->_size == builder->_capacity) enlarge(builder);
}

void StringBuilder_appendChars(StringBuilder* builder, char c, size_t times) {
  // +1 for null terminator.
  if (builder->_size + times + 1 >= builder->_capacity)
    enlargeTo(builder, builder->_size + times + 1);
  while (times--) builder->_buffer[builder->_size++] = c;
}


void StringBuilder_insert(StringBuilder* builder, size_t index, const char* str,
    size_t n) {
  if (!str) {
    fprintf(stderr, "Error at StringBuilder_insert: 'str' argument is null\n");
    return;
  }
  if (index > builder->_size) return;

  char* src = builder->_buffer;
  char* dest = src;
  size_t cap = builder->_capacity;
  size_t size = builder->_size + 1 + n;
  while (cap < size) cap <<= 1;
  if (cap != builder->_capacity) {
    dest = calloc(cap, sizeof(char));
    //technically index-1 but it's being overwritten anyways
    memcpy(dest, src, sizeof(char) * index);
  }

  //make space for the string, and then copy it to that space
  memmove(dest + index + n, src + index,
    sizeof(char) * (builder->_size - index));
  memcpy(dest + index, str, sizeof(char) * n);

  //free if 'dest' is a new memory block
  if (dest != src){
    free(builder->_buffer);
    builder->_buffer = dest;
    builder->_capacity = cap;
  }
  builder->_size += n;
}

void StringBuilder_insertMultiple(StringBuilder* builder, size_t index,
    const char* str, size_t n, size_t times){
  if (!str) {
    fprintf(stderr, "Error at StringBuilder_insert: 'str' argument is null\n");
    return;
  }
  if (index > builder->_size) return;

  char* src = builder->_buffer;
  char* dest = src;
  size_t cap = builder->_capacity;
  size_t size = builder->_size + 1 + (n * times);
  while (cap < size) cap <<= 1;
  if (cap != builder->_capacity) {
    dest = calloc(cap, sizeof(char));
    //technically index-1 but it's being overwritten anyways
    memcpy(dest, src, sizeof(char) * index);
  }

  //make space for the string and copy it 'times' times to the space
  memmove(dest + index + (n * times), src + index,
    sizeof(char) * (builder->_size - index));
  for (int i = 0; i < times; i++)
    memcpy(dest + index + (i * n), str, sizeof(char) * n);

  //free if 'dest' is a new memory block
  if (dest != src){
    free(builder->_buffer);
    builder->_buffer = dest;
    builder->_capacity = cap;
  }
  builder->_size += n * times;
}

void StringBuilder_insertChar(StringBuilder* builder, size_t index, char c){
  if (index > builder->_size) return;
  
  char prev = c;
  for (;index <= builder->_size; index++){
    char temp = prev;
    prev = builder->_buffer[index];
    builder->_buffer[index] = temp;
  }
  
  if (++builder->_size == builder->_capacity) enlarge(builder);
}

void StringBuilder_insertChars(StringBuilder* builder, size_t index, char c,
    size_t times){
  if (!times) return;
  if (index > builder->_size) return;
  if (builder->_size + times >= builder->_capacity)
    enlargeTo(builder, builder->_size + 1 + times);

  //move the buffer 'times' times to the right
  for (size_t i = builder->_size + times - 1; i >= index + times; i--){
    builder->_buffer[i] = builder->_buffer[i - times];
  }

  //insert the chars
  for (size_t i = 0; i < times; i++) builder->_buffer[index + i] = c;

  builder->_size += times;
}



size_t StringBuilder_indexOf(const StringBuilder* builder, char* str, size_t n) {
  if (!str) {
    fprintf(stderr, "Error at StringBuilder_append: 'str' argument is null\n");
    return builder->_size;
  }

  for (size_t i = 0, stri = 0; i < builder->_size; i++, stri++) {
    if (builder->_buffer[i] != str[stri]) stri = 0;
    if (stri >= n - 1) return i - stri;
  }
  return builder->_size;
}

size_t StringBuilder_indexOfChar(const StringBuilder* builder, char c) {
  for (size_t i = 0; i < builder->_size; i++)
    if (builder->_buffer[i] == c) return i;
  return builder->_size;
}

size_t StringBuilder_lastIndexOf(const StringBuilder* builder, char* str,
    size_t n) {
  if (!str) {
    fprintf(stderr, "Error at StringBuilder_append: 'str' argument is null\n");
    return builder->_size;
  }

  for (size_t i = builder->_size - 1, stri = n - 1;; i--, stri--) {
    if (builder->_buffer[i] != str[stri]) stri = n - 1;
    if (stri == 0) return i;
    if (i == 0) break;
  }
  return builder->_size;
}

size_t StringBuilder_lastIndexOfChar(const StringBuilder* builder, char c) {
  for (int i = builder->_size - 1;; i--) {
    if (builder->_buffer[i] == c) return i;
    if (i == 0) break;
  }
  return builder->_size;
}


void StringBuilder_replace(StringBuilder* builder, const char* str, size_t nstr,
    const char* newStr, size_t nnewStr) {
  if (!str || !newStr) {
    fprintf(stderr, "Error at StringBuilder_replace: 'str' or 'newStr' \
argument is null\n");
    return;
  }

  //divide into oldbuff - the original, and buff - a new buffer to copy to
  char* oldbuff = builder->_buffer;
  size_t cap = builder->_capacity, size = builder->_size - nstr + nnewStr;
  while (cap <= size) cap <<= 1;
  char* buff = calloc(cap, sizeof(char));
  if (!buff) {
    fprintf(stderr, "Error at StringBuilder_replace: Failed allocating \
memory\n");
    fprintf(stderr, "%s\n", strerror(errno));
    return;
  }

  size_t i = builder->_size;
  for (size_t oldi = 0, stri = 0; oldi < builder->_size; oldi++, stri++) {
    if (oldbuff[oldi] != str[stri]) stri = 0;
    if (stri == nstr - 1) {
      i = oldi - stri;
      break;
    }
    buff[oldi] = oldbuff[oldi];
  }

  if (i == builder->_size) {
    free(buff);
    return;
  }

  /*for (size_t stri = 0; stri < nnewStr; stri++, i++)
    buff[i] = newStr[stri];
  for (size_t oldi = i - nnewStr + nstr; oldi < builder->_size; oldi++, i++)
    buff[i] = oldbuff[i];*/
  memmove(buff + i + nnewStr, oldbuff + i + nstr,
    sizeof(char) * (builder->_size - i - nstr));
  memmove(buff + i, newStr, sizeof(char) * nnewStr);
  buff[size] = '\0';

  free(builder->_buffer);
  builder->_buffer = buff;
  builder->_size = size;
  builder->_capacity = cap;
}

void StringBuilder_replaceAll(StringBuilder* builder, const char* str,
    size_t nstr, const char* newStr, size_t nnewStr) {
  if (!str || !newStr) {
    fprintf(stderr, "Error at StringBuilder_replace: 'str' or 'newStr' \
argument is null\n");
    return;
  }

  char* oldbuff = builder->_buffer;
  size_t cap = builder->_capacity;
  char* buff = calloc(cap, sizeof(char));
  if (!buff) {
    fprintf(stderr, "Error at StringBuilder_replace: Failed allocating \
memory\n");
    fprintf(stderr, "%s\n", strerror(errno));
    return;
  }

  size_t i = 0;
  for (size_t oldi = 0, stri = 0; oldi < builder->_size; oldi++, i++) {
    //Found 'str' inside the buffer
    if (stri == nstr) {
      i -= stri;
      if (i + nnewStr + (builder->_size - oldi) >= cap - 1) {
        buff = resize(buff, cap);
        cap <<= 1;
      }
      /*for (stri = 0; stri < nnewStr; stri++, i++)
        buff[i] = newStr[stri];*/
      memmove(buff + i, newStr, sizeof(char) * nnewStr);
      i += nnewStr;
      stri = 0;
    }
    if (oldbuff[oldi] == str[stri]) stri++;
    else stri = 0;
    buff[i] = oldbuff[oldi];
  }
  buff[i] = '\0';

  free(builder->_buffer);
  builder->_buffer = buff;
  builder->_size = i;
  builder->_capacity = cap;
}

void StringBuilder_replaceChar(StringBuilder* builder, char c, char newc) {
  for (size_t i = 0; i < builder->_size; i++)
    if (builder->_buffer[i] == c) {
      builder->_buffer[i] = newc;
      return;
    }
}

void StringBuilder_replaceAllChar(StringBuilder* builder, char c, char newc) {
  for (size_t i = 0; i < builder->_size; i++)
    if (builder->_buffer[i] == c)
      builder->_buffer[i] = newc;
}


void StringBuilder_remove(StringBuilder* builder, const char* str, size_t n) {
  char* buff = builder->_buffer;
  size_t size = builder->_size;

  //search for the string in the buffer
  for (size_t buffi = 0, stri = 0; buffi < size; buffi++) {
    if (stri == n){
      char* dest = buff + buffi - n;
      size -= buffi;
      memmove(dest, dest + n, sizeof(char) * size);
      //update the size and set null terminator
      builder->_size -= n;
      buff[builder->_size] = '\0';
      return;
    }
    if (buff[buffi] == str[stri]) stri++;
    else stri = 0;
  }
}

void StringBuilder_removeChar(StringBuilder* builder, char chr) {
  char* buff = builder->_buffer;
  size_t size = builder->_size;

  //search for the character
  for (size_t i = 0; i < size; i++) if (buff[i] == chr) {
    memmove(buff + i, buff + i + 1, sizeof(char) * (size - i - 1));
    //update the size and set null terminator
    builder->_size--;
    buff[builder->_size] = '\0';
    return;
  }
}

void StringBuilder_removeAll(StringBuilder* builder, const char* str, size_t n) {
  char* buff = builder->_buffer;
  size_t size = builder->_size;
  size_t d = 0; //delta, difference, distance, whatever

  //search for the string in the buffer
  for (size_t buffi = 0, stri = 0; buffi < size - d; buffi++) {
    if (stri == n){
      buffi -= n;
      d += n;
      stri = 0;
    }

    if (d) buff[buffi] = buff[buffi + d];
    
    if (buff[buffi] == str[stri]) stri++;
    else stri = 0;
  }

  //update the size and set null terminator
  if (d){
    builder->_size -= d;
    buff[builder->_size] = '\0';
  }
}

void StringBuilder_removeAllChar(StringBuilder* builder, char chr) {
  char* buff = builder->_buffer;
  size_t size = builder->_size;
  size_t d = 0; //delta, difference, distance, whatever
  
  //search for the character
  for (size_t i = 0; i < size - d; i++){
    if (buff[i + d] == chr) d++;
    if (d) buff[i] = buff[i + d];
  }

  //update the size and set null terminator
  if (d){
    builder->_size -= d;
    buff[builder->_size] = '\0';
  }
}

void StringBuilder_removeAt(StringBuilder* builder, size_t index) {
  StringBuilder_removeRange(builder, index, 1);
}

void StringBuilder_removeRange(StringBuilder* builder, size_t index, size_t n) {
  if (index >= builder->_size || !n) return;
  if (n > builder->_size - index) n = builder->_size - index;
  char* buff = builder->_buffer;
  size_t size = builder->_size - index - n;
  memmove(buff + index, buff + index + n, sizeof(char) * size);

  //update the size and set null terminator
  builder->_size -= n;
  buff[builder->_size] = '\0';
}


char* StringBuilder_buildString(const StringBuilder* builder) {
  char* string = malloc(sizeof(char) * (builder->_size + 1));
  if (!string) {
    fprintf(stderr, "Error at StringBuilder_buildString: Failed allocating \
a string pointer.\n");
    fprintf(stderr, "%s\n", strerror(errno));
    return NULL;
  }

  memcpy(string, builder->_buffer, builder->_size);
  string[builder->_size] = '\0';
  return string;
}

char* StringBuilder_buildSubString(const StringBuilder* builder, size_t index,
    size_t n) {
  if (index >= builder->_size || !n) return NULL;
  char* string = calloc(n + 1, sizeof(char));
  if (n > builder->_size - index) n = builder->_size - index;
  if (!string) {
    fprintf(stderr, "Error at StringBuilder_buildString: Failed allocating \
a string pointer.\n");
    fprintf(stderr, "%s\n", strerror(errno));
    return NULL;
  }
  
  memcpy(string, builder->_buffer + index, n * sizeof(char));
  string[n] = '\0';
  return string;
}


void StringBuilder_clear(StringBuilder* builder) {
  builder->_buffer[0] = '\0';
  builder->_size = 0;
}

StringBuilder* StringBuilder_free(StringBuilder* ptr) {
  if (!ptr) return NULL;
  if (ptr->_buffer) free(ptr->_buffer);
  free(ptr);
  return NULL;
}

//========================================

/*Print the builder as an array of characters in the following format:
 "['H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '\0']"*/
void debugPrint(const StringBuilder* builder){
  printf("StringBuilder{\n");
  printf("\tValue: \"%s\"\n", builder->_buffer);
  printf("\tBuffer: [");
  for (size_t i = 0; i < builder->_capacity; i++){
    if (i) printf(", ");
    char* str;
    switch(builder->_buffer[i]){
      case '\0': str = "'\\0'"; break;
      case '\a': str = "'\\a'"; break;
      case '\b': str = "'\\b'"; break;
      case '\e': str = "'\\e'"; break;
      case '\f': str = "'\\f'"; break;
      case '\n': str = "'\\n'"; break;
      case '\r': str = "'\\r'"; break;
      case '\t': str = "'\\t'"; break;
      case '\v': str = "'\\v'"; break;
      default: str = (char[]){'\'', builder->_buffer[i], '\'', '\0'};
    }
    printf(str);
  }
  printf("]\n");
  printf("\tSize: %zu\n", builder->_size);
  printf("\tCapacity: %zu\n", builder->_capacity);
  printf("}\n");
}

//Increase the StringBuilder's capacity x2.
void enlarge(StringBuilder* builder) {
  size_t cap = builder->_capacity << 1;
  char* buff = realloc(builder->_buffer, (sizeof(char) * cap));
  if (!buff) {
    fprintf(stderr, "Error at enlarge: Failed allocating new buffer.\n");
    fprintf(stderr, "%s\n", strerror(errno));
    free(builder->_buffer);
    return;
  }

  //for (size_t i = builder->_capacity; i < cap; i++) buff[i] = '\0';
  memset(buff + builder->_capacity, '\0', sizeof(char) * builder->_capacity);
  builder->_buffer = buff;
  builder->_capacity = cap;
}

/*Increase the StringBuilder's capacity to the closest(rounding up) power of 2
 * of the specified size(Does *not* shrink). */
void enlargeTo(StringBuilder* builder, size_t size) {
  size_t cap = builder->_capacity;
  while (cap < size) cap <<= 1;
  char* buff = realloc(builder->_buffer, (sizeof(char) * cap));
  if (!buff) {
    fprintf(stderr, "Error at enlarge: Failed allocating new buffer.\n");
    fprintf(stderr, "%s\n", strerror(errno));
    free(builder->_buffer);
    builder->_buffer = NULL;
    return;
  }

  //for (size_t i = builder->_capacity; i < cap; i++) buff[i] = '\0';
  memset(buff + builder->_capacity, '\0',
    sizeof(char) * (cap - builder->_capacity));
  builder->_buffer = buff;
  builder->_capacity = cap;
}

//Return a bigger copy of an array, and free the original.
char* resize(char* buff, size_t cap) {
  char* newBuff = realloc(buff, cap << 1);
  if (!newBuff){
    fprintf(stderr, "Error at StringBuilder_replaceAll: Failed to allocate \
memory.\n");
    fprintf(stderr, "%s\n", strerror(errno));
    return NULL;
  }
  //for (size_t i = cap; i < cap << 1; i++) buff[i] = '\0';
  memset(newBuff + cap, '\0', sizeof(char)*cap);
  return newBuff;
}
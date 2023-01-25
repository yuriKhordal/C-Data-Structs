#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "strbuild.h"

int enlarge(StringBuilder* builder);
int enlargeTo(StringBuilder* builder, size_t size);
char* resize(char* buff, size_t cap);



StringBuilder* StringBuilder_new() {
  return StringBuilder_news(STRING_BUILDER_DEFAULT_SIZE);
}

StringBuilder* StringBuilder_news(size_t size) {
  StringBuilder* builder = malloc(sizeof(StringBuilder));
  if (!builder) return NULL;

  StringBuilder_init(builder, size);
  return builder;
}

StringBuilder* StringBuilder_newa(const char* str, size_t n) {
  if (!str) return NULL;
  
  StringBuilder* builder = StringBuilder_news(n + 1);
  if (!builder) return NULL;

  memcpy(builder->_buffer, str, n);
  builder->_buffer[n] = '\0';
  builder->_size = n;
  return builder;
}

void StringBuilder_init(StringBuilder* builder, size_t size) {
  if (!builder) return;

  size_t temp = STRING_BUILDER_MINIMAL_SIZE;
  // Find the closest power of 2 bigger then size.
  while (temp < size) temp <<= 1;
  size = temp;
  builder->_buffer = calloc(size, sizeof(char));
  if (!builder->_buffer) return NULL;

  builder->_size = 0;
  builder->_capacity = size;
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



DS_codes_t StringBuilder_append(StringBuilder* builder, const char* str) {
  return StringBuilder_nappend(builder, str, strlen(str));
}

DS_codes_t StringBuilder_nappend(StringBuilder* builder,
const char* str, size_t n) {
  if (!str) return ERR_NULL;
  if (n == 0) return DS_SUCCESS;

  // +1 for null terminator.
  if (builder->_size + n + 1 >= builder->_capacity) {
    int res = enlargeTo(builder, builder->_size + n + 1);
    if (res != DS_SUCCESS) return res;
  }

  memcpy(builder->_buffer + builder->_size, str, sizeof(char) * n);

  builder->_size += n;
  return DS_SUCCESS;
}

DS_codes_t StringBuilder_appendMultiple(StringBuilder* builder,
const char* str, size_t times) {
  return StringBuilder_nappendMultiple(builder, str, strlen(str), times);
}

DS_codes_t StringBuilder_nappendMultiple(StringBuilder* builder,
const char* str, size_t n, size_t times) {
  if (!str) return ERR_NULL;
  if (times == 0 || n == 0) return DS_SUCCESS;

  if (builder->_size + n * times + 1 >= builder->_capacity) {
    int res = enlargeTo(builder, builder->_size + n * times + 1);
    if (res != DS_SUCCESS) return res;
  }
  
  for (size_t i = 0; i < times; i++)
    memcpy(builder->_buffer + builder->_size + (i * n), str, sizeof(char) * n);
    
  builder->_size += n * times;
  return DS_SUCCESS;
}

DS_codes_t StringBuilder_appendChar(StringBuilder* builder, char c) {
  builder->_buffer[builder->_size++] = c;
  if (builder->_size == builder->_capacity) {
    int res = enlarge(builder);
    if (res != DS_SUCCESS) return res;
  }
  return DS_SUCCESS;
}

DS_codes_t StringBuilder_appendChars(StringBuilder* builder,
char c, size_t times) {
  if (times == 0) return DS_SUCCESS;

  // +1 for null terminator.
  if (builder->_size + times + 1 >= builder->_capacity) {
    int res = enlargeTo(builder, builder->_size + times + 1);
    if (res != DS_SUCCESS) return res;
  }
  while (times--) builder->_buffer[builder->_size++] = c;
  return DS_SUCCESS;
}



DS_codes_t StringBuilder_insert(StringBuilder* builder,
size_t index, const char* str) {
  return StringBuilder_ninsert(builder, index, str, strlen(str));
}

DS_codes_t StringBuilder_ninsert(StringBuilder* builder,
size_t index, const char* str, size_t n) {
  if (!str) return ERR_NULL;
  if (index > builder->_size) return ERR_OUTOFRANGE;
  if (n == 0) return DS_SUCCESS;

  char* src = builder->_buffer;
  char* dest = src;
  size_t cap = builder->_capacity;
  size_t size = builder->_size + 1 + n;
  while (cap < size) cap <<= 1;
  if (cap > builder->_capacity) {
    dest = calloc(cap, sizeof(char));
    if (!dest) return ERR_MEM;
    // Technically index-1 but it's being overwritten anyways
    memcpy(dest, src, sizeof(char) * index);
  }

  // Make space for the string, and then copy it to that space
  memmove(dest + index + n, src + index,
    sizeof(char) * (builder->_size - index));
  memcpy(dest + index, str, sizeof(char) * n);

  // Free if 'dest' is a new memory block
  if (dest != src){
    free(builder->_buffer);
    builder->_buffer = dest;
    builder->_capacity = cap;
  }
  builder->_size += n;
  return DS_SUCCESS;
}

DS_codes_t StringBuilder_insertMultiple(StringBuilder* builder,
size_t index, const char* str, size_t times) {
  return StringBuilder_ninsertMultiple(builder, index, str, strlen(str), times);
}

DS_codes_t StringBuilder_ninsertMultiple(StringBuilder* builder,
size_t index, const char* str, size_t n, size_t times) {
  if (!str) return ERR_NULL;
  if (index > builder->_size) return ERR_OUTOFRANGE;
  if (times == 0 || n == 0) return DS_SUCCESS;

  char* src = builder->_buffer;
  char* dest = src;
  size_t cap = builder->_capacity;
  size_t size = builder->_size + 1 + (n * times);
  while (cap < size) cap <<= 1;
  if (cap != builder->_capacity) {
    dest = calloc(cap, sizeof(char));
    if (!dest) return ERR_MEM;
    // Technically index-1 but it's being overwritten anyways
    memcpy(dest, src, sizeof(char) * index);
  }

  // Make space for the string and copy it 'times' times to the space
  memmove(dest + index + (n * times), src + index,
    sizeof(char) * (builder->_size - index));
  for (int i = 0; i < times; i++)
    memcpy(dest + index + (i * n), str, sizeof(char) * n);

  // Free if 'dest' is a new memory block
  if (dest != src){
    free(builder->_buffer);
    builder->_buffer = dest;
    builder->_capacity = cap;
  }
  builder->_size += n * times;
  return DS_SUCCESS;
}

// TODO: Change to memmove
DS_codes_t StringBuilder_insertChar(StringBuilder* builder,
size_t index, char c){
  if (index > builder->_size) return ERR_OUTOFRANGE;
  
  char prev = c;
  for (;index <= builder->_size; index++){
    char temp = prev;
    prev = builder->_buffer[index];
    builder->_buffer[index] = temp;
  }
  
  if (++builder->_size == builder->_capacity) {
    int res = enlarge(builder);
    if (res != DS_SUCCESS) return res;
  }
  return DS_SUCCESS;
}

// TODO: Change to memmove
DS_codes_t StringBuilder_insertChars(StringBuilder* builder,
size_t index, char c, size_t times){
  if (index > builder->_size) return ERR_OUTOFRANGE;
  if (times == 0) return DS_SUCCESS;

  if (builder->_size + times >= builder->_capacity) {
    int res = enlargeTo(builder, builder->_size + 1 + times);
    if (res != DS_SUCCESS) return res;
  }

  //move the buffer 'times' times to the right
  for (size_t i = builder->_size + times - 1; i >= index + times; i--){
    builder->_buffer[i] = builder->_buffer[i - times];
  }

  //insert the chars
  for (size_t i = 0; i < times; i++) builder->_buffer[index + i] = c;

  builder->_size += times;
  return DS_SUCCESS;
}



// TODO: see inside.
size_t StringBuilder_indexOf(const StringBuilder* builder, char* str) {
  return StringBuilder_nindexOfFrom(builder, str, strlen(str), 0);
}

size_t StringBuilder_indexOfFrom(const StringBuilder* builder,
char* str, size_t fromIndex) {
  return StringBuilder_nindexOfFrom(builder, str, strlen(str), fromIndex);
}

size_t StringBuilder_nindexOf(const StringBuilder* builder,
char* str, size_t n) {
  return StringBuilder_nindexOfFrom(builder, str, n, 0);
}

size_t StringBuilder_nindexOfFrom(const StringBuilder* builder,
char* str, size_t n, size_t fromIndex) {
  if (!str) return builder->_size;

  // TODO: Potentially skips on strings with duplicates?
  // What happens when searching for "oneonetwo" in "123oneoneonetwothree"?
  for (size_t i = fromIndex, stri = 0; i < builder->_size; i++, stri++) {
    if (builder->_buffer[i] != str[stri]) stri = 0;
    if (stri >= n - 1) return i - stri;
  }
  return builder->_size;
}

size_t StringBuilder_indexOfChar(const StringBuilder* builder, char c) {
  return StringBuilder_indexOfCharFrom(builder, c, 0);
}

size_t StringBuilder_indexOfCharFrom(const StringBuilder* builder,
char c, size_t fromIndex) {
  for (size_t i = fromIndex; i < builder->_size; i++)
    if (builder->_buffer[i] == c) return i;
  return builder->_size;
}

size_t StringBuilder_lastIndexOf(const StringBuilder* builder,
char* str) {
  return StringBuilder_nlastIndexOfFrom(builder, str, strlen(str), builder->_size - 1);
}

size_t StringBuilder_lastIndexOfFrom(const StringBuilder* builder,
char* str, size_t fromIndex) {
  return StringBuilder_nlastIndexOfFrom(builder, str, strlen(str), fromIndex);
}

size_t StringBuilder_nlastIndexOf(const StringBuilder* builder,
char* str, size_t n) {
  return StringBuilder_nlastIndexOfFrom(builder, str, n, builder->_size - 1);
}

size_t StringBuilder_nlastIndexOfFrom(const StringBuilder* builder,
char* str, size_t n, size_t fromIndex) {
  if (!str) return builder->_size;

  for (size_t i = fromIndex, stri = n - 1;; i--, stri--) {
    if (builder->_buffer[i] != str[stri]) stri = n - 1;
    if (stri == 0) return i;
    if (i == 0) break;
  }
  return builder->_size;
}

size_t StringBuilder_lastIndexOfChar(const StringBuilder* builder, char c) {
  return StringBuilder_lastIndexOfCharFrom(builder, c, builder->_size - 1);
}

size_t StringBuilder_lastIndexOfCharFrom(const StringBuilder* builder,
char c, size_t fromIndex) {
  for (int i = fromIndex;; i--) {
    if (builder->_buffer[i] == c) return i;
    if (i == 0) break;
  }
  return builder->_size;
}



DS_codes_t StringBuilder_replace(StringBuilder* builder,
const char* str, const char* newStr) {
  return StringBuilder_nreplace(builder, str, strlen(str), newStr, strlen(newStr));
}

DS_codes_t StringBuilder_nreplace(StringBuilder* builder,
const char* str, size_t nstr, const char* newStr, size_t nnewStr) {
  if (!str || !newStr) return ERR_NULL;
  if (nstr == 0 && nnewStr == 0) return DS_SUCCESS;

  // Divide into oldbuff - the original, and buff - a new buffer to copy to
  char* oldbuff = builder->_buffer;
  size_t cap = builder->_capacity, size = builder->_size - nstr + nnewStr;
  while (cap <= size) cap <<= 1;
  char* buff = calloc(cap, sizeof(char));
  if (!buff) {
    free(buff);
    return ERR_MEM;
  }

  // TODO: Same possible problem as with indexOf.
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
    return DS_SUCCESS;
  }

  memmove(buff + i + nnewStr, oldbuff + i + nstr,
    sizeof(char) * (builder->_size - i - nstr));
  memmove(buff + i, newStr, sizeof(char) * nnewStr);
  buff[size] = '\0';

  free(builder->_buffer);
  builder->_buffer = buff;
  builder->_size = size;
  builder->_capacity = cap;
  return DS_SUCCESS;
}

DS_codes_t StringBuilder_replaceAll(StringBuilder* builder,
const char* str, const char* newStr) {
  return StringBuilder_nreplaceAll(builder, str, strlen(str), newStr, strlen(newStr));
}

DS_codes_t StringBuilder_nreplaceAll(StringBuilder* builder,
const char* str, size_t nstr, const char* newStr, size_t nnewStr) {
  if (!str || !newStr) return ERR_NULL;
  if (nstr == 0 && nnewStr == 0) return DS_SUCCESS;

  char* oldbuff = builder->_buffer;
  size_t cap = builder->_capacity;
  char* buff = calloc(cap, sizeof(char));
  if (!buff) {
    free(buff);
    return ERR_MEM;
  }

  size_t i = 0;
  for (size_t oldi = 0, stri = 0; oldi < builder->_size; oldi++, i++) {
    //Found 'str' inside the buffer
    if (stri == nstr) {
      i -= stri;
      if (i + nnewStr + (builder->_size - oldi) >= cap - 1) {
        char* temp = resize(buff, cap);
        if (!temp) {
          free(buff);
          return ERR_MEM;
        }
        buff = temp;
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
  return DS_SUCCESS;
}

void StringBuilder_replaceChar(StringBuilder* builder, char c, char newc) {
  for (size_t i = 0; i < builder->_size; i++) {
    if (builder->_buffer[i] == c) {
      builder->_buffer[i] = newc;
      return;
    }
  }
}

void StringBuilder_replaceAllChar(StringBuilder* builder, char c, char newc) {
  for (size_t i = 0; i < builder->_size; i++) {
    if (builder->_buffer[i] == c) builder->_buffer[i] = newc;
  }
}



void StringBuilder_remove(StringBuilder* builder, const char* str) {
  StringBuilder_nremove(builder, str, strlen(str));
}

void StringBuilder_nremove(StringBuilder* builder, const char* str, size_t n) {
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

void StringBuilder_removeAll(StringBuilder* builder, const char* str) {
  StringBuilder_nremoveAll(builder, str, strlen(str));
}

void StringBuilder_nremoveAll(StringBuilder* builder, const char* str, size_t n) {
  char* buff = builder->_buffer;
  size_t size = builder->_size;
  size_t d = 0; // delta, difference, distance, whatever

  // Search for the string in the buffer
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

  // Update the size and set null terminator
  if (d){
    builder->_size -= d;
    buff[builder->_size] = '\0';
  }
}

void StringBuilder_removeAllChar(StringBuilder* builder, char chr) {
  char* buff = builder->_buffer;
  size_t size = builder->_size;
  size_t d = 0; // delta, difference, distance, whatever
  
  // Search for the character
  for (size_t i = 0; i < size - d; i++){
    if (buff[i + d] == chr) d++;
    if (d) buff[i] = buff[i + d];
  }

  // Update the size and set null terminator
  if (d){
    builder->_size -= d;
    buff[builder->_size] = '\0';
  }
}

void StringBuilder_removeAt(StringBuilder* builder, size_t index) {
  StringBuilder_removeRange(builder, index, 1);
}

void StringBuilder_removeRange(StringBuilder* builder, size_t index, size_t n) {
  if (index >= builder->_size || n == 0) return;

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
  if (!string) return NULL;

  memcpy(string, builder->_buffer, builder->_size);
  string[builder->_size] = '\0';
  return string;
}

char* StringBuilder_buildSubString(const StringBuilder* builder,
size_t index, size_t n) {
  if (index >= builder->_size || n == 0) return NULL;

  char* string = calloc(n + 1, sizeof(char));
  if (!string) return NULL;
  if (n > builder->_size - index) n = builder->_size - index;
  
  memcpy(string, builder->_buffer + index, n * sizeof(char));
  string[n] = '\0';
  return string;
}



void StringBuilder_clear(StringBuilder* builder) {
  builder->_buffer[0] = '\0';
  builder->_size = 0;
}

void StringBuilder_destroy(StringBuilder* ptr) {
  if (ptr && ptr->_buffer) free(ptr->_buffer);
}

StringBuilder* StringBuilder_free(StringBuilder* ptr) {
  if (!ptr) return NULL;
  StringBuilder_destroy(ptr);
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
int enlarge(StringBuilder* builder) {
  size_t cap = builder->_capacity << 1;
  char* buff = realloc(builder->_buffer, (sizeof(char) * cap));
  if (!buff) return ERR_MEM;

  // Fill the new memory with zeors.
  memset(buff + builder->_capacity, '\0', sizeof(char) * builder->_capacity);
  builder->_buffer = buff;
  builder->_capacity = cap;
  
  return DS_SUCCESS;
}

/*Increase the StringBuilder's capacity to the closest(rounding up) power of 2
 * of the specified size(Does *not* shrink). */
int enlargeTo(StringBuilder* builder, size_t size) {
  size_t cap = builder->_capacity;
  while (cap < size) cap <<= 1;
  char* buff = realloc(builder->_buffer, (sizeof(char) * cap));
  if (!buff) return ERR_MEM;

  // Fill the new memory with zeros.
  memset(buff + builder->_capacity, '\0',
    sizeof(char) * (cap - builder->_capacity));
  builder->_buffer = buff;
  builder->_capacity = cap;

  return DS_SUCCESS;
}

// Return a bigger copy of an array, and free the original.
char* resize(char* buff, size_t cap) {
  char* newBuff = realloc(buff, cap << 1);
  if (!newBuff) {
    return NULL;
  }
  // Fill the new memory with zeros.
  memset(newBuff + cap, '\0', sizeof(char)*cap);
  return newBuff;
}
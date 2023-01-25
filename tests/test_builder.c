#include<stdio.h>
#include<assert.h>
#include "string.h"
#include "builder.h"

#define streq(str1, str2) !strcmp(str1, str2)
#define myassert(expression)  { \
  printf("Asserting line: `%s`: ", #expression); \
  assert(expression); \
  printf("Success!\n"); \
}

extern void debugPrint(const StringBuilder* builder);

void test_getSet();
void test_append();
void test_insert();
void test_index();
void test_replace();
void test_remove();
void test_build();

const char const* str = "Hello, World!";
const char const* longstr = "Hello, World! This is a long Hello to the World!";
const char const* str2 = "str ";

int main(){
  StringBuilder* builder = StringBuilder_newa(str, 13);

  printf("Testing getters and setters: ");
  test_getSet();

  printf("Testing append: ");
  test_append();

  printf("Testing insert: ");
  test_insert();
  
  printf("Testing index: ");
  test_index();
  
  printf("Testing relplace: ");
  test_replace();
  
  printf("Testing remove: ");
  test_remove();
  
  printf("Testing build: ");
  test_build();

  //debugPrint(builder);
  printf("done!\n");
}

void test_getSet(){
  StringBuilder* builder = StringBuilder_newa(str, 13);

  assert(13 == StringBuilder_getSize(builder));
  assert(16 == StringBuilder_getCapacity(builder));

  assert('H' == StringBuilder_charAt(builder, 0));
  assert('W' == StringBuilder_charAt(builder, 7));
  assert('l' == StringBuilder_charAt(builder, 2));

  StringBuilder_set(builder, 'h', 0);
  StringBuilder_set(builder, 'w', 7);
  StringBuilder_set(builder, '.', 12);
  assert(streq(builder->_buffer, "hello, world."));

  StringBuilder_free(builder);
  printf("Success!\n");
}

void test_append(){
  StringBuilder* builder = StringBuilder_new();
  
  StringBuilder_append(builder, str, 13);
  StringBuilder_appendMultiple(builder, str2, 4, 5);

  for (int i = 0; i < 10; i++) StringBuilder_appendChar(builder, '0' + i);

  StringBuilder_appendChars(builder, '!', 3);

  assert(streq("Hello, World!str str str str str 0123456789!!!", builder->_buffer));

  StringBuilder_free(builder);
  printf("Success!\n");
}

void test_insert(){
  StringBuilder* builder = StringBuilder_newa(str, 13);
  
  StringBuilder_insertChar(builder, 5, '1');
  StringBuilder_insertChar(builder, 0, '2');
  StringBuilder_insertChar(builder, 15, '3');
  StringBuilder_insertChar(builder, 20, '4');
  StringBuilder_insertChar(builder, 20, '5');

  assert(streq("2Hello1, World!3", builder->_buffer));
  assert(builder->_size == 16);
  assert(builder->_capacity == 32);
  
  StringBuilder_free(builder);
  builder = StringBuilder_newa(str, 13);
  
  StringBuilder_insertChars(builder, 5, '1', 3);
  StringBuilder_insertChars(builder, 0, '2', 2);
  StringBuilder_insertChars(builder, 15, '3', 4);
  StringBuilder_insertChars(builder, 20, '4', 1);
  StringBuilder_insertChars(builder, 20, '5', 0);

  assert(streq("22Hello111, Wor3333l4d!", builder->_buffer));
  assert(builder->_size == 23);
  assert(builder->_capacity == 32);
  
  StringBuilder_free(builder);
  builder = StringBuilder_newa(str, 13);

  StringBuilder_insert(builder, 5, "123", 3);
  StringBuilder_insert(builder, 16, "4567", 4);
  StringBuilder_insert(builder, 0, "89", 2);

  assert(streq("89Hello123, World!4567", builder->_buffer));
  assert(builder->_size == 22);
  assert(builder->_capacity == 32);
  
  StringBuilder_free(builder);
  builder = StringBuilder_newa(str, 13);

  StringBuilder_insertMultiple(builder, 5, "123", 3, 2);
  StringBuilder_insertMultiple(builder, 0, "456", 3, 3);
  StringBuilder_insertMultiple(builder, 28, "08", 2, 4);

  assert(streq("456456456Hello123123, World!08080808", builder->_buffer));
  assert(builder->_size == 36);
  assert(builder->_capacity == 64);

  // printf("%d/%d: %s\n", builder->_size, builder->_capacity, builder->_buffer);

  StringBuilder_free(builder);
  printf("Success!\n");
}

void test_index(){
  StringBuilder* builder = StringBuilder_newa(longstr, 48);
  
  assert(StringBuilder_indexOfChar(builder, 'l') == 2);
  assert(StringBuilder_lastIndexOfChar(builder, 'l') == 45);
  assert(StringBuilder_indexOfChar(builder, 'Z') == builder->_size);
  assert(StringBuilder_lastIndexOfChar(builder, 'Z') == builder->_size);

  // assert(StringBuilder_charAt(builder,
  //   StringBuilder_indexOfChar(builder, 'l')) == 'l');
  // assert(StringBuilder_charAt(builder,
  //   StringBuilder_lastIndexOfChar(builder, 'l')) == 'l');
  assert(builder->_buffer[StringBuilder_indexOfChar(builder, 'l')] == 'l');
  assert(builder->_buffer[StringBuilder_lastIndexOfChar(builder, 'l')] == 'l');
  
  assert(StringBuilder_indexOf(builder, "Hel", 3) == 0);
  assert(StringBuilder_lastIndexOf(builder, "Hel", 3) == 29);
  assert(StringBuilder_indexOf(builder, "Dad", 3) == builder->_size);
  assert(StringBuilder_lastIndexOf(builder, "Dad", 3) == builder->_size);

  StringBuilder_free(builder);
  printf("Success!\n");
}

void test_replace(){
  StringBuilder* builder = StringBuilder_newa(str, 13);
  
  StringBuilder_replaceChar(builder, 'o', 'O');
  StringBuilder_replaceAllChar(builder, 'l', 'L');

  assert(streq(builder->_buffer, "HeLLO, WorLd!"));
  assert(builder->_size == 13);
  assert(builder->_capacity == 16);

  StringBuilder_free(builder);
  builder = StringBuilder_newa(longstr, 48);

  StringBuilder_replace(builder, "Hello", 5, "Hi", 2);
  StringBuilder_replaceAll(builder, "World", 5, "Za Wardo", 8);

  assert(streq(builder->_buffer, "Hi, Za Wardo! This is a long Hello to the Za Wardo!"));
  assert(builder->_size == 51);
  assert(builder->_capacity == 64);

  StringBuilder_free(builder);
  printf("Success!\n");
}

void test_remove(){
  StringBuilder* builder = StringBuilder_newa(longstr, 48);
  
  StringBuilder_removeChar(builder, ',');
  StringBuilder_removeAllChar(builder, ' ');
  StringBuilder_remove(builder, "Hello", 5);
  StringBuilder_removeAll(builder, "World", 5);
  StringBuilder_removeAt(builder, 22);
  StringBuilder_removeAt(builder, 7);
  StringBuilder_removeAt(builder, 0);
  StringBuilder_removeRange(builder, 15, 2);
  StringBuilder_removeRange(builder, 4, 2);
  
  // printf("%d/%d: %s\n", builder->_size, builder->_capacity, builder->_buffer);

  assert(streq(builder->_buffer, "ThislongHellothe"));
  assert(builder->_size == 16);
  assert(builder->_capacity == 64);

  StringBuilder_free(builder);
  printf("Success!\n");
}

void test_build(){
  StringBuilder* builder = StringBuilder_new();
  
  for (char c = 'a'; c <= 'z'; c++) StringBuilder_appendChar(builder, c);
  StringBuilder_insert(builder, 0, "123", 3);
  StringBuilder_append(builder, "456", 3);

  char* str = StringBuilder_buildString(builder);
  char* sub = StringBuilder_buildSubString(builder, 3, 26);

  assert(streq(str, "123abcdefghijklmnopqrstuvwxyz456"));
  assert(streq(sub, "abcdefghijklmnopqrstuvwxyz"));

  StringBuilder_free(builder);
  printf("Success!\n");
}
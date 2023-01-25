#include<stdio.h>
#include "primes.h"
//#include "no_def_map.h"
#include "hashmap.h"

long long hash(const char **key) {
  long long hash = 0;
  const char *k = *key;
  for (; *k; k++) {
    hash += *k * 31 + 5;
  }
  return hash;
}
bool keycmp(const char **key1, const char **key2) {
  return !strcmp(*key1, *key2);
}

HashMap(MapStringInt, char*, int, long long, hash, keycmp)
HashMap(HashMap_name, char*, int, long long, hash, keycmp)

void primes_test();
void hashmap_test();
void hashmap_forEachTest();
void hashmap_forEachTest2();
void hashmap_print(const HashMap_name *map);

int main(int argc, char const *argv[]) {
  primes_test();
  hashmap_test();
  hashmap_forEachTest();
  hashmap_forEachTest2();
  return 0;
}

void primes_test() {
  for (size_t i = MAX_PRIME - 100; i < MAX_PRIME + 100; i++) {
    if (i % 7 == 0) printf("\n");
    printf("%zd: [%zd]=%zd\t", i, nearest_prime_index(i), nearest_prime(i));
  }
  printf("\n");
}

void hashmap_test() {
  HashMap_name map;
  DS_codes_t code;
  HashMap_name_init(&map, 0);
  printf("Start: "); hashmap_print(&map);

  int val = 10; const char *key = "Ten";
  code = HashMap_name_put(&map, &key, &val);
  printf("code = %d\n", code);

  key = "Twenty"; val = 20;
  code = HashMap_name_put(&map, &key, &val);
  printf("code = %d\n", code);

  key = "Fifteen"; val = 15;
  code = HashMap_name_put(&map, &key, &val);
  printf("code = %d\n", code);

  key = "one"; val = 1;
  code = HashMap_name_put(&map, &key, &val);
  printf("code = %d\n", code);

  key = "twelve"; val = 12;
  code = HashMap_name_put(&map, &key, &val);
  printf("code = %d\n", code);

  key = "three"; val = 3;
  code = HashMap_name_put(&map, &key, &val);
  printf("code = %d\n", code);
  printf("Add numbers: "); hashmap_print(&map);

  key = "nine"; val = 9;
  code = HashMap_name_put(&map, &key, &val);
  printf("code = %d\n", code);
  printf("Add nine: "); hashmap_print(&map);

  key = "Ten";
  code = HashMap_name_remove(&map, &key);
  printf("code = %d\n", code);
  printf("Delete Ten: "); hashmap_print(&map);

  key = "five"; val = 5;
  code = HashMap_name_put(&map, &key, &val);
  printf("code = %d\n", code);
  printf("Add five: "); hashmap_print(&map);

  key = "nine";
  code = HashMap_name_remove(&map, &key);
  printf("code = %d\n", code);
  printf("Delete nine: "); hashmap_print(&map);
  
  key = "one"; val = -6;
  code = HashMap_name_put(&map, &key, &val);
  printf("code = %d\n", code);
  printf("Put one=-6: "); hashmap_print(&map);

  key = "nine";
  printf("has %s = %d\n", key, HashMap_name_has(&map, &key));
  key = "ten";
  printf("has %s = %d\n", key, HashMap_name_has(&map, &key));
  key = "five";
  printf("has %s = %d\n", key, HashMap_name_has(&map, &key));
  key = "bubbles";
  printf("has %s = %d\n", key, HashMap_name_has(&map, &key));
  key = "one";
  printf("has %s = %d\n", key, HashMap_name_has(&map, &key));

  key = "one";
  int one = *HashMap_name_get(&map, &key);
  printf("get %s = %d\n", key, one);
  key = "five";
  int *five = HashMap_name_get(&map, &key);
  printf("get %s = %d\n", key, *five);
  *five = 55;
  key = "Twenty";
  *HashMap_name_get(&map, &key) = 21;
  key = "none";
  printf("get %s = %p\n", key, HashMap_name_get(&map, &key));
  printf("Get: "); hashmap_print(&map);

  
  HashMap_name_clear(&map);
  printf("Clear: "); hashmap_print(&map);

  HashMap_name_destroy(&map);
}

void hashmap_forEachTest() {
  HashMap_name *map = HashMap_name_new();
  HashMap_name_entry_t *entry;
  size_t buck, i=0;
  int val; const char *key;

  hashmap_print(map);

  key = "Age"; val = 23;
  HashMap_name_put(map, &key, &val);
  key = "Year"; val = 1999;
  HashMap_name_put(map, &key, &val);
  key = "Weight"; val = 70;
  HashMap_name_put(map, &key, &val);
  key = "Height"; val = 188;
  HashMap_name_put(map, &key, &val);

  hashmap_print(map);

  map_for_each_entry(map, entry, buck) {
    printf("Bucket %zd Entry %zd {\n", buck, i);
    printf("\tIndex: %zd,\n", i);
    printf("\tKey: \"%s\",\n", entry->key);
    printf("\tHash: %lld,\n", entry->key_hash);
    printf("\tNext: %ld,\n", entry->next);
    printf("\tVal: %d,\n", entry->val);
    printf("}");
    i++;
  }
  HashMap_name_free(map);
}

void hashmap_forEachTest2() {
  HashMap_name map;
  HashMap_name_init(&map, 0);
  int val; const char *key;

  key = "Ten"; val = 10;
  HashMap_name_put(&map, &key, &val);
  key = "Twenty"; val = 20;
  HashMap_name_put(&map, &key, &val);
  key = "Fifteen"; val = 15;
  HashMap_name_put(&map, &key, &val);
  key = "one"; val = 1;
  HashMap_name_put(&map, &key, &val);
  key = "twelve"; val = 12;
  HashMap_name_put(&map, &key, &val);
  key = "three"; val = 3;
  HashMap_name_put(&map, &key, &val);
  key = "nine"; val = 9;
  HashMap_name_put(&map, &key, &val);
  key = "hunder"; val = 100;
  HashMap_name_put(&map, &key, &val);
  key = "thirty"; val = 30;
  HashMap_name_put(&map, &key, &val);
  key = "zero"; val = 0;
  HashMap_name_put(&map, &key, &val);
  key = "Ten";
  HashMap_name_remove(&map, &key);
  key = "five"; val = 5;
  HashMap_name_put(&map, &key, &val);
  key = "nine";
  HashMap_name_remove(&map, &key);
  key = "twelve";
  HashMap_name_remove(&map, &key);

  hashmap_print(&map);

  size_t i;
  HashMap_name_entry_t *entry;
  map_for_each_entry(&map, entry, i) {
    printf("Bucket %zd {\n", i);
    printf("\tKey: \"%s\",\n", entry->key);
    printf("\tHash: %lld,\n", entry->key_hash);
    printf("\tNext: %ld,\n", entry->next);
    printf("\tVal: %d,\n", entry->val);
    printf("} ");
  }

  HashMap_name_destroy(&map);
}

void hashmap_print(const HashMap_name *map) {
  printf("Hash Map:\n");
  printf("\tBuckets: [");
  for (size_t i = 0; i < map->cap ; i++) {
    if (i != 0) printf(",");
    printf(" %ld", map->buckets[i]);
  }
  printf(" ]\n");

  printf("\tEntries: [");
  for (size_t i = 0; i < map->cap ; i++) {
    HashMap_name_entry_t *entry = map->entries + i;
    if (i != 0) printf(", ");
    printf("{\n");
    printf("\t\tIndex: %zd,\n", i);
    printf("\t\tKey: \"%s\",\n", entry->key);
    printf("\t\tHash: %lld,\n", entry->key_hash);
    printf("\t\tNext: %ld,\n", entry->next);
    printf("\t\tVal: %d,\n", entry->val);
    printf("\t}");
  }
  printf("]\n");
  printf("\tNext Empty: %zd\n", map->next_empty);
  printf("\tSize: %zd\n", map->size);
  printf("\tCapacity: %zd\n", map->cap);
}
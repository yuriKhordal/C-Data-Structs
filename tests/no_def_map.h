#ifndef __NO_DEF_MAP_H__
#define __NO_DEF_MAP_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "primes.h"

#define first_entry(map, bucket) \
  ((map)->buckets[(bucket)] != -1 ? &(map)->entries[(map)->buckets[(bucket)]] : NULL)

#define next_entry(map, entry) \
 ((entry)->next != -1 ? &(map)->entries[(entry)->next] : NULL)

#define for_each_entry_in_map(map, entry, bucket) \
  for ((bucket) = 0; (bucket) < (map)->cap; (bucket)++) \
  for((entry) = map_first_entry(map, bucket); (entry) != NULL; (entry) = map_next_entry(map, entry))

#pragma region no_def
typedef char* key__t;
typedef int val_t;
typedef unsigned long long hash_t;
hash_t hash(const key__t *key) {
  hash_t hash = 0;
  char *k = *key;
  for (; *k; k++) {
    hash += *k * 31 + 5;
  }
  return hash;
}
bool keycmp(const key__t *key1, const key__t *key2) {
  return !strcmp(*key1, *key2);
}

/*#ifndef _SSIZE_T_DEFINED
typedef long long ssize_t;
#endif*/
#pragma endregion

// Define ssize_t
#ifdef _MSC_VER
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#else
#include <unistd.h>
#endif

/**Represents function return codes.*/
typedef enum {
  HMP_SET = 2, HMP_ADD = 1,
  DS_SUCCESS = 0,
  ERR_TOOSMALL= -1, ERR_TOOBIG = -3, ERR_MEM = -3,
  ERR_KEYNOTFOUND = -4
} DS_codes_t;

/**A pointer to a function that hashes a key.*/
hash_t (*const HashMap_name_hash)(const key__t*) = &hash;
/**A pointer to a function that compares two keys and returns true if they're equal.*/
bool (*const HashMap_name_keycmp)(const key__t*, const key__t*) = &keycmp;

/**Represents an entry in the hash map.*/
typedef struct {
  /**The key of the entry*/
  const key__t key;
  /**The hash of the key.*/
  const hash_t key_hash;
  /**The index of the next entry in case of hash collisions.*/
  ssize_t next;
  /**The value of the entry.*/
  val_t val;
} HashMap_name_entry_t;

/**Represents a hash map data structure.*/
typedef struct {
  /**The entries of the map, all the Key-Value pairs.*/
  HashMap_name_entry_t *entries;
  /**An array of indices that maps a normalized hash to an entry index.
   * Index -1 means there is no such entry.*/
  ssize_t* buckets;
  /**The amount of entries in the map.*/
  size_t size;
  /**The next empty cell in the entries array.*/
  size_t next_empty;
  /**The maximum capacity of the map.*/
  size_t cap;
} HashMap_name;

/**
 * Allocates a new hash map and returns a pointer to it.
 * @return A pointer to the new hash map. NULL on failure.
 * @note Returns NULL on failed memory allocation.
*/
HashMap_name * HashMap_name_new();
/**
 * Allocates a new hash map with a given initial size and returns a pointer to it.
 * The hash map will have an initial size of at least `size`.
 * @param size The requested initial size for the hash map.
 * @return A pointer to the new hash map. NULL on failure.
 * @note Returns NULL on failed memory allocation.
*/
HashMap_name * HashMap_name_snew(size_t size);
/**
 * Initialize a hash map, if a map struct was made without the new() function,
 * this function will initialize it fully.
 * @param map The map to initialize.
 * @param size The initial size of the map. 0 for default size.
 * @return DS_SUCCESS on successfull initialization, an error code on failure.
 * @note Error codes:
 * ERR_MEM - Memory allocation error.
*/
DS_codes_t HashMap_name_init(HashMap_name *map, size_t size);
/**
 * Adds or overwrites a key value pair to the map.
 * @param map The hash map.
 * @param key The key by which to map the pair.
 * @param value The value to map to the key.
 * @return HMP_ADD if a new pair was added, HMP_SET if the key already exists
 * and it's paired value was overwritten. An error code on failure. Can only
 * while adding a new pair, not when setting.
 * @note Errors: 
 * ERR_MEM - Memory allocation error.
*/
DS_codes_t HashMap_name_put(HashMap_name *map, const key__t *key, const val_t *value);
/**
 * Check if the map has a specified key stored.
 * @param map The hash map.
 * @param key The key to search for.
 * @return True if the key is in the map, false otherwise.
*/
bool HashMap_name_has(const HashMap_name *map, const key__t *key);
/**
 * Get the value mapped to a specified key.
 * @param map The hash map.
 * @param key The key that the value was mapped to.
 * @return A pointer to the value, or NULL if it was not found.
*/
val_t * HashMap_name_get(const HashMap_name *map, const key__t *key);
/**
 * Remove the value mapped to a specified key.
 * @param map The hash map.
 * @param key The key that the value was mapped to.
 * @return DS_SUCCESS on successfull removal, an error code otherwise.
 * @note Errors: 
 * ERR_KEYNOTFOUND - If the key was not found in the map.
*/
DS_codes_t HashMap_name_remove(HashMap_name *map, const key__t *key);
/**
 * Clears the map of all keys and values.
 * @param map The hash map.
*/
void HashMap_name_clear(HashMap_name *map);
/**
 * Attempts to resize the map to different size.
 * @param map The hash map.
 * @param new_size The new size for the map.
 * @return DS_SUCCESS on successful resizing, an error code on failure.
 * @note Errors:
 * ERR_TOOSMALL - The new size is too small to fit in all elements already
 * present in the map.
 * ERR_TOOBIG - The new size is too big for the hash map to resize.
 * ERR_MEM - Memory allocation error.
*/
DS_codes_t HashMap_name_resize(HashMap_name *map, size_t new_size);
/**
 * Releases all the memory the hash map uses.
 * @param map The hash map.
 * @note For hash maps that were not created with new() use destroy() instead.
*/
void HashMap_name_free(HashMap_name *map);
/**
 * Releases all the memory the hash map uses.
 * @param map The hash map.
 * @note For hash maps that were created with new() use free() instead.
*/
void HashMap_name_destroy(HashMap_name *map);

HashMap_name * HashMap_name_new() {
  return HashMap_name_snew(0);
}

HashMap_name * HashMap_name_snew(size_t size) {
  HashMap_name *map = malloc(sizeof(HashMap_name));
  if (map == NULL) return NULL;
  if (HashMap_name_init(map, size) != DS_SUCCESS) return NULL;
  return map;
}

DS_codes_t HashMap_name_init(HashMap_name *map, size_t size) {
  typedef HashMap_name_entry_t entry_t;
  size_t initial = nearest_prime(size);

  map->buckets = malloc(initial*sizeof(size_t));
  if (map->buckets == NULL) return ERR_MEM;
  for(size_t i = 0; i < initial; i++) map->buckets[i] = -1;

  map->entries = malloc(initial*sizeof(entry_t));
  if (map->entries == NULL) {
    free(map->buckets);
    return ERR_MEM;
  }
  for(size_t i = 0; i < initial; i++) {
    map->entries[i].next = i+1;
  }

  map->cap = initial;
  map->size = 0;
  map->next_empty = 0;

  return DS_SUCCESS;
}

DS_codes_t HashMap_name_put(HashMap_name *map, const key__t *key, const val_t *value) {
  typedef HashMap_name_entry_t entry_t;
  hash_t hash = HashMap_name_hash(key);
  size_t bucket = hash % map->cap;
  ssize_t index = map->buckets[bucket];
  
  // If the key exists, overwrite it.
  for(ssize_t i = index; i != -1; i = map->entries[i].next) {
    entry_t *entry = map->entries + i;
    // Key exists. No new entries, set(overwrite).
    if (entry->key_hash == hash && keycmp(key, &entry->key)) {
      entry->val = *value;
      return HMP_SET;
    }
    index = i;
  }

  // Key doesn't exist. Insert
  // Reserve the next empty slot, and set the next empty to be the "next next".
  size_t empty = map->next_empty;
  map->next_empty = map->entries[map->next_empty].next;
  entry_t new_entry = {
    .key = *key,
    .key_hash = hash,
    .next = map->buckets[bucket],
    .val = *value
  };
  map->buckets[bucket] = empty;
  memcpy(map->entries + empty, &new_entry, sizeof(entry_t));

  // Check if resize needed.
  map->size++;
  if (map->size == map->cap) {
    DS_codes_t res = HashMap_name_resize(map, map->cap + 1);
    if (res != DS_SUCCESS) return res;
  }

  return HMP_ADD;
}

bool HashMap_name_has(const HashMap_name *map, const key__t *key) {
  hash_t hash = HashMap_name_hash(key);
  size_t bucket = hash % map->cap;

  for (ssize_t i = map->buckets[bucket]; i != -1; i = map->entries[i].next) {
    HashMap_name_entry_t *entry = map->entries + i;
    // Exact Match Found. Key exists at i.
    if (entry->key_hash == hash && keycmp(key, &entry->key)) {
      return true;
    }
  }

  return false;
}

val_t * HashMap_name_get(const HashMap_name *map, const key__t *key) {
  hash_t hash = HashMap_name_hash(key);
  size_t bucket = hash % map->cap;

  for (ssize_t i = map->buckets[bucket]; i != -1; i = map->entries[i].next) {
    HashMap_name_entry_t *entry = map->entries + i;
    // Exact Match Found. Key exists at i.
    if (entry->key_hash == hash && keycmp(key, &entry->key)) {
      return &entry->val;
    }
  }

  return NULL;
}

DS_codes_t HashMap_name_remove(HashMap_name *map, const key__t *key) {
  hash_t hash = HashMap_name_hash(key);
  size_t bucket = hash % map->cap;
  ssize_t prev = -1;

  for (ssize_t i = map->buckets[bucket]; i != -1; i = map->entries[i].next) {
    HashMap_name_entry_t *entry = map->entries + i;
    // Exact Match Found. Key exists at i.
    if (entry->key_hash == hash && keycmp(key, &entry->key)) {
      //Unlink entry from the bucket.
      if (prev == -1) map->buckets[bucket] = entry->next;
      else map->entries[prev].next = entry->next;
      // Set the entry's index as the next empty slot.
      entry->next = map->next_empty;
      map->next_empty = i;
      map->size--;
      return DS_SUCCESS;
    }
    prev = i;
  }

  return ERR_KEYNOTFOUND;
}

void HashMap_name_clear(HashMap_name *map) {
  for (size_t i = 0; i < map->cap; i++) {
    map->buckets[i] = -1;
    map->entries[i].next = i + 1;
  }
  map->next_empty = 0;
  map->size = 0;
}

DS_codes_t HashMap_name_resize(HashMap_name *map, size_t new_size) {
  typedef HashMap_name_entry_t entry_t;
  if (new_size < map->size) return ERR_TOOSMALL;

  // Find the next prime size.
  new_size = nearest_prime(new_size);
  if (new_size == PRIME_TOOBIG) return ERR_TOOBIG;
  // Resize entries.
  entry_t *tmp = realloc(map->entries, new_size * sizeof(entry_t));
  if (tmp == NULL) return ERR_MEM;
  map->entries = tmp;
  for (size_t i = map->cap; i < new_size; i++) map->entries[i].next = i + 1;

  // Allocate new buckets.
  ssize_t *new_buckets = malloc(new_size * sizeof(ssize_t));
  if (new_buckets == NULL) {
    free(new_buckets);
    return ERR_MEM;
  }
  for (size_t i = 0; i < new_size; i++) new_buckets[i] = -1;
  
  // Recalculate indices for bigger bucket
  for (size_t i = 0; i < map->cap; i++) {
    while (map->buckets[i] != -1) {
      entry_t *entry = &map->entries[map->buckets[i]];
      size_t entry_pos = map->buckets[i];
      size_t bucket = entry->key_hash % new_size;
      // Unlink entry from the old bucket, old bucket now points at the next link.
      map->buckets[i] = entry->next;
      // Link the entry to the back of the new bucket, behind it's head.
      entry->next = new_buckets[bucket];
      // Change the head of the new bucket to point at the entry as the new head.
      new_buckets[bucket] = entry_pos;
    }
  }

  map->cap = new_size;
  free(map->buckets);
  map->buckets = new_buckets;
  return DS_SUCCESS;
}

void HashMap_name_free(HashMap_name *map) {
  HashMap_name_destroy(map);
  if (map != NULL) free(map);
}

void HashMap_name_destroy(HashMap_name *map) {
  if (map->buckets != NULL) free(map->buckets);
  if (map->entries != NULL) free(map->entries);
}

#endif
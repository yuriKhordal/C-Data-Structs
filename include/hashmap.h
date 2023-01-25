#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "primes.h"
#include "errors.h"

/**
 * Get the first entry in a bucket or NULL if the bucket is empty.
 * @param map A pointer to a hash map.
 * @param bucket The bucket to get the first entry from.
*/
#define map_first_entry(map, bucket) \
  ((map)->buckets[(bucket)] != -1 ? &(map)->entries[(map)->buckets[(bucket)]] : NULL)

/**
 * Get the next entry in a bucket or NULL if the current entry is the last.
 * @param map A pointer to a hash map.
 * @param entry A pointer to the entry to get the next entry from.
*/
#define map_next_entry(map, entry) \
 ((entry)->next != -1 ? &(map)->entries[(entry)->next] : NULL)

/**
 * Iterate over every entry in a hash map.
 * @param map A pointer to the map to iterate over.
 * @param entry A pointer for iterating over entries.
 * @param bucket An indexer for iterating over buckets.
 * @note Accesses the entries directly, overwriting anything except the value
 * is unsafe and should not be done.
*/
#define map_for_each_entry(map, entry, bucket) \
  for ((bucket) = 0; (bucket) < (map)->cap; (bucket)++) \
  for((entry) = map_first_entry(map, bucket); (entry) != NULL; \
    (entry) = map_next_entry(map, entry))

// Define ssize_t
#ifdef _MSC_VER
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#else
#include <unistd.h>
#endif

/* ========================= DECLARATIONS ========================= */

#define HashMap_entry_declare(hm_name) typedef struct hm_name##_entry_t hm_name##_entry_t;
#define HashMap_struct_declare(hm_name) typedef struct hm_name hm_name;
#define HashMap_hash_declare(hm_name, key_t, hash_t) \
  extern hash_t (*const hm_name##_hash)(const key_t*);
#define HashMap_keycmp_declare(hm_name, key_t) \
  extern bool (*const hm_name##_keycmp)(const key_t*, const key_t*);

#define HashMap_new_declare(hm_name) \
/** \
 * Allocates a new hash map and returns a pointer to it.\
 * @return A pointer to the new hash map. NULL on failure. \
 * @note Returns NULL on failed memory allocation. \
*/ \
hm_name * hm_name##_new();

#define HashMap_snew_declare(hm_name) \
/** \
 * Allocates a new hash map with a given initial size and returns a pointer to it. \
 * The hash map will have an initial size of at least `size`. \
 * @param size The requested initial size for the hash map. \
 * @return A pointer to the new hash map. NULL on failure. \
 * @note Returns NULL on failed memory allocation. \
*/ \
hm_name * hm_name##_snew(size_t size);

#define HashMap_init_declare(hm_name) \
/** \
 * Initialize a hash map, if a map struct was made without the new() function, \
 * this function will initialize it fully. \
 * @param map The map to initialize. \
 * @param size The initial size of the map. 0 for default size. \
 * @return DS_SUCCESS on successfull initialization, an error code on failure. \
 * @note Error codes: \
 * ERR_MEM - Memory allocation error. \
*/ \
DS_codes_t hm_name##_init(hm_name *map, size_t size);

#define HashMap_put_declare(hm_name, key_t, val_t) \
/** \
 * Adds or overwrites a key value pair to the map. \
 * @param map The hash map. \
 * @param key The key by which to map the pair. \
 * @param value The value to map to the key. \
 * @return HMP_ADD if a new pair was added, HMP_SET if the key already exists \
 * and it's paired value was overwritten. An error code on failure. Can only \
 * while adding a new pair, not when setting. \
 * @note Errors:  \
 * ERR_MEM - Memory allocation error. \
*/ \
DS_codes_t hm_name##_put(hm_name *map, const key_t *key, const val_t *value);

#define HashMap_has_declare(hm_name, key_t) \
/** \
 * Check if the map has a specified key stored. \
 * @param map The hash map. \
 * @param key The key to search for. \
 * @return True if the key is in the map, false otherwise. \
*/ \
bool hm_name##_has(const hm_name *map, const key_t *key);

#define HashMap_get_declare(hm_name, key_t, val_t) \
/** \
 * Get the value mapped to a specified key. \
 * @param map The hash map. \
 * @param key The key that the value was mapped to. \
 * @return A pointer to the value, or NULL if it was not found. \
*/ \
val_t * hm_name##_get(const hm_name *map, const key_t *key);

#define HashMap_remove_declare(hm_name, key_t) \
/** \
 * Remove the value mapped to a specified key. \
 * @param map The hash map. \
 * @param key The key that the value was mapped to. \
 * @return DS_SUCCESS on successfull removal, an error code otherwise. \
 * @note Errors:  \
 * ERR_KEYNOTFOUND - If the key was not found in the map. \
*/ \
DS_codes_t hm_name##_remove(hm_name *map, const key_t *key);

#define HashMap_clear_declare(hm_name) \
/** \
 * Clears the map of all keys and values. \
 * @param map The hash map. \
*/ \
void hm_name##_clear(hm_name *map);

#define HashMap_resize_declare(hm_name) \
/** \
 * Attempts to resize the map to different size. \
 * @param map The hash map. \
 * @param new_size The new size for the map. \
 * @return DS_SUCCESS on successful resizing, an error code on failure. \
 * @note Errors: \
 * ERR_TOOSMALL - The new size is too small to fit in all elements already \
 * present in the map. \
 * ERR_TOOBIG - The new size is too big for the hash map to resize. \
 * ERR_MEM - Memory allocation error. \
*/ \
DS_codes_t hm_name##_resize(hm_name *map, size_t new_size);

#define HashMap_destroy_declare(hm_name) \
/** \
 * Releases all the memory the hash map uses. \
 * @param map The hash map. \
 * @note For hash maps that were created with new() use free() instead. \
*/ \
void hm_name##_destroy(hm_name *map);

#define HashMap_free_declare(hm_name) \
/** \
 * Releases all the memory the hash map uses. \
 * @param map The hash map. \
 * @note For hash maps that were not created with new() use destroy() instead. \
*/ \
void hm_name##_free(hm_name *map); 

/* ========================= DEFINITIONS ========================= */

#define HashMap_entry_define(hm_name, key_t, val_t, hash_t) \
/**Represents an entry in the hash map.*/ \
struct hm_name##_entry_t { \
  /**The key of the entry*/ \
  const key_t key; \
  /**The hash of the key.*/ \
  const hash_t key_hash; \
  /**The index of the next entry in case of hash collisions.*/ \
  ssize_t next; \
  /**The value of the entry.*/ \
  val_t val; \
};

#define HashMap_struct_define(hm_name) \
/**Represents a hash map data structure.*/ \
struct hm_name { \
  /**The entries of the map, all the Key-Value pairs.*/ \
  hm_name##_entry_t *entries; \
  /**An array of indices that maps a normalized hash to an entry index. \
   * Index -1 means there is no such entry.*/ \
  ssize_t* buckets; \
  /**The amount of entries in the map.*/ \
  size_t size; \
  /**The next empty cell in the entries array.*/ \
  size_t next_empty; \
  /**The maximum capacity of the map.*/ \
  size_t cap; \
};

#define HashMap_hash_define(hm_name, key_t, hash_t, hash) \
/**A pointer to a function that hashes a key.*/ \
hash_t (*const hm_name##_hash)(const key_t*) = hash;

#define HashMap_keycmp_define(hm_name, key_t, keycmp) \
/**A pointer to a function that compares two keys and returns true if they're equal.*/ \
bool (*const hm_name##_keycmp)(const key_t*, const key_t*) = keycmp;

#define HashMap_new_define(hm_name) \
hm_name * hm_name##_new() { \
  return hm_name##_snew(0); \
}

#define HashMap_snew_define(hm_name) \
hm_name * hm_name##_snew(size_t size) { \
  hm_name *map = malloc(sizeof(hm_name)); \
  if (map == NULL) return NULL; \
  if (hm_name##_init(map, size) != DS_SUCCESS) return NULL; \
  return map; \
}

#define HashMap_init_define(hm_name) \
DS_codes_t hm_name##_init(hm_name *map, size_t size) { \
  size_t initial = nearest_prime(size); \
 \
  map->buckets = malloc(initial*sizeof(size_t)); \
  if (map->buckets == NULL) return ERR_MEM; \
  for(size_t i = 0; i < initial; i++) map->buckets[i] = -1; \
 \
  map->entries = malloc(initial*sizeof(hm_name##_entry_t)); \
  if (map->entries == NULL) { \
    free(map->buckets); \
    return ERR_MEM; \
  } \
  for(size_t i = 0; i < initial; i++) { \
    map->entries[i].next = i+1; \
  } \
 \
  map->cap = initial; \
  map->size = 0; \
  map->next_empty = 0; \
 \
  return DS_SUCCESS; \
}

#define HashMap_put_define(hm_name, key_t, val_t, hash_t) \
DS_codes_t hm_name##_put(hm_name *map, const key_t *key, const val_t *value) { \
  hash_t hash = hm_name##_hash(key); \
  size_t bucket = hash % map->cap; \
  ssize_t index = map->buckets[bucket]; \
   \
  /* If the key exists, overwrite it. */ \
  for(ssize_t i = index; i != -1; i = map->entries[i].next) { \
    hm_name##_entry_t *entry = map->entries + i; \
    /* Key exists. No new entries, set(overwrite). */ \
    if (entry->key_hash == hash && hm_name##_keycmp(key, &entry->key)) { \
      entry->val = *value; \
      return HMP_SET; \
    } \
    index = i; \
  } \
 \
  /* Key doesn't exist. Insert */ \
  /* Reserve the next empty slot, and set the next empty to be the "next next". */ \
  size_t empty = map->next_empty; \
  map->next_empty = map->entries[map->next_empty].next; \
  hm_name##_entry_t new_entry = { \
    .key = *key, \
    .key_hash = hash, \
    .next = map->buckets[bucket], \
    .val = *value \
  }; \
  map->buckets[bucket] = empty; \
  memcpy(map->entries + empty, &new_entry, sizeof(hm_name##_entry_t)); \
 \
  /* Check if resize needed. */ \
  map->size++; \
  if (map->size == map->cap) { \
    DS_codes_t res = hm_name##_resize(map, map->cap + 1); \
    if (res != DS_SUCCESS) return res; \
  } \
 \
  return HMP_ADD; \
}

#define HashMap_has_define(hm_name, key_t, hash_t) \
bool hm_name##_has(const hm_name *map, const key_t *key) { \
  hash_t hash = hm_name##_hash(key); \
  size_t bucket = hash % map->cap; \
 \
  for (ssize_t i = map->buckets[bucket]; i != -1; i = map->entries[i].next) { \
    hm_name##_entry_t *entry = map->entries + i; \
    /* Exact Match Found. Key exists at i. */ \
    if (entry->key_hash == hash && hm_name##_keycmp(key, &entry->key)) { \
      return true; \
    } \
  } \
 \
  return false; \
}

#define HashMap_get_define(hm_name, key_t, val_t, hash_t) \
val_t * hm_name##_get(const hm_name *map, const key_t *key) { \
  hash_t hash = hm_name##_hash(key); \
  size_t bucket = hash % map->cap; \
 \
  for (ssize_t i = map->buckets[bucket]; i != -1; i = map->entries[i].next) { \
    hm_name##_entry_t *entry = map->entries + i; \
    /* Exact Match Found. Key exists at i. */ \
    if (entry->key_hash == hash && hm_name##_keycmp(key, &entry->key)) { \
      return &entry->val; \
    } \
  } \
 \
  return NULL; \
}

#define HashMap_remove_define(hm_name, key_t, hash_t) \
DS_codes_t hm_name##_remove(hm_name *map, const key_t *key) { \
  hash_t hash = hm_name##_hash(key); \
  size_t bucket = hash % map->cap; \
  ssize_t prev = -1; \
 \
  for (ssize_t i = map->buckets[bucket]; i != -1; i = map->entries[i].next) { \
    hm_name##_entry_t *entry = map->entries + i; \
    /* Exact Match Found. Key exists at i. */ \
    if (entry->key_hash == hash && keycmp(key, &entry->key)) { \
      /* Unlink entry from the bucket. */ \
      if (prev == -1) map->buckets[bucket] = entry->next; \
      else map->entries[prev].next = entry->next; \
      /* Set the entry's index as the next empty slot. */ \
      entry->next = map->next_empty; \
      map->next_empty = i; \
      map->size--; \
      return DS_SUCCESS; \
    } \
    prev = i; \
  } \
 \
  return ERR_KEYNOTFOUND; \
}

#define HashMap_clear_define(hm_name) \
void hm_name##_clear(hm_name *map) { \
  for (size_t i = 0; i < map->cap; i++) { \
    map->buckets[i] = -1; \
    map->entries[i].next = i + 1; \
  } \
  map->next_empty = 0; \
  map->size = 0; \
}

#define HashMap_resize_define(hm_name) \
DS_codes_t hm_name##_resize(hm_name *map, size_t new_size) { \
  if (new_size < map->size) return ERR_TOOSMALL; \
 \
  /* Find the next prime size. */ \
  new_size = nearest_prime(new_size); \
  if (new_size == PRIME_TOOBIG) return ERR_TOOBIG; \
  /* Resize entries. */ \
  hm_name##_entry_t *tmp = realloc(map->entries, new_size * sizeof(hm_name##_entry_t)); \
  if (tmp == NULL) return ERR_MEM; \
  map->entries = tmp; \
  for (size_t i = map->cap; i < new_size; i++) map->entries[i].next = i + 1; \
 \
  /* Allocate new buckets. */ \
  ssize_t *new_buckets = malloc(new_size * sizeof(ssize_t)); \
  if (new_buckets == NULL) { \
    free(new_buckets); \
    return ERR_MEM; \
  } \
  for (size_t i = 0; i < new_size; i++) new_buckets[i] = -1; \
   \
  /* Recalculate indices for bigger bucket */ \
  for (size_t i = 0; i < map->cap; i++) { \
    while (map->buckets[i] != -1) { \
      hm_name##_entry_t *entry = &map->entries[map->buckets[i]]; \
      size_t entry_pos = map->buckets[i]; \
      size_t bucket = entry->key_hash % new_size; \
      /* Unlink entry from the old bucket, old bucket now points at the next link. */ \
      map->buckets[i] = entry->next; \
      /* Link the entry to the back of the new bucket, behind it's head. */ \
      entry->next = new_buckets[bucket]; \
      /* Change the head of the new bucket to point at the entry as the new head. */ \
      new_buckets[bucket] = entry_pos; \
    } \
  } \
 \
  map->cap = new_size; \
  free(map->buckets); \
  map->buckets = new_buckets; \
  return DS_SUCCESS; \
}

#define HashMap_destroy_define(hm_name) \
void hm_name##_destroy(hm_name *map) { \
  if (map->buckets != NULL) free(map->buckets); \
  if (map->entries != NULL) free(map->entries); \
}

#define HashMap_free_define(hm_name) \
void hm_name##_free(hm_name *map) { \
  hm_name##_destroy(map); \
  if (map != NULL) free(map); \
}

/* ========================= ALL ========================= */

/**
 * Generate the declarations for a hash map data structure for a given
 * key and value types.
 * @param hm_name The name to generate the hash map struct as, and prefix
 * all the hash map methods with.
 * @param key_t The data type of the key for the hash map.
 * @param val_t The data type of the value for the hash map.
 * @param hash_t The data type of the hash.
 * @note It's best to put this macro in a header file.
*/
#define HashMap_declare(hm_name, key_t, val_t, hash_t) \
HashMap_entry_declare(hm_name) \
HashMap_struct_declare(hm_name) \
HashMap_hash_declare(hm_name, key_t, hash_t) \
HashMap_keycmp_declare(hm_name, key_t) \
HashMap_new_declare(hm_name) \
HashMap_snew_declare(hm_name) \
HashMap_init_declare(hm_name) \
HashMap_put_declare(hm_name, key_t, val_t) \
HashMap_has_declare(hm_name, key_t) \
HashMap_get_declare(hm_name, key_t, val_t) \
HashMap_remove_declare(hm_name, key_t) \
HashMap_clear_declare(hm_name) \
HashMap_resize_declare(hm_name) \
HashMap_destroy_declare(hm_name) \
HashMap_free_declare(hm_name)

/**
 * Generate the definitions for the hash map data structure for a given
 * key and value types.
 * @param hm_name The name to generate the hash map struct as, and prefix
 * all the hash map methods with.
 * @param key_t The data type of the key for the hash map.
 * @param val_t The data type of the value for the hash map.
 * @param hash_t The data type of the hash.
 * @param hash A pointer to the hash function for hashing keys.
 * @param keycmp A pointer to a function for comparing keys.
 * @note It's best to put this macro in a code file.
*/
#define HashMap_define(hm_name, key_t, val_t, hash_t, hash, keycmp) \
HashMap_entry_define(hm_name, key_t, val_t, hash_t) \
HashMap_struct_define(hm_name) \
HashMap_hash_define(hm_name, key_t, hash_t, hash) \
HashMap_keycmp_define(hm_name, key_t, keycmp) \
HashMap_new_define(hm_name) \
HashMap_snew_define(hm_name) \
HashMap_init_define(hm_name) \
HashMap_put_define(hm_name, key_t, val_t, hash_t) \
HashMap_has_define(hm_name, key_t, hash_t) \
HashMap_get_define(hm_name, key_t, val_t, hash_t) \
HashMap_remove_define(hm_name, key_t, hash_t) \
HashMap_clear_define(hm_name) \
HashMap_resize_define(hm_name) \
HashMap_destroy_define(hm_name) \
HashMap_free_define(hm_name)

/**
 * Generate a full hash map data structure implementation for a given
 * key and value types.
 * @param hm_name The name to generate the hash map struct as, and prefix
 * all the hash map methods with.
 * @param key_t The data type of the key for the hash map.
 * @param val_t The data type of the value for the hash map.
 * @param hash_t The data type of the hash.
 * @param hash A pointer to the hash function for hashing keys.
 * @param keycmp A pointer to a function for comparing keys.
 * @note This macro will generate a hash map structure and it's functions,
 * with the given key and value types. It should not be put within a function
 * but in some global scope, like at the start of the file that uses it,
 * or better yet, in a header file.
 * @note It would be better to use the HashMap_declare and HashMap_define
 * macros seperately, the declare macro in a header file, and the define macro
 * in a code file.
*/
#define HashMap(hm_name, key_t, val_t, hash_t, hash, keycmp) \
HashMap_declare(hm_name, key_t, val_t, hash_t) \
HashMap_define(hm_name, key_t, val_t, hash_t, hash, keycmp)

#endif
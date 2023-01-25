#ifndef __PRIMES_H__
#define __PRIMES_H__

#include<stddef.h>

#define MIN_PRIME (7)
#define MAX_PRIME (7199369)
#define PRIME_TOOBIG (primes_size)

/*Because hash functions use primes to compute hashes, prime number sizes work
well for hash table sizes, taken straight from microsoft's implementation.*/
/**A hardcoded array of primes for hash table sizes.*/
const extern size_t primes[];
/*
const size_t primes[] = {
  7, 11, 17, 23, 29, 37, 47, 59, 71, 89, 107, 131, 163, 197, 239, 293,
  353, 431, 521, 631, 761, 919, 1103, 1327, 1597, 1931, 2333, 2801, 3371, 4049,
  4861, 5839, 7013, 8419, 10103, 12143, 14591, 17519, 21023, 25229, 30293,
  36353, 43627, 52361, 62851, 75431, 90523, 108631, 130363, 156437, 187751,
  225307, 270371, 324449, 389357, 467237, 560689, 672827, 807403, 968897,
  1162687, 1395263, 1674319, 2009191, 2411033, 2893249, 3471899, 4166287,
  4999559, 5999471, 7199369
};
*/

/**The size of the primes array.*/
const extern size_t primes_size;
/*const size_t primes_size = sizeof(primes) / sizeof(size_t);*/

/**
 * Returns the smallest prime number that's bigger then the specified number.
 * @param num The number to find a prime for.
 * @return The smallest prime number that's bigger then `num`.
 * returns PRIMES_TOOBIG if the number is higher than MAX_PRIME.
*/
size_t nearest_prime(size_t num);

/**
 * Returns the index of the smallest prime number that's bigger then the
 * specified number.
 * @param num The number to find a prime for.
 * @return The index of the smallest prime number that's bigger then `num`.
*/
size_t nearest_prime_index(size_t num);

#endif
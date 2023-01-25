#include "primes.h"

const size_t primes[] = {
  /*3, */7, 11, 17, 23, 29, 37, 47, 59, 71, 89, 107, 131, 163, 197, 239, 293,
  353, 431, 521, 631, 761, 919, 1103, 1327, 1597, 1931, 2333, 2801, 3371, 4049,
  4861, 5839, 7013, 8419, 10103, 12143, 14591, 17519, 21023, 25229, 30293,
  36353, 43627, 52361, 62851, 75431, 90523, 108631, 130363, 156437, 187751,
  225307, 270371, 324449, 389357, 467237, 560689, 672827, 807403, 968897,
  1162687, 1395263, 1674319, 2009191, 2411033, 2893249, 3471899, 4166287,
  4999559, 5999471, 7199369
};

const size_t primes_size = sizeof(primes) / sizeof(size_t);

size_t nearest_prime(size_t num) {
  size_t index = nearest_prime_index(num);
  if (index == PRIME_TOOBIG) return PRIME_TOOBIG;
  return primes[nearest_prime_index(num)];
}

size_t nearest_prime_index(size_t num) {
  if (num > MAX_PRIME) return PRIME_TOOBIG;
  if (num <= primes[0]) return 0;
  if (num == primes[primes_size - 1]) return primes_size - 1;

  /*Binary search*/
  size_t start = 0, end = primes_size - 1;
  while (end - start > 1) {
    size_t mid = (start + end) / 2;
    if (num > primes[mid]) start = mid;
    else if (num < primes[mid]) end = mid;
    else return mid;
  }
  return end;
}

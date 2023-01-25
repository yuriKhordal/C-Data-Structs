/**The various return codes for the data structures.*/
typedef enum DataStructs_codes_t {
  /**The hashmap's put method overwrote an entry(set mode).*/
  HMP_SET = 2,
  /**The hashmap's put method added an entry.*/
  HMP_ADD = 1,
  /**The opeation completed successfully.*/
  DS_SUCCESS = 0,
  /**A value of a paremeter is too small.*/
  ERR_TOOSMALL= -1,
  /**A value of a paremeter is too big.*/
  ERR_TOOBIG = -2,
  /**A memory allocation error.*/
  ERR_MEM = -3,
  /**A value of a paremeter is NULL.*/
  ERR_NULL = -4,
  /**A value of a paremeter is out of the range of valid values.*/
  ERR_OUTOFRANGE = -5,
  /**A key was not found in the hashmap.*/
  ERR_KEYNOTFOUND = -6
} DS_codes_t;
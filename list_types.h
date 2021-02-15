#ifndef __LIST_TYPES_H__
#define __LIST_TYPES_H__
#include "list.h"

STRUCT_LIST(char,	ListChar)
STRUCT_LIST(short,	ListShort)
STRUCT_LIST(int,	ListInt)
STRUCT_LIST(long,	ListLong)
STRUCT_LIST(float,	ListFloat)
STRUCT_LIST(double,	ListDouble)

STRUCT_LIST(char*,	ListCharPtr)
STRUCT_LIST(short*,	ListShortPtr)
STRUCT_LIST(int*,	ListIntPtr)
STRUCT_LIST(long*,	ListLongPtr)
STRUCT_LIST(float*,	ListFloatPtr)
STRUCT_LIST(double*,ListDoublePtr)

STRUCT_LIST(long long,		ListLLong)
STRUCT_LIST(long double,	ListLDouble)
STRUCT_LIST(long long*,		ListLLongPtr)
STRUCT_LIST(long double*,	ListLDoublePtr)

STRUCT_LIST(signed char,	ListSChar)
STRUCT_LIST(unsigned char,	ListUChar)
STRUCT_LIST(unsigned short,	ListUShort)
STRUCT_LIST(unsigned int,	ListUInt)
STRUCT_LIST(unsigned long,	ListULong)
STRUCT_LIST(unsigned long long,ListULLong)

STRUCT_LIST(signed char*,	ListSCharPtr)
STRUCT_LIST(unsigned char*,	ListUCharPtr)
STRUCT_LIST(unsigned short*,ListUShortPtr)
STRUCT_LIST(unsigned int*,	ListUIntPtr)
STRUCT_LIST(unsigned long*,	ListULongPtr)
STRUCT_LIST(unsigned long long*,ListULLongPtr)

STRUCT_LIST(size_t,	ListSizeT)

#endif
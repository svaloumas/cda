#include <stddef.h>
#include <string.h>
#include <assert.h>

#define CDA_TRUE  1
#define CDA_FALSE 0

#define CDA_ASSERT(exp)       assert(exp)
#define CDA_CARD(arr)         sizeof(arr)/sizeof(*arr)
#define CDA_NEW(type)         (type *)CDA_malloc(sizeof(type))
#define CDA_NEW_STR(str)      (strcpy((char *)CDA_malloc(strlen(str) + 1), str))
#define CDA_NEW_STR_IF(str)   ((str) == NULL ? NULL : CDA_NEW_STR(str))

typedef int            CDA_BOOL_t;
typedef signed char    CDA_INT8_t;
typedef unsigned char  CDA_UINT8_t;
typedef signed short   CDA_INT16_t;
typedef unsigned short CDA_UINT16_t;
typedef signed int     CDA_INT32_t;
typedef unsigned int   CDA_UINT32_t;
typedef signed long    CDA_INT64_t;
typedef unsigned long  CDA_UINT64_t;

void *CDA_malloc(size_t size);
void *CDA_calloc(size_t nitems, size_t size);
void *CDA_realloc(void *ptr, size_t size);
void CDA_free(void *mem);

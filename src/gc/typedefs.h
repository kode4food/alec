#pragma once

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t Byte_t;
typedef size_t Size_t;
typedef Byte_t GCData_t;

// To allow circular references
typedef struct Entry Entry;
typedef struct GC GC;
typedef struct Log Log;
typedef struct LogEntry LogEntry;
typedef struct Ref Ref;
typedef struct RefList RefList;
typedef struct RefSpan RefSpan;
typedef struct Type Type;

#ifdef __cplusplus
}
#endif

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "type.h"
#include "typedefs.h"

typedef struct Entry Entry;

struct Entry {
  Type* type;
  Size_t size;
  GCData_t data[];
};

#ifdef __cplusplus
}
#endif

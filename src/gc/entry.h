#pragma once

#include "typedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Entry {
  Type* type;
  Size_t size;
  GCData_t data[];
};

#ifdef __cplusplus
}
#endif

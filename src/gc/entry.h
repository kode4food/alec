//
// Created by Thomas Bradford on 20.08.20.
//

#ifndef ALE_SRC_GC_ENTRY_H_
#define ALE_SRC_GC_ENTRY_H_

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

#endif//ALE_SRC_GC_ENTRY_H_

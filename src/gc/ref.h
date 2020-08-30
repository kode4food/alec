#pragma once

#include "entry.h"
#include "typedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  kInit,
  kGrey,
  kFlipper1,
  kFlipper2,
} GCStatus_t;

struct Ref {
  GC *gc;
  GCStatus_t status;
  Entry *entry;
};

#define REF_GC(ref) ((GC *) ((ref)->gc))
#define DEREF(ref, type) ((type *) ((ref)->entry->data))

Ref *RefPin(Ref *ref);
Ref *RefUnpin(Ref *ref);
Ref *RefMark(Ref *ref);
void RefFree(Ref *ref);

#ifdef __cplusplus
}
#endif

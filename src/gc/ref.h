//
// Created by Thomas Bradford on 19.08.20.
//

#ifndef ALE_SRC_GC_REF_H_
#define ALE_SRC_GC_REF_H_

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
#define DEREF(ref, type) ((type *)((ref)->entry->data))
#define FLIP_STATUS(status) (status == kFlipper1 ? kFlipper2 : kFlipper1)

Ref *RefPin(Ref *ref);
Ref *RefUnpin(Ref *ref);
Ref *RefMark(Ref *ref);
void RefFree(Ref *ref);

#ifdef __cplusplus
}
#endif

#endif// ALE_SRC_GC_REF_H_

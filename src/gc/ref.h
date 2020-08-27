//
// Created by Thomas Bradford on 19.08.20.
//

#ifndef ALE_SRC_GC_REF_H_
#define ALE_SRC_GC_REF_H_

#include "entry.h"
#include "typedefs.h"

typedef uint8_t GCStatus_t;

const GCStatus_t kInit = 0;
const GCStatus_t kGrey = 1;
const GCStatus_t kFlipper = 2;

struct Ref {
  GC *gc;
  GCStatus_t status;
  Entry *entry;
};

#define REF_GC(ref) ((GC *) ((ref)->gc))
#define DEREF(ref) (&((ref)->entry.data))
#define FLIP_STATUS(status) (status == kFlipper ? kFlipper + 1 : kFlipper)

Ref *RefPin(Ref *ref);
Ref *RefUnpin(Ref *ref);
Ref *RefMark(Ref *ref);
void RefFree(Ref *ref);

#endif// ALE_SRC_GC_REF_H_

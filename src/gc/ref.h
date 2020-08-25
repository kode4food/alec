//
// Created by Thomas Bradford on 19.08.20.
//

#ifndef ALE_SRC_GC_REF_H_
#define ALE_SRC_GC_REF_H_

#include "entry.h"
#include "typedefs.h"

typedef enum {
  kInitialStatus,
  kUnmarkedStatus,
  kPendingStatus,
  kMarkedStatus,
  kCollectedStatus,
} GCStatus_t;

struct Ref {
  GC *gc;
  GCStatus_t status;
  Entry *entry;
};

#define REF_GC(ref) ((GC *) ((ref)->gc))
#define DEREF(ref) (&((ref)->entry.data))

Ref *RefPin(Ref *ref);
Ref *RefUnpin(Ref *ref);
Ref *RefMark(Ref *ref);

#endif// ALE_SRC_GC_REF_H_

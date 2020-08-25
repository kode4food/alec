//
// Created by Thomas Bradford on 19.08.20.
//

#ifndef ALE_SRC_GC_REF_H_
#define ALE_SRC_GC_REF_H_

#include <stdint.h>

#include "entry.h"

typedef enum {
  kInitialStatus,
  kUnmarkedStatus,
  kPendingStatus,
  kMarkedStatus,
  kCollectedStatus,
} GCStatus_t;

typedef struct {
  struct GC *gc;
  GCStatus_t status;
  Entry *entry;
} Ref;

#define REF_GC(ref) ((GC *) ((ref)->gc))
#define DEREF(ref) (&((ref)->entry.data))

#endif// ALE_SRC_GC_REF_H_

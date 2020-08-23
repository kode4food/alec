//
// Created by Thomas Bradford on 19.08.20.
//

#ifndef ALE_SRC_GC_REF_H_
#define ALE_SRC_GC_REF_H_

#include <stdint.h>

#include "entry.h"

typedef enum {
  GCInitialStatus,
  GCUnmarkedStatus,
  GCPendingStatus,
  GCMarkedStatus,
  GCCollectedStatus,
} GCStatus_t;

typedef struct {
  struct GC *gc;
  GCStatus_t status;
  GCEntry *entry;
} GCRef;

#define RefGC(ref) ((GC *) (ref->gc))
#define DeRef(ref) (&(ref->entry.data))

#endif// ALE_SRC_GC_REF_H_

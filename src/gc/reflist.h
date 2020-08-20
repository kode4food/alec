//
// Created by Thomas Bradford on 19.08.20.
//

#ifndef ALE_SRC_GC_REFLIST_H_
#define ALE_SRC_GC_REFLIST_H_

#include <stdbool.h>
#include <stdlib.h>

#include "ref.h"

typedef struct GCRefList GCRefList;

struct GCRefList {
  GCRef *ref;
  GCRefList *next;
};

const GCRefList *EmptyRefList = NULL;

GCRefList *gcRefListAdd(GCRefList *list, GCRef *ref);
GCRefList *gcRefListRemove(GCRefList *list, GCRef *ref);

#endif// ALE_SRC_GC_REFLIST_H_

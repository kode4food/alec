//
// Created by Thomas Bradford on 19.08.20.
//

#ifndef ALE_SRC_GC_REFSPAN_H_
#define ALE_SRC_GC_REFSPAN_H_

#include "types.h"
#include "ref.h"

const GCSize_t defaultSpanSize = 1024;

struct GCRefSpan {
  GCSize_t count;
  GCSize_t capacity;
  GCRefSpan *next;
  GCRef refs[];
};

GCRefSpan *gcAllocRefSpan(GCSize_t capacity);

#endif // ALE_SRC_GC_REFSPAN_H_

//
// Created by Thomas Bradford on 19.08.20.
//

#ifndef ALE_SRC_GC_REFSPAN_H_
#define ALE_SRC_GC_REFSPAN_H_

#include "entry.h"
#include "ref.h"

const GCSize_t kDefaultSpanSize = 1024;

typedef struct RefSpan RefSpan;

struct RefSpan {
  GCSize_t count;
  GCSize_t capacity;
  RefSpan *next;
  Ref refs[];
};

RefSpan *RefSpanAlloc(GCSize_t capacity, RefSpan *next);

#endif// ALE_SRC_GC_REFSPAN_H_

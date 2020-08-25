//
// Created by Thomas Bradford on 19.08.20.
//

#ifndef ALE_SRC_GC_REFSPAN_H_
#define ALE_SRC_GC_REFSPAN_H_

#include "ref.h"
#include "typedefs.h"

const Size_t kDefaultSpanSize = 1024;

typedef struct RefSpan RefSpan;

struct RefSpan {
  Size_t count;
  Size_t capacity;
  RefSpan *next;
  Ref refs[];
};

RefSpan *RefSpanAlloc(Size_t capacity, RefSpan *next);

#endif// ALE_SRC_GC_REFSPAN_H_

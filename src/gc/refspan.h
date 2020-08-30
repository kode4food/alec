#pragma once

#include "ref.h"
#include "typedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct RefSpan RefSpan;

struct RefSpan {
  Size_t count;
  Size_t capacity;
  RefSpan *next;
  Ref refs[];
};

RefSpan *RefSpanAlloc(Size_t capacity, RefSpan *next);
RefSpan *RefSpanAllocDefault(RefSpan *next);

#ifdef __cplusplus
}
#endif

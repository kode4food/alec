//
// Created by Thomas Bradford on 19.08.20.
//

#ifndef ALE_SRC_GC_REFSPAN_H_
#define ALE_SRC_GC_REFSPAN_H_

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

#endif// ALE_SRC_GC_REFSPAN_H_

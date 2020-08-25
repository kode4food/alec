//
// Created by Thomas Bradford on 19.08.20.
//

#include "refspan.h"

#include <stdlib.h>

RefSpan *RefSpanAlloc(GCSize_t capacity, RefSpan *next) {
  GCSize_t total_size = sizeof(RefSpan) + (capacity * sizeof(Ref));
  RefSpan *span = malloc(total_size);
  *span = (RefSpan){
      .count = 0,
      .capacity = capacity,
      .next = next,
  };
  return span;
}

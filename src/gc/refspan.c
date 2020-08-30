#include "refspan.h"

const Size_t kDefaultSpanSize = 1024;

RefSpan *RefSpanAlloc(Size_t capacity, RefSpan *next) {
  Size_t total_size = sizeof(RefSpan) + (capacity * sizeof(Ref));
  RefSpan *span = malloc(total_size);
  *span = (RefSpan){
      .count = 0,
      .capacity = capacity,
      .next = next,
  };
  return span;
}

RefSpan *RefSpanAllocDefault(RefSpan *next) {
  return RefSpanAlloc(kDefaultSpanSize, next);
}

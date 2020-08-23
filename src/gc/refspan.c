//
// Created by Thomas Bradford on 19.08.20.
//

#include "refspan.h"

#include <stdlib.h>

GCRefSpan *gcAllocRefSpan(GCSize_t capacity, GCRefSpan *next) {
  GCSize_t totalSize = sizeof(GCRefSpan) + (capacity * sizeof(GCRef));
  GCRefSpan *span = malloc(totalSize);
  *span = (GCRefSpan){
      .count = 0,
      .capacity = capacity,
      .next = next,
  };
  return span;
}

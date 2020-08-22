//
// Created by Thomas Bradford on 20.08.20.
//

#ifndef ALE_SRC_GC_ENTRY_H_
#define ALE_SRC_GC_ENTRY_H_

#include <stdint.h>

typedef uint64_t GCSize_t;

typedef void (*GCMarker)(void* ptr);

typedef struct {
  GCMarker marker;
} GCType;

typedef struct {
  GCType* type;
  GCSize_t size;
  void* ptr;
} GCEntry;

#endif//ALE_SRC_GC_ENTRY_H_

//
// Created by Thomas Bradford on 20.08.20.
//

#ifndef ALE_SRC_GC_DATA_H_
#define ALE_SRC_GC_DATA_H_

#include <stdint.h>

typedef uint64_t GCSize_t;
typedef uint8_t* GCContent_p;

typedef void (*GCMarker)(GCContent_p content);

typedef struct {
  GCMarker marker;
} GCType;

typedef struct {
  GCType* type;
  GCSize_t size;
  GCContent_p content;
} GCData;

#endif//ALE_SRC_GC_DATA_H_

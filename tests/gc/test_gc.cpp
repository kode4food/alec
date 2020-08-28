//
// Created by Thomas Bradford on 17.08.20.
//

#include "gc/gc.h"
#include "gc/type.h"

#define CATCH_CONFIG_MAIN
#include "catch.h"

TEST_CASE("Garbage collect an atomic value") {
  Type int_type = {
      .default_size = sizeof(int),
  };

  GC *gc = GCInit();
  REQUIRE(gc != NULL);

  Ref *r = GCNew(gc, &int_type);
  RefPin(r);
  int *i1 = DEREF(r, int);
  *i1 = 42;

  Size_t freed = GCCollect(gc);
  REQUIRE(freed == 0);

  int *i2 = DEREF(r, int);
  REQUIRE(*i2 == *i1);
  REQUIRE(*i2 == 42);

  RefUnpin(r);
  freed = GCCollect(gc);
  REQUIRE(freed == sizeof(int));
}

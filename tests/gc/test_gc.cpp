//
// Created by Thomas Bradford on 17.08.20.
//

#include "gc/gc.h"
#include "gc/type.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

SCENARIO("Garbage collect an atomic value") {
  Type int_type = {
      .default_size = sizeof(int),
  };

  GIVEN("A newly instantiated Garbage Collector") {
    GC *gc = GCInit();
    REQUIRE(gc != NULL);

    WHEN("An integer is allocated and pinned") {
      Ref *r = GCNew(gc, &int_type);
      RefPin(r);
      int *i1 = DEREF(r, int);
      *i1 = 42;

      THEN("It should not be collected") {
        Size_t freed = GCCollect(gc);
        REQUIRE(freed == 0);

        AND_THEN("It should be retained") {
          int *i2 = DEREF(r, int);
          REQUIRE(*i2 == 42);
        }
      }

      AND_WHEN("It is unpinned") {
        RefUnpin(r);

        THEN("It should be capable of being freed") {
          Size_t freed = GCCollect(gc);
          REQUIRE(freed == sizeof(int));
        }
      }
    }
  }
}

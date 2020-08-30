#pragma once
#include "catch.hpp"
#include "gc/log.h"

SCENARIO("Log appends correctly") {

  GIVEN("A newly instantiated Log") {
    GC *gc = GCInit();
    REQUIRE(gc != NULL);
  }
}

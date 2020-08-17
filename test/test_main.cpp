//
// Created by Thomas Bradford on 17.08.20.
//

#define CATCH_CONFIG_MAIN
#include "catch.h"

TEST_CASE("Prove that one equals two"){
  int one = 1;
  REQUIRE( one == 1 );
}

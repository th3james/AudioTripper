//
//  HelloCppTests.h
//  AudioTrip
//
//  Created by James Cox on 21/01/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#include "catch.hpp"

#include "HelloCppBridge.h"

TEST_CASE( "It returns a friendly greeting", "[hello]" ) {
  REQUIRE(sayHelloCpp() == "Hello there");
}

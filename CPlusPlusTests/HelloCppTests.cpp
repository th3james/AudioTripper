//
//  HelloCppTests.h
//  AudioTrip
//
//  Created by James Cox on 21/01/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#include "catch.hpp"

#include "HelloCppBridge.h"
#include "TestClass.hpp"

TEST_CASE( "It returns a friendly greeting", "[hello]" ) {
  REQUIRE(sayHelloCpp() == "Hello there");
}

TEST_CASE( "TestClass.greet() returns a friendly greeting", "[hello]" ) {
  const char * greeting = "Hello there";
  CHECK(TestClass(greeting).greet() == greeting);
  
  const char * greeting2 = "Howdy";
  CHECK(TestClass(greeting2).greet() == greeting2);
}
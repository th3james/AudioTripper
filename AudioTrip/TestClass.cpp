//
//  TestClass.cpp
//  AudioTrip
//
//  Created by James Cox on 22/01/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#include "TestClass.hpp"

TestClass::TestClass(const char * theGreeting) {
  greeting = theGreeting;
}

const char * TestClass::greet() {
  return greeting;
};

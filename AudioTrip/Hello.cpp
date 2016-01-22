//
//  Hello.cpp
//  AudioTrip
//
//  Created by James Cox on 21/01/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#include "HelloCppBridge.h"
#include "TestClass.hpp"

const char * sayHelloCpp() {
  return TestClass("Hello there").greet();
}
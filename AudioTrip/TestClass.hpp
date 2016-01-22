//
//  TestClass.hpp
//  AudioTrip
//
//  Created by James Cox on 22/01/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#ifndef TestClass_hpp
#define TestClass_hpp

#include <stdio.h>

class TestClass {
public:
  TestClass(const char * theGreeting);
  const char * greet();

private:
  const char * greeting;
};

#endif /* TestClass_hpp */

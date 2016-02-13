//
//  AudioTripper.hpp
//  AudioTrip
//
//  Created by James Cox on 24/01/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#ifndef AudioTripper_hpp
#define AudioTripper_hpp

#include <stdio.h>

namespace AudioTripper {
  struct EvaluatedFile {
    const char * filePath;
    int16_t loudestPeak;
    uint32_t fileLength;
    char * format;
  };
  
  struct EvaluatedFile evaluate(const char * filePath);
}

#endif /* AudioTripper_hpp */

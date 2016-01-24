//
//  AudioTripper.cpp
//  AudioTrip
//
//  Created by James Cox on 24/01/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#include "AudioTripper.hpp"

namespace AudioTripper {
  struct EvaluatedFile evaluate(const char * filePath) {
    EvaluatedFile file;
    file.filePath = filePath;
    
    return file;
  }
}
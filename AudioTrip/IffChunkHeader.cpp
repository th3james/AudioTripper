//
//  IffChunkHeader.cpp
//  AudioTrip
//
//  Created by James Cox on 27/02/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#include "IffChunkHeader.hpp"

namespace AiffReader {
  IffChunkHeader:: IffChunkHeader() {
    typeId.reserve(4);
  }
}
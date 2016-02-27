//
//  IffChunkHeader.hpp
//  AudioTrip
//
//  Created by James Cox on 27/02/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#ifndef IffChunkHeader_hpp
#define IffChunkHeader_hpp

#include <stdio.h>
#include <stdint.h>
#include <string>

namespace AiffReader {
  
  struct IffChunkHeader {
    std::string typeId;
    uint32_t chunkLength;
    
    IffChunkHeader();
  };
  
}

#endif /* IffChunkHeader_hpp */

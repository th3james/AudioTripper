//
//  SoundDataChunk.hpp
//  AudioTrip
//
//  Created by James Cox on 27/02/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#ifndef SoundDataChunk_hpp
#define SoundDataChunk_hpp

#include <stdio.h>
#include <stdint.h>
#include <vector>
#include "SampleFrame.hpp"

namespace AiffReader {
  
  struct SoundDataChunk {
    uint32_t    offset;
    uint32_t    blockSize;
    uint32_t    sampleFrameCount;
    uint16_t    channelCount;
    std::vector<SampleFrame> sampleFrames;
    
    SoundDataChunk(int32_t theSampleFrameCount, uint16_t theChannelCount);
  };
  
}

#endif /* SoundDataChunk_hpp */

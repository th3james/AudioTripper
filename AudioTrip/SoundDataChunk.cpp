//
//  SoundDataChunk.cpp
//  AudioTrip
//
//  Created by James Cox on 27/02/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#include "SoundDataChunk.hpp"

namespace AiffReader {
  
  SoundDataChunk::SoundDataChunk(int32_t theSampleFrameCount, uint16_t theChannelCount) {
    sampleFrameCount = theSampleFrameCount;
    channelCount = theChannelCount;
    
    sampleFrames.reserve(sampleFrameCount);
    for(int32_t i = 0; i < sampleFrameCount; i++) {
      sampleFrames.push_back(SampleFrame(channelCount));
    }
  }
  
}
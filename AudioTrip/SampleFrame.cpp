//
//  SampleFrame.cpp
//  AudioTrip
//
//  Created by James Cox on 27/02/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#include "SampleFrame.hpp"

namespace AiffReader {
  SampleFrame::SampleFrame(int16_t theChannelCount) {
    channelCount = theChannelCount;
    samplePoints.reserve(channelCount);
    for(int16_t i = 0; i < channelCount; i++) {
      samplePoints.push_back(0);
    }
  }
}
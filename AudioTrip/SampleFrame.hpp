//
//  SampleFrame.hpp
//  AudioTrip
//
//  Created by James Cox on 27/02/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#ifndef SampleFrame_hpp
#define SampleFrame_hpp

#include <stdio.h>
#include <stdint.h>
#include <vector>

namespace AiffReader {
  
  struct SampleFrame {
    int16_t channelCount;
    std::vector<int16_t> samplePoints;
    
    SampleFrame(int16_t theChannelCount);
  };
  
}

#endif /* SampleFrame_hpp */

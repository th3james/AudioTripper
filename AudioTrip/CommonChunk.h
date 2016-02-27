//
//  CommonChunk.h
//  AudioTrip
//
//  Created by James Cox on 27/02/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#ifndef CommonChunk_h
#define CommonChunk_h

namespace AiffReader {
  struct CommonChunk {
    uint16_t  numChannels;
    uint32_t  numSampleFrames;
    uint16_t  sampleSize;
    uint32_t  sampleRate;
  };
}

#endif /* CommonChunk_h */

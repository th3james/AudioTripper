//
//  AiffReader.hpp
//  AudioTrip
//
//  Created by James Cox on 14/02/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#ifndef AiffReader_hpp
#define AiffReader_hpp

#include <stdio.h>
#include <stdint.h>
#include <fstream>

namespace AiffReader {
  
  struct IffChunkHeader {
    char * typeId;
    uint32_t chunkLength;
    
    ~IffChunkHeader() {
      delete typeId;
    }
  };
  
  struct CommonChunk {
    uint16_t  numChannels;
    uint32_t  numSampleFrames;
    uint16_t  sampleSize;
    uint32_t  sampleRate;
  };

  struct SampleFrame {
    int16_t channelCount;
    int16_t *samplePoints;
    
    void allocate(int16_t theChannelCount) {
      channelCount = theChannelCount;
      samplePoints = new int16_t [channelCount];
    }
    
    ~SampleFrame() {
      delete[] samplePoints;
    }
  };
  
  struct SoundDataChunk {
    uint32_t    offset;
    uint32_t    blockSize;
    uint32_t    sampleFrameCount;
    uint16_t    channelCount;
    SampleFrame *sampleFrames;
    
    SoundDataChunk(int32_t theSampleFrameCount, uint16_t theChannelCount) {
      sampleFrameCount = theSampleFrameCount;
      channelCount = theChannelCount;
      
      sampleFrames = new SampleFrame [sampleFrameCount];
    }
    
    ~SoundDataChunk() {
      delete[] sampleFrames;
    }
  };
  
  uint32_t readULong(std::ifstream& audiofile);
  uint16_t readUShort(std::ifstream& audiofile);
  int16_t readShort(std::ifstream& audiofile);
  
  IffChunkHeader readChunkHeader(std::ifstream& audioFile);
  CommonChunk readCommonChunk(std::ifstream& audioFile);
  SoundDataChunk readSoundDataChunk(
    std::ifstream& audioFile, IffChunkHeader& header, CommonChunk common
  );
  
}


#endif /* AiffReader_hpp */

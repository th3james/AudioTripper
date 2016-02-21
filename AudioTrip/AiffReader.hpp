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
#include <vector>

namespace AiffReader {
  
  struct IffChunkHeader {
    std::string typeId;
    uint32_t chunkLength;
    
    IffChunkHeader() {
      typeId.reserve(4);
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
    std::vector<int16_t> samplePoints;
    
    SampleFrame(int16_t theChannelCount) {
      channelCount = theChannelCount;
      samplePoints.reserve(channelCount);
      for(int16_t i = 0; i < channelCount; i++) {
        samplePoints.push_back(0);
      }
    }
  };
  
  struct SoundDataChunk {
    uint32_t    offset;
    uint32_t    blockSize;
    uint32_t    sampleFrameCount;
    uint16_t    channelCount;
    std::vector<SampleFrame> sampleFrames;
    
    SoundDataChunk(int32_t theSampleFrameCount, uint16_t theChannelCount) {
      sampleFrameCount = theSampleFrameCount;
      channelCount = theChannelCount;
      
      sampleFrames.reserve(sampleFrameCount);
      for(int32_t i = 0; i < sampleFrameCount; i++) {
        sampleFrames.push_back(SampleFrame(channelCount));
      }
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

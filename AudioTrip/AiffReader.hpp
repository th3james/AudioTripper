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

#include "IffChunkHeader.hpp"
#include "CommonChunk.h"
#include "SampleFrame.hpp"
#include "SoundDataChunk.hpp"

namespace AiffReader {
  
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

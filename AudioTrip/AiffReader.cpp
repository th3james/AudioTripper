//
//  AiffReader.cpp
//  AudioTrip
//
//  Created by James Cox on 14/02/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#include "AiffReader.hpp"
#include <assert.h>
#include <libkern/OSByteOrder.h>
using namespace std;

namespace AiffReader {
  uint32_t readULong(ifstream& audioFile) {
    uint32_t number;
    audioFile.read(reinterpret_cast<char*>(&number), sizeof(number));
    return OSSwapBigToHostInt32(number);
  }
  
  uint16_t readUShort(ifstream& audioFile) {
    uint16_t number;
    audioFile.read(reinterpret_cast<char*>(&number), sizeof(number));
    return OSSwapBigToHostInt16(number);
  }
  
  int16_t readShort(ifstream& audioFile) {
    int16_t number;
    audioFile.read(reinterpret_cast<char*>(&number), sizeof(number));
    return OSSwapBigToHostInt16(number);
  }
  
  IffChunkHeader readChunkHeader(ifstream& audioFile) {
    IffChunkHeader header;
    
    int8_t size = 4;
    std::string buffer(size, ' ');
    audioFile.read(&buffer[0], size);
    header.typeId = buffer;
    header.chunkLength = AiffReader::readULong(audioFile);
    
    return header;
  }
  
  CommonChunk readCommonChunk(ifstream& audioFile) {
    CommonChunk chunk;
    
    chunk.numChannels = AiffReader::readUShort(audioFile);
    chunk.numSampleFrames = AiffReader::readULong(audioFile);
    chunk.sampleSize = AiffReader::readUShort(audioFile);
    assert(chunk.sampleSize == 16);
    
    // This isn't actually a UInt, it's a 10 byte extended float
    // Skipping handling it for now
    // chunk.sampleRate = readUInt(audioFile);
    chunk.sampleRate = 0;
    audioFile.seekg(10, ios::cur);
    
    return chunk;
  }
  
  SoundDataChunk readSoundDataChunk(ifstream& audioFile, IffChunkHeader& header, CommonChunk common) {
    SoundDataChunk chunk = SoundDataChunk(
      common.numSampleFrames, common.numChannels
    );
    
    uint32_t remainingBytes = header.chunkLength;
    
    chunk.offset = AiffReader::readULong(audioFile);
    assert(chunk.offset == 0);
    remainingBytes -= sizeof(chunk.offset);
    
    chunk.blockSize = AiffReader::readULong(audioFile);
    assert(chunk.blockSize == 0);
    remainingBytes -= sizeof(chunk.blockSize);

    assert(chunk.sampleFrames.size() > 0);
    for (int32_t sfi = 0; sfi < chunk.sampleFrames.size(); sfi++) {
      SampleFrame& frame = chunk.sampleFrames.at(sfi);
      
      for (uint16_t ci = 0; ci < chunk.channelCount; ci++) {
        assert(remainingBytes > 0);
        
        frame.samplePoints[ci] = readShort(audioFile);
        remainingBytes -= sizeof(frame.samplePoints.at(ci));
      }
    }
    assert(remainingBytes == 0);
    
    return chunk;
  }
}
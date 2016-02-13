//
//  AudioTripper.cpp
//  AudioTrip
//
//  Created by James Cox on 24/01/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#include <stdint.h>
#include <iostream>
#include <fstream>
using namespace std;
#include <libkern/OSByteOrder.h>

#include "AudioTripper.hpp"

namespace AudioTripper {
  struct IffChunkHeader {
    char * typeId;
    uint32_t chunkLength;
    
    ~IffChunkHeader() {
      delete typeId;
    }
  };
  
  struct CommonChunk {
    uint16_t   numChannels;
    uint32_t   numSampleFrames;
    uint16_t   sampleSize;
    uint32_t   sampleRate;
  };
  
  namespace private_details {
    uint32_t readULong(ifstream& audioFile) {
      uint32_t number;
      audioFile.read(reinterpret_cast<char*>(&number), sizeof(number));
      return OSSwapBigToHostInt32(number);
    }
    
    uint16_t readShort(ifstream& audioFile) {
      uint16_t number;
      audioFile.read(reinterpret_cast<char*>(&number), sizeof(number));
      return OSSwapBigToHostInt16(number);
    }
    
    IffChunkHeader readChunkHeader(ifstream& audioFile) {
      IffChunkHeader header = {
        new char
      };
      
      audioFile.read(header.typeId, 4);
      header.chunkLength = readULong(audioFile);
      
      return header;
    }
    
    CommonChunk readCommonChunk(ifstream& audioFile) {
      CommonChunk chunk;
      
      chunk.numChannels = readShort(audioFile);
      chunk.numSampleFrames = readULong(audioFile);
      chunk.sampleSize = readShort(audioFile);
      
      // This isn't actually a UInt, it's a 10 byte extended float
      // Skipping handling it for now
      // chunk.sampleRate = readUInt(audioFile);
      audioFile.seekg(10, ios::cur);
      
      return chunk;
    }
    
    unsigned int readLoudestPeakFromSoundChunk(ifstream& audioFile, IffChunkHeader& header, CommonChunk common) {
      uint32_t remainingBytes = header.chunkLength;
      /*
      unsigned int offset = readULong(audioFile);
      remainingBytes -= sizeof(offset);
      unsigned int blockSize = readULong(audioFile);
      remainingBytes -= sizeof(blockSize);
       */
      
      audioFile.seekg(remainingBytes, ios::cur);
      return 0;
    }
  };
  
  
  struct EvaluatedFile evaluate(const char * filePath) {
    EvaluatedFile evaluatedFile;
    evaluatedFile.filePath = filePath;

    ifstream audioFile;
    audioFile.open(evaluatedFile.filePath, ios::binary);
    
    char fileTypeHeader;
    
    if (audioFile.good()) {
      audioFile.seekg (0, ios::beg);
      
      // Read 'FORM' header
      audioFile.read(&fileTypeHeader, 4);
      // Read file length
      evaluatedFile.fileLength = private_details::readULong(audioFile);
      // Read file format
      evaluatedFile.format = new char;
      audioFile.read(evaluatedFile.format, 4);
      
      CommonChunk common;
      
      while (audioFile.tellg() < evaluatedFile.fileLength) {
        IffChunkHeader header = private_details::readChunkHeader(audioFile);
        if (strncmp(header.typeId, "COMM", 4) == 0) {
          common = private_details::readCommonChunk(audioFile);
        } else if (strncmp(header.typeId, "SSND", 4) == 0) {
          evaluatedFile.loudestPeak = private_details::readLoudestPeakFromSoundChunk(audioFile, header, common);
        } else {
          audioFile.seekg(header.chunkLength, ios::cur);
        }
      };
        
      audioFile.close();
    }
    
    return evaluatedFile;
  };
  
};
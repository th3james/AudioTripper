//
//  AudioTripper.cpp
//  AudioTrip
//
//  Created by James Cox on 24/01/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#include <stdint.h>
#include <assert.h>
#include "AiffReader.hpp"
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
 
    IffChunkHeader readChunkHeader(ifstream& audioFile) {
      IffChunkHeader header = {
        new char
      };
      
      audioFile.read(header.typeId, 4);
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
    
    int16_t readLoudestPeakFromSoundChunk(ifstream& audioFile, IffChunkHeader& header, CommonChunk common) {
      int16_t loudestPeak = 0;
      uint32_t remainingBytes = header.chunkLength;

      uint32_t offset = AiffReader::readULong(audioFile);
      assert(offset == 0);
      remainingBytes -= sizeof(offset);
      
      uint32_t blockSize = AiffReader::readULong(audioFile);
      assert(offset == 0);
      remainingBytes -= sizeof(blockSize);
      
      uint32_t remainingSampleFrames = common.numSampleFrames;
      
      while (remainingSampleFrames > 0) {
        for (uint16_t channelIndex = 0; channelIndex < common.numChannels; channelIndex++) {
          assert(remainingBytes > 0);
          
          int16_t samplePoint = AiffReader::readShort(audioFile);
          if (samplePoint > loudestPeak) {
            loudestPeak = samplePoint;
          }
          remainingBytes -= sizeof(samplePoint);

        }
        remainingSampleFrames--;
      }
      assert(remainingBytes == 0);
      audioFile.seekg(remainingBytes, ios::cur);
      
      return loudestPeak;
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
      evaluatedFile.fileLength = AiffReader::readULong(audioFile);
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
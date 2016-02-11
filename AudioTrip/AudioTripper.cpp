//
//  AudioTripper.cpp
//  AudioTrip
//
//  Created by James Cox on 24/01/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;
#include <libkern/OSByteOrder.h>

#include "AudioTripper.hpp"

namespace AudioTripper {
  struct IffChunkHeader {
    char * typeId;
    unsigned int chunkLength;
    
    ~IffChunkHeader() {
      delete typeId;
    }
  };
  
  struct CommonChunk {
    short          numChannels;
    unsigned int   numSampleFrames;
    short          sampleSize;
    unsigned int   sampleRate;
  };
  
  namespace private_details {
    unsigned int readUInt(ifstream& audioFile) {
      unsigned int number;
      audioFile.read(reinterpret_cast<char*>(&number), sizeof(number));
      return OSSwapBigToHostInt32(number);
    }
    
    short readShort(ifstream& audioFile) {
      unsigned int number;
      audioFile.read(reinterpret_cast<char*>(&number), 2);
      return OSSwapBigToHostInt16(number);
    }
    
    IffChunkHeader readChunkHeader(ifstream& audioFile) {
      IffChunkHeader header = {
        new char
      };
      
      audioFile.read(header.typeId, 4);
      header.chunkLength = readUInt(audioFile);
      
      return header;
    }
    
    CommonChunk readCommonChunk(ifstream& audioFile) {
      CommonChunk chunk;
      
      chunk.numChannels = readShort(audioFile);
      chunk.numSampleFrames = readUInt(audioFile);
      chunk.sampleSize = readShort(audioFile);
      
      // This isn't actually a UInt, it's a 10 byte extended float
      // Skipping handling it for now
      // chunk.sampleRate = readUInt(audioFile);
      audioFile.seekg(10, ios::cur);
      
      return chunk;
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
      evaluatedFile.fileLength = private_details::readUInt(audioFile);
      // Read file format
      evaluatedFile.format = new char;
      audioFile.read(evaluatedFile.format, 4);
      
      CommonChunk common;
      
      while (audioFile.tellg() < evaluatedFile.fileLength) {
        IffChunkHeader header = private_details::readChunkHeader(audioFile);
        if (strncmp(header.typeId, "COMM", 4) == 0) {
          common = private_details::readCommonChunk(audioFile);
        } else {
          audioFile.seekg(header.chunkLength, ios::cur);
        }
      };
        
      audioFile.close();
    }
    
    return evaluatedFile;
  };
  
};
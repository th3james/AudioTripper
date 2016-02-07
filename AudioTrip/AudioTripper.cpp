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
  };
  
  struct CommonChunk {
    IffChunkHeader header;
    
    short          numChannels;
    unsigned long  numSampleFrames;
    short          sampleSize;
    unsigned long  sampleRate;
  };
  
  namespace private_details {
    unsigned int readUInt(ifstream& audioFile) {
      unsigned int number;
      audioFile.read(reinterpret_cast<char*>(&number), sizeof(number));
      return OSSwapBigToHostInt32(number);
    }
    
    IffChunkHeader readChunkHeader(ifstream& audioFile) {
      IffChunkHeader header = {
        new char
      };
      
      audioFile.read(header.typeId, 4);
      header.chunkLength = readUInt(audioFile);
      
      return header;
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
      
      while (audioFile.tellg() < evaluatedFile.fileLength && audioFile.tellg() < 5000) {
        IffChunkHeader header = private_details::readChunkHeader(audioFile);
        cout << header.typeId;
        audioFile.seekg(header.chunkLength, ios::cur);
      };
          
      audioFile.close();
    }
    
    return evaluatedFile;
  };
  
};
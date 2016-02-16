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

  namespace private_details {
    
    int16_t findLoudestPeak(AiffReader::SoundDataChunk soundData) {
      int16_t loudestPeak = 0;
      
      for (int32_t sfi = 0; sfi < soundData.sampleFrameCount; sfi++) {
        AiffReader::SampleFrame sampleFrame = soundData.sampleFrames[sfi];
        
        for (uint16_t ci = 0; ci < sampleFrame.channelCount; ci++) {
          int16_t samplePoint = sampleFrame.samplePoints[ci];
          if (samplePoint > loudestPeak) {
            loudestPeak = samplePoint;
          }
        }
      }
      
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
      
      AiffReader::CommonChunk common;
      
      while (audioFile.tellg() < evaluatedFile.fileLength) {
        AiffReader::IffChunkHeader header = AiffReader::readChunkHeader(audioFile);
        if (strncmp(header.typeId, "COMM", 4) == 0) {
          common = AiffReader::readCommonChunk(audioFile);
        } else if (strncmp(header.typeId, "SSND", 4) == 0) {
          
          AiffReader::SoundDataChunk soundData = AiffReader::readSoundDataChunk(audioFile, header, common);
          evaluatedFile.loudestPeak = private_details::findLoudestPeak(soundData);
        } else {
          audioFile.seekg(header.chunkLength, ios::cur);
        }
      };
        
      audioFile.close();
    }
    
    return evaluatedFile;
  };
  
};
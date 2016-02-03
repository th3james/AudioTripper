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
  namespace private_details {
    unsigned int readFileLength(ifstream& audioFile) {
      unsigned int fileLength;
      audioFile.read(reinterpret_cast<char*>(&fileLength), sizeof(fileLength));
      fileLength = OSSwapBigToHostInt32(fileLength);
      return fileLength;
    }
  };
  
  struct EvaluatedFile evaluate(const char * filePath) {
    EvaluatedFile evaluatedFile;
    evaluatedFile.filePath = filePath;
    
    const unsigned short int bytesToRead = 4;
    ifstream audioFile;
    audioFile.open(evaluatedFile.filePath, ios::binary);
    
    char fileTypeHeader;
    
    if (audioFile.good()) {
      audioFile.seekg (0, ios::beg);
      
      // Read 'FORM' header
      audioFile.read(&fileTypeHeader, bytesToRead);
      
      evaluatedFile.fileLength = private_details::readFileLength(audioFile);
      
      audioFile.close();
    }
    
    return evaluatedFile;
  };
  
};
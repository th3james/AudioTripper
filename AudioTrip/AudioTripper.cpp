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
      audioFile.read(&fileTypeHeader, bytesToRead);
      
      
      audioFile.read(reinterpret_cast<char*>(&evaluatedFile.fileLength), sizeof(evaluatedFile.fileLength));
      // IFF file length numbers are big-endian
      evaluatedFile.fileLength = OSSwapBigToHostInt32(evaluatedFile.fileLength);
      
      audioFile.close();
    }
    
    return evaluatedFile;
  };
  
};
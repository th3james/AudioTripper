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

#include "AudioTripper.hpp"

namespace AudioTripper {
  namespace private_details {
    signed long int readFileLeadingString(const char * filePath) {
      signed long int leadingByteSum = 0;
      const unsigned short int bytesToRead = 4;
      
      ifstream audioFile;
      audioFile.open(filePath, ios::in|ios::binary);
      
      char * memblock = new char[bytesToRead];
      
      if (audioFile.good()) {
        audioFile.seekg (0, ios::beg);
        audioFile.read(memblock, bytesToRead);
        audioFile.close();
        
        for (int i=0; i<bytesToRead; i++) {
          leadingByteSum += (int)memblock[i];
        };
      } else {
        leadingByteSum = -1;
      }

      return leadingByteSum;
    };
  };
  
  struct EvaluatedFile evaluate(const char * filePath) {
    EvaluatedFile file;
    file.filePath = filePath;
    file.loudestPeak = private_details::readFileLeadingString(filePath);
    
    return file;
  };
  
};
//
//  AiffReader.cpp
//  AudioTrip
//
//  Created by James Cox on 14/02/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#include "AiffReader.hpp"
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
}
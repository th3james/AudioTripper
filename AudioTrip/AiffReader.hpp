//
//  AiffReader.hpp
//  AudioTrip
//
//  Created by James Cox on 14/02/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#ifndef AiffReader_hpp
#define AiffReader_hpp

#include <stdio.h>
#include <stdint.h>
#include <fstream>

namespace AiffReader {
  uint32_t readULong(std::ifstream& audiofile);
  uint16_t readUShort(std::ifstream& audiofile);
  int16_t readShort(std::ifstream& audiofile);
}


#endif /* AiffReader_hpp */

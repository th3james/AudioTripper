//
//  AudioTripperTests.cpp
//  AudioTrip
//
//  Created by James Cox on 24/01/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#include "catch.hpp"

#include "AudioTripper.hpp"

TEST_CASE( "AudioTripper::evaluate returns an AudioTripper::EvaluatedFile", "[audioTripper]" ) {
  const char * filePath = "/Users/th3james/src/curricular/cpp/AudioTrip/CPlusPlusTests/fixtures/VoiceSampleWithGap.aif";
  struct AudioTripper::EvaluatedFile result = AudioTripper::evaluate(filePath);
  
  SECTION("with the given file path") {
    CHECK(result.filePath == filePath);
  }
  
  SECTION("with the format") {
    const char * expectedFormat = "AIFF";
    
    CHECK(strcmp(result.format, expectedFormat) == 0);
  }
  
  SECTION("with the loudest peak") {
    uint16_t expectedPeak = 32391;
    
    CHECK(result.loudestPeak == expectedPeak);
  }
  
  SECTION("with length of the file") {
    uint32_t expectedLength = 7042644;
        
    CHECK(result.fileLength == expectedLength);
  }
}
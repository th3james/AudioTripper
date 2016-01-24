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
  
  SECTION("with the loudest peak") {
    const char * formString = "FORM";
    
    signed long int expectedPeak = 0;
    
    // why doesn't sizeof(formString) return 4?
    for (int i = 0; i < 4; i++) {
      expectedPeak += (int)formString[i];
    }
    
    CHECK(result.loudestPeak == expectedPeak);
  }
}
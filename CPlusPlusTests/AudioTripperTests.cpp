//
//  AudioTripperTests.cpp
//  AudioTrip
//
//  Created by James Cox on 24/01/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

#include "catch.hpp"

#include "AudioTripper.hpp"

TEST_CASE( "AudioTripper::evaluate returns an AudioTripper::EvaluatedFile with the given path", "[audioTripper]" ) {
  const char * filePath = "./fixtures/speech.aif";
  struct AudioTripper::EvaluatedFile result = AudioTripper::evaluate(filePath);
  CHECK(result.filePath == filePath);
}
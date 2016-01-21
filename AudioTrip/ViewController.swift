//
//  ViewController.swift
//  AudioTrip
//
//  Created by James Cox on 21/01/2016.
//  Copyright © 2016 James Cox-Morton. All rights reserved.
//

import Cocoa

class ViewController: NSViewController {

  @IBOutlet weak var datLabel: NSTextField!
  
  override func viewDidLoad() {
    super.viewDidLoad()

    var ptr = sayHelloCpp()
    let cppValue = withUnsafePointer(&ptr) { thePtr in
      String.fromCString(thePtr[0])!
    }
    datLabel.stringValue = "Changed \(cppValue)"
  }

  override var representedObject: AnyObject? {
    didSet {
    // Update the view, if already loaded.
    }
  }


}


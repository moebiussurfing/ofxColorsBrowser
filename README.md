ofxColorsBrowser
=============================

# Overview
**ofxColorsBrowser** is an **openFrameworks** addon to browse big color libraries.

## Screenshot
![image](/readme_images/Capture.PNG?raw=true "image")

## Features
* Three included libraries.
  * Pantone (>3000 colors from a JSON file).
  * Open Color.
  * OF Native named colors
* Gui with clickable colored boxes. 
  * Can be completely disabled to simplify.
* Key commands
* Basic parameters and app modes.
* Store/Recall settings.

## Usage
 
### ofApp.h
```.cpp
#include "ofxColorsBrowser.h"

ofxColorsBrowser colorBrowser;
ofFloatColor color_BACK;
```

### ofApp.cpp
```.cpp
ofApp::setup(){
    colorBrowser.setup_colorBACK(color_BACK);// set local target color receiver
    colorBrowser.setup();

ofApp::update(){
	ofxColorsBrowser.update();
}

ofApp::draw(){
    ofBackground( ofColor( color_BACK ));// auto updated when changes
	colorBrowser.draw();
}
```

## Dependencies
 * ofxFontStash
 * ofxGui
 * ofxSurfingHelpers

 Already included into ```/libs```:  
* ofxOpenColor
* ofxRectangleUtils

## Tested systems
- **Windows10** / **VS2017** / **OF ~0.11**
- **macOS High Sierra** / **Xcode 9/10** / **OF ~0.11**

## Author
Addon by **@moebiusSurfing**  
*(ManuMolina). 2020.*

## License
*MIT License.*
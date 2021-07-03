ofxColorsBrowser
=============================

# Overview
An **openFrameworks** add-on to browse many named color libraries imported from JSON files.  

## Screenshots

#### ofxSurfingColors
![image](/readme_images/Capture.PNG?raw=true "image")

## Color Libraries
  * **Pantone** (+2000 colors).
  * [**Sanzo Wada**](https://github.com/dblodorn/sanzo-wada): [A Dictionary of Color Combinations](https://sanzo-wada.dmbk.io/) from **@dblodorn**.
  * [**Crayola**](https://gist.github.com/jjdelc/1868136) from **@jjdelc**.
  * [**Cheprasov**](https://github.com/cheprasov/json-colors) from **@cheprasov**.
  * [**Open Color**](https://github.com/pd-andy/ofxOpenColor) from **@pd-andy**.
  * **OF Native** named colors.

## Features
* Updatable with other text files based libraries (JSON, XML, or other colors libs/addons).
* Cards with seteable amount of colors.
* Sort the library by Hue, Name or with the original sorting.
* **GUI** with clickable colored and named boxes. 
* The interface can be completely disabled to simplify. But still exposing access to the colors.
* Key commands, browse with arrow keys and an **ofxGui** debug panel.
* Basic exposed parameters to integrate in other apps/add-ons. Store/Recall settings.

## Usage
 
### ofApp.h
```.cpp
#include "ofxColorsBrowser.h"

ofxColorsBrowser colorBrowser;
ofFloatColor colorBg;
```

### ofApp.cpp
```.cpp
ofApp::setup()
{
	colorBrowser.setupColorPtr(colorBg); // set local target color "receiver"
	colorBrowser.setup();
}

ofApp::draw()
{
 	ofBackground(colorBg); // auto updated when changes
}
```

## Dependencies
- [ofxSurfingHelpers](https://github.com/moebiussurfing/ofxSurfingHelpers)  
- ofxGui
- [ofxRectangleUtils](https://github.com/bakercp/ofxRectangleUtils) *  
- [ofxFontStash](https://github.com/armadillu/ofxFontStash) *  
- [ofxSurfingImGui](https://github.com/moebiussurfing/ofxSurfingImGui) **  
- [ofxImGui](https://github.com/Daandelange/ofxImGui/) FORK **  
- [ofxWindowApp](https://github.com/moebiussurfing/ofxWindowApp) ***  
* Not required when interface is disabled.  
** Not required when ImGui is disabled.  
*** Not required. For some example only.   
Already bundled into ```OF_ADDON/libs```. No need to add to the **PROJECT GENERATOR**!    
- [ofxOpenColor](https://github.com/pd-andy/ofxOpenColor)  
 
## Tested systems
- **Windows10** / **VS2017** / **OF ~0.11**
- **macOS High Sierra** / **Xcode 9/10** / **OF ~0.11**

## Author
Addon by **@moebiusSurfing**  
*(ManuMolina). 2020.*  

_Thanks to **@bakercp**, **@armadillu**, **@pd-andy** and all the JSON packers linked above for their repositories._  

## License
*MIT License.*

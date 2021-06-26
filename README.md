ofxColorsBrowser
=============================

# Overview
An **openFrameworks** add-on to browse color libraries from JSON files.  

## Screenshot
#### Pantone  
![image](/readme_images/Capture.PNG?raw=true "image")  

#### Wada Sanzo
![image](/readme_images/Capture2.PNG?raw=true "image")

## Color Libraries
  * **Pantone** (+2000 colors from a JSON file).
  * [Wada Sanzo](https://sanzo-wada.dmbk.io/): A Dictionary of Color Combinations.
  * **Open Color**.
  * **OF Native** named colors

## Features
* Technically updatable with other parsed libraries (JSON, XML, or other colors libs/addons).
* Sort by Hue, Name or with the original sorting.
* **GUI** with clickable colored and named boxes. 
* Interface can be completely disabled to simplify. (But still having access to the colors)
* Key commands, browse with arrow keys and **ofxGui** panel.
* Basic parameters and app modes. Store / Recall settings.

## Usage
 
### ofApp.h
```.cpp
#include "ofxColorsBrowser.h"

ofxColorsBrowser colorBrowser;
ofFloatColor color_BACK;
```

### ofApp.cpp
```.cpp
ofApp::setup()
{
  colorBrowser.setup_colorBACK(color_BACK); // set local target color auto-receiver
  colorBrowser.setup();
}

ofApp::update()
{
  ofxColorsBrowser.update();
}

ofApp::draw()
{
  ofColor colorBg = ofColor(color_BACK); // auto updated when a color is picked
  ofBackground(colorBg);
  colorBrowser.draw();
}
```

## Dependencies
- ofxGui
- [ofxSurfingHelpers](https://github.com/moebiussurfing/ofxSurfingHelpers)  

*Not required when interface is disabled:*  
- [ofxRectangleUtils](https://github.com/bakercp/ofxRectangleUtils) 
- [ofxFontStash](https://github.com/armadillu/ofxFontStash)  

Already included into ```/libs```:  
- [ofxOpenColor](https://github.com/pd-andy/ofxOpenColor)  
 
## Tested systems
- **Windows10** / **VS2017** / **OF ~0.11**
- **macOS High Sierra** / **Xcode 9/10** / **OF ~0.11**

## Author
Addon by **@moebiusSurfing**  
*(ManuMolina). 2020.*  

Thanks to **@bakercp**, **@armadillu** and **@pd-andy** for their repositories.  

## License
*MIT License.*

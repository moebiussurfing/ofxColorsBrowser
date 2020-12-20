#pragma once

#include "ofMain.h"
#include "ofxColorsBrowser.h"

class ofApp: public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void exit();
    void keyPressed(int key);

    ofxColorsBrowser ColorBrowser;
    ofFloatColor color_BACK;

    bool SHOW_ColorBrowser = true;
    bool ENABLE_ColorBrowser_Keys = true;
};

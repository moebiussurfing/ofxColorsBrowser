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
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofxColorsBrowser ColorBrowser;
    ofFloatColor color_BACK;

    bool SHOW_ColorBrowser = true;
    bool ENABLE_ColorBrowser_Keys = true;

};

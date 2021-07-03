#pragma once
#include "ofMain.h"

#include "ofxColorsBrowser.h"

/*

NOTE

To run this example out-of-the-box you must do:

1. Uncomment the line:
#define USE_OFX_COLOR_BROWSER_INTERFACE
into ofxColorsBrowser.h
This is to enable the user NATIVE GUI.

2. Remove ofxColorBrowser/src/ImGui folder to not use ImGui at all.

*/

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void windowResized(int w, int h);

	ofxColorsBrowser colorBrowser;

	ofFloatColor colorBg;
};

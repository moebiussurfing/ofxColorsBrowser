#pragma once
#include "ofMain.h"

#include "ofxSurfingColors.h"

/*

NOTE

To run this example out-of-the-box,
you must uncomment the line:
#define USE_OFX_COLOR_BROWSER_INTERFACE
into ofxColorsBrowser.h
This is to enable the user GUI.

*/

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void windowResized(int w, int h);

	ofxSurfingColors surfingColors;

	ofFloatColor colorBg;
};

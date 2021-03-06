#ifdef USE_OFX_COLOR_BROWSER_INTERFACE

//
//  Color_BitmapTextButton.h
//  AnimationBreaker
//
//  Created by Gal Sasson on 1/19/15.
//
//

#ifndef __ofxInterface__Color_BitmapTextButton__
#define __ofxInterface__Color_BitmapTextButton__

#include <stdio.h>
#include "ofMain.h"

#include "ofxInterface.h"
#include "ofxFontStash.h"

namespace ofxInterface
{

    class Color_BitmapTextButton : public Node
    {
    public:

        void setup(const string& label);

        void setBackground(bool set) { bDrawBackground = set; }
        void setBorder(bool set) { bDrawBorder = set; }

        void setLabelColor(const ofColor& c) { labelColor = c; }
        void setBGColor(const ofColor& c) { bgColor = c; }
        void setBorderColor(const ofColor& c) { borderColor = c; }

        void draw();

        void onTouchDown(TouchEvent& event);
        void onTouchMove(TouchEvent& event);
        void onTouchUp(TouchEvent& event);

//private:

        bool bDrawBackground;
        bool bDrawBorder;

        ofColor borderColor;
        ofColor bgColor;
        ofColor labelColor;

        string label;
        bool bLabel = true;
        void setLabelVisible(bool b);

        void setInset(float x, float y);
        float _x = 1;
        float _y = 1;
        void setFontSize(float s);
        float fontSize = 10;
        ofRectangle getTextBox();
        bool loadFont(string file);
        ofxFontStash font;//TODO: Add pointer support to save font loads

        // pointer to the external color that will be updated onClick callback
        void setup_colorBACK(ofFloatColor &c);
        ofFloatColor *colorBACK;
        bool colorBack_DEFINED = false;

    };

}	// namespace

#endif /* defined(__ofxUINode__Color_BitmapTextButton__) */

#endif
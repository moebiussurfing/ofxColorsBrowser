
#include "Color_BitmapTextButton.h"

namespace ofxInterface
{

    void Color_BitmapTextButton::setup(const string &_label)
    {
        label = _label;
        setSize(label.length()*8 + 10, 20);
        setName(label);

        bDrawBorder = true;
        bDrawBackground = true;

        borderColor = ofColor(0);
        bgColor = ofColor(255);
        labelColor = ofColor(0);

        ofAddListener(eventTouchDown, this, &Color_BitmapTextButton::onTouchDown);
        ofAddListener(eventTouchUp, this, &Color_BitmapTextButton::onTouchUp);
        ofAddListener(eventTouchMove, this, &Color_BitmapTextButton::onTouchMove);
    }

    void Color_BitmapTextButton::draw()
    {
        if (bDrawBackground) {
            ofSetColor(bgColor * (isTouched()?0.5:1));
            ofFill();
            ofDrawRectangle(0, 0, getWidth(), getHeight());
        }

        ofSetColor(labelColor);
        ofDrawBitmapString(label, 5, getHeight()-5);

        if (bDrawBorder) {
            ofSetColor(borderColor);
            ofNoFill();
            ofSetLineWidth(1);
            ofDrawRectangle(0, 0, getWidth(), getHeight());
        }
    }

    void Color_BitmapTextButton::onTouchDown(ofxInterface::TouchEvent &event)
    {
//        ofVec2f local = toLocal(event.position);
//
//        color = ofColor(255);
//        bTouched = true;
//
//        touchAnchor = local;
    }

    void Color_BitmapTextButton::onTouchUp(ofxInterface::TouchEvent &event)
    {
//        ofVec2f local = toLocal(event.position);
//
//        color = ofColor(100);
//        bTouched = false;
    }

    void Color_BitmapTextButton::onTouchMove(ofxInterface::TouchEvent &event)
    {
//        ofVec2f parentPos = ((Node*)parent)->toLocal(event.position);
//
//        setPosition(parentPos - touchAnchor);
    }

} 	// namespace

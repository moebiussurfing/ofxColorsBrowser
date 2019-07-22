//
//  ButtonColor.h
//  example-basic
//
//  Created by Gal Sasson on 2/4/15.
//
//

#ifndef __example_basic__ButtonColor__
#define __example_basic__ButtonColor__

#include <stdio.h>
#include "ofMain.h"

#include "ofxInterface.h"

using namespace ofxInterface;

/******
 * This is ButtonColor
 * It's a button that can be dragged around
 *
 * ofxInterface::Node is a subclass of ofNode with additional 
 * features.
 *
 * The two most important features are:
 *
 * 1. the 'draw' function: override it to draw your ui component,
 *    in local space, will be called by 'render'.
 *
 * 2. the 'contains' function: override to return if a point is inside the
 *    component. If your component is rectangular you do not have to provide 
 *    your own contains function, instead, call 'setSize()' on setup
 *    and the default implementation of 'contains' will take care of that.
 *
 */

class ButtonColor : public ofxInterface::Node
{

public:
	void setup(float x, float y, float w, float h);

	void update();
	void draw();


	void onTouchDown(TouchEvent& event);
	void onTouchMove(TouchEvent& event);
	void onTouchUp(TouchEvent& event);


	ofColor color;
	ofVec2f touchAnchor;

	bool bTouched;

};

#endif /* defined(__example_basic__ButtonColor__) */

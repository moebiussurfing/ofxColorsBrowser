//
//  ButtonColor.cpp
//  example-basic
//
//  Created by Gal Sasson on 2/4/15.
//
//

#include "ButtonColor.h"


void ButtonColor::setup(float x, float y, float w, float h)
{
	/*****
	 * you get these from ofxInterface::Node
	 */
	setPosition(x, y);
	setSize(w, h);

	color = ofColor(100);
	bTouched = false;

	/*****
	 * register for touch events
	 *
	 * TouchManager will notify these automatically
	 */
	ofAddListener(eventTouchDown, this, &ButtonColor::onTouchDown);
	ofAddListener(eventTouchUp, this, &ButtonColor::onTouchUp);
	ofAddListener(eventTouchMove, this, &ButtonColor::onTouchMove);
}

void ButtonColor::update()
{
}

void ButtonColor::draw()
{
	/*****
	 * always draw in local space
	 */

	// draw the frame
	ofSetColor(color);
	ofNoFill();
	ofDrawRectangle(0, 0, getWidth(), getHeight());

	// draw the touch anchor
	if (bTouched) {
		ofSetColor(150, 200, 255);
		ofFill();
		ofDrawEllipse(touchAnchor, 10, 10);
	}
}


void ButtonColor::onTouchDown(ofxInterface::TouchEvent &event)
{
	/*****
	 * event.position is always in global space, use toLocal
	 */

	ofVec2f local = toLocal(event.position);

	color = ofColor(255);
	bTouched = true;

	touchAnchor = local;
}

void ButtonColor::onTouchUp(ofxInterface::TouchEvent &event)
{
	ofVec2f local = toLocal(event.position);

	color = ofColor(100);
	bTouched = false;
}


void ButtonColor::onTouchMove(ofxInterface::TouchEvent &event)
{
	ofVec2f parentPos = ((Node*)parent)->toLocal(event.position);

	setPosition(parentPos - touchAnchor);
}
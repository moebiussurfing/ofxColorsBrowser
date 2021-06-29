#include "myClassBasic.h"
//--------------------------------------------------------------
myClassBasic::myClassBasic(){
	ofAddListener(ofEvents().update, this, &myClassBasic::update);
	ofAddListener(ofEvents().keyPressed, this, &myClassBasic::keyPressed);
}

//--------------------------------------------------------------
myClassBasic::~myClassBasic(){
	ofRemoveListener(ofEvents().update, this, &myClassBasic::update);
	ofRemoveListener(ofEvents().keyPressed, this, &myClassBasic::keyPressed);
}

//--------------------------------------------------------------
void myClassBasic::setup(){
}

////--------------------------------------------------------------
//void myClassBasic::update(){
//}

//--------------------------------------------------------------
void myClassBasic::update(ofEventArgs & args)
{
}

//--------------------------------------------------------------
void myClassBasic::draw(){
}

//--------------------------------------------------------------
void myClassBasic::keyPressed(ofKeyEventArgs &eventArgs)
{
	const int key = eventArgs.key;

	// modifiers
	bool mod_COMMAND = eventArgs.hasModifier(OF_KEY_COMMAND);
	bool mod_CONTROL = eventArgs.hasModifier(OF_KEY_CONTROL);
	bool mod_ALT = eventArgs.hasModifier(OF_KEY_ALT);
	bool mod_SHIFT = eventArgs.hasModifier(OF_KEY_SHIFT);

	ofLogNotice(__FUNCTION__) << " : " << key;

	//--

	if (false){}

	else if (key == 'G' && !mod_ALT)
	{
	}
}

//--------------------------------------------------------------
void myClassBasic::exit(){
}

//--------------------------------------------------------------
void myClassBasic::setBool(bool b){
		ofLogNotice(__FUNCTION__) << ofToString(b?"true":"false");
}

//--------------------------------------------------------------
bool myClassBasic::getBool(){
	return true;
}


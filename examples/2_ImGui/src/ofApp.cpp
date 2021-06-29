#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);

	surfingColors.setupColorPtr(colorBg); // set local target color receiver
	surfingColors.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(colorBg); // auto updated when changes
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	//if (key == OF_KEY_F1) colorBrowser.setNextColor();
	//if (key == OF_KEY_F2) colorBrowser.setNextColorRow();
	//if (key == OF_KEY_F3) colorBrowser.setNextCard();
	//if (key == OF_KEY_F4) colorBrowser.setNextCardRow();
	//if (key == OF_KEY_F5) colorBrowser.setRandomColor();
	//if (key == OF_KEY_F6) colorBrowser.setRandomCard();
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	surfingColors.windowResized(w, h);
}
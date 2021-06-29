#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);

	colorBrowser.setupColorPtr(colorBg); // set local target color receiver
	colorBrowser.setup();
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

#ifndef USE_OFX_COLOR_BROWSER_INTERFACE
	colorBrowser.loa
#endif	
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	colorBrowser.windowResized(w, h);
}
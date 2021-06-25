#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    colorBrowser.setup_colorBACK(color_BACK);// set local target color receiver

    colorBrowser.setup();

    colorBrowser.setVisible(true);
}

//--------------------------------------------------------------
void ofApp::update(){
	colorBrowser.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground( ofColor( color_BACK ));// auto updated when changes

	colorBrowser.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	colorBrowser.windowResized(w, h);
}


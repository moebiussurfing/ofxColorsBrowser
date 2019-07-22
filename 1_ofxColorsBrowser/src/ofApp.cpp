#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(64);
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();

    ColorBrowser.setup_colorBACK(color_BACK);
    ColorBrowser.setPosition(glm::vec2(300, 10));
	ColorBrowser.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	ColorBrowser.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofBackground(color_BACK);
    ofClear(ofColor( color_BACK ));
	ColorBrowser.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){
	ColorBrowser.exit();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

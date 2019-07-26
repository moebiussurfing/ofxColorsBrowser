#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(64);

    ColorBrowser.setBoxSize(25);
    ColorBrowser.setRowsSize(5);
    ColorBrowser.setup_colorBACK(color_BACK);
    ColorBrowser.setPosition(glm::vec2(30, 80));
	ColorBrowser.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	ColorBrowser.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground( ofColor( color_BACK ));
	ColorBrowser.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){
	ColorBrowser.exit();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == ' ')
        ColorBrowser.switch_palette_Type();

    if (key == OF_KEY_RETURN)
        ColorBrowser.switch_sorted_Type();
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

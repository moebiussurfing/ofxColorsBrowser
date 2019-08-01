#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(64);
    ofSetFrameRate(30);
    
    ColorBrowser.setBoxSize(15);
    ColorBrowser.setRowsSize(7*8);
//    ColorBrowser.setRowsSize(5);
    ColorBrowser.setup_colorBACK(color_BACK);

    ColorBrowser.setPosition(glm::vec2(220, 80));
    ColorBrowser.setPositionHelper(glm::vec2(ofGetWidth()-250, 20));

    ColorBrowser.setup();

    ColorBrowser.setVisible(SHOW_ColorBrowser);
    ColorBrowser.setVisible_debugText(SHOW_ColorBrowser);
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

//    if (key == 'p')
//        ColorBrowser.switch_palette_Type();
//
//    if (key == 's')
//        ColorBrowser.switch_sorted_Type();

    if (key == 'g')
    {
        SHOW_ColorBrowser =!SHOW_ColorBrowser;
        ColorBrowser.setVisible(SHOW_ColorBrowser);
        ColorBrowser.setVisible_debugText(SHOW_ColorBrowser);
    }

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


#pragma once

#include "ofMain.h"

#include "ofxOpenColor.h"
#include "ofxInterface.h"
#include "ofxInterfaceWidgets.h"
#include "Color_BitmapTextButton.h"

using namespace ofxInterface;

#if (_MSC_VER)
#define strcasecmp _stricmp
#endif

typedef struct
{
    string name;
    ofColor color;
} colorNameMapping;

enum {
    OFX_COLOR_NATIVE,
    OFX_OPEN_COLOR
};

class ofxColorsBrowser {

public:

    ofxColorsBrowser();
    ~ofxColorsBrowser();

    void setup();
    void update();
    void draw();
    void draw_native();
    void exit();

    map < string, ofColor > colorNameMap;
    vector < colorNameMapping > colorNames;

    ofPoint mouseSmoothed;
    int sortedType;             // keep track of which sort we've done
    float mouseX, mouseY;

    int MODE_COLOR;
    void generateColors();

    ofxInterface::Node* scene;
    vector<Color_BitmapTextButton*> buttons_txt;
    void populateScene();
    void clearPopulate();
    bool bShowDebug = false;

    glm::vec2 position;
    void setPosition(glm::vec2 p);

    ofFloatColor color_BACK;
    void setup_colorBACK(ofFloatColor &c);

private:

    void keyPressed( ofKeyEventArgs& eventArgs);
    void keyReleased( ofKeyEventArgs& eventArgs );
    void addKeysListeners();
    void removeKeysListeners();

    void mouseDragged( ofMouseEventArgs& eventArgs );
    void mousePressed( ofMouseEventArgs& eventArgs );
    void mouseReleased( ofMouseEventArgs& eventArgs );
    void addMouseListeners();
    void removeMouseListeners();

};

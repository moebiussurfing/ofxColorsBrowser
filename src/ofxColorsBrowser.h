
#pragma once

#include "ofMain.h"
#include "ofxOpenColor.h"

#if (_MSC_VER)
#define strcasecmp _stricmp
#endif

typedef struct
{
    string name;
    ofColor color;
} colorNameMapping;

enum {
    OFX_COLOR_NATIVE = 0,
    OFX_OPEN_COLOR
};

class ofxColorsBrowser {

public:

    ofxColorsBrowser();
    ~ofxColorsBrowser();

    void setup();
    void update();
    void draw();
    void exit();

    map < string, ofColor > colorNameMap;
    vector < colorNameMapping > colorNames;
    ofPoint mouseSmoothed;
    int sortedType;             // keep track of which sort we've done

    float mouseX, mouseY;

    int MODE_COLOR;

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


#pragma once

#include "ofMain.h"

#include "ofxOpenColor.h"
#include "ofxRectangleUtils.h"
#include "ofxRectangle.h"
using namespace ofx;

#define KEY_SHORTCUTS_ENABLE; // internal shorcuts no add listeners or remove

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

//--

    ofxColorsBrowser();
    ~ofxColorsBrowser();

    void setup();
    void update();
    void draw();
    void exit();

    //----

    // API

    void setPosition(glm::vec2 p);
    void switch_palette_Type();
    void switch_sorted_Type();
    void set_palette_Type(int p);
    void set_sorted_Type(int p);

    void setRowsSize(int rows);
    void setBoxSize(float size);

    void setVisible(bool b);
    void setVisible_debugText(bool b);

    void set_ENABLE_clicks(bool b)
    {
        ENABLE_clicks = b;
    }

    void set_ENABLE_keys(bool b)
    {
        ENABLE_keys = b;
        if(ENABLE_keys)
            addKeysListeners();
        else
            removeKeysListeners();
    }

    void setup_colorBACK(ofFloatColor &c);

    // TODO:
    void setSize(glm::vec2 size);

    //----

    // OFXRECTANGLE MODE

    std::vector<ofxRectangle> rectangles;
    std::vector<ofRectangle*> selectedRects;
    ofxRectangle selectedRectsBoundingBox;
    ofxRectangle* draggingRectPtr;
    glm::vec2 dragStart;
    bool isSelecting;
    ofRectangle selectionRect;
    ofAlignHorz hAlign;
    ofAlignVert vAlign;
    ofRectangle* anchorRect;
    string keyboardCommands;
    bool showKeyboardCommands;
    std::vector<ofRectangle>  packedRects;
//    ofRotatedRectangle rotatedRect;
//    ofRectanglePacker packer;
    void rectangles_update();
    void rectangles_draw();

    //--

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

    //-

    bool SHOW_debugText = false;
    bool SHOW_ColorsBrowse = true;
    bool ENABLE_clicks = true;
    bool ENABLE_keys = false;

    vector<ofColor> palete;
    vector<ofColor> getPalette();

    ofFloatColor color_BACK;
    ofFloatColor color_BACK_PRE;
    ofFloatColor *color_BACK_OFAPP;

    void generateColors();
    map < string, ofColor > colorNameMap;
    vector < colorNameMapping > colorNames;

    void populateScene();
    void clearPopulate();
    bool bShowDebug = false;

    //-

    glm::vec2 position;
    int MODE_COLOR; // 0: OFX_COLOR_NATIVE, 1: OFX_OPEN_COLOR
    int MODE_SORTING;
    int perRow = 10;
    float size = 50;//boxes
    float pad = 2;
};

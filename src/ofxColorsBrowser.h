
#pragma once

#include "ofMain.h"

#include "ofxColourLoversHelper.h"

#include "ofxOpenColor.h"
#include "ofxInterfaceWidgets.h"
#include "Color_BitmapTextButton.h"

#include "ofxRectangleUtils.h"
#include "ofxRectangle.h"
using namespace ofx;

#include "ofxInterface.h"
using namespace ofxInterface;
#if (_MSC_VER)
#define strcasecmp _stricmp
#endif

//#define KEY_SHORTCUTS_ENABLE;// shorcuts

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

    map < string, ofColor > colorNameMap;
    vector < colorNameMapping > colorNames;

//    void draw_native();
//    ofPoint mouseSmoothed;
//    float mouseX, mouseY;

    void generateColors();

    ofxInterface::Node* scene;
    vector<Color_BitmapTextButton*> buttons_txt;
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

    //--

    // API

    void setPosition(glm::vec2 p);
    void switch_palette_Type();
    void switch_sorted_Type();
    void set_palette_Type(int p);
    void set_sorted_Type(int p);

    void setRowsSize(int rows);
    void setBoxSize(float size);
    // TODO:
    void setSize(glm::vec2 size);

    //--

    ofFloatColor color_BACK;
    ofFloatColor color_BACK_PRE;
    void setup_colorBACK(ofFloatColor &c);
    ofFloatColor *color_BACK_OFAPP;
//    void Changed_color_clicked(ofFloatColor &color);

    //--

    // COLOUR LOVERS

    ofxColourLoversHelper ColourLoversHelper;
    void ColourLover_setup();
    void ColourLover_draw();
    ofColor myColor;
    vector<ofColor> myPalette;
    string myPalette_Name = "";

    //--

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

//    ofRotatedRectangle rotatedRect;
    std::vector<ofRectangle>  packedRects;

//    ofRectanglePacker packer;

    void rectangles_update();
    void rectangles_draw();

    //--

//private:

    void keyPressed( ofKeyEventArgs& eventArgs);
    void keyReleased( ofKeyEventArgs& eventArgs );
    void addKeysListeners();
    void removeKeysListeners();

    void mouseDragged( ofMouseEventArgs& eventArgs );
    void mousePressed( ofMouseEventArgs& eventArgs );
    void mouseReleased( ofMouseEventArgs& eventArgs );
    void addMouseListeners();
    void removeMouseListeners();


    bool SHOW_debugText = false;
    void setVisible_debugText(bool b);
};

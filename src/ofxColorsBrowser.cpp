#include "ofxColorsBrowser.h"

//--------------------------------------------------------------
void ofxColorsBrowser::setVisible(bool b)
{
    SHOW_ColorsBrowse = b;
    set_ENABLE_clicks(b);
}

//--------------------------------------------------------------

// comparing colors to sorting methods

bool compareName( const colorNameMapping& s1, const colorNameMapping& s2 ) {
    return s1.name < s2.name;
}

bool compareBrightness( const colorNameMapping& s1, const colorNameMapping& s2 ) {
    return s1.color.getBrightness() < s2.color.getBrightness();
}

bool compareHue( const colorNameMapping& s1, const colorNameMapping& s2 ) {
    return s1.color.getHue() < s2.color.getHue();
}

bool compareSaturation( const colorNameMapping& s1, const colorNameMapping& s2 ) {
    return s1.color.getSaturation() < s2.color.getSaturation();
}

//--------------------------------------------------------------
ofxColorsBrowser::ofxColorsBrowser()
{
    addMouseListeners();

#ifdef KEY_SHORTCUTS_ENABLE
    set_ENABLE_keys(true);
#else
    set_ENABLE_keys(false);
#endif
}

//--------------------------------------------------------------
void ofxColorsBrowser::generate_ColorsInPalette(){
    colorNames.clear();
    colorNameMap.clear();

    //--

    // 1. OFX_PANTONE_COLORS

    if (MODE_COLOR == OFX_PANTONE_COLORS)
    {
        for (int i=0; i<pantoneNames.size(); i++)
        {
            colorNameMap[pantoneNames[i]] = pantoneColors[i];
        }
    }

    //-

    // 2. OFX_OPEN_COLOR

    else if (MODE_COLOR == OFX_OPEN_COLOR)
    {
        bool flipOrder = true;
        int iFlip;

#define NUM_COLORS_ROW 10
        for (int i = 0; i<NUM_COLORS_ROW; i++)
        {
            if (flipOrder)
                iFlip = (NUM_COLORS_ROW-1)-i;
            else
                iFlip = i;

            //  Gray
            colorNameMap["GREY " + ofToString(i)] = oc_gray_[iFlip];//flip order: iFlip
            //  Red
            colorNameMap["RED " + ofToString(i)] = oc_red_[iFlip];
            //  Pink
            colorNameMap["PINK " + ofToString(i)] = oc_pink_[iFlip];
            //  Grape
            colorNameMap["GRAPE " + ofToString(i)] = oc_grape_[iFlip];
            //  Violet
            colorNameMap["VIOLET " + ofToString(i)] = oc_violet_[iFlip];
            //  Indigo
            colorNameMap["INDIGO " + ofToString(i)] = oc_indigo_[iFlip];
            //  Blue
            colorNameMap["BLUE " + ofToString(i)] = oc_blue_[iFlip];
            //  Cyan
            colorNameMap["CYAN " + ofToString(i)] = oc_cyan_[iFlip];
            //  Teal
            colorNameMap["TEAL " + ofToString(i)] = oc_teal_[iFlip];
            //  Green
            colorNameMap["GREEN " + ofToString(i)] = oc_green_[iFlip];
            //  Lime
            colorNameMap["LIME " + ofToString(i)] =  oc_lime_[iFlip];
            //  Yellow
            colorNameMap["YELLOW " + ofToString(i)] =  oc_yellow_[iFlip];
            //  Orange
            colorNameMap["ORANGE " + ofToString(i)] =  oc_orange_[iFlip];
        }
    }

    //-

        // 3. OFX_COLOR_NATIVE

    else if (MODE_COLOR == OFX_COLOR_NATIVE)
    {
        // build a map from name to ofColor of all the named OF colors;

        colorNameMap["white"] = ofColor::white;
        colorNameMap["gray"] = ofColor::gray;
        colorNameMap["black"] = ofColor::black;
        colorNameMap["red"] = ofColor::red;
        colorNameMap["green"] = ofColor::green;
        colorNameMap["blue"] = ofColor::blue;
        colorNameMap["cyan"] = ofColor::cyan;
        colorNameMap["magenta"] = ofColor::magenta;
        colorNameMap["yellow"] = ofColor::yellow;
        colorNameMap["aliceBlue"] = ofColor::aliceBlue;
        colorNameMap["antiqueWhite"] = ofColor::antiqueWhite;
        colorNameMap["aqua"] = ofColor::aqua;
        colorNameMap["aquamarine"] = ofColor::aquamarine;
        colorNameMap["azure"] = ofColor::azure;
        colorNameMap["beige"] = ofColor::beige;
        colorNameMap["bisque"] = ofColor::bisque;
        colorNameMap["blanchedAlmond"] = ofColor::blanchedAlmond;
        colorNameMap["blueViolet"] = ofColor::blueViolet;
        colorNameMap["brown"] = ofColor::brown;
        colorNameMap["burlyWood"] = ofColor::burlyWood;
        colorNameMap["cadetBlue"] = ofColor::cadetBlue;
        colorNameMap["chartreuse"] = ofColor::chartreuse;
        colorNameMap["chocolate"] = ofColor::chocolate;
        colorNameMap["coral"] = ofColor::coral;
        colorNameMap["cornflowerBlue"] = ofColor::cornflowerBlue;
        colorNameMap["cornsilk"] = ofColor::cornsilk;
        colorNameMap["crimson"] = ofColor::crimson;
        colorNameMap["darkBlue"] = ofColor::darkBlue;
        colorNameMap["darkCyan"] = ofColor::darkCyan;
        colorNameMap["darkGoldenRod"] = ofColor::darkGoldenRod;
        colorNameMap["darkGray"] = ofColor::darkGray;
        colorNameMap["darkGrey"] = ofColor::darkGrey;
        colorNameMap["darkGreen"] = ofColor::darkGreen;
        colorNameMap["darkKhaki"] = ofColor::darkKhaki;
        colorNameMap["darkMagenta"] = ofColor::darkMagenta;
        colorNameMap["darkOliveGreen"] = ofColor::darkOliveGreen;
        colorNameMap["darkorange"] = ofColor::darkorange;
        colorNameMap["darkOrchid"] = ofColor::darkOrchid;
        colorNameMap["darkRed"] = ofColor::darkRed;
        colorNameMap["darkSalmon"] = ofColor::darkSalmon;
        colorNameMap["darkSeaGreen"] = ofColor::darkSeaGreen;
        colorNameMap["darkSlateBlue"] = ofColor::darkSlateBlue;
        colorNameMap["darkSlateGray"] = ofColor::darkSlateGray;
        colorNameMap["darkSlateGrey"] = ofColor::darkSlateGrey;
        colorNameMap["darkTurquoise"] = ofColor::darkTurquoise;
        colorNameMap["darkViolet"] = ofColor::darkViolet;
        colorNameMap["deepPink"] = ofColor::deepPink;
        colorNameMap["deepSkyBlue"] = ofColor::deepSkyBlue;
        colorNameMap["dimGray"] = ofColor::dimGray;
        colorNameMap["dimGrey"] = ofColor::dimGrey;
        colorNameMap["dodgerBlue"] = ofColor::dodgerBlue;
        colorNameMap["fireBrick"] = ofColor::fireBrick;
        colorNameMap["floralWhite"] = ofColor::floralWhite;
        colorNameMap["forestGreen"] = ofColor::forestGreen;
        colorNameMap["fuchsia"] = ofColor::fuchsia;
        colorNameMap["gainsboro"] = ofColor::gainsboro;
        colorNameMap["ghostWhite"] = ofColor::ghostWhite;
        colorNameMap["gold"] = ofColor::gold;
        colorNameMap["goldenRod"] = ofColor::goldenRod;
        colorNameMap["grey"] = ofColor::grey;
        colorNameMap["greenYellow"] = ofColor::greenYellow;
        colorNameMap["honeyDew"] = ofColor::honeyDew;
        colorNameMap["hotPink"] = ofColor::hotPink;
        colorNameMap["indianRed "] = ofColor::indianRed;
        colorNameMap["indigo "] = ofColor::indigo;
        colorNameMap["ivory"] = ofColor::ivory;
        colorNameMap["khaki"] = ofColor::khaki;
        colorNameMap["lavender"] = ofColor::lavender;
        colorNameMap["lavenderBlush"] = ofColor::lavenderBlush;
        colorNameMap["lawnGreen"] = ofColor::lawnGreen;
        colorNameMap["lemonChiffon"] = ofColor::lemonChiffon;
        colorNameMap["lightBlue"] = ofColor::lightBlue;
        colorNameMap["lightCoral"] = ofColor::lightCoral;
        colorNameMap["lightCyan"] = ofColor::lightCyan;
        colorNameMap["lightGoldenRodYellow"] = ofColor::lightGoldenRodYellow;
        colorNameMap["lightGray"] = ofColor::lightGray;
        colorNameMap["lightGrey"] = ofColor::lightGrey;
        colorNameMap["lightGreen"] = ofColor::lightGreen;
        colorNameMap["lightPink"] = ofColor::lightPink;
        colorNameMap["lightSalmon"] = ofColor::lightSalmon;
        colorNameMap["lightSeaGreen"] = ofColor::lightSeaGreen;
        colorNameMap["lightSkyBlue"] = ofColor::lightSkyBlue;
        colorNameMap["lightSlateGray"] = ofColor::lightSlateGray;
        colorNameMap["lightSlateGrey"] = ofColor::lightSlateGrey;
        colorNameMap["lightSteelBlue"] = ofColor::lightSteelBlue;
        colorNameMap["lightYellow"] = ofColor::lightYellow;
        colorNameMap["lime"] = ofColor::lime;
        colorNameMap["limeGreen"] = ofColor::limeGreen;
        colorNameMap["linen"] = ofColor::linen;
        colorNameMap["maroon"] = ofColor::maroon;
        colorNameMap["mediumAquaMarine"] = ofColor::mediumAquaMarine;
        colorNameMap["mediumBlue"] = ofColor::mediumBlue;
        colorNameMap["mediumOrchid"] = ofColor::mediumOrchid;
        colorNameMap["mediumPurple"] = ofColor::mediumPurple;
        colorNameMap["mediumSeaGreen"] = ofColor::mediumSeaGreen;
        colorNameMap["mediumSlateBlue"] = ofColor::mediumSlateBlue;
        colorNameMap["mediumSpringGreen"] = ofColor::mediumSpringGreen;
        colorNameMap["mediumTurquoise"] = ofColor::mediumTurquoise;
        colorNameMap["mediumVioletRed"] = ofColor::mediumVioletRed;
        colorNameMap["midnightBlue"] = ofColor::midnightBlue;
        colorNameMap["mintCream"] = ofColor::mintCream;
        colorNameMap["mistyRose"] = ofColor::mistyRose;
        colorNameMap["moccasin"] = ofColor::moccasin;
        colorNameMap["navajoWhite"] = ofColor::navajoWhite;
        colorNameMap["navy"] = ofColor::navy;
        colorNameMap["oldLace"] = ofColor::oldLace;
        colorNameMap["olive"] = ofColor::olive;
        colorNameMap["oliveDrab"] = ofColor::oliveDrab;
        colorNameMap["orange"] = ofColor::orange;
        colorNameMap["orangeRed"] = ofColor::orangeRed;
        colorNameMap["orchid"] = ofColor::orchid;
        colorNameMap["paleGoldenRod"] = ofColor::paleGoldenRod;
        colorNameMap["paleGreen"] = ofColor::paleGreen;
        colorNameMap["paleTurquoise"] = ofColor::paleTurquoise;
        colorNameMap["paleVioletRed"] = ofColor::paleVioletRed;
        colorNameMap["papayaWhip"] = ofColor::papayaWhip;
        colorNameMap["peachPuff"] = ofColor::peachPuff;
        colorNameMap["peru"] = ofColor::peru;
        colorNameMap["pink"] = ofColor::pink;
        colorNameMap["plum"] = ofColor::plum;
        colorNameMap["powderBlue"] = ofColor::powderBlue;
        colorNameMap["purple"] = ofColor::purple;
        colorNameMap["rosyBrown"] = ofColor::rosyBrown;
        colorNameMap["royalBlue"] = ofColor::royalBlue;
        colorNameMap["saddleBrown"] = ofColor::saddleBrown;
        colorNameMap["salmon"] = ofColor::salmon;
        colorNameMap["sandyBrown"] = ofColor::sandyBrown;
        colorNameMap["seaGreen"] = ofColor::seaGreen;
        colorNameMap["seaShell"] = ofColor::seaShell;
        colorNameMap["sienna"] = ofColor::sienna;
        colorNameMap["silver"] = ofColor::silver;
        colorNameMap["skyBlue"] = ofColor::skyBlue;
        colorNameMap["slateBlue"] = ofColor::slateBlue;
        colorNameMap["slateGray"] = ofColor::slateGray;
        colorNameMap["slateGrey"] = ofColor::slateGrey;
        colorNameMap["snow"] = ofColor::snow;
        colorNameMap["springGreen"] = ofColor::springGreen;
        colorNameMap["steelBlue"] = ofColor::steelBlue;
        colorNameMap["tan"] = ofColor::tan;
        colorNameMap["teal"] = ofColor::teal;
        colorNameMap["thistle"] = ofColor::thistle;
        colorNameMap["tomato"] = ofColor::tomato;
        colorNameMap["turquoise"] = ofColor::turquoise;
        colorNameMap["violet"] = ofColor::violet;
        colorNameMap["wheat"] = ofColor::wheat;
        colorNameMap["whiteSmoke"] = ofColor::whiteSmoke;
        colorNameMap["yellowGreen"] = ofColor::yellowGreen;
    }

    // this map is useful if we want to address the colors by string.
    // since we might want to sort this, we can put them in a vector also

    for (unsigned int i = 0; i < colorNameMap.size(); i++){

        map<string, ofColor>::iterator mapEntry = colorNameMap.begin();
        std::advance( mapEntry, i );

        colorNameMapping mapping;
        mapping.name = mapEntry->first;
        mapping.color = mapEntry->second;
        colorNames.push_back(mapping);

    }

    MODE_SORTING = 1; // by name, at the start

    //-
}

/*
 These string to hex conversions aren't trivial.
 */
static int stringToHex(string hex){
    int aHex;
    stringstream convert ( hex );
    convert>> std::hex >> aHex;
    return aHex;
}

static void hexToColor(ofColor &col,string hex){
    string r = hex.substr(0,2);
    int ri = stringToHex(r);
    string g = hex.substr(2,2);
    int gi = stringToHex(g);
    string b = hex.substr(4,2);
    int bi = stringToHex(b);
    col.set(ri,gi,bi);
}

//--------------------------------------------------------------
void ofxColorsBrowser::load_Pantone_JSON(){

    pantoneNames.clear();
    pantoneColors.clear();

    string path = "colors/pantone-colors.json";
    ofFile file(path);
    if(file.exists()){
        file >> js;
        cout << js;
        cout<< endl;

        int i;
        i=0;
        for (auto & jsName: js["names"]){
            cout << "NAMES  ["<<i<<"] "<<jsName<<endl;
            pantoneNames.push_back(jsName);
            i++;
        }

        i=0;
        for (auto & jsValues: js["values"]){
            cout << "VALUES ["<<i<<"] "<<jsValues<<endl;

            ofColor c;
            string colorHEXcode = ofToString(jsValues);
//            cout<<"COLOR HEX:"<<colorHEXcode<<endl;
            vector<string> colorHEXcode_VEC = ofSplitString(colorHEXcode, "#");
            string myCol = colorHEXcode_VEC[1];
//            cout<<"myCol:"<<myCol<<endl;
            vector<string> myCol2 = ofSplitString(myCol, "\"");
//            cout<<"myCol2:"<<myCol2[0]<<endl;
            hexToColor(c,myCol2[0]);
//            cout<<"hexToColor: "<<c<<endl;

            pantoneColors.push_back(c);
            i++;
        }
    }
    else
    {
        ofLogNotice("")<<"FILE '"<<path<<"' NOT FOUND!";
    }
}

//--------------------------------------------------------------
void ofxColorsBrowser::setup(){

    //--

    // PANTONE COLORS
    load_Pantone_JSON();

    //--

    // default palette mode

    MODE_COLOR = OFX_PANTONE_COLORS;
//    MODE_COLOR = OFX_OPEN_COLOR;

    generate_ColorsInPalette();

    //--

    populate_colorsBoxes();

    //-

    set_ENABLE_clicks(true);

    setVisible_debugText(false);

    //--
}


//--------------------------------------------------------------
vector<ofColor> ofxColorsBrowser::getPalette()
{
    ofLogNotice("ofxColorsBrowser") << "getPalette:";

    int numColors = colorNames.size();
    ofLogNotice("ofxColorsBrowser") << "numColors:" << numColors;

    vector<ofColor> _palette;
    _palette.resize(numColors);

    for (int i = 0; i < colorNames.size(); i++)
    {
        ofLogNotice("ofxColorsBrowser") << "color: "+ofToString(i)+"_"+ofToString( _palette[i] );
        _palette[i] = colorNames[i].color;
    }

    return _palette;
}


//--------------------------------------------------------------
void ofxColorsBrowser::populate_colorsBoxes()
{
    float x = position.x;
    float y = position.y;

    //--

    // 1. OFXRECTANGLE MODE

    isSelecting     = false;
    draggingRectPtr = NULL;

    // create a random set of rectangles to play with
    for (int i = 0; i < colorNames.size(); i++)
    {
        float xBtn = x + (i%perRow)*(size+pad);
        float yBtn = y + (i/perRow)*(size+pad);

        ofxRectangle rect(ofRectangle(xBtn,yBtn,size,size), colorNames[i].color);

        // add the random rectangle
        rectangles.push_back(rect);
    }

    selectedRectsBoundingBox = ofxRectangle(ofRectangle(),
            ofColor(127,80));

    hAlign = OF_ALIGN_HORZ_LEFT;
    vAlign = OF_ALIGN_VERT_TOP;

    anchorRect = NULL;

    showKeyboardCommands = false;

    //--
}


//--------------------------------------------------------------
void ofxColorsBrowser::update(){

    if (color_BACK != color_BACK_PRE)
    {
        color_BACK_OFAPP->set(color_BACK);
        color_BACK_PRE = color_BACK;
    }

    //-

    rectangles_update();

    //--
}

//--------------------------------------------------------------
void ofxColorsBrowser::draw()
{
    //-

    // 1. ALL THE COLORS NAMES

    // show all names from loaded palette
    for (int i=0; i<colorNames.size(); i++) {
        string str = colorNames[i].name;
        if (i == currColor) {

            ofDrawBitmapStringHighlight(str, 0, 20 + i * 20, ofColor::white, ofColor::black);
        } else {
            ofDrawBitmapStringHighlight(str, 0, 20 + i * 20, ofColor::black, ofColor::white);
        }
    }

//    for (int i=0; i<pantoneNames.size(); i++)
//    {
//        string str;
//        str = pantoneNames[i];
//        ofDrawBitmapStringHighlight(str, 0, 0+20 + i*20, ofColor::black, ofColor::white);
//    }

    //-

    // 2. MONITOR COLOR SELECTED: name & position in vector

    {
        int i = 0;
        int x = position.x;
        int y = 25;
        ofDrawBitmapStringHighlight("currName : "+currName, x, y+(i++)*20, ofColor::black, ofColor::white);
        ofDrawBitmapStringHighlight("currColor: "+ofToString(currColor), x, y+(i++)*20, ofColor::black, ofColor::white);
        ofDrawBitmapStringHighlight("currColor_OriginalPos: "+ofToString(currColor_OriginalPos), x, y+(i++)*20, ofColor::black, ofColor::white);
    }

    //-

    // 3. MONITOR APP MODES

    if (SHOW_ColorsBrowse)
    {
        if (SHOW_debugText)
        {
            string str;

            //-

            str = "SORTING MODE: ";
            switch (MODE_SORTING) {
                case 1:
                    str += "NAME";
                    break;
                case 2:
                    str += "HUE";
                    break;
                case 3:
                    str += "BRIGHTNESS";
                    break;
                case 4:
                    str += "SATURATION";
                    break;
            }
            ofDrawBitmapStringHighlight(str, positionHelper.x, positionHelper.y+50, ofColor::black, ofColor::white);

            //-

            str = "PALETTE NAME: ";
            switch (MODE_COLOR) {
                case OFX_PANTONE_COLORS:
                    str += "PANTONE COLORS";
                    break;
                case OFX_COLOR_NATIVE:
                    str += "OF NATIVE COLORS";
                    break;
                case OFX_OPEN_COLOR:
                    str += "OPEN COLOR";
                    break;
            }
            ofDrawBitmapStringHighlight(str, positionHelper.x, positionHelper.y+20, ofColor::black, ofColor::white);

            //-

            if (ENABLE_keys)
            {
#ifdef KEY_SHORTCUTS_ENABLE
                str = "SORT BY:\n";
                str += "[1] NAME\n";
                str += "[2] HUE\n";
                str += "[3] BRIGHTNESS\n";
                str += "[4] SATURATION\n";
                str += "[5] NEXT\n";
                str += "\n";
                str += "PALETTE:\n";
                str += "[BACKSPACE] NEXT\n";
                str += "[D] DEBUG";
                ofDrawBitmapStringHighlight(str, positionHelper.x, positionHelper.y+100, ofColor::black, ofColor::white);
#endif
            }
        }

        //--

        // 4. COLOR BOXES

        rectangles_draw();//rectangles with mouse management and draggables..

        //--
    }
}

//--------------------------------------------------------------
void ofxColorsBrowser::keyPressed( ofKeyEventArgs& eventArgs )
{
    const int & key = eventArgs.key;
//    ofLogNotice("ofxColorsBrowser") << "key: " << key;

    // show debug
    if (key == 'd'){
        bShowDebug = !bShowDebug;

        for (int i = 0; i < rectangles.size(); i++)
        {
            rectangles[i].setDebug(bShowDebug);
        }
    }

    // change to next palette
    if(key == OF_KEY_BACKSPACE)
    {
        MODE_COLOR++;
        MODE_COLOR = MODE_COLOR%3;

//        switch (MODE_COLOR)
//        {
//            case OFX_COLOR_NATIVE:
//                break;
//
//        }
//
////        if (MODE_COLOR == OFX_COLOR_NATIVE)
////            MODE_COLOR = OFX_OPEN_COLOR;
////
////        else if (MODE_COLOR == OFX_COLOR_NATIVE)
////            MODE_COLOR = OFX_OPEN_COLOR;
////
////        else if (MODE_COLOR = OFX_OPEN_COLOR)
////            MODE_COLOR = OFX_COLOR_NATIVE;

        clearPopulate();
        generate_ColorsInPalette();
        populate_colorsBoxes();
    }

    // select sorting
    if (key == '1'){
        if (MODE_SORTING != 1){
            MODE_SORTING = 1;
            ofSort(colorNames, compareName);
            clearPopulate();
            populate_colorsBoxes();
        }
    }
    else if (key == '2'){
        if (MODE_SORTING != 2){
            MODE_SORTING = 2;
            ofSort(colorNames, compareHue);
            clearPopulate();
            populate_colorsBoxes();
        }
    }
    else if (key == '3'){
        if (MODE_SORTING != 3){
            MODE_SORTING = 3;
            ofSort(colorNames, compareBrightness);
            clearPopulate();
            populate_colorsBoxes();
        }
    }
    else if (key == '4'){
        if (MODE_SORTING != 4){
            MODE_SORTING = 4;
            ofSort(colorNames, compareSaturation);
            clearPopulate();
            populate_colorsBoxes();
        }
    }
    else if (key == '5'){
        switch_sorted_Type();
    }


    else if (key == 'p'){
        RectangleUtils::pack(selectedRects, ofRectangle(0,
                0,
                ofRandom(500),
                ofRandom(500)));
    }

    //---

    // debug ofxRectangle handling

    if (bShowDebug)
    {

//    if (key == OF_KEY_UP) {
//        for(size_t i = 0; i < selectedRects.size(); i++) {
//            selectedRects[i]->vAlign = OF_ALIGN_VERT_TOP;
//        }
//    } else if (key == OF_KEY_DOWN) {
//        for(size_t i = 0; i < selectedRects.size(); i++) {
//            selectedRects[i]->vAlign = OF_ALIGN_VERT_BOTTOM;
//        }
//    } else if (key == OF_KEY_LEFT) {
//        for(size_t i = 0; i < selectedRects.size(); i++) {
//            selectedRects[i]->hAlign = OF_ALIGN_HORZ_LEFT;
//        }
//    } else if (key == OF_KEY_RIGHT) {
//        for(size_t i = 0; i < selectedRects.size(); i++) {
//            selectedRects[i]->hAlign = OF_ALIGN_HORZ_RIGHT;
//        }
//    } else if (key == 'c') {
//        for(size_t i = 0; i < selectedRects.size(); i++) {
//            selectedRects[i]->hAlign = OF_ALIGN_HORZ_CENTER;
//        }
//    } else if (key == 'C') {
//        for(size_t i = 0; i < selectedRects.size(); i++) {
//            selectedRects[i]->vAlign = OF_ALIGN_VERT_CENTER;
//        }
//    } else if (key == 'i') {
//        for(size_t i = 0; i < selectedRects.size(); i++) {
//            selectedRects[i]->hAlign = OF_ALIGN_HORZ_IGNORE;
//        }
//    } else if (key == 'I') {
//        for(size_t i = 0; i < selectedRects.size(); i++) {
//            selectedRects[i]->vAlign = OF_ALIGN_VERT_IGNORE;
//        }
//
        /*} else */ if (key == 'a') {
            if (hAlign == OF_ALIGN_HORZ_LEFT) {
                hAlign = OF_ALIGN_HORZ_CENTER;
            } else if (hAlign == OF_ALIGN_HORZ_CENTER) {
                hAlign = OF_ALIGN_HORZ_RIGHT;
            } else if (hAlign == OF_ALIGN_HORZ_RIGHT) {
                hAlign = OF_ALIGN_HORZ_IGNORE;
            } else if (hAlign == OF_ALIGN_HORZ_IGNORE) {
                hAlign = OF_ALIGN_HORZ_LEFT;
            }
        } else if (key == 'A') {
            if (vAlign == OF_ALIGN_VERT_TOP) {
                vAlign = OF_ALIGN_VERT_CENTER;
            } else if (vAlign == OF_ALIGN_VERT_CENTER) {
                vAlign = OF_ALIGN_VERT_BOTTOM;
            } else if (vAlign == OF_ALIGN_VERT_BOTTOM) {
                vAlign = OF_ALIGN_VERT_IGNORE;
            } else if (vAlign == OF_ALIGN_VERT_IGNORE) {
                vAlign = OF_ALIGN_VERT_TOP;
            }
        } else if (key == 'W') {
            RectangleUtils::sortByAbsWidth(selectedRects);
        } else if (key == 'A') {
            RectangleUtils::sortByArea(selectedRects);
        } else if (key == 'H') {
            RectangleUtils::sortByAbsHeight(selectedRects);
        } else if (key == 'c') {
            RectangleUtils::cascade(selectedRects, ofRectangle(0, 0, ofGetWidth(), ofGetHeight()), glm::vec2(30, 30));
        } else if (key == 'v') {
            RectangleUtils::alignVert(selectedRects, vAlign);
        } else if (key == 'h') {
            // horizontal align selection
            RectangleUtils::alignHorz(selectedRects, hAlign);
        } else if (key == 'x') {
            // distribute in x
            RectangleUtils::distributeHorz(selectedRects, hAlign);
        } else if (key == 'y') {
            RectangleUtils::distributeVert(selectedRects, vAlign);
        } else if (key == 'p') {

            RectangleUtils::pack(selectedRects, ofRectangle(0,
                    0,
                    ofGetWidth(),
                    ofGetHeight()));


        } else if (key == ' ') {
            showKeyboardCommands = !showKeyboardCommands;
        }
    }
}

//--------------------------------------------------------------
void ofxColorsBrowser::clearPopulate()
{
    // TODO: this is not require since swap from ofXInterface to ofxrectangleUtils
    ofLogNotice("ofxColorsBrowser") << "clearPopulate";

//    colorNames.clear();

    //-

    rectangles.clear();
}

//--------------------------------------------------------------
void ofxColorsBrowser::keyReleased( ofKeyEventArgs& eventArgs )
{
    if( eventArgs.key == ' ')
    {
    }
}


//--------------------------------------------------------------
void ofxColorsBrowser::addKeysListeners()
{
    ofAddListener( ofEvents().keyPressed, this, &ofxColorsBrowser::keyPressed );
}


//--------------------------------------------------------------
void ofxColorsBrowser::removeKeysListeners()
{
    ofRemoveListener( ofEvents().keyPressed, this, &ofxColorsBrowser::keyPressed );
}


//--------------------------------------------------------------
void ofxColorsBrowser::mouseDragged(ofMouseEventArgs& eventArgs){
    const int & x = eventArgs.x;
    const int & y = eventArgs.y;
    const int & button = eventArgs.button;
//    ofLogNotice("ofxColorsBrowser") << "mouseDragged " <<  x << ", " << y << ", " << button;

    if (bShowDebug)
    {
        if (draggingRectPtr != NULL) {
            draggingRectPtr->setPosition(ofPoint(x,y) - draggingRectPtr->dragOffset);

            if (draggingRectPtr == &selectedRectsBoundingBox) {
                for(size_t i = 0; i < rectangles.size(); i++) {
                    if (rectangles[i].isSelected) {
                        rectangles[i].setPosition(ofPoint(x,y) - rectangles[i].dragOffset);
                    }
                }
            }

        }
    }
}


//--------------------------------------------------------------
void ofxColorsBrowser::mousePressed(ofMouseEventArgs& eventArgs){
    const int & x = eventArgs.x;
    const int & y = eventArgs.y;
    const int & button = eventArgs.button;
//    ofLogNotice("ofxColorsBrowser") << "mousePressed " <<  x << ", " << y << ", " << button;

    if (ENABLE_clicks)
    {
        dragStart = glm::vec2(x, y);  // set a new drag start point

        if (!ofGetKeyPressed('A')) {

            bool foundAClickTarget = false;

            // first check to see if we are in the bounding box
            if (!selectedRects.empty() &&
                    selectedRectsBoundingBox.inside(dragStart))
            {

                if (bShowDebug)
                {
                    draggingRectPtr = &selectedRectsBoundingBox;
//            selectedRectsBoundingBox.dragOffset = dragStart - selectedRectsBoundingBox.getPosition().xy;
                    selectedRectsBoundingBox.dragOffset.x = dragStart.x - selectedRectsBoundingBox.getPosition().x;
                    selectedRectsBoundingBox.dragOffset.y = dragStart.y - selectedRectsBoundingBox.getPosition().y;


                    for (std::size_t i = 0; i < rectangles.size(); i++) {
                        if (rectangles[i].isSelected) {
//                    rectangles[i].dragOffset = dragStart - rectangles[i].getPosition().xy;
                            rectangles[i].dragOffset.x = dragStart.x - rectangles[i].getPosition().x;
                            rectangles[i].dragOffset.y = dragStart.y - rectangles[i].getPosition().y;
                        }
                    }
                    foundAClickTarget = true;
                }
            }

            else
            {
                // RECTANGLE COLOR CLICKED

                selectedRects.clear();
                // otherwise, go through all of the rects and see if we can drag one
                for (size_t i = 0; i < rectangles.size(); i++) {
                    rectangles[i].isSelected = false; // assume none
                    if (!foundAClickTarget && rectangles[i].isOver) {
                        draggingRectPtr = &rectangles[i];
                        rectangles[i].isSelected = true;
                        rectangles[i].dragOffset = dragStart - rectangles[i].getPosition();
                        foundAClickTarget = true;

                        //-

                        ofLogNotice("ofxColorsBrowser:mousePressed") << "clicked box ["<<i<<"]";
                        color_BACK = ofColor(rectangles[i].color);

                        currColor = i;
                        currName = colorNames[currColor].name;

                        currColor_OriginalPos = currColor;

//                        colorNames.clear();
//                        colorNameMap.clear();
//
//                        colorNameMap[pantoneNames[i]] = pantoneColors[i];
                        if (MODE_COLOR == OFX_PANTONE_COLORS)
                        {
                            currName = pantoneNames[i];//original name in position without sorting..
                        }

                        //-

                    }
                }
            }

            isSelecting = !foundAClickTarget; // means our click did not land on an existing rect
        } else {
            if (anchorRect != nullptr) {
                delete anchorRect;
                anchorRect = nullptr;
            }

            if (bShowDebug) {
                anchorRect = new ofRectangle(dragStart, 0, 0);
            }
        }
    }
}


//--------------------------------------------------------------
void ofxColorsBrowser::mouseReleased(ofMouseEventArgs& eventArgs) {
    const int &x = eventArgs.x;
    const int &y = eventArgs.y;
    const int &button = eventArgs.button;
//    ofLogNotice("ofxColorsBrowser") << "mouseReleased " <<  x << ", " << y << ", " << button;

    if (ENABLE_clicks) {
        draggingRectPtr = nullptr;
        isSelecting = false;
    }
}


//--------------------------------------------------------------
void ofxColorsBrowser::addMouseListeners()
{
    ofAddListener( ofEvents().mouseDragged, this, &ofxColorsBrowser::mouseDragged );
    ofAddListener( ofEvents().mousePressed, this, &ofxColorsBrowser::mousePressed );
    ofAddListener( ofEvents().mouseReleased, this, &ofxColorsBrowser::mouseReleased );
}


//--------------------------------------------------------------
void ofxColorsBrowser::removeMouseListeners()
{
    ofRemoveListener( ofEvents().mouseDragged, this, &ofxColorsBrowser::mouseDragged );
    ofRemoveListener( ofEvents().mousePressed, this, &ofxColorsBrowser::mousePressed );
    ofRemoveListener( ofEvents().mouseReleased, this, &ofxColorsBrowser::mouseReleased );
}


//--------------------------------------------------------------
void ofxColorsBrowser::exit()
{
//    ColourLoversHelper.exit();

    removeKeysListeners();
    removeMouseListeners();
}


//--------------------------------------------------------------
ofxColorsBrowser::~ofxColorsBrowser()
{
//    removeKeysListeners();
//    removeMouseListeners();
}


//--------------------------------------------------------------
void ofxColorsBrowser::setup_colorBACK(ofFloatColor &c)
{
//    colorBack_DEFINED = true;
//    color_BACK = c;
    color_BACK_OFAPP = &c;
}


//--------------------------------------------------------------
void ofxColorsBrowser::setPosition(glm::vec2 p){
    position = p;
}


//--------------------------------------------------------------
void ofxColorsBrowser::setBoxSize(float _size)
{
    size = _size;
}


//--------------------------------------------------------------
void ofxColorsBrowser::setRowsSize(int rows){
    perRow = rows;
}


//--------------------------------------------------------------
void ofxColorsBrowser::switch_palette_Type(){
    MODE_COLOR = (MODE_COLOR+1) % 2;
    ofLogNotice("ofxColorsBrowser") << "switch_palette_Type: " << MODE_COLOR;

    clearPopulate();
    generate_ColorsInPalette();
    populate_colorsBoxes();
}


//--------------------------------------------------------------
void ofxColorsBrowser::switch_sorted_Type(){
    MODE_SORTING++;
//    MODE_SORTING = MODE_SORTING%5;
    if (MODE_SORTING == 5)
        MODE_SORTING = 1;

    ofLogNotice("ofxColorsBrowser") << "switch_sorted_Type: " << MODE_SORTING;

    switch (MODE_SORTING)
    {
        case 1:
            ofSort(colorNames, compareName);
            break;
        case 2:
            ofSort(colorNames, compareHue);
            break;
        case 3:
            ofSort(colorNames, compareBrightness);
            break;
        case 4:
            ofSort(colorNames, compareSaturation);
            break;
    }

    if (MODE_SORTING >= 1 && MODE_SORTING<=4)
    {
        clearPopulate();
        populate_colorsBoxes();
    }
}


//--------------------------------------------------------------
void ofxColorsBrowser::set_palette_Type(int p)
{
    MODE_COLOR = p;

    clearPopulate();
    generate_ColorsInPalette();
    populate_colorsBoxes();
}


//--------------------------------------------------------------
void ofxColorsBrowser::set_sorted_Type(int p)
{
    MODE_SORTING = p;

    switch (MODE_SORTING)
    {
        case 1:
            ofSort(colorNames, compareName);
            break;
        case 2:
            ofSort(colorNames, compareHue);
            break;
        case 3:
            ofSort(colorNames, compareBrightness);
            break;
        case 4:
            ofSort(colorNames, compareSaturation);
            break;
    }

    if (p >= 1 && p<=4)
    {
        clearPopulate();
        populate_colorsBoxes();
    }
}


////--------------------------------------------------------------
//void ofxColorsBrowser::draw_native(){
//
//    // calculate the total size needed to display all the colors
//
//    float totalSize = (ceil(colorNameMap.size()/3.0)) * 50 - ofGetHeight() + 60;
//
//    // map the smoothed mouse to this:
//
//    float offset = ofMap(mouseSmoothed.y, 0, ofGetHeight(), 0, totalSize, true);
//
//    // draw all the colors
//    // note this could be optimized, since we're drawing plenty that's offscreen here.
//
//    for (unsigned int i = 0; i < colorNames.size(); i++){
//
//        int x = (i % 3) * ofGetWidth()/3.0;
//        int y = (floor(i / 3)) * 50;
//
//        ofSetColor( colorNames[i].color );
//        ofDrawRectangle(0 + x, y - offset, (i%3 == 2) ? ofGetWidth() - x : ofGetWidth()/3.0, 50);
//
//        ofDrawBitmapStringHighlight(colorNames[i].name, 20 + x, y -offset+30, ofColor::white, ofColor::black);
//    }
//}


//--------------------------------------------------------------
void ofxColorsBrowser::rectangles_update()
{
    if (ENABLE_clicks)
    {
        ofPoint mouse(ofGetMouseX(), ofGetMouseY());


        bool foundIsOver = false;
        bool hasFirstSelection = false;

        if (draggingRectPtr == NULL) {
            selectedRects.clear();
        }

        for (size_t i = 0; i < rectangles.size(); ++i) {
            // if we are selecting, re-evaluate this each time
            if (isSelecting) {
                rectangles[i].isSelected = rectangles[i].intersects(selectionRect);
            }

            // grow the slection box
            if (rectangles[i].isSelected) {

                if (draggingRectPtr == NULL) {

                    if (!hasFirstSelection) {
                        selectedRectsBoundingBox = rectangles[i];
                        hasFirstSelection = true;
                    } else {
                        selectedRectsBoundingBox.growToInclude(rectangles[i]);
                    }

                    selectedRects.push_back(&rectangles[i]);
                    hasFirstSelection = true;
                }
            }

            // check is over -- only set isOver if other things aren't happening
            if (!foundIsOver &&
                    /*selectedRects.empty() &&
                    !rectangles[i].isSelected && */
                            (draggingRectPtr == NULL ||
                                    draggingRectPtr == &rectangles[i] ||
                                    draggingRectPtr == &selectedRectsBoundingBox) &&
                    rectangles[i].inside(mouse)) {
                rectangles[i].isOver = true;
                foundIsOver = true;
            } else {
                rectangles[i].isOver = false;
            }
        }


        if (isSelecting) {
            selectionRect.set(glm::vec3(dragStart.x, dragStart.y, 0), mouse);
        }
    }
}


//--------------------------------------------------------------
void ofxColorsBrowser::rectangles_draw(){

    ofPoint mouse(ofGetMouseX(),ofGetMouseY());

    if (bShowDebug)
    {
        ofFill();
        ofSetColor(255,showKeyboardCommands ? 255 : 127);
        ofDrawBitmapString(showKeyboardCommands ? keyboardCommands : "Press (Spacebar) for help.", 12,16);
    }

    // draw all of our rectangles
    for (size_t i = 0; i < rectangles.size(); ++i)
    {
        ofRectangle* rect = (ofRectangle*)&rectangles[i];
        unsigned int selectionIndex = ofFind(selectedRects, rect);
        rectangles[i].draw(i,selectionIndex == selectedRects.size() ? -1 : selectionIndex);
    }

    // clicked color border
    // draw our bounding box rectangle
    if (!isSelecting && !selectedRects.empty())
    {
//        ofFill();
////        ofSetColor(255,20);
//        ofSetColor(0,200);
//        ofDrawRectangle(selectedRectsBoundingBox);

        ofNoFill();
//        ofSetColor(255,80);
//        ofSetColor(0,64);
        ofSetColor(0,255);//full black
        ofDrawRectangle(selectedRectsBoundingBox);
    }

    // draw our selection rectangle
    if (isSelecting && bShowDebug)
    {
        ofNoFill();
//        ofSetColor(255,255,0,200);
        ofSetColor(ofColor(ofColor::black, 200));
        ofDrawRectangle(selectionRect);
    }

    if (bShowDebug)
    {
        stringstream ss;
        ss << "Keyboard [(Spacebar) to hide]" << endl;
        ss << "W: sort by absolute width" << endl;
        ss << "A: sort by area" << endl;
        ss << "H: sort by absolute height" << endl;
        ss << "c: cascade" << endl;
        ss << "v: align vertical with current vAlign" << endl;
        ss << "h: align horizontal with current hAlign" << endl;
        ss << "x: distribute horizontal with current hAlign" << endl;
        ss << "h: distribute vertical with current vAlign" << endl;
        ss << "p: pack rectangles" << endl;
        keyboardCommands = ss.str();

        string hAlignString = "";
        switch (hAlign) {
            case OF_ALIGN_HORZ_LEFT:
                hAlignString = "OF_ALIGN_HORZ_LEFT";
                break;
            case OF_ALIGN_HORZ_CENTER:
                hAlignString = "OF_ALIGN_HORZ_CENTER";
                break;
            case OF_ALIGN_HORZ_RIGHT:
                hAlignString = "OF_ALIGN_HORZ_RIGHT";
                break;
            case OF_ALIGN_HORZ_IGNORE:
                hAlignString = "OF_ALIGN_HORZ_IGNORE";
                break;
            default:
                hAlignString = "??";
                break;
        }

        string vAlignString = "";
        switch (vAlign) {
            case OF_ALIGN_VERT_TOP:
                vAlignString = "OF_ALIGN_VERT_TOP";
                break;
            case OF_ALIGN_VERT_CENTER:
                vAlignString = "OF_ALIGN_VERT_CENTER";
                break;
            case OF_ALIGN_VERT_BOTTOM:
                vAlignString = "OF_ALIGN_VERT_BOTTOM";
                break;
            case OF_ALIGN_VERT_IGNORE:
                vAlignString = "OF_ALIGN_VERT_IGNORE";
                break;
            default:
                vAlignString = "??";
                break;
        }

        ofFill();
        ofSetColor(255);
        ofDrawBitmapString("Press (a) to toggle selection hAlign : " + hAlignString, 10, ofGetHeight() - 24);
        ofDrawBitmapString("Press (A) to toggle selection vAlign : " + vAlignString, 10, ofGetHeight() - 10);
    }

    ofNoFill();
    ofSetColor(255,255,0);

    for(int i = 0; i < packedRects.size(); i++)
    {
        ofDrawRectangle(packedRects[i]);
    }
}


//--------------------------------------------------------------
void ofxColorsBrowser::setVisible_debugText(bool b)
{
    SHOW_debugText = b;
}
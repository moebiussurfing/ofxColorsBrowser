#include "ofxColorsBrowser.h"

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

    // comment to disable shortcuts
#ifdef KEY_SHORTCUTS_ENABLE
    addKeysListeners();
#endif

    // TODO: test pointer back color
//    color_BACK.addListener(this, &ofxColorsBrowser::Changed_color_clicked);
}

//--------------------------------------------------------------
void ofxColorsBrowser::generateColors(){
    colorNames.clear();
    colorNameMap.clear();

    if (MODE_COLOR == OFX_OPEN_COLOR)
    {

#define NUM_COLORS 10
        for (int i = 0; i<NUM_COLORS; i++)
        {
            //  Gray
            colorNameMap["GREY " + ofToString(i)] = oc_gray_[i];
            //  Red
            colorNameMap["RED " + ofToString(i)] = oc_red_[i];
            //  Pink
            colorNameMap["PINK " + ofToString(i)] = oc_pink_[i];
            //  Grape
            colorNameMap["GRAPE " + ofToString(i)] = oc_grape_[i];
            //  Violet
            colorNameMap["VIOLET " + ofToString(i)] = oc_violet_[i];
            //  Indigo
            colorNameMap["INDIGO " + ofToString(i)] = oc_indigo_[i];
            //  Blue
            colorNameMap["BLUE " + ofToString(i)] = oc_blue_[i];
            //  Cyan
            colorNameMap["CYAN " + ofToString(i)] = oc_cyan_[i];
            //  Teal
            colorNameMap["TEAL " + ofToString(i)] = oc_teal_[i];
            //  Green
            colorNameMap["GREEN " + ofToString(i)] = oc_green_[i];
            //  Lime
            colorNameMap["LIME " + ofToString(i)] =  oc_lime_[i];
            //  Yellow
            colorNameMap["YELLOW " + ofToString(i)] =  oc_yellow_[i];
            //  Orange
            colorNameMap["ORANGE " + ofToString(i)] =  oc_orange_[i];
        }
    }

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

//--------------------------------------------------------------
void ofxColorsBrowser::setup(){
    MODE_COLOR = OFX_OPEN_COLOR;//default mode
    generateColors();

    //-

    scene = new Node();
    scene->setSize(ofGetWidth(), ofGetHeight());
    scene->setName("Scene");
    TouchManager::one().setup(scene);
    populateScene();
}

//--------------------------------------------------------------
void ofxColorsBrowser::populateScene()
{
    float x = position.x;
    float y = position.y;

    for (int i = 0; i < colorNames.size(); i++)
    {
        float xBtn = x + (i%perRow)*(size+pad);
        float yBtn = y + (i/perRow)*(size+pad);

        Color_BitmapTextButton *btn = new Color_BitmapTextButton();
//        btn->loadFont("assets/fonts/PragmataProR_0822.ttf");
        btn->setup(colorNames[i].name);
        btn->setBackground(true);
        btn->setBGColor(colorNames[i].color);
        btn->setBorderColor(ofColor::black);
        btn->setPosition(xBtn, yBtn);
        btn->setSize(size, size);
        btn->setLabelColor(ofColor::black);
        btn->setName("col" + ofToString(i));
        btn->setup_colorBACK(color_BACK);
        scene->addChild(btn);

//        if (i%perRow>0) {
//            btn->placeNextTo(*buttons_txt[i-1], Node::RIGHT);
//        }
        buttons_txt.push_back(btn);
    }
}

//--------------------------------------------------------------
void ofxColorsBrowser::update(){

    if (color_BACK != color_BACK_PRE)
    {
        color_BACK_OFAPP->set(color_BACK);
        color_BACK_PRE = color_BACK;
    }

    //-

    // smoothing the mouse a bit over time
    mouseSmoothed = 0.95 * mouseSmoothed + 0.05 * ofPoint(mouseX, mouseY);

    //-

    TouchManager::one().update();
    float dt = 1. / ofGetFrameRate();
    for (int i = 0; i < buttons_txt.size(); i++)
    {
        buttons_txt[i]->update(dt);
    }
}

//--------------------------------------------------------------
void ofxColorsBrowser::draw(){
//    ofClear(ofColor( color_BACK ));//TODO: moved to ofApp. pointer back color

    scene->render();
    if (bShowDebug) {
        scene->renderDebug();
    }

    ofPushStyle();

//    ofSetColor(0);
//    ofDrawRectangle(position.x, ofGetHeight()-60, 500, 60);
    string str;

#ifdef KEY_SHORTCUTS_ENABLE
    str = "press '1' to sort by name, '2' to sort by hue,\n'3' to sort by brightness, '4' to sort by saturation";
    ofDrawBitmapStringHighlight(str, position.x+20, ofGetHeight()-60 + 40, ofColor::black, ofColor::white);
#else
    str = "SORTING: ";
    switch (MODE_SORTING)
    {
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
    ofDrawBitmapStringHighlight(str, position.x+20, ofGetHeight()-60 + 30, ofColor::black, ofColor::white);

    str = "PALETTE: ";
    switch (MODE_COLOR)
    {
        case 0:
            str += "OF NATIVE NAMES";
            break;
        case 1:
            str += "OPEN COLOR";
            break;
    }
    ofDrawBitmapStringHighlight(str, position.x+20, ofGetHeight()-60 + 50, ofColor::black, ofColor::white);
#endif

    ofPopStyle();
}

//--------------------------------------------------------------
void ofxColorsBrowser::draw_native(){

    // calculate the total size needed to display all the colors

    float totalSize = (ceil(colorNameMap.size()/3.0)) * 50 - ofGetHeight() + 60;

    // map the smoothed mouse to this: 

    float offset = ofMap(mouseSmoothed.y, 0, ofGetHeight(), 0, totalSize, true);

    // draw all the colors
    // note this could be optimized, since we're drawing plenty that's offscreen here.

    for (unsigned int i = 0; i < colorNames.size(); i++){

        int x = (i % 3) * ofGetWidth()/3.0;
        int y = (floor(i / 3)) * 50;

        ofSetColor( colorNames[i].color );
        ofDrawRectangle(0 + x, y - offset, (i%3 == 2) ? ofGetWidth() - x : ofGetWidth()/3.0, 50);

        ofDrawBitmapStringHighlight(colorNames[i].name, 20 + x, y -offset+30, ofColor::white, ofColor::black);
    }

}

//--------------------------------------------------------------
void ofxColorsBrowser::keyPressed( ofKeyEventArgs& eventArgs )
{
    const int & key = eventArgs.key;
    cout << "key: " << key << endl;

    if (key == 'd'){
        bShowDebug = !bShowDebug;
    }

    if(key == OF_KEY_BACKSPACE)
    {
        if (MODE_COLOR == OFX_COLOR_NATIVE)
            MODE_COLOR = OFX_OPEN_COLOR;
        else if (MODE_COLOR = OFX_OPEN_COLOR)
            MODE_COLOR = OFX_COLOR_NATIVE;

        clearPopulate();
        generateColors();
        populateScene();
    }

    if (key == '1'){
        if (MODE_SORTING != 1){
            MODE_SORTING = 1;
            ofSort(colorNames, compareName);
            clearPopulate();
            populateScene();
        }
    } else if (key == '2'){
        if (MODE_SORTING != 2){
            MODE_SORTING = 2;
            ofSort(colorNames, compareHue);
            clearPopulate();
            populateScene();
        }
    } else if (key == '3'){
        if (MODE_SORTING != 3){
            MODE_SORTING = 3;
            ofSort(colorNames, compareBrightness);
            clearPopulate();
            populateScene();
        }
    } else if (key == '4'){
        if (MODE_SORTING != 4){
            MODE_SORTING = 4;
            ofSort(colorNames, compareSaturation);
            clearPopulate();
            populateScene();
        }
    }
}

//--------------------------------------------------------------
void ofxColorsBrowser::clearPopulate()
{
    cout << endl;
    cout << "clearPopulate" << endl;
    cout << "getNumChildren: " << scene->getNumChildren() << endl;

    for (int i=0; i< buttons_txt.size(); i++)
    {
        std::string n = ("col" + ofToString(i));
        auto a = scene->getChildWithName(n, scene->getNumChildren());
        auto b = a->getName();
        scene->removeChild(a, false);
//        cout << "removed children: " << b << endl;
    }
    buttons_txt.clear();
    cout << endl;
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

    TouchManager::one().touchMove(button, ofVec2f(x, y));
}

//--------------------------------------------------------------
void ofxColorsBrowser::mousePressed(ofMouseEventArgs& eventArgs){
    const int & x = eventArgs.x;
    const int & y = eventArgs.y;
    const int & button = eventArgs.button;
//    ofLogNotice("ofxColorsBrowser") << "mousePressed " <<  x << ", " << y << ", " << button;

    mouseX = x;
    mouseY = y;

    TouchManager::one().touchDown(button, ofVec2f(x, y));
}

//--------------------------------------------------------------
void ofxColorsBrowser::mouseReleased(ofMouseEventArgs& eventArgs){
    const int & x = eventArgs.x;
    const int & y = eventArgs.y;
    const int & button = eventArgs.button;
//    ofLogNotice("ofxColorsBrowser") << "mouseReleased " <<  x << ", " << y << ", " << button;

    TouchManager::one().touchUp(button, ofVec2f(x, y));
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
    ofRemoveListener( ofEvents().keyPressed, this, &ofxColorsBrowser::keyPressed );
}

//--------------------------------------------------------------
void ofxColorsBrowser::exit()
{

}

//--------------------------------------------------------------
ofxColorsBrowser::~ofxColorsBrowser()
{
    removeKeysListeners();
    removeMouseListeners();
}

//--------------------------------------------------------------
void ofxColorsBrowser::setup_colorBACK(ofFloatColor &c)
{
//    colorBack_DEFINED = true;
//    color_BACK = c;
    color_BACK_OFAPP = &c;
}

////--------------------------------------------------------------
//void ofxColorsBrowser::Changed_color_clicked(ofFloatColor &color)
//{
////    ofLogNotice("ofxColorManager") << "Changed_color_clicked " << ofToString(color);
////    color_picked.set(color);
//}

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
    generateColors();
    populateScene();
}

//--------------------------------------------------------------
void ofxColorsBrowser::switch_sorted_Type(){
    MODE_SORTING++;
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
        populateScene();
    }
}

//--------------------------------------------------------------
void ofxColorsBrowser::set_palette_Type(int p)
{
    MODE_COLOR = p;

    clearPopulate();
    generateColors();
    populateScene();
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
        populateScene();
    }
}

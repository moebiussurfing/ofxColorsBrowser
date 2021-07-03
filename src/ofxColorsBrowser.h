#pragma once

#include "ofMain.h"


/*

	TODO:

	+ add pointer back
	+ move layout settings on a float window to not deform grid while editing
	+ make a base class to improve adding more libraries?
	+ add more browseable pages on basic gui
	+ more responsive, variable sizes..
	+ split build from resize responsive layout. to allow live rescaling

*/


//----------

//	OPTIONAL

// uncomment to run the bundled example!
#define USE_OFX_COLOR_BROWSER_INTERFACE // -> This includes the GUI: rectangle boxes, color names listing, keys/mouse browsing etc..

//TODO: WIP. adding this library
//#define USE_OFX_MATERIAL_COLOR

//----------


#include "ofxSurfingHelpers.h"
#include "ofxGui.h"
#include "ofxSurfing_ofxGui.h"

#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
#include "ofxRectangleUtils.h"
#include "ofxRectangle.h"
#include "ofxFontStash.h"
using namespace ofx;
#endif

#include "ofxOpenColor.h"

// internal shorcuts no add listeners or remove
#define KEY_SHORTCUTS_ENABLE

//--

// sorting modes
enum
{
	SORTING_ORIGINAL,
	SORTING_NAME,
	SORTING_HUE,
	SORTING_BRIGHTNESS,
	SORTING_SATURATION
};

// libraries
enum
{
	OFX_PANTONE_COLORS,		// 0
	OFX_SANZOWADA_COLORS,	// 1
	OFX_COLOR_NATIVE,		// 2
#ifdef USE_OFX_MATERIAL_COLOR
	OFX_MATERIAL_COLOR,		// 3 TODO:
#endif
	OFX_OPEN_COLOR,			// 4
	OFX_CHEPRASOV,			// 5
	OFX_CRAYOLA,			// 6
	OFXCOLORSBROWSER__COUNT
};

// a color struct
typedef struct
{
	std::string name;
	ofColor color;
	int position; // original position vs name, hue, sat...etc
}
colorMapping_STRUCT;

//--

class ofxColorsBrowser
{

	// text render
private:
#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
	ofxFontStash fontNames;
#endif
	ofTrueTypeFont fontHelp;
	std::string helpInfo;
	std::string helpInfoFull;

	//--

	// debug gui
	ofxPanel gui;

public:

	//--

public:
	ofxColorsBrowser();
	~ofxColorsBrowser();

	void setup();
	void update(ofEventArgs & args);
	void draw(ofEventArgs & args);
	void exit();
	void windowResized(int w, int h);

	//--

private:
	// importers
	void load_Pantone_JSON();
	void load_SanzoWada_JSON();
	void load_Material_JSON();
	void load_Cheprasov_JSON();
	void load_Crayola_JSON();

	//----

	// API

	//-

public:
	void setPositionRectangles(glm::vec2 p);
	void setPositionHelper(glm::vec2 p)
	{
		positionHelper = p;
	};

	//--

	// brwose

	// to use externally by the code

public:
	// colors
	int getColorIndex();
	void setColorIndex(int index);
	void setNextColor();
	void setPreviousColor();
	void setNextColorRow();
	void setPreviousColorRow();
	void setRandomColor();
	// cards
	int getCardIndex();
	void setCardIndex(int index);
	void setNextCard();
	void setPreviousCard();
	void setNextCardRow();
	void setPreviousCardRow();
	void setRandomCard();
	// library
	void setNextLibrary();
	void setPreviousLibrary();
	void setLibraryType(int p);
	// sorting
	void setNextSortType();
	void setPreviousSortType();
	void setSortingType(int p);

	void resetLayout();

	ofFloatColor getColor() {
		return	*color_BACK_OFAPP;
	}

	//--

	// gui

	// TODO: resize buttons to fit..
	//void setSize(glm::vec2 size);

	void setRowsSize(int rows);
	void setBoxSize(float size);

	void setVisible(bool b);
	void setVisibleDebug(bool b);
	void setToggleVisibleDebug();

	//--------------------------------------------------------------
	bool isVisible() {
		return bGui.get();
	}
	//--------------------------------------------------------------
	void setToggleVisible()
	{
		bGui = !bGui.get();
		ofLogNotice(__FUNCTION__) << "bGui: " << bGui;

		setVisible(bGui);

		//bShowRectangles = !bShowRectangles;
		//setVisible(bShowRectangles);
	}

	//--------------------------------------------------------------
	void setEnableInterfaceClicks(bool b)
	{
		bEnableClicks = b;

#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
		if (b)
		{
			//addKeysListeners();
			addMouseListeners();
		}
		else
		{
			//removeKeysListeners();
			removeMouseListeners();
		}
#endif
	}
	//--------------------------------------------------------------
	void setToggleEnableKeys() {
		bKeys = !bKeys;

		setEnableKeys(bKeys);
	}
	//--------------------------------------------------------------
	void setEnableKeys(bool b)
	{
		bKeys = b;

#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
		if (bKeys) addKeysListeners();
		else removeKeysListeners();
#endif
	}
	//--------------------------------------------------------------
	void setActive(bool b)
	{
		bKeys = b;

#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
		if (bKeys) addKeysListeners();
		else removeKeysListeners();
#endif

		setVisible(b);
	}

	//----

	// referenced pointer back
	void setupColorPtr(ofFloatColor &c); // to reference a pointer and autoupdate referenced local color when the user picks a color inside the add-on scope

	//-

public:
	// main library getter
	vector<ofColor> getLibraryColors();

	vector<std::string> getNames();

	int getAmountcolors();
	int getLibraryIndex() {
		return index_Library.get();
	}
	int getCardsAmountcolors() {
		return amtColorsInCard.get();
	}
	std::string getLibraryName() {
		return name_Library.get();
	}	
	std::string getSortingTypeName() {
		return MODE_SORTING_name.get();
	}

	//--

private:

	std::string path_Global;
	std::string path_FileSettings;
	std::string path_Jsons;

	// path for json colors files
	std::string path_FilePantone;
	std::string path_FileSanzoWada;
	std::string path_FileMaterial;
	std::string path_FileCheprasov;
	std::string path_FileCrayola;

	//-

	// grid layout

public:
	//private:
	ofParameter<float> boxSize{ "Box Size", 30, 10, 100 };//boxes
	ofParameter<float> boxPad{ "Pad", 0, 0, 10 };
	ofParameter<int> amtColorsInCard{ "Card Colors", 7, 2, 20 };// minimal card of colors
	ofParameter<int> amtCardsInRow{ "Row Cards", 4, 2, 20 };
	ofParameter<bool> bResetColorsBox{ "Reset Box", false };

	ofParameter<bool> bLockLayout{ "Lock Layout", true };
	ofParameter<bool> bShowCards{ "Show Cards", true };
	ofParameter<bool> bShowRectangles{ "Show Rectangles", true };
	ofParameter<bool> bShowDebugRectangles{ "Show Debug Rectangles", false };
	ofParameter<bool> bShowHelp{ "Show Help", true };
	ofParameter<bool> bShowNamesList{ "Show Names List", false };

private:
	int amtColorsPerRow;
	int index_Card = 0;
	int cardColor_size = 100;
	int cardColor_pad = 20;


public:
	ofParameter<bool> bKeys{ "Enable Keys", false };
	ofParameter<bool> bGui{ "Gui Internal", true };
	ofParameter<bool> bGuiDebug{ "Gui Debug", false };
	//bool bGuiDebug = false;


	//--

	// main storage

private:
	map<std::string, ofColor> colors_NamesMAP;

	//TODO:	
public:
	vector<colorMapping_STRUCT> colors_STRUCT;

	//----

private:

	// pantone colors
	ofJson jsPantone;
	vector<ofColor> colors_Pantone;
	vector<std::string> colors_PantoneNames;

	// snazo wada
	ofJson jSanzoWada;
	vector<ofColor> colors_SanzoWada;
	vector<std::string> colors_SanzoWadaNames;

	// cheprasov
	ofJson jCheprasov;
	vector<ofColor> colors_Cheprasov;
	vector<std::string> colors_CheprasovNames;

	// crayola
	ofJson jCrayola;
	vector<ofColor> colors_Crayola;
	vector<std::string> colors_CrayolaNames;

	// material
	ofJson jMaterial;
	vector<ofColor> colors_Material;
	vector<std::string> colors_MaterialNames;
	vector<std::string> tagsMaterial{
		"50", "100", "200", "300", "400", "500",
		"600", "700", "800", "900",
		"a100", "a200", "a400", "a700" };

	//----

	// rectangle manager system - ofxRectangle

	//-

private:
	// TODO:
	// draggable, sortable, align...
#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
	std::vector<ofxRectangle> rectangles;
	std::vector<ofRectangle *> rectanglesSelected;
	ofxRectangle selectedRectsBoundingBox;
	ofxRectangle *draggingRectPtr;
	glm::vec2 dragStart;
	bool isSelecting;
	ofRectangle selectionRect;
	ofAlignHorz hAlign;
	ofAlignVert vAlign;
	ofRectangle *anchorRect;
	std::string keyboardCommands;
	bool showKeyboardCommands;
	std::vector<ofRectangle> packedRects;
#endif

	//-

private:
	void updateRectangles();
	void drawRectangles();

	void drawHelp();

	//-

	// color converters
	// These string to hex conversions aren't trivial.
	static int stringToHex(std::string hex)
	{
		int aHex;
		stringstream convert(hex);
		convert >> std::hex >> aHex;
		return aHex;
	}

	static void hexToColor(ofColor &col, std::string hex)
	{
		std::string r = hex.substr(0, 2);
		int ri = stringToHex(r);
		std::string g = hex.substr(2, 2);
		int gi = stringToHex(g);
		std::string b = hex.substr(4, 2);
		int bi = stringToHex(b);
		col.set(ri, gi, bi);
	}

	//----

public:
	void keyPressed(ofKeyEventArgs &eventArgs);
	void keyReleased(ofKeyEventArgs &eventArgs);

	void mouseDragged(ofMouseEventArgs &eventArgs);
	void mousePressed(ofMouseEventArgs &eventArgs);
	void mouseReleased(ofMouseEventArgs &eventArgs);

private:
	void addKeysListeners();
	void removeKeysListeners();

	void addMouseListeners();
	void removeMouseListeners();

	//-

	// modes and states

private:
	//bool bShowNamesList = false;
	//bool bShowDebugRectangles = false;//for rectangle manager
	//bool bShowRectangles = true;

	bool bEnableClicks = true;

	//-

	// pointers back

	ofFloatColor color_BACK;
	ofFloatColor color_BACK_PRE;
	ofFloatColor *color_BACK_OFAPP;

	//-

	void buildLibraryColors();
	void refreshRectanglesClicks(); // to browsing by keys
	void buildRectangles();
	void clearRectangles();

	int pageNum;

	//-

	//// rectangles position
	//glm::vec2 positionRectangles;
	//// text debug positions
	//glm::vec2 positionHelper;
	//// cards list names
	//glm::vec2 positionCards;

	// rectangles position
	ofParameter<glm::vec2> positionRectangles{ "position_Rectangles",  glm::vec2(0), glm::vec2(0), glm::vec2(1920) };
	// text debug positions
	ofParameter<glm::vec2> positionHelper{ "position_Helper",  glm::vec2(0), glm::vec2(0), glm::vec2(1920) };
	// cards list names
	ofParameter<glm::vec2> positionCards{ "position_Cards",  glm::vec2(0), glm::vec2(0), glm::vec2(1920) };
	// names list
	ofParameter<glm::vec2> positionNames{ "position_Names",  glm::vec2(0), glm::vec2(0), glm::vec2(1920) };
	ofParameter<bool> bResetLayout{ "Reset Layout", false };

	//--

public:
	//private:
	ofParameter<int> index_Library{ "Library", 0, 0, 0 };
	ofParameter<std::string> name_Library{ " ", "" };

	// 0:ORIGINAL, 1:NAME, 2:HUE, 3:BRIGHTNESS, 4:SATURATION, 5:NEXT
	ofParameter<int> MODE_SORTING{ "Sorting Mode", 0, 0, 4 };
	ofParameter<std::string> MODE_SORTING_name{ " ", "" };

public:
	ofParameterGroup params;

	ofParameterGroup params_Layout;
	ofParameterGroup params_GuiPanels;
	void Changed_Params(ofAbstractParameter &e);

	ofEventListener listener_Library;
	ofEventListener listener_ModeSorting;

private:
	// last clicked color box
	std::string currName = "";
	int index_Color = -1;
	int currColor_OriginalPos = -1;
};

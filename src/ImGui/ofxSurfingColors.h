#pragma once

#include "ofMain.h"

#include "ofxSurfingImGui.h"

#include "ofxColorsBrowser.h"

class ofxSurfingColors
{

public:
	ofxColorsBrowser colorBrowser;
	ofFloatColor *color_BACK_OFAPP;
	void setupColorPtr(ofFloatColor &c);
	ofFloatColor colorBg;
	
	void gui_Library();

	//-

public:
	ofxSurfingColors();
	~ofxSurfingColors();

	void setup();
	void update(ofEventArgs & args);
	void draw(ofEventArgs & args);
	void keyPressed(ofKeyEventArgs &eventArgs);
	void windowResized(int w, int h);
	void exit();

	void setBool(bool b);
	bool getBool();

	ofxSurfing_ImGui_Manager guiManager; 
	void drawImGui();
private:

public:




	//----

	// libs library palette
	// using colorBrowser
private:

//#ifdef USE_OFX_COLOR_BROWSER
//	ofxColorsBrowser colorBrowser;
//#endif

	vector<ofColor> palette_Lib_Cols;
	vector<std::string> palette_Lib_Names;

	ofEventListener listener_Library;
	ofEventListener listener_ModeSorting;

	void refresh_Libs();
	void refresh_Kits();
	void refresh_Paths();

	int lib_RowSize = 7; // 7 colors per row Pantone lib
	int lib_Page_NumColors;
	int lib_TotalColors;
	int lib_Page_Max;

	//gui grid layout
	//rows per page
	ofParameter<int> lib_NumRows{ "Rows Amnt" , 10, 5, 10 * 5 };
	ofParameter<int> lib_Page_Index{ "Page" , 0, 0, lib_Page_Max };
	ofParameter<bool>lib_CardsMode{ "Mode Cards", false };
	ofParameter<int> lib_MaxColumns{ "Columns Max", 7, 1, 7 * 6 };
	ofParameter<float> scale_LibCol{ "Scale", 1, 0.5, 1.5 };

	//--

	// app settings json/xml

	ofParameterGroup params_Library{ "LIBRARY" };

	//--

	// colors library layout

private:
	ofParameter<bool> lib_Responsive_ModeGrid;
	ofParameter<bool> lib_Responsive_ModeFit;
	ofParameter<bool> bPagerized;
	ofParameter<int> sizeLibColBox;
	ofParameter<bool> bResponsive_Panels;
	ofParameter<int> sizePaletteBox;

	ofParameter<bool> bFitLayout;




	bool ENABLE_CALLBACKS_Pickers = true;


	// main picker color
	ofParameter<ofFloatColor> color_Picked;
	ofParameter<bool> SHOW_Advanced{ "ADVANCED", false };



private:
	std::string last_Lib_NameColor = "";
	int last_ColorPicked_Lib;

	//-	

private:
	ImVec4 borderLineColor = ImVec4(0, 0, 0, 0.65); //  for selected color buttons, toggles and blinking 
	float borderLineWidth = 1.0f;
	float labelPadding = 0.0; // label buttons

	void resetLibraryLayout();

	int last_Lib_Index = -1; // last library picked color


					ImGuiStyle *style = nullptr;




};


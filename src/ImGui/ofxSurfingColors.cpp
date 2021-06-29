#include "ofxSurfingColors.h"

//--------------------------------------------------------------
ofxSurfingColors::ofxSurfingColors() {

	path_Global = "ofxSurfingColors/";
	path_FileSettings = path_Global + "AppSettings.xml";
	ofxSurfingHelpers::CheckFolder(path_Global);

	ofAddListener(ofEvents().update, this, &ofxSurfingColors::update);
	ofAddListener(ofEvents().draw, this, &ofxSurfingColors::draw);
	ofAddListener(ofEvents().keyPressed, this, &ofxSurfingColors::keyPressed);
}

//--------------------------------------------------------------
ofxSurfingColors::~ofxSurfingColors() {
	ofRemoveListener(ofEvents().update, this, &ofxSurfingColors::update);
	ofRemoveListener(ofEvents().draw, this, &ofxSurfingColors::draw);
	ofRemoveListener(ofEvents().keyPressed, this, &ofxSurfingColors::keyPressed);

	exit();
}

//--------------------------------------------------------------
void ofxSurfingColors::setup() {
	guiManager.setImGuiAutodraw(true);
	guiManager.setup();

	//colorBrowser.setupColorPtr(colorBg); // set local target color receiver
	colorBrowser.setup();

	//-

	// library

	sizeLibColBox.set("Size Lib", 25, 10, 100);
	lib_Responsive_ModeGrid.set("Responsive Grid", false);
	lib_Responsive_ModeFit.set("Responsive Fit", true);
	bPagerized.set("Mode Paging", false);
	//palette
	sizePaletteBox.set("Size Plt", 25, 10, 500);
	bResponsive_Panels.set("Responsive", false);

	bFitLayout.set("Fit", true);

	//-

	params_Library.setName("Library Layout");
	params_Library.add(lib_Page_Index);
	params_Library.add(lib_MaxColumns);
	params_Library.add(lib_NumRows);
	params_Library.add(lib_CardsMode);
	params_Library.add(scale_LibCol);
	params_Library.add(scale_ColRange);
	params_Library.add(lib_Responsive_ModeGrid);
	params_Library.add(lib_Responsive_ModeFit);
	params_Library.add(bPagerized);
	params_Library.add(sizeLibColBox);

	//-

	params.setName("ofxSurfingColors");
	params.add(colorBrowser.bGui);
	params.add(SHOW_Advanced);
	params.add(colorBrowser.bGui);
	params.add(params_Library);

	// settings
	ofxSurfingHelpers::loadGroup(params, path_FileSettings);

	//-

	//--------------------------------------------------------------
	listener_Library = colorBrowser.index_Library.newListener([this](int &i)
	{
		ofLogNotice("ofxSurfingColors > ofxColorsBrowser : Changed index_Library: ") << i;

		refresh_Libs();
	});

	//-

	refresh_Libs();
}

//--------------------------------------------------------------
void ofxSurfingColors::setupColorPtr(ofFloatColor &c)
{
	//color_BACK = c;
	color_BACK_OFAPP = &c;

	colorBrowser.setupColorPtr(*color_BACK_OFAPP); // set local target color receiver
}

//--------------------------------------------------------------
void ofxSurfingColors::update(ofEventArgs & args)
{
}

//--------------------------------------------------------------
void ofxSurfingColors::draw(ofEventArgs & args)
{
	drawImGui();
}

//--------------------------------------------------------------
void ofxSurfingColors::keyPressed(ofKeyEventArgs &eventArgs)
{
	const int key = eventArgs.key;

	// modifiers
	bool mod_COMMAND = eventArgs.hasModifier(OF_KEY_COMMAND);
	bool mod_CONTROL = eventArgs.hasModifier(OF_KEY_CONTROL);
	bool mod_ALT = eventArgs.hasModifier(OF_KEY_ALT);
	bool mod_SHIFT = eventArgs.hasModifier(OF_KEY_SHIFT);

	ofLogNotice(__FUNCTION__) << " : " << key;

	//--

	if (false) {}

	else if (key == 'G' && !mod_ALT)
	{
	}

	if (key == OF_KEY_F1) colorBrowser.setNextColor();
	if (key == OF_KEY_F2) colorBrowser.setNextColorRow();
	if (key == OF_KEY_F3) colorBrowser.setNextCard();
	if (key == OF_KEY_F4) colorBrowser.setNextCardRow();
	if (key == OF_KEY_F5) colorBrowser.setRandomColor();
	if (key == OF_KEY_F6) colorBrowser.setRandomCard();

	//TODO:
	refresh_Libs();
}

//--------------------------------------------------------------
void ofxSurfingColors::exit() {
	ofxSurfingHelpers::saveGroup(params, path_FileSettings);
}

//--------------------------------------------------------------
void ofxSurfingColors::setBool(bool b) {
	ofLogNotice(__FUNCTION__) << ofToString(b ? "true" : "false");
}

//--------------------------------------------------------------
bool ofxSurfingColors::getBool() {
	return true;
}

//--------------------------------------------------------------
void ofxSurfingColors::drawImGui()
{
	guiManager.begin();
	{
		static bool bOpen0 = true;
		{
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
			if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

			guiManager.beginWindow("ofxSurfingColors", NULL, window_flags);
			{
				ofxImGuiSurfing::AddToggleRoundedButton(colorBrowser.bGui);
				ofxImGuiSurfing::AddToggleRoundedButton(colorBrowser.bGuiDebug);
				ofxImGuiSurfing::AddToggleRoundedButton(colorBrowser.bKeys);
				ofxImGuiSurfing::AddToggleRoundedButton(SHOW_Advanced);
			}
			guiManager.endWindow();
		}

		//--

		drawImGuiLibrary();
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofxSurfingColors::windowResized(int w, int h) {
	colorBrowser.windowResized(w, h);
}

//--------------------------------------------------------------
void ofxSurfingColors::drawImGuiLibrary()
{
	static bool auto_resize = false;

	//--

	// set position and size of a window panel

	float xx = 10;
	float yy = 10;
	float ww = 250;
	float hh = 600;
	
	ImGuiCond flagsCond = ImGuiCond_None;
	flagsCond |= ImGuiCond_FirstUseEver;
	//flagsCond |= ImGuiCond_Appearing;

	ImGui::SetNextWindowSize(ImVec2(ww, hh), flagsCond);
	ImGui::SetNextWindowPos(ImVec2(xx, yy), flagsCond);
	
	// xx + = ww + pad;

	//--

	ImGuiWindowFlags flagsw;
	flagsw = auto_resize ? ImGuiWindowFlags_AlwaysAutoResize : ImGuiWindowFlags_None;
	//flagsw |= flagsWindowsLocked;

	//--

	// blink when a new preset is editing
	float a = ofxSurfingHelpers::getFadeBlink();

	// color and line for selected widgets
	ImVec4 borderLineColor2 = ImVec4(0, 0, 0, a);

	//--

	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(ww, hh));

	guiManager.beginWindow("LIBRARY", NULL, flagsw);
	{
		bool bUpdate = false;

		//--

		// layout
		float _h = WIDGETS_HEIGHT;
		float _hh = _h / 2;
		float _spcx = ImGui::GetStyle().ItemSpacing.x;
		float _spcy = ImGui::GetStyle().ItemSpacing.y;
		float _w100 = ofxImGuiSurfing::getWidgetsWidth(1); // 1 widget full width
		float _w50 = ofxImGuiSurfing::getWidgetsWidth(2);  // 2 widgets half width
		float _w33 = ofxImGuiSurfing::getWidgetsWidth(3);  // 3 widgets third width
		float _w25 = ofxImGuiSurfing::getWidgetsWidth(4);  // 4 widgets quarter width

		//-----

		// Or using raw ImGui
		// Three widgets and fit width in one line
		if (ImGui::Button("LIBRARY", ImVec2(_w100, _h))) {
			colorBrowser.setNextLibrary();
		}
		if (ImGui::Button("SORT TYPE", ImVec2(_w100, _h))) {
			colorBrowser.setNextSortType();
		}

		if (ImGui::Button("< COLOR", ImVec2(_w50, _hh))) {
			colorBrowser.setPreviousColor();
		}
		ImGui::SameLine();
		if (ImGui::Button("COLOR >", ImVec2(_w50, _hh))) {
			colorBrowser.setNextColor();
		}

		if (ImGui::Button("< CARD", ImVec2(_w50, _hh))) {
			colorBrowser.setPreviousCard();
		}
		ImGui::SameLine();
		if (ImGui::Button("CARD >", ImVec2(_w50, _hh))) {
			colorBrowser.setNextCard();
		}
		
		if (ImGui::Button("RANDOM COLOR", ImVec2(_w50, _hh))) {
			colorBrowser.setRandomColor();
		}
		ImGui::SameLine();
		if (ImGui::Button("RANDOM CARD", ImVec2(_w50, _hh))) {
			colorBrowser.setRandomCard();
		}

		//// Draw RAW ImGui or SurfingWidgets with ofParameters

		//// One widget full with and half height
		//if (AddBigToggle(b1, _w100, _h / 2)) {}

		//// Two widgets same line/row with the 50% of window panel width 
		//if (AddBigButton(b2, _w50, _h)) {}
		//ImGui::SameLine();
		//if (AddBigButton(b3, _w50, _h)) {}

		ImGui::Dummy(ImVec2(0, 20));

		//-----

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
		flags |= ImGuiTreeNodeFlags_Framed; // uncomment to draw dark tittle bar
		//flags |= ImGuiTreeNodeFlags_DefaultOpen; // comment to start closed

		ofxImGuiSurfing::AddGroup(colorBrowser.paramsLayout, flags);
		
		ImGui::Dummy(ImVec2(0, 20));

		//-----

		int _colsSize;
		if (lib_CardsMode) _colsSize = lib_RowSize;
		else _colsSize = lib_MaxColumns;

		//--

		// a. pantone cards: 7 colors / row
		//lib_Page_NumColors = lib_NumRows * lib_RowSize;

		// b. responsive
		lib_Page_NumColors = lib_NumRows * lib_MaxColumns.get();

		//lib_Page_Max = lib_TotalColors / (lib_Page_NumColors - 1);
		//lib_Page_Index.setMax(lib_Page_Max - 1);

		lib_Page_Max = lib_TotalColors / lib_Page_NumColors;
		lib_Page_Index.setMax(lib_Page_Max);

		//--

		// pagerize

		int lib_StartCol;
		int lib_EndCol;

		if (bPagerized)
		{
			lib_StartCol = lib_Page_Index * lib_Page_NumColors;
			lib_EndCol = lib_StartCol + lib_Page_NumColors;
		}
		else
		{
			lib_StartCol = 0;
			lib_EndCol = lib_TotalColors - 1;
		}

		//--

		// get color from outside color picked

		//maybe required because get() causes callbacks too (?)
		ENABLE_CALLBACKS_Pickers = false;
		ImVec4 _c = color_Picked.get();
		ENABLE_CALLBACKS_Pickers = true;

		//--

		std::string s;

		// 1. lib name (ie: pantone)
		s = colorBrowser.getLibraryName();
		ImGui::Text(s.c_str());

		ImGui::SameLine();

		// 3. index/total
		s = "    " + ofToString(last_Lib_Index) + " / " + ofToString(lib_TotalColors - 1);
		ImGui::Text(s.c_str());

		// 2. color name
		ImGui::Text(last_Lib_NameColor.c_str());

		//--

		// advanced

#ifdef USE_EXTRA_LIBRARIES
		if (ImGui::CollapsingHeader("Advanced"))
#endif
		{
			if (SHOW_Advanced)
			{
				if (ImGui::CollapsingHeader("LAYOUT"))
				{
					ImGui::Dummy(ImVec2(0, 20));

					ImGui::PushItemWidth(_w33);

					ofxImGuiSurfing::AddParameter(lib_Responsive_ModeFit);
					if (!lib_Responsive_ModeFit)
					{
						ofxImGuiSurfing::AddParameter(lib_Responsive_ModeGrid);
						ImGui::InputInt(sizeLibColBox.getName().c_str(), (int*)&sizeLibColBox.get(), 1, 5);
						ofxImGuiSurfing::AddParameter(bPagerized);
					}

					//-

					// responsive

					if (lib_Responsive_ModeFit)
					{
						ImGui::InputInt(lib_NumRows.getName().c_str(), (int*)&lib_NumRows.get(), 1, 5);
						ImGui::InputInt(lib_MaxColumns.getName().c_str(), (int*)&lib_MaxColumns.get(), 1, 5);
					}
					else if (!lib_Responsive_ModeGrid)
					{
						ofxImGuiSurfing::AddParameter(lib_CardsMode);
						ImGui::InputFloat(scale_LibCol.getName().c_str(), (float *)&scale_LibCol.get(), 0.02f, 0.1f);

						if (!lib_CardsMode)
						{
							ImGui::InputInt(lib_NumRows.getName().c_str(), (int*)&lib_NumRows.get(), 1, 5);
							ImGui::InputInt(lib_MaxColumns.getName().c_str(), (int*)&lib_MaxColumns.get(), 1, 5);

						}
					}
					else if (lib_Responsive_ModeGrid)
					{
						ofxImGuiSurfing::AddParameter(lib_CardsMode);
						ImGui::InputFloat(scale_LibCol.getName().c_str(), (float *)&scale_LibCol.get(), 0.02f, 0.1f);
					}

					lib_MaxColumns = ofClamp(lib_MaxColumns, 1, 100);
					lib_NumRows = ofClamp(lib_NumRows, 1, 100);

					ImGui::PopItemWidth();

					if (ImGui::Button("Reset", ImVec2(_w100, WIDGETS_HEIGHT))) {
						resetLibraryLayout();
					}
				}
			}

			//--

			// 2.2 draw all palette colors grid

			//--

			// libraries

#ifdef USE_EXTRA_LIBRARIES

			if (ImGui::CollapsingHeader("Library"))
			{
				ofxImGuiSurfing::AddParameter(colorBrowser.LibraryColors_Index);
				ofxImGuiSurfing::AddParameter(colorBrowser.LibraryColors_Index_name);

				ImGui::Dummy(ImVec2(0.0f, 5.0f));

				ofxImGuiSurfing::AddParameter(colorBrowser.MODE_SORTING);
				ofxImGuiSurfing::AddParameter(colorBrowser.MODE_SORTING_name);

				ImGui::Dummy(ImVec2(0.0f, 5.0f));

				ofxImGuiSurfing::AddParameter(colorBrowser.ENABLE_keys);
			}
#endif
		}

		//--

		// 1. arrow buttons

		if (bPagerized)
		{
			ImGui::PushButtonRepeat(true);

			// 1.1 prev
			if (ImGui::ArrowButton("##left", ImGuiDir_Left))
			{
				if (lib_Page_Index > 0)
				{
					lib_Page_Index--;
				}
			}

			ImGui::SameLine(0, _spcy);

			// 1.2 next
			if (ImGui::ArrowButton("##right", ImGuiDir_Right))
			{
				if (lib_Page_Index < lib_Page_Max)
				{
					lib_Page_Index++;
				}
			}

			ImGui::PopButtonRepeat();

			//-

			// 2. page slider

			ImGui::SameLine();
			ImGui::PushItemWidth(-50);
			ofxImGuiSurfing::AddParameter(lib_Page_Index);//page slider selector
			ImGui::PopItemWidth();

			lib_Page_Index = ofClamp(lib_Page_Index.get(), 0, lib_Page_Index.getMax());
		}

		//-

		//TODO:
		// random buttons
		//float _h = BUTTON_BIG_HEIGHT;
		//ImVec2 bb{ _w50, _h / 2 };
		//if (ImGui::Button("Random1", bb))
		//{
		//	doRandomizeColorLibrary(false);
		//}
		//ImGui::SameLine();
		//if (ImGui::Button("Random2", bb))
		//{
		//	doRandomizeColorLibrary(true);
		//}

		ImGui::Dummy(ImVec2(0.0f, 5.0f));

		//----

		// 2. grid colors

		// responsive
		ImVec2 _sz((float)sizeLibColBox.get(), (float)sizeLibColBox.get());

		int _countBtns;
		if (lib_Responsive_ModeGrid) _countBtns = lib_TotalColors;
		else _countBtns = lib_EndCol - lib_StartCol;
		float _wx2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

		//--

		// boxes sizes

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

		_w100 = ImGui::GetContentRegionAvail().x - _spcx;
		_h = ImGui::GetContentRegionAvail().y - _spcy;

		ImVec2 _bb;

		if (lib_Responsive_ModeFit)
		{
			float _wb = _w100 / lib_MaxColumns;
			float _wh = _h / lib_NumRows;
			_bb = ImVec2(_wb, _wh);
		}
		else if (lib_Responsive_ModeGrid)
		{
			_bb = _sz;
		}
		else
		{
			_bb = ImVec2(sizeLibColBox * scale_LibCol, sizeLibColBox * scale_LibCol);
		}

		//--

		for (int n = lib_StartCol; n < lib_EndCol && n < lib_TotalColors; n++)
		{
			//--

			// 1. responsive buttons size

			if (lib_Responsive_ModeGrid && !lib_Responsive_ModeFit)
			{
				ImGui::PushID(n);

				style = &ImGui::GetStyle();
				style->WindowMenuButtonPosition = ImGuiDir_None;

				const ImVec4 color2 = style->Colors[ImGuiCol_Button];//do not changes the color
				ImGui::PushStyleColor(ImGuiCol_Button, color2);
			}

			//--

			// 2. color box
			{
				ImGui::PushID(n);

				//ImGui::PushStyleVar(ImGui::ImGuiStyleVar_FrameBorderSize), 1.0f;

				if (!lib_Responsive_ModeGrid)
				{
					if ((n % _colsSize) != 0)
					{
						ImGui::SameLine(0, 0);//vertical inter line
					}
				}

				// draw border to selected color
				bool bDrawBorder = false;
				if (n == last_ColorPicked_Lib)
				{
					bDrawBorder = true;
					ImGui::PushStyleColor(ImGuiCol_Border, borderLineColor2);
					ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderLineWidth + 1.5);
				}

				//--

				// 3. color button

				ImGuiColorEditFlags _flags =
					ImGuiColorEditFlags_NoAlpha |
					ImGuiColorEditFlags_NoPicker |
					ImGuiColorEditFlags_NoTooltip;

				ofFloatColor _c = ofColor(palette_Lib_Cols[n]);

				// 4. if one clicked

				if (ImGui::ColorButton("##paletteLib", _c, _flags, _bb))
				{
					// picked
					color_Picked = _c;

					// index
					last_ColorPicked_Lib = n;
					last_Lib_Index = n;

					//---

					// color name
					if (n < palette_Lib_Names.size())
					{
						last_Lib_NameColor = palette_Lib_Names[n];

						std::string str = "Lib Picked: [" + ofToString(last_ColorPicked_Lib) + "] " + last_Lib_NameColor;
						ofLogNotice(__FUNCTION__) << str;
					}

					//-

					bUpdate = true;

					//--

					////TODO:
					////ofxSurfingColors
					//last_Lib_Index = n;
					//colorBrowser.index_Library = last_Lib_Index;
				}

				//----

				// draw border to selected color
				if (bDrawBorder)
				{
					ImGui::PopStyleColor();
					ImGui::PopStyleVar(1);
				}

				ImGui::PopID();
			}

			//--

			// responsive buttons size
			if (lib_Responsive_ModeGrid && !lib_Responsive_ModeFit)
			{
				ImGui::PopStyleColor();

				float last_button_x2 = ImGui::GetItemRectMax().x;

				float next_button_x2 = last_button_x2 + _sz.x; // Expected position if next button was on same line
				//float next_button_x2 = last_button_x2 + style->ItemSpacing.x + _wSz.x; // Expected position if next button was on same line

				if (n + 1 < _countBtns && next_button_x2 < _wx2)
				{
					ImGui::SameLine(0, 0);//vertical inter line
					//ImGui::SameLine(0, ImGui::GetStyle().ItemSpacing.y);//vertical inter line
				}

				ImGui::PopID();
			}
		}

		ImGui::PopStyleVar();

		//----

		if (bUpdate)
		{
			//refresh_FromPicked();
		}
	}
	guiManager.endWindow();

	ImGui::PopStyleVar();
}

//--------------------------------------------------------------
void ofxSurfingColors::refresh_Libs()
{
	lib_TotalColors = colorBrowser.colors_STRUCT.size();
	lib_MaxColumns = colorBrowser.getCardsAmountcolors();//better fit layout

	lib_Page_NumColors = lib_NumRows * lib_RowSize;
	lib_Page_Max = lib_TotalColors / lib_Page_NumColors - 1;

	palette_Lib_Cols.clear();
	palette_Lib_Cols = colorBrowser.getLibraryColors();

	palette_Lib_Names.clear();
	palette_Lib_Names = colorBrowser.getNames();

	lib_Page_Index = 0;
	last_ColorPicked_Lib = 0;

	//--

	resetLibraryLayout();
}



//--------------------------------------------------------------
void ofxSurfingColors::resetLibraryLayout()
{
	ofLogNotice(__FUNCTION__) << "----------------- RESET LIBRARY -----------------" << endl;

	lib_Responsive_ModeGrid = false;
	lib_CardsMode = false;
	bPagerized = true;
	lib_Page_Index = 0;
	scale_LibCol = 25;
	lib_NumRows = 14;
	lib_MaxColumns = 7;
	lib_Responsive_ModeFit = true;
}

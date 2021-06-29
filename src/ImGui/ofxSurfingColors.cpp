#include "ofxSurfingColors.h"

#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
#undef USE_OFX_COLOR_BROWSER_INTERFACE
#endif

//--------------------------------------------------------------
ofxSurfingColors::ofxSurfingColors() {
	ofAddListener(ofEvents().update, this, &ofxSurfingColors::update);
	ofAddListener(ofEvents().draw, this, &ofxSurfingColors::draw);
	ofAddListener(ofEvents().keyPressed, this, &ofxSurfingColors::keyPressed);
}

//--------------------------------------------------------------
ofxSurfingColors::~ofxSurfingColors() {
	ofRemoveListener(ofEvents().update, this, &ofxSurfingColors::update);
	ofRemoveListener(ofEvents().draw, this, &ofxSurfingColors::draw);
	ofRemoveListener(ofEvents().keyPressed, this, &ofxSurfingColors::keyPressed);
}

//--------------------------------------------------------------
void ofxSurfingColors::setup() {
	guiManager.setImGuiAutodraw(true);
	guiManager.setup();

	colorBrowser.setupColorPtr(colorBg); // set local target color receiver
	colorBrowser.setup();
}

//--------------------------------------------------------------
void ofxSurfingColors::setupColorPtr(ofFloatColor &c)
{
	//color_BACK = c;
	color_BACK_OFAPP = &c;
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
}

//--------------------------------------------------------------
void ofxSurfingColors::exit() {
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

			//ImGui::Begin("Show Windows", &bOpen0, window_flags);
			guiManager.beginWindow("ofxSurfingColors", NULL, window_flags);
			{
				ofxImGuiSurfing::AddToggleRoundedButton(colorBrowser.bGui);
				ofxImGuiSurfing::AddToggleRoundedButton(colorBrowser.bGuiDebug);
				ofxImGuiSurfing::AddToggleRoundedButton(colorBrowser.bKeys);
				ofxImGuiSurfing::AddToggleRoundedButton(SHOW_Advanced);


			}
			guiManager.endWindow();
			//ImGui::End();
		}

		//--

		gui_Library();
	}
	guiManager.end();
}

//--------------------------------------------------------------
void ofxSurfingColors::windowResized(int w, int h) {
	colorBrowser.windowResized(w, h);
}



//--------------------------------------------------------------
void ofxSurfingColors::gui_Library()
{
	static bool auto_resize = false;

	float ww, hh;
	ww = 175;
	hh = 350;
	ImGui::SetWindowSize(ImVec2(ww, hh));

	ImGuiWindowFlags flagsw;
	flagsw = auto_resize ? ImGuiWindowFlags_AlwaysAutoResize : ImGuiWindowFlags_None;
	//flagsw |= flagsWindowsLocked;

	//--

	//blink when a new preset is editing
	float a = ofxSurfingHelpers::getFadeBlink();
	// color and line for selected widgets
	ImVec4 borderLineColor2 = ImVec4(0, 0, 0, a);

	//--

	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(ww, hh));

	guiManager.beginWindow("LIBRARY", NULL, flagsw);
	//if (ofxImGui::BeginWindow("LIBRARY", mainSettings, flagsw))
	{
		bool bUpdate = false;

		//--

		float _spcx;
		float _spcy;
		float _w100;
		float _h100;
		float _w99;
		float _w50;
		float _w33;
		float _w25;
		float _h;
		ofxImGuiSurfing::refreshImGui_WidgetsSizes(_spcx, _spcy, _w100, _h100, _w99, _w50, _w33, _w25, _h);

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
				if (ImGui::CollapsingHeader("Layout"))
				{
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
			ImGui::PushItemWidth(-40);
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

			// responsive buttons size

			if (lib_Responsive_ModeGrid && !lib_Responsive_ModeFit)
			{
				ImGui::PushID(n);

				style = &ImGui::GetStyle();
				style->WindowMenuButtonPosition = ImGuiDir_None;

				const ImVec4 color2 = style->Colors[ImGuiCol_Button];//do not changes the color
				ImGui::PushStyleColor(ImGuiCol_Button, color2);
			}

			//--

			// color box
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

				// color button

				ImGuiColorEditFlags _flags =
					ImGuiColorEditFlags_NoAlpha |
					ImGuiColorEditFlags_NoPicker |
					ImGuiColorEditFlags_NoTooltip;

				ofFloatColor _c = ofColor(palette_Lib_Cols[n]);

				// if one clicked

				if (ImGui::ColorButton("##paletteLib", _c, _flags, _bb))

				{
					// picked
					color_Picked = _c;

					// index
					last_ColorPicked_Lib = n;
					last_Lib_Index = n;

					// color name
					if (n < palette_Lib_Names.size())
					{
						last_Lib_NameColor = palette_Lib_Names[n];

						std::string str = "Lib Picked: [" + ofToString(last_ColorPicked_Lib) + "] " +
							last_Lib_NameColor;
						ofLogNotice(__FUNCTION__) << str;
					}

					//-

					bUpdate = true;
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

	//ofxImGui::EndWindow(mainSettings);
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

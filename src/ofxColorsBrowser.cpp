#include "ofxColorsBrowser.h"

//--------------------------------------------------------------
// comparing colors to sorting methods

bool compareName(const colorMapping_STRUCT &s1, const colorMapping_STRUCT &s2)
{
	return s1.name < s2.name;
}

bool compareBrightness(const colorMapping_STRUCT &s1, const colorMapping_STRUCT &s2)
{
	return s1.color.getBrightness() < s2.color.getBrightness();
}

bool compareHue(const colorMapping_STRUCT &s1, const colorMapping_STRUCT &s2)
{
	return s1.color.getHue() < s2.color.getHue();
}

bool compareSaturation(const colorMapping_STRUCT &s1, const colorMapping_STRUCT &s2)
{
	return s1.color.getSaturation() < s2.color.getSaturation();
}

bool comparePosition(const colorMapping_STRUCT &s1, const colorMapping_STRUCT &s2)
{
	return s1.position < s2.position;
}

//----

//--------------------------------------------------------------
void ofxColorsBrowser::windowResized(int w, int h) {
	//setPositionHelper(glm::vec2(ofGetWidth() - 400, 0));
}

//--------------------------------------------------------------
ofxColorsBrowser::ofxColorsBrowser()
{
	ofxSurfingHelpers::setThemeDark_ofxGui();

#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
	addMouseListeners();
#endif

#ifdef KEY_SHORTCUTS_ENABLE
	setEnableKeys(true);
#else
	setEnableKeys(false);
#endif

	//-

	path_Global = "ofxColorsBrowser/";
	path_FileSettings = path_Global + "AppSettings.xml";

	//-

	// library files
	path_FilePantone = path_Global + "pantone-colors.json";
	path_FileSanzoWada = path_Global + "SANZO_WADA_Library.json";
	path_FileMaterial = path_Global + "material-colors.json";
	path_FileCheprasov = path_Global + "cheprasov-colors.json";
	path_FileCrayola = path_Global + "crayola.json";
	// * add your new libs here!

	//-

	ofxSurfingHelpers::CheckFolder(path_Global);

	//--

	helpInfo = "";
	helpInfo += "\n";
	helpInfo += "KEYS";
	helpInfo += "\n\n";
	helpInfo += "Mouse Click           Colors  ";
	helpInfo += "\n";
	helpInfo += "Up|Down|Left|Right            ";
	helpInfo += "\n";
	helpInfo += "\n";
	helpInfo += "BackSpace             Library ";
	helpInfo += "\n";
	helpInfo += "\n";
	helpInfo += "space|a|d|w|s|        Cards   ";
	helpInfo += "\n";
	helpInfo += "r                     Random  ";
	helpInfo += "\n";
	helpInfo += "\n";
	helpInfo += "Tab|0|1|2|3|4         Sorting ";
	helpInfo += "\n";
	helpInfo += "\n";
	helpInfo += "K                     Keys    ";
	helpInfo += "\n";
	helpInfo += "D                     Debug   ";
	helpInfo += "\n";
	helpInfo += "g                     Gui     ";
	helpInfo += "\n";
	//helpInfo += "G                     Gui Panel";
	//helpInfo += "\n";
}

//--------------------------------------------------------------
void ofxColorsBrowser::buildColors()
{
	ofLogNotice(__FUNCTION__);

	colors_STRUCT.clear();
	colors_NamesMAP.clear();
	//TODO: seems is not erasing last name colors..?

	//-

	index_Card = 0;
	index_Color = 0;

	//--

	// 0. OFX_PANTONE_COLORS

	if (index_Library == OFX_PANTONE_COLORS)
	{
		ofLogNotice(__FUNCTION__) << "OFX_PANTONE_COLORS";

		// ideal card size and layout
		{
			amtColorsInCard = 7;
			amtCardsInRow = 10;

			boxSize = 15;
			boxPad = 0.5;

			cardColor_size = 100;
			cardColor_pad = 20;
		}

		//-

		std::string name;
		ofColor c;

		for (int i = 0; i < colors_PantoneNames.size(); i++)
		{
			name = colors_PantoneNames[i];
			c = colors_Pantone[i];
			{
				// 1. names map
				colors_NamesMAP[name] = c;

				// 2. struct
				colorMapping_STRUCT myColor;
				myColor.name = name;
				myColor.color = c;
				myColor.position = i;

				// 3. add color to vector
				colors_STRUCT.push_back(myColor);
			}
		}
		ofLogNotice(__FUNCTION__);
	}

	//--

	// 1. OFX_SANZOWADA_COLORS

	else if (index_Library == OFX_SANZOWADA_COLORS)
	{
		ofLogNotice(__FUNCTION__) << "OFX_SANZOWADA_COLORS";

		// ideal card size and layout
		{
			amtColorsInCard = 8;
			amtCardsInRow = 2;

			boxSize = 52;
			boxPad = 1;
			
			cardColor_size = 100;
			cardColor_pad = 20;
		}

		//-

		std::string name;
		ofColor c;

		for (int i = 0; i < colors_SanzoWadaNames.size(); i++)
		{
			name = colors_SanzoWadaNames[i];
			c = colors_SanzoWada[i];
			{
				// 1. names map
				colors_NamesMAP[name] = c;

				// 2. struct
				colorMapping_STRUCT myColor;
				myColor.name = name;
				myColor.color = c;
				myColor.position = i;

				// 3. add color to vector
				colors_STRUCT.push_back(myColor);
			}
		}
		ofLogNotice(__FUNCTION__);
	}

	//----

	// 2. OFX_COLOR_NATIVE

	else if (index_Library == OFX_COLOR_NATIVE)
	{
		// build a map from name to ofColor of all the named OF colors;
		colors_NamesMAP["white"] = ofColor::white;
		colors_NamesMAP["gray"] = ofColor::gray;
		colors_NamesMAP["black"] = ofColor::black;
		colors_NamesMAP["red"] = ofColor::red;
		colors_NamesMAP["green"] = ofColor::green;
		colors_NamesMAP["blue"] = ofColor::blue;
		colors_NamesMAP["cyan"] = ofColor::cyan;
		colors_NamesMAP["magenta"] = ofColor::magenta;
		colors_NamesMAP["yellow"] = ofColor::yellow;
		colors_NamesMAP["aliceBlue"] = ofColor::aliceBlue;
		colors_NamesMAP["antiqueWhite"] = ofColor::antiqueWhite;
		colors_NamesMAP["aqua"] = ofColor::aqua;
		colors_NamesMAP["aquamarine"] = ofColor::aquamarine;
		colors_NamesMAP["azure"] = ofColor::azure;
		colors_NamesMAP["beige"] = ofColor::beige;
		colors_NamesMAP["bisque"] = ofColor::bisque;
		colors_NamesMAP["blanchedAlmond"] = ofColor::blanchedAlmond;
		colors_NamesMAP["blueViolet"] = ofColor::blueViolet;
		colors_NamesMAP["brown"] = ofColor::brown;
		colors_NamesMAP["burlyWood"] = ofColor::burlyWood;
		colors_NamesMAP["cadetBlue"] = ofColor::cadetBlue;
		colors_NamesMAP["chartreuse"] = ofColor::chartreuse;
		colors_NamesMAP["chocolate"] = ofColor::chocolate;
		colors_NamesMAP["coral"] = ofColor::coral;
		colors_NamesMAP["cornflowerBlue"] = ofColor::cornflowerBlue;
		colors_NamesMAP["cornsilk"] = ofColor::cornsilk;
		colors_NamesMAP["crimson"] = ofColor::crimson;
		colors_NamesMAP["darkBlue"] = ofColor::darkBlue;
		colors_NamesMAP["darkCyan"] = ofColor::darkCyan;
		colors_NamesMAP["darkGoldenRod"] = ofColor::darkGoldenRod;
		colors_NamesMAP["darkGray"] = ofColor::darkGray;
		colors_NamesMAP["darkGrey"] = ofColor::darkGrey;
		colors_NamesMAP["darkGreen"] = ofColor::darkGreen;
		colors_NamesMAP["darkKhaki"] = ofColor::darkKhaki;
		colors_NamesMAP["darkMagenta"] = ofColor::darkMagenta;
		colors_NamesMAP["darkOliveGreen"] = ofColor::darkOliveGreen;
		colors_NamesMAP["darkorange"] = ofColor::darkorange;
		colors_NamesMAP["darkOrchid"] = ofColor::darkOrchid;
		colors_NamesMAP["darkRed"] = ofColor::darkRed;
		colors_NamesMAP["darkSalmon"] = ofColor::darkSalmon;
		colors_NamesMAP["darkSeaGreen"] = ofColor::darkSeaGreen;
		colors_NamesMAP["darkSlateBlue"] = ofColor::darkSlateBlue;
		colors_NamesMAP["darkSlateGray"] = ofColor::darkSlateGray;
		colors_NamesMAP["darkSlateGrey"] = ofColor::darkSlateGrey;
		colors_NamesMAP["darkTurquoise"] = ofColor::darkTurquoise;
		colors_NamesMAP["darkViolet"] = ofColor::darkViolet;
		colors_NamesMAP["deepPink"] = ofColor::deepPink;
		colors_NamesMAP["deepSkyBlue"] = ofColor::deepSkyBlue;
		colors_NamesMAP["dimGray"] = ofColor::dimGray;
		colors_NamesMAP["dimGrey"] = ofColor::dimGrey;
		colors_NamesMAP["dodgerBlue"] = ofColor::dodgerBlue;
		colors_NamesMAP["fireBrick"] = ofColor::fireBrick;
		colors_NamesMAP["floralWhite"] = ofColor::floralWhite;
		colors_NamesMAP["forestGreen"] = ofColor::forestGreen;
		colors_NamesMAP["fuchsia"] = ofColor::fuchsia;
		colors_NamesMAP["gainsboro"] = ofColor::gainsboro;
		colors_NamesMAP["ghostWhite"] = ofColor::ghostWhite;
		colors_NamesMAP["gold"] = ofColor::gold;
		colors_NamesMAP["goldenRod"] = ofColor::goldenRod;
		colors_NamesMAP["grey"] = ofColor::grey;
		colors_NamesMAP["greenYellow"] = ofColor::greenYellow;
		colors_NamesMAP["honeyDew"] = ofColor::honeyDew;
		colors_NamesMAP["hotPink"] = ofColor::hotPink;
		colors_NamesMAP["indianRed "] = ofColor::indianRed;
		colors_NamesMAP["indigo "] = ofColor::indigo;
		colors_NamesMAP["ivory"] = ofColor::ivory;
		colors_NamesMAP["khaki"] = ofColor::khaki;
		colors_NamesMAP["lavender"] = ofColor::lavender;
		colors_NamesMAP["lavenderBlush"] = ofColor::lavenderBlush;
		colors_NamesMAP["lawnGreen"] = ofColor::lawnGreen;
		colors_NamesMAP["lemonChiffon"] = ofColor::lemonChiffon;
		colors_NamesMAP["lightBlue"] = ofColor::lightBlue;
		colors_NamesMAP["lightCoral"] = ofColor::lightCoral;
		colors_NamesMAP["lightCyan"] = ofColor::lightCyan;
		colors_NamesMAP["lightGoldenRodYellow"] = ofColor::lightGoldenRodYellow;
		colors_NamesMAP["lightGray"] = ofColor::lightGray;
		colors_NamesMAP["lightGrey"] = ofColor::lightGrey;
		colors_NamesMAP["lightGreen"] = ofColor::lightGreen;
		colors_NamesMAP["lightPink"] = ofColor::lightPink;
		colors_NamesMAP["lightSalmon"] = ofColor::lightSalmon;
		colors_NamesMAP["lightSeaGreen"] = ofColor::lightSeaGreen;
		colors_NamesMAP["lightSkyBlue"] = ofColor::lightSkyBlue;
		colors_NamesMAP["lightSlateGray"] = ofColor::lightSlateGray;
		colors_NamesMAP["lightSlateGrey"] = ofColor::lightSlateGrey;
		colors_NamesMAP["lightSteelBlue"] = ofColor::lightSteelBlue;
		colors_NamesMAP["lightYellow"] = ofColor::lightYellow;
		colors_NamesMAP["lime"] = ofColor::lime;
		colors_NamesMAP["limeGreen"] = ofColor::limeGreen;
		colors_NamesMAP["linen"] = ofColor::linen;
		colors_NamesMAP["maroon"] = ofColor::maroon;
		colors_NamesMAP["mediumAquaMarine"] = ofColor::mediumAquaMarine;
		colors_NamesMAP["mediumBlue"] = ofColor::mediumBlue;
		colors_NamesMAP["mediumOrchid"] = ofColor::mediumOrchid;
		colors_NamesMAP["mediumPurple"] = ofColor::mediumPurple;
		colors_NamesMAP["mediumSeaGreen"] = ofColor::mediumSeaGreen;
		colors_NamesMAP["mediumSlateBlue"] = ofColor::mediumSlateBlue;
		colors_NamesMAP["mediumSpringGreen"] = ofColor::mediumSpringGreen;
		colors_NamesMAP["mediumTurquoise"] = ofColor::mediumTurquoise;
		colors_NamesMAP["mediumVioletRed"] = ofColor::mediumVioletRed;
		colors_NamesMAP["midnightBlue"] = ofColor::midnightBlue;
		colors_NamesMAP["mintCream"] = ofColor::mintCream;
		colors_NamesMAP["mistyRose"] = ofColor::mistyRose;
		colors_NamesMAP["moccasin"] = ofColor::moccasin;
		colors_NamesMAP["navajoWhite"] = ofColor::navajoWhite;
		colors_NamesMAP["navy"] = ofColor::navy;
		colors_NamesMAP["oldLace"] = ofColor::oldLace;
		colors_NamesMAP["olive"] = ofColor::olive;
		colors_NamesMAP["oliveDrab"] = ofColor::oliveDrab;
		colors_NamesMAP["orange"] = ofColor::orange;
		colors_NamesMAP["orangeRed"] = ofColor::orangeRed;
		colors_NamesMAP["orchid"] = ofColor::orchid;
		colors_NamesMAP["paleGoldenRod"] = ofColor::paleGoldenRod;
		colors_NamesMAP["paleGreen"] = ofColor::paleGreen;
		colors_NamesMAP["paleTurquoise"] = ofColor::paleTurquoise;
		colors_NamesMAP["paleVioletRed"] = ofColor::paleVioletRed;
		colors_NamesMAP["papayaWhip"] = ofColor::papayaWhip;
		colors_NamesMAP["peachPuff"] = ofColor::peachPuff;
		colors_NamesMAP["peru"] = ofColor::peru;
		colors_NamesMAP["pink"] = ofColor::pink;
		colors_NamesMAP["plum"] = ofColor::plum;
		colors_NamesMAP["powderBlue"] = ofColor::powderBlue;
		colors_NamesMAP["purple"] = ofColor::purple;
		colors_NamesMAP["rosyBrown"] = ofColor::rosyBrown;
		colors_NamesMAP["royalBlue"] = ofColor::royalBlue;
		colors_NamesMAP["saddleBrown"] = ofColor::saddleBrown;
		colors_NamesMAP["salmon"] = ofColor::salmon;
		colors_NamesMAP["sandyBrown"] = ofColor::sandyBrown;
		colors_NamesMAP["seaGreen"] = ofColor::seaGreen;
		colors_NamesMAP["seaShell"] = ofColor::seaShell;
		colors_NamesMAP["sienna"] = ofColor::sienna;
		colors_NamesMAP["silver"] = ofColor::silver;
		colors_NamesMAP["skyBlue"] = ofColor::skyBlue;
		colors_NamesMAP["slateBlue"] = ofColor::slateBlue;
		colors_NamesMAP["slateGray"] = ofColor::slateGray;
		colors_NamesMAP["slateGrey"] = ofColor::slateGrey;
		colors_NamesMAP["snow"] = ofColor::snow;
		colors_NamesMAP["springGreen"] = ofColor::springGreen;
		colors_NamesMAP["steelBlue"] = ofColor::steelBlue;
		colors_NamesMAP["tan"] = ofColor::tan;
		colors_NamesMAP["teal"] = ofColor::teal;
		colors_NamesMAP["thistle"] = ofColor::thistle;
		colors_NamesMAP["tomato"] = ofColor::tomato;
		colors_NamesMAP["turquoise"] = ofColor::turquoise;
		colors_NamesMAP["violet"] = ofColor::violet;
		colors_NamesMAP["wheat"] = ofColor::wheat;
		colors_NamesMAP["whiteSmoke"] = ofColor::whiteSmoke;
		colors_NamesMAP["yellowGreen"] = ofColor::yellowGreen;

		int i = 0;
		for (auto const &x : colors_NamesMAP)
		{
			// std::cout << x.first  // string (key)
			// << ':'
			// << x.second // string's value
			// << std::endl ;

			colorMapping_STRUCT myColor;
			myColor.name = x.first;
			myColor.color = x.second;
			myColor.position = i;

			colors_STRUCT.push_back(myColor);

			i++;
		}

		//--

		// dessired distribution for this palette
		{
			amtColorsInCard = 10;
			amtCardsInRow = 2;

			boxSize = 50;
			boxPad = 2;

			cardColor_size = 100;
			cardColor_pad = 10;
		}
	}

	//----

	// 3. OFX_MATERIAL_COLOR

	//TODO:
	else if (index_Library == OFX_MATERIAL_COLOR)
	{
		ofLogNotice(__FUNCTION__) << "OFX_MATERIAL_COLOR";

	}

	//----

	// 4. OFX_OPEN_COLOR

	else if (index_Library == OFX_OPEN_COLOR)
	{
		ofLogNotice(__FUNCTION__) << "OFX_OPEN_COLOR";

#define NUM_COLORS_ROW 10
		// that's the ideal distribution for open color palette
		
		bool flipOrder = true;
		int iFlip;
		int pos = 0;//-1? to set correlative positions...

		for (int i = 0; i < NUM_COLORS_ROW; i++)
		{
			// flip order: iFlip
			if (flipOrder) iFlip = (NUM_COLORS_ROW - 1) - i;
			else iFlip = i;

			// 1.
			colors_NamesMAP["GREY " + ofToString(i)] = oc_gray_[iFlip];
			colors_NamesMAP["RED " + ofToString(i)] = oc_red_[iFlip];
			colors_NamesMAP["PINK " + ofToString(i)] = oc_pink_[iFlip];
			colors_NamesMAP["GRAPE " + ofToString(i)] = oc_grape_[iFlip];
			colors_NamesMAP["VIOLET " + ofToString(i)] = oc_violet_[iFlip];
			colors_NamesMAP["INDIGO " + ofToString(i)] = oc_indigo_[iFlip];
			colors_NamesMAP["BLUE " + ofToString(i)] = oc_blue_[iFlip];
			colors_NamesMAP["CYAN " + ofToString(i)] = oc_cyan_[iFlip];
			colors_NamesMAP["TEAL " + ofToString(i)] = oc_teal_[iFlip];
			colors_NamesMAP["GREEN " + ofToString(i)] = oc_green_[iFlip];
			colors_NamesMAP["LIME " + ofToString(i)] = oc_lime_[iFlip];
			colors_NamesMAP["YELLOW " + ofToString(i)] = oc_yellow_[iFlip];
			colors_NamesMAP["ORANGE " + ofToString(i)] = oc_orange_[iFlip];

			// 2. vector
			colorMapping_STRUCT colorGREY;
			colorMapping_STRUCT colorRED;
			colorMapping_STRUCT colorPINK;
			colorMapping_STRUCT colorGRAPE;
			colorMapping_STRUCT colorVIOLET;
			colorMapping_STRUCT colorINDIGO;
			colorMapping_STRUCT colorBLUE;
			colorMapping_STRUCT colorCYAN;
			colorMapping_STRUCT colorTEAL;
			colorMapping_STRUCT colorGREEN;
			colorMapping_STRUCT colorLIME;
			colorMapping_STRUCT colorYELLOW;
			colorMapping_STRUCT colorORANGE;

			colorGREY.name = "GREY " + ofToString(i);
			colorRED.name = "RED " + ofToString(i);
			colorPINK.name = "PINK " + ofToString(i);
			colorGRAPE.name = "GRAPE " + ofToString(i);
			colorVIOLET.name = "VIOLET " + ofToString(i);
			colorINDIGO.name = "INDIGO " + ofToString(i);
			colorBLUE.name = "BLUE " + ofToString(i);
			colorCYAN.name = "CYAN " + ofToString(i);
			colorTEAL.name = "TEAL " + ofToString(i);
			colorGREEN.name = "GREEN " + ofToString(i);
			colorLIME.name = "LIME " + ofToString(i);
			colorYELLOW.name = "YELLOW " + ofToString(i);
			colorORANGE.name = "ORANGE " + ofToString(i);

			colorGREY.color = oc_gray_[iFlip];
			colorRED.color = oc_red_[iFlip];
			colorPINK.color = oc_pink_[iFlip];
			colorGRAPE.color = oc_grape_[iFlip];
			colorVIOLET.color = oc_violet_[iFlip];
			colorINDIGO.color = oc_indigo_[iFlip];
			colorBLUE.color = oc_blue_[iFlip];
			colorCYAN.color = oc_cyan_[iFlip];
			colorTEAL.color = oc_teal_[iFlip];
			colorGREEN.color = oc_green_[iFlip];
			colorLIME.color = oc_lime_[iFlip];
			colorYELLOW.color = oc_yellow_[iFlip];
			colorORANGE.color = oc_orange_[iFlip];

			colorGREY.position = pos++;
			colorRED.position = pos++;
			colorPINK.position = pos++;
			colorGRAPE.position = pos++;
			colorVIOLET.position = pos++;
			colorINDIGO.position = pos++;
			colorBLUE.position = pos++;
			colorCYAN.position = pos++;
			colorTEAL.position = pos++;
			colorGREEN.position = pos++;
			colorLIME.position = pos++;
			colorYELLOW.position = pos++;
			colorORANGE.position = pos++;

			//-

			colors_STRUCT.push_back(colorGREY);
			colors_STRUCT.push_back(colorRED);
			colors_STRUCT.push_back(colorPINK);
			colors_STRUCT.push_back(colorGRAPE);
			colors_STRUCT.push_back(colorVIOLET);
			colors_STRUCT.push_back(colorINDIGO);
			colors_STRUCT.push_back(colorBLUE);
			colors_STRUCT.push_back(colorCYAN);
			colors_STRUCT.push_back(colorTEAL);
			colors_STRUCT.push_back(colorGREEN);
			colors_STRUCT.push_back(colorLIME);
			colors_STRUCT.push_back(colorYELLOW);
			colors_STRUCT.push_back(colorORANGE);
		}

		//-

		// ideal card size and layout
		{
			amtColorsInCard = 13; //  important to mantain gradient
			amtCardsInRow = 1;

			boxSize = 50;
			boxPad = 1;

			cardColor_size = 70;
			cardColor_pad = 5;
		}
	}

	//----

	// 5. OFX_CHEPRASOV

	else if (index_Library == OFX_CHEPRASOV)
	{
		ofLogNotice(__FUNCTION__) << "OFX_CHEPRASOV";

		// ideal card size and layout
		{
			amtColorsInCard = 7;
			amtCardsInRow = 9;

			boxSize = 20;
			boxPad = 1;

			cardColor_size = 100;
			cardColor_pad = 20;
		}

		//-

		std::string name;
		ofColor c;

		for (int i = 0; i < colors_CheprasovNames.size(); i++)
		{
			name = colors_CheprasovNames[i];
			c = colors_Cheprasov[i];
			{
				// 1. names map
				colors_NamesMAP[name] = c;

				// 2. struct
				colorMapping_STRUCT myColor;
				myColor.name = name;
				myColor.color = c;
				myColor.position = i;

				// 3. add color to vector
				colors_STRUCT.push_back(myColor);
			}
		}
		ofLogNotice(__FUNCTION__);
	}

	//----

	// 6. OFX_CRAYOLA

	else if (index_Library == OFX_CRAYOLA)
	{
		ofLogNotice(__FUNCTION__) << "OFX_CRAYOLA";

		// ideal card size and layout
		{
			//TODO: responsive
			int count = colors_STRUCT.size();
			int w = ofGetWidth() - 300;
			int h = ofGetHeight() - 200;

			amtColorsInCard = 7;
			amtCardsInRow = 3;

			boxSize = 60;
			boxPad = 1;

			cardColor_size = 100;
			cardColor_pad = 20;
		}

		//-

		std::string name;
		ofColor c;

		for (int i = 0; i < colors_CrayolaNames.size(); i++)
		{
			name = colors_CrayolaNames[i];
			c = colors_Crayola[i];
			{
				// 1. names map
				colors_NamesMAP[name] = c;

				// 2. struct
				colorMapping_STRUCT myColor;
				myColor.name = name;
				myColor.color = c;
				myColor.position = i;

				// 3. add color to vector
				colors_STRUCT.push_back(myColor);
			}
		}
		ofLogNotice(__FUNCTION__);
	}

	// * add your new libs here!
}

//--

// importers

//--------------------------------------------------------------
void ofxColorsBrowser::load_Pantone_JSON()
{
	ofLogNotice(__FUNCTION__);

	colors_PantoneNames.clear();
	colors_Pantone.clear();

	ofFile file(path_FilePantone);
	if (file.exists())
	{
		file >> js;
		ofLogNotice(__FUNCTION__) << js;
		ofLogNotice(__FUNCTION__) << endl;

		int i = 0;
		for (auto &jsName : js["names"])
		{
			//ofLogNotice(__FUNCTION__) << "NAMES  ["<<i<<"] "<<jsName<<endl;
			colors_PantoneNames.push_back(jsName);
			i++;
		}

		i = 0;
		for (auto &jsValues : js["values"])
		{
			//ofLogNotice(__FUNCTION__) << "VALUES ["<<i<<"] "<<jsValues<<endl;
			ofColor c;
			std::string colorHEXcode = ofToString(jsValues);
			vector<std::string> colorHEXcode_VEC = ofSplitString(colorHEXcode, "#");
			std::string myCol = colorHEXcode_VEC[1];
			vector<std::string> myCol2 = ofSplitString(myCol, "\"");
			hexToColor(c, myCol2[0]);

			colors_Pantone.push_back(c);
			i++;
		}
	}
	else
	{
		ofLogNotice(__FUNCTION__) << "FILE '" << path_FilePantone << "' NOT FOUND!";
	}
}

//--------------------------------------------------------------
void ofxColorsBrowser::load_SanzoWadaDictionary_JSON()
{
	ofLogNotice(__FUNCTION__);

	colors_SanzoWada.clear();
	colors_SanzoWadaNames.clear();

	ofFile file(path_FileSanzoWada);
	if (file.exists())
	{
		file >> jSanzoWada;
		ofLogNotice(__FUNCTION__) << jSanzoWada;
		ofLogNotice(__FUNCTION__) << endl;

		for (auto &jc : jSanzoWada)
		{
			string _name = jc["name"];
			string _hex = jc["hex"];

			ofStringReplace(_hex, "#", "");
			ofColor c;
			hexToColor(c, _hex);

			colors_SanzoWadaNames.push_back(_name);
			colors_SanzoWada.push_back(c);
		}
	}
	else
	{
		ofLogNotice(__FUNCTION__) << "FILE '" << path_FilePantone << "' NOT FOUND!";
	}
}

//--------------------------------------------------------------
void ofxColorsBrowser::load_Material_JSON()
{
	//TODO:

	ofLogNotice(__FUNCTION__);

	colors_MaterialNames.clear();
	colors_Material.clear();

	ofFile file(path_FileMaterial);
	if (file.exists())
	{
		file >> js;
		ofLogNotice(__FUNCTION__) << js;

		int i = 0;
		for (auto &jp : js)
		{
			//		ofLogNotice(__FUNCTION__) << "----------------------\n" << "SUB-PALETTE  [" << i << "] " << jp;
			//		//ofLogNotice(__FUNCTION__) << ofToString(jp[i]); jp.get(i);
			//		ofLogNotice(__FUNCTION__) << jp[i];

			//		int c = 0;
			//		for (auto &jc : jp)
			//		{
			//			ofLogNotice(__FUNCTION__) << "COLOR  [" << i << "] " << jc;// << " " << jp[i];

			//			for (auto &jt : jc)
			//			{
			//				colors_MaterialNames.push_back(tagsMaterial[c]);
			//				ofLogNotice(__FUNCTION__) << "Name:" << ofToString(tagsMaterial[c]) << " Hex:" << ofToString(jc);
			//			}

			//			//colors_MaterialNames.push_back(jsName);
			//			c++;
			//		}

			//		//i = 0;
			//		//for (auto &jsValues : js["values"])
			//		//{
			//		//	//ofLogNotice(__FUNCTION__) << "VALUES ["<<i<<"] "<<jsValues<<endl;
			//		//	ofColor c;
			//		//	std::string colorHEXcode = ofToString(jsValues);
			//		//	vector<std::string> colorHEXcode_VEC = ofSplitString(colorHEXcode, "#");
			//		//	std::string myCol = colorHEXcode_VEC[1];
			//		//	vector<std::string> myCol2 = ofSplitString(myCol, "\"");
			//		//	hexToColor(c, myCol2[0]);

			//		//	colors_Pantone.push_back(c);
			//		i++;
		}
	}
	else
	{
		ofLogNotice(__FUNCTION__) << "FILE '" << path_FileMaterial << "' NOT FOUND!";
	}
}

//--------------------------------------------------------------
void ofxColorsBrowser::load_Cheprasov_JSON()
{
	// Taken from here: https://github.com/cheprasov/json-colors

	ofLogNotice(__FUNCTION__);

	colors_Cheprasov.clear();
	colors_CheprasovNames.clear();

	ofFile file(path_FileCheprasov);
	if (file.exists())
	{
		file >> jCheprasov;
		ofLogNotice(__FUNCTION__) << jCheprasov;
		ofLogNotice(__FUNCTION__) << endl;

		for (auto &jc : jCheprasov)
		{
			string _name = jc["name"];
			string _hex = jc["hex"];

			ofStringReplace(_hex, "#", "");
			ofColor c;
			hexToColor(c, _hex);

			colors_CheprasovNames.push_back(_name);
			colors_Cheprasov.push_back(c);
		}
	}
	else
	{
		ofLogNotice(__FUNCTION__) << "FILE '" << path_FileCheprasov << "' NOT FOUND!";
	}
}

//--------------------------------------------------------------
void ofxColorsBrowser::load_Crayola_JSON()
{
	// Taken from here: https://gist.github.com/jjdelc/1868136

	ofLogNotice(__FUNCTION__);

	colors_Crayola.clear();
	colors_CrayolaNames.clear();

	ofFile file(path_FileCrayola);
	if (file.exists())
	{
		file >> jCrayola;
		ofLogNotice(__FUNCTION__) << jCrayola;
		ofLogNotice(__FUNCTION__) << endl;

		for (auto &jc : jCrayola)
		{
			string _name = jc["name"];
			string _hex = jc["hex"];

			ofStringReplace(_hex, "#", "");
			ofColor c;
			hexToColor(c, _hex);

			colors_CrayolaNames.push_back(_name);
			colors_Crayola.push_back(c);
		}
	}
	else
	{
		ofLogNotice(__FUNCTION__) << "FILE '" << path_FileCrayola << "' NOT FOUND!";
	}
}

//--------------------------------------------------------------
void ofxColorsBrowser::setup()
{
	//position
	setPositionRectangles(glm::vec2(250, 390)); // call before setup

	//--

#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
	std::string _path;
	_path = "assets/fonts/Kazesawa-Extrabold.ttf";
	font.setup(_path, 1.0, 1024, false, 8, 1.5);
	font.setCharacterSpacing(0);

	//_path = "assets/fonts/mono.ttf";
	//font2.load(_path, 10, true, true);

	_path = "assets/fonts/overpass-mono-bold.otf";
	//_path = "assets/fonts/telegrama_render.otf";
	font2.load(_path, 8, true, true, true);
	// if font not present will draw rectangle box with a default font
#endif

	//-

	// exclude
	MODE_SORTING_name.setSerializable(false);
	name_Library.setSerializable(false);
	bShowCards.setSerializable(false);

	//-

	params.setName("ofxColorsBrowser");
	paramsLayout.setName("Layout");
	params.add(index_Library);
	params.add(name_Library);
	params.add(MODE_SORTING);
	//paramsLayout.add(boxSize);
	//paramsLayout.add(boxPad);
	//paramsLayout.add(amtColorsInCard);
	//paramsLayout.add(amtCardsInRow);
	//paramsLayout.add(bShowCards);
	params.add(paramsLayout);
	params.add(ENABLE_keys);

	//-

	gui.setup("ofxColorsBrowser");
	gui.add(params);
	gui.setPosition(ofGetWidth() * 0.5 - 100, 10);

	//-

	//--------------------------------------------------------------
	listener_ModeSorting = MODE_SORTING.newListener([this](int &i)
	{
		ofLogNotice("MODE_SORTING: ") << i;

		if (MODE_SORTING == 5) MODE_SORTING = 0;
		MODE_SORTING = ofClamp(MODE_SORTING, 0, 4);

		if (MODE_SORTING == 0) { ofSort(colors_STRUCT, comparePosition); MODE_SORTING_name = "Original"; }
		else if (MODE_SORTING == 1) { ofSort(colors_STRUCT, compareName); MODE_SORTING_name = "Name"; }
		else if (MODE_SORTING == 2) { ofSort(colors_STRUCT, compareHue); MODE_SORTING_name = "Hue"; }
		else if (MODE_SORTING == 3) { ofSort(colors_STRUCT, compareBrightness); MODE_SORTING_name = "Brightness"; }
		else if (MODE_SORTING == 4) { ofSort(colors_STRUCT, compareSaturation); MODE_SORTING_name = "Saturation"; }

		clearInterface();
		buildRectangles();
	});

	//-

	//--------------------------------------------------------------
	listener_Library = index_Library.newListener([this](int &i)
	{
		ofLogNotice("index_Library: ") << i;

		index_Library = ofClamp(index_Library, index_Library.getMin(), index_Library.getMax());

		// exclude. skip material
		if (index_Library == OFX_MATERIAL_COLOR) index_Library++;
		//if (index_Library == OFX_MATERIAL_COLOR) index_Library = OFX_PANTONE_COLORS;

		switch (index_Library)
		{
		case OFX_PANTONE_COLORS:	 // 0
			ofLogNotice(__FUNCTION__) << "OFX_PANTONE_COLORS";
			name_Library = "Pantone";
			break;

		case OFX_SANZOWADA_COLORS:	// 1
			ofLogNotice(__FUNCTION__) << "OFX_SANZOWADA_COLORS";
			name_Library = "Sanzo Wada";
			break;

		case OFX_COLOR_NATIVE:		// 2
			ofLogNotice(__FUNCTION__) << "OFX_COLOR_NATIVE";
			name_Library = "OF Native";
			break;

		case OFX_MATERIAL_COLOR:	// 3
			ofLogNotice(__FUNCTION__) << "OFX_MATERIAL_COLOR";
			name_Library = "Material";
			break;

		case OFX_OPEN_COLOR:		// 4
			ofLogNotice(__FUNCTION__) << "OFX_OPEN_COLOR";
			name_Library = "Open Color";
			break;

		case OFX_CHEPRASOV:			// 5
			ofLogNotice(__FUNCTION__) << "OFX_CHEPRASOV";
			name_Library = "Cheprasov";
			break;

		case OFX_CRAYOLA:			// 6
			ofLogNotice(__FUNCTION__) << "OFX_CRAYOLA";
			name_Library = "Crayola";
			break;

			// * add your new libs here!

			//
		}

		//-

		// build
		clearInterface();
		buildColors();
		buildRectangles();

		//workflow
		// refresh
		//MODE_SORTING = 0; // A. reset
		MODE_SORTING = MODE_SORTING; // B. mantain previous
	});

	//----

	index_Library.setMax(OFXCOLORSBROWSER__COUNT - 1);


	//----

	// read json files

	// 0. pantone colors
	load_Pantone_JSON();

	// 1. sanzo colors
	load_SanzoWadaDictionary_JSON();

	// 2. native OF colors
	// uses an addon instead of a json

	//TODO: fix
	// 3. material colors
	load_Material_JSON(); // -> crashes

	// 4. open colors
	// uses an addon instead of a json

	// 5. cheprasov colors
	load_Cheprasov_JSON();

	// 6. crayola colors
	load_Crayola_JSON();

	// * add your new libs here!

	//----


	// 1. default sorting
	MODE_SORTING = SORTING_ORIGINAL;
	// by name, at the start

	// 2. default palette mode
	index_Library = OFX_PANTONE_COLORS;

	//--

	// build current loaded library
	buildColors();

	//--

#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
	buildRectangles();
#endif	

	//-----

	// startup

	if (isVisible())
	{
		setEnableInterfaceClicks(true);
		setVisibleDebug(true);
	}

	//index_Color = 0;
	//index_Card = 0;
	//refresh_Clicks();

	// settings
	ofxSurfingHelpers::loadGroup(params, path_FileSettings);
}


//--------------------------------------------------------------
void ofxColorsBrowser::buildRectangles()
{
#ifdef USE_OFX_COLOR_BROWSER_INTERFACE

	ofLogNotice(__FUNCTION__);

	float x = positionRectangles.x;
	float y = positionRectangles.y;

	perRow = amtColorsInCard * amtCardsInRow;

	isSelecting = false;
	draggingRectPtr = NULL;

	for (int i = 0; i < colors_STRUCT.size(); i++)
	{
		float xBtn = x + (i % perRow) * (boxSize + boxPad);
		float yBtn = y + (i / perRow) * (boxSize + boxPad);

		ofColor c = colors_STRUCT[i].color;

		ofxRectangle r(ofRectangle(xBtn, yBtn, boxSize, boxSize), c);

		r.setName(colors_STRUCT[i].name);
		r.setPosition_inVector(colors_STRUCT[i].position);

		rectangles.push_back(r);
	}

	selectedRectsBoundingBox = ofxRectangle(ofRectangle(), ofColor(127, 80));
	hAlign = OF_ALIGN_HORZ_LEFT;
	vAlign = OF_ALIGN_VERT_TOP;
	anchorRect = NULL;
	showKeyboardCommands = false;

	//-

	// workflow
	// startup
	index_Color = 0;
	index_Card = 0;
	refresh_Clicks();

#endif
}


//--------------------------------------------------------------
void ofxColorsBrowser::update()
{
	if (color_BACK != color_BACK_PRE)
	{
		color_BACK_OFAPP->set(color_BACK);
		color_BACK_PRE = color_BACK;
	}

	//-

#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
	rectangles_update();
#endif
}

//--------------------------------------------------------------
void ofxColorsBrowser::draw()
{
	if (bGui)
	{
		ofPushMatrix();
		ofPushStyle();

		//position
		float _x = 20;
		float _y = 40;

		//-

		// 1. draw all the colors names

		int maxLinesThatFitsScreen = 42; // related to font size..
		bool bColorizeLabel = false;
		bool bColorizeBg = true;

		int iPadded;
		int line;
		int lineBegin;
		int lineEnd;
		int maxCards = maxLinesThatFitsScreen / amtColorsInCard;
		int linesPage = amtColorsInCard * maxCards;
		int pageNum;

		std::string str;
		ofColor c;

		//--

		// calculate layout
		pageNum = (int)index_Color / linesPage;
		lineBegin = pageNum * linesPage;
		lineEnd = lineBegin + linesPage - 1;

		//--

		// 0. draw all color names marking the one selected

		//--

		// avoid crashes
		if (colors_STRUCT.size() == 0) return;

#ifdef USE_OFX_COLOR_BROWSER_INTERFACE

		//--

		// 1. left lateral list

		if (SHOW_debugText)
		{
			float fontSize = 20;
			float x = _x;
			float rectWidth = 200;
			int margin = 6;

			//-

			// 0.0  background rectangle
			ofSetColor(255); // white
			ofFill();
			float _h = linesPage * fontSize;
			int _dim = 10;
			ofDrawRectRounded(x - _dim, _y - fontSize + margin - _dim, rectWidth + 2 * _dim, _h + 2 * _dim, 5);
			//ofDrawRectRounded(x, _y - fontSize + margin, rectWidth, _h, 5);

			//-

			for (int i = lineBegin; i <= lineEnd; i++)
			{
				//i = ofClamp(i, 0, colors_STRUCT.size() - 1);
				line = i;

				if (colors_STRUCT.size() > 0 && line < colors_STRUCT.size()) str = colors_STRUCT[line].name;
				else str = "";

				if (pageNum == 0) iPadded = i;
				else iPadded = i - lineBegin;

				float y = _y + iPadded * fontSize;

				//-

				// 1. selected color

				if (i == index_Color)
				{
					// 1.1 rectangle selector

					if (!bColorizeBg) ofSetColor(0);//black
					else ofSetColor(colors_STRUCT[i].color);

					ofDrawRectRounded(x, y - fontSize + margin, rectWidth, fontSize, 5);
					//ofDrawRectangle(x, y - fontSize + margin, rectWidth, fontSize);

					//// border
					//ofNoFill();
					//ofSetLineWidth(2);
					//ofSetColor(0);
					//ofDrawRectangle(x, y - fontSize + margin, rectWidth, fontSize);
					//ofFill();

					// text
					if (bColorizeLabel) c = colors_STRUCT[i].color;
					else c = ofColor::white;

					// A
					//// shadow
					//ofSetColor(ofColor(ofColor::black, 200));
					//font.draw(
					//	str,
					//	fontSize,
					//	x + margin + 1,
					//	y + 1
					//);
					// body
					ofSetColor(c);
					font.draw(
						str,
						fontSize,
						x + margin,
						y
					);

					// B
					//ofDrawBitmapStringHighlight(str, x, y, c, ofColor::black);
				}

				// 1.2. all colors. not selected

				else
				{
					//// 1.2.1 background rectangle

					////TODO:
					//// this is very low performant bc we draw a rectangle for each name!
					//// should draw a bigger bg rectangle
					//ofSetColor(255); // white
					//ofDrawRectangle(x, y - fontSize + margin, rectWidth, fontSize);

					//-

					// 1.2.2 label
					if (bColorizeLabel) c = colors_STRUCT[i].color;
					else c = ofColor::black;

					//A
					//ofDrawBitmapStringHighlight(str, 10, 20 + iPadded * 20, c, ofColor::white);

					//B
					ofSetColor(c);
					font.draw(
						str,
						fontSize,
						x + margin,
						y
					);
				}

				//-

				// 1.3. line to mark first color on each card

				if (amtColorsInCard != 1)
					if (i % amtColorsInCard == 0 && i < colors_STRUCT.size())
					{
						int lineSize = 2;
						//int lineSize = 3;
						//int px = x + 0;
						int px = x + 2;
						int py = y - 4;
						ofSetLineWidth(2.0);
						ofDrawLine(px, py, px + lineSize, py);
					}
			}
		}
#endif

		//--

		// help info

		// 2. monitor color selected: 
		// name & index

#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
		if (SHOW_debugText)
		{
			std::string str = "";
			//str += "DEBUG";
			//str += "\n";

			str += "Library            ";
			str += ofToString(index_Library) + "/" + ofToString(index_Library.getMax()) + "  ";
			str += "\n";
			str += "Color              " + ofToString(currColor_OriginalPos + 1) + "/" + ofToString(colors_STRUCT.size());
			str += "\n";
			str += "Card               " + ofToString(index_Card + 1);
			str += "\n";
			str += "Page               " + ofToString(pageNum + 1);
			str += "\n";
			str += "Colors/Card        " + ofToString(amtColorsInCard);
			str += "\n";
			str += "Cards/Row          " + ofToString(amtCardsInRow);
			//str += "\n";

			//float w = ofxSurfingHelpers::getWidthBBtextBoxed(font2, ofToUpper(str));

			//position
			int x = positionRectangles.x + 0;
			int y = 15;

			ofxSurfingHelpers::drawTextBoxed(font2, ofToUpper(str), x, y,
				ofColor(255), ofColor(0, 247), false, ofColor(128), 50, 5);
		}
#endif

		//--

		// 3. monitor selected library

		if (SHOW_InterfaceColors)
		{
			if (SHOW_debugText)
			{
				std::string str1;
				str1 = "";
				str1 += "\n";

				//str1 += "MONITOR";
				//str1 += "\n";
				//str1 += "\n";
				//str1 += "LIBRARY: ";
				//str1 += " " + ofToString(index_Library) + "/" + ofToString(index_Library.getMax()) + "  ";

				//-

				str1 += "LIBRARY: ";

				switch (index_Library)
				{
				case OFX_PANTONE_COLORS:
					str1 += "PANTONE";
					break;

				case OFX_SANZOWADA_COLORS:
					str1 += "SANZO WADA";
					break;

				case OFX_COLOR_NATIVE:
					str1 += "OF NATIVE";
					break;

				case OFX_OPEN_COLOR:
					str1 += "OPEN COLOR";
					break;

				case OFX_MATERIAL_COLOR:
					str1 += "MATERIAL COLORS";
					break;

				case OFX_CHEPRASOV:
					str1 += "CHEPRASOV";
					break;

				case OFX_CRAYOLA:
					str1 += "CRAYOLA";
					break;
				}

				//ofDrawBitmapStringHighlight(str1, positionHelper.x, positionHelper.y + 20, ofColor::black, ofColor::white);

				//-

				str1 += "\n";
				str1 += "SORTING: ";

				switch (MODE_SORTING)
				{
				case 0:
					str1 += "ORIGINAL";
					break;

				case 1:
					str1 += "NAME";
					break;

				case 2:
					str1 += "HUE";
					break;

				case 3:
					str1 += "BRIGHTNESS";
					break;

				case 4:
					str1 += "SATURATION";
					break;
				}

				//ofDrawBitmapStringHighlight(str1, positionHelper.x, positionHelper.y + 50, ofColor::black, ofColor::white);

				//-

				str1 += "\n";

				std::string str2 = str1 + helpInfo;

				float w = ofxSurfingHelpers::getWidthBBtextBoxed(font2, ofToUpper(str2)) + 10;

				setPositionHelper(glm::vec2(ofGetWidth() - w, 5));

				ofxSurfingHelpers::drawTextBoxed(font2, ofToUpper(str2), positionHelper.x, positionHelper.y,
					ofColor(255), ofColor(0, 247), false, ofColor(128), 50, 5);
			}

			//--

			// 4. draw all clickable color boxes

#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
			drawRectangles();

			//TODO:
			// extra interface is
			// rectangles with mouse management and draggables..
#endif
		}

		ofPopMatrix();
		ofPopStyle();

		//-----

		// debug gui
		if (bGuiDebug) gui.draw();
	}
}

//--------------------------------------------------------------
void ofxColorsBrowser::keyPressed(ofKeyEventArgs &eventArgs)
{
	const int &key = eventArgs.key;
	ofLogNotice(__FUNCTION__) << " : " << key;

	if (key == 'K')
	{
		setToggleEnableKeys();
	}

	//-

	if (ENABLE_keys)
	{
		//-

#ifdef USE_OFX_COLOR_BROWSER_INTERFACE

		if (key == 'g')
		{
			setToggleVisible();
		}

		else if (key == 'D')
		{
			setToggleVisibleDebug();
		}

		else if (key == 'G')
		{
			bGuiDebug = !bGuiDebug;
		}

		// 0. card selector

		//next card
		else if (/*key == OF_KEY_RIGHT_SHIFT ||*/ key == 'd' || key == ' ')
		{
			index_Card++;
			if (amtColorsInCard * index_Card + amtColorsInCard > colors_STRUCT.size())
				index_Card = 0;

			index_Color = amtColorsInCard * index_Card;
			refresh_Clicks();
		}
		//prev card
		else if (/*key == OF_KEY_LEFT_SHIFT ||*/ key == 'a')
		{
			index_Card--;
			if (index_Card < 0)
				index_Card = (colors_STRUCT.size() - 1) / amtColorsInCard;

			index_Color = amtColorsInCard * index_Card;
			refresh_Clicks();
		}
		else if (key == 's')//prev card
		{
			index_Color += amtCardsInRow * amtColorsInCard;
			if (index_Color > colors_STRUCT.size() - 1)
				index_Color = 0;
			index_Card = index_Color / amtColorsInCard;
			refresh_Clicks();
		}
		else if (key == 'w')//prev card
		{
			index_Color -= amtCardsInRow * amtColorsInCard;
			if (index_Color < 0)
				index_Color = colors_STRUCT.size() - 1 - amtColorsInCard;
			index_Card = index_Color / amtColorsInCard;
			refresh_Clicks();
		}

		//-

		else if (key == 'r')//random to one card
		{
			index_Card = (int)ofRandom((colors_STRUCT.size()) / amtColorsInCard);
			index_Color = amtColorsInCard * index_Card;
			refresh_Clicks();
		}
		//-

		// 1. slelect colors 
		else if (key == OF_KEY_RIGHT)
		{
			index_Color++;
			int sizeCols = colors_STRUCT.size();
			if (index_Color > sizeCols - 1)
				index_Color = 0;
			index_Card = index_Color / amtColorsInCard;
			refresh_Clicks();
		}
		else if (key == OF_KEY_LEFT)
		{
			index_Color--;
			if (index_Color < 0)
				index_Color = colors_STRUCT.size() - 1;
			index_Card = index_Color / amtColorsInCard;
			refresh_Clicks();
		}
		else if (key == OF_KEY_DOWN)
		{
			index_Color = index_Color + perRow;
			int sizeCols = colors_STRUCT.size();
			if (index_Color > sizeCols - 1)
				index_Color = sizeCols - 1;
			index_Card = index_Color / amtColorsInCard;
			refresh_Clicks();
		}
		else if (key == OF_KEY_UP)
		{
			index_Color = index_Color - perRow;
			if (index_Color < 0)
				index_Color = 0;
			index_Card = index_Color / amtColorsInCard;
			refresh_Clicks();
		}
#endif

		//-

		// 2. change to next palette

		if (key == OF_KEY_BACKSPACE)
		{
			if (index_Library < index_Library.getMax()) index_Library++;
			else index_Library = index_Library.getMin();
		}

		//-

		// 3. select sorting

		else if (key == '0')
		{
			if (MODE_SORTING != 0)
			{
				MODE_SORTING = 0;
			}
		}
		else if (key == '1')
		{
			if (MODE_SORTING != 1)
			{
				MODE_SORTING = 1;
			}
		}
		else if (key == '2')
		{
			if (MODE_SORTING != 2)
			{
				MODE_SORTING = 2;
			}
		}
		else if (key == '3')
		{
			if (MODE_SORTING != 3)
			{
				MODE_SORTING = 3;
			}
		}
		else if (key == '4')
		{
			if (MODE_SORTING != 4)
			{
				MODE_SORTING = 4;
			}
		}
		else if (key == OF_KEY_TAB)
		{
			nextSortType();
		}

		//--

		//    // rectangles manager
		//
		//    // some tools to rectangles sorting and align
		//
		////    // show debug
		////else if (key == 'd')
		////{
		////    bShowDebug = !bShowDebug;
		////
		////    for (int i = 0; i < rectangles.size(); i++)
		////    {
		////        rectangles[i].setDebug(bShowDebug);
		////    }
		////}
		////
		////else if (key == 'p')
		////{
		////    RectangleUtils::pack(selectedRects, ofRectangle(0,
		////        0,
		////        ofRandom(500),
		////        ofRandom(500)));
		////}
		//
		//    // debug ofxRectangle handling
		//else if (bShowDebug)
		//{
		//
		//    //    if (key == OF_KEY_UP) {
		//    //        for(size_t i = 0; i < selectedRects.boxSize(); i++) {
		//    //            selectedRects[i]->vAlign = OF_ALIGN_VERT_TOP;
		//    //        }
		//    //    } else if (key == OF_KEY_DOWN) {
		//    //        for(size_t i = 0; i < selectedRects.boxSize(); i++) {
		//    //            selectedRects[i]->vAlign = OF_ALIGN_VERT_BOTTOM;
		//    //        }
		//    //    } else if (key == OF_KEY_LEFT) {
		//    //        for(size_t i = 0; i < selectedRects.boxSize(); i++) {
		//    //            selectedRects[i]->hAlign = OF_ALIGN_HORZ_LEFT;
		//    //        }
		//    //    } else if (key == OF_KEY_RIGHT) {
		//    //        for(size_t i = 0; i < selectedRects.boxSize(); i++) {
		//    //            selectedRects[i]->hAlign = OF_ALIGN_HORZ_RIGHT;
		//    //        }
		//    //    } else if (key == 'c') {
		//    //        for(size_t i = 0; i < selectedRects.boxSize(); i++) {
		//    //            selectedRects[i]->hAlign = OF_ALIGN_HORZ_CENTER;
		//    //        }
		//    //    } else if (key == 'C') {
		//    //        for(size_t i = 0; i < selectedRects.boxSize(); i++) {
		//    //            selectedRects[i]->vAlign = OF_ALIGN_VERT_CENTER;
		//    //        }
		//    //    } else if (key == 'i') {
		//    //        for(size_t i = 0; i < selectedRects.boxSize(); i++) {
		//    //            selectedRects[i]->hAlign = OF_ALIGN_HORZ_IGNORE;
		//    //        }
		//    //    } else if (key == 'I') {
		//    //        for(size_t i = 0; i < selectedRects.boxSize(); i++) {
		//    //            selectedRects[i]->vAlign = OF_ALIGN_VERT_IGNORE;
		//    //        }
		//    //
		//    /*} else */ if (key == 'a')
		//    {
		//        if (hAlign == OF_ALIGN_HORZ_LEFT)
		//        {
		//            hAlign = OF_ALIGN_HORZ_CENTER;
		//        }
		//        else if (hAlign == OF_ALIGN_HORZ_CENTER)
		//        {
		//            hAlign = OF_ALIGN_HORZ_RIGHT;
		//        }
		//        else if (hAlign == OF_ALIGN_HORZ_RIGHT)
		//        {
		//            hAlign = OF_ALIGN_HORZ_IGNORE;
		//        }
		//        else if (hAlign == OF_ALIGN_HORZ_IGNORE)
		//        {
		//            hAlign = OF_ALIGN_HORZ_LEFT;
		//        }
		//    }
		//    else if (key == 'A')
		//    {
		//        if (vAlign == OF_ALIGN_VERT_TOP)
		//        {
		//            vAlign = OF_ALIGN_VERT_CENTER;
		//        }
		//        else if (vAlign == OF_ALIGN_VERT_CENTER)
		//        {
		//            vAlign = OF_ALIGN_VERT_BOTTOM;
		//        }
		//        else if (vAlign == OF_ALIGN_VERT_BOTTOM)
		//        {
		//            vAlign = OF_ALIGN_VERT_IGNORE;
		//        }
		//        else if (vAlign == OF_ALIGN_VERT_IGNORE)
		//        {
		//            vAlign = OF_ALIGN_VERT_TOP;
		//        }
		//    }
		//    else if (key == 'W')
		//    {
		//        RectangleUtils::sortByAbsWidth(selectedRects);
		//    }
		//    else if (key == 'A')
		//    {
		//        RectangleUtils::sortByArea(selectedRects);
		//    }
		//    else if (key == 'H')
		//    {
		//        RectangleUtils::sortByAbsHeight(selectedRects);
		//    }
		//    else if (key == 'c')
		//    {
		//        RectangleUtils::cascade(selectedRects, ofRectangle(0, 0, ofGetWidth(), ofGetHeight()), glm::vec2(30, 30));
		//    }
		//    else if (key == 'v')
		//    {
		//        RectangleUtils::alignVert(selectedRects, vAlign);
		//    }
		//    else if (key == 'h')
		//    {
		//        // horizontal align selection
		//        RectangleUtils::alignHorz(selectedRects, hAlign);
		//    }
		//    else if (key == 'x')
		//    {
		//        // distribute in x
		//        RectangleUtils::distributeHorz(selectedRects, hAlign);
		//    }
		//    else if (key == 'y')
		//    {
		//        RectangleUtils::distributeVert(selectedRects, vAlign);
		//    }
		//    else if (key == 'p')
		//    {
		//        RectangleUtils::pack(selectedRects, ofRectangle(0,
		//            0,
		//            ofGetWidth(),
		//            ofGetHeight()));
		//    }
		//    else if (key == ' ')
		//    {
		//        showKeyboardCommands = !showKeyboardCommands;
		//    }
		//}
	}
}

//--------------------------------------------------------------
void ofxColorsBrowser::clearInterface()
{
#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
	ofLogNotice(__FUNCTION__);

	rectangles.clear();
#endif	
}

//--------------------------------------------------------------
void ofxColorsBrowser::keyReleased(ofKeyEventArgs &eventArgs)
{
}

//--------------------------------------------------------------
void ofxColorsBrowser::addKeysListeners()
{
	ofAddListener(ofEvents().keyPressed, this, &ofxColorsBrowser::keyPressed);
}

//--------------------------------------------------------------
void ofxColorsBrowser::removeKeysListeners()
{
	ofRemoveListener(ofEvents().keyPressed, this, &ofxColorsBrowser::keyPressed);
}

//--------------------------------------------------------------
void ofxColorsBrowser::mouseDragged(ofMouseEventArgs &eventArgs)
{
#ifdef USE_OFX_COLOR_BROWSER_INTERFACE

	if (bShowDebug)
	{
		const int &x = eventArgs.x;
		const int &y = eventArgs.y;
		const int &button = eventArgs.button;
		//ofLogNotice(__FUNCTION__) << "mouseDragged " <<  x << ", " << y << ", " << button;

		if (draggingRectPtr != NULL)
		{
			draggingRectPtr->setPosition(ofPoint(x, y) - draggingRectPtr->dragOffset);

			if (draggingRectPtr == &selectedRectsBoundingBox)
			{
				for (size_t i = 0; i < rectangles.size(); i++)
				{
					if (rectangles[i].isSelected)
					{
						rectangles[i].setPosition(ofPoint(x, y) - rectangles[i].dragOffset);
					}
				}
			}
		}
	}

#endif
}


//--------------------------------------------------------------
void ofxColorsBrowser::mousePressed(ofMouseEventArgs &eventArgs)
{
#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
	if (ENABLE_clicks)
	{
		const int &x = eventArgs.x;
		const int &y = eventArgs.y;
		const int &button = eventArgs.button;

		//ofLogNotice(__FUNCTION__) << "mousePressed " <<  x << ", " << y << ", " << button;

		//-

		// 1. rectangles system

		dragStart = glm::vec2(x, y);  // set a new drag start point

		// SHORTCUT MODE

		if (!ofGetKeyPressed('A'))
		{
			bool foundAClickTarget = false;

			// first check to see if we are in the bounding box
			if (!selectedRects.empty() &&
				selectedRectsBoundingBox.inside(dragStart))
			{
				if (bShowDebug)
				{
					draggingRectPtr = &selectedRectsBoundingBox;
					//selectedRectsBoundingBox.dragOffset = dragStart - selectedRectsBoundingBox.getPosition().xy;
					selectedRectsBoundingBox.dragOffset.x = dragStart.x - selectedRectsBoundingBox.getPosition().x;
					selectedRectsBoundingBox.dragOffset.y = dragStart.y - selectedRectsBoundingBox.getPosition().y;

					for (std::size_t i = 0; i < rectangles.size(); i++)
					{
						if (rectangles[i].isSelected)
						{
							//rectangles[i].dragOffset = dragStart - rectangles[i].getPosition().xy;
							rectangles[i].dragOffset.x = dragStart.x - rectangles[i].getPosition().x;
							rectangles[i].dragOffset.y = dragStart.y - rectangles[i].getPosition().y;
						}
					}
					foundAClickTarget = true;
				}
			}

			// RECTANGLE COLOR CLICKED
			else
			{

				selectedRects.clear();
				// otherwise, go through all of the rects and see if we can drag one
				for (size_t i = 0; i < rectangles.size(); i++)
				{
					rectangles[i].isSelected = false; // assume none

					if (!foundAClickTarget && rectangles[i].isOver)
					{
						draggingRectPtr = &rectangles[i];
						rectangles[i].isSelected = true;
						rectangles[i].dragOffset = dragStart - rectangles[i].getPosition();
						foundAClickTarget = true;

						//-

						// TEST
						ofLogNotice(__FUNCTION__) << "mousePressed box clicked  [" << i << "]";
						ofLogNotice(__FUNCTION__) << "mousePressed box name     [" << rectangles[i].name << "]";
						ofLogNotice(__FUNCTION__) << "mousePressed box position ["
							<< rectangles[i].position_inVector << "]";

						//-

						// 1. get rectangle clicked color

						ofColor cRect = rectangles[i].color;

						//-

						// 2. apply color pointer back

						color_BACK = ofColor(cRect);
						// ofColor c = colors_STRUCT[index_Color].color;
						// color_BACK = ofColor( c );

						//-

						// 3. update browsing grid

						index_Color = i;
						ofLogNotice(__FUNCTION__) << "index_Color [" << index_Color << "]";

						currName = colors_STRUCT[index_Color].name;
						ofLogNotice(__FUNCTION__) << "currName [" << currName << "]";

						currColor_OriginalPos = colors_STRUCT[index_Color].position;
						ofLogNotice(__FUNCTION__) << "originalPos[" << currColor_OriginalPos << "]";

						//-

						// 4. update selected card
						index_Card = index_Color / amtColorsInCard;
						//refresh_Clicks();
					}
				}
			}

			isSelecting = !foundAClickTarget; // means our click did not land on an existing rect
		}
		else
		{
			if (anchorRect != nullptr)
			{
				delete anchorRect;
				anchorRect = nullptr;
			}

			if (bShowDebug)
			{
				anchorRect = new ofRectangle(dragStart, 0, 0);
			}
		}
	}

#endif
}


//--------------------------------------------------------------
void ofxColorsBrowser::refresh_Clicks()//over rectangles
{
#ifdef USE_OFX_COLOR_BROWSER_INTERFACE

	ofLogNotice(__FUNCTION__) << "make clicked box by keys following index_Color: [" << index_Color << "]";

	//-

	// handle rectangles

	selectedRects.clear();//clear drag and deselect

	//deselect all
	for (size_t i = 0; i < rectangles.size(); i++)
	{
		rectangles[i].isSelected = false; // assume none
	}

	if (index_Color < rectangles.size())
	{
		// select current color
		rectangles[index_Color].isSelected = true;
	}

	//-

	if (index_Color < colors_STRUCT.size())
	{
		ofColor c = colors_STRUCT[index_Color].color;
		color_BACK = ofColor(c);

		ofLogNotice(__FUNCTION__) << "index_Color is [" << index_Color << "]";

		currName = colors_STRUCT[index_Color].name;
		ofLogNotice(__FUNCTION__) << "currName is [" << currName << "]";

		currColor_OriginalPos = colors_STRUCT[index_Color].position;
		ofLogNotice(__FUNCTION__) << "originalPos was [" << currColor_OriginalPos << "]";
	}

#endif
}

//--------------------------------------------------------------
void ofxColorsBrowser::mouseReleased(ofMouseEventArgs &eventArgs)
{
#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
	if (ENABLE_clicks)
	{

		const int &x = eventArgs.x;
		const int &y = eventArgs.y;
		const int &button = eventArgs.button;
		//ofLogNotice(__FUNCTION__) << "mouseReleased " <<  x << ", " << y << ", " << button;

		draggingRectPtr = nullptr;
		isSelecting = false;
	}

#endif
}

//--------------------------------------------------------------
void ofxColorsBrowser::addMouseListeners()
{
#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
	ofAddListener(ofEvents().mouseDragged, this, &ofxColorsBrowser::mouseDragged);
	ofAddListener(ofEvents().mousePressed, this, &ofxColorsBrowser::mousePressed);
	ofAddListener(ofEvents().mouseReleased, this, &ofxColorsBrowser::mouseReleased);
#endif
}

//--------------------------------------------------------------
void ofxColorsBrowser::removeMouseListeners()
{
#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
	ofRemoveListener(ofEvents().mouseDragged, this, &ofxColorsBrowser::mouseDragged);
	ofRemoveListener(ofEvents().mousePressed, this, &ofxColorsBrowser::mousePressed);
	ofRemoveListener(ofEvents().mouseReleased, this, &ofxColorsBrowser::mouseReleased);
#endif
}

//--------------------------------------------------------------
void ofxColorsBrowser::exit()
{
#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
	removeKeysListeners();
	removeMouseListeners();

	//setEnableInterfaceClicks(false);
#endif
	ofxSurfingHelpers::saveGroup(params, path_FileSettings);
}

//--------------------------------------------------------------
ofxColorsBrowser::~ofxColorsBrowser()
{
	exit();
}

//--------------------------------------------------------------
void ofxColorsBrowser::setup_colorBACK(ofFloatColor &c)
{
	//color_BACK = c;
	color_BACK_OFAPP = &c;
}

//--------------------------------------------------------------
void ofxColorsBrowser::setPositionRectangles(glm::vec2 p)
{
	positionRectangles = p;
}

//--------------------------------------------------------------
void ofxColorsBrowser::setBoxSize(float _size)
{
	boxSize = _size;
}

//--------------------------------------------------------------
void ofxColorsBrowser::setRowsSize(int rows)
{
	perRow = rows;
}

//--------------------------------------------------------------
void ofxColorsBrowser::switch_palette_Type()
{
	if (index_Library < index_Library.getMax()) index_Library++;
	else index_Library = index_Library.getMin();

	ofLogNotice(__FUNCTION__) << index_Library;
}

//--------------------------------------------------------------
void ofxColorsBrowser::nextSortType()
{
	MODE_SORTING++;
}

//--------------------------------------------------------------
void ofxColorsBrowser::set_palette_Type(int p)
{
	index_Library = p;
}

//--------------------------------------------------------------
void ofxColorsBrowser::set_sorted_Type(int p)
{
	MODE_SORTING = p;

	switch (MODE_SORTING)
	{
	case 0:
		ofSort(colors_STRUCT, comparePosition);
		break;
	case 1:
		ofSort(colors_STRUCT, compareName);
		break;
	case 2:
		ofSort(colors_STRUCT, compareHue);
		break;
	case 3:
		ofSort(colors_STRUCT, compareBrightness);
		break;
	case 4:
		ofSort(colors_STRUCT, compareSaturation);
		break;
	}

	if (p >= 0 && p <= 4)
	{
		clearInterface();
		buildRectangles();
	}
}

//--------------------------------------------------------------
void ofxColorsBrowser::rectangles_update()
{
#ifdef USE_OFX_COLOR_BROWSER_INTERFACE

	if (ENABLE_clicks)
	{
		ofPoint mouse(ofGetMouseX(), ofGetMouseY());


		bool foundIsOver = false;
		bool hasFirstSelection = false;

		if (draggingRectPtr == NULL)
		{
			selectedRects.clear();
		}

		for (size_t i = 0; i < rectangles.size(); ++i)
		{
			// if we are selecting, re-evaluate this each time
			if (isSelecting)
			{
				rectangles[i].isSelected = rectangles[i].intersects(selectionRect);
			}

			// grow the slection box
			if (rectangles[i].isSelected)
			{
				if (draggingRectPtr == NULL)
				{
					if (!hasFirstSelection)
					{
						selectedRectsBoundingBox = rectangles[i];
						hasFirstSelection = true;
					}
					else
					{
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
				rectangles[i].inside(mouse))
			{
				rectangles[i].isOver = true;
				foundIsOver = true;
			}
			else
			{
				rectangles[i].isOver = false;
			}
		}

		if (isSelecting)
		{
			selectionRect.set(glm::vec3(dragStart.x, dragStart.y, 0), mouse);
		}
	}

#endif
}

//--------------------------------------------------------------
void ofxColorsBrowser::drawRectangles()
{
#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
	ofPushStyle();
	//-

	// 0. debug rectangles manager
	//ofPoint mouse(ofGetMouseX(), ofGetMouseY());
	//if (bShowDebug)
	//{
	//	ofFill();
	//	ofSetColor(255, showKeyboardCommands ? 255 : 127);
	//	ofDrawBitmapString(showKeyboardCommands ? keyboardCommands : "Press (Spacebar) for help.", 12, 16);
	//}

	positionCards = glm::vec2(positionRectangles.x + 15, 200);

	//--

	// card of colors

	// 1. draw card rectangles

	if (bShowCards)
	{
		int padding = 15;
		int labelSize = 25;

		int letterPad = 15;
		float fontSize = 16;
		float fontPad = 5;

		float x;
		float y;

		ofColor colorBgCards = ofColor(250);

		if (colors_STRUCT.size() > 0)
		{
			ofPushStyle();

			//--

			// 1. white background

			ofSetColor(colorBgCards);

			float yBg = positionCards.y - padding;
			float hBg = (cardColor_size + cardColor_pad) + 2 * padding + labelSize;
			float ymaxBg = yBg + hBg;

			ofDrawRectRounded(
				glm::vec2(
					positionCards.x - padding,
					yBg),
					(cardColor_size + cardColor_pad) * (amtColorsInCard)+padding,
				hBg
				, 5
			);

			//ofDrawRectRounded(
			//    glm::vec2(
			//        positionCards.x - padding,
			//        positionCards.y - padding),
			//    (cardColor_size + cardColor_pad) * (amtColorsInCard) + 2 * padding,
			//    (cardColor_size * 1.1 + cardColor_pad) + 2 * padding + 25,
			//    5,
			//    5,
			//    5,
			//    5
			//);

			//-

			// 2. each color in current card

			int colorBegin = amtColorsInCard * index_Card;
			int colorEnd = colorBegin + amtColorsInCard;

			for (int i = 0; i < amtColorsInCard; i++)
			{
				int iPad = i + colorBegin;
				if (iPad < colors_STRUCT.size())
				{
					ofSetColor(colors_STRUCT[iPad].color);
					ofFill();

					// 2.1 color box

					//ofDrawRectangle(
					//    positionCards.x + i * (cardColor_size + cardColor_pad),
					//    positionCards.y,
					//    cardColor_size,
					//    cardColor_size);

					ofDrawRectRounded(
						glm::vec2(
							positionCards.x + i * (cardColor_size + cardColor_pad),
							positionCards.y),
						cardColor_size,
						cardColor_size,
						2.5,
						2.5,
						0.0,
						0.0
					);

					//ofDrawRectangle(
					//    positionCards.x + i * (cardColor_size + cardColor_pad),
					//    positionCards.y,
					//    cardColor_size,
					//    cardColor_size*1.1);

					//-

					// 2.2. background text box

					// 2.2.1 text background
					ofSetColor(colorBgCards);//white
					float _yy = positionCards.y + cardColor_size;
					float _hh = 50;
					_yy = MIN(_yy, ymaxBg - _hh - 10); // limit inside

					ofDrawRectangle(
						glm::vec2(
							positionCards.x + i * (cardColor_size + cardColor_pad),
							_yy),
						cardColor_size,
						_hh
					);

					//-

					// 2.2.2 text font

					// A.
					//x = positionCards.x + i * (cardColor_size + cardColor_pad) + 4;
					//y = positionCards.y + cardColor_size - 6;

					// B.
					x = positionCards.x + i * (cardColor_size + cardColor_pad) + 3;
					y = positionCards.y + cardColor_size + letterPad;

					// A.
					//ofDrawBitmapStringHighlight(
					//    colors_STRUCT[iPad].name,
					//    x,
					//    y);

					// B.
					//ofColor c = colors_STRUCT[iPad].color;
					ofColor c = 0;//black
					ofSetColor(c);

					std::string str;
					if (index_Library == OFX_PANTONE_COLORS) str += "PANTONE\n";

					string _n = colors_STRUCT[iPad].name;
					ofStringReplace(_n, " ", "\n"); // break lines when space
					ofStringReplace(_n, "-", "\n"); // break lines when space
					str += _n;

					font.drawMultiLine(
						ofToUpper(str),
						fontSize,
						x + fontPad,
						y
					);

				}
			}

			ofPopStyle();
		}
	}

	//--

	// 1.2 draw all of our rectangles system

	//else if (!bShowCards)
	{
		for (size_t i = 0; i < rectangles.size(); ++i)
		{
			ofRectangle *rect = (ofRectangle *)&rectangles[i];
			unsigned int selectionIndex = ofFind(selectedRects, rect);
			rectangles[i].draw(i, selectionIndex == selectedRects.size() ? -1 : selectionIndex);
		}
	}

	//--

	// rectangles management ?

	// 2. draw border on color
	// draw our bounding box rectangle
	if (!isSelecting && !selectedRects.empty())
	{
		ofNoFill();
		ofSetColor(0, 255);//full black
		ofDrawRectangle(selectedRectsBoundingBox);
	}

	// 3. draw border on selected color box
	if (isSelecting && bShowDebug)
	{
		ofNoFill();
		ofSetColor(ofColor(ofColor::black, 200));
		ofDrawRectangle(selectionRect);
	}

	//--

	// 4. rectangles management debug
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

		std::string hAlignString = "";
		switch (hAlign)
		{
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

		std::string vAlignString = "";
		switch (vAlign)
		{
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
	ofSetColor(255, 255, 0);

	for (int i = 0; i < packedRects.size(); i++)
	{
		ofDrawRectangle(packedRects[i]);
	}

	//-
	ofPopStyle();
#endif
}

//--------------------------------------------------------------
int ofxColorsBrowser::getSize() {
	ofLogNotice(__FUNCTION__) << colors_STRUCT.size();
	return colors_STRUCT.size();
}

//--------------------------------------------------------------
vector<ofColor> ofxColorsBrowser::getPalette()
{
	ofLogNotice(__FUNCTION__);

	int numColors = colors_STRUCT.size();
	ofLogNotice(__FUNCTION__) << "numColors:" << numColors;

	vector<ofColor> p;
	p.resize(numColors);

	for (int i = 0; i < colors_STRUCT.size(); i++)
	{
		p[i] = colors_STRUCT[i].color;
		ofLogVerbose(__FUNCTION__) << "color [" + ofToString(i) + "]  " + ofToString(p[i]);
	}

	return p;
}

//--------------------------------------------------------------
vector<std::string> ofxColorsBrowser::getNames()
{
	ofLogNotice(__FUNCTION__);

	int numColors = colors_STRUCT.size();
	ofLogNotice(__FUNCTION__) << "numColors:" << numColors;

	vector<std::string> n;
	n.resize(numColors);

	for (int i = 0; i < colors_STRUCT.size(); i++)
	{
		n[i] = colors_STRUCT[i].name;
		ofLogVerbose(__FUNCTION__) << "color [" + ofToString(i) + "]  " + ofToString(n[i]);
	}

	return n;
}

//--------------------------------------------------------------
void ofxColorsBrowser::setVisible(bool b)
{
	ofLogNotice(__FUNCTION__) << "bGui: " << bGui;

	bGui = b;

	SHOW_InterfaceColors = b;

	setEnableInterfaceClicks(b);
}

//--------------------------------------------------------------
void ofxColorsBrowser::setVisibleDebug(bool b)
{
	SHOW_debugText = b;
}
//--------------------------------------------------------------
void ofxColorsBrowser::setToggleVisibleDebug()
{
	SHOW_debugText = !SHOW_debugText;
}




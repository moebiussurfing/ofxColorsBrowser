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
	
	// library files
	path_FilePantone = path_Global + "pantone-colors.json";
	path_FileSanzoWada = path_Global + "SANZO_WADA_Library.json";
	path_FileCheprasov = path_Global + "cheprasov-colors.json";
	path_FileMaterial = path_Global + "material-colors.json";

	path_FileSettings = path_Global + "AppSettings.xml";

	ofxSurfingHelpers::CheckFolder(path_Global);

	//--

	helpInfo = "";
	helpInfo += "\n";
	helpInfo += "KEYS";
	helpInfo += "\n\n";
	//helpInfo += "\n";
	helpInfo += "Mouse Click           Browse Colors";
	helpInfo += "\n";
	helpInfo += "Up|Down|Left|Right    ";
	helpInfo += "\n";
	helpInfo += "BackSpace             Library";
	helpInfo += "\n";
	helpInfo += "Tab                   Sorting Type";
	helpInfo += "\n";
	helpInfo += "adws                  Browse Cards";
	helpInfo += "\n";
	helpInfo += "r                     Random Card";
	helpInfo += "\n";
	helpInfo += "01234                 Sort Type";
	helpInfo += "\n";
	helpInfo += "K                     Keys";
	helpInfo += "\n";
	helpInfo += "D                     Debug";
	helpInfo += "\n";
	helpInfo += "g                     Gui";
	helpInfo += "\n";
	//helpInfo += "G                     Gui Panel";
	//helpInfo += "\n";
}

//--------------------------------------------------------------
void ofxColorsBrowser::buildColors()
{
	ofLogNotice(__FUNCTION__);

	colors_STRUCT.clear();
	colorNameMap.clear();
	//TODO: seems is not erasing last name colors..?

	//-

	cardNum = 0;
	currColor = 0;

	//--

	// 0. OFX_PANTONE_COLORS

	if (index_Library == OFX_PANTONE_COLORS)
	{
		ofLogNotice(__FUNCTION__) << "OFX_PANTONE_COLORS";

		// ideal card size and layout
		cardSize = 7;
		bShowCards = true;
		cardsPerRow = 10;

		boxSize = 15;
		boxPad = 0.5;

		cardColor_size = 100;
		cardColor_pad = 20;

		//-

		std::string name;
		ofColor c;

		for (int i = 0; i < colors_PantoneNames.size(); i++)
		{
			name = colors_PantoneNames[i];
			c = colors_Pantone[i];
			{
				// 1. names map
				colorNameMap[name] = c;

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
		cardSize = 1;
		bShowCards = true;

		cardsPerRow = 25;
		boxSize = 45;
		boxPad = 0.5;

		cardColor_size = 100;
		cardColor_pad = 20;

		//-

		std::string name;
		ofColor c;

		for (int i = 0; i < colorsNames_SanzoWada.size(); i++)
		{
			name = colorsNames_SanzoWada[i];
			c = colors_SanzoWada[i];
			{
				// 1. names map
				colorNameMap[name] = c;

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
		// dessired distribution for this palette
		cardSize = 1;
		cardsPerRow = 14;
		bShowCards = true;

		boxSize = 40;
		boxPad = 2;

		cardColor_size = 100;
		cardColor_pad = 10;

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

		int i = 0;
		for (auto const &x : colorNameMap)
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

		// dessired distribution for this palette
		cardSize = 13;
		cardsPerRow = 1;
		boxSize = 30;
		boxPad = 1;

		cardColor_size = 65;
		cardColor_pad = 5;

		bool flipOrder = true;
		int iFlip;
		int pos = 0;//-1? to set correlative positions...

		for (int i = 0; i < NUM_COLORS_ROW; i++)
		{
			// flip order: iFlip
			if (flipOrder) iFlip = (NUM_COLORS_ROW - 1) - i;
			else iFlip = i;

			// 1.
			colorNameMap["GREY " + ofToString(i)] = oc_gray_[iFlip];
			colorNameMap["RED " + ofToString(i)] = oc_red_[iFlip];
			colorNameMap["PINK " + ofToString(i)] = oc_pink_[iFlip];
			colorNameMap["GRAPE " + ofToString(i)] = oc_grape_[iFlip];
			colorNameMap["VIOLET " + ofToString(i)] = oc_violet_[iFlip];
			colorNameMap["INDIGO " + ofToString(i)] = oc_indigo_[iFlip];
			colorNameMap["BLUE " + ofToString(i)] = oc_blue_[iFlip];
			colorNameMap["CYAN " + ofToString(i)] = oc_cyan_[iFlip];
			colorNameMap["TEAL " + ofToString(i)] = oc_teal_[iFlip];
			colorNameMap["GREEN " + ofToString(i)] = oc_green_[iFlip];
			colorNameMap["LIME " + ofToString(i)] = oc_lime_[iFlip];
			colorNameMap["YELLOW " + ofToString(i)] = oc_yellow_[iFlip];
			colorNameMap["ORANGE " + ofToString(i)] = oc_orange_[iFlip];

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
	}

	//----

	// 5. OFX_CHEPRASOV

	else if (index_Library == OFX_CHEPRASOV)
	{
		ofLogNotice(__FUNCTION__) << "OFX_CHEPRASOV";

		// ideal card size and layout
		cardSize = 7;
		bShowCards = true;
		cardsPerRow = 10;

		boxSize = 15;
		boxPad = 0.5;

		cardColor_size = 100;
		cardColor_pad = 20;

		//-

		std::string name;
		ofColor c;

		for (int i = 0; i < colorsNames_Cheprasov.size(); i++)
		{
			name = colorsNames_Cheprasov[i];
			c = colors_Cheprasov[i];
			{
				// 1. names map
				colorNameMap[name] = c;

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
}

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
	colorsNames_SanzoWada.clear();

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

			colorsNames_SanzoWada.push_back(_name);

			ofStringReplace(_hex, "#", "");
			ofColor c;
			hexToColor(c, _hex);
			colors_SanzoWada.push_back(c);
		}
	}
	else
	{
		ofLogNotice(__FUNCTION__) << "FILE '" << path_FilePantone << "' NOT FOUND!";
	}
}

//--------------------------------------------------------------
void ofxColorsBrowser::load_Cheprasov_JSON()
{
	// Taken from here: https://github.com/cheprasov/json-colors

	ofLogNotice(__FUNCTION__);

	colors_Cheprasov.clear();
	colorsNames_Cheprasov.clear();

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

			colorsNames_Cheprasov.push_back(_name);

			ofStringReplace(_hex, "#", "");
			ofColor c;
			hexToColor(c, _hex);

			colors_Cheprasov.push_back(c);
		}
	}
	else
	{
		ofLogNotice(__FUNCTION__) << "FILE '" << path_FileCheprasov << "' NOT FOUND!";
	}
}

//--------------------------------------------------------------
void ofxColorsBrowser::load_Material_JSON()
{
	//TODO:

	//ofLogNotice(__FUNCTION__);

	//colors_MaterialNames.clear();
	//colors_Material.clear();

	//ofFile file(path_FileMaterial);
	//if (file.exists())
	//{
	//	file >> js;
	//	ofLogNotice(__FUNCTION__) << js;

	//	int i = 0;
	//	for (auto &jp : js)
	//	{
	//		//TODO: parse palette colors json...

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
	//	}
	//}
	//else
	//{
	//	ofLogNotice(__FUNCTION__) << "FILE '" << path_FileMaterial << "' NOT FOUND!";
	//}
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

	params.setName("ofxColorsBrowser");
	paramsLayout.setName("Layout");
	params.add(index_Library);
	params.add(name_Library);
	params.add(MODE_SORTING);
	//paramsLayout.add(boxSize);
	//paramsLayout.add(boxPad);
	//paramsLayout.add(cardSize);
	//paramsLayout.add(cardsPerRow);
	//paramsLayout.add(bShowCards);
	params.add(paramsLayout);
	params.add(ENABLE_keys);


	bShowCards.setSerializable(false);

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
		case OFX_PANTONE_COLORS:
			ofLogNotice(__FUNCTION__) << "OFX_PANTONE_COLORS";
			name_Library = "Pantone";
			break;

		case OFX_SANZOWADA_COLORS:
			ofLogNotice(__FUNCTION__) << "OFX_SANZOWADA_COLORS";
			name_Library = "Sanzo Wada";
			break;

		case OFX_COLOR_NATIVE:
			ofLogNotice(__FUNCTION__) << "OFX_COLOR_NATIVE";
			name_Library = "OF Native";
			break;

		case OFX_MATERIAL_COLOR:
			ofLogNotice(__FUNCTION__) << "OFX_MATERIAL_COLOR";
			name_Library = "Material";
			break;

		case OFX_OPEN_COLOR:
			ofLogNotice(__FUNCTION__) << "OFX_OPEN_COLOR";
			name_Library = "Open Color";
			break;

		case OFX_CHEPRASOV:
			ofLogNotice(__FUNCTION__) << "OFX_CHEPRASOV";
			name_Library = "Cheprasov";
			break;
		}

		//-

		clearInterface();
		buildColors();
		buildRectangles();

		//workflow
		// refresh
		MODE_SORTING = 0; // A. reset
		//MODE_SORTING = MODE_SORTING; // B. mantain previous
	});

	//----

	// read json files
	index_Library.setMax(5);

	//-

	// 1. pantone colors
	load_Pantone_JSON();

	// 2. sanzo colors
	load_SanzoWadaDictionary_JSON();

	// 5. cheprasov colors
	load_Cheprasov_JSON();

	//TODO:
	// 4. material colors
	load_Material_JSON(); // -> crashes

	//--

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

	//currColor = 0;
	//cardNum = 0;
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

	perRow = cardSize * cardsPerRow;

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
	currColor = 0;
	cardNum = 0;
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
	if (SHOW_Gui)
	{
		ofPushMatrix();
		ofPushStyle();

		//position
		float _x = 20;
		float _y = 40;

		//TODO: add more pages...

		//-

		// 1. draw all the colors names

		int maxLinesThatFitsScreen = 42;
		bool bColorizeLabel = false;
		bool bColorizeBg = true;

		int iPadded;
		int line;
		int lineBegin;
		int lineEnd;
		int maxCards = maxLinesThatFitsScreen / cardSize;
		int linesPage = cardSize * maxCards;
		int pageNum;

		pageNum = (int)currColor / linesPage;
		lineBegin = pageNum * linesPage;
		lineEnd = lineBegin + linesPage - 1;//-1

		std::string str;
		ofColor c;

		//--

		// draw all color names marking the one selected

		//TODO:
		if (colors_STRUCT.size() == 0) return;

#ifdef USE_OFX_COLOR_BROWSER_INTERFACE

		// 1. left lateral list

		if (SHOW_debugText)
		{
			for (int i = lineBegin; i <= lineEnd; i++)
			{
				//i = ofClamp(i, 0, colors_STRUCT.size() - 1);
				line = i;

				if (colors_STRUCT.size() > 0 && line < colors_STRUCT.size()) str = colors_STRUCT[line].name;
				else str = "";

				if (pageNum == 0)
				{
					iPadded = i;
				}
				else
				{
					iPadded = i - lineBegin;
				}

				// all marked names

				float fontSize = 20;
				float fontMargin = 10;
				float x = _x;
				float y = _y + iPadded * 20;
				float rectWidth = 200;
				int margin = 6;

				//-

				// 1. selected color

				if (i == currColor)
				{
					// rectangle
					if (!bColorizeBg) ofSetColor(0);//black
					else ofSetColor(colors_STRUCT[i].color);
					ofDrawRectangle(x, y - fontSize + margin, rectWidth, fontSize);
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

				// 2. all colors. not selected
				
				else
				{
					// back light
					ofSetColor(255);//white
					ofDrawRectangle(x, y - fontSize + margin, rectWidth, fontSize);

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

				// 3. line to mark first color on each card

				if (cardSize != 1)
					if (i % cardSize == 0 && i < colors_STRUCT.size())
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

		// 2. MONITOR COLOR SELECTED: name & position in vector

#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
		if (SHOW_debugText)
		{
			std::string str = "";
			//str += "DEBUG";
			//str += "\n";

			str += "Library       ";
			str += ofToString(index_Library) + "/" + ofToString(index_Library.getMax()) + "  ";
			str += "\n";
			str += "Color         " + ofToString(currColor_OriginalPos + 1) + "/" + ofToString(colors_STRUCT.size());
			str += "\n";
			str += "Card          " + ofToString(cardNum + 1);
			str += "\n";
			str += "Page          " + ofToString(pageNum + 1);
			str += "\n";
			str += "Card Size     " + ofToString(cardSize);
			str += "\n";
			str += "Cards/Row     " + ofToString(cardsPerRow);
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

		// 3. MONITOR APP MODES

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
					str1 += "SANZO WADA DICTIONARY";
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

			// 4. DRAW COLOR BOXES

#ifdef USE_OFX_COLOR_BROWSER_INTERFACE
			drawRectangles();

			//TODO:
			// extra interface is
			// rectangles with mouse management and draggables..
#endif
		//--
		}

		ofPopMatrix();
		ofPopStyle();

		//-

		if (bGui) gui.draw();
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
			bGui = !bGui;
		}

		// 0. card selector

		else if (key == OF_KEY_RIGHT_SHIFT || key == 'd')//prev card
		{
			cardNum++;
			if (cardSize * cardNum + cardSize > colors_STRUCT.size())
				cardNum = 0;

			currColor = cardSize * cardNum;
			refresh_Clicks();
		}
		else if (key == OF_KEY_LEFT_SHIFT || key == 'a')//next card
		{
			cardNum--;
			if (cardNum < 0)
				cardNum = (colors_STRUCT.size() - 1) / cardSize;

			currColor = cardSize * cardNum;
			refresh_Clicks();
		}
		else if (key == 's')//prev card
		{
			currColor += cardsPerRow * cardSize;
			if (currColor > colors_STRUCT.size() - 1)
				currColor = 0;
			cardNum = currColor / cardSize;
			refresh_Clicks();
		}
		else if (key == 'w')//prev card
		{
			currColor -= cardsPerRow * cardSize;
			if (currColor < 0)
				currColor = colors_STRUCT.size() - 1 - cardSize;
			cardNum = currColor / cardSize;
			refresh_Clicks();
		}

		//-

		else if (key == 'r')//random to one card
		{
			cardNum = (int)ofRandom((colors_STRUCT.size()) / cardSize);
			currColor = cardSize * cardNum;
			refresh_Clicks();
		}
		//-

		// 1. slelect colors 
		else if (key == OF_KEY_RIGHT)
		{
			currColor++;
			int sizeCols = colors_STRUCT.size();
			if (currColor > sizeCols - 1)
				currColor = 0;
			cardNum = currColor / cardSize;
			refresh_Clicks();
		}
		else if (key == OF_KEY_LEFT)
		{
			currColor--;
			if (currColor < 0)
				currColor = colors_STRUCT.size() - 1;
			cardNum = currColor / cardSize;
			refresh_Clicks();
		}
		else if (key == OF_KEY_DOWN)
		{
			currColor = currColor + perRow;
			int sizeCols = colors_STRUCT.size();
			if (currColor > sizeCols - 1)
				currColor = sizeCols - 1;
			cardNum = currColor / cardSize;
			refresh_Clicks();
		}
		else if (key == OF_KEY_UP)
		{
			currColor = currColor - perRow;
			if (currColor < 0)
				currColor = 0;
			cardNum = currColor / cardSize;
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
						// ofColor c = colors_STRUCT[currColor].color;
						// color_BACK = ofColor( c );

						//-

						// 3. update browsing grid

						currColor = i;
						ofLogNotice(__FUNCTION__) << "currColor [" << currColor << "]";

						currName = colors_STRUCT[currColor].name;
						ofLogNotice(__FUNCTION__) << "currName [" << currName << "]";

						currColor_OriginalPos = colors_STRUCT[currColor].position;
						ofLogNotice(__FUNCTION__) << "originalPos[" << currColor_OriginalPos << "]";

						//-

						// 4. update selected card
						cardNum = currColor / cardSize;
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

	ofLogNotice(__FUNCTION__) << "make clicked box by keys following currColor: [" << currColor << "]";

	//-

	// handle rectangles

	selectedRects.clear();//clear drag and deselect

	//deselect all
	for (size_t i = 0; i < rectangles.size(); i++)
	{
		rectangles[i].isSelected = false; // assume none
	}

	if (currColor < rectangles.size())
	{
		// select current color
		rectangles[currColor].isSelected = true;
	}

	//-

	if (currColor < colors_STRUCT.size())
	{
		ofColor c = colors_STRUCT[currColor].color;
		color_BACK = ofColor(c);

		ofLogNotice(__FUNCTION__) << "currColor is [" << currColor << "]";

		currName = colors_STRUCT[currColor].name;
		ofLogNotice(__FUNCTION__) << "currName is [" << currName << "]";

		currColor_OriginalPos = colors_STRUCT[currColor].position;
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

	// cards enabled:

	// 1. draw card rectangles

	if (bShowCards)
	{
		int padding = 15;
		int labelSize = 25;

		int letterPad = 15;
		float fontSize = 16;
		//float fontSize = 12;
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
					(cardColor_size + cardColor_pad) * (cardSize)+padding,
				hBg
				, 5
			);

			//ofDrawRectRounded(
			//    glm::vec2(
			//        positionCards.x - padding,
			//        positionCards.y - padding),
			//    (cardColor_size + cardColor_pad) * (cardSize) + 2 * padding,
			//    (cardColor_size * 1.1 + cardColor_pad) + 2 * padding + 25,
			//    5,
			//    5,
			//    5,
			//    5
			//);

			//-

			// 2. each color in card

			int colorBegin = cardSize * cardNum;
			int colorEnd = colorBegin + cardSize;

			for (int i = 0; i < cardSize; i++)
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
					//ofStringReplace(_n, " ", "\n"); // break lines when space
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
	ofLogNotice(__FUNCTION__) << "SHOW_Gui: " << SHOW_Gui;

	SHOW_Gui = b;

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




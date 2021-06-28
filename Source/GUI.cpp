#include "stdafx.h"
#include "Hooking.h";
#include <filesystem>

//Menu Drawing
void Menu::Drawing::Text(const char * text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center)
{
	UI::SET_TEXT_CENTRE(center);
	UI::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
	UI::SET_TEXT_FONT(rgbaf.f);
	UI::SET_TEXT_SCALE(size.w, size.h);
	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)text);
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y);
}

void Menu::Drawing::PlayerText(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center)
{
	UI::SET_TEXT_CENTRE(center);
	UI::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
	UI::SET_TEXT_FONT(rgbaf.f);
	UI::SET_TEXT_SCALE(size.w, size.h);
	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)text);
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y);
}
void Menu::Drawing::PlayerInfoText(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center, bool right)
{
	UI::SET_TEXT_RIGHT_JUSTIFY(right);
	UI::SET_TEXT_CENTRE(center);
	UI::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
	UI::SET_TEXT_FONT(rgbaf.f);
	UI::SET_TEXT_SCALE(size.w, size.h);
	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)text);
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y);
}

void Menu::Drawing::Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Streamedtexture.c_str()))
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)Streamedtexture.c_str(), false);
	}
	else
	{
		GRAPHICS::DRAW_SPRITE((char*)Streamedtexture.c_str(), (char*)textureName.c_str(), x, y, width, height, rotation, r, g, b, a);
	}
}//sec //no no lok

void Menu::Drawing::Rect(RGBA rgba, VECTOR2 position, VECTOR2_2 size)
{
	GRAPHICS::DRAW_RECT(position.x, position.y, size.w, size.h, rgba.r, rgba.g, rgba.b, rgba.a);
}

//Menu Floats etc...

float Menu::Settings::menuXscale = 0.22f;
float Menu::Settings::ScrollerWidth = 0.008f;
float Menu::Settings::menuXscale321 = 0.01f;
float Menu::Settings::ScrollerThing = 0.02f;
bool Menu::Settings::DrawTextOutline = false;
float Menu::Settings::menuX = 0.81f;
float Menu::Settings::KeyboardText = 0.5f;
float Menu::Settings::scrollbarX = 0.9280f;
bool Menu::Settings::displayEnd = true;
bool Menu::Settings::displayScrollTop = true;
bool Menu::Settings::displayScrollEnd = true;
bool Menu::Settings::showSmalltitle = true;
bool Menu::Settings::selectPressed = false;
bool Menu::Settings::leftPressed = false;
bool Menu::Settings::rightPressed = false;
bool firstopen = true;
int Menu::Settings::maxVisOptions = 11;
int Menu::Settings::currentOption = 1;
int Menu::Settings::optionCount = 0;
int Menu ::Settings::openpress;
SubMenus Menu::Settings::currentMenu;
int Menu::Settings::menuLevel = 1;
int Menu::Settings::optionsArray[1000];
SubMenus Menu::Settings::menusArray[1000];
int Menu::Settings::cursorMenuX = (Menu::Settings::menuX * 100) * 15;
int Menu::Settings::Minufick = 0;
int Menu::Settings::secfick = 0;
int Menu::Settings::Hourfick = 0;

RGBAF Menu::Settings::count{ 255, 255, 255, 255, 7 };
RGBAF Menu::Settings::titleText{ 255, 255, 255, 255, 2 };
RGBAF Menu::Settings::ultratitleText{ 255, 255, 255, 255, 6 };
RGBA Menu::Settings::titleRect{ 22, 6, 45, 240 };
RGBAF Menu::Settings::optionText{ 255, 255, 255, 255, 4 };
RGBAF Menu::Settings::breakText{ 255, 255, 255, 255, 7 };
RGBAF Menu::Settings::arrow{ 255, 255, 255, 255, 3 };  
RGBA Menu::Settings::arrow2{ 255, 255, 255, 230 }; // Mod Menu Colors 
RGBA Menu::Settings::optionRect{ 0, 0, 0, 160 };
RGBA Menu::Settings::LoginRect{ 0, 0, 0, 130 };
RGBA Menu::Settings::optionRect123{ 0, 0, 0, 130 };
RGBA Menu::Settings::ScrollerAddon{ 0, 0, 0, 245 };
RGBA Menu::Settings::scroller123{ 7, 84, 61, 170 };
RGBA Menu::Settings::optionRect2{ 0, 0, 0, 245 };
RGBA Menu::Settings::breakRect{ 0, 0, 0, 110 };
RGBA Menu::Settings::scroller{ 7, 100, 255, 140 };
RGBAF Menu::Settings::integre{ 255, 255, 255, 255, 2 };
RGBA Menu::Settings::line{ 7, 84, 61, 230 };
RGBA Menu::Settings::primary{ 255, 0, 0 };
RGBA Menu::Settings::secondary{ 0, 255, 0 };

//Important - Register custom sprite from appdata - Get cutsom banner image
static fpFileRegister file_register = (fpFileRegister)(Memory::pattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9").count(1).get(0).get<decltype(file_register)>());

bool FileExists(const std::string& fileName)
{
	struct stat buffer;
	return (stat(fileName.c_str(), &buffer) == 0);
}

//Import custom banner / BANNER

void Menu::BANNER()
{
	const char* file = "Banner.ytd";
	std::ostringstream m_FilePath; m_FilePath << std::getenv("appdata") << "\\Niteures\\Banner\\" << file;

	int textureID;
	if (FileExists(m_FilePath.str().c_str()))
		file_register(&textureID, m_FilePath.str().c_str(), true, file, false);

	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("Banner", false); //Image name need to be Header.pgn/jpg
}

void Menu::ARROW()
{
	const char* file = "Arrow.ytd";
	std::ostringstream m_FilePath; m_FilePath << std::getenv("appdata") << "\\Niteures\\Arrow\\" << file;

	int textureID;
	if (FileExists(m_FilePath.str().c_str()))
		file_register(&textureID, m_FilePath.str().c_str(), true, file, false);

	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("Arrow", false); //Image name need to be Arrow.pgn
}

void Menu::LOGO()
{
	const char* file = "Logo.ytd";
	std::ostringstream m_FilePath; m_FilePath << std::getenv("appdata") << "\\Niteures\\Logo\\" << file;

	int textureID;
	if (FileExists(m_FilePath.str().c_str()))
		file_register(&textureID, m_FilePath.str().c_str(), true, file, false);

	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("Logo", false); //Image name need to be Logo.pgn
}

void Menu::PLAYERINFO()
{
	const char* file = "Infobox.ytd";
	std::ostringstream m_FilePath; m_FilePath << std::getenv("appdata") << "\\Niteures\\Infobox\\" << file;

	int textureID;
	if (FileExists(m_FilePath.str().c_str()))
		file_register(&textureID, m_FilePath.str().c_str(), true, file, false);

	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("Infobox", false); //Image name need to be Infobox.pgn
}

void Menu::PLATE()
{
	const char* file = "Plate.ytd";
	std::ostringstream m_FilePath; m_FilePath << std::getenv("appdata") << "\\Niteures\\Plate\\" << file;

	int textureID;
	if (FileExists(m_FilePath.str().c_str()))
		file_register(&textureID, m_FilePath.str().c_str(), true, file, false);

	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("Plate", false); //Image name need to be Infobox.pgn
}

void Menu::NOTIFYICON()
{
	const char* file = "Notify.ytd";
	std::ostringstream m_FilePath; m_FilePath << std::getenv("appdata") << "\\Niteures\\Icons\\" << file;

	int textureID;
	if (FileExists(m_FilePath.str().c_str()))
		file_register(&textureID, m_FilePath.str().c_str(), true, file, false);

	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("Banner", false); //Image name need to be Header.pgn/jpg
}

void Menu::Title(const char* title)
{
	//Drawing::Text(title, Settings::titleText, { Settings::menuX, 0.095f }, { 0.85f, 0.85f }, true);
	Drawing::Spriter("Banner", "Banner", Settings::menuX, 0.1175f, Menu::Settings::menuXscale, 0.085f, 0, 255, 255, 255, 245);
	Drawing::Rect(Settings::line, { Settings::menuX, 0.1175f + 0.0425f }, { 0.22f, 0.002f });
	//Drawing::Rect(Settings::titleRect, { Settings::menuX, 0.1175f }, { 0.21f, 0.085f });

	// Disable Controls
	UI::HIDE_HELP_TEXT_THIS_FRAME();
	CAM::SET_CINEMATIC_BUTTON_ACTIVE(0);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(10);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(6);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(7);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(9);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(8);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_NEXT_CAMERA, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_CHARACTER_WHEEL, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MAP_POI, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
}

void Menu::OptionInfo(const char* infotext)
{
	Drawing::Spriter("Infobox", "Infobox", 0.50f, 0.9010f, Menu::Settings::menuXscale, 0.085f, 0, 255, 255, 255, 245);
	//Drawing::Rect(Settings::optionRect, { 0.50f, 0.9010f }, { Menu::Settings::menuXscale, 0.085f } );
	Drawing::Text(infotext, Settings::optionText, { 0.50f, 0.8850f }, { 0.40f, 0.40f }, true);
	//Drawing::Rect(Settings::line, { 0.50f,  0.9500f }, { 0.21f, 0.002f });
}

int prevOption = 0;
float prevf;
float ScrollerSpeed = 0.01f; // here like 0.01f, it's slower //can i change the colour lilke transparent? of scroller? ye yes lol 
const auto animscroll = [](int* prev, const int cur) {
	if (prevf == NULL)
		prevf = *prev * 0.035f + 0.1415f;
	const auto curf = cur * 0.035f + 0.1415f;
	if (Menu::Settings::currentOption <= Menu::Settings::maxVisOptions && Menu::Settings::optionCount <= Menu::Settings::maxVisOptions) {
		if (*prev != cur)
		{
			if (prevf < curf)
			{
				if (prevf + ScrollerSpeed > curf)
					prevf = prevf + (curf - prevf);
				else
					prevf = prevf + ScrollerSpeed;
				GRAPHICS::DRAW_RECT(Menu::Settings::menuX, prevf, 0.24f, 0.035f, Menu::Settings::scroller.r, Menu::Settings::scroller.g, Menu::Settings::scroller.b, Menu::Settings::scroller.a);
				if (prevf >= curf)
				{
					prevf = curf;
					*prev = cur;
				}
			}
			if (prevf > curf)
			{
				if (prevf - ScrollerSpeed < curf)
					prevf = prevf - (prevf - curf);
				prevf = prevf - ScrollerSpeed;
				GRAPHICS::DRAW_RECT(Menu::Settings::menuX, prevf, 0.24f, 0.035f, Menu::Settings::scroller.r, Menu::Settings::scroller.g, Menu::Settings::scroller.b, Menu::Settings::scroller.a);
				if (prevf <= curf)
				{
					prevf = curf;
					*prev = cur;
				}
			}
		}
		else
		{
			*prev = cur;
			GRAPHICS::DRAW_RECT(Menu::Settings::menuX, cur * 0.035f + 0.1415f, 0.24f, 0.035f, Menu::Settings::scroller.r, Menu::Settings::scroller.g, Menu::Settings::scroller.b, Menu::Settings::scroller.a);
		}
	}
	else if ((Menu::Settings::optionCount > (Menu::Settings::currentOption - Menu::Settings::maxVisOptions)) && Menu::Settings::optionCount <= Menu::Settings::currentOption) {
		GRAPHICS::DRAW_RECT(Menu::Settings::menuX, ((Menu::Settings::optionCount - (Menu::Settings::currentOption - Menu::Settings::maxVisOptions)) * 0.035f + 0.1415f), 0.24f, 0.035f, Menu::Settings::scroller.r, Menu::Settings::scroller.g, Menu::Settings::scroller.b, Menu::Settings::scroller.a);
	}
};

float xxxxx = 0.1415f;
void Menu::ScrollBar() {
	using namespace Menu;
	int curopt = Settings::currentOption;
	int optcnt = Settings::optionCount;
	int maxopt = Settings::maxVisOptions;
	if (Settings::menuLevel > 0) 
	{
		GRAPHICS::DRAW_RECT(Settings::menuX - 0.130, 0.437f, 0.012f, (maxopt * 0.035f + 0.039f), 14, 14, 14, 196);
		GRAPHICS::DRAW_RECT(Settings::menuX - 0.130f, ((((curopt * (maxopt * 0.035f)) / optcnt))) + 0.155f, 0.010f, 0.035f, 255, 0, 0, 235);
	}
}

float ScrollerPos = { 0.035f + 0.1768f };
float Scrollerpos2 = { (Menu::Settings::optionCount - (Menu::Settings::currentOption - 11)) * 0.035f + 0.1768f };
float TargetPos;

void Menu::AnimatedScroll()
{
	if (Settings::optionCount > Settings::maxVisOptions)
	{
		if (Settings::currentOption > Settings::maxVisOptions)
		{
			TargetPos = Settings::maxVisOptions * 0.035f + 0.1768f;
			//Menu::Drawing::Rect(Menu::Settings::scroller, { Menu::Settings::menuX, TargetPos }, { 0.20f, 0.035f });
		}
		else
		{
			TargetPos = Settings::currentOption * 0.035f + 0.1768f;
			//Menu::Drawing::Rect(Menu::Settings::scroller, { Menu::Settings::menuX, TargetPos }, { 0.20f, 0.035f });
		}
	}
	else
	{
		TargetPos = Settings::currentOption * 0.035f + 0.1768f;
	}
	if (ScrollerPos > TargetPos)
	{
		ScrollerPos -= 0.0005f;
		Menu::Drawing::Rect(Menu::Settings::scroller, { Menu::Settings::menuX, ScrollerPos }, { 0.20f, 0.035f });
	}
	if (ScrollerPos < TargetPos)
	{
		ScrollerPos += 0.0005f;
		Menu::Drawing::Rect(Menu::Settings::scroller, { Menu::Settings::menuX, ScrollerPos }, { 0.20f, 0.035f });
	}
}

void SimpleSmoothScrolling() 
{
	using namespace Menu;
	float toPos;
	if (Settings::optionCount > Settings::maxVisOptions) {
		if (Settings::currentOption > Settings::maxVisOptions) {
			toPos = (0.1f / 3) + ((Settings::maxVisOptions * 0.035f) + 0.1261f);
		}
		else {
			toPos = (0.1f / 3) + ((Settings::currentOption * 0.035f) + 0.1261f);
		}
	}
	else {
		toPos = (0.1f / 3) + ((Settings::currentOption * 0.035f) + 0.1261f);
	}
	if (Menu::Settings::scrollBarPos > toPos) {
		Menu::Settings::scrollBarPos -= 0.005f;
		Drawing::Rect(Settings::scroller, { Settings::menuX,  toPos }, { 0.20f, 0.035f });
	}
	if (Menu::Settings::scrollBarPos < toPos) {
		Menu::Settings::scrollBarPos += 0.005f;
		Drawing::Rect(Settings::scroller, { Settings::menuX, toPos }, { 0.20f, 0.035f });
	}
}
int Menu::Settings::scrollBarPos = 0;

float Menu::Settings::ScrollerSpeed = 0.005f; //Or change it.
bool Menu::Settings::enable_smooth = true;
bool enable_scrollbar = false;
float prevfff;
int prevOptionnn = 0; //Add prevOption = 1 to open key on Menu::Checks::Controlls in gui.cpp and on numpad0 (back)
void AnimatedScrolling(int* prev, const int cur)
{
	if (prevfff == NULL)
		prevfff = *prev * 0.035f + 0.1768f;
	const auto curf = cur * 0.035f + 0.1768f;
	if (*prev != cur)
	{
		//Drawing::Rect(Settings::scroller, { Settings::menuX, Settings::menuY + (cur)*0.035f + 0.1415f }, { Menu::Settings::menuWidth, 0.035f }); //0.038f
		if (prevfff < curf)
		{
			if (prevfff + Menu::Settings::ScrollerSpeed > curf)
				prevfff = prevfff + (curf - prevfff);
			else
				prevfff = prevfff + Menu::Settings::ScrollerSpeed;
			Menu::Drawing::Rect(Menu::Settings::scroller, { Menu::Settings::menuX, prevfff }, { 0.20f, 0.035f });

			if (enable_scrollbar)
			{
				// Menu::Drawing::Rect(Menu::Settings::scroller, { Menu::Settings::menuX - Menu::Settings::scrollbarWidthIndex, Menu::Settings::menuY + prevf }, { 0.008f, 0.035f });
			}
			if (prevfff >= curf)
			{
				prevfff = curf;
				*prev = cur;
			}
		}
		if (prevfff > curf)
		{
			if (prevfff - Menu::Settings::ScrollerSpeed < curf)
				prevfff = prevfff - (prevfff - curf);
			prevfff = prevfff - Menu::Settings::ScrollerSpeed;

			Menu::Drawing::Rect(Menu::Settings::scroller, { Menu::Settings::menuX, prevfff }, { 0.20f, 0.035f });

			if (enable_scrollbar)
			{
				//Menu::Drawing::Rect(Menu::Settings::scroller, { Menu::Settings::menuX - Menu::Settings::scrollbarWidthIndex, Menu::Settings::menuY + prevf }, { 0.008f, 0.035f });
			}
			if (prevfff <= curf)
			{
				prevfff = curf;
				*prev = cur;
			}
		}
	}
	else
	{
		*prev = cur;
		Menu::Drawing::Rect(Menu::Settings::scroller, { Menu::Settings::menuX, prevfff }, { 0.20f, 0.035f });
		if (enable_scrollbar)
		{
			//Menu::Drawing::Rect(Menu::Settings::scroller, { Menu::Settings::menuX - Menu::Settings::scrollbarWidthIndex, Menu::Settings::menuY + (cur) * 0.035f + 0.1415f }, { 0.008f, 0.035f });
		}
	}
}
//-----------------------------------------------------------------------
//Creating vehicle preview option

struct VehBmpSprite
{
	Hash modelHash;
	std::string dict, imgName;

	friend bool operator == (const VehBmpSprite& left, const Hash right)
	{
		return left.modelHash == right;
	}

	VehBmpSprite()
		: modelHash(0)
	{
	}
	VehBmpSprite(Hash modelHashP)
		: modelHash(modelHashP)
	{
	}
	VehBmpSprite(Hash modelHashP, std::string dictP, std::string imgNameP)
		: modelHash(modelHashP), dict(dictP), imgName(imgNameP)
	{
	}
};

enum VehicleHash : DWORD
{

	//Casino
	VEHICLE_CARACARA2 = 0xaf966f3c,
	VEHICLE_DRAFTER = 0x28EAB80F,
	VEHICLE_DYNASTY = 0x127e90d5,
	VEHICLE_EMERUS = 0x4ee74355,
	VEHICLE_GAUNTLET3 = 0x2b0c4dcd,
	VEHICLE_GAUNTLET4 = 0x734c5e50,
	VEHICLE_HELLION = 0xea6a047f,
	VEHICLE_ISSI7 = 0x6e8da4f7,
	VEHICLE_JUGULAR = 0xf38c4245,
	VEHICLE_KRIEGER = 0xd86a0247,
	VEHICLE_LOCUST = 0xc7e55211,
	VEHICLE_NEBULA = 0xcb642637,
	VEHICLE_NEO = 0x9f6ed5a2,
	VEHICLE_NOVAK = 0x92f5024e,
	VEHICLE_PARAGON = 0xe550775b,
	VEHICLE_PARAGON2 = 0x546d8eee,
	VEHICLE_PEYOTE2 = 0x9472cd24,
	VEHICLE_RROCKET = 0x36a167e0,
	VEHICLE_S80 = 0xeca6b6a3,
	VEHICLE_THRAX = 0x3e3d1f59,
	VEHICLE_ZION3 = 0x6f039a67,
	VEHICLE_ZORRUSSO = 0xd757d97d,
	///Casino Heist///
	VEHICLE_FORMULA = 0x1446590a,
	VEHICLE_FURIA = 0x3944d5a0,
	VEHICLE_IMORGON = 0xbc7c0a00,
	VEHICLE_KOMODA = 0xce44c4b9,
	VEHICLE_REBLA = 0x04f48fc4,
	VEHICLE_STRYDER = 0x11f58a5a,
	VEHICLE_VSTR = 0x56cdee7d,

	VEHICLE_ASBO = 0x42aca95f,
	VEHICLE_EVERON = 0x97553c28,
	VEHICLE_KANJO = 0x18619b7e,
	VEHICLE_OUTLAW = 0x185e2ff3,
	VEHICLE_RETINUE2 = 0x79178f0a,
	VEHICLE_SUGOI = 0x3adb9758,
	VEHICLE_SULTAN2 = 0x3404691c,
	VEHICLE_VAGRANT = 0x2c1fea99,
	VEHICLE_YOSEMITE2 = 0x64f49967,

	VEHICLE_BLAZER2 = 0xfd231729,
	VEHICLE_BOXVILLE = 0x898eccea,
	VEHICLE_BURRITO2 = 0xc9e8ff76,
	VEHICLE_FIRETRUK = 0x73920f8e,
	VEHICLE_JB7002 = 0x177da45c,
	VEHICLE_LGUARD = 0x1bf8d381,
	VEHICLE_MINITANK = 0xb53c6c52,
	VEHICLE_ZHABA = 0x4c8dba51,
	VEHICLE_STOCKADE = 0x6827cf72,
	///Casino Heist///

	VEHICLE_ADDER = 0xB779A091,
	VEHICLE_AIRBUS = 0x4C80EB0E,
	VEHICLE_AIRTUG = 0x5D0AAC8F,
	VEHICLE_AKUMA = 0x63ABADE7,
	VEHICLE_ALPHA = 0x2DB8D1AA,
	VEHICLE_AMBULANCE = 0x45D56ADA,
	VEHICLE_ANNIHILATOR = 0x31F0B376,
	VEHICLE_ARMYTANKER = 0xB8081009,
	VEHICLE_ARMYTRAILER = 0xA7FF33F5,
	VEHICLE_ARMYTRAILER2 = 0x9E6B14D6,
	VEHICLE_ASEA = 0x94204D89,
	VEHICLE_ASEA2 = 0x9441D8D5,
	VEHICLE_ASTEROPE = 0x8E9254FB,
	VEHICLE_BAGGER = 0x806B9CC3,
	VEHICLE_BALETRAILER = 0xE82AE656,
	VEHICLE_BALLER = 0xCFCA3668,
	VEHICLE_BALLER2 = 0x08852855,
	VEHICLE_BALLER3 = 0x6FF0F727,
	VEHICLE_BALLER4 = 0x25CBE2E2,
	VEHICLE_BALLER5 = 0x1C09CF5E,
	VEHICLE_BALLER6 = 0x27B4E6B0,
	VEHICLE_BANSHEE = 0xC1E908D2,
	VEHICLE_BANSHEE2 = 0x25C5AF13,
	VEHICLE_BARRACKS = 0xCEEA3F4B,
	VEHICLE_BARRACKS2 = 0x4008EABB,
	VEHICLE_BARRACKS3 = 0x2592B5CF,
	VEHICLE_BATI = 0xF9300CC5,
	VEHICLE_BATI2 = 0xCADD5D2D,
	VEHICLE_BESTIAGTS = 0x4BFCF28B,
	VEHICLE_BENSON = 0x7A61B330,
	VEHICLE_BESRA = 0x6CBD1D6D,
	VEHICLE_BF400 = 0x05283265,
	VEHICLE_BFINJECTION = 0x432AA566,
	VEHICLE_BIFF = 0x32B91AE8,
	VEHICLE_BIFTA = 0xEB298297,
	VEHICLE_BISON = 0xFEFD644F,
	VEHICLE_BISON2 = 0x7B8297C5,
	VEHICLE_BISON3 = 0x67B3F020,
	VEHICLE_BJXL = 0x32B29A4B,
	VEHICLE_BLADE = 0xB820ED5E,
	VEHICLE_BLAZER = 0x8125BCF9,
	//VEHICLE_BLAZER2 = 0xFD231729,
	VEHICLE_BLAZER3 = 0xB44F0582,
	VEHICLE_BLIMP = 0xF7004C86,
	VEHICLE_BLIMP2 = 0xDB6B4924,
	VEHICLE_BLISTA = 0xEB70965F,
	VEHICLE_BLISTA2 = 0x3DEE5EDA,
	VEHICLE_BLISTA3 = 0xDCBC1C3B,
	VEHICLE_BMX = 0x43779C54,
	VEHICLE_BOATTRAILER = 0x1F3D44B5,
	VEHICLE_BOBCATXL = 0x3FC5D440,
	VEHICLE_BODHI2 = 0xAA699BB6,
	//VEHICLE_BOXVILLE = 0x898ECCEA,
	VEHICLE_BOXVILLE2 = 0xF21B33BE,
	VEHICLE_BOXVILLE3 = 0x07405E08,
	VEHICLE_BOXVILLE4 = 0x1A79847A,
	VEHICLE_BRAWLER = 0xA7CE1BC5,
	VEHICLE_BRICKADE = 0xEDC6F847,
	VEHICLE_BRIOSO = 0x5C55CB39,
	VEHICLE_BTYPE = 0x06FF6914,
	VEHICLE_BTYPE2 = 0xCE6B35A4,
	VEHICLE_BTYPE3 = 0xDC19D101,
	VEHICLE_BUCCANEER = 0xD756460C,
	VEHICLE_BUCCANEER2 = 0xC397F748,
	VEHICLE_BUFFALO = 0xEDD516C6,
	VEHICLE_BUFFALO2 = 0x2BEC3CBE,
	VEHICLE_BUFFALO3 = 0xE2C013E,
	VEHICLE_BULLDOZER = 0x7074F39D,
	VEHICLE_BULLET = 0x9AE6DDA1,
	VEHICLE_BURRITO = 0xAFBB2CA4,
	//VEHICLE_BURRITO2 = 0xC9E8FF76,
	VEHICLE_BURRITO3 = 0x98171BD3,
	VEHICLE_BURRITO4 = 0x353B561D,
	VEHICLE_BURRITO5 = 0x437CF2A0,
	VEHICLE_BUS = 0xD577C962,
	VEHICLE_BUZZARD = 0x2F03547B,
	VEHICLE_BUZZARD2 = 0x2C75F0DD,
	VEHICLE_CABLECAR = 0xC6C3242D,
	VEHICLE_CADDY = 0x44623884,
	VEHICLE_CADDY2 = 0xDFF0594C,
	VEHICLE_CAMPER = 0x6FD95F68,
	VEHICLE_CARBONIZZARE = 0x7B8AB45F,
	VEHICLE_CARBONRS = 0x00ABB0C0,
	VEHICLE_CARGOBOB = 0xFCFCB68B,
	VEHICLE_CARGOBOB2 = 0x60A7EA10,
	VEHICLE_CARGOBOB3 = 0x53174EEF,
	VEHICLE_CARGOBOB4 = 0x78BC1A3C,
	VEHICLE_CARGOPLANE = 0x15F27762,
	VEHICLE_CASCO = 0x3822BDFE,
	VEHICLE_CAVALCADE = 0x779F23AA,
	VEHICLE_CAVALCADE2 = 0xD0EB2BE5,
	VEHICLE_CHEETAH = 0xB1D95DA0,
	VEHICLE_CHINO = 0x14D69010,
	VEHICLE_CHINO2 = 0xAED64A63,
	VEHICLE_CLIFFHANGER = 0x17420102,
	VEHICLE_COACH = 0x84718D34,
	VEHICLE_COGCABRIO = 0x13B57D8A,
	VEHICLE_COG55 = 0x360A438E,
	VEHICLE_COG552 = 0x29FCD3E4,
	VEHICLE_COMET2 = 0xC1AE4D16,
	VEHICLE_COGNOSCENTI = 0x86FE0B60,
	VEHICLE_COGNOSCENTI2 = 0xDBF2D57A,
	VEHICLE_CONTENDER = 0x28B67ACA,
	VEHICLE_COQUETTE = 0x067BC037,
	VEHICLE_COQUETTE2 = 0x3C4E2113,
	VEHICLE_COQUETTE3 = 0x2EC385FE,
	VEHICLE_CRUISER = 0x1ABA13B5,
	VEHICLE_CRUSADER = 0x132D5A1A,
	VEHICLE_CUBAN800 = 0xD9927FE3,
	VEHICLE_CUTTER = 0xC3FBA120,
	VEHICLE_DAEMON = 0x77934CEE,
	VEHICLE_DILETTANTE = 0xBC993509,
	VEHICLE_DILETTANTE2 = 0x64430650,
	VEHICLE_DINGHY = 0x3D961290,
	VEHICLE_DINGHY2 = 0x107F392C,
	VEHICLE_DINGHY3 = 0x1E5E54EA,
	VEHICLE_DINGHY4 = 0x33B47F96,
	VEHICLE_DLOADER = 0x698521E3,
	VEHICLE_DOCKTRAILER = 0x806EFBEE,
	VEHICLE_DOCKTUG = 0xCB44B1CA,
	VEHICLE_DODO = 0xCA495705,
	VEHICLE_DOMINATOR = 0x04CE68AC,
	VEHICLE_DOMINATOR2 = 0xC96B73D9,
	VEHICLE_DOUBLE = 0x9C669788,
	VEHICLE_DUBSTA = 0x462FE277,
	VEHICLE_DUBSTA2 = 0xE882E5F6,
	VEHICLE_DUBSTA3 = 0xB6410173,
	VEHICLE_DUKES = 0x2B26F456,
	VEHICLE_DUKES2 = 0xEC8F7094,
	VEHICLE_DUMP = 0x810369E2,
	VEHICLE_DUNE = 0x9CF21E0F,
	VEHICLE_DUNE2 = 0x1FD824AF,
	VEHICLE_DUSTER = 0x39D6779E,
	VEHICLE_ELEGY2 = 0xDE3D9D22,
	VEHICLE_EMPEROR = 0xD7278283,
	VEHICLE_EMPEROR2 = 0x8FC3AADC,
	VEHICLE_EMPEROR3 = 0xB5FCF74E,
	VEHICLE_ENDURO = 0x6882FA73,
	VEHICLE_ENTITYXF = 0xB2FE5CF9,
	VEHICLE_EXEMPLAR = 0xFFB15B5E,
	VEHICLE_F620 = 0xDCBCBE48,
	VEHICLE_FACTION = 0x81A9CDDF,
	VEHICLE_FACTION2 = 0x95466BDB,
	VEHICLE_FACTION3 = 0x866BCE26,
	VEHICLE_FAGGIO2 = 0x0350D1AB,
	VEHICLE_FBI = 0x432EA949,
	VEHICLE_FBI2 = 0x9DC66994,
	VEHICLE_FELON = 0xE8A8BDA8,
	VEHICLE_FELON2 = 0xFAAD85EE,
	VEHICLE_FELTZER2 = 0x8911B9F5,
	VEHICLE_FELTZER3 = 0xA29D6D10,
	//VEHICLE_FIRETRUK = 0x73920F8E,
	VEHICLE_FIXTER = 0xCE23D3BF,
	VEHICLE_FLATBED = 0x50B0215A,
	VEHICLE_FMJ = 0x5502626C,
	VEHICLE_FORKLIFT = 0x58E49664,
	VEHICLE_FQ2 = 0xBC32A33B,
	VEHICLE_FREIGHT = 0x3D6AAA9B,
	VEHICLE_FREIGHTCAR = 0x0AFD22A6,
	VEHICLE_FREIGHTCONT1 = 0x36DCFF98,
	VEHICLE_FREIGHTCONT2 = 0x0E512E79,
	VEHICLE_FREIGHTGRAIN = 0x264D9262,
	VEHICLE_FREIGHTTRAILER = 0xD1ABB666,
	VEHICLE_FROGGER = 0x2C634FBD,
	VEHICLE_FROGGER2 = 0x742E9AC0,
	VEHICLE_FUGITIVE = 0x71CB2FFB,
	VEHICLE_FUROREGT = 0xBF1691E0,
	VEHICLE_FUSILADE = 0x1DC0BA53,
	VEHICLE_FUTO = 0x7836CE2F,
	VEHICLE_GARGOYLE = 0x2C2C2324,
	VEHICLE_GAUNTLET = 0x94B395C5,
	VEHICLE_GAUNTLET2 = 0x14D22159,
	VEHICLE_GBURRITO = 0x97FA4F36,
	VEHICLE_GBURRITO2 = 0x11AA0E14,
	VEHICLE_GLENDALE = 0x047A6BC1,
	VEHICLE_GRAINTRAILER = 0x3CC7F596,
	VEHICLE_GRANGER = 0x9628879C,
	VEHICLE_GRESLEY = 0xA3FC0F4D,
	VEHICLE_GUARDIAN = 0x825A9F4C,
	VEHICLE_HABANERO = 0x34B7390F,
	VEHICLE_HAKUCHOU = 0x4B6C568A,
	VEHICLE_HANDLER = 0x1A7FCEFA,
	VEHICLE_HAULER = 0x5A82F9AE,
	VEHICLE_HEXER = 0x11F76C14,
	VEHICLE_HOTKNIFE = 0x0239E390,
	VEHICLE_HUNTLEY = 0x1D06D681,
	VEHICLE_HYDRA = 0x39D6E83F,
	VEHICLE_INFERNUS = 0x18F25AC7,
	VEHICLE_INGOT = 0xB3206692,
	VEHICLE_INNOVATION = 0xF683EACA,
	VEHICLE_INSURGENT = 0x9114EADA,
	VEHICLE_INSURGENT2 = 0x7B7E56F0,
	VEHICLE_INTRUDER = 0x34DD8AA1,
	VEHICLE_ISSI2 = 0xB9CB3B69,
	VEHICLE_JACKAL = 0xDAC67112,
	VEHICLE_JB700 = 0x3EAB5555,
	VEHICLE_JESTER = 0xB2A716A3,
	VEHICLE_JESTER2 = 0xBE0E6126,
	VEHICLE_JET = 0x3F119114,
	VEHICLE_JETMAX = 0x33581161,
	VEHICLE_JOURNEY = 0xF8D48E7A,
	VEHICLE_KALAHARI = 0x05852838,
	VEHICLE_KHAMELION = 0x206D1B68,
	VEHICLE_KURUMA = 0xAE2BFE94,
	VEHICLE_KURUMA2 = 0x187D938D,
	VEHICLE_LANDSTALKER = 0x4BA4E8DC,
	VEHICLE_LAZER = 0xB39B0AE6,
	VEHICLE_LE7B = 0xB6846A55,
	VEHICLE_LECTRO = 0x26321E67,
	//VEHICLE_LGUARD = 0x1BF8D381,
	VEHICLE_LIMO2 = 0xF92AEC4D,
	VEHICLE_LURCHER = 0x7B47A6A7,
	VEHICLE_LUXOR = 0x250B0C5E,
	VEHICLE_LUXOR2 = 0xB79F589E,
	VEHICLE_LYNX = 0x1CBDC10B,
	VEHICLE_MAMBA = 0x9CFFFC56,
	VEHICLE_MAMMATUS = 0x97E55D11,
	VEHICLE_MANANA = 0x81634188,
	VEHICLE_MARQUIS = 0xC1CE1183,
	VEHICLE_MARSHALL = 0x49863E9C,
	VEHICLE_MASSACRO = 0xF77ADE32,
	VEHICLE_MASSACRO2 = 0xDA5819A3,
	VEHICLE_MAVERICK = 0x9D0450CA,
	VEHICLE_MESA = 0x36848602,
	VEHICLE_MESA2 = 0xD36A4B44,
	VEHICLE_MESA3 = 0x84F42E51,
	VEHICLE_METROTRAIN = 0x33C9E158,
	VEHICLE_MILJET = 0x09D80F93,
	VEHICLE_MINIVAN = 0xED7EADA4,
	VEHICLE_MINIVAN2 = 0xBCDE91F0,
	VEHICLE_MIXER = 0xD138A6BB,
	VEHICLE_MIXER2 = 0x1C534995,
	VEHICLE_MONROE = 0xE62B361B,
	VEHICLE_MONSTER = 0xCD93A7DB,
	VEHICLE_MOONBEAM = 0x1F52A43F,
	VEHICLE_MOONBEAM2 = 0x710A2B9B,
	VEHICLE_MOWER = 0x6A4BD8F6,
	VEHICLE_MULE = 0x35ED670B,
	VEHICLE_MULE2 = 0xC1632BEB,
	VEHICLE_MULE3 = 0x85A5B471,
	VEHICLE_NEMESIS = 0xDA288376,
	VEHICLE_NIGHTSHADE = 0x8C2BD0DC,
	VEHICLE_NIMBUS = 0xB2CF7250,
	VEHICLE_NINEF = 0x3D8FA25C,
	VEHICLE_NINEF2 = 0xA8E38B01,
	VEHICLE_OMNIS = 0xD1AD4937,
	VEHICLE_ORACLE = 0x506434F6,
	VEHICLE_ORACLE2 = 0xE18195B2,
	VEHICLE_OSIRIS = 0x767164D6,
	VEHICLE_PACKER = 0x21EEE87D,
	VEHICLE_PANTO = 0xE644E480,
	VEHICLE_PARADISE = 0x58B3979C,
	VEHICLE_PATRIOT = 0xCFCFEB3B,
	VEHICLE_PBUS = 0x885F3671,
	VEHICLE_PCJ = 0xC9CEAF06,
	VEHICLE_PENUMBRA = 0xE9805550,
	VEHICLE_PEYOTE = 0x6D19CCBC,
	VEHICLE_PFISTER811 = 0x92EF6E04,
	VEHICLE_PHANTOM = 0x809AA4CB,
	VEHICLE_PHOENIX = 0x831A21D5,
	VEHICLE_PICADOR = 0x59E0FBF3,
	VEHICLE_PIGALLE = 0x404B6381,
	VEHICLE_POLICE = 0x79FBB0C5,
	VEHICLE_POLICE2 = 0x9F05F101,
	VEHICLE_POLICE3 = 0x71FA16EA,
	VEHICLE_POLICE4 = 0x8A63C7B9,
	VEHICLE_POLICEB = 0xFDEFAEC3,
	VEHICLE_POLICEOLD1 = 0xA46462F7,
	VEHICLE_POLICEOLD2 = 0x95F4C618,
	VEHICLE_POLICET = 0x1B38E955,
	VEHICLE_POLMAV = 0x1517D4D9,
	VEHICLE_PONY = 0xF8DE29A8,
	VEHICLE_PONY2 = 0x38408341,
	VEHICLE_POUNDER = 0x7DE35E7D,
	VEHICLE_PRAIRIE = 0xA988D3A2,
	VEHICLE_PRANGER = 0x2C33B46E,
	VEHICLE_PREDATOR = 0xE2E7D4AB,
	VEHICLE_PREMIER = 0x8FB66F9B,
	VEHICLE_PRIMO = 0xBB6B404F,
	VEHICLE_PRIMO2 = 0x86618EDA,
	VEHICLE_PROPTRAILER = 0x153E1B0A,
	VEHICLE_PROTOTIPO = 0x7E8F677F,
	VEHICLE_RADI = 0x9D96B45B,
	VEHICLE_RAKETRAILER = 0x174CB172,
	VEHICLE_RALLYTRUCK = 0x829A3C44,
	VEHICLE_RANCHERXL = 0x6210CBB0,
	VEHICLE_RANCHERXL2 = 0x7341576B,
	VEHICLE_RAPIDGT = 0x8CB29A14,
	VEHICLE_RAPIDGT2 = 0x679450AF,
	VEHICLE_RATLOADER = 0xD83C13CE,
	VEHICLE_RATLOADER2 = 0xDCE1D9F7,
	VEHICLE_REAPER = 0x0DF381E5,
	VEHICLE_REBEL = 0xB802DD46,
	VEHICLE_REBEL2 = 0x8612B64B,
	VEHICLE_REGINA = 0xFF22D208,
	VEHICLE_RENTALBUS = 0xBE819C63,
	VEHICLE_RHAPSODY = 0x322CF98F,
	VEHICLE_RHINO = 0x2EA68690,
	VEHICLE_RIOT = 0xB822A1AA,
	VEHICLE_RIPLEY = 0xCD935EF9,
	VEHICLE_ROCOTO = 0x7F5C91F1,
	VEHICLE_ROMERO = 0x2560B2FC,
	VEHICLE_RUBBLE = 0x9A5B1DCC,
	VEHICLE_RUFFIAN = 0xCABD11E8,
	VEHICLE_RUINER = 0xF26CEFF9,
	VEHICLE_RUMPO = 0x4543B74D,
	VEHICLE_RUMPO2 = 0x961AFEF7,
	VEHICLE_RUMPO3 = 0x57F682AF,
	VEHICLE_SABREGT = 0x9B909C94,
	VEHICLE_SABREGT2 = 0x0D4EA603,
	VEHICLE_SADLER = 0xDC434E51,
	VEHICLE_SADLER2 = 0x2BC345D1,
	VEHICLE_SANCHEZ = 0x2EF89E46,
	VEHICLE_SANCHEZ2 = 0xA960B13E,
	VEHICLE_SANDKING = 0xB9210FD0,
	VEHICLE_SANDKING2 = 0x3AF8C345,
	VEHICLE_SAVAGE = 0xFB133A17,
	VEHICLE_SCHAFTER2 = 0xB52B5113,
	VEHICLE_SCHAFTER3 = 0xA774B5A6,
	VEHICLE_SCHAFTER4 = 0x58CF185C,
	VEHICLE_SCHAFTER5 = 0xCB0E7CD9,
	VEHICLE_SCHAFTER6 = 0x72934BE4,
	VEHICLE_SCHWARZER = 0xD37B7976,
	VEHICLE_SCORCHER = 0xF4E1AA15,
	VEHICLE_SCRAP = 0x9A9FD3DF,
	VEHICLE_SEASHARK = 0xC2974024,
	VEHICLE_SEASHARK2 = 0xDB4388E4,
	VEHICLE_SEASHARK3 = 0xED762D49,
	VEHICLE_SEMINOLE = 0x48CECED3,
	VEHICLE_SENTINEL = 0x50732C82,
	VEHICLE_SENTINEL2 = 0x3412AE2D,
	VEHICLE_SERRANO = 0x4FB1A214,
	VEHICLE_SEVEN70 = 0x97398A4B,
	VEHICLE_SHAMAL = 0xB79C1BF5,
	VEHICLE_SHEAVA = 0x30D3F6D8,
	VEHICLE_SHERIFF = 0x9BAA707C,
	VEHICLE_SHERIFF2 = 0x72935408,
	VEHICLE_SKYLIFT = 0x3E48BF23,
	VEHICLE_SLAMVAN = 0x2B7F9DE3,
	VEHICLE_SLAMVAN2 = 0x31ADBBFC,
	VEHICLE_SLAMVAN3 = 0x42BC5E19,
	VEHICLE_SOVEREIGN = 0x2C509634,
	VEHICLE_SPEEDER = 0x0DC60D2B,
	VEHICLE_SPEEDER2 = 0x1A144F2A,
	VEHICLE_SPEEDO = 0xCFB3870C,
	VEHICLE_SPEEDO2 = 0x2B6DC64A,
	VEHICLE_SQUALO = 0x17DF5EC2,
	VEHICLE_STALION = 0x72A4C31E,
	VEHICLE_STALION2 = 0xE80F67EE,
	VEHICLE_STANIER = 0xA7EDE74D,
	VEHICLE_STINGER = 0x5C23AF9B,
	VEHICLE_STINGERGT = 0x82E499FA,
	//VEHICLE_STOCKADE = 0x6827CF72,
	VEHICLE_STOCKADE3 = 0xF337AB36,
	VEHICLE_STRATUM = 0x66B4FC45,
	VEHICLE_STRETCH = 0x8B13F083,
	VEHICLE_STUNT = 0x81794C70,
	VEHICLE_SUBMERSIBLE = 0x2DFF622F,
	VEHICLE_SUBMERSIBLE2 = 0xC07107EE,
	VEHICLE_SULTAN = 0x39DA2754,
	VEHICLE_SULTANRS = 0xEE6024BC,
	VEHICLE_SUNTRAP = 0xEF2295C9,
	VEHICLE_SUPERD = 0x42F2ED16,
	VEHICLE_SUPERVOLITO = 0x2A54C47D,
	VEHICLE_SUPERVOLITO2 = 0x9C5E5644,
	VEHICLE_SURANO = 0x16E478C1,
	VEHICLE_SURFER = 0x29B0DA97,
	VEHICLE_SURFER2 = 0xB1D80E06,
	VEHICLE_SURGE = 0x8F0E3594,
	VEHICLE_SWIFT = 0xEBC24DF2,
	VEHICLE_SWIFT2 = 0x4019CB4C,
	VEHICLE_T20 = 0x6322B39A,
	VEHICLE_TACO = 0x744CA80D,
	VEHICLE_TAILGATER = 0xC3DDFDCE,
	VEHICLE_TAMPA = 0x39F9C898,
	VEHICLE_TAMPA2 = 0xC0240885,
	VEHICLE_TANKER = 0xD46F4737,
	VEHICLE_TANKER2 = 0x74998082,
	VEHICLE_TANKERCAR = 0x22EDDC30,
	VEHICLE_TAXI = 0xC703DB5F,
	VEHICLE_TECHNICAL = 0x83051506,
	VEHICLE_THRUST = 0x6D6F8F43,
	VEHICLE_TIPTRUCK = 0x02E19879,
	VEHICLE_TIPTRUCK2 = 0xC7824E5E,
	VEHICLE_TITAN = 0x761E2AD3,
	VEHICLE_TORO = 0x3FD5AA2F,
	VEHICLE_TORO2 = 0x362CAC6D,
	VEHICLE_TORNADO = 0x1BB290BC,
	VEHICLE_TORNADO2 = 0x5B42A5C4,
	VEHICLE_TORNADO3 = 0x690A4153,
	VEHICLE_TORNADO4 = 0x86CF7CDD,
	VEHICLE_TORNADO5 = 0x94DA98EF,
	VEHICLE_TOURBUS = 0x73B1C3CB,
	VEHICLE_TOWTRUCK = 0xB12314E0,
	VEHICLE_TOWTRUCK2 = 0xE5A2D6C6,
	VEHICLE_TR2 = 0x7BE032C6,
	VEHICLE_TR3 = 0x6A59902D,
	VEHICLE_TR4 = 0x7CAB34D0,
	VEHICLE_TRACTOR = 0x61D6BA8C,
	VEHICLE_TRACTOR2 = 0x843B73DE,
	VEHICLE_TRACTOR3 = 0x562A97BD,
	VEHICLE_TRAILERLOGS = 0x782A236D,
	VEHICLE_TRAILERS = 0xCBB2BE0E,
	VEHICLE_TRAILERS2 = 0xA1DA3C91,
	VEHICLE_TRAILERS3 = 0x8548036D,
	VEHICLE_TRAILERSMALL = 0x2A72BEAB,
	VEHICLE_TRASH = 0x72435A19,
	VEHICLE_TRASH2 = 0xB527915C,
	VEHICLE_TRFLAT = 0xAF62F6B2,
	VEHICLE_TRIBIKE = 0x4339CD69,
	VEHICLE_TRIBIKE2 = 0xB67597EC,
	VEHICLE_TRIBIKE3 = 0xE823FB48,
	VEHICLE_TROHPYTRUCK = 0x5728D321,
	VEHICLE_TROHPYTRUCK2 = 0x3335A165,
	VEHICLE_TROPIC = 0x1149422F,
	VEHICLE_TROPIC2 = 0x56590FE9,
	VEHICLE_TROPOS = 0x707E63A4,
	VEHICLE_TUG = 0x82CAC433,
	VEHICLE_TURISMOR = 0x185484E1,
	VEHICLE_TVTRAILER = 0x967620BE,
	VEHICLE_TYRUS = 0x7B406EFB,
	VEHICLE_UTILLITRUCK = 0x1ED0A534,
	VEHICLE_UTILLITRUCK2 = 0x34E6BF6B,
	VEHICLE_UTILLITRUCK3 = 0x7F2153DF,
	VEHICLE_VACCA = 0x142E0DC3,
	VEHICLE_VADER = 0xF79A00F7,
	VEHICLE_VALKYRIE = 0xA09E15FD,
	VEHICLE_VALKYRIE2 = 0x5BFA5C4B,
	VEHICLE_VELUM = 0x9C429B6A,
	VEHICLE_VELUM2 = 0x403820E8,
	VEHICLE_VERLIERER2 = 0x41B77FA4,
	VEHICLE_VESTRA = 0x4FF77E37,
	VEHICLE_VIGERO = 0xCEC6B9B7,
	VEHICLE_VINDICATOR = 0xAF599F01,
	VEHICLE_VIRGO = 0xE2504942,
	VEHICLE_VIRGO2 = 0xCA62927A,
	VEHICLE_VIRGO3 = 0x00FDFFB0,
	VEHICLE_VOLATUS = 0x920016F1,
	VEHICLE_VOLTIC = 0x9F4B77BE,
	VEHICLE_VOODOO2 = 0x1F3766E3,
	VEHICLE_VOODOO = 0x779B4F2D,
	VEHICLE_WARRENER = 0x51D83328,
	VEHICLE_WASHINGTON = 0x69F06B57,
	VEHICLE_WINDSOR = 0x5E4327C8,
	VEHICLE_WINDSOR2 = 0x8CF5CAE1,
	VEHICLE_XLS = 0x47BBCF2E,
	VEHICLE_XLS2 = 0xE6401328,
	VEHICLE_YOUGA = 0x03E5F6B8,
	VEHICLE_ZENTORNO = 0xAC5DF515,
	VEHICLE_ZION = 0xBD1B39C3,
	VEHICLE_ZION2 = 0xB8E2AE18,
	VEHICLE_ZTYPE = 0x2D3BD401,

	// Bikers DLC 1.0.877.1
	VEHICLE_ESSKEY = 0x794CB30C,
	VEHICLE_NIGHTBLADE = 0xA0438767,
	VEHICLE_DEFILER = 0x30FF0190,
	VEHICLE_AVARUS = 0x81E38F7F,
	VEHICLE_ZOMBIEA = 0xC3D7C72B,
	VEHICLE_ZOMBIEB = 0xDE05FB87,
	VEHICLE_HAKUCHOU2 = 0xF0C2A91F,
	VEHICLE_VORTEX = 0xDBA9DBFC,
	VEHICLE_CHIMERA = 0x00675ED7,
	VEHICLE_RAPTOR = 0xD7C56D39,
	VEHICLE_DAEMON2 = 0xAC4E93C9,
	VEHICLE_RATBIKE = 0x6FACDF31,
	VEHICLE_WOLFSBANE = 0xDB20A373,
	VEHICLE_BLAZER4 = 0xE5BA6858,
	VEHICLE_SHOTARO = 0xE7D2A16E,
	VEHICLE_TORNADO6 = 0xA31CB573,
	VEHICLE_SANCTUS = 0x58E316C7,
	VEHICLE_YOUGA2 = 0x3D29CD2B,
	VEHICLE_MANCHEZ = 0xA5325278,
	VEHICLE_FAGGIO3 = 0xB328B188,
	VEHICLE_FAGGIO = 0x9229E4EB,
	VEHICLE_FAGGION = 0x7F384994,

	// Import/Export DLC 1.0.944.2
	VEHICLE_VOLTIC2 = 0x3AF76F4A,
	VEHICLE_RUINER2 = 0x381E10BD,
	VEHICLE_RUINER3 = 0x2E5AFD37,
	VEHICLE_DUNE4 = 0xCEB28249,
	VEHICLE_DUNE5 = 0xED62BFA9,
	VEHICLE_PHANTOM2 = 0x9DAE1398,
	VEHICLE_TECHNICAL2 = 0x4662BCBB,
	VEHICLE_BOXVILLE5 = 0x28AD20E1,
	VEHICLE_WASTLNDR = 0x8E08EC82,
	VEHICLE_BLAZER5 = 0xA1355F67,
	VEHICLE_COMET3 = 0x877358AD,
	VEHICLE_DIABLOUS = 0xF1B44F44,
	VEHICLE_DIABLOUS2 = 0x6ABDF65E,
	VEHICLE_ELEGY = 0x0BBA2261,
	VEHICLE_FCR = 0x25676EAF,
	VEHICLE_FCR2 = 0xD2D5E00E,
	VEHICLE_ITALIGTB = 0x85E8E76B,
	VEHICLE_ITALIGTB2 = 0xE33A477B,
	VEHICLE_NERO = 0x3DA47243,
	VEHICLE_NERO2 = 0x4131F378,
	VEHICLE_PENETRATOR = 0x9734F3EA,
	VEHICLE_SPECTER = 0x706E2B40,
	VEHICLE_SPECTER2 = 0x400F5147,
	VEHICLE_TEMPESTA = 0x1044926F,

	// mpspecialraces 1.0.1011.1
	VEHICLE_GP1 = 0x4992196C,
	VEHICLE_INFERNUS2 = 0xAC33179C,
	VEHICLE_RUSTON = 0x2AE524A8,
	VEHICLE_TURISMO2 = 0xC575DF11,

	// mpgunrunning 1.0.1103.2
	VEHICLE_APC = 0x2189D250,
	VEHICLE_ARDENT = 0x097E5533,
	VEHICLE_CADDY3 = 0xD227BDBB,
	VEHICLE_CHEETAH2 = 0x0D4E5F4D,
	VEHICLE_DUNE3 = 0x711D4738,
	VEHICLE_HALFTRACK = 0xFE141DA6,
	VEHICLE_HAULER2 = 0x171C92C4,
	VEHICLE_INSURGENT3 = 0x8D4B7A8A,
	VEHICLE_NIGHTSHARK = 0x19DD9ED1,
	VEHICLE_OPPRESSOR = 0x34B82784,
	VEHICLE_PHANTOM3 = 0x0A90ED5C,
	VEHICLE_TAMPA3 = 0xB7D9F7F1,
	VEHICLE_TECHNICAL3 = 0x50D4D19F,
	VEHICLE_TORERO = 0x59A9E570,
	VEHICLE_TRAILERS4 = 0xBE66F5AA,
	VEHICLE_TRAILERLARGE = 0x5993F939,
	VEHICLE_TRAILERSMALL2 = 0x8FD54EBB,
	VEHICLE_VAGNER = 0x7397224C,
	VEHICLE_XA21 = 0x36B4A8A9,

	// mpairraces 1.0.1180.2
	VEHICLE_ALPHAZ1 = 0xA52F6866,
	VEHICLE_BOMBUSHKA = 0xFE0A508C,
	VEHICLE_CYCLONE = 0x52FF9437,
	VEHICLE_HAVOK = 0x89BA59F5,
	VEHICLE_HOWARD = 0xC3F25753,
	VEHICLE_HUNTER = 0xFD707EDE,
	VEHICLE_MICROLIGHT = 0x96E24857,
	VEHICLE_MOGUL = 0xD35698EF,
	VEHICLE_MOLOTOK = 0x5D56F01B,
	VEHICLE_NOKOTA = 0x3DC92356,
	VEHICLE_PYRO = 0xAD6065C0,
	VEHICLE_RAPIDGT3 = 0x7A2EF5E4,
	VEHICLE_RETINUE = 0x6DBD6C0A,
	VEHICLE_ROGUE = 0xC5DD6967,
	VEHICLE_SEABREEZE = 0xE8983F9F,
	VEHICLE_STARLING = 0x9A9EB7DE,
	VEHICLE_TULA = 0x3E2E4F8A,
	VEHICLE_VIGILANTE = 0xB5EF4C33,
	VEHICLE_VISIONE = 0xC4810400,

	// mpchristmas2017 1.0.1290.1
	VEHICLE_AKULA = 0x46699F47,
	VEHICLE_BARRAGE = 0xF34DFB25,
	VEHICLE_CHERNOBOG = 0xD6BC7523,
	VEHICLE_DELUXO = 0x586765FB,
	VEHICLE_KHANJALI = 0xAA6F980A,
	VEHICLE_RIOT2 = 0x9B16A3B4,
	VEHICLE_STROMBERG = 0x34DBA661,
	VEHICLE_THRUSTER = 0x58CDAF30,
	VEHICLE_VOLATOL = 0x1AAD0DED,
	VEHICLE_HERMES = 0x00E83C17,
	VEHICLE_KAMACHO = 0xE9CEEDE7,
	VEHICLE_RIATA = 0xA4A4E453,
	VEHICLE_SENTINEL3 = 0x41D149AA,
	VEHICLE_STREITER = 0x67D2B389,
	VEHICLE_YOSEMITE = 0x6F946279,
	VEHICLE_AUTARCH = 0xED552C74,
	VEHICLE_AVENGER = 0x81BD2ED0,
	VEHICLE_AVENGER2 = 0x18606535,
	VEHICLE_COMET4 = 0x5D1903F9,
	VEHICLE_COMET5 = 0x276D98A3,
	VEHICLE_GT500 = 0x8408F33A,
	VEHICLE_HUSTLER = 0x23CA25F2,
	VEHICLE_NEON = 0x91CA96EE,
	VEHICLE_PARIAH = 0x33B98FE2,
	VEHICLE_RAIDEN = 0xA4D99B7D,
	VEHICLE_REVOLTER = 0xE78CC3D9,
	VEHICLE_SAVESTRA = 0x35DED0DD,
	VEHICLE_SC1 = 0x5097F589,
	VEHICLE_VISERIS = 0xE8A8BA94,
	VEHICLE_Z190 = 0x3201DD49,

	// b1365 Southern san andreas autos series
	VEHICLE_CARACARA = 0x4ABEBF23,
	VEHICLE_CHEBUREK = 0xC514AAE0,
	VEHICLE_DOMINATOR3 = 0xC52C6B93,
	VEHICLE_ELLIE = 0xB472D2B5,
	VEHICLE_ENTITY2 = 0x8198AEDC,
	VEHICLE_FAGALOA = 0x6068AD86,
	VEHICLE_FLASHGT = 0xB4F32118,
	VEHICLE_GB200 = 0x71CBEA98,
	VEHICLE_HOTRING = 0x42836BE5,
	VEHICLE_ISSI3 = 0x378236E1,
	VEHICLE_JESTER3 = 0xF330CB6A,
	VEHICLE_MICHELLI = 0x3E5BD8D9,
	VEHICLE_SEASPARROW = 0xD4AE63D9,
	VEHICLE_TAIPAN = 0xBC5DC07E,
	VEHICLE_TEZERACT = 0x3D7C6410,
	VEHICLE_TYRANT = 0xE99011C2,

	// b1495 After hours
	VEHICLE_PBUS2 = 0x149BD32A,
	VEHICLE_PATRIOT2 = 0xE6E967F8,
	VEHICLE_TERBYTE = 0x897AFC65,
	VEHICLE_POUNDER2 = 0x6290F15B,
	VEHICLE_MULE4 = 0x73F4110E,
	VEHICLE_MENACER = 0x79DD18AE,
	VEHICLE_OPPRESSOR2 = 0x7B54A9D3,
	VEHICLE_SCRAMJET = 0xD9F0503D,
	VEHICLE_STRIKEFORCE = 0x64DE07A1,
	VEHICLE_SWINGER = 0x1DD4C0FF,
	VEHICLE_STAFFORD = 0x1324E960,
	VEHICLE_FREECRAWLER = 0xFCC2F483,
	VEHICLE_BLIMP3 = 0xEDA4ED97,
	VEHICLE_SPEEDO4 = 0x0D17099D,

	// b1604 Arena battle
	VEHICLE_BRUISER = 0x27D79225,
	VEHICLE_BRUISER2 = 0x9B065C9E,
	VEHICLE_BRUISER3 = 0x8644331A,
	VEHICLE_BRUTUS = 0x7F81A829,
	VEHICLE_BRUTUS2 = 0x8F49AE28,
	VEHICLE_BRUTUS3 = 0x798682A2,
	VEHICLE_CERBERUS = 0xD039510B,
	VEHICLE_CERBERUS2 = 0x287FA449,
	VEHICLE_CERBERUS3 = 0x71D3B6F0,
	VEHICLE_CLIQUE = 0xA29F78B0,
	VEHICLE_DEATHBIKE = 0xFE5F0722,
	VEHICLE_DEATHBIKE2 = 0x93F09558,
	VEHICLE_DEATHBIKE3 = 0xAE12C99C,
	VEHICLE_DEVESTE = 0x5EE005DA,
	VEHICLE_DEVIANT = 0x4C3FFF49,
	VEHICLE_DOMINATOR4 = 0xD6FB0F30,
	VEHICLE_DOMINATOR5 = 0xAE0A3D4F,
	VEHICLE_DOMINATOR6 = 0xB2E046FB,
	VEHICLE_IMPALER = 0x83070B62,
	VEHICLE_IMPALER2 = 0x3C26BD0C,
	VEHICLE_IMPALER3 = 0x8D45DF49,
	VEHICLE_IMPALER4 = 0x9804F4C7,
	VEHICLE_IMPERATOR = 0x1A861243,
	VEHICLE_IMPERATOR2 = 0x619C1B82,
	VEHICLE_IMPERATOR3 = 0xD2F77E37,
	VEHICLE_ISSI4 = 0x256E92BA,
	VEHICLE_ISSI5 = 0x5BA0FF1E,
	VEHICLE_ISSI6 = 0x49E25BA1,
	VEHICLE_ITALIGTO = 0xEC3E3404,
	VEHICLE_MONSTER3 = 0x669EB40A,
	VEHICLE_MONSTER4 = 0x32174AFC,
	VEHICLE_MONSTER5 = 0xD556917C,
	VEHICLE_RCBANDITO = 0xEEF345EC,
	VEHICLE_SCARAB = 0xBBA2A2F7,
	VEHICLE_SCARAB2 = 0x5BEB3CE0,
	VEHICLE_SCARAB3 = 0xDD71BFEB,
	VEHICLE_SCHLAGEN = 0xE1C03AB0,
	VEHICLE_SLAMVAN4 = 0x8526E2F5,
	VEHICLE_SLAMVAN5 = 0x163F8520,
	VEHICLE_SLAMVAN6 = 0x67D52852,
	VEHICLE_TOROS = 0xBA5334AC,
	formula2 = 0x8B213907,
	VEHICLE_TULIP = 0x56D42971,
	VEHICLE_VAMOS = 0xFD128DFD,
	VEHICLE_ZR380 = 0x20314B42,
	VEHICLE_ZR3802 = 0xBE11EFC6,
	VEHICLE_ZR3803 = 0xA7DCC35C,

};

std::vector<VehBmpSprite> VehicleBmps{

	//lgm_dlc_casinoheist
	{ VEHICLE_FORMULA, "lgm_dlc_casinoheist", "formula"},
	{ formula2, "lgm_dlc_casinoheist", "formula2"},
	{ VEHICLE_FURIA,"lgm_dlc_casinoheist", "furia"},
	{ VEHICLE_IMORGON, "lgm_dlc_casinoheist", "imorgon"},
	{ VEHICLE_KOMODA, "lgm_dlc_casinoheist", "komoda"},
	{ VEHICLE_REBLA, "lgm_dlc_casinoheist", "rebla"},
	{ VEHICLE_STRYDER, "lgm_dlc_casinoheist", "stryder"},
	{ VEHICLE_VSTR, "lgm_dlc_casinoheist", "vstr"},

	//sssa_dlc_casinoheist
	{ VEHICLE_ASBO, "sssa_dlc_casinoheist", "asbo" },
	{ VEHICLE_EVERON, "sssa_dlc_casinoheist", "everon"},
	{ VEHICLE_KANJO , "sssa_dlc_casinoheist", "kanjo"},
	{ VEHICLE_OUTLAW, "sssa_dlc_casinoheist", "outlaw"},
	{ VEHICLE_RETINUE2, "sssa_dlc_casinoheist", "retinue2"},
	{ VEHICLE_SUGOI, "sssa_dlc_casinoheist", "sugoi"},
	{ VEHICLE_SULTAN2, "sssa_dlc_casinoheist", "sultan2"},
	{ VEHICLE_VAGRANT, "sssa_dlc_casinoheist", "vagrant"},
	{ VEHICLE_YOSEMITE2, "sssa_dlc_casinoheist", "yosemite2"},

	//candc_casinoheist
	{ VEHICLE_BLAZER2, "candc_casinoheist", "asbo" },
	{ VEHICLE_BOXVILLE, "candc_casinoheist", "everon"},
	{ VEHICLE_BURRITO2, "candc_casinoheist", "kanjo"},
	{ VEHICLE_FIRETRUK, "candc_casinoheist", "outlaw"},
	{ VEHICLE_JB7002, "candc_casinoheist", "retinue2"},
	{ VEHICLE_LGUARD, "candc_casinoheist", "sugoi"},
	{ VEHICLE_MINITANK, "candc_casinoheist", "sultan2"},
	{ VEHICLE_ZHABA, "candc_casinoheist", "vagrant"},
	{ VEHICLE_STOCKADE, "candc_casinoheist", "yosemite2"},
	///Casino
	{ VEHICLE_CARACARA2, "sssa_dlc_vinewood", "caracara2" },
			{ VEHICLE_DRAFTER, "lgm_dlc_vinewood", "drafter" },
			{ VEHICLE_DYNASTY, "sssa_dlc_vinewood", "dynasty"},
			{ VEHICLE_EMERUS, "lgm_dlc_vinewood", "emerus"},
			{ VEHICLE_GAUNTLET3, "sssa_dlc_vinewood", "gauntlet3"},
			{ VEHICLE_GAUNTLET4, "sssa_dlc_vinewood", "gauntlet4"},

			{ VEHICLE_HELLION, "sssa_dlc_vinewood", "hellion"},
			{ VEHICLE_ISSI7, "sssa_dlc_vinewood", "issi7"},
			{ VEHICLE_JUGULAR, "lgm_dlc_vinewood", "jugular"},
			{ VEHICLE_KRIEGER, "lgm_dlc_vinewood", "krieger"},

			{ VEHICLE_LOCUST, "lgm_dlc_vinewood", "locust"},
			{ VEHICLE_NEBULA, "sssa_dlc_vinewood", "nebula"},
			{ VEHICLE_NEO, "lgm_dlc_vinewood", "neo"},
			{ VEHICLE_NOVAK, "lgm_dlc_vinewood", "novak"},

			{ VEHICLE_PARAGON, "lgm_dlc_vinewood", "paragon"},

			{ VEHICLE_PARAGON2, "lgm_dlc_vinewood", "paragon2"},
			{ VEHICLE_PEYOTE2, "sssa_dlc_vinewood", "peyote2"},
			{ VEHICLE_RROCKET, "lgm_dlc_vinewood", "rrocket"},
			{ VEHICLE_S80, "lgm_dlc_vinewood", "s80"},
			{ VEHICLE_THRAX, "lgm_dlc_vinewood", "thrax"},
			{ VEHICLE_ZION3, "sssa_dlc_vinewood", "zion3"},
			{ VEHICLE_ZORRUSSO, "lgm_dlc_vinewood", "zorrusso"},


			{ VEHICLE_AIRBUS, "candc_default", "airbus" },
			{ VEHICLE_BARRACKS, "candc_default", "barracks" },
			{ VEHICLE_BOXVILLE4, "candc_default", "boxville4" },
			{ VEHICLE_BUS, "candc_default", "bus" },
			{ VEHICLE_BUZZARD, "candc_default", "buzzard" },
			{ VEHICLE_CARGOBOB, "candc_default", "cargobob" },
			{ VEHICLE_COACH, "candc_default", "coach" },
			{ VEHICLE_CRUSADER, "candc_default", "crusader" },
			{ VEHICLE_DUBSTA3, "candc_default", "dubsta3" },
			{ VEHICLE_DUKES2, "candc_default", "dukes" },
			{ VEHICLE_DUMP, "candc_default", "dump" },
			{ VEHICLE_HYDRA, "candc_default", "hydra" },
			{ VEHICLE_INSURGENT, "candc_default", "insurgent" },
			{ VEHICLE_INSURGENT2, "candc_default", "insurgent2" },
			{ VEHICLE_JOURNEY, "candc_default", "journey" },
			{ VEHICLE_MARSHALL, "candc_default", "marshall" },
			{ VEHICLE_MESA, "candc_default", "mesa" },
			{ VEHICLE_MESA3, "candc_default", "mesa3" },
			{ VEHICLE_MONSTER, "candc_default", "monster" },
			{ VEHICLE_MULE, "candc_default", "mule" },
			{ VEHICLE_MULE3, "candc_default", "mule3" },
			{ VEHICLE_PBUS, "candc_default", "pbus" },
			{ VEHICLE_RENTALBUS, "candc_default", "rentbus" },
			{ VEHICLE_RHINO, "candc_default", "rhino" },
			{ VEHICLE_SAVAGE, "candc_default", "savage" },
			{ VEHICLE_TECHNICAL, "candc_default", "technical" },
			{ VEHICLE_VALKYRIE, "candc_default", "valkyrie" },

			{ VEHICLE_DINGHY3, "dock_default", "dinghy3" },
			{ VEHICLE_JETMAX, "dock_default", "jetmax" },
			{ VEHICLE_MARQUIS, "dock_default", "marquis" },
			{ VEHICLE_SEASHARK, "dock_default", "seashark" },
			{ VEHICLE_SPEEDER, "dock_default", "speeder" },
			{ VEHICLE_SQUALO, "dock_default", "squalo" },
			{ VEHICLE_SUBMERSIBLE2, "dock_default", "sub2" },
			{ VEHICLE_SUNTRAP, "dock_default", "suntrap" },
			{ VEHICLE_TROPIC, "dock_default", "tropic" },

			{ VEHICLE_ANNIHILATOR, "elt_default", "annihl" },
			{ VEHICLE_CUBAN800, "elt_default", "cuban800" },
			{ VEHICLE_DODO, "elt_default", "dodo" },
			{ VEHICLE_DUSTER, "elt_default", "duster" },
			{ VEHICLE_FROGGER, "elt_default", "frogger" },
			{ VEHICLE_LUXOR, "elt_default", "luxor" },
			{ VEHICLE_MAMMATUS, "elt_default", "mammatus" },
			{ VEHICLE_MAVERICK, "elt_default", "maverick" },
			{ VEHICLE_SHAMAL, "elt_default", "shamal" },
			{ VEHICLE_STUNT, "elt_default", "stunt" },
			{ VEHICLE_TITAN, "elt_default", "titan" },
			{ VEHICLE_VELUM, "elt_default", "velum" },
			{ VEHICLE_VELUM2, "elt_default", "velum2" },

			{ VEHICLE_VESTRA, "elt_dlc_business", "vestra" },

			{ VEHICLE_LUXOR2, "elt_dlc_luxe", "luxor2" },
			{ VEHICLE_SWIFT2, "elt_dlc_luxe", "swift2" },

			{ VEHICLE_BESRA, "elt_dlc_pilot", "besra" },
			{ VEHICLE_MILJET, "elt_dlc_pilot", "miljet" },
			{ VEHICLE_SWIFT, "elt_dlc_pilot", "swift" },

			{ VEHICLE_ADDER, "lgm_default", "adder" },
			{ VEHICLE_BANSHEE, "lgm_default", "banshee" },
			{ VEHICLE_BULLET, "lgm_default", "bullet" },
			{ VEHICLE_CARBONIZZARE, "lgm_default", "carboniz" },
			{ VEHICLE_CARBONRS, "lgm_default", "carbon" },
			{ VEHICLE_CHEETAH, "lgm_default", "cheetah" },
			{ VEHICLE_COGCABRIO, "lgm_default", "cogcabri" },
			{ VEHICLE_COMET2, "lgm_default", "comet2" },
			{ VEHICLE_COQUETTE, "lgm_default", "coquette" },
			{ VEHICLE_ELEGY2, "lgm_default", "elegy2" },
			{ VEHICLE_ENTITYXF, "lgm_default", "entityxf" },
			{ VEHICLE_EXEMPLAR, "lgm_default", "exemplar" },
			{ VEHICLE_FELTZER2, "lgm_default", "feltzer" },
			{ VEHICLE_HOTKNIFE, "lgm_default", "hotknife" },
			{ VEHICLE_JB700, "lgm_default", "jb700" },
			{ VEHICLE_KHAMELION, "lgm_default", "khamel" },
			{ VEHICLE_MONROE, "lgm_default", "monroe" },
			{ VEHICLE_NEMESIS, "sssa_dlc_heist", "nemesis" },
			{ VEHICLE_NINEF, "lgm_default", "ninef" },
			{ VEHICLE_NINEF2, "lgm_default", "ninef2" },
			{ VEHICLE_RAPIDGT, "lgm_default", "rapidgt" },
			{ VEHICLE_RAPIDGT2, "lgm_default", "rapidgt2" },
			{ VEHICLE_STINGER, "lgm_default", "stinger" },
			{ VEHICLE_STINGERGT, "lgm_default", "stingerg" },
			{ VEHICLE_VOLTIC, "lgm_default", "voltic_tless" },
			{ VEHICLE_ZTYPE, "lgm_default", "ztype" },

			{ VEHICLE_ALPHA, "lgm_dlc_business", "alpha" },
			{ VEHICLE_JESTER, "lgm_dlc_business", "jester" },
			{ VEHICLE_TURISMOR, "lgm_dlc_business", "turismor" },

			{ VEHICLE_COQUETTE2, "lgm_dlc_pilot", "coquette2" },

			{ VEHICLE_HUNTLEY, "lgm_dlc_business2", "huntley" },
			{ VEHICLE_MASSACRO, "lgm_dlc_business2", "massacro" },
			{ VEHICLE_THRUST, "lgm_dlc_business2", "thrust" },
			{ VEHICLE_ZENTORNO, "lgm_dlc_business2", "zentorno" },

			{ VEHICLE_FUROREGT, "lgm_dlc_lts_creator", "furore" },

			{ VEHICLE_FELTZER3, "lgm_dlc_luxe", "feltzer3" },
			{ VEHICLE_OSIRIS, "lgm_dlc_luxe", "osiris" },
			{ VEHICLE_VIRGO, "lgm_dlc_luxe", "virgo" },
			{ VEHICLE_WINDSOR, "lgm_dlc_luxe", "windsor" },
			{ VEHICLE_BRAWLER, "lgm_dlc_luxe", "brawler" },
			{ VEHICLE_VINDICATOR, "lgm_dlc_luxe", "vindicator" },
			{ VEHICLE_CHINO, "lgm_dlc_luxe", "chino" },
			{ VEHICLE_COQUETTE3, "lgm_dlc_luxe", "coquette3" },
			{ VEHICLE_T20, "lgm_dlc_luxe", "t20" },

			{ VEHICLE_TORO, "dock_default", "toro" },

			{ VEHICLE_BMX, "pandm_default", "bmx" },
			{ VEHICLE_CRUISER, "pandm_default", "cruiser" },
			{ VEHICLE_SCORCHER, "pandm_default", "scorcher" },
			{ VEHICLE_TRIBIKE, "pandm_default", "tribike" },
			{ VEHICLE_TRIBIKE2, "pandm_default", "tribike2" },
			{ VEHICLE_TRIBIKE3, "pandm_default", "tribike3" },

			{ VEHICLE_AKUMA, "sssa_default", "akuma" },
			{ VEHICLE_BALLER, "sssa_default", "baller2" },
			{ VEHICLE_BATI, "sssa_default", "bati" },
			{ VEHICLE_BATI2, "sssa_default", "bati2" },
			{ VEHICLE_BFINJECTION, "sssa_default", "bfinject" },
			{ VEHICLE_BIFTA, "sssa_default", "bifta" },
			{ VEHICLE_BISON, "sssa_default", "bison" },
			{ VEHICLE_BLAZER, "sssa_default", "blazer" },
			{ VEHICLE_BODHI2, "sssa_default", "bodhi2" },
			{ VEHICLE_CAVALCADE, "sssa_default", "cavcade" },
			{ VEHICLE_DILETTANTE, "sssa_default", "dilettan" },
			{ VEHICLE_DOUBLE, "sssa_default", "double" },
			{ VEHICLE_DUNE, "sssa_default", "dune" },
			{ VEHICLE_FAGGIO2, "sssa_default", "faggio" },
			{ VEHICLE_FELON, "sssa_default", "felon" },
			{ VEHICLE_FELON2, "sssa_default", "felon2" },
			{ VEHICLE_FUGITIVE, "sssa_default", "fugitive" },
			{ VEHICLE_GAUNTLET, "sssa_default", "gauntlet" },
			{ VEHICLE_HEXER, "sssa_default", "hexer" },
			{ VEHICLE_INFERNUS, "sssa_default", "infernus" },
			{ VEHICLE_ISSI2, "sssa_default", "issi2" },
			{ VEHICLE_KALAHARI, "sssa_default", "kalahari" },
			{ VEHICLE_ORACLE, "sssa_default", "oracle" },
			{ VEHICLE_PARADISE, "sssa_default", "paradise" },
			{ VEHICLE_PCJ, "sssa_default", "pcj" },
			{ VEHICLE_REBEL, "sssa_default", "rebel" },
			{ VEHICLE_ROCOTO, "sssa_default", "rocoto" },
			{ VEHICLE_RUFFIAN, "sssa_default", "ruffian" },
			{ VEHICLE_SADLER, "sssa_default", "sadler" },
			{ VEHICLE_SANCHEZ, "sssa_default", "sanchez" },
			{ VEHICLE_SANCHEZ2, "sssa_default", "sanchez2" },
			{ VEHICLE_SANDKING, "sssa_default", "sandking" },
			{ VEHICLE_SANDKING2, "sssa_default", "sandkin2" },
			{ VEHICLE_SCHWARZER, "sssa_default", "schwarze" },
			{ VEHICLE_STRETCH, "sssa_default", "stretch" },
			{ VEHICLE_SUPERD, "lgm_default", "superd" },
			{ VEHICLE_SURANO, "lgm_default", "surano_convertable" },
			{ VEHICLE_VACCA, "lgm_default", "vacca" },
			{ VEHICLE_VADER, "sssa_default", "vader" },
			{ VEHICLE_VIGERO, "sssa_default", "vigero" },
			{ VEHICLE_ZION, "sssa_default", "zion" },
			{ VEHICLE_ZION2, "sssa_default", "zion2" },

			{ VEHICLE_ASEA, "sssa_dlc_business", "asea" },
			{ VEHICLE_ASTEROPE, "sssa_dlc_business", "astrope" },
			{ VEHICLE_BOBCATXL, "sssa_dlc_business", "bobcatxl" },
			{ VEHICLE_CAVALCADE2, "sssa_dlc_business", "cavcade2" },
			{ VEHICLE_INGOT, "sssa_dlc_business", "ingot" },
			{ VEHICLE_INTRUDER, "sssa_dlc_business", "intruder" },
			{ VEHICLE_MINIVAN, "sssa_dlc_business", "minivan" },
			{ VEHICLE_PREMIER, "sssa_dlc_business", "premier" },
			{ VEHICLE_RADI, "sssa_dlc_business", "radi" },
			{ VEHICLE_RANCHERXL, "sssa_dlc_business", "rancherx" },
			{ VEHICLE_STANIER, "sssa_dlc_business", "stanier" },
			{ VEHICLE_STRATUM, "sssa_dlc_business", "stratum" },
			{ VEHICLE_WASHINGTON, "sssa_dlc_business", "washingt" },
			{ VEHICLE_DOMINATOR, "sssa_dlc_business2", "dominato" },
			{ VEHICLE_F620, "sssa_dlc_business2", "f620" },
			{ VEHICLE_FUSILADE, "sssa_dlc_business2", "fusilade" },
			{ VEHICLE_PENUMBRA, "sssa_dlc_business2", "penumbra" },
			{ VEHICLE_SENTINEL, "sssa_dlc_business2", "sentinel" },

			{ VEHICLE_JESTER2, "sssa_dlc_christmas_2", "jester2" },
			{ VEHICLE_MASSACRO2, "sssa_dlc_christmas_2", "massacro2" },
			{ VEHICLE_RATLOADER2, "sssa_dlc_christmas_2", "rloader2" },
			{ VEHICLE_SLAMVAN, "sssa_dlc_christmas_2", "slamvan" },

			{ VEHICLE_ENDURO, "sssa_dlc_heist", "enduro" },
			{ VEHICLE_GBURRITO2, "sssa_dlc_heist", "gburrito2" },
			{ VEHICLE_GRESLEY, "sssa_dlc_heist", "gresley" },
			{ VEHICLE_JACKAL, "sssa_dlc_heist", "jackal" },
			{ VEHICLE_KURUMA, "sssa_dlc_heist", "kuruma" },
			{ VEHICLE_KURUMA2, "sssa_dlc_heist", "kuruma2" },
			{ VEHICLE_LANDSTALKER, "sssa_dlc_heist", "landstalker" },
			{ VEHICLE_RUMPO, "sssa_dlc_heist", "rumpo" },
			{ VEHICLE_SCHAFTER2, "sssa_dlc_heist", "schafter2" },
			{ VEHICLE_SEMINOLE, "sssa_dlc_heist", "seminole" },
			{ VEHICLE_SURGE, "sssa_dlc_heist", "surge" },

			{ VEHICLE_BLADE, "sssa_dlc_hipster", "blade" },
			{ VEHICLE_BLAZER3, "sssa_dlc_hipster", "blazer3" },
			{ VEHICLE_BUFFALO, "sssa_dlc_hipster", "buffalo" },
			{ VEHICLE_BUFFALO2, "sssa_dlc_hipster", "buffalo2" },
			{ VEHICLE_GLENDALE, "sssa_dlc_hipster", "glendale" },
			{ VEHICLE_PANTO, "sssa_dlc_hipster", "panto" },
			{ VEHICLE_PICADOR, "sssa_dlc_hipster", "picador" },
			{ VEHICLE_PIGALLE, "sssa_dlc_hipster", "pigalle" },
			{ VEHICLE_PRIMO, "sssa_dlc_hipster", "primo" },
			{ VEHICLE_REBEL2, "sssa_dlc_hipster", "rebel2" },
			{ VEHICLE_REGINA, "sssa_dlc_hipster", "regina" },
			{ VEHICLE_RHAPSODY, "sssa_dlc_hipster", "rhapsody" },
			{ VEHICLE_SURFER, "sssa_dlc_hipster", "surfer" },
			{ VEHICLE_TAILGATER, "sssa_dlc_hipster", "tailgater" },
			{ VEHICLE_WARRENER, "sssa_dlc_hipster", "warrener" },
			{ VEHICLE_YOUGA, "sssa_dlc_hipster", "youga" },

			{ VEHICLE_SOVEREIGN, "sssa_dlc_independence", "sovereign" },

			{ VEHICLE_HAKUCHOU, "sssa_dlc_lts_creator", "hakuchou" },
			{ VEHICLE_INNOVATION, "sssa_dlc_lts_creator", "innovation" },

			{ VEHICLE_BLISTA2, "sssa_dlc_mp_to_sp", "blista2" },
			{ VEHICLE_BUFFALO3, "sssa_dlc_mp_to_sp", "buffalo3" },
			{ VEHICLE_DOMINATOR2, "sssa_dlc_mp_to_sp", "dominator2" },
			{ VEHICLE_GAUNTLET2, "sssa_dlc_mp_to_sp", "gauntlet2" },
			{ VEHICLE_STALION, "sssa_dlc_mp_to_sp", "stallion" },
			{ VEHICLE_STALION2, "sssa_dlc_mp_to_sp", "stalion2" },

			{ VEHICLE_RATLOADER, "sssa_dlc_valentines", "rloader" },
			{ VEHICLE_BTYPE, "lgm_dlc_valentines", "roosevelt" },

			{ VEHICLE_CASCO, "lgm_dlc_heist", "casco" },
			{ VEHICLE_LECTRO, "lgm_dlc_heist", "lectro" },

			{ VEHICLE_BUCCANEER2, "lsc_default", "buccaneer2_b" },
			{ VEHICLE_BUCCANEER, "lsc_default", "buccaneer2" },
			{ VEHICLE_CHINO2, "lsc_default", "chino2_b" },
			{ VEHICLE_CHINO, "lsc_default", "chino2" },
			{ VEHICLE_FACTION, "lsc_default", "faction2_a" },
			{ VEHICLE_FACTION2, "lsc_default", "faction2_b" },
			{ VEHICLE_MOONBEAM, "lsc_default", "moonbeam2_a" },
			{ VEHICLE_MOONBEAM2, "lsc_default", "moonbeam2_b" },
			{ VEHICLE_PRIMO, "lsc_default", "primo2_a" },
			{ VEHICLE_PRIMO2, "lsc_default", "primo2_b" },
			{ VEHICLE_VOODOO2, "lsc_default", "voodoo_a" },
			{ VEHICLE_VOODOO, "lsc_default", "voodoo_b" },

			{ VEHICLE_BTYPE2, "sssa_dlc_halloween", "btype2" },
			{ VEHICLE_LURCHER, "sssa_dlc_halloween", "lurcher" },

			{ VEHICLE_SUPERVOLITO, "elt_dlc_apartments", "svolito" },
			{ VEHICLE_SUPERVOLITO2, "elt_dlc_apartments", "svolito2" },
			{ VEHICLE_LIMO2, "candc_apartments", "limo2" },
			{ VEHICLE_BALLER3, "lgm_dlc_apartments", "baller3" },
			{ VEHICLE_BALLER4, "lgm_dlc_apartments", "baller4" },
			{ VEHICLE_COG55, "lgm_dlc_apartments", "cog55" },
			{ VEHICLE_COGNOSCENTI, "lgm_dlc_apartments", "cognosc" },
			{ VEHICLE_COGNOSCENTI2, "lgm_dlc_apartments", "cognosc" },
			{ VEHICLE_MAMBA, "lgm_dlc_apartments", "mamba" },
			{ VEHICLE_NIGHTSHADE, "lgm_dlc_apartments", "niteshad" },
			{ VEHICLE_SCHAFTER3, "lgm_dlc_apartments", "schafter3" },
			{ VEHICLE_SCHAFTER4, "lgm_dlc_apartments", "schafter4" },
			{ VEHICLE_VERLIERER2, "lgm_dlc_apartments", "verlier" },
			{ VEHICLE_TAMPA, "sssa_dlc_christmas_3", "tampa" },

			{ VEHICLE_BANSHEE2, "lsc_jan2016", "banshee2" },
			{ VEHICLE_SULTANRS, "lsc_jan2016", "sultan2" },
			{ VEHICLE_BTYPE3, "lgm_dlc_valentines2", "roosevelt2" },

			//{ VEHICLE_FACTION, "lsc_lowrider2", "faction3_a" },
			{ VEHICLE_FACTION3, "lsc_lowrider2", "faction3_b" },
			//{ VEHICLE_MINIVAN, "lsc_lowrider2", "minivan2_a" },
			{ VEHICLE_MINIVAN2, "lsc_lowrider2", "minivan2_b" },
			{ VEHICLE_SABREGT, "lsc_lowrider2", "sabregt2_a" },
			{ VEHICLE_SABREGT2, "lsc_lowrider2", "sabregt2_b" },
			//{ VEHICLE_SLAMVAN, "lsc_lowrider2", "slamvan3_a" },
			{ VEHICLE_SLAMVAN3, "lsc_lowrider2", "slamvan3_b" },
			{ VEHICLE_TORNADO, "lsc_lowrider2", "tornado5_a" },
			{ VEHICLE_TORNADO5, "lsc_lowrider2", "tornado5_b" },
			//{ VEHICLE_VIRGO, "lsc_lowrider2", "virgo2_a" },
			{ VEHICLE_VIRGO2, "lsc_lowrider2", "virgo2_b" },

			{ VEHICLE_BESTIAGTS, "lgm_dlc_executive1", "bestiagts" },
			{ VEHICLE_FMJ, "lgm_dlc_executive1", "fmj" },
			{ VEHICLE_PFISTER811, "lgm_dlc_executive1", "pfister811" },
			{ VEHICLE_PROTOTIPO, "lgm_dlc_executive1", "prototipo" },
			{ VEHICLE_REAPER, "lgm_dlc_executive1", "reaper" },
			{ VEHICLE_SEVEN70, "lgm_dlc_executive1", "seven70" },
			{ VEHICLE_WINDSOR2, "lgm_dlc_executive1", "windsor2" },
			{ VEHICLE_XLS, "lgm_dlc_executive1", "xls" },
			{ VEHICLE_XLS2, "lgm_dlc_executive1", "xls" },
			{ VEHICLE_RUMPO3, "sssa_dlc_executive_1", "rumpo3" },
			{ VEHICLE_BRICKADE, "candc_executive1", "brickade" },
			{ VEHICLE_CARGOBOB2, "candc_executive1", "cargobob2" },
			{ VEHICLE_NIMBUS, "elt_dlc_executive1", "nimbus" },
			{ VEHICLE_VOLATUS, "elt_dlc_executive1", "volatus" },
			{ VEHICLE_TUG, "dock_dlc_executive1", "tug" },

			{ VEHICLE_LE7B, "lgm_dlc_stunt", "le7b" },
			{ VEHICLE_LYNX, "lgm_dlc_stunt", "lynx" },
			{ VEHICLE_SHEAVA, "lgm_dlc_stunt", "sheava" },
			{ VEHICLE_TYRUS, "lgm_dlc_stunt", "tyrus" },
			{ VEHICLE_BF400, "sssa_dlc_stunt", "bf400" },
			{ VEHICLE_BRIOSO, "sssa_dlc_stunt", "brioso" },
			{ VEHICLE_CLIFFHANGER, "sssa_dlc_stunt", "cliffhanger" },
			{ VEHICLE_CONTENDER, "sssa_dlc_stunt", "contender" },
			{ VEHICLE_GARGOYLE, "sssa_dlc_stunt", "gargoyle" },
			{ VEHICLE_OMNIS, "sssa_dlc_stunt", "omnis" },
			{ VEHICLE_RALLYTRUCK, "sssa_dlc_stunt", "rallytruck" },
			{ VEHICLE_TAMPA2, "sssa_dlc_stunt", "tampa2" },
			{ VEHICLE_TROHPYTRUCK, "sssa_dlc_stunt", "trophy" },
			{ VEHICLE_TROHPYTRUCK2, "sssa_dlc_stunt", "trophy2" },
			{ VEHICLE_TROPOS, "sssa_dlc_stunt", "tropos" },

			{ VEHICLE_HAKUCHOU2, "lgm_dlc_biker", "hakuchou2" },
			{ VEHICLE_RAPTOR, "lgm_dlc_biker", "raptor" },
			{ VEHICLE_SHOTARO, "lgm_dlc_biker", "shotaro" },
			{ VEHICLE_AVARUS, "sssa_dlc_biker", "avarus" },
			{ VEHICLE_BAGGER, "sssa_dlc_biker", "bagger" },
			{ VEHICLE_BLAZER4, "sssa_dlc_biker", "blazer4" },
			{ VEHICLE_CHIMERA, "sssa_dlc_biker", "chimera" },
			{ VEHICLE_DAEMON2, "sssa_dlc_biker", "daemon2" },
			{ VEHICLE_DEFILER, "sssa_dlc_biker", "defiler" },
			{ VEHICLE_ESSKEY, "sssa_dlc_biker", "esskey" },
			{ VEHICLE_FAGGIO3, "sssa_dlc_biker", "faggio3" },
			{ VEHICLE_FAGGION, "sssa_dlc_biker", "faggion" },
			{ VEHICLE_MANCHEZ, "sssa_dlc_biker", "manchez" },
			{ VEHICLE_NIGHTBLADE, "sssa_dlc_biker", "nightblade" },
			{ VEHICLE_RATBIKE, "sssa_dlc_biker", "ratbike" },
			{ VEHICLE_SANCTUS, "sssa_dlc_biker", "sanctus" },
			{ VEHICLE_TORNADO6, "sssa_dlc_biker", "tornado6" },
			{ VEHICLE_VORTEX, "sssa_dlc_biker", "vortex" },
			{ VEHICLE_WOLFSBANE, "sssa_dlc_biker", "wolfsbane" },
			{ VEHICLE_YOUGA2, "sssa_dlc_biker", "youga2" },
			{ VEHICLE_ZOMBIEA, "sssa_dlc_biker", "zombiea" },
			{ VEHICLE_ZOMBIEB, "sssa_dlc_biker", "zombieb" },

			{ VEHICLE_BLAZER5, "candc_importexport", "blazer5" },
			{ VEHICLE_BOXVILLE5, "candc_importexport", "boxville5" },
			{ VEHICLE_DUNE5, "candc_importexport", "dune5" },
			{ VEHICLE_PHANTOM2, "candc_importexport", "phantom2" },
			{ VEHICLE_RUINER2, "candc_importexport", "ruiner2" },
			{ VEHICLE_TECHNICAL2, "candc_importexport", "technical2" },
			{ VEHICLE_VOLTIC2, "candc_importexport", "voltic2" },
			{ VEHICLE_WASTLNDR, "candc_importexport", "wastlndr" },
			{ VEHICLE_PENETRATOR, "lgm_dlc_importexport", "penetrator" },
			{ VEHICLE_TEMPESTA, "lgm_dlc_importexport", "tempesta" },
			//{ VEHICLE_COMET2, "lsc_dlc_import_export", "comet3_a" },
			{ VEHICLE_COMET3, "lsc_dlc_import_export", "comet3_b" },
			{ VEHICLE_DIABLOUS, "lsc_dlc_import_export", "diablous2_a" },
			{ VEHICLE_DIABLOUS2, "lsc_dlc_import_export", "diablous2_b" },
			//{ VEHICLE_ELEGY2, "lsc_dlc_import_export", "elegy_a" },
			{ VEHICLE_ELEGY, "lsc_dlc_import_export", "elegy_b" },
			{ VEHICLE_FCR, "lsc_dlc_import_export", "fcr2_a" },
			{ VEHICLE_FCR2, "lsc_dlc_import_export", "fcr2_b" },
			{ VEHICLE_ITALIGTB, "lsc_dlc_import_export", "italigtb2_a" },
			{ VEHICLE_ITALIGTB2, "lsc_dlc_import_export", "italigtb2_b" },
			{ VEHICLE_NERO, "lsc_dlc_import_export", "nero2_a" },
			{ VEHICLE_NERO2, "lsc_dlc_import_export", "nero2_b" },
			{ VEHICLE_SPECTER, "lsc_dlc_import_export", "specter2_a" },
			{ VEHICLE_SPECTER2, "lsc_dlc_import_export", "specter2_b" },

			{ VEHICLE_GP1, "lgm_dlc_specialraces", "gp1" },
			{ VEHICLE_INFERNUS2, "lgm_dlc_specialraces", "infernus2" },
			{ VEHICLE_RUSTON, "lgm_dlc_specialraces", "ruston" },
			{ VEHICLE_TURISMO2, "lgm_dlc_specialraces", "turismo2" },

			{ VEHICLE_APC, "candc_gunrunning", "apc" },
			{ VEHICLE_ARDENT, "candc_gunrunning", "ardent" },
			{ VEHICLE_CADDY3, "foreclosures_bunker", "transportation_1" },
			{ VEHICLE_CHEETAH2, "lgm_dlc_gunrunning", "cheetah2" },
			{ VEHICLE_DUNE3, "candc_gunrunning", "dune3" },
			{ VEHICLE_HALFTRACK, "candc_gunrunning", "halftrack" },
			{ VEHICLE_HAULER2 , "candc_truck", "cab_1" },
			//{ VEHICLE_INSURGENT3, "", "insurgent3" },
			{ VEHICLE_NIGHTSHARK, "candc_gunrunning", "nightshark" },
			{ VEHICLE_OPPRESSOR, "candc_gunrunning", "oppressor" },
			//{ VEHICLE_PHANTOM3, "", "phantom3" },
			{ VEHICLE_TAMPA3, "candc_gunrunning", "tampa3" },
			//{ VEHICLE_TECHNICAL3, "", "technical3" },
			{ VEHICLE_TORERO, "lgm_dlc_gunrunning", "torero" },
			//{ VEHICLE_TRAILERS4, "", "" },
			//{ VEHICLE_TRAILERLARGE, "", "" },
			{ VEHICLE_TRAILERSMALL2, "candc_gunrunning", "trsmall2" },
			{ VEHICLE_VAGNER, "lgm_dlc_gunrunning", "vagner" },
			{ VEHICLE_XA21, "lgm_dlc_gunrunning", "xa21" },

			{ VEHICLE_HAULER2, "candc_truck", "cab_0" },
			{ VEHICLE_LAZER, "candc_smuggler", "lazer" },
			{ VEHICLE_BOMBUSHKA, "candc_smuggler","bombushka" },
			{ VEHICLE_HUNTER, "candc_smuggler","hunter" },
			{ VEHICLE_LAZER , "candc_smuggler","lazer" },
			{ VEHICLE_MOGUL , "candc_smuggler","mogul" },
			{ VEHICLE_MOLOTOK  , "candc_smuggler","molotok" },
			{ VEHICLE_NOKOTA, "candc_smuggler","nokota" },
			{ VEHICLE_PYRO  , "candc_smuggler","pyro" },
			{ VEHICLE_ROGUE , "candc_smuggler","rogue" },
			{ VEHICLE_STARLING , "candc_smuggler","starling" },
			{ VEHICLE_TULA  , "candc_smuggler","tula" },
			{ VEHICLE_VIGILANTE, "candc_smuggler","vigilante" },
			{ VEHICLE_CYCLONE  , "lgm_dlc_smuggler" , "cyclone" },
			{ VEHICLE_RAPIDGT3 , "lgm_dlc_smuggler" , "rapidgt3" },
			{ VEHICLE_VISIONE  , "lgm_dlc_smuggler" , "visione" },
			{ VEHICLE_RETINUE , "sssa_dlc_smuggler", "retinue" },
			{ VEHICLE_ALPHAZ1  , "elt_dlc_smuggler" , "alphaz1" },
			{ VEHICLE_HAVOK , "elt_dlc_smuggler" , "havok" },
			{ VEHICLE_HOWARD, "elt_dlc_smuggler" , "howard" },
			{ VEHICLE_MICROLIGHT   , "elt_dlc_smuggler" , "microlight" },
			{ VEHICLE_SEABREEZE, "elt_dlc_smuggler" , "seabreeze" },

			// b1290
			{ VEHICLE_AKULA, "candc_xmas2017", "akula" },
			{ VEHICLE_BARRAGE, "candc_xmas2017", "barrage" },
			{ VEHICLE_CHERNOBOG, "candc_xmas2017", "chernobog" },
			{ VEHICLE_DELUXO, "candc_xmas2017", "deluxo" },
			{ VEHICLE_KHANJALI, "candc_xmas2017", "khanjali" },
			{ VEHICLE_RIOT2, "candc_xmas2017", "riot2" },
			{ VEHICLE_STROMBERG, "candc_xmas2017", "stromberg" },
			{ VEHICLE_THRUSTER, "candc_xmas2017", "thruster" },
			{ VEHICLE_VOLATOL, "candc_xmas2017", "volatol" },
			{ VEHICLE_HERMES, "sssa_dlc_xmas2017", "hermes" },
			{ VEHICLE_KAMACHO, "sssa_dlc_xmas2017", "kamacho" },
			{ VEHICLE_RIATA, "sssa_dlc_xmas2017", "riata" },
			{ VEHICLE_SENTINEL3, "sssa_dlc_xmas2017", "sentinel3" },
			{ VEHICLE_STREITER, "sssa_dlc_xmas2017", "streiter" },
			{ VEHICLE_YOSEMITE, "sssa_dlc_xmas2017", "yosemite" },
			{ VEHICLE_AUTARCH, "sssa_dlc_xmas2017", "autarch" },
			{ VEHICLE_COMET4, "lgm_dlc_xmas2017", "comet4" },
			{ VEHICLE_COMET5, "lgm_dlc_xmas2017", "comet5" },
			{ VEHICLE_GT500, "lgm_dlc_xmas2017", "gt500" },
			{ VEHICLE_HUSTLER, "lgm_dlc_xmas2017", "hustler" },
			{ VEHICLE_NEON, "lgm_dlc_xmas2017", "neon" },
			{ VEHICLE_PARIAH, "lgm_dlc_xmas2017", "pariah" },
			{ VEHICLE_RAIDEN, "lgm_dlc_xmas2017", "raiden" },
			{ VEHICLE_REVOLTER, "lgm_dlc_xmas2017", "revolter" },
			{ VEHICLE_SAVESTRA, "lgm_dlc_xmas2017", "savestra" },
			{ VEHICLE_SC1, "lgm_dlc_xmas2017", "sc1" },
			{ VEHICLE_VISERIS, "lgm_dlc_xmas2017", "viseris" },
			{ VEHICLE_Z190, "lgm_dlc_xmas2017", "z190" },

			// b1365 Southern san andreas autos series
			{ VEHICLE_CARACARA, "candc_assault", "caracara" },
			{ VEHICLE_ENTITY2, "lgm_dlc_assault", "entity2" },
			{ VEHICLE_FLASHGT, "lgm_dlc_assault", "flashgt" },
			{ VEHICLE_GB200, "lgm_dlc_assault", "gb200" },
			{ VEHICLE_JESTER3, "lgm_dlc_assault", "jester3" },
			{ VEHICLE_TAIPAN, "lgm_dlc_assault", "taipan" },
			{ VEHICLE_TEZERACT, "lgm_dlc_assault", "tezeract" },
			{ VEHICLE_TYRANT, "lgm_dlc_assault", "tyrant" },
			{ VEHICLE_SEASPARROW, "elt_dlc_assault", "sparrow" },
			{ VEHICLE_CHEBUREK, "sssa_dlc_assault", "cheburek" },
			{ VEHICLE_DOMINATOR3, "sssa_dlc_assault", "dominator3" },
			{ VEHICLE_ELLIE, "sssa_dlc_assault", "ellie" },
			{ VEHICLE_FAGALOA, "sssa_dlc_assault", "fagaloa" },
			{ VEHICLE_HOTRING, "sssa_dlc_assault", "hotring" },
			{ VEHICLE_ISSI3, "sssa_dlc_assault", "issi3" },
			//{ VEHICLE_ISSI3, "mba_vehicles", "issi3" },
			{ VEHICLE_MICHELLI, "sssa_dlc_assault", "michelli" },

			// b1493 After hours
			{ VEHICLE_PBUS2, "sssa_dlc_battle", "pbus2" },
			{ VEHICLE_PATRIOT, "sssa_dlc_battle", "patriot" },
			{ VEHICLE_PATRIOT2, "sssa_dlc_battle", "patriot2" },
			{ VEHICLE_TERBYTE, "candc_hacker", "banner0" },
			{ VEHICLE_POUNDER2, "candc_battle", "pounder2" },
			{ VEHICLE_MULE4, "candc_battle", "mule4" },
			{ VEHICLE_MENACER, "candc_battle", "menacer" },
			{ VEHICLE_OPPRESSOR2, "candc_battle", "oppressor2" },
			{ VEHICLE_SCRAMJET, "candc_battle", "scramjet" },
			{ VEHICLE_STRIKEFORCE, "candc_battle", "strikeforce" },
			{ VEHICLE_SWINGER, "lgm_dlc_battle", "swinger" },
			{ VEHICLE_STAFFORD, "lgm_dlc_battle", "stafford" },
			{ VEHICLE_FREECRAWLER, "lgm_dlc_battle", "freecrawler" },
			{ VEHICLE_BLIMP3, "elt_dlc_battle", "blimp3" },
			//{ VEHICLE_SPEEDO4, "", "" },

			// b1604 Arena battle
			{ VEHICLE_BLISTA3, "sssa_dlc_arena", "blista3" },
			{ VEHICLE_BRUISER, "mba_vehicles", "bruiser_c_1" },
			{ VEHICLE_BRUISER2, "mba_vehicles", "bruiser_c_2" },
			{ VEHICLE_BRUISER3, "mba_vehicles", "bruiser_c_3" },
			{ VEHICLE_BRUTUS, "mba_vehicles", "brutus1" },
			{ VEHICLE_BRUTUS2, "mba_vehicles", "brutus2" },
			{ VEHICLE_BRUTUS3, "mba_vehicles", "brutus3" },
			{ VEHICLE_CERBERUS, "mba_vehicles", "cerberus1" },
			{ VEHICLE_CERBERUS2, "mba_vehicles", "cerberus2" },
			{ VEHICLE_CERBERUS3, "mba_vehicles", "cerberus3" },
			{ VEHICLE_CLIQUE, "lgm_dlc_arena", "clique" },
			{ VEHICLE_DEATHBIKE, "mba_vehicles", "deathbike_c_1" },
			{ VEHICLE_DEATHBIKE2, "mba_vehicles", "deathbike_c_2" },
			{ VEHICLE_DEATHBIKE3, "mba_vehicles", "deathbike_c_3" },
			{ VEHICLE_DEVESTE, "lgm_dlc_arena", "deveste" },
			{ VEHICLE_DEVIANT, "lgm_dlc_arena", "deviant" },
			{ VEHICLE_DOMINATOR4, "mba_vehicles", "dominato_c_1" },
			{ VEHICLE_DOMINATOR5, "mba_vehicles", "dominato_c_2" },
			{ VEHICLE_DOMINATOR6, "mba_vehicles", "dominato_c_3" },
			{ VEHICLE_IMPALER, "mba_vehicles", "impaler" },
			{ VEHICLE_IMPALER2, "mba_vehicles", "impaler_c_1" },
			{ VEHICLE_IMPALER3, "mba_vehicles", "impaler_c_2" },
			{ VEHICLE_IMPALER4, "mba_vehicles", "impaler_c_3" },
			{ VEHICLE_IMPERATOR, "mba_vehicles", "imperator1" },
			{ VEHICLE_IMPERATOR2, "mba_vehicles", "imperator2" },
			{ VEHICLE_IMPERATOR3, "mba_vehicles", "imperator3" },
			//{ VEHICLE_ISSI3, "mba_vehicles", "issi3" },
			{ VEHICLE_ISSI4, "mba_vehicles", "issi3_c_1" },
			{ VEHICLE_ISSI5, "mba_vehicles", "issi3_c_2" },
			{ VEHICLE_ISSI6, "mba_vehicles", "issi3_c_3" },
			{ VEHICLE_ITALIGTO, "lgm_dlc_arena", "italigto" },
			{ VEHICLE_MONSTER3, "mba_vehicles", "monster_c_1" },
			{ VEHICLE_MONSTER4, "mba_vehicles", "monster_c_2" },
			{ VEHICLE_MONSTER5, "mba_vehicles", "monster_c_3" },
			{ VEHICLE_RCBANDITO, "sssa_dlc_arena", "rcbandito" },
			{ VEHICLE_SCARAB, "mba_vehicles", "scarab1" },
			{ VEHICLE_SCARAB2, "mba_vehicles", "scarab2" },
			{ VEHICLE_SCARAB3, "mba_vehicles", "scarab3" },
			{ VEHICLE_SCHLAGEN, "lgm_dlc_arena", "schlagen" },
			{ VEHICLE_SLAMVAN4, "mba_vehicles", "slamvan_c_1" },
			{ VEHICLE_SLAMVAN5, "mba_vehicles", "slamvan_c_2" },
			{ VEHICLE_SLAMVAN6, "mba_vehicles", "slamvan_c_3" },
			{ VEHICLE_TOROS, "lgm_dlc_arena", "toros" },
			{ VEHICLE_TULIP, "sssa_dlc_arena", "tulip" },
			{ VEHICLE_VAMOS, "sssa_dlc_arena", "vamos" },
			{ VEHICLE_ZR380, "mba_vehicles", "zr3801" },
			{ VEHICLE_ZR3802, "mba_vehicles", "zr3802" },
			{ VEHICLE_ZR3803, "mba_vehicles", "zr3803" },
};

bool Menu::VehicleOption(std::string vehicle)
{
	char* op = &vehicle[0];
	float preBennerX = 0.80f;
	float preBennerY = 0.1775f;
	float VehBannerWidth123 = 0.13f;
	float VehBannerHeight123 = 0.13f;
	RGBA preBenner = { 34, 123, 76, 235 };

	float lineX123 = { Menu::Settings::menuX - 0.19f };
	float lineY123 = 0.32f;
	Menu::Option(op);
	if (Menu::Settings::optionCount == Menu::Settings::currentOption) {
		std::string pic[2] = { "**Invalid**", "**Invalid**" };
		for (auto p : VehicleBmps) {
			if (p.modelHash == GAMEPLAY::GET_HASH_KEY(op)) {
				pic[0] = p.dict;
				pic[1] = p.imgName;
				break;
			}
		}
		Menu::Vehicle(pic[0], pic[1]);
		if (Menu::Settings::selectPressed) {
			Menu::Drawing::Spriter(pic[0], pic[1], 0.70f, 0.1775f, Menu::Settings::menuXscale, 0.085f, 0, 255, 255, 255, 245);
			Drawing::Spriter("VehicleBanner", "VehicleBanner", Menu::Settings::menuX - 0.17f, 0.1f, VehBannerWidth123, VehBannerHeight123, 0, 255, 255, 255, 245);
			Drawing::Rect(Settings::line, { lineX123, lineY123 }, { 0.15f, 0.002f });
			//DrawSpriteeee(pic[0], pic[1], preBennerX, preBennerY, 0, RGBAA(255, 255, 255, 255));
			//GRAPHICS::DRAW_VEHICLE_SPRITE(pic[0], pic[1], 0.69f, 0.1675f, 0.424f, 0.72, 0, 255, 255, 255, 255);
			Features::autovehi(op);
			return true;
		}
	}
	return false;
}

//Veh preview ends here!
//-----------------------------------------------------------------------

void Menu::KeyboardText(const char* title)
{
	Drawing::Text(title, Settings::titleText, { Settings::KeyboardText, 0.25f }, { 0.35f, 0.35f }, true);
}

bool Menu::Option(const char* option)
{
	int curopt = Settings::currentOption;
	int optcnt = Settings::optionCount;
	int maxopt = Settings::maxVisOptions;
	Settings::optionCount++;
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	if (Settings::currentOption <= 11 && Settings::optionCount <= 11)
	{
		Drawing::Text(option, Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount) * 0.035f + 0.163f }, { 0.401f, 0.41f }, false);
		Drawing::Rect(Settings::optionRect, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.1768f }, { 0.22f, 0.035f });

		Drawing::Rect(Settings::optionRect, { Settings::scrollbarX, (Settings::optionCount) * 0.035f + 0.1768f }, { Settings::ScrollerWidth, 0.035f });//Scrollbar
		onThis ? Drawing::Rect(Settings::scroller, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.1768f }, { 0.22f, 0.035f }) :  NULL;
 
		onThis ? Drawing::Rect(Settings::scroller, { Settings::scrollbarX, (Settings::optionCount) * 0.035f + 0.1768f }, { 0.007f, 0.035f }) : NULL; //

	}
	else if (Settings::optionCount > (Settings::currentOption - 11) && Settings::optionCount <= Settings::currentOption)
	{
		Drawing::Text(option, Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.163f }, { 0.41f, 0.41f }, false);
		Drawing::Rect(Settings::optionRect, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.1768f }, { 0.22f, 0.035f });

		Drawing::Rect(Settings::optionRect, { Settings::scrollbarX, (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.1768f }, { Settings::ScrollerWidth, 0.035f });//Scrollabr

		onThis ? Drawing::Rect(Settings::scroller, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.1768f }, { 0.22f, 0.035f }) : NULL;

		onThis ? Drawing::Rect(Settings::scroller, { Settings::scrollbarX, (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.1768f }, { 0.007f, 0.035f }) : NULL;
	}

	if (onThis)
		animscroll(&prevOption, Settings::currentOption);
	if (Settings::currentOption == Settings::optionCount)
	{
		if (Settings::selectPressed)
		{
			return true;
		}
	}
	return false;
}


bool Menu::LoginTab1(const char* option)
{
	float ThisRectX = 0.5f;
	float ThisRectY = 0.45f;
	float ThisTextX = { ThisRectX + 0.035f };
	float ThisTextY = { ThisRectY };
		Drawing::Text(option, Settings::optionText, { ThisTextX, ThisTextY }, { 0.42f, 0.42f }, false);
		Drawing::Rect(Settings::LoginRect, { ThisRectX, ThisRectY }, { 0.20f, 0.035f });
	return false;
}

bool Menu::Break(const char* option)
{
	Settings::optionCount++;
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	if (Settings::currentOption <= 11 && Settings::optionCount <= 11)
	{
		Drawing::Text(option, Settings::count, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.162f }, { 0.40f, 0.40f }, true);
		Drawing::Rect(Settings::optionRect, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.1768f }, { Menu::Settings::menuXscale, 0.035f });

		Drawing::Rect(Settings::optionRect, { Settings::scrollbarX, (Settings::optionCount) * 0.035f + 0.1768f }, { Menu::Settings::ScrollerWidth, 0.035f });
		onThis ? Drawing::Rect(Settings::scroller, { Settings::scrollbarX, (Settings::optionCount) * 0.035f + 0.1768f }, { 0.007f, 0.035f }) : NULL;
	}
	else if (Settings::optionCount > (Settings::currentOption - 11) && Settings::optionCount <= Settings::currentOption)
	{
		Drawing::Text(option, Settings::count, { Settings::menuX, (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.162f }, { 0.40f, 0.40f }, true);
		Drawing::Rect(Settings::optionRect, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.1768f }, { Menu::Settings::menuXscale, 0.035f });

		Drawing::Rect(Settings::optionRect, { Settings::scrollbarX, (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.1768f }, { Menu::Settings::ScrollerWidth, 0.035f });
		onThis ? Drawing::Rect(Settings::scroller, { Settings::scrollbarX, (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.1768f }, { 0.007f, 0.035f }) : NULL;
	}
	return false;
}

bool Menu::MenuBreak(const char* breaktext)
{
	int DownPress = VK_DOWN;
	int NumDown = VK_NUMPAD2;
	int UpPress = VK_UP;
	int NumUp = VK_NUMPAD8;
	Settings::optionCount++;
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	if (Settings::currentOption <= 11 && Settings::optionCount <= 11)
	{
		Drawing::Text(breaktext, Settings::count, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.162f }, { 0.40f, 0.40f }, true); //Drawing menubreak - text
		Drawing::Rect(Settings::optionRect, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.1768f }, { Menu::Settings::menuXscale, 0.035f }); //Drawing menubreak - rect
		Drawing::Rect(Settings::optionRect, { Settings::scrollbarX, (Settings::optionCount) * 0.035f + 0.1768f }, { Settings::ScrollerWidth, 0.035f });//Scrollbar
		//Function to scroll
		if (onThis && GetAsyncKeyState(UpPress))
		{
			Settings::currentOption--;
		}
		if (onThis && GetAsyncKeyState(DownPress))
		{
			Settings::currentOption++;
		}
		if (onThis && GetAsyncKeyState(NumUp))
		{
			Settings::currentOption--;
		}
		if (onThis && GetAsyncKeyState(NumDown))
		{
			Settings::currentOption++;
		}
	}
	else if (Settings::optionCount > (Settings::currentOption - 11) && Settings::optionCount <= Settings::currentOption)
	{
		Drawing::Text(breaktext, Settings::count, { Settings::menuX, (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.162f }, { 0.40f, 0.40f }, true); //Drawing menubreak - text
		Drawing::Rect(Settings::optionRect, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.1768f }, { Menu::Settings::menuXscale, 0.035f }); //Drawing menubreak - rect
		Drawing::Rect(Settings::optionRect, { Settings::scrollbarX, (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.1768f }, { Settings::ScrollerWidth, 0.035f });//Scrollabr
		//Function to scroll
		if (onThis && GetAsyncKeyState(UpPress))
		{
			Settings::currentOption--;
		}
		if (onThis && GetAsyncKeyState(DownPress))
		{
			Settings::currentOption++;
		}
		if (onThis && GetAsyncKeyState(NumUp))
		{
			Settings::currentOption--;
		}
		if (onThis && GetAsyncKeyState(NumDown))
		{
			Settings::currentOption++;
		}
	}
	return false;
}

bool Menu::SmallTitle(const char* option)
{
	if (Settings::showSmalltitle);
	{

		Drawing::Text(option, Settings::count, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.164f }, { 0.40f, 0.40f }, true);
		Drawing::Rect(Settings::optionRect2, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.1775f }, { Menu::Settings::menuXscale, 0.035f });
		//Addon to scrollbar
		Drawing::Rect({ 0,0,0,220 }, { Settings::scrollbarX, (Settings::optionCount) * 0.035f + 0.1870f }, { Menu::Settings::ScrollerWidth, 0.015f });
		Drawing::Spriter("commonmenutu", "arrowleft", Settings::scrollbarX, ((Settings::optionCount) * 0.035f + 0.1870f), 0.008f, 0.012f, 90, Settings::arrow2.r, Settings::arrow2.g, Settings::arrow2.b, Settings::arrow2.a);
		//Drawing::Rect({ 0,0,0,245 }, { Settings::scrollbarX, ((Settings::optionCount + 1) * 0.0354f + 0.1715f) }, { Menu::Settings::menuXscale321, 0.035f });
	}
	return false;
}

bool Menu::MenuOption(const char* option, SubMenus newSub)
{
	Option(option);

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		//Drawing::Text("~w~>>", Menu::Settings::optionText, { Settings::menuX + 0.078f, (Settings::optionCount) * 0.035f + 0.160f }, { 0.45f, 0.45f }, true);
	    Drawing::Spriter("commonmenu", "arrowleft", Settings::menuX + 0.097f, (Settings::optionCount) * 0.035f + 0.178f, 0.014f, 0.026f, 180, Settings::arrow2.r, Settings::arrow2.g, Settings::arrow2.b, Settings::arrow2.a);
	    
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		//Drawing::Text("~w~>>", Menu::Settings::optionText, { Settings::menuX + 0.078f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.160f }, { 0.45f, 0.45f }, true);
	Drawing::Spriter("commonmenu", "arrowleft", Settings::menuX + 0.097f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.178f, 0.014f, 0.026f, 180, Settings::arrow2.r, Settings::arrow2.g, Settings::arrow2.b, Settings::arrow2.a);
	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) 
	{
		MenuLevelHandler::MoveMenu(newSub);
		return true;
	}
	return false;
}

bool Menu::MenuOption(const char* option, SubMenus newSub, std::function<void()> function)
{
	MenuOption(option, newSub);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	return false;
}

bool Menu::PlayerSub(const char* option, SubMenus newSub, int pid)
{
	char* GPic = "CHAR_MULTIPLAYER";
	int index = 1383710;
	for (int i = 0; i <= 150; i += 5)
	{
		__int64* base = globalHandle(index + i).Get<__int64>();
		int playerId = *base;
		if (playerId == pid)
		{
			__int64* logo = globalHandle(index + i + 1).Get<__int64>();
			GPic = PED::GET_PEDHEADSHOT_TXD_STRING(*logo);
			break;
		}
		if (playerId == -1)
			break;
	}
	Option(option);
	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Spriter(GPic, GPic, (Settings::menuX + 0.097f), (Settings::optionCount * 0.035f + 0.178f), 0.015f, 0.027f, 0, 255, 255, 255, 255);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Spriter(GPic, GPic, (Settings::menuX + 0.097f), ((Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.178f), 0.015f, 0.027f, 0, 255, 255, 255, 255);
	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		MenuLevelHandler::MoveMenu(newSub);
		return true;
	}
	return false;
}

bool Menu::Toggle(const char* option, bool& b00l)
{
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	Option(option);

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Spriter("mprankbadge", b00l ? "globe" : "globe", (Settings::menuX + 0.097f), (Settings::optionCount * 0.035f + 0.177f), 0.015f, 0.025f, 0, b00l ? 0 : 255, b00l ? 255 : 0, 0, 255);
	    //Drawing::Spriter("On", b00l ? "On" : "On", (Settings::menuX + 0.090f), (Settings::optionCount * 0.035f + 0.177f), 0.017f, 0.027f, 0, b00l ? 0 : 255, b00l ? 255 : 0, 0, 255);

	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Spriter("mprankbadge", b00l ? "globe" : "globe", (Settings::menuX + 0.097f), ((Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.177f), 0.015f, 0.025f, 0, b00l ? 0 : 255, b00l ? 255 : 0, 0, 255);
	    //Drawing::Spriter("Off", b00l ? "Off" : "Off", (Settings::menuX + 0.090f), ((Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.177f), 0.017f, 0.027f, 0, b00l ? 0 : 255, b00l ? 255 : 0, 0, 255);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		b00l ^= 1;
		return true;
	}
	return false;
}

bool Menu::Toggle(const char* option, bool& b00l, std::function<void()> function)
{
	Toggle(option, b00l);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	return false;
}

int NumInput() 
{
	WAIT(50);
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(1, "", "", "", "", "", "", 10);
	while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return 0;
	return atof(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
}

bool Menu::Int(const char* option, int& _int, int min, int max)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_int < max ? _int++ : _int = min;
		}
		if (Settings::rightPressed) {
			_int >= min ? _int-- : _int = max;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX + 0.097f, Settings::optionCount * 0.035f + 0.165f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX + 0.097f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.165f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

bool Menu::Int(const char* option, int& _int, int min, int max, int step)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_int < max ? _int += step : _int = min;
		}
		if (Settings::rightPressed) {
			_int >= min ? _int -= step : _int = max;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX + 0.097f, Settings::optionCount * 0.035f + 0.165f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX + 0.097f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.165f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

#pragma warning(disable: 4244)

bool Menu::Float(const char* option, float& _float, int min, int max)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_float <= min ? _float = max : _float -= 0.1f;
		}
		if (Settings::rightPressed) {
			_float >= max ? _float = min : _float += 0.1f;
		}
		_float < min ? _float = max : _float > max ? _float = min : NULL;
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.095f, Settings::optionCount * 0.035f + 0.165f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.095f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.165f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

bool Menu::Float(const char* option, float& _float, int min, int max, int step)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_float <= min ? _float = max : _float -= 0.1f;
		}
		if (Settings::rightPressed) {
			_float >= max ? _float = min : _float += 0.1f;
		}
		_float < min ? _float = max : _float > max ? _float = min : NULL;
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.095f, Settings::optionCount * 0.035f + 0.165f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.095f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.165f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

#pragma warning(default: 4244)

#pragma warning(disable: 4267)

bool Menu::IntVector(const char* option, std::vector<int> Vector, int& position)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		int max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

bool Menu::FloatVector(const char* option, std::vector<float> Vector, int& position)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

bool Menu::FloatVector(const char* option, std::vector<float> Vector, int& position, std::function<void()> function)
{
	FloatVector(option, Vector, position);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}

bool Menu::StringVector(const char* option, std::vector<std::string> Vector, int& position)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar((Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar((Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

bool Menu::StringVector(const char* option, std::vector<std::string> Vector, int& position, std::function<void()> function)
{
	StringVector(option, Vector, position);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}

bool Menu::StringVector(const char* option, std::vector<char*> Vector, int& position)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(((Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(((Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.12f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

#pragma warning(default: 4267)

bool Menu::StringVector(const char* option, std::vector<char*> Vector, int& position, std::function<void()> function)
{
	StringVector(option, Vector, position);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}

bool Menu::ListVector(const char* option, std::vector<char*> Vector, int& position)
{
	constexpr static const VECTOR2_2 textSize = { 0.45f, 0.45f };
	bool onThis = Settings::currentOption == Settings::optionCount + 1 ? true : false;
	Option("");

	if (Settings::optionCount == Settings::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (Settings::rightPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::leftPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions) {
		std::string SelectedChar
			= UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL($(Vector[position])));
		if (SelectedChar == "NULL") SelectedChar = Vector[position];

		UI::SET_TEXT_COLOUR(255, 255, 255, 255);
		UI::SET_TEXT_FONT(6);
		UI::SET_TEXT_SCALE(textSize.w, textSize.h);
		UI::SET_TEXT_CENTRE(false);
		if (Menu::Settings::DrawTextOutline) {
			UI::SET_TEXT_DROPSHADOW(1, 0, 0, 0, 0);
			UI::SET_TEXT_EDGE(1, 0, 0, 0, 0);
			UI::SET_TEXT_OUTLINE();
		}
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		std::string s = option;
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(Tools::StringToChar(s + " <<" + SelectedChar + ">>"));
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(Settings::menuX - 0.09f, Settings::optionCount * 0.035f + 0.125f);
	}
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption) {
		std::string SelectedChar
			= UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL($(Vector[position])));
		if (SelectedChar == "NULL") SelectedChar = Vector[position];

		UI::SET_TEXT_COLOUR(255, 255, 255, 255);
		UI::SET_TEXT_FONT(6);
		UI::SET_TEXT_SCALE(textSize.w, textSize.h);
		UI::SET_TEXT_CENTRE(false);
		UI::SET_TEXT_DROPSHADOW(1, 0, 0, 0, 0);
		UI::SET_TEXT_EDGE(1, 0, 0, 0, 0);
		UI::SET_TEXT_OUTLINE();
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		std::string s = option;
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(Tools::StringToChar(s + " <<" + SelectedChar + ">>"));
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(Settings::menuX - 0.09f, (Settings::optionCount - (Settings::currentOption - Settings::maxVisOptions)) * 0.035f + 0.125f);
	}

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return false;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return false;
	return false;
}

bool Menu::Teleport(const char* option, Vector3 coords)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		Entity handle;
		PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) ? handle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) : PLAYER::PLAYER_PED_ID();
		ENTITY::SET_ENTITY_COORDS(handle, coords.x, coords.y, coords.z, false, false, false, false);
		return true;
	}
	return false;
}

bool Menu::Teleport(const char* option, Vector3 coords, std::function<void()> function)
{
	Teleport(option, coords);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	return false;
}

void Menu::info(const char* info)
{
	if (Settings::currentOption <= 11 && Settings::optionCount <= 11)
	{
		if (bool onThis = true) { Drawing::Text(info, Settings::optionText, { Settings::menuX - 0.100f, 17 * 0.035f + 0.1600f }, { 0.25f, 0.25f }, false); }
	}
	else if (Settings::optionCount > (Settings::currentOption - 11) && Settings::optionCount <= Settings::currentOption)
	{
		if (bool onThis = true) { Drawing::Text(info, Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.1300f }, { 0.25f, 0.25f }, false); }
	}
}

void Menu::End()
{
	int opcount = Settings::optionCount;
	int currop = Settings::currentOption;

	if (opcount >= 11) 
	{
		Drawing::Text(Tools::StringToChar(std::to_string(currop) + " / " + std::to_string(opcount)), Settings::count, { Settings::menuX + 0.095f, 13 * 0.035f + 0.129f }, { 0.35f, 0.35f }, true);
		Drawing::Text("1.0", Menu::Settings::count, { Settings::menuX - 0.098f, 13 * 0.035f + 0.129f }, { 0.35f, 0.35f }, true);
		Drawing::Rect(Settings::optionRect2, { Settings::menuX, 13 * 0.035f + 0.1415f }, { 0.22f, 0.035f });
		Drawing::Rect(Settings::line, { Settings::menuX, 13 * 0.035f + 0.1235f }, { 0.22f, 0.00132f });
		//Drawing::Spriter("commonmenu", "shop_arrows_upanddown", Settings::menuX, ((11 + 2) * 0.035f + 0.142f), 0.020f, 0.035f, 180, Settings::count.r, Settings::count.g, Settings::count.b, Settings::count.a);
		Drawing::Spriter("Logo", "Logo", Settings::menuX, ((11 + 2) * 0.035f + 0.142f), 0.012f, 0.023f, 0, Settings::arrow2.r, Settings::arrow2.g, Settings::arrow2.b, Settings::arrow2.a);
		//Scrollbar Addon
		Drawing::Rect({ 0,0,0,220 }, { Settings::scrollbarX, ((11 + 1) * 0.035f + 0.1660f) }, { Menu::Settings::ScrollerWidth, 0.014f });//-------
		Drawing::Spriter("commonmenutu", "arrowleft", Settings::scrollbarX + 0.000021, ((11 + 1) * 0.035f + 0.1670f), 0.008f, 0.012f, -90, Settings::arrow2.r, Settings::arrow2.g, Settings::arrow2.b, Settings::arrow2.a);
	}
	else if (opcount > 0) 
	{
		Drawing::Text(Tools::StringToChar(std::to_string(currop) + " / " + std::to_string(opcount)), Settings::count, { Settings::menuX + 0.095f, (Settings::optionCount + 2) * 0.035f + 0.129f }, { 0.35f, 0.35f }, true);
		Drawing::Text("1.0", Menu::Settings::count, { Settings::menuX - 0.098f, (Settings::optionCount + 2) * 0.035f + 0.129f }, { 0.35f, 0.35f }, true);
		Drawing::Rect(Settings::optionRect2, { Settings::menuX, (Settings::optionCount + 2) * 0.035f + 0.1415f }, { 0.22f, 0.035f });
		Drawing::Rect(Settings::line, { Settings::menuX, (Settings::optionCount + 2) * 0.035f + 0.1235f }, { 0.22f, 0.00132f });
		//Drawing::Spriter("commonmenu", "shop_arrows_upanddown", Settings::menuX, ((Settings::optionCount + 2) * 0.035f + 0.142f), 0.020f, 0.035f, 180, Settings::count.r, Settings::count.g, Settings::count.b, Settings::count.a);
		//Drawing::Spriter("commonmenutu", "arrowleft", Settings::scrollbarX + 0.000011, ((Settings::optionCount + 2) * 0.035f + 0.175f), 0.008f, 0.012f, -90, Settings::arrow2.r, Settings::arrow2.g, Settings::arrow2.b, Settings::arrow2.a);
		Drawing::Spriter("Logo", "Logo", Settings::menuX, ((Settings::optionCount + 2) * 0.035f + 0.142f), 0.012f, 0.023f, 0, Settings::arrow2.r, Settings::arrow2.g, Settings::arrow2.b, Settings::arrow2.a);
		//Scrollbar Addon
		Drawing::Rect({ 0,0,0,220 }, { Settings::scrollbarX, ((Settings::optionCount + 1) * 0.035f + 0.1660f) }, { Menu::Settings::ScrollerWidth, 0.014f });//-------
		Drawing::Spriter("commonmenutu", "arrowleft", Settings::scrollbarX + 0.000021, ((Settings::optionCount + 1) * 0.035f + 0.1670f), 0.008f, 0.012f, -90, Settings::arrow2.r, Settings::arrow2.g, Settings::arrow2.b, Settings::arrow2.a);
	}
}

int IconNotification(char *text, char *text2, char *Subject)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG("CHAR_GANGAPP", "CHAR_GANGAPP", false, 7, text2, Subject, 1.0, "___Menu");
	return UI::_DRAW_NOTIFICATION(1, 1);
}

void PlaySoundFrontend_default(char* sound_name)
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, sound_name, "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
}

void PlaySoundFrontend_default2(char* sound_name)
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, sound_name, "DLC_HEIST_BIOLAB_PREP_HACKING_SOUNDS", 0);
}

int Menu::Settings::keyPressDelay = 200;
int Menu::Settings::keyPressPreviousTick = GetTickCount();
int Menu::Settings::keyPressDelay2 = 100;
int Menu::Settings::keyPressPreviousTick2 = GetTickCount();
int Menu::Settings::keyPressDelay3 = 140;
int Menu::Settings::keyPressPreviousTick3 = GetTickCount();
int Menu::Settings::openKey = VK_F8 && VK_MULTIPLY;
int Menu::Settings::backKey = VK_NUMPAD0;
int Menu::Settings::upKey = VK_NUMPAD8;
int Menu::Settings::downKey = VK_NUMPAD2;
int Menu::Settings::leftKey = VK_NUMPAD4;
int Menu::Settings::rightKey = VK_NUMPAD6;
int Menu::Settings::selectKey = VK_NUMPAD5;
int Menu::Settings::arrowupKey = VK_UP;
int Menu::Settings::arrowdownKey = VK_DOWN;
int Menu::Settings::arrowleftKey = VK_LEFT;
int Menu::Settings::arrowrightKey = VK_RIGHT;
int Menu::Settings::enterKey = VK_RETURN;
int Menu::Settings::deleteKey = VK_BACK;

#pragma endregion

bool Menu::Settings::controllerinput = true;

void Menu::Checks::Controlls()
{
	Settings::selectPressed = false;
	Settings::leftPressed = false;
	Settings::rightPressed = false;
	if (GetTickCount() - Settings::keyPressPreviousTick > Settings::keyPressDelay) {
	if (GetTickCount() - Settings::keyPressPreviousTick2 > Settings::keyPressDelay2) {
		if (GetTickCount() - Settings::keyPressPreviousTick3 > Settings::keyPressDelay3) {
			if (IsKeyPressed(VK_F8) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlScriptRB) && CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight) && Settings::controllerinput) {
				Settings::menuLevel == 0 ? MenuLevelHandler::MoveMenu(SubMenus::mainmenu) : Settings::menuLevel == 1 ? MenuLevelHandler::BackMenu() : NULL;
				Settings::keyPressPreviousTick = GetTickCount();
				PlaySoundFrontend_default("YES");
				prevOption = 1;
				//prevOptionnn = 1;
			}
			else if (IsKeyPressed(VK_NUMPAD0) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendCancel) && Settings::controllerinput) {
				Settings::menuLevel > 0 ? MenuLevelHandler::BackMenu() : NULL;
				if (Settings::menuLevel > 0)
					PlaySoundFrontend_default("BACK");
				//prevOptionnn = 1;
				Settings::keyPressPreviousTick = GetTickCount();
			}
			else if (IsKeyPressed(VK_NUMPAD8) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendUp) && Settings::controllerinput) {
				Settings::currentOption > 1 ? Settings::currentOption-- : Settings::currentOption = Settings::optionCount;
				if (Settings::menuLevel > 0)
					PlaySoundFrontend_default("NAV_UP_DOWN");

				Settings::keyPressPreviousTick2 = GetTickCount();
			}
			else if (IsKeyPressed(VK_NUMPAD2) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendDown) && Settings::controllerinput) {
				Settings::currentOption < Settings::optionCount ? Settings::currentOption++ : Settings::currentOption = 1;
				if (Settings::menuLevel > 0)
					PlaySoundFrontend_default("NAV_UP_DOWN");

				Settings::keyPressPreviousTick2 = GetTickCount();
			}
			else if (IsKeyPressed(VK_NUMPAD6) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight) && Settings::controllerinput) {
				Settings::leftPressed = true;
				if (Settings::menuLevel > 0)
					PlaySoundFrontend_default("NAV_UP_DOWN");

				Settings::keyPressPreviousTick3 = GetTickCount();
			}
			else if (IsKeyPressed(VK_NUMPAD4) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneLeft) && Settings::controllerinput) {
				Settings::rightPressed = true;
				if (Settings::menuLevel > 0)
					PlaySoundFrontend_default("NAV_UP_DOWN");

				Settings::keyPressPreviousTick3 = GetTickCount();
			}
			else if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept) && Settings::controllerinput) {
				Settings::selectPressed = true;
				if (Settings::menuLevel > 0)
					PlaySoundFrontend_default("SELECT");

				Settings::keyPressPreviousTick = GetTickCount();
			}
		}
	}
  }
	Settings::optionCount = 0;
}

#pragma warning(default : 4018)

void Menu::MenuLevelHandler::MoveMenu(SubMenus menu)
{
	Settings::menusArray[Settings::menuLevel] = Settings::currentMenu;
	Settings::optionsArray[Settings::menuLevel] = Settings::currentOption;
	Settings::menuLevel++;
	Settings::currentMenu = menu;
	Settings::currentOption = 1;
}

void Menu::MenuLevelHandler::BackMenu()
{
	Settings::menuLevel--;
	Settings::currentMenu = Settings::menusArray[Settings::menuLevel];
	Settings::currentOption = Settings::optionsArray[Settings::menuLevel];
}

char * Menu::Tools::StringToChar(std::string string)
{
	return _strdup(string.c_str());
}

void Menu::Files::WriteStringToIni(std::string string, std::string file, std::string app, std::string key)
{
	WritePrivateProfileStringA(app.c_str(), key.c_str(), string.c_str(), file.c_str());
}

std::string Menu::Files::ReadStringFromIni(std::string file, std::string app, std::string key)
{
	char buf[100];
	GetPrivateProfileStringA(app.c_str(), key.c_str(), "NULL", buf, 100, file.c_str());
	return (std::string)buf;
}

void Menu::Files::WriteIntToIni(int intValue, std::string file, std::string app, std::string key)
{
	WriteStringToIni(std::to_string(intValue), file, app, key);
}

int Menu::Files::ReadIntFromIni(std::string file, std::string app, std::string key)
{
	return std::stoi(ReadStringFromIni(file, app, key));
}

void Menu::Files::WriteFloatToIni(float floatValue, std::string file, std::string app, std::string key)
{
	WriteStringToIni((std::to_string(floatValue)), file, app, key);
}

float Menu::Files::ReadFloatFromIni(std::string file, std::string app, std::string key)
{
	return std::stof(ReadStringFromIni(file, app, key));
}

void Menu::Files::WriteBoolToIni(bool b00l, std::string file, std::string app, std::string key)
{
	WriteStringToIni(b00l ? "true" : "false", file, app, key);
}

bool Menu::Files::ReadBoolFromIni(std::string file, std::string app, std::string key)
{
	return ReadStringFromIni(file, app, key) == "true" ? true : false;
}

//Gohere

void Menu::Vehicle(std::string texture1, std::string texture2)
{
	float VehBannerWidth = 0.13f;
	float VehBannerHeight = 0.045f;

	float lineX = { Menu::Settings::menuX - 0.19f };
	float lineY = 0.2451f;
	if (Menu::Settings::menuX < 0.78f)
	{
		if (Menu::Settings::optionCount == Menu::Settings::currentOption) 
		{ 
			Menu::Drawing::Spriter(texture1, texture2, Menu::Settings::menuX - 0.19f, 0.1795f, 0.13f, 0.13f, 0, 255, 255, 255, 255);
			Drawing::Spriter("VehicleBanner", "VehicleBanner", Menu::Settings::menuX - 0.19f, 0.097f, VehBannerWidth, VehBannerHeight, 0, 255, 255, 255, 245);
			Drawing::Rect(Settings::line, { lineX, lineY }, { 0.13f, 0.004f });
		}
	}
	else 
	{ 
		if (Menu::Settings::optionCount == Menu::Settings::currentOption) 
		{ 
			Menu::Drawing::Spriter(texture1, texture2, Menu::Settings::menuX - 0.19f, 0.1795f, 0.13f, 0.13f, 0, 255, 255, 255, 255);
			Drawing::Spriter("VehicleBanner", "VehicleBanner", Menu::Settings::menuX - 0.19f, 0.097f, VehBannerWidth, VehBannerHeight, 0, 255, 255, 255, 245);
			Drawing::Rect(Settings::line, { lineX, lineY }, { 0.13f, 0.004f });
		} 
	}
}

void Menu::Speedometer(char* text)
{
	Drawing::Text(text, Settings::titleText, { 0.84f, 0.8800f }, { 0.70f, 0.70f }, false);
}

void Menu::fps(char* text)
{
	Drawing::Text(text, Settings::optionText, { 0.84f, 0.050f }, { 0.70f, 0.70f }, false);
}

void Menu::AddSmallTitle(char* text)
{
	if (Menu::Settings::menuX < 0.78f)
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX + 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("InfoBanner", "InfoBanner", Settings::menuX + 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);
		Drawing::Spriter("Logo", "Logo", Settings::menuX, 0.177f, 0.012f, 0.023f, 0, Settings::arrow2.r, Settings::arrow2.g, Settings::arrow2.b, Settings::arrow2.a);
	}
	else
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX - 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("InfoBanner", "InfoBanner", Settings::menuX - 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);
		Drawing::Spriter("Logo", "Logo", Settings::menuX, 0.177f, 0.012f, 0.023f, 0, Settings::arrow2.r, Settings::arrow2.g, Settings::arrow2.b, Settings::arrow2.a);
	}
}

void Menu::AddSmallInfo(char* text, short line)
{
	if (Menu::Settings::menuX < 0.78f)
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX + 0.175f, ((16 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 16 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX + 0.120f, (line * 0.030f) + 0.123f }, { 0.375f, 0.375f }, false);
	}
	else
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX - 0.175f, ((16 * 0.035f) / 2.0f) + 0.185f - 0.135f }, { 0.115f, 16 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX - 0.228f, (line * 0.020f) + 0.123f }, { 0.375f, 0.375f }, false);
	}
}

void Menu::DrawPlayerInfo(char* text, short line)
{
	//Variables
	float BottomW = 0.15f;
	float BottomH = 0.040f;
	float BottomX = { Settings::menuX - 0.185f };
	float BottomY = 0.3349f;
	RGBA backgroundColor = { 0,0,0, 150 };
	int KOKO = 1;
	if (Menu::Settings::menuX < 0.78f)
	{
		if (line == 1) 
		{
			Drawing::Rect(backgroundColor, { Settings::menuX - 0.185f, 0.3299f }, { 0.15f, 0.4f }); 
			Drawing::Spriter("PlayerInfo", "PlayerInfo", BottomX, BottomY, BottomW, BottomH, 0, KOKO, KOKO, KOKO, KOKO);
		}
		Drawing::Text(text, Settings::count, { Settings::menuX + 0.250f, (line * 0.030f) + 0.130f }, { 0.375f, 0.375f }, false);

	}
	else
	{
		if (line == 1) 
		{
			Drawing::Rect(backgroundColor, { Settings::menuX - 0.185f, 0.3299f }, { 0.15f, 0.4f });
			Drawing::Spriter("PlayerInfo", "PlayerInfo", BottomX, BottomY, BottomW, BottomH, 0, KOKO, KOKO, KOKO, KOKO);
		}
		Drawing::Text(text, Settings::count, { Settings::menuX - 0.250f, (line * 0.030f) + 0.130f }, { 0.375f, 0.375f }, false);

	}

}

void Menu::PrintWelcome(char* text, char* text1, char* text2)
{
	RGBA RectRGB = { 7, 84, 61, 200 };
	float RectX = 0.5f;
	float RectY = 0.9f;
	float RectH = 0.050f;
	float RectW = 5.5f;
	Drawing::Text(text, Settings::count, { 0.50f, 0.9f }, { 0.420f, 0.420f }, true);
	Drawing::Text(text1, Settings::count, { 0.50f, 0.9f }, { 0.420f, 0.420f }, true);
	Drawing::Text(text2, Settings::count, { 0.50f, 0.9f }, { 0.420f, 0.420f }, true);
	Menu::Drawing::Rect(RectRGB, { RectX , RectY }, { RectW , RectH });


}

void Menu::DrawPlayerBanner(char* text)
{
	//I like use variables hihihi
	float bannerX = { Settings::menuX - 0.185f };
	float bannerY = 0.1040f;
	float bannerW = 0.15f;
	float bannerH = 0.05f;
	float bannerR = 0;
	float LineH = 0.0015f;

	float BottomW = 0.15f;
	float BottomH = 0.035f;
	float BottomX = { Settings::menuX - 0.185f };
	float BottomY = 0.5470f;
	int KO = 255;
	RGBA BottomColor = { 0,0,0,240 };
	if (Menu::Settings::menuX < 0.78f)
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX + 0.185f, 0.090f }, { 0.425f, 0.425f }, true);
		//Drawing::Spriter("PlayerInfo", "PlayerInfo", Settings::menuX + 0.175f, 0.1175f - 0.019f, 0.15f, 0.05f, 0, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);
		Drawing::Spriter("PlayerInfo", "PlayerInfo", bannerX, bannerY, bannerW, bannerH, bannerR, KO, KO, KO, KO);
		Drawing::Rect(Settings::line, { bannerX, 0.1290f }, { bannerW, LineH });
		Drawing::Spriter("PlayerInfo", "PlayerInfo", BottomX, BottomY, BottomW, BottomH, 0, KO, KO, KO, KO); //bottom
		//Drawing::Rect(BottomColor, { bannerX, BottomY }, { bannerW, BottomH }); //here kappeno
	}
	else
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX - 0.185f, 0.090f }, { 0.425f, 0.425f }, true);
		//Drawing::Spriter("PlayerInfo", "PlayerInfo", Settings::menuX - 0.175f, 0.1175f - 0.019f, 0.15f, 0.05f, 0, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);
		Drawing::Spriter("PlayerInfo", "PlayerInfo", bannerX, bannerY, bannerW, bannerH, bannerR, KO, KO, KO, KO);
		Drawing::Rect(Settings::line, { bannerX, 0.1290f}, { bannerW, LineH });
		Drawing::Spriter("PlayerInfo", "PlayerInfo", BottomX, BottomY, BottomW, BottomH, 0, KO, KO, KO, KO); //bottom
		//Drawing::Rect(BottomColor, { bannerX, BottomY }, { bannerW, BottomH }); //here kappeno
	}
}

void Menu::AddSmallTitle2(char* text)
{
	if (Menu::Settings::menuX < 0.78f)
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX + 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX + 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);
	}
	else
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX - 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX - 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);
	}
}

void Menu::AddSmallInfo2(char* text, short line)
{
	if (Menu::Settings::menuX < 0.78f)
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX + 0.175f, ((13 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 13 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX + 0.120f, (line * 0.020f) + 0.123f }, { 0.375f, 0.375f }, false);
	}
	else
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX - 0.175f, ((13 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 13 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX - 0.228f, (line * 0.020f) + 0.123f }, { 0.375f, 0.375f }, false);
	}
}

void Menu::AddSmallTitle3(char* text)
{
	if (Menu::Settings::menuX < 0.78f)
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX + 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX + 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);
	}
	else
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX - 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX - 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);
	}
}

void Menu::AddSmallInfo3(char* text, short line) //U don't need to i'll doi it later
{
	if (Menu::Settings::menuX < 0.78f)
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX + 0.175f, ((11 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 11 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX + 0.120f, (line * 0.020f) + 0.123f }, { 0.375f, 0.375f }, false);
	}
	else
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX - 0.175f, ((11 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 11 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX - 0.228f, (line * 0.020f) + 0.123f }, { 0.375f, 0.375f }, false);
	}
}

//External custom gui stuff - new player info ;)

void Menu::DrawBoxTitle(char* title)
{
	Drawing::Text(title, Settings::titleText, { Settings::menuX - 0.240f, 0.100f }, { 0.425f, 0.425f }, true);
}

void Menu::DrawBoxLine(char* info, short line)
{
	float PosX = { Settings::menuX - 0.240f };
	float PosY = 0.1175f + 0.1725f;
	float BoxWidth = 0.20f;
	float Boxheight = 0.40f;
	RGBA BoxBG = { 0,0,0, 160 };
	RGBA backgroundColor = { 0,0,0, 160 };
	//Now draw
	if (Menu::Settings::menuX < 0.78f)
	{
		if (line == 1)
		{
			Drawing::Rect(Settings::optionRect, { PosX, PosY }, { BoxWidth, Boxheight });
		}
		Drawing::Text(info, Settings::optionText, { Settings::menuX - 0.420f, (line * 0.030f) + 0.130f }, { 0.37f, 0.37f }, false);

	}
	else
	{
		if (line == 1)
		{
			Drawing::Rect(Settings::optionRect, { PosX, PosY }, { BoxWidth, Boxheight });
			//Drawing::Rect(Settings::line, { PosX - 0.10f, PosY }, { 0.0015f, 9 * 0.030f }); //Good position for left side of box
			//Drawing::Rect(Settings::line, { PosX + 0.10f, PosY }, { 0.0015f, 9 * 0.030f }); //Good position for right side of box
		}
		Drawing::Text(info, Settings::count, { Settings::menuX - 0.420f, (line * 0.030f) + 0.130f }, { 0.375f, 0.375f }, false);

	}
}

void Menu::DrawBoxLineRight(char* info, short line)
{
	float PosX = { Settings::menuX - 0.240f };
	float PosY = 0.1175f + 0.1725f;
	float BoxWidth = 0.20f;
	float Boxheight = 0.40f;
	if (Menu::Settings::menuX < 0.78f)
	{
		if (line == 1)
		{
			Drawing::Rect(Settings::optionRect, { PosX, PosY }, { BoxWidth, Boxheight });
		}
		Drawing::Text(info, Settings::count, { Settings::menuX - 0.220f, (line * 0.030f) - 0.140f }, { 0.37f, 0.37f }, false);

	}
	else
	{
		if (line == 1)
		{
			Drawing::Rect(Settings::optionRect, { PosX, PosY }, { BoxWidth, Boxheight });
		}
		Drawing::Text(info, Settings::count, { Settings::menuX - 0.220f, (line * 0.030f) - 0.140f }, { 0.37f, 0.37f }, false);

	}
}

void Menu::DrawBoxLineRightSideSide(char* info, char* sidedtext,short line)
{
	float PosX = { Settings::menuX - 0.240f };
	float PosY = 0.1175f + 0.1725f;
	float BoxWidth = 0.20f;
	float Boxheight = 0.40f;
	float NormalTextPos = { Settings::menuX - 0.230f };
	float x_pos{};
	if (Menu::Settings::menuX < 0.78f)
	{
		if (line == 1)
		{
			Drawing::Rect(Settings::optionRect, { PosX, PosY }, { BoxWidth, Boxheight });
			Drawing::Rect(Settings::line, { PosX - 0.10f, PosY }, { 0.0015f, 9 * 0.030f }); //left side of box
            Drawing::Rect(Settings::line, { PosX + 0.10f, PosY }, { 0.0015f, 9 * 0.030f }); //right side of box
			Drawing::Rect(Settings::line, { PosX , PosY }, { 0.0015f, 9 * 0.030f });        //Center line
		}
		Drawing::Text(info, Settings::count, { Settings::menuX - 0.220f, (line * 0.030f) - 0.140f }, { 0.37f, 0.37f }, false);
		Drawing::PlayerInfoText(sidedtext, Settings::count, { Settings::menuX - 0.180f, (line * 0.030f) - 0.140f }, { 0.37f, 0.37f }, false, true);
	}
	else
	{
		if (line == 1)
		{
			Drawing::Rect(Settings::optionRect, { PosX, PosY }, { BoxWidth, Boxheight });
			Drawing::Rect(Settings::line, { PosX - 0.10f, PosY }, { 0.0015f, 9 * 0.030f }); //Good position for left side of box
            Drawing::Rect(Settings::line, { PosX + 0.10f, PosY }, { 0.0015f, 9 * 0.030f }); //Good position for right side of box
			Drawing::Rect(Settings::line, { PosX , PosY }, { 0.0015f, 9 * 0.030f });        //Center line
		}
		Drawing::Text(info, Settings::count, { NormalTextPos, (line * 0.030f) - 0.210f }, { 0.37f, 0.37f }, false);
		UI::SET_TEXT_WRAP(0.f, x_pos + 0.66f);
		Drawing::PlayerInfoText(sidedtext, Settings::count, { x_pos + 0.66f, (line * 0.030f) - 0.210f }, { 0.37f, 0.37f }, false, true);

	}
}

void Menu::DrawLeftToRightText(char* info, char* sidedtext, short line)
{
	float PosX = { Settings::menuX - 0.240f };
	float PosY = 0.1175f + 0.2020f;
	float BoxWidth = 0.20f;
	float Boxheight = 0.45f;
	float MainTextPos = { Settings::menuX - 0.330f };
	float x_pos{};
	float DownLineY = { (line * 0.030f) - 0.140f };
	if (Menu::Settings::menuX < 0.78f)
	{
		if (line == 1)
		{
			Drawing::Rect(Settings::optionRect, { PosX, PosY }, { BoxWidth, Boxheight });
			Drawing::Rect(Settings::line, { PosX - 0.10f, PosY }, { 0.0015f, 9 * 0.030f }); //Good position for left side of box
			Drawing::Rect(Settings::line, { PosX + 0.10f, PosY }, { 0.0015f, 9 * 0.030f }); //Good position for right side of box
			Drawing::Rect(Settings::line, { PosX , PosY }, { 0.0015f, 9 * 0.030f });        //Center line
		}
		Drawing::Text(info, Settings::count, { MainTextPos, (line * 0.030f) - 0.140f }, { 0.37f, 0.37f }, false);
		Drawing::PlayerInfoText(sidedtext, Settings::count, { Settings::menuX - 0.180f, DownLineY }, { 0.37f, 0.37f }, false, true);
	}
	else
	{
		if (line == 1)
		{
			Drawing::Rect(Settings::optionRect, { PosX, PosY }, { BoxWidth, Boxheight });
			Drawing::Rect(Settings::line, { PosX - 0.10f, PosY }, { 0.0015f, Boxheight });           //Left Line
			Drawing::Rect(Settings::line, { PosX + 0.10f, PosY }, { 0.0015f, Boxheight });           //Right Line
			Drawing::Rect(Settings::line, { PosX, PosY +  0.225f }, { BoxWidth, 0.0015f });          //Bottom Line
			Drawing::Rect(Settings::line, { PosX, PosY - 0.225f }, { BoxWidth, 0.0015f });           //Top Line
			Drawing::Rect(Settings::line, { PosX , PosY - 0.035f }, { 0.0015f, 9 * 0.030f });        //Center line
			Drawing::Rect(Settings::line, { PosX , PosY + 0.172f }, { 0.0015f, 3 * 0.025f });        //Center line [DOWN]

		}
		Drawing::Text(info, Settings::count, { MainTextPos, (line * 0.030f) + 0.150f }, { 0.37f, 0.37f }, false);
		UI::SET_TEXT_WRAP(0.f, x_pos + 0.56f);
		Drawing::PlayerInfoText(sidedtext, Settings::count, { x_pos + 0.56f, (line * 0.030f) + 0.150f }, { 0.37f, 0.37f }, false, true);
	}
}


//-----------------------

void Menu::RightTextDown(char* info, char* sidedtext, short line)
{
	float PosX = { Settings::menuX - 0.240f };
	float PosY = 0.1175f + 0.1725f;
	float BoxWidth = 0.20f;
	float Boxheight = 0.40f;
	float NormalTextPos = { Settings::menuX - 0.230f };
	float x_pos{};
	if (Menu::Settings::menuX < 0.78f)
	{
		if (line == 1)
		{
			Drawing::Rect(Settings::optionRect, { PosX, PosY }, { BoxWidth, Boxheight });
			Drawing::Rect(Settings::line, { PosX - 0.10f, PosY }, { 0.0015f, 9 * 0.030f }); //left side of box
			Drawing::Rect(Settings::line, { PosX + 0.10f, PosY }, { 0.0015f, 9 * 0.030f }); //right side of box
			Drawing::Rect(Settings::line, { PosX , PosY }, { 0.0015f, 9 * 0.030f });        //Center line
		}
		Drawing::Text(info, Settings::count, { Settings::menuX - 0.220f, (line * 0.030f) - 0.140f }, { 0.37f, 0.37f }, false);
		Drawing::PlayerInfoText(sidedtext, Settings::count, { Settings::menuX - 0.180f, (line * 0.030f) - 0.140f }, { 0.37f, 0.37f }, false, true);
	}
	else
	{
		if (line == 1)
		{
			Drawing::Rect(Settings::optionRect, { PosX, PosY }, { BoxWidth, Boxheight });
			Drawing::Rect(Settings::line, { PosX - 0.10f, PosY }, { 0.0015f, 9 * 0.030f }); //Good position for left side of box
			Drawing::Rect(Settings::line, { PosX + 0.10f, PosY }, { 0.0015f, 9 * 0.030f }); //Good position for right side of box
			Drawing::Rect(Settings::line, { PosX , PosY }, { 0.0015f, 9 * 0.030f });        //Center line
		}
		Drawing::Text(info, Settings::count, { NormalTextPos, (line * 0.030f) - 0.180f }, { 0.37f, 0.37f }, false);
		UI::SET_TEXT_WRAP(0.f, x_pos + 0.66f);
		Drawing::PlayerInfoText(sidedtext, Settings::count, { x_pos + 0.66f, (line * 0.030f) - 0.180f }, { 0.37f, 0.37f }, false, true);

	}
}

void Menu::LeftTextDown(char* info, char* sidedtext, short line)
{
	float PosX = { Settings::menuX - 0.240f };
	float PosY = 0.1275f + 0.1860f;
	float LineY = 0.1175 + 0.1750;
	float BoxWidth = 0.20f;
	float Boxheight = 0.45f;
	float MainTextPos = { Settings::menuX - 0.330f };
	float x_pos{};

	if (Menu::Settings::menuX < 0.78f)
	{
		if (line == 1)
		{
			Drawing::Rect(Settings::optionRect, { PosX, PosY }, { BoxWidth, Boxheight });
			Drawing::Rect(Settings::line, { PosX - 0.10f, PosY }, { 0.0015f, 9 * 0.030f });  //Good position for left side of box
			Drawing::Rect(Settings::line, { PosX + 0.10f, PosY }, { 0.0015f, 9 * 0.030f });  //Good position for right side of box
			Drawing::Rect(Settings::line, { PosX , LineY }, { 0.0015f, 9 * 0.030f });        //Center line
		}
		Drawing::Text(info, Settings::count, { MainTextPos, (line * 0.030f) - 0.140f }, { 0.37f, 0.37f }, false);
		Drawing::PlayerInfoText(sidedtext, Settings::count, { Settings::menuX - 0.180f, (line * 0.030f) - 0.140f }, { 0.37f, 0.37f }, false, true);
	}
	else
	{
		if (line == 1)
		{
			Drawing::Rect(Settings::optionRect, { PosX, PosY }, { BoxWidth, Boxheight });
			Drawing::Rect(Settings::line, { PosX - 0.10f, PosY }, { 0.0015f, 9 * 0.030f }); //Good position for left side of box
			Drawing::Rect(Settings::line, { PosX + 0.10f, PosY }, { 0.0015f, 9 * 0.030f }); //Good position for right side of box
			Drawing::Rect(Settings::line, { PosX , PosY - 0.030f }, { 0.0015f, 9 * 0.030f });        //Center line
		}
		Drawing::Text(info, Settings::count, { MainTextPos, (line * 0.030f) + 0.180f }, { 0.37f, 0.37f }, false);
		UI::SET_TEXT_WRAP(0.f, x_pos + 0.56f);
		Drawing::PlayerInfoText(sidedtext, Settings::count, { x_pos + 0.56f, (line * 0.030f) + 0.180f }, { 0.37f, 0.37f }, false, true);
	}
}


//-------------------CUSTOM INT OPTION

bool Menu::IntOption(const char* option, int& _int, int min, int max)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_int < max ? _int++ : _int = min;
		}
		if (Settings::rightPressed) {
			_int >= min ? _int-- : _int = max;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX + 0.097f, Settings::optionCount * 0.035f + 0.165f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX + 0.097f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.165f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

bool Menu::IntOption(const char* option, int& _int, int min, int max, int step)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_int < max ? _int += step : _int = min;
		}
		if (Settings::rightPressed) {
			_int >= min ? _int -= step : _int = max;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX + 0.097f, Settings::optionCount * 0.035f + 0.165f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX + 0.097f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.035f + 0.165f }, { 0.32f, 0.32f }, true);
	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}

bool Menu::IntOption(const char* option, int& _int, int min, int max, std::function<void()> function)
{
	Int(option, _int, min, max);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}

bool Menu::IntOption(const char* option, int& _int, int min, int max, int step, std::function<void()> function)
{
	Int(option, _int, min, max, step);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}

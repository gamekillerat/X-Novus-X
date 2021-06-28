#pragma once

enum SubMenus { //Add Sub Menus in here
	NOMENU,
	mainmenu,
	sub,
	settings,
	exitgta,
	settingstheme,
	Credits,
	themeloader,
	settingstitlerect,
	settingsscroller,
	settingsoptiontext,
	font,
	//My own here
	self_options,
	my_weapon,
	my_veh,
	teleport_options,
	world_options,
	network,
	recovery_options,
	modell_swap,
	misc_options,
	modder_protection,
	menu_settings,
	effects_me,
	Animation,
	weps,
	vehoptions,
	teleport,
	session,
	special_options,
	Mouevement_Type,
	Sport_Options,
	Sex_Options,
	Dance_Options,
	SuperHero_Options,
	Misc_OptionsAnims,
	weather,
	map_modsz,
	vehspawner,
	sport,
	coupes,
	arena,
	casino,
	playlist,
	onlineplayer_opt,
	player_tele,
	player_veh,
	player_weapon,
	player_drops,
	player_Troll,
	modell_change,
	misc,
	protections,
	ses_mgs,
	all_players,
	all_teleport,
	allP_teleport,
	player_tele_loc,
	obj_player,
	EXTRA_trolling,
	weather_online,
	recovery,
	adnv_recoverty,
	custom_look,
	men_outf,
	women_outf,
	lobby_weather,
	cha_na,
	pre_name,
	Moto_bikes,
	Boats,
	Planes,
	Helicopters_Car,
	super_cars,
	SCENARIOS,
	vis_play_me,
	veh_nitro,
	loopedPTfx,
	onlineLobbyWet,
	NewProtect,
	SpoofKill,
	new_tele,
	std_loc,
	online_loc,
	tower_loc,
	shop_loc,
	night_loc,
	port_lsc,
	Neons,
	out_create,
	network_list,
	lobby_rain,
	all_drops,
	remote_player,
	sess_time,
	Dev_Tools,
	rect_draw_tool,
};

extern enum SubMenus;

typedef struct VECTOR2 {
	float x, y;
};
typedef struct VECTOR2_2 {
	float w, h;
};
typedef struct RGBAF {
	int r, g, b, a, f;
};
typedef struct RGBA {
	int r, g, b, a;
};
typedef struct RGB {
	int r, g, b;
};
struct RGBAA {
	int r;
	int g;
	int b;
	int a;
	RGBAA(int red, int green, int blue, int alpha) {
		this->r = red;
		this->g = green;
		this->b = blue;
		this->a = alpha;
	}
};
namespace Menu {
	namespace Drawing {
		void Text(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center);
		void PlayerText(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center);
		void PlayerInfoText(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center, bool right);
		void coords(Vector3* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center);
		void LogoText(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center);
		void Title(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center);
		void Rect(RGBA rgba, VECTOR2 position, VECTOR2_2 size);
		void Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a);
	}
	namespace Settings {
		extern bool selectPressed;
		extern bool leftPressed;
		extern bool rightPressed; //displayScrollTop displayScrollEnd
		extern bool center;
		extern bool displayEnd;
		extern bool displayScrollTop;
		extern bool displayScrollEnd;
		extern bool showSmalltitle;
		extern bool controllerinput;
		extern bool SetupScroller;
		extern bool enable_smooth;
		//extern bool enable_scrollbar;
		extern int maxVisOptions;
		extern int currentOption;
		extern int optionCount;
		extern int scrollBarPos;
		extern SubMenus currentMenu;
		extern int menuLevel;
		extern int optionsArray[1000];
		extern SubMenus menusArray[1000];
		extern int cursorMenuX;
		extern int Hourfick;
		extern int Minufick;
		extern int secfick;

		extern float scrollbarX;
		extern float ScrollerSpeed;
		extern float menuX;
		extern float KeyboardText;
		extern float menuXscale;
		extern float ScrollerWidth;
		extern float menuXscale321;
		extern float ScrollerThing;
        extern RGBAF count;
		extern RGBAF titleText;
		extern RGBAF ultratitleText;
		extern RGBA titleRect;
		extern RGBAF breakText;
		extern RGBAF optionText;
		extern RGBA selectedText;
		extern RGBAF arrow;
		extern RGBAF integre;
		extern RGBA optionRect;
		extern RGBA LoginRect;
		extern RGBA optionRect123;
		extern RGBA ScrollerAddon;
		extern RGBA breakRect;
	    extern RGBA optionRect2;
		extern RGBA scroller;
		extern RGBA scroller123;
		extern RGBA line;
		extern RGBA arrow2;
		extern RGBA key;
		extern RGBA primary;
		extern RGBA secondary;
		extern bool DrawTextOutline;

		extern int keyPressDelay;
		extern int keyPressPreviousTick;
		extern int keyPressDelay2;
		extern int keyPressPreviousTick2;
		extern int keyPressDelay3;
		extern int keyPressPreviousTick3;
		extern int openKey;
		extern int backKey;
		extern int upKey;
		extern int downKey;
		extern int leftKey;
		extern int rightKey;
		extern int selectKey;
		extern int arrowupKey;
		extern int arrowdownKey;
		extern int arrowleftKey;
		extern int arrowrightKey;
		extern int enterKey;
		extern int deleteKey;
		extern int openpress;
		extern int downpress;
		extern int uppress;
		extern int backpress;
		extern int click;
		extern int leftpress;
		extern int rightpress;



	}
	namespace MenuLevelHandler {
		void MoveMenu(SubMenus menu);
		void BackMenu();
	}
	namespace Checks {
		void Controlls();
	}
	namespace Tools {
		char* StringToChar(std::string string);
	}
	namespace Files {
		void WriteStringToIni(std::string string, std::string file, std::string app, std::string key);
		std::string ReadStringFromIni(std::string file, std::string app, std::string key);
		void WriteIntToIni(int intValue, std::string file, std::string app, std::string key);
		int ReadIntFromIni(std::string file, std::string app, std::string key);
		void WriteFloatToIni(float floatValue, std::string file, std::string app, std::string key);
		float ReadFloatFromIni(std::string file, std::string app, std::string key);
		void WriteBoolToIni(bool b00l, std::string file, std::string app, std::string key);
		bool ReadBoolFromIni(std::string file, std::string app, std::string key);
	}

	void Title(const char* title);
	void OptionInfo(const char* infotext);
	void KeyboardText(const char* title);
	void notifymgs(const char* title);
	void PremiumTitle(const char* title);
	bool VehicleOption(std::string vehicle);
	void BUTTON2();
	void LOGO();
	void ScrollBar();
	void Subtitle(const char* title);
	void DrawGlare(float pX, float pY, float scaleX, float scaleY, int red, int green, int blue, int alpha);
	void info(const char * title);
	void Vehicle(std::string texture1, std::string texture2);
	void Speedometer(char* text);
	void fps(char* text);
	void coords(Vector3 text);
	void AddSmallTitle(char* text);
	void AddSmallInfo(char* text, short line);
	void AddSmallTitle2(char* text);
	void AddSmallInfo2(char* text, short line);
	void AddSmallTitle3(char* text);
	void AddSmallInfo3(char* text, short line);
	void PrintWelcome(char* text, char* text1, char* text2);
	//New info box
	void DrawPlayerInfo(char* text, short line);
	void DrawPlayerBanner(char* text);
	void DrawPlayerBox();
	void DrawBoxLine(char* text, short line);
	void DrawBoxLineRight(char* text, short line);
	void DrawBoxLineRightSideSide(char* info, char* sidedtext, short line);
	void RightTextDown(char* info, char* sidedtext, short line);
	void LeftTextDown(char* info, char* sidedtext, short line);
	void DrawLeftToRightText(char* info, char* sidedtext, short line);
	void DrawBoxTitle(char* title);
	//Ends here
	bool Break(const char* option);
	bool MenuBreak(const char* breaktext);
	bool Break22(const char* option);
	bool SmallTitle(const char* option);
	bool Option(const char* option);
	bool LoginTab1(const char* option);
	bool DirOption(const char* option);
	bool Option(const char* option, std::function<void()> function);
	bool MenuOption(const char* option, SubMenus newSub);
	bool MenuOption(const char* option, SubMenus newSub, std::function<void()> function);
	bool PlayerSub(const char* option, SubMenus newSub, int pid);
	bool Toggle(const char* option, bool& b00l);
	bool Toggle(const char* option, bool& b00l, std::function<void()> function);
	bool Int(const char* option, int& _int, int min, int max);
	bool Int(const char* option, int& _int, int min, int max, int step);
	bool Int(const char* option, int& _int, int min, int max, std::function<void()> function);
	bool Int(const char* option, int& _int, int min, int max, int step, std::function<void()> function);
	bool IntOption(const char* option, int& _int, int min, int max);
	bool IntOption(const char* option, int& _int, int min, int max, int step);
	bool IntOption(const char* option, int& _int, int min, int max, std::function<void()> function);
	bool IntOption(const char* option, int& _int, int min, int max, int step, std::function<void()> function);
	bool Float(const char* option, float& _float, int min, int max);
	bool Float(const char* option, float& _float, int min, int max);
	bool Float(const char* option, float& _float, int min, int max, int step);
	bool Float(const char* option, float& _float, int min, int max, float step);
	bool IntVector(const char* option, std::vector<int> Vector, int& position);
	bool IntVector(const char* option, std::vector<int> Vector, int& position, std::function<void()> function);
	bool FloatVector(const char* option, std::vector<float> Vector, int& position);
	bool FloatVector(const char* option, std::vector<float> Vector, int& position, std::function<void()> function);
	bool StringVector(const char* option, std::vector<std::string> Vector, int& position);
	bool StringVector(const char* option, std::vector<std::string> Vector, int& position, std::function<void()> function);
	bool StringVector(const char* option, std::vector<char*> Vector, int& position);
	bool StringVector(const char* option, std::vector<char*> Vector, int& position, std::function<void()> function);
	bool ListVector(const char* option, std::vector<char*> Vector, int& position);
	bool Teleport(const char* option, Vector3 coords);
	bool Teleport(const char* option, Vector3 coords, std::function<void()> function);
	void End();
	void AnimatedScroll();
	//YTD Import
	void BANNER();
	void ARROW();
	void PLAYERINFO();
	void PLATE();
	void NOTIFYICON();
}

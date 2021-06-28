#include "stdafx.h";

///KINDA A BACKUP

//#include "Auth/Networking/WinHttpClient.h"
//#include "Auth/Networking/Web2.0.h"
//
//HW_PROFILE_INFO hwProfileInfo;
//
//
///*
//
//TARGET WEBSITE: www.menu.com
//
//DEVELOPER: NiteDev
//---------------------------------------------
//ERROR CODES:
//---------------------------------------------
//
//0x0C53e = Empty HWID
//
//0x1C27e = Wrong HWID
//
//0x4C73F = Wrong Username or Password
//
//*/
//
//namespace EXTERNAL
//{
//	
//
//	const char* HWIDERROR = "";
//
//	void Notifycation(char* msg, char* title, char* Subject);
//	void DisableControls();
//	void EnableControls();
//	void Delay(DWORD MS);
//	char* DefultKeyboard(char* windowName, int maxInput = 25, char* defaultText = "");
//
//	namespace ADDON
//	{
//		bool CheckAuth = true;
//	}
//}
//
//void EXTERNAL::Notifycation(char* msg, char* title, char* Subject)
//{
//	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
//	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(msg);
//	UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG("CHAR_GANGAPP", "CHAR_GANGAPP", false, 7, title, Subject, 1.0, "Novus");
//	UI::_DRAW_NOTIFICATION(FALSE, FALSE);
//}
//
//void EXTERNAL::DisableControls()
//{
//	CONTROLS::DISABLE_CONTROL_ACTION(VK_F8, VK_F8, true);
//}
//
//void EXTERNAL::EnableControls()
//{
//	CONTROLS::ENABLE_CONTROL_ACTION(VK_F8, VK_F8, true);
//}
//
//void EXTERNAL::Delay(DWORD SEC)
//{
//	DWORD FULLSEC = SEC + 000;
//	WAIT(FULLSEC);
//}
//
//void BottomMSG(char* fmt, ...)
//{
//	char buf[2048] = { 0 };
//	va_list va_alist;
//
//	va_start(va_alist, fmt);
//	vsprintf_s(buf, fmt, va_alist);
//	va_end(va_alist);
//
//	char buff2[2048] = { 0 };
//	sprintf_s(buff2, "%s", buf);
//
//	UI::BEGIN_TEXT_COMMAND_PRINT("STRING");
//	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
//	UI::END_TEXT_COMMAND_PRINT(4000, 1);
//}
//void BottomMSG(std::string str)
//{
//	BottomMSG(&str[0]);
//}
//
//void SimpleMSG(char* fmt, ...)
//{
//	char buf[2048] = { 0 };
//	va_list va_alist;
//
//	va_start(va_alist, fmt);
//	vsprintf_s(buf, fmt, va_alist);
//	va_end(va_alist);
//
//	char buff2[2048] = { 0 };
//	sprintf_s(buff2, "%s", buf);
//
//	UI::SET_TEXT_OUTLINE();
//	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
//	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
//	UI::_DRAW_NOTIFICATION(FALSE, FALSE);
//}
//void SimpleMSG(std::string str)
//{
//	SimpleMSG(&str[0]);
//}
//
//char* DefultKeyboard(char* windowName, int maxInput = 25, char* defaultText = "")
//{
//	BottomMSG(windowName);
//	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(0, "", "", defaultText, "", "", "", maxInput);
//	while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
//	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return "";
//	return GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
//}
//
//std::wstring ZZZzzz(const std::string& str)
//{
//	using convert_typeX = std::codecvt_utf8<wchar_t>;
//	std::wstring_convert<convert_typeX, wchar_t> converterX;
//	return converterX.from_bytes(str);
//}
//
//void GetURLResponde()
//{
//	//if (GetCurrentHwProfile(&hwProfileInfo) != NULL)
//	//{
//	//	wchar_t* hwidproc = hwProfileInfo.szHwProfileGuid;
//	//	wstring hwidc(hwidproc);
//
//	//	if (hwidc.empty())
//	//	{
//	//		Log::Msg("[EHD], [0x0C53e]");
//	//		EXTERNAL::Notifycation("Empty HWID", "Novus", "~r~ERROR - 0x0C53e");
//	//		SimpleMSG("Try again in 5 sec...", "Novus", "~r~ERROR");
//	//		EXTERNAL::DisableControls();
//	//		EXTERNAL::Delay(5000);
//	//		GetURLResponde();
//	//	}
//
//	//	//Grab their HWID and send it to Web URL
//	//	string hwidPro(hwidc.begin(), hwidc.end());
//	//	char* hwidfinal = new char[hwidPro.size() + 1]; // +1 to account for \0 byte
//	//	*hwidfinal = '\0';
//	//	strncat(hwidfinal, hwidPro.c_str(), hwidPro.size());
//	//	TCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
//	//	DWORD size = sizeof(computerName) / sizeof(computerName[0]);
//	//	GetComputerName(computerName, &size);
//	//	wstring test(&computerName[0]); //convert to wstring
//	//	string test2(test.begin(), test.end());
//	//	char* compName = new char[test2.size() + 1];
//	//	*compName = '\0';
//	//	strncat(compName, test2.c_str(), test2.size());
//
//
//
//	//	char* combinedHwid = new char[strlen(hwidfinal) + strlen(compName) + 1];
//	//	*combinedHwid = '\0';
//	//	strcat(combinedHwid, compName);
//	//	strcat(combinedHwid, hwidfinal);
//
//	//	string Username = DefultKeyboard("", 25, "");
//	//	string Password = DefultKeyboard("", 25, "");
//	//	char* username = new char[Username.length() + 1];
//	//	strcpy(username, Username.c_str());
//	//	delete[] username;
//
//	//	char* password = new char[Password.length() + 1];
//	//	strcpy(password, Password.c_str());
//	//	delete[] password;
//
//	//	
//	//	WinHttpClient hwidclient(FinalAuthLink);
//	//	hwidclient.SetRequireValidSslCertificates(true);
//
//
//	//	hwidclient.SendHttpRequest();
//	//	std::wstring hwidresponse = hwidclient.GetResponseContent();
//	//	std::wstring const str = hwidresponse.c_str();
//
//
//	//	using convert_type = std::codecvt_utf8<wchar_t>;
//	//	std::wstring_convert<convert_type, wchar_t> converter;
//
//	//	//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
//	//	std::string converted_str = converter.to_bytes(str);
//	//	char* cstr2 = new char[converted_str.length() + 1];
//	//	strcpy(cstr2, converted_str.c_str());
//	//	delete[] cstr2;
//
//	//	if (converted_str.find("true") == 0 && converted_str.find("standard"))
//	//	{
//	//		EXTERNAL::ADDON::CheckAuth == false;
//	//		EXTERNAL::EnableControls();
//	//		char WelcomeText[100];
//	//		sprintf(WelcomeText, "Welcome to ~g~Novus MENU~w~ %s", Username);
//	//		EXTERNAL::Notifycation(WelcomeText, "Novus", "STANDARD - v1.0");
//	//		EXTERNAL::Notifycation("Open the menu with F8", "Novus", "CONTROLS");
//	//		NULL;
//	//	}
//	//	else
//	//	{
//	//		Log::Msg("[ICL], [0x4C73F]");
//	//		EXTERNAL::Notifycation("Your Username or Password was wrong!", "Novus", "~r~ERROR - 0x4C73F");
//	//		SimpleMSG("Try again in 3 sec...");
//	//		EXTERNAL::DisableControls();
//	//		EXTERNAL::Delay(3000);
//	//		GetURLResponde();
//	//	}
//	//}
//}

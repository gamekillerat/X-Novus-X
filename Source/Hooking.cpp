//Hooking.cpp
#pragma once
#include "stdafx.h"


using namespace Memory;

ScriptThread*(*GetActiveThread)() = nullptr;
HMODULE _hmoduleDLL;
HANDLE mainFiber;
DWORD wakeAt;

std::vector<LPVOID>		Hooking::m_hooks;
uint64_t*				Hooking::m_frameCount;
fpIsDLCPresent			Hooking::is_DLC_present;
SetSessionWeather       Hooking::set_session_weather;
SetOPNetworkWeather     Hooking::set_network_weather;
fpStatSetInt            Hooking::stat_set_int;
static eGameState* 											m_gameState;
static uint64_t												m_worldPtr;
static BlipList*											m_blipList;
fpCNetworkIncrementStatEvent		Hooking::m_CNetworkIncrementStatEventt;
static Hooking::NativeRegistrationNew**						m_registrationTable;
static std::unordered_map<uint64_t, Hooking::NativeHandler>	m_handlerCache;
fpGetPlayerName			Hooking::get_player_name;
static std::vector<LPVOID>									m_hookedNative;
static __int64**                                            m_globalPtr;
fpGetEventData          Hooking::get_script_event_data;
fpGetLabelText          Hooking::GetLabelText = nullptr;
static fpGetEventData											get_script_event_data;

const int EVENT_COUNT = 78;
static std::vector<void*> EventPtr;
static char EventRestore[EVENT_COUNT] = {};
char* Hooking::loading_text = "Joining Online With Novus";
static HANDLE scriptFiber;


//New hooking names ;)
addOwnedExplosion                       Hooking::add_owned_explosion;
twoBytes*                               Hooking::m_ownedExplosionBypass;
fpGetWaypointPos		                Hooking::get_waypoint_pos;
fpNetworkIsSessionStarted			    Hooking::network_is_session_started;
Trigger_Script_Event__	                Hooking::trigger_script_event;
clockTime*                              Hooking::ClockTime;
fpSetSessionTime                        Hooking::set_session_time_info;
/* Start Hooking */
void Hooking::Start(HMODULE hmoduleDLL)
{
	_hmoduleDLL = hmoduleDLL;
	Log::Init(hmoduleDLL);
	FindPatterns();
	if (!InitializeHooks()) Cleanup();
}


BOOL Hooking::InitializeHooks()
{
	BOOL returnVal = TRUE;

	if (!iHook.Initialize()) {

		Log::Error("Failed to initialize InputHook");
		returnVal = FALSE;
	}

	if (MH_Initialize() != MH_OK) {
		Log::Error("MinHook failed to initialize");
		returnVal = FALSE;
	}

	if (!HookNatives()) {

		Log::Error("Failed to initialize NativeHooks");
		returnVal = FALSE;
	}

	return returnVal;
}

template <typename T>
bool Native(DWORD64 hash, LPVOID hookFunction, T** trampoline)
{
	if (*reinterpret_cast<LPVOID*>(trampoline) != NULL)
		return true;
	auto originalFunction = Hooking::GetNativeHandler(hash);
	if (originalFunction != 0) {
		MH_STATUS createHookStatus = MH_CreateHook(originalFunction, hookFunction, reinterpret_cast<LPVOID*>(trampoline));
		if (((createHookStatus == MH_OK) || (createHookStatus == MH_ERROR_ALREADY_CREATED)) && (MH_EnableHook(originalFunction) == MH_OK))
		{
			m_hookedNative.push_back((LPVOID)originalFunction);
			DEBUGMSG("Hooked Native 0x%#p", hash);
			return true;
		}
	}

	return false;
}

uint64_t CMetaData::m_begin = 0;
uint64_t CMetaData::m_end = 0;
DWORD CMetaData::m_size = 0;

uint64_t CMetaData::begin()
{
	return m_begin;
}
uint64_t CMetaData::end()
{
	return m_end;
}
DWORD CMetaData::size()
{
	return m_size;
}

void CMetaData::init()
{
	if (m_begin && m_size)
		return;

	m_begin = (uint64_t)GetModuleHandleA(nullptr);
	const IMAGE_DOS_HEADER*	headerDos = (const IMAGE_DOS_HEADER*)m_begin;
	const IMAGE_NT_HEADERS*	headerNt = (const IMAGE_NT_HEADERS64*)((const BYTE*)headerDos + headerDos->e_lfanew);
	m_size = headerNt->OptionalHeader.SizeOfCode;
	m_end = m_begin + m_size;
	return;
}
fpIsDLCPresent	OG_IS_DLC_PRESENT = nullptr;
BOOL __cdecl HK_IS_DLC_PRESENT()
{
	static uint64_t	last = 0;
	uint64_t		cur = *Hooking::m_frameCount;
	if (last != cur)
	{
		last = cur;
		Hooking::onTickInit();
	}
	return OG_IS_DLC_PRESENT();
}
Hooking::NativeHandler ORIG_WAIT = NULL;
void* __cdecl MY_WAIT(NativeContext *cxt)
{
	static int lastThread = 0;
	int threadId = SCRIPT::GET_ID_OF_THIS_THREAD();
	if (!lastThread)
	{
		char* name = SCRIPT::_GET_NAME_OF_THREAD(threadId);
		if (strcmp(name, "main_persistent") == 0)
		{
			lastThread = threadId;
			Log::Msg("Hooked Script NAME: %s ID: %i", name, threadId);
		}
	}
	if (threadId == lastThread) Hooking::onTickInit();
	ORIG_WAIT(cxt);
	return cxt;
}

Hooking::NativeHandler  ORIG_NETWORK_SESSION_KICK_PLAYER = NULL;
void *__cdecl MY_NETWORK_SESSION_KICK_PLAYER(NativeContext* cxt)
{
	Player player = cxt->GetArgument<int>(0);
	if (player == PLAYER::PLAYER_ID())
	{
		ORIG_NETWORK_SESSION_KICK_PLAYER(cxt);
	}
	return nullptr;
}


Hooking::NativeHandler  ORIG_NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE = NULL;
void *__cdecl MY_NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(NativeContext* cxt)
{
	Player player = cxt->GetArgument<int>(0);
	if (player == PLAYER::PLAYER_ID())
	{
		ORIG_NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(cxt);
	}
	return nullptr;
}

Hooking::NativeHandler  ORIG_ATTACH_ENTITY_TO_ENTITY = NULL;
void *__cdecl MY_ATTACH_ENTITY_TO_ENTITY(NativeContext* cxt)
{
	Player player = cxt->GetArgument<int>(0);
	if (player == PLAYER::PLAYER_ID())
	{
		ORIG_ATTACH_ENTITY_TO_ENTITY(cxt);
	}
	return nullptr;
}

Hooking::NativeHandler ORIG_CLEAR_PED_TASKS_IMMEDIATELY = NULL;
void *__cdecl MY_CLEAR_PED_TASKS_IMMEDIATELY(NativeContext *cxt)
{
	if (cxt->GetArgument<Ped>(0) != PLAYER::PLAYER_PED_ID())
	{
		ORIG_CLEAR_PED_TASKS_IMMEDIATELY(cxt);
	}

	return nullptr;
}

Hooking::NativeHandler ORIG_CLEAR_PED_TASKS = NULL;
void *__cdecl MY_CLEAR_PED_TASKS(NativeContext *cxt)
{
	if (cxt->GetArgument<Ped>(0) != PLAYER::PLAYER_PED_ID())
	{
		ORIG_CLEAR_PED_TASKS(cxt);
	}

	return nullptr;
}

Hooking::NativeHandler ORIG_CLEAR_PED_SECONDARY_TASK = NULL;
void *__cdecl MY_CLEAR_PED_SECONDARY_TASK(NativeContext *cxt)
{
	if (cxt->GetArgument<Ped>(0) != PLAYER::PLAYER_PED_ID())
	{
		ORIG_CLEAR_PED_SECONDARY_TASK(cxt);
	}
	return nullptr;
}

Hooking::NativeHandler ORIG_CLONE_PED = NULL;
void *__cdecl MY_CLONE_PED(NativeContext *cxt)
{
	if (cxt->GetArgument<Ped>(0) != PLAYER::PLAYER_PED_ID())
	{
		ORIG_CLONE_PED(cxt);
	}
	return nullptr;
}


std::vector<int> defuseEventList = {
			406574440 ,
			 1496305992 ,
			 -2145660408 ,
			 2058344104 ,
			 -1246838892 ,
			 297770348 ,
			 498709856 ,
			 1432301416 ,
			 -452918768 ,
			 -498955166 ,
			 1772702665 ,
			 1472041801 ,
			 521876760 ,
			 -741569622 ,
			  623353069 ,
			 -24665064 ,
			 1408242514 ,
			 -961323766 ,
			 -1246838892 ,
			 930233414 ,
			 297770348 ,
			 498709856 ,
			 1432301416 ,
			 -701823896 ,
			 -327286343 ,
			 -348418057 ,
			 -38669034 ,
			 -442609600 ,
			 320958241 ,
			 1663317123 ,
			 552065831 ,
			 -163616977 ,
			 -615431083 ,
			 -1961284186 ,
			 189238289 ,
			 -125347541 ,
			 1667907776 ,
			 774421744 ,
			  1404046700 ,
			 297770348 ,
			 498709856 ,
			 -2017629233 ,
			 564131320 ,
			 1055326208 ,
			 -1443461156 ,
			 561831609 ,
			 297770348 ,
			  498709856 ,
			  1432301416 ,
			  -741569622 ,
			  -741569622 ,
			  -741569622 ,
			  623353069 ,
			  -24665064 ,
			  -961323766 ,
			  -1246838892 ,
			  930233414 ,
			 297770348 ,
			   498709856 ,
			   1432301416 ,
			   -741569622 ,
			  1758371826 ,
			  -20869460 ,
			  1663317123 ,
			  -814250534 ,
			  502531308 ,
			  -2017629233 ,
			  709335341 ,
			  1408706672 ,
			  -615431083 ,
			  83889733 ,
			  245423013 ,
			  434650799 ,
			  918819909 ,
			   623353069 ,
			  -394200909 ,
			  1508155656 ,
			  963801520 ,
			  861803892 ,
			  1647874347 ,
			  352347079 ,
			  189238289 ,
			  -327286343 ,
			  -1439858051 ,
			  521876760 ,
			  -1130790470 ,
			  -916045477 ,
			  -1924332863 ,
			  193185511 ,
			  1877809576 ,
			  523712273 ,
			  -1302989626 ,
			  -73121960 ,
			  1091694297 ,
			  189577788 ,
			  901923086 ,
			  1980160043 ,
			  49032278 ,
			  -2066829834 ,
			  1472041801 ,
			   623353069 ,
			  1071328985 ,
			  724418743 ,
			  822417436 ,
			  890896299 ,
			  322981094 ,
			  482951063 ,
			  146034718 ,
			  -36183323 ,
			  -335191407 ,
			  508430049 ,
			  480048178 ,
			  118624522 ,
			  82165269 ,
			  2090686445 ,
			  -1178193785 ,
			 1404046700 ,
			  1778168668 ,
			  339625040 ,
			  -1321155738 ,
			  -979374148 ,
			  -1720012516 ,
			  898856529 ,
			  -1142468390 ,
			  -1699295646 ,
			  2138371129 ,
			   623353069 ,
			  1981990936 ,
			  888267326 ,
			  362090628 ,
			  -1627224982 ,
			  1279971571 ,
			  -1704719905 ,
			  1417640596 ,
			  251884576 ,
			  -961516517 ,
			  -471223072 ,
			  131052851 ,
			  -904116584 ,
			  -43708501 ,
			  -804142609 ,
			  256182072 ,
			  2053379718 ,
			  857140506 ,
			  310704871 ,
			  -906869562 ,
			  346095784 ,
			  -1816260298 ,
			  781752000 ,
			  881107247 ,
			  201500071 ,
			  1865815519 ,
			  -1240650576 ,
			  1996697700 ,
			   623353069 ,
			  -1349547643 ,
			  118148470 ,
			  -1945280109 ,
			  -1496164047 ,
			  -1456895310 ,
			  -1712443583 ,
			  1333683672 ,
			  1387341684 ,
			  -435423673 ,
			  -1307725993 ,
			  -2006277699 ,
			  1119989583 ,
			  -155167316 ,
			  -563897659 ,
			  380850754 ,
			  -742855220 ,
			  2117809793 ,
			  -1249282212 ,
			  -706275331 ,
			  -1933245257 ,
			  420531845 ,
			  -1140845626 ,
			  2069146067 ,
			  621228928 ,
			  290191363 ,
			  -2110179252 ,
			  -615831251 ,
			  1471580568 ,
			  1045220557 ,
			  -1148590118 ,
			  -569373826 ,
			  1453328116 ,
			  1386093045 ,
			  209830230 ,
			  -1587392072 ,
			  -262147301 ,
			  1116334142 ,
			  1163207422 ,
			  361852054 ,
			  1311308492 ,
			  1131828144 ,
			  1054081024 ,
			  1000011951 ,
			   623353069 ,
			 4990770 ,
			  127346459 ,
			  824365124 ,
			  1548794127 ,
			  -1788191560 ,
			  1724490830 ,
			  -1052213624 ,
			  743358831 ,
			  -782556854 ,
			  426751791 ,
			  -2020463550 ,
			  -1857189069 ,
			  1564615395 ,
			  -903067097 ,
			  -797746128 ,
			  71703256 ,
			  370537077 ,
			  170508679 ,
			  275033734 ,
			  459263416 ,
			  1381803144 ,
			  1216246321 ,
			  -1205055403 ,
			  -2041146541 ,
			  -254129362 ,
			   623353069 ,
			  -1033009429 ,
			  -1839401287 ,
			  1078404666 ,
			  -125347541 ,
			  106447194 ,
			  -1695045910 ,
			  1014519574 ,
			  1971017958 ,
			  -1958748595 ,
			 623353069 ,
			  1905289427 ,
			  2042933818 ,
			  -692471382 ,
			  321656337 ,
			  6840162 ,
			  -1010395481 ,
			  1070706073 ,
			  -1871464949 ,
			  -1773160953 ,
			  -1900102430 ,
			  -1127711271 ,
			  -1720940007 ,
			  -701823896 ,
			  1088035140 ,
			  894885858 ,
			  -1245089876 ,
			   623353069 ,
			  -708301411 ,
			 774421744 ,
			  2095614502 ,
			  -1548391120 ,
			  -1590759069 ,
			  -1961284186 ,
			  983043215 ,
			  823323117 ,
			  -347067541 ,
			  -1949038199 ,
			  368447669 ,
			  -712526240 ,
			  -395934173 ,
			  -2118134456 ,
			  -2053209519 ,
			  -2120020909 ,
			  1750231825 ,
			  -1815806749 ,
			  -100604291 ,
			  1034081830 ,
			  -1570741512 ,
			  -2099492219 ,
			  -2052930435 ,
			  -1969967074 ,
			  406857800 ,
			  -1617247716 ,
			  1767220965 ,
			  568793304 ,
			  981817799 ,
			  -617164799 ,
			  1567865855 ,
			  -1818550779 ,
			  -1153009121 ,
			  -1964956981 ,
			  1658079306 ,
			  -427192511 ,
			  -1926987112 ,
			  -514046096 ,
			  1432301416 ,
			  147164987 ,
			  -1411930028 ,
			  314667560 ,
			  -173662905 ,
			  -1297785021 ,
			  -13389525 ,
			  623353069 ,
			  -1246838892 ,
			  2128847919 ,
			  -1605452877 ,
			  -247786993 ,
			  1899922317 ,
			  1159655011 ,
			  -1236662280 ,
			  -327286343 ,
			  -632266118 ,
			  426145626 ,
			  -1607727591 ,
			  75959252 ,
			  -961323766 ,
			  1089802031 ,
			  -620488063 ,
			  -80260497 ,
			  900146065 ,
			  634715799 ,
			  -1179957982 ,
			  930233414 ,
			  2037380969 ,
			  -1441342807 ,
			  1997336063 ,
			  500910216 ,
			  1152017566 ,
			   623353069 ,
			  988581119 ,
			  1826420594 ,
			  1898418294 ,
			  -931251033 ,
			  -841066582 ,
			  -1708373442 ,
			  -69369765 ,
			  143196100 ,
			  2101702851 ,
			  -1900445345 ,
			  966865853 ,
			  -1618821911 ,
			  1416599206 ,
			  -684933083 ,
			  -1745220171 ,
			  -331009836 ,
			  -2007637601 ,
			  -82508567 ,
			  1780075204 ,
			  -1384208350 ,
			  -1441300790 ,
			  -1539546643 ,
			  2062826530 ,
			  -109734847 ,
			  1311711891 ,
			  1616439311 ,
			  -1802448502 ,
			   623353069 ,
			  1403826689 ,
			  -158858713 ,
			  -885542897 ,
			  -1183687243 ,
			  569454533 ,
			  -348418057 ,
			  1810877168 ,
			  -1804237432 ,
			  776906349 ,
			  498709856 ,
			  297770348 ,
			  1667907776 ,
			  -985688171 ,
			  1404046700 ,
			  -1434746202 ,
			  1148978077 ,
			  -991216811 ,
			  1105133568 ,
			  1142206100 ,
			  1160342691 ,
			  1109623859 ,
			  297770348 ,
			  498709856 ,
			  -2017629233 ,
			  82165269 ,
			  -2017629233 ,
			  297770348 ,
			  498709856 ,
			  -2017629233 ,
			  -2017629233 ,
			  297770348 ,
			  498709856 ,
			  -2017629233 ,
			  82165269 ,
			  -2017629233 ,
			  297770348 ,
			  498709856 ,
			  -2017629233 ,
				  521876760,
				  -498955166,
				  -1089379066,

};


//void* m_OriginalGetEventData = nullptr;
//BOOL __cdecl HK_GET_EVENT_DATA(int eventGroup, int eventIndex, uint64_t* argStruct, int argStructSize)
//{
//	if (Features::lgevts)
//	{
//		auto result = static_cast<decltype(&HK_GET_EVENT_DATA)>(m_OriginalGetEventData)(eventGroup, eventIndex, argStruct, argStructSize);
//		char* name = PLAYER::GET_PLAYER_NAME(argStruct[1]);
//		char buf[30];
//		char id[30];
//		char sender[30];
//		unsigned int Bit = (1 << argStruct[1]);
//		snprintf(id, sizeof(id), "ID: %i", argStruct[0]);
//		snprintf(sender, sizeof(sender), "Sender: %s", name);
//		//	if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(argStruct[1]) != PLAYER::PLAYER_PED_ID()) {
//
//		for (auto hash : defuseEventList)
//			if (hash == argStruct[0])
//			{
//				//	auto result = static_cast<decltype(&HK_GET_EVENT_DATA)>(m_OriginalGetEventData)(eventGroup, eventIndex, argStruct, argStructSize);
//				//if (Features::redrect == true)
//				//{
//				//	if (!PLAYER::PLAYER_PED_ID())
//				//	{
//				//		//notifyMap("Blocked & Redirected");
//				//		SCRIPT::eventur(1, argStruct, argStructSize, Bit);
//				//	}
//				//}
//				//notifyMap("%s", sender, id, "Blocked");
//				//notifyMap("From: %s", sender, "ID %s", id, "Blocked");
//				//if (Features::BlckAll)
//				//{
//				//	notifyMap("%s", sender);
//				//	notifyMap("%s", id);
//				//	notifyMap("Blocked");
//				//	notifyMap("%s", id, sender, "Blocked");
//				//}
//				return false;
//			}
//	}
//	//}
//	else
//	{
//		return HK_GET_EVENT_DATA(eventGroup, eventIndex, argStruct, argStructSize);
//	}
//}

//newset anti script events




void Hooking::ownedExplosionBypass(bool toggle)
{
	constexpr twoBytes patched = { 0x39, 0xDB };
	constexpr twoBytes restore = { 0x3B, 0xF8 };
	if (m_ownedExplosionBypass == nullptr) return;
	*m_ownedExplosionBypass = toggle ? patched : restore;
} //OWNED_EXPLOSION



void* GED_Nullpointer = nullptr;
BOOL __cdecl HK_GET_EVENT_DATA(std::int32_t EventGruppe, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount) 
{

	auto HandlerBool = static_cast<decltype(&HK_GET_EVENT_DATA)>(GED_Nullpointer)(EventGruppe, eventIndex, args, argCount);
	if (HandlerBool) {
		//char id[30];
		Player player = args[1];
		//snprintf(id, sizeof(id), "ID: %i", args[0]);
		char* sender = Hooking::get_player_name(player);

		for (int i = 0; i < 393; ++i)
		{

			if (args[0] == defuseEventList[i] && Features::lgevts) {
				if (Features::lgevtssss == true) 
				{ 
					notifyMap("Event: Script\nSender: " + std::string(sender) + "\nStatus: Blocked"); 
				}
				//	notifyBlocked("Event%s", id);
				return false;
			}
		}
	}
}

void BlockedMSG(char* fmt, ...)
{
	char buf[2048] = { 0 };
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);

	char buff2[2048] = { 0 };
	sprintf_s(buff2, "%s", buf);

	UI::_SET_NOTIFICATION_BACKGROUND_COLOR(6);
	UI::_SET_NOTIFICATION_TEXT_ENTRY((char*)"STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
	UI::_DRAW_NOTIFICATION(1, 1);
} 

void BlockedMSG(std::string str) { BlockedMSG(&str[0]); }

void* m_OriginalIncrementStatEvent = nullptr;
//void* m_OriginalIncrementStatEvent;

BOOL __cdecl CNetworkIncrementStatEventtt(uint64_t net_event_struct, int64_t sender, int64_t a3) { // weißt du was das ist ?  report bvlocker 

	const auto hash = *reinterpret_cast<DWORD*>(net_event_struct + 0x30);
	auto sender_id = *reinterpret_cast<std::int8_t*>(sender + 0x2D);
	auto sender_name = Hooking::get_player_name(sender_id);

	switch (hash)
	{
		//if (hash == 0xcbfd04a4)
		//{
		//	notifyMap("Blocked TEST from %s", sender_name);
		//	return false;
		//}
	case 0xcbfd04a4 /* MPPLY_GAME_EXPLOITS */:
		BlockedMSG("%s Tried to report you for MPPLY_GAME_EXPLOITS", sender_name);
		//notifyMap("Blocked MPPLY_GAME_EXPLOITS from %s", sender_name);
		return false;
		break;
	case 0x0e7072cd /* MPPLY_VC_HATE */:
		BlockedMSG("%s Tried to report you for MPPLY_VC_HATE", sender_name);
		//notifyMap("Blocked Report, MPPLY_VC_HATE from %s", sender_name);
		return false;
		break;
	case 0x9f79ba0b /* MPPLY_EXPLOITS */:
		BlockedMSG("%s Tried to report you for MPPLY_EXPLOITS", sender_name);
		//notifyMap("Blocked MPPLY_EXPLOITS from %s", sender_name);
		return false;
		break;
	case 0x762f9994 /* MPPLY_TC_ANNOYINGME */:
		BlockedMSG("%s Tried to report you for MPPLY_TC_ANNOYINGME", sender_name);
		//notifyMap("Blocked MPPLY_TC_ANNOYINGME from %s", sender_name);
		return false;
		break;
	case 0xb722d6c0 /* MPPLY_TC_HATE */:
		BlockedMSG("%s Tried to report you for MPPLY_TC_HATE", sender_name);
		//notifyMap("Blocked MPPLY_TC_HATE from %s", sender_name);
		return false;
		break;
	case 0x9C6A0C42: //MPPLY_GRIEFING
		BlockedMSG("%s Tried to report you for MPPLY_GRIEFING", sender_name);
		//notifyMap("Blocked MPPLY_GRIEFING from %s", sender_name);
		return false;
		break;
	case -1342164223: //MPPLY_GRIEFING
		BlockedMSG("%s Tried to report you for MPPLY_GRIEFING", sender_name);
		//notifyMap("Blocked MPPLY_GRIEFING from %s", sender_name);
		return false;
		break;
	case 0x62EB8C5A: //MPPLY_VC_ANNOYINGME
		BlockedMSG("%s Tried to report you for MPPLY_TC_ANNOYINGME", sender_name);
		//notifyMap("Blocked MPPLY_VC_ANNOYINGME from %s", sender_name);
		return false;
		break;
	case 0x3CDB43E2: //MPPLY_OFFENSIVE_LANGUAGE
		BlockedMSG("%s Tried to report you for MPPLY_OFFENSIVE_LANGUAGE", sender_name);
		//notifyMap("Blocked MPPLY_OFFENSIVE_LANGUAGE from %s", sender_name);
		return false;
		break;
	case 0xE8FB6DD5: //MPPLY_OFFENSIVE_TAGPLATE
		BlockedMSG("%s Tried to report you for MPPLY_OFFENSIVE_TAGPLATE", sender_name);
		//notifyMap("Blocked MPPLY_OFFENSIVE_TAGPLATE from %s", sender_name);
		return false;
		break;
	case 0xF3DE4879: //MPPLY_OFFENSIVE_UGC
		BlockedMSG("%s Tried to report you for MPPLY_OFFENSIVE_UGC", sender_name);
		//notifyMap("Blocked MPPLY_OFFENSIVE_UGC from %s", sender_name);
		return false;
		break;
	case 0xAA238FF0: //MPPLY_BAD_CREW_NAME
		BlockedMSG("%s Tried to report you for MPPLY_BAD_CREW_NAME", sender_name);
		//notifyMap("Blocked MPPLY_BAD_CREW_NAME from %s", sender_name);
		return false;
		break;
	case 0x03511A79: //MPPLY_BAD_CREW_MOTTO
		BlockedMSG("%s Tried to report you for MPPLY_BAD_CREW_MOTTO", sender_name);
		//notifyMap("Blocked MPPLY_BAD_CREW_MOTTO from %s", sender_name);
		return false;
		break;
		//case 1619412469:
	case 0x3B566D5C: //MPPLY_BAD_CREW_STATUS
		BlockedMSG("%s Tried to report you for MPPLY_BAD_CREW_STATUS", sender_name);
		//notifyMap("Blocked MPPLY_BAD_CREW_STATUS from %s", sender_name);
		return false;
		break;
	case 0x368F6FD9: //MPPLY_BAD_CREW_EMBLEM
		BlockedMSG("%s Tried to report you for MPPLY_BAD_CREW_EMBLEM", sender_name);
		//notifyMap("Blocked MPPLY_BAD_CREW_EMBLEM %s", sender_name);
		return false;
		break;

		return false;
	}
	//notifyMap("Blocked report from %s", sender_name);
	return static_cast<decltype(&CNetworkIncrementStatEventtt)>(m_OriginalIncrementStatEvent)(net_event_struct, sender, a3);
}



fpGetLabelText ogGetLabelText = nullptr;
const char* __cdecl hkGetLabelText(void* this_, const char* label)
{
	if (std::strcmp(label, "HUD_JOINING") == 0)
	{
		return Hooking::loading_text;
	}

	return ogGetLabelText(this_, label);
}

bool Hooking::HookNatives()
{

	MH_STATUS status = MH_CreateHook(Hooking::is_DLC_present, HK_IS_DLC_PRESENT, (void**)&OG_IS_DLC_PRESENT);
	{
		if ((status != MH_OK && status != MH_ERROR_ALREADY_CREATED) || MH_EnableHook(Hooking::is_DLC_present) != MH_OK)
			return false;
		Hooking::m_hooks.push_back(Hooking::is_DLC_present);
	}

	MH_STATUS statusssssssssssssssssssss = MH_CreateHook(Hooking::m_CNetworkIncrementStatEventt, CNetworkIncrementStatEventtt, (void**)&m_OriginalIncrementStatEvent);
	if (statusssssssssssssssssssss != MH_OK || MH_EnableHook(Hooking::m_CNetworkIncrementStatEventt) != MH_OK)
		return false;
	Log::Msg("Hook Succeed Block reports now %s", MH_StatusToString(statusssssssssssssssssssss));
	Log::Msg("HOOKED BLOCK REPORTS");
	Hooking::m_hooks.push_back(Hooking::m_CNetworkIncrementStatEventt);



	//MH_STATUS statusssss = MH_CreateHook(Hooking::GetLabelText, hkGetLabelText, (void**)&ogGetLabelText);
	//if ((statusssss != MH_OK && statusssss != MH_ERROR_ALREADY_CREATED) || MH_EnableHook(Hooking::GetLabelText) != MH_OK)
	//	return false;
	//Log::Msg("Hook Succeed GetLAbelText %s", MH_StatusToString(statusssss));
	//Hooking::m_hooks.push_back(Hooking::GetLabelText);


	MH_STATUS statuslol = MH_CreateHook(Hooking::GetLabelText, hkGetLabelText, (void**)&ogGetLabelText);
	if (status != MH_OK || MH_EnableHook(Hooking::GetLabelText) != MH_OK)
		return false;
	Hooking::m_hooks.push_back(Hooking::GetLabelText);




	MH_STATUS stataus = MH_CreateHook(Hooking::get_script_event_data, &HK_GET_EVENT_DATA, (void**)&GED_Nullpointer);
	if ((stataus != MH_OK && stataus != MH_ERROR_ALREADY_CREATED) || MH_EnableHook(Hooking::get_script_event_data) != MH_OK)
	{
		Log::Msg("Hook Status %s", MH_StatusToString(stataus));
		return false;
	}
	Log::Msg("Hook Succeed Status %s", MH_StatusToString(stataus));
	Hooking::m_hooks.push_back(Hooking::get_script_event_data);
	Log::Msg("Hook Successfully!");
	return true;
	Log::Msg("Hooked SmartScriptEvent Prtoection");
	


}

/*void __stdcall ScriptFunction(LPVOID lpParameter)
{
	try
	{
		ScriptMain();

	}
	catch (...)
	{
		Log::Fatal("Failed scriptFiber");
	}
}
*/
void __stdcall ScriptFunction(LPVOID lpParameter)
{
	try
	{
		ScriptMain();

	}
	catch (...)
	{
		Log::Fatal("Failed scriptFiber");
	}
}

void Hooking::onTickInit()
{
	if (mainFiber == nullptr)
		mainFiber = ConvertThreadToFiber(nullptr);

	if (timeGetTime() < wakeAt)
		return;

	static HANDLE scriptFiber;
	if (scriptFiber)
		SwitchToFiber(scriptFiber);
	else
		scriptFiber = CreateFiber(NULL, ScriptFunction, nullptr);
}

void Hooking::FailPatterns(const char* name)
{
	char buf[4096];
	sprintf_s(buf, "finding %s", name);
	Log::Error(buf);
	Cleanup();
}

/*
//CPatternResult
*/

CPatternResult::CPatternResult(void* pVoid) :
	m_pVoid(pVoid)
{}
CPatternResult::CPatternResult(void* pVoid, void* pBegin, void* pEnd) :
	m_pVoid(pVoid),
	m_pBegin(pBegin),
	m_pEnd(pEnd)
{}
CPatternResult::~CPatternResult() {}

/*
//CPattern Public
*/

CPattern::CPattern(char* szByte, char* szMask) :
	m_szByte(szByte),
	m_szMask(szMask),
	m_bSet(false)
{}
CPattern::~CPattern() {}

CPattern&	CPattern::find(int i, uint64_t startAddress)
{
	match(i, startAddress, false);
	if (m_result.size() <= i)
		m_result.push_back(nullptr);
	return *this;
}

CPattern&	CPattern::virtual_find(int i, uint64_t startAddress)
{
	match(i, startAddress, true);
	if (m_result.size() <= i)
		m_result.push_back(nullptr);
	return *this;
}

CPatternResult	CPattern::get(int i)
{
	if (m_result.size() > i)
		return m_result[i];
	return nullptr;
}





/*
//CPattern Private
*/
bool	CPattern::match(int i, uint64_t startAddress, bool virt)
{
	if (m_bSet)
		return false;
	uint64_t	begin = 0;
	uint64_t	end = 0;
	if (!virt)
	{
		CMetaData::init();
		begin = CMetaData::begin() + startAddress;
		end = CMetaData::end();
		if (begin >= end)
			return false;
	}
	int		j = 0;
	do
	{
		if (virt)
			begin = virtual_find_pattern(startAddress, (BYTE*)m_szByte, m_szMask) + 1;
		else
			begin = find_pattern(begin, end, (BYTE*)m_szByte, m_szMask) + 1;
		if (begin == NULL)
			break;
		j++;
	} while (j < i);

	m_bSet = true;
	return true;
}

bool	CPattern::byte_compare(const BYTE* pData, const BYTE* btMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++btMask)
		if (*szMask == 'x' && *pData != *btMask)
			break;
	if ((*szMask) != 0)
		return false;
	return true;
}


uint64_t	CPattern::find_pattern(uint64_t address, uint64_t end, BYTE *btMask, char *szMask)
{
	size_t len = strlen(szMask) + 1;
	for (uint64_t i = 0; i < (end - address - len); i++)
	{
		BYTE*	ptr = (BYTE*)(address + i);
		if (byte_compare(ptr, btMask, szMask))
		{
			m_result.push_back(CPatternResult((void*)(address + i)));
			return address + i;
		}
	}
	return NULL;
}

uint64_t	CPattern::virtual_find_pattern(uint64_t address, BYTE *btMask, char *szMask)
{
	MEMORY_BASIC_INFORMATION mbi;
	char*	pStart = nullptr;
	char*	pEnd = nullptr;
	char*	res = nullptr;
	size_t	maskLen = strlen(szMask);

	while (res == nullptr && sizeof(mbi) == VirtualQuery(pEnd, &mbi, sizeof(mbi)))
	{
		pStart = pEnd;
		pEnd += mbi.RegionSize;
		if (mbi.Protect != PAGE_READWRITE || mbi.State != MEM_COMMIT)
			continue;

		for (int i = 0; pStart < pEnd - maskLen && res == nullptr; ++pStart)
		{
			if (byte_compare((BYTE*)pStart, btMask, szMask))
			{
				m_result.push_back(CPatternResult((void*)pStart, mbi.BaseAddress, pEnd));
				res = pStart;
			}
		}

		mbi = {};
	}
	return (uint64_t)res;
}

void	failPat(const char* name)
{
	Log::Fatal("Failed to find %s pattern.", name);
	exit(0);
}
template <typename Y>
void	setPat123
(
	const char* name,
	char* pat,
	char* mask,
	Y** out,
	bool		rel,
	int			offset = 0,
	int			deref = 0,
	int			skip = 0
)
{
	Y* ptr = nullptr;

	CPattern pattern(pat, mask);
	pattern.find(1 + skip);
	if (rel)
		ptr = pattern.get(skip).get_rel<T>(offset);
	else
		ptr = pattern.get(skip).get<T>(offset);

	while (true)
	{
		if (ptr == nullptr)
			failPat(name);

		if (deref <= 0)
			break;
		ptr = *(Y**)ptr;
		--deref;
	}

	*out = ptr;
	return;
}
template <typename T>
void	setPat
(
	const char*	name,
	char*		pat,
	char*		mask,
	T**			out,
	bool		rel,
	int			offset = 0,
	int			deref = 0,
	int			skip = 0
)

{
	T*	ptr = nullptr;

	CPattern pattern(pat, mask);
	pattern.find(1 + skip);
	if (rel)
		ptr = pattern.get(skip).get_rel<T>(offset);
	else
		ptr = pattern.get(skip).get<T>(offset);

	while (true)
	{
		if (ptr == nullptr)
			failPat(name);

		if (deref <= 0)
			break;
		ptr = *(T**)ptr;
		--deref;
	}

	*out = ptr;
	return;
}

template <typename T>
void	setFn
(
	const char*	name,
	char*		pat,
	char*		mask,
	T*			out,
	int			skip = 0
)
{
	char*	ptr = nullptr;

	CPattern pattern(pat, mask);
	pattern.find(1 + skip);
	ptr = pattern.get(skip).get<char>(0);

	if (ptr == nullptr)
		failPat(name);

	*out = (T)ptr;
	return;
}

void HookMsg(std::string txt, bool hooked = false) 
{
	hooked ? Log::Msg("Found %s -> Hooked", txt) : Log::Msg("Found %s", txt);
}

void Hooking::FindPatterns()
{
	HANDLE steam = GetModuleHandleA("steam_api64.dll");

	auto p_activeThread = pattern("E8 ? ? ? ? 48 8B 88 10 01 00 00");
	auto p_blipList = pattern("4C 8D 05 ? ? ? ? 0F B7 C1");
	auto p_fixVector3Result = pattern("83 79 18 00 48 8B D1 74 4A FF 4A 18");
	auto p_gameLegals = pattern("72 1F E8 ? ? ? ? 8B 0D");
	auto p_gameLogos = pattern("70 6C 61 74 66 6F 72 6D 3A");
	auto p_gameState = pattern("83 3D ? ? ? ? ? 8A D9 74 0A");
	auto p_modelCheck = pattern("48 85 C0 0F 84 ? ? ? ? 8B 48 50");
	auto p_modelSpawn = pattern("48 8B C8 FF 52 30 84 C0 74 05 48");
	auto p_nativeTable = pattern("76 32 48 8B 53 40 48 8D 0D");
	auto p_worldPtr = pattern("48 8B 05 ? ? ? ? 45 ? ? ? ? 48 8B 48 08 48 85 C9 74 07");
	auto p_globalPtr = pattern("4C 8D 05 ? ? ? ? 4D 8B 08 4D 85 C9 74 11");
	auto p_eventHook = pattern("48 83 EC 28 E8 ? ? ? ? 48 8B 0D ? ? ? ? 4C 8D 0D ? ? ? ? 4C 8D 05 ? ? ? ? BA 03");

	setPat<uint64_t>("frame count",
		"\x8B\x15\x00\x00\x00\x00\x41\xFF\xCF",
		"xx????xxx",
		&Hooking::m_frameCount,
		true,
		2);

	setFn<fpIsDLCPresent>("is_DLC_present",
		"\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x81\xF9\x00\x00\x00\x00",
		"xxxx?xxxxxxx????",
		&Hooking::is_DLC_present);

	//setPat<void>("name changer", "\x48\x8B\x05\x00\x00\x00\x00\xC3\x8A\xD1", "xxx????xxx", &Hooking::m_onlineName, true, 3, 1);

	setFn<fpGetEventData>("get_script_event_data",
		"\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x49\x8B\xF8\x4C\x8D\x05\x00\x00\x00\x00",
		"xxxx?xxxxxxxxxxx????",
		&Hooking::get_script_event_data);

	setFn<SetSessionWeather>("set_session_weather",
		"\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x30\x40\x8A\xE9",
		"xxxx?xxxx?xxxx?xxxxxxxx",
		&Hooking::set_session_weather);
	Log::Msg("SLW");

	setPat<twoBytes>("owned explosion bypass",
		"\x3B\xF8\x40\x0F\x94\xC7",
		"xxxxxx",
		&Hooking::m_ownedExplosionBypass,
		false);
	HookMsg("OEB", true);

	setFn<addOwnedExplosion>("add_owned_explosion",
		"\x48\x8B\xC4\x48\x89\x58\x08\x48\x89\x70\x10\x48\x89\x78\x18\x4C\x89\x70\x20\x55\x48\x8D\x68\xB9\x48\x81\xEC\x00\x00\x00\x00\x0F\x29\x70\xE8\x41\x8B\xD8",
		"xxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxx",
		&Hooking::add_owned_explosion);
	HookMsg("AOE");


	HookMsg("GSH");
	setFn<fpStatSetInt>("stat_set_int",
		"\x89\x54\x24\x10\x55\x53\x56\x57\x41\x57",
		"xxxxxxxxxx",
		&Hooking::stat_set_int);
	HookMsg("DCE", true);


	setFn<fpGetPlayerName>("get_player_name",
		"\x40\x53\x48\x83\xEC\x20\x80\x3D\x00\x00\x00\x00\x00\x8B\xD9\x74\x22",
		"xxxxxxxx?????xxxx",
		&Hooking::get_player_name);
	Log::Msg("[Hooking] Hooked GPN");


	setFn<fpCNetworkIncrementStatEvent>("NetworkEventidk",
		"\x48\x89\x5C\x24\x00\x48\x89\x74\x24\x00\x55\x57\x41\x55\x41\x56\x41\x57\x48\x8B\xEC\x48\x83\xEC\x60\x8B\x79\x30",
		"xxxx?xxxx?xxxxxxxxxxxxxxxxxx",
		&Hooking::m_CNetworkIncrementStatEventt);


	setFn<fpGetWaypointPos>("get_waypoint_pos",
		"\x48\x89\x5C\x24\x08\x57\x48\x83\xEC\x20\x8B\x15\x00\x00\x00\x00\x65\x48\x8B\x04\x25\x00\x00\x00\x00\x48\x8B\xF9\x48\x8B\x04\xD0\xB9\xB4",
		"xxxxxxxxxxxx????xxxxx????xxxxxxxxx",
		&Hooking::get_waypoint_pos);

	setFn<fpNetworkIsSessionStarted>("network_is_session_started",
		"\x48\x8B\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x48\x8B\xC8\xE8\x00\x00\x00\x00\x48\x8B\xCF",
		"xxx????x????xxxx????xxx",
		&Hooking::network_is_session_started);

	Hooking::GetLabelText = static_cast<fpGetLabelText>(Memory::pattern("48 89 5C 24 ? 57 48 83 EC 20 48 8B DA 48 8B F9 48 85 D2 75 44 E8").count(1).get(0).get<void>(0));

	setFn<Trigger_Script_Event__>("trigger_script_event",
		"\x48\x8B\xC4\x48\x89\x58\x08\x48\x89\x68\x10\x48\x89\x70\x18\x48\x89\x78\x20\x41\x56\x48\x81\xEC\x00\x00\x00\x00\x45\x8B\xF0\x41\x8B\xF9",
		"xxxxxxxxxxxxxxxxxxxxxxxx????xxxxxx",
		&Hooking::trigger_script_event);
	Log::Msg("TSE");

	setPat<clockTime>("clock_time",
		"\x48\x8D\x0D\x00\x00\x00\x00\x8B\xFA\xE8\x00\x00\x00\x00\x44\x8D\x0C\x5B",
		"xxx????xxx????xxxx",
		&Hooking::ClockTime, true, 3);

	setFn<fpSetSessionTime>("session_time_set",
		"\x48\x89\x5C\x24\x08\x57\x48\x83\xEC\x20\x8B\xF9\x48\x8B\x0D\x00\x00\x00\x00\x48\x8B\xDA\x33\xD2\xE9\x00\x00\x00\x00",
		"xxxxxxxxxxxxxxx????xxxxxx????",
		&Hooking::set_session_time_info);

	char * c_location = nullptr;
	void * v_location = nullptr;

	Sleep(5000);

	CPattern pattern_modelCheck("\x48\x85\xC0\x0F\x84\x00\x00\x00\x00\x8B\x48\x50", "xxxxx????xxx");
	auto ptr = pattern_modelCheck.find(0).get(0).get<char>(0);
	ptr == nullptr ? Log::Error("Failed to find modelCheck_pattern") : Memory::nop(ptr, 24);

	CPattern pattern_modelSpawn("\x48\x8B\xC8\xFF\x52\x30\x84\xC0\x74\x05\x48", "xxxxxxxxxxx");
	ptr = pattern_modelSpawn.find(0).get(0).get<char>(8);
	ptr == nullptr ? Log::Error("Loaded .ini vehicle spawner.") : Memory::nop(ptr, 2);

	Log::Msg("Getting Game State...");
	c_location = p_gameState.count(1).get(0).get<char>(2);
	c_location == nullptr ? FailPatterns("gameState") : m_gameState = reinterpret_cast<decltype(m_gameState)>(c_location + *(int32_t*)c_location + 5);

	Log::Msg("Getting vector3 result fixer func...");
	v_location = p_fixVector3Result.count(1).get(0).get<void>(0);
	if (v_location != nullptr) scrNativeCallContext::SetVectorResults = (void(*)(scrNativeCallContext*))(v_location);

	Log::Msg("Getting native registration table...");
	c_location = p_nativeTable.count(1).get(0).get<char>(9);
	c_location == nullptr ? FailPatterns("native registration table") : m_registrationTable = reinterpret_cast<decltype(m_registrationTable)>(c_location + *(int32_t*)c_location + 4);

	Log::Msg("Getting World Pointer...");
	c_location = p_worldPtr.count(1).get(0).get<char>(0);
	c_location == nullptr ? FailPatterns("world Pointer") : m_worldPtr = reinterpret_cast<uint64_t>(c_location) + *reinterpret_cast<int*>(reinterpret_cast<uint64_t>(c_location) + 3) + 7;

	Log::Msg("Getting Blip List...");
	c_location = p_blipList.count(1).get(0).get<char>(0);
	c_location == nullptr ? FailPatterns("blip List") : m_blipList = (BlipList*)(c_location + *reinterpret_cast<int*>(c_location + 3) + 7);




	Log::Msg("Getting active script thread...");
	c_location = p_activeThread.count(1).get(0).get<char>(1);
	c_location == nullptr ? FailPatterns("Active Script Thread") : GetActiveThread = reinterpret_cast<decltype(GetActiveThread)>(c_location + *(int32_t*)c_location + 4);

	Log::Msg("Getting World Pointer...");
	c_location = p_globalPtr.count(1).get(0).get<char>(0);
	__int64 patternAddr = NULL;
	c_location == nullptr ? FailPatterns("globalTable") : patternAddr = reinterpret_cast<decltype(patternAddr)>(c_location);
	m_globalPtr = (__int64**)(patternAddr + *(int*)(patternAddr + 3) + 7);

	Log::Msg("Getting Event Hook...");
	if ((c_location = p_eventHook.count(1).get(0).get<char>(0)))
	{
		int i = 0, j = 0, matches = 0, found = 0;
		char* pattern = "\x4C\x8D\x05";
		while (found != EVENT_COUNT)
		{
			if (c_location[i] == pattern[j])
			{
				if (++matches == 3)
				{
					EventPtr.push_back((void*)(reinterpret_cast<uint64_t>(c_location + i - j) + *reinterpret_cast<int*>(c_location + i + 1) + 7));
					found++;
					j = matches = 0;
				}
				j++;
			}
			else
			{
				matches = j = 0;
			}
			i++;
		}
	}

	Log::Msg("Initializing natives...");
	CrossMapping::initNativeMap();

	Log::Msg("Checking if GTA V is ready...");
	while (*m_gameState != GameStatePlaying) {
		Sleep(200);
	}
	Log::Msg("GTA V ready!");
}

static Hooking::NativeHandler _Handler(uint64_t origHash)
{
	uint64_t newHash = CrossMapping::MapNative(origHash);
	if (newHash == 0)
	{
		return nullptr;
	}

	Hooking::NativeRegistrationNew * table = m_registrationTable[newHash & 0xFF];

	for (; table; table = table->getNextRegistration())
	{
		for (uint32_t i = 0; i < table->getNumEntries(); i++)
		{
			if (newHash == table->getHash(i))
			{
				return table->handlers[i];
			}
		}
	}
	return nullptr;
}

Hooking::NativeHandler Hooking::GetNativeHandler(uint64_t origHash)
{
	auto& handler = m_handlerCache[origHash];

	if (handler == nullptr)
	{
		handler = _Handler(origHash);
	}

	return handler;
}

eGameState Hooking::GetGameState()
{
	return *m_gameState;
}

uint64_t Hooking::getWorldPtr()
{
	return m_worldPtr;
}
void WAIT(DWORD ms)
{
	wakeAt = timeGetTime() + ms;
	SwitchToFiber(mainFiber);
}

void Hooking::Cleanup()
{
	Log::Msg("Cleaning up hooks");
	ownedExplosionBypass(false);
	for (int i = 0; i < m_hooks.size(); i++)
		if (MH_DisableHook(m_hooks[i]) != MH_OK && MH_RemoveHook(m_hooks[i]) != MH_OK)
			Log::Error("Failed to unhook %p", (void*)m_hooks[i]);
	MH_Uninitialize();

	FreeLibraryAndExitThread(static_cast<HMODULE>(_hmoduleDLL), 1);
}

void Hooking::defuseEvent(RockstarEvent e, bool toggle)
{
	static const unsigned char retn = 0xC3;
	char* p = (char*)EventPtr[e];
	if (toggle)
	{
		if (EventRestore[e] == 0)
			EventRestore[e] = p[0];
		*p = retn;
	}
	else
	{
		if (EventRestore[e] != 0)
			*p = EventRestore[e];
	}
}

__int64** Hooking::getGlobalPtr()
{
	return m_globalPtr;
}

/*void EventHooks::setplayername(std::string& name)
{
	size_t newLen = name.size() + 1;
	if (newLen <= 1 || newLen > 20)
		return;
	char    buffer[0x20] = {};
	char* pSearch = (char*)Hooking::m_onlineName + 0x5C;
	size_t    curLen = strlen(pSearch) + 1;
	strncpy_s(buffer, pSearch, curLen);
	for (uint32_t i = 0, found = 0, match = 0; found < 4; ++pSearch)
	{
		if (*pSearch != buffer[i])
			goto LABEL_RESET;
		if (++match < curLen)
		{
			++i;
			continue;
		}
		strncpy_s(pSearch - i, newLen, &name[0], newLen);
		++found;
	LABEL_RESET:
		i = match = 0;
	}
	strncpy(PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()), &name[0], newLen);
}*/
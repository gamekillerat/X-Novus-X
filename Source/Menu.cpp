#pragma once
#include "stdafx.h"
#include "UserInfo.cpp"
#include "Auth/Networking/WinHttpClient.h"
#include "Auth/Networking/Web2.0.h"
#include "MenuFunctions.cpp"
#include "Functions.h"
#include "AwsomeMods.h"
#include "NewProtections.h"
#include "ModderProtect.h"
#include "Playerinfo.h"
#include "SVT.h"
#include "Ini.h"
#include "GAME.h"
//#include "Auth.h"
//wait a bit
//Define object hashes

#define PICKUP_MONEY_CASE 0x1E9A99F8
#define PROP_MONEY_BAG_03 0x9CA6F755


namespace hooks
{
	typedef BOOL(__fastcall* tSTAT_SET_INT)(Hash statName, int value, BOOL save);
	static BOOL STAT_SET_INT(Hash statName, int value, BOOL save) { static tSTAT_SET_INT oSTAT_SET_INT = (tSTAT_SET_INT)(Memory::pattern("89 54 24 10 55 53 56 57 41 57").count(1).get(0).get<void>()); return oSTAT_SET_INT(statName, value, save); }
	typedef Pickup(__fastcall* tCREATE_AMBIENT_PICKUPP)(DWORD pickupHash, Vector3 pos, int unk0, int value, DWORD modelHash, bool unk1, bool unk2);
	static Pickup CREATE_AMBIENT_PICKUPP(DWORD pickupHash, Vector3 pos, int unk0, int value, DWORD modelHash, bool unk1, bool unk2) { static tCREATE_AMBIENT_PICKUPP oCREATE_AMBIENT_PICKUPP = (tCREATE_AMBIENT_PICKUPP)(Memory::pattern("48 8B C4 48 89 58 10 48 89 70 18 48 89 78 20 55 41 54 41 55 41 56 41 57 48 8D 68 C1 48 81 EC ? ? ? ? 45 8B F9 41 8B F0 4C 8B EA E8 ? ? ? ? 0F B7 0D ? ? ? ? 33 FF 44 8B C7 44 8B D7 44 8B E0 85 C9 7E 1C 48 8B 1D ? ? ? ?").count(1).get(0).get<void>()); return oCREATE_AMBIENT_PICKUPP(pickupHash, pos, unk0, value, modelHash, unk1, unk2); }
	static Pickup CREATE_AMBIENT_PICKUP(DWORD pickupHash, float x, float y, float z, int unk0, int value, DWORD modelHash, bool unk1, bool unk2) {
		Vector3 coords;
		coords.x = x;
		coords.y = y;
		coords.z = z;
		return CREATE_AMBIENT_PICKUPP(pickupHash, coords, unk0, value, modelHash, unk1, unk2);
	}

	typedef BOOL(__fastcall* tREQUEST_MODEL)(Hash model);
	static BOOL REQUEST_MODELL(Hash model) { static tREQUEST_MODEL oREQUEST_MODEL = (tREQUEST_MODEL)(Memory::pattern("48 89 5C 24 ? 48 89 7C 24 ? 55 48 8B EC 48 83 EC 50 8B 45 18").count(1).get(0).get<void>()); return oREQUEST_MODEL(model); }
	typedef bool(__fastcall* tHAS_MODEL_LOADED)(Hash model);
	static bool HAS_MODEL_LOADEDD(Hash model) { static tHAS_MODEL_LOADED oHAS_MODEL_LOADED = (tHAS_MODEL_LOADED)(Memory::pattern("48 89 7C 24 ? 55 48 8B EC 48 83 EC 20 8B 45 18 BF").count(1).get(0).get<void>()); return oHAS_MODEL_LOADED(model); }
	typedef BOOL(__fastcall* tSET_MODEL_AS_NO_LONGER_NEEDED)(DWORD hash);
	static BOOL SET_MODEL_AS_NO_LONGER_NEEDEDD(DWORD hash) { static tSET_MODEL_AS_NO_LONGER_NEEDED oSET_MODEL_AS_NO_LONGER_NEEDED = (tSET_MODEL_AS_NO_LONGER_NEEDED)(Memory::pattern("40 53 48 83 EC 30 48 8D 54 24 ? 8B D9").count(1).get(0).get<void>()); return oSET_MODEL_AS_NO_LONGER_NEEDED(hash); }
	typedef void(__fastcall* tGIVE_DELAYED_WEAPON_TO_PED)(Ped ped, Hash weaponHash, int time, BOOL equipNow);
	static void GIVE_DELAYED_WEAPON_TO_PED(Ped ped, Hash weaponHash, int time, BOOL equipNow) { static tGIVE_DELAYED_WEAPON_TO_PED oGIVE_DELAYED_WEAPON_TO_PED = (tGIVE_DELAYED_WEAPON_TO_PED)(Memory::pattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 41 8A E9 41 8B F0 8B FA E8 ? ? ? ? 48 8B D8 48 85 C0 74 63").count(1).get(0).get<void>()); return oGIVE_DELAYED_WEAPON_TO_PED(ped, weaponHash, time, equipNow); }
	typedef void(__fastcall* tSET_ENTITY_MAX_HEALTH)(Entity entity, int value);
	static void SET_ENTITY_MAX_HEALTH(Entity entity, int value) { static tSET_ENTITY_MAX_HEALTH oSET_ENTITY_MAX_HEALTH = (tSET_ENTITY_MAX_HEALTH)(Memory::pattern("40 53 48 83 EC 20 E8 ? ? ? ? 48 8B D8 48 85 C0 74 19 4C 8B 00 8B 15 ? ? ? ? 48 8B C8 41 FF 50 08 84 C0 74 05 48 8B C3 EB 02 33 C0 48 83 C4 20 5B C3 48 89 5C 24 ? 48 89 6C 24 ? 56 57").count(1).get(0).get<void>()); return oSET_ENTITY_MAX_HEALTH(entity, value); }
	
}


//Define useful things
Vector3 VehicleSpawCoords;
int spawnedVehHandle[10000];
float SpeedVehicle;
float animationspeed = 8.0f;
int numSpawned = 1;
bool vehicleSpawnNeeded = false;
int vehicleToSpawnHash; float Loading = 0.0f;
#define MyPedId	PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID())
#define MyCurentLoc ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1)
PCHAR g_pszVehicleImageDicts[] = {
	"lgm_default",
	"lgm_dlc_biker",
	"lgm_dlc_business",
	"lgm_dlc_business2",
	"lgm_dlc_executive1",
	"lgm_dlc_heist",
	"lgm_dlc_importexport",
	"lgm_dlc_lts_creator",
	"lgm_dlc_luxe",
	"lgm_dlc_pilot",
	"lgm_dlc_specialraces",
	"lgm_dlc_valentines",
	"lgm_dlc_valentines2",
	"lsc_default",
	"lsc_dlc_import_export",
	"lsc_jan2016",
	"lsc_lowrider2",
	"sssa_default",
	"sssa_dlc_biker",
	"sssa_dlc_business",
	"sssa_dlc_business2",
	"sssa_dlc_christmas_2",
	"sssa_dlc_christmas_3",
	"sssa_dlc_executive_1",
	"sssa_dlc_halloween",
	"sssa_dlc_heist",
	"sssa_dlc_hipster",
	"sssa_dlc_independence",
	"sssa_dlc_lts_creator",
	"sssa_dlc_mp_to_sp",
};
//Definding bools and int:S - Functions
Vehicle hash_veh, AddSpawnVehiclelot = 0, SpawnCannonVehHandle; Vehicle CheckVehicle[1024];
bool SpawnVehicle = false;
bool vehiclePrev = true;
bool godmode = false;
bool FIREBREATH = false;
bool Neverwanted = false;
bool Rpaint = false;
bool blackradar = false;
bool moneyDrop = false;
bool vehgodmode = false;
bool spectate_player = false;
bool waterLoop = false;
bool playerfireloop = false;
bool freeze_player = false;
bool fastRun = false;
bool fastSwim = false;
bool moneyGunme = false;
bool noIdle = false;
bool rp_incr = false;
bool police_igga = false;
bool freeze = false;
bool cyrclenew = false;
bool player_money_gun = false;
bool player_explo_gun = false;
bool playerAlwanted = false;
bool superJump = false;
bool hornBoostme = false;
bool MoonGravity = false;
bool hornBoostThem = false;
bool big_player = false;
bool nocontrolBoost = false;
bool moneyRound = false;
bool weird = false;
bool disweap = false;
bool actweap = false;
bool smooth_scroll = true;
bool invisable = false;
bool OnlineRpaint = false;
bool money_all = false;
bool all_boost = false;
bool all_money_gun = false;
bool dis_fps = false;
bool dis_coords = false;
bool spawn_upg = false;
bool explo_loop = false;
bool re_loop = false;
//Weapon bools
bool xpx_ammo = false;
bool xpx_ammo1 = false;
bool xpx_ammo2 = false;
bool xpx_ammo3 = false;
bool molo_gun = false;
bool flare_gun = false;
bool smoke_gun = false;
bool water_gun = false;
bool delete_gun = false;
bool explosive_malee = false;
bool teleport_gun = false;
bool RgbGun = false;
//Define things
bool PTLoopedO[35] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
#define ARRAYSIZE(A)    RTL_NUMBER_OF_V2(A)
#define _ARRAYSIZE(A)   RTL_NUMBER_OF_V1(A)

void menu_auth()
{

}

void BigPlayer()
{
	if (big_player)
	{
		PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 150, true);
	}
	else
	{
		PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 150, false);
	}
}

void AntiIdle()
{
	if (noIdle)
	{
		globalHandle(1388864).At(45).As<int>() = 1;
	}
	else
	{

		{
			globalHandle(1388864).At(45).As<int>() = 0;
		}
	}
}
//game - modell swapper hashes

char* pedModels[] = {
	"A_C_Boar","A_C_Chickenhawk","A_C_Chimp","A_C_Chop","A_C_Cormorant","A_C_Cow","A_C_Coyote","A_C_Crow","A_C_Deer","A_C_Fish","A_C_Hen","A_C_Husky","A_C_MtLion","A_C_Pig","A_C_Pigeon","A_C_Rat","A_C_Retriever",
	"A_C_Rhesus","A_C_Rottweiler","A_C_Seagull","A_C_SharkTiger","A_C_shepherd","A_F_M_Beach_01","A_F_M_BevHills_01","A_F_M_BevHills_02","A_F_M_BodyBuild_01","A_F_M_Business_02","A_F_M_Downtown_01","A_F_M_EastSA_01",
	"A_F_M_EastSA_02","A_F_M_FatBla_01","A_F_M_FatCult_01","A_F_M_FatWhite_01","A_F_M_KTown_01","A_F_M_KTown_02","A_F_M_ProlHost_01","A_F_M_Salton_01","A_F_M_SkidRow_01","A_F_M_SouCentMC_01","A_F_M_SouCent_01","A_F_M_SouCent_02",
	"A_F_M_Tourist_01","A_F_M_TrampBeac_01","A_F_M_Tramp_01","A_F_O_GenStreet_01","A_F_O_Indian_01","A_F_O_KTown_01","A_F_O_Salton_01","A_F_O_SouCent_01","A_F_O_SouCent_02","A_F_Y_Beach_01","A_F_Y_BevHills_01","A_F_Y_BevHills_02",
	"A_F_Y_BevHills_03","A_F_Y_BevHills_04","A_F_Y_Business_01","A_F_Y_Business_02","A_F_Y_Business_03","A_F_Y_Business_04","A_F_Y_EastSA_01","A_F_Y_EastSA_02","A_F_Y_EastSA_03","A_F_Y_Epsilon_01","A_F_Y_Fitness_01",
	"A_F_Y_Fitness_02","A_F_Y_GenHot_01","A_F_Y_Golfer_01","A_F_Y_Hiker_01","A_F_Y_Hippie_01","A_F_Y_Hipster_01","A_F_Y_Hipster_02","A_F_Y_Hipster_03","A_F_Y_Hipster_04","A_F_Y_Indian_01","A_F_Y_Juggalo_01","A_F_Y_Runner_01",
	"A_F_Y_RurMeth_01","A_F_Y_SCDressy_01","A_F_Y_Skater_01","A_F_Y_SouCent_01","A_F_Y_SouCent_02","A_F_Y_SouCent_03","A_F_Y_Tennis_01","A_F_Y_Topless_01","A_F_Y_Tourist_01","A_F_Y_Tourist_02","A_F_Y_Vinewood_01",
	"A_F_Y_Vinewood_02","A_F_Y_Vinewood_03","A_F_Y_Vinewood_04","A_F_Y_Yoga_01","A_M_M_ACult_01","A_M_M_AfriAmer_01","A_M_M_Beach_01","A_M_M_Beach_02","A_M_M_BevHills_01","A_M_M_BevHills_02","A_M_M_Business_01",
	"A_M_M_EastSA_01","A_M_M_EastSA_02","A_M_M_Farmer_01","A_M_M_FatLatin_01","A_M_M_GenFat_01","A_M_M_GenFat_02","A_M_M_Golfer_01","A_M_M_HasJew_01","A_M_M_Hillbilly_01","A_M_M_Hillbilly_02","A_M_M_Indian_01",
	"A_M_M_KTown_01","A_M_M_Malibu_01","A_M_M_MexCntry_01","A_M_M_MexLabor_01","A_M_M_OG_Boss_01","A_M_M_Paparazzi_01","A_M_M_Polynesian_01","A_M_M_ProlHost_01","A_M_M_RurMeth_01","A_M_M_Salton_01","A_M_M_Salton_02",
	"A_M_M_Salton_03","A_M_M_Salton_04","A_M_M_Skater_01","A_M_M_Skidrow_01","A_M_M_SoCenLat_01","A_M_M_SouCent_01","A_M_M_SouCent_02","A_M_M_SouCent_03","A_M_M_SouCent_04","A_M_M_StLat_02","A_M_M_Tennis_01",
	"A_M_M_Tourist_01","A_M_M_TrampBeac_01","A_M_M_Tramp_01","A_M_M_TranVest_01","A_M_M_TranVest_02","A_M_O_ACult_01","A_M_O_ACult_02","A_M_O_Beach_01","A_M_O_GenStreet_01","A_M_O_KTown_01","A_M_O_Salton_01",
	"A_M_O_SouCent_01","A_M_O_SouCent_02","A_M_O_SouCent_03","A_M_O_Tramp_01","A_M_Y_ACult_01","A_M_Y_ACult_02","A_M_Y_BeachVesp_01","A_M_Y_BeachVesp_02","A_M_Y_Beach_01","A_M_Y_Beach_02","A_M_Y_Beach_03","A_M_Y_BevHills_01",
	"A_M_Y_BevHills_02","A_M_Y_BreakDance_01","A_M_Y_BusiCas_01","A_M_Y_Business_01","A_M_Y_Business_02","A_M_Y_Business_03","A_M_Y_Cyclist_01","A_M_Y_DHill_01","A_M_Y_Downtown_01","A_M_Y_EastSA_01","A_M_Y_EastSA_02",
	"A_M_Y_Epsilon_01","A_M_Y_Epsilon_02","A_M_Y_Gay_01","A_M_Y_Gay_02","A_M_Y_GenStreet_01","A_M_Y_GenStreet_02","A_M_Y_Golfer_01","A_M_Y_HasJew_01","A_M_Y_Hiker_01","A_M_Y_Hippy_01","A_M_Y_Hipster_01","A_M_Y_Hipster_02",
	"A_M_Y_Hipster_03","A_M_Y_Indian_01","A_M_Y_Jetski_01","A_M_Y_Juggalo_01","A_M_Y_KTown_01","A_M_Y_KTown_02","A_M_Y_Latino_01","A_M_Y_MethHead_01","A_M_Y_MexThug_01","A_M_Y_MotoX_01","A_M_Y_MotoX_02","A_M_Y_MusclBeac_01",
	"A_M_Y_MusclBeac_02","A_M_Y_Polynesian_01","A_M_Y_RoadCyc_01","A_M_Y_Runner_01","A_M_Y_Runner_02","A_M_Y_Salton_01","A_M_Y_Skater_01","A_M_Y_Skater_02","A_M_Y_SouCent_01","A_M_Y_SouCent_02","A_M_Y_SouCent_03","A_M_Y_SouCent_04",
	"A_M_Y_StBla_01","A_M_Y_StBla_02","A_M_Y_StLat_01","A_M_Y_StWhi_01","A_M_Y_StWhi_02","A_M_Y_Sunbathe_01","A_M_Y_Surfer_01","A_M_Y_VinDouche_01","A_M_Y_Vinewood_01","A_M_Y_Vinewood_02","A_M_Y_Vinewood_03","A_M_Y_Vinewood_04",
	"A_M_Y_Yoga_01","CSB_Abigail","CSB_Anita","CSB_Anton","CSB_BallasOG","CSB_Bride","CSB_BurgerDrug","CSB_Car3guy1","CSB_Car3guy2","CSB_Chef","CSB_Chin_goon","CSB_Cletus","CSB_Cop","CSB_Customer","CSB_Denise_friend",
	"CSB_FOS_rep","CSB_G","CSB_Groom","CSB_Grove_str_dlr","CSB_Hao","CSB_Hugh","CSB_Imran","CSB_Janitor","CSB_Maude","CSB_MWeather","CSB_Ortega","CSB_Oscar","CSB_PornDudes","CSB_PrologueDriver","CSB_ProlSec","CSB_Ramp_gang",
	"CSB_Ramp_hic","CSB_Ramp_hipster","CSB_Ramp_marine","CSB_Ramp_mex","CSB_Reporter","CSB_RoccoPelosi","CSB_Screen_Writer","CSB_Stripper_01","CSB_Stripper_02","CSB_Tonya","CSB_TrafficWarden","CS_AmandaTownley","CS_Andreas",
	"cs_ashley","CS_Bankman","CS_Barry","CS_Beverly","CS_Brad","CS_BradCadaver","CS_Carbuyer","CS_Casey","CS_ChengSr","CS_ChrisFormage","CS_Clay","CS_Dale","CS_DaveNorton","cs_debra","cs_denise","CS_Devin","CS_Dom","CS_Dreyfuss",
	"CS_DrFriedlander","CS_Fabien","CS_FBISuit_01","CS_Floyd","CS_Guadalope","cs_gurk","CS_Hunter","CS_Janet","CS_JewelAss","CS_JimmyBoston","CS_JimmyDiSanto","CS_JoeMinuteMan","CS_JohnnyKlebitz","CS_Josef","CS_Josh","CS_LamarDavis",
	"CS_Lazlow","CS_LesterCrest","CS_LifeInvad_01","CS_Magenta","CS_Manuel","CS_Marnie","CS_MartinMadrazo","CS_MaryAnn","CS_Michelle","CS_Milton","CS_Molly","CS_MovPremF_01","CS_MovPremMale","CS_MRK","CS_MrsPhillips","CS_MRS_Thornhill",
	"CS_Natalia","CS_NervousRon","CS_Nigel","CS_Old_Man1A","CS_Old_Man2","CS_Omega","CS_Orleans","CS_Paper","CS_Patricia","CS_Priest","CS_ProlSec_02","CS_RussianDrunk","CS_SiemonYetarian","CS_Solomon","CS_SteveHains","CS_Stretch",
	"CS_Tanisha","CS_TaoCheng","CS_TaosTranslator","CS_TennisCoach","CS_Terry","CS_Tom","CS_TomEpsilon","CS_TracyDiSanto","CS_Wade","CS_Zimbor","G_F_Y_ballas_01","G_F_Y_Families_01","G_F_Y_Lost_01","G_F_Y_Vagos_01","G_M_M_ArmBoss_01",
	"G_M_M_ArmGoon_01","G_M_M_ArmLieut_01","G_M_M_ChemWork_01","G_M_M_ChiBoss_01","G_M_M_ChiCold_01","G_M_M_ChiGoon_01","G_M_M_ChiGoon_02","G_M_M_KorBoss_01","G_M_M_MexBoss_01","G_M_M_MexBoss_02","G_M_Y_ArmGoon_02","G_M_Y_Azteca_01",
	"G_M_Y_BallaEast_01","G_M_Y_BallaOrig_01","G_M_Y_BallaSout_01","G_M_Y_FamCA_01","G_M_Y_FamDNF_01","G_M_Y_FamFor_01","G_M_Y_Korean_01","G_M_Y_Korean_02","G_M_Y_KorLieut_01","G_M_Y_Lost_01","G_M_Y_Lost_02","G_M_Y_Lost_03",
	"G_M_Y_MexGang_01","G_M_Y_MexGoon_01","G_M_Y_MexGoon_02","G_M_Y_MexGoon_03","G_M_Y_PoloGoon_01","G_M_Y_PoloGoon_02","G_M_Y_SalvaBoss_01","G_M_Y_SalvaGoon_01","G_M_Y_SalvaGoon_02","G_M_Y_SalvaGoon_03","G_M_Y_StrPunk_01","G_M_Y_StrPunk_02",
	"HC_Driver","HC_Gunman","HC_Hacker","IG_Abigail","IG_AmandaTownley","IG_Andreas","IG_Ashley","IG_BallasOG","IG_Bankman","IG_Barry","IG_BestMen","IG_Beverly","IG_Brad","IG_Bride","IG_Car3guy1","IG_Car3guy2","IG_Casey",
	"IG_Chef","IG_ChengSr","IG_ChrisFormage","IG_Clay","IG_ClayPain","IG_Cletus","IG_Dale","IG_DaveNorton","IG_Denise","IG_Devin","IG_Dom","IG_Dreyfuss","IG_DrFriedlander","IG_Fabien","IG_FBISuit_01","IG_Floyd","IG_Groom",
	"IG_Hao","IG_Hunter","IG_Janet","ig_JAY_Norris","IG_JewelAss","IG_JimmyBoston","IG_JimmyDiSanto","IG_JoeMinuteMan","ig_JohnnyKlebitz","IG_Josef","IG_Josh","IG_KerryMcIntosh","IG_LamarDavis","IG_Lazlow","IG_LesterCrest",
	"IG_LifeInvad_01","IG_LifeInvad_02","IG_Magenta","IG_Manuel","IG_Marnie","IG_MaryAnn","IG_Maude","IG_Michelle","IG_Milton","IG_Molly","IG_MRK","IG_MrsPhillips","IG_MRS_Thornhill","IG_Natalia","IG_NervousRon","IG_Nigel",
	"IG_Old_Man1A","IG_Old_Man2","IG_Omega","IG_ONeil","IG_Orleans","IG_Ortega","IG_Paper","IG_Patricia","IG_Priest","IG_ProlSec_02","IG_Ramp_Gang","IG_Ramp_Hic","IG_Ramp_Hipster","IG_Ramp_Mex","IG_RoccoPelosi","IG_RussianDrunk",
	"IG_Screen_Writer","IG_SiemonYetarian","IG_Solomon","IG_SteveHains","IG_Stretch","IG_Talina","IG_Tanisha","IG_TaoCheng","IG_TaosTranslator","ig_TennisCoach","IG_Terry","IG_TomEpsilon","IG_Tonya","IG_TracyDiSanto","IG_TrafficWarden",
	"IG_TylerDix","IG_Wade","IG_Zimbor","MP_F_DeadHooker","MP_F_Freemode_01","MP_F_Misty_01","MP_F_StripperLite","MP_G_M_Pros_01","MP_HeadTargets","MP_M_Claude_01","MP_M_ExArmy_01","MP_M_FamDD_01","MP_M_FIBSec_01","MP_M_Freemode_01",
	"MP_M_Marston_01","MP_M_Niko_01","MP_M_ShopKeep_01","MP_S_M_Armoured_01","Player_One","Player_Two","Player_Zero","slod_human","slod_large_quadped","slod_small_quadped","S_F_M_Fembarber","S_F_M_Maid_01","S_F_M_Shop_HIGH",
	"S_F_M_SweatShop_01","S_F_Y_AirHostess_01","S_F_Y_Bartender_01","S_F_Y_Baywatch_01","S_F_Y_Cop_01","S_F_Y_Factory_01","S_F_Y_Hooker_01","S_F_Y_Hooker_02","S_F_Y_Hooker_03","S_F_Y_Migrant_01","S_F_Y_MovPrem_01","S_F_Y_Ranger_01",
	"S_F_Y_Scrubs_01","S_F_Y_Sheriff_01","S_F_Y_Shop_LOW","S_F_Y_Shop_MID","S_F_Y_StripperLite","S_F_Y_Stripper_01","S_F_Y_Stripper_02","S_F_Y_SweatShop_01","S_M_M_AmmuCountry","S_M_M_Armoured_01","S_M_M_Armoured_02","S_M_M_AutoShop_01",
	"S_M_M_AutoShop_02","S_M_M_Bouncer_01","S_M_M_ChemSec_01","S_M_M_CIASec_01","S_M_M_CntryBar_01","S_M_M_DockWork_01","S_M_M_Doctor_01","S_M_M_FIBOffice_01","S_M_M_FIBOffice_02","S_M_M_Gaffer_01","S_M_M_Gardener_01","S_M_M_GenTransport",
	"S_M_M_HairDress_01","S_M_M_HighSec_01","S_M_M_HighSec_02","S_M_M_Janitor","S_M_M_LatHandy_01","S_M_M_LifeInvad_01","S_M_M_Linecook","S_M_M_LSMetro_01","S_M_M_Mariachi_01","S_M_M_Marine_01","S_M_M_Marine_02","S_M_M_Migrant_01",
	"S_M_M_MovAlien_01","S_M_M_MovPrem_01","S_M_M_MovSpace_01","S_M_M_Paramedic_01","S_M_M_Pilot_01","S_M_M_Pilot_02","S_M_M_Postal_01","S_M_M_Postal_02","S_M_M_PrisGuard_01","S_M_M_Scientist_01","S_M_M_Security_01","S_M_M_SnowCop_01",
	"S_M_M_StrPerf_01","S_M_M_StrPreach_01","S_M_M_StrVend_01","S_M_M_Trucker_01","S_M_M_UPS_01","S_M_M_UPS_02","S_M_O_Busker_01","S_M_Y_AirWorker","S_M_Y_AmmuCity_01","S_M_Y_ArmyMech_01","S_M_Y_Autopsy_01","S_M_Y_Barman_01","S_M_Y_BayWatch_01",
	"S_M_Y_BlackOps_01","S_M_Y_BlackOps_02","S_M_Y_BlackOps_03","S_M_Y_BusBoy_01","S_M_Y_Chef_01","S_M_Y_Clown_01","S_M_Y_Construct_01","S_M_Y_Construct_02","S_M_Y_Cop_01","S_M_Y_Dealer_01","S_M_Y_DevinSec_01","S_M_Y_DockWork_01","S_M_Y_Doorman_01",
	"S_M_Y_DWService_01","S_M_Y_DWService_02","S_M_Y_Factory_01","S_M_Y_Fireman_01","S_M_Y_Garbage","S_M_Y_Grip_01","S_M_Y_HwayCop_01","S_M_Y_Marine_01","S_M_Y_Marine_02","S_M_Y_Marine_03","S_M_Y_Mime","S_M_Y_PestCont_01",
	"S_M_Y_Pilot_01","S_M_Y_PrisMuscl_01","S_M_Y_Prisoner_01","S_M_Y_Ranger_01","S_M_Y_Robber_01","S_M_Y_Sheriff_01","S_M_Y_Shop_MASK","S_M_Y_StrVend_01","S_M_Y_Swat_01","S_M_Y_USCG_01","S_M_Y_Valet_01","S_M_Y_Waiter_01",
	"S_M_Y_WinClean_01","S_M_Y_XMech_01","S_M_Y_XMech_02","U_F_M_Corpse_01","U_F_M_Miranda","U_F_M_ProMourn_01","U_F_O_MovieStar","U_F_O_ProlHost_01","U_F_Y_BikerChic","U_F_Y_COMJane","U_F_Y_corpse_01","U_F_Y_corpse_02",
	"U_F_Y_HotPosh_01","U_F_Y_JewelAss_01","U_F_Y_Mistress","U_F_Y_PoppyMich","U_F_Y_Princess","U_F_Y_SpyActress","U_M_M_Aldinapoli","U_M_M_BankMan","U_M_M_BikeHire_01","U_M_M_FIBArchitect","U_M_M_FilmDirector","U_M_M_GlenStank_01",
	"U_M_M_Griff_01","U_M_M_Jesus_01","U_M_M_JewelSec_01","U_M_M_JewelThief","U_M_M_MarkFost","U_M_M_PartyTarget","U_M_M_ProlSec_01","U_M_M_ProMourn_01","U_M_M_RivalPap","U_M_M_SpyActor","U_M_M_WillyFist","U_M_O_FinGuru_01",
	"U_M_O_TapHillBilly","U_M_O_Tramp_01","U_M_Y_Abner","U_M_Y_AntonB",	"U_M_Y_BabyD","U_M_Y_Baygor","U_M_Y_BurgerDrug_01","U_M_Y_Chip","U_M_Y_Cyclist_01","U_M_Y_FIBMugger_01","U_M_Y_Guido_01","U_M_Y_GunVend_01","U_M_Y_Hippie_01",
	"U_M_Y_ImpoRage","U_M_Y_Justin","U_M_Y_Mani","U_M_Y_MilitaryBum","U_M_Y_Paparazzi","U_M_Y_Party_01","U_M_Y_Pogo_01","U_M_Y_Prisoner_01","U_M_Y_ProlDriver_01","U_M_Y_RSRanger_01","U_M_Y_SBike","U_M_Y_StagGrm_01","U_M_Y_Tattoo_01",
	"U_M_Y_Zombie_01",
};
//All players - lobby bools
bool allplayerscash = false;
//bool moneyDrop = false;
//int
int TimePD5;
int rpvalue;
int r = 255;
int g = 100;
int b = 0;
int selectedPlayer = 0;

bool keyboardActive = false;
int keyboardAction;
//Define some coords - Vector3
//Vector3 shootcoords;
//Definding models

//Outfit Int:s

int outfit1 = 0;
int outfit2 = 0;
int outfit3 = 0;
int outfit4 = 0;
int mask1 = 0;
int mask2 = 0;
int shirt1 = 0;
int pants1 = 0;
int hands1 = 0;
int shoes1 = 0;
int eyes1 = 0;
int Accessories1 = 0;
int mission1 = 0;
int decals1 = 0;
int collars1 = 0;

//Effetcs bools
bool clown = false;
/*Custom Bools*/

bool cstrcmp(const char* s1, const char* s2)
{
	while (*s1 && (*s1 == *s2))
		s1++, s2++;
	if (*(const unsigned char*)s1 - *(const unsigned char*)s2 == 0)
		return true;
	else
		return false;
}
//Bools for protections
bool noRemoveWeps = false;
bool noGiveWeps = false;
bool antiFreeze = false;
bool novote = false;
bool noDrop = false;
bool vehExplode = false;
bool wantLvl = false;
bool clearArea = false;
bool playSound = false;
bool bankReq = false;
bool Timeproc = false;
bool Weatherproc = false;
bool Scriptproc = false;
bool leaverequest = false;
bool request_scene = false;
bool start_scene = false;
bool send_report2 = false;
bool send_fx = false;
bool bAutoWaypoint = false;

void teleport1(float x, float y, float z) {
	PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0) ? PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), x, y, z + 1.0f) : ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), x, y, z + 1.0f, 0, 0, 0, 1);
}

void MapNotify(char* msg)
{
	UI::_0x574EE85C("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(strdup(msg));
	UI::_DRAW_NOTIFICATION(false, true);
}

VOID AutoTpToWaypoint() {
	INT iWp = UI::GET_FIRST_BLIP_INFO_ID(8);
	if (UI::DOES_BLIP_EXIST(iWp)) {
		Vector3 vCoords = UI::GET_BLIP_COORDS(iWp);
		GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(vCoords.x, vCoords.y, vCoords.z, &vCoords.z, 0);
		teleport1(vCoords.x, vCoords.y, vCoords.z);
		MapNotify("Teleported to waypoint.");
	}
}
bool animNeeded = false;
char *animSetToDo;
int pedToDoAnimOn;
char *animNameToDo;
void Otherloops() {
	if (bAutoWaypoint) {
		AutoTpToWaypoint();
	}
	if (animNeeded)
	{

		if (STREAMING::HAS_ANIM_DICT_LOADED(animSetToDo))
		{
			AI::TASK_PLAY_ANIM(pedToDoAnimOn, animSetToDo, animNameToDo, animationspeed, 0.0f, -1, 9, 0.0f, false, false, false);
			animNeeded = false;
		}
	}

}

void doAnimation1(Ped ped, char *animSet, char *animName)
{
	animNeeded = true;
	pedToDoAnimOn = ped;
	animSetToDo = animSet;
	animNameToDo = animName;
	STREAMING::REQUEST_ANIM_DICT(animSetToDo);
}

void AddWalkingTyle(char* Name, char* WalkName) {
	Menu::Option(Name);
	if (Menu::Settings::currentOption == Menu::Settings::optionCount && Menu::Settings::selectPressed) {
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PLAYER::PLAYER_PED_ID());
		STREAMING::REQUEST_ANIM_SET(WalkName);
		if (STREAMING::HAS_ANIM_SET_LOADED(WalkName))
		{
			PED::SET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), WalkName, 0);
		}
	}
}
//New bools

bool NontArget = false;
bool under_wt_time = false;


void notifyleft2(char* text, char* text2, char* Subject)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG("CHAR_GANGAPP", "CHAR_GANGAPP", false, 7, text2, Subject, 1.0, "___Menu 1.0");
	UI::_DRAW_NOTIFICATION(FALSE, FALSE);
} //This works fine!

void ImgNotify(char* text, char* text2, char* Subject)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG("Logo", "Logo", false, 7, text2, Subject, 1.0, "Novus");
	UI::_DRAW_NOTIFICATION(FALSE, FALSE);
}

/*void notifyleft3(string text, string text2, string Subject)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::SET_STRING_TEXT(text);
	UI::_SET_CLAN_TAG("CHAR_GANGAPP", "CHAR_GANGAPP", false, 7, text2, Subject, 1.0, "___Menu 1.0");
	UI::_DRAW_NOTIFICATION(FALSE, FALSE);
} //This works fine!*/


void spawn_money_safe(Player selectedPlayer)
{
	Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(selectedPlayer, 0.0f, 0.0f, 0.5f);
	Hash PigeonHash = GAMEPLAY::GET_HASH_KEY("a_c_pigeon");
	if (STREAMING::IS_MODEL_IN_CDIMAGE(PigeonHash))
	{
		if (STREAMING::IS_MODEL_VALID(PigeonHash))
		{
			int TenK = 10000;
			hooks::REQUEST_MODELL(PigeonHash);
			while (!hooks::HAS_MODEL_LOADEDD(PigeonHash)) WAIT(0);
			Ped pigeonBank = PED::LEAKEAE_AEAJEJAEKAJE_EE_E(26, PigeonHash, coords.x, coords.y + 0.15, coords.z, ENTITY::GET_ENTITY_HEADING(selectedPlayer), TRUE, TRUE);
			Ped pigeonBank2 = PED::LEAKEAE_AEAJEJAEKAJE_EE_E(26, PigeonHash, coords.x, coords.y - 0.15, coords.z, ENTITY::GET_ENTITY_HEADING(selectedPlayer), TRUE, TRUE);

			Ped pigeonBank3 = PED::LEAKEAE_AEAJEJAEKAJE_EE_E(26, PigeonHash, coords.x + 0.15, coords.y, coords.z, ENTITY::GET_ENTITY_HEADING(selectedPlayer), TRUE, TRUE);
			Ped pigeonBank4 = PED::LEAKEAE_AEAJEJAEKAJE_EE_E(26, PigeonHash, coords.x - 0.15, coords.y, coords.z, ENTITY::GET_ENTITY_HEADING(selectedPlayer), TRUE, TRUE);

			Ped pigeonBank5 = PED::LEAKEAE_AEAJEJAEKAJE_EE_E(26, PigeonHash, coords.x + 0.15, coords.y + 0.15, coords.z, ENTITY::GET_ENTITY_HEADING(selectedPlayer), TRUE, TRUE);
			Ped pigeonBank6 = PED::LEAKEAE_AEAJEJAEKAJE_EE_E(26, PigeonHash, coords.x + 0.15, coords.y - 0.15, coords.z, ENTITY::GET_ENTITY_HEADING(selectedPlayer), TRUE, TRUE);

			Ped pigeonBank7 = PED::LEAKEAE_AEAJEJAEKAJE_EE_E(26, PigeonHash, coords.x - 0.15, coords.y + 0.15, coords.z, ENTITY::GET_ENTITY_HEADING(selectedPlayer), TRUE, TRUE);
			Ped pigeonBank8 = PED::LEAKEAE_AEAJEJAEKAJE_EE_E(26, PigeonHash, coords.x - 0.15, coords.y - 0.15, coords.z, ENTITY::GET_ENTITY_HEADING(selectedPlayer), TRUE, TRUE);

			Ped pigeonBank9 = PED::LEAKEAE_AEAJEJAEKAJE_EE_E(26, PigeonHash, coords.x, coords.y, coords.z, ENTITY::GET_ENTITY_HEADING(selectedPlayer), TRUE, TRUE);

			PED::SET_PED_MONEY(pigeonBank, TenK);
			PED::SET_PED_MONEY(pigeonBank2, TenK);
			PED::SET_PED_MONEY(pigeonBank3, TenK);
			PED::SET_PED_MONEY(pigeonBank4, TenK);
			PED::SET_PED_MONEY(pigeonBank5, TenK);
			PED::SET_PED_MONEY(pigeonBank6, TenK);
			PED::SET_PED_MONEY(pigeonBank7, TenK);
			PED::SET_PED_MONEY(pigeonBank8, TenK);
			PED::SET_PED_MONEY(pigeonBank9, TenK);

			ENTITY::SET_ENTITY_HEALTH(pigeonBank, 0);
			ENTITY::SET_ENTITY_HEALTH(pigeonBank2, 0);
			ENTITY::SET_ENTITY_HEALTH(pigeonBank3, 0);
			ENTITY::SET_ENTITY_HEALTH(pigeonBank4, 0);
			ENTITY::SET_ENTITY_HEALTH(pigeonBank5, 0);
			ENTITY::SET_ENTITY_HEALTH(pigeonBank6, 0);
			ENTITY::SET_ENTITY_HEALTH(pigeonBank7, 0);
			ENTITY::SET_ENTITY_HEALTH(pigeonBank8, 0);
			ENTITY::SET_ENTITY_HEALTH(pigeonBank9, 0);
			WAIT(200);

			PED::DELETE_PED(&pigeonBank);
			PED::DELETE_PED(&pigeonBank2);
			PED::DELETE_PED(&pigeonBank3);
			PED::DELETE_PED(&pigeonBank4);
			PED::DELETE_PED(&pigeonBank5);
			PED::DELETE_PED(&pigeonBank6);
			PED::DELETE_PED(&pigeonBank7);
			PED::DELETE_PED(&pigeonBank8);
			PED::DELETE_PED(&pigeonBank9);
		}
	}
}


void spawn_money_safee(Player selectedPlayer)
{
	Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(selectedPlayer, 0.0f, 0.0f, 0.5f);
	Hash PigeonHash = GAMEPLAY::GET_HASH_KEY("a_c_pigeon");
	if (STREAMING::IS_MODEL_IN_CDIMAGE(PigeonHash))
	{
		if (STREAMING::IS_MODEL_VALID(PigeonHash))
		{
			int TenK = 30000;
			hooks::REQUEST_MODELL(PigeonHash);
			while (!hooks::HAS_MODEL_LOADEDD(PigeonHash)) WAIT(0);
			Ped pigeonBank = PED::LEAKEAE_AEAJEJAEKAJE_EE_E(26, PigeonHash, coords.x, coords.y + 0.15, coords.z, ENTITY::GET_ENTITY_HEADING(selectedPlayer), TRUE, TRUE);
			Ped pigeonBank2 = PED::LEAKEAE_AEAJEJAEKAJE_EE_E(26, PigeonHash, coords.x, coords.y - 0.15, coords.z, ENTITY::GET_ENTITY_HEADING(selectedPlayer), TRUE, TRUE);

			Ped pigeonBank3 = PED::LEAKEAE_AEAJEJAEKAJE_EE_E(26, PigeonHash, coords.x + 0.15, coords.y, coords.z, ENTITY::GET_ENTITY_HEADING(selectedPlayer), TRUE, TRUE);
			Ped pigeonBank4 = PED::LEAKEAE_AEAJEJAEKAJE_EE_E(26, PigeonHash, coords.x - 0.15, coords.y, coords.z, ENTITY::GET_ENTITY_HEADING(selectedPlayer), TRUE, TRUE);

			Ped pigeonBank5 = PED::LEAKEAE_AEAJEJAEKAJE_EE_E(26, PigeonHash, coords.x + 0.15, coords.y + 0.15, coords.z, ENTITY::GET_ENTITY_HEADING(selectedPlayer), TRUE, TRUE);
			Ped pigeonBank6 = PED::LEAKEAE_AEAJEJAEKAJE_EE_E(26, PigeonHash, coords.x + 0.15, coords.y - 0.15, coords.z, ENTITY::GET_ENTITY_HEADING(selectedPlayer), TRUE, TRUE);

			Ped pigeonBank7 = PED::LEAKEAE_AEAJEJAEKAJE_EE_E(26, PigeonHash, coords.x - 0.15, coords.y + 0.15, coords.z, ENTITY::GET_ENTITY_HEADING(selectedPlayer), TRUE, TRUE);
			Ped pigeonBank8 = PED::LEAKEAE_AEAJEJAEKAJE_EE_E(26, PigeonHash, coords.x - 0.15, coords.y - 0.15, coords.z, ENTITY::GET_ENTITY_HEADING(selectedPlayer), TRUE, TRUE);

			Ped pigeonBank9 = PED::LEAKEAE_AEAJEJAEKAJE_EE_E(26, PigeonHash, coords.x, coords.y, coords.z, ENTITY::GET_ENTITY_HEADING(selectedPlayer), TRUE, TRUE);

			PED::SET_PED_MONEY(pigeonBank, TenK);
			PED::SET_PED_MONEY(pigeonBank2, TenK);
			PED::SET_PED_MONEY(pigeonBank3, TenK);
			PED::SET_PED_MONEY(pigeonBank4, TenK);
			PED::SET_PED_MONEY(pigeonBank5, TenK);
			PED::SET_PED_MONEY(pigeonBank6, TenK);
			PED::SET_PED_MONEY(pigeonBank7, TenK);
			PED::SET_PED_MONEY(pigeonBank8, TenK);
			PED::SET_PED_MONEY(pigeonBank9, TenK);

			ENTITY::SET_ENTITY_HEALTH(pigeonBank, 0);
			ENTITY::SET_ENTITY_HEALTH(pigeonBank2, 0);
			ENTITY::SET_ENTITY_HEALTH(pigeonBank3, 0);
			ENTITY::SET_ENTITY_HEALTH(pigeonBank4, 0);
			ENTITY::SET_ENTITY_HEALTH(pigeonBank5, 0);
			ENTITY::SET_ENTITY_HEALTH(pigeonBank6, 0);
			ENTITY::SET_ENTITY_HEALTH(pigeonBank7, 0);
			ENTITY::SET_ENTITY_HEALTH(pigeonBank8, 0);
			ENTITY::SET_ENTITY_HEALTH(pigeonBank9, 0);
			WAIT(200);

			PED::DELETE_PED(&pigeonBank);
			PED::DELETE_PED(&pigeonBank2);
			PED::DELETE_PED(&pigeonBank3);
			PED::DELETE_PED(&pigeonBank4);
			PED::DELETE_PED(&pigeonBank5);
			PED::DELETE_PED(&pigeonBank6);
			PED::DELETE_PED(&pigeonBank7);
			PED::DELETE_PED(&pigeonBank8);
			PED::DELETE_PED(&pigeonBank9);
		}
	}
}

namespace VehList
{

}
bool AutoRepVeh = false;
void AutoVehRep()
{
	if (AutoRepVeh)
	{
		uint AutoVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()));

		VEHICLE::SET_VEHICLE_FIXED(AutoVeh);
		VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(AutoVeh);
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(AutoVeh, 0);
	}
	else
	{
		NULL;
	}
}

bool loop_text = true;

void notifyError(char* text, char* text2, char* Subject)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG("CHAR_GANGAPP", "CHAR_GANGAPP", false, 7, text2, Subject, 1.0, "~r~___ERROR");
	UI::_DRAW_NOTIFICATION(FALSE, FALSE);
} //This works fine!

#pragma region ....
extern int Levels[8000];

void SetRank(int rpvalue)
{
	if (rpvalue < 1 && rpvalue > 8000)
	{
		rpvalue = 8000;
	}
	hooks::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CHAR_SET_RP_GIFT_ADMIN"), Levels[rpvalue], 0); // S_I_S is for stat set int 
	hooks::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CHAR_SET_RP_GIFT_ADMIN"), Levels[rpvalue], 0);

}


int Levels[8000] = { 0, 800, 2100, 3800, 6100, 9500, 12500, 16000, 19800, 24000, 28500, 33400, 38700, 44200, 50200, 56400, 63000, 69900, 77100, 84700, 92500, 100700, 109200, 118000, 127100, 136500, 146200,
156200, 166500, 177100, 188000, 199200, 210700, 222400, 234500, 246800, 259400, 272300, 285500, 299000, 312700, 326800, 341000, 355600, 370500, 385600, 401000, 416600, 432600, 448800, 465200, 482000, 499000,
516300, 533800, 551600, 569600, 588000, 606500, 625400, 644500, 663800, 683400, 703300, 723400, 743800, 764500, 785400, 806500, 827900, 849600, 871500, 893600, 916000, 938700, 961600, 984700, 1008100, 1031800,
1055700, 1079800, 1104200, 1128800, 1153700, 1178800, 1204200, 1229800, 1255600, 1281700, 1308100, 1334600, 1361400, 1388500, 1415800, 1443300, 1471100, 1499100, 1527300, 1555800, 1584350, 1612950, 1641600,
1670300, 1699050, 1727850, 1756700, 1785600, 1814550, 1843550, 1872600, 1901700, 1930850, 1960050, 1989300, 2018600, 2047950, 2077350, 2106800, 2136300, 2165850, 2195450, 2225100, 2254800, 2284550, 2314350,
2344200, 2374100, 2404050, 2434050, 2464100, 2494200, 2524350, 2554550, 2584800, 2615100, 2645450, 2675850, 2706300, 2736800, 2767350, 2797950, 2828600, 2859300, 2890050, 2920850, 2951700, 2982600, 3013550,
3044550, 3075600, 3106700, 3137850, 3169050, 3200300, 3231600, 3262950, 3294350, 3325800, 3357300, 3388850, 3420450, 3452100, 3483800, 3515550, 3547350, 3579200, 3611100, 3643050, 3675050, 3707100, 3739200,
3771350, 3803550, 3835800, 3868100, 3900450, 3932850, 3965300, 3997800, 4030350, 4062950, 4095600, 4128300, 4161050, 4193850, 4226700, 4259600, 4292550, 4325550, 4358600, 4391700, 4424850, 4458050, 4491300,
4524600, 4557950, 4591350, 4624800, 4658300, 4691850, 4725450, 4759100, 4792800, 4826550, 4860350, 4894200, 4928100, 4962050, 4996050, 5030100, 5064200, 5098350, 5132550, 5166800, 5201100, 5235450, 5269850,
5304300, 5338800, 5373350, 5407950, 5442600, 5477300, 5512050, 5546850, 5581700, 5616600, 5651550, 5686550, 5721600, 5756700, 5791850, 5827050, 5862300, 5897600, 5932950, 5968350, 6003800, 6039300, 6074850,
6110450, 6146100, 6181800, 6217550, 6253350, 6289200, 6325100, 6361050, 6397050, 6433100, 6469200, 6505350, 6541550, 6577800, 6614100, 6650450, 6686850, 6723300, 6759800, 6796350, 6832950, 6869600, 6906300,
6943050, 6979850, 7016700, 7053600, 7090550, 7127550, 7164600, 7201700, 7238850, 7276050, 7313300, 7350600, 7387950, 7425350, 7462800, 7500300, 7537850, 7575450, 7613100, 7650800, 7688550, 7726350, 7764200,
7802100, 7840050, 7878050, 7916100, 7954200, 7992350, 8030550, 8068800, 8107100, 8145450, 8183850, 8222300, 8260800, 8299350, 8337950, 8376600, 8415300, 8454050, 8492850, 8531700, 8570600, 8609550, 8648550,
8687600, 8726700, 8765850, 8805050, 8844300, 8883600, 8922950, 8962350, 9001800, 9041300, 9080850, 9120450, 9160100, 9199800, 9239550, 9279350, 9319200, 9359100, 9399050, 9439050, 9479100, 9519200, 9559350,
9599550, 9639800, 9680100, 9720450, 9760850, 9801300, 9841800, 9882350, 9922950, 9963600, 10004300, 10045050, 10085850, 10126700, 10167600, 10208550, 10249550, 10290600, 10331700, 10372850, 10414050, 10455300,
10496600, 10537950, 10579350, 10620800, 10662300, 10703850, 10745450, 10787100, 10828800, 10870550, 10912350, 10954200, 10996100, 11038050, 11080050, 11122100, 11164200, 11206350, 11248550, 11290800, 11333100,
11375450, 11417850, 11460300, 11502800, 11545350, 11587950, 11630600, 11673300, 11716050, 11758850, 11801700, 11844600, 11887550, 11930550, 11973600, 12016700, 12059850, 12103050, 12146300, 12189600, 12232950,
12276350, 12319800, 12363300, 12406850, 12450450, 12494100, 12537800, 12581550, 12625350, 12669200, 12713100, 12757050, 12801050, 12845100, 12889200, 12933350, 12977550, 13021800, 13066100, 13110450, 13154850,
13199300, 13243800, 13288350, 13332950, 13377600, 13422300, 13467050, 13511850, 13556700, 13601600, 13646550, 13691550, 13736600, 13781700, 13826850, 13872050, 13917300, 13962600, 14007950, 14053350, 14098800,
14144300, 14189850, 14235450, 14281100, 14326800, 14372550, 14418350, 14464200, 14510100, 14556050, 14602050, 14648100, 14694200, 14740350, 14786550, 14832800, 14879100, 14925450, 14971850, 15018300, 15064800,
15111350, 15157950, 15204600, 15251300, 15298050, 15344850, 15391700, 15438600, 15485550, 15532550, 15579600, 15626700, 15673850, 15721050, 15768300, 15815600, 15862950, 15910350, 15957800, 16005300, 16052850,
16100450, 16148100, 16195800, 16243550, 16291350, 16339200, 16387100, 16435050, 16483050, 16531100, 16579200, 16627350, 16675550, 16723800, 16772100, 16820450, 16868850, 16917300, 16965800, 17014350, 17062950,
17111600, 17160300, 17209050, 17257850, 17306700, 17355600, 17404550, 17453550, 17502600, 17551700, 17600850, 17650050, 17699300, 17748600, 17797950, 17847350, 17896800, 17946300, 17995850, 18045450, 18095100,
18144800, 18194550, 18244350, 18294200, 18344100, 18394050, 18444050, 18494100, 18544200, 18594350, 18644550, 18694800, 18745100, 18795450, 18845850, 18896300, 18946800, 18997350, 19047950, 19098600, 19149300,
19200050, 19250850, 19301700, 19352600, 19403550, 19454550, 19505600, 19556700, 19607850, 19659050, 19710300, 19761600, 19812950, 19864350, 19915800, 19967300, 20018850, 20070450, 20122100, 20173800, 20225550,
20277350, 20329200, 20381100, 20433050, 20485050, 20537100, 20589200, 20641350, 20693550, 20745800, 20798100, 20850450, 20902850, 20955300, 21007800, 21060350, 21112950, 21165600, 21218300, 21271050, 21323850,
21376700, 21429600, 21482550, 21535550, 21588600, 21641700, 21694850, 21748050, 21801300, 21854600, 21907950, 21961350, 22014800, 22068300, 22121850, 22175450, 22229100, 22282800, 22336550, 22390350, 22444200,
22498100, 22552050, 22606050, 22660100, 22714200, 22768350, 22822550, 22876800, 22931100, 22985450, 23039850, 23094300, 23148800, 23203350, 23257950, 23312600, 23367300, 23422050, 23476850, 23531700, 23586600,
23641550, 23696550, 23751600, 23806700, 23861850, 23917050, 23972300, 24027600, 24082950, 24138350, 24193800, 24249300, 24304850, 24360450, 24416100, 24471800, 24527550, 24583350, 24639200, 24695100, 24751050,
24807050, 24863100, 24919200, 24975350, 25031550, 25087800, 25144100, 25200450, 25256850, 25313300, 25369800, 25426350, 25482950, 25539600, 25596300, 25653050, 25709850, 25766700, 25823600, 25880550, 25937550,
25994600, 26051700, 26108850, 26166050, 26223300, 26280600, 26337950, 26395350, 26452800, 26510300, 26567850, 26625450, 26683100, 26740800, 26798550, 26856350, 26914200, 26972100, 27030050, 27088050, 27146100,
27204200, 27262350, 27320550, 27378800, 27437100, 27495450, 27553850, 27612300, 27670800, 27729350, 27787950, 27846600, 27905300, 27964050, 28022850, 28081700, 28140600, 28199550, 28258550, 28317600, 28376700,
28435850, 28495050, 28554300, 28613600, 28672950, 28732350, 28791800, 28851300, 28910850, 28970450, 29030100, 29089800, 29149550, 29209350, 29269200, 29329100, 29389050, 29449050, 29509100, 29569200, 29629350,
29689550, 29749800, 29810100, 29870450, 29930850, 29991300, 30051800, 30112350, 30172950, 30233600, 30294300, 30355050, 30415850, 30476700, 30537600, 30598550, 30659550, 30720600, 30781700, 30842850, 30904050,
30965300, 31026600, 31087950, 31149350, 31210800, 31272300, 31333850, 31395450, 31457100, 31518800, 31580550, 31642350, 31704200, 31766100, 31828050, 31890050, 31952100, 32014200, 32076350, 32138550, 32200800,
32263100, 32325450, 32387850, 32450300, 32512800, 32575350, 32637950, 32700600, 32763300, 32826050, 32888850, 32951700, 33014600, 33077550, 33140550, 33203600, 33266700, 33329850, 33393050, 33456300, 33519600,
33582950, 33646350, 33709800, 33773300, 33836850, 33900450, 33964100, 34027800, 34091550, 34155350, 34219200, 34283100, 34347050, 34411050, 34475100, 34539200, 34603350, 34667550, 34731800, 34796100, 34860450,
34924850, 34989300, 35053800, 35118350, 35182950, 35247600, 35312300, 35377050, 35441850, 35506700, 35571600, 35636550, 35701550, 35766600, 35831700, 35896850, 35962050, 36027300, 36092600, 36157950, 36223350,
36288800, 36354300, 36419850, 36485450, 36551100, 36616800, 36682550, 36748350, 36814200, 36880100, 36946050, 37012050, 37078100, 37144200, 37210350, 37276550, 37342800, 37409100, 37475450, 37541850, 37608300,
37674800, 37741350, 37807950, 37874600, 37941300, 38008050, 38074850, 38141700, 38208600, 38275550, 38342550, 38409600, 38476700, 38543850, 38611050, 38678300, 38745600, 38812950, 38880350, 38947800, 39015300,
39082850, 39150450, 39218100, 39285800, 39353550, 39421350, 39489200, 39557100, 39625050, 39693050, 39761100, 39829200, 39897350, 39965550, 40033800, 40102100, 40170450, 40238850, 40307300, 40375800, 40444350,
40512950, 40581600, 40650300, 40719050, 40787850, 40856700, 40925600, 40994550, 41063550, 41132600, 41201700, 41270850, 41340050, 41409300, 41478600, 41547950, 41617350, 41686800, 41756300, 41825850, 41895450,
41965100, 42034800, 42104550, 42174350, 42244200, 42314100, 42384050, 42454050, 42524100, 42594200, 42664350, 42734550, 42804800, 42875100, 42945450, 43015850, 43086300, 43156800, 43227350, 43297950, 43368600,
43439300, 43510050, 43580850, 43651700, 43722600, 43793550, 43864550, 43935600, 44006700, 44077850, 44149050, 44220300, 44291600, 44362950, 44434350, 44505800, 44577300, 44648850, 44720450, 44792100, 44863800,
44935550, 45007350, 45079200, 45151100, 45223050, 45295050, 45367100, 45439200, 45511350, 45583550, 45655800, 45728100, 45800450, 45872850, 45945300, 46017800, 46090350, 46162950, 46235600, 46308300, 46381050,
46453850, 46526700, 46599600, 46672550, 46745550, 46818600, 46891700, 46964850, 47038050, 47111300, 47184600, 47257950, 47331350, 47404800, 47478300, 47551850, 47625450, 47699100, 47772800, 47846550, 47920350,
47994200, 48068100, 48142050, 48216050, 48290100, 48364200, 48438350, 48512550, 48586800, 48661100, 48735450, 48809850, 48884300, 48958800, 49033350, 49107950, 49182600, 49257300, 49332050, 49406850, 49481700,
49556600, 49631550, 49706550, 49781600, 49856700, 49931850, 50007050, 50082300, 50157600, 50232950, 50308350, 50383800, 50459300, 50534850, 50610450, 50686100, 50761800, 50837550, 50913350, 50989200, 51065100,
51141050, 51217050, 51293100, 51369200, 51445350, 51521550, 51597800, 51674100, 51750450, 51826850, 51903300, 51979800, 52056350, 52132950, 52209600, 52286300, 52363050, 52439850, 52516700, 52593600, 52670550,
52747550, 52824600, 52901700, 52978850, 53056050, 53133300, 53210600, 53287950, 53365350, 53442800, 53520300, 53597850, 53675450, 53753100, 53830800, 53908550, 53986350, 54064200, 54142100, 54220050, 54298050,
54376100, 54454200, 54532350, 54610550, 54688800, 54767100, 54845450, 54923850, 55002300, 55080800, 55159350, 55237950, 55316600, 55395300, 55474050, 55552850, 55631700, 55710600, 55789550, 55868550, 55947600,
56026700, 56105850, 56185050, 56264300, 56343600, 56422950, 56502350, 56581800, 56661300, 56740850, 56820450, 56900100, 56979800, 57059550, 57139350, 57219200, 57299100, 57379050, 57459050, 57539100, 57619200,
57699350, 57779550, 57859800, 57940100, 58020450, 58100850, 58181300, 58261800, 58342350, 58422950, 58503600, 58584300, 58665050, 58745850, 58826700, 58907600, 58988550, 59069550, 59150600, 59231700, 59312850,
59394050, 59475300, 59556600, 59637950, 59719350, 59800800, 59882300, 59963850, 60045450, 60127100, 60208800, 60290550, 60372350, 60454200, 60536100, 60618050, 60700050, 60782100, 60864200, 60946350, 61028550,
61110800, 61193100, 61275450, 61357850, 61440300, 61522800, 61605350, 61687950, 61770600, 61853300, 61936050, 62018850, 62101700, 62184600, 62267550, 62350550, 62433600, 62516700, 62599850, 62683050, 62766300,
62849600, 62932950, 63016350, 63099800, 63183300, 63266850, 63350450, 63434100, 63517800, 63601550, 63685350, 63769200, 63853100, 63937050, 64021050, 64105100, 64189200, 64273350, 64357550, 64441800, 64526100,
64610450, 64694850, 64779300, 64863800, 64948350, 65032950, 65117600, 65202300, 65287050, 65371850, 65456700, 65541600, 65626550, 65711550, 65796600, 65881700, 65966850, 66052050, 66137300, 66222600, 66307950,
66393350, 66478800, 66564300, 66649850, 66735450, 66821100, 66906800, 66992550, 67078350, 67164200, 67250100, 67336050, 67422050, 67508100, 67594200, 67680350, 67766550, 67852800, 67939100, 68025450, 68111850,
68198300, 68284800, 68371350, 68457950, 68544600, 68631300, 68718050, 68804850, 68891700, 68978600, 69065550, 69152550, 69239600, 69326700, 69413850, 69501050, 69588300, 69675600, 69762950, 69850350, 69937800,
70025300, 70112850, 70200450, 70288100, 70375800, 70463550, 70551350, 70639200, 70727100, 70815050, 70903050, 70991100, 71079200, 71167350, 71255550, 71343800, 71432100, 71520450, 71608850, 71697300, 71785800,
71874350, 71962950, 72051600, 72140300, 72229050, 72317850, 72406700, 72495600, 72584550, 72673550, 72762600, 72851700, 72940850, 73030050, 73119300, 73208600, 73297950, 73387350, 73476800, 73566300, 73655850,
73745450, 73835100, 73924800, 74014550, 74104350, 74194200, 74284100, 74374050, 74464050, 74554100, 74644200, 74734350, 74824550, 74914800, 75005100, 75095450, 75185850, 75276300, 75366800, 75457350, 75547950,
75638600, 75729300, 75820050, 75910850, 76001700, 76092600, 76183550, 76274550, 76365600, 76456700, 76547850, 76639050, 76730300, 76821600, 76912950, 77004350, 77095800, 77187300, 77278850, 77370450, 77462100,
77553800, 77645550, 77737350, 77829200, 77921100, 78013050, 78105050, 78197100, 78289200, 78381350, 78473550, 78565800, 78658100, 78750450, 78842850, 78935300, 79027800, 79120350, 79212950, 79305600, 79398300,
79491050, 79583850, 79676700, 79769600, 79862550, 79955550, 80048600, 80141700, 80234850, 80328050, 80421300, 80514600, 80607950, 80701350, 80794800, 80888300, 80981850, 81075450, 81169100, 81262800, 81356550,
81450350, 81544200, 81638100, 81732050, 81826050, 81920100, 82014200, 82108350, 82202550, 82296800, 82391100, 82485450, 82579850, 82674300, 82768800, 82863350, 82957950, 83052600, 83147300, 83242050, 83336850,
83431700, 83526600, 83621550, 83716550, 83811600, 83906700, 84001850, 84097050, 84192300, 84287600, 84382950, 84478350, 84573800, 84669300, 84764850, 84860450, 84956100, 85051800, 85147550, 85243350, 85339200,
85435100, 85531050, 85627050, 85723100, 85819200, 85915350, 86011550, 86107800, 86204100, 86300450, 86396850, 86493300, 86589800, 86686350, 86782950, 86879600, 86976300, 87073050, 87169850, 87266700, 87363600,
87460550, 87557550, 87654600, 87751700, 87848850, 87946050, 88043300, 88140600, 88237950, 88335350, 88432800, 88530300, 88627850, 88725450, 88823100, 88920800, 89018550, 89116350, 89214200, 89312100, 89410050,
89508050, 89606100, 89704200, 89802350, 89900550, 89998800, 90097100, 90195450, 90293850, 90392300, 90490800, 90589350, 90687950, 90786600, 90885300, 90984050, 91082850, 91181700, 91280600, 91379550, 91478550,
91577600, 91676700, 91775850, 91875050, 91974300, 92073600, 92172950, 92272350, 92371800, 92471300, 92570850, 92670450, 92770100, 92869800, 92969550, 93069350, 93169200, 93269100, 93369050, 93469050, 93569100,
93669200, 93769350, 93869550, 93969800, 94070100, 94170450, 94270850, 94371300, 94471800, 94572350, 94672950, 94773600, 94874300, 94975050, 95075850, 95176700, 95277600, 95378550, 95479550, 95580600, 95681700,
95782850, 95884050, 95985300, 96086600, 96187950, 96289350, 96390800, 96492300, 96593850, 96695450, 96797100, 96898800, 97000550, 97102350, 97204200, 97306100, 97408050, 97510050, 97612100, 97714200, 97816350,
97918550, 98020800, 98123100, 98225450, 98327850, 98430300, 98532800, 98635350, 98737950, 98840600, 98943300, 99046050, 99148850, 99251700, 99354600, 99457550, 99560550, 99663600, 99766700, 99869850, 99973050,
100076300, 100179600, 100282950, 100386350, 100489800, 100593300, 100696850, 100800450, 100904100, 101007800, 101111550, 101215350, 101319200, 101423100, 101527050, 101631050, 101735100, 101839200, 101943350,
102047550, 102151800, 102256100, 102360450, 102464850, 102569300, 102673800, 102778350, 102882950, 102987600, 103092300, 103197050, 103301850, 103406700, 103511600, 103616550, 103721550, 103826600, 103931700,
104036850, 104142050, 104247300, 104352600, 104457950, 104563350, 104668800, 104774300, 104879850, 104985450, 105091100, 105196800, 105302550, 105408350, 105514200, 105620100, 105726050, 105832050, 105938100,
106044200, 106150350, 106256550, 106362800, 106469100, 106575450, 106681850, 106788300, 106894800, 107001350, 107107950, 107214600, 107321300, 107428050, 107534850, 107641700, 107748600, 107855550, 107962550,
108069600, 108176700, 108283850, 108391050, 108498300, 108605600, 108712950, 108820350, 108927800, 109035300, 109142850, 109250450, 109358100, 109465800, 109573550, 109681350, 109789200, 109897100, 110005050,
110113050, 110221100, 110329200, 110437350, 110545550, 110653800, 110762100, 110870450, 110978850, 111087300, 111195800, 111304350, 111412950, 111521600, 111630300, 111739050, 111847850, 111956700, 112065600,
112174550, 112283550, 112392600, 112501700, 112610850, 112720050, 112829300, 112938600, 113047950, 113157350, 113266800, 113376300, 113485850, 113595450, 113705100, 113814800, 113924550, 114034350, 114144200,
114254100, 114364050, 114474050, 114584100, 114694200, 114804350, 114914550, 115024800, 115135100, 115245450, 115355850, 115466300, 115576800, 115687350, 115797950, 115908600, 116019300, 116130050, 116240850,
116351700, 116462600, 116573550, 116684550, 116795600, 116906700, 117017850, 117129050, 117240300, 117351600, 117462950, 117574350, 117685800, 117797300, 117908850, 118020450, 118132100, 118243800, 118355550,
118467350, 118579200, 118691100, 118803050, 118915050, 119027100, 119139200, 119251350, 119363550, 119475800, 119588100, 119700450, 119812850, 119925300, 120037800, 120150350, 120262950, 120375600, 120488300,
120601050, 120713850, 120826700, 120939600, 121052550, 121165550, 121278600, 121391700, 121504850, 121618050, 121731300, 121844600, 121957950, 122071350, 122184800, 122298300, 122411850, 122525450, 122639100,
122752800, 122866550, 122980350, 123094200, 123208100, 123322050, 123436050, 123550100, 123664200, 123778350, 123892550, 124006800, 124121100, 124235450, 124349850, 124464300, 124578800, 124693350, 124807950,
124922600, 125037300, 125152050, 125266850, 125381700, 125496600, 125611550, 125726550, 125841600, 125956700, 126071850, 126187050, 126302300, 126417600, 126532950, 126648350, 126763800, 126879300, 126994850,
127110450, 127226100, 127341800, 127457550, 127573350, 127689200, 127805100, 127921050, 128037050, 128153100, 128269200, 128385350, 128501550, 128617800, 128734100, 128850450, 128966850, 129083300, 129199800,
129316350, 129432950, 129549600, 129666300, 129783050, 129899850, 130016700, 130133600, 130250550, 130367550, 130484600, 130601700, 130718850, 130836050, 130953300, 131070600, 131187950, 131305350, 131422800,
131540300, 131657850, 131775450, 131893100, 132010800, 132128550, 132246350, 132364200, 132482100, 132600050, 132718050, 132836100, 132954200, 133072350, 133190550, 133308800, 133427100, 133545450, 133663850,
133782300, 133900800, 134019350, 134137950, 134256600, 134375300, 134494050, 134612850, 134731700, 134850600, 134969550, 135088550, 135207600, 135326700, 135445850, 135565050, 135684300, 135803600, 135922950,
136042350, 136161800, 136281300, 136400850, 136520450, 136640100, 136759800, 136879550, 136999350, 137119200, 137239100, 137359050, 137479050, 137599100, 137719200, 137839350, 137959550, 138079800, 138200100,
138320450, 138440850, 138561300, 138681800, 138802350, 138922950, 139043600, 139164300, 139285050, 139405850, 139526700, 139647600, 139768550, 139889550, 140010600, 140131700, 140252850, 140374050, 140495300,
140616600, 140737950, 140859350, 140980800, 141102300, 141223850, 141345450, 141467100, 141588800, 141710550, 141832350, 141954200, 142076100, 142198050, 142320050, 142442100, 142564200, 142686350, 142808550,
142930800, 143053100, 143175450, 143297850, 143420300, 143542800, 143665350, 143787950, 143910600, 144033300, 144156050, 144278850, 144401700, 144524600, 144647550, 144770550, 144893600, 145016700, 145139850,
145263050, 145386300, 145509600, 145632950, 145756350, 145879800, 146003300, 146126850, 146250450, 146374100, 146497800, 146621550, 146745350, 146869200, 146993100, 147117050, 147241050, 147365100, 147489200,
147613350, 147737550, 147861800, 147986100, 148110450, 148234850, 148359300, 148483800, 148608350, 148732950, 148857600, 148982300, 149107050, 149231850, 149356700, 149481600, 149606550, 149731550, 149856600,
149981700, 150106850, 150232050, 150357300, 150482600, 150607950, 150733350, 150858800, 150984300, 151109850, 151235450, 151361100, 151486800, 151612550, 151738350, 151864200, 151990100, 152116050, 152242050,
152368100, 152494200, 152620350, 152746550, 152872800, 152999100, 153125450, 153251850, 153378300, 153504800, 153631350, 153757950, 153884600, 154011300, 154138050, 154264850, 154391700, 154518600, 154645550,
154772550, 154899600, 155026700, 155153850, 155281050, 155408300, 155535600, 155662950, 155790350, 155917800, 156045300, 156172850, 156300450, 156428100, 156555800, 156683550, 156811350, 156939200, 157067100,
157195050, 157323050, 157451100, 157579200, 157707350, 157835550, 157963800, 158092100, 158220450, 158348850, 158477300, 158605800, 158734350, 158862950, 158991600, 159120300, 159249050, 159377850, 159506700,
159635600, 159764550, 159893550, 160022600, 160151700, 160280850, 160410050, 160539300, 160668600, 160797950, 160927350, 161056800, 161186300, 161315850, 161445450, 161575100, 161704800, 161834550, 161964350,
162094200, 162224100, 162354050, 162484050, 162614100, 162744200, 162874350, 163004550, 163134800, 163265100, 163395450, 163525850, 163656300, 163786800, 163917350, 164047950, 164178600, 164309300, 164440050,
164570850, 164701700, 164832600, 164963550, 165094550, 165225600, 165356700, 165487850, 165619050, 165750300, 165881600, 166012950, 166144350, 166275800, 166407300, 166538850, 166670450, 166802100, 166933800,
167065550, 167197350, 167329200, 167461100, 167593050, 167725050, 167857100, 167989200, 168121350, 168253550, 168385800, 168518100, 168650450, 168782850, 168915300, 169047800, 169180350, 169312950, 169445600,
169578300, 169711050, 169843850, 169976700, 170109600, 170242550, 170375550, 170508600, 170641700, 170774850, 170908050, 171041300, 171174600, 171307950, 171441350, 171574800, 171708300, 171841850, 171975450,
172109100, 172242800, 172376550, 172510350, 172644200, 172778100, 172912050, 173046050, 173180100, 173314200, 173448350, 173582550, 173716800, 173851100, 173985450, 174119850, 174254300, 174388800, 174523350,
174657950, 174792600, 174927300, 175062050, 175196850, 175331700, 175466600, 175601550, 175736550, 175871600, 176006700, 176141850, 176277050, 176412300, 176547600, 176682950, 176818350, 176953800, 177089300,
177224850, 177360450, 177496100, 177631800, 177767550, 177903350, 178039200, 178175100, 178311050, 178447050, 178583100, 178719200, 178855350, 178991550, 179127800, 179264100, 179400450, 179536850, 179673300,
179809800, 179946350, 180082950, 180219600, 180356300, 180493050, 180629850, 180766700, 180903600, 181040550, 181177550, 181314600, 181451700, 181588850, 181726050, 181863300, 182000600, 182137950, 182275350,
182412800, 182550300, 182687850, 182825450, 182963100, 183100800, 183238550, 183376350, 183514200, 183652100, 183790050, 183928050, 184066100, 184204200, 184342350, 184480550, 184618800, 184757100, 184895450,
185033850, 185172300, 185310800, 185449350, 185587950, 185726600, 185865300, 186004050, 186142850, 186281700, 186420600, 186559550, 186698550, 186837600, 186976700, 187115850, 187255050, 187394300, 187533600,
187672950, 187812350, 187951800, 188091300, 188230850, 188370450, 188510100, 188649800, 188789550, 188929350, 189069200, 189209100, 189349050, 189489050, 189629100, 189769200, 189909350, 190049550, 190189800,
190330100, 190470450, 190610850, 190751300, 190891800, 191032350, 191172950, 191313600, 191454300, 191595050, 191735850, 191876700, 192017600, 192158550, 192299550, 192440600, 192581700, 192722850, 192864050,
193005300, 193146600, 193287950, 193429350, 193570800, 193712300, 193853850, 193995450, 194137100, 194278800, 194420550, 194562350, 194704200, 194846100, 194988050, 195130050, 195272100, 195414200, 195556350,
195698550, 195840800, 195983100, 196125450, 196267850, 196410300, 196552800, 196695350, 196837950, 196980600, 197123300, 197266050, 197408850, 197551700, 197694600, 197837550, 197980550, 198123600, 198266700,
198409850, 198553050, 198696300, 198839600, 198982950, 199126350, 199269800, 199413300, 199556850, 199700450, 199844100, 199987800, 200131550, 200275350, 200419200, 200563100, 200707050, 200851050, 200995100,
201139200, 201283350, 201427550, 201571800, 201716100, 201860450, 202004850, 202149300, 202293800, 202438350, 202582950, 202727600, 202872300, 203017050, 203161850, 203306700, 203451600, 203596550, 203741550,
203886600, 204031700, 204176850, 204322050, 204467300, 204612600, 204757950, 204903350, 205048800, 205194300, 205339850, 205485450, 205631100, 205776800, 205922550, 206068350, 206214200, 206360100, 206506050,
206652050, 206798100, 206944200, 207090350, 207236550, 207382800, 207529100, 207675450, 207821850, 207968300, 208114800, 208261350, 208407950, 208554600, 208701300, 208848050, 208994850, 209141700, 209288600,
209435550, 209582550, 209729600, 209876700, 210023850, 210171050, 210318300, 210465600, 210612950, 210760350, 210907800, 211055300, 211202850, 211350450, 211498100, 211645800, 211793550, 211941350, 212089200,
212237100, 212385050, 212533050, 212681100, 212829200, 212977350, 213125550, 213273800, 213422100, 213570450, 213718850, 213867300, 214015800, 214164350, 214312950, 214461600, 214610300, 214759050, 214907850,
215056700, 215205600, 215354550, 215503550, 215652600, 215801700, 215950850, 216100050, 216249300, 216398600, 216547950, 216697350, 216846800, 216996300, 217145850, 217295450, 217445100, 217594800, 217744550,
217894350, 218044200, 218194100, 218344050, 218494050, 218644100, 218794200, 218944350, 219094550, 219244800, 219395100, 219545450, 219695850, 219846300, 219996800, 220147350, 220297950, 220448600, 220599300,
220750050, 220900850, 221051700, 221202600, 221353550, 221504550, 221655600, 221806700, 221957850, 222109050, 222260300, 222411600, 222562950, 222714350, 222865800, 223017300, 223168850, 223320450, 223472100,
223623800, 223775550, 223927350, 224079200, 224231100, 224383050, 224535050, 224687100, 224839200, 224991350, 225143550, 225295800, 225448100, 225600450, 225752850, 225905300, 226057800, 226210350, 226362950,
226515600, 226668300, 226821050, 226973850, 227126700, 227279600, 227432550, 227585550, 227738600, 227891700, 228044850, 228198050, 228351300, 228504600, 228657950, 228811350, 228964800, 229118300, 229271850,
229425450, 229579100, 229732800, 229886550, 230040350, 230194200, 230348100, 230502050, 230656050, 230810100, 230964200, 231118350, 231272550, 231426800, 231581100, 231735450, 231889850, 232044300, 232198800,
232353350, 232507950, 232662600, 232817300, 232972050, 233126850, 233281700, 233436600, 233591550, 233746550, 233901600, 234056700, 234211850, 234367050, 234522300, 234677600, 234832950, 234988350, 235143800,
235299300, 235454850, 235610450, 235766100, 235921800, 236077550, 236233350, 236389200, 236545100, 236701050, 236857050, 237013100, 237169200, 237325350, 237481550, 237637800, 237794100, 237950450, 238106850,
238263300, 238419800, 238576350, 238732950, 238889600, 239046300, 239203050, 239359850, 239516700, 239673600, 239830550, 239987550, 240144600, 240301700, 240458850, 240616050, 240773300, 240930600, 241087950,
241245350, 241402800, 241560300, 241717850, 241875450, 242033100, 242190800, 242348550, 242506350, 242664200, 242822100, 242980050, 243138050, 243296100, 243454200, 243612350, 243770550, 243928800, 244087100,
244245450, 244403850, 244562300, 244720800, 244879350, 245037950, 245196600, 245355300, 245514050, 245672850, 245831700, 245990600, 246149550, 246308550, 246467600, 246626700, 246785850, 246945050, 247104300,
247263600, 247422950, 247582350, 247741800, 247901300, 248060850, 248220450, 248380100, 248539800, 248699550, 248859350, 249019200, 249179100, 249339050, 249499050, 249659100, 249819200, 249979350, 250139550,
250299800, 250460100, 250620450, 250780850, 250941300, 251101800, 251262350, 251422950, 251583600, 251744300, 251905050, 252065850, 252226700, 252387600, 252548550, 252709550, 252870600, 253031700, 253192850,
253354050, 253515300, 253676600, 253837950, 253999350, 254160800, 254322300, 254483850, 254645450, 254807100, 254968800, 255130550, 255292350, 255454200, 255616100, 255778050, 255940050, 256102100, 256264200,
256426350, 256588550, 256750800, 256913100, 257075450, 257237850, 257400300, 257562800, 257725350, 257887950, 258050600, 258213300, 258376050, 258538850, 258701700, 258864600, 259027550, 259190550, 259353600,
259516700, 259679850, 259843050, 260006300, 260169600, 260332950, 260496350, 260659800, 260823300, 260986850, 261150450, 261314100, 261477800, 261641550, 261805350, 261969200, 262133100, 262297050, 262461050,
262625100, 262789200, 262953350, 263117550, 263281800, 263446100, 263610450, 263774850, 263939300, 264103800, 264268350, 264432950, 264597600, 264762300, 264927050, 265091850, 265256700, 265421600, 265586550,
265751550, 265916600, 266081700, 266246850, 266412050, 266577300, 266742600, 266907950, 267073350, 267238800, 267404300, 267569850, 267735450, 267901100, 268066800, 268232550, 268398350, 268564200, 268730100,
268896050, 269062050, 269228100, 269394200, 269560350, 269726550, 269892800, 270059100, 270225450, 270391850, 270558300, 270724800, 270891350, 271057950, 271224600, 271391300, 271558050, 271724850, 271891700,
272058600, 272225550, 272392550, 272559600, 272726700, 272893850, 273061050, 273228300, 273395600, 273562950, 273730350, 273897800, 274065300, 274232850, 274400450, 274568100, 274735800, 274903550, 275071350,
275239200, 275407100, 275575050, 275743050, 275911100, 276079200, 276247350, 276415550, 276583800, 276752100, 276920450, 277088850, 277257300, 277425800, 277594350, 277762950, 277931600, 278100300, 278269050,
278437850, 278606700, 278775600, 278944550, 279113550, 279282600, 279451700, 279620850, 279790050, 279959300, 280128600, 280297950, 280467350, 280636800, 280806300, 280975850, 281145450, 281315100, 281484800,
281654550, 281824350, 281994200, 282164100, 282334050, 282504050, 282674100, 282844200, 283014350, 283184550, 283354800, 283525100, 283695450, 283865850, 284036300, 284206800, 284377350, 284547950, 284718600,
284889300, 285060050, 285230850, 285401700, 285572600, 285743550, 285914550, 286085600, 286256700, 286427850, 286599050, 286770300, 286941600, 287112950, 287284350, 287455800, 287627300, 287798850, 287970450,
288142100, 288313800, 288485550, 288657350, 288829200, 289001100, 289173050, 289345050, 289517100, 289689200, 289861350, 290033550, 290205800, 290378100, 290550450, 290722850, 290895300, 291067800, 291240350,
291412950, 291585600, 291758300, 291931050, 292103850, 292276700, 292449600, 292622550, 292795550, 292968600, 293141700, 293314850, 293488050, 293661300, 293834600, 294007950, 294181350, 294354800, 294528300,
294701850, 294875450, 295049100, 295222800, 295396550, 295570350, 295744200, 295918100, 296092050, 296266050, 296440100, 296614200, 296788350, 296962550, 297136800, 297311100, 297485450, 297659850, 297834300,
298008800, 298183350, 298357950, 298532600, 298707300, 298882050, 299056850, 299231700, 299406600, 299581550, 299756550, 299931600, 300106700, 300281850, 300457050, 300632300, 300807600, 300982950, 301158350,
301333800, 301509300, 301684850, 301860450, 302036100, 302211800, 302387550, 302563350, 302739200, 302915100, 303091050, 303267050, 303443100, 303619200, 303795350, 303971550, 304147800, 304324100, 304500450,
304676850, 304853300, 305029800, 305206350, 305382950, 305559600, 305736300, 305913050, 306089850, 306266700, 306443600, 306620550, 306797550, 306974600, 307151700, 307328850, 307506050, 307683300, 307860600,
308037950, 308215350, 308392800, 308570300, 308747850, 308925450, 309103100, 309280800, 309458550, 309636350, 309814200, 309992100, 310170050, 310348050, 310526100, 310704200, 310882350, 311060550, 311238800,
311417100, 311595450, 311773850, 311952300, 312130800, 312309350, 312487950, 312666600, 312845300, 313024050, 313202850, 313381700, 313560600, 313739550, 313918550, 314097600, 314276700, 314455850, 314635050,
314814300, 314993600, 315172950, 315352350, 315531800, 315711300, 315890850, 316070450, 316250100, 316429800, 316609550, 316789350, 316969200, 317149100, 317329050, 317509050, 317689100, 317869200, 318049350,
318229550, 318409800, 318590100, 318770450, 318950850, 319131300, 319311800, 319492350, 319672950, 319853600, 320034300, 320215050, 320395850, 320576700, 320757600, 320938550, 321119550, 321300600, 321481700,
321662850, 321844050, 322025300, 322206600, 322387950, 322569350, 322750800, 322932300, 323113850, 323295450, 323477100, 323658800, 323840550, 324022350, 324204200, 324386100, 324568050, 324750050, 324932100,
325114200, 325296350, 325478550, 325660800, 325843100, 326025450, 326207850, 326390300, 326572800, 326755350, 326937950, 327120600, 327303300, 327486050, 327668850, 327851700, 328034600, 328217550, 328400550,
328583600, 328766700, 328949850, 329133050, 329316300, 329499600, 329682950, 329866350, 330049800, 330233300, 330416850, 330600450, 330784100, 330967800, 331151550, 331335350, 331519200, 331703100, 331887050,
332071050, 332255100, 332439200, 332623350, 332807550, 332991800, 333176100, 333360450, 333544850, 333729300, 333913800, 334098350, 334282950, 334467600, 334652300, 334837050, 335021850, 335206700, 335391600,
335576550, 335761550, 335946600, 336131700, 336316850, 336502050, 336687300, 336872600, 337057950, 337243350, 337428800, 337614300, 337799850, 337985450, 338171100, 338356800, 338542550, 338728350, 338914200,
339100100, 339286050, 339472050, 339658100, 339844200, 340030350, 340216550, 340402800, 340589100, 340775450, 340961850, 341148300, 341334800, 341521350, 341707950, 341894600, 342081300, 342268050, 342454850,
342641700, 342828600, 343015550, 343202550, 343389600, 343576700, 343763850, 343951050, 344138300, 344325600, 344512950, 344700350, 344887800, 345075300, 345262850, 345450450, 345638100, 345825800, 346013550,
346201350, 346389200, 346577100, 346765050, 346953050, 347141100, 347329200, 347517350, 347705550, 347893800, 348082100, 348270450, 348458850, 348647300, 348835800, 349024350, 349212950, 349401600, 349590300,
349779050, 349967850, 350156700, 350345600, 350534550, 350723550, 350912600, 351101700, 351290850, 351480050, 351669300, 351858600, 352047950, 352237350, 352426800, 352616300, 352805850, 352995450, 353185100,
353374800, 353564550, 353754350, 353944200, 354134100, 354324050, 354514050, 354704100, 354894200, 355084350, 355274550, 355464800, 355655100, 355845450, 356035850, 356226300, 356416800, 356607350, 356797950,
356988600, 357179300, 357370050, 357560850, 357751700, 357942600, 358133550, 358324550, 358515600, 358706700, 358897850, 359089050, 359280300, 359471600, 359662950, 359854350, 360045800, 360237300, 360428850,
360620450, 360812100, 361003800, 361195550, 361387350, 361579200, 361771100, 361963050, 362155050, 362347100, 362539200, 362731350, 362923550, 363115800, 363308100, 363500450, 363692850, 363885300, 364077800,
364270350, 364462950, 364655600, 364848300, 365041050, 365233850, 365426700, 365619600, 365812550, 366005550, 366198600, 366391700, 366584850, 366778050, 366971300, 367164600, 367357950, 367551350, 367744800,
367938300, 368131850, 368325450, 368519100, 368712800, 368906550, 369100350, 369294200, 369488100, 369682050, 369876050, 370070100, 370264200, 370458350, 370652550, 370846800, 371041100, 371235450, 371429850,
371624300, 371818800, 372013350, 372207950, 372402600, 372597300, 372792050, 372986850, 373181700, 373376600, 373571550, 373766550, 373961600, 374156700, 374351850, 374547050, 374742300, 374937600, 375132950,
375328350, 375523800, 375719300, 375914850, 376110450, 376306100, 376501800, 376697550, 376893350, 377089200, 377285100, 377481050, 377677050, 377873100, 378069200, 378265350, 378461550, 378657800, 378854100,
379050450, 379246850, 379443300, 379639800, 379836350, 380032950, 380229600, 380426300, 380623050, 380819850, 381016700, 381213600, 381410550, 381607550, 381804600, 382001700, 382198850, 382396050, 382593300,
382790600, 382987950, 383185350, 383382800, 383580300, 383777850, 383975450, 384173100, 384370800, 384568550, 384766350, 384964200, 385162100, 385360050, 385558050, 385756100, 385954200, 386152350, 386350550,
386548800, 386747100, 386945450, 387143850, 387342300, 387540800, 387739350, 387937950, 388136600, 388335300, 388534050, 388732850, 388931700, 389130600, 389329550, 389528550, 389727600, 389926700, 390125850,
390325050, 390524300, 390723600, 390922950, 391122350, 391321800, 391521300, 391720850, 391920450, 392120100, 392319800, 392519550, 392719350, 392919200, 393119100, 393319050, 393519050, 393719100, 393919200,
394119350, 394319550, 394519800, 394720100, 394920450, 395120850, 395321300, 395521800, 395722350, 395922950, 396123600, 396324300, 396525050, 396725850, 396926700, 397127600, 397328550, 397529550, 397730600,
397931700, 398132850, 398334050, 398535300, 398736600, 398937950, 399139350, 399340800, 399542300, 399743850, 399945450, 400147100, 400348800, 400550550, 400752350, 400954200, 401156100, 401358050, 401560050,
401762100, 401964200, 402166350, 402368550, 402570800, 402773100, 402975450, 403177850, 403380300, 403582800, 403785350, 403987950, 404190600, 404393300, 404596050, 404798850, 405001700, 405204600, 405407550,
405610550, 405813600, 406016700, 406219850, 406423050, 406626300, 406829600, 407032950, 407236350, 407439800, 407643300, 407846850, 408050450, 408254100, 408457800, 408661550, 408865350, 409069200, 409273100,
409477050, 409681050, 409885100, 410089200, 410293350, 410497550, 410701800, 410906100, 411110450, 411314850, 411519300, 411723800, 411928350, 412132950, 412337600, 412542300, 412747050, 412951850, 413156700,
413361600, 413566550, 413771550, 413976600, 414181700, 414386850, 414592050, 414797300, 415002600, 415207950, 415413350, 415618800, 415824300, 416029850, 416235450, 416441100, 416646800, 416852550, 417058350,
417264200, 417470100, 417676050, 417882050, 418088100, 418294200, 418500350, 418706550, 418912800, 419119100, 419325450, 419531850, 419738300, 419944800, 420151350, 420357950, 420564600, 420771300, 420978050,
421184850, 421391700, 421598600, 421805550, 422012550, 422219600, 422426700, 422633850, 422841050, 423048300, 423255600, 423462950, 423670350, 423877800, 424085300, 424292850, 424500450, 424708100, 424915800,
425123550, 425331350, 425539200, 425747100, 425955050, 426163050, 426371100, 426579200, 426787350, 426995550, 427203800, 427412100, 427620450, 427828850, 428037300, 428245800, 428454350, 428662950, 428871600,
429080300, 429289050, 429497850, 429706700, 429915600, 430124550, 430333550, 430542600, 430751700, 430960850, 431170050, 431379300, 431588600, 431797950, 432007350, 432216800, 432426300, 432635850, 432845450,
433055100, 433264800, 433474550, 433684350, 433894200, 434104100, 434314050, 434524050, 434734100, 434944200, 435154350, 435364550, 435574800, 435785100, 435995450, 436205850, 436416300, 436626800, 436837350,
437047950, 437258600, 437469300, 437680050, 437890850, 438101700, 438312600, 438523550, 438734550, 438945600, 439156700, 439367850, 439579050, 439790300, 440001600, 440212950, 440424350, 440635800, 440847300,
441058850, 441270450, 441482100, 441693800, 441905550, 442117350, 442329200, 442541100, 442753050, 442965050, 443177100, 443389200, 443601350, 443813550, 444025800, 444238100, 444450450, 444662850, 444875300,
445087800, 445300350, 445512950, 445725600, 445938300, 446151050, 446363850, 446576700, 446789600, 447002550, 447215550, 447428600, 447641700, 447854850, 448068050, 448281300, 448494600, 448707950, 448921350,
449134800, 449348300, 449561850, 449775450, 449989100, 450202800, 450416550, 450630350, 450844200, 451058100, 451272050, 451486050, 451700100, 451914200, 452128350, 452342550, 452556800, 452771100, 452985450,
453199850, 453414300, 453628800, 453843350, 454057950, 454272600, 454487300, 454702050, 454916850, 455131700, 455346600, 455561550, 455776550, 455991600, 456206700, 456421850, 456637050, 456852300, 457067600,
457282950, 457498350, 457713800, 457929300, 458144850, 458360450, 458576100, 458791800, 459007550, 459223350, 459439200, 459655100, 459871050, 460087050, 460303100, 460519200, 460735350, 460951550, 461167800,
461384100, 461600450, 461816850, 462033300, 462249800, 462466350, 462682950, 462899600, 463116300, 463333050, 463549850, 463766700, 463983600, 464200550, 464417550, 464634600, 464851700, 465068850, 465286050,
465503300, 465720600, 465937950, 466155350, 466372800, 466590300, 466807850, 467025450, 467243100, 467460800, 467678550, 467896350, 468114200, 468332100, 468550050, 468768050, 468986100, 469204200, 469422350,
469640550, 469858800, 470077100, 470295450, 470513850, 470732300, 470950800, 471169350, 471387950, 471606600, 471825300, 472044050, 472262850, 472481700, 472700600, 472919550, 473138550, 473357600, 473576700,
473795850, 474015050, 474234300, 474453600, 474672950, 474892350, 475111800, 475331300, 475550850, 475770450, 475990100, 476209800, 476429550, 476649350, 476869200, 477089100, 477309050, 477529050, 477749100,
477969200, 478189350, 478409550, 478629800, 478850100, 479070450, 479290850, 479511300, 479731800, 479952350, 480172950, 480393600, 480614300, 480835050, 481055850, 481276700, 481497600, 481718550, 481939550, 482160600, 482381700, 482602850, 482824050, 483045300, 483266600, 483487950, 483709350, 483930800, 484152300, 484373850, 484595450, 484817100, 485038800, 485260550, 485482350, 485704200, 485926100, 486148050, 486370050, 486592100, 486814200, 487036350, 487258550, 487480800, 487703100, 487925450, 488147850, 488370300, 488592800, 488815350, 489037950, 489260600, 489483300, 489706050, 489928850, 490151700, 490374600, 490597550, 490820550, 491043600, 491266700, 491489850, 491713050, 491936300, 492159600, 492382950, 492606350, 492829800, 493053300, 493276850, 493500450, 493724100, 493947800, 494171550, 494395350, 494619200, 494843100, 495067050, 495291050, 495515100, 495739200, 495963350, 496187550, 496411800, 496636100, 496860450, 497084850, 497309300, 497533800, 497758350, 497982950, 498207600, 498432300, 498657050, 498881850, 499106700, 499331600, 499556550, 499781550, 500006600, 500231700, 500456850, 500682050, 500907300, 501132600, 501357950, 501583350, 501808800, 502034300, 502259850, 502485450, 502711100, 502936800, 503162550, 503388350, 503614200, 503840100, 504066050, 504292050, 504518100, 504744200, 504970350, 505196550, 505422800, 505649100, 505875450, 506101850, 506328300, 506554800, 506781350, 507007950, 507234600, 507461300, 507688050, 507914850, 508141700, 508368600, 508595550, 508822550, 509049600, 509276700, 509503850, 509731050, 509958300, 510185600, 510412950, 510640350, 510867800, 511095300, 511322850, 511550450, 511778100, 512005800, 512233550, 512461350, 512689200, 512917100, 513145050, 513373050, 513601100, 513829200, 514057350, 514285550, 514513800, 514742100, 514970450, 515198850, 515427300, 515655800, 515884350, 516112950, 516341600, 516570300, 516799050, 517027850, 517256700, 517485600, 517714550, 517943550, 518172600, 518401700, 518630850, 518860050, 519089300, 519318600, 519547950, 519777350, 520006800, 520236300, 520465850, 520695450, 520925100, 521154800, 521384550, 521614350, 521844200, 522074100, 522304050, 522534050, 522764100, 522994200, 523224350, 523454550, 523684800, 523915100, 524145450, 524375850, 524606300, 524836800, 525067350, 525297950, 525528600, 525759300, 525990050, 526220850, 526451700, 526682600, 526913550, 527144550, 527375600, 527606700, 527837850, 528069050, 528300300, 528531600, 528762950, 528994350, 529225800, 529457300, 529688850, 529920450, 530152100, 530383800, 530615550, 530847350, 531079200, 531311100, 531543050, 531775050, 532007100, 532239200, 532471350, 532703550, 532935800, 533168100, 533400450, 533632850, 533865300, 534097800, 534330350, 534562950, 534795600, 535028300, 535261050, 535493850, 535726700, 535959600, 536192550, 536425550, 536658600, 536891700, 537124850, 537358050, 537591300, 537824600, 538057950, 538291350, 538524800, 538758300, 538991850, 539225450, 539459100, 539692800, 539926550, 540160350, 540394200, 540628100, 540862050, 541096050, 541330100, 541564200, 541798350, 542032550, 542266800, 542501100, 542735450, 542969850, 543204300, 543438800, 543673350, 543907950, 544142600, 544377300, 544612050, 544846850, 545081700, 545316600, 545551550, 545786550, 546021600, 546256700, 546491850, 546727050, 546962300, 547197600, 547432950, 547668350, 547903800, 548139300, 548374850, 548610450, 548846100, 549081800, 549317550, 549553350, 549789200, 550025100, 550261050, 550497050, 550733100, 550969200, 551205350, 551441550, 551677800, 551914100, 552150450, 552386850, 552623300, 552859800, 553096350, 553332950, 553569600, 553806300, 554043050, 554279850, 554516700, 554753600, 554990550, 555227550, 555464600, 555701700, 555938850, 556176050, 556413300, 556650600, 556887950, 557125350, 557362800, 557600300, 557837850, 558075450, 558313100, 558550800, 558788550, 559026350, 559264200, 559502100, 559740050, 559978050, 560216100, 560454200, 560692350, 560930550, 561168800, 561407100, 561645450, 561883850, 562122300, 562360800, 562599350, 562837950, 563076600, 563315300, 563554050, 563792850, 564031700, 564270600, 564509550, 564748550, 564987600, 565226700, 565465850, 565705050, 565944300, 566183600, 566422950, 566662350, 566901800, 567141300, 567380850, 567620450, 567860100, 568099800, 568339550, 568579350, 568819200, 569059100, 569299050, 569539050, 569779100, 570019200, 570259350, 570499550, 570739800, 570980100, 571220450, 571460850, 571701300, 571941800, 572182350, 572422950, 572663600, 572904300, 573145050, 573385850, 573626700, 573867600, 574108550, 574349550, 574590600, 574831700, 575072850, 575314050, 575555300, 575796600, 576037950, 576279350, 576520800, 576762300, 577003850, 577245450, 577487100, 577728800, 577970550, 578212350, 578454200, 578696100, 578938050, 579180050, 579422100, 579664200, 579906350, 580148550, 580390800, 580633100, 580875450, 581117850, 581360300, 581602800, 581845350, 582087950, 582330600, 582573300, 582816050, 583058850, 583301700, 583544600, 583787550, 584030550, 584273600, 584516700, 584759850, 585003050, 585246300, 585489600, 585732950, 585976350, 586219800, 586463300, 586706850, 586950450, 587194100, 587437800, 587681550, 587925350, 588169200, 588413100, 588657050, 588901050, 589145100, 589389200, 589633350, 589877550, 590121800, 590366100, 590610450, 590854850, 591099300, 591343800, 591588350, 591832950, 592077600, 592322300, 592567050, 592811850, 593056700, 593301600, 593546550, 593791550, 594036600, 594281700, 594526850, 594772050, 595017300, 595262600, 595507950, 595753350, 595998800, 596244300, 596489850, 596735450, 596981100, 597226800, 597472550, 597718350, 597964200, 598210100, 598456050, 598702050, 598948100, 599194200, 599440350, 599686550, 599932800, 600179100, 600425450, 600671850, 600918300, 601164800, 601411350, 601657950, 601904600, 602151300, 602398050, 602644850, 602891700, 603138600, 603385550, 603632550, 603879600, 604126700, 604373850, 604621050, 604868300, 605115600, 605362950, 605610350, 605857800, 606105300, 606352850, 606600450, 606848100, 607095800, 607343550, 607591350, 607839200, 608087100, 608335050, 608583050, 608831100, 609079200, 609327350, 609575550, 609823800, 610072100, 610320450, 610568850, 610817300, 611065800, 611314350, 611562950, 611811600, 612060300, 612309050, 612557850, 612806700, 613055600, 613304550, 613553550, 613802600, 614051700, 614300850, 614550050, 614799300, 615048600, 615297950, 615547350, 615796800, 616046300, 616295850, 616545450, 616795100, 617044800, 617294550, 617544350, 617794200, 618044100, 618294050, 618544050, 618794100, 619044200, 619294350, 619544550, 619794800, 620045100, 620295450, 620545850, 620796300, 621046800, 621297350, 621547950, 621798600, 622049300, 622300050, 622550850, 622801700, 623052600, 623303550, 623554550, 623805600, 624056700, 624307850, 624559050, 624810300, 625061600, 625312950, 625564350, 625815800, 626067300, 626318850, 626570450, 626822100, 627073800, 627325550, 627577350, 627829200, 628081100, 628333050, 628585050, 628837100, 629089200, 629341350, 629593550, 629845800, 630098100, 630350450, 630602850, 630855300, 631107800, 631360350, 631612950, 631865600, 632118300, 632371050, 632623850, 632876700, 633129600, 633382550, 633635550, 633888600, 634141700, 634394850, 634648050, 634901300, 635154600, 635407950, 635661350, 635914800, 636168300, 636421850, 636675450, 636929100, 637182800, 637436550, 637690350, 637944200, 638198100, 638452050, 638706050, 638960100, 639214200, 639468350, 639722550, 639976800, 640231100, 640485450, 640739850, 640994300, 641248800, 641503350, 641757950, 642012600, 642267300, 642522050, 642776850, 643031700, 643286600, 643541550, 643796550, 644051600, 644306700, 644561850, 644817050, 645072300, 645327600, 645582950, 645838350, 646093800, 646349300, 646604850, 646860450, 647116100, 647371800, 647627550, 647883350, 648139200, 648395100, 648651050, 648907050, 649163100, 649419200, 649675350, 649931550, 650187800, 650444100, 650700450, 650956850, 651213300, 651469800, 651726350, 651982950, 652239600, 652496300, 652753050, 653009850, 653266700, 653523600, 653780550, 654037550, 654294600, 654551700, 654808850, 655066050, 655323300, 655580600, 655837950, 656095350, 656352800, 656610300, 656867850, 657125450, 657383100, 657640800, 657898550, 658156350, 658414200, 658672100, 658930050, 659188050, 659446100, 659704200, 659962350, 660220550, 660478800, 660737100, 660995450, 661253850, 661512300, 661770800, 662029350, 662287950, 662546600, 662805300, 663064050, 663322850, 663581700, 663840600, 664099550, 664358550, 664617600, 664876700, 665135850, 665395050, 665654300, 665913600, 666172950, 666432350, 666691800, 666951300, 667210850, 667470450, 667730100, 667989800, 668249550, 668509350, 668769200, 669029100, 669289050, 669549050, 669809100, 670069200, 670329350, 670589550, 670849800, 671110100, 671370450, 671630850, 671891300, 672151800, 672412350, 672672950, 672933600, 673194300, 673455050, 673715850, 673976700, 674237600, 674498550, 674759550, 675020600, 675281700, 675542850, 675804050, 676065300, 676326600, 676587950, 676849350, 677110800, 677372300, 677633850, 677895450, 678157100, 678418800, 678680550, 678942350, 679204200, 679466100, 679728050, 679990050, 680252100, 680514200, 680776350, 681038550, 681300800, 681563100, 681825450, 682087850, 682350300, 682612800, 682875350, 683137950, 683400600, 683663300, 683926050, 684188850, 684451700, 684714600, 684977550, 685240550, 685503600, 685766700, 686029850, 686293050, 686556300, 686819600, 687082950, 687346350, 687609800, 687873300, 688136850, 688400450, 688664100, 688927800, 689191550, 689455350, 689719200, 689983100, 690247050, 690511050, 690775100, 691039200, 691303350, 691567550, 691831800, 692096100, 692360450, 692624850, 692889300, 693153800, 693418350, 693682950, 693947600, 694212300, 694477050, 694741850, 695006700, 695271600, 695536550, 695801550, 696066600, 696331700, 696596850, 696862050, 697127300, 697392600, 697657950, 697923350, 698188800, 698454300, 698719850, 698985450, 699251100, 699516800, 699782550, 700048350, 700314200, 700580100, 700846050, 701112050, 701378100, 701644200, 701910350, 702176550, 702442800, 702709100, 702975450, 703241850, 703508300, 703774800, 704041350, 704307950, 704574600, 704841300, 705108050, 705374850, 705641700, 705908600, 706175550, 706442550, 706709600, 706976700, 707243850, 707511050, 707778300, 708045600, 708312950, 708580350, 708847800, 709115300, 709382850, 709650450, 709918100, 710185800, 710453550, 710721350, 710989200, 711257100, 711525050, 711793050, 712061100, 712329200, 712597350, 712865550, 713133800, 713402100, 713670450, 713938850, 714207300, 714475800, 714744350, 715012950, 715281600, 715550300, 715819050, 716087850, 716356700, 716625600, 716894550, 717163550, 717432600, 717701700, 717970850, 718240050, 718509300, 718778600, 719047950, 719317350, 719586800, 719856300, 720125850, 720395450, 720665100, 720934800, 721204550, 721474350, 721744200, 722014100, 722284050, 722554050, 722824100, 723094200, 723364350, 723634550, 723904800, 724175100, 724445450, 724715850, 724986300, 725256800, 725527350, 725797950, 726068600, 726339300, 726610050, 726880850, 727151700, 727422600, 727693550, 727964550, 728235600, 728506700, 728777850, 729049050, 729320300, 729591600, 729862950, 730134350, 730405800, 730677300, 730948850, 731220450, 731492100, 731763800, 732035550, 732307350, 732579200, 732851100, 733123050, 733395050, 733667100, 733939200, 734211350, 734483550, 734755800, 735028100, 735300450, 735572850, 735845300, 736117800, 736390350, 736662950, 736935600, 737208300, 737481050, 737753850, 738026700, 738299600, 738572550, 738845550, 739118600, 739391700, 739664850, 739938050, 740211300, 740484600, 740757950, 741031350, 741304800, 741578300, 741851850, 742125450, 742399100, 742672800, 742946550, 743220350, 743494200, 743768100, 744042050, 744316050, 744590100, 744864200, 745138350, 745412550, 745686800, 745961100, 746235450, 746509850, 746784300, 747058800, 747333350, 747607950, 747882600, 748157300, 748432050, 748706850, 748981700, 749256600, 749531550, 749806550, 750081600, 750356700, 750631850, 750907050, 751182300, 751457600, 751732950, 752008350, 752283800, 752559300, 752834850, 753110450, 753386100, 753661800, 753937550, 754213350, 754489200, 754765100, 755041050, 755317050, 755593100, 755869200, 756145350, 756421550, 756697800, 756974100, 757250450, 757526850, 757803300, 758079800, 758356350, 758632950, 758909600, 759186300, 759463050, 759739850, 760016700, 760293600, 760570550, 760847550, 761124600, 761401700, 761678850, 761956050, 762233300, 762510600, 762787950, 763065350, 763342800, 763620300, 763897850, 764175450, 764453100, 764730800, 765008550, 765286350, 765564200, 765842100, 766120050, 766398050, 766676100, 766954200, 767232350, 767510550, 767788800, 768067100, 768345450, 768623850, 768902300, 769180800, 769459350, 769737950, 770016600, 770295300, 770574050, 770852850, 771131700, 771410600, 771689550, 771968550, 772247600, 772526700, 772805850, 773085050, 773364300, 773643600, 773922950, 774202350, 774481800, 774761300, 775040850, 775320450, 775600100, 775879800, 776159550, 776439350, 776719200, 776999100, 777279050, 777559050, 777839100, 778119200, 778399350, 778679550, 778959800, 779240100, 779520450, 779800850, 780081300, 780361800, 780642350, 780922950, 781203600, 781484300, 781765050, 782045850, 782326700, 782607600, 782888550, 783169550, 783450600, 783731700, 784012850, 784294050, 784575300, 784856600, 785137950, 785419350, 785700800, 785982300, 786263850, 786545450, 786827100, 787108800, 787390550, 787672350, 787954200, 788236100, 788518050, 788800050, 789082100, 789364200, 789646350, 789928550, 790210800, 790493100, 790775450, 791057850, 791340300, 791622800, 791905350, 792187950, 792470600, 792753300, 793036050, 793318850, 793601700, 793884600, 794167550, 794450550, 794733600, 795016700, 795299850, 795583050, 795866300, 796149600, 796432950, 796716350, 796999800, 797283300, 797566850, 797850450, 798134100, 798417800, 798701550, 798985350, 799269200, 799553100, 799837050, 800121050, 800405100, 800689200, 800973350, 801257550, 801541800, 801826100, 802110450, 802394850, 802679300, 802963800, 803248350, 803532950, 803817600, 804102300, 804387050, 804671850, 804956700, 805241600, 805526550, 805811550, 806096600, 806381700, 806666850, 806952050, 807237300, 807522600, 807807950, 808093350, 808378800, 808664300, 808949850, 809235450, 809521100, 809806800, 810092550, 810378350, 810664200, 810950100, 811236050, 811522050, 811808100, 812094200, 812380350, 812666550, 812952800, 813239100, 813525450, 813811850, 814098300, 814384800, 814671350, 814957950, 815244600, 815531300, 815818050, 816104850, 816391700, 816678600, 816965550, 817252550, 817539600, 817826700, 818113850, 818401050, 818688300, 818975600, 819262950, 819550350, 819837800, 820125300, 820412850, 820700450, 820988100, 821275800, 821563550, 821851350, 822139200, 822427100, 822715050, 823003050, 823291100, 823579200, 823867350, 824155550, 824443800, 824732100, 825020450, 825308850, 825597300, 825885800, 826174350, 826462950, 826751600, 827040300, 827329050, 827617850, 827906700, 828195600, 828484550, 828773550, 829062600, 829351700, 829640850, 829930050, 830219300, 830508600, 830797950, 831087350, 831376800, 831666300, 831955850, 832245450, 832535100, 832824800, 833114550, 833404350, 833694200, 833984100, 834274050, 834564050, 834854100, 835144200, 835434350, 835724550, 836014800, 836305100, 836595450, 836885850, 837176300, 837466800, 837757350, 838047950, 838338600, 838629300, 838920050, 839210850, 839501700, 839792600, 840083550, 840374550, 840665600, 840956700, 841247850, 841539050, 841830300, 842121600, 842412950, 842704350, 842995800, 843287300, 843578850, 843870450, 844162100, 844453800, 844745550, 845037350, 845329200, 845621100, 845913050, 846205050, 846497100, 846789200, 847081350, 847373550, 847665800, 847958100, 848250450, 848542850, 848835300, 849127800, 849420350, 849712950, 850005600, 850298300, 850591050, 850883850, 851176700, 851469600, 851762550, 852055550, 852348600, 852641700, 852934850, 853228050, 853521300, 853814600, 854107950, 854401350, 854694800, 854988300, 855281850, 855575450, 855869100, 856162800, 856456550, 856750350, 857044200, 857338100, 857632050, 857926050, 858220100, 858514200, 858808350, 859102550, 859396800, 859691100, 859985450, 860279850, 860574300, 860868800, 861163350, 861457950, 861752600, 862047300, 862342050, 862636850, 862931700, 863226600, 863521550, 863816550, 864111600, 864406700, 864701850, 864997050, 865292300, 865587600, 865882950, 866178350, 866473800, 866769300, 867064850, 867360450, 867656100, 867951800, 868247550, 868543350, 868839200, 869135100, 869431050, 869727050, 870023100, 870319200, 870615350, 870911550, 871207800, 871504100, 871800450, 872096850, 872393300, 872689800, 872986350, 873282950, 873579600, 873876300, 874173050, 874469850, 874766700, 875063600, 875360550, 875657550, 875954600, 876251700, 876548850, 876846050, 877143300, 877440600, 877737950, 878035350, 878332800, 878630300, 878927850, 879225450, 879523100, 879820800, 880118550, 880416350, 880714200, 881012100, 881310050, 881608050, 881906100, 882204200, 882502350, 882800550, 883098800, 883397100, 883695450, 883993850, 884292300, 884590800, 884889350, 885187950, 885486600, 885785300, 886084050, 886382850, 886681700, 886980600, 887279550, 887578550, 887877600, 888176700, 888475850, 888775050, 889074300, 889373600, 889672950, 889972350, 890271800, 890571300, 890870850, 891170450, 891470100, 891769800, 892069550, 892369350, 892669200, 892969100, 893269050, 893569050, 893869100, 894169200, 894469350, 894769550, 895069800, 895370100, 895670450, 895970850, 896271300, 896571800, 896872350, 897172950, 897473600, 897774300, 898075050, 898375850, 898676700, 898977600, 899278550, 899579550, 899880600, 900181700, 900482850, 900784050, 901085300, 901386600, 901687950, 901989350, 902290800, 902592300, 902893850, 903195450, 903497100, 903798800, 904100550, 904402350, 904704200, 905006100, 905308050, 905610050, 905912100, 906214200, 906516350, 906818550, 907120800, 907423100, 907725450, 908027850, 908330300, 908632800, 908935350, 909237950, 909540600, 909843300, 910146050, 910448850, 910751700, 911054600, 911357550, 911660550, 911963600, 912266700, 912569850, 912873050, 913176300, 913479600, 913782950, 914086350, 914389800, 914693300, 914996850, 915300450, 915604100, 915907800, 916211550, 916515350, 916819200, 917123100, 917427050, 917731050, 918035100, 918339200, 918643350, 918947550, 919251800, 919556100, 919860450, 920164850, 920469300, 920773800, 921078350, 921382950, 921687600, 921992300, 922297050, 922601850, 922906700, 923211600, 923516550, 923821550, 924126600, 924431700, 924736850, 925042050, 925347300, 925652600, 925957950, 926263350, 926568800, 926874300, 927179850, 927485450, 927791100, 928096800, 928402550, 928708350, 929014200, 929320100, 929626050, 929932050, 930238100, 930544200, 930850350, 931156550, 931462800, 931769100, 932075450, 932381850, 932688300, 932994800, 933301350, 933607950, 933914600, 934221300, 934528050, 934834850, 935141700, 935448600, 935755550, 936062550, 936369600, 936676700, 936983850, 937291050, 937598300, 937905600, 938212950, 938520350, 938827800, 939135300, 939442850, 939750450, 940058100, 940365800, 940673550, 940981350, 941289200, 941597100, 941905050, 942213050, 942521100, 942829200, 943137350, 943445550, 943753800, 944062100, 944370450, 944678850, 944987300, 945295800, 945604350, 945912950, 946221600, 946530300, 946839050, 947147850, 947456700, 947765600, 948074550, 948383550, 948692600, 949001700, 949310850, 949620050, 949929300, 950238600, 950547950, 950857350, 951166800, 951476300, 951785850, 952095450, 952405100, 952714800, 953024550, 953334350, 953644200, 953954100, 954264050, 954574050, 954884100, 955194200, 955504350, 955814550, 956124800, 956435100, 956745450, 957055850, 957366300, 957676800, 957987350, 958297950, 958608600, 958919300, 959230050, 959540850, 959851700, 960162600, 960473550, 960784550, 961095600, 961406700, 961717850, 962029050, 962340300, 962651600, 962962950, 963274350, 963585800, 963897300, 964208850, 964520450, 964832100, 965143800, 965455550, 965767350, 966079200, 966391100, 966703050, 967015050, 967327100, 967639200, 967951350, 968263550, 968575800, 968888100, 969200450, 969512850, 969825300, 970137800, 970450350, 970762950, 971075600, 971388300, 971701050, 972013850, 972326700, 972639600, 972952550, 973265550, 973578600, 973891700, 974204850, 974518050, 974831300, 975144600, 975457950, 975771350, 976084800, 976398300, 976711850, 977025450, 977339100, 977652800, 977966550, 978280350, 978594200, 978908100, 979222050, 979536050, 979850100, 980164200, 980478350, 980792550, 981106800, 981421100, 981735450, 982049850, 982364300, 982678800, 982993350, 983307950, 983622600, 983937300, 984252050, 984566850, 984881700, 985196600, 985511550, 985826550, 986141600, 986456700, 986771850, 987087050, 987402300, 987717600, 988032950, 988348350, 988663800, 988979300, 989294850, 989610450, 989926100, 990241800, 990557550, 990873350, 991189200, 991505100, 991821050, 992137050, 992453100, 992769200, 993085350, 993401550, 993717800, 994034100, 994350450, 994666850, 994983300, 995299800, 995616350, 995932950, 996249600, 996566300, 996883050, 997199850, 997516700, 997833600, 998150550, 998467550, 998784600, 999101700, 999418850, 999736050, 1000053300, 1000370600, 1000687950, 1001005350, 1001322800, 1001640300, 1001957850, 1002275450, 1002593100, 1002910800, 1003228550, 1003546350, 1003864200, 1004182100, 1004500050, 1004818050, 1005136100, 1005454200, 1005772350, 1006090550, 1006408800, 1006727100, 1007045450, 1007363850, 1007682300, 1008000800, 1008319350, 1008637950, 1008956600, 1009275300, 1009594050, 1009912850, 1010231700, 1010550600, 1010869550, 1011188550, 1011507600, 1011826700, 1012145850, 1012465050, 1012784300, 1013103600, 1013422950, 1013742350, 1014061800, 1014381300, 1014700850, 1015020450, 1015340100, 1015659800, 1015979550, 1016299350, 1016619200, 1016939100, 1017259050, 1017579050, 1017899100, 1018219200, 1018539350, 1018859550, 1019179800, 1019500100, 1019820450, 1020140850, 1020461300, 1020781800, 1021102350, 1021422950, 1021743600, 1022064300, 1022385050, 1022705850, 1023026700, 1023347600, 1023668550, 1023989550, 1024310600, 1024631700, 1024952850, 1025274050, 1025595300, 1025916600, 1026237950, 1026559350, 1026880800, 1027202300, 1027523850, 1027845450, 1028167100, 1028488800, 1028810550, 1029132350, 1029454200, 1029776100, 1030098050, 1030420050, 1030742100, 1031064200, 1031386350, 1031708550, 1032030800, 1032353100, 1032675450, 1032997850, 1033320300, 1033642800, 1033965350, 1034287950, 1034610600, 1034933300, 1035256050, 1035578850, 1035901700, 1036224600, 1036547550, 1036870550, 1037193600, 1037516700, 1037839850, 1038163050, 1038486300, 1038809600, 1039132950, 1039456350, 1039779800, 1040103300, 1040426850, 1040750450, 1041074100, 1041397800, 1041721550, 1042045350, 1042369200, 1042693100, 1043017050, 1043341050, 1043665100, 1043989200, 1044313350, 1044637550, 1044961800, 1045286100, 1045610450, 1045934850, 1046259300, 1046583800, 1046908350, 1047232950, 1047557600, 1047882300, 1048207050, 1048531850, 1048856700, 1049181600, 1049506550, 1049831550, 1050156600, 1050481700, 1050806850, 1051132050, 1051457300, 1051782600, 1052107950, 1052433350, 1052758800, 1053084300, 1053409850, 1053735450, 1054061100, 1054386800, 1054712550, 1055038350, 1055364200, 1055690100, 1056016050, 1056342050, 1056668100, 1056994200, 1057320350, 1057646550, 1057972800, 1058299100, 1058625450, 1058951850, 1059278300, 1059604800, 1059931350, 1060257950, 1060584600, 1060911300, 1061238050, 1061564850, 1061891700, 1062218600, 1062545550, 1062872550, 1063199600, 1063526700, 1063853850, 1064181050, 1064508300, 1064835600, 1065162950, 1065490350, 1065817800, 1066145300, 1066472850, 1066800450, 1067128100, 1067455800, 1067783550, 1068111350, 1068439200, 1068767100, 1069095050, 1069423050, 1069751100, 1070079200, 1070407350, 1070735550, 1071063800, 1071392100, 1071720450, 1072048850, 1072377300, 1072705800, 1073034350, 1073362950, 1073691600, 1074020300, 1074349050, 1074677850, 1075006700, 1075335600, 1075664550, 1075993550, 1076322600, 1076651700, 1076980850, 1077310050, 1077639300, 1077968600, 1078297950, 1078627350, 1078956800, 1079286300, 1079615850, 1079945450, 1080275100, 1080604800, 1080934550, 1081264350, 1081594200, 1081924100, 1082254050, 1082584050, 1082914100, 1083244200, 1083574350, 1083904550, 1084234800, 1084565100, 1084895450, 1085225850, 1085556300, 1085886800, 1086217350, 1086547950, 1086878600, 1087209300, 1087540050, 1087870850, 1088201700, 1088532600, 1088863550, 1089194550, 1089525600, 1089856700, 1090187850, 1090519050, 1090850300, 1091181600, 1091512950, 1091844350, 1092175800, 1092507300, 1092838850, 1093170450, 1093502100, 1093833800, 1094165550, 1094497350, 1094829200, 1095161100, 1095493050, 1095825050, 1096157100, 1096489200, 1096821350, 1097153550, 1097485800, 1097818100, 1098150450, 1098482850, 1098815300, 1099147800, 1099480350, 1099812950, 1100145600, 1100478300, 1100811050, 1101143850, 1101476700, 1101809600, 1102142550, 1102475550, 1102808600, 1103141700, 1103474850, 1103808050, 1104141300, 1104474600, 1104807950, 1105141350, 1105474800, 1105808300, 1106141850, 1106475450, 1106809100, 1107142800, 1107476550, 1107810350, 1108144200, 1108478100, 1108812050, 1109146050, 1109480100, 1109814200, 1110148350, 1110482550, 1110816800, 1111151100, 1111485450, 1111819850, 1112154300, 1112488800, 1112823350, 1113157950, 1113492600, 1113827300, 1114162050, 1114496850, 1114831700, 1115166600, 1115501550, 1115836550, 1116171600, 1116506700, 1116841850, 1117177050, 1117512300, 1117847600, 1118182950, 1118518350, 1118853800, 1119189300, 1119524850, 1119860450, 1120196100, 1120531800, 1120867550, 1121203350, 1121539200, 1121875100, 1122211050, 1122547050, 1122883100, 1123219200, 1123555350, 1123891550, 1124227800, 1124564100, 1124900450, 1125236850, 1125573300, 1125909800, 1126246350, 1126582950, 1126919600, 1127256300, 1127593050, 1127929850, 1128266700, 1128603600, 1128940550, 1129277550, 1129614600, 1129951700, 1130288850, 1130626050, 1130963300, 1131300600, 1131637950, 1131975350, 1132312800, 1132650300, 1132987850, 1133325450, 1133663100, 1134000800, 1134338550, 1134676350, 1135014200, 1135352100, 1135690050, 1136028050, 1136366100, 1136704200, 1137042350, 1137380550, 1137718800, 1138057100, 1138395450, 1138733850, 1139072300, 1139410800, 1139749350, 1140087950, 1140426600, 1140765300, 1141104050, 1141442850, 1141781700, 1142120600, 1142459550, 1142798550, 1143137600, 1143476700, 1143815850, 1144155050, 1144494300, 1144833600, 1145172950, 1145512350, 1145851800, 1146191300, 1146530850, 1146870450, 1147210100, 1147549800, 1147889550, 1148229350, 1148569200, 1148909100, 1149249050, 1149589050, 1149929100, 1150269200, 1150609350, 1150949550, 1151289800, 1151630100, 1151970450, 1152310850, 1152651300, 1152991800, 1153332350, 1153672950, 1154013600, 1154354300, 1154695050, 1155035850, 1155376700, 1155717600, 1156058550, 1156399550, 1156740600, 1157081700, 1157422850, 1157764050, 1158105300, 1158446600, 1158787950, 1159129350, 1159470800, 1159812300, 1160153850, 1160495450, 1160837100, 1161178800, 1161520550, 1161862350, 1162204200, 1162546100, 1162888050, 1163230050, 1163572100, 1163914200, 1164256350, 1164598550, 1164940800, 1165283100, 1165625450, 1165967850, 1166310300, 1166652800, 1166995350, 1167337950, 1167680600, 1168023300, 1168366050, 1168708850, 1169051700, 1169394600, 1169737550, 1170080550, 1170423600, 1170766700, 1171109850, 1171453050, 1171796300, 1172139600, 1172482950, 1172826350, 1173169800, 1173513300, 1173856850, 1174200450, 1174544100, 1174887800, 1175231550, 1175575350, 1175919200, 1176263100, 1176607050, 1176951050, 1177295100, 1177639200, 1177983350, 1178327550, 1178671800, 1179016100, 1179360450, 1179704850, 1180049300, 1180393800, 1180738350, 1181082950, 1181427600, 1181772300, 1182117050, 1182461850, 1182806700, 1183151600, 1183496550, 1183841550, 1184186600, 1184531700, 1184876850, 1185222050, 1185567300, 1185912600, 1186257950, 1186603350, 1186948800, 1187294300, 1187639850, 1187985450, 1188331100, 1188676800, 1189022550, 1189368350, 1189714200, 1190060100, 1190406050, 1190752050, 1191098100, 1191444200, 1191790350, 1192136550, 1192482800, 1192829100, 1193175450, 1193521850, 1193868300, 1194214800, 1194561350, 1194907950, 1195254600, 1195601300, 1195948050, 1196294850, 1196641700, 1196988600, 1197335550, 1197682550, 1198029600, 1198376700, 1198723850, 1199071050, 1199418300, 1199765600, 1200112950, 1200460350, 1200807800, 1201155300, 1201502850, 1201850450, 1202198100, 1202545800, 1202893550, 1203241350, 1203589200, 1203937100, 1204285050, 1204633050, 1204981100, 1205329200, 1205677350, 1206025550, 1206373800, 1206722100, 1207070450, 1207418850, 1207767300, 1208115800, 1208464350, 1208812950, 1209161600, 1209510300, 1209859050, 1210207850, 1210556700, 1210905600, 1211254550, 1211603550, 1211952600, 1212301700, 1212650850, 1213000050, 1213349300, 1213698600, 1214047950, 1214397350, 1214746800, 1215096300, 1215445850, 1215795450, 1216145100, 1216494800, 1216844550, 1217194350, 1217544200, 1217894100, 1218244050, 1218594050, 1218944100, 1219294200, 1219644350, 1219994550, 1220344800, 1220695100, 1221045450, 1221395850, 1221746300, 1222096800, 1222447350, 1222797950, 1223148600, 1223499300, 1223850050, 1224200850, 1224551700, 1224902600, 1225253550, 1225604550, 1225955600, 1226306700, 1226657850, 1227009050, 1227360300, 1227711600, 1228062950, 1228414350, 1228765800, 1229117300, 1229468850, 1229820450, 1230172100, 1230523800, 1230875550, 1231227350, 1231579200, 1231931100, 1232283050, 1232635050, 1232987100, 1233339200, 1233691350, 1234043550, 1234395800, 1234748100, 1235100450, 1235452850, 1235805300, 1236157800, 1236510350, 1236862950, 1237215600, 1237568300, 1237921050, 1238273850, 1238626700, 1238979600, 1239332550, 1239685550, 1240038600, 1240391700, 1240744850, 1241098050, 1241451300, 1241804600, 1242157950, 1242511350, 1242864800, 1243218300, 1243571850, 1243925450, 1244279100, 1244632800, 1244986550, 1245340350, 1245694200, 1246048100, 1246402050, 1246756050, 1247110100, 1247464200, 1247818350, 1248172550, 1248526800, 1248881100, 1249235450, 1249589850, 1249944300, 1250298800, 1250653350, 1251007950, 1251362600, 1251717300, 1252072050, 1252426850, 1252781700, 1253136600, 1253491550, 1253846550, 1254201600, 1254556700, 1254911850, 1255267050, 1255622300, 1255977600, 1256332950, 1256688350, 1257043800, 1257399300, 1257754850, 1258110450, 1258466100, 1258821800, 1259177550, 1259533350, 1259889200, 1260245100, 1260601050, 1260957050, 1261313100, 1261669200, 1262025350, 1262381550, 1262737800, 1263094100, 1263450450, 1263806850, 1264163300, 1264519800, 1264876350, 1265232950, 1265589600, 1265946300, 1266303050, 1266659850, 1267016700, 1267373600, 1267730550, 1268087550, 1268444600, 1268801700, 1269158850, 1269516050, 1269873300, 1270230600, 1270587950, 1270945350, 1271302800, 1271660300, 1272017850, 1272375450, 1272733100, 1273090800, 1273448550, 1273806350, 1274164200, 1274522100, 1274880050, 1275238050, 1275596100, 1275954200, 1276312350, 1276670550, 1277028800, 1277387100, 1277745450, 1278103850, 1278462300, 1278820800, 1279179350, 1279537950, 1279896600, 1280255300, 1280614050, 1280972850, 1281331700, 1281690600, 1282049550, 1282408550, 1282767600, 1283126700, 1283485850, 1283845050, 1284204300, 1284563600, 1284922950, 1285282350, 1285641800, 1286001300, 1286360850, 1286720450, 1287080100, 1287439800, 1287799550, 1288159350, 1288519200, 1288879100, 1289239050, 1289599050, 1289959100, 1290319200, 1290679350, 1291039550, 1291399800, 1291760100, 1292120450, 1292480850, 1292841300, 1293201800, 1293562350, 1293922950, 1294283600, 1294644300, 1295005050, 1295365850, 1295726700, 1296087600, 1296448550, 1296809550, 1297170600, 1297531700, 1297892850, 1298254050, 1298615300, 1298976600, 1299337950, 1299699350, 1300060800, 1300422300, 1300783850, 1301145450, 1301507100, 1301868800, 1302230550, 1302592350, 1302954200, 1303316100, 1303678050, 1304040050, 1304402100, 1304764200, 1305126350, 1305488550, 1305850800, 1306213100, 1306575450, 1306937850, 1307300300, 1307662800, 1308025350, 1308387950, 1308750600, 1309113300, 1309476050, 1309838850, 1310201700, 1310564600, 1310927550, 1311290550, 1311653600, 1312016700, 1312379850, 1312743050, 1313106300, 1313469600, 1313832950, 1314196350, 1314559800, 1314923300, 1315286850, 1315650450, 1316014100, 1316377800, 1316741550, 1317105350, 1317469200, 1317833100, 1318197050, 1318561050, 1318925100, 1319289200, 1319653350, 1320017550, 1320381800, 1320746100, 1321110450, 1321474850, 1321839300, 1322203800, 1322568350, 1322932950, 1323297600, 1323662300, 1324027050, 1324391850, 1324756700, 1325121600, 1325486550, 1325851550, 1326216600, 1326581700, 1326946850, 1327312050, 1327677300, 1328042600, 1328407950, 1328773350, 1329138800, 1329504300, 1329869850, 1330235450, 1330601100, 1330966800, 1331332550, 1331698350, 1332064200, 1332430100, 1332796050, 1333162050, 1333528100, 1333894200, 1334260350, 1334626550, 1334992800, 1335359100, 1335725450, 1336091850, 1336458300, 1336824800, 1337191350, 1337557950, 1337924600, 1338291300, 1338658050, 1339024850, 1339391700, 1339758600, 1340125550, 1340492550, 1340859600, 1341226700, 1341593850, 1341961050, 1342328300, 1342695600, 1343062950, 1343430350, 1343797800, 1344165300, 1344532850, 1344900450, 1345268100, 1345635800, 1346003550, 1346371350, 1346739200, 1347107100, 1347475050, 1347843050, 1348211100, 1348579200, 1348947350, 1349315550, 1349683800, 1350052100, 1350420450, 1350788850, 1351157300, 1351525800, 1351894350, 1352262950, 1352631600, 1353000300, 1353369050, 1353737850, 1354106700, 1354475600, 1354844550, 1355213550, 1355582600, 1355951700, 1356320850, 1356690050, 1357059300, 1357428600, 1357797950, 1358167350, 1358536800, 1358906300, 1359275850, 1359645450, 1360015100, 1360384800, 1360754550, 1361124350, 1361494200, 1361864100, 1362234050, 1362604050, 1362974100, 1363344200, 1363714350, 1364084550, 1364454800, 1364825100, 1365195450, 1365565850, 1365936300, 1366306800, 1366677350, 1367047950, 1367418600, 1367789300, 1368160050, 1368530850, 1368901700, 1369272600, 1369643550, 1370014550, 1370385600, 1370756700, 1371127850, 1371499050, 1371870300, 1372241600, 1372612950, 1372984350, 1373355800, 1373727300, 1374098850, 1374470450, 1374842100, 1375213800, 1375585550, 1375957350, 1376329200, 1376701100, 1377073050, 1377445050, 1377817100, 1378189200, 1378561350, 1378933550, 1379305800, 1379678100, 1380050450, 1380422850, 1380795300, 1381167800, 1381540350, 1381912950, 1382285600, 1382658300, 1383031050, 1383403850, 1383776700, 1384149600, 1384522550, 1384895550, 1385268600, 1385641700, 1386014850, 1386388050, 1386761300, 1387134600, 1387507950, 1387881350, 1388254800, 1388628300, 1389001850, 1389375450, 1389749100, 1390122800, 1390496550, 1390870350, 1391244200, 1391618100, 1391992050, 1392366050, 1392740100, 1393114200, 1393488350, 1393862550, 1394236800, 1394611100, 1394985450, 1395359850, 1395734300, 1396108800, 1396483350, 1396857950, 1397232600, 1397607300, 1397982050, 1398356850, 1398731700, 1399106600, 1399481550, 1399856550, 1400231600, 1400606700, 1400981850, 1401357050, 1401732300, 1402107600, 1402482950, 1402858350, 1403233800, 1403609300, 1403984850, 1404360450, 1404736100, 1405111800, 1405487550, 1405863350, 1406239200, 1406615100, 1406991050, 1407367050, 1407743100, 1408119200, 1408495350, 1408871550, 1409247800, 1409624100, 1410000450, 1410376850, 1410753300, 1411129800, 1411506350, 1411882950, 1412259600, 1412636300, 1413013050, 1413389850, 1413766700, 1414143600, 1414520550, 1414897550, 1415274600, 1415651700, 1416028850, 1416406050, 1416783300, 1417160600, 1417537950, 1417915350, 1418292800, 1418670300, 1419047850, 1419425450, 1419803100, 1420180800, 1420558550, 1420936350, 1421314200, 1421692100, 1422070050, 1422448050, 1422826100, 1423204200, 1423582350, 1423960550, 1424338800, 1424717100, 1425095450, 1425473850, 1425852300, 1426230800, 1426609350, 1426987950, 1427366600, 1427745300, 1428124050, 1428502850, 1428881700, 1429260600, 1429639550, 1430018550, 1430397600, 1430776700, 1431155850, 1431535050, 1431914300, 1432293600, 1432672950, 1433052350, 1433431800, 1433811300, 1434190850, 1434570450, 1434950100, 1435329800, 1435709550, 1436089350, 1436469200, 1436849100, 1437229050, 1437609050, 1437989100, 1438369200, 1438749350, 1439129550, 1439509800, 1439890100, 1440270450, 1440650850, 1441031300, 1441411800, 1441792350, 1442172950, 1442553600, 1442934300, 1443315050, 1443695850, 1444076700, 1444457600, 1444838550, 1445219550, 1445600600, 1445981700, 1446362850, 1446744050, 1447125300, 1447506600, 1447887950, 1448269350, 1448650800, 1449032300, 1449413850, 1449795450, 1450177100, 1450558800, 1450940550, 1451322350, 1451704200, 1452086100, 1452468050, 1452850050, 1453232100, 1453614200, 1453996350, 1454378550, 1454760800, 1455143100, 1455525450, 1455907850, 1456290300, 1456672800, 1457055350, 1457437950, 1457820600, 1458203300, 1458586050, 1458968850, 1459351700, 1459734600, 1460117550, 1460500550, 1460883600, 1461266700, 1461649850, 1462033050, 1462416300, 1462799600, 1463182950, 1463566350, 1463949800, 1464333300, 1464716850, 1465100450, 1465484100, 1465867800, 1466251550, 1466635350, 1467019200, 1467403100, 1467787050, 1468171050, 1468555100, 1468939200, 1469323350, 1469707550, 1470091800, 1470476100, 1470860450, 1471244850, 1471629300, 1472013800, 1472398350, 1472782950, 1473167600, 1473552300, 1473937050, 1474321850, 1474706700, 1475091600, 1475476550, 1475861550, 1476246600, 1476631700, 1477016850, 1477402050, 1477787300, 1478172600, 1478557950, 1478943350, 1479328800, 1479714300, 1480099850, 1480485450, 1480871100, 1481256800, 1481642550, 1482028350, 1482414200, 1482800100, 1483186050, 1483572050, 1483958100, 1484344200, 1484730350, 1485116550, 1485502800, 1485889100, 1486275450, 1486661850, 1487048300, 1487434800, 1487821350, 1488207950, 1488594600, 1488981300, 1489368050, 1489754850, 1490141700, 1490528600, 1490915550, 1491302550, 1491689600, 1492076700, 1492463850, 1492851050, 1493238300, 1493625600, 1494012950, 1494400350, 1494787800, 1495175300, 1495562850, 1495950450, 1496338100, 1496725800, 1497113550, 1497501350, 1497889200, 1498277100, 1498665050, 1499053050, 1499441100, 1499829200, 1500217350, 1500605550, 1500993800, 1501382100, 1501770450, 1502158850, 1502547300, 1502935800, 1503324350, 1503712950, 1504101600, 1504490300, 1504879050, 1505267850, 1505656700, 1506045600, 1506434550, 1506823550, 1507212600, 1507601700, 1507990850, 1508380050, 1508769300, 1509158600, 1509547950, 1509937350, 1510326800, 1510716300, 1511105850, 1511495450, 1511885100, 1512274800, 1512664550, 1513054350, 1513444200, 1513834100, 1514224050, 1514614050, 1515004100, 1515394200, 1515784350, 1516174550, 1516564800, 1516955100, 1517345450, 1517735850, 1518126300, 1518516800, 1518907350, 1519297950, 1519688600, 1520079300, 1520470050, 1520860850, 1521251700, 1521642600, 1522033550, 1522424550, 1522815600, 1523206700, 1523597850, 1523989050, 1524380300, 1524771600, 1525162950, 1525554350, 1525945800, 1526337300, 1526728850, 1527120450, 1527512100, 1527903800, 1528295550, 1528687350, 1529079200, 1529471100, 1529863050, 1530255050, 1530647100, 1531039200, 1531431350, 1531823550, 1532215800, 1532608100, 1533000450, 1533392850, 1533785300, 1534177800, 1534570350, 1534962950, 1535355600, 1535748300, 1536141050, 1536533850, 1536926700, 1537319600, 1537712550, 1538105550, 1538498600, 1538891700, 1539284850, 1539678050, 1540071300, 1540464600, 1540857950, 1541251350, 1541644800, 1542038300, 1542431850, 1542825450, 1543219100, 1543612800, 1544006550, 1544400350, 1544794200, 1545188100, 1545582050, 1545976050, 1546370100, 1546764200, 1547158350, 1547552550, 1547946800, 1548341100, 1548735450, 1549129850, 1549524300, 1549918800, 1550313350, 1550707950, 1551102600, 1551497300, 1551892050, 1552286850, 1552681700, 1553076600, 1553471550, 1553866550, 1554261600, 1554656700, 1555051850, 1555447050, 1555842300, 1556237600, 1556632950, 1557028350, 1557423800, 1557819300, 1558214850, 1558610450, 1559006100, 1559401800, 1559797550, 1560193350, 1560589200, 1560985100, 1561381050, 1561777050, 1562173100, 1562569200, 1562965350, 1563361550, 1563757800, 1564154100, 1564550450, 1564946850, 1565343300, 1565739800, 1566136350, 1566532950, 1566929600, 1567326300, 1567723050, 1568119850, 1568516700, 1568913600, 1569310550, 1569707550, 1570104600, 1570501700, 1570898850, 1571296050, 1571693300, 1572090600, 1572487950, 1572885350, 1573282800, 1573680300, 1574077850, 1574475450, 1574873100, 1575270800, 1575668550, 1576066350, 1576464200, 1576862100, 1577260050, 1577658050, 1578056100, 1578454200, 1578852350, 1579250550, 1579648800, 1580047100, 1580445450, 1580843850, 1581242300, 1581640800, 1582039350, 1582437950, 1582836600, 1583235300, 1583634050, 1584032850, 1584431700, 1584830600, 1585229550, 1585628550, 1586027600, 1586426700, 1586825850, 1587225050, 1587624300, 1588023600, 1588422950, 1588822350, 1589221800, 1589621300, 1590020850, 1590420450, 1590820100, 1591219800, 1591619550, 1592019350, 1592419200, 1592819100, 1593219050, 1593619050, 1594019100, 1594419200, 1594819350, 1595219550, 1595619800, 1596020100, 1596420450, 1596820850, 1597221300, 1597621800, 1598022350, 1598422950, 1598823600, 1599224300, 1599625050, 1600025850, 1600426700, 1600827600, 1601228550, 1601629550, 1602030600, 1602431700, 1602832850, 1603234050, 1603635300, 1604036600, 1604437950, 1604839350, 1605240800, 1605642300, 1606043850, 1606445450, 1606847100, 1607248800, 1607650550, 1608052350, 1608454200, 1608856100, 1609258050, 1609660050, 1610062100, 1610464200, 1610866350, 1611268550, 1611670800, 1612073100, 1612475450, 1612877850, 1613280300, 1613682800, 1614085350, 1614487950, 1614890600, 1615293300, 1615696050, 1616098850, 1616501700, 1616904600, 1617307550, 1617710550, 1618113600, 1618516700, 1618919850, 1619323050, 1619726300, 1620129600, 1620532950, 1620936350, 1621339800, 1621743300, 1622146850, 1622550450, 1622954100, 1623357800, 1623761550, 1624165350, 1624569200, 1624973100, 1625377050, 1625781050, 1626185100, 1626589200, 1626993350, 1627397550, 1627801800, 1628206100, 1628610450, 1629014850, 1629419300, 1629823800, 1630228350, 1630632950, 1631037600, 1631442300, 1631847050, 1632251850, 1632656700, 1633061600, 1633466550, 1633871550, 1634276600, 1634681700, 1635086850, 1635492050, 1635897300, 1636302600, 1636707950, 1637113350, 1637518800, 1637924300, 1638329850, 1638735450, 1639141100, 1639546800, 1639952550, 1640358350, 1640764200, 1641170100, 1641576050, 1641982050, 1642388100, 1642794200, 1643200350, 1643606550, 1644012800, 1644419100, 1644825450, 1645231850, 1645638300, 1646044800, 1646451350, 1646857950, 1647264600, 1647671300, 1648078050, 1648484850, 1648891700, 1649298600, 1649705550, 1650112550, 1650519600, 1650926700, 1651333850, 1651741050, 1652148300, 1652555600, 1652962950, 1653370350, 1653777800, 1654185300, 1654592850, 1655000450, 1655408100, 1655815800, 1656223550, 1656631350, 1657039200, 1657447100, 1657855050, 1658263050, 1658671100, 1659079200, 1659487350, 1659895550, 1660303800, 1660712100, 1661120450, 1661528850, 1661937300, 1662345800, 1662754350, 1663162950, 1663571600, 1663980300, 1664389050, 1664797850, 1665206700, 1665615600, 1666024550, 1666433550, 1666842600, 1667251700, 1667660850, 1668070050, 1668479300, 1668888600, 1669297950, 1669707350, 1670116800, 1670526300, 1670935850, 1671345450, 1671755100, 1672164800, 1672574550, 1672984350, 1673394200, 1673804100, 1674214050, 1674624050, 1675034100, 1675444200, 1675854350, 1676264550, 1676674800, 1677085100, 1677495450, 1677905850, 1678316300, 1678726800, 1679137350, 1679547950, 1679958600, 1680369300, 1680780050, 1681190850, 1681601700, 1682012600, 1682423550, 1682834550, 1683245600, 1683656700, 1684067850, 1684479050, 1684890300, 1685301600, 1685712950, 1686124350, 1686535800, 1686947300, 1687358850, 1687770450, 1688182100, 1688593800, 1689005550, 1689417350, 1689829200, 1690241100, 1690653050, 1691065050, 1691477100, 1691889200, 1692301350, 1692713550, 1693125800, 1693538100, 1693950450, 1694362850, 1694775300, 1695187800, 1695600350, 1696012950, 1696425600, 1696838300, 1697251050, 1697663850, 1698076700, 1698489600, 1698902550, 1699315550, 1699728600, 1700141700, 1700554850, 1700968050, 1701381300, 1701794600, 1702207950, 1702621350, 1703034800, 1703448300, 1703861850, 1704275450, 1704689100, 1705102800, 1705516550, 1705930350, 1706344200, 1706758100, 1707172050, 1707586050, 1708000100, 1708414200, 1708828350, 1709242550, 1709656800, 1710071100, 1710485450, 1710899850, 1711314300, 1711728800, 1712143350, 1712557950, 1712972600, 1713387300, 1713802050, 1714216850, 1714631700, 1715046600, 1715461550, 1715876550, 1716291600, 1716706700, 1717121850, 1717537050, 1717952300, 1718367600, 1718782950, 1719198350, 1719613800, 1720029300, 1720444850, 1720860450, 1721276100, 1721691800, 1722107550, 1722523350, 1722939200, 1723355100, 1723771050, 1724187050, 1724603100, 1725019200, 1725435350, 1725851550, 1726267800, 1726684100, 1727100450, 1727516850, 1727933300, 1728349800, 1728766350, 1729182950, 1729599600, 1730016300, 1730433050, 1730849850, 1731266700, 1731683600, 1732100550, 1732517550, 1732934600, 1733351700, 1733768850, 1734186050, 1734603300, 1735020600, 1735437950, 1735855350, 1736272800, 1736690300, 1737107850, 1737525450, 1737943100, 1738360800, 1738778550, 1739196350, 1739614200, 1740032100, 1740450050, 1740868050, 1741286100, 1741704200, 1742122350, 1742540550, 1742958800, 1743377100, 1743795450, 1744213850, 1744632300, 1745050800, 1745469350, 1745887950, 1746306600, 1746725300, 1747144050, 1747562850, 1747981700, 1748400600, 1748819550, 1749238550, 1749657600, 1750076700, 1750495850, 1750915050, 1751334300, 1751753600, 1752172950, 1752592350, 1753011800, 1753431300, 1753850850, 1754270450, 1754690100, 1755109800, 1755529550, 1755949350, 1756369200, 1756789100, 1757209050, 1757629050, 1758049100, 1758469200, 1758889350, 1759309550, 1759729800, 1760150100, 1760570450, 1760990850, 1761411300, 1761831800, 1762252350, 1762672950, 1763093600, 1763514300, 1763935050, 1764355850, 1764776700, 1765197600, 1765618550, 1766039550, 1766460600, 1766881700, 1767302850, 1767724050, 1768145300, 1768566600, 1768987950, 1769409350, 1769830800, 1770252300, 1770673850, 1771095450, 1771517100, 1771938800, 1772360550, 1772782350, 1773204200, 1773626100, 1774048050, 1774470050, 1774892100, 1775314200, 1775736350, 1776158550, 1776580800, 1777003100, 1777425450, 1777847850, 1778270300, 1778692800, 1779115350, 1779537950, 1779960600, 1780383300, 1780806050, 1781228850, 1781651700, 1782074600, 1782497550, 1782920550, 1783343600, 1783766700, 1784189850, 1784613050, 1785036300, 1785459600, 1785882950, 1786306350, 1786729800, 1787153300, 1787576850 };
char* CharKeyboard(char* windowName = "", int maxInput = 21, char* defaultText = "") {
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(0, "", "", defaultText, "", "", "", maxInput);
	while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return "";
	return GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
}

char* CharKeyboardUser(char* windowName = "username:", int maxInput = 21, char* defaultText = "") {
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Enter your username:");
	if (loop_text)
	{
		Menu::KeyboardText("Enter your username:");
	}
	notifyBottom("Enter your username:");
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(0, "", "", defaultText, "", "", "", maxInput);
	Menu::Drawing::Text("Enter your username:", Menu::Settings::count, { 0.40f, 0.1775f }, { 0.35f, 0.35f }, false);
	while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return "";
	return GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
}

char* CharKeyboardPass(char* windowName = "Password:", int maxInput = 21, char* defaultText = "") {
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Enter your username:");
	if (loop_text)
	{
		Menu::KeyboardText("Enter your password:");
	}
	notifyBottom("Enter your Password:");
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(0, "", "", defaultText, "", "", "", maxInput);
	while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return "";
	return GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
}

int NumberKeyboard() {
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(1, "", "", "", "", "", "", 10);
	while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return 0;
	return atof(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
}

void notifyleft(char* msg)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(msg);
	UI::_DRAW_NOTIFICATION(2000, 1);
}

char* objects[136] = { "prop_bskball_01", "PROP_MP_RAMP_03", "PROP_MP_RAMP_02", "PROP_MP_RAMP_01", "PROP_JETSKI_RAMP_01", "PROP_WATER_RAMP_03", "PROP_VEND_SNAK_01", "PROP_TRI_START_BANNER", "PROP_TRI_FINISH_BANNER", "PROP_TEMP_BLOCK_BLOCKER", "PROP_SLUICEGATEL", "PROP_SKIP_08A", "PROP_SAM_01", "PROP_RUB_CONT_01B", "PROP_ROADCONE01A", "PROP_MP_ARROW_BARRIER_01", "PROP_HOTEL_CLOCK_01", "PROP_LIFEBLURB_02", "PROP_COFFIN_02B", "PROP_MP_NUM_1", "PROP_MP_NUM_2", "PROP_MP_NUM_3", "PROP_MP_NUM_4", "PROP_MP_NUM_5", "PROP_MP_NUM_6", "PROP_MP_NUM_7", "PROP_MP_NUM_8", "PROP_MP_NUM_9", "prop_xmas_tree_int", "prop_bumper_car_01", "prop_beer_neon_01", "prop_space_rifle", "prop_dummy_01", "prop_rub_trolley01a", "prop_wheelchair_01_s", "PROP_CS_KATANA_01", "PROP_CS_DILDO_01", "prop_armchair_01", "prop_bin_04a", "prop_chair_01a", "prop_dog_cage_01", "prop_dummy_plane", "prop_golf_bag_01", "prop_arcade_01", "hei_prop_heist_emp", "prop_alien_egg_01", "prop_air_towbar_01", "hei_prop_heist_tug", "prop_air_luggtrolley", "PROP_CUP_SAUCER_01", "prop_wheelchair_01", "prop_ld_toilet_01", "prop_acc_guitar_01", "prop_bank_vaultdoor", "p_v_43_safe_s", "p_spinning_anus_s", "prop_can_canoe", "prop_air_woodsteps", "Prop_weed_01", "prop_a_trailer_door_01", "prop_apple_box_01", "prop_air_fueltrail1", "prop_barrel_02a", "prop_barrel_float_1", "prop_barrier_wat_03b", "prop_air_fueltrail2", "prop_air_propeller01", "prop_windmill_01", "prop_Ld_ferris_wheel", "p_tram_crash_s", "p_oil_slick_01", "p_ld_stinger_s", "p_ld_soc_ball_01", "prop_juicestand", "p_oil_pjack_01_s", "prop_barbell_01", "prop_barbell_100kg", "p_parachute1_s", "p_cablecar_s", "prop_beach_fire", "prop_lev_des_barge_02", "prop_lev_des_barge_01", "prop_a_base_bars_01", "prop_beach_bars_01", "prop_air_bigradar", "prop_weed_pallet", "prop_artifact_01", "prop_attache_case_01", "prop_large_gold", "prop_roller_car_01", "prop_water_corpse_01", "prop_water_corpse_02", "prop_dummy_01", "prop_atm_01", "hei_prop_carrier_docklight_01", "hei_prop_carrier_liferafts", "hei_prop_carrier_ord_03", "hei_prop_carrier_defense_02", "hei_prop_carrier_defense_01", "hei_prop_carrier_radar_1", "hei_prop_carrier_radar_2", "hei_prop_hei_bust_01", "hei_prop_wall_alarm_on", "hei_prop_wall_light_10a_cr", "prop_afsign_amun", "prop_afsign_vbike", "prop_aircon_l_01", "prop_aircon_l_02", "prop_aircon_l_03", "prop_aircon_l_04", "prop_airhockey_01", "prop_air_bagloader", "prop_air_blastfence_01", "prop_air_blastfence_02", "prop_air_cargo_01a", "prop_air_chock_01", "prop_air_chock_03", "prop_air_gasbogey_01", "prop_air_generator_03", "prop_air_stair_02", "prop_amb_40oz_02", "prop_amb_40oz_03", "prop_amb_beer_bottle", "prop_amb_donut", "prop_amb_handbag_01", "prop_amp_01", "prop_anim_cash_pile_02", "prop_asteroid_01", "prop_arm_wrestle_01", "prop_ballistic_shield", "prop_bank_shutter", "prop_barier_conc_02b", "prop_barier_conc_05a", "prop_barrel_01a", "prop_bar_stool_01", "prop_basejump_target_01" };
Vector3 TPCoords;
void TPto(Vector3 Coords)
{
	int Handle = PLAYER::PLAYER_PED_ID();
	if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0))
	{
		ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(Handle, false), Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
	}
	else
		ENTITY::SET_ENTITY_COORDS(Handle, Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
}

void teleporttocoords(Player selectedPlayer, Vector3 target)
{
	for (int iz = 0; iz < 2; iz++)
	{
		Ped destPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer);
		Vector3 ourLoc = target;
		AI::CLEAR_PED_TASKS_IMMEDIATELY(destPed);
		int netScene = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE2(ourLoc.x, ourLoc.y, ourLoc.z, 0.f, 0.f, 0.f, 0, 0, 0, 0.f, 0.f, 0.f);
		NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(destPed, netScene, "amb@code_human_cower@female@base", "base", 8.f, -8.f, 2, 0, 100.f, 0);
		NETWORK::NETWORK_START_SYNCHRONISED_SCENE(netScene);
		WAIT(150);
		AI::CLEAR_PED_TASKS_IMMEDIATELY(destPed);
		NETWORK::NETWORK_STOP_SYNCHRONISED_SCENE(netScene);
	}
}

//Draw socialclub messenge
void drawNotification(char* msg)
{
	if (Menu::Settings::menuX == 0.17f)
	{
		UI::_0x574EE85C("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING(msg);
		UI::__SET_NOTIFICATION_MESSAGE("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", true, 4, "Zendoz Menu", "");
		UI::_DRAW_NOTIFICATION(false, true);
	}
	else
	{
		UI::_0xF42C43C7("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING(msg);
		UI::_0x38F82261(3000, 1);
	}
}
//All voids for mods
void GodMode()
{
	if (godmode)
	{
		Memory::set_value<bool>({ OFFSET_PLAYER, OFFSET_ENTITY_GOD }, true); //Setting player value to undealdy true
	}
	else
	{
		Memory::set_value<bool>({ OFFSET_PLAYER, OFFSET_ENTITY_GOD }, false);
	}
}// 

void FastRun()
{
	
	if (fastRun)
	{
		Memory::set_value<float>({ OFFSET_PLAYER , OFFSET_PLAYER_INFO , OFFSET_PLAYER_INFO_RUN_SPD }, 2.5);
	}
	else
	{
		Memory::set_value<float>({ OFFSET_PLAYER , OFFSET_PLAYER_INFO , OFFSET_PLAYER_INFO_RUN_SPD }, 1.0);
	}
}

void FastSwim()
{
	int default1 = 0;
	if (fastSwim)
	{
		Memory::set_value<float>({ OFFSET_PLAYER , OFFSET_PLAYER_INFO , OFFSET_PLAYER_INFO_SWIM_SPD }, 3.5);
	}
	else
	{
		Memory::set_value<float>({ OFFSET_PLAYER , OFFSET_PLAYER_INFO , OFFSET_PLAYER_INFO_SWIM_SPD }, default1); // ur trolling 
	}
}

void VehicleGodMode()
{
	if (vehgodmode)
	{
		Memory::set_value<bool>({ OFFSET_VEHICLE_HEALTH, OFFSET_ENTITY_GOD }, 1); //Setting player value to undealdy true // who maked this ? demonforum.net hahaha // hell yeah // hes trolling 2
	}
	else
	{
		Memory::set_value<bool>({ OFFSET_VEHICLE_HEALTH, OFFSET_ENTITY_GOD }, 0); 
	}
}

void firebreath()
{
	if (FIREBREATH)
	{


		float XPos = 0.02, YPos = 0.2, ZPos = 0.0, XOff = 90.0, YOff = -100.0, ZOff = 90.0;

		STREAMING::REQUEST_NAMED_PTFX_ASSET("core");
		GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL("core");
		if ((timeGetTime() - TimePD5) > 200)
		{
			int ptfx = GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE("ent_sht_flame", PLAYER::PLAYER_PED_ID(), XPos, YPos, ZPos,
				XOff, YOff, ZOff, SKEL_Head, 1, 1, 1, 1);
			TimePD5 = timeGetTime();
		}
	}
	else
	{
		NULL;
	}

}

void SuperJump()
{
	if (superJump)
	{
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_PED_ID());
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
	}
	else
	{
		NULL;
	}
}

void setWeather(char* weather) {
	*(unsigned int*)0x10953F8 = 0x60000000;
	*(unsigned int*)0x10953A4 = 0x60000000;
	*(unsigned int*)0x3D3EB0 = 0x60000000;
	GAMEPLAY::S_W_N_P(weather);
}

bool unlim = false;

void unLim()
{
	if (unlim)
	{
		WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), true);
	}
	else
	{
		WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), false);
	}
}
 
void RGBswitch()
{
	if (r > 0 && b == 0) {
		r--;
		g++;
	}
	if (g > 0 && r == 0) {
		g--;
		b++;
	}
	if (b > 0 && g == 0) {
		r++;
		b--;
	}
}

void rpaint()
{
	if (Rpaint)
	{
		Ped playerped = PLAYER::PLAYER_PED_ID();
		{
			RGBswitch();
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(playerped);

			if (PED::IS_PED_IN_ANY_VEHICLE(playerped, 0));
			{
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, r, g, b);
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, r, g, b);
			}

		}
	}
}

void Onlinerpaint()
{
	if (OnlineRpaint)
	{
		Ped onlineped = PLAYER::GET_PLAYER_PED(selectedPlayer);
		{
			RGBswitch();
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(selectedPlayer), true);

			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(selectedPlayer), true))
			{
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, r, g, b);
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, r, g, b);
			}

		}
	}
}

void ExplodeLoop()
{
	if (explo_loop)
	{
		Vector3 targetCords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), false);
		FIRE::ADD_EXPLOSION(targetCords.x, targetCords.y, targetCords.z, 0, 0.0f, true, false, 10.0f);
	}
	else
	{
		NULL;
	}
}

void neverwanted()
{
	if (Neverwanted)
	{
		Memory::set_value<int32_t>({ (2 * 4 * 2) / 2, 4 * 1000 + 280, 0x0848 }, 0); 
	}
}

void CreateVehicleOnPlayer(char* hash) {
	Hash model = GAMEPLAY::GET_HASH_KEY(hash);
	if (STREAMING::IS_MODEL_VALID(model))
	{
		if (spawn_upg)
		{
		hooks::REQUEST_MODELL(model);
		while (!hooks::HAS_MODEL_LOADEDD(model)) WAIT(1);
		Vector3 ourCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
		float forward = 5.f;
		float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
		float xVector = forward * sin(degToRad(heading)) * -1.f;
		float yVector = forward * cos(degToRad(heading));
		Vehicle veh = VEHICLE::C_O_P(model, ourCoords.x + xVector, ourCoords.y + yVector, ourCoords.z, heading, true, true);
		RequestControlOfEnt(veh);
		VEHICLE::SET_VEHICLE_ENGINE_ON1(veh, true, true, true);
		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
		DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
		VEHICLE::SET_VEHICLE_IS_STOLEN(veh, false);
		auto networkId = NETWORK::VEH_TO_NET(veh);
		if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(veh))
			NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
		//GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("shop_controller");
		WAIT(150);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		for (int i = 0; i < 50; i++)
		{
			VEHICLE::SET_VEHICLE_MOD(veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1, false);
		}
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, "Too fast!");
	}
		else
		{
			hooks::REQUEST_MODELL(model);
			while (!hooks::HAS_MODEL_LOADEDD(model)) WAIT(1);
			Vector3 ourCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			float forward = 5.f;
			float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
			float xVector = forward * sin(degToRad(heading)) * -1.f;
			float yVector = forward * cos(degToRad(heading));
			Vehicle veh = VEHICLE::C_O_P(model, ourCoords.x + xVector, ourCoords.y + yVector, ourCoords.z, heading, true, true);
			RequestControlOfEnt(veh);
			VEHICLE::SET_VEHICLE_ENGINE_ON1(veh, true, true, true);
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
			DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
			VEHICLE::SET_VEHICLE_IS_STOLEN(veh, false);
			auto networkId = NETWORK::VEH_TO_NET(veh);
			if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(veh))
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
			//GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("shop_controller");
			WAIT(150);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
		}
  }
}
//-----------------------
INT g_lInfoBoxInfoCount;
FLOAT g_fInfoBoxTitleWidth = 0.20f;
FLOAT g_fInfoBoxTitleLength = 0.05f;
FLOAT fMenuTextOffset = 0.01300000000000000000000000000000f; // 0.01300000000000000000000000000000f
FLOAT fMenuTextSize = 0.35000000000000000000000000000000f; // 0.35000000000000000000000000000000f
FLOAT fMenuIncrement = 0.03703703703703703703703703703704f; // 0.03703703703703703703703703703704f
FLOAT fBannerPosX = 0.84895833333333333333333333333333f;	// 0.84895833333333333333333333333333f
FLOAT fBannerPosY = 0.08611111111111111111111111111111f;	// 0.08611111111111111111111111111111f
FLOAT fBannerSizeX = 0.22395833333333333333333333333333f;	// 0.22395833333333333333333333333333f
FLOAT fBannerSizeY = 0.09000000000000000000000000000000f;	// 0.09000000000000000000000000000000f
FLOAT fMenuScale = 1.0f;




VOID DrawSprite(PCHAR szDict, PCHAR szTexture, FLOAT fPosX, FLOAT fPosY, FLOAT fRot, RGBAA g_Col, FLOAT fScaleX = 1.0f, FLOAT fScaleY = 1.0f, bool resu = true) {
	INT g_ScreenRes[2];
	GRAPHICS::GET_SCREEN_RESOLUTION(&g_ScreenRes[0], &g_ScreenRes[1]);
	Vector3 g_TextureRes = GRAPHICS::GET_TEXTURE_RESOLUTION(szDict, szTexture);
	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(szDict, FALSE);
	while (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(szDict))
		WAIT(0);
	if (resu)
		GRAPHICS::DRAW_SPRITE(szDict, szTexture, fPosX, fPosY, (g_TextureRes.x / (FLOAT)g_ScreenRes[0]) * fScaleX, (g_TextureRes.y / (FLOAT)g_ScreenRes[1]) * fScaleY, fRot, g_Col.r, g_Col.g, g_Col.b, g_Col.a);
	else
		GRAPHICS::DRAW_SPRITE(szDict, szTexture, fPosX, fPosY, fScaleX, fScaleY, fRot, g_Col.r, g_Col.g, g_Col.b, g_Col.a);
}

void DrawText2(char * text, int font, float x, float y, float scalex, float scaley, int r, int b, int g, int a, bool center)
{
	UI::SET_TEXT_CENTRE(center);
	UI::SET_TEXT_COLOUR(r, g, b, a);
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(scalex, scaley);
	UI::SET_TEXT_DROPSHADOW(1, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(1, 0, 0, 0, 0);
	UI::SET_TEXT_OUTLINE();
	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)text);
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(x, y);

}

void DrawSprite1(char * Streamedtexture, char * textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(Streamedtexture, false);
	if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(Streamedtexture));
	GRAPHICS::DRAW_SPRITE(Streamedtexture, textureName, x, y, width, height, rotation, r, g, b, a);
}

VOID DrawVehicleImagePreview(PCHAR l_pszModelName) 
{
	INT l_lScreenRes[2];
	GRAPHICS::GET_SCREEN_RESOLUTION(&l_lScreenRes[0], &l_lScreenRes[1]);
	for (INT i = 0; i < sizeof(*RtlpNumberOf(g_pszVehicleImageDicts)); i++) {//wait Drawing::Spriter //U can just hit 
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(g_pszVehicleImageDicts[i], TRUE);
		if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(g_pszVehicleImageDicts[i])) {
			Vector3 l_lTextureRes = GRAPHICS::GET_TEXTURE_RESOLUTION(g_pszVehicleImageDicts[i], l_pszModelName);// put ur position i don-t know where it gonna be becouse yhe ididn't do posotion for that! But my menu x is 
			if (l_lTextureRes.x > 64.0f && l_lTextureRes.y > 64.0f) {
					DrawSprite(g_pszVehicleImageDicts[i], l_pszModelName, (fBannerPosX >= 0.5f) ? (fBannerSizeX - (fBannerSizeX / 2) - ((l_lTextureRes.x / (FLOAT)l_lScreenRes[0]) / 2)) : (fBannerPosX + (fBannerSizeX / 2) + ((l_lTextureRes.x / (FLOAT)l_lScreenRes[0]) / 2)), (fBannerPosY - ((fBannerSizeY / 2)) + ((l_lTextureRes.y / (FLOAT)l_lScreenRes[1]) / 2)), 0.0f, RGBAA(255, 255, 255, 255));
				DrawSprite(g_pszVehicleImageDicts[i], l_pszModelName, (fBannerPosX - (((fBannerSizeX * fMenuScale) * fMenuScale) / 2) - (g_fInfoBoxTitleWidth / 2)), ((fBannerPosY - ((((fBannerSizeY * fMenuScale) * fMenuScale) / 2)) + (g_fInfoBoxTitleLength / 2)) + (g_fInfoBoxTitleLength / 2)) + ((g_lInfoBoxInfoCount * (g_fInfoBoxTitleLength / 2)) / 2) + 0.0035f, 0.0f, RGBAA(255, 255, 255, 255)); // fine 
					GRAPHICS::DRAW_RECT((fBannerPosX - (((fBannerSizeX * fMenuScale) * fMenuScale) / 2) - (g_fInfoBoxTitleWidth / 2)), ((fBannerPosY - ((((fBannerSizeY * fMenuScale) * fMenuScale) / 2)) + (g_fInfoBoxTitleLength / 2)) + (g_fInfoBoxTitleLength / 2)) + ((g_lInfoBoxInfoCount * (g_fInfoBoxTitleLength / 2)) / 2) + 0.0035f, g_fInfoBoxTitleWidth, (g_lInfoBoxInfoCount * (g_fInfoBoxTitleLength / 2)) + 0.007f, 180,122,170,255);
			}
		} 
	}
}





//void ReturnVehicleInformation(Hash VehicleHash, CHAR* vehicleDirectory = "www_legendarymotorsport_net", CHAR* vehicleTexture = "lms_pattern") { //sure i'll upload to mediafire. make sure u do v141 as sdk i think nha do no upgrade and latest sdk okey  i will now also i need to update my gta too lmfao is here a auth like i need to put something in my folders or what? tHe auth is from website and databse. But the banner and all that is stored in appdata ahh so menu have a auth right? yhe it does ahh secured auth? yHE 
//	int VehicleScaleForm = GRAPHICS::REQUEST_SCALEFORM_MOVIE("mp_car_stats_01");
//
//	if (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(VehicleHash))
//		VehicleScaleForm = GRAPHICS::REQUEST_SCALEFORM_MOVIE("mp_car_stats_01");
//	else {
//		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(VehicleScaleForm, "SET_VEHICLE_INFOR_AND_STATS");
//		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_FLOAT(UI::_0x95C4B5AD(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(VehicleHash)));
//	GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_STRING("Vehicle Stats");
//		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_STRING(subroute_CHUD(sub_21170(VehicleHash)));
//		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_STRING(sub_21170(VehicleHash));
//		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_STRING("Top Speed");
//		GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_STRING("Acceleration");
//		//GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_STRING("Braking");
//		//GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_STRING("Traction");
//		//GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(SYSTEM::ROUND(VEHICLE::_0x8F291C4A(VehicleHash)));
//		//GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(SYSTEM::ROUND(VEHICLE::GET_VEHICLE_MODEL_ACCELERATION(VehicleHash)));
//		//GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(SYSTEM::ROUND(VEHICLE::GET_VEHICLE_MODEL_MAX_BRAKING(VehicleHash)));
//		//GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(SYSTEM::ROUND(VEHICLE::GET_VEHICLE_MODEL_MAX_TRACTION(VehicleHash)));
//		GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
//	}
//	//GRAPHICS::DRAW_SCALEFORM_MOVIE11(VehicleScaleForm, design3 + 0.2, 0.3951389 + 0.01, 0.75, 0.80, 255, 255, 255, 255, 0);
//
//	if (vehicleDirectory == "www_legendarymotorsport_net" && vehicleTexture == "lms_pattern")
//		PrintText("No Vehicle Preview", 1, design3, 0.3951389 + 0.4902778, 0.4, 0.4, 255, 255, 255, 255, true, true);
//	else
//		DrawSprite1(vehicleDirectory, vehicleTexture, design3 + 0.2, 0.3951389 + 0.4902778, 0.1359375, 0.1333333, 0, 255, 255, 255, 255);
//}

float VehicleSpriteX = 0.535f;
int optionsRed = 255;
int optionsGreen = 255;
int optionsBlue = 255;
int optionsOpacity = 255;

void AddSpawnVehicle(char* option, char* model, char* Streamedtexture = "www_legendarymotorsport_net", char* textureName = "lms_pattern")
{
	Menu::Option(option);
	if (Menu::Settings::currentOption <= 16 && Menu::Settings::optionCount <= 16)
	{

		if (vehiclePrev)
		{
			GRAPHICS::DRAW_RECT(0.570, 0.166, 0.200, 0.200, 20, 20, 20, 255);
			Menu::Drawing::Spriter(Streamedtexture, textureName, 0.570, 0.166, 0.200, 0.200, 0, 255, 255, 255, 255);
			if (Streamedtexture == "www_legendarymotorsport_net" && textureName == "lms_pattern")
			{
				DrawText2("Image preview not found.", 0, 0.570, 0.148, 0.350, 0.350, 255, 255, 255, 255, true);
			}
		}

	}
	if (Menu::Settings::selectPressed ){
		hash_veh = GAMEPLAY::GET_HASH_KEY(model);
		SpawnVehicle = true;

		/*TopText(JoinStrings("Vehicle: ", option, " ~g~Spawned"));*/
	}

	
}

//Important shit LOL

typedef void(__fastcall* tSetLobbyWeather)(char a1, int a2, int a3, __int64 a4);
static void SetLobbyWeathers(char a1, int a2, int a3, __int64 a4) { static tSetLobbyWeather oSetLobbyWeather = (tSetLobbyWeather)(Memory::pattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 40 8A E9 48 8B 0D ? ? ? ? 8B F2 33 D2 49 8B D9 41 8B F8 E8 ? ? ? ? 84 C0 74 77 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 1B 44 8B CF 44 8B C6 40 8A D5 48 8B C8 48 89 5C 24 ? E8 ? ? ? ? 48 8B D8 EB 02 33 DB 48 8B 0D ? ? ? ? BF ? ? ? ? 8B D7 E8 ? ? ? ? 48 85 C0 74 22 4C 8B 00 48 8B D3 48 8B C8 41 FF 90 ? ? ? ? 84 C0 74 0E 48 8B 0D ? ? ? ? 8B D7 E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 8B D3 E8 ? ? ? ? 48 8B 5C 24 ?").count(1).get(0).get<void>()); return oSetLobbyWeather(a1, a2, a3, a4); }

//Make notify

void notifyBlocked(char* fmt, ...)
{
	char buf[2048] = { 0 };
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);
	//
	char buff2[2048] = { 0 };
	sprintf_s(buff2, "%s", buf);

	UI::_SET_NOTIFICATION_BACKGROUND_COLOR(6);
	UI::_SET_NOTIFICATION_FLASH_COLOR(255, 0, 0, 255);
	UI::_SET_NOTIFICATION_TEXT_ENTRY((char*)"STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
	UI::_DRAW_NOTIFICATION(1, 1);
}
void notifyBlocked(std::string str)
{
	notifyBlocked(&str[0]);
}

//Define weathers
std::size_t WeatherTypePos = 0;
char* WeatherTypes[] =
{
	"EXTRASUNNY", //1
	"CLEAR", //2
	"CLOUDS", //3
	"SMOG", //4
	"FOGGY", //5
	"OVERCAST", //6
	"RAIN", //7
	"THUNDER", //8
	"CLEARING", //9
	"NEUTRAL", //10
	"SNOW", //11
	"BLIZZARD", //12
	"SNOWLIGHT", //13
	"XMAS", //14
	"HALLOWEEN", // 15
	"BLACK SCREEN" //16
};

//Create option to change

void SetNetworkWeather(int weather)
{
	if (NETWORK::NETWORK_IS_IN_SESSION())
	{
		SetLobbyWeathers(1, weather, 76, 0);//
	}//
	else {
		notifyBlocked((char*)"You must be online to use this option.");
		return;
	}
}//48 8B D9 0F 84 ? ? ? ? 8A 49 2D 

void addVehicleOption(char *option, Hash vehicle, char* Streamedtexture = "www_legendarymotorsport_net", char* textureName = "lms_pattern", char *info = NULL)
{
	Menu::Option(option);
	if (Menu::Settings::currentOption <= 16 && Menu::Settings::optionCount <= 16)
	{
		//LastVehicle = false;
		if (vehiclePrev)
		{
			GRAPHICS::DRAW_RECT(0.570, 0.166, 0.200, 0.200, 20, 20, 20, 255);
			Menu::Drawing::Spriter(Streamedtexture, textureName, 0.570, 0.166, 0.200, 0.200, 0, 255, 255, 255, 255);
			if (Streamedtexture == "www_legendarymotorsport_net" && textureName == "lms_pattern")
			{
				DrawText2("Image preview not found.", 0, 0.570, 0.148, 0.350, 0.350, 255, 255, 255, 255, true);
			}
		}
		if (Menu::Settings::selectPressed && STREAMING::IS_MODEL_VALID(vehicle))
		{
			VehicleSpawCoords = ENTITY::GET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), false);
			//SpeedVehicle = ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0));
			//SpeedVehicle = VEHICLE::GET_VEHICLE_ACCELERATION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0));
			vehicleToSpawnHash = vehicle;
			vehicleSpawnNeeded = true;
			hooks::REQUEST_MODELL(vehicle);
			/*if (DisablePTFXSpawn)
			{
				addFXTeleport(vehicleSpawnFx);
			}*/
		}
	}
}

//It does work i tryed where is ur selection toggle what u mean?

void Online::MoneyDrop()
{
	if (moneyDrop)
	{
		if ((timeGetTime() - TimePD5) > 50) { // 1000 is delay 1000 ms so 1 sec 
			hooks::REQUEST_MODELL(PROP_MONEY_BAG_03);
			//Getting online player coords - Using Vector3
			Vector3 player = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true);
			if (hooks::HAS_MODEL_LOADEDD(PROP_MONEY_BAG_03))
			{
#define CREATE_A hooks::CREATE_AMBIENT_PICKUP // for surness // safe btw why do rename like alosmote all natives //ahh .....
				CREATE_A(PICKUP_MONEY_CASE, player.x, player.y, player.z + 3, 0, 2500, PROP_MONEY_BAG_03, true, false);
				hooks::SET_MODEL_AS_NO_LONGER_NEEDEDD(PROP_MONEY_BAG_03);
				TimePD5 = timeGetTime();
			}
		}
	}
	else
	{
		NULL;
	}
}

// enjoy tnx! Could you send me thje code over for money you showed me last night // work others in this project ? Nha only me i hope 

int attachobj[100];

int nuattach = 1;

void Online::attachobjects2(char* object)
{
	bool custom = false;
	int hash = 0;
	Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), true);
	hash = GAMEPLAY::GET_HASH_KEY(object);
	if (STREAMING::IS_MODEL_IN_CDIMAGE(hash))
	{
		if (STREAMING::IS_MODEL_VALID(hash))
		{
			hooks::REQUEST_MODELL(hash);
			if (hooks::HAS_MODEL_LOADEDD(hash))
			{
				attachobj[nuattach] = OBJECT::CREATE_OBJECT(hash, pos.x, pos.y, pos.z, 1, 1, 1);
				if (ENTITY::DOES_ENTITY_EXIST(attachobj[nuattach]))
				{
					ENTITY::ATTACH_ENTITY_TO_ENTITY(attachobj[nuattach], PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), 31086, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 1);
					nuattach++;
					if (nuattach >= 101) { nuattach = 1; }
				}
			}
		}
	}
}

bool spec = false;

void Spectate()
{
	if (spec)
	{
		NETWORK::SPECTATE(true, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer));
	}
	else
	{
		NETWORK::SPECTATE(false, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer));
	}
}

void ExplosiveAmmoSmall() // small explosion
{
	Vector3 explosivecoords;
	if (xpx_ammo)
	{
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &explosivecoords))
		{
			FIRE::E_P_X(explosivecoords.x, explosivecoords.y, explosivecoords.z, 18, 18, true, false, 0);
		}
	}
	else
	{
		NULL;
	}
}

namespace bools
{
	bool WrapInVehicle = false, SpawnMaxVehicle = true, SpawnEffectVehicle = true, SpawnWithCustom = true, VeicleFrontLight = true;
}

void Vehicle_Spawner_Loop() {
	//if (SpawnVehicle) {
	//	if (!hooks::HAS_MODEL_LOADEDD(hash_veh))
	//		hooks::REQUEST_MODELL(hash_veh);
	//	else
	//	{
	//		float speed = ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0));
	//		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
	//		CheckVehicle[AddSpawnVehiclelot] = VEHICLE::CREATE_VEHICLE(hash_veh, coords.x + 2, coords.y, coords.z, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 1, 0);
	//		if (ENTITY::DOES_ENTITY_EXIST(CheckVehicle[AddSpawnVehiclelot]))
	//		{
	//			Vehicle SpawnDelete = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
	//			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(SpawnDelete, 1, 1);
	//			ENTITY::DELETE_ENTITY(&SpawnDelete);
	//			VEHICLE::SET_VEHICLE_ENGINE_ON(CheckVehicle[AddSpawnVehiclelot], true, true);
	//			VEHICLE::SET_VEHICLE_FORWARD_SPEED(CheckVehicle[AddSpawnVehiclelot], speed);

	//			ENTITY::SET_ENTITY_INVINCIBLE(CheckVehicle[AddSpawnVehiclelot], 1);
	//			VEHICLE::SET_VEHICLE_DIRT_LEVEL(CheckVehicle[AddSpawnVehiclelot], 0.0f);
	//			VEHICLE::SET_VEHICLE_CAN_BREAK(CheckVehicle[AddSpawnVehiclelot], 0);
	//			ENTITY::SET_ENTITY_CAN_BE_DAMAGED(CheckVehicle[AddSpawnVehiclelot], 0);
	//			ENTITY::SET_ENTITY_PROOFS(CheckVehicle[AddSpawnVehiclelot], 1, 1, 1, 1, 1, 1, 1, 1);
	//			VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(CheckVehicle[AddSpawnVehiclelot], 0);
	//			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(CheckVehicle[AddSpawnVehiclelot], 0);
	//			if (bools::WrapInVehicle) {
	//				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), CheckVehicle[AddSpawnVehiclelot], -1);
	//			}
	//			if (bools::SpawnMaxVehicle) {
	//	/*			MAX_VEHICLE_UPGRADE(CheckVehicle[AddSpawnVehiclelot]);*/ 
	//			}
	//		/*	if (!SpawnEffectVehicle) {
	//				NETWORK::NETWORK_FADE_IN_ENTITY(CheckVehicle[AddSpawnVehiclelot], true);
	//				GRAPHICS::_SET_PTFX_ASSET_OLD_2_NEW("scr_firework_indep_repeat_burst_rwb", "scr_firework_xmas_repeat_burst_rgw");
	//				STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("proj_xmas_firework");
	//				STREAMING::REQUEST_NAMED_PTFX_ASSET("proj_xmas_firework");
	//				GRAPHICS::_SET_PTFX_ASSET_NEXT_CALL("proj_xmas_firework");
	//				GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2("scr_firework_indep_repeat_burst_rwb", coords.x, coords.y, coords.z, 0.0, 0.0, 0.0, 1.0f, 1, 1, 1);
	//			}*/
	//			if (bools::SpawnWithCustom) {
	//				//VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(CheckVehicle[AddSpawnVehiclelot], CustomPrimaryR, CustomPrimaryG, CustomPrimaryB);
	//				//VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(CheckVehicle[AddSpawnVehiclelot], CustomSecondaryR, CustomSecondaryG, CustomSecondaryB);
	//				//VEHICLE::SET_VEHICLE_COLOURS(CheckVehicle[AddSpawnVehiclelot], SetPrimaryColour, SetSecondaryColour);
	//				//VEHICLE::SET_VEHICLE_EXTRA_COLOURS(CheckVehicle[AddSpawnVehiclelot], VehicleExtraColour, SetWheelPaint);
	//			}
	//			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(CheckVehicle[AddSpawnVehiclelot], TRUE, TRUE);
	//			NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(CheckVehicle[AddSpawnVehiclelot]), 1);
	//			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash_veh);
	//			AddSpawnVehiclelot++;
	//			SpawnVehicle = false;
	//		}
	//		/*if (VeicleFrontLight) {
	//			VEHICLE::SET_VEHICLE_MOD_KIT(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0);
	//			VEHICLE::TOGGLE_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), MOD_XENONLIGHTS, 1);
	//		}
	//		else {
	//			VEHICLE::SET_VEHICLE_MOD_KIT(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0);
	//			VEHICLE::TOGGLE_VEHICLE_MOD(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), MOD_XENONLIGHTS, 0);
	//		}*/
	//	}
	//}
	if (vehicleSpawnNeeded)
	{
		Loading += 8.0f;
		if (!hooks::HAS_MODEL_LOADEDD(vehicleToSpawnHash)) {
			DrawSprite1("mpleaderboard", "leaderboard_time_icon", 0.280f, 0.132f, 0.025f, 0.0444f, Loading, 255, 255, 255, 255);
		}
		if (hooks::HAS_MODEL_LOADEDD(vehicleToSpawnHash))
		{
			/*if (DeleteLastVeh)
			{
				Vehicle Curr = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 1);
				VEHICLE::DELETE_VEHICLE(&Curr);
			}*/

			Ped ped = PLAYER::PLAYER_PED_ID();
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped, false);
			float Heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
			//if (!DeleteLastVeh)
			//{
			//	GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0)), &minDimension, &minDimension);
			//	float spawnOffY = max(5.0f, 2.0f + 0.5f * (maxDimension.y - minDimension.y));

			//	Vector3 SelfWorldCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, spawnOffY, 0.0);
			//	Vector3 SelfWorldCoords2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 0.0, spawnOffY, 0.0);
			//	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1))
			//		spawnedVehHandle[numSpawned] = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, SelfWorldCoords2.x, SelfWorldCoords2.y, SelfWorldCoords2.z, Heading, 1, 0);
			//	else
			//		spawnedVehHandle[numSpawned] = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, SelfWorldCoords.x, SelfWorldCoords.y, SelfWorldCoords.z, Heading, 1, 0);
			//}
			//else
			//{
			//	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1))
			//		spawnedVehHandle[numSpawned] = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, VehicleSpawCoords.x, VehicleSpawCoords.y, VehicleSpawCoords.z, Heading, 1, 0);
			//	else
			//		spawnedVehHandle[numSpawned] = VEHICLE::CREATE_VEHICLE(vehicleToSpawnHash, coords.x, coords.y, coords.z, Heading, 1, 0);
			//}
			if (ENTITY::DOES_ENTITY_EXIST(spawnedVehHandle[numSpawned]))
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(spawnedVehHandle[numSpawned]);
				if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(spawnedVehHandle[numSpawned]))
				{
					DWORD id = NETWORK::NET_TO_VEH(spawnedVehHandle[numSpawned]);
					id;
					NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(id, true);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(spawnedVehHandle[numSpawned], SpeedVehicle);
					if (!ENTITY::IS_ENTITY_IN_AIR(PLAYER::PLAYER_PED_ID()))
						VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(spawnedVehHandle[numSpawned]);
					ENTITY::SET_ENTITY_VISIBLE1(spawnedVehHandle[numSpawned], TRUE);
					VEHICLE::SET_HELI_BLADES_FULL_SPEED(spawnedVehHandle[numSpawned]);
					VEHICLE::SET_VEHICLE_ENGINE_ON(spawnedVehHandle[numSpawned], TRUE, TRUE);
					VEHICLE::TOGGLE_VEHICLE_MOD(spawnedVehHandle[numSpawned], 20, TRUE);
					VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(spawnedVehHandle[numSpawned], 255, 0, 0);
					ENTITY::_SET_ENTITY_SOMETHING(spawnedVehHandle[numSpawned], TRUE);
				}
			}
		}
	}
}

void ExplosiveAmmoNormal() // Normal Explosion
{
	Vector3 explosivecoords;
	if (xpx_ammo1)
	{
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &explosivecoords))
		{
			FIRE::E_P_X(explosivecoords.x, explosivecoords.y, explosivecoords.z, 5, 5, true, false, 0);
		}
	}
	else
	{
		NULL;
	}
}

void ExplosiveAmmoBig() // Big Explosion
{
	Vector3 explosivecoords;
	if (xpx_ammo2)
	{
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &explosivecoords))
		{
			FIRE::E_P_X(explosivecoords.x, explosivecoords.y, explosivecoords.z, 8, 8, true, false, 0);
		}
	}
	else
	{
		NULL;
	}
}

void MolotovGun() // Molotov Gun
{
	Vector3 explosivecoords;
	if (molo_gun)
	{
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &explosivecoords))
		{
			FIRE::E_P_X(explosivecoords.x, explosivecoords.y, explosivecoords.z, 3, 3, true, false, 0);
		}
	}
	else
	{
		NULL;
	}
}

void FlareGun() // Flare Gun
{
	Vector3 explosivecoords;
	if (flare_gun)
	{
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &explosivecoords))
		{
			FIRE::E_P_X(explosivecoords.x, explosivecoords.y, explosivecoords.z, 22, 22, true, false, 0);
		}
	}
	else
	{
		NULL;
	}
}

void SmokeGun() // Smoke Gun
{
	Vector3 explosivecoords;
	if (smoke_gun)
	{
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &explosivecoords))
		{
			FIRE::E_P_X(explosivecoords.x, explosivecoords.y, explosivecoords.z, 19, 19, true, false, 0);
		}
	}
	else
	{
		NULL;
	}
}

void WaterGun() // Smoke Gun
{
	Vector3 explosivecoords;
	if (water_gun)
	{
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &explosivecoords))
		{
			FIRE::E_P_X(explosivecoords.x, explosivecoords.y, explosivecoords.z, 13, 13, true, false, 0);
		}
	}
	else
	{
		NULL;
	}
}

void DeleteGun()
{
	if (delete_gun)
	{
		if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()) && PED::IS_PED_SHOOTING_IN_AREA)
		{
			Vector3 deltetecoords;
			if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &deltetecoords))
			{
				GAMEPLAY::_CLEAR_AREA_OF_EVERYTHING(deltetecoords.x, deltetecoords.y, deltetecoords.z, 2, 0, 0, 0, 0);
			}
		}
	}
	else
	{
		NULL;
	}
}

void TeleportGun()
{
	if (teleport_gun)
	{
		if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()) && PED::IS_PED_SHOOTING_IN_AREA)
		{
			Vector3 teleportcoords;
			if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &teleportcoords))
			{
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), teleportcoords.x, teleportcoords.y, teleportcoords.z + 1, 0, 0, 0, 0);
			}
		}
		else
		{
			NULL;
		}
	}
}

void WaterLoop(Player target)
{
	if (waterLoop)
	{
		Player selectedPlayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
		Vector3 Pos = ENTITY::GET_ENTITY_COORDS(selectedPlayer, true);
		FIRE::ADD_EXPLOSION(Pos.x, Pos.y, Pos.z, 12, 5, true, 0, 0);
	}
	else
	{
		NULL;
	}
}

void FireLoop(Player target)
{
	if (playerfireloop)
	{
		Player victim = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer);
		Vector3 Pos = ENTITY::G_C_O_E(selectedPlayer, true);
		FIRE::E_P_X(Pos.x, Pos.y, Pos.z, 12, 5, true, 0, 0);
	}
}

void MoneyGunMe() {
	if (moneyGunme)
	{
		Vector3 shootcoords;
		//if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()) && PED::IS_PED_SHOOTING_IN_AREA) // lol // u dont neet this crab
		//{
			hooks::REQUEST_MODELL(PROP_MONEY_BAG_03);
				if (hooks::HAS_MODEL_LOADEDD(PROP_MONEY_BAG_03))
				{
					if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &shootcoords))
					{
#define W_P_CREATE OBJECT::A_P_O_P
					W_P_CREATE(PICKUP_MONEY_CASE, shootcoords.x, shootcoords.y, shootcoords.z + 0.5, 0, 2500, PROP_MONEY_BAG_03, 0, 1);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PROP_MONEY_BAG_03);
				} // wait a sec why 0 and 1 // 0 = false 1 = true
			}
		//}
     }
	else
	{
		NULL;
	}
}

void MoneyGunThem() {
	if (player_money_gun)
	{
		Vector3 themshootcoords;
		//if (ENTITY::DOES_ENTITY_EXIST(PLAYER::PLAYER_PED_ID()) && PED::IS_PED_SHOOTING_IN_AREA) // lol // u dont neet this crab
		//{
		hooks::REQUEST_MODELL(PROP_MONEY_BAG_03);
		if (hooks::HAS_MODEL_LOADEDD(PROP_MONEY_BAG_03))
		{
			if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_ONLINE_PLAYER_ID(selectedPlayer), &themshootcoords))
			{
#define W_P_CREATE OBJECT::A_P_O_P
				W_P_CREATE(PICKUP_MONEY_CASE, themshootcoords.x, themshootcoords.y, themshootcoords.z + 0.5, 0, 2500, PROP_MONEY_BAG_03, 0, 1);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PROP_MONEY_BAG_03);
			} // 0 = false 1 = true
		}
		//}
	}
	else
	{
		NULL;
	}
}

Vector3 theyshootexlo;

void GiveExplosiveGun() 
{
	if (player_explo_gun)
	{
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_ONLINE_PLAYER_ID(selectedPlayer), &theyshootexlo))
		{
			FIRE::E_P_X(theyshootexlo.x, theyshootexlo.y, theyshootexlo.z, 18, 18, true, false, 0);
		}
	}
	else
	{
		NULL;
	}
}

void CyrcleNew()
{
	if (cyrclenew)
	{
		Ped iPed = PLAYER::PLAYER_PED_ID();
		if ((timeGetTime() - TimePD5) > 100) {
			hooks::REQUEST_MODELL(PROP_MONEY_BAG_03);
			if (!hooks::HAS_MODEL_LOADEDD(PROP_MONEY_BAG_03)) {
				WAIT(0);
			}

			Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(iPed, FALSE);
#define P_M_M_D_P OBJECT::M_P_O_P_M
			P_M_M_D_P(playerPosition.x, playerPosition.y, playerPosition.z, 2500, 1, PROP_MONEY_BAG_03);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PROP_MONEY_BAG_03);
			TimePD5 = timeGetTime();
		}
	}
		else
		{
			NULL;
		}
	  // ahh nah wait 
}//done wait

void MoneyAroundPlayer()
{
	if (moneyRound)
	{
		Ped OnlinePed = PLAYER::GET_PLAYER_PED(selectedPlayer);
		if ((timeGetTime() - TimePD5) > 500) {
			hooks::REQUEST_MODELL(PROP_MONEY_BAG_03);
			if (!hooks::HAS_MODEL_LOADEDD(PROP_MONEY_BAG_03)) {
				WAIT(0);
			}

			Vector3 playerPosition1 = ENTITY::GET_ENTITY_COORDS(OnlinePed, FALSE);
#define P_M_M_D_P OBJECT::M_P_O_P_M
			P_M_M_D_P(playerPosition1.x, playerPosition1.y, playerPosition1.z, 2500, 1, PROP_MONEY_BAG_03);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PROP_MONEY_BAG_03);
			TimePD5 = timeGetTime();
		}
	}
	else
	{
		NULL;
	}
	// ahh nah wait 
}//done wait

void PlayerAlwaysWanted()
{
	if (playerAlwanted)
	{
		PLAYER::SET_PLAYER_WANTED_LEVEL(PLAYER::GET_ONLINE_PLAYER_ID(selectedPlayer), + 5, true);
	}
	else
	{
		NULL;
	}
}

bool hornboost = false;

void HornBoostThem()
{
	if (hornBoostThem)
	{
		if (PLAYER::IS_PLAYER_PRESSING_HORN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::GET_PLAYER_PED(selectedPlayer))))
		{
			Vehicle Veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::GET_PLAYER_PED(selectedPlayer)), false);
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Veh);
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Veh))
			{
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(Veh, 50);
			}//change bool name please
		}
	}
}

void FreezePlayer() 
{
	if (freeze)
	{
		AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED(selectedPlayer));
	}
	else
	{
		NULL;
	}
}

//N_R_C_O_E = NETWORK_REQUEST_CONTROL_OF_ENTITY
//N_H_C_O_E = NETWORK_HAS_CONTROL_OF_ENTITY

/*void HornBoostThem()
{
	if (hornBoostThem)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(selectedPlayer), true))
		{
				Vehicle carBoost = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), true);
				NETWORK::N_R_C_O_E(carBoost);
				if (NETWORK::N_H_C_O_E(carBoost))
				{
					if (PLAYER::IS_PLAYER_PRESSING_HORN(PLAYER::GET_PLAYER_PED(selectedPlayer)))
					{
						VEHICLE::SET_VEHICLE_FORWARD_SPEED(carBoost, 40);
					}
				}
			}
		}
		else
		{
			NULL;
		}
}
*/

void BoostTherCarNoNontrolled()
{
	if (nocontrolBoost)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(selectedPlayer), true))
		{
			Vehicle carBoost = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), true);
			NETWORK::N_R_C_O_E(carBoost);
			if (NETWORK::N_H_C_O_E(carBoost))
			{
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(carBoost, 40);
			}
		}
	}
	else
	{
		NULL;
	}
}

void HornBoostMe() {
	if (hornBoostme)
	{
		if (PLAYER::IS_PLAYER_PRESSING_HORN(PLAYER::PLAYER_ID()))
		{
			Vehicle Veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), false);
			NETWORK::N_R_C_O_E(Veh);
			if (NETWORK::N_H_C_O_E(Veh))
			{
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(Veh, 40);
			}
		}
	}
	else
	{
		NULL;
	}
}

//wait

void DisableWeaponOnl()
{
	if (disweap)
	{
		PED::SET_DISABLE_WEAPONS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), true);
	}
}

void Me::Invisibility()
{
	if (invisable)
	{
		ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), false, 0);
	}
	else
	{
		ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, 0);
	}
}

int Handle_Player(int selectedPlayer)
{
	int Handle = 0;
	NETWORK::NETWORK_HANDLE_FROM_PLAYER(selectedPlayer, 13, 5);
	return Handle;
}

void sendText(char* text, int player)
{
	NETWORK::NETWORK_SEND_TEXT_MESSAGE("", Handle_Player(PLAYER::GET_PLAYER_PED(selectedPlayer)));
}

void RpIncreace()
{
	if (rp_incr)
	{
		Memory::set_value<float>({ OFFSET_PLAYER , OFFSET_PLAYER_INFO , OFFSET_PLAYER_INFO_WANTED }, +5);
		WAIT(1000);
		Memory::set_value<float>({ OFFSET_PLAYER , OFFSET_PLAYER_INFO , OFFSET_PLAYER_INFO_WANTED }, -5);
	}
	else
	{
		Memory::set_value<float>({ OFFSET_PLAYER , OFFSET_PLAYER_INFO , OFFSET_PLAYER_INFO_WANTED }, -5);
	}
}

/*
  void get_event_data(int EventId, int ArgsSize)
{
	int* ArgsStruct;
	SCRIPT::GET_EVENT_DATA(1, EventId, ArgsStruct, ArgsSize);


	int* ArgsStr[2];
	SCRIPT::GET_EVENT_DATA(1, EventId, ArgsStr[2], ArgsSize);
	notifyMap(SCRIPT::GET_THIS_SCRIPT_NAME()); //it's prob the notifyMap fumnction
	notifyMap(SCRIPT::_GET_NUMBER_OF_INSTANCES_OF_SCRIPT_WITH_NAME_HASH);
}


bool seeeventid = false;
void SeeEventID()
{
	if (seeeventid)
	{
		get_event_data;
	}
}
*/

//Or maybe it can be TriggerScriptEvent function as well. Maybe that one aswell!

//Important - Script event function

static void TriggerScriptEvent(int eventGroup, uint64_t* args, int argCount, int bit)
{
	static auto func = reinterpret_cast<void(*)(int, uint64_t*, int, int)>(Memory::pattern("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 81 EC ? ? ? ? 45 8B F0 41 8B F9").count(1).get(0).get<void>(0));
	func(eventGroup, args, argCount, bit);
}

/*All Players*/
void RemoveAllPlayersWeps()
{
	for (int i = 0; i < 32; i++)
	{
		if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) {
			if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) != PLAYER::PLAYER_PED_ID())
			{
				Player allplayers = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
				if (!(cstrcmp(PLAYER::GET_PLAYER_NAME(i), "-")))
				{
					WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(allplayers), true);
				}
			}
		}
	}
}

void GiveAllPlayersWeps()
{
	for (int i = 0; i < 32; i++)
	{
		if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) {
			Player allplayers = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
			if (!(cstrcmp(PLAYER::GET_PLAYER_NAME(i), "-")))
			{
				if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) != PLAYER::PLAYER_PED_ID())
				{
					uint Weapons[]{ 0xAF3696A1, 0x476BF155, 0xB62D1F670, 0xDFE37640, 0xC1B3C3D1, 0x99B507EA, 0x678B81B1, 0x4E875F73, 0x958A4A8F, 0x440E4788, 0x84BD7BFD, 0x1B06D571, 0x5EF9FEC4, 0x22D8FE39, 0x99AEEB3B, 0x13532244, 0x2BE6766B, 0xEFE7E2DF, 0xBFEFFF6D, 0x83BF0278, 0xAF113F99, 0x9D07F764, 0x7FD62962, 0x1D073A89, 0x7846A318, 0xE284C527, 0x9D61E50F, 0x3656C8C1, 0x05FC3C11, 0x0C472FE2, 0x33058E22, 0xA284510B, 0x4DD2DC56, 0xB1CA77B1, 0x687652CE, 0x42BF8A85, 0x93E220BD, 0x2C3731D9, 0xFDBC8A50, 0x24B17070, 0x060EC506, 0x34A67B97, 0xFDBADCED, 0x23C9F95C, 0x497FACC3, 0xF9E6AA4B, 0x61012683, 0xC0A3098D, 0xD205520E, 0xBFD21232, 0x7F229F94, 0x92A27487, 0x083839C4, 0x7F7497E5, 0xA89CB99E, 0x3AABBBAA, 0xC734385A, 0x787F0BB, 0x47757124, 0xD04C944D, GAMEPLAY::GET_HASH_KEY("WEAPON_HATCHET"), GAMEPLAY::GET_HASH_KEY("WEAPON_RAILGUN") };
					for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
						WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(allplayers), Weapons[i], 9999, 1);
					}
				}
			}
		}
	}
}
//Creating void to make an pickup for all players
void dropPickup(Vector3 Location, char* PickupModel, char* PickupBehavior, int PickupAmount)
{
	int Model = GAMEPLAY::GET_HASH_KEY(PickupModel);
	int Behavior = GAMEPLAY::GET_HASH_KEY(PickupBehavior); //"PICKUP_MONEY_CASE"
	hooks::REQUEST_MODELL(Model);
	if (hooks::HAS_MODEL_LOADEDD(Model))
	{
		Location.z += 1;
		OBJECT::CREATE_AMBIENT_PICKUP(Behavior, Location.x, Location.y, Location.z, 0, PickupAmount, Model, 0, 2);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Model);
	}
}
//void to spawn the pickup
/*
void MoneyDropAll()
{
	if (money_all)
	{
		for (int i = 0; i < 32; i++)
		{
			if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) {
				Player allplayers = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
				Vector3 allplayerscoord = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), true);//Getting coords from all players in lobby
				if (!(cstrcmp(PLAYER::GET_PLAYER_NAME(i), "-")))
				{
					if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) != PLAYER::PLAYER_PED_ID())
					{
						if (hooks::HAS_MODEL_LOADEDD(PROP_MONEY_BAG_03))
						{
#define CREATE_A OBJECT::A_P_O_P // for surness // safe btw why do rename like alosmote all natives //ahh .....
							CREATE_A(PICKUP_MONEY_CASE, allplayerscoord.x, allplayerscoord.y, allplayerscoord.z + 3, 0, 2500, PROP_MONEY_BAG_03, true, false);
							STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PROP_MONEY_BAG_03);
							TimePD5 = timeGetTime();
						}
					}
				}
			}
		}
	}
	else
	{
		NULL;
	}
}
*/
/*void AllmoneyGun()
{
	for (int i = 0; i < 32; i++)
	{
		if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) {
			Player allplayers = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
			if (!(cstrcmp(PLAYER::GET_PLAYER_NAME(i), "-")))
			{
				if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) != PLAYER::PLAYER_PED_ID())
				{
					uint Weapons[]{ 0xAF3696A1, 0x476BF155, 0xB62D1F670, 0xDFE37640, 0xC1B3C3D1, 0x99B507EA, 0x678B81B1, 0x4E875F73, 0x958A4A8F, 0x440E4788, 0x84BD7BFD, 0x1B06D571, 0x5EF9FEC4, 0x22D8FE39, 0x99AEEB3B, 0x13532244, 0x2BE6766B, 0xEFE7E2DF, 0xBFEFFF6D, 0x83BF0278, 0xAF113F99, 0x9D07F764, 0x7FD62962, 0x1D073A89, 0x7846A318, 0xE284C527, 0x9D61E50F, 0x3656C8C1, 0x05FC3C11, 0x0C472FE2, 0x33058E22, 0xA284510B, 0x4DD2DC56, 0xB1CA77B1, 0x687652CE, 0x42BF8A85, 0x93E220BD, 0x2C3731D9, 0xFDBC8A50, 0x24B17070, 0x060EC506, 0x34A67B97, 0xFDBADCED, 0x23C9F95C, 0x497FACC3, 0xF9E6AA4B, 0x61012683, 0xC0A3098D, 0xD205520E, 0xBFD21232, 0x7F229F94, 0x92A27487, 0x083839C4, 0x7F7497E5, 0xA89CB99E, 0x3AABBBAA, 0xC734385A, 0x787F0BB, 0x47757124, 0xD04C944D, GAMEPLAY::GET_HASH_KEY("WEAPON_HATCHET"), GAMEPLAY::GET_HASH_KEY("WEAPON_RAILGUN") };
					for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
						WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(allplayers), Weapons[i], 9999, 1);
					}
				}
			}
		}
	}
}
*/
void AllmoneyGun()
{
	if (all_money_gun)
	{
		for (int i = 0; i < 32; i++)
		{
			if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) {
				Vector3 allshootcoords;
				Player allplayers = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
				Vector3 allplayerscoord = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), true);//Getting coords from all players in lobby
				if (!(cstrcmp(PLAYER::GET_PLAYER_NAME(i), "-")))
				{
					if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) != PLAYER::PLAYER_PED_ID())
					{
						if (hooks::HAS_MODEL_LOADEDD(PROP_MONEY_BAG_03))
						{
							if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::GET_ONLINE_PLAYER_ID(i), &allshootcoords))
							{
#define CREATE_A OBJECT::A_P_O_P // for surness // safe btw why do rename like alosmote all natives //ahh .....
								CREATE_A(PICKUP_MONEY_CASE, allshootcoords.x, allshootcoords.y, allshootcoords.z + 0.5, 0, 2500, PROP_MONEY_BAG_03, true, false);
								STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PROP_MONEY_BAG_03);
								TimePD5 = timeGetTime();
							}
						}
					}
				}
			}
		}
	}
}

void MoneyDropAll()
{
	if (money_all)
	{
		Online::DropCashLobby(selectedPlayer);
	}
	else
	{
		NULL;	
	}
}

void AllPlayerBoost()
{
	if (all_boost)
	{
		for (int i = 0; i < 33; i++)
		{
			if (PLAYER::IS_PLAYER_PRESSING_HORN(i))
			{
				Vehicle Veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(i), false);
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Veh);
				if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Veh))
				{
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(Veh, 100);
				}
			}
		}
	}
	else
	{
		NULL;
	}
}
bool GiveBoost = false;
void GiveHornBoost()
{
	int selectedOnlinePed = selectedPlayer;
	if (GiveBoost)
	{
		if (PLAYER::IS_PLAYER_PRESSING_HORN(selectedOnlinePed))
		{
			Vehicle Veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(selectedOnlinePed), false);
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Veh);
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Veh))
			{
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(Veh, 80);
			}
		}
	}
	else
	{
		NULL;
	}
}
//Creating the menu itself
// uff 

void SetTunable(int index, int value)
{
	int TunablesAddress = (*(int*)0x1E70374) + 4; //0x1E60274
	{
		if (TunablesAddress != 0)
		{
			int temp = TunablesAddress;
			temp += (index * 4);
			*(int*)temp = value;
		}
	}
}

void startKeyboard(int action, char* defaultText, int maxLength)
{
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(0, "FMMC_KEY_TIP8", "", defaultText, "", "", "", maxLength);
	keyboardAction = action;
	keyboardActive = true;
}

void CHANGE_WEATHER(char* WeatherName)
{
	GAMEPLAY::SET_WEATHER_TYPE_PERSIST(WeatherName);
	GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST(WeatherName);
	GAMEPLAY::SET_WEATHER_TYPE_NOW(WeatherName);
	GAMEPLAY::SET_OVERRIDE_WEATHER(WeatherName);
}

bool esp_all = false;
void esp(Player target)
{
	if (esp_all)
	{
		if (target != PLAYER::PLAYER_ID() && ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target)))
		{
			Vector3 entitylocation = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target), false);
			Vector3 top1world = { entitylocation.x + 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z + .8f, NULL };
			Vector3 top2world = { entitylocation.x - 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z + .8f, NULL };
			Vector3 top3world = { entitylocation.x + 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z + .8f, NULL };
			Vector3 top4world = { entitylocation.x - 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z + .8f, NULL };
			Vector3 bottom1world = { entitylocation.x + 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z - .8f, NULL };
			Vector3 bottom2world = { entitylocation.x - 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z - .8f, NULL };
			Vector3 bottom3world = { entitylocation.x + 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z - .8f, NULL };
			Vector3 bottom4world = { entitylocation.x - 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z - .8f, NULL };

			GRAPHICS::DRAW_LINE(top1world.x, top1world.y, top1world.z, top2world.x, top2world.y, top2world.z, 255, 0, 0, 255);
			GRAPHICS::DRAW_LINE(top2world.x, top2world.y, top2world.z, top4world.x, top4world.y, top4world.z, 255, 0, 0, 255);
			GRAPHICS::DRAW_LINE(top4world.x, top4world.y, top4world.z, top3world.x, top3world.y, top3world.z, 255, 0, 0, 255);
			GRAPHICS::DRAW_LINE(top1world.x, top1world.y, top1world.z, top3world.x, top3world.y, top3world.z, 255, 0, 0, 255);

			GRAPHICS::DRAW_LINE(bottom1world.x, bottom1world.y, bottom1world.z, bottom2world.x, bottom2world.y, bottom2world.z, 255, 0, 0, 255);
			GRAPHICS::DRAW_LINE(bottom2world.x, bottom2world.y, bottom2world.z, bottom4world.x, bottom4world.y, bottom4world.z, 255, 0, 0, 255);
			GRAPHICS::DRAW_LINE(bottom3world.x, bottom3world.y, bottom3world.z, bottom4world.x, bottom4world.y, bottom4world.z, 255, 0, 0, 255);
			GRAPHICS::DRAW_LINE(bottom3world.x, bottom3world.y, bottom3world.z, bottom1world.x, bottom1world.y, bottom1world.z, 255, 0, 0, 255);

			GRAPHICS::DRAW_LINE(top1world.x, top1world.y, top1world.z, bottom1world.x, bottom1world.y, bottom1world.z, 255, 0, 0, 255);
			GRAPHICS::DRAW_LINE(top2world.x, top2world.y, top2world.z, bottom2world.x, bottom2world.y, bottom2world.z, 255, 0, 0, 255);
			GRAPHICS::DRAW_LINE(top3world.x, top3world.y, top3world.z, bottom3world.x, bottom3world.y, bottom3world.z, 255, 0, 0, 255);
			GRAPHICS::DRAW_LINE(top4world.x, top4world.y, top4world.z, bottom4world.x, bottom4world.y, bottom4world.z, 255, 0, 0, 255);

			Vector3 locationOne = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target), false);
			Vector3 locationTwo = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			GRAPHICS::DRAW_LINE(locationOne.x, locationOne.y, locationOne.z, locationTwo.x, locationTwo.y, locationTwo.z, 255, 0, 0, 255);
		}
	}
}

#define PuttingMarker1 = PuttingMarker;
bool draw_marker = true;
void DrawSelectedMarker()
{
	if (draw_marker)
	{
		Vector3 playerMark = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true);
		GRAPHICS::DRAW_MARKER(2, playerMark.x, playerMark.y, playerMark.z + 2, playerMark.x, playerMark.y, playerMark.z, 0.0, 180.0, 0.0, 2.0, 2.0, 2.0, 255, 128, 0, 50, false, true, 2, 180, "MarkerTypeChevronUpx2", "MarkerTypeChevronUpx2", true);
	}
}
bool force_fie = false;
void Me::Force()
{
	if (force_fie)
	{
		godmode = true;//turns on godmode once forcfield is activated
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true);
		FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, 0x08, 640.00, 0, 1, 0);
	}
	else
	{
		NULL;
	}
}
bool veh_mode_god = false;
void godmodeveh()
{
	if (veh_mode_god)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(MyPedId, false))
		{
			Memory::set_value<bool>({ OFFSET_ENTITY_GOD }, 1);
		}
		else
		{
			Memory::set_value<bool>({ OFFSET_ENTITY_GOD }, 0);
		}
	}
}

bool off_map = false;

void OffRadar() 
{
	if (off_map)
	{
		Ped playerPed = PLAYER::PLAYER_ID();
		globalHandle(2423644 + 1 + PLAYER::PLAYER_ID() * 406 + 196).At(203).As<bool>() = true;
		globalHandle(2436641 + 70).At(69).As<int>() = NETWORK::GET_NETWORK_TIME() + 9999999999;
	}
	else
	{
		NULL;
	}
}

bool tiny_Player = false;

void TinyPlay()
{
	if (tiny_Player)
	{
		PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, true);
	}
	else
	{
		PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, false);
	}
}

bool mob_rad = false;

void MobileRadio()
{
	int station = AUDIO::GET_PLAYER_RADIO_STATION_INDEX();
	if (mob_rad)
	{
		AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(true);
		AUDIO::SET_MOBILE_PHONE_RADIO_STATE(1);
		AUDIO::SET_RADIO_TO_STATION_INDEX(station);
	}
	else
	{
		AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(false);
		AUDIO::SET_MOBILE_PHONE_RADIO_STATE(0);
	}
}

void teleport_to_marker(Player target)
{
	Vector3 coords = get_blip_marker();
	Entity e = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
	if (PED::IS_PED_IN_ANY_VEHICLE(e, 0))
	{
		e = PED::GET_VEHICLE_PED_IS_USING(e);
	}
	bool groundFound = false;
	static float groundCheckHeight[] =
	{ 100.0, 150.0, 50.0, 0.0, 0.3, 0.5, 1.0, 2.0, 3.0, 5.0, 10.0, 15.0, 20.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0 };
	for (int i = 0; i < sizeof(groundCheckHeight) / sizeof(float); i++)
	{
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, groundCheckHeight[i], 0, 0, 1);
		WAIT(100);
		if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheckHeight[i], &coords.z, 0))
		{
			groundFound = true;
			coords.z += 3.0;
			break;
		}
	}
	if (!groundFound)
	{
		coords.z = 5.0;
	}
	teleporttocoords(target, coords);
}

void exlosiveMalee()
{
	if (explosive_malee)
	{
		GAMEPLAY::SET_EXPLOSIVE_MELEE_THIS_FRAME(PLAYER::PLAYER_PED_ID());
	}
	else
	{
		NULL;
	}
}

Vector3 get_blip_markeeer()
{
	static Vector3 zero;
	Vector3 coords;

	bool blipFound = false;
	// search for marker blip
	int blipIterator = UI::_GET_BLIP_INFO_ID_ITERATOR();
	for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator))
	{
		if (UI::GET_BLIP_INFO_ID_TYPE(i) == 4)
		{
			coords = UI::GET_BLIP_INFO_ID_COORD(i);
			blipFound = true;
			break;
		}
	}
	if (blipFound)
	{
		return coords;
	}

	return zero;
}

//void teleport_to_markeeer()
//{
//	Vector3 coords = get_blip_markeeer();
//
//	if (coords.x == 0 && coords.y == 0)
//	{
//		//notifyMap("No Waypoint has been set!", 0);
//		return;
//	}
//
//	// get entity to teleport
//	Entity e = PLAYER::PLAYER_PED_ID();
//	if (PED::IS_PED_IN_ANY_VEHICLE(e, 0))
//	{
//		e = PED::GET_VEHICLE_PED_IS_USING(e);
//	}
//
//	// load needed map region and check height levels for ground existence
//	bool groundFound = false;
//	static float groundCheckHeight[] =
//	{ 100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0 };
//	for (int i = 0; i < sizeof(groundCheckHeight) / sizeof(float); i++)
//	{
//		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, groundCheckHeight[i], 0, 0, 1);
//		WAIT(100);
//		if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheckHeight[i], &coords.z, 0))
//		{
//			groundFound = true;
//			coords.z += 3.0;
//			break;
//		}
//	}
//	// if ground not found then set Z in air and give player a parachute
//	if (!groundFound)
//	{
//		coords.z = 1000.0;
//		WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
//	}
//	//do it
//	teleport_to_coords(e, coords);
//}

char* call1o;
char* call2o;
char* nameo;
Ped PTLoopPed;
bool looped_fx = false;
void Me::PTFXCALL(char* call1, char* call2, char* name)
{
	call1o = call1;
	call2o = call2;
	nameo = name;

	STREAMING::REQUEST_NAMED_PTFX_ASSET(call1);
	GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL(call2);
	GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY(name, PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
	if (looped_fx)
	{
		GRAPHICS::START_PARTICLE_FX_LOOPED_ON_ENTITY(name, PLAYER::PLAYER_PED_ID(), 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 1.0, false, false, false);
	}

}
bool clown2 = false;

void LoopFX()
{
	if (clown2)
	{
		Me::PTFXCALL("scr_rcbarry2", "scr_rcbarry2", "scr_clown_appears");
	}
	else
	{
		NULL;
	}
}

void RelodeLoop()
{
	Player OnlinePed = PLAYER::GET_PLAYER_PED(selectedPlayer);
	if (re_loop)
	{
		WEAPON::MAKE_PED_RELOAD(OnlinePed);
    }
	else
	{
		NULL;
	}
}

void RGB_GUN() {
	Ped playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer);
	static LPCSTR weaponNames[] = {
		"WEAPON_KNIFE", "WEAPON_NIGHTSTICK", "WEAPON_HAMMER", "WEAPON_BAT", "WEAPON_GOLFCLUB", "WEAPON_CROWBAR",
		"WEAPON_PISTOL", "WEAPON_COMBATPISTOL", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_MICROSMG", "WEAPON_SMG",
		"WEAPON_ASSAULTSMG", "WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_MG",
		"WEAPON_COMBATMG", "WEAPON_PUMPSHOTGUN", "WEAPON_SAWNOFFSHOTGUN", "WEAPON_ASSAULTSHOTGUN", "WEAPON_BULLPUPSHOTGUN",
		"WEAPON_STUNGUN", "WEAPON_SNIPERRIFLE", "WEAPON_HEAVYSNIPER", "WEAPON_GRENADELAUNCHER", "WEAPON_GRENADELAUNCHER_SMOKE",
		"WEAPON_RPG", "WEAPON_MINIGUN", "WEAPON_GRENADE", "WEAPON_STICKYBOMB", "WEAPON_SMOKEGRENADE", "WEAPON_BZGAS",
		"WEAPON_MOLOTOV", "WEAPON_FIREEXTINGUISHER", "WEAPON_PETROLCAN",
		"WEAPON_SNSPISTOL", "WEAPON_SPECIALCARBINE", "WEAPON_HEAVYPISTOL", "WEAPON_BULLPUPRIFLE", "WEAPON_HOMINGLAUNCHER",
		"WEAPON_PROXMINE", "WEAPON_SNOWBALL", "WEAPON_VINTAGEPISTOL", "WEAPON_DAGGER", "WEAPON_FIREWORK", "WEAPON_MUSKET",
		"WEAPON_MARKSMANRIFLE", "WEAPON_HEAVYSHOTGUN", "WEAPON_GUSENBERG", "WEAPON_HATCHET", "WEAPON_RAILGUN", "WEAPON_FLAREGUN",
		"WEAPON_KNUCKLE", "GADGET_NIGHTVISION", "GADGET_PARACHUTE", "WEAPON_MARKSMANPISTOL", "", ""
	};
	if (RgbGun)
	{
		for (int i = 0; i < sizeof(weaponNames) / sizeof(weaponNames[0]); i++)
		{
			if (WEAPON::HAS_PED_GOT_WEAPON(playerPed, GAMEPLAY::GET_HASH_KEY((char*)weaponNames[i]), 0))
			{
				WEAPON::SET_PED_WEAPON_TINT_INDEX(playerPed, GAMEPLAY::GET_HASH_KEY((char*)weaponNames[i]), rand() % 8);
			}
		}
	}
	else
	{
		NULL;
	}
}

void Features::teleporttocoords(Player player, Vector3 target)
{
	for (int iz = 0; iz < 2; iz++)
	{
		Ped destPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		Vector3 ourLoc = target;
		AI::CLEAR_PED_TASKS_IMMEDIATELY(destPed);
		int netScene = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE2(ourLoc.x, ourLoc.y, ourLoc.z, 0.f, 0.f, 0.f, 0, 0, 0, 0.f, 0.f, 0.f);
		NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(destPed, netScene, "amb@code_human_cower@female@base", "base", 8.f, -8.f, 2, 0, 100.f, 0);
		NETWORK::NETWORK_START_SYNCHRONISED_SCENE(netScene);
		WAIT(150);
		AI::CLEAR_PED_TASKS_IMMEDIATELY(destPed);
		NETWORK::NETWORK_STOP_SYNCHRONISED_SCENE(netScene);
	}
}

bool selecArrow = true;

void DisplayMarker()
{
	//Getting online player coords
	Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), false);
	//Drawing marker on those coords
	GRAPHICS::DRAW_MARKER(2, coords.x, coords.y, coords.z + 1.3f, 0, 0, 0, 0, 180, 0, 0.7, 0.7, 0.7, 4, 84, 61, 180, 1, 1, 1, 0, 0, 0, 0);
	GRAPHICS::DRAW_MARKER(27, coords.x, coords.y, coords.z + 1.0f, 0, 0, 0, 0, 0, 0, 0.7, 0.7, 0.7, 4, 84, 61, 0, 1, 1, 1, 0, 0, 0, 0);
}

//void tele_to_pointer()
//{
//	int WaypointHandle;
//	WaypointHandle = UI::GET_FIRST_BLIP_INFO_ID(8);
//	if (UI::DOES_BLIP_EXIST(WaypointHandle))
//	{
//		Vector3 Waypointpos = UI::GET_BLIP_COORDS(WaypointHandle);
//		//Waypointpos.z += 25.0f;
//		int Waypointpos2;
//		int Handle = PLAYER::PLAYER_PED_ID();
//		if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0))
//			Handle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
//		ENTITY::SET_ENTITY_COORDS(Handle, Waypointpos.x, Waypointpos.y, Waypointpos.z, 0, 0, 0, 1);
//	}
//}

bool lucky_loop = false;

void LuckyWheelLoop()
{
	if (lucky_loop)
	{
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_LUCKY_WHEEL_USAGE"), 0, 1);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_LUCKY_WHEEL_USAGE"), 0, 1);
	}
	else
	{
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_LUCKY_WHEEL_USAGE"), 1, 1);
		STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_LUCKY_WHEEL_USAGE"), 1, 1);
	}
}

void teleport_to_me()
{
	for (int iz = 0; iz < 2; iz++)
	{
		Ped SelectedPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer);
		int MyPos = PLAYER::PLAYER_PED_ID();
		Vector3 ourLoc = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(MyPos, 0.0, 0.0, 0.0);
		AI::CLEAR_PED_TASKS_IMMEDIATELY(SelectedPed);
		int netScene = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE2(ourLoc.x, ourLoc.y, ourLoc.z, 0.f, 0.f, 0.f, 0, 0, 0, 0.f, 0.f, 0.f);
		NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(SelectedPed, netScene, "amb@code_human_cower@female@base", "base", 8.f, -8.f, 2, 0, 100.f, 0);
		NETWORK::NETWORK_START_SYNCHRONISED_SCENE(netScene);
		WAIT(150);
		AI::CLEAR_PED_TASKS_IMMEDIATELY(SelectedPed);
		NETWORK::NETWORK_STOP_SYNCHRONISED_SCENE(netScene);
	}
}

bool vehGodBool = false;

bool RequestNetworkControl(int playerHandle, int carHandle)
{
	int Vehicle = PED::GET_VEHICLE_PED_IS_IN(playerHandle, 0);
	if (ENTITY::DOES_ENTITY_EXIST(carHandle) && ENTITY::IS_ENTITY_A_VEHICLE(carHandle))
	{
		if (NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(carHandle))
		{
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(carHandle))
			{
				return true;
			}
		}
	}
	return false;
}

void VehGod()
{
	int car = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);

	if (vehGodBool)
	{
		RequestNetworkControl(PLAYER::PLAYER_PED_ID(), car);

		if (RequestNetworkControl(PLAYER::PLAYER_PED_ID(), car))
		{
			ENTITY::SET_ENTITY_PROOFS(car, true, true, true, true, true, true, true, true);
			ENTITY::SET_ENTITY_INVINCIBLE(car, true);
			VEHICLE::SET_VEHICLE_STRONG(car, true);
		}
	}
	else
	{
		NULL;
	}
}

void UnlockEveryUn()
{
	notifyMap("Preparing Character...");
	WAIT(1500);
	notifyMap("Your unlocks will start in 4 sec...");
	WAIT(4000);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 0);

	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_2"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_3"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_4"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_5"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_6"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_7"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_8"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_9"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_10"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_11"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_12"), -1, 1);

	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_ENEMYDRIVEBYKILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_USJS_COMPLETED"), 50, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_USJS_FOUND"), 50, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DB_PLAYER_KILLS"), 1000, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_KILLS_PLAYERS"), 1000, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMHORDWAVESSURVIVE"), 21, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TDM_MVP"), 60, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_HOLD_UP_SHOPS"), 20, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_RACES_WON"), 101, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_NO_ARMWRESTLING_WINS"), 21, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMBBETWIN"), 50000, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 51, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_TOTALKILLS"), 500, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_DM_TOTAL_DEATHS"), 412, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_PLAYER_HEADSHOTS"), 623, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 63, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TDM_WINS"), 13, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_GTA_RACES_WON"), 12, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_GOLF_WON"), 2, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_TG_WON"), 2, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_RT_WON"), 2, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_CT_WON"), 2, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_GRAN_WON"), 2, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TENNIS_WON"), 2, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TENNIS_MATCHES_WON"), 2, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_WON"), 101, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_LOST"), 36, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_25_KILLS_STICKYBOMBS"), 50, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_50_KILLS_GRENADES"), 50, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS"), 50, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_AWD_20_KILLS_MELEE"), 50, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_MOLOTOV_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CMBTPISTOL_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_PISTOL50_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_APPISTOL_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_MICROSMG_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_SMG_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ASLTSMG_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ASLTRIFLE_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CRBNRIFLE_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ADVRIFLE_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_MG_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CMBTMG_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ASLTMG_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_PUMP_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_SAWNOFF_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_BULLPUP_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ASLTSHTGN_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_SNIPERRFL_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_HVYSNIPER_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_GRNLAUNCH_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_RPG_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_MINIGUNS_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_SMKGRENADE_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_STKYBMB_ENEMY_KILLS"), 600, 0);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_MOLOTOV_ENEMY_KILLS"), 600, 0);

	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_7"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_2"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_3"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_4"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_5"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_6"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_7"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_2"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_3"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_4"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_5"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_6"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_7"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_2"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_3"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_4"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_5"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_6"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_7"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_2"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_3"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_4"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_5"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_6"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_7"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_2"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_3"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_4"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_5"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_6"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_7"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_8"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_9"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_10"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_OUTFIT"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_2"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_3"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_4"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_5"), -1, 1);;
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_6"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_7"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_2"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_3"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_4"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_5"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_6"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_7"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_2"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_3"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_4"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_5"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_6"), -1, 1);;
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_7"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_2"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_3"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_4"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_5"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_6"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_7"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_2"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_3"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_4"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_5"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_6"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_7"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_2"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_3"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_4"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_5"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_6"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_7"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_8"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_9"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_10"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_OUTFIT"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TORSO"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_2"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_3"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_4"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_5"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_6"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_7"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL2"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL2_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_DECL"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH_2"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TORSO"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_2"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_3"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_4"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_5"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_6"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_7"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL2"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL2_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_DECL"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH_2"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_0"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_2"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_3"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_4"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_5"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_6"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_7"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_8"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_9"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_10"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_11"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_12"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_13"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_14"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_15"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_16"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_17"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_18"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_19"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_21"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_22"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_23"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_24"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_24"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_25"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_26"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_27"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_28"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_29"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_30"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_31"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_32"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_33"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_34"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_35"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_36"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_37"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_38"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_39"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_40"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_2"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_3"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_4"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_5"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_6"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_7"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_8"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_9"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_12"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_13"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
	Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_12"), -1, 1);
}

bool CheckFriendStatus(Player player, bool result)
{
	int NETWORK_HANDLE[76];
	NETWORK::NETWORK_HANDLE_FROM_PLAYER_UPD(player, &NETWORK_HANDLE[0], 13);
	if (NETWORK::NETWORK_IS_HANDLE_VALID(&NETWORK_HANDLE[0], 13))
	{
		result = NETWORK::NETWORK_IS_FRIEND(&NETWORK_HANDLE[0]);
		return true;
	}
	return false;
}

void PoliceIgnore()
{
	if (police_igga)
	{
		PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_PED_ID(), true);
	}
	else
	{
		PLAYER::SET_POLICE_IGNORE_PLAYER(PLAYER::PLAYER_PED_ID(), false);
	}
}

void SetMoneyAmmont()
{
	//Create variables for easy access later on
	Ped onlinePed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer);
	int MoneyAmmount = 50000;

    PED::S_P_M_A(onlinePed, MoneyAmmount);
}

void NonTargetMe()
{
	Ped MyPed = PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID());
	if (NontArget)
	{
        PED::SET_PED_CAN_BE_TARGETTED(MyPed, false);
	}
	else
	{
		PED::SET_PED_CAN_BE_TARGETTED(MyPed, true);
	}
}

void WaterTime()
{
	if (under_wt_time)
	{
		Ped Localplayer = PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID());
		float watertime = 1000;
		PED::SET_PED_MAX_TIME_IN_WATER(Localplayer, 1000);
	}
	else
	{
		NULL;
	}
}
//Creating custom loading text
void CustomText()
{
	//g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_JOINING"), "Isn't " BIGBASE_NAME " the fucking best?");
	//g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_TRANSP"), "Isn't " BIGBASE_NAME " the fucking best?");
}
//Menu starts here - Don't under here
bool sck = false;
void sUCK()
{
	if (sck)
	{
		STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MPx_ARCADE_PAY_TIME_LEFT"), -1, true);
		STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_ARCADE_PAY_TIME_LEFT"), -1, true);
		STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP1_ARCADE_PAY_TIME_LEFT"), -1, true);

		globalHandle(262145 + 28369).As<bool>() = true;
		globalHandle(262145 + 28369).As<bool>() = 200000;
		globalHandle(262145 + 28369).As<int>() = true;
		globalHandle(262145 + 28369).As<int>() = 200000;
	}
	else
	{
		NULL;
	}
}
//Menu Info Logins!

//Usernames
char* Usernames[] =
{
	//user 1
	"nitedev",
	//user 2
	"admin",
	//user 3
	"adad"
};
//Passwords
char* Passwords[] =
{
	//user 1
	"data",
	//user 2
	"admin",
	//user 3
	"ad"
};
//User 1 - adad
char* username1 = "OwnerNovus";
char* userkey1 = "RTX2080";
//User 2 - Admin
char* username2 = "Admin";
char* userkey2 = "CURENT-ADM1N";
//User 3 - NiteDev
char* username3 = "NiteDev";
char* userkey3 = "AGT7-RTX3-14XS-F01Y"; //this is a local example yh i understand i have that too wait i show u
//User 4 - TEST
char* username4 = "TEST";
char* userkey4 = "TEST";
//User 4 - MarioMods01
char* username5 = "MarioMods01";
char* userkey5= "E0d85943017cc35ic";

void check_auth()
{
	//Other strings - Random

	std::string injectorType = "~g~MyInjector0102230.exe";
	std::string MenuVer = "~b~1.0.0";
	std::string ServerStat = "~g~Running...";
	std::string WebsiteLink = "https://www.Novusmenu.com";

	//Bools

	bool check_user;

	//If statement and while loops

		//Check username----------------------------------------

		GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, "", "", "", "", "", "", 20);
		notifyBottom("Please enter your Username:");
		while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == false) WAIT(0);
		std::string userName = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();

		//Check password----------------------------------------

		GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, "", "", "", "", "", "", 20);
		notifyBottom("Please enter your Licens Key:");
		while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == false) WAIT(0);
		std::string userPass = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();

		//Add one if statement per user

		//-----------------------USER 1-----------------------------------------

		if (userName == username1 && userPass == userkey1) //User 1
		{
			//Disable button till time loads out

			CONTROLS::DISABLE_CONTROL_ACTION(VK_F8, VK_F8, true);

			//Show messenges if success

			notifyleft2("Welcome To Novus Menu", "Novus", "V-1.0.0"); //Message, title, subtitle - notifyleft2
			notifyleft2("Setting up menu! Wait...", "Novus", "SETUP"); //Message, title, subtitle - notifyleft2
			WAIT(4000);//Wait 4 secons to load
			CONTROLS::ENABLE_CONTROL_ACTION(VK_F8, VK_F8, true); //Enable open button if username and key is correct
			notifyleft2("Open menu with F8", "Novus", "CONTROLS"); //Message, title, subtitle - notifyleft2
			NULL;
		}

		if (userName == username2 && userPass == userkey2) //User 2
		{
			//Disable button till time loads out

			CONTROLS::DISABLE_CONTROL_ACTION(VK_F8, VK_F8, true);

			//Show messenges if success

			notifyleft2("Welcome To Novus Menu", "Novus", "V-1.0.0"); //Message, title, subtitle - notifyleft2
			notifyleft2("Setting up menu! Wait...", "Novus", "SETUP"); //Message, title, subtitle - notifyleft2
			WAIT(4000);//Wait 4 secons to load
			CONTROLS::ENABLE_CONTROL_ACTION(VK_F8, VK_F8, true); //Enable open button if username and key is correct
			notifyleft2("Open menu with F8", "Novus", "CONTROLS"); //Message, title, subtitle - notifyleft2
			NULL;
		}

		if (userName == username3 && userPass == userkey3) //User 3
		{
			//Disable button till time loads out

			CONTROLS::DISABLE_CONTROL_ACTION(VK_F8, VK_F8, true);

			//Show messenges if success

			notifyleft2("Welcome To Novus Menu", "Novus", "V-1.0.0"); //Message, title, subtitle - notifyleft2
			notifyleft2("Setting up menu! Wait...", "Novus", "SETUP"); //Message, title, subtitle - notifyleft2
			WAIT(4000);//Wait 4 secons to load
			CONTROLS::ENABLE_CONTROL_ACTION(VK_F8, VK_F8, true); //Enable open button if username and key is correct
			notifyleft2("Open menu with F8", "Novus", "CONTROLS"); //Message, title, subtitle - notifyleft2

		}
		if (userName == username4 && userPass == userkey4) //User 3
		{
			//Disable button till time loads out

			CONTROLS::DISABLE_CONTROL_ACTION(VK_F8, VK_F8, true);

			//Show messenges if success

			notifyleft2("Welcome To Novus Menu", "Novus", "V-1.0.0"); //Message, title, subtitle - notifyleft2
			notifyleft2("Setting up menu! Wait...", "Novus", "SETUP"); //Message, title, subtitle - notifyleft2
			WAIT(4000);//Wait 4 secons to load
			CONTROLS::ENABLE_CONTROL_ACTION(VK_F8, VK_F8, true); //Enable open button if username and key is correct
			notifyleft2("Open menu with F8", "Novus", "CONTROLS"); //Message, title, subtitle - notifyleft2

		}
		/*-----------------------USER 2-----------------------------------------

		else if (userName == username2 && userPass == userkey2) //User 2
		{
			//Disable button till time loads out

			CONTROLS::DISABLE_CONTROL_ACTION(VK_F8, VK_F8, true);

			//Show messenges if success

			notifyleft2("Welcome To Novus Menu", "Novus", "V-1.0.0"); //Message, title, subtitle - notifyleft2
			notifyleft2("Setting up menu! Wait...", "Novus", "SETUP"); //Message, title, subtitle - notifyleft2
			WAIT(4000);
			CONTROLS::ENABLE_CONTROL_ACTION(VK_F8, VK_F8, true); //Enable open button if username and key is correct
			notifyleft2("Open menu with F8", "Novus", "CONTROLS"); //Message, title, subtitle - notifyleft2
			NULL;
		}

		//-----------------------USER 3-----------------------------------------

		else if (userName == username3 && userPass == userkey3) //User 3
		{
			//Disable button till time loads out

			CONTROLS::DISABLE_CONTROL_ACTION(VK_F8, VK_F8, true);

			//Show messenges if success

			notifyleft2("Welcome To Novus Menu", "Novus", "V-1.0.0"); //Message, title, subtitle - notifyleft2
			notifyleft2("Setting up menu! Wait...", "Novus", "SETUP"); //Message, title, subtitle - notifyleft2
			WAIT(4000);
			CONTROLS::ENABLE_CONTROL_ACTION(VK_F8, VK_F8, true); //Enable open button if username and key is correct
			notifyleft2("Open menu with F8", "Novus", "CONTROLS"); //Message, title, subtitle - notifyleft2
			NULL;
		}

		//-----------------------USER 4-----------------------------------------

		else if (userName == username3 && userPass == userkey3) //User 3
		{
			//Disable button till time loads out

			CONTROLS::DISABLE_CONTROL_ACTION(VK_F8, VK_F8, true);

			//Show messenges if success

			notifyleft2("Welcome To Novus Menu", "Novus", "V-1.0.0"); //Message, title, subtitle - notifyleft2
			notifyleft2("Setting up menu! Wait...", "Novus", "SETUP"); //Message, title, subtitle - notifyleft2
			WAIT(4000);
			CONTROLS::ENABLE_CONTROL_ACTION(VK_F8, VK_F8, true); //Enable open button if username and key is correct
			notifyleft2("Open menu with F8", "Novus", "CONTROLS"); //Message, title, subtitle - notifyleft2
			NULL;
		}

		//If details is wrong --------- Start here LOL - XD*/

		else
		{
			bool LoopedRestart = true;
			//Disable open button if username and key is wrong

				CONTROLS::DISABLE_CONTROL_ACTION(VK_F8, VK_F8, true);

				//Show error message

				notifyleft2("Username or Key was wrong! GTA will be exited in 5 sec...", "Novus", "~r~ERROR:"); //Message, title, subtitle - notifyleft2
				notifyleft2("https://www.Novusmenu.com", "Novus", "Purchase at:"); //Message, title, subtitle - notifyleft2

				//Wait 5 sec to load up login again

				NULL;
				WAIT(5000);
				exit(0);
			}
	}

void DrawWelcome(char* fmt, ...)
{
	//Create some stuff
	RGBA WelcomeRectColor = { 7, 84, 61, 170 };
	float WelcomeRectX = 0.0f;
	float WelcomeRectY = 0.9f;
	float WelcomeRectWidth = 1.1f;
	float WelcomeRectHeight = 0.065f;
		char buf[2048] = { 0 };
		va_list va_alist;

		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);

		char buff2[2048] = { 0 };
		sprintf_s(buff2, "%s", buf);

		UI::BEGIN_TEXT_COMMAND_PRINT("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
		UI::END_TEXT_COMMAND_PRINT(4000, 1);
		Menu::Drawing::Rect(WelcomeRectColor, { WelcomeRectX, WelcomeRectY }, { WelcomeRectWidth, WelcomeRectHeight });
}	
void DrawWelcome(std::string str) 
{ 
	DrawWelcome(&str[0]); 
}
bool IP_Spoof = false;
void IPSpoof() 
{
	if (IP_Spoof)
	{
		*(byte*)0xC21AC5CC = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(100, 1000);
		*(byte*)(0xC21AC5CC + 0x01) = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(100, 800);
		*(byte*)(0xC21AC5CC + 0x02) = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(100, 500);
		*(byte*)(0xC21AC5CC + 0x03) = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(100, 1500);
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(PLAYER::PLAYER_ID())) 
		{
			char* Address = PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID());
			*(UINT8*)(Address - 0x48) = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(100, 1000);
			*(UINT8*)(Address - 0x47) = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(100, 800);
			*(UINT8*)(Address - 0x46) = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(100, 500);
			*(UINT8*)(Address - 0x45) = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(100, 1500);
		}
	}
}

bool noAFKme = false;

void AntiAFK()
{
	if (noAFKme)
	{
		globalHandle(0x40001).At(0x56).As<int>() = INT_MAX;
		globalHandle(0x40001).At(0x57).As<int>() = INT_MAX;
		globalHandle(0x40001).At(0x58).As<int>() = INT_MAX;
		globalHandle(0x40001).At(0x59).As<int>() = INT_MAX;
	}
}

bool OffRadarOnMe = false;
void MeOffRadar()
{
	if (OffRadarOnMe)
	{
		globalHandle(2424073).At(PLAYER::PLAYER_ID(), 421).At(200).As<int>() = 1;
		globalHandle(2437549).At(70).As<int>() = NETWORK::GET_NETWORK_TIME();
	}
	else
	{
		globalHandle(2424047).At(PLAYER::PLAYER_ID(), 416).At(200).As<int>() = 0;
	}
}

void setupdraw(bool outline)
{
	UI::SET_TEXT_FONT(1);
	UI::SET_TEXT_SCALE(0.4f, 0.4f);
	UI::SET_TEXT_COLOUR(255, 255, 255, 255);
	UI::SET_TEXT_WRAP(0.0f, 1.0f);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	if (outline)
	{
		UI::SET_TEXT_OUTLINE();
	}
}

void drawstring(char* text, float X, float Y)
{
	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(X, Y);
}

bool showMyFPS = false;

void DisplayFPS()
{
	if (showMyFPS)
	{
		float LastFrameTime = GAMEPLAY::GET_FRAME_TIME();
		int getFPS = (1.0f / LastFrameTime);
		char FPStext[60];
		snprintf(FPStext, sizeof(FPStext), "FPS: ~b~ %d", getFPS);
		setupdraw(true);
		UI::SET_TEXT_FONT(6);
		UI::SET_TEXT_SCALE(0.5f, 0.5f);
		UI::SET_TEXT_COLOUR(255, 255, 255, 255);
		UI::SET_TEXT_CENTRE(0);
		drawstring(FPStext, 0.020f, 0.010f);
	}
}

bool showMyCoords = false;
void DisplayCOORDS()
{
	if (showMyCoords)
	{
		Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(MyPedId, false);
		char COORDStext[60];
		snprintf(COORDStext, sizeof(COORDStext), "COORDS: ~b~ %d", MyCoords);
		setupdraw(true);
		UI::SET_TEXT_FONT(6);
		UI::SET_TEXT_SCALE(0.5f, 0.5f);
		UI::SET_TEXT_COLOUR(255, 255, 255, 255);
		UI::SET_TEXT_CENTRE(0);
		drawstring(COORDStext, 0.020f, 0.010f);
	}
}

bool dis_map = true;

void Dismap()
{
	if (dis_map)
	{
		UI::DISPLAY_RADAR(true);
	}
	else
	{
		UI::DISPLAY_RADAR(false);
	}
}

bool time_view = false;

void DisplayTime()
{
	if (time_view)
	{
		// declaring argument of time() 
		time_t my_time = time(NULL);
		char TIME[100];
		const char* discTime = "~g~Curent Time And Date:";
		float TimeX = 0.27f;
		float TimeY = 0.8f;
		float TimeY2 = 0.83f;
		float RectX = 0.27f;
		float RectY = 0.83f;
		//Lines - Border [FLOATS]
		float LineHeight = 0.002f;
		float LineWidth1 = 0.15f;
		float TopLineX = 0.27f;
		float TopLineY = 0.795f;
		//Line 2
		float BottomLineX = 0.27f;
		float BottomLineY = 0.795f + 0.035f * 2;
		float  RectWidth = 0.15f;
		float  RectHeight = 0.035f * 2;
		RGBA RectColor = { 0,0,0,150 };
		RGBA BorderColor = { 7, 84, 61,200 };
		// ctime() used to give the present time and date
		//Draw Border
		Menu::Drawing::Rect(BorderColor, { TopLineX, TopLineY }, { LineWidth1, LineHeight }); //TOP
		Menu::Drawing::Rect(BorderColor, { BottomLineX, BottomLineY }, { LineWidth1, LineHeight }); //BOTTOM
		//Draw background
		Menu::Drawing::Rect(RectColor, { RectX, RectY }, { RectWidth, RectHeight });
		//Draw time and date
		sprintf(TIME, "%s", ctime(&my_time));
		Menu::Drawing::Text(discTime, { 255, 255, 255, 255 }, { TimeX, TimeY }, { 0.32f, 0.32f }, true);
		Menu::Drawing::Text(TIME, { 255, 255, 255, 255 }, { TimeX, TimeY2 }, { 0.25f, 0.25f }, true);
		//notifyMap(TIME);
	}
	else
	{
		NULL;
	}
}

bool display_login = false;

void DrawLogin()
{
	float LoginX = 0.5f;
	float LoginY = 0.5f;
	float LoginWidth = 0.3f;
	float LoginHeight = 0.3f;
	float TextX = 0.5f;
	float TextY = 0.50f;
	RGBA LoginColor = { 0,0,0,240 };
	if (display_login)
	{
		UI::_SHOW_CURSOR_THIS_FRAME();
		Menu::Drawing::Text("LOGIN", { 255, 255, 255, 255 }, { TextX, TextY }, { 0.40f, 0.40f }, true);
		if (Menu::LoginTab1(""))
		{
			string curentuser = CharKeyboardUser("", 21, ""); //Use username keyboard!! __--__
		}
		Menu::Drawing::Rect(LoginColor, { LoginX , LoginY }, { LoginWidth , LoginHeight });
	}
}

bool dis_data = false;


bool CrashPlayerNow = false;

void SimpleCrash()
{
	//creating variables
	Vector3 PlayerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_ONLINE_PLAYER_ID(selectedPlayer), false);
	Ped OnlinePed = PLAYER::GET_PLAYER_PED(selectedPlayer);
	int ScriptedPlayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer);
	Vector3 CrashCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ScriptedPlayer, 0.0, 5.0, 0.0);
	float ShakeSize = 1000.f;
	bool ExplodePlayer = false;
	bool SpawnLoop = false;
	bool FuckCamLoop = false;

	if (CrashPlayerNow)
	{

		ExplodePlayer = true;
		SpawnLoop = true;
		FuckCamLoop = true;

		if (ExplodePlayer)
		{
			FIRE::E_P_X(PlayerCoords.x, PlayerCoords.y, PlayerCoords.z, 0, 1000.f, true, false, ShakeSize); //1
			FIRE::E_P_X(PlayerCoords.x, PlayerCoords.y, PlayerCoords.z, 0, 1000.f, true, false, ShakeSize); //1
		}

		if (SpawnLoop) //Spawn Blimp in a loop
		{
			Online::SpawnVehicleToPlayer("Blimp2", CrashCoords, 0, 0.0f); //1
			Online::SpawnVehicleToPlayer("Blimp2", CrashCoords, 0, 0.0f); //2
		}

		if (FuckCamLoop)
		{
			FIRE::E_P_X(PlayerCoords.x, PlayerCoords.y, PlayerCoords.z, 4, 0.f, false, true, ShakeSize); //1
			FIRE::E_P_X(PlayerCoords.x, PlayerCoords.y, PlayerCoords.z, 4, 0.f, false, true, ShakeSize); //2
		}

	}
	//Online::SpawnVehicleToPlayer()

}

bool SVT::CrashHelp(int args, int test) 
{
	return (((int(*)(int, int))0x82918F38)(selectedPlayer, 1) == test);
}

int Crashint;
void crash_steps() 
{
	if (Crashint == 0) {
		SVT::v2(selectedPlayer);

	}
	if (Crashint == 1) {
		SVT::v3(selectedPlayer);

	}
	if (Crashint == 2) {
		SVT::v4(selectedPlayer);

	}
	if (Crashint == 3) {
		SVT::v5(selectedPlayer);

	}
	if (Crashint == 4) {
		SVT::v6(selectedPlayer);

		if (Crashint == 5) {
			SVT::v7(selectedPlayer);

		}
		if (Crashint == 6) {
			SVT::v8(selectedPlayer);

		}
		if (Crashint == 7) {
			SVT::v9(selectedPlayer);

		}
		if (Crashint == 8) {
			SVT::v10(selectedPlayer);

		}
		if (Crashint == 9) {
			SVT::v11(selectedPlayer);

		}

	}
}

//Create Simple Portable LSC
int Amorr = 0;
int Enginee = 0;
int Brake = 0;
int Spoilerr = 0;
int Skirtt = 0;
int Suspensionn = 0;
int Transmission = 0;
int Bumperr = 0;
int Bumper2 = 0;
int Exhaust = 0;
int Bonnet = 0;
int Rollcage = 0;
int Klaxonn = 0;

void LSC(int LSCType, int LSCIndex)
{
	int vehid = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
	VEHICLE::SET_VEHICLE_MOD_KIT(vehid, 0);
	VEHICLE::SET_VEHICLE_MOD(vehid, LSCType, LSCIndex, 0);
}

//Some new veh options in here yet also some player (me)
namespace NewOption
{
	bool speedo_draw = false;
	bool DriftMod = false;
	bool speedo_plate = false;
	bool Vehicle_Gravity = false;
	bool Invisible_vehicle = false;
	bool Supergrip = false;
	bool NightLookOnMe = false;
	bool thermal_vision = false;
	bool IDKReally = false;
	bool NitrousEffect = false;
	bool NitrousExhaust = false;
	bool water_drive = false;
	int AirHeigt, FerrisWheele;
	bool FuelModeToggle = 0,
		DISABLE_PHONE = 0,
		walkingmario = 0,
		LightMeUp = 0,
		LightMeUp_Disco = 0;
	bool Spanlllll = false;
	bool MeinCode = false;
	bool Zusatz = false;
	bool dis_my_phone = false;
	bool key_drift = false;
	//Void's
	void DrawSpeedometer()
	{
		if (speedo_draw)
		{
			{
				char Buffer[2][256]; float Speed = 0.0f, MetersPerSecond = 0.0f;
				float speedoXfloat = 0.850993, speedoYvalue = 0.855998, speedoXfloatgrad = 0.850993, speedoYvaluegrad = 0.871998, widthgrad = 0.11f, heightgrad = 0.055000f;
				int VehicleEnt = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				if (ENTITY::DOES_ENTITY_EXIST(VehicleEnt) && ENTITY::IS_ENTITY_A_VEHICLE(VehicleEnt))
				{
					MetersPerSecond = ENTITY::GET_ENTITY_SPEED(VehicleEnt);
					Speed = MetersPerSecond * 2.236936; sprintf(Buffer[1], "MP/H");
					sprintf(Buffer[0], "%.1f ", Speed);
					strcat(Buffer[0], Buffer[1]);
					Menu::Drawing::Text(Buffer[0], { 255, 255, 255, 255 }, { speedoXfloat, speedoYvalue }, { 0.40f, 0.40f }, true);
					Menu::Drawing::Spriter("Plate", "Plate", speedoXfloatgrad, speedoYvaluegrad, widthgrad, heightgrad, 0.0f, 7, 84, 61, 255);
				}
			}
		}
	}

	void VehDriftMode()
	{
		if (DriftMod)
		{
			VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), true);
		}
		else
		{
			VEHICLE::SET_VEHICLE_REDUCE_GRIP(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), false);
		}
	}

	void HotKeyDrift()
	{
		Player MyPed = PLAYER::PLAYER_PED_ID();
		Hash MyVeh = PED::GET_VEHICLE_PED_IS_IN(MyPed, FALSE);
		if (key_drift)
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE))
			{
				//If user press VK_LSHIFT do this
				if (IsKeyPressed(VK_LSHIFT))
				{
						VEHICLE::SET_VEHICLE_REDUCE_GRIP(MyVeh, true);
				}
				else
				{
						VEHICLE::SET_VEHICLE_REDUCE_GRIP(MyVeh, false);
				}
			}
			else
			{
				key_drift = false;
				notifyMap("~r~ERROR: ~w~You must be in an VEHICLE to use this feature");
			}
		}
	}

	char* FtoS(float input)
	{
		char returnvalue[64];
		int wholenumber = (int)input;
		input -= wholenumber;
		input *= 100;
		sprintf(returnvalue, "%d.%d", wholenumber, (int)input);
		return returnvalue;
	}

	void SpeedPlate()
	{
		int myvehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);

		if (speedo_plate)
		{
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(myvehicle, FtoS(ENTITY::GET_ENTITY_SPEED(myvehicle)));
		}
		else
		{
			NULL;
		}
	}

	void vehGravity()
	{
		int vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

		if (Vehicle_Gravity)
		{
			VEHICLE::SET_VEHICLE_GRAVITY(vehicle, false);
		}
		else
		{
			VEHICLE::SET_VEHICLE_GRAVITY(vehicle, true);
		}
	}

	void NoSeeVeh()
	{
		Vehicle myvehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);

		if (Invisible_vehicle)
		{
			ENTITY::SET_ENTITY_VISIBLE1(myvehicle, false);
		}
		else
		{
			ENTITY::SET_ENTITY_VISIBLE1(myvehicle, true);
		}
	}

	void NightVision()
	{
		if(NightLookOnMe)
		{
			GRAPHICS::SET_NIGHTVISION(1);
		}
		else
		{
			GRAPHICS::SET_NIGHTVISION(0);
		}
	}

	void TermalVis()
	{
		if (thermal_vision)
		{
			GRAPHICS::SET_SEETHROUGH(1);
		}
		else
		{
			GRAPHICS::SET_SEETHROUGH(0);
		}
	}

	void IDKwhatISthis()
	{
		if (IDKReally)
		{
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), PED_FLAG_SHRINK, 1);
		}
		else
		{
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), PED_FLAG_SHRINK, 0);
		}
	}

	bool SpawnWheel()
	{
		int ObjectName = GAMEPLAY::GET_HASH_KEY("prop_ld_ferris_wheel");
		if (STREAMING::IS_MODEL_IN_CDIMAGE(ObjectName))
		{
			if (STREAMING::IS_MODEL_VALID(ObjectName))
			{
				hooks::REQUEST_MODELL(ObjectName);
				Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				if (hooks::HAS_MODEL_LOADEDD(ObjectName))
				{
					FerrisWheele = OBJECT::CREATE_OBJECT(ObjectName, coords.x, coords.y, coords.z, 1, 0, 1);
					if (ENTITY::DOES_ENTITY_EXIST(FerrisWheele))
					{
						Vector3 Me = ENTITY::GET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
						ENTITY::SET_ENTITY_COORDS(FerrisWheele, Me.x, Me.y, AirHeigt, 1, 0, 0, 1);
						ENTITY::SET_ENTITY_ROTATION(FerrisWheele, 180, 90, 180, 2, 1);
						ENTITY::SET_ENTITY_VISIBLE1(FerrisWheele, false);
						ENTITY::SET_ENTITY_ALPHA(FerrisWheele, 0, 0);
						ENTITY::FREEZE_ENTITY_POSITION(FerrisWheele, true);
						if (!water_drive)
							ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), Me.x, Me.y, AirHeigt + 2, 1, 0, 0, 1);
						Zusatz = true;
						return true;
					}
					else return false;
				}
				else return false;
			}
		}
		return 0;
	}

	void DeleteEntity(int Handle)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Handle);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Handle, 1, 1);
		ENTITY::DELETE_ENTITY(&Handle);
	}

	void DriveWater()
	{
		if (water_drive)
		{
			water_drive = true;
			AirHeigt = -1.6;
			Spanlllll = true;
			MeinCode = false;
		}
		else
		{
			water_drive = false;
			Zusatz = false;
			DeleteEntity(FerrisWheele);
		}
	}

	void DriveAir()
	{
		if (MeinCode)
		{
			AirHeigt = 360;
			MeinCode = true;
			Spanlllll = true;
			water_drive = false;
		}
		else
		{
			MeinCode = false;
			Zusatz = false;
			DeleteEntity(FerrisWheele);
		}
	}

	void WalkOnTheWalls()
	{
		if (walkingmario)
		{
			wall_walking();
		}
	}

	void Zusatz123321()
	{
		if (Zusatz) 
		{
			if (ENTITY::DOES_ENTITY_EXIST(FerrisWheele)) 
			{
				Vector3 po;
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
					po = ENTITY::GET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 1);
				else
					po = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				if (water_drive)
				{
					AirHeigt = -1, 2;
					ENTITY::SET_ENTITY_COORDS(FerrisWheele, po.x, po.y, AirHeigt, 1, 0, 0, 1);
				}
				else {
					AirHeigt = 360;
					ENTITY::SET_ENTITY_COORDS(FerrisWheele, po.x, po.y, AirHeigt, 1, 0, 0, 1);
				}
				ENTITY::SET_ENTITY_ROTATION(FerrisWheele, 180, 90, 180, 2, 1);
				ENTITY::SET_ENTITY_VISIBLE1(FerrisWheele, false);
				ENTITY::SET_ENTITY_ALPHA(FerrisWheele, 0, 0);
			}
		}
		if (Spanlllll) {
			if (SpawnWheel() == true) { Spanlllll = false; }
		}
	}

	void NoPhone()
	{
		if (dis_my_phone)
		{
			UI::HIDE_HELP_TEXT_THIS_FRAME();
			CONTROLS::SET_INPUT_EXCLUSIVE(2, 176);
			CONTROLS::SET_INPUT_EXCLUSIVE(2, 161);
			CONTROLS::SET_INPUT_EXCLUSIVE(2, 165);
			CONTROLS::SET_INPUT_EXCLUSIVE(2, 163);
			CONTROLS::SET_INPUT_EXCLUSIVE(2, 164);
			CONTROLS::SET_INPUT_EXCLUSIVE(2, 193);
			CONTROLS::SET_INPUT_EXCLUSIVE(2, 194);
			CONTROLS::SET_INPUT_EXCLUSIVE(2, 195);
			CONTROLS::SET_INPUT_EXCLUSIVE(0, 195);
			CONTROLS::SET_INPUT_EXCLUSIVE(2, 203);
		}
	}

	bool VehicleNitrous = false;

	void NitroEffect()
	{
		char* Exhausts[] = 
		{ 
			"exhaust", 
			"exhaust_2", 
			"exhaust_3", 
			"exhaust_4",
			"exhaust_5",
			"exhaust_6",
			"exhaust_7" 
		};
		if (VehicleNitrous) 
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
				notifyMap("Press ~INPUT_VEH_HORN~ to use NOS.");
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				CONTROLS::SET_INPUT_EXCLUSIVE(0, 79);
				if (CONTROLS::IS_CONTROL_PRESSED(0, 79))
				{
					AUDIO::SET_VEHICLE_BOOST_ACTIVE(veh, 1);
					if (NitrousEffect)
					{
						GRAPHICS::_START_SCREEN_EFFECT("RaceTurbo", 0, 0);
					}
					ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), true, 0, 2.0, 0, 0, 0, 0, true, true, true, true, false, true);
					AUDIO::SET_VEHICLE_BOOST_ACTIVE(veh, 0);
					if (NitrousExhaust) {
						STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_carsteal4");
						if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_carsteal4"))
						{
							Vector3 min, max;
							GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(veh), &min, &max);
							float direction = ENTITY::GET_ENTITY_HEADING(veh);
							for (int i = 0; i < sizeof(Exhausts) / sizeof(Exhausts[0]); i++)
							{
								Vector3 offset = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(veh, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(veh, (char*)Exhausts[i]));
								GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL("scr_carsteal4");
								GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_carsteal5_car_muzzle_flash", offset.x, offset.y, offset.z, 0.0f, 0.0f, direction - 90.0f, 0.5f, 0, 0, 0);
							}
						}
					}
				}
			}
		}
	}

	void DiscoMan()
	{
		if (LightMeUp_Disco)
		{
			Vector3 cooords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
			GRAPHICS::DRAW_LIGHT_WITH_RANGE(cooords.x, cooords.y, cooords.z, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), 25.0f, 100.0f);
		}
	}

	void InfiLoading()
	{
			DWORD64 args[9] = { -125347541, selectedPlayer, 0, -1, 1, 0, 0,0,0 }; //Custom
			TriggerScriptEvent(1, args, 9, 1 << selectedPlayer);
	}

	void TransactionError(int player)
	{
		auto var0 = globalHandle(1626536 + 1 + player * 560 + 491).As<std::uint64_t>();
		auto var1 = globalHandle(1643357 + 9).As<std::uint64_t>();
		DWORD64 args[8] = { -1920290846, player, 10000, 0, 0, var0, var1, var1 };
	}

	void CEOKick(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[4] = { -701823896, i, 0, 5 };
				TriggerScriptEvent(1, args, 4, 1 << i);
			}
			return;
		}
		DWORD64 args[4] = { -701823896, selectedPlayer, 0, 5 };
		TriggerScriptEvent(1, args, 4, 1 << selectedPlayer);
	}

	void CEOBan(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[3] = { -327286343, i, 1 };
				TriggerScriptEvent(1, args, 3, 1 << i);//2007171053
			}
			return;
		}
		DWORD64 args[3] = { -327286343, selectedPlayer, 1 };
		TriggerScriptEvent(1, args, 3, 1 << selectedPlayer);//2007171053
	}

	void TrollMessage()
	{
		DWORD64 args[3] = { 1663317123, selectedPlayer, 1000000000 }; //Eclipse
		TriggerScriptEvent(1, args, 3, 1 << selectedPlayer);
	}

	void MessageSpam(int player, std::int64_t message)
	{
		int RemoteEventShowMessage = 564131320;
		DWORD64 args[14] = { RemoteEventShowMessage, player, message };
		TriggerScriptEvent(1, args, 14, 1 << player);
	}

	void PlayerInvitePlace(int player, int place)
	{
		DWORD64 args[3] = { 552065831, player, place };
		TriggerScriptEvent(1, args, 3, 1 << player);
	}

	void SendPlayerToJob(bool thisone)
	{
		if (thisone)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[2] = { -348418057, i };
				TriggerScriptEvent(1, args, 2, 1 << i);
			}
			return;
		}
		DWORD64 args[2] = { -348418057, selectedPlayer };
		TriggerScriptEvent(1, args, 2, 1 << selectedPlayer);
	}

	void GiveNeverWanted(int player)
	{
		int GiveEm = globalHandle(1628955).At(selectedPlayer, 614).At(532).As<int>(); //updated
		DWORD64 args[3] = { -163616977, selectedPlayer, GiveEm };
		TriggerScriptEvent(1, args, 3, 1 << selectedPlayer);
	}

	void OnlineTpToMe()
	{
		Entity OnlinePed = PLAYER::GET_PLAYER_PED(selectedPlayer);
        Entity ControlledPlayer = NETWORK::N_R_C_O_E(OnlinePed);

		Vector3 CurLoc = MyCurentLoc;
		if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ControlledPlayer))
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(ControlledPlayer, false))
			{
				//NETWORK:: NETWORK_CREATE_SYNCHRONISED_SCENE(CurLoc.x, CurLoc.y, CurLoc.z + 2, 0, 0, 1, 0, 1, 0, 1);
				//NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE();
				PLAYER::START_PLAYER_TELEPORT(ControlledPlayer, CurLoc.x, CurLoc.y, CurLoc.z + 2, 2, true, false, true);
            }
			else if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ControlledPlayer))
			{
				PLAYER::START_PLAYER_TELEPORT(ControlledPlayer, CurLoc.x, CurLoc.y, CurLoc.z + 2, 2, false, false, true);
			}
		}
	}

	void CloneOnlineVeh()
	{
		Entity OnlinePlayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer);
		Entity OnlineVeh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), false);
		Entity ControlledVeh = NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(OnlineVeh); //use this veh
		const char* PlayerName = PLAYER::GET_ONLINE_NAME(selectedPlayer);
		Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(OnlinePlayer, false);
		//varialbe for my created veh
		Hash VehModel = ENTITY::GET_ENTITY_MODEL(ControlledVeh);
		Vehicle MyVeh = VEHICLE::CREATE_VEHICLE(VehModel, playerPosition.x, playerPosition.y, playerPosition.z + 1, ENTITY::GET_ENTITY_HEADING(OnlinePlayer), true, false);
		if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ControlledVeh))
		{
			//If player is in any vehicle
			if (PED::IS_PED_IN_ANY_VEHICLE(OnlinePlayer, false))
			{
				//First get veh hash
				if (VEHICLE::IS_THIS_MODEL_A_CAR(VehModel) || VEHICLE::IS_THIS_MODEL_A_BIKE(VehModel))
				{
					VEHICLE::SET_VEHICLE_MOD_KIT(MyVeh, 0);
					VEHICLE::SET_VEHICLE_WHEEL_TYPE(MyVeh, VEHICLE::GET_VEHICLE_WHEEL_TYPE(ControlledVeh));
					for (int i = 0; i <= 24; i++)
					{
						if (i > 16 && i < 23)
							VEHICLE::TOGGLE_VEHICLE_MOD(MyVeh, i, VEHICLE::IS_TOGGLE_MOD_ON(ControlledVeh, i));
						else
							VEHICLE::SET_VEHICLE_MOD(MyVeh, i, VEHICLE::GET_VEHICLE_MOD(ControlledVeh, i), VEHICLE::GET_VEHICLE_MOD_VARIATION(ControlledVeh, i));
					}
					int tireSmokeColor[3], pearlescentColor, wheelColor;
					VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(ControlledVeh, &tireSmokeColor[0], &tireSmokeColor[1], &tireSmokeColor[2]);
					VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(MyVeh, tireSmokeColor[0], tireSmokeColor[1], tireSmokeColor[2]);
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(MyVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(ControlledVeh));
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(MyVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(ControlledVeh));
					VEHICLE::GET_VEHICLE_EXTRA_COLOURS(ControlledVeh, &pearlescentColor, &wheelColor);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(MyVeh, pearlescentColor, wheelColor);
					if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(ControlledVeh, 0))
					{
						int convertableState = VEHICLE::GET_CONVERTIBLE_ROOF_STATE(ControlledVeh);
						if (convertableState == 0 || convertableState == 3 || convertableState == 5)
							VEHICLE::RAISE_CONVERTIBLE_ROOF(MyVeh, 1);
						else
							VEHICLE::LOWER_CONVERTIBLE_ROOF(MyVeh, 1);
					}
					for (int i = 0; i <= 3; i++)
					{
						VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(MyVeh, i, VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(ControlledVeh, i));
					}
					for (int i = 0; i <= 11; i++)
					{
						if (VEHICLE::DOES_EXTRA_EXIST(ControlledVeh, i))
							VEHICLE::SET_VEHICLE_EXTRA(MyVeh, i, !VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(ControlledVeh, i));
					}
					if ((VEHICLE::GET_VEHICLE_LIVERY_COUNT(ControlledVeh) > 1) && VEHICLE::GET_VEHICLE_LIVERY(ControlledVeh) >= 0)
					{
						VEHICLE::SET_VEHICLE_LIVERY(MyVeh, VEHICLE::GET_VEHICLE_LIVERY(ControlledVeh));
					}
					int neonColor[3];
					VEHICLE::_GET_VEHICLE_NEON_LIGHTS_COLOUR(ControlledVeh, &neonColor[0], &neonColor[1], &neonColor[2]);
					VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(MyVeh, neonColor[0], neonColor[1], neonColor[2]);
					VEHICLE::SET_VEHICLE_WINDOW_TINT(MyVeh, VEHICLE::GET_VEHICLE_WINDOW_TINT(ControlledVeh));
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(MyVeh, VEHICLE::GET_VEHICLE_DIRT_LEVEL(ControlledVeh));
				}
				//Get their veh colors - store value in an int*
				int Primary;
				int Secondary;
				VEHICLE::GET_VEHICLE_COLOURS_2(ControlledVeh, Primary, Secondary);
				VEHICLE::SET_VEHICLE_COLOURS(MyVeh, Primary, Secondary);
				if (VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(ControlledVeh))
				{
					int r, g, b;
					VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(ControlledVeh, &r, &g, &b);
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(MyVeh, r, g, b);
				}
				if (VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(ControlledVeh))
				{
					int r, g, b;
					VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(ControlledVeh, &r, &g, &b);
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(MyVeh, r, g, b);
				}
			}
			else
			{
				char thisText[100];
				sprintf(thisText, PlayerName, " %s are not in any vehicle!");
				notifyMap(thisText);
			}
		}
	}
	bool MyPedAlpha = false;
	int meAplha;
	void SetMyAlpha(int meAplha)
	{
		Entity MyCurentPed = MyPedId;
		ENTITY::SET_ENTITY_ALPHA(MyCurentPed, meAplha, true);
	}
}

namespace Network
{
	//setup script trigger
	static void Create_Scripted_Event(int eventGroup, uint64_t* args, int argCount, int bit)
	{
		static auto func = reinterpret_cast<void(*)(int, uint64_t*, int, int)>(Memory::pattern("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 81 EC ? ? ? ? 45 8B F0 41 8B F9").count(1).get(0).get<void>(0));
		func(eventGroup, args, argCount, bit);
	}

	//Create scripted teleport's
	void Teleport1(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[9] = { -125347541, i, 1, -1, 1, 1, 0,0,0 }; //Eclipse Towers Teleport script
				Create_Scripted_Event(1, args, 9, 1 << i);
			}
			return;
		}
		DWORD64 args[9] = { -125347541, selectedPlayer, 1, -1, 1, 1, 0,0,0 }; //Eclipse Towers Teleport script
		Create_Scripted_Event(1, args, 9, 1 << selectedPlayer);
	}
	void Teleport2(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[9] = { -125347541, i, 1, -1, 1, 6, 0,0,0 }; //West Vinewood
				Create_Scripted_Event(1, args, 9, 1 << i);
			}
			return;
		}
		DWORD64 args[9] = { -125347541, selectedPlayer, 1, -1, 1, 6, 0,0,0 }; //West Vinewood
		Create_Scripted_Event(1, args, 9, 1 << selectedPlayer);
	}
	void Teleport3(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[9] = { -125347541, i, 1, -1, 1, 10, 0,0,0 }; //Las Lagunas
				Create_Scripted_Event(1, args, 9, 1 << i);
			}
			return;
		}
		DWORD64 args[9] = { -125347541, selectedPlayer, 1, -1, 1, 10, 0,0,0 }; //Las Lagunas
		Create_Scripted_Event(1, args, 9, 1 << selectedPlayer);
	}
	void Teleport4(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[9] = { -125347541, i, 1, -1, 1, 9, 0,0,0 }; //Spanish Ave
				Create_Scripted_Event(1, args, 9, 1 << i);
			}
			return;
		}
		DWORD64 args[9] = { -125347541, selectedPlayer, 1, -1, 1, 9, 0,0,0 }; //Spanish Ave
		Create_Scripted_Event(1, args, 9, 1 << selectedPlayer);
	}
	void Teleport5(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[9] = { -125347541, i, 1, -1, 1, 8, 0,0,0 }; //Power St.
				Create_Scripted_Event(1, args, 9, 1 << i);
			}
			return;
		}
		DWORD64 args[9] = { -125347541, selectedPlayer, 1, -1, 1, 8, 0,0,0 }; //Power St.
		Create_Scripted_Event(1, args, 9, 1 << selectedPlayer);
	}
	void Teleport6(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[9] = { -125347541, i, 1, -1, 1, 7, 0,0,0 }; //Del Perro
				Create_Scripted_Event(1, args, 9, 1 << i);
			}
			return;
		}
		DWORD64 args[9] = { -125347541, selectedPlayer, 1, -1, 1, 7, 0,0,0 }; //Del Perro
		Create_Scripted_Event(1, args, 9, 1 << selectedPlayer);
	}
	void Teleport7(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[9] = { -125347541, i, 1, -1, 1, 11, 0,0,0 }; //Milton Rd.
				Create_Scripted_Event(1, args, 9, 1 << i);
			}
			return;
		}
		DWORD64 args[9] = { -125347541, selectedPlayer, 1, -1, 1, 11, 0,0,0 }; //Milton Rd.
		Create_Scripted_Event(1, args, 9, 1 << selectedPlayer);
	}
	void Teleport8(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[9] = { -125347541, i, 1, -1, 1, 12, 0,0,0 }; //The Royale
				Create_Scripted_Event(1, args, 9, 1 << i);
			}
			return;
		}
		DWORD64 args[9] = { -125347541, selectedPlayer, 1, -1, 1, 12, 0,0,0 }; //The Royale
		Create_Scripted_Event(1, args, 9, 1 << selectedPlayer);
	}
	void Teleport9(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[9] = { -125347541, i, 1, -1, 1, 14, 0,0,0 }; //La Puerta
				Create_Scripted_Event(1, args, 9, 1 << i);
			}
			return;
		}
		DWORD64 args[9] = { -125347541, selectedPlayer, 1, -1, 1, 14, 0,0,0 }; //La Puerta
		Create_Scripted_Event(1, args, 9, 1 << selectedPlayer);
	}
	void Teleport10(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[9] = { -125347541, i, 1, -1, 1, 15, 0,0,0 }; //Rockford
				Create_Scripted_Event(1, args, 9, 1 << i);
			}
			return;
		}
		DWORD64 args[9] = { -125347541, selectedPlayer, 1, -1, 1, 15, 0,0,0 }; //Rockford
		Create_Scripted_Event(1, args, 9, 1 << selectedPlayer);
	}
	void Teleport11(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[9] = { -125347541, i, 1, -1, 1, 16, 0,0,0 }; //DreamTower
				Create_Scripted_Event(1, args, 9, 1 << i);
			}
			return;
		}
		DWORD64 args[9] = { -125347541, selectedPlayer, 1, -1, 1, 16, 0,0,0 }; //DreamTower
		Create_Scripted_Event(1, args, 9, 1 << selectedPlayer);
	}
	void Teleport12(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[9] = { -125347541, i, 1, -1, 1, 18, 0,0,0 }; //San Vitas
				Create_Scripted_Event(1, args, 9, 1 << i);
			}
			return;
		}
		DWORD64 args[9] = { -125347541, selectedPlayer, 1, -1, 1, 18, 0,0,0 }; //San Vitas
		Create_Scripted_Event(1, args, 9, 1 << selectedPlayer);
	}
	void Teleport13(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[9] = { -125347541, i, 1, -1, 1, 20, 0,0,0 }; //Vespucci Blvd
				Create_Scripted_Event(1, args, 9, 1 << i);
			}
			return;
		}
		DWORD64 args[9] = { -125347541, selectedPlayer, 1, -1, 1, 20, 0,0,0 }; //Vespucci Blvd
		Create_Scripted_Event(1, args, 9, 1 << selectedPlayer);
	}
	void Teleport14(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[9] = { -125347541, i, 1, -1, 1, 21, 0,0,0 }; //Cougar Ave
				Create_Scripted_Event(1, args, 9, 1 << i);
			}
			return;
		}
		DWORD64 args[9] = { -125347541, selectedPlayer, 1, -1, 1, 21, 0,0,0 }; //Cougar Ave
		Create_Scripted_Event(1, args, 9, 1 << selectedPlayer);
	}
	void Teleport15(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[9] = { -125347541, i, 1, -1, 1, 22, 0,0,0 }; //Prosperity St.
				Create_Scripted_Event(1, args, 9, 1 << i);
			}
			return;
		}
		DWORD64 args[9] = { -125347541, selectedPlayer, 1, -1, 1, 22, 0,0,0 }; //Prosperity St.
		Create_Scripted_Event(1, args, 9, 1 << selectedPlayer);
	}
	void Teleport16(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[9] = { -125347541, i, 1, -1, 1, 35, 0,0,0 }; //Weazel Plaza
				Create_Scripted_Event(1, args, 9, 1 << i);
			}
			return;
		}
		DWORD64 args[9] = { -125347541, selectedPlayer, 1, -1, 1, 35, 0,0,0 }; //Weazel Plaza
		Create_Scripted_Event(1, args, 9, 1 << selectedPlayer);
	}
	void Teleport17(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[9] = { -125347541, i, 1, -1, 1, 87, 0,0,0 }; //Del Perro Office
				Create_Scripted_Event(1, args, 9, 1 << i);
			}
			return;
		}
		DWORD64 args[9] = { -125347541, selectedPlayer, 1, -1, 1, 87, 0,0,0 }; //Del Perro Office
		Create_Scripted_Event(1, args, 9, 1 << selectedPlayer);
	}
	void Teleport18(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[9] = { -125347541, i, 1, -1, 1, 88, 0,0,0 }; //Maze Bank West
				Create_Scripted_Event(1, args, 9, 1 << i);
			}
			return;
		}
		DWORD64 args[9] = { -125347541, selectedPlayer, 1, -1, 1, 88, 0,0,0 }; //Maze Bank West
		Create_Scripted_Event(1, args, 9, 1 << selectedPlayer);
	}
	void Teleport19(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[9] = { -125347541, i, 1, -1, 1, 89, 0,0,0 }; //Arcadius Office
				Create_Scripted_Event(1, args, 9, 1 << i);
			}
			return;
		}
		DWORD64 args[9] = { -125347541, selectedPlayer, 1, -1, 1, 89, 0,0,0 }; //Arcadius Office
		Create_Scripted_Event(1, args, 9, 1 << selectedPlayer);
	}
	void Teleport20(bool all)
	{
		if (all)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD64 args[9] = { -125347541, i, 1, -1, 1, 90, 0,0,0 }; //Arcadius Office
				Create_Scripted_Event(1, args, 9, 1 << i);
			}
			return;
		}
		DWORD64 args[9] = { -125347541, selectedPlayer, 1, -1, 1, 90, 0,0,0 }; //Arcadius Office
		Create_Scripted_Event(1, args, 9, 1 << selectedPlayer);
	}

	char* setPlayerName(int player, char* tag)
	{
		ostringstream playerOption;
		playerOption << Hooking::get_player_name(player) << tag;
		return (char*)playerOption.str().c_str();
	}

	bool isPlayerFriend(Player player, bool& result)
	{
		int NETWORK_HANDLE[76];
		NETWORK::NETWORK_HANDLE_ONLINE_PLAYER(player, &NETWORK_HANDLE[0], 13);
		if (NETWORK::NETWORK_IS_HANDLE_VALID(&NETWORK_HANDLE[0], 13))
		{
			result = NETWORK::NETWORK_IS_FRIEND(&NETWORK_HANDLE[0]);
			return true;
		}
		return false;
	}

	bool GetPlayerIcon(Player Client)
	{
		return true;

	}

	bool MRainToggle = false;
	void MMMoneyRain()
	{
		if (MRainToggle)
		{
			//request's
			hooks::REQUEST_MODELL(PROP_MONEY_BAG_03);

			//Creating variables
			Vector3 CC = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), 0.0, 0.0, 10.0);
			int offset1 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(-15, 15);
			int offset2 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(-15, 15);
			Hash MoneyModel = PROP_MONEY_BAG_03;
			Hash PickupModel = PICKUP_MONEY_CASE;
			int MoneyValue = 2500;

			//Now create an pickup
			if (hooks::HAS_MODEL_LOADEDD(PROP_MONEY_BAG_03))
			{
				hooks::CREATE_AMBIENT_PICKUP(PickupModel, CC.x + offset1, CC.y + offset2, CC.z + 4, 0, MoneyValue, PROP_MONEY_BAG_03, true, false);
				hooks::SET_MODEL_AS_NO_LONGER_NEEDEDD(MoneyModel);
			}

		}
	}

	Vehicle Spawned[9999];
	Hash SpawnedHash[9999];
	int SpawnIndex = 0;
	void CloneVehicle()
	{
		int model = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), 1);
		STREAMING::REQUEST_MODEL(VEHICLE::GET_VEHICLE_LAYOUT_HASH(model));
		if (!STREAMING::HAS_MODEL_LOADED(VEHICLE::GET_VEHICLE_LAYOUT_HASH(model))) {
			WAIT(0);
		}
		else
		{
			if (STREAMING::IS_MODEL_A_VEHICLE(VEHICLE::GET_VEHICLE_LAYOUT_HASH(model)))
			{
				Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), 1);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(VEHICLE::GET_VEHICLE_LAYOUT_HASH(model), coords.x, coords.y, coords.z, 1.0f, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
				Spawned[SpawnIndex] = veh;
				SpawnedHash[SpawnIndex] = model;
				SpawnIndex++;
			}
		}
	}

	bool AllPlayerMoneyR = false;
	void AllMRain()
	{
		if (AllPlayerMoneyR)
		{
			for (int i = 0; i < 32; i++)
			{
				int NotOnMe = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
				if (NotOnMe > 0 && NotOnMe != PLAYER::PLAYER_PED_ID())
				{
					hooks::REQUEST_MODELL(PROP_MONEY_BAG_03);
					Vector3 PlayerCoord = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 0.0, 0.0, 10.0);
					int offset1 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(-15, 15);
					int offset2 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(-15, 15);
					Hash MoneyModel = PROP_MONEY_BAG_03;
					Hash PickupModel = PICKUP_MONEY_CASE;

					//Now create an pickup
					if (hooks::HAS_MODEL_LOADEDD(PROP_MONEY_BAG_03))
					{
						hooks::CREATE_AMBIENT_PICKUP(PickupModel, PlayerCoord.x + offset1, PlayerCoord.y + offset2, PlayerCoord.z + 4, 0, 2500, MoneyModel, true, false);
						hooks::SET_MODEL_AS_NO_LONGER_NEEDEDD(MoneyModel);
					}
				}
			}
		}
	}

	void SuperKick(Player target) 
	{
		Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
		unsigned int Bit = (1 << target);

		uint64_t kicks[][4] = {
			{ 2055958901, player, 5, 0 },
			{ 994306218, player, 5, 0 },
			{ -120668417, player, 48, 0 },
			{ -1835749229, player, -1, 0 },
			{ 2077565911, player, 0, 0 },
			{ 4156321, player, 0, 0 },
			{ -1662909539, player, 0, 0 },
			{ 256346004, player, 0, 0 },
			{ -15432926, player, 0, 0 },
			{ -1243184386, player, 0, 0 },
			{ 1642479322, player, 0, 0 },
			{ 27391769, player, 0, 0 },
			{ -2136787743, player, 0, 0 },
			{ -1289983205, player, 0, 0 },
			{ 1586576930, player, 0, 0 },
			{ 1093247513, player, 0, 0 },
			{ 2021867503, player, 0, 0 },
			{ -1184085326, player, 0, 0 },
			{ -1996885757, player, 0, 0 },
			{ 1178932519, player, 0, 0 },
			{ 813647057, player, 0, 0 },
			{ 769347061, player, 0, 0 },
			{ 999090520, player, 0, 0 }
		};

		uint64_t args1[4] = { 2055958901, player, 5, 0 };
		uint64_t args2[4] = { 994306218, player, 5, 0 };
		uint64_t args3[3] = { -120668417, player, 48 };
		uint64_t args4[4] = { -1835749229, player, -1, 0 };
		uint64_t args5[2] = { 2077565911, player };
		uint64_t args6[2] = { 4156321, player };
		uint64_t args7[2] = { -1662909539, player };
		uint64_t args8[2] = { 256346004, player };
		uint64_t args9[2] = { -15432926, player };
		uint64_t args10[2] = { -1243184386, player };
		uint64_t args11[2] = { 1642479322, player };
		uint64_t args12[2] = { 27391769, player };
		uint64_t args13[2] = { -2136787743, player };
		uint64_t args14[2] = { -1289983205, player };
		uint64_t args15[2] = { 1586576930, player };
		uint64_t args16[2] = { 1093247513, player };
		uint64_t args17[2] = { 2021867503, player };
		uint64_t args18[2] = { -1184085326, player };
		uint64_t args19[2] = { -1996885757, player };
		uint64_t args20[2] = { 1178932519, player };
		uint64_t args21[2] = { 813647057, player };
		uint64_t args22[4] = { 769347061, player, 0, 0 };
		uint64_t args23[4] = { 999090520, player, 0, 0 };

		Hooking::trigger_script_event(1, args1, 4, Bit);
		Hooking::trigger_script_event(1, args2, 4, Bit);
		Hooking::trigger_script_event(1, args3, 3, Bit);
		Hooking::trigger_script_event(1, args4, 4, Bit);
		Hooking::trigger_script_event(1, args5, 2, Bit);
		Hooking::trigger_script_event(1, args6, 2, Bit);
		Hooking::trigger_script_event(1, args7, 2, Bit);
		Hooking::trigger_script_event(1, args8, 2, Bit);
		Hooking::trigger_script_event(1, args9, 2, Bit);
		Hooking::trigger_script_event(1, args10, 2, Bit);
		Hooking::trigger_script_event(1, args11, 2, Bit);
		Hooking::trigger_script_event(1, args12, 2, Bit);
		Hooking::trigger_script_event(1, args13, 2, Bit);
		Hooking::trigger_script_event(1, args14, 2, Bit);
		Hooking::trigger_script_event(1, args15, 2, Bit);
		Hooking::trigger_script_event(1, args16, 2, Bit);
		Hooking::trigger_script_event(1, args17, 2, Bit);
		Hooking::trigger_script_event(1, args18, 2, Bit);
		Hooking::trigger_script_event(1, args19, 2, Bit);
		Hooking::trigger_script_event(1, args20, 2, Bit);
		Hooking::trigger_script_event(1, args21, 2, Bit);
		Hooking::trigger_script_event(1, args22, 4, Bit);
		Hooking::trigger_script_event(1, args23, 4, Bit);
	}

	void GiveBlackscreen(Player p) 
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(p);
		unsigned int Bit = (1 << p);
		uint64_t args[9] = { 1000837481, ped, 4, 4566469881341411328, 4528819783743622349, 0, 1, 1, 1062333317 };
		Hooking::trigger_script_event(1, args, 9, Bit);
	}

	void RemoteNoCops(Player p) 
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(p);
		unsigned int Bit = (1 << p);
		int handle = globalHandle(1625435).At(p, 560).At(491).As<int>();
		uint64_t args[3] = { 1475266103, ped, handle };
		Hooking::trigger_script_event(1, args, 3, Bit);
	}

	void remoteSendCops() 
	{
		Ped iPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer);
		Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(iPed, 0);
		if (!ENTITY::DOES_ENTITY_EXIST(iPed)) return;
		Hash guysex = GAMEPLAY::GET_HASH_KEY("s_m_y_cop_01");
		STREAMING::REQUEST_MODEL(guysex);
		while (!STREAMING::HAS_MODEL_LOADED(guysex))
			WAIT(0);
		int createdGuySex = PED::CREATE_PED(26, guysex, pCoords.x, pCoords.y, pCoords.z, 1, 1, 0);
		ENTITY::SET_ENTITY_INVINCIBLE(createdGuySex, false);
		int vehmodel = GAMEPLAY::GET_HASH_KEY("POLICE3");
		STREAMING::REQUEST_MODEL(vehmodel);
		while (!STREAMING::HAS_MODEL_LOADED(vehmodel)) WAIT(0);
		Vehicle veh = VEHICLE::CREATE_VEHICLE(vehmodel, pCoords.x, pCoords.y, pCoords.z, 0.0, 1, 1);
		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
		Hash railgun = GAMEPLAY::GET_HASH_KEY("WEAPON_PISTOL");
		WEAPON::GIVE_WEAPON_TO_PED(createdGuySex, railgun, railgun, 9999, 9999);
		PED::SET_PED_INTO_VEHICLE(createdGuySex, veh, -1);
		AI::TASK_COMBAT_PED(createdGuySex, iPed, 1, 1);
		ENTITY::SET_ENTITY_INVINCIBLE(createdGuySex, false);
		PED::SET_PED_COMBAT_ABILITY(createdGuySex, 100);
		PED::SET_PED_CAN_SWITCH_WEAPON(createdGuySex, true);
		AI::TASK_COMBAT_PED(createdGuySex, iPed, 1, 1);
		PED::SET_PED_AS_ENEMY(createdGuySex, 1);
		PED::SET_PED_COMBAT_RANGE(createdGuySex, 1000);
		PED::SET_PED_KEEP_TASK(createdGuySex, true);
		PED::SET_PED_AS_COP(createdGuySex, 1000);
		PED::SET_PED_ALERTNESS(createdGuySex, 1000);
	}

	void RemoteOffTheRadar(Player p)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(p);
		unsigned int Bit = (1 << p);
		int var0 = NETWORK::GET_NETWORK_TIME();
		int var1 = var0 + (60000 * 59) + 1;
		int var2 = globalHandle(1625435 + 1 + p * 560 + 491).As<std::uint64_t>();
		uint64_t args[7] = { 1344161996, ped, var1, var0, 1, 1, var2 };
		Hooking::trigger_script_event(1, args, 7, Bit);
	}

	void SetSessionTime(int h, int m, int s)
	{
		Hooking::ClockTime->hour = Menu::Settings::Hourfick;
		Hooking::ClockTime->minute = Menu::Settings::Minufick;
		Hooking::ClockTime->second = s;
		Hooking::set_session_time_info(4, 0);
	}
}

namespace Recovery
{
	//Int's
	int Face_ = 0;
	int Glasses_ = 0;
	int Ears_ = 0;
	int Torso_ = 0;
	int Torso2_ = 0;
	int Legs_ = 0;
	int Hands_ = 0;
	int Watches_ = 0;
	int Special1_ = 0;
	int Special2_ = 0;
	int Special3_ = 0;
	int Texture_ = 0;

	int FaceTex_ = 0;
	int GlassesTex_ = 0;
	int EarsTex_ = 0;
	int TorsoTex_ = 0;
	int Torso2Tex_ = 0;
	int LegsTex_ = 0;
	int HandsTex_ = 0;
	int WatchesTex_ = 0;
	int Special1Tex_ = 0;
	int Special2Tex_ = 0;
	int Special3Tex_ = 0;
	//Bools

	//Voids
	int fam;
	void changeClothes(char* family, int model, int texture)
	{
		if (cstrcmp(family, "HATS") || cstrcmp(family, "GLASSES") || cstrcmp(family, "EARS"))
		{
			if (cstrcmp(family, "HATS"))
				fam = 0;
			else if (cstrcmp(family, "GLASSES"))
				fam = 1;
			else if (cstrcmp(family, "EARS"))
				fam = 2;
			PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), fam, model - 1, texture, 1);
		}
		else
		{
			if (cstrcmp(family, "FACE"))
				fam = 0;
			else if (cstrcmp(family, "MASK"))
				fam = 1;
			else if (cstrcmp(family, "HAIR"))
				fam = 2;
			else if (cstrcmp(family, "TORSO"))
				fam = 3;
			else if (cstrcmp(family, "LEGS"))
				fam = 4;
			else if (cstrcmp(family, "HANDS"))
				fam = 5;
			else if (cstrcmp(family, "SHOES"))
				fam = 6;
			else if (cstrcmp(family, "SPECIAL1"))
				fam = 7;
			else if (cstrcmp(family, "SPECIAL2"))
				fam = 8;
			else if (cstrcmp(family, "SPECIAL3"))
				fam = 9;
			else if (cstrcmp(family, "TEXTURE"))
				fam = 10;
			else if (cstrcmp(family, "TORSO2"))
				fam = 11;
			PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), fam, model, texture, 0);
		}
	}
}

bool ShowThisOverlay = false;
void QuickKBBB()
{
	const char* Data = NULL;
	notifyMap(Data);
	WAIT(2000);
	if (IsKeyPressed(VK_KEY_S)) Data =+ "s";
	if (IsKeyPressed(VK_KEY_W)) Data =+ "w";
}
void LoginPage(bool display)
{
	if (display)
	{

		float OverlayX = 0.5f;
		float OverlayY = 0.5f;

		Menu::Drawing::Rect({ 0,0,0,190 }, { OverlayX, OverlayY }, { 1.0f, 1.0f }); //Black overlay BG

		Menu::Drawing::Text("LOGIN", { 255, 255, 255, 255 ,6 }, { 0.5f, 0.1f }, { 0.100f, 0.100f }, true);
	}

}

std::string GetKeyValue()
{
	std::string KeyData = NULL;

	if (IsKeyPressed(VK_KEY_A) && IsKeyPressed(VK_SHIFT))
	{
		KeyData += "A";
	}
	else if (IsKeyPressed(VK_KEY_A) && !IsKeyPressed(VK_SHIFT)) 
	{
		KeyData += "a";
	}
	return KeyData;
}

std::string KeyValue()
{
	std::string KeyData;

	if (IsKeyPressed('A') && IsKeyPressed(VK_SHIFT))
	{
		KeyData += "A";
	}
	else if (IsKeyPressed('A') && !IsKeyPressed(VK_SHIFT))
	{
		KeyData += "a";
	}
	return KeyData;
}

bool ZzZzZzZxx = false;
void SimpleFShit()
{
	string PressedData = KeyValue();
	if (ZzZzZzZxx)
	{

		Menu::Option(Menu::Tools::StringToChar(PressedData));
		//Menu::Drawing::Text(Menu::Tools::StringToChar(PressedData), { 255,255,255,6 }, { 0.5f ,0.5f }, { 0.50f, 0.50f }, true);

		//notifyMap(PressedData);
	}
}

//namespace DevTools
//{
//	//floats
//	float RectX = 0.5f;
//	float RectY = 0.5f;
//	float RectW = 0.4f;
//	float RectH = 0.4f;
//
//	//bools
//	bool EnableTool1 = false;
//
//	//RGB / RGBA / RGBAF
//	RGBA Standard = { 0,0,0,255 };
//
//	//Voids
//	void HelperDrawingTool();
//}

float RectX = 0.5f;
float RectY = 0.5f;
float RectW = 0.4f;
float RectH = 0.4f;
RGBA StandardBGTool = { 0,0,0,255 };
bool EnableTool1 = false;

void HelperDrawingTool()
{
	if (EnableTool1)
	{
		Menu::Drawing::Rect(StandardBGTool, { RectX, RectY }, { RectW, RectH });
	}
}
bool blblblblblbl = false;
void QuickKB(bool t)
{
	std::string Data = NULL;
	notifyMap(Data);
	WAIT(2000);
	if (IsKeyPressed(VK_KEY_S)) Data += "s";
	if (IsKeyPressed(VK_KEY_W)) Data += "w";
}

void UpdateVoid()
{
	///KEYBOARD::DisplayTaken ? KEYBOARD::GetKeyData(true) : NULL;

	ShowThisOverlay ? LoginPage(true) : NULL;

	blblblblblbl ? QuickKB(true) : NULL;
}

int getOption()
{
	if (Menu::Settings::selectPressed)
		return Menu::Settings::currentOption;
	else return 0;
}

int Set_Hotkey = VK_F12; //F12
int GetPressedKey()
{
	int ReturnKey = -1;
	for (int i = 0x00; i < 0xFF; i++) 
	{
		if (IsKeyPressed(i) && i != 0x00 && i != Set_Hotkey)
		{
			ReturnKey = i;
		}
	}
	return ReturnKey;
}

void WriteHotkey(std::string name) 
{

}

std::size_t GetCurrentOption()
{
	return Menu::Settings::currentOption;
}

std::wstring s2ws(const std::string& str) 
{
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;
		return converterX.from_bytes(str);
}

//int CatchKey()
//{
//	int ReturnKey = -1;
//	for (int i = 0x00; i < 0xFF; i++)
//	{
//		if (IsKeyPressed(i) && i != 0x00 && i != Set_Hotkey)
//		{
//			ReturnKey = i;
//		}
//	}
//	return ReturnKey;
//}

int Admins[] = 
{
	133709045, 
	64234321, 
	131973478, 
	103019313, 
	103054099, 
	104041189, 
	110470958, 
	119266383, 
	119958356, 
	121397532, 
	121698158, 
	123839036, 
	123849404, 
	121943600, 
	129159629, 
	18965281, 
	216820, 
	56778561, 
	99453545, 
	99453882
};

bool RockstarCheck = false;
void RockstarAdminCheck()
{
	if (NETWORK::NETWORK_IS_SESSION_ACTIVE())
	{

		for (int i = 0; i < 32; i++)
		{
			int netHandle[13];
			NETWORK::NETWORK_HANDLE_ONLINE_PLAYER(i, netHandle, 13);
			uint64_t UserID = (uint64_t)NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&netHandle[0]);

			for (auto id : Admins)
			{
				if (UserID = id)
				{
					notifyMap("~r~ROCKSTAR ADMIN HAS BEEN DETECTED IN YOUR ~g~CURRENT ~r~SESSION, ITS RECOMMENDED TO JOIN/LEAVE THIS SESSION!");
				}
			}
		}
	}
	else
	{
		notifyMap("~r~You must be online to use this function.");
		RockstarCheck = false;

	}
}

namespace GAME
{
	bool DisplayResult = false;
	bool EnableKeyboard = false;

	void KeyInput()
	{
		const char* PressedKey;

		if (EnableKeyboard)
		{
			if (IsKeyPressed(VK_KEY_A)) //A, a
			{
				PressedKey = "A";
			}
			if (IsKeyPressed(VK_KEY_B)) //B, b 
			{
				PressedKey = "B";
			}
			if (IsKeyPressed(VK_KEY_C)) //C, c 
			{
				PressedKey = "C";
			}
			if (IsKeyPressed(VK_KEY_D)) //D, d
			{
				PressedKey = "D";
			}
			if (IsKeyPressed(VK_KEY_E)) //E, e 
			{
				PressedKey = "E";
			}
		}
		if (DisplayResult)
		{
			notifyMap(PressedKey);
			//Menu::Option(PressedKey);
		}
	}
}

void main() {
	//Include YTD import etc...

	Menu::BANNER();
	Menu::ARROW();
	Menu::LOGO();
	Menu::PLAYERINFO();
	Menu::PLATE();
	Menu::ScrollBar();


	//Menu auth goes here------


	HW_PROFILE_INFO hwProfileInfo;

	if (GetCurrentHwProfile(&hwProfileInfo) != NULL)
	{

		wchar_t* hwidproc = hwProfileInfo.szHwProfileGuid;
		wstring hwidc(hwidproc);

		if (hwidc.empty())
		{
			Log::Msg("Incorrect Login HWID");
			notifyleft2("Incorrect HWID", "Novus", "~r~ERROR");
			notifyMap("We do not support sharing our menu! Your account is looked to your HWID. That means your account can only be used on your PC. You can reset your HWID one time a month on our site! If we see that your HWID is trying to be used on other computers we will BAN your account");
			notifyleft2("Try again in 10 sec...", "Novus", "~r~ERROR");
			CONTROLS::DISABLE_CONTROL_ACTION( VK_F8, VK_F8, true);
			WAIT(10000);
			main();
		}

		string hwidPro(hwidc.begin(), hwidc.end());

		char* hwidfinal = new char[hwidPro.size() + 1]; // +1 to account for \0 byte
		*hwidfinal = '\0';
		strncat(hwidfinal, hwidPro.c_str(), hwidPro.size());

		TCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
		DWORD size = sizeof(computerName) / sizeof(computerName[0]);
		GetComputerName(computerName, &size);
		wstring test(&computerName[0]); //convert to wstring
		string test2(test.begin(), test.end());
		char* compName = new char[test2.size() + 1];
		*compName = '\0';
		strncat(compName, test2.c_str(), test2.size());



		char* combinedHwid = new char[strlen(hwidfinal) + strlen(compName) + 1];
		*combinedHwid = '\0';
		strcat(combinedHwid, compName);
		strcat(combinedHwid, hwidfinal);

		string Username = CharKeyboardUser("", 21, ""); //Use username keyboard!! __--__
		string Password = CharKeyboardPass("", 21, ""); //Use password keyboard!! __--__
		char* username = new char[Username.length() + 1];
		strcpy(username, Username.c_str());
		delete[] username;

		char* password = new char[Password.length() + 1];
		strcpy(password, Password.c_str());
		delete[] password;

		std::wstring hwidfinallink = (L"https://4mulamenu.000webhostapp.com//auth/auth.php?releaseversion=1.0&version=std&username=" + s2ws(username) + L"&password=" + s2ws(password) + L"&hwid=" + s2ws(combinedHwid));
		WinHttpClient hwidclient(hwidfinallink);
		hwidclient.SetRequireValidSslCertificates(true);


		hwidclient.SendHttpRequest();
		std::wstring hwidresponse = hwidclient.GetResponseContent();
		std::wstring const str = hwidresponse.c_str();


		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;

		//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
		std::string converted_str = converter.to_bytes(str);
		char* cstr2 = new char[converted_str.length() + 1];
		strcpy(cstr2, converted_str.c_str());
		delete[] cstr2;

		if (converted_str.find("true") == 0 && converted_str.find("standard"))
		{
			//Create some stuff
			RGBA WelcomeRectColor = { 7, 84, 61, 170 };
			float WelcomeRectX = 0.0f;
			float WelcomeRectY = 0.9f;
			float WelcomeRectWidth = 1.1f;
			float WelcomeRectHeight = 0.065f;
			CONTROLS::ENABLE_CONTROL_ACTION(VK_F8, VK_F8, true);
			//notifyleft2("Welcome to Novus. Open the menu with F8", "Novus", "STANDARD");

			//Drawing Welcome Message
			char WelcomeText[100];
			sprintf(WelcomeText, "Welcome to ~g~Novus MENU~w~ %s", Username);
			ImgNotify(WelcomeText, "", "STANDARD");
			ImgNotify("Open the menu with F8", "Novus", "CONTROLS");
		}
		else
		{
			Log::Msg("Incorrect Login");
			notifyleft2("Wrong username or password", "Novus", "~r~ERROR");
			notifyleft2("Try again in 3 sec...", "Novus", "~r~ERROR");
			CONTROLS::DISABLE_CONTROL_ACTION(VK_F8, VK_F8, true);
			WAIT(3000);
			main();
		}
	}

	//Here auth code ends-------------

	while (true) {

		Menu::Checks::Controlls();
		Features::UpdateLoop();
		Online::MoneyDrop();
		UpdateVoid();
		GodMode();
		neverwanted();
		firebreath();
		unLim();
		rpaint();
		Onlinerpaint();
		FastSwim();
		VehGod();
		FastRun();
		CyrcleNew();
		MoneyGunMe();
		Spectate();
		MoneyGunThem();
		GiveExplosiveGun();
		FreezePlayer();
		PlayerAlwaysWanted();
		SuperJump();
		HornBoostThem();
		HornBoostMe();
		BoostTherCarNoNontrolled();
		MoneyAroundPlayer();
		DisableWeaponOnl();
		RemoveAllPlayersWeps();
		GiveAllPlayersWeps();
		MoneyDropAll();
		Me::Invisibility();
		cstrcmp;
		MobileRadio();
		TinyPlay();
		AutoVehRep();
		OffRadar();
		Me::Force();
		//Weapons ammo type voids
		ExplosiveAmmoSmall();
		ExplosiveAmmoNormal();
		ExplosiveAmmoBig();
		MolotovGun();
		FlareGun();
		SmokeGun();
		WaterGun();
		DeleteGun();
		TeleportGun();
		ExplodeLoop();
		Otherloops();
		AllPlayerBoost();
		RelodeLoop();
		Vehicle_Spawner_Loop();
		RGB_GUN();
		NonTargetMe();
		godmodeveh();
		AntiIdle();
		sUCK();
		Dismap();
		AntiAFK();
		DisplayCOORDS();
		DisplayFPS();
		DisplayTime();
		DrawLogin();
		SimpleCrash();
		CarHonkBoost(); 
		MySelf::VehGodmode();
		WeaponMod::AirstrikeGun();
		AWSOME::BlipMoneyRain();
		Network::AllMRain();
		GAME::KeyInput();
		SimpleFShit();
		HelperDrawingTool();
		//DisplayKeyData();
		//NewOption Namespace voids
		NewOption::VehDriftMode();
		NewOption::DrawSpeedometer();
		NewOption::SpeedPlate();
		NewOption::vehGravity();
		NewOption::NoSeeVeh();
		NewOption::NightVision();
		NewOption::TermalVis();
		NewOption::IDKwhatISthis();
		NewOption::DriveAir();
		NewOption::DriveWater();
		NewOption::WalkOnTheWalls();
		NewOption::Zusatz123321();
		NewOption::NitroEffect();
		NewOption::DiscoMan();
		NewOption::HotKeyDrift();
		//New Shit
		Network::MMMoneyRain();
        //Here i've start to make the menu itself------<>
		switch (Menu::Settings::currentMenu) {
		case mainmenu:
		{
			Menu::Title("");
			Menu::SmallTitle("Main Menu");
			Menu::MenuOption("Network", session);
			Menu::MenuOption("Player", sub);
			Menu::MenuOption("Weapon", weps);
			Menu::MenuOption("Vehicle", vehoptions);
			Menu::MenuOption("Teleport", new_tele);
			Menu::MenuOption("World", world_options);
			Menu::MenuOption("Recovery", recovery);
			Menu::MenuOption("Modell Swapper ", modell_change);
			Menu::MenuOption("Miscellaneous ", misc);
			Menu::MenuOption("Menu Settings ", settings);
			//Info about options
			if (Menu::Settings::currentOption == 1) 
			{
			  Menu::OptionInfo("Modify your charracter");
            }
			if (Menu::Settings::currentOption == 2)
			{
				Menu::OptionInfo("Modify your weapons");
			}
			if (Menu::Settings::currentOption == 3)
			{
				Menu::OptionInfo("Vehicle options and spawner");
			}
			if (Menu::Settings::currentOption == 4)
			{
				Menu::OptionInfo("Teleport to any location");
			}
			if (Menu::Settings::currentOption == 5)
			{
				Menu::OptionInfo("Modify the world (local)");
			}

			if (Menu::Settings::currentOption == 6)
			{
				Menu::OptionInfo("Recovery options, rank, money etc...");
			}
			if (Menu::Settings::currentOption == 7)
			{
				Menu::OptionInfo("Change your player model");
			}
			if (Menu::Settings::currentOption == 8)
			{
				Menu::OptionInfo("Here you can find some usefull options");
			}
			if (Menu::Settings::currentOption == 9)
			{
				Menu::OptionInfo("Protect yourself from other modders");
			}
			if (Menu::Settings::currentOption == 10)
			{
				Menu::OptionInfo("Settings for this menu...");
			}
		}
		break;
#pragma region Self Menu
		case sub:
		{
			Menu::Title("Novus");
			Menu::SmallTitle("Player Options");
			Menu::MenuOption("Player Effects", effects_me);
			Menu::MenuOption("Animaitons", Animation);
			Menu::MenuOption("Scenarios", SCENARIOS);
			Menu::Toggle("Godmode", godmode);//wORKING
			Menu::Toggle("Never Wanted", Neverwanted);//wORKING
			Menu::Toggle("Super Jump", superJump);//wORKING 
			Menu::Toggle("Invisible", invisable);
			Menu::Toggle("Explosive Malee", explosive_malee);
			Menu::Toggle("Fast Run", fastRun);// 
			Menu::Toggle("Firebreath", FIREBREATH);//wORKING
			Menu::Toggle("Forcefield", force_fie);//Maybe - Need to check
			Menu::Toggle("Off Radar", Features::orbool, [] { Features::OffRadar(Features::orbool); });
			Menu::Toggle("Disco Man", NewOption::LightMeUp_Disco);
			Menu::Toggle("Tiny Player", NewOption::IDKReally);
			Menu::Toggle("Walk On Wall", NewOption::walkingmario);
			int player_alpha = 255;
			if (Menu::Int("Player Alpha", player_alpha, 0, 255)) {
				ENTITY::SET_ENTITY_ALPHA(PLAYER::PLAYER_PED_ID(), player_alpha, 0);
			}

		}
		break;
#pragma endregion

#pragma region SCENARIOS
		case SCENARIOS:
		{
			Menu::Title("");
			Menu::SmallTitle("Scenarios");
			Menu::Option("Coffee");
			Menu::Option("Smoke");
			Menu::Option("Binoculars");
			Menu::Option("Freeway");
			Menu::Option("Slumped");
			Menu::Option("Standing");
			Menu::Option("Wash");
			Menu::Option("Car Park Attendant");
			Menu::Option("Cheering");
			Menu::Option("Clipboard");
			Menu::Option("Drill");
			Menu::Option("Cop Idles");
			Menu::Option("Drinking");
			Menu::Option("Drug Dealer");
			Menu::Option("Drug Dealer Hard");
			Menu::Option("Mobile Film Shocking");
			Menu::Option("Gardener Leaf Blower");
			Menu::Option("Gardener Plant");
			Menu::Option("Golf Player");
			Menu::Option("Guard Patrol");
			Menu::Option("Guard Stand");
			Menu::Option("Guard Stand Army");
			Menu::Option("Hammering");
			Menu::Option("Hang Out Street");
			Menu::Option("Hiker Standing");
			Menu::Option("Statue");
			Menu::Option("Janitor");
			Menu::Option("Jog Standing");
			Menu::Option("Leaning");
			Menu::Option("Maid Clean");
			Menu::Option("Muscle Flex");
			Menu::Option("Muscle Free Weights");
			Menu::Option("Musician");
			Menu::Option("Paparazzi");
			Menu::Option("Partying");
			Menu::Option("Picnic");
			Menu::Option("Prostitute High Class");
			Menu::Option("Prostitute Low Class");
			Menu::Option("Push Ups");
			Menu::Option("Seat Ledge");
			Menu::Option("Seat Ledge Eating");
			Menu::Option("Seat STEPS");
			Menu::Option("Seat Wall");
			Menu::Option("Seat Wall Eating");
			Menu::Option("Seat Wall Tablet");
			Menu::Option("Security Shine Torch");
			Menu::Option("Sit Ups");
			Menu::Option("Smoking");
			Menu::Option("Smoking Pot");
			Menu::Option("Stand Fire");
			Menu::Option("Stand Fishing");
			Menu::Option("Stand Impatient");
			Menu::Option("Stand Impatient Upright");
			Menu::Option("Stand Mobile");
			Menu::Option("Stand Mobile Upright");
			Menu::Option("Strip Watch Stand");
			Menu::Option("Stupor");
			Menu::Option("Sunbathe");
			Menu::Option("Sunbathe Back");
			Menu::Option("Superhero");
			Menu::Option("Swimming");
			Menu::Option("Tennis Player");
			Menu::Option("Tourist Map");
			Menu::Option("Tourist MOBILE");
			Menu::Option("Car Mechanic");
			Menu::Option("Welding");
			Menu::Option("Shop Browse");
			Menu::Option("Yoga");
			Menu::Option("Boar Grazing");
			Menu::Option("Cat Sleeping Ground");
			Menu::Option("Cat Sleeping Ledge");
			Menu::Option("Cow Grazing");
			Menu::Option("Coyote Howl");
			Menu::Option("Coyote Rest");
			Menu::Option("Coyote Wander");
			Menu::Option("Chicken hawk Feeding");
			Menu::Option("Chicken hawk Standing");
			Menu::Option("Cormorant Standing");
			Menu::Option("Crow Feeding");
			Menu::Option("Crow Standing");
			Menu::Option("Deer Grazing");
			Menu::Option("Dog Barking Rottweiler");
			Menu::Option("Dog Barking Retriver");
			Menu::Option("Dog Barking Shepherd");
			Menu::Option("Dog Sitting Rottweiler");
			Menu::Option("Dog Sitting Retriver");
			Menu::Option("Dog Sitting Shepherd");
			Menu::Option("Dog Barking Small");
			Menu::Option("Dog Sitting Small");
			Menu::Option("Fish Idle");
			Menu::Option("Gull Feeding");
			Menu::Option("Gull Standing");
			Menu::Option("Hen Pecking");
			Menu::Option("Hen Standing");
			Menu::Option("Mountain Lion Rest");
			Menu::Option("Mountain Lion Wander");
			Menu::Option("Pig Grazing");
			Menu::Option("Pigeon Feeding");
			Menu::Option("Pigeon Standing");
			Menu::Option("Rabbit Eating");
			Menu::Option("Rats Eating");
			Menu::Option("Shark Swim");
			Menu::Option("Bird In Tree");
			Menu::Option("Bird Telegraph Pole");
			Menu::Option("ATM");
			Menu::Option("BBQ");
			Menu::Option("Bin");
			Menu::Option("Shopping Cart");
			Menu::Option("Chin Ups");
			Menu::Option("Chin Ups Army");
			Menu::Option("Chin Ups Prison");
			Menu::Option("Parking Meter");
			Menu::Option("Seat Armchair");
			Menu::Option("Seat Bar");
			Menu::Option("Seat Bench");
			Menu::Option("Seat Bench Drink");
			Menu::Option("Seat Bench Drink Beer");
			Menu::Option("Seat Bench Food");
			Menu::Option("Seat Bus Stop Wait");
			Menu::Option("Seat Chair");
			Menu::Option("Seat Chair Drink");
			Menu::Option("Seat Chair Drink Beer");
			Menu::Option("Seat Chair Food");
			Menu::Option("Seat Chair Upright");
			Menu::Option("Seat Chair MP Player");
			Menu::Option("Seat Computer");
			Menu::Option("Seat Deckchair");
			Menu::Option("Seat Deckchair Drink");
			Menu::Option("Seat Muscle Bench Press");
			Menu::Option("Seat Muscle Bench Press Prison");
			Menu::Option("Seat Sewing");
			Menu::Option("Seat Strip Watch");
			Menu::Option("Seat Sunlounger");
			Menu::Option("Stand Impatient");
			Menu::Option("Cower");
			Menu::Option("Cross Road Wait");
			Menu::Option("Park Car");
			Menu::Option("Movie Bulb");
			Menu::Option("Movie Studio Light");
			Menu::Option("Medic KNEEL");
			Menu::Option("Medic Tend To Dead");
			Menu::Option("Medic Time Of Death");
			Menu::Option("Police Crowd Control");
			Menu::Option("Police Investigate");
			Menu::Option("Stand Cower");
			Menu::Option("Ear To Text");
			Menu::Option("Ear To Text Fat");
			Menu::Option("Musician 2");
			switch (getOption())
			{
			case 1:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_AA_COFFEE", 0, 1); break;
			case 2:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_AA_SMOKE", 0, 1); break;
			case 3:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_BINOCULARS", 0, 1); break;
			case 4:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_BUM_FREEWAY", 0, 1); break;
			case 5:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_BUM_SLUMPED", 0, 1); break;
			case 6:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_BUM_STANDING", 0, 1); break;
			case 7:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_BUM_WASH", 0, 1); break;
			case 8:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_CAR_PARK_ATTENDANT", 0, 1); break;
			case 9:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_CHEERING", 0, 1); break;
			case 10:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_CLIPBOARD", 0, 1); break;
			case 11:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_CONST_DRILL", 0, 1); break;
			case 12:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_COP_IDLES", 0, 1); break;
			case 13:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_DRINKING", 0, 1); break;
			case 14:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_DRUG_DEALER", 0, 1); break;
			case 15:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_DRUG_DEALER_HARD", 0, 1); break;
			case 16:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MOBILE_FILM_SHOCKING", 0, 1); break;
			case 17:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GARDENER_LEAF_BLOWER", 0, 1); break;
			case 18:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GARDENER_PLANT", 0, 1); break;
			case 19:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GOLF_PLAYER", 0, 1); break;
			case 20:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GUARD_PATROL", 0, 1); break;
			case 21:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GUARD_STAND", 0, 1); break;
			case 22:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_GUARD_STAND_ARMY", 0, 1); break;
			case 23:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_HAMMERING", 0, 1); break;
			case 24:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_HANG_OUT_STREET", 0, 1); break;
			case 25:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_HIKER_STANDING", 0, 1); break;
			case 26:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_HUMAN_STATUE", 0, 1); break;
			case 27:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_JANITOR", 0, 1); break;
			case 28:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_JOG_STANDING", 0, 1); break;
			case 29:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_LEANING", 0, 1); break;
			case 30:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MAID_CLEAN", 0, 1); break;
			case 31:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MUSCLE_FLEX", 0, 1); break;
			case 32:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MUSCLE_FREE_WEIGHTS", 0, 1); break;
			case 33:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MUSICIAN", 0, 1); break;
			case 34:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_PAPARAZZI", 0, 1); break;
			case 35:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_PARTYING", 0, 1); break;
			case 36:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_PICNIC", 0, 1); break;
			case 37:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_PROSTITUTE_HIGH_CLASS", 0, 1); break;
			case 38:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_PROSTITUTE_LOW_CLASS", 0, 1); break;
			case 39:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_PUSH_UPS", 0, 1); break;
			case 40:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SEAT_LEDGE", 0, 1); break;
			case 41:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SEAT_LEDGE_EATING", 0, 1); break;
			case 42:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SEAT_STEPS", 0, 1); break;
			case 43:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SEAT_WALL", 0, 1); break;
			case 44:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SEAT_WALL_EATING", 0, 1); break;
			case 45:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SEAT_WALL_TABLET", 0, 1); break;
			case 46:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SECURITY_SHINE_TORCH", 0, 1); break;
			case 47:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SIT_UPS", 0, 1); break;
			case 48:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SMOKING", 0, 1); break;
			case 49:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SMOKING_POT", 0, 1); break;
			case 50:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_STAND_FIRE", 0, 1); break;
			case 51:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_STAND_FISHING", 0, 1); break;
			case 52:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_STAND_IMPATIENT", 0, 1); break;
			case 53:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_STAND_IMPATIENT_UPRIGHT", 0, 1); break;
			case 54:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_STAND_MOBILE", 0, 1); break;
			case 55:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_STAND_MOBILE_UPRIGHT", 0, 1); break;
			case 56:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_STRIP_WATCH_STAND", 0, 1); break;
			case 57:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_STUPOR", 0, 1); break;
			case 58:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SUNBATHE", 0, 1); break;
			case 59:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SUNBATHE_BACK", 0, 1); break;
			case 60:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SUPERHERO", 0, 1); break;
			case 61:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_SWIMMING", 0, 1); break;
			case 62:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_TENNIS_PLAYER", 0, 1); break;
			case 63:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_TOURIST_MAP", 0, 1); break;
			case 64:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_TOURIST_MOBILE", 0, 1); break;
			case 65:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_VEHICLE_MECHANIC", 0, 1); break;
			case 66:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_WELDING", 0, 1); break;
			case 67:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_WINDOW_SHOP_BROWSE", 0, 1); break;
			case 68:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_YOGA", 0, 1); break;
			case 69:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_BOAR_GRAZING", 0, 1); break;
			case 70:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_CAT_SLEEPING_GROUND", 0, 1); break;
			case 71:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_CAT_SLEEPING_LEDGE", 0, 1); break;
			case 72:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_COW_GRAZING", 0, 1); break;
			case 73:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_COYOTE_HOWL", 0, 1); break;
			case 74:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_COYOTE_REST", 0, 1); break;
			case 75:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_COYOTE_WANDER", 0, 1); break;
			case 76:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_CHICKENHAWK_FEEDING", 0, 1); break;
			case 77:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_CHICKENHAWK_STANDING", 0, 1); break;
			case 78:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_CORMORANT_STANDING", 0, 1); break;
			case 79:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_CROW_FEEDING", 0, 1); break;
			case 80:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_CROW_STANDING", 0, 1); break;
			case 81:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_DEER_GRAZING", 0, 1); break;
			case 82:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_DOG_BARKING_ROTTWEILER", 0, 1); break;
			case 83:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_DOG_BARKING_RETRIEVER", 0, 1); break;
			case 84:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_DOG_BARKING_SHEPHERD", 0, 1); break;
			case 85:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_DOG_SITTING_ROTTWEILER", 0, 1); break;
			case 86:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_DOG_SITTING_RETRIEVER", 0, 1); break;
			case 87:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_DOG_SITTING_SHEPHERD", 0, 1); break;
			case 88:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_DOG_BARKING_SMALL", 0, 1); break;
			case 89:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_DOG_SITTING_SMALL", 0, 1); break;
			case 90:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_FISH_IDLE", 0, 1); break;
			case 91:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_GULL_FEEDING", 0, 1); break;
			case 92:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_GULL_STANDING", 0, 1); break;
			case 93:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HEN_PECKING", 0, 1); break;
			case 94:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HEN_STANDING", 0, 1); break;
			case 95:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_MOUNTAIN_LION_REST", 0, 1); break;
			case 96:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_MOUNTAIN_LION_WANDER", 0, 1); break;
			case 97:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_PIG_GRAZING", 0, 1); break;
			case 98:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_PIGEON_FEEDING", 0, 1); break;
			case 99:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_PIGEON_STANDING", 0, 1); break;
			case 100:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_RABBIT_EATING", 0, 1); break;
			case 101:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_RATS_EATING", 0, 1); break;
			case 102:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_SHARK_SWIM", 0, 1); break;
			case 103:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_BIRD_IN_TREE", 0, 1); break;
			case 104:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_BIRD_TELEGRAPH_POLE", 0, 1); break;
			case 105:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_ATM", 0, 1); break;
			case 106:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_BBQ", 0, 1); break;
			case 107:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_BUM_BIN", 0, 1); break;
			case 108:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_BUM_SHOPPING_CART", 0, 1); break;
			case 109:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_MUSCLE_CHIN_UPS", 0, 1); break;
			case 110:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_MUSCLE_CHIN_UPS_ARMY", 0, 1); break;
			case 111:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_MUSCLE_CHIN_UPS_PRISON", 0, 1); break;
			case 112:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_PARKING_METER", 0, 1); break;
			case 113:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_ARMCHAIR", 0, 1); break;
			case 114:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_BAR", 0, 1); break;
			case 115:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_BENCH", 0, 1); break;
			case 116:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_BENCH_DRINK", 0, 1); break;
			case 117:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_BENCH_DRINK_BEER", 0, 1); break;
			case 118:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_BENCH_FOOD", 0, 1); break;
			case 119:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_BUS_STOP_WAIT", 0, 1); break;
			case 120:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_CHAIR", 0, 1); break;
			case 121:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_CHAIR_DRINK", 0, 1); break;
			case 122:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_CHAIR_DRINK_BEER", 0, 1); break;
			case 123:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_CHAIR_FOOD", 0, 1); break;
			case 124:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_CHAIR_UPRIGHT", 0, 1); break;
			case 125:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_CHAIR_MP_PLAYER", 0, 1); break;
			case 126:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_COMPUTER", 0, 1); break;
			case 127:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_DECKCHAIR", 0, 1); break;
			case 128:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_DECKCHAIR_DRINK", 0, 1); break;
			case 129:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS", 0, 1); break;
			case 130:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS_PRISON", 0, 1); break;
			case 131:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_SEWING", 0, 1); break;
			case 132:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_STRIP_WATCH", 0, 1); break;
			case 133:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_SEAT_SUNLOUNGER", 0, 1); break;
			case 134:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_STAND_IMPATIENT", 0, 1); break;
			case 135:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "CODE_HUMAN_COWER", 0, 1); break;
			case 136:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "CODE_HUMAN_CROSS_ROAD_WAIT", 0, 1); break;
			case 137:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "CODE_HUMAN_PARK_CAR", 0, 1); break;
			case 138:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_MOVIE_BULB", 0, 1); break;
			case 139:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "PROP_HUMAN_MOVIE_STUDIO_LIGHT", 0, 1); break;
			case 140:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "CODE_HUMAN_MEDIC_KNEEL", 0, 1); break;
			case 141:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "CODE_HUMAN_MEDIC_TEND_TO_DEAD", 0, 1); break;
			case 142:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "CODE_HUMAN_MEDIC_TIME_OF_DEATH", 0, 1); break;
			case 143:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "CODE_HUMAN_POLICE_CROWD_CONTROL", 0, 1); break;
			case 144:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "CODE_HUMAN_POLICE_INVESTIGATE", 0, 1); break;
			case 145:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "CODE_HUMAN_STAND_COWER", 0, 1); break;
			case 146:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "EAR_TO_TEXT", 0, 1); break;
			case 147:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "EAR_TO_TEXT_FAT", 0, 1); break;
			case 148:
				AI::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), "WORLD_HUMAN_MUSICIAN", 0, 2); break;
			}
		}
		break;
#pragma endregion

#pragma region Movement_Type
		case Mouevement_Type:
		{
			Menu::Title("");
			Menu::SmallTitle("Movement Style");
			AddWalkingTyle("Male", "move_m@generic");
			AddWalkingTyle("Female", "move_f@generic");
			if (Menu::Option("Clear Movement Style"))
			{
				ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), 0);
				AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
			}
		
		}
		break;
#pragma endregion

#pragma region ANIMATIONS
		case Animation:
		{
			Menu::Title("");
			Menu::SmallTitle("Animations");
			Menu::Float("Animation Speed", animationspeed, 0, 100);
			Menu::MenuOption("Movement Style", Mouevement_Type);
            Menu::MenuOption("Sport Animation", Sport_Options);
			Menu::MenuOption("Sex Animation", Sex_Options);
			Menu::MenuOption("Dance Animation", Dance_Options);
			Menu::MenuOption("Super Hero Animation", SuperHero_Options);
			Menu::MenuOption("Misc Animation", Misc_OptionsAnims);
			if (Menu::Option("Stop Animation"))
			{
				ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), 0);
				AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
			}
	    }
	break;
#pragma endregion

#pragma region Dance
		case Dance_Options:
		{
			Menu::Title("");
			Menu::SmallTitle("Dance");
			if (Menu::Option("Pole Dance"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "mini@strip_club@pole_dance@pole_dance1", "pd_dance_01");
			}
			if (Menu::Option("Pole Dance 2"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "mini@strip_club@pole_dance@pole_dance2", "pd_dance_02");
			}
			if (Menu::Option("Pole Dance 3"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "mini@strip_club@pole_dance@pole_dance3", "pd_dance_03");

			}
			if (Menu::Option("Private Dance"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "mini@strip_club@private_dance@part1", "priv_dance_p1");
			}
			if (Menu::Option("Tap Dancing Heaven"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "special_ped@mountain_dancer@monologue_2@monologue_2a", "mnt_dnc_angel");
			}
			if (Menu::Option("Buttwag Dance"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "special_ped@mountain_dancer@monologue_3@monologue_3a", "mnt_dnc_buttwag");
			}
			if (Menu::Option("Verse Dance"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "special_ped@mountain_dancer@monologue_1@monologue_1a", "mnt_dnc_verse");
			}
			if (Menu::Option("Heaven Dance"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "special_ped@mountain_dancer@monologue_4@monologue_4a", "mtn_dnc_if_you_want_to_get_to_heaven");
			}
			if (Menu::Option("Heaven Dance"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "mini@strip_club@pole_dance@stage_enter ", "stage_enter");
			}
		}
		break;
#pragma endregion

#pragma region Super Hero
		case SuperHero_Options:
		{
			Menu::Title("");
			Menu::SmallTitle("Super Hero");
			if (Menu::Option("Space Pistol"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "amb@world_human_superhero@male@space_pistol@base", "base");
			}
			if (Menu::Option("Space Rifle"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "amb@world_human_superhero@male@space_rifle@base", "base");
			}

		}
		break;
#pragma endregion

#pragma region Misc Animations
		case Misc_OptionsAnims:
		{
			Menu::Title("");
			Menu::SmallTitle("Misc Animations");
			if (Menu::Option("Tazer"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "ragdoll@human", "electrocute");
			}
			if (Menu::Option("Stun Fire"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "ragdoll@human", "on_fire");
			}
			if (Menu::Option("Electrocute"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "stungun@standing", "damage");
			}
			if (Menu::Option("Wave Yo Arms"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "random@car_thief@victimpoints_ig_3", "arms_waving");
			}
			if (Menu::Option("Cop Kneeling Arrest"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "random@car_thief@victimpoints_ig_3", "arms_waving");
			}
			if (Menu::Option("Wave Yo Arms"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "random@car_thief@victimpoints_ig_3", "arms_waving");

			}
			if (Menu::Option("Cop Hands Up"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "random@arrests", "kneeling_arrest_idle");

			}
		}
		break;
#pragma endregion

#pragma region Sex Animations
		case Sex_Options: {
			Menu::Title("");
			Menu::SmallTitle("Sex");
			if (Menu::Option("Fuck"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "rcmpaparazzo_2", "shag_loop_a");
			}
			if (Menu::Option("Fuck 2"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "rcmpaparazzo_2", "shag_loop_poppy");
			}
			if (Menu::Option("Car Sex [MALE]"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "ODDJOBS@ASSASSINATE@VICE@SEX", "frontseat_carsex_loop_m");

			}
			if (Menu::Option("Car Sex [FEMALE]"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "ODDJOBS@ASSASSINATE@VICE@SEX", "frontseat_carsex_loop_f");
			}
			if (Menu::Option("Drunk Car Sex [MALE]"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "random@drunk_driver_2", "cardrunksex_loop_m");
			}
			if (Menu::Option("Drunk Car Sex [FEMALE]"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "random@drunk_driver_2", "cardrunksex_loop_f");
			}
			if (Menu::Option("Prostitue Male Sex"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "mini@prostitutes@sexnorm_veh", "sex_loop_male");
			}
			if (Menu::Option("Prostitue Female Sex"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "mini@prostitutes@sexnorm_veh", "sex_loop_prostitute");
			}
			if (Menu::Option("Prostitue Male BJ"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "mini@prostitutes@sexnorm_veh", "bj_loop_male");
			}
			if (Menu::Option("Prostitue Female BJ"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "mini@prostitutes@sexnorm_veh", "bj_loop_prostitute");
			}
		}
		break;
#pragma endregion

#pragma region Sport Animations
		case Sport_Options:
		{
			Menu::Title("");
			Menu::SmallTitle("Sport Animations");
			if (Menu::Option("Situps"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "amb@world_human_sit_ups@male@base", "base");
			}
			if (Menu::Option("Pushups"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "amb@world_human_push_ups@male@base", "base");
			}
			if (Menu::Option("Bench Press"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "amb@prop_human_seat_muscle_bench_press@base", "base");

			}
			if (Menu::Option("Chin Ups"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "amb@prop_human_muscle_chin_ups@male@base", "base");
			}
			if (Menu::Option("Free Weights"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "amb@world_human_muscle_free_weights@male@barbell@base", "base");
			}
			if (Menu::Option("Flex Side"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "amb@world_human_muscle_flex@arms_at_side@base", "base");
			}
			if (Menu::Option("Flex Front"))
			{
				doAnimation1(PLAYER::PLAYER_PED_ID(), "amb@world_human_muscle_flex@arms_in_front@base", "base");
			}
		}
		break;
#pragma endregion

#pragma region Player Effects
		case effects_me:
		{
			Menu::Title("");
			Menu::SmallTitle("Player Effects");
			Menu::MenuOption("Player Visions", vis_play_me);
			Menu::MenuOption("Looped FX", loopedPTfx);
			if (Menu::Option("Clown Appears"))
			{
				Me::PTFXCALL("scr_rcbarry2", "scr_rcbarry2", "scr_clown_appears");
			}
			if (Menu::Option("Firework"))
			{
				Me::PTFXCALL("scr_indep_fireworks", "scr_indep_fireworks", "scr_indep_firework_trailburst");
			}
			if (Menu::Option("Banknotes"))
			{
				Me::PTFXCALL("scr_ornate_heist", "scr_ornate_heist", "scr_heist_ornate_banknotes");
			}
			if (Menu::Option("Truck Crash"))
			{
				Me::PTFXCALL("scr_fbi4", "scr_fbi4", "scr_fbi4_trucks_crash");
			}
			if (Menu::Option("Alien"))
			{
				Me::PTFXCALL("scr_rcbarry1", "scr_rcbarry1", "scr_alien_disintegrate");
			}
			if (Menu::Option("Electric Box"))
			{
				Me::PTFXCALL("scr_agencyheistb", "scr_agencyheistb", "scr_agency3b_elec_box");
			}
			if (Menu::Option("Water Splash"))
			{
				Me::PTFXCALL("scr_fbi5a", "scr_fbi5a", "scr_fbi5_ped_water_splash");
			}
			if (Menu::Option("Bubbles"))
			{
				Me::PTFXCALL("scr_fbi5a", "scr_fbi5a", "water_splash_ped_bubbles");
			}
			if (Menu::Option("Blood Entry"))
			{
				Me::PTFXCALL("scr_finalec2", "scr_finalec2", "scr_finale2_blood_entry");
			}
			if (Menu::Option("Dirt Throw"))
			{
				Me::PTFXCALL("core_snow", "core_snow", "cs_mich1_spade_dirt_throw");
			}
			if (Menu::Option("Ped Sliced"))
			{
				Me::PTFXCALL("scr_michael2", "scr_michael2", "scr_abattoir_ped_sliced");
			}
			if (Menu::Option("Camera"))
			{
				Me::PTFXCALL("scr_rcpaparazzo1", "scr_rcpaparazzo1", "scr_rcpap1_camera");
			}
			if (Menu::Option("Meth Smoke"))
			{
				Me::PTFXCALL("scr_familyscenem", "scr_familyscenem", "scr_meth_pipe_smoke");
			}
			if (Menu::Option("Burial Dirt"))
			{
				Me::PTFXCALL("scr_reburials", "scr_reburials", "scr_burial_dirt");
			}
		}
		break;
#pragma endregion

#pragma region Looped FX
		case loopedPTfx:
		{
			Menu::Title(""); //Just import banner image - text in this wont appear :=)
			Menu::SmallTitle("Looped Effects");
			Menu::Toggle("Clown Effects", Features::ClownLoop);
			Menu::Toggle("Firework", Features::fireworkloop);
			Menu::Toggle("Alien 1", Features::alien1);
			Menu::Toggle("Alien 2", Features::alien2);
			Menu::Toggle("Electric", Features::electric);
			Menu::Toggle("Water Splash", Features::watereffect);
			Menu::Toggle("Smoke", Features::smokeeffect);
		}
		break;
#pragma endregion

#pragma region Player Visions
		case vis_play_me:
		{
			Menu::Title("");
			Menu::SmallTitle("Player Visions");
			Menu::Toggle("Night Vision", NewOption::NightLookOnMe);
			Menu::Toggle("Thermal Vision", NewOption::thermal_vision);
		}
		break;
#pragma endregion

#pragma region recovery
		case recovery:
		{
			Menu::Title("Recovery");
			Menu::SmallTitle("Recovery");
			Menu::MenuOption("advanced recovery", adnv_recoverty);
			if (Menu::Int("choose level", rpvalue, 0, 8000))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					rpvalue = NumberKeyboard();
				}
			}
			if (Menu::Option("Apply Level"))
			{
				notifyBottom("~g~change session to apply level");
				SetRank(rpvalue);
			}
			Menu::Toggle("RP Loop", Features::RPLoop, [] { Features::rpLoop(Features::RPLoop); });
			Menu::MenuBreak("~f~[Money Options]");
			Menu::Toggle("Circle Drop", cyrclenew);
			Menu::Toggle("Money Drop", moneyDrop);
			if (Menu::Option("Unlock Everything In Game"))
			{
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMRACEWORLDRECHOLDER"), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_ENEMYDRIVEBYKILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_USJS_COMPLETED"), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_USJS_FOUND"), 50, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMWINALLRACEMODES"), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMWINEVERYGAMEMODE"), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_DB_PLAYER_KILLS"), 1000, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_KILLS_PLAYERS"), 1000, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMHORDWAVESSURVIVE"), 21, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TDM_MVP"), 60, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_HOLD_UP_SHOPS"), 20, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_RACES_WON"), 101, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_NO_ARMWRESTLING_WINS"), 21, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMATTGANGHQ"), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMBBETWIN"), 50000, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 51, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMFULLYMODDEDCAR"), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_TOTALKILLS"), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_DM_TOTAL_DEATHS"), 412, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_PLAYER_HEADSHOTS"), 623, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 63, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TDM_WINS"), 13, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_GTA_RACES_WON"), 12, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_GOLF_WON"), 2, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_TG_WON"), 2, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_RT_WON"), 2, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_CT_WON"), 2, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_GRAN_WON"), 2, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TENNIS_WON"), 2, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TENNIS_MATCHES_WON"), 2, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_WON"), 101, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_LOST"), 36, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_25_KILLS_STICKYBOMBS"), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_50_KILLS_GRENADES"), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS"), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_AWD_20_KILLS_MELEE"), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MOLOTOV_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CMBTPISTOL_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_PISTOL50_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_APPISTOL_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MICROSMG_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SMG_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ASLTSMG_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ASLTRIFLE_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CRBNRIFLE_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ADVRIFLE_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MG_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CMBTMG_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ASLTMG_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_PUMP_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SAWNOFF_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_BULLPUP_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_ASLTSHTGN_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SNIPERRFL_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_HVYSNIPER_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_GRNLAUNCH_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_RPG_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MINIGUNS_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_SMKGRENADE_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_STKYBMB_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_MOLOTOV_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_8"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_9"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_10"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_OUTFIT"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_5"), -1, 1);;
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_6"), -1, 1);;
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_8"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_9"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_10"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_OUTFIT"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TORSO"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL2_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_DECL"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TORSO"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL2_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_DECL"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), 100, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), 100, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMRACEWORLDRECHOLDER"), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_ENEMYDRIVEBYKILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_USJS_COMPLETED"), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_USJS_FOUND"), 50, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMWINALLRACEMODES"), 1, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMWINEVERYGAMEMODE"), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_DB_PLAYER_KILLS"), 1000, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_KILLS_PLAYERS"), 1000, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMHORDWAVESSURVIVE"), 21, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_TDM_MVP"), 60, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_HOLD_UP_SHOPS"), 20, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_RACES_WON"), 101, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_NO_ARMWRESTLING_WINS"), 21, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMATTGANGHQ"), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMBBETWIN"), 50000, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_DM_WINS"), 51, 1);
				STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FMFULLYMODDEDCAR"), 1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_DM_TOTALKILLS"), 500, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_DM_TOTAL_DEATHS"), 412, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_PLAYER_HEADSHOTS"), 623, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_DM_WINS"), 63, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_TDM_WINS"), 13, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_GTA_RACES_WON"), 12, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_GOLF_WON"), 2, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_TG_WON"), 2, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_RT_WON"), 2, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_CT_WON"), 2, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_SHOOTRANG_GRAN_WON"), 2, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_FM_TENNIS_WON"), 2, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_TENNIS_MATCHES_WON"), 2, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_TOTAL_RACES_WON"), 101, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MPPLY_TOTAL_RACES_LOST"), 36, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_25_KILLS_STICKYBOMBS"), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_50_KILLS_GRENADES"), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_GRENADE_ENEMY_KILLS"), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_AWD_20_KILLS_MELEE"), 50, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MOLOTOV_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CMBTPISTOL_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_PISTOL50_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_APPISTOL_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MICROSMG_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SMG_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_ASLTSMG_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_ASLTRIFLE_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CRBNRIFLE_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_ADVRIFLE_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MG_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CMBTMG_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_ASLTMG_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_PUMP_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SAWNOFF_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_BULLPUP_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_ASLTSHTGN_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SNIPERRFL_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_HVYSNIPER_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_GRNLAUNCH_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_RPG_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MINIGUNS_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_GRENADE_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_SMKGRENADE_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_STKYBMB_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_MOLOTOV_ENEMY_KILLS"), 600, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_HAIR_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_JBIB_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_LEGS_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_FEET_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_BERD_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_8"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_9"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_PROPS_10"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_OUTFIT"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_5"), -1, 1);;
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_HAIR_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_JBIB_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_6"), -1, 1);;
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_LEGS_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_FEET_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_BERD_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_8"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_9"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_PROPS_10"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_OUTFIT"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_TORSO"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_SPECIAL2_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_DECL"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_TEETH"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_TEETH_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_AVAILABLE_TEETH_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_TORSO"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_3"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_4"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_5"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_6"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL_7"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL2"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_SPECIAL2_1"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_DECL"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP1_CLTHS_ACQUIRED_TEETH"), -1, 1);
				STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MP0_REV_DA_IN_POSSESSION"), -1, 1);
}




			
			if (Menu::Option("~g~15M STEALTH"))
			{
				int money = 312105838;
				Any transactionID = money;
				if (UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&transactionID, 1474183246, -1586170317, 1445302971, 15000000, 4))
					UNK3::_NETWORK_SHOP_CHECKOUT_START(transactionID);

				Features::TimePD1 = timeGetTime();



			}
			if (Menu::Option("~g~10M STEALTH"))
			{
				int money = 312105838;
				Any transactionID = money;
				if (UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&transactionID, 1474183246, -1586170317, 1445302971, 10000000, 4))
					UNK3::_NETWORK_SHOP_CHECKOUT_START(transactionID);

				Features::TimePD1 = timeGetTime();

			}
			if (Menu::Option("~g~5M STEALTH"))
			{
				int money = 312105838;
				Any transactionID = money;
				if (UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&transactionID, 1474183246, -1586170317, 1445302971, 5000000, 4))
					UNK3::_NETWORK_SHOP_CHECKOUT_START(transactionID);

				Features::TimePD1 = timeGetTime();
			}
			if (Menu::Option("~g~3M STEALTH"))
			{
				int money = 312105838;
				Any transactionID = money;
				if (UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&transactionID, 1474183246, -1586170317, 1445302971, 300000, 4))
					UNK3::_NETWORK_SHOP_CHECKOUT_START(transactionID);

				Features::TimePD1 = timeGetTime();
			}
			if (Menu::Option("~g~1.2M STEALTH"))
			{
				int money = 312105838;
				Any transactionID = money;
				if (UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&transactionID, 1474183246, -1586170317, 1445302971, 1200000, 4))
					UNK3::_NETWORK_SHOP_CHECKOUT_START(transactionID);

				Features::TimePD1 = timeGetTime();
			}
			if (Menu::Option("~g~600K STEALTH"))
			{
				int money = 312105838;
				Any transactionID = money;
				if (UNK3::_NETWORK_SHOP_BEGIN_SERVICE(&transactionID, 1474183246, -1586170317, 1445302971, 600000, 4))
					UNK3::_NETWORK_SHOP_CHECKOUT_START(transactionID);

				Features::TimePD1 = timeGetTime();
			}
		}
		break;//yhe
#pragma endregion

#pragma region Advanced Recovery
		case adnv_recoverty:
		{
			Menu::Title("");
			Menu::SmallTitle("Advanced Recovery");
			if (Menu::Option("Set Kills")) 
			{
				Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MPPLY_KILLS_PLAYERS"), NumberKeyboard(), 1);
			}
			if (Menu::Option("Set Deaths")) 
			{
				Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MPPLY_DEATHS_PLAYER"), NumberKeyboard(), 1);
			}
			if (Menu::Option("Unlock Everyting"))
			{
				UnlockEveryUn();
			}
			if (Menu::Option("Max Your Stats")) 
			{
				Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, true);
				Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, true);
				Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, true);
				Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, true);
				Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, true);
				Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, true);
				Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, true);
			}
			if (Menu::Option("One Million Snacks"))
			{
				Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_YUM_SNACKS"), 1000000, 1);

				Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_HEALTH_SNACKS"), 1000000, 1);

				Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_NO_BOUGHT_EPIC_SNACKS"), 1000000, 1);

				Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_NUMBER_OF_ORANGE_BOUGHT"), 1000000, 1);

				Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_CIGARETTES_BOUGHT"), 1000000, 1);
			}
			if (Menu::Option("One Million Body Armor"))
			{
				Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_1_COUNT"), 1000000, 1);

				Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_2_COUNT"), 1000000, 1);

				Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_3_COUNT"), 1000000, 1);

				Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_4_COUNT"), 1000000, 1);

				Hooking::stat_set_int(GAMEPLAY::GET_HASH_KEY("MP0_MP_CHAR_ARMOUR_5_COUNT"), 1000000, 1);
			}
			if (Menu::Option("Remove Badsport")) {
				STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MPPLY_OVERALL_BADSPORT"), 0.0f, TRUE);
				STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MPPLY_DESTROYED_PVEHICLES"), 0, TRUE);
				STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MPPLY_BADSPORT_MESSAGE"), 0, TRUE);
			}
		}
		break;
#pragma endregion

#pragma region Outfit Creator - editor
		case out_create:
		{
			Menu::Title("");
			Menu::SmallTitle("Outfit Editor");
			if (Menu::Int("Hats", Recovery::Face_, 0, 255)) 
			{ 
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) 
				{
					Recovery::Face_ = NumberKeyboard();
				}
				Recovery::changeClothes("HATS", Recovery::Face_, Recovery::FaceTex_); 
			}
			if (Menu::Int("Hats Texture", Recovery::FaceTex_, 0, 255)) 
			{ 
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					Recovery::Face_ = NumberKeyboard();
				}
				Recovery::changeClothes("HATS", Recovery::Face_, Recovery::FaceTex_); 
			}
			if (Menu::Int("Glasses", Recovery::Glasses_, 0, 255)) 
			{ 
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					Recovery::Glasses_ = NumberKeyboard();
				}
				Recovery::changeClothes("GLASSES", Recovery::Glasses_, Recovery::GlassesTex_); 
			}
			if (Menu::Int("Glasses Texture", Recovery::GlassesTex_, 0, 255)) 
			{ 
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					Recovery::GlassesTex_ = NumberKeyboard();
				}
				Recovery::changeClothes("GLASSES", Recovery::Glasses_, Recovery::GlassesTex_); 
			}
			if (Menu::Int("Ears", Recovery::Ears_, 0, 255)) 
			{ 
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					Recovery::Ears_ = NumberKeyboard();
				}
				Recovery::changeClothes("EARS", Recovery::Ears_, Recovery::EarsTex_); 
			}
			if (Menu::Int("Ears Texture", Recovery::EarsTex_, 0, 255)) 
			{ 
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					Recovery::Ears_ = NumberKeyboard();
				}
				Recovery::changeClothes("EARS", Recovery::Ears_, Recovery::EarsTex_); 
			}
			if (Menu::Int("Torso invisible", Recovery::Torso_, 0, 255)) 
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					Recovery::Torso_ = NumberKeyboard();
				}
				Recovery::changeClothes("TORSO", Recovery::Torso_, Recovery::TorsoTex_); 
			}
			if (Menu::Int("Torso invisible Texture", Recovery::TorsoTex_, 0, 255)) 
			{ 
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					Recovery::TorsoTex_ = NumberKeyboard();
				}
				Recovery::changeClothes("TORSO", Recovery::Torso_, Recovery::TorsoTex_); 
			}
			if (Menu::Int("Torso", Recovery::Torso2_, 0, 255)) 
			{ 
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					Recovery::Torso2_ = NumberKeyboard();
				}
				Recovery::changeClothes("TORSO2", Recovery::Torso2_, Recovery::Torso2Tex_); 
			}
			if (Menu::Int("Torso Texture", Recovery::Torso2Tex_, 0, 255)) 
			{ 
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					Recovery::Torso2Tex_ = NumberKeyboard();
				}
				Recovery::changeClothes("TORSO2", Recovery::Torso2_, Recovery::Torso2Tex_); 
			}
			if (Menu::Int("Legs", Recovery::Legs_, 0, 255)) 
			{ 
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					Recovery::Legs_ = NumberKeyboard();
				}
				Recovery::changeClothes("LEGS", Recovery::Legs_, Recovery::LegsTex_); 
			}
			if (Menu::Int("Legs Texture", Recovery::LegsTex_, 0, 255)) 
			{ 
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					Recovery::LegsTex_ = NumberKeyboard();
				}
				Recovery::changeClothes("LEGS", Recovery::Legs_, Recovery::LegsTex_); 
			}
			if (Menu::Int("Parachutes", Recovery::Hands_, 0, 255)) 
			{ 
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					Recovery::Hands_ = NumberKeyboard();
				}
				Recovery::changeClothes("HANDS", Recovery::Hands_, Recovery::HandsTex_); 
			}
			if (Menu::Int("Parachutes Texture", Recovery::HandsTex_, 0, 255)) 
			{ 
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					Recovery::HandsTex_ = NumberKeyboard();
				}
				Recovery::changeClothes("HANDS", Recovery::Hands_, Recovery::HandsTex_); 
			}
			if (Menu::Int("Shoes", Recovery::Watches_, 0, 255))
			{ 
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					Recovery::Watches_ = NumberKeyboard();
				}
				Recovery::changeClothes("SHOES", Recovery::Watches_, Recovery::WatchesTex_); 
			}
			if (Menu::Int("Shoes Texture", Recovery::WatchesTex_, 0, 255)) 
			{ 
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					Recovery::WatchesTex_ = NumberKeyboard();
				}
				Recovery::changeClothes("SHOES", Recovery::Watches_, Recovery::WatchesTex_); 
			}
			if (Menu::Int("Special 1", Recovery::Special1_, 0, 255)) 
			{ 
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					Recovery::Special1_ = NumberKeyboard();
				}
				Recovery::changeClothes("SPECIAL1", Recovery::Special1_, Recovery::Special1Tex_); 
			}
			if (Menu::Int("Special 1 Texture", Recovery::Special1Tex_, 0, 255)) 
			{ 
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					Recovery::Special1Tex_ = NumberKeyboard();
				}
				Recovery::changeClothes("SPECIAL1", Recovery::Special1_, Recovery::Special1Tex_); 
			}
			if (Menu::Int("Special 2", Recovery::Special2_, 0, 255)) 
			{ 
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					Recovery::Special2_ = NumberKeyboard();
				}
				Recovery::changeClothes("SPECIAL2", Recovery::Special2_, Recovery::Special2Tex_); 
			}
			if (Menu::Int("Special 2 Texture", Recovery::Special2Tex_, 0, 255)) 
			{ 
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					Recovery::Special2Tex_ = NumberKeyboard();
				}
				Recovery::changeClothes("SPECIAL2", Recovery::Special2_, Recovery::Special2Tex_); 
			}
			if (Menu::Int("Special 3", Recovery::Special3_, 0, 255)) 
			{ 
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					Recovery::Special3_ = NumberKeyboard();
				}
				Recovery::changeClothes("SPECIAL3", Recovery::Special3_, Recovery::Special3Tex_); 
			}
			if (Menu::Int("Special 3 Texture", Recovery::Special3Tex_, 0, 255)) 
			{ 
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					Recovery::Special3Tex_ = NumberKeyboard();
				}
				Recovery::changeClothes("SPECIAL3", Recovery::Special3_, Recovery::Special3Tex_); 
			}
		}
		break;
#pragma endregion

#pragma region men outfits
		case men_outf:
		{
			Menu::Title("");
			Menu::SmallTitle("Men Outfits");
		}
		break;
#pragma endregion

#pragma region women outfits
		case women_outf:
		{
			Menu::Title("");
			Menu::SmallTitle("Women Outfits");
		}
		break;
#pragma endregion

#pragma region weps
		case weps:
		{
			Menu::Title("");
			Menu::SmallTitle("Weapon");
			Menu::MenuOption("Spoofed Killer", SpoofKill);
			if (Menu::Option("Give all Weapons"))
			{
				uint Weapons[]{ 0xAF3696A1, 0x476BF155, 0xB62D1F670, 0xDFE37640, 0xC1B3C3D1, 0x99B507EA, 0x678B81B1, 0x4E875F73, 0x958A4A8F, 0x440E4788, 0x84BD7BFD, 0x1B06D571, 0x5EF9FEC4, 0x22D8FE39, 0x99AEEB3B, 0x13532244, 0x2BE6766B, 0xEFE7E2DF, 0xBFEFFF6D, 0x83BF0278, 0xAF113F99, 0x9D07F764, 0x7FD62962, 0x1D073A89, 0x7846A318, 0xE284C527, 0x9D61E50F, 0x3656C8C1, 0x05FC3C11, 0x0C472FE2, 0x33058E22, 0xA284510B, 0x4DD2DC56, 0xB1CA77B1, 0x687652CE, 0x42BF8A85, 0x93E220BD, 0x2C3731D9, 0xFDBC8A50, 0x24B17070, 0x060EC506, 0x34A67B97, 0xFDBADCED, 0x23C9F95C, 0x497FACC3, 0xF9E6AA4B, 0x61012683, 0xC0A3098D, 0xD205520E, 0xBFD21232, 0x7F229F94, 0x92A27487, 0x083839C4, 0x7F7497E5, 0xA89CB99E, 0x3AABBBAA, 0xC734385A, 0x787F0BB, 0x47757124, 0xD04C944D, GAMEPLAY::GET_HASH_KEY("WEAPON_HATCHET"), GAMEPLAY::GET_HASH_KEY("WEAPON_RAILGUN") };
				for (int i = 0; i < (sizeof(Weapons) / 4); i++)
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), Weapons[i], 9999, 1);
			}
			if (Menu::Option("Give all mk2 weapons"))
			{

				uint Weapons[] = { GAMEPLAY::GET_HASH_KEY("weapon_revolver_mk2"), GAMEPLAY::GET_HASH_KEY("weapon_snspistol_mk2"), GAMEPLAY::GET_HASH_KEY("weapon_smg_mk2"), GAMEPLAY::GET_HASH_KEY("weapon_pumpshotgun_mk2"), GAMEPLAY::GET_HASH_KEY("weapon_assaultrifle_mk2"), GAMEPLAY::GET_HASH_KEY("weapon_carbinerifle_mk2"), GAMEPLAY::GET_HASH_KEY("weapon_specialcarbine_mk2"), GAMEPLAY::GET_HASH_KEY("weapon_bullpuprifle_mk2"), GAMEPLAY::GET_HASH_KEY("weapon_combatmg_mk2"), GAMEPLAY::GET_HASH_KEY("weapon_heavysniper_mk2"), GAMEPLAY::GET_HASH_KEY("weapon_marksmanrifle_mk2"), };
				for (int i = 0; i < (sizeof(Weapons) / 4); i++)
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), Weapons[i], 9999, 1);

			}
			Menu::Toggle("Unlimited Ammo", unlim);
			Menu::MenuBreak("[Weapon Impacts]");
			Menu::Toggle("Explosive Ammo(Small)", xpx_ammo);
			Menu::Toggle("Explosive Ammo(Normal)", xpx_ammo1);
			Menu::Toggle("Explosive Ammo(Big)", xpx_ammo2);
			Menu::Toggle("Molotov Gun", molo_gun);
			Menu::Toggle("Flare Gun", flare_gun);
			Menu::Toggle("Smoke Gun", smoke_gun);
			Menu::Toggle("Airstrike Gun", WeaponMod::airstrikeWep);
			Menu::MenuBreak("[Weapon Mods]");//Title in middle of tab - break
			Menu::Toggle("Delete Gun", delete_gun);
			Menu::Toggle("Teleport Gun", teleport_gun);
			Menu::Toggle("Money Gun", moneyGunme);
			Menu::Toggle("Gravity Gun", Features::GravityGun, [] { Features::gravitygun(Features::GravityGun); });
			Menu::Toggle("Aimbot", AimbotBool);


		}
		break;
#pragma endregion

#pragma region New Teleport
		case new_tele:
		{
			Menu::Title("");
			Menu::SmallTitle("Teleport");
			Menu::Toggle("Free Cam", Features::freeT, [] { Features::freeCamt(Features::freeT); });
			if (Menu::Option("Waypoint"))
			{
				MySelf::Teleport_To_Blip();
			}
			if (Menu::Option("2 Meter Infront"))
			{
				Vector3 Coords;
				Coords.x = MyCurentLoc.x - 2.5f; Coords.y = MyCurentLoc.y; Coords.z = MyCurentLoc.z;
				TPto(Coords);
			}
			Menu::MenuOption("Standard", std_loc);
			Menu::MenuOption("Online", online_loc);
			Menu::MenuOption("Towers", tower_loc);
			Menu::MenuOption("Shops", shop_loc);
			Menu::MenuOption("Nightclubs", night_loc);
			Menu::MenuBreak("~f~Quick Teleports");
			if (Menu::Option("Airport")) 
			{
				Vector3 Coords;
				Coords.x = -1102.2910f; Coords.y = -2894.5160f; Coords.z = 13.9467f;
				TPto(Coords);
			}
			if (Menu::Option("Los Santos Customs"))
			{
				Vector3 Coords;
				Coords.x = -373.01; Coords.y = -124.91; Coords.z = 38.31;
				TPto(Coords);
			}
			if (Menu::Option("Ponsonbys")) 
			{
				Vector3 Coords;
				Coords.x = -718.91; Coords.y = -158.16; Coords.z = 37.00;
				TPto(Coords);
			}
			if (Menu::Option("FBI Lobby")) 
			{
				Vector3 Coords;
				Coords.x = 135.5220f; Coords.y = -749.0003f; Coords.z = 260.0000f;
				TPto(Coords);
			}
			if (Menu::Option("Mazebank Roof"))
			{
				Vector3 Coords;
				Coords.x = -74.94243f; Coords.y = -818.63446f; Coords.z = 326.174347f;
				TPto(Coords);
			}
			if (Menu::Option("Mount Chiliad")) 
			{
				Vector3 Coords;
				Coords.x = 496.75f; Coords.y = 5591.17f; Coords.z = 795.03f;
				TPto(Coords);
			}
		}
		break;
#pragma endregion

#pragma region Standard Teleport
		case std_loc:
		{
			Menu::Title("");
			Menu::SmallTitle("Standard");
			if (Menu::Option("Mazebank Roof"))
			{
				Vector3 Coords;
				Coords.x = -74.94243f; Coords.y = -818.63446f; Coords.z = 326.174347f;
				TPto(Coords);
			}
			if (Menu::Option("Mount Chiliad")) {
				Vector3 Coords;
				Coords.x = 496.75f; Coords.y = 5591.17f; Coords.z = 795.03f;
				TPto(Coords);
			}
			if (Menu::Option("Military Base")) {
				Vector3 Coords;
				Coords.x = -2012.8470f; Coords.y = 2956.5270f; Coords.z = 32.8101f;
				TPto(Coords);
			}
			if (Menu::Option("Zancudo Tower")) { //Eyy btw i was trying do display my coords but didnt work
				Vector3 Coords;
				Coords.x = -2356.0940; Coords.y = 3248.645; Coords.z = 101.4505;
				TPto(Coords);
			}
			if (Menu::Option("Mask Shop")) {
				Vector3 Coords;
				Coords.x = -1338.16; Coords.y = -1278.11; Coords.z = 4.87;
				TPto(Coords);
			}
			if (Menu::Option("Los Santos Customs")) {
				Vector3 Coords;
				Coords.x = -373.01; Coords.y = -124.91; Coords.z = 38.31;
				TPto(Coords);
			}
			if (Menu::Option("Ammu-Nation")) {
				Vector3 Coords;
				Coords.x = 247.3652; Coords.y = -45.8777; Coords.z = 69.9411;
				TPto(Coords);
			}
			if (Menu::Option("Airport")) {
				Vector3 Coords;
				Coords.x = -1102.2910f; Coords.y = -2894.5160f; Coords.z = 13.9467f;
				TPto(Coords);
			}
			if (Menu::Option("Ponsonbys")) {
				Vector3 Coords;
				Coords.x = -718.91; Coords.y = -158.16; Coords.z = 37.00;
				TPto(Coords);
			}
			if (Menu::Option("Waterfall")) {
				Vector3 Coords;
				Coords.x = -597.9525f; Coords.y = 4475.2910f; Coords.z = 25.6890f;
				TPto(Coords);
			}
			if (Menu::Option("FBI Lobby")) {
				Vector3 Coords;
				Coords.x = 135.5220f; Coords.y = -749.0003f; Coords.z = 260.0000f;
				TPto(Coords);
			}
			if (Menu::Option("Human Labs")) {
				Vector3 Coords;
				Coords.x = 3617.231f; Coords.y = 3739.871f; Coords.z = 28.6901f;
				TPto(Coords);
			}
			if (Menu::Option("Sandy Shores Airfield")) {
				Vector3 Coords;
				Coords.x = 1741.4960f; Coords.y = 3269.2570f; Coords.z = 41.6014f;
				TPto(Coords);
			}
		}
		break;
#pragma endregion

#pragma region Online Teleport
		case online_loc:
		{
			Menu::Title("");
			Menu::SmallTitle("Online");
			if (Menu::Option("10 Car Garage")) 
			{
				PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), 229.3382f, -992.9117f, -98.9999f);
			}
			if (Menu::Option("6 Car Garage")) 
			{
				PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), 197.8153f, -1002.293f, -99.0004f);
			}
			if (Menu::Option("2 Car Garage")) 
			{
				PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), 173.2904f, -1003.600f, -98.9999f);
			}
			if (Menu::Option("Impound Lot")) 
			{
				PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), 391.4746f, -1637.975f, 29.3148f);
			}
			if (Menu::Option("LSPD Char Creator")) {

				PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), 402.6675f, -1003.000f, -99.0040f);
			}
			if (Menu::Option("Mission Carpark")) 
			{
				PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), 405.9359f, -954.0912f, -99.0041f);
			}
			if (Menu::Option("Mors Mutuals")) 
			{
				PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), -222.1977f, -1185.850f, 23.0294f);
			}
		}
		break;
#pragma endregion

#pragma region Towers Teleport
		case tower_loc:
		{
			Menu::Title("");
			Menu::SmallTitle("Towers");
			if (Menu::Option("Secret Army Tower")) 
			{
				Vector3 Coords;
				Coords.x = -2358.946045f; Coords.y = 3252.216797f; Coords.z = 101.450424f;
				TPto(Coords);
			}
			if (Menu::Option("Eclipse Tower Apartment")) 
			{
				Vector3 Coords;
				Coords.x = -810.110901f; Coords.y = 300.467865f; Coords.z = 86.118515f;
				TPto(Coords);
			}
			if (Menu::Option("Tinsel Tower Apartment")) 
			{
				Vector3 Coords;
				Coords.x = -641.864624f; Coords.y = 24.014740f; Coords.z = 39.351025f;
				TPto(Coords);
			}
			if (Menu::Option("Maze Tower")) 
			{
				Vector3 Coords;
				Coords.x = -73.92588f; Coords.y = -818.455078f; Coords.z = 326.174377f;
				TPto(Coords);
			}
			if (Menu::Option("Construction Tower")) 
			{
				Vector3 Coords;
				Coords.x = -143.881927f; Coords.y = -984.810852f; Coords.z = 269.134308f;
				TPto(Coords);
			}
			if (Menu::Option("Clock Tower")) 
			{
				Vector3 Coords;
				Coords.x = -1238.675537f; Coords.y = -847.954590f; Coords.z = 85.161690f;
				TPto(Coords);
			}
			if (Menu::Option("Sniper Tower")) 
			{
				Vector3 Coords;
				Coords.x = -550.989380f; Coords.y = -193.862366f; Coords.z = 76.499336f;
				TPto(Coords);
			}
			if (Menu::Option("Prison Tower")) 
			{
				Vector3 Coords;
				Coords.x = 1541.6290f; Coords.y = 2470.1400f; Coords.z = 62.8751f;
				TPto(Coords);
			}
			if (Menu::Option("Creek(Mountain Tower)")) 
			{
				Vector3 Coords;
				Coords.x = 2784.6060f; Coords.y = 6000.8770f; Coords.z = 357.2007f;
				TPto(Coords);
			}
			if (Menu::Option("Eclipse Towers")) 
			{
				Vector3 Coords;
				Coords.x = -773.351990f; Coords.y = 309.809235f; Coords.z = 85.699196f;
				TPto(Coords);
			}
			if (Menu::Option("Tinsel Towers")) 
			{
				Vector3 Coords;
				Coords.x = -641.864624f; Coords.y = 24.014740f; Coords.z = 39.351025f;
				TPto(Coords);
			}
			if (Menu::Option("Zancudo Tower")) 
			{
				Vector3 Coords;
				Coords.x = -2356.0940; Coords.y = 3248.645; Coords.z = 101.4505;
				TPto(Coords);
			}
		}
		break;
#pragma endregion

#pragma region Shops Teleport
		case shop_loc:
		{
			Menu::Title("");
			Menu::SmallTitle("Shops");
			if (Menu::Option("Ammunation")) 
			{
				PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), 247.3652f, -45.8777f, 69.9411f);
			}
			if (Menu::Option("Barber Shop")) 
			{
				PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), -1293.231f, -1117.002f, 6.6402f);
			}
			if (Menu::Option("Bennys")) 
			{
				PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), -205.3417f, -1305.824f, 31.3527f);
			}
			if (Menu::Option("LSC")) 
			{
				PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), -367.7336f, -130.8588f, 38.6772f);
			}
			if (Menu::Option("Clothing Shop")) 
			{
				PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), -159.2996f, -304.3292f, 39.7333f);
			}
			if (Menu::Option("Tattoo Shop")) 
			{
				PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::PLAYER_PED_ID(), 319.7877f, 172.2311f, 103.7454f);
			}
		}
		break;
#pragma endregion

#pragma region Nightclub Teleport
		case night_loc:
		{
			Menu::Title("");
			Menu::SmallTitle("Nightclubs");
			if (Menu::Option("Downtown Vinewood")) 
			{
				Vector3 Coords;
				Coords.x = 373.260f; Coords.y = 254.730f; Coords.z = 102.954f;
				TPto(Coords);
			}
			if (Menu::Option("Vinewood Middle")) 
			{
				Vector3 Coords;
				Coords.x = 7.939f; Coords.y = 218.331f; Coords.z = 107.607f;
				TPto(Coords);
			}
			if (Menu::Option("Del Perro")) 
			{
				Vector3 Coords;
				Coords.x = -1289.758f; Coords.y = -647.775f; Coords.z = 26.573f;
				TPto(Coords);
			}
			if (Menu::Option("Vespucci")) 
			{
				Vector3 Coords;
				Coords.x = -1164.017f; Coords.y = -1199.575f; Coords.z = 3.772f;
				TPto(Coords);
			}
			if (Menu::Option("Airport")) 
			{
				Vector3 Coords;
				Coords.x = -664.626f; Coords.y = -2462.964f; Coords.z = 13.944;
				TPto(Coords);
			}
			if (Menu::Option("Strawberry")) 
			{
				Vector3 Coords;
				Coords.x = 82.522f; Coords.y = -1298.378f; Coords.z = 29.293f;
				TPto(Coords);
			}
			if (Menu::Option("Cypress Flats")) 
			{
				Vector3 Coords;
				Coords.x = 377.244f; Coords.y = -1111.520f; Coords.z = 29.406f;
				TPto(Coords);
			}
			if (Menu::Option("La Mesa")) 
			{
				Vector3 Coords;
				Coords.x = 784.305f; Coords.y = -1279.764f; Coords.z = 26.358f;
				TPto(Coords);
			}
			if (Menu::Option("Misson Row")) 
			{
				Vector3 Coords;
				Coords.x = 865.235f; Coords.y = -2094.451f; Coords.z = 30.241f;
				TPto(Coords);
			}
			if (Menu::Option("Elysian Island")) 
			{
				Vector3 Coords;
				Coords.x = 188.878f; Coords.y = -3161.526f; Coords.z = 5.787f;
				TPto(Coords);
			}
		}
		break;
#pragma endregion

#pragma region Spoofed Killer
		case SpoofKill:
		{
			Menu::Title("");
			Menu::SmallTitle("Spoofed Killer");
			Menu::Toggle("Enable Spoofed Killer", Features::killSpooferOn);
			ostringstream s_killer; s_killer << "Selected Killer: " << PLAYER::GET_PLAYER_NAME(Features::spoofKiller);
			Menu::Option(s_killer.str().c_str());
			Menu::MenuBreak("~f~Players");
			for (int i = 0; i < 33; i++) 
			{
				if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) 
				{
					if (Menu::Option(PLAYER::GET_PLAYER_NAME(i))) 
					{
						Features::spoofKiller = i;
					}
				}
			}
		}
		break;
#pragma endregion

#pragma region World
		case world_options:
		{
			Menu::Title("");
			Menu::SmallTitle("World Options");
			Menu::MenuOption("Weather", weather);
			if (Menu::Toggle("Moon Gravity", MoonGravity)) 
			{
				GAMEPLAY::SET_GRAVITY_LEVEL(MoonGravity ? 2 : 0);
			}
			if (Menu::Option("Create Thunder")) 
			{
                GAMEPLAY::_CREATE_LIGHTNING_THUNDER();
			}
			//Int options --
			int WaveIntensity;
			if (Menu::Int("Wave Intensity", WaveIntensity, 0, 100)) 
			{
				WATER::_SET_CURRENT_INTENSITY(WaveIntensity);
			}

			int rainIntensity;
			if (Menu::Int("Rain Intensity", rainIntensity, 0, 100)) 
			{
				GAMEPLAY::_SET_RAIN_FX_INTENSITY(rainIntensity);
			}

			int oprainIntensity;
			if (Menu::Int("Wind Speed", oprainIntensity, 0, 100)) 
			{
				GAMEPLAY::SET_WIND_SPEED(oprainIntensity);
			}

			int dioprainIntensity;
            if (Menu::Int("Wind Direction", dioprainIntensity, 0, 100)) 
			{
				GAMEPLAY::SET_WIND_DIRECTION(dioprainIntensity);
			}

			if (Menu::Settings::currentOption == 1)
			{
				Menu::OptionInfo("Change the local weather");
			}
			if (Menu::Settings::currentOption == 2)
			{
				Menu::OptionInfo("Enables moon gravity...");
			}
			if (Menu::Settings::currentOption == 3)
			{
				Menu::OptionInfo("Set thunderstorm now...");
			}
			if (Menu::Settings::currentOption == 4)
			{
				Menu::OptionInfo("Change the wave intensity from water");
			}
			if (Menu::Settings::currentOption == 5)
			{
				Menu::OptionInfo("Change the rain intensity");
			}
			if (Menu::Settings::currentOption == 6)
			{
				Menu::OptionInfo("Change the wind speed");
			}
			if (Menu::Settings::currentOption == 7)
			{
				Menu::OptionInfo("Change wind direction...");
			}
		}
		break;
#pragma endregion

#pragma region Special Options
		case special_options:
		{
			Menu::Title("");
			Menu::SmallTitle("Special");
			Menu::Toggle("RP Increace(Police)", rp_incr); //Not
			Menu::Toggle("Police Ignore", police_igga); //Don't know
			Menu::Toggle("Non Target", NontArget); //Dont' know - Mayvbbe
			if (Menu::Option("Police Mode")) //Works
			{
				notifyleft2("You are now in cop mode!", "Novus", "Cop mode ~g~Enabled!");
				Ped Thisped = PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID());
				PED::SET_PED_AS_COP(Thisped, true);
			}
			//Menu::Toggle("Unlimited Underwater", under_wt_time);
			Menu::Toggle("Unlimited Lucky Wheel", lucky_loop);
			Menu::Toggle("Display Minimap", dis_map);
			Menu::Toggle("IP Spoofer", IP_Spoof);

			//Info
			if (Menu::Settings::currentOption == 1)
			{
				Menu::OptionInfo("Earn RP by police bug");
			}
			if (Menu::Settings::currentOption == 2)
			{
				Menu::OptionInfo("Makes the police ignore you");
			}
			if (Menu::Settings::currentOption == 3)
			{
				Menu::OptionInfo("You get untarget-able");
			}
			if (Menu::Settings::currentOption == 4)
			{
				Menu::OptionInfo("Turns you into a police...");
			}
			if (Menu::Settings::currentOption == 5)
			{
				Menu::OptionInfo("Gives you ulimites spinns on lucky wheel");
			}
			if (Menu::Settings::currentOption == 6)
			{
				Menu::OptionInfo("Minimap enable / disable");
			}
		}
		break;
#pragma endregion

#pragma region Teleport
		case teleport:
		{
			Menu::Title("");
			Menu::SmallTitle("Teleport");
			Menu::Toggle("Teleport To Waypoint", bAutoWaypoint); //Dont' know - Mayvbbe -- leter fix cuz toggle
			//Menu::Toggle("Teleport To Waypoint", bAutoWaypoint); //Dont' know - Mayvbbe
			if (Menu::Option("Teleport 2 M Infront")) 
			{
				Vector3 Coords;
				Coords.x = MyCurentLoc.x - 2.5f; Coords.y = MyCurentLoc.y; Coords.z = MyCurentLoc.z;
				TPto(Coords);
			}
			if (Menu::Option("Mazebank Roof"))
			{
				Vector3 Coords;
				Coords.x = -74.94243f; Coords.y = -818.63446f; Coords.z = 326.174347f;
				TPto(Coords);
			}
			if (Menu::Option("Mount Chiliad")) {
				Vector3 Coords;
				Coords.x = 496.75f; Coords.y = 5591.17f; Coords.z = 795.03f;
				TPto(Coords);
			}
			if (Menu::Option("Military Base")) {
				Vector3 Coords;
				Coords.x = -2012.8470f; Coords.y = 2956.5270f; Coords.z = 32.8101f;
				TPto(Coords);
			}
			if (Menu::Option("Zancudo Tower")) { //Eyy btw i was trying do display my coords but didnt work
				Vector3 Coords;
				Coords.x = -2356.0940; Coords.y = 3248.645; Coords.z = 101.4505;
				TPto(Coords);
			}
			if (Menu::Option("Mask Shop")) {
				Vector3 Coords;
				Coords.x = -1338.16; Coords.y = -1278.11; Coords.z = 4.87;
				TPto(Coords);
			}
			if (Menu::Option("Los Santos Customs")) {
				Vector3 Coords;
				Coords.x = -373.01; Coords.y = -124.91; Coords.z = 38.31;
				TPto(Coords);
			}
			if (Menu::Option("Ammu-Nation")) {
				Vector3 Coords;
				Coords.x = 247.3652; Coords.y = -45.8777; Coords.z = 69.9411;
				TPto(Coords);
			}
			if (Menu::Option("Airport")) {
				Vector3 Coords;
				Coords.x = -1102.2910f; Coords.y = -2894.5160f; Coords.z = 13.9467f;
				TPto(Coords);
			}
			if (Menu::Option("Ponsonbys")) {
				Vector3 Coords;
				Coords.x = -718.91; Coords.y = -158.16; Coords.z = 37.00;
				TPto(Coords);
			}
			if (Menu::Option("Waterfall")) {
				Vector3 Coords;
				Coords.x = -597.9525f; Coords.y = 4475.2910f; Coords.z = 25.6890f;
				TPto(Coords);
			}
			if (Menu::Option("FBI Lobby")) {
				Vector3 Coords;
				Coords.x = 135.5220f; Coords.y = -749.0003f; Coords.z = 260.0000f;
				TPto(Coords);
			}
			if (Menu::Option("Human Labs")) {
				Vector3 Coords;
				Coords.x = 3617.231f; Coords.y = 3739.871f; Coords.z = 28.6901f;
				TPto(Coords);
			}
			if (Menu::Option("MMI")) {
				Vector3 Coords;
				Coords.x = -222.1977; Coords.y = -1185.8500; Coords.z = 23.0294;
				TPto(Coords);
			}
			if (Menu::Option("Sandy Shores Airfield")) {
				Vector3 Coords;
				Coords.x = 1741.4960f; Coords.y = 3269.2570f; Coords.z = 41.6014f;
				TPto(Coords);
			}

			//Info
			if (Menu::Settings::currentOption == 1)
			{
				Menu::OptionInfo("Teleport to Waypoint, if enabled it's auto");
			}
			if (Menu::Settings::currentOption == 2)
			{
				Menu::OptionInfo("Teleport 2 meters infront");
			}
			if (Menu::Settings::currentOption == 3)
			{
				Menu::OptionInfo("Teleport to Mazebank roof");
			}
			if (Menu::Settings::currentOption == 4)
			{
				Menu::OptionInfo("Teleport to Mount Chiliad");
			}
			if (Menu::Settings::currentOption == 5)
			{
				Menu::OptionInfo("Teleport to Military Base");
			}
			if (Menu::Settings::currentOption == 6)
			{
				Menu::OptionInfo("Teleport to Zancudo Tower");
			}
			if (Menu::Settings::currentOption == 6)
			{
				Menu::OptionInfo("Teleport to Mask Shop");
			}
			if (Menu::Settings::currentOption == 7)
			{
				Menu::OptionInfo("Teleport to Los Santos Customs");
			}
			if (Menu::Settings::currentOption == 8)
			{
				Menu::OptionInfo("Teleport to Ammu-Nation");
			}
			if (Menu::Settings::currentOption == 9)
			{
				Menu::OptionInfo("Teleport to Airport");
			}
			if (Menu::Settings::currentOption == 10)
			{
				Menu::OptionInfo("Teleport to Ponsonbys");
			}
			if (Menu::Settings::currentOption == 11)
			{
				Menu::OptionInfo("Teleport to Waterfall");
			}
			if (Menu::Settings::currentOption == 12)
			{
				Menu::OptionInfo("Teleport to FBI Lobby");
			}
			if (Menu::Settings::currentOption == 13)
			{
				Menu::OptionInfo("Teleport to Human Labs");
			}
			if (Menu::Settings::currentOption == 14)
			{
				Menu::OptionInfo("Teleport to MMI");
			}
			if (Menu::Settings::currentOption == 15)
			{
				Menu::OptionInfo("Teleport to MMI Sandy Shores Airfield");
			}
		}
		break;
#pragma endregion

#pragma region Map mods
		case map_modsz:
		{
			Menu::Title("");
			Menu::SmallTitle("");
			Menu::Option("Nothing LOL1");
			Menu::Option("Nothing LOL2");
			Menu::Option("Nothing LOL3");
			Menu::Option("Nothing LOL4");
			Menu::Option("Nothing LOL5");
			Menu::Option("Nothing LOL6");
			Menu::Option("Nothing LOL7");
		}
		break;
#pragma endregion
//Vehicle spawner and Vehicle options
#pragma region vehspawnerr
		case vehspawner:
		{
			Menu::Title("");
			Menu::SmallTitle("Vehicle Spawner");
			//Menu::MenuOption("Modded Vehicles ~r~(Coming)", sport);
			Menu::MenuOption("Sport", sport); 
			Menu::MenuOption("Super", super_cars);
			Menu::MenuOption("Coupes", coupes);
			Menu::MenuOption("Arena War", arena);
			Menu::MenuOption("Casino", casino);
			Menu::MenuOption("Bikes", Moto_bikes);
			Menu::MenuOption("Boats", Boats);
			Menu::MenuOption("Planes", Planes);
			Menu::MenuOption("Helicopters", Helicopters_Car);
			//Info


		}
		break;
#pragma endregion

#pragma region vehoptions
		case vehoptions:
		{
			Menu::Title("");
			Menu::SmallTitle("Vehicle");
			Menu::MenuOption("Vehicle Spawner ", vehspawner);
			Menu::MenuOption("Vehicle Nitro", veh_nitro);
			Menu::MenuOption("Portable LSC", port_lsc);
			if (Menu::Option("Max Upgrade Car")) 
			{
				Features::maxvehicle();
			}
			if (Menu::Option("Random Paint"))
			{
				int VehID = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(VehID, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255));
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(VehID, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255));
			}
			if (Menu::Option("Repair Vehicle"))
			{
				uint Vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID()));
				VEHICLE::SET_VEHICLE_FIXED(Vehicle);
				VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(Vehicle);
				VEHICLE::SET_VEHICLE_DIRT_LEVEL(Vehicle, 0);
			}
			if (Menu::Option("Custom Plate"))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
				RequestControlOfEnt(veh);
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, CharKeyboard());
			}
			Menu::Toggle("Rainbow Vehicle", Rpaint);
			Menu::Toggle("Godmode Vehicle", MySelf::CarGMode);
			Menu::Toggle("Horn Boost", hornBoostme);
			Menu::Toggle("Auto Repair", AutoRepVeh);
			//Menu::Toggle("Super Grip", NewOption::Supergrip);
			Menu::Toggle("Invisible Vehicle", NewOption::Invisible_vehicle);
			Menu::Toggle("Anti Gravity", NewOption::Vehicle_Gravity);
			Menu::Toggle("Speedometer Plate", NewOption::speedo_plate);
			Menu::Toggle("Normal Speedometer", NewOption::speedo_draw);
			Menu::Toggle("Drift Mode", NewOption::DriftMod);
			Menu::Toggle("HotKey Drift[Left Shift]", NewOption::key_drift);
			Menu::Toggle("Drive On Water", NewOption::water_drive);
			Menu::Toggle("Drive In Air", NewOption::MeinCode);

			//info
			if (Menu::Settings::currentOption == 1)
			{
				Menu::OptionInfo("Vehicle Spawner");
			}
			if (Menu::Settings::currentOption == 2)
			{
				Menu::OptionInfo("Max upgrade your curent vehicle");
			}
			if (Menu::Settings::currentOption == 3)
			{
				Menu::OptionInfo("Gives vehicle an random paint");
			}
			if (Menu::Settings::currentOption == 4)
			{
				Menu::OptionInfo("Repairs curent vehicle");
			}
			if (Menu::Settings::currentOption == 5)
			{
				Menu::OptionInfo("Set custom nummer plate");
			}
			if (Menu::Settings::currentOption == 6)
			{
				Menu::OptionInfo("Enable rainbow vehicle");
			}
			if (Menu::Settings::currentOption == 7)
			{
				Menu::OptionInfo("Set your vehicle into godmode");
			}
			if (Menu::Settings::currentOption == 8)
			{
				Menu::OptionInfo("Enable horn boost vehicle");
			}
			if (Menu::Settings::currentOption == 9)
			{
				Menu::OptionInfo("Auto rapairs your vehicle");
			}

		}
		break;
#pragma endregion

#pragma region Vehicle Nitro
		case veh_nitro:
		{
			Menu::Title("");
			Menu::SmallTitle("Vehicle Nitro");
			Menu::Toggle("Enable Nitro", NewOption::VehicleNitrous);
			Menu::Toggle("Screen Effect", NewOption::NitrousEffect);
			Menu::Toggle("Exhaust Flames", NewOption::NitrousExhaust);
			if (Menu::Option("Realistic Vehicle Nitro")) 
			{
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 40.0f);
			}
			if (Menu::Option("Ridiculous Vehicle Nitro")) 
			{
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), 100.0f);
			}
			Menu::MenuBreak("~f~Horn Boost");
			if (Menu::Int("Boost Power", HonkPower, 50, 500))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) 
				{
					HonkPower = NumberKeyboard();
				}
			}
			Menu::Toggle("Enable Horn Boost", Car_HonkBoost);
			Menu::Toggle("Enable Boost Effect", HonkEffect);
		}
		break;
#pragma endregion

#pragma region Portable LSC
		case port_lsc:
		{
			Menu::Title("");
			Menu::SmallTitle("Portable LSC");
			Menu::MenuOption("Neons Options", Neons);

			if (Menu::Option("Paint Chrome")) 
			{
				VEHICLE::SET_VEHICLE_COLOURS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 120, 120);
			}
			if (Menu::Option("Paint Raindom")) 
			{
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), rand() % 255, rand() % 255, rand() % 255);
				if (VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID())))
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), rand() % 255, rand() % 255, rand() % 255);
			}
			if (Menu::Int("Armor", Amorr, 0, 4))
			{
				LSC(16, Amorr);
			}
			if (Menu::Int("Engine", Enginee, 0, 3))
			{
				LSC(11, Enginee);
			}
			if (Menu::Int("Break", Brake, 0, 3))
			{
				LSC(12, Brake);
			}
			if (Menu::Int("Spoiler", Spoilerr, 0, 6))
			{
				LSC(0, Spoilerr);
			}
			if (Menu::Int("Skirt", Skirtt, 0, 3))
			{
				LSC(3, Skirtt);
			}
			if (Menu::Int("Suspension", Suspensionn, 0, 3))
			{
				LSC(15, Suspensionn);
			}
			if (Menu::Int("Transmission", Transmission, 0, 3))
			{
				LSC(13, Transmission);
			}
			if (Menu::Int("Front Bumper", Bumperr, 0, 3))
			{
				LSC(1, Bumperr);
			}
			if (Menu::Int("Rear Bumper", Bumper2, 0, 3))
			{
				LSC(2, Bumper2);
			}
			if (Menu::Int("Exhaust", Exhaust, 0, 3))
			{
				LSC(4, Exhaust);
			}
			if (Menu::Int("Hood", Bonnet, 0, 3))
			{
				LSC(7, Bonnet);
			}
			if (Menu::Int("Rollcage", Rollcage, 0, 3))
			{
				LSC(5, Rollcage);
			}
			if (Menu::Int("Horn", Klaxonn, 0, 15))
			{
				LSC(14, Klaxonn);
			}
		}
		break;
#pragma endregion

#pragma region coupes
		case coupes:
		{
			Menu::Title("");//Use this line to include banner on option page
			Menu::SmallTitle("Coupes");
			//List start here <<
			char* coupes[] = 
			{ 
					"COGCABRIO", "EXEMPLAR", "F620", "FELON", "FELON2",
					"JACKAL", "ORACLE", "ORACLE2", "SENTINEL", "SENTINEL2",
					"WINDSOR", "WINDSOR2", "ZION", "ZION2"
			};
			//List ends here
			Menu::Title("Coupe");
			for (int i = 0; i < ARRAYSIZE(coupes); i++)
			{

				Menu::VehicleOption(coupes[i]);
			}


		}
		break;


		
#pragma endregion

#pragma region Sports
		case sport:
		{
			 char* coupes2[] = {
				"ALPHA", "BANSHEE", "BESTIAGTS", "BLISTA2", "BLISTA3",
				"BUFFALO", "BUFFALO2", "BUFFALO3", "CARBONIZZARE", "COMET2",
				"COQUETTE", "ELEGY", "ELEGY2", "FELTZER2", "FUROREGT", "FUSILADE",
				"FUTO", "JESTER", "JESTER2", "KHAMELION", "KURUMA",
				"KURUMA2", "LYNX", "MASSACRO", "MASSACRO2", "NINEF",
				"NINEF2", "OMNIS", "PENUMBRA", "RAPIDGT", "RAPIDGT2",
				"RAPTOR", "SCHAFTER3", "SCHAFTER4", "SCHWARZE", "SEVEN70",
				"SULTAN", "SURANO", "SPECTER", "SPECTER2", "TAMPA2", "TROPOS", "VERLIERER2",
				"RUINER2", "PHANTOM2", "RUSTON", "COMET4", "COMET5", "NEON", "PARIAH", "RAIDEN", "REVOLTER", "SENTINEL3", "STREITER", "Z190",
				"GB200", "HOTRING", "ITALIGTO", "SCHLAGEN", "ZR380", "ZR3802", "ZR3803",
				"DRAFTER", "JUGULAR", "LOCUST", "NEO", "PARAGON", "PARAGON2", "IMORGON", "KOMODA", "SUGOI", "SULTAN2", "VSTR"
			};
			Menu::Title("Sportcars");
			Menu::SmallTitle("Sport");

			Menu::Title("Sport");
			for (int i = 0; i < ARRAYSIZE(coupes2); i++)
			{

				Menu::VehicleOption(coupes2[i]);
			}

		}
		break;
#pragma endregion

#pragma region Super Vehicle
		case super_cars:
		{
			static char* Super1[] = {
	"ADDER", "BANSHEE2", "BULLET", "CHEETAH", "ENTITYXF",
	"FMJ", "SHEAVA", "INFERNUS", "NERO", "NERO2","OSIRIS", "LE7B",
	"ITALIGTB", "ITALIGTB2", "PFISTER811", "PROTOTIPO", "REAPER", "SULTANRS", "T20",
	"TEMPESTA", "TURISMOR", "TYRUS", "VACCA", "VOLTIC", "ZENTORNO", "VOLTIC2", "PENETRATOR", "GP1", "XA21", "VIGILANTE",
	"CYCLONE", "VISIONE", "AUTARCH", "SC1", "ENTITY2", "TAIPAN", "TEZERACT", "TYRANT", "SCRAMJET", "DEVESTE",
	"EMERUS", "KRIEGER", "S80", "THRAX", "ZORRUSSO", "FURIA", "FORMULA", "FORMULA2"
			};
			Menu::Title("Super");
			Menu::SmallTitle("Super");

			Menu::Title("Sport");
			for (int i = 0; i < ARRAYSIZE(Super1); i++)
			{

				Menu::VehicleOption(Super1[i]);
			}
		}
		break;
#pragma endregion

#pragma region Bikes
		case Moto_bikes:
		{
			char* Motorcycles1[] = {
	"AKUMA", "AVARUS", "BAGGER", "BATI", "BATI2",
	"BF400", "CARBONRS", "CHIMERA", "CLIFFHANGER", "DAEMON",
	"DAEMON2", "DEFILER", "DOUBLE", "ENDURO", "ESSKEY",
	"FAGGIO", "FAGGIO2", "FAGGIO3", "GARGOYLE", "HAKUCHOU",
	"HAKUCHOU2", "HEXER", "INNOVATION", "LECTRO", "MANCHEZ",
	"NEMESIS", "NIGHTBLADE", "PCJ", "RATBIKE", "RUFFIAN",
	"SANCHEZ", "SANCHEZ2", "SANCTUS", "SHOTARO", "SOVEREIGN",
	"THRUST", "VADER", "VINDICATOR", "VORTEX", "WOLFSBANE",
	"ZOMBIEA", "ZOMBIEB", "DIABLOUS", "DIABLOUS2", "FCR",
	"FCR2", "OPPRESSOR", "AVENGER", "OPPRESSOR2", "DEATHBIKE2",
	"DEATHBIKE3", "DEATHBIKE", "RROCKET", "STRYDER"
			};
			Menu::Title("Sport");
			Menu::SmallTitle("Motors");

			for (int i = 0; i < ARRAYSIZE(Motorcycles1); i++)
			{

				Menu::VehicleOption(Motorcycles1[i]);
			}
		}
		break;
#pragma endregion

#pragma region Boats
		case Boats:
		{
			char* Boats1[] = {
	"DINGHY", "DINGHY2", "DINGHY3", "DINGHY4", "JETMAX",
	"MARQUIS", "PREDATOR", "SEASHARK", "SEASHARK2", "SEASHARK3",
	"SPEEDER", "SPEEDER2", "SQUALO", "SUBMERSIBLE", "SUBMERSIBLE2",
	"SUNTRAP", "TORO", "TORO2", "TROPIC", "TROPIC2",
	"TUG"
			};
			Menu::Title("Sport");
			Menu::SmallTitle("Boats");

			for (int i = 0; i < ARRAYSIZE(Boats1); i++)
			{

				Menu::VehicleOption(Boats1[i]);
			}
		}
		break;
#pragma endregion

#pragma region Planes
		case Planes:
		{
			char* Planes1[] = {
	"BESRA", "CARGOPLANE", "CUBAN800", "DODO", "DUSTER",
	"HYDRA", "JET", "LAZER", "LUXOR", "LUXOR2",
	"MAMMATUS", "MILJET", "NIMBUS", "SHAMAL", "STUNT",
	"TITAN", "VELUM", "VELUM2", "VESTRA", "BOMBUSHKA",
	"ALPHAZ1", "TULA", "ROGUE", "PYRO", "MOGUL",
	"NOKOTA", "MOLOTOK", "SEABREEZE", "MICROLIGHT", "HOWARD",
	"STARLING", "AVENGER2", "VOLATOL", "STRIKEFORCE"
			};
			Menu::Title("Sport");
			Menu::SmallTitle("Planes");

			for (int i = 0; i < ARRAYSIZE(Planes1); i++)
			{

				Menu::VehicleOption(Planes1[i]);
			}
		}
		break;
#pragma endregion

#pragma region Helicopters
		case Helicopters_Car:
		{
			char* Helicopters1[] = {
	"ANNIHILATOR", "BLIMP", "BLIMP2", "BUZZARD", "BUZZARD2",
	"CARGOBOB", "CARGOBOB2", "CARGOBOB3", "CARGOBOB4", "FROGGER",
	"FROGGER2", "MAVERICK", "POLMAV", "SAVAGE", "SKYLIFT",
	"SUPERVOLITO", "SUPERVOLITO2", "SWIFT", "SWIFT2", "VALKYRIE",
	"VALKYRIE2", "VOLATUS", "HUNTER", "HAVOK", "AKULA", "SEASPARROW",
	"BLIMP3"
			};
			Menu::Title("Sport");
			Menu::SmallTitle("Helicopters");

			for (int i = 0; i < ARRAYSIZE(Helicopters1); i++)
			{

				Menu::VehicleOption(Helicopters1[i]);
			}
		}
		break;
#pragma endregion
//Normal pages again
#pragma region Session
		case session:
		{
			Menu::Title("");
			Menu::SmallTitle("Network");
			Menu::MenuOption("Player List", playlist);
			Menu::MenuOption("All players", all_players);
			Menu::MenuOption("Protections ", NewProtect);
			Menu::MenuOption("Session Weather", onlineLobbyWet);
			Menu::MenuBreak("~f~[Spoofer]");
			Menu::MenuOption("Chage Name", cha_na);
			Menu::Toggle("IP Spoofer", IP_Spoof);

			//info
			if (Menu::Settings::currentOption == 1)
			{
				Menu::OptionInfo("View list over online players");
			}
			if (Menu::Settings::currentOption == 2)
			{
				Menu::OptionInfo("Manage all lobby players");
			}
			if (Menu::Settings::currentOption == 3)
			{
				Menu::OptionInfo("Change weather in lobby");
			}
			if (Menu::Settings::currentOption == 4)
			{
				Menu::OptionInfo("Spoofer options");
			}
			if (Menu::Settings::currentOption == 5)
			{
				Menu::OptionInfo("Change your ingame name");
			}
			if (Menu::Settings::currentOption == 6)
			{
				Menu::OptionInfo("Spoof your ip adress");
			}
		}
		break;
#pragma endregion
//working session weather - Pattern fixed :)
#pragma region Session Weather
		case onlineLobbyWet:
		{
			Menu::Title("");
			Menu::SmallTitle("Session Weather");

			if (Menu::MenuOption("Session Time", sess_time))
			{
				if (NETWORK::NETWORK_IS_IN_SESSION())
				{
					NULL;
				}
				else if (!NETWORK::NETWORK_IS_IN_SESSION())
				{
					notifyMap("~r~ERROR: ~s~This feature can't be used in Story Mode!");
				}
			}
			if (Menu::Option("Extra Sunny"))
			{
				if (NETWORK::NETWORK_IS_IN_SESSION())
				{
					Hooking::set_session_weather(1, 0, 76, 0);
				}
				else if (!NETWORK::NETWORK_IS_IN_SESSION())
				{
					CHANGE_WEATHER("Clear"); break;
				}
			}
			if (Menu::Option("Clear"))
			{
				if (NETWORK::NETWORK_IS_IN_SESSION())
				{
					Hooking::set_session_weather(1, 1, 76, 0);
				}
				else if (!NETWORK::NETWORK_IS_IN_SESSION())
				{
					CHANGE_WEATHER("Clear"); break;
				}
			}
			if (Menu::Option("Clouds"))
			{
				if (NETWORK::NETWORK_IS_IN_SESSION())
				{
					Hooking::set_session_weather(1, 2, 76, 0);
				}
				else if (!NETWORK::NETWORK_IS_IN_SESSION())
				{
					CHANGE_WEATHER("Clouds"); break;
				}
			}
			if (Menu::Option("Cloudy"))
			{
				if (NETWORK::NETWORK_IS_IN_SESSION())
				{
					Hooking::set_session_weather(1, 5, 76, 0);
				}
				else if (!NETWORK::NETWORK_IS_IN_SESSION())
				{
					CHANGE_WEATHER("Clouds"); break;
				}
			}
			//rain
			if (Menu::Option("Rain"))
			{
				if (NETWORK::NETWORK_IS_IN_SESSION())
				{
					Hooking::set_session_weather(1, 6, 76, 0);
				}
				else if (!NETWORK::NETWORK_IS_IN_SESSION())
				{
					CHANGE_WEATHER("Clearing"); break;
				}
			}
			if (Menu::Option("Light Rain"))
			{
				if (NETWORK::NETWORK_IS_IN_SESSION())
				{
					Hooking::set_session_weather(1, 8, 76, 0);
				}
				else if (!NETWORK::NETWORK_IS_IN_SESSION())
				{
					CHANGE_WEATHER("Clearing"); break;
				}
			}
			if (Menu::Option("Polluted Rain"))
			{
				if (NETWORK::NETWORK_IS_IN_SESSION())
				{
					Hooking::set_session_weather(1, 9, 76, 0);
				}
				else if (!NETWORK::NETWORK_IS_IN_SESSION())
				{
					CHANGE_WEATHER("Clearing"); break;
				}
			}
			if (Menu::Option("Thunder"))
			{
				if (NETWORK::NETWORK_IS_IN_SESSION())
				{
					Hooking::set_session_weather(1, 7, 76, 0);
				}
				else if (!NETWORK::NETWORK_IS_IN_SESSION())
				{
					notifyMap("~r~ERROR: ~w~This weather type can't be setted in Story Mode!");
				}
			}
			//clearing
			if (Menu::Option("Clearing 1")) 
			{
				if (NETWORK::NETWORK_IS_IN_SESSION())
				{
					Hooking::set_session_weather(1, 3, 76, 0);
				}
				else if (!NETWORK::NETWORK_IS_IN_SESSION())
				{
					CHANGE_WEATHER("Clearing"); break;
				}
			}

			if (Menu::Option("Clearing 2")) 
			{
				if (NETWORK::NETWORK_IS_IN_SESSION())
				{
					Hooking::set_session_weather(1, 4, 76, 0);
				}
				else if (!NETWORK::NETWORK_IS_IN_SESSION())
				{
					CHANGE_WEATHER("Clearing"); break;
				}
			}
			//Snow's
			if (Menu::Option("Light Snow")) 
			{
				if (NETWORK::NETWORK_IS_IN_SESSION())
				{
					Hooking::set_session_weather(1, 10, 76, 0);
				}
				else if (!NETWORK::NETWORK_IS_IN_SESSION())
				{
					CHANGE_WEATHER("Snowlight"); break;
				}
			}
			if (Menu::Option("Snow")) 
			{
				if (NETWORK::NETWORK_IS_IN_SESSION())
				{
					Hooking::set_session_weather(1, 11, 76, 0);
				}
				else if (!NETWORK::NETWORK_IS_IN_SESSION())
				{
					CHANGE_WEATHER("Blizzard"); break;
				}
			}
			//DLC's
			if (Menu::Option("Xmas"))
			{
				if (NETWORK::NETWORK_IS_IN_SESSION())
				{
					Hooking::set_session_weather(1, 13, 76, 0);
				}
				else if (!NETWORK::NETWORK_IS_IN_SESSION())
				{
					notifyMap("~r~ERROR: ~w~This weather type can't be setted in Story Mode!");
				}
			}
			if (Menu::Option("Halloween")) 
			{
				if (NETWORK::NETWORK_IS_IN_SESSION())
				{
					Hooking::set_session_weather(1, 14, 76, 0);
				}
				else if (!NETWORK::NETWORK_IS_IN_SESSION())
				{
					notifyMap("~r~ERROR: ~w~This weather type can't be setted in Story Mode!");
				}
			}
			if (Menu::Option("Blackout")) 
			{
				if (NETWORK::NETWORK_IS_IN_SESSION())
				{
					Hooking::set_session_weather(1, 15, 76, 0);
				}
				else if (!NETWORK::NETWORK_IS_IN_SESSION())
				{
					notifyMap("~r~ERROR: ~w~This weather type can't be setted in Story Mode!");
				}
			}
		}
		break;
#pragma endregion

#pragma region Session Time
		case sess_time:
		{
			Menu::Title("");
			Menu::SmallTitle("Session Time");
			Menu::Int("Hour", Menu::Settings::Hourfick, 0, 23);
			Menu::Int("Minute", Menu::Settings::Minufick, 0, 59);
			Menu::Int("Second", Menu::Settings::secfick, 0, 59);

			if (Menu::Option("Set Time"))
			{
				Network::SetSessionTime(Menu::Settings::Hourfick, Menu::Settings::Minufick, Menu::Settings::secfick);
            }
		}
		break;
#pragma endregion
//Display
#pragma region Display Name
		case cha_na:
		{
			Menu::Title("");
			Menu::SmallTitle("Change Name");
			Menu::MenuOption("Premade Names", pre_name);
			Menu::MenuBreak("~f~Input Name");
			if (Menu::Option("Plain name")) 
			{
				char* newname;

				GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, "Enter new displayname:", "", "", "name", "", "", 16);
                while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == false) WAIT(0);
				if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return;
				{
					newname = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
				}
				Features::SetName(newname);
			}
			if (Menu::Option("~italic~Italic Name")) {
				char* newname;
				GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, "Enter new displayname:", "", "", "name", "", "", 16);
				while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
				if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return;
				{
					newname = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
				}
				Features::SetName(Menu::Tools::StringToChar("~italic~" + (std::string)newname));
			}
			if (Menu::Option("~bold~Bold Name")) {
				char* newname;
				GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, "Enter new displayname:", "", "", "name", "", "", 16);
				while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
				if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return;
				{
					newname = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
				}
				Features::SetName(Menu::Tools::StringToChar("~bold~" + (std::string)newname));
			}
			Menu::MenuBreak("~f~[Set Name With Color]");
			if (Menu::Option("~r~Red ~s~Name")) {
				char* newname;
				GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, "Enter new displayname:", "", "", "name", "", "", 16);
				while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
				if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return;
				{
					newname = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
				}
				Features::SetName(Menu::Tools::StringToChar("~r~" + (std::string)newname));
			}
			if (Menu::Option("~g~Green ~s~Name")) {
				char* newname;
				GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, "Enter new displayname:", "", "", "name", "", "", 16);
				while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
				if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return;
				{
					newname = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
				}
				Features::SetName(Menu::Tools::StringToChar("~g~" + (std::string)newname));
			}
			if (Menu::Option("~b~Blue ~s~Name")) {
				char* newname;
				GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, "Enter new displayname:", "", "", "name", "", "", 16);
				while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
				if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return;
				{
					newname = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
				}
				Features::SetName(Menu::Tools::StringToChar("~b~" + (std::string)newname));
			}
		}
		break;
#pragma endregion

#pragma region Preset names
		case pre_name:
		{
			Menu::Title("");
			Menu::SmallTitle("Preset Names");
			if (Menu::Option("NotYourDad"))
			{
				char* NotYourDad;
				NotYourDad = "NotYourDad";
				Features::SetName(NotYourDad);
			}
			if (Menu::Option("RockstarDev"))
			{
				char* RockstarDev;
				RockstarDev = "RockstarDev";
				Features::SetName(RockstarDev);
			}
			if (Menu::Option("X-_-X"))
			{
				char* XX;
				XX = "X-_-X";
				Features::SetName(XX);
			}
			if (Menu::Option("StrongGuy"))
			{
				char* StrongGuy;
				StrongGuy = "StrongGuy";
				Features::SetName(StrongGuy);
			}
			if (Menu::Option("TryBeatMe"))
			{
				char* TryBeatMe;
				TryBeatMe = "TryBeatMe";
				Features::SetName(TryBeatMe);
			}
			if (Menu::Option("ReportMePlease"))
			{
				char* ReportMePlease;
				ReportMePlease = "ReportMePlease";
				Features::SetName(ReportMePlease);
			}
			Menu::MenuBreak("~f~Colored Names");
			if (Menu::Option("~r~KillMeHomie"))
			{
				char* KillMeHomie;
				KillMeHomie = "KillMeHomie";
				Features::SetName(Menu::Tools::StringToChar("~r~" + (std::string)KillMeHomie));
			}
			if (Menu::Option("~g~NoobieBooiXD"))
			{
				char* NoobieBooiXD;
				NoobieBooiXD = "NoobieBooiXD";
				Features::SetName(Menu::Tools::StringToChar("~g~" + (std::string)NoobieBooiXD));
            }
			if (Menu::Option("~b~T3stM3"))
			{
				char* T3STm3;
				T3STm3 = "T3STm3";
				Features::SetName(Menu::Tools::StringToChar("~b~" + (std::string)T3STm3));
			}
		}
		break;
#pragma endregion
//Local Weather
#pragma region Weather
		case weather:
		{
			Menu::Title("");
			Menu::SmallTitle("Weather");
			if (Menu::Option("Clear")) {
				CHANGE_WEATHER("Clear"); break;
			}
			if (Menu::Option("Rain")) {
				CHANGE_WEATHER("Clearing"); break;
			}
			if (Menu::Option("Snowlight")) {
				CHANGE_WEATHER("Snowlight"); break;
			}
			if (Menu::Option("Thunder")) {
				CHANGE_WEATHER("Thunder"); break;
			}
			if (Menu::Option("Blizzard")) {
				CHANGE_WEATHER("Blizzard"); break;
			}
			if (Menu::Option("Overcast")) {
				CHANGE_WEATHER("Overcast"); break;
			}
            if (Menu::Option("Foggy")) {
				CHANGE_WEATHER("Foggy"); break;
			}
			if (Menu::Option("Smog")) {
				CHANGE_WEATHER("Smog"); break;
			}
			if (Menu::Option("Clouds")) {
				CHANGE_WEATHER("Clouds"); break;
			}



		}
		break;
#pragma endregion
//Online weather
#pragma region Online Weather
		case weather_online:
		{
			Menu::Title("");
			Menu::SmallTitle("Session Weather");
			if (Menu::Option("Extra sunny"))
			{
				Hooking::set_network_weather(1, 0, 76, 0);
			}
			if (Menu::Option("Clear"))
			{
				Hooking::set_network_weather(1, 1, 76, 0);
			}
			if (Menu::Option("Clouds"))
			{
				Hooking::set_network_weather(1, 2, 76, 0);
			}
			if (Menu::Option("Smog"))
			{
				Hooking::set_network_weather(1, 3, 76, 0);
			}
			if (Menu::Option("Foggy"))
			{
				Hooking::set_network_weather(1, 4, 76, 0);
			}
			if (Menu::Option("Overcast"))
			{
				Hooking::set_network_weather(1, 5, 76, 0);
			}
			if (Menu::Option("Rain"))
			{
				Hooking::set_network_weather(1, 6, 76, 0);
			}
			if (Menu::Option("Thunder"))
			{
				Hooking::set_network_weather(1, 7, 76, 0);
			}
			if (Menu::Option("Clearing"))
			{
				Hooking::set_network_weather(1, 8, 76, 0);
			}
			if (Menu::Option("Drugs"))
			{
				Hooking::set_network_weather(1, 9, 76, 0);
			}
			if (Menu::Option("Snow"))
			{
				Hooking::set_network_weather(1, 10, 76, 0);
			}
			if (Menu::Option("Blizzard"))
			{
				Hooking::set_network_weather(1, 11, 76, 0);
			}
			if (Menu::Option("Snowlight"))
			{
				Hooking::set_network_weather(1, 12, 76, 0);
			}
			if (Menu::Option("Xmas"))
			{
				Hooking::set_network_weather(1, 13, 76, 0);
			}
			if (Menu::Option("Halloween"))
			{
				Hooking::set_network_weather(1, 14, 76, 0);
			}
			if (Menu::Option("Blackscreen"))
			{
				Hooking::set_network_weather(1, 15, 76, 0);
			}
			if (Menu::Option("Random weather"))
			{
				int RanWet = rndInt(0, 14);
				Hooking::set_session_weather(1, RanWet, 76, 0);
			}
		}
		break;
#pragma endregion

#pragma region playerlist
		case playlist:
		{
			Menu::Title("");
			Menu::SmallTitle("Player List");
			for (int i = 0; i < 32; ++i) {
				float IconX = { Menu::Settings::menuX - 0.095f };
				float IconY = { (Menu::Settings::optionCount) * 0.035f + 0.250f };
				int IconColor1 = 255;
				for (int i = 0; i < 32; ++i)
				{
					DWORD model = ENTITY::GET_ENTITY_MODEL(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
					Player isFriend = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
					bool is_friend;
					bool handle_valid = CheckFriendStatus(i, is_friend);
					BYTE God = PLAYER::GET_PLAYER_INVINCIBLE(selectedPlayer);

					//Get all players in current session
					if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)))
					{
						char* PlayerName = PLAYER::GET_PLAYER_NAME(i);
						char Buffer[255];

						//Check if player is session host
						if (NETWORK::NETWORK_GET_HOST_OF_SCRIPT("Freemode", -1, 0) == i)
						{
							char* PlayerName = PLAYER::GET_PLAYER_NAME(i);
							char Buffer[255];
							sprintf(Buffer, "%s ~y~[Session Host]", PlayerName);
							PlayerName = Buffer;
							Menu::MenuOption(PlayerName, onlineplayer_opt) ? selectedPlayer = i : NULL;
						}

						//Check if player is your player
						else if (isFriend == PLAYER::PLAYER_PED_ID())
						{
							char* PlayerName = PLAYER::GET_PLAYER_NAME(i);
							char Buffer[255];
							sprintf(Buffer, "%s ~b~[Me]", PlayerName);
							PlayerName = Buffer;
							Menu::MenuOption(PlayerName, onlineplayer_opt) ? selectedPlayer = i : NULL;
						}

						//Check if player is your friend
						else if (handle_valid && is_friend)
						{
							char* PlayerName = PLAYER::GET_PLAYER_NAME(i);
							char Buffer[255];
							sprintf(Buffer, "%s ~g~[Friend]", PlayerName);
							PlayerName = Buffer;
							Menu::MenuOption(PlayerName, onlineplayer_opt) ? selectedPlayer = i : NULL;
						}

						//Ckeck if player is from rockstar
						else if (NETWORK::NETWORK_PLAYER_IS_ROCKSTAR_DEV(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)))
						{
							char* PlayerName = PLAYER::GET_PLAYER_NAME(i);
							char Buffer[255];
							sprintf(Buffer, "%s ~r~[Rockstar Developer]", PlayerName);
							PlayerName = Buffer;
							Menu::MenuOption(PlayerName, onlineplayer_opt) ? selectedPlayer = i : NULL;
						}

						//Check if player is in godmode - Dosen't work yet
						else if (God = 1)
						{
							char* PlayerName = PLAYER::GET_PLAYER_NAME(i);
							char Buffer[255];
							sprintf(Buffer, "%s", PlayerName);
							PlayerName = Buffer;
							Menu::MenuOption(PlayerName, onlineplayer_opt) ? selectedPlayer = i : NULL;
						}

						//If nothing of those are true, just create a normal option
						else
						{
							Menu::MenuOption(PlayerName, onlineplayer_opt) ? selectedPlayer = i : NULL;
						}
					}
				}
				break;
			}
		}
		break;
#pragma endregion

#pragma region New PlayerList
		case network_list:
		{
			Menu::Title("");
			Menu::SmallTitle("Player List");

			for (int i = 0; i < 32; ++i) 
			{
				for (int i = 0; i < 32; ++i)
				{
					DWORD model = ENTITY::GET_ENTITY_MODEL(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
					Player isFriend = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
					bool is_friend;
					bool handle_valid = CheckFriendStatus(i, is_friend);
					BYTE God = PLAYER::GET_PLAYER_INVINCIBLE(selectedPlayer);

					//Get all players in current session
					if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)))
					{
						char* PlayerName = PLAYER::GET_PLAYER_NAME(i);
						char Buffer[255];

						//Check if player is session host
						if (NETWORK::NETWORK_GET_HOST_OF_SCRIPT("Freemode", -1, 0) == i)
						{
							char* PlayerName = PLAYER::GET_PLAYER_NAME(i);
							char Buffer[255];
							sprintf(Buffer, "%s ~y~[Session Host]", PlayerName);
							PlayerName = Buffer;
							//Menu::MenuOption(PlayerName, onlineplayer_opt) ? selectedPlayer = i : NULL;
							Menu::PlayerSub(PlayerName, onlineplayer_opt, i) ? selectedPlayer = i : NULL;
						}

						//Check if player is your player
						else if (isFriend == PLAYER::PLAYER_PED_ID())
						{
							char* PlayerName = PLAYER::GET_PLAYER_NAME(i);
							char Buffer[255];
							sprintf(Buffer, "%s ~b~[Me]", PlayerName);
							PlayerName = Buffer;
							//Menu::MenuOption(PlayerName, onlineplayer_opt) ? selectedPlayer = i : NULL;
							Menu::PlayerSub(PlayerName, onlineplayer_opt, i) ? selectedPlayer = i : NULL;
						}

						//Check if player is your friend
						else if (handle_valid && is_friend)
						{
							char* PlayerName = PLAYER::GET_PLAYER_NAME(i);
							char Buffer[255];
							sprintf(Buffer, "%s ~g~[Friend]", PlayerName);
							PlayerName = Buffer;
							Menu::MenuOption(PlayerName, onlineplayer_opt) ? selectedPlayer = i : NULL;
							//Menu::PlayerSub(PlayerName, onlineplayer_opt, i) ? selectedPlayer = i : NULL;
						}

						//Ckeck if player is from rockstar
						else if (NETWORK::NETWORK_PLAYER_IS_ROCKSTAR_DEV(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)))
						{
							char* PlayerName = PLAYER::GET_PLAYER_NAME(i);
							char Buffer[255];
							sprintf(Buffer, "%s ~r~[RockstarDev]", PlayerName);
							PlayerName = Buffer;
							//Menu::MenuOption(PlayerName, onlineplayer_opt) ? selectedPlayer = i : NULL;
							Menu::PlayerSub(PlayerName, onlineplayer_opt, i) ? selectedPlayer = i : NULL;
						}

						//Check if player is in godmode - Dosen't work yet
						else if (God = 1)
						{
							char* PlayerName = PLAYER::GET_PLAYER_NAME(i);
							char Buffer[255];
							sprintf(Buffer, "%s", PlayerName);
							PlayerName = Buffer;
							//Menu::MenuOption(PlayerName, onlineplayer_opt) ? selectedPlayer = i : NULL;
							Menu::PlayerSub(PlayerName, onlineplayer_opt, i) ? selectedPlayer = i : NULL;
						}

						//If nothing of those are true, just create a normal option
						else
						{
							//Menu::MenuOption(PlayerName, onlineplayer_opt) ? selectedPlayer = i : NULL;
							Menu::PlayerSub(PlayerName, onlineplayer_opt, i) ? selectedPlayer = i : NULL;
						}
					}
				}
				break;
			}

		}
		break;
#pragma endregion
//Options for online plyaer - selectedPlayer
#pragma region Online player
		case onlineplayer_opt:
		{
			Menu::Title("");
			Features::GetPlayerInfo(PLAYER::GET_PLAYER_NAME(selectedPlayer), selectedPlayer);//This is drawing out information about player etc...
			DisplayMarker();
			Menu::SmallTitle("Online Player");
			Menu::MenuOption("Player Teleport", player_tele);
			Menu::MenuOption("Player Vehicle", player_veh);
			Menu::MenuOption("Player Weapon", player_weapon);
			Menu::MenuOption("Player Recovery", player_drops);
			Menu::MenuOption("Player Trolling", player_Troll);
			Menu::Toggle("Spectate Player", spec);
			Menu::Toggle("Water Loop", waterLoop);
			Menu::Toggle("Fire Loop", playerfireloop);
			Menu::Toggle("Freeze Player In Place", freeze);
			if (Menu::Option("Explode Player"))
			{
				Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_ONLINE_PLAYER_ID(selectedPlayer), false);//Just rewnamed it = Get_player_ped_script... but not so
				FIRE::E_P_X(playerCoords.x, playerCoords.y, playerCoords.z, 0, 1000.f, true, false, 1000.f);
				notifyleft("Player ~r~Exploded!");
			}
			if (Menu::Option("Airstrike Player"))
			{
				Player OnlineTarget = selectedPlayer;
				OnlineStuff::AirStrikePed(OnlineTarget);
			}
			if (Menu::Option("Kick Player From Vehicle"))
			{

				Player player = selectedPlayer;

				DWORD64 args[3] = { -1089379066 , player, 48 };
				TriggerScriptEvent(1, args, 3, 1 << player);
			}
			Menu::MenuBreak("~f~[Remote Options]");
			if (Menu::Option("~b~Host ~s~Kick"))
			{
				NETWORK::NETWORK_SESSION_KICK_PLAYER(PLAYER::GET_ONLINE_PLAYER_ID(selectedPlayer));
			}
			//Non-Host Kick's
			if (Menu::Option("~r~Non-Host ~s~Kick"))
			{

				Player player = selectedPlayer;

				DWORD64 args[4] = { -1246838892 , player, 48 };
				TriggerScriptEvent(1, args, 3, 1 << player);
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { -1246838892 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { 930233414 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { 297770348 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { 498709856 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { 1432301416 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { -452918768 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { -498955166 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { 1472041801 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { 521876760 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { -741569622 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { 623353069 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { -24665064 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { -961323766 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { -1246838892 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { 930233414 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { 297770348 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { 498709856 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { 1432301416 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { 1432301416 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { -701823896 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { -327286343 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { -348418057 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { -38669034 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { 320958241 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { 1663317123 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { 552065831 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { -163616977 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { -615431083 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { -1961284186 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { 189238289 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { -125347541 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { 1667907776 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { 774421744 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { 1404046700 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { 297770348 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { 498709856 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
				{
					Player player = selectedPlayer;

					DWORD64 args[4] = { -2017629233 , player, 48 };
					TriggerScriptEvent(1, args, 3, 1 << player);
				}
			}
			if (Menu::Option("Kick"))
			{
				Network::SuperKick(selectedPlayer);
			}

		}
		break;
#pragma endregion

#pragma region Online Recovery
		case player_drops:
		{
			Menu::Title("");
			Features::GetPlayerInfo(PLAYER::GET_PLAYER_NAME(selectedPlayer), selectedPlayer);//This is drawing out information about player etc...
			DisplayMarker();
			Menu::SmallTitle("Player Recovery");
			Menu::Toggle("Money Drop", moneyDrop);
			Menu::Toggle("Money Rain", Network::MRainToggle);
			if (Menu::Option("Drop Money Bag(2K)"))
			{
				hooks::REQUEST_MODELL(0x113FD533);
				//Getting online player coords - Using Vector3
				Vector3 player = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(selectedPlayer), true);
				if (hooks::HAS_MODEL_LOADEDD(0x113FD533))
				{
					OBJECT::CREATE_AMBIENT_PICKUP(0xCE6FDD6B, player.x, player.y, player.z + 3, 0, 2000, 0x113FD533, true, false);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(0x113FD533);
				}
			}//End if statement here
			Menu::Toggle("Spawn Money Around Player(loop)", moneyRound);
			if (Menu::Option("Spawn Money Around Player"))
			{
				Ped OnlinePed2 = PLAYER::GET_PLAYER_PED(selectedPlayer);
				if ((timeGetTime() - TimePD5) > 100) {
					hooks::REQUEST_MODELL(PROP_MONEY_BAG_03);
					if (!hooks::HAS_MODEL_LOADEDD(PROP_MONEY_BAG_03)) {
						WAIT(0);
					}

					Vector3 playerPosition1 = ENTITY::GET_ENTITY_COORDS(OnlinePed2, FALSE);
#define P_M_M_D_P OBJECT::M_P_O_P_M
					P_M_M_D_P(playerPosition1.x, playerPosition1.y, playerPosition1.z, 2500, 1, PROP_MONEY_BAG_03);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PROP_MONEY_BAG_03);
					TimePD5 = timeGetTime();
				}
			}
			if (Menu::Option("Give 50K"))
			{
				SetMoneyAmmont();
			}
			Menu::MenuBreak("~f~[Outfit]");
			if (Menu::Option("Give Player Modded Outfit"))
			{
				PED::R_C_T_P(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), true); 
				notifyleft("Random outfit has been applyed to player!");
				notifyleft("Tell Player to ~g~save ~s~outfit and ~g~change lobby ~s~to see it!");
			}

		}
		break;
#pragma endregion

#pragma region Online Vehicle
		case player_veh:
		{
			Menu::Title("");
			Features::GetPlayerInfo(PLAYER::GET_PLAYER_NAME(selectedPlayer), selectedPlayer);//This is drawing out information about player etc...
			DisplayMarker();
			Menu::SmallTitle("Player Vehicle");
			if (Menu::Option("Make Players Vehicle Jump"))
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(selectedPlayer), true))
				{
					NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), true));
					if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), true)));
					{
						ENTITY::APPLY_FORCE_TO_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), true), 1, 0, 0, 20, 0, 0, 0, 1, false, true, true, true, true);
					}
				}
				else 
				{
					notifyleft2("Player are not in any vehicle!", "Novus", "Error - 0x026c532");
				}
			}
			if (Menu::Option("Clone Vehicle"))
			{
				Network::CloneVehicle();
			}
			if (Menu::Option("Repair Players Vehicle"))
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(selectedPlayer), true))
				{
					uint OnlineVehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(selectedPlayer));
					VEHICLE::SET_VEHICLE_FIXED(OnlineVehicle);
					VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(OnlineVehicle);
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(OnlineVehicle, 0);
				}
				else
				{
					notifyleft2("Player are not in any vehicle!", "Novus", "Error - 0x026c532");
				}
			}
			if (Menu::Option("Max Players Vehicle"))
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(selectedPlayer), true))
				{
					Vehicle Netvehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(selectedPlayer), false);
					VEHICLE::SET_VEHICLE_MOD_KIT(Netvehicle, 0);
					for (int i = 0; i < 50; i++)
					{
						VEHICLE::SET_VEHICLE_MOD(Netvehicle, i, VEHICLE::GET_NUM_VEHICLE_MODS(Netvehicle, i) - 1, false);
					}
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Netvehicle, "Novus");
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Netvehicle, 7, 84, 61);
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Netvehicle, 7, 84, 61);
					uint OnlineVehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(selectedPlayer));
					VEHICLE::SET_VEHICLE_FIXED(OnlineVehicle);
					VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(OnlineVehicle);
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(OnlineVehicle, 0);
				}
				else
				{
					notifyleft2("Player are not in any vehicle!", "Novus", "Error - 0x026c532");
				}
			}
			if (Menu::Option("Smash Vehicle Windows"))
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(selectedPlayer), true))
				{
					Vehicle UserVeh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(selectedPlayer), false);
					VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 10);
					VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 9);
					VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 8);
					VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 7);
					VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 6);
					VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 5);
					VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 4);
					VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 3);
					VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 2);
					VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 1);
					VEHICLE::SMASH_VEHICLE_WINDOW(UserVeh, 0);
				}
				else
				{
					notifyleft2("Player are not in any vehicle!", "Novus", "Error - 0x026c532");
				}
			}
			if (Menu::Option("Fix Vehicle Windows"))
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(selectedPlayer), true))
				{
					Vehicle UserVeh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(selectedPlayer), false);
					VEHICLE::FIX_VEHICLE_WINDOW(UserVeh, 10);
					VEHICLE::FIX_VEHICLE_WINDOW(UserVeh, 9);
					VEHICLE::FIX_VEHICLE_WINDOW(UserVeh, 8);
					VEHICLE::FIX_VEHICLE_WINDOW(UserVeh, 7);
					VEHICLE::FIX_VEHICLE_WINDOW(UserVeh, 6);
					VEHICLE::FIX_VEHICLE_WINDOW(UserVeh, 5);
					VEHICLE::FIX_VEHICLE_WINDOW(UserVeh, 4);
					VEHICLE::FIX_VEHICLE_WINDOW(UserVeh, 3);
					VEHICLE::FIX_VEHICLE_WINDOW(UserVeh, 2);
					VEHICLE::FIX_VEHICLE_WINDOW(UserVeh, 1);
					VEHICLE::FIX_VEHICLE_WINDOW(UserVeh, 0);
				}
				else
				{
					notifyleft2("Player are not in any vehicle!", "Novus", "Error - 0x026c532");
				}
			}
			if (Menu::Option("Set Custom Vehicle Plate"))
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(selectedPlayer), true))
				{
					Vehicle Userveh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(selectedPlayer), false);
					RequestControlOfEnt(Userveh);
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Userveh, CharKeyboard());
				}
				else
				{
					notifyleft2("Player are not in any vehicle!", "Novus", "Error - 0x026c532");
				}
			}
			Menu::Toggle("Rainbow Vehicle", OnlineRpaint);
			Menu::Toggle("Give Horn Boost", GiveBoost);
			//Spawn vehicle to them
			Menu::MenuBreak("~f~[Spawn Vehicle To Them]");
			if (Menu::Option("Spawn T20"))
			{
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer);
				AI::CLEAR_PED_TASKS_IMMEDIATELY(Handle);
				Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(Handle, 0);
				Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
				Vehicle zentorno = Online::SpawnVehicleToPlayer("t20", Ocoords, 0, 0.0f);
				ENTITY::SET_ENTITY_INVINCIBLE(zentorno, 0);
			}
			if (Menu::Option("Spawn Monstertruck"))
			{
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer);
				AI::CLEAR_PED_TASKS_IMMEDIATELY(Handle);
				Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(Handle, 0);
				Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
				Vehicle zentorno = Online::SpawnVehicleToPlayer("MONSTER", Ocoords, 0, 0.0f);
				ENTITY::SET_ENTITY_INVINCIBLE(zentorno, 0);
			}
		    if (Menu::Option("Spawn Tank"))
			{
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer);
				AI::CLEAR_PED_TASKS_IMMEDIATELY(Handle);
				Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(Handle, 0);
				Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
				Vehicle zentorno = Online::SpawnVehicleToPlayer("RHINO", Ocoords, 0, 0.0f);
				ENTITY::SET_ENTITY_INVINCIBLE(zentorno, 0);
			}
			if (Menu::Option("Spawn Spacedocker"))
			{
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer);
				AI::CLEAR_PED_TASKS_IMMEDIATELY(Handle);
				Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(Handle, 0);
				Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
				Vehicle zentorno = Online::SpawnVehicleToPlayer("DUNE2", Ocoords, 0, 0.0f);
				ENTITY::SET_ENTITY_INVINCIBLE(zentorno, 0);
			}
			if (Menu::Option("Spawn Formula F1")) //Kuruma2
			{
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer);
				AI::CLEAR_PED_TASKS_IMMEDIATELY(Handle);
				Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(Handle, 0);
				Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
				Vehicle zentorno = Online::SpawnVehicleToPlayer("Formula", Ocoords, 0, 0.0f);
				ENTITY::SET_ENTITY_INVINCIBLE(zentorno, 0);
			}
			if (Menu::Option("Spawn Armored Kuruma")) 
			{
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer);
				AI::CLEAR_PED_TASKS_IMMEDIATELY(Handle);
				Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(Handle, 0);
				Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
				Vehicle zentorno = Online::SpawnVehicleToPlayer("Kuruma2", Ocoords, 0, 0.0f);
				ENTITY::SET_ENTITY_INVINCIBLE(zentorno, 0);
			}
			if (Menu::Option("Spawn Sultan RS"))
			{
				int Handle = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer);//sultanrs
				AI::CLEAR_PED_TASKS_IMMEDIATELY(Handle);
				Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(Handle, 0);
				Vector3 Ocoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Handle, 0.0, 5.0, 0.0);
				Vehicle zentorno = Online::SpawnVehicleToPlayer("sultanrs", Ocoords, 0, 0.0f);
				ENTITY::SET_ENTITY_INVINCIBLE(zentorno, 0);
			}
		}
		break;
#pragma endregion

#pragma region Online Weapon
		case player_weapon:
		{
			Features::GetPlayerInfo(PLAYER::GET_PLAYER_NAME(selectedPlayer), selectedPlayer);//This is drawing out information about player etc...
			DisplayMarker();
			Menu::Title("");
			Menu::SmallTitle("Player Weapon");
			if (Menu::Option("Give Player All Weapons"))
			{
				uint Weapons[]{ 0xAF3696A1, 0x476BF155, 0xB62D1F670, 0xDFE37640, 0xC1B3C3D1, 0x99B507EA, 0x678B81B1, 0x4E875F73, 0x958A4A8F, 0x440E4788, 0x84BD7BFD, 0x1B06D571, 0x5EF9FEC4, 0x22D8FE39, 0x99AEEB3B, 0x13532244, 0x2BE6766B, 0xEFE7E2DF, 0xBFEFFF6D, 0x83BF0278, 0xAF113F99, 0x9D07F764, 0x7FD62962, 0x1D073A89, 0x7846A318, 0xE284C527, 0x9D61E50F, 0x3656C8C1, 0x05FC3C11, 0x0C472FE2, 0x33058E22, 0xA284510B, 0x4DD2DC56, 0xB1CA77B1, 0x687652CE, 0x42BF8A85, 0x93E220BD, 0x2C3731D9, 0xFDBC8A50, 0x24B17070, 0x060EC506, 0x34A67B97, 0xFDBADCED, 0x23C9F95C, 0x497FACC3, 0xF9E6AA4B, 0x61012683, 0xC0A3098D, 0xD205520E, 0xBFD21232, 0x7F229F94, 0x92A27487, 0x083839C4, 0x7F7497E5, 0xA89CB99E, 0x3AABBBAA, 0xC734385A, 0x787F0BB, 0x47757124, 0xD04C944D, GAMEPLAY::GET_HASH_KEY("WEAPON_HATCHET"), GAMEPLAY::GET_HASH_KEY("WEAPON_RAILGUN") };
				for (int i = 0; i < (sizeof(Weapons) / 4); i++)
					hooks::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), Weapons[i], 9999, 1);
				    notifyleft2("You gived all weapons!", "Novus", PLAYER::GET_PLAYER_NAME(selectedPlayer));
			}
			if (Menu::Option("Give All MK2 Weapons"))
			{
				uint Weapons[] = { GAMEPLAY::GET_HASH_KEY("weapon_revolver_mk2"), GAMEPLAY::GET_HASH_KEY("weapon_snspistol_mk2"), GAMEPLAY::GET_HASH_KEY("weapon_smg_mk2"), GAMEPLAY::GET_HASH_KEY("weapon_pumpshotgun_mk2"), GAMEPLAY::GET_HASH_KEY("weapon_assaultrifle_mk2"), GAMEPLAY::GET_HASH_KEY("weapon_carbinerifle_mk2"), GAMEPLAY::GET_HASH_KEY("weapon_specialcarbine_mk2"), GAMEPLAY::GET_HASH_KEY("weapon_bullpuprifle_mk2"), GAMEPLAY::GET_HASH_KEY("weapon_combatmg_mk2"), GAMEPLAY::GET_HASH_KEY("weapon_heavysniper_mk2"), GAMEPLAY::GET_HASH_KEY("weapon_marksmanrifle_mk2"), };
				for (int i = 0; i < (sizeof(Weapons) / 4); i++)
					hooks::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), Weapons[i], 9999, 1);
				    notifyleft2("You gived all  MK2 weapons!", "Novus", PLAYER::GET_PLAYER_NAME(selectedPlayer));
			}
			if (Menu::Option("Remove All Weapons"))
			{
				WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), true);
				notifyleft2("You removed all weapons!", "Novus", PLAYER::GET_PLAYER_NAME(selectedPlayer));
			}
			Menu::MenuBreak("~f~[Weapon Mods]");
			Menu::Toggle("Give Explosive Gun", player_explo_gun);//Explosive gun to player
			Menu::Toggle("Give Money Gun", player_money_gun);//Money gun to player
		}
		break;
#pragma endregion

#pragma region Player Trolling
		case player_Troll:
		{
			Menu::Title("");
			Features::GetPlayerInfo(PLAYER::GET_PLAYER_NAME(selectedPlayer), selectedPlayer);//This is drawing out information about player etc...
			DisplayMarker();
			Menu::SmallTitle("Player Trolling");
			Menu::MenuOption("Attach Object", obj_player);
			Menu::MenuOption("Extra Trolling", EXTRA_trolling);
			Menu::MenuOption("Remote Options", remote_player);
			if (Menu::Option("Kill Player")) {

				int selectedPed = selectedPlayer;
				Vector3 KillPosition = { -15000, -15000, -50 };
				Features::teleporttocoords(selectedPed, KillPosition);

			}
			if (Menu::Option("Steal Outfit"))
			{

				Ped playerPed = PLAYER::PLAYER_PED_ID();
				Ped theirPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer);

				for (int i = 0; i < 12; i++)
				{
					PED::SET_PED_COMPONENT_VARIATION(playerPed, i, PED::GET_PED_DRAWABLE_VARIATION(theirPed, i),
						PED::GET_PED_TEXTURE_VARIATION(theirPed, i),
						PED::GET_PED_PALETTE_VARIATION(theirPed, i));
					for (int i = 0; i < 2; i++)
					{
						WAIT(0);
					}
				}
			}
			Menu::Toggle("Crash Player", CrashPlayerNow); //Don't use to close players!
			if (Menu::Option("Instant Crash"))
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY((PLAYER::GET_PLAYER_PED(selectedPlayer), true));
				if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY((PLAYER::GET_PLAYER_PED(selectedPlayer), true)))
				{
					OnlineStuff::InstantCrashPlayer(PLAYER::GET_PLAYER_PED(selectedPlayer));
				}
			}
			//if (Menu::Option("SVT Crash"))
			//{
			//	crash_steps();
			//}
			if (Menu::Option("Infinite Loading Screen"))
			{
				NewOption::InfiLoading();
			}
			if (Menu::Option("Transaction Error"))
			{
				int ThisOnlinePed = selectedPlayer;
				NewOption::TransactionError(ThisOnlinePed);
			}
			if (Menu::Option("CEO Kick"))
			{
				NewOption::CEOKick(true);
			}
			if (Menu::Option("CEO Ban"))
			{
				NewOption::CEOBan(true);
			}
			if (Menu::Option("Send To Job"))
			{
				NewOption::SendPlayerToJob(true);
			}
			Menu::MenuBreak("~f~[Troll Messages]");
			if (Menu::Option("Troll Message"))
			{
				NewOption::TrollMessage();
			}
			if (Menu::Option("Spectating Message"))
			{
				int thisPlayer = selectedPlayer;
				NewOption::MessageSpam(thisPlayer, SendSpectatingMessage);
			}
			if (Menu::Option("Idle Kick Message"))
			{
				int thisPlayer = selectedPlayer;
				NewOption::MessageSpam(thisPlayer, SendIdleKickMessage);
			}
			if (Menu::Option("Going Psycho Message"))
			{
				int thisPlayer = selectedPlayer;
				NewOption::MessageSpam(thisPlayer, SendPsychoMessage);
			}
			if (Menu::Option("Goon Remove Message"))
			{
				int thisPlayer = selectedPlayer;
				NewOption::MessageSpam(thisPlayer, SendGoonRemoveMessage);
			}
			if (Menu::Option("Goon Leave Message"))
			{
				int thisPlayer = selectedPlayer;
				NewOption::MessageSpam(thisPlayer, SendGoonLeaveMessage);
			}
			if (Menu::Option("Goon Join Message"))
			{
				int thisPlayer = selectedPlayer;
				NewOption::MessageSpam(thisPlayer, SendGoonJoinMessage);
			}
			Menu::MenuBreak("~f~[Invites]");
			if (Menu::Option("To Apartment"))
			{
				int SelectToInvite = selectedPlayer;
				NewOption::PlayerInvitePlace(SelectToInvite, 70); //70 = Apartment
			}
			if (Menu::Option("To Clubhouse"))
			{
				int SelectToInvite = selectedPlayer;
				NewOption::PlayerInvitePlace(SelectToInvite, 3); //3 = Clubhouse
			}
			if (Menu::Option("To Office"))
			{
				int SelectToInvite = selectedPlayer;
				NewOption::PlayerInvitePlace(SelectToInvite, 2); //2 = Office
			}
			if (Menu::Option("To Office Garage"))
			{
				int SelectToInvite = selectedPlayer;
				NewOption::PlayerInvitePlace(SelectToInvite, 6); //2 = Office Garage
			}
			if (Menu::Option("To Yacht"))
			{
				int SelectToInvite = selectedPlayer;
				NewOption::PlayerInvitePlace(SelectToInvite, 1); //1 = Yacht
			}
			if (Menu::Option("Give Never Wanted"))
			{
				int thisCurentOnline = selectedPlayer;
				NewOption::GiveNeverWanted(thisCurentOnline);
			}
			if (Menu::Option("Cage Player"))
			{
				Online::trapcage(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer));
			}
			if (Menu::Option("Clone Player"))
			{
				PED::CLONE_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), 1, 1, 1);
			}

			if (Menu::Option("Ram Player")) {
				float offset;
				Hash vehmodel = GAMEPLAY::GET_HASH_KEY("SANDKING");
				hooks::REQUEST_MODELL(vehmodel);

				while (!hooks::HAS_MODEL_LOADEDD(vehmodel)) WAIT(0);
				Vector3 pCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), 0.0, -10.0, 0.0);

				if (STREAMING::IS_MODEL_IN_CDIMAGE(vehmodel) && STREAMING::IS_MODEL_A_VEHICLE(vehmodel))
				{
					Vector3 dim1, dim2;
					GAMEPLAY::GET_MODEL_DIMENSIONS(vehmodel, &dim1, &dim2);

					offset = dim2.y * 1.6;

					Vector3 dir = ENTITY::GET_ENTITY_FORWARD_VECTOR(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer));
					float rot = (ENTITY::GET_ENTITY_ROTATION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), 0)).z;

					Vehicle veh = VEHICLE::CREATE_VEHICLE(vehmodel, pCoords.x + (dir.x * offset), pCoords.y + (dir.y * offset), pCoords.z, rot, 1, 1);

					VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
					ENTITY::SET_ENTITY_VISIBLE(veh, true, 0);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 700.0);
				}

			}
			if (Menu::Option("Shake Cam"))
			{
				Vector3 targetCords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), false);
				FIRE::ADD_EXPLOSION(targetCords.x, targetCords.y, targetCords.z, 4, 0.f, false, true, 1000.f);
			}
			Menu::Toggle("Explode Loop", explo_loop);
			int eclone[1000];
			int egcount = 1;
			if (Menu::Option("Spawn Enemy")) {
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash railgun = GAMEPLAY::GET_HASH_KEY("WEAPON_RAILGUN");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("s_m_m_chemsec_01");
				hooks::REQUEST_MODELL(pedm);
				while (!hooks::HAS_MODEL_LOADEDD(pedm))
					WAIT(0);
				eclone[egcount] = PED::LEAKEAE_AEAJEJAEKAJE_EE_E(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				ENTITY::SET_ENTITY_INVINCIBLE(eclone[egcount], false);
				PED::SET_PED_COMBAT_ABILITY(eclone[egcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(eclone[egcount], railgun, railgun, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(eclone[egcount], true);
				AI::TASK_COMBAT_PED(eclone[egcount], selectedplayer, 1, 1);
				PED::SET_PED_ALERTNESS(eclone[egcount], 1000);
				PED::SET_PED_COMBAT_RANGE(eclone[egcount], 1000);
				egcount++;
			}
			int clone[1000];
			int gcount = 1;
			if (Menu::Option("Spawn Bodyguard")) {
				Ped selectedplayer = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer);
				if (!ENTITY::DOES_ENTITY_EXIST(selectedplayer)) return;
				Hash railgun = GAMEPLAY::GET_HASH_KEY("WEAPON_RAILGUN");
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(selectedplayer, 1);
				Hash pedm = GAMEPLAY::GET_HASH_KEY("u_m_y_pogo_01"); //u_m_y_pogo_01
				hooks::REQUEST_MODELL(pedm);
				while (!hooks::HAS_MODEL_LOADEDD(pedm))
					WAIT(0);
				int my_group = PLAYER::GET_PLAYER_GROUP(selectedplayer);
				clone[gcount] = PED::LEAKEAE_AEAJEJAEKAJE_EE_E(26, pedm, pos.x + rand() % 1, pos.y + rand() % 1, pos.z + 1, 0, 1, 1);
				PED::SET_PED_AS_GROUP_LEADER(selectedplayer, my_group);
				PED::SET_PED_AS_GROUP_MEMBER(clone[gcount], my_group);
				PED::SET_PED_NEVER_LEAVES_GROUP(clone[gcount], my_group);
				ENTITY::SET_ENTITY_INVINCIBLE(clone[gcount], false);
				PED::SET_PED_COMBAT_ABILITY(clone[gcount], 100);
				WEAPON::GIVE_WEAPON_TO_PED(clone[gcount], railgun, railgun, 9999, 9999);
				PED::SET_PED_CAN_SWITCH_WEAPON(clone[gcount], true);
				PED::SET_GROUP_FORMATION(my_group, 3);
				PED::SET_PED_MAX_HEALTH(clone[gcount], 5000);
				gcount++;
			}
			if (Menu::Option("Attach You To Player"))
			{
				ENTITY::ATTACH_ENTITY_TO_ENTITY(PLAYER::PLAYER_PED_ID(), PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), 0, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, true, true, false, true, 2, true);
			}
			if (Menu::Option("Detach From Player"))
			{
				ENTITY::DETACH_ENTITY(PLAYER::PLAYER_PED_ID(), true, true);
			}

		}
		break;
#pragma endregion

#pragma region EXTRA TROLLING
		case EXTRA_trolling:
		{
			Menu::Title("");
			Features::GetPlayerInfo(PLAYER::GET_PLAYER_NAME(selectedPlayer), selectedPlayer);//This is drawing out information about player etc...
			DisplayMarker();
			Menu::SmallTitle("E X T R A   T R O L L I N G");
			Menu::Toggle("Reload Loop", re_loop);
			Menu::Toggle("RGB Weapons", RgbGun);
			if (Menu::Option("Kill Player")) {

				int selectedPed = selectedPlayer;
				Vector3 KillPosition = { -15000, -15000, -50 };
				Features::teleporttocoords(selectedPed, KillPosition);

			}
			if (Menu::Option("Steal Outfit"))
			{

				Ped playerPed = PLAYER::PLAYER_PED_ID();
				Ped theirPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer);

				for (int i = 0; i < 12; i++)
				{
					PED::SET_PED_COMPONENT_VARIATION(playerPed, i, PED::GET_PED_DRAWABLE_VARIATION(theirPed, i),
						PED::GET_PED_TEXTURE_VARIATION(theirPed, i),
						PED::GET_PED_PALETTE_VARIATION(theirPed, i));
					for (int i = 0; i < 2; i++)
					{
						WAIT(0);
					}
				}
			}
			Menu::Toggle("Crash Player", CrashPlayerNow); //Don't use to close players!
			if (Menu::Option("Instant Crash"))
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY((PLAYER::GET_PLAYER_PED(selectedPlayer), true));
				if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY((PLAYER::GET_PLAYER_PED(selectedPlayer), true)))
				{
                     OnlineStuff::InstantCrashPlayer(PLAYER::GET_PLAYER_PED(selectedPlayer));
				}
            }
			//if (Menu::Option("SVT Crash"))
			//{
			//	crash_steps();
			//}
			if (Menu::Option("Infinite Loading Screen"))
			{
				NewOption::InfiLoading();
			}
			if (Menu::Option("Transaction Error"))
			{
				int ThisOnlinePed = selectedPlayer;
				NewOption::TransactionError(ThisOnlinePed);
			}
			if (Menu::Option("CEO Kick"))
			{
				NewOption::CEOKick(true);
            }
			if (Menu::Option("CEO Ban"))
			{
				NewOption::CEOBan(true);
			}
			if (Menu::Option("Send To Job"))
			{
				NewOption::SendPlayerToJob(true);
			}
			Menu::MenuBreak("~f~[Troll Messages]");
			if (Menu::Option("Troll Message"))
			{
				NewOption::TrollMessage();
			}
			if (Menu::Option("Spectating Message"))
			{
				int thisPlayer = selectedPlayer;
				NewOption::MessageSpam(thisPlayer, SendSpectatingMessage);
			}
			if (Menu::Option("Idle Kick Message"))
			{
				int thisPlayer = selectedPlayer;
				NewOption::MessageSpam(thisPlayer, SendIdleKickMessage);
			}
			if (Menu::Option("Going Psycho Message"))
			{
				int thisPlayer = selectedPlayer;
				NewOption::MessageSpam(thisPlayer, SendPsychoMessage);
			}
			if (Menu::Option("Goon Remove Message"))
			{
				int thisPlayer = selectedPlayer;
				NewOption::MessageSpam(thisPlayer, SendGoonRemoveMessage);
			}
			if (Menu::Option("Goon Leave Message"))
			{
				int thisPlayer = selectedPlayer;
				NewOption::MessageSpam(thisPlayer, SendGoonLeaveMessage);
			}
			if (Menu::Option("Goon Join Message"))
			{
				int thisPlayer = selectedPlayer;
				NewOption::MessageSpam(thisPlayer, SendGoonJoinMessage);
			}
			Menu::MenuBreak("~f~[Invites]");
			if (Menu::Option("To Apartment"))
			{
				int SelectToInvite = selectedPlayer;
				NewOption::PlayerInvitePlace(SelectToInvite, 70); //70 = Apartment
			}
			if (Menu::Option("To Clubhouse"))
			{
				int SelectToInvite = selectedPlayer;
				NewOption::PlayerInvitePlace(SelectToInvite, 3); //3 = Clubhouse
			}
			if (Menu::Option("To Office"))
			{
				int SelectToInvite = selectedPlayer;
				NewOption::PlayerInvitePlace(SelectToInvite, 2); //2 = Office
			}
			if (Menu::Option("To Office Garage"))
			{
				int SelectToInvite = selectedPlayer;
				NewOption::PlayerInvitePlace(SelectToInvite, 6); //2 = Office Garage
			}
			if (Menu::Option("To Yacht"))
			{
				int SelectToInvite = selectedPlayer;
				NewOption::PlayerInvitePlace(SelectToInvite, 1); //1 = Yacht
			}
		}
		break;
#pragma endregion

#pragma region Remote Options
		case remote_player:
		{
			Menu::Title("");
			Menu::SmallTitle("R E M O T E   O P T I O N S");
			if (Menu::Option("Infinite Loading Screen"))
			{
				NewOption::InfiLoading();
			}
			if (Menu::Option("Transaction Error"))
			{
				int ThisOnlinePed = selectedPlayer;
				NewOption::TransactionError(ThisOnlinePed);
			}
			if (Menu::Option("CEO Kick"))
			{
				NewOption::CEOKick(true);
			}
			if (Menu::Option("CEO Ban"))
			{
				NewOption::CEOBan(false);
			}
			if (Menu::Option("Send To Job"))
			{
				NewOption::SendPlayerToJob(false);
			}
			if (Menu::Option("Blackscreen"))
			{
				Network::GiveBlackscreen(selectedPlayer);
			}

			if (Menu::Option("Remote Off Radar"))
			{
				Network::RemoteOffTheRadar(selectedPlayer);
			}

			if (Menu::Option("CEO Kick"))
			{
				NewOption::CEOKick(false);
			}

			if (Menu::Option("CEO Ban"))
			{
				NewOption::CEOBan(false);
			}

			if (Menu::Option("Send To Job"))
			{
				NewOption::SendPlayerToJob(true);
			}

			if (Menu::Option("Give Cops"))
			{
				Network::remoteSendCops();
			}

			if (Menu::Option("Remove Cops"))
			{
				Network::RemoteNoCops(selectedPlayer);
			}
			Menu::MenuBreak("~f~[Trolling Messages]");
			if (Menu::Option("Troll Message"))
			{
				NewOption::TrollMessage();
			}
			if (Menu::Option("Spectating Message"))
			{
				int thisPlayer = selectedPlayer;
				NewOption::MessageSpam(thisPlayer, SendSpectatingMessage);
			}
			if (Menu::Option("Idle Kick Message"))
			{
				int thisPlayer = selectedPlayer;
				NewOption::MessageSpam(thisPlayer, SendIdleKickMessage);
			}
			if (Menu::Option("Going Psycho Message"))
			{
				int thisPlayer = selectedPlayer;
				NewOption::MessageSpam(thisPlayer, SendPsychoMessage);
			}
			if (Menu::Option("Goon Remove Message"))
			{
				int thisPlayer = selectedPlayer;
				NewOption::MessageSpam(thisPlayer, SendGoonRemoveMessage);
			}
			if (Menu::Option("Goon Leave Message"))
			{
				int thisPlayer = selectedPlayer;
				NewOption::MessageSpam(thisPlayer, SendGoonLeaveMessage);
			}
			if (Menu::Option("Goon Join Message"))
			{
				int thisPlayer = selectedPlayer;
				NewOption::MessageSpam(thisPlayer, SendGoonJoinMessage);
			}
			Menu::MenuBreak("~f~[Invites]");
			if (Menu::Option("To Apartment"))
			{
				int SelectToInvite = selectedPlayer;
				NewOption::PlayerInvitePlace(SelectToInvite, 70); //70 = Apartment
			}
			if (Menu::Option("To Clubhouse"))
			{
				int SelectToInvite = selectedPlayer;
				NewOption::PlayerInvitePlace(SelectToInvite, 3); //3 = Clubhouse
			}
			if (Menu::Option("To Office"))
			{
				int SelectToInvite = selectedPlayer;
				NewOption::PlayerInvitePlace(SelectToInvite, 2); //2 = Office
			}
			if (Menu::Option("To Office Garage"))
			{
				int SelectToInvite = selectedPlayer;
				NewOption::PlayerInvitePlace(SelectToInvite, 6); //2 = Office Garage
			}
			if (Menu::Option("To Yacht"))
			{
				int SelectToInvite = selectedPlayer;
				NewOption::PlayerInvitePlace(SelectToInvite, 1); //1 = Yacht
			}
		}
		break;
#pragma endregion

#pragma region Player Objects
		case obj_player:
		{
			Menu::Title("");
			Features::GetPlayerInfo(PLAYER::GET_PLAYER_NAME(selectedPlayer), selectedPlayer);//This is drawing out information about player etc...
			DisplayMarker();
			Menu::SmallTitle("Attach Object");
			if (Menu::Option("Delete All Objects")) {
				for (int i = 0; i < 5; i++) {
					Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), 1);
					GAMEPLAY::CLEAR_AREA_OF_PEDS(coords.x, coords.y, coords.z, 2, 0);
					GAMEPLAY::CLEAR_AREA_OF_OBJECTS(coords.x, coords.y, coords.z, 2, 0);
					GAMEPLAY::CLEAR_AREA_OF_VEHICLES(coords.x, coords.y, coords.z, 2, 0, 0, 0, 0, 0);
					for (int i = 0; i < 136; i++) {
						Object obj = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(coords.x, coords.y, coords.z, 4.0, GAMEPLAY::GET_HASH_KEY(objects[i]), 0, 0, 1);

						if (ENTITY::DOES_ENTITY_EXIST(obj) && ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(obj, PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer))) {
							RequestControlOfEnt(obj);
							int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(obj);
							NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
							Online::RequestControlOfid(netID);
							ENTITY::DETACH_ENTITY(obj, 1, 1);
							if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(obj)) {
								ENTITY::SET_ENTITY_AS_MISSION_ENTITY(obj, 1, 1);
								ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&obj);
								ENTITY::DELETE_ENTITY(&obj);
							}
						}
					}
				}
			}
			if (Menu::Option("Plate"))
			{
				Online::attachobjects2("p_oil_slick_01");
			}
			if (Menu::Option("EMP"))
			{
				Online::attachobjects2("hei_prop_heist_emp");
			}
			if (Menu::Option("Big Orange Ball ~o~SEMI-GODMODE"))
			{
				Online::attachobjects2("prop_juicestand");
			}
			if (Menu::Option("Weed Plant"))
			{
				Online::attachobjects2("prop_weed_01");
			}
			if (Menu::Option("Safe"))
			{
				Online::attachobjects2("p_v_43_safe_s");
			}
			if (Menu::Option("Ufo"))
			{
				Online::attachobjects2("p_spinning_anus_s");
			}
			if (Menu::Option("Toilet"))
			{
				Online::attachobjects2("prop_ld_toilet_01");
			}
			if (Menu::Option("Xmas Tree"))
			{
				Online::attachobjects2("prop_xmas_tree_int");
			}
			if (Menu::Option("Windmill"))
			{
				Online::attachobjects2("prop_windmill_01");
			}
			if (Menu::Option("Radar"))
			{
				Online::attachobjects2("prop_air_bigradar");
			}
		}
		break;
#pragma endregion

#pragma region Player Teleport Menu
		case player_tele:
		{
			Menu::Title("");
			Features::GetPlayerInfo(PLAYER::GET_PLAYER_NAME(selectedPlayer), selectedPlayer);//This is drawing out information about player etc...
			DisplayMarker();
			Menu::SmallTitle("Player Teleport");
			Menu::MenuOption("Teleport To Locations ", player_tele_loc);
			if (Menu::Option("Teleport To Player"))
			{
				Entity handle;
				Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), false);
				PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) ? handle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) : handle = PLAYER::PLAYER_PED_ID();
				ENTITY::SET_ENTITY_COORDS(handle, coords.x, coords.y, coords.z, false, false, false, false);
			}
			if (Menu::Option("Teleport Into Their Vehicle"))
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(selectedPlayer), false);
				for (int i = -1; i < 16; i++)
				{
					if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, i))
					{
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, i);
					}
				}
			}
			if (Menu::Option("Teleport To You [Vehicle]"))
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(selectedPlayer, true))
				{
					OnlineStuff::TPTheirVeh(selectedPlayer);
					notifyMap("Player has been teleported to you!");
				}
				else
				{
					notifyMap("~r~ERROR: ~w~Player is not in any vehicle");
				}
			}
		}
		break;
#pragma endregion


#pragma endregion

#pragma region Online All Players
		case all_players:
		{
			Menu::Title("");
			Menu::SmallTitle("All Players");
			Menu::MenuOption("Drops", all_drops);
			Menu::MenuOption("Lobby Message", ses_mgs);
			Menu::Toggle("ESP", esp_all);
			Menu::Toggle("Money Drop", Features::AllDropOn, [] { Features::AllMoneyDrop(Features::AllDropOn); });
			if (Menu::Option("Give Weps in the Lobby")) 
			{

				for (int i = 0; i < 32; i++)
				{
					if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) {
						Player allplayers = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
						if (!(cstrcmp(PLAYER::GET_PLAYER_NAME(i), "-")))
						{
							if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) != PLAYER::PLAYER_PED_ID())
							{
								uint Weapons[] = { 0x99B507EA, 0x678B81B1, 0x4E875F73, 0x958A4A8F, 0x440E4788, 0x84BD7BFD, 0x1B06D571, 0x5EF9FEC4, 0x22D8FE39, 0x99AEEB3B, 0x13532244, 0x2BE6766B, 0xEFE7E2DF, 0xBFEFFF6D, 0x83BF0278, 0xAF113F99, 0x9D07F764, 0x7FD62962, 0x1D073A89, 0x7846A318, 0xE284C527, 0x9D61E50F, 0x3656C8C1, 0x05FC3C11, 0x0C472FE2, 0x33058E22, 0xA284510B, 0x4DD2DC56, 0xB1CA77B1, 0x687652CE, 0x42BF8A85, 0x93E220BD, 0x2C3731D9, 0xFDBC8A50, 0x24B17070, 0x060EC506, 0x34A67B97, 0xFDBADCED, 0x23C9F95C, 0x497FACC3, 0xF9E6AA4B, 0x61012683, 0xC0A3098D, 0xD205520E, 0xBFD21232, 0x7F229F94, 0x92A27487, 0x083839C4, 0x7F7497E5, 0xA89CB99E, 0x3AABBBAA, 0xC734385A, 0x787F0BB, 0x47757124, 0xD04C944D };
								for (int i = 0; i < (sizeof(Weapons) / 4); i++) {
									WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(allplayers), Weapons[i], 9999, 1);
								}
							}
						}
					}
				}
			}
			if (Menu::Option("Remove All Weapons")) 
			{
				for (int i = 0; i < 33; i++)
				{
					Player allplayers = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
                    WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(allplayers), true);
				}
			}
            if (Menu::Option("Explode All Players")) {
				for (int i = 0; i < 33; i++)
				{
					if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) == PLAYER::PLAYER_PED_ID()) continue;
					{
						Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);//Get all online players coords
						FIRE::ADD_EXPLOSION(coords.x, coords.y, coords.z, 0, 1000.f, true, false, 100.f);
					}
				}
			}
			if (Menu::Option("Kick All Players")) {
				for (int i = 0; i < 32; i++)
				{
					if (i != PLAYER::PLAYER_ID())
					{

						DWORD64 args[3] = { -1246838892 , i, 48 };
						TriggerScriptEvent(1, args, 3, 1 << i);

					}
				}
			}

		}
		break;
#pragma endregion

#pragma region All Teleport
		case allP_teleport:
		{
			Menu::Title("");
			Menu::SmallTitle("Teleport All");
			if (Menu::Option("Eclipse Towers")) { Network::Teleport1(true); }
			if (Menu::Option("West Vinewood")) { Network::Teleport2(true); }
			if (Menu::Option("Las Lagunas")) { Network::Teleport3(true); }
			if (Menu::Option("Spanish Ave")) { Network::Teleport4(true); }
			if (Menu::Option("Power St")) { Network::Teleport5(true); }
			if (Menu::Option("Del Perro")) { Network::Teleport6(true); }
			if (Menu::Option("Milton Rd")) { Network::Teleport7(true); }
			if (Menu::Option("The Royale")) { Network::Teleport8(true); }
			if (Menu::Option("La Puerta")) { Network::Teleport9(true); }
			if (Menu::Option("Rockford Dr")) { Network::Teleport10(true); }
			if (Menu::Option("Dream Tower")) { Network::Teleport11(true); }
			if (Menu::Option("San Vitas")) { Network::Teleport12(true); }
			if (Menu::Option("Vespucci Blvd")) { Network::Teleport13(true); }
			if (Menu::Option("Cougar Ave")) { Network::Teleport14(true); }
			if (Menu::Option("Prosperity St")) { Network::Teleport15(true); }
			if (Menu::Option("Weazel Plaza")) { Network::Teleport16(true); }
			if (Menu::Option("Del Perro Office")) { Network::Teleport17(true); }
			if (Menu::Option("Maze Bank West Office")) { Network::Teleport18(true); }
			if (Menu::Option("Arcadius Office")) { Network::Teleport19(true); }
			if (Menu::Option("Maze Bank Office")) { Network::Teleport20(true); }
		}
		break;
#pragma endregion

#pragma region All Player Money
		case all_drops:
		{
			Menu::Title("");
			Menu::SmallTitle("Lobby Drops");
			Menu::Toggle("Enable Money Drop", Features::AllDropOn, [] { Features::AllMoneyDrop(Features::AllDropOn); });
			//if (Menu::Int("Drop Delay", Features::DropDelay, 0, 500))
			//{
			//	if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) 
			//	{
			//		Features::DropDelay = NumberKeyboard();
			//	}
			//}
			//if (Menu::Int("Money Model", Features::MoneyType, 0, 26))
			//{
			//	if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
			//	{
			//		Features::MoneyType = NumberKeyboard();
			//	}
			//}
			Menu::MenuBreak("~f~Money Rain");
			Menu::Toggle("Enable Money Rain", Network::AllPlayerMoneyR);
			Menu::MenuBreak("~f~---------------------");
			if (Menu::Option("Drop All Bodyarmor"))
			{
				notifyMap("Not added yet!");
			}
		}
		break;
#pragma endregion

#pragma region lobby message
		case ses_mgs:
		{
			Menu::Title("");
			Menu::SmallTitle("Lobby Message");
			if (Menu::Option("Custom Message"))
			{
				for (int i = 0; i < 33; i++)
				{

					GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, "", "", "", "", "", "", 60);
						while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == false) WAIT(0);
						int handle[76]; //var num3 = sub_34009(A_0, (A_1) + 264, (A_1) + 272);
						NETWORK::N_H_F_P(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), &handle[0], 13);
						NETWORK::SEND_NETWORK_TEXT_MESSAGE(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT(), &handle[0]);
				}
			}
			if (Menu::Option("Come to airport"))
			{
				for (int i = 0; i < 33; i++)
				{
					char* mgs = "Come to airport";
					int handle[76];
					NETWORK::N_H_F_P(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), &handle[0], 13);
					NETWORK::SEND_NETWORK_TEXT_MESSAGE(mgs, &handle[0]);
				}
			}
			if (Menu::Option("Who want's money?"))
			{
				for (int i = 0; i < 32; i++)
				{
					char* mgs = "Who want's money?";
					int handle[76];
					NETWORK::N_H_F_P(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), &handle[0], 13);
					NETWORK::SEND_NETWORK_TEXT_MESSAGE(mgs, &handle[0]);
				}
			}
			if (Menu::Option("Good bye everyone!"))
			{
				for (int i = 0; i < 32; i++)
				{
					char* mgs = "Good bye everyone!";
					int handle[76];
					NETWORK::N_H_F_P(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), &handle[0], 13);
					NETWORK::SEND_NETWORK_TEXT_MESSAGE(mgs, &handle[0]);
				}
			}
		}
		break;
#pragma endregion

#pragma region Lobby Rain
		case lobby_rain:
		{
			Menu::Title("");
			Menu::SmallTitle("Waypoint Money");
			Menu::Toggle("Enable Money Rain", AWSOME::RainToggle);
			Menu::MenuBreak("~f~Money");
			if (Menu::Int("Amount:", AWSOME::RainAmount, 1, 2500))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) 
				{
					AWSOME::RainAmount = NumberKeyboard();
				}
			}
			Menu::MenuBreak("~f~Money Model");
			if (Menu::Option("Paperbag"))
			{
				AWSOME::MoneyType = 0;
			}
			if (Menu::Option("Paperbag2"))
			{
				AWSOME::MoneyType = 1;
			}
			if (Menu::Option("Moneybag"))
			{
				AWSOME::MoneyType = 2;
			}
			if (Menu::Option("Alien egg"))
			{
				AWSOME::MoneyType = 3;
			}
			if (Menu::Option("Guitar"))
			{
				AWSOME::MoneyType = 4;
			}
			if (Menu::Option("Grave"))
			{
				AWSOME::MoneyType = 5;
			}
			if (Menu::Option("Dildo"))
			{
				AWSOME::MoneyType = 6;
			}
			if (Menu::Option("Dummy"))
			{
				AWSOME::MoneyType = 7;
			}
			if (Menu::Option("Toilet"))
			{
				AWSOME::MoneyType = 8;
			}
			if (Menu::Option("Weed"))
			{
				AWSOME::MoneyType = 9;
			}
			if (Menu::Option("Oil"))
			{
				AWSOME::MoneyType = 10;
			}
		}
		break;
#pragma endregion

#pragma region protections
		case protections:
		{
			Menu::Title("");
			Menu::SmallTitle("Protections");
			Menu::Toggle("Anti Script Events", Features::lgevts);
			Menu::Toggle("Display Message", Features::lgevtssss);
			Menu::Toggle("Anti Freeze", Features::lgevtssss); // thats all //Okey i gonna show u teleport?
		//	Menu::Toggle("Freeze", antiFreeze, [] { Hooking::defuseEvent(RockstarEvent::NETWORK_CLEAR_PED_TASKS_EVENT, antiFreeze); });
			Menu::Toggle("Remove Weapons", noRemoveWeps, [] { Hooking::defuseEvent(RockstarEvent::REMOVE_ALL_WEAPONS_EVENT, noRemoveWeps); });
			Menu::Toggle("Give Weapons", noGiveWeps, [] { Hooking::defuseEvent(RockstarEvent::GIVE_WEAPON_EVENT, noGiveWeps); });
			Menu::Toggle("Drop Pickups", noDrop, [] { Hooking::defuseEvent(RockstarEvent::GIVE_PICKUP_REWARDS_EVENT, noDrop); });
			Menu::Toggle("Explode Vehicle", vehExplode, [] { Hooking::defuseEvent(RockstarEvent::BLOW_UP_VEHICLE_EVENT, vehExplode); });
			Menu::Toggle("Play Sound", playSound, [] { Hooking::defuseEvent(RockstarEvent::NETWORK_PLAY_SOUND_EVENT, playSound); });
			Menu::Toggle("Bank Requset", bankReq, [] { Hooking::defuseEvent(RockstarEvent::NETWORK_BANK_REQUEST_EVENT, bankReq); });
			Menu::Toggle("Time", Timeproc, [] {Hooking::defuseEvent(RockstarEvent::GAME_CLOCK_EVENT, Timeproc); });
			Menu::Toggle("Weather", Weatherproc, [] {Hooking::defuseEvent(RockstarEvent::GAME_WEATHER_EVENT, Weatherproc); });
			//Menu::Toggle("Start Scene", start_scene, [] {Hooking::defuseEvent(RockstarEvent::NETWORK_START_SYNCED_SCENE_EVENT, start_scene); });
			//Menu::Toggle("Reports", send_report2, [] {Hooking::defuseEvent(RockstarEvent::REPORT_MYSELF_EVENT, send_report2); }); 
			Menu::Toggle("Anti FX", send_fx, [] {Hooking::defuseEvent(RockstarEvent::NETWORK_PTFX_EVENT, send_fx); });

		}
		break;
#pragma endregion

#pragma region new protections
		case NewProtect:
		{
			Menu::Title("");
			Menu::SmallTitle("Protections");
			Menu::Toggle("Anti Script Events", Features::lgevts);                                                                     //1
			Menu::Toggle("Display Blocked Scripts", Features::lgevtssss);                                                             //2
			Menu::Toggle("Display Blocks", Protect::eventShieldBool, [] { Protect::eventShield(); });                                 //3 Just displays and redicts Trigger_Script_Event - NOT WORKING YET [X]
			Menu::Toggle("General", Protect::General, [] { Protect::GeneralProtect(Protect::General); });                             //4
			Menu::Toggle("Kick", Protect::antiKick, [] { Protect::AntiKick(Protect::antiKick); });                                    //6
			Menu::Toggle("Freeze", Protect::antiFreeze, [] { Protect::AntiFreeze(Protect::antiFreeze); });                            //7
			Menu::Toggle("Explosion", Protect::antiExplosion, [] { Protect::AntiExplosion(Protect::antiExplosion); });                //8
			Menu::Toggle("Weather-Time", Protect::antiweatherTime, [] { Protect::antiWeatherTime(Protect::antiweatherTime); });       //9
			Menu::Toggle("Stats", Protect::antiStat, [] { Protect::AntiStat(Protect::antiStat); });                                   //19
			Menu::Toggle("Control", Protect::antiControl, [] { Protect::AntiControl(Protect::antiControl); });                        //11
			Menu::Toggle("Weapon", Protect::antiWeapon, [] { Protect::AntiWeapon(Protect::antiWeapon); });                            //12
			Menu::Toggle("Wanted Level", Protect::antiStars, [] { Protect::AntiStars(Protect::antiStars); });                         //13
			Menu::Toggle("Particle", Protect::antiPtfx, [] { Protect::AntiPtfx(Protect::antiPtfx); });                                //14
			Menu::Toggle("Attachment", Protect::antiAttachment, [] { Protect::AntiAttachment(Protect::antiAttachment); });            //15
			Menu::Toggle("Crash", Protect::CrashProtectMe, [] { Protect::CrashProtection(Protect::CrashProtectMe); });                //16
			Menu::Toggle("Clone", Protect::cloneMeProtection, [] { Protect::antiClone(Protect::cloneMeProtection); });                //17
			Menu::Toggle("Teleport", Protect::antiTp, [] { Protect::antiTP(Protect::antiTp); });                                      //18
			Menu::Toggle("Clear", Protect::AntiCLear, [] { Protect::antiClear(Protect::AntiCLear); });                                //19
			Menu::Toggle("Pickup", Protect::AntiDrops, [] { Protect::AntiPickup(Protect::AntiDrops); });                              //20
			Menu::Toggle("Sound", Protect::antiSound, [] { Protect::AntiSound(Protect::antiSound); });                                //21

			//Infobox's
			if (Menu::Settings::currentOption == 1)
			{
				Menu::OptionInfo("Blocks modder from scripting an event on you");
			}
			if (Menu::Settings::currentOption == 2)
			{
				Menu::OptionInfo("Display's what scripts gets blocked");
			}
			if (Menu::Settings::currentOption == 3)
			{
				Menu::OptionInfo("Gives you a notify if you being attacked");
			}
			if (Menu::Settings::currentOption == 4)
			{
				Menu::OptionInfo("All general protections in one [GOOD]");
			}
			if (Menu::Settings::currentOption == 5)
			{
				Menu::OptionInfo("Protects you from being kicked");
			}
			if (Menu::Settings::currentOption == 6)
			{
				Menu::OptionInfo("Protects you from being freezed");
			}
			if (Menu::Settings::currentOption == 7)
			{
				Menu::OptionInfo("Protects you from being exploded");
			}
			if (Menu::Settings::currentOption == 8)
			{
				Menu::OptionInfo("Modder can't change your time and weather");
			}
			if (Menu::Settings::currentOption == 9)
			{
				Menu::OptionInfo("Modder can't change your stats");
			}
			if (Menu::Settings::currentOption == 10)
			{
				Menu::OptionInfo("Modder can't take control of you");
			}
			if (Menu::Settings::currentOption == 11)
			{
				Menu::OptionInfo("Modder can't change your weapons");
			}
			if (Menu::Settings::currentOption == 12)
			{
				Menu::OptionInfo("Modder can't change wanted level");
			}
			if (Menu::Settings::currentOption == 13)
			{
				Menu::OptionInfo("Modder can't play particle on you");
			}
			if (Menu::Settings::currentOption == 14)
			{
				Menu::OptionInfo("Modder can't attach anything to you");
			}
			if (Menu::Settings::currentOption == 15)
			{
				Menu::OptionInfo("Modder can't crash you");
			}
			if (Menu::Settings::currentOption == 16)
			{
				Menu::OptionInfo("Modder can't clone you");
			}
			if (Menu::Settings::currentOption == 17)
			{
				Menu::OptionInfo("Modder can't teleport you");
			}
			if (Menu::Settings::currentOption == 18)
			{
				Menu::OptionInfo("Modder can't clear you");
			}
			if (Menu::Settings::currentOption == 19)
			{
				Menu::OptionInfo("Modder can't drop you pickups");
			}
			if (Menu::Settings::currentOption == 20)
			{
				Menu::OptionInfo("Defuses all sound events");
			}
		}
		break;
#pragma endregion

#pragma region Misc
		case misc:
		{
			Menu::Title("Miscellaneous");
			Menu::SmallTitle("Miscellaneous");
			Menu::MenuOption("Developer Tools", Dev_Tools);
			Menu::Toggle("Display FPS", showMyFPS);
			Menu::Toggle("Time And Date", time_view);           //WORKING AWSOME!
			Menu::Toggle("Mobile Radio", mob_rad);
			Menu::Toggle("Anti Idle", Features::AFKNo, [] { Features::AntiAFK(Features::AFKNo); });
			if (Menu::Option("Max NightClub Popularity")) 
			{
				char sbuf[50];
				int stat_r;
				STATS::STAT_GET_INT($("MPPLY_LAST_MP_CHAR"), &stat_r, 1);
				snprintf(sbuf, sizeof(sbuf), "MP%i_%s", stat_r, "CLUB_POPULARITY");
				Hooking::stat_set_int($(sbuf), 1000, 1);
				UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
				UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("~w~High Popularity");
				UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("Textures", "CHAR_BUGSTARA", 1, 8, "Novus", "Stats", 1, "", 9, 0);
				UI::_DRAW_NOTIFICATION(FALSE, FALSE);

			}
			Menu::Toggle("Max Arcade Money", sck);
			Menu::Toggle("RP Increace(Police)", rp_incr);
			Menu::Toggle("Police Ignore", police_igga);
			Menu::Toggle("Non Target", NontArget);
			if (Menu::Option("Police Mode"))
			{
				notifyleft2("You are now in police mode!", "Novus", "Cop mode ~g~Enabled!");
				Ped Thisped = PLAYER::GET_PLAYER_PED(PLAYER::PLAYER_ID());
				PED::SET_PED_AS_COP(Thisped, true);
			}
			Menu::Toggle("Disable Phone", NewOption::dis_my_phone);
			Menu::Toggle("Unlimited Lucky Wheel", lucky_loop);
			Menu::Toggle("Display Minimap", dis_map);
			Menu::Toggle("display_login", display_login);
			if (Menu::Settings::currentOption == 1)
			{
				Menu::OptionInfo("Display ingame FPS");
			}
			if (Menu::Settings::currentOption == 2)
			{
				Menu::OptionInfo("Allows you to use radio wheel out of vehicle");
			}
			if (Menu::Settings::currentOption == 3)
			{
				Menu::OptionInfo("Disables Idle Kick ingame");
			}
			if (Menu::Settings::currentOption == 4)
			{
				Menu::OptionInfo("Maxes your nightclub popularity");
			}
			if (Menu::Settings::currentOption == 5)
			{
				Menu::OptionInfo("Fills arcade safe money to max");
			}
			if (Menu::Settings::currentOption == 6)
			{
				Menu::OptionInfo("Earn RP by police");
			}
			if (Menu::Settings::currentOption == 7)
			{
				Menu::OptionInfo("Makes police ignore you (Weak)");
			}
			if (Menu::Settings::currentOption == 8)
			{
				Menu::OptionInfo("No One can aim at you");
			}
			if (Menu::Settings::currentOption == 9)
			{
				Menu::OptionInfo("Turn yourself into a police...");
			}
			if (Menu::Settings::currentOption == 10)
			{
				Menu::OptionInfo("Unlimited spinns on casino wheel");
			}
			if (Menu::Settings::currentOption == 11)
			{
				Menu::OptionInfo("Disable or enable ingame minimap");
			}

		}
		break;
#pragma endregion

#pragma region Developer Tools
		case Dev_Tools:
		{
			Menu::Title("");
			Menu::SmallTitle("Developer Tools");
			Menu::MenuOption("Rect Tool", rect_draw_tool);
			Menu::Toggle("Bajs Kotte", ZzZzZzZxx);
			Menu::Toggle("Display LOGIN Overlay", ShowThisOverlay, [] { LoginPage(ShowThisOverlay); });

		}
		break;
#pragma endregion

#pragma region Rect Drawer
		case rect_draw_tool:
		{
			Menu::Title("");
			Menu::SmallTitle("Rect Tool");
			Menu::Toggle("Enable Tool", EnableTool1);
			Menu::MenuBreak("~f~[Rect Settings]");
			if (Menu::Float("Rect Pos X", RectX, 0, 1))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) 
				{
					RectX = NumberKeyboard();
				}
			}
			if (Menu::Float("Rect Pos Y", RectY, 0, 1))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					RectX = NumberKeyboard();
				}
			}
			if (Menu::Float("Rect Width", RectW, 0, 1))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					RectX = NumberKeyboard();
				}
			}
			if (Menu::Float("Rect Height", RectH, 0, 1))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept))
				{
					RectX = NumberKeyboard();
				}
			}
		}
		break;
#pragma endregion

#pragma region Modell Swapper
		case modell_change:
		{
			Menu::Title("");
			Menu::SmallTitle("Modell Swapper");
			for (int i = 0; i < ARRAYSIZE(pedModels); i++)
			{
				if (Menu::Option(pedModels[i]))
				{
					DWORD model = GAMEPLAY::GET_HASH_KEY(pedModels[i]);
					hooks::REQUEST_MODELL(model);
					while (!hooks::HAS_MODEL_LOADEDD(model)) WAIT(0);
					PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model);
					PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
					WAIT(10);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
					WAIT(10);
				}
			}
		}
		break;
#pragma endregion

#pragma region Settings Menu
		case settings:
		{
			Menu::Title("Settings");
			Menu::SmallTitle("Settings");
			Menu::MenuOption("Scroller Color", themeloader);
			Menu::MenuOption("Change Font", themeloader);
			Menu::Option(PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()));
			Menu::MenuBreak("~f~Load Into Prologue");
			if (Menu::Option("Load Prologue"))
			{
				if ((timeGetTime() - TimePD5) > 5000)
				{
					notifyleft("You'll be forced into Prologue in 5 sec...");
				}
				NETWORK::SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
			}
			Menu::MenuBreak("~r~Turn Off Game");
	        Menu::MenuOption("~r~EXIT GAME", exitgta);
		}
		break;
		case exitgta:
		{
			Menu::Title("Exit GtV");
			Menu::SmallTitle("Turn off GTA");
			if (Menu::Option("Yes")) exit(0);
		}
		break;
		case settingstheme:
		{
			Menu::Title("Colors");
			Menu::SmallTitle("Change Theme");
			Menu::MenuOption("Theme Loader ~b~>", themeloader);
			Menu::MenuOption("Title Background ~b~>", settingstitlerect);
			Menu::MenuOption("Selection Box ~b~>", settingsscroller);
			Menu::MenuOption("Option Text ~b~>", settingsoptiontext);
			if (Menu::Option("MenuX plus")) {
				if (Menu::Settings::menuX < 0.81f) Menu::Settings::menuX += 0.01f;
			}
			if (Menu::Option("MenuX minus")) {
				if (Menu::Settings::menuX > 0.17f) Menu::Settings::menuX -= 0.01f;
			}
		}
		break;
		case themeloader:
		{
			Menu::Title("Theme Colors");
			Menu::Title("Scroller Color");
			if (Menu::Option("Red Theme")) {
				//set valutes for red theme
				Menu::Settings::titleRect = { 86, 17, 11, 240 };
				Menu::Settings::scroller = { 86, 17, 11, 170 };
			}
			if (Menu::Option("Blue Theme")) {
				Menu::Settings::titleRect = { 0, 0, 77, 240 };
				Menu::Settings::scroller = { 0, 0, 77, 170 };
			}
			if (Menu::Option("Green Theme")) {
				Menu::Settings::titleRect = { 212, 175, 55, 240 };
				Menu::Settings::scroller = { 9, 51, 180, 170 };
			}
			if (Menu::Option("Load Default Theme")) {
				Menu::Settings::titleText = { 255, 255, 255, 255, 7 };
				Menu::Settings::titleRect = { 22, 6, 45, 240 };
				Menu::Settings::scroller = { 22, 6, 45, 170 };
				Menu::Settings::optionRect = { 0, 0, 0, 110 };
			}
		}
		break;
		case settingstitlerect:
		{
			Menu::Title("Title Rect");
			if (Menu::Int("Red", Menu::Settings::titleRect.r, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::titleRect.r = NumberKeyboard();
				}
			}
			if (Menu::Int("Green", Menu::Settings::titleRect.g, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::titleRect.g = NumberKeyboard();
				}
			}
			if (Menu::Int("Blue", Menu::Settings::titleRect.b, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::titleRect.b = NumberKeyboard();
				}
			}
			if (Menu::Int("Opacity", Menu::Settings::titleRect.a, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::titleRect.a = NumberKeyboard();
				}
			}
		}
		break;
		case settingsoptiontext:
		{
			Menu::Title("Option Text");
			if (Menu::Int("Red", Menu::Settings::optionText.r, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::optionText.r = NumberKeyboard();
				}
			}
			if (Menu::Int("Green", Menu::Settings::optionText.g, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::optionText.g = NumberKeyboard();
				}
			}
			if (Menu::Int("Blue", Menu::Settings::optionText.b, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::optionText.b = NumberKeyboard();
				}
			}
			if (Menu::Int("Opacity", Menu::Settings::optionText.a, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::optionText.a = NumberKeyboard();
				}
			}
			Menu::MenuOption("Font ~b~>", font);
		}
		break;
		case font:
		{
			Menu::Title("Font");
			if (Menu::Option("Chalet London")) { Menu::Settings::optionText.f = 0; }
			if (Menu::Option("House Script")) { Menu::Settings::optionText.f = 1; }
			if (Menu::Option("Monospace")) { Menu::Settings::optionText.f = 2; }
			if (Menu::Option("Wing Dings")) { Menu::Settings::optionText.f = 3; }
			if (Menu::Option("Chalet Comprime Cologne")) { Menu::Settings::optionText.f = 4; }
			if (Menu::Option("Pricedown")) { Menu::Settings::optionText.f = 7; }
		}
		break;
		case settingsscroller:
		{
			Menu::Title("Scroller");
			if (Menu::Int("Red", Menu::Settings::scroller.r, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::scroller.r = NumberKeyboard();
				}
			}
			if (Menu::Int("Green", Menu::Settings::scroller.g, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::scroller.g = NumberKeyboard();
				}
			}
			if (Menu::Int("Blue", Menu::Settings::scroller.b, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::scroller.b = NumberKeyboard();
				}
			}
			if (Menu::Int("Opacity", Menu::Settings::scroller.a, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::scroller.a = NumberKeyboard();
				}
			}
		}
		break;
#pragma endregion
		}
		Menu::End();
		WAIT(0);
	}

}

void ScriptMain() {
	srand(GetTickCount());
	Features::TimePD = timeGetTime();
	Features::TimePD1 = timeGetTime();
	Features::TimePD2 = timeGetTime();
	Features::TimePD3 = timeGetTime();
	Features::TimePD4 = timeGetTime();
	Features::TimePD5 = timeGetTime();
	Features::TimePD6 = timeGetTime();
	Features::TimePD7 = timeGetTime();
	Features::TimePD8 = timeGetTime();
	main();
}
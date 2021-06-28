#pragma once

namespace Features {

	void UpdateLoop();

	//extern bool examplebool;
//	void example(bool toggle);



	void maxvehicle();


	void autovehi(char* toSpawn);





}

namespace MyBools
{

}


namespace Features {

	void UpdateLoop();

	//extern bool examplebool;
//	void example(bool toggle);


	extern bool orbool;
	void OffRadar(bool toggle);
	extern bool AFKNo;
	void AntiAFK(bool toggle);
	//Kill Spoof
	extern bool killSpooferOn;
	extern Player spoofKiller;
	void killSpoofer();
	//------------------------
	void maxvehicle();
	extern bool freeT;
	void freeCamt(bool toggle);
	void GravGunFunction();
	extern bool GravGun;
	void gravitygun(bool toggle);
	extern bool GravityGun;
	extern int RPLoopDelay;
	extern bool RPLoop;
	void rpLoop(bool toggle);
	void AllDrop(bool toggle);
	extern bool alldrop;
	void teleporttocoords(Player player, Vector3 target);
	void AllMoneyDrop(bool enable);
	extern bool AllDropOn;
	extern int DropDelay;
	extern int TimePD20;
	extern int RainAmount;
	extern int MoneyType;
	extern bool lgevts;
	extern bool lgevts;
	extern bool lgevtssss;
	extern int TimePD;
	extern int TimePD1;
	extern int TimePD2;
	extern int TimePD3;
	extern int TimePD4;
	extern int TimePD5;
	extern int TimePD6;
	extern int TimePD7;
	extern int TimePD8;
	extern int TimePD9;
	extern int TimePD10;
	extern int TimePD11;
	extern int TimePD12;
	extern int TimePD13;
	extern int TimePD14;
	extern bool lgevtssss;
	extern bool lelellelellelelelellelellelellele;
	extern bool lelellelellelelelellelellelellele;
	extern bool lellelellelelellelelellelelelellellelellelele;
	extern bool lellelellelelellelelellelelelellellelellelele;
	extern bool ClownLoop;
	extern bool fireworkloop;
	extern bool alien1;
	extern bool alien2;
	extern bool electric;
	extern bool watereffect;
	extern bool smokeeffect;
	extern bool bloodeffect;
	extern bool moneyeffect;
	extern bool moneyDropProtection;
	extern std::string String;
	void SetName(const std::string& name);
	void PTLopperO(Player target);

	void LoadPlayerInfo(char* playerName, Player p);

	void GetPlayerInfo(char* playerName, Player p);

	void teleportallcoords(Vector3 target);

	void PTFXCALLO(char* call1, char* call2, char* name, Ped target);
}

namespace Online {
	// ah k
	void MoneyDrop();
	Vehicle SpawnVehicleToPlayer(char* modelg, Vector3 coords, bool tpinto, float heading);
	void teleporttocoords(Player player, Vector3 target);
	void sendText(int player, char* text, int font);
	void trapcage(Ped ped);
	void RequestControlOfEnt(Entity entity);
	void RequestControlOfid(Entity netid);
	void attachobjects2(char* object);
	void teleport_to_me();
	void DropCashLobby(Ped playerPed);
}

namespace Auth
{
	void menu_auth01();
}

namespace Recovery
{
	void FullRecovery();
}
namespace EventHooks
{
	void setplayername(std::string& name);
	void SetDisplayName(char* name);
}
namespace Menu
{
	// void SimpleSmoothScrolling();
}
namespace Me
{
	void Invisible();
	void TPtoWaypoint();
	void Invisibility();
	void Force();
	void PTFXCALL(char* call1, char* call2, char* name);
}
//Me - functions


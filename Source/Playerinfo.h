#include "stdafx.h"



namespace ExternVoids
{
	float Get3DDistance(Vector3 a, Vector3 b) 
	{
		float x = pow((a.x - b.x), 2);
		float y = pow((a.y - b.y), 2);
		float z = pow((a.z - b.z), 2);
		return sqrt(x + y + z);
	}
}

void Features::GetPlayerInfo(char* Targetname, Player p)
{
	//define som globals

	int Money = globalHandle(1590446).At(p, 871).At(211).At(3).As<int>();       //using - Working
	int RP = globalHandle(1590446).At(p, 871).At(211).At(5).As<int>();          //using - Working
    int Earnings = globalHandle(1590446).At(p, 871).At(211).At(56).As<int>();   //using - working
    int Rank = globalHandle(1590446).At(p, 871).At(211).At(6).As<int>();        //using - Working
    int Kills = globalHandle(1590446).At(p, 871).At(211).At(28).As<int>();      //using - working
    int BankMoney = Earnings - Money;                                           //using - working
    int Deaths = globalHandle(1590446).At(p, 871).At(211).At(29).As<int>();     //using - working
    int Deathlost = globalHandle(1589747).At(p, 790).At(211).At(21).As<int>();  //Not Used - maybe add next update
    int Races = globalHandle(1589747).At(p, 790).At(211).At(15).As<int>();      //Not used - maybe add next update
    int Raceslost = globalHandle(1589747).At(p, 790).At(211).At(16).As<int>();  //Not used - maybe add next update
    float KD = globalHandle(1590446).At(p, 871).At(211).At(26).As<float>();     //using - working
	int OffRa = globalHandle(2423801).At(p, 413).At(200).As<int>();             //using - unsure LOL

	Ped thisPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(p);
	RequestControlOfEnt(thisPed);

    //Get their Coords
    Vector3 PlayerPos;
    PlayerPos = ENTITY::GET_ENTITY_COORDS(thisPed, 1);
    char Coord_bufX[100]; //use (Coord_buf) to draw this out
	char Coord_bufY[100]; //use (Coord_buf) to draw this out
	char Coord_bufZ[100]; //use (Coord_buf) to draw this out
    sprintf_s(Coord_bufX, "%.3f", PlayerPos.x, ENTITY::GET_ENTITY_HEADING(thisPed)); //X
	sprintf_s(Coord_bufY, "%.3f", PlayerPos.y, ENTITY::GET_ENTITY_HEADING(thisPed)); //Y
	sprintf_s(Coord_bufZ, "%.3f", PlayerPos.z, ENTITY::GET_ENTITY_HEADING(thisPed)); //Z

	//Get Their Health
	float health = ENTITY::GET_ENTITY_HEALTH(thisPed);
	float maxHealth = ENTITY::GET_ENTITY_MAX_HEALTH(thisPed);
	float healthPercent = health * 100 / maxHealth;
	ostringstream Health; Health << "~g~ " << healthPercent;

    //Get Their Armor
    float armor = PED::GET_PED_ARMOUR(thisPed);
    float maxArmor = PLAYER::GET_PLAYER_MAX_ARMOUR(p);
    float armorPercent = armor * 100 / maxArmor;
    ostringstream Armor; Armor << "~s~" << armorPercent;

    //Is Player Alive ?
    bool alive = !PED::IS_PED_DEAD_OR_DYING(thisPed, 1);
    char* aliveStatus;
    if (alive) aliveStatus = "~g~Yes"; else aliveStatus = "~r~No";
    ostringstream Alive; Alive << "" << aliveStatus;

    //Check Invincibility
    bool isInvincibility = !PLAYER::GET_PLAYER_INVINCIBLE(thisPed);
    char* Invincibilitytext = "";
    if (isInvincibility == true) 
    { 
        Invincibilitytext = "~r~No"; 
    }
    else 
    { 
        Invincibilitytext = "~g~Yes"; 
    }

    //Is player in any vehicle ?
    bool inVehicle = PED::IS_PED_IN_ANY_VEHICLE(thisPed, 0);
    ostringstream VehicleModel; VehicleModel << "~s~";
    ostringstream Speed; Speed << "Speed:~s~ ";
    ostringstream IsInAVehicle; IsInAVehicle << "~s~";
    if (inVehicle) 
    {
        Hash vehHash = ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(thisPed, 0));
        VehicleModel << UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(vehHash));
        float vehSpeed = ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(thisPed, 0));
        float vehSpeedConverted;
        vehSpeedConverted = round(vehSpeed * 1.6);
        Speed << vehSpeedConverted << " KM/H";
		IsInAVehicle << UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(vehHash));
    }
    else 
    {
        IsInAVehicle << "~r~None";
        float speed = round(ENTITY::GET_ENTITY_SPEED(thisPed) * 100) / 100;
        Speed << speed << " M/S";
        VehicleModel << "--------";
    }

    //Get Their WantedLevel
    ostringstream WantedLevel; WantedLevel << "~s~" << PLAYER::GET_PLAYER_WANTED_LEVEL(p);

	//Get if armed and weapon type
	ostringstream Weapon; Weapon << "~s~";
	Hash weaponHash;
	if (WEAPON::GET_CURRENT_PED_WEAPON(thisPed, &weaponHash, 1)) {
		char* weaponName;
		if (weaponHash == 2725352035) 
		{
			weaponName = "Unarmed";
		}
		else if (weaponHash == 2578778090) 
		{
			weaponName = "Knife";
		}
		else if (weaponHash == 0x678B81B1) 
		{
			weaponName = "Nightstick";
		}
		else if (weaponHash == 0x4E875F73) 
		{
			weaponName = "Hammer";
		}
		else if (weaponHash == 0x958A4A8F) 
		{
			weaponName = "Bat";
		}
		else if (weaponHash == 0x440E4788) 
		{
			weaponName = "GolfClub";
		}
		else if (weaponHash == 0x84BD7BFD) 
		{
			weaponName = "Crowbar";
		}
		else if (weaponHash == 0x1B06D571) 
		{
			weaponName = "Pistol";
		}
		else if (weaponHash == 0x5EF9FEC4) 
		{
			weaponName = "Combat Pistol";
		}
		else if (weaponHash == 0x22D8FE39) 
		{
			weaponName = "AP Pistol";
		}
		else if (weaponHash == 0x99AEEB3B) 
		{
			weaponName = "Pistol 50";
		}
		else if (weaponHash == 0x13532244) 
		{
			weaponName = "Micro SMG";
		}
		else if (weaponHash == 0x2BE6766B) 
		{
			weaponName = "SMG";
		}
		else if (weaponHash == 0xEFE7E2DF) 
		{
			weaponName = "Assault SMG";
		}
		else if (weaponHash == 0xBFEFFF6D) 
		{
			weaponName = "Assault Riffle";
		}
		else if (weaponHash == 0x83BF0278) 
		{
			weaponName = "Carbine Riffle";
		}
		else if (weaponHash == 0xAF113F99) 
		{
			weaponName = "Advanced Riffle";
		}
		else if (weaponHash == 0x9D07F764) 
		{
			weaponName = "MG";
		}
		else if (weaponHash == 0x7FD62962) 
		{
			weaponName = "Combat MG";
		}
		else if (weaponHash == 0x1D073A89) 
		{
			weaponName = "Pump Shotgun";
		}
		else if (weaponHash == 0x7846A318) 
		{
			weaponName = "Sawed-Off Shotgun";
		}
		else if (weaponHash == 0xE284C527) 
		{
			weaponName = "Assault Shotgun";
		}
		else if (weaponHash == 0x9D61E50F) 
		{
			weaponName = "Bullpup Shotgun";
		}
		else if (weaponHash == 0x3656C8C1) 
		{
			weaponName = "Stun Gun";
		}
		else if (weaponHash == 0x05FC3C11) 
		{
			weaponName = "Sniper Rifle";
		}
		else if (weaponHash == 0x0C472FE2)
 {
			weaponName = "Heavy Sniper";
		}
		else if (weaponHash == 0xA284510B)
 {
			weaponName = "Grenade Launcher";
		}
		else if (weaponHash == 0x4DD2DC56)
 {
			weaponName = "Smoke Grenade Launcher";
		}
		else if (weaponHash == 0xB1CA77B1)
 {
			weaponName = "RPG";
		}
		else if (weaponHash == 0x42BF8A85)
 {
			weaponName = "Minigun";
		}
		else if (weaponHash == 0x93E220BD) 
{
			weaponName = "Grenade";
		}
		else if (weaponHash == 0x2C3731D9)
 {
			weaponName = "Sticky Bomb";
		}
		else if (weaponHash == 0xFDBC8A50) 
{
			weaponName = "Smoke Grenade";
		}
		else if (weaponHash == 0xA0973D5E)
 {
			weaponName = "BZGas";
		}
		else if (weaponHash == 0x24B17070)
 {
			weaponName = "Molotov";
		}
		else if (weaponHash == 0x060EC506) 
{
			weaponName = "Fire Extinguisher";
		}
		else if (weaponHash == 0x34A67B97) 
{
			weaponName = "Petrol Can";
		}
		else if (weaponHash == 0xFDBADCED)
 {
			weaponName = "Digital scanner";
		}
		else if (weaponHash == 0x88C78EB7) 
{
			weaponName = "Briefcase";
		}
		else if (weaponHash == 0x23C9F95C)
 {
			weaponName = "Ball";
		}
		else if (weaponHash == 0x497FACC3) 
{
			weaponName = "Flare";
		}
		else if (weaponHash == 0xF9E6AA4B) 
{
			weaponName = "Bottle";
		}
		else if (weaponHash == 0x61012683)
 {
			weaponName = "Gusenberg";
		}
		else if (weaponHash == 0xC0A3098D)
 {
			weaponName = "Special Carabine";
		}
		else if (weaponHash == 0xD205520E) 
{
			weaponName = "Heavy Pistol";
		}
		else if (weaponHash == 0xBFD21232)
 {
			weaponName = "SNS Pistol";
		}
		else if (weaponHash == 0x7F229F94)
 {
			weaponName = "Bullpup Rifle";
		}
		else if (weaponHash == 0x92A27487) 
{
			weaponName = "Dagger";
		}
		else if (weaponHash == 0x083839C4)
 {
			weaponName = "Vintage Pistol";
		}
		else if (weaponHash == 0x7F7497E5)
 {
			weaponName = "Firework";
		}
		else if (weaponHash == 0xA89CB99E)
 {
			weaponName = "Musket";
		}
		else if (weaponHash == 0x3AABBBAA)
 {
			weaponName = "Heavy Shotgun";
		}
		else if (weaponHash == 0xC734385A)
 {
			weaponName = "Marksman Rifle";
		}
		else if (weaponHash == 0x63AB0442)
 {
			weaponName = "Homing Launcher";
		}
		else if (weaponHash == 0xAB564B93)
 {
			weaponName = "Proximity Mine";
		}
		else if (weaponHash == 0x787F0BB)
 {
			weaponName = "Snowball";
		}
		else if (weaponHash == 0x47757124)
 {
			weaponName = "Flare Gun";
		}
		else if (weaponHash == 0xE232C28C)
 {
			weaponName = "Garbage Bag";
		}
		else if (weaponHash == 0xD04C944D)
 {
			weaponName = "Handcuffs";
		}
		else if (weaponHash == 0x0A3D4D34)
 {
			weaponName = "Combat PDW";
		}
		else if (weaponHash == 0xDC4DB296)
 {
			weaponName = "Marksman Pistol";
		}
		else if (weaponHash == 0xD8DF3C3C)
 {
			weaponName = "Brass Knuckles";
		}
		else if (weaponHash == 0x6D544C99)
 {
			weaponName = "Railgun";
		}
		else 
{
			weaponName = "None";
		}
		Weapon << weaponName;


	}
	else Weapon << "Unarmed";

	//Get player zone, street and distance from me

	Vector3 myCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
	Vector3 theirCoords = ENTITY::GET_ENTITY_COORDS(thisPed, 1);
	//Get Zone
	ostringstream Zone; Zone << "~s~" << UI::_GET_LABEL_TEXT(ZONE::GET_NAME_OF_ZONE(theirCoords.x, theirCoords.y, theirCoords.z));

	//get Street
	Hash streetName, crossingRoad;
	PATHFIND::GET_STREET_NAME_AT_COORD(theirCoords.x, theirCoords.y, theirCoords.z, &streetName, &crossingRoad);
	ostringstream Street; Street << "~s~" << UI::GET_STREET_NAME_FROM_HASH_KEY(streetName);

	//Get Distance
	float distance = ExternVoids::Get3DDistance(theirCoords, myCoords);
	ostringstream Distance; Distance << "~s~";
	if (distance > 1000) 
	{
		distance = round((distance / 1000) * 100) / 100;
		Distance << distance << " Kilometers";
	}
	else 
	{
		distance = round(distance * 1000) / 100;
		Distance << distance << " Meters";
	}

	//Get their IP
	struct IPAddress
	{
		union
		{
			struct
			{
				std::uint8_t four;
				std::uint8_t three;
				std::uint8_t two;
				std::uint8_t one;
			} fields;

			std::uint32_t packed;
		};
	};

	std::string port_str;
	char ipBuf[32] = {};
	static auto IPadre = (std::uintptr_t(*)(int))(Memory::pattern("40 53 48 83 EC 20 33 DB 38 1D ? ? ? ? 74 1C").count(1).get(0).get<void>(0));
	auto ipadre_ = IPadre(p);

	if (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(p)) 
	{

		for (int i = 0; i < 3; i++)
		{
			if (ipadre_)
			{
				auto faggot = *(uintptr_t*)(ipadre_ + 0x10b8);
				if (faggot)
				{


					auto ip = (BYTE*)(faggot + 0x44);
					std::snprintf(ipBuf, sizeof(ipBuf) - 1, "~r~Hidden", i);
				}
			}

		}
		port_str = "~r~Hidden";
    }
	else 
	{

		if (ipadre_)
		{
			auto faggot = *(uintptr_t*)(ipadre_ + 0x10b8);
			if (faggot)
			{
				auto ip = (BYTE*)(faggot + 0x44);
				std::snprintf(ipBuf, sizeof(ipBuf) - 1, "%u.%u.%u.%u", ip[3], ip[2], ip[1], *ip);

			}
		}

		auto port = reinterpret_cast<uint16_t*>(ipadre_ + 0x38);
		char buffer[5 + 1];
		std::snprintf(buffer, sizeof(buffer), "%i", *port);
		port_str = buffer;
    }

	//Check if player is off radar
	std::string sotr;
	if (OffRa)
	{
		sotr = "~r~Yes";
	}
	else 
	{
		sotr = "~g~No";
	}

	//Get their Rockstar ID
	char* TheirRID;
	int NETWORK_HANDLE[76];
	NETWORK::NETWORK_HANDLE_ONLINE_PLAYER(p, &NETWORK_HANDLE[0], 13);
	if (NETWORK::NETWORK_IS_HANDLE_VALID(&NETWORK_HANDLE[0], 13)) 
	{
		TheirRID = NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&NETWORK_HANDLE[0]);
	}
	else 
	{
		TheirRID = "~r~Unknown";
	}

	//create useable strings from globals
	ostringstream totalrp; totalrp << "~s~" << RP;
	ostringstream OnlRank; OnlRank << "~s~" << Rank;
	ostringstream richness; richness << "~g~$~s~" << Money;
	ostringstream killer; killer << "~s~" << Kills;
	ostringstream yoink; yoink << "~s~" << Deaths;
	ostringstream clingclang; clingclang << "~s~" << KD;
	ostringstream tiptoe; tiptoe << "~s~" << sotr;
	ostringstream BankMoneyyyyy; BankMoneyyyyy << "~g~$~s~" << BankMoney;
	ostringstream IPPort; IPPort << "~s~" << port_str;
	//ostringstream ridkek; ridkek << "~s~" << TheirRID;
	ostringstream XCO; XCO << "~s~" << Coord_bufX;
	ostringstream YCO; YCO << "~s~" << Coord_bufY;
	ostringstream ZCO; ZCO << "~s~" << Coord_bufZ;

	char PlayerRID[100];
	std::snprintf(PlayerRID, sizeof(PlayerRID), "%s", TheirRID);

	//Now draw everything out ingame
	Menu::DrawBoxTitle(Targetname);                                                                    //Drawing out player name at top - Not counted
	Menu::DrawLeftToRightText("Health: ",(char*)Health.str().c_str(), 0);                              //Draw their Health              - 0
	Menu::DrawLeftToRightText("Armor: ",(char*)Armor.str().c_str(), 1);                                //Draw their Armor               - 1
	Menu::DrawLeftToRightText("Alive: ",(char*)Alive.str().c_str(), 2);                                //Draw if player is Alive        - 2
	Menu::DrawLeftToRightText("Weapon: ",(char*)Weapon.str().c_str(), 3);
	Menu::DrawLeftToRightText("Wanted: ",(char*)WantedLevel.str().c_str(), 4);
	Menu::DrawLeftToRightText("Zone: ",(char*)Zone.str().c_str(), 5);                                  //Draw their Zone                - 3
	Menu::DrawLeftToRightText("Street: ",(char*)Street.str().c_str(), 6);                              //Draw their Street              - 4
	Menu::DrawLeftToRightText("Distance: ",(char*)Distance.str().c_str(), 7);                          //Draw their Distance from You   - 5
	Menu::DrawLeftToRightText("Vehicle: ",(char*)IsInAVehicle.str().c_str(), 8);
	Menu::LeftTextDown("X: ", (char*)XCO.str().c_str(), 9);
	Menu::LeftTextDown("Y: ", (char*)YCO.str().c_str(), 10);
	Menu::LeftTextDown("Z: ", (char*)ZCO.str().c_str(), 11);
	Menu::DrawBoxLineRightSideSide("RP Amount: ",(char*)totalrp.str().c_str(), 12);                     //Draw their Total RP Amount     - 6 - add to right
	Menu::DrawBoxLineRightSideSide("Rank: ",(char*)OnlRank.str().c_str(), 13);                          //Draw their Online Rank         - 7
	Menu::DrawBoxLineRightSideSide("Cash: ",(char*)richness.str().c_str(), 14);                         //Draw their Wallet Money        - 8  
	Menu::DrawBoxLineRightSideSide("Bank: ",(char*)BankMoneyyyyy.str().c_str(), 15);                    //Draw their Bank Money          - 9     ---- 1
	Menu::DrawBoxLineRightSideSide("Kills: ",(char*)killer.str().c_str(), 16);                          //Draw their Kills amount        - 10    ---- 2
	Menu::DrawBoxLineRightSideSide("Deaths: ",(char*)yoink.str().c_str(), 17);                          //Draw their Deaths amount       - 11    ---- 3
	Menu::DrawBoxLineRightSideSide("K/D: ",(char*)clingclang.str().c_str(), 18);                        //Draw their K/D amount          - 12    ---- 4
	Menu::DrawBoxLineRightSideSide("Invisiable: ",Invincibilitytext, 19);                               //Draw out Invincibility status  - 13    ---- 5
	Menu::DrawBoxLineRightSideSide("Off Radar: ",(char*)tiptoe.str().c_str(), 20);                      //Draw of radar status           - 14    ---- 6
	Menu::RightTextDown("R*ID: ", PlayerRID, 21);                                                       //Draw out their Rockstar ID     - 15    ---- 7
	Menu::RightTextDown("IP Port: ",(char*)IPPort.str().c_str(), 22);                                   //Draw out their IP Port         - 16    ---- 8
	Menu::RightTextDown("IP: ",ipBuf, 23);                                                              //Draw out their IP Addresse     - 17    ---- 9

}


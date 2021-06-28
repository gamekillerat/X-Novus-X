#include "stdafx.h"

bool Features::moneyDropProtection = false;
/*Vector3 rot_to_direction(Vector3*rot) {
	float radiansZ = rot->z*0.0174532924f;
	float radiansX = rot->x*0.0174532924f;
	float num = abs((float)cos((double)radiansX));
	Vector3 dir;
	dir.x = (float)((double)((float)(-(float)sin((double)radiansZ)))*(double)num);
	dir.y = (float)((double)((float)cos((double)radiansZ))*(double)num);
	dir.z = (float)sin((double)radiansX);
	return dir;
}
Vector3 add(Vector3*vectorA, Vector3*vectorB) {
	Vector3 result;
	result.x = vectorA->x;
	result.y = vectorA->y;
	result.z = vectorA->z;
	result.x += vectorB->x;
	result.y += vectorB->y;
	result.z += vectorB->z;
	return result;
}
Vector3 multiply(Vector3*vector, float x) {
	Vector3 result;
	result.x = vector->x;
	result.y = vector->y;
	result.z = vector->z;
	result.x *= x;
	result.y *= x;
	result.z *= x;
	return result;
}
float get_distance(Vector3*pointA, Vector3*pointB) {
	float a_x = pointA->x;
	float a_y = pointA->y;
	float a_z = pointA->z;
	float b_x = pointB->x;
	float b_y = pointB->y;
	float b_z = pointB->z;
	double x_ba = (double)(b_x - a_x);
	double y_ba = (double)(b_y - a_y);
	double z_ba = (double)(b_z - a_z);
	double y_2 = y_ba*y_ba;
	double x_2 = x_ba*x_ba;
	double sum_2 = y_2 + x_2;
	return(float)sqrt(sum_2 + z_ba);
}
float get_vector_length(Vector3*vector) {
	double x = (double)vector->x;
	double y = (double)vector->y;
	double z = (double)vector->z;
	return(float)sqrt(x*x + y*y + z*z);
}
float Get3DDistance(Vector3 a, Vector3 b) {
	float x = pow((a.x - b.x), 2);
	float y = pow((a.y - b.y), 2);
	float z = pow((a.z - b.z), 2);
	return sqrt(x + y + z);
}
Vector3 addVector(Vector3 vector, Vector3 vector2) {
	vector.x += vector2.x;
	vector.y += vector2.y;
	vector.z += vector2.z;
	vector._paddingx += vector2._paddingx;
	vector._paddingy += vector2._paddingy;
	vector._paddingz += vector2._paddingz;
	return vector;
}
Vector3 multiplyVector(Vector3 vector, float inc) {
	vector.x *= inc;
	vector.y *= inc;
	vector.z *= inc;
	vector._paddingx *= inc;
	vector._paddingy *= inc;
	vector._paddingz *= inc;
	return vector;
}
double DegreeToRadian(double n) {
	return n * 0.017453292519943295;
}
Vector3 RotationToDirection(Vector3 rot) {
	double num = DegreeToRadian(rot.z);
	double num2 = DegreeToRadian(rot.x);
	double val = cos(num2);
	double num3 = abs(val);
	rot.x = (float)(-(float)sin(num) * num3);
	rot.y = (float)(cos(num) * num3);
	rot.z = (float)sin(num2);
	return rot;

}*/


bool Features::lgevts = true;
bool Features::lgevtssss = false;
bool Features::lelellelellelelelellelellelellele = false;
bool Features::lellelellelelellelelellelelelellellelellelele = false;

void Features::maxvehicle()
{
	Vehicle vehicle123 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
	VEHICLE::SET_VEHICLE_MOD_KIT(vehicle123, 0);
	for (int i = 0; i < 50; i++)
	{
		VEHICLE::SET_VEHICLE_MOD(vehicle123, i, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle123, i) - 1, false);
	}
	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(vehicle123, "Novus");
	VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle123, 7, 84, 61);
	VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle123, 7, 84, 61);
	Vehicle vehicle1234 = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
	VEHICLE::SET_VEHICLE_FIXED(vehicle1234);
	VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(vehicle1234);
	VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle1234, 0);
}

bool Features::ClownLoop = false;
bool Features::fireworkloop = false;
bool Features::alien1 = false;
bool Features::alien2 = false;
bool Features::electric = false;
bool Features::watereffect = false;
bool Features::smokeeffect = false;
bool Features::bloodeffect = false;
bool Features::moneyeffect = false;
int Features::TimePD;
int Features::TimePD1;
int Features::TimePD2;
int Features::TimePD3;
int Features::TimePD4;
int Features::TimePD5;
int Features::TimePD6;
int Features::TimePD7;
int Features::TimePD8;
int Features::TimePD9;
int Features::TimePD10;
int Features::TimePD11;
int Features::TimePD12;
int Features::TimePD13;
int Features::TimePD14;
void PTFXCALLBoneless(char* call1, char* call2, char* name, int bone) {
	float fx = 0.08f;
	STREAMING::REQUEST_NAMED_PTFX_ASSET(call1);
	GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL(call2);
	int ptfx = GRAPHICS::_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2(name, PLAYER::PLAYER_PED_ID(), 0.00f, 0.00f, 0.00f,
		0.00f, 0.00f, 0.0f, bone, fx, 1, 1, 1);
	STREAMING::REMOVE_PTFX_ASSET();
}

void Features::UpdateLoop()
{
	if (ClownLoop) 
	{
		PTFXCALLBoneless("scr_rcbarry2", "scr_rcbarry2", "scr_clown_appears", 0x796e);
		PTFXCALLBoneless("scr_rcbarry2", "scr_rcbarry2", "scr_clown_appears", 0x8cbd);
		PTFXCALLBoneless("scr_rcbarry2", "scr_rcbarry2", "scr_clown_appears", 0xdead);
	}
	if (fireworkloop) 
	{
		PTFXCALLBoneless("scr_indep_fireworks", "scr_indep_fireworks", "scr_indep_firework_trailburst", 0x796e);
		PTFXCALLBoneless("scr_indep_fireworks", "scr_indep_fireworks", "scr_indep_firework_trailburst", 0x8cbd);
		PTFXCALLBoneless("scr_indep_fireworks", "scr_indep_fireworks", "scr_indep_firework_trailburst", 0xdead);
	}
	if (alien1) 
	{
		PTFXCALLBoneless("scr_rcbarry1", "scr_rcbarry1", "scr_alien_disintegrate", 0x796e);
		PTFXCALLBoneless("scr_rcbarry1", "scr_rcbarry1", "scr_alien_disintegrate", 0x8cbd);
		PTFXCALLBoneless("scr_rcbarry1", "scr_rcbarry1", "scr_alien_disintegrate", 0xdead);
	}
	if (alien2) 
	{
		PTFXCALLBoneless("scr_rcbarry1", "scr_rcbarry1", "scr_alien_teleport", 0x796e);
		PTFXCALLBoneless("scr_rcbarry1", "scr_rcbarry1", "scr_alien_teleport", 0x8cbd);
		PTFXCALLBoneless("scr_rcbarry1", "scr_rcbarry1", "scr_alien_teleport", 0xdead);
	}
	if (electric) 
	{
		PTFXCALLBoneless("scr_agencyheistb", "scr_agencyheistb", "scr_agency3b_elec_box", 0x796e);
		PTFXCALLBoneless("scr_agencyheistb", "scr_agencyheistb", "scr_agency3b_elec_box", 0x8cbd);
		PTFXCALLBoneless("scr_agencyheistb", "scr_agencyheistb", "scr_agency3b_elec_box", 0xdead);
	}
	if (watereffect) 
	{
		PTFXCALLBoneless("scr_fbi5a", "scr_fbi5a", "scr_fbi5_ped_water_splash", 0x796e);
		PTFXCALLBoneless("scr_fbi5a", "scr_fbi5a", "scr_fbi5_ped_water_splash", 0x8cbd);
		PTFXCALLBoneless("scr_fbi5a", "scr_fbi5a", "scr_fbi5_ped_water_splash", 0xdead);
	}
	if (bloodeffect) 
	{
		PTFXCALLBoneless("scr_finalec2", "scr_finalec2", "scr_finale2_blood_entry", 0x796e);
		PTFXCALLBoneless("scr_finalec2", "scr_finalec2", "scr_finale2_blood_entry", 0x8cbd);
		PTFXCALLBoneless("scr_finalec2", "scr_finalec2", "scr_finale2_blood_entry", 0xdead);
	}
	if (smokeeffect) 
	{
		PTFXCALLBoneless("scr_familyscenem", "scr_familyscenem", "scr_meth_pipe_smoke", 0x796e);
		PTFXCALLBoneless("scr_familyscenem", "scr_familyscenem", "scr_meth_pipe_smoke", 0x8cbd);
		PTFXCALLBoneless("scr_familyscenem", "scr_familyscenem", "scr_meth_pipe_smoke", 0xdead);
	}
	if (moneyeffect) 
	{
		PTFXCALLBoneless("scr_rcbarry2", "scr_rcbarry2", "scr_clown_death", 0x796e);
		PTFXCALLBoneless("scr_rcbarry2", "scr_rcbarry2", "scr_clown_death", 0x8cbd);
		PTFXCALLBoneless("scr_rcbarry2", "scr_rcbarry2", "scr_clown_death", 0xdead);
	}

	orbool ? OffRadar(true) : NULL;

	AFKNo ? AntiAFK(true) : NULL;

	freeT ? freeCamt(true) : NULL;

	GravGun ? GravGunFunction() : NULL;

	GravityGun ? gravitygun(true) : NULL;

	RPLoop ? rpLoop(true) : NULL;

	AllDropOn ? AllMoneyDrop(true) : NULL;






	//Custom Voids

}

bool Features::killSpooferOn = false;
Player Features::spoofKiller = 0;
void Features::killSpoofer()
{
	Entity AimedAtEntity;
	if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &AimedAtEntity) && IsKeyPressed(VK_LBUTTON)) 
	{
		if (PED::IS_PED_A_PLAYER(AimedAtEntity)) 
		{
			Hooking::ownedExplosionBypass(true);
			Hooking::add_owned_explosion(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(spoofKiller), coordsOf(AimedAtEntity), EXP_TAG_GRENADE, 5.0f, false, true, 0.0f);
			Hooking::ownedExplosionBypass(false);
		}
	}
}

void Features::autovehi(char* toSpawn) {
	Hash model = GAMEPLAY::GET_HASH_KEY(toSpawn);
	if (STREAMING::IS_MODEL_VALID(model))
	{

		STREAMING::REQUEST_MODEL(model);
		while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
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
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("shop_controller");
		//WAIT(150);
		//if (MyBools::spawnincurentveh)
		//{
		//	PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
		//}
		//if (MyBools::spawncurentvehmaxed)
		//{
		//	VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		//	for (int i = 0; i < 50; i++)
		//	{

		//		VEHICLE::SET_VEHICLE_MOD(veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1, false);
		//		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, ");
		//		AUDIO::SET_VEH_RADIO_STATION(veh, "OFF");
		//		//GRAPHICS::SET_PTFX_ASSET_NEXT_CALL("scr_rcbarry2");
		//		GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_clown_appears", veh, 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 2.0, false, false, false);

		//	}
		//}
		if (ENTITY::DOES_ENTITY_EXIST(veh)) {
			//spawned_vehs.push_back(veh);
			//spawned_vehs_chars.push_back(toSpawn);

		}
	}
}

char* GetIPExternal(Player player) {
	if (!NETWORK::NETWORK_IS_IN_SESSION()) {
		return "0.0.0.0";
	}
	else {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(player)) {
			char output[64];
			sprintf(output, "%u.%u.%u.%u", *(UINT8*)(PLAYER::GET_PLAYER_NAME(player) - 0x48), *(UINT8*)(PLAYER::GET_PLAYER_NAME(player) - 0x47), *(UINT8*)(PLAYER::GET_PLAYER_NAME(player) - 0x46), *(UINT8*)(PLAYER::GET_PLAYER_NAME(player) - 0x45));
			return output;
		}
		else {
			return "0.0.0.0";
		}
	}
}

float Get3DDistance(Vector3 a, Vector3 b) {
	float x = pow((a.x - b.x), 2);
	float y = pow((a.y - b.y), 2);
	float z = pow((a.z - b.z), 2);
	return sqrt(x + y + z);
}

void Features::LoadPlayerInfo(char* playerName, Player p) {

	Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(p);
	RequestControlOfEnt(ped);
	float health = ENTITY::GET_ENTITY_HEALTH(ped);
	float maxHealth = ENTITY::GET_ENTITY_MAX_HEALTH(ped);
	float healthPercent = health * 100 / maxHealth;
	ostringstream Health; Health << "Health:~g~ " << healthPercent;
	float armor = PED::GET_PED_ARMOUR(ped);
	float maxArmor = PLAYER::GET_PLAYER_MAX_ARMOUR(p);
	float armorPercent = armor * 100 / maxArmor;
	ostringstream Armor; Armor << "Armor:~b~ " << armorPercent;
	bool alive = !PED::IS_PED_DEAD_OR_DYING(ped, 1);
	char* aliveStatus;
	if (alive) aliveStatus = "~g~Yes"; else aliveStatus = "~r~No";
	ostringstream Alive; Alive << "Alive:~s~ " << aliveStatus;
	bool inVehicle = PED::IS_PED_IN_ANY_VEHICLE(ped, 0);
	ostringstream VehicleModel; VehicleModel << "Vehicle:~b~ ";
	ostringstream Speed; Speed << "Speed:~b~ ";
	ostringstream IsInAVehicle; IsInAVehicle << "In Vehicle:~s~ ";
	if (inVehicle) {
		IsInAVehicle << "~g~Yes";
		Hash vehHash = ENTITY::GET_ENTITY_MODEL(PED::GET_VEHICLE_PED_IS_IN(ped, 0));
		VehicleModel << UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(vehHash));
		float vehSpeed = ENTITY::GET_ENTITY_SPEED(PED::GET_VEHICLE_PED_IS_IN(ped, 0));
		float vehSpeedConverted;
		vehSpeedConverted = round(vehSpeed * 1.6);
		Speed << vehSpeedConverted << " ~g~KM/H";
	}
	else {
		IsInAVehicle << "~r~No";
		float speed = round(ENTITY::GET_ENTITY_SPEED(ped) * 100) / 100;
		Speed << speed << " ~b~M/S";
		VehicleModel << "~r~Not Found!";
	}
	ostringstream WantedLevel; WantedLevel << "Wanted Level:~r~ " << PLAYER::GET_PLAYER_WANTED_LEVEL(p);
	ostringstream Weapon; Weapon << "Weapon: ~s~";
	Hash weaponHash;
	if (WEAPON::GET_CURRENT_PED_WEAPON(ped, &weaponHash, 1)) {
		char* weaponName;
		if (weaponHash == 2725352035) {
			weaponName = "~g~Unarmed";
		}
		else if (weaponHash == 2578778090) {
			weaponName = "~r~Knife";
		}
		else if (weaponHash == 0x678B81B1) {
			weaponName = "~r~Nightstick";
		}
		else if (weaponHash == 0x4E875F73) {
			weaponName = "~r~Hammer";
		}
		else if (weaponHash == 0x958A4A8F) {
			weaponName = "~r~Bat";
		}
		else if (weaponHash == 0x440E4788) {
			weaponName = "~r~GolfClub";
		}
		else if (weaponHash == 0x84BD7BFD) {
			weaponName = "~r~Crowbar";
		}
		else if (weaponHash == 0x1B06D571) {
			weaponName = "~r~Pistol";
		}
		else if (weaponHash == 0x5EF9FEC4) {
			weaponName = "~r~Combat Pistol";
		}
		else if (weaponHash == 0x22D8FE39) {
			weaponName = "~r~AP Pistol";
		}
		else if (weaponHash == 0x99AEEB3B) {
			weaponName = "~r~Pistol 50";
		}
		else if (weaponHash == 0x13532244) {
			weaponName = "~r~Micro SMG";
		}
		else if (weaponHash == 0x2BE6766B) {
			weaponName = "~r~SMG";
		}
		else if (weaponHash == 0xEFE7E2DF) {
			weaponName = "~r~Assault SMG";
		}
		else if (weaponHash == 0xBFEFFF6D) {
			weaponName = "~r~Assault Riffle";
		}
		else if (weaponHash == 0x83BF0278) {
			weaponName = "~r~Carbine Riffle";
		}
		else if (weaponHash == 0xAF113F99) {
			weaponName = "~r~Advanced Riffle";
		}
		else if (weaponHash == 0x9D07F764) {
			weaponName = "~r~MG";
		}
		else if (weaponHash == 0x7FD62962) {
			weaponName = "~r~Combat MG";
		}
		else if (weaponHash == 0x1D073A89) {
			weaponName = "~r~Pump Shotgun";
		}
		else if (weaponHash == 0x7846A318) {
			weaponName = "~r~Sawed-Off Shotgun";
		}
		else if (weaponHash == 0xE284C527) {
			weaponName = "~r~Assault Shotgun";
		}
		else if (weaponHash == 0x9D61E50F) {
			weaponName = "~r~Bullpup Shotgun";
		}
		else if (weaponHash == 0x3656C8C1) {
			weaponName = "~r~Stun Gun";
		}
		else if (weaponHash == 0x05FC3C11) {
			weaponName = "~r~Sniper Rifle";
		}
		else if (weaponHash == 0x0C472FE2) {
			weaponName = "~r~Heavy Sniper";
		}
		else if (weaponHash == 0xA284510B) {
			weaponName = "~r~Grenade Launcher";
		}
		else if (weaponHash == 0x4DD2DC56) {
			weaponName = "~r~Smoke Grenade Launcher";
		}
		else if (weaponHash == 0xB1CA77B1) {
			weaponName = "~r~RPG";
		}
		else if (weaponHash == 0x42BF8A85) {
			weaponName = "~r~Minigun";
		}
		else if (weaponHash == 0x93E220BD) {
			weaponName = "~r~Grenade";
		}
		else if (weaponHash == 0x2C3731D9) {
			weaponName = "~r~Sticky Bomb";
		}
		else if (weaponHash == 0xFDBC8A50) {
			weaponName = "~r~Smoke Grenade";
		}
		else if (weaponHash == 0xA0973D5E) {
			weaponName = "~r~BZGas";
		}
		else if (weaponHash == 0x24B17070) {
			weaponName = "~r~Molotov";
		}
		else if (weaponHash == 0x060EC506) {
			weaponName = "~r~Fire Extinguisher";
		}
		else if (weaponHash == 0x34A67B97) {
			weaponName = "~r~Petrol Can";
		}
		else if (weaponHash == 0xFDBADCED) {
			weaponName = "~r~Digital scanner";
		}
		else if (weaponHash == 0x88C78EB7) {
			weaponName = "~r~Briefcase";
		}
		else if (weaponHash == 0x23C9F95C) {
			weaponName = "~r~Ball";
		}
		else if (weaponHash == 0x497FACC3) {
			weaponName = "~r~Flare";
		}
		else if (weaponHash == 0xF9E6AA4B) {
			weaponName = "~r~Bottle";
		}
		else if (weaponHash == 0x61012683) {
			weaponName = "~r~Gusenberg";
		}
		else if (weaponHash == 0xC0A3098D) {
			weaponName = "Special Carabine";
		}
		else if (weaponHash == 0xD205520E) {
			weaponName = "~r~Heavy Pistol";
		}
		else if (weaponHash == 0xBFD21232) {
			weaponName = "~r~SNS Pistol";
		}
		else if (weaponHash == 0x7F229F94) {
			weaponName = "~r~Bullpup Rifle";
		}
		else if (weaponHash == 0x92A27487) {
			weaponName = "~r~Dagger";
		}
		else if (weaponHash == 0x083839C4) {
			weaponName = "~r~Vintage Pistol";
		}
		else if (weaponHash == 0x7F7497E5) {
			weaponName = "~r~Firework";
		}
		else if (weaponHash == 0xA89CB99E) {
			weaponName = "~r~Musket";
		}
		else if (weaponHash == 0x3AABBBAA) {
			weaponName = "~r~Heavy Shotgun";
		}
		else if (weaponHash == 0xC734385A) {
			weaponName = "~r~Marksman Rifle";
		}
		else if (weaponHash == 0x63AB0442) {
			weaponName = "~r~Homing Launcher";
		}
		else if (weaponHash == 0xAB564B93) {
			weaponName = "~r~Proximity Mine";
		}
		else if (weaponHash == 0x787F0BB) {
			weaponName = "~r~Snowball";
		}
		else if (weaponHash == 0x47757124) {
			weaponName = "~r~Flare Gun";
		}
		else if (weaponHash == 0xE232C28C) {
			weaponName = "~r~Garbage Bag";
		}
		else if (weaponHash == 0xD04C944D) {
			weaponName = "~r~Handcuffs";
		}
		else if (weaponHash == 0x0A3D4D34) {
			weaponName = "~r~Combat PDW";
		}
		else if (weaponHash == 0xDC4DB296) {
			weaponName = "~r~Marksman Pistol";
		}
		else if (weaponHash == 0xD8DF3C3C) {
			weaponName = "~r~Brass Knuckles";
		}
		else if (weaponHash == 0x6D544C99) {
			weaponName = "~r~Railgun";
		}
		else {
			weaponName = "~g~Unarmed";
		}
		Weapon << weaponName;
	}
	else Weapon << "~g~Unarmed";
	Vector3 myCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
	Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped, 1);
	ostringstream Zone; Zone << "Zone: ~b~" << UI::_GET_LABEL_TEXT(ZONE::GET_NAME_OF_ZONE(coords.x, coords.y, coords.z));
	Hash streetName, crossingRoad;
	PATHFIND::GET_STREET_NAME_AT_COORD(coords.x, coords.y, coords.z, &streetName, &crossingRoad);
	ostringstream Street; Street << "Street: ~g~" << UI::GET_STREET_NAME_FROM_HASH_KEY(streetName);
	float distance = Get3DDistance(coords, myCoords);
	ostringstream Distance; Distance << "Distance: ~b~";

	if (distance > 1000) {
		distance = round((distance / 1000) * 100) / 100;
		Distance << distance << " Kilometers";
	}
	else {
		distance = round(distance * 1000) / 100;
		Distance << distance << " Meters";
	}

	//std::string GetIPExternal(int player) {
	//	if (!NETWORK::NETWORK_IS_IN_SESSION()) {
	//		return "0.0.0.0";
	//	}
	//	else {
	//		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(player)) {
	//			char output[64];
	//			sprintf(output, "%u.%u.%u.%u", *(UINT8*)(PLAYER::GET_PLAYER_NAME(player) - 0x48), *(UINT8*)(PLAYER::GET_PLAYER_NAME(player) - 0x47), *(UINT8*)(PLAYER::GET_PLAYER_NAME(player) - 0x46), *(UINT8*)(PLAYER::GET_PLAYER_NAME(player) - 0x45));
	//			return output;
	//		}
	//		else {
	//			return "0.0.0.0";
	//		}
	//	}
	//}
	//Simple get theird RID

	int PlayerRID[13];
	char TheirRID[100];
	NETWORK::NETWORK_HANDLE_ONLINE_PLAYER(p, PlayerRID, 13);
	char* UserID = NETWORK::NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(&PlayerRID[0]);
	sprintf(TheirRID, "RID: %i", PlayerRID);
	// -----------
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

	char* addr = PLAYER::GET_PLAYER_NAME(ped);
	unsigned char ip1 = (int)(addr - 0x48);
	unsigned char ip2 = (int)(addr - 0x47);
	unsigned char ip3 = (int)(addr - 0x46);
	unsigned char ip4 = (int)(addr - 0x45);
	char ipbuf[4000];
	sprintf(ipbuf, "IP: %o.%i.%i.%i", ip4, ip3, ip2, ip1);
	char* addr1 = PLAYER::GET_PLAYER_NAME(p);
	unsigned char ip11 = (int)(addr1 - 0x34);
	unsigned char ip22 = (int)(addr1 - 0x35);
	unsigned char ip33 = (int)(addr1 - 0x36);
	unsigned char ip44 = (int)(addr1 - 0x37);

	char ipbuf1[4000];
	sprintf(ipbuf1, "IP: %i.%i.%i.%o", ip44, ip33, ip22, ip11);

	char IPADDR[4][4];
	if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(p)) {
		sprintf(IPADDR[0], "%i", *(UINT8*)(PLAYER::GET_PLAYER_NAME(p) - 0x48));
		sprintf(IPADDR[1], "%i", *(UINT8*)(PLAYER::GET_PLAYER_NAME(p) - 0x47));
		sprintf(IPADDR[2], "%i", *(UINT8*)(PLAYER::GET_PLAYER_NAME(p) - 0x46));
		sprintf(IPADDR[3], "%i", *(UINT8*)(PLAYER::GET_PLAYER_NAME(p) - 0x45));
		sprintf(IPADDR[4], "IP: %s.%s.%s.%s", IPADDR[0], IPADDR[1], IPADDR[2], IPADDR[3]);
	}
	else
		sprintf(IPADDR[4], "~HUD_RADAR_DAMAGE~Not Online");
	// ---------
	Menu::DrawPlayerBanner(playerName);
	Menu::DrawPlayerInfo((char*)Health.str().c_str(), 0);
	Menu::DrawPlayerInfo((char*)Armor.str().c_str(), 1);
	Menu::DrawPlayerInfo((char*)Alive.str().c_str(), 2);
	Menu::DrawPlayerInfo((char*)IsInAVehicle.str().c_str(), 3);
	Menu::DrawPlayerInfo((char*)VehicleModel.str().c_str(), 4);
	Menu::DrawPlayerInfo((char*)Speed.str().c_str(), 5);
	Menu::DrawPlayerInfo((char*)WantedLevel.str().c_str(), 6);
	Menu::DrawPlayerInfo((char*)Weapon.str().c_str(), 7);
	Menu::DrawPlayerInfo((char*)Zone.str().c_str(), 8);
	Menu::DrawPlayerInfo((char*)Street.str().c_str(), 9);
	Menu::DrawPlayerInfo((char*)Distance.str().c_str(), 10);
	Menu::DrawPlayerInfo(IPADDR[4], 11);
	//Menu::DrawPlayerInfo(TheirRID, 20);
	//Menu::DrawPlayerInfo(TheirRID[100]);


}

bool Features::orbool = false;
void Features::OffRadar(bool toggle)
{
	globalHandle(2424073).At(PLAYER::PLAYER_ID(), 421).At(200).As<int>() = 1; //Updated
	globalHandle(2437549).At(70).As<int>() = NETWORK::GET_NETWORK_TIME(); //Updated
	//if (!Features::OffRadarBool)
		//globalHandle(2424047).At(PLAYER::PLAYER_ID(), 416).At(200).As<int>() = 0;//Updated

}

bool Features::AFKNo = false;
void Features::AntiAFK(bool toggle)
{
	STATS::PLAYSTATS_IDLE_KICK(99999999);
}






bool Features::RPLoop = false;
int Features::RPLoopDelay = 7;
int Rptick2 = 0;
int Rptick = 0;
void Features::rpLoop(bool toggle) 
{
	Rptick++;
	if (Rptick > Features::RPLoopDelay) 
	{
		Memory::set_value<int>({ (2 * 4 * 2) / 2, 4 * 1000 + 280, 500 * 4 - 70 + 70 + 72 }, 3);
		Rptick2++;
		if (Rptick2 > Features::RPLoopDelay) 
		{
			Memory::set_value<int>({ (2 * 4 * 2) / 2, 4 * 1000 + 280, 500 * 4 - 70 + 70 + 72 }, 0);
			Rptick = 0;
			Rptick2 = 0;
		}
	}
}

//bool Features::alldrop = false;
//void Features::AllDrop(bool toggle)
//{ // all player 2k
//	if (alldrop)
//	{
//
//		if ((timeGetTime() - Features::TimePD2) > Features::DropDelay)
//		{
//			for (int i = 0; i < 32; i++)
//			{
//				int excludeMe = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
//				if (excludeMe > 0 && excludeMe != PLAYER::PLAYER_PED_ID())
//				{
//					Ped iPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
//					STREAMING::REQUEST_MODEL(Features::bagHash);
//					if (!STREAMING::HAS_MODEL_LOADED(Features::bagHash)) {
//						WAIT(0);
//					}
//					else {
//						Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(iPed, FALSE);
//						OBJECT::pockup(0xDE78F17E, playerPosition.x, playerPosition.y, playerPosition.z + Features::DropHeight / 10, 0, Features::DropAmount, Features::bagHash, FALSE, TRUE);
//						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Features::bagHash);
//					}
//					Features::TimePD2 = timeGetTime();
//				}
//			}
//
//		}
//	}
//}
namespace HASHHH
{
#define PICKUP_MONEY_CASE 0x1E9A99F8 

	Hash MoneyModel(int id)
	{
		switch (id)
		{
		case 0: return -1666779307; break;                                        //Paperbag
		case 1: return -1803909274; break;                                        //Paperbag2
		case 2: return 0x113FD533; break;                                         //Moneybag
		case 3: return 1803116220; break;                                         //Alien egg
		case 4: return -708789241; break;                                         //Guitar
		case 5: return 1522853652; break;                                         //Grave
		case 6: return -463441113; break;                                         //Dildo
		case 7: return -144591170; break;                                         //Dummy
		case 8: return -930879665; break;                                         //Toilet
		case 9: return -1688127; break;                                           //Weed
		case 10: return -492435441; break;                                        //Oil
		case 11: return GAMEPLAY::GET_HASH_KEY("hei_prop_heist_emp"); break;      //EMP
		case 12: return GAMEPLAY::GET_HASH_KEY("prop_juicestand"); break;         //Ball
		case 13: return GAMEPLAY::GET_HASH_KEY("prop_weed_01"); break;            //Weed2
		case 14: return GAMEPLAY::GET_HASH_KEY("p_v_43_safe_s"); break;           //Safe
		case 15: return GAMEPLAY::GET_HASH_KEY("p_spinning_anus_s"); break;       //UFO
		case 16: return GAMEPLAY::GET_HASH_KEY("prop_xmas_tree_int"); break;      //Xmas tree
		case 17: return GAMEPLAY::GET_HASH_KEY("prop_air_bigradar"); break;       //Radar
		case 18: return GAMEPLAY::GET_HASH_KEY("prop_cs_duffel_01b"); break;      //Duffel
		case 19: return GAMEPLAY::GET_HASH_KEY("PROP_MP_RAMP_03"); break;         //Ramp
		case 20: return GAMEPLAY::GET_HASH_KEY("PROP_MP_NUM_1"); break;           //1
		case 21: return GAMEPLAY::GET_HASH_KEY("PROP_MP_NUM_2"); break;           //2
		case 22: return GAMEPLAY::GET_HASH_KEY("PROP_MP_NUM_3"); break;           //3
		case 23: return GAMEPLAY::GET_HASH_KEY("prop_dummy_plane"); break;        //Plane
		case 24: return GAMEPLAY::GET_HASH_KEY("prop_anim_cash_pile_02"); break;  //Cash pile
		case 25: return GAMEPLAY::GET_HASH_KEY("prop_amb_donut"); break;          //Donut
		case 26: return GAMEPLAY::GET_HASH_KEY("prop_Ld_ferris_wheel"); break;    //Ferris wheel
		}
	}
}

bool Features::AllDropOn = false;
int Features::DropDelay = 0;
int Features::TimePD20;
int Features::RainAmount = 2500;
int Features::MoneyType = 0;

void Features::AllMoneyDrop(bool enable)
{
	if ((timeGetTime() - Features::TimePD20) > Features::DropDelay)
	{
		for (int i = 0; i < 32; i++)
		{
			if (MoneyType < 0)
			{
				MoneyType = 0;
			}
			if (MoneyType > 26)
			{
				MoneyType = 26;
			}
			if (DropDelay < 0)
			{
				DropDelay = 0;
			}
			if (DropDelay > 500)
			{
				DropDelay = 500;
			}
			int excludeMe = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
			if (excludeMe > 0 && excludeMe != PLAYER::PLAYER_PED_ID())
			{
				Ped iPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
				STREAMING::REQUEST_MODEL(HASHHH::MoneyModel(MoneyType));

				if (!STREAMING::HAS_MODEL_LOADED(HASHHH::MoneyModel(MoneyType)))
				{
					
				}
				else 
				{
					Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(iPed, false);
					OBJECT::CREATE_AMBIENT_PICKUP(0x1E9A99F8, playerPosition.x, playerPosition.y, playerPosition.z + 3, 0, Features::RainAmount, HASHHH::MoneyModel(MoneyType), FALSE, TRUE);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(HASHHH::MoneyModel(MoneyType));
				}
				Features::TimePD20 = timeGetTime();
			}
		}
	}
}

void Features::teleportallcoords(Vector3 target)
{
	for (int i2 = 0; i2 < 2; i2++)
	{
		Vector3 targetCoords = target;
		for (int i = 0; i < 32; i++)
		{
			if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)))
			{
				AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
				int netScene = NETWORK::N_C_S_S(targetCoords.x, targetCoords.y, targetCoords.z, 0.f, 0.f, 0.f, 0, 0, 0, 0.f, 0.f, 0.f);
				NETWORK::NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), netScene, "amb@code_human_cower@female@base", "base", 8.f, -8.f, 2, 0, 100.f, 0);
				NETWORK::NETWORK_START_SYNCHRONISED_SCENE(netScene);
			}
		}
		WAIT(150);
		for (int i = 0; i < 32; i++)
		{
			if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)))
			{
				AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
			}
		}
	}
}

Vehicle Online::SpawnVehicleToPlayer(char* modelg, Vector3 coords, bool tpinto = 0, float heading = 0.0f) {
	DWORD model = GAMEPLAY::GET_HASH_KEY(modelg);
	if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model)) {
		STREAMING::REQUEST_MODEL(model);
		while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(50);
		Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, heading, 1, 1);
		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
		VEHICLE::SET_VEHICLE_IS_STOLEN(veh, 0);
		return veh;
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
	}

}

void Online::teleporttocoords(Player selectedPlayer, Vector3 target)
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

void Online::trapcage(Ped ped)
{
	Vector3 remotePos = ENTITY::GET_ENTITY_COORDS(ped, 0);
	Object obj = OBJECT::CREATE_OBJECT($("prop_gold_cont_01"), remotePos.x, remotePos.y, remotePos.z - 1.f, true, false, false);
}

void Online::RequestControlOfid(Entity netid)
{
	int tick = 0;

	while (!NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netid) && tick <= 25)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netid);
		tick++;
	}
}

void Online::RequestControlOfEnt(Entity entity)
{
	int tick = 0;
	while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) && tick <= 25)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
		tick++;
	}
	if (NETWORK::NETWORK_IS_SESSION_STARTED())
	{
		int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
		RequestControlOfid(netID);
		NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
	}
}

void Online::sendText(int player, char* text, int font)
{
	if (player == PLAYER::PLAYER_ID())
	{
		UI::SET_TEXT_FONT(font);
		UI::_0x574EE85C("STRING");
		UI::_ADD_TEXT_COMPONENT_STRING(text);
		UI::_DRAW_NOTIFICATION(false, true);
	}
	else
	{
		int NetHandleBuffer = 0x10070200;
		NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, NetHandleBuffer, 13);
		NETWORK::NETWORK_SEND_TEXT_MESSAGE(text, NetHandleBuffer);
	}
}



#define OFFSET_PLAYER_NAME_LOCAL        0x7C
MODULEINFO Main_Info = { 0 };

void EventHooks::SetDisplayName(char* name)
{
	DWORD64 startChange = DWORD64(Main_Info.lpBaseOfDll);

	uintptr_t displayOff01 = Memory::get_base_offsetted(0x28B59BC);
	uintptr_t displayOff02 = Memory::get_base_offsetted(0x28BB8C4);
	uintptr_t displayOff03 = Memory::get_base_offsetted(0x2CE7FEC);
	uintptr_t displayOff04 = Memory::get_base_offsetted(0x2CEAFBF);
	uintptr_t displayOff05 = Memory::get_base_offsetted(0x2CEE3BF);
	uintptr_t displayOff06 = Memory::get_base_offsetted(0x2CEE654);
	uintptr_t displayOff07 = Memory::get_multilayer_pointer(Hooking::getWorldPtr(), { OFFSET_PLAYER, OFFSET_PLAYER_INFO, OFFSET_PLAYER_NAME_LOCAL });

	memcpy(reinterpret_cast<void*>(displayOff01), name, 16);
	memcpy(reinterpret_cast<void*>(displayOff02), name, 16);
	memcpy(reinterpret_cast<void*>(displayOff03), name, 16);
	memcpy(reinterpret_cast<void*>(displayOff04), name, 16);
	memcpy(reinterpret_cast<void*>(displayOff05), name, 16);
	memcpy(reinterpret_cast<void*>(displayOff06), name, 16);
	memcpy(reinterpret_cast<void*>(displayOff07), name, 16);

	notifyMap(Menu::Tools::StringToChar("Setting up displayname ~b~" + (std::string)name));
	WAIT(3000);
	notifyMap("Your new displayname is now ~g~visable!");
}



class AbstractCallback
{
public:
	virtual ~AbstractCallback() noexcept = default;
	AbstractCallback(AbstractCallback const&) = delete;
	AbstractCallback& operator=(AbstractCallback const&) = delete;
	AbstractCallback(AbstractCallback&&) = delete;
	AbstractCallback& operator=(AbstractCallback&&) = delete;

	virtual bool IsDone() = 0;
	virtual void OnSuccess() = 0;
	virtual void OnFailure() = 0;
protected:
	AbstractCallback() = default;
};
class KeyboardCallback : public AbstractCallback
{
public:
	explicit KeyboardCallback(std::string type, std::function<void()> action) :
		m_type(type),
		m_Action(std::move(action))
	{
	}

	bool IsDone() override
	{
		return GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD();
	}

	void OnSuccess() override
	{
		if (m_type == "NAME")
		{
			if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT())
			{
			}
			char* name = GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
			Features::SetName(name);

		}
		if (m_Action)
			std::invoke(m_Action);
	}

	void OnFailure() override
	{
		CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(0);
	}
private:
	std::function<void()> m_Action;
	std::string m_type;
};

static std::vector<DWORD64> NameAddresses;
std::vector<DWORD64> getNameAdresses()
{
	return NameAddresses;
}
void AllocateNameAddresses() {

	static DWORD64 LocalNameAddress = NULL;

	LocalNameAddress = Memory::get_multilayer_pointer(Hooking::getWorldPtr(), { 0x08, 0x10B8, 0x7C });

	if (NameAddresses.empty())
	{
		std::string CurrentMask;
		const char* NameToScan = PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID());
		for (uint8_t i = 0; i < strlen(NameToScan); i++) CurrentMask += "x";
		const char* mask = CurrentMask.c_str();

		for (DWORD64 addr : Memory::get_string_addresses(NameToScan)) {
			char buff[100];
			_snprintf_s(buff, sizeof(buff), "OtherName\t\t 0x%p (0x%.8X)", addr, addr - Memory::get_base());
			NameAddresses.push_back((addr));
		}

		if (LocalNameAddress)
			NameAddresses.push_back((LocalNameAddress));
	}
}

std::string Features::String = "";
#pragma execution_character_set("utf-8")
void Features::SetName(const std::string& name)
{
	AllocateNameAddresses();
	size_t newLen = name.size() + 1;
	if (newLen <= 1 || newLen > 20)
		return;

	char	buffer[0x20] = {};
	char* pSearch = PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()) + 0x5C;
	size_t	curLen = strlen(pSearch) + 1;
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
	int VectorSize = getNameAdresses().size();
	int i = 0;
	for (DWORD64 Address : getNameAdresses()) {
		i++;
		strncpy((char*)Address, &name[0], newLen);
	}
}



#define PROP_MONEY_BAG_01 0x113FD533
#define PICKUP_MONEY_CASE 0x1E9A99F8
int TimePD1;
int Dropfreqvalue = 100;
void Online::DropCashLobby(Ped playerPed)
{
	if ((timeGetTime() - TimePD1) > Dropfreqvalue)
	{
		for (int i = 0; i < 32; i++)
		{
			int excludeMe = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
			if (excludeMe > 0 && excludeMe != PLAYER::PLAYER_PED_ID())
			{
				Ped iPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
				STREAMING::REQUEST_MODEL(PROP_MONEY_BAG_01);
				if (!STREAMING::HAS_MODEL_LOADED(PROP_MONEY_BAG_01)) {
					WAIT(0);
				}
				else {
					Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(iPed, FALSE);
					OBJECT::CREATE_AMBIENT_PICKUP(PICKUP_MONEY_CASE, playerPosition.x, playerPosition.y, playerPosition.z + 1.0f, 0, 2000, PROP_MONEY_BAG_01, FALSE, TRUE);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PROP_MONEY_BAG_01);
				}
				TimePD1 = timeGetTime();
			}
		}

	}
}

void Recovery::FullRecovery()
{
	notifyMap("Preparing to make full account recovery");
	WAIT(1000);
	notifyMap("Loading requirements...");
	WAIT(1000);
	notifyMap("Your recovery will start in 3 seconds...");
	WAIT(3000);
	RECOVERY::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 0);
	RECOVERY::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 0);
	RECOVERY::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 0);

	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_1"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_2"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_3"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_4"), -1, 1);
	RECOVERY::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_5"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_6"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_7"), -1, 1);
	RECOVERY::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_8"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_9"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_10"), -1, 1);
	RECOVERY::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_11"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_tattoo_fm_unlocks_12"), -1, 1);

	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMRACEWORLDRECHOLDER"), 1, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_ENEMYDRIVEBYKILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_USJS_COMPLETED"), 50, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_USJS_FOUND"), 50, 0);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMWINALLRACEMODES"), 1, 0);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMWINEVERYGAMEMODE"), 1, 0);
	RECOVERY::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_DB_PLAYER_KILLS"), 1000, 0);
	RECOVERY::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_KILLS_PLAYERS"), 1000, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMHORDWAVESSURVIVE"), 21, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TDM_MVP"), 60, 0);
	RECOVERY::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_HOLD_UP_SHOPS"), 20, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_RACES_WON"), 101, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_NO_ARMWRESTLING_WINS"), 21, 0);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMATTGANGHQ"), 1, 0);
	RECOVERY::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMBBETWIN"), 50000, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 51, 0);
	STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FMFULLYMODDEDCAR"), 1, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_TOTALKILLS"), 500, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_DM_TOTAL_DEATHS"), 412, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TIMES_FINISH_DM_TOP_3"), 36, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_PLAYER_HEADSHOTS"), 623, 0);
	RECOVERY::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_DM_WINS"), 63, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TDM_WINS"), 13, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_GTA_RACES_WON"), 12, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_GOLF_WON"), 2, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_TG_WON"), 2, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_RT_WON"), 2, 0);
	RECOVERY::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_CT_WON"), 2, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_SHOOTRANG_GRAN_WON"), 2, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_FM_TENNIS_WON"), 2, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TENNIS_MATCHES_WON"), 2, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_TDEATHMATCH_WON"), 63, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_WON"), 101, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_DEATHMATCH_LOST"), 23, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_MPPLY_TOTAL_RACES_LOST"), 36, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_25_KILLS_STICKYBOMBS"), 50, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_50_KILLS_GRENADES"), 50, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS"), 50, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_AWD_20_KILLS_MELEE"), 50, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_MOLOTOV_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CMBTPISTOL_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_PISTOL50_ENEMY_KILLS"), 600, 0);
	RECOVERY::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_APPISTOL_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_MICROSMG_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_SMG_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_ASLTSMG_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_ASLTRIFLE_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CRBNRIFLE_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_ADVRIFLE_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_MG_ENEMY_KILLS"), 600, 0);
	RECOVERY::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CMBTMG_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_ASLTMG_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_PUMP_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_SAWNOFF_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_BULLPUP_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_ASLTSHTGN_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_SNIPERRFL_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_HVYSNIPER_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_GRNLAUNCH_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_RPG_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_MINIGUNS_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_GRENADE_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_SMKGRENADE_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_STKYBMB_ENEMY_KILLS"), 600, 0);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_MOLOTOV_ENEMY_KILLS"), 600, 0);

	RECOVERY::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_1"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_2"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_3"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_4"), -1, 1);
	RECOVERY::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_5"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_6"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_HAIR_7"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_1"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_2"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_3"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_4"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_5"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_6"), -1, 1);
	RECOVERY::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_JBIB_7"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_1"), -1, 1);
	RECOVERY::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_2"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_3"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_4"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_5"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_6"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_LEGS_7"), -1, 1);
	RECOVERY::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_1"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_2"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_3"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_4"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_5"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_6"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_FEET_7"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_1"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_2"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_3"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_4"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_5"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_6"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_BERD_7"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_1"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_2"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_3"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_4"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_5"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_6"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_7"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_8"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_9"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_PROPS_10"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_OUTFIT"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_1"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_2"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_3"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_4"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_5"), -1, 1);;
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_6"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_HAIR_7"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_1"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_2"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_3"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_4"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_5"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_6"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_JBIB_7"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_1"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_2"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_3"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_4"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_5"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_6"), -1, 1);;
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_LEGS_7"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_1"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_2"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_3"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_4"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_5"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_6"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_FEET_7"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_1"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_2"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_3"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_4"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_5"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_6"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_BERD_7"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_1"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_2"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_3"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_4"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_5"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_6"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_7"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_8"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_9"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_PROPS_10"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_OUTFIT"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TORSO"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_1"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_2"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_3"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_4"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_5"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_6"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL_7"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL2"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_SPECIAL2_1"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_DECL"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH_1"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_AVAILABLE_TEETH_2"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TORSO"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_1"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_2"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_3"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_4"), -1, 1);
	STATS::I_S_S_T(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_5"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_6"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL_7"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL2"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_SPECIAL2_1"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_DECL"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH_1"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_CLTHS_ACQUIRED_TEETH_2"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_0"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_1"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_2"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_3"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_4"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_5"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_6"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_7"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_8"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_9"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_10"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_11"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_12"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_13"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_14"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_15"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_16"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_17"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_18"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_19"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_21"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_22"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_23"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_24"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_24"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_25"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_26"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_27"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_28"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_29"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_30"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_31"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_32"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_33"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_34"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_35"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_36"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_37"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_38"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_39"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_DLC_APPAREL_ACQUIRED_40"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_2"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_3"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_4"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_5"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_6"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_7"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_8"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_9"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_12"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_13"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_1"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_10"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_11"), -1, 1);
	STATS::S_I_S(GAMEPLAY::GET_HASH_KEY("MP0_ADMIN_CLOTHES_GV_BS_12"), -1, 1);
	WAIT(2000);
	notifyMap("full account recovery has been done!");
}

int entdistance = 4;
bool disallowNewEntity;
Entity gravityentity;
Entity shotentity;
Vehicle gravityvehicle;
bool grav_target_locked;
bool Features::GravGun = false;

void Features::GravGunFunction() {
	Entity EntityTarget;
	DWORD equippedWeapon;
	WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &equippedWeapon, 1);
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
	Vector3 dir = rot_to_direction(&rot);
	Vector3 camPosition = CAM::GET_GAMEPLAY_CAM_COORD();
	Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
	float spawnDistance = get_distance(&camPosition, &playerPosition);
	spawnDistance += 5;
	Vector3 spawnPosition = add(&camPosition, &multiply(&dir, spawnDistance));


	Player tempPed = PLAYER::PLAYER_ID();
	if (grav_target_locked)
	{
		if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &EntityTarget) && GetAsyncKeyState(VK_RBUTTON))
		{
			Vector3 EntityTargetPos = ENTITY::GET_ENTITY_COORDS(EntityTarget, 0);
			PLAYER::DISABLE_PLAYER_FIRING(tempPed, true);
			if (ENTITY::IS_ENTITY_A_PED(EntityTarget) && PED::IS_PED_IN_ANY_VEHICLE(EntityTarget, 1))
			{
				EntityTarget = PED::GET_VEHICLE_PED_IS_IN(EntityTarget, 0);
			}

			RequestControlOfEnt(EntityTarget);

			if (ENTITY::IS_ENTITY_A_VEHICLE(EntityTarget))
				ENTITY::SET_ENTITY_HEADING(
					EntityTarget, ENTITY::GET_ENTITY_HEADING(tempPed));

			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(EntityTarget, spawnPosition.x, spawnPosition.y, spawnPosition.z, 0, 0, 0);

			if (GetAsyncKeyState(VK_LBUTTON))
			{
				AUDIO::PLAY_SOUND_FROM_ENTITY(-1, "Foot_Swish", EntityTarget, "docks_heist_finale_2a_sounds", 0, 0);
				ENTITY::SET_ENTITY_HEADING(EntityTarget, ENTITY::GET_ENTITY_HEADING(tempPed));
				ENTITY::APPLY_FORCE_TO_ENTITY(EntityTarget, 1, dir.x * 10000.0f, dir.y * 10000.0f, dir.z * 10000.0f, 0.0f, 0.0f,
					0.0f, 0, 0, 1, 1, 0, 1);
				grav_target_locked = false;
				PLAYER::DISABLE_PLAYER_FIRING(tempPed, false);
			}
		}
	}
	if (!PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &EntityTarget))
	{
		grav_target_locked = true;
		PLAYER::DISABLE_PLAYER_FIRING(tempPed, false);
	}
}

bool RequestNetworkControl(uint vehID)
{
	int Tries = 0;
	bool
		hasControl = false,
		giveUp = false;
	do
	{
		hasControl = NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehID);
		Tries++;
		if (Tries > 300)
			giveUp = true;
	} while (!hasControl && !giveUp);

	if (giveUp)
		return false;
	else return true;
}

bool Features::GravityGun = false;
void Features::gravitygun(bool toggle) {

	Entity EntityTarget;
	DWORD equippedWeapon;
	WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &equippedWeapon, 1);
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
	Vector3 dir = rot_to_direction(&rot);
	Vector3 camPosition = CAM::GET_GAMEPLAY_CAM_COORD();
	Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
	float spawnDistance = get_distance(&camPosition, &playerPosition);
	spawnDistance += 6;
	Vector3 spawnPosition = add(&camPosition, &multiply(&dir, spawnDistance));


	Player tempPed = PLAYER::PLAYER_ID();

	if (grav_target_locked)
	{
		if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &EntityTarget) && GetAsyncKeyState(VK_RBUTTON))
		{
			Vector3 EntityTargetPos = ENTITY::GET_ENTITY_COORDS(EntityTarget, 0);
			PLAYER::DISABLE_PLAYER_FIRING(tempPed, true);
			if (ENTITY::IS_ENTITY_A_PED(EntityTarget) && PED::IS_PED_IN_ANY_VEHICLE(EntityTarget, 1))
			{
				EntityTarget = PED::GET_VEHICLE_PED_IS_IN(EntityTarget, 0);
			}

			RequestNetworkControl(EntityTarget);

			if (ENTITY::IS_ENTITY_A_VEHICLE(EntityTarget))
				ENTITY::SET_ENTITY_HEADING(
					EntityTarget, ENTITY::GET_ENTITY_HEADING(tempPed));

			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(EntityTarget, spawnPosition.x, spawnPosition.y, spawnPosition.z, 0, 0, 0);

			if (GetAsyncKeyState(VK_LBUTTON))
			{
				AUDIO::PLAY_SOUND_FROM_ENTITY(-1, "Foot_Swish", EntityTarget, "docks_heist_finale_2a_sounds", 0, 0);
				ENTITY::SET_ENTITY_HEADING(EntityTarget, ENTITY::GET_ENTITY_HEADING(tempPed));
				ENTITY::APPLY_FORCE_TO_ENTITY(EntityTarget, 1, dir.x * 10000.0f, dir.y * 10000.0f, dir.z * 10000.0f, 0.0f, 0.0f,
					0.0f, 0, 0, 1, 1, 0, 1);
				grav_target_locked = false;
				PLAYER::DISABLE_PLAYER_FIRING(tempPed, false);
			}
		}
	}
	if (!PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &EntityTarget))
	{
		grav_target_locked = true;
		PLAYER::DISABLE_PLAYER_FIRING(tempPed, false);
	}


}




















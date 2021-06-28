#include "stdafx.h"

namespace SVT
{
	//int's & bool's
	bool CrashHelp(int args, int test);
	//void's
	void v2(int client);             //SVT Crash v2
	void v3(int client);             //SVT Crash v3
	void v4(int client);             //SVT Crash v4
	void v5(int client);             //SVT Crash v5
	void v6(int client);             //SVT Crash v6
	void v7(int client);             //SVT Crash v7
	void v8(int client);             //SVT Crash v8
	void v9(int client);             //SVT Crash v9
	void v10(int client);            //SVT Crash v10
	void v11(int client);            //SVT Crash v11
	void crash_steps();              //To do all crashes
	void FreezeTaxi_Heli();
}

int TypeAddr1 = 184;
int TypeAddr2 = 116;
//VEHICLE TYPE EDITOR
void SVT::FreezeTaxi_Heli()
{
	static int(__cdecl * VehicleType1)(int Vehicle) = (int(__cdecl*)(int))(0xCD78AC70 + ((195 * 0x270) - TypeAddr1));
	static int(__cdecl * VehicleType2)(int Vehicle) = (int(__cdecl*)(int))(0xCD78AC70 + ((195 * 0x270) - TypeAddr2));
	*(int*)VehicleType1 = 0x0B;
	*(int*)VehicleType2 = 0xE6;
}

static void Trigger_Script_Event_(int* Args, int Agrcount, Player BitsetPlayer) 
{
	int Bitset = 0;
	GAMEPLAY::SET_BIT(&Bitset, BitsetPlayer);
	if (Bitset != 0) {
		SCRIPT::T_SS_E(1, Args, Agrcount, Bitset);
	}
}


void SVT::v2(int client)
{
	Vector3 Cords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(client), true);
	STREAMING::REQUEST_MODEL(0xC703DB5F); //Taxi
	STREAMING::REQUEST_MODEL(-163714847); //The Pilot
	if (STREAMING::IS_MODEL_VALID(0xC703DB5F) && STREAMING::IS_MODEL_VALID(-163714847)) {
		FreezeTaxi_Heli();
		Vehicle Taxi = VEHICLE::CREATE_VEHICLE(0xC703DB5F, Cords.x, Cords.y, Cords.z + 10.0f, 0.0f, true, true);
		NETWORK::NETWORK_FADE_IN_ENTITY(Taxi, true);
		Ped Pilot = PED::CREATE_PED(1, -163714847, Cords.x, Cords.y, Cords.z + 15.0f, 0.0f, true, true);
		if (ENTITY::DOES_ENTITY_EXIST(Taxi) && ENTITY::DOES_ENTITY_EXIST(Pilot)) {
			ENTITY::APPLY_FORCE_TO_ENTITY(Taxi, true, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f, 0.0f, true, true, true, true, true, true);
			PED::SET_PED_INTO_VEHICLE(Pilot, Taxi, -1);
			AI::TASK_HELI_MISSION(Pilot, Taxi, 0, PLAYER::GET_PLAYER_PED(client), 0.0f, 0.0f, 0.0f, 4, 100.0, 0.0, 0.0f, -1, -1, -1, 32);
			notifyMap("Sent Freeze car");
		}
	}
}

void SVT::v3(int client) 
{
	Vector3 Cords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(client), true);
	STREAMING::REQUEST_MODEL(0x15F27762); //Taxi
	STREAMING::REQUEST_MODEL(-163714847); //The Pilot
	if (STREAMING::IS_MODEL_VALID(0xC703DB5F) && STREAMING::IS_MODEL_VALID(-163714847)) {
		FreezeTaxi_Heli();
		Vehicle Taxi = VEHICLE::CREATE_VEHICLE(0xC703DB5F, Cords.x, Cords.y, Cords.z + 10.0f, 0.0f, true, true);
		NETWORK::NETWORK_FADE_IN_ENTITY(Taxi, true);
		Ped Pilot = PED::CREATE_PED(1, -163714847, Cords.x, Cords.y, Cords.z + 15.0f, 0.0f, true, true);
		if (ENTITY::DOES_ENTITY_EXIST(Taxi) && ENTITY::DOES_ENTITY_EXIST(Pilot)) {
			ENTITY::APPLY_FORCE_TO_ENTITY(Taxi, true, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f, 0.0f, true, true, true, true, true, true);
			PED::SET_PED_INTO_VEHICLE(Pilot, Taxi, -1);
			AI::TASK_HELI_MISSION(Pilot, Taxi, 0, PLAYER::GET_PLAYER_PED(client), 0.0f, 0.0f, 0.0f, 4, 100.0f, 0.0f, 0.0f, -1, -1, -1, 32);
			notifyMap("Sent Freeze car");
		}
	}
}

void SVT::v4(int client)
{
	if (STREAMING::HAS_MODEL_LOADED(-1003748966)) {
		notifyMap("Step 1/3\nComplete");
		Vector3 Loc = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(client), true);
		Ped CrashObject = PED::CREATE_PED(26, -1003748966, Loc.x, Loc.y, Loc.z, 0.0f, true, true);
		Vehicle CrashPed = VEHICLE::CREATE_VEHICLE(-1003748966, Loc.x, Loc.y, Loc.z, 0.0f, true, true);
		if (ENTITY::DOES_ENTITY_EXIST(CrashPed)) {
			ENTITY::ATTACH_ENTITY_TO_ENTITY(CrashObject, PLAYER::GET_PLAYER_PED(client), -1, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(CrashPed, PLAYER::GET_PLAYER_PED(client), -1, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
			notifyMap("Step 2/3\nComplete");
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(-1003748966);
			if (ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(CrashObject, PLAYER::GET_PLAYER_PED(client))) {
				ENTITY::SET_ENTITY_VISIBLE1(CrashObject, 0);
				ENTITY::SET_ENTITY_VISIBLE1(CrashPed, 0);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(CrashObject, 1, 1);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(CrashPed, 1, 1);
				ENTITY::DELETE_ENTITY(&CrashObject);
				ENTITY::DELETE_ENTITY(&CrashPed);
				notifyMap("Step 3/3\nComplete");
			}
		}
	}
	else {
		STREAMING::REQUEST_MODEL(-1003748966);
	}
}

void SVT::v5(int client)
{
	if (STREAMING::HAS_MODEL_LOADED(-1003748966)) {
		notifyMap("Step 1/3\nComplete");
		Vector3 Loc = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(client), true);
		Ped CrashObject = PED::CREATE_PED(26, -1003748966, Loc.x, Loc.y, Loc.z, 0.0f, true, true);
		Vehicle CrashPed = VEHICLE::CREATE_VEHICLE(-1003748966, Loc.x, Loc.y, Loc.z, 0.0f, true, true);
		Object CrashVh = OBJECT::CREATE_OBJECT(-1003748966, Loc.x, Loc.y, Loc.z, 0, 1, 1);
		if (ENTITY::DOES_ENTITY_EXIST(CrashPed)) {
			ENTITY::ATTACH_ENTITY_TO_ENTITY(CrashObject, PLAYER::GET_PLAYER_PED(client), -1, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(CrashPed, PLAYER::GET_PLAYER_PED(client), -1, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(CrashVh, PLAYER::GET_PLAYER_PED(client), -1, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
			notifyMap("Step 2/3\nComplete");
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(-1003748966);
			if (ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(CrashObject, PLAYER::GET_PLAYER_PED(client))) {
				ENTITY::SET_ENTITY_VISIBLE1(CrashObject, 0);
				ENTITY::SET_ENTITY_VISIBLE1(CrashPed, 0);
				ENTITY::SET_ENTITY_VISIBLE1(CrashVh, 0);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(CrashObject, 1, 1);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(CrashPed, 1, 1);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(CrashVh, 1, 1);
				ENTITY::DELETE_ENTITY(&CrashObject);
				ENTITY::DELETE_ENTITY(&CrashPed);
				ENTITY::DELETE_ENTITY(&CrashVh);
				notifyMap("Step 3/3\nComplete");
			}
		}
	}
	else {
		STREAMING::REQUEST_MODEL(-1003748966);
	}
}

void SVT::v6(int client) {//player
	int vVar0[3];// int client use to be int player 
	vVar0[0] = 3;
	vVar0[1] = client;//player
	vVar0[2] = 26;
	Trigger_Script_Event_(vVar0, 3, client);//player
}

void SVT::v7(int client) {
	STREAMING::REQUEST_MODEL(0x4498DDE);
	Vector3 Loc = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(client), 1);
	if (STREAMING::HAS_MODEL_LOADED(0x4498DDE)) {
		int Crash = (PED::CREATE_PED(21, 0x3F039CBA, Loc.x, Loc.y, Loc.z, 0, 1, 0));
		if (ENTITY::DOES_ENTITY_EXIST(Crash)) {
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(0x4498DDE);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(Crash, client, -1, 0, -0.3, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1);
		}
	}
}

void SVT::v8(int client) {
	*(int*)0x82FBFE24 = 0x60000000;
	*(int*)0x82FBFE2C = 0x60000000;
	*(int*)0x82FBFE14 = 0x419A0024;
	*(int*)0x82FBFE24 = 0x419A00EC;
	*(int*)0x82FBFE2C = 0x38600004;
	*(int*)0x830D8094 = 0x817E0010;
	UINT64 unk = ((UINT64(*)(UINT64, UINT64))0x82918F38)(client, true);//get_player_net_address
	((UINT64(*)(UINT64, UINT64))0x830E1B10)(1, unk);
	((UINT64(*)(UINT64, UINT64))0x830E1B10)(1, unk);
	*(int*)0x82FBFE14 = 0x60000000;
	*(int*)0x82FBFE24 = 0x60000000;
	*(int*)0x82FBFE2C = 0x60000000;
	*(int*)0x830D8094 = 0x39600018;
	notifyMap("~r~Crash Sent");
}

void SVT::v9(int client)
{
	*(int*)0x82FBFE14 = 0x60000000;
	*(int*)0x82FBFE24 = 0x60000000;
	*(int*)0x82FBFE2C = 0x60000000;
	*(int*)0x830D8094 = 0x39600018;
	*(int*)0x830EEF60 = 0x60000000;
	*(int*)0x830ED27C = 0x38800000;
	UINT64 unk = ((UINT64(*)(UINT64, UINT64))0x82918F38)(client, true);
	((UINT64(*)(UINT64, UINT64))0x830E1B10)(1, unk);
	((UINT64(*)(UINT64, UINT64))0x830E1B10)(1, unk);
	*(int*)0x82FBFE14 = 0x419A0024;
	*(int*)0x82FBFE24 = 0x419A00EC;
	*(int*)0x82FBFE2C = 0x38600004;
	*(int*)0x830D8094 = 0x817E0010;
	*(int*)0x830EB6E4 = 0x38800000;
	notifyMap("~r~Crash sent");
}

void SVT::v10(int client)
{
	Vector3 Pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(client), 1);
	ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), Pos.x, Pos.y, Pos.z, 0, 0, 0, 1);
	Object obj = OBJECT::CREATE_OBJECT(0x6B795EBC, Pos.x, Pos.y, Pos.z, 1, 1, 1);
	ENTITY::SET_ENTITY_VISIBLE1(obj, false);
	WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xB1CA77B1, 9999, 1);
	if (PLAYER::GET_NUMBER_OF_PLAYERS() > 2) {
		int li_r4 = 0x38800000;
		int i_o = ((int(*)(int))0x8352A738)(obj);
		if (i_o) {
			i_o = *(int*)(i_o + 0x4C);
			if (i_o) {
				i_o = *(unsigned short*)(i_o + 6);
			}
		}
		*(int*)0x830EEDDC = li_r4 + i_o;
		*(int*)0x830EEEDC = li_r4 + 1;
		*(int*)0x830EEF60 = 0x60000000;
		*(int*)0x820A1EBC = (int)CrashHelp;
		*(int*)0x830EB6E4 = li_r4;
		*(int*)0x830ED27C = li_r4;
		WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::GET_PLAYER_PED(client), 0);
		WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED(client), 1);
	}
	GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Pos.x, Pos.y, Pos.z + 25.0f, Pos.x, Pos.y, Pos.z + 26.0f, 5, 0, 0xB1CA77B1, PLAYER::PLAYER_PED_ID(), 1, 1, 5.0f);
}

void SVT::v11(int client)
{
	Vector3 Pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(client), 1);
	ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), Pos.x, Pos.y, Pos.z, 0, 0, 0, 1);
	Object obj = OBJECT::CREATE_OBJECT(0x6B795EBC, Pos.x, Pos.y, Pos.z, 1, 1, 1);
	ENTITY::SET_ENTITY_VISIBLE(obj, false, false);
	WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xB1CA77B1, 9999, 1);
	if (PLAYER::GET_NUMBER_OF_PLAYERS() > 2) {
		int li_r4 = 0x38800000;
		int i_o = ((int(*)(int))0x8352A738)(obj);
		if (i_o) {
			i_o = *(int*)(i_o + 0x4C);
			if (i_o) {
				i_o = *(unsigned short*)(i_o + 6);
			}
		}
		*(int*)0x830EEDDC = li_r4 + i_o;
		*(int*)0x830EEEDC = li_r4 + 1;
		v2(client); v6(client);
		v8(client); v9(client);
		*(int*)0x830EEF60 = 0x60000000;
		*(int*)0x820A1EBC = (int)CrashHelp;
		*(int*)0x830EB6E4 = li_r4;
		*(int*)0x830ED27C = li_r4;
		WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::GET_PLAYER_PED(client), 0);
		WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED(client), 1);
	}
	GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Pos.x, Pos.y, Pos.z + 25.0f, Pos.x, Pos.y, Pos.z + 26.0f, 5, 0, 0xB1CA77B1, PLAYER::PLAYER_PED_ID(), 1, 1, 5.0f);
}

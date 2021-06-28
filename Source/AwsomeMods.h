#include "stdafx.h"

void loadA(char* animation)
{
	if (!STREAMING::HAS_ANIM_DICT_LOADED(animation))
	{
		STREAMING::REQUEST_ANIM_DICT(animation);
	}
}
void loadM(char* model)
{
	if (STREAMING::IS_MODEL_VALID(GAMEPLAY::GET_HASH_KEY(model)) && !STREAMING::HAS_MODEL_LOADED(GAMEPLAY::GET_HASH_KEY(model)))
	{
		STREAMING::REQUEST_MODEL(GAMEPLAY::GET_HASH_KEY(model));
	}
}

void request_() {
	loadA("move_m@brave");
	loadM("w_pi_pistol");

}

int Rr = 153;
int Rg = 102;
int Rb = 255;
int entityHit, PBone, Entity_Punch, _Mouvement;
BOOL hit__ = 0; BOOL hit2 = 0, on_wall_hit = 0;
Vector3 endCoords, endCoords2, surfaceNormal, arriveCoords;
int ray_result_, ray_result_2, wall_detected;
bool walkwalking = 0, on_wall = 0;
Vector3 CamRotationWall;
Object arrive_helper, wall_helper;

void wall_walking()
{

	Vector3 starting_p = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
	Vector3 ending_p = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 0.50, 0.0);
	float heading;
	GRAPHICS::DRAW_LINE(starting_p.x, starting_p.y, starting_p.z, ending_p.x, ending_p.y, ending_p.z, Rr, Rg, Rb, 255);

	int wall_ray = WORLDPROBE::_START_SHAPE_TEST_RAY(starting_p.x, starting_p.y, starting_p.z, ending_p.x, ending_p.y, ending_p.z, 1, PLAYER::PLAYER_PED_ID(), 7);
	WORLDPROBE::GET_SHAPE_TEST_RESULT(wall_ray, &hit__, &endCoords, &surfaceNormal, &wall_detected);

	if (hit__)
	{
		if (!ENTITY::DOES_ENTITY_EXIST(wall_helper))
		{
			wall_helper = OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY("w_pi_pistol"), endCoords.x, endCoords.y, endCoords.z, 1, 0, 0);
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(wall_helper, endCoords.x, endCoords.y, endCoords.z, 0, 0, 0);
			ENTITY::SET_ENTITY_COLLISION_(wall_helper, 0);
			ENTITY::FREEZE_ENTITY_POSITION(wall_helper, 1);
			ENTITY::SET_ENTITY_VISIBLE1(wall_helper, 0);

			heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
			ENTITY::SET_ENTITY_HEADING(wall_helper, heading);

			ENTITY::ATTACH_ENTITY_TO_ENTITY(PLAYER::PLAYER_PED_ID(), wall_helper, -1, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 1);
			//AI::TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), "move_crouch_proto", "idle_intro", 8.0, 0.0, -1, 1, 0, 0, 0, 0);
			on_wall = 1;
		}
	}

	if (ENTITY::DOES_ENTITY_EXIST(wall_helper))
	{
		Vector3 rot_ = ENTITY::GET_ENTITY_ROTATION(wall_helper, 2);
		ENTITY::SET_ENTITY_ROTATION(wall_helper, 89.0, rot_.y, rot_.z, 2, 1);
	}

	if (on_wall) {

		CAM::_CLAMP_GAMEPLAY_CAM_PITCH(-90.0, 90.0);

		Vector3 ending_p = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 0.35, -2.20); //-1.10
		int on_wall_ray = WORLDPROBE::_START_SHAPE_TEST_RAY(starting_p.x, starting_p.y, starting_p.z, ending_p.x, ending_p.y, ending_p.z, 1, PLAYER::PLAYER_PED_ID(), 7);
		WORLDPROBE::GET_SHAPE_TEST_RESULT(on_wall_ray, &on_wall_hit, &endCoords, &surfaceNormal, &wall_detected);

		GRAPHICS::DRAW_LINE(starting_p.x, starting_p.y, starting_p.z, ending_p.x, ending_p.y, ending_p.z, 0, 0, 255, 255);

		if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, 193))
		{
			if (on_wall_hit)
			{
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(wall_helper, endCoords.x, endCoords.y, endCoords.z, 0, 0, 0);
			}
			else {
				if (!ENTITY::DOES_ENTITY_EXIST(arrive_helper))
				{
					arrive_helper = OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY("w_pi_pistol"), endCoords.x, endCoords.y, endCoords.z, 1, 0, 1);
					ENTITY::SET_ENTITY_COLLISION_(arrive_helper, 0);
					ENTITY::FREEZE_ENTITY_POSITION(arrive_helper, 1);
					ENTITY::SET_ENTITY_VISIBLE1(arrive_helper, 0);
				}
				else {

					Vector3 dim_min, dim_max;
					float ground;

					GAMEPLAY::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()), &dim_min, &dim_max);
					Vector3 Position_ = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), dim_min.x, dim_min.y + 4.5, dim_min.z + 2.5f);
					ENTITY::SET_ENTITY_COORDS(arrive_helper, ending_p.x, ending_p.y, ending_p.z, 0, 0, 0, 1);

					Vector3 arrive_helper_coords = ENTITY::GET_ENTITY_COORDS(arrive_helper, 1);

					ENTITY::DELETE_ENTITY(&wall_helper);
					if (ENTITY::DOES_ENTITY_EXIST(arrive_helper))
					{
						ENTITY::DELETE_ENTITY(&arrive_helper);
					}

					GAMEPLAY::_GET_GROUND_Z_FOR_3D_COORD(arrive_helper_coords.x, arrive_helper_coords.y, arrive_helper_coords.z, &ground);
					ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), arrive_helper_coords.x, arrive_helper_coords.y, arrive_helper_coords.z, 0, 0, 0, 1);

					//ENTITY::SET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID(), heading);
					AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
					on_wall_hit = 0;
					on_wall = 0;
				}
			}
		}

		if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, 192) && on_wall)
		{
			ENTITY::DELETE_ENTITY(&wall_helper);
			if (ENTITY::DOES_ENTITY_EXIST(arrive_helper))
			{
				ENTITY::DELETE_ENTITY(&arrive_helper);
			}
			AI::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
			on_wall = 0;
		}

	}

	if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, 193) && on_wall)
	{
		if (!ENTITY::IS_ENTITY_PLAYING_ANIM(PLAYER::PLAYER_PED_ID(), "move_m@brave", "run", 1)) {
			AI::TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), "move_m@brave", "run", 8.0, 0.0, -1, 1, 0, 0, 0, 0);
		}
	}

	if (CONTROLS::IS_DISABLED_CONTROL_JUST_RELEASED(0, 193) && on_wall)
	{
		AI::STOP_ANIM_TASK(PLAYER::PLAYER_PED_ID(), "move_m@brave", "run", 2.0);
		//AI::TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), "move_crouch_proto", "idle_intro", 8.0, 0.0, -1, 1, 0, 0, 0, 0);
	}

}

int lvlvalue;
void SpoofOnlineLevel(int value)
{
	globalHandle(1589747).At(PLAYER::PLAYER_ID(), 818).At(211).At(6).As<int>() = lvlvalue; //globalHandle(1589747).At(PLAYER::PLAYER_ID(), 818).At(211).At(6).As<int>() = -1;

}

bool AimbotBool = false;
void Aimbot()
{
	int player = PLAYER::PLAYER_ID();
	int playerPed = PLAYER::PLAYER_PED_ID();

	if (AimbotBool)
	{
		for (int i = 0; i < 32; i++)
		{
			if (i != player)
			{
				if (GetAsyncKeyState(VK_RBUTTON))
				{
					Ped targetPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
					Vector3 targetPos = ENTITY::GET_ENTITY_COORDS(targetPed, 1);
					BOOL exists = ENTITY::DOES_ENTITY_EXIST(targetPed);
					BOOL dead = PLAYER::IS_PLAYER_DEAD(targetPed);

					if (exists && !dead)
					{
						float screenX, screenY;
						BOOL onScreen = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(targetPos.x, targetPos.y, targetPos.z, &screenX, &screenY);
						if (ENTITY::IS_ENTITY_VISIBLE(targetPed) && onScreen)
						{
							if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(playerPed, targetPed, 17))
							{
								Vector3 targetCoords = PED::GET_PED_BONE_COORDS(targetPed, 31086, 0, 0, 0);
								PED::SET_PED_SHOOTS_AT_COORD(playerPed, targetCoords.x, targetCoords.y, targetCoords.z, 1);

							}
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

bool WaterShoot = false;
void ShootWater()
{
	if (WaterShoot)
	{
		Ped PedID = PLAYER::PLAYER_PED_ID();
		Vector3 pos;
		WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PedID, &pos);
		Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_PED_ID());
		FIRE::ADD_EXP_123(pos.x, pos.y, pos.z, 13, 5.f, true, false, 0.f, false);
	}
	else
	{
		NULL;
	}
}

bool OffMapToggle = false;

void OffOnlineMap()
{
	int OffTime = 1000;
	if (OffMapToggle)
	{
		globalHandle(2423801).At(PLAYER::PLAYER_ID(), 413).At(200).As<int>() = 1;
		globalHandle(2437022).At(70).As<int>() = NETWORK::GET_NETWORK_TIME() + (OffTime * 59) + 1;
	}
	else
	{

	}
}

bool NoIdlekick = false;

void defuseIdleKick()
{
	if (NoIdlekick) 
	{
		globalHandle(262145).At(86).As<int>() = 999999;
		globalHandle(262145).At(87).As<int>() = 999999;
		globalHandle(262145).At(88).As<int>() = 999999;
		globalHandle(262145).At(89).As<int>() = 999999;
	}
	else
	{

	}

}

int HonkPower;
int MinSpeed = 50;
bool Car_HonkBoost = false;
bool HonkEffect = false;

void CarHonkBoost()
{
	Vehicle MyVeh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID()), false);

	if (Car_HonkBoost)
	{
		if (PLAYER::IS_PLAYER_PRESSING_HORN(PLAYER::PLAYER_ID()))
		{
			NETWORK::N_R_C_O_E(MyVeh);
			if (NETWORK::N_H_C_O_E(MyVeh))
			{
				if (MinSpeed < HonkPower)
				{
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(MyVeh, HonkPower);
				}
				else if (MinSpeed > HonkPower)
				{
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(MyVeh, MinSpeed);
				}

				if (HonkEffect)
				{
					GRAPHICS::_START_SCREEN_EFFECT("RaceTurbo", 0, true);
				}
				else if (!HonkEffect)
				{
					GRAPHICS::_STOP_SCREEN_EFFECT("RaceTurbo");
				}
			}
		}
		else
		{
			GRAPHICS::_STOP_SCREEN_EFFECT("RaceTurbo");
		}
	}
}

bool Features::freeT = false;
void Features::freeCamt(bool toggle)
{
	static bool lock;
	static std::int32_t cam;
	static float dist;
	auto rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
	auto coord = CAM::GET_GAMEPLAY_CAM_COORD();
	Vector3 p_coord = { 0,0,0 };
	int Handle = PLAYER::PLAYER_PED_ID();

	if (!CAM::DOES_CAM_EXIST(cam)) {
		cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
		CAM::SET_CAM_ROT(cam, rot.x, rot.y, rot.z, 0);
		CAM::SET_CAM_COORD(cam, coord.x, coord.y, coord.z);
	}
	if (!toggle)
	{
		Vector3 camCoords = CAM::GET_CAM_COORD(cam);
		ENTITY::SET_ENTITY_COORDS(Handle, camCoords.x, camCoords.y, camCoords.z, 0, 0, 0, 1);
		CAM::RENDER_SCRIPT_CAMS(false, true, 700, 1, 1);
		CAM::SET_CAM_ACTIVE(cam, 0);
		CAM::DESTROY_CAM(cam, true);
		PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), 0);

	}

	CAM::RENDER_SCRIPT_CAMS(true, true, 700, 1, 1);
	CAM::SET_CAM_ACTIVE(cam, 1);
	CAM::SET_CAM_ROT(cam, rot.x, rot.y, rot.z, 0);

	p_coord = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);

	ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), p_coord.x, p_coord.y, p_coord.z, 0, 0, 0);
	PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), 1);
	UI::HIDE_HUD_AND_RADAR_THIS_FRAME();

	auto speed = .5f;
	if (IsKeyPressed(VK_LSHIFT))
	{
		speed += .3f;
	}

	if (IsKeyPressed(VK_KEY_S))
	{
		speed /= -1;
		auto c = add(&CAM::GET_CAM_COORD(cam), &multiply(&rot_to_direction(&rot), speed));
		CAM::SET_CAM_COORD(cam, c.x, c.y, c.z);
	}

	if (IsKeyPressed(VK_KEY_W))
	{
		auto c = add(&CAM::GET_CAM_COORD(cam), &multiply(&rot_to_direction(&rot), speed));
		CAM::SET_CAM_COORD(cam, c.x, c.y, c.z);
	}
}

namespace OnlineChat
{

}

namespace MySelf
{
	//bools
	bool cargodmodebool = true;
	bool CarGMode = false;


	//voids
	void VehGodmode()
	{
		if (CarGMode)
		{
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			ENTITY::SET_ENTITY_INVINCIBLE(vehicle, cargodmodebool);
			ENTITY::SET_ENTITY_PROOFS(vehicle, cargodmodebool, cargodmodebool, cargodmodebool, cargodmodebool, cargodmodebool, cargodmodebool, cargodmodebool, cargodmodebool);
			VEHICLE::SET_VEHICLE_DAMAGE(vehicle, 0.f, 0.f, 0.f, 0.f, 200.f, false);
			VEHICLE::SET_VEHICLE_ENVEFF_SCALE(vehicle, 0.f);
			VEHICLE::SET_DISABLE_VEHICLE_PETROL_TANK_DAMAGE(vehicle, cargodmodebool);
			VEHICLE::SET_DISABLE_VEHICLE_PETROL_TANK_FIRES(vehicle, cargodmodebool);
			VEHICLE::SET_VEHICLE_BODY_HEALTH(vehicle, 1000.f);
			VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(vehicle, !cargodmodebool);
			VEHICLE::SET_VEHICLE_CAN_BREAK(vehicle, !cargodmodebool);
			VEHICLE::SET_VEHICLE_ENGINE_HEALTH(vehicle, 1000.f);
			VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(vehicle, !cargodmodebool);
			VEHICLE::SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE(vehicle, !cargodmodebool);
			VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(vehicle, 1000.f);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(vehicle, !cargodmodebool);
			VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(vehicle, !cargodmodebool);
			VEHICLE::SET_VEHICLE_FIXED(vehicle);
			VEHICLE::SET_VEHICLE_DAMAGE(vehicle, 0.f, 0.f, 0.f, 0.f, 200.f, true);
			VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(vehicle);
			VEHICLE::SET_VEHICLE_ENVEFF_SCALE(vehicle, 0.f);
			VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0.f);
			VEHICLE::SET_VEHICLE_BODY_HEALTH(vehicle, 1000.f);
			VEHICLE::SET_VEHICLE_ENGINE_HEALTH(vehicle, 1000.f);
			VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(vehicle, 1000.f);
			if (VEHICLE::_IS_VEHICLE_DAMAGED(vehicle))
			{
				for (int i = 0; i < 10; i++)
				{
					try {
						VEHICLE::SET_VEHICLE_TYRE_FIXED(vehicle, i);
					}
					catch (...) {
						return;
					}
				}
			}
		}
	}

	void Teleport_To_Blip() 
	{
		Vector3 BlipCoords = get_blip_marker();
		Entity MyPlayer = PLAYER::PLAYER_PED_ID();
		int None = 0;
		float AirHeight = 1000.0;
		bool groundFound = false;
		static float groundCheckHeight[] = { 100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0 };
		char* ErrorMGS = "~r~ERROR: ~s~No waypoint found!";

		// If no waypoint has been set
		if (BlipCoords.x == None && BlipCoords.y == None)
		{
			notifyMap(ErrorMGS);
			return;
		}

		// Check if you are in any vehicle , If you are define you player as a vehicle
		if (PED::IS_PED_IN_ANY_VEHICLE(MyPlayer, false))
		{
			MyPlayer = PED::GET_VEHICLE_PED_IS_USING(MyPlayer);
		}

		// Get ground height and stuff ;)
		for (int i = 0; i < sizeof(groundCheckHeight) / sizeof(float); i++)
		{
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(MyPlayer, BlipCoords.x, BlipCoords.y, groundCheckHeight[i], 0, 0, 1);
			WAIT(100);
			if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(BlipCoords.x, BlipCoords.y, groundCheckHeight[i], &BlipCoords.z, 0))
			{
				groundFound = true;
				BlipCoords.z += 2.5;
				break;
			}
		}

		// If no ground where found, Set player in air and give parachute
		if (!groundFound) 
		{
			BlipCoords.z = AirHeight;
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
		}
		teleport_to_coords(MyPlayer, BlipCoords);
	}

}

namespace WeaponMod
{
	//Bools 
	bool airstrikeWep = false;
	//Void's

	void AirstrikeGun()
	{
		Vector3 ShootCoord;
		Player MyPlayer = PLAYER::PLAYER_PED_ID();
		if (airstrikeWep)
		{
			if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(MyPlayer, &ShootCoord))
			{
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(ShootCoord.x, ShootCoord.y, ShootCoord.z + 5, ShootCoord.x, ShootCoord.y, ShootCoord.z, 100, 1, GAMEPLAY::GET_HASH_KEY("WEAPON_AIRSTRIKE_ROCKET"), MyPlayer, 1, 1, 100);
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(ShootCoord.x, ShootCoord.y + 5, ShootCoord.z + 5, ShootCoord.x, ShootCoord.y, ShootCoord.z, 100, 1, GAMEPLAY::GET_HASH_KEY("WEAPON_AIRSTRIKE_ROCKET"), MyPlayer, 1, 1, 130);
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(ShootCoord.x + 3, ShootCoord.y, ShootCoord.z + 5, ShootCoord.x, ShootCoord.y, ShootCoord.z, 100, 1, GAMEPLAY::GET_HASH_KEY("WEAPON_AIRSTRIKE_ROCKET"), MyPlayer, 1, 1, 80);
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(ShootCoord.x - 5, ShootCoord.y, ShootCoord.z + 5, ShootCoord.x, ShootCoord.y, ShootCoord.z, 100, 1, GAMEPLAY::GET_HASH_KEY("WEAPON_AIRSTRIKE_ROCKET"), MyPlayer, 1, 1, 110);
				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(ShootCoord.x, ShootCoord.y - 2, ShootCoord.z + 5, ShootCoord.x, ShootCoord.y, ShootCoord.z, 100, 1, GAMEPLAY::GET_HASH_KEY("WEAPON_AIRSTRIKE_ROCKET"), MyPlayer, 1, 1, 150);
			}
		}
		else
		{
			NULL;
		}
	}
}

namespace OnlineStuff
{
	void StartTPtoMe(Player Onlineplayer, Vector3 target)
	{
		for (int iz = 0; iz < 2; iz++)
		{
			Ped destPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(Onlineplayer);
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

	void DoTPToMe(Player targetPlayer)
	{
		Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
		Sleep(1000);
		StartTPtoMe(targetPlayer, MyCoords);
	}

	void TPTheirVeh(Player OnlinePed)
	{
		Entity PlayerVeh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_ONLINE_PLAYER_ID(OnlinePed));
		Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);

		Entity ScriptedVeh = NETWORK::N_R_C_O_E((PlayerVeh, true));
		if (NETWORK::N_R_C_O_E((ScriptedVeh, true)))
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY((PLAYER::GET_PLAYER_PED(OnlinePed), true));
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY((PLAYER::GET_PLAYER_PED(OnlinePed), true)))
			{
				ENTITY::SET_ENTITY_COORDS_VECTOR3(ScriptedVeh, MyCoords, true, true, true, false);
			}
		}
	}

	void InstantCrashPlayer(Player ped)
	{
		Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(ped, FALSE);
		static Hash modelHashes[] =
		{
			0x9CF21E0F, 0x34315488,
			0x6A27FEB1, 0xCB2ACC8,
			0xC6899CDE, 0xD14B5BA3,
			0xD9F4474C, 0x32A9996C,
			0x69D4F974, 0xCAFC1EC3,
			0x79B41171, 0x1075651,
			0xC07792D4, 0x781E451D,
			0x762657C6, 0xC2E75A21,
			0xC3C00861, 0x81FB3FF0,
			0x45EF7804, 0xE65EC0E4,
			0xE764D794, 0xFBF7D21F,
			0xE1AEB708, 0xA5E3D471,
			0xD971BBAE, 0xCF7A9A9D,
			0xC2CC99D8, 0x8FB233A4,
			0x24E08E1F, 0x337B2B54,
			0xB9402F87, 0x4F2526DA
		};


		for each (Hash modelHash in modelHashes)
		{
			Object obj = OBJECT::CREATE_OBJECT(modelHash, playerPosition.x, playerPosition.y, playerPosition.z, 1, 1, 1);
		}
	}

	void AirStrikePed(Player OnlinePlayer)
	{
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(OnlinePlayer, 0);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords.x, coords.y, coords.z + 5, coords.x, coords.y, coords.z, 100, 1, GAMEPLAY::GET_HASH_KEY("WEAPON_AIRSTRIKE_ROCKET"), PLAYER::PLAYER_PED_ID(), 1, 1, 100);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords.x, coords.y + 5, coords.z + 5, coords.x, coords.y, coords.z, 100, 1, GAMEPLAY::GET_HASH_KEY("WEAPON_AIRSTRIKE_ROCKET"), PLAYER::PLAYER_PED_ID(), 1, 1, 130);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords.x + 3, coords.y, coords.z + 5, coords.x, coords.y, coords.z, 100, 1, GAMEPLAY::GET_HASH_KEY("WEAPON_AIRSTRIKE_ROCKET"), PLAYER::PLAYER_PED_ID(), 1, 1, 80);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords.x - 5, coords.y, coords.z + 5, coords.x, coords.y, coords.z, 100, 1, GAMEPLAY::GET_HASH_KEY("WEAPON_AIRSTRIKE_ROCKET"), PLAYER::PLAYER_PED_ID(), 1, 1, 110);
		GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(coords.x, coords.y - 2, coords.z + 5, coords.x, coords.y, coords.z, 100, 1, GAMEPLAY::GET_HASH_KEY("WEAPON_AIRSTRIKE_ROCKET"), PLAYER::PLAYER_PED_ID(), 1, 1, 150);
	}

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	//Work  on later

	//void SetBit(int& varible, int bit)
	//{
	//	varible |= 1UL << bit;
	//}
	//bool CheckBit(int variable, int bit)
	//{
	//	return (variable >> bit) & 1U;
	//}
	//DWORD crash_cam_timer = 0;

	//int crash_cam_toggles = 0, crash_cam_entity = 0, crash_cam = 0;

	//BYTE crash_cam_client = 0;

	//void toggleCrashCam(bool toggle)
	//{

	//	if (!toggle)
	//	{
	//		CAM::SET_CAM_ACTIVE(crash_cam, false);
	//		CAM::DESTROY_CAM(crash_cam, false);
	//		CAM::RENDER_SCRIPT_CAMS(0, 0, 3000, 1, 0);
	//		STREAMING::CLEAR_FOCUS();
	//	}
	//	else
	//	{
	//		if (!CAM::DOES_CAM_EXIST(crash_cam)) crash_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
	//		CAM::SET_CAM_COORD(crash_cam, 0.0f, 0.0f, 10000.0f);
	//		STREAMING::_SET_FOCUS_AREA(0.0f, 0.0f, 10000.0f, 0.0f, 0.0f, 0.0f);
	//		CAM::SET_CAM_ACTIVE(crash_cam, true);
	//		CAM::RENDER_SCRIPT_CAMS(1, 0, 3000, 1, 0);
	//	}
	//}

	//void STVCrash()
	//{

	//	if (CheckBit(crash_cam_toggles, 2))
	//	{
	//		if (GetTickCount() > crash_cam_timer)
	//		{
	//			if (ENTITY::DOES_ENTITY_EXIST(crash_cam_entity))
	//			{
	//				SetBit(crash_cam_toggles, 15);
	//				int entity = crash_cam_entity;
	//				if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity))
	//				{
	//					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(entity, 0, 1);
	//					ENTITY::DETACH_ENTITY(entity, 0, 0);
	//					ENTITY::DELETE_ENTITY(&entity);
	//					drawAlert("Step 3/3 completed.");
	//				}
	//				else NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
	//			}
	//			else
	//			{
	//				if (!CheckBit(crash_cam_toggles, 15)) drawAlert("Step failed.");
	//				toggleCrashCam(false);
	//				crash_cam_toggles = 0;
	//				crash_cam_entity = 0;
	//			}
	//		}
	//		else
	//		{
	//			STREAMING::REQUEST_MODEL(0xC1CE1183);
	//			if (STREAMING::HAS_MODEL_LOADED(0xC1CE1183))
	//			{
	//				if (!CheckBit(crash_cam_toggles, 16)) drawAlert("Step 1/3 completed.");
	//				if (!crash_cam_entity)
	//				{
	//					int ped = PLAYER::GET_PLAYER_PED(crash_cam_client);
	//					Vector3 Position = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
	//					crash_cam_entity = OBJECT::CREATE_OBJECT(0xC1CE1183, Position.x, Position.y, Position.z, true, true, false);
	//					if (ENTITY::DOES_ENTITY_EXIST(crash_cam_entity))
	//					{
	//						SetBit(crash_cam_toggles, 16);
	//						ENTITY::ATTACH_ENTITY_TO_ENTITY(crash_cam_entity, ped, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 2, 1);
	//						drawAlert("Step 2/3 completed.");
	//					}
	//				}
	//			}
	//		}
	//	}

	//	std::vector<int> crash_cam_entities;
	//	if (CheckBit(crash_cam_toggles, 0))
	//	{
	//		if (GetTickCount() > crash_cam_timer)
	//		{
	//			for (int i = ((int)crash_cam_entities.size() - 1); i >= 0; i--)
	//			{
	//				if (ENTITY::DOES_ENTITY_EXIST(crash_cam_entities[i]))
	//				{
	//					SetBit(crash_cam_toggles, 15);
	//					int entity = crash_cam_entities[i];
	//					if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity))
	//					{
	//						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(0x2D7030F3);
	//						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(entity, 0, 1);
	//						ENTITY::DELETE_ENTITY(&entity);
	//						crash_cam_entities.erase(crash_cam_entities.begin() + i);
	//						drawAlert("Step 3/3 completed.");
	//					}
	//					else NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
	//				}
	//				else crash_cam_entities.erase(crash_cam_entities.begin() + i);
	//			}
	//			if ((int)crash_cam_entities.size() == 0)
	//			{
	//				if (!CheckBit(crash_cam_toggles, 15)) printf("Step failed."); drawAlert("Step failed.");
	//				toggleCrashCam(false);
	//				crash_cam_toggles = 0;
	//				crash_cam_entity = 0;
	//			}
	//		}
	//		else
	//		{
	//			STREAMING::REQUEST_MODEL(0x2D7030F3);
	//			if (STREAMING::HAS_MODEL_LOADED(0x2D7030F3))
	//			{
	//				if (!CheckBit(crash_cam_toggles, 16)) drawAlert("Step 1/3 completed.");
	//				int ped = PLAYER::GET_PLAYER_PED(crash_cam_client);
	//				if ((!crash_cam_entity || !ENTITY::DOES_ENTITY_EXIST(crash_cam_entity)) && (int)crash_cam_entities.size() < 10)
	//				{
	//					AI::CLEAR_PED_TASKS_IMMEDIATELY(ped);
	//					Vector3 Position = ENTITY::GET_ENTITY_COORDS(ped, 0);
	//					crash_cam_entity = PED::CREATE_PED(26, 0x2D7030F3, Position.x, Position.y, Position.z, 0.0f, 1, 0);
	//					int netid = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(crash_cam_entity);
	//					NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(netid, 1);
	//				}
	//				if (ENTITY::DOES_ENTITY_EXIST(crash_cam_entity))
	//				{
	//					if (ENTITY::GET_ENTITY_MODEL(crash_cam_entity) == 0x2D7030F3)
	//					{
	//						SetBit(crash_cam_toggles, 16);

	//						crash_cam_entities.push_back(crash_cam_entity);

	//						//STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(crash_cam_hash);
	//						ENTITY::ATTACH_ENTITY_TO_ENTITY(crash_cam_entity, ped, -1, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 2, 1);
	//						ENTITY::DETACH_ENTITY(crash_cam_entity, 1, 1);
	//						ENTITY::FREEZE_ENTITY_POSITION(crash_cam_entity, true);
	//						drawAlert("Step 2/3 completed.");

	//						crash_cam_entity = 0;
	//					}
	//					else crash_cam_entity = 0;
	//				}
	//			}
	//		}
	//	}
	//}
}

namespace SVTCrashes
{
	void SVTv2(int client);
	void SVTv2(int client);
	void SVTv2(int client);
	void SVTv2(int client);
	void SVTv2(int client);
	void SVTv2(int client);
	void SVTv2(int client);
	void SVTv2(int client);
	void SVTv2(int client);
}

namespace HASH
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

namespace AWSOME
{
	//Public int's using AWSOME::
	int RainAmount = 2500;
	int MoneyType = 0;
	//Public bool's using AWSOME::
	bool RainToggle = false;

	//Void's
	void BlipMoneyRain() //Waypoint Money Rain
	{
		if (RainToggle)
		{
			if (!UI::DOES_BLIP_EXIST)
			{
				notifyMap("~r~ERROR: ~s~No Waypoint Found!");
			}
			else if (UI::DOES_BLIP_EXIST)
			{
				Vector3 Waypoint = get_blip_marker();
				STREAMING::REQUEST_MODEL(HASH::MoneyModel(MoneyType));
				int RanRange1 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 15);
				int RanRange2 = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 15);

				STREAMING::REQUEST_MODEL(HASH::MoneyModel(MoneyType));
				while (!STREAMING::HAS_MODEL_LOADED(HASH::MoneyModel(MoneyType)))
					WAIT(0);
				if (STREAMING::HAS_MODEL_LOADED(HASH::MoneyModel(MoneyType)))
				{
					OBJECT::CREATE_AMBIENT_PICKUP(PICKUP_MONEY_CASE, Waypoint.x + RanRange1, Waypoint.y + RanRange2, Waypoint.z, 0, RainAmount, HASH::MoneyModel(MoneyType), false, true);
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(HASH::MoneyModel(MoneyType));
				}
			}
		}
	}

	void TeleNearCar()
	{
		Vector3 MyCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
		Vehicle CloseVeh = VEHICLE::GET_CLOSEST_VEHICLE(MyCoords.x, MyCoords.y, MyCoords.y, 200.0f, 0, 71);
		Ped MyPed = PLAYER::PLAYER_PED_ID();

		PED::SET_PED_INTO_VEHICLE(MyPed, CloseVeh, 1);
	}
}

namespace NETOPTION
{
#define PICKUP_MONEY_CASE 0x1E9A99F8
#define PROP_MONEY_BAG_03 0x9CA6F755

	Vehicle Spawned[9999];
	Hash SpawnedHash[9999];
	int SpawnIndex = 0;
	void CloneVehicle(Player CLIENT)
	{
		int model = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CLIENT), 1);
		STREAMING::REQUEST_MODEL(VEHICLE::GET_VEHICLE_LAYOUT_HASH(model));
		if (!STREAMING::HAS_MODEL_LOADED(VEHICLE::GET_VEHICLE_LAYOUT_HASH(model))) {
			WAIT(0);
		}
		else 
		{
			if (STREAMING::IS_MODEL_A_VEHICLE(VEHICLE::GET_VEHICLE_LAYOUT_HASH(model)))
			{
				Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(CLIENT), 1);
				Vehicle veh = VEHICLE::CREATE_VEHICLE(VEHICLE::GET_VEHICLE_LAYOUT_HASH(model), coords.x, coords.y, coords.z, 1.0f, 1, 1);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
				Spawned[SpawnIndex] = veh;
				SpawnedHash[SpawnIndex] = model;
				SpawnIndex++;
			}
		}
	}
}



















namespace Cursor 
{
	extern bool cursorOn;
	extern bool CheckIfActive;
	void cursor();
	POINT cursorPos();
	bool insideMenu();
	float getMenuTop();
	float getOptionHeight();
	int onOption();
	void getOnscreenOptions(int& start, int& end);
	void moveScroller();
	void CheckEnableKey();
}
//Create mouse support for my menu
#pragma region cursor
bool Cursor::cursorOn = false;
bool Cursor::CheckIfActive = true;

//The main function of the cursor
void Cursor::cursor() 
{
	if (cursorOn) {
		//Disable controls
		CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(0);
		CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(1);
		CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(2);
		//Show the cursor
		UI::_SET_CURSOR_SPRITE(5);
		UI::_SHOW_CURSOR_THIS_FRAME();
		if (Cursor::insideMenu()) {
			Cursor::moveScroller();
			//If you click on an option
			if (GetAsyncKeyState(VK_LBUTTON)) {
				Menu::Settings::selectPressed = true;
			}
			else {
				Menu::Settings::selectPressed = false;
			}
		}
		else {
			if (GetAsyncKeyState(VK_LBUTTON)) {
				Menu::Settings::cursorMenuX = Cursor::cursorPos().x;
				Menu::Settings::menuX = ((float)Cursor::cursorPos().x / 100) / 15;
			}
		}
	}
	else {
		CONTROLS::ENABLE_ALL_CONTROL_ACTIONS(0);
		CONTROLS::ENABLE_ALL_CONTROL_ACTIONS(1);
		CONTROLS::ENABLE_ALL_CONTROL_ACTIONS(2);
	}
}

//Get the position of the cursor
POINT Cursor::cursorPos() {
	POINT pt;
	if (GetCursorPos(&pt) && Cursor::cursorOn) {
		return pt;
	}
	else {
		POINT fail = { 0, 0 };
		return fail;
	}
}

//Checks if the cursor is inside the menu
bool Cursor::insideMenu() {
	if (Cursor::cursorOn) {
		float cx = (float)Cursor::cursorPos().x;
		float cy = (float)Cursor::cursorPos().y;
		//The cursor position gets calculated differently than the menu position
		//MenuPosition = (CursorPosition / 100) / 15
		//CursorPosition = (MenuPosition * 100) * 15
		float m1 = ((Menu::Settings::menuX * 100) * 15) - 155;
		float m2 = ((Menu::Settings::menuX * 100) * 15) + 180;
		//m1 = left menu border, m2 = right menu border
		if (cx > m1&& cx < m2 && cy > Cursor::getMenuTop()) {
			return true;
		}
		else {
			return false;
		}
	}
}

//The Y-coord of the menu top
float Cursor::getMenuTop() {
	return 146;
}

//The height of one option
float Cursor::getOptionHeight() {
	return 31.193;
}

//Returns the height of n options
int optionHeight(int op) {
	return Cursor::getMenuTop() + (Cursor::getOptionHeight() * op);
}

//Returns the number of the option that the cursor is on
int Cursor::onOption() {
	float cy = (float)Cursor::cursorPos().y;
	int count = Menu::Settings::optionCount;
	if (Cursor::insideMenu()) {
		for (int i = 0; i < 16; i++) {
			if (cy > optionHeight(i) && cy < optionHeight(i + 1)) {
				return i + 1;
			}
		}
	}
	else {
		return -1;
	}
}

//Gets the options that are currently onscreen
void Cursor::getOnscreenOptions(int& start, int& end) {
	int count = Menu::Settings::optionCount;
	int current = Menu::Settings::currentOption;
	if (count < 17) {
		start = 1;
		end = count;
	}
	else {
		if (current < 17) {
			start = 1;
			end = 16;
		}
		else {
			start = current - 15;
			end = current;
		}
	}
}

//Moves the scroller
void Cursor::moveScroller() 
{
	//Saves the options that are onscreen in an array
	int onscreen[16]/* = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }*/;
	int unused;
	Cursor::getOnscreenOptions(onscreen[0], unused);
	for (int i = 1; i < ARRAYSIZE(onscreen); i++) {
		onscreen[i] = onscreen[i - 1] + 1;
	}
	//Breaks if an option-check is applied? if (onscreen[15] < Menu::Settings::optionCount)
	//Sets the scroller to the specific option
	//Cursor::onOption() ranges from 1 to 16; selects the index of the onscreen options
	Menu::Settings::currentOption = onscreen[Cursor::onOption() - 1];
}

//Excludes
//Remote tp
//Moneydrop
//Remove money
//Better outfit changer
//Player info
//Random weather
//Minimenu-TP
#pragma endregion


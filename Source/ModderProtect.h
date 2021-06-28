#include "stdafx.h"

namespace Protect
{
	//bools
	bool antiKick = false;
	bool antiFreeze = false;
	bool antiExplosion = false;
	bool antiweatherTime = false;
	bool antiSound = false;
	bool antiStat = false;
	bool antiAttachment = false;
	bool antiControl = false;
	bool antiWeapon = false;
	bool antiStars = false;
	bool antiPtfx = false;
	bool antiTp = false;
	bool AntiCLear = false;
	bool CrashProtectMe = false;
	bool CloneProtection = false;
	bool cloneMeProtection = false;
	bool AntiDrops = false;
	bool General = false;
	bool eventShieldBool = false;
	bool VehFreezeProtection = false;
	bool EasyGeneral = false;
	//Int's
	int VehicleFreezeProtectionDelay = 0;

	//voids
	void AntiKick(bool t)
	{
		Hooking::defuseEvent(REMOTE_SCRIPT_LEAVE_EVENT, t);
		Hooking::defuseEvent(KICK_VOTES_EVENT, t);
		globalHandle(1377446).At(594).As<int>() = 594; //SP kick
		globalHandle(1377446).At(595).As<int>() = 595; //kick
		globalHandle(1382674).At(584).As<int>() = 584;
	}

	void AntiFreeze(bool t)
	{
		Hooking::defuseEvent(RAGDOLL_REQUEST_EVENT, t);
		Hooking::defuseEvent(INCIDENT_ENTITY_EVENT, t);
		Hooking::defuseEvent(CLEAR_AREA_EVENT, t);
		Hooking::defuseEvent(CLEAR_RECTANGLE_AREA_EVENT, t);
		Hooking::defuseEvent(NETWORK_CLEAR_PED_TASKS_EVENT, t);
		Hooking::defuseEvent(NETWORK_SOUND_CAR_HORN_EVENT, t);
		Hooking::defuseEvent(NETWORK_PLAY_SOUND_EVENT, t);
		Hooking::defuseEvent(NETWORK_STOP_SOUND_EVENT, t);
		Hooking::defuseEvent(NETWORK_PLAY_AIRDEFENSE_FIRE_EVENT, t);
	}

	void AntiExplosion(bool t)
	{
		Hooking::defuseEvent(FIRE_EVENT, t);
		Hooking::defuseEvent(EXPLOSION_EVENT, t);
		Hooking::defuseEvent(REQUEST_PHONE_EXPLOSION_EVENT, t);
		Hooking::defuseEvent(BLOW_UP_VEHICLE_EVENT, t);
	}

	void antiWeatherTime(bool t)
	{
		Hooking::defuseEvent(GAME_CLOCK_EVENT, t);
		Hooking::defuseEvent(GAME_WEATHER_EVENT, t);
	}

	void AntiSound(bool t)
	{
		Hooking::defuseEvent(NETWORK_SOUND_CAR_HORN_EVENT, t);
		Hooking::defuseEvent(NETWORK_PLAY_SOUND_EVENT, t);
		Hooking::defuseEvent(NETWORK_STOP_SOUND_EVENT, t);
		Hooking::defuseEvent(NETWORK_PLAY_AIRDEFENSE_FIRE_EVENT, t);
	}

	void AntiStat(bool t)
	{
		Hooking::defuseEvent(NETWORK_BANK_REQUEST_EVENT, t);
		Hooking::defuseEvent(NETWORK_INCREMENT_STAT_EVENT, t);
	}

	void RequestControlOfid(Entity netid)
	{
		int tick = 0;

		while (!NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netid) && tick <= 25)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netid);
			tick++;
		}

	}

	void AntiAttachment(bool t)
	{
		Hooking::defuseEvent(REQUEST_DETACHMENT_EVENT, t);
		char* objects[136] = { "prop_bskball_01", "PROP_MP_RAMP_03", "PROP_MP_RAMP_02", "PROP_MP_RAMP_01", "PROP_JETSKI_RAMP_01", "PROP_WATER_RAMP_03", "PROP_VEND_SNAK_01", "PROP_TRI_START_BANNER", "PROP_TRI_FINISH_BANNER", "PROP_TEMP_BLOCK_BLOCKER", "PROP_SLUICEGATEL", "PROP_SKIP_08A", "PROP_SAM_01", "PROP_RUB_CONT_01B", "PROP_ROADCONE01A", "PROP_MP_ARROW_BARRIER_01", "PROP_HOTEL_CLOCK_01", "PROP_LIFEBLURB_02", "PROP_COFFIN_02B", "PROP_MP_NUM_1", "PROP_MP_NUM_2", "PROP_MP_NUM_3", "PROP_MP_NUM_4", "PROP_MP_NUM_5", "PROP_MP_NUM_6", "PROP_MP_NUM_7", "PROP_MP_NUM_8", "PROP_MP_NUM_9", "prop_xmas_tree_int", "prop_bumper_car_01", "prop_beer_neon_01", "prop_space_rifle", "prop_dummy_01", "prop_rub_trolley01a", "prop_wheelchair_01_s", "PROP_CS_KATANA_01", "PROP_CS_DILDO_01", "prop_armchair_01", "prop_bin_04a", "prop_chair_01a", "prop_dog_cage_01", "prop_dummy_plane", "prop_golf_bag_01", "prop_arcade_01", "hei_prop_heist_emp", "prop_alien_egg_01", "prop_air_towbar_01", "hei_prop_heist_tug", "prop_air_luggtrolley", "PROP_CUP_SAUCER_01", "prop_wheelchair_01", "prop_ld_toilet_01", "prop_acc_guitar_01", "prop_bank_vaultdoor", "p_v_43_safe_s", "p_spinning_anus_s", "prop_can_canoe", "prop_air_woodsteps", "Prop_weed_01", "prop_a_trailer_door_01", "prop_apple_box_01", "prop_air_fueltrail1", "prop_barrel_02a", "prop_barrel_float_1", "prop_barrier_wat_03b", "prop_air_fueltrail2", "prop_air_propeller01", "prop_windmill_01", "prop_Ld_ferris_wheel", "p_tram_crash_s", "p_oil_slick_01", "p_ld_stinger_s", "p_ld_soc_ball_01", "prop_juicestand", "p_oil_pjack_01_s", "prop_barbell_01", "prop_barbell_100kg", "p_parachute1_s", "p_cablecar_s", "prop_beach_fire", "prop_lev_des_barge_02", "prop_lev_des_barge_01", "prop_a_base_bars_01", "prop_beach_bars_01", "prop_air_bigradar", "prop_weed_pallet", "prop_artifact_01", "prop_attache_case_01", "prop_large_gold", "prop_roller_car_01", "prop_water_corpse_01", "prop_water_corpse_02", "prop_dummy_01", "prop_atm_01", "hei_prop_carrier_docklight_01", "hei_prop_carrier_liferafts", "hei_prop_carrier_ord_03", "hei_prop_carrier_defense_02", "hei_prop_carrier_defense_01", "hei_prop_carrier_radar_1", "hei_prop_carrier_radar_2", "hei_prop_hei_bust_01", "hei_prop_wall_alarm_on", "hei_prop_wall_light_10a_cr", "prop_afsign_amun", "prop_afsign_vbike", "prop_aircon_l_01", "prop_aircon_l_02", "prop_aircon_l_03", "prop_aircon_l_04", "prop_airhockey_01", "prop_air_bagloader", "prop_air_blastfence_01", "prop_air_blastfence_02", "prop_air_cargo_01a", "prop_air_chock_01", "prop_air_chock_03", "prop_air_gasbogey_01", "prop_air_generator_03", "prop_air_stair_02", "prop_amb_40oz_02", "prop_amb_40oz_03", "prop_amb_beer_bottle", "prop_amb_donut", "prop_amb_handbag_01", "prop_amp_01", "prop_anim_cash_pile_02", "prop_asteroid_01", "prop_arm_wrestle_01", "prop_ballistic_shield", "prop_bank_shutter", "prop_barier_conc_02b", "prop_barier_conc_05a", "prop_barrel_01a", "prop_bar_stool_01", "prop_basejump_target_01" };
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
		GAMEPLAY::CLEAR_AREA_OF_PEDS(coords.x, coords.y, coords.z, 2, 0);
		GAMEPLAY::CLEAR_AREA_OF_OBJECTS(coords.x, coords.y, coords.z, 2, 0);
		GAMEPLAY::CLEAR_AREA_OF_VEHICLES(coords.x, coords.y, coords.z, 2, 0, 0, 0, 0, 0);
		for (int i = 0; i < 136; i++) {
			Object obj = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(coords.x, coords.y, coords.z, 4.0, GAMEPLAY::GET_HASH_KEY(objects[i]), 0, 0, 1);

			if (ENTITY::DOES_ENTITY_EXIST(obj) && ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(obj, PLAYER::PLAYER_PED_ID())) {
				RequestControlOfEnt(obj);
				int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(obj);
				NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
				RequestControlOfid(netID);
				ENTITY::DETACH_ENTITY(obj, 1, 1);
				if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(obj)) {
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(obj, 1, 1);
					ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&obj);
					ENTITY::DELETE_ENTITY(&obj);
				}
			}
		}
	}

	void AntiControl(bool t)
	{
		Hooking::defuseEvent(REQUEST_CONTROL_EVENT, t);
		Hooking::defuseEvent(GIVE_CONTROL_EVENT, t);
		Hooking::defuseEvent(VEHICLE_COMPONENT_CONTROL_EVENT, t);
	}

	void AntiWeapon(bool t)
	{
		Hooking::defuseEvent(GIVE_WEAPON_EVENT, t);
		Hooking::defuseEvent(REMOVE_WEAPON_EVENT, t);
		Hooking::defuseEvent(REMOVE_ALL_WEAPONS_EVENT, t);
	}

	void AntiStars(bool t)
	{
		Hooking::defuseEvent(ALTER_WANTED_LEVEL_EVENT, t);
	}

	void AntiPtfx(bool t)
	{
		Hooking::defuseEvent(NETWORK_PTFX_EVENT, t);
	}

	void antiTP(bool t)
	{
		Hooking::defuseEvent(NETWORK_REQUEST_SYNCED_SCENE_EVENT, t);
		Hooking::defuseEvent(NETWORK_UPDATE_SYNCED_SCENE_EVENT, t);
		Hooking::defuseEvent(NETWORK_START_SYNCED_SCENE_EVENT, t);
		globalHandle(1377446).At(486).As<int>() = 486; //TP
		globalHandle(1382674).At(499).As<int>() = 499; //TP
	}

	void antiClear(bool t)
	{
		Hooking::defuseEvent(CLEAR_AREA_EVENT, t);
	}

	void CrashProtection(bool t)
	{
		Hash crashModelHashes[] = { 0xceea3f4b, 0x2592b5cf, 0x9cf21e0f, 0xc1ce1183, 0x49863e9c, 0xcd93a7db, 0x82cac433, 0x74f24de,  0x1c725a1,  0x81fb3ff0,
		0x79b41171, 0x781e451d, 0xa5e3d471, 0x6a27feb1, 0x861d914d, 0x8c049d17, 0xffba70aa, 0xe65ec0e4, 0xc3c00861, 0x5f5dd65c,
		0xc07792d4, 0x53cfe80a, 0xd9f4474c, 0xcb2acc8,  0xc6899cde, 0xd14b5ba3, 0x32a9996c, 0x69d4f974, 0xc2e75a21, 0x1075651,
		0xe1aeb708, 0xcbbb6c39, 0x6fa03a5e, 0xcf7a9a9d, 0x34315488, 0x45ef7804, 0xac3de147, 0xcafc1ec3, 0xd971bbae, 0xe764d794,
		0xf51f7309, 0x1e78c9d,  0xa49658fc, 0x4f2526da, 0x576ab4f6, 0xd20b1778, 0x54bc1cd8, 0xce109c5c, 0xe049c0ce, 0x78de93d1,
		0xe5b89d31, 0x5850e7b3, 0x6aed0e4b, 0xc50a4285, 0xb648a502, 0x5e497511, 0x47c14801, 0xfd8bb397, 0xef541728, 0xc2cc99d8,
		0x8fb233a4, 0x24e08e1f, 0x337b2b54, 0x7367d224, 0x919d9255, 0x4484243f, 0x3c91d42d, 0x3353525a, 0xc175f658, 0x762657c6,
		0x94ac15b3, 0x28014a56, 0xe0a8bfc9, 0x3a559c31, 0x5fc8a70,  0x3b545487, 0xb9402f87
		};

		Player player = PLAYER::PLAYER_ID();
		Vector3 coords = coordsOf(player);
		Ped clone;
		PED::GET_CLOSEST_PED(coords.x, coords.y, coords.z, 4.0, 0, 1, &clone, 0, 0, -1);
		if (ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(clone, PLAYER::PLAYER_PED_ID())) {
			RequestControlOfEnt(clone);
			int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(clone);
			RequestControlOfid(netID);
			NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
			ENTITY::DETACH_ENTITY(clone, 1, 1);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(clone, 1, 1);
			ENTITY::DELETE_ENTITY(&clone);
			ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&clone);
			ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z - 1000, 0, 0, 0, 1);
		}

		for each (Hash h in crashModelHashes) {
			if (OBJECT::IS_OBJECT_NEAR_POINT(h, coords.x, coords.y, coords.z, 2.0f)) {
				Object a = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(coords.x, coords.y, coords.z, 2.0f, h, false, true, true);
				RequestControlOfEnt(a);
				int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(a);
				RequestControlOfid(netID);
				NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
				ENTITY::DETACH_ENTITY(a, 1, 1);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(clone, 1, 1);
				ENTITY::DELETE_ENTITY(&a);
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&a);
				ENTITY::SET_ENTITY_COORDS(player, coords.x, coords.y, coords.z - 1000, 0, 0, 0, 1);
			}
		}
	}

	void antiClone(bool t)
	{
		if (!CUTSCENE::IS_CUTSCENE_ACTIVE() && !CUTSCENE::IS_CUTSCENE_PLAYING() && !STREAMING::IS_NETWORK_LOADING_SCENE() && !NETWORK::NETWORK_IS_IN_MP_CUTSCENE() && !INTERIOR::IS_INTERIOR_SCENE())
		{
			Ped Closest;
			Vector3 MyPos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
			if (PED::GET_CLOSEST_PED(MyPos.x, MyPos.y, MyPos.z, 5, true, true, &Closest, false, true, -1))
			{
				if (ENTITY::GET_ENTITY_MODEL(Closest) == ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()))
				{
					if (!PED::IS_PED_A_PLAYER(Closest))
					{
						if (ENTITY::DOES_ENTITY_EXIST(Closest))
						{
							if (NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Closest))
							{
								if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Closest))
								{
									ENTITY::DETACH_ENTITY(Closest, 1, 1);
									ENTITY::SET_ENTITY_COORDS(Closest, 6000.0, 6000.0, 6000.0, true, false, false, true);
									ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Closest, 1, 1);
									PED::DELETE_PED(&Closest);
									ENTITY::DELETE_ENTITY(&Closest);
								}
							}
						}
					}
				}
			}
		}
	}

	void antiVehFreeze(bool t)
	{
		if (VehicleFreezeProtectionDelay < GAMEPLAY::GET_GAME_TIMER())
		{
			const int numElements = 10;
			const int arrSize = numElements + 1;  //Start at index 2, and the odd elements are padding
			int vehs[arrSize];
			vehs[0] = numElements;
			int count = PED::GET_PED_NEARBY_VEHICLES(PLAYER::PLAYER_PED_ID(), vehs);
			for (int i = 0; i < count; ++i)
			{
				int offsettedID = i + 1;
				if (ENTITY::DOES_ENTITY_EXIST(vehs[offsettedID]))
				{
					bool Contin = true;
					if (t)
					{
						if (!(ENTITY::IS_ENTITY_ATTACHED(vehs[offsettedID]) && ENTITY::GET_ENTITY_ATTACHED_TO(vehs[offsettedID]) == PLAYER::PLAYER_PED_ID()))
							Contin = false;
					}
					if (Contin)
					{
						if (NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(vehs[offsettedID]) && NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(vehs[offsettedID]))
						{
							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehs[offsettedID], 0, 1);
							ENTITY::DELETE_ENTITY(&vehs[offsettedID]);

						}
					}
				}
			}
			VehicleFreezeProtectionDelay = GAMEPLAY::GET_GAME_TIMER() + 500;
		}
	}

	void AntiPickup(bool t)
	{
		Hooking::defuseEvent(REQUEST_PICKUP_EVENT, t);
		Hooking::defuseEvent(REQUEST_MAP_PICKUP_EVENT, t);
	}

	void GeneralProtect(bool t)
	{
		globalHandle(1382674).At(610).As<int>() = 610; //SP kick
		globalHandle(1382674).At(609).As<int>() = 609; //kick
		globalHandle(1382674).At(536).As<int>() = 536; //ceo kick
		globalHandle(1382674).At(558).As<int>() = 558; //ceo ban
		globalHandle(1377446).At(486).As<int>() = 486; //TP
		globalHandle(1382674).At(499).As<int>() = 499; //TP
		globalHandle(1382674).At(532).As<int>() = 532; //ceo kick 2
		globalHandle(1382674).At(295).As<int>() = 295; //mission
		globalHandle(1382674).At(350).As<int>() = 350; //transaction
		globalHandle(1382674).At(0).As<int>() = 0; //notification
		globalHandle(1382674).At(61).As<int>() = 61; //gentle kick
		globalHandle(1382674).At(584).As<int>() = 584; //kick 2
		globalHandle(1382674).At(2).As<int>() = 2; //rotate cam
		globalHandle(1382674).At(490).As<int>() = 490; //clearwanted
		globalHandle(1382674).At(545).As<int>() = 545; //bribe cops
		globalHandle(1382674).At(433).As<int>() = 433; //insurance
		globalHandle(1382674).At(492).As<int>() = 492; //offradar
		globalHandle(1382674).At(609).As<int>() = 609; //Non-Host kick
		globalHandle(1382674).At(608).As<int>() = 608; //SP kick
		globalHandle(1382674).At(16).As<int>() = 16; //Superkick XXI
		globalHandle(1382674).At(21).As<int>() = 21; //Superkick XX
		globalHandle(1382674).At(677).As<int>() = 677; //Superkick XIX
		globalHandle(1382674).At(601).As<int>() = 601; //Superkick XVIII
		globalHandle(1382674).At(23).As<int>() = 23; //Superkick XVII
		globalHandle(1382674).At(24).As<int>() = 24; //Superkick XVI
		globalHandle(1382674).At(582).As<int>() = 582; //Superkick XV
		globalHandle(1382674).At(599).As<int>() = 599; //Superkick XIV
		globalHandle(1382674).At(577).As<int>() = 577; //Superkick XIII
		globalHandle(1382674).At(576).As<int>() = 576; //Superkick XII
		globalHandle(1382674).At(532).As<int>() = 532; //Superkick XI
		globalHandle(1382674).At(688).As<int>() = 688; //Superkick X
		globalHandle(1382674).At(455).As<int>() = 455; //Superkick IX
		globalHandle(1382674).At(449).As<int>() = 449; //Superkick VIII
		globalHandle(1382674).At(336).As<int>() = 336; //Superkick VII
		globalHandle(1382674).At(294).As<int>() = 294; //Superkick VI
		globalHandle(1382674).At(694).As<int>() = 694; //Superkick V
		globalHandle(1382674).At(602).As<int>() = 602; //Superkick IV
		globalHandle(1382674).At(584).As<int>() = 584; //Superkick III
		globalHandle(1382674).At(610).As<int>() = 610; //Superkick II
		globalHandle(1382674).At(693).As<int>() = 693; //Superkick I
	}

	void GeneralHidden(bool t)
	{
		//Now defuse all notmal event's - From bad menus XD
		Hooking::defuseEvent(SCRIPT_ARRAY_DATA_VERIFY_EVENT, t);
		Hooking::defuseEvent(REQUEST_CONTROL_EVENT, t);
		Hooking::defuseEvent(GIVE_CONTROL_EVENT, t);
		Hooking::defuseEvent(WEAPON_DAMAGE_EVENT, t);
		Hooking::defuseEvent(REQUEST_PICKUP_EVENT, t);
		Hooking::defuseEvent(REQUEST_MAP_PICKUP_EVENT, t);
		Hooking::defuseEvent(GAME_CLOCK_EVENT, t);
		Hooking::defuseEvent(GAME_WEATHER_EVENT, t);
		Hooking::defuseEvent(RESPAWN_PLAYER_PED_EVENT, t);
		Hooking::defuseEvent(GIVE_WEAPON_EVENT, t);
		Hooking::defuseEvent(REMOVE_WEAPON_EVENT, t);
		Hooking::defuseEvent(REMOVE_ALL_WEAPONS_EVENT, t);
		Hooking::defuseEvent(REMOVE_ALL_WEAPONS_EVENT, t);
		Hooking::defuseEvent(REMOVE_ALL_WEAPONS_EVENT, t);
		Hooking::defuseEvent(VEHICLE_COMPONENT_CONTROL_EVENT, t);
		Hooking::defuseEvent(FIRE_EVENT, t);
		Hooking::defuseEvent(EXPLOSION_EVENT, t);
		Hooking::defuseEvent(START_PROJECTILE_EVENT, t);
		Hooking::defuseEvent(ALTER_WANTED_LEVEL_EVENT, t);
		Hooking::defuseEvent(CHANGE_RADIO_STATION_EVENT, t);
		Hooking::defuseEvent(RAGDOLL_REQUEST_EVENT, t);
		Hooking::defuseEvent(PLAYER_TAUNT_EVENT, t);
		Hooking::defuseEvent(PLAYER_CARD_STAT_EVENT, t);
		Hooking::defuseEvent(DOOR_BREAK_EVENT, t);
		Hooking::defuseEvent(SCRIPTED_GAME_EVENT, t);
		Hooking::defuseEvent(REMOTE_SCRIPT_INFO_EVENT, t);
		Hooking::defuseEvent(REMOTE_SCRIPT_LEAVE_EVENT, t);
		Hooking::defuseEvent(MARK_AS_NO_LONGER_NEEDED_EVENT, t);
		Hooking::defuseEvent(CONVERT_TO_SCRIPT_ENTITY_EVENT, t);
		Hooking::defuseEvent(SCRIPT_WORLD_STATE_EVENT, t);
		Hooking::defuseEvent(INCIDENT_ENTITY_EVENT, t);
		Hooking::defuseEvent(CLEAR_AREA_EVENT, t);
		Hooking::defuseEvent(CLEAR_RECTANGLE_AREA_EVENT, t);
		Hooking::defuseEvent(NETWORK_REQUEST_SYNCED_SCENE_EVENT, t);
		Hooking::defuseEvent(NETWORK_START_SYNCED_SCENE_EVENT, t);
		Hooking::defuseEvent(NETWORK_UPDATE_SYNCED_SCENE_EVENT, t);
		Hooking::defuseEvent(NETWORK_STOP_SYNCED_SCENE_EVENT, t);
		Hooking::defuseEvent(GIVE_PED_SCRIPTED_TASK_EVENT, t);
		Hooking::defuseEvent(GIVE_PED_SEQUENCE_TASK_EVENT, t);
		Hooking::defuseEvent(NETWORK_CLEAR_PED_TASKS_EVENT, t);
		Hooking::defuseEvent(NETWORK_START_PED_ARREST_EVENT, t);
		Hooking::defuseEvent(NETWORK_START_PED_UNCUFF_EVENT, t);
		Hooking::defuseEvent(NETWORK_SOUND_CAR_HORN_EVENT, t);
		Hooking::defuseEvent(NETWORK_ENTITY_AREA_STATUS_EVENT, t);
		Hooking::defuseEvent(NETWORK_GARAGE_OCCUPIED_STATUS_EVENT, t);
		Hooking::defuseEvent(PED_CONVERSATION_LINE_EVENT, t);
		Hooking::defuseEvent(SCRIPT_ENTITY_STATE_CHANGE_EVENT, t);
		Hooking::defuseEvent(NETWORK_PLAY_SOUND_EVENT, t);
		Hooking::defuseEvent(NETWORK_STOP_SOUND_EVENT, t);
		Hooking::defuseEvent(NETWORK_PLAY_AIRDEFENSE_FIRE_EVENT, t);
		Hooking::defuseEvent(NETWORK_BANK_REQUEST_EVENT, t);
		Hooking::defuseEvent(REQUEST_DOOR_EVENT, t);
		Hooking::defuseEvent(NETWORK_TRAIN_REQUEST_EVENT, t);
		Hooking::defuseEvent(NETWORK_TRAIN_REPORT_EVENT, t);
		Hooking::defuseEvent(NETWORK_INCREMENT_STAT_EVENT, t);
		Hooking::defuseEvent(MODIFY_VEHICLE_LOCK_WORD_STATE_DATA, t);
		Hooking::defuseEvent(REQUEST_PHONE_EXPLOSION_EVENT, t);
		Hooking::defuseEvent(REQUEST_DETACHMENT_EVENT, t);
		Hooking::defuseEvent(KICK_VOTES_EVENT, t);
		Hooking::defuseEvent(GIVE_PICKUP_REWARDS_EVENT, t);
		Hooking::defuseEvent(NETWORK_CRC_HASH_CHECK_EVENT, t);
		Hooking::defuseEvent(BLOW_UP_VEHICLE_EVENT, t);
		Hooking::defuseEvent(NETWORK_SPECIAL_FIRE_EQUIPPED_WEAPON, t);
		Hooking::defuseEvent(NETWORK_RESPONDED_TO_THREAT_EVENT, t);
		Hooking::defuseEvent(NETWORK_SHOUT_TARGET_POSITION, t);
		Hooking::defuseEvent(PICKUP_DESTROYED_EVENT, t);
		Hooking::defuseEvent(UPDATE_PLAYER_SCARS_EVENT, t);
		Hooking::defuseEvent(NETWORK_CHECK_EXE_SIZE_EVENT, t);
		Hooking::defuseEvent(NETWORK_PTFX_EVENT, t);
		Hooking::defuseEvent(NETWORK_PED_SEEN_DEAD_PED_EVENT, t);
		Hooking::defuseEvent(REMOVE_STICKY_BOMB_EVENT, t);
		Hooking::defuseEvent(NETWORK_CHECK_CODE_CRCS_EVENT, t);
		Hooking::defuseEvent(INFORM_SILENCED_GUNSHOT_EVENT, t);
		Hooking::defuseEvent(PED_PLAY_PAIN_EVENT, t);
		Hooking::defuseEvent(CACHE_PLAYER_HEAD_BLEND_DATA_EVENT, t);
		Hooking::defuseEvent(REMOVE_PED_FROM_PEDGROUP_EVENT, t);
		Hooking::defuseEvent(REPORT_MYSELF_EVENT, t);
		Hooking::defuseEvent(REPORT_CASH_SPAWN_EVENT, t);
		Hooking::defuseEvent(ACTIVATE_VEHICLE_SPECIAL_ABILITY_EVENT, t);
		Hooking::defuseEvent(NETWORK_CHECK_CATALOG_CRC, t);
	}

	static void Trigger_Script_Event(int eventGroup, uint64_t* args, int argCount, int bit)
	{
		static auto func = reinterpret_cast<void(*)(int, uint64_t*, int, int)>(Memory::pattern("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 81 EC ? ? ? ? 45 8B F0 41 8B F9").count(1).get(0).get<void>(0));
		func(eventGroup, args, argCount, bit);
	}

	void eventShield()
	{
		uint64_t var0[10];
		bool data = Hooking::get_script_event_data(1, 0, var0, 10);
		if (data) {
			if (var0[0] == 360381720) {
				char* playername = PLAYER::GET_PLAYER_NAME(var0[1]);
				notifyMap("~r~%s tried to CEO ban you.", playername);
				if (playername != PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())) {
					globalHandle(1382674).At(558).As<int>() = 558;
					unsigned int Bit = (1 << var0[1]);
					Trigger_Script_Event(1, var0, 10, Bit);
				}
			}
			if (var0[0] == -1190833098) {
				char* playername = PLAYER::GET_PLAYER_NAME(var0[1]);
				notifyMap("~r~%s tried to CEO kick you.", playername);
				if (playername != PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())) {
					globalHandle(1382674).At(536).As<int>() = 536;
					globalHandle(1382674).At(532).As<int>() = 532;
					unsigned int Bit = (1 << var0[1]);
					Trigger_Script_Event(1, var0, 10, Bit);
				}
			}
			if (var0[0] == 769347061) {
				char* playername = PLAYER::GET_PLAYER_NAME(var0[1]);
				notifyMap("~r~%s tried to kick you.", playername);
				if (playername != PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())) {
					globalHandle(1382674).At(609).As<int>() = 609;
					unsigned int Bit = (1 << var0[1]);
					Trigger_Script_Event(1, var0, 10, Bit);
				}
			}
			if (var0[0] == 999090520) {
				char* playername = PLAYER::GET_PLAYER_NAME(var0[1]);
				notifyMap("~r~%s tried to kick you to singleplayer.", playername);
				if (playername != PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())) {
					globalHandle(1382674).At(610).As<int>() = 610;
					unsigned int Bit = (1 << var0[1]);
					Trigger_Script_Event(1, var0, 10, Bit);
				}
			}
			if (var0[0] == -1571039706) {
				char* playername = PLAYER::GET_PLAYER_NAME(var0[1]);
				notifyMap("~r~%s tried to send you to a mission.", playername);
				if (playername != PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())) {
					globalHandle(1382674).At(295).As<int>() = 295;
					unsigned int Bit = (1 << var0[1]);
					Trigger_Script_Event(1, var0, 10, Bit);
				}
			}
			if (var0[0] == 1000837481) {
				char* playername = PLAYER::GET_PLAYER_NAME(var0[1]);
				notifyMap("~r~%s tried to teleport you.", playername);
				if (playername != PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())) {
					globalHandle(1377446).At(486).As<int>() = 486;
					globalHandle(1382674).At(499).As<int>() = 499;
					unsigned int Bit = (1 << var0[1]);
					Trigger_Script_Event(1, var0, 10, Bit);
				}
			}
			if (var0[0] == 4119492672) {
				char* playername = PLAYER::GET_PLAYER_NAME(var0[1]);
				notifyMap("~r~%s tried to soundspam you.", playername);
				if (playername != PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())) {
					globalHandle(1377446).At(33).As<int>() = 33;
					unsigned int Bit = (1 << var0[1]);
					Trigger_Script_Event(1, var0, 10, Bit);
				}
			}
			if (var0[0] == -1920290846) {
				char* playername = PLAYER::GET_PLAYER_NAME(var0[1]);
				notifyMap("~r~%s tried to send an error to you.", playername);
				if (playername != PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())) {
					globalHandle(1382674).At(350).As<int>() = 350;
					unsigned int Bit = (1 << var0[1]);
					Trigger_Script_Event(1, var0, 10, Bit);
				}
			}
			if (var0[0] == -181444979) {
				char* playername = PLAYER::GET_PLAYER_NAME(var0[1]);
				notifyMap("~r~%s tried to show you a banner.", playername);
				if (playername != PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())) {
					//globalHandle(idk).At(idk).As<int>() = idk;
					unsigned int Bit = (1 << var0[1]);
					Trigger_Script_Event(1, var0, 10, Bit);
				}
			}
			if (var0[0] == -2105858993) {
				char* playername = PLAYER::GET_PLAYER_NAME(var0[1]);
				notifyMap("~r~%s tried to kick you from the club.", playername);
				if (playername != PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())) {
					//globalHandle(idk).At(idk).As<int>() = idk;
					unsigned int Bit = (1 << var0[1]);
					Trigger_Script_Event(1, var0, 10, Bit);
				}
			}
			if (var0[0] == 713068249) {
				char* playername = PLAYER::GET_PLAYER_NAME(var0[1]);
				notifyMap("~r~%s tried to show a notification.", playername);
				if (playername != PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())) {
					globalHandle(1382674).At(0).As<int>() = 0;
					unsigned int Bit = (1 << var0[1]);
					Trigger_Script_Event(1, var0, 10, Bit);
				}
			}
			if (var0[0] == 325218053) {
				char* playername = PLAYER::GET_PLAYER_NAME(var0[1]);
				notifyMap("~r~%s tried to kick you from the vehicle.", playername);
				if (playername != PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())) {
					globalHandle(1382674).At(61).As<int>() = 61;
					unsigned int Bit = (1 << var0[1]);
					Trigger_Script_Event(1, var0, 10, Bit);
				}
			}
			if (var0[0] == -1835749229) {
				char* playername = PLAYER::GET_PLAYER_NAME(var0[1]);
				notifyMap((char*)"~r~%s tried to superkick IV you.", playername);
				if (playername != PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())) {
					globalHandle(1382674).At(602).As<int>() = 602;
					unsigned int Bit = (1 << var0[1]);
					Trigger_Script_Event(1, var0, 10, Bit);
				}
			}
			if (var0[0] == -120668417) {
				char* playername = PLAYER::GET_PLAYER_NAME(var0[1]);
				notifyMap((char*)"~r~%s tried to superkick III you.", playername);
				if (playername != PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())) {
					globalHandle(1382674).At(584).As<int>() = 584;
					unsigned int Bit = (1 << var0[1]);
					Trigger_Script_Event(1, var0, 10, Bit);
				}
			}
			if (var0[0] == 994306218) {
				char* playername = PLAYER::GET_PLAYER_NAME(var0[1]);
				notifyMap((char*)"~r~%s tried to superkick II you.", playername);
				if (playername != PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())) {
					globalHandle(1382674).At(610).As<int>() = 610;
					unsigned int Bit = (1 << var0[1]);
					Trigger_Script_Event(1, var0, 10, Bit);
				}
			}
			if (var0[0] == 2055958901) {
				char* playername = PLAYER::GET_PLAYER_NAME(var0[1]);
				notifyMap((char*)"~r~%s tried to superkick I you.", playername);
				if (playername != PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())) {
					globalHandle(1382674).At(693).As<int>() = 693;
					unsigned int Bit = (1 << var0[1]);
					Trigger_Script_Event(1, var0, 10, Bit);
				}
			}
			if (var0[0] == 566035618) {
				char* playername = PLAYER::GET_PLAYER_NAME(var0[1]);
				notifyMap("~r~%s tried to rotate your cam.", playername);
				if (playername != PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID())) {
					globalHandle(1382674).At(2).As<int>() = 2;
					unsigned int Bit = (1 << var0[1]);
					Trigger_Script_Event(1, var0, 10, Bit);
				}
			}
		}
	}
}

#include "stdafx.h"
//Includes over here

//Creating namespaces

namespace extraBool
{

}

namespace STAFFOPTION
{
	void LogEvents()
	{

	}

	void BlackList()
	{

	}
}

namespace CUSTOMPROTECT
{
	//bools
	bool AnitDrop = false;
	//voids

	void AntiDrop()
	{
		if (AnitDrop)
		{
			
		}
	}
}

namespace MYSELF
{
	//bools

	//Voids
	void TeleportVeh()
	{
		Ped Myped = PLAYER::PLAYER_PED_ID();

		//AI::TASK_WARP_PED_INTO_VEHICLE();
	}
}
//int selectedPlayer = 0;
namespace ONLINE
{
	//void SetvehStore()
	//{
	//	//First get online ped

	//	Ped Onlineped = PLAYER::GET_PLAYER_PED(selectedPlayer);

	//	//Now get their curent vehicle

	//	Vehicle Theirvehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(Onlineped), true);

	//	//Getting control of their curent vehicle

	//	NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(Theirvehicle);

	//	int controlVehicle = NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(Theirvehicle);
	//	//Now check if we have control of it...
	//	if (controlVehicle)
	//	{
	//		//Do all vehicle options in here
	//		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(selectedPlayer), true))
	//		{
	//			Vehicle Netvehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(selectedPlayer), false);
	//			VEHICLE::SET_VEHICLE_MOD_KIT(Netvehicle, 0);
	//			for (int i = 0; i < 50; i++)
	//			{
	//				VEHICLE::SET_VEHICLE_MOD(Netvehicle, i, VEHICLE::GET_NUM_VEHICLE_MODS(Netvehicle, i) - 1, false);
	//			}
	//			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Netvehicle, "Flexy");
	//			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Netvehicle, 7, 84, 61);
	//			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Netvehicle, 7, 84, 61);
	//			uint OnlineVehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED(selectedPlayer));
	//			VEHICLE::SET_VEHICLE_FIXED(OnlineVehicle);
	//			VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(OnlineVehicle);
	//			VEHICLE::SET_VEHICLE_DIRT_LEVEL(OnlineVehicle, 0);
	//			VEHICLE::SET_VEHICLE_WINDOW_TINT(OnlineVehicle, 6);
	//			VEHICLE::SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER(OnlineVehicle, true);
	//		}
	//	}
	//	//SET_VEHICLE_WINDOW_TINT
	//		//SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER
	//}
}
#include "stdafx.h"



//Creating a namespace calles FUNCTION01 to call void in here do   ---   FUNCTION01::YourVoidHere();
namespace FUNCTION01
{

}
//Creating namespaces for custom gta v natives - Undetected as well
namespace SelectMe
{
	static Ped My_Id() { return invoke<Ped>(0xD80958FC74E988A6); } // 0xD80958FC74E988A6 0xFA92E226
	static Ped Get_My_Ped(Player player) { return invoke<Ped>(0x43A66C31C68491C0, player); } // 0x43A66C31C68491C0 0x6E31E993
}

namespace MyOptions
{

}
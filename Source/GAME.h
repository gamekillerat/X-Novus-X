#include "stdafx.h"


namespace BOOLS
{

}

namespace USERDATA
{
	string UserData;
}

/*
------------------------------------------------------------------|
------------------------------NOTES:------------------------------|
------------------------------------------------------------------|

LETTERS:

VK_KEY_A = A
VK_KEY_B = B
VK_KEY_C = C
VK_KEY_D = D
VK_KEY_E = E
VK_KEY_F = F
VK_KEY_G = G
VK_KEY_H = H
VK_KEY_I = I
VK_KEY_J = J
VK_KEY_K = K
VK_KEY_L = L
VK_KEY_M = M
VK_KEY_N = N
VK_KEY_O = O
VK_KEY_P = P
VK_KEY_Q = Q
VK_KEY_R = R
VK_KEY_S = S
VK_KEY_T = T
VK_KEY_U = U
VK_KEY_V = V
VK_KEY_W = W
VK_KEY_X = X
VK_KEY_Y = Y
VK_KEY_Z = Z

NUMMBERS:
VK_KEY_0 = 0
VK_KEY_1 = 1
VK_KEY_2 = 2
VK_KEY_3 = 3
VK_KEY_4 = 4
VK_KEY_5 = 5
VK_KEY_6 = 6
VK_KEY_7 = 7
VK_KEY_8 = 8
VK_KEY_9 = 9

*/

namespace KEYBOARD
{
	bool DisplayTaken = false;
	void GetKeyData(bool KeyboardActive)
	{
		//Creating a string to store key data in
		std::string Data = NULL;

		//USERDATA::UserData = Data;

				//Letter Detection

				if (IsKeyPressed(VK_KEY_A)) //A, a
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "A";
					}
					else
					{
						Data += "a";
					}
				}

				if (IsKeyPressed(VK_KEY_B)) //B, b
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "B";
					}
					else
					{
						Data += "b";
					}
				}

				if (IsKeyPressed(VK_KEY_C)) //C, c
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "C";
					}
					else
					{
						Data += "c";
					}
				}

				if (IsKeyPressed(VK_KEY_D)) //D, d
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "D";
					}
					else
					{
						Data += "d";
					}
				}

				if (IsKeyPressed(VK_KEY_E)) //E, e
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "E";
					}
					else
					{
						Data += "e";
					}
				}

				if (IsKeyPressed(VK_KEY_F)) //F, f
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "F";
					}
					else
					{
						Data += "f";
					}
				}

				if (IsKeyPressed(VK_KEY_G)) //G, g
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "G";
					}
					else
					{
						Data += "g";
					}
				}

				if (IsKeyPressed(VK_KEY_H)) //H, h
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "H";
					}
					else
					{
						Data += "h";
					}
				}

				if (IsKeyPressed(VK_KEY_I)) //I, i
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "I";
					}
					else
					{
						Data += "i";
					}
				}

				if (IsKeyPressed(VK_KEY_J)) //J, j
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "J";
					}
					else
					{
						Data += "j";
					}
				}

				if (IsKeyPressed(VK_KEY_K)) //K, k
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "K";
					}
					else
					{
						Data += "k";
					}
				}

				if (IsKeyPressed(VK_KEY_L)) //L, l
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "L";
					}
					else
					{
						Data += "l";
					}
				}

				if (IsKeyPressed(VK_KEY_M)) //M, m
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "M";
					}
					else
					{
						Data += "m";
					}
				}

				if (IsKeyPressed(VK_KEY_N)) //N, n
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "N";
					}
					else
					{
						Data += "n";
					}
				}

				if (IsKeyPressed(VK_KEY_O)) //O, o
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "O";
					}
					else
					{
						Data += "o";
					}
				}

				if (IsKeyPressed(VK_KEY_P)) //P, p
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "P";
					}
					else
					{
						Data += "p";
					}
				}

				if (IsKeyPressed(VK_KEY_Q)) //Q, q
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "Q";
					}
					else
					{
						Data += "q";
					}
				}

				if (IsKeyPressed(VK_KEY_R)) //R, r
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "R";
					}
					else
					{
						Data += "r";
					}
				}

				if (IsKeyPressed(VK_KEY_S)) //S, s
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "S";
					}
					else
					{
						Data += "s";
					}
				}

				if (IsKeyPressed(VK_KEY_T)) //T, t
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "T";
					}
					else
					{
						Data += "t";
					}
				}

				if (IsKeyPressed(VK_KEY_U)) //U, u
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "U";
					}
					else
					{
						Data += "u";
					}
				}

				if (IsKeyPressed(VK_KEY_V)) //V, v
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "V";
					}
					else
					{
						Data += "v";
					}
				}

				if (IsKeyPressed(VK_KEY_W)) //W, w
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "W";
					}
					else
					{
						Data += "w";
					}
				}

				if (IsKeyPressed(VK_KEY_X)) //X, x
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "X";
					}
					else
					{
						Data += "x";
					}
				}

				if (IsKeyPressed(VK_KEY_Y)) //Y, y
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "Y";
					}
					else
					{
						Data += "y";
					}
				}

				if (IsKeyPressed(VK_KEY_Z)) //Z, z
				{
					if (IsKeyPressed(VK_SHIFT))
					{
						Data += "Z";
					}
					else
					{
						Data += "z";
					}
				}

				//Nummber Detection

				if (IsKeyPressed(VK_KEY_0)) //0
				{
					Data += "0";
				}

				if (IsKeyPressed(VK_KEY_1)) //1
				{
					Data += "1";
				}

				if (IsKeyPressed(VK_KEY_2)) //2
				{
					Data += "2";
				}

				if (IsKeyPressed(VK_KEY_3)) //3
				{
					Data += "3";
				}

				if (IsKeyPressed(VK_KEY_4)) //4
				{
					Data += "4";
				}

				if (IsKeyPressed(VK_KEY_5)) //5
				{
					Data += "5";
				}

				if (IsKeyPressed(VK_KEY_6)) //6
				{
					Data += "6";
				}

				if (IsKeyPressed(VK_KEY_7)) //7
				{
					Data += "7";
				}

				if (IsKeyPressed(VK_KEY_8)) //8
				{
					Data += "8";
				}

				if (IsKeyPressed(VK_KEY_9)) //9
				{
					Data += "9";
				}

				notifyMap(Data);
			}

	bool show_login = false;
	void DrawKeyboard(bool t)
	{
		if (t)
		{
			show_login = true;
			float LoginX = 0.5f;
			float LoginY = 0.5f;
			float LoginWidth = 0.3f;
			float LoginHeight = 0.3f;
			float TextX = 0.5f;
			float TextY = 0.35f;
			RGBA LoginColor = { 0,0,0,240 };
			RGBA BG = { 0, 0, 0, 190 };
			if (show_login)
			{
				UI::_SHOW_CURSOR_THIS_FRAME();
				Menu::Drawing::Rect(LoginColor, { LoginX , LoginY }, { LoginWidth , LoginHeight });
				Menu::Drawing::Text("LOGIN", { 255, 255, 255, 255 }, { TextX, TextY }, { 0.40f, 0.40f }, true);
			}
		}
		else if (!t)
		{
			show_login = false;
		}
	}

	bool Activate = false;
	static void CreateKeyboard()
	{
		if (Activate)
		{
			if (IsKeyPressed(VK_NUMPAD5))
			{
				GetKeyData(true);
			}
			DrawKeyboard(true);
			char* UserGlobal = Menu::Tools::StringToChar(USERDATA::UserData);
			Menu::LoginTab1(UserGlobal);
		}
		else if (!Activate)
		{
			DrawKeyboard(false);
		}
	}
}

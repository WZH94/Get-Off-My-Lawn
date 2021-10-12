/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Font.cpp
\author Wong Zhihao(100%)
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file adds fonts to the font list and contains every font in the game.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Font.h"		// Function declarations
#include "AEEngine.h"	// AEGfxCreateFont

/******************************************************************************/
/*!
	Loads up fonts to be used in the game
*/
/******************************************************************************/
void Font_Manager::Load_Fonts()
{
	for (unsigned TYPE = 0; TYPE < F_LAST; ++TYPE)
	{
		switch (TYPE)
		{
		case F_TEST_MAIN_MENU: font_list_.at(TYPE) = AEGfxCreateFont("Buxton Sketch", 16, false, false);
			break;

		case F_GAME_UI_TEXT: font_list_.at(TYPE) = AEGfxCreateFont("Buxton Sketch", 20, true, false);
			break;

		case F_FULLSCREEN_GAME_UI_TEXT: font_list_.at(TYPE) = AEGfxCreateFont("Buxton Sketch", 25, true, false);
			break;

		case F_DEBUGGING_TEXT: font_list_.at(TYPE) = AEGfxCreateFont("Buxton Sketch", 15, true, false);
			break;
		
		case F_GAME_GENERAL_TEXT: font_list_.at(TYPE) = AEGfxCreateFont("Buxton Sketch", 30, true, false);
		}
	}
}

/******************************************************************************/
/*!
	Gets a specified font
*/
/******************************************************************************/
unsigned Font_Manager::Get_Font(Font_Types font_type)
{
	return font_list_.at(font_type);
}

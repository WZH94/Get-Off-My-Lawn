/******************************************************************************/
/*!
\game Get Off My Lawn!
\file   Font.h
\author Wong Zhihao(100%)
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the declarations of the Font_List and its function

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef FONT_H
#define FONT_H

#include <array>	// Array

enum Font_Types
{
	// Font use					Font Description
	F_TEST_MAIN_MENU = 0,		// Arial, 16, false, false
	F_GAME_UI_TEXT,				// Cooper Black, 15, true, false
	F_FULLSCREEN_GAME_UI_TEXT,	// Cooper Black, 25, true, false

	F_DEBUGGING_TEXT,			// Courier New, 15, true, false

	F_GAME_GENERAL_TEXT,        // Buxton Sketch, 30, true, false

	F_LAST						// Last enum
};

class Font_Manager
{
private:
	std::array <unsigned, F_LAST> font_list_;	// Font list

public:
	// Loads up fonts to be used in the game
	void Load_Fonts();

	// Gets a specified font
	unsigned Get_Font(Font_Types);
};

#endif
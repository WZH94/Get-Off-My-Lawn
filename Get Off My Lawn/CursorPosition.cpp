/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   CursorPosition.cpp
\author Wong Zhihao(100%)
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file calculates and stores the cursor position from Alpha Engine into
in-game coordinates every frame

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "CursorPosition.h"	// Class and function declarations
#include "main.h"			// Windows width and height

/******************************************************************************/
/*!
	Gets the cursor position
*/
/******************************************************************************/
AEVec2 Cursor_Position::Get_Cursor_Position() const
{
	return cursor_position_;
}

/******************************************************************************/
/*!
	Calculates and sets the cursor position
*/
/******************************************************************************/
void Cursor_Position::Set_Cursor_Position()
{
	int cursor_x = 0, cursor_y = 0;

	// Find system cursor position
	AEInputGetCursorPosition(&cursor_x, &cursor_y);

	// Change into in game coordinates
	cursor_x -= HALF_SCREEN_WIDTH;
	cursor_y = HALF_SCREEN_HEIGHT - cursor_y;

	// Limit them to the in game width and height
	if (cursor_x < -HALF_SCREEN_WIDTH)
		cursor_x = -HALF_SCREEN_WIDTH;

	else if (cursor_x > HALF_SCREEN_WIDTH)
		cursor_x = HALF_SCREEN_WIDTH;

	if (cursor_y < -HALF_SCREEN_HEIGHT)
		cursor_y = -HALF_SCREEN_HEIGHT;

	else if (cursor_y > HALF_SCREEN_HEIGHT)
		cursor_y = HALF_SCREEN_HEIGHT;

	cursor_position_.x = (float)cursor_x;
	cursor_position_.y = (float)cursor_y;
}

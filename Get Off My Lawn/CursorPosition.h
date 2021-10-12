/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   CursorPosition.h
\author Wong Zhihao(100%)
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the declaration of the Cursor Position class and functions.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef CURSORPOSITION_H
#define CURSORPOSITION_H

#include "AEEngine.h"	// AEVec2 component

class Cursor_Position
{
protected:
	AEVec2 cursor_position_;	// The in-game coordinates cursor position

public:
	// Gets the cursor position
	AEVec2 Get_Cursor_Position() const;

	// Calculates and sets the cursor position
	void Set_Cursor_Position();
};

#endif
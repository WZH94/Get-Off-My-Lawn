/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   SystemComponents.h
\author Wong Zhihao			(100%)
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the declarations of the SystemComponents, which holds
various system components and their functions for state functions.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef SYSTEMCOMPONENTS_H
#define SYSTEMCOMPONENTS_H

// System components
#include "GraphicsManager.h"
#include "CursorPosition.h"
#include "Font.h"
#include "FrameRateManager.h"
#include "AudioManager.h"

// For other files to use
#include "main.h"

class System_Components
{
private:

public:
	///////////////
	// Components
	Graphics_Manager* graphics_manager_;
	Cursor_Position* cursor_position_;
	Font_Manager* font_manager_;
	Framerate_Manager* framerate_manager;
	Audio_Manager* audio_manager;

	//////////////
	// Functions

	// Loads up the system components and allocates memory for them
	void Load_System_Components();

	// Unloads and frees all the system components
	void Unload_System_Components();

};
 
extern System_Components system_components;

#endif
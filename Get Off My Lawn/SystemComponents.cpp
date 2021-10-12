/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   SystemComponents.cpp
\author Wong Zhihao				(100%)
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the implementation of the SystemComponents, which holds
various system components and their functions for state functions.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "SystemComponents.h"	// Class and function declarations

/******************************************************************************/
/*!
	Loads up the system components and allocates memory for them
*/
/******************************************************************************/
void System_Components::Load_System_Components()
{
	graphics_manager_ = new Graphics_Manager;

	graphics_manager_->Load_Graphics();

	cursor_position_ = new Cursor_Position;

	font_manager_ = new Font_Manager;
	font_manager_->Load_Fonts();

	framerate_manager = new Framerate_Manager;

	audio_manager = new Audio_Manager;
	audio_manager->Initialise_FMOD();
}

/******************************************************************************/
/*!
	Unloads and frees all the system components
*/
/******************************************************************************/
void System_Components::Unload_System_Components()
{
	graphics_manager_->Unload_Graphics();

	delete graphics_manager_;

	delete cursor_position_;

	delete font_manager_;

	delete framerate_manager;

	audio_manager->Release_FMOD();

	delete audio_manager;
}

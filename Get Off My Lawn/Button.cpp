
/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Button.cpp
\author Ngm Hui Min, Lois (100%)
\par    email: lois.ngm\@digipen.edu
\par    DigiPen login: lois.ngm
\par    Course: GAM150
\date	13/04/18
\brief
This file contains code algorithmn for general buttons

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Button.h"
#include "GraphicsManager.h"
#include "RenderManager.h"
#include "ObjectList.h"
#include "PlayerData.h"
#include "GameStateList.h"

#include <iostream>
#include "LevelData.h"
#include "SystemComponents.h"
#include "LogicComponents.h"
#include <math.h>

/******************************************************************************/
/*!
		Defeault Constructor
*/
/******************************************************************************/
Button::Button()
{
}

/******************************************************************************/
/*!
				Non-default constructor
*/
/******************************************************************************/
Button::Button(float x, float y, float scale_x, float scale_y, UNIT_TYPES t, float texture_width, float texture_start, SIDES side, OBJECT_TYPES obj)
	: GameObject(side, x, y, scale_x, scale_y, obj, t)
{
	Set_Start_Texture(texture_start);
	Set_Texture_Change(texture_start);
	Set_Texture_Width(texture_width);
}

/******************************************************************************/
/*!
						Destructor
*/
/******************************************************************************/
Button::~Button()
{

}
/******************************************************************************/
/*!
	Updates for Button
*/
/******************************************************************************/

void Button::Update()
{
}
/******************************************************************************/
/*!
					Draw for button
*/
/******************************************************************************/

void Button::Draw()
{
	if (alive_)
		Render_Object(*this);
}
/******************************************************************************/
/*!
			Set states for buttons
*/
/******************************************************************************/
void Button::Set_Active(ACTIVE a)
{
	// if current state is paused and it is not getting unpaused, return
	if (active_ == PAUSED && a != UNPAUSE)
		return;
	// if the state is the same, do not enter
	if (active_ == a)
		return;

	// handle texture changes and sound effects
	switch (a)
	{
	case LOCKED:
		Set_Texture_Change(Get_Start_Texture() + Get_Texture_Width() * 3);
		break;
	case INACTIVE:
		Set_Texture_Change(Get_Start_Texture());
		break;
	case HOVER:
		Set_Texture_Change(Get_Start_Texture() + Get_Texture_Width());
		system_components.audio_manager->Play_Sound(SFX_BUTTON_HOVER);
		break;
	case CLICK:
		Set_Texture_Change(Get_Start_Texture() + (Get_Texture_Width() * 2));
		break;
	}
	active_ = a;

}

/******************************************************************************/
/*!			
					getter for Button
*/
/******************************************************************************/
ACTIVE Button::Get_Active()
{
	return active_;
}
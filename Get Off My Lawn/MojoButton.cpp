/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   MojoButton.cpp
\author Ngm Hui Min, Lois(100%)
\par    email: lois.ngm\@digipen.edu
\par    DigiPen login: lois.ngm
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the algorithmn to change the control the granny mojo level 
up button

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "MojoButton.h"
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
					Constructor
*/
/******************************************************************************/
MojoButton::MojoButton()
{
}
/******************************************************************************/
/*!
					Non-default Constructor
*/
/******************************************************************************/

MojoButton::MojoButton(float x, float y, float scale_x, float scale_y, UNIT_TYPES t, float texture_width, float texture_start)
	: Button(x, y, scale_x, scale_y, t, texture_width), active_multiplier_(0)
{
	Set_Start_Texture(texture_start);
	Set_Texture_Change(texture_start + 0.25f * 3);
	Set_Texture_Width(0.25f);
}

/******************************************************************************/
/*!
					Destrcutor
*/
/******************************************************************************/
MojoButton::~MojoButton()
{

}

/******************************************************************************/
/*!
					updates the granny mojo button
*/
/******************************************************************************/
void MojoButton::Update()
{
	if (logic_components.level_data->players->Get_Max_Granny_Mojo() < (playdata.Get_Money_Rate_Upgrade() ? 500 : 300) &&
		logic_components.level_data->players->Get_Granny_Mojo() >= 
		((playdata.Get_Money_Rate_Upgrade() == 2)?(logic_components.level_data->players->Get_Max_Granny_Mojo() - 30.0f):(logic_components.level_data->players->Get_Max_Granny_Mojo() - 20.0f)) &&
		Get_Active() != CLICK)
	{
		Set_Active(INACTIVE);

		if (active_multiplier_ <= 0.0f)
		{
			if (Get_Texture_Change() == 0.0f)
				Set_Texture_Change(Get_Texture_Width());

			else
				Set_Texture_Change(0.0f);

			active_multiplier_ = 0.5f;
		}

		else
		{
			active_multiplier_ -= system_components.framerate_manager->Get_Game_Time();
		}
	}

	else if(Get_Active() != CLICK)
		Set_Active(LOCKED);
}

/******************************************************************************/
/*!
				Draws
*/
/******************************************************************************/
void MojoButton::Draw()
{
	if (alive_)
		Render_Object(*this);
}

/******************************************************************************/
/*!
			Setter for Active
*/
/******************************************************************************/
void MojoButton::Set_Active(ACTIVE a)
{
	if (active_ == a)
		return;

	// Granny buttons
	switch (a)
	{
	case LOCKED:
		Set_Texture_Change(Get_Start_Texture() + Get_Texture_Width() * 3);
		break;
	case INACTIVE:
		Set_Texture_Change(Get_Start_Texture());
		break;
	case CLICK:
		Set_Texture_Change(Get_Start_Texture() + Get_Texture_Width() * 2);
		system_components.audio_manager->Play_Sound(SFX_LEVEL_BUTTON_UP);
		break;
	}
	active_ = a;

}
/******************************************************************************/
/*!
				getter Active
*/
/******************************************************************************/

ACTIVE MojoButton::Get_Active()
{
	return active_;
}
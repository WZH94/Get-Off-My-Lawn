/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   DescriptionButton.cpp
\author Ngm Hui Min, Lois(100%)
\par    email: lois.ngm\@digipen.edu
\par    DigiPen login: lois.ngm
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the algorithmn to control and handle description buttons.
Description buttons are buttons that have descriptions on them to describe
what they do

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "DescriptionButton.h"
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
DescriptionButton::DescriptionButton()
{
}
/******************************************************************************/
/*!
			Non-default Constructor
*/
/******************************************************************************/

DescriptionButton::DescriptionButton(float x, float y, float scale_x, float scale_y, UNIT_TYPES t, float texture_width, OBJECT_TYPES obj)
	: Button(x, y, scale_x, scale_y, t, texture_width, 0.0f, NONE, obj)
{
	Set_Active(INACTIVE);
	Set_Texture_Width(texture_width);
	description_ = nullptr;
	if (t >= BUTTON_HEALTH_INCREASE && t <= BUTTON_TOWER_STUN)
	{
		switch (t)
		{
			// for shop
		case BUTTON_RANGE_INCREASE:
			if (Get_x() == -540.0f || Get_x() == -60.0f || Get_x() == 180.0f || Get_x() == 300.0f) 
			{
				description_ = new GameObject{ NONE, x + 175.0f, y + 55.5f, 300.0f, 75.0f, DESCRIPTION, DESC_RANGE_INCREASE_1 };
				description_->Set_Alive(false);
				logic_components.object_manager->Insert_Object(description_);
			}
			break;
		case BUTTON_RANGE_INCREASE_2:
				description_ = new GameObject{ NONE, x - 175.0f, y + 55.5f, 300.0f, 75.0f, DESCRIPTION, DESC_RANGE_INCREASE_2 };
				description_->Set_Alive(false);
				logic_components.object_manager->Insert_Object(description_);
			break;
		case BUTTON_HEALTH_INCREASE:
			if (Get_x() == -420.0f || Get_x() == -300.0f || Get_x() == 60.0f)
			{
				description_ = new GameObject{ NONE, x + 175.0f, y + 55.5f, 300.0f, 75.0f, DESCRIPTION, DESC_HEALTH_INCREASE_1 };
				description_->Set_Alive(false);
				logic_components.object_manager->Insert_Object(description_);
			}
			if (Get_x() == 420.0f)
			{
				description_ = new GameObject{ NONE, x - 175.0f, y + 55.5f, 300.0f, 75.0f, DESCRIPTION, DESC_HEALTH_INCREASE_2 };
				description_->Set_Alive(false);
				logic_components.object_manager->Insert_Object(description_);
			}
			break;
		case BUTTON_COOKIE_ATTACKRATE_INCREASE:
			description_ = new GameObject{ NONE, x + 175.0f, y + 55.5f, 300.0f, 75.0f, DESCRIPTION, DESC_ATTACKRATE_INCREASE_2 };
			description_->Set_Alive(false);
			logic_components.object_manager->Insert_Object(description_);
			break;
		case BUTTON_NINJA_ATTACKRATE_INCREASE:
			description_ = new GameObject{ NONE, x + 175.0f, y + 55.5f, 300.0f, 75.0f, DESCRIPTION, DESC_ATTACKRATE_INCREASE_1 };
			description_->Set_Alive(false);
			logic_components.object_manager->Insert_Object(description_);
			break;
		case BUTTON_MAX_CAP:
			description_ = new GameObject{ NONE, x - 175.0f, y + 55.5f, 300.0f, 75.0f, DESCRIPTION, DESC_MAX_CAP_INCREASE };
			description_->Set_Alive(false);
			logic_components.object_manager->Insert_Object(description_);
			break;
		case BUTTON_SPEED_INCREASE:
			description_ = new GameObject{ NONE, x + 175.0f, y + 55.5f, 300.0f, 75.0f, DESCRIPTION, DESC_SPEED_INCREASE };
			description_->Set_Alive(false);
			logic_components.object_manager->Insert_Object(description_);
			break;
		case BUTTON_COOLDOWN_DECREASE:
			description_ = new GameObject{ NONE, x + 175.0f, y + 55.5f, 300.0f, 75.0f, DESCRIPTION, DESC_COOLDOWN_DECREASE };
			description_->Set_Alive(false);
			logic_components.object_manager->Insert_Object(description_);
			break;
		case BUTTON_DAMAGE_INCREASE:
			description_ = new GameObject{ NONE, x + 175.0f, y + 55.5f, 300.0f, 75.0f, DESCRIPTION, DESC_DAMAGE_INCREASE };
			description_->Set_Alive(false);
			logic_components.object_manager->Insert_Object(description_);
			break;
		case BUTTON_HEALING_INCREASE:
			description_ = new GameObject{ NONE, x + 175.0f, y + 55.5f, 300.0f, 75.0f, DESCRIPTION, DESC_HEALING_INCREASE };
			description_->Set_Alive(false);
			logic_components.object_manager->Insert_Object(description_);
			break;
		case BUTTON_COST_DECREASE:
			description_ = new GameObject{ NONE, x - 175.0f, y + 55.5f, 300.0f, 75.0f, DESCRIPTION, DESC_COST_DECREASE };
			description_->Set_Alive(false);
			logic_components.object_manager->Insert_Object(description_);
			break;

			// for tower nodes
		case BUTTON_TOWER_SHOOTER:
			description_ = new GameObject{ NONE, x + 150.0f, y + 75.0f, 300.0f, 150.0f, SCALABLE_DESCRIPTION, DESC_TOWER_SHOOTER };
			description_->Set_Alive(false);
			Set_Active(LOCKED);
			logic_components.object_manager->Insert_Object(description_);
			break;
		case BUTTON_TOWER_SWINGING:
			description_ = new GameObject{ NONE, x + 150.0f, y + 75.0f, 300.0f, 150.0f, SCALABLE_DESCRIPTION, DESC_TOWER_SWINGING };
			description_->Set_Alive(false);
			Set_Active(LOCKED);
			logic_components.object_manager->Insert_Object(description_);
			break;
		case BUTTON_TOWER_POISON:
			description_ = new GameObject{ NONE, x + 150.0f, y + 75.0f, 300.0f, 150.0f, SCALABLE_DESCRIPTION, DESC_TOWER_POISON };
			description_->Set_Alive(false);
			Set_Active(LOCKED);
			logic_components.object_manager->Insert_Object(description_);
			break;
		case BUTTON_TOWER_SLOW:
			description_ = new GameObject{ NONE, x+150.0f, y+75.0f, 300.0f, 150.0f, SCALABLE_DESCRIPTION, DESC_TOWER_SLOW };
			description_->Set_Alive(false);
			Set_Active(LOCKED);
			logic_components.object_manager->Insert_Object(description_);
			break;
		case BUTTON_TOWER_STUN:
			description_ = new GameObject{ NONE, x + 150.0f, y + 75.0f, 300.0f, 150.0f, SCALABLE_DESCRIPTION, DESC_TOWER_STUN };
			description_->Set_Alive(false);
			Set_Active(LOCKED);
			logic_components.object_manager->Insert_Object(description_);
			break;

		}
	}
}
/******************************************************************************/
/*!
			Destructor
*/
/******************************************************************************/
DescriptionButton::~DescriptionButton()
{

}
/******************************************************************************/
/*!
					Updates
*/
/******************************************************************************/

void DescriptionButton::Update()
{
	// tier one buttons in shop
	if (Get_Unit_Type() >= BUTTON_HEALTH_INCREASE && Get_Unit_Type() <= BUTTON_MAX_CAP)
	{
		if (Get_Active() != BOUGHT && !playdata.Get_Stars_Collected())
		{
			Set_Active(LOCKED);
		}
	}
	// tier 2 buttons in shop
	if (Get_Unit_Type() >= BUTTON_COOKIE_ATTACKRATE_INCREASE && Get_Unit_Type() <= BUTTON_RANGE_INCREASE_2)
	{

		if (Get_Active() != BOUGHT && playdata.Get_Stars_Collected() <= 1)
		{
			Set_Active(LOCKED);
		}
		else if(playdata.Get_Stars_Collected() >= 2 && Get_Active() == LOCKED)
		{
			switch (Get_Unit_Type())
			{
			case BUTTON_COOKIE_ATTACKRATE_INCREASE:
			{
				if (playdata.Get_Shooter_Upgrade() == 1)
					Set_Active(UNLOCKED);
				break;
			}
			case BUTTON_SPEED_INCREASE:
			{
				if (playdata.Get_Tank_Upgrade() == 1)
					Set_Active(UNLOCKED);
				break;
			}
			case BUTTON_COOLDOWN_DECREASE: 
			{
				if(Get_x() == -300.0f)
					if (playdata.Get_Speed_Upgrade() == 1)
						Set_Active(UNLOCKED);
				if (Get_x() == -180.0f)
					if (playdata.Get_Saboteur_Upgrade() == 1)
						Set_Active(UNLOCKED);
				break;
			}
			case BUTTON_DAMAGE_INCREASE:
			{
				if (Get_x() == -60.0f)
					if (playdata.Get_Slow_Upgrade() == 1)
						Set_Active(UNLOCKED);

				if (Get_x() == 60.0f)
					if (playdata.Get_Bruiser_Upgrade() == 1)
						Set_Active(UNLOCKED);

				if (Get_x() == 180.0f)
					if (playdata.Get_Stun_Upgrade() == 1)
						Set_Active(UNLOCKED);

				break;
			}
			case BUTTON_HEALING_INCREASE:
				if (playdata.Get_Heal_Upgrade() == 1)
					Set_Active(UNLOCKED);
				break;
			case BUTTON_RANGE_INCREASE_2:
				if (playdata.Get_Buff_Upgrade() == 1)
					Set_Active(UNLOCKED);
			case BUTTON_COST_DECREASE:
				if (playdata.Get_Money_Rate_Upgrade() == 1)
						Set_Active(UNLOCKED);
			}
		}
	}
}
/******************************************************************************/
/*!
								Draws
*/
/******************************************************************************/

void DescriptionButton::Draw()
{
	if (alive_)
		Render_Object(*this);
}
/******************************************************************************/
/*!
					Setter for active
*/
/******************************************************************************/
void DescriptionButton::Set_Active(ACTIVE a)
{
	// if same state, return
	if (active_ == a)
		return;
	// if item is currently bought, return
	if (active_ == BOUGHT)
		return;
	// if button is locked and button entered is not unlocked, return
	if (active_ == LOCKED && a != UNLOCKED)
		return;
	switch (a)
	{
	case LOCKED:
		Set_Texture_Change(Get_Start_Texture() + Get_Texture_Width() * 3);
		break;
	case INACTIVE:
		Set_Texture_Change(Get_Start_Texture());
		description_->Set_Alive(false);
		break;
	case HOVER:
		Set_Texture_Change(Get_Start_Texture() + Get_Texture_Width());
		system_components.audio_manager->Play_Sound(SFX_BUTTON_HOVER);
		description_->Set_Alive(true);
		break;
	case CLICK:
		Set_Texture_Change(Get_Start_Texture() + (Get_Texture_Width() * 2));
		break;
	case BOUGHT:
		Set_Texture_Change(Get_Start_Texture() + (Get_Texture_Width() * 4));
		break;
	case UNLOCKED:
		Set_Texture_Change(Get_Start_Texture());
		a = INACTIVE;
		break;
	}
	active_ = a;

}

/******************************************************************************/
/*!
			Getter for description
*/
/******************************************************************************/
GameObject * DescriptionButton::Get_Description()
{
	return description_;
}

/******************************************************************************/
/*!
			Setter for description
*/
/******************************************************************************/
void DescriptionButton::Set_Description(GameObject * desc)
{
	description_ = desc;
}
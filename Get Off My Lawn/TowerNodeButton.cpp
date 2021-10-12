/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   TowerNodeButton.cpp
\author Ngm Hui Min, Lois(100%)
\par    email: lois.ngm\@digipen.edu
\par    DigiPen login: lois.ngm
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the algorithmn to control and handle Granny side tower nodes

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "TowerNodeButton.h"
#include "GraphicsManager.h"
#include "RenderManager.h"
#include "ObjectList.h"
#include "PlayerData.h"
#include "GameStateList.h"

#include <iostream>
#include "LevelData.h"
#include "SystemComponents.h"
#include "LogicComponents.h"
#include "DescriptionButton.h"
#include "Input.h"
#include <math.h>

TowerNodeButton::TowerNodeButton()
{
}

TowerNodeButton::TowerNodeButton(float x, float y, float scale_x, float scale_y, UNIT_TYPES t, float texture_width = 0.0f, float texture_start = 0.0f, SIDES side = GRANDMA)
	: Button(x, y, scale_x, scale_y, t, texture_width, texture_start, side, SCALABLE_BUTTON)
{
	shooter_ = nullptr;
	swinging_ = nullptr;
	poison_ = nullptr;
	slow_ = nullptr;
	stun_ = nullptr;
	close_ = nullptr;
	ring_ = nullptr;
	float x_shift_lr = 40.0f;
	float y_shift = 30.0f;
	float x_shift_ud = 15.0f;
	switch (t)
	{
	case G_TOWER_NODE4:
		stun_ = new DescriptionButton(x - x_shift_ud, y - y_shift, 27.5f, 27.5f, BUTTON_TOWER_STUN, 0.25f, SCALABLE_BUTTON);
		slow_ = new DescriptionButton(x + x_shift_ud, y - y_shift, 27.5f, 27.5f, BUTTON_TOWER_SLOW, 0.25f, SCALABLE_BUTTON);
		logic_components.object_manager->Insert_Object(stun_);
		logic_components.object_manager->Insert_Object(slow_);
		stun_->Set_Alive(false);
		slow_->Set_Alive(false);
	case G_TOWER_NODE3:
		poison_ = new DescriptionButton(x + x_shift_lr, y, 27.5f, 27.5f, BUTTON_TOWER_POISON, 0.25f, SCALABLE_BUTTON);
		logic_components.object_manager->Insert_Object(poison_);
		poison_->Set_Alive(false);
	case G_TOWER_NODE2:
		swinging_ = new DescriptionButton(x + x_shift_ud, y + y_shift, 27.5f, 27.5f, BUTTON_TOWER_SWINGING, 0.25f, SCALABLE_BUTTON);
		logic_components.object_manager->Insert_Object(swinging_);
		swinging_->Set_Alive(false);
	case G_TOWER_NODE1:
		shooter_ = new DescriptionButton(x - x_shift_ud, y + y_shift, 27.5f, 27.5f, BUTTON_TOWER_SHOOTER, 0.25f, SCALABLE_BUTTON);
		close_ = new Button(x - x_shift_lr, y, 27.5f, 27.5f, BUTTON_TOWER_CLOSE, 0.25f, 0.0f, NONE, SCALABLE_BUTTON);
		ring_ = new GameObject(NONE, x, y, 75.0f, 75.0f, SCALABLE_GENERAL, GENERAL_RING);
		ring_->Set_Alive(false);
		shooter_->Set_Alive(false);
		close_->Set_Alive(false);
		logic_components.object_manager->Insert_Object(ring_);
		logic_components.object_manager->Insert_Object(shooter_);
		logic_components.object_manager->Insert_Object(close_);
		break;
	}
}

TowerNodeButton::~TowerNodeButton()
{

}

void TowerNodeButton::Update()
{
	// Update according to granny mojo
	if (active_ == RELEASED)
	{
		if (close_) 
		{
			if (Cursor_Box_Collision_Camera(close_))
			{
				if (close_->Get_Active() != CLICK)
					close_->Set_Active(HOVER);
				if (AEInputCheckCurr(AEVK_LBUTTON))
					close_->Set_Active(CLICK);
				if (AEInputCheckReleased(AEVK_LBUTTON))
				{
					Set_Active(INACTIVE);
					system_components.audio_manager->Play_Sound(SFX_BUTTON_CLICK);
				}
			}
			else
				close_->Set_Active(INACTIVE);
		}
		if (shooter_)
			Check_Tower_Buttons(shooter_, 100.0f);
		if (swinging_)
			Check_Tower_Buttons(swinging_, 200.0f);
		if (poison_)
			Check_Tower_Buttons(poison_, 150.0f);
		if (slow_)
			Check_Tower_Buttons(slow_, 150.0f);
		if (stun_)
			Check_Tower_Buttons(stun_, 200.0f);
	}
}

void TowerNodeButton::Check_Tower_Buttons(DescriptionButton* button, float money)
{

	if (logic_components.level_data->players->Get_Granny_Mojo() >= money && button->Get_Active() != INACTIVE && button->Get_Active() != HOVER && button->Get_Active() != CLICK)
	{
		button->Set_Active(UNLOCKED);
	}
	if (Cursor_Box_Collision_Camera(button))
	{
		if (button->Get_Active() == LOCKED)
		{
			button->Get_Description()->Set_Alive(true);
		}


		if (button->Get_Active() != CLICK)
		{
			button->Set_Active(HOVER);
		}
		if (AEInputCheckCurr(AEVK_LBUTTON))
		{
			button->Set_Active(CLICK);
		}
		if (AEInputCheckReleased(AEVK_LBUTTON))
		{
			if (logic_components.level_data->players->Get_Granny_Mojo() >= money)
			{
				logic_components.level_data->players->Set_Granny_Mojo(-money);
				switch (button->Get_Unit_Type()) {
				case BUTTON_TOWER_SHOOTER:
					Spawn_Object(G_T_SHOOTING, Get_x(), Get_y());
					system_components.audio_manager->Play_Sound(SFX_TOWER_CONSTRUCT, pos_.x, pos_.y);
					break;
				case BUTTON_TOWER_SWINGING:
					Spawn_Object(G_T_SWING, Get_x(), Get_y());
					system_components.audio_manager->Play_Sound(SFX_TOWER_CONSTRUCT, pos_.x, pos_.y);
					break;
				case BUTTON_TOWER_POISON:
					Spawn_Object(G_T_POISON, Get_x(), Get_y());
					system_components.audio_manager->Play_Sound(SFX_TOWER_CONSTRUCT, pos_.x, pos_.y);
					break;
				case BUTTON_TOWER_SLOW:
					Spawn_Object(G_T_SLOW, Get_x(), Get_y());
					system_components.audio_manager->Play_Sound(SFX_TOWER_CONSTRUCT, pos_.x, pos_.y);
					break;
				case BUTTON_TOWER_STUN:
					Spawn_Object(G_T_STUN, Get_x(), Get_y());
					system_components.audio_manager->Play_Sound(SFX_TOWER_CONSTRUCT, pos_.x, pos_.y);
					break;
				default:
					break;
				}
				Set_Active(BOUGHT);
				if (logic_components.level_data->players->Get_Granny_Mojo() >= money)
					button->Set_Active(INACTIVE);
				else
					button->Set_Active(LOCKED);
			}
			button->Get_Description()->Set_Alive(false);
		}
	}
	else if (button->Get_Active() != LOCKED)
		button->Set_Active(INACTIVE);
	if (!Cursor_Box_Collision_Camera(button))
		button->Get_Description()->Set_Alive(false);
}

void TowerNodeButton::Draw()
{
	if (alive_)
		Render_Object(*this);
}
void TowerNodeButton::Set_Active(ACTIVE a)
{
	if (active_ == a)
		return;

	// Tower Node Buttons
	switch (a)
	{
	case INACTIVE:
		if (stun_)stun_->Set_Alive(false);
		if (slow_) slow_->Set_Alive(false);
		if (poison_)poison_->Set_Alive(false);
		if (swinging_) swinging_->Set_Alive(false);
		if (shooter_)shooter_->Set_Alive(false);
		if (close_) close_->Set_Alive(false);
		if (ring_) ring_->Set_Alive(false);
		Set_Texture_Change(Get_Start_Texture());
		break;
	case HOVER:
		Set_Texture_Change(Get_Start_Texture() + Get_Texture_Width());
		system_components.audio_manager->Play_Sound(SFX_BUTTON_HOVER);
		break;
	case CLICK:
		Set_Texture_Change(Get_Start_Texture() + (Get_Texture_Width() * 2));
		break;
	case RELEASED:
		if (stun_)stun_->Set_Alive(true);
		if (slow_) slow_->Set_Alive(true);
		if (poison_)poison_->Set_Alive(true);
		if (swinging_) swinging_->Set_Alive(true);
		if(shooter_)shooter_->Set_Alive(true);
		if(close_) close_->Set_Alive(true);
		if (ring_) ring_->Set_Alive(true);
		Set_Texture_Change(Get_Start_Texture());
		break;
	case BOUGHT:
		Set_Alive(false);
		if (stun_)stun_->Set_Alive(false);
		if (slow_) slow_->Set_Alive(false);
		if (poison_)poison_->Set_Alive(false);
		if (swinging_) swinging_->Set_Alive(false);
		if (shooter_)shooter_->Set_Alive(false);
		if (close_) close_->Set_Alive(false);
		if (ring_) ring_->Set_Alive(false);
		Set_Texture_Change(Get_Start_Texture());
		break;
	}
	active_ = a;

}

ACTIVE TowerNodeButton::Get_Active()
{
	return active_;
}



DescriptionButton* TowerNodeButton::Get_Shooter_Button()
{
	return shooter_;
}
DescriptionButton* TowerNodeButton::Get_Swinging_Button()
{
	return swinging_;
}
DescriptionButton* TowerNodeButton::Get_Poison_Button()
{
	return poison_;
}
DescriptionButton* TowerNodeButton::Get_Slow_Button()
{
	return slow_;
}
DescriptionButton* TowerNodeButton::Get_Stun_Button()
{
	return stun_;
}
Button* TowerNodeButton::Get_Close_Button()
{
	return close_;
}
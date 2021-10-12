/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   SoldierButton.cpp
\author Ngm Hui Min, Lois(100%)
\par    email: lois.ngm\@digipen.edu
\par    DigiPen login: lois.ngm
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the algorithmn to control soldier buttons and handle them 
as well.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "SoldierButton.h"
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

SoldierButton::SoldierButton()
{
}

SoldierButton::SoldierButton(float x, float y, float scale_x, float scale_y, UNIT_TYPES t, float texture_width)
	: DescriptionButton(x, y, scale_x, scale_y, t, texture_width), countdown_timer_(0), current_timer_(0), ratio_granny_filler_(0)
{
	Set_Active(INACTIVE);
	granny_bar_ = nullptr;
	granny_filler_ = nullptr;
	description_ = nullptr;
	if (t >= G_BUTTON_1 && t <= G_BUTTON_9)
	{
		granny_bar_ = new GameObject{NONE, x, y - 20.0f, 42.0f, 10.0f, DESCRIPTION, GRANNY_BAR };
		granny_filler_ = new GameObject{NONE, x, y - 20.0f, 0.0f, 8.0f, DESCRIPTION, GRANNY_FILLER };
		description_ = new GameObject{NONE, 400.0f, 75.0f, 240.0f, 400.0f, DESCRIPTION, G_DESC };
		logic_components.object_manager->Insert_Object(description_);
		logic_components.object_manager->Insert_Object(granny_bar_);
		logic_components.object_manager->Insert_Object(granny_filler_);
		switch (t)
		{
		case G_BUTTON_1:
			description_->Set_Texture_Change(0.0f);
			break;
		case G_BUTTON_2:
			description_->Set_Texture_Change(0.1f);
			break;
		case G_BUTTON_3:
			description_->Set_Texture_Change(0.2f);
			break;
		case G_BUTTON_4:
			description_->Set_Texture_Change(0.3f);
			break;
		case G_BUTTON_5:
			description_->Set_Texture_Change(0.4f);
			break;
		case G_BUTTON_6:
			description_->Set_Texture_Change(0.5f);
			break;
		case G_BUTTON_7:
			description_->Set_Texture_Change(0.6f);
			break;
		case G_BUTTON_8:
			description_->Set_Texture_Change(0.7f);
			break;
		case G_BUTTON_9:
			description_->Set_Texture_Change(0.8f);
			break;
		default:
			break;
		}
		description_->Set_Alive(false);
	}
}



SoldierButton::~SoldierButton()
{

}

void SoldierButton::Update()
{
	switch (Get_Unit_Type())
	{
	case G_BUTTON_1:
		if (logic_components.level_data->players->Get_Granny_Mojo() < 10 || countdown_timer_ > 0)
			Set_Active(LOCKED);
		else if (Get_Active() != HOVER && Get_Active() != CLICK)
			Set_Active(INACTIVE);
		break;
	case G_BUTTON_2:
	case G_BUTTON_3:
		if (logic_components.level_data->players->Get_Granny_Mojo() < 20 || countdown_timer_ > 0)
			Set_Active(LOCKED);
		else if (Get_Active() != HOVER && Get_Active() != CLICK)
			Set_Active(INACTIVE);
		break;
	case G_BUTTON_4:
		if (logic_components.level_data->players->Get_Granny_Mojo() < 35 || countdown_timer_ > 0)
			Set_Active(LOCKED);
		else if (Get_Active() != HOVER && Get_Active() != CLICK)
			Set_Active(INACTIVE);
		break;
	case G_BUTTON_5:
		if (logic_components.level_data->players->Get_Granny_Mojo() < 50 || countdown_timer_ > 0)
			Set_Active(LOCKED);
		else if (Get_Active() != HOVER && Get_Active() != CLICK)
			Set_Active(INACTIVE);
		break;
	case G_BUTTON_6:
		if (logic_components.level_data->players->Get_Granny_Mojo() < 100 || countdown_timer_ > 0)
			Set_Active(LOCKED);
		else if (Get_Active() != HOVER && Get_Active() != CLICK)
			Set_Active(INACTIVE);
		break;
	case G_BUTTON_7:
		if (logic_components.level_data->players->Get_Granny_Mojo() < 75 || countdown_timer_ > 0)
			Set_Active(LOCKED);
		else if (Get_Active() != HOVER && Get_Active() != CLICK)
			Set_Active(INACTIVE);
		break;
	case G_BUTTON_8:
		if (logic_components.level_data->players->Get_Granny_Mojo() < 80 || countdown_timer_ > 0)
			Set_Active(LOCKED);
		else if (Get_Active() != HOVER && Get_Active() != CLICK)
			Set_Active(INACTIVE);
		break;
	case G_BUTTON_9:
		if (logic_components.level_data->players->Get_Granny_Mojo() < 70 || countdown_timer_ > 0)
			Set_Active(LOCKED);
		else if (Get_Active() != HOVER && Get_Active() != CLICK)
			Set_Active(INACTIVE);
		break;
	}
	if (countdown_timer_ >= 0.0f) 
	{
		countdown_timer_ -= system_components.framerate_manager->Get_Game_Time();
		f64 move = 38.0f * (ratio_granny_filler_ - countdown_timer_) / ratio_granny_filler_;
		granny_filler_->Set_Scale_X(float(move));
	}

	if(countdown_timer_ <= 0.0f && granny_bar_->Get_Alive())
	{
		granny_bar_->Set_Alive(false);
		granny_filler_->Set_Alive(false);
		countdown_timer_ = 0.0f;
		return;
	}
}

void SoldierButton::Draw()
{
	if (alive_)
		Render_Object(*this);
}
void SoldierButton::Set_Active(ACTIVE a)
{
	if (active_ == a)
		return;
	switch (a)
	{
	case LOCKED:
		Set_Texture_Change(Get_Start_Texture() + Get_Texture_Width() * 3);
		description_->Set_Alive(false);
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
	}
	active_ = a;

}

GameObject * SoldierButton::Get_Description()
{
	return description_;
}


void SoldierButton::Set_Countdown_Timer(f64 timer)
{
	ratio_granny_filler_ = timer;
	countdown_timer_ = timer;
	granny_filler_->Set_Scale_X(0.0f);
	granny_bar_->Set_Alive(true);
	granny_filler_->Set_Alive(true);
}
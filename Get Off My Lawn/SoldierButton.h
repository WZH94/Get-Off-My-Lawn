/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   SoldierButton.h
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
#pragma once
#ifndef SoldierButton_H
#define SoldierButton_H

#include "GameObject.h"
#include "DescriptionButton.h"
//#include "System.h"

typedef class Graphics_Manager Graphics_Manager;
typedef enum UNIT_TYPES UNIT_TYPES;
typedef class Level Level;
class SoldierButton: public DescriptionButton
{
private:
	f64 countdown_timer_;
	f64 current_timer_;
	f64 update_timer_;
	f64 ratio_granny_filler_;
	GameObject* granny_bar_;
	GameObject* granny_filler_;
public:
	SoldierButton();
	SoldierButton(float x, float y, float scale_x, float scale_y, UNIT_TYPES type, float texture_width = 0.0f);
	virtual ~SoldierButton();
	virtual void Update();
	virtual void Draw();
	void Set_Active(ACTIVE a);
	GameObject * Get_Description();
	void Set_Countdown_Timer(f64 timer);
};
#endif SoldierButton_H
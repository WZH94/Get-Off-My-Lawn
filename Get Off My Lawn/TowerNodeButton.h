/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   TowerNodeButton.h
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
#pragma once
#ifndef TowerNodeButton_H
#define TowerNodeButton_H

#include "GameObject.h"
#include "Button.h"
//#include "System.h"

typedef class Graphics_Manager Graphics_Manager;
typedef enum UNIT_TYPES UNIT_TYPES;
typedef class Level Level;
typedef class DescriptionButton DescriptionButton;
class TowerNodeButton : public Button
{
protected:
	DescriptionButton *shooter_;
	DescriptionButton *swinging_;
	DescriptionButton *poison_;
	DescriptionButton *slow_;
	DescriptionButton *stun_;
	Button *close_;
	GameObject *ring_;
public:
	TowerNodeButton();
	TowerNodeButton(float x, float y, float scale_x, float scale_y, UNIT_TYPES t, float texture_width, float texture_start, SIDES side);
	virtual ~TowerNodeButton();
	virtual void Update();
	virtual void Draw();
	virtual void Set_Active(ACTIVE a);
	ACTIVE Get_Active();
	DescriptionButton* Get_Shooter_Button();
	DescriptionButton* Get_Swinging_Button();
	DescriptionButton* Get_Poison_Button();
	DescriptionButton* Get_Slow_Button();
	DescriptionButton* Get_Stun_Button();
	Button* Get_Close_Button();
	void Check_Tower_Buttons(DescriptionButton*, float);
};
#endif TowerNodeButton_H
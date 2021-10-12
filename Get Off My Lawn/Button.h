/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Button.h
\author Ngm Hui Min, Lois(100%)
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
#pragma once
#ifndef Button_H
#define Button_H

#include "GameObject.h"

enum ACTIVE
{
	INACTIVE = 0,
	HOVER, 
	CLICK,
	BOUGHT,
	PAUSED,
	UNPAUSE,
	RELEASED,
	LOCKED,
	UNLOCKED,
};


typedef class Graphics_Manager Graphics_Manager;
typedef enum UNIT_TYPES UNIT_TYPES;
typedef class Level Level;
class Button : public GameObject
{
protected:
	// button state
	ACTIVE active_;
public:
	// default constructor
	Button();
	// non-default constructor
	Button(float x, float y, float scale_x, float scale_y, UNIT_TYPES type, float texture_width = 0.0f, float texture_start = 0.0f, SIDES = NONE, OBJECT_TYPES obj = BUTTONS);
	// destructor
	virtual ~Button();
	// updates
	virtual void Update();
	// draws
	virtual void Draw();
	// setter for active_
	virtual void Set_Active(ACTIVE a);
	// getter for active_
	ACTIVE Get_Active();

};
#endif Button_H
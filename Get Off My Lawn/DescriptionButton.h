/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   DescriptionButton.h
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
#pragma once
#ifndef DescriptionButton_H
#define DescriptionButton_H

#include "GameObject.h"
#include "Button.h"
//#include "System.h"

typedef class Graphics_Manager Graphics_Manager;
typedef enum UNIT_TYPES UNIT_TYPES;
typedef class Level Level;
class DescriptionButton : public Button 
{
protected:
	GameObject* description_;				// description box for explanation on item
public:
	// Default Constructor
	DescriptionButton();
	// Non-default Constructor
	DescriptionButton(float x, float y, float scale_x, float scale_y, UNIT_TYPES type, float texture_width = 0.0f, OBJECT_TYPES = BUTTONS);
	// destructor
	virtual ~DescriptionButton();
	// update
	virtual void Update ();
	// draw
	virtual void Draw();
	// setter for active
	void Set_Active(ACTIVE a);
	// getter for description
	GameObject * Get_Description();
	// setter for description
	void Set_Description(GameObject *);
};
#endif DescriptionButton_H
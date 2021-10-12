/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   MojoButton.h
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
#ifndef MojoButton_H
#define MojoButton_H

#include "GameObject.h"
#include "Button.h"

typedef class Graphics_Manager Graphics_Manager;
typedef enum UNIT_TYPES UNIT_TYPES;
typedef class Level Level;
class MojoButton : public Button
{
protected:
	f64			active_multiplier_;				// to change textures to show it's time to upgrade
public:
	// Constructor
	MojoButton();
	// non-default constructor
	MojoButton(float x, float y, float scale_x, float scale_y, UNIT_TYPES type, float texture_width = 0.0f, float texture_start = 0.0f);
	// destructor
	virtual ~MojoButton();
	// updates
	virtual void Update();
	// draws
	virtual void Draw();
	// setter for active
	virtual void Set_Active(ACTIVE a);
	// getter for active
	ACTIVE Get_Active();

};
#endif MojoButton_H
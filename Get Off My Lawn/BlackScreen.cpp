/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   BlackScreen.cpp
\author Wong Zhihao		(100%)
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login:zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the algorithmn for black screens (for fading and tinting)

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "BlackScreen.h"	// Function and class declarations
#include "RenderManager.h"	// Render object

/******************************************************************************/
/*!
Constructor for the black screen
*/
/******************************************************************************/
BlackScreen::BlackScreen(SIDES side, float x, float y, float scale_x, float scale_y, OBJECT_TYPES object_type, UNIT_TYPES unit_type, f32 angle_)
	:
	// Construct the gameobject first
	GameObject(
		side,
		x, y,
		scale_x,
		scale_y,
		object_type,
		unit_type,
		angle_
	),

	// Set default properties
	is_fading_{false},
	render_type_{true},
	transparency_{1.0f}

{
	// If its a tint, set transparent
	if (object_type == TYPE_BLACK_SCREEN_TINT)
		transparency_ = 0;
}

/******************************************************************************/
/*!
Update function for Black Screen
*/
/******************************************************************************/
void BlackScreen::Update()
{
	// Check if it is fading
	if (is_fading_)
	{
		// Modify transparency
		transparency_ += transparency_modifier_;

		// If fully transparent, set to 0 and make it not fading
		if (transparency_ < 0)
		{
			transparency_ = 0;
			is_fading_ = false;
			render_type_ = false;
		}

		// Else same for opaque
		else if (transparency_ > 1.0f)
		{
			transparency_ = 1.0f;
			is_fading_ = false;
			render_type_ = true;
		}
	}

	// Security check
	else if (is_fading_ == false && transparency_ >= 1.0f)
	{
		Initiate_Fade_Black_Screen(false);
	}
}

/******************************************************************************/
/*!
Draw Black Screen
*/
/******************************************************************************/
void BlackScreen::Draw()
{
	Render_Object(*this);
}

/******************************************************************************/
/*!
Initiate Black screen to fade to black or fade out from black based on bool fade_type
*/
/******************************************************************************/
void BlackScreen::Initiate_Fade_Black_Screen(bool fade_type)
{
	// Set it to fade more opaque or transparent
	if (fade_type)
		transparency_modifier_ = 0.02f;
	
	else transparency_modifier_ = -0.04f;

	is_fading_ = true;
}

/******************************************************************************/
/*!
Set Black Screen to be tinted half opaque black
*/
/******************************************************************************/
void BlackScreen::Set_Black_Tint_Screen(bool pause_type)
{
	if (pause_type == true)
		transparency_ = 0.5f;

	else transparency_ = 0;
}

bool BlackScreen::Get_Is_Fading() const
{
	return is_fading_;
}

bool BlackScreen::Get_Render_Type() const
{
	return render_type_;
}

float BlackScreen::Get_Transparency() const
{
	return transparency_;
}
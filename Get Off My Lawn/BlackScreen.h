/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   BlackScreen.h
\author Wong Zhihao(100%)
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login:zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the algorithmn for black screens (for fading and tinting).

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef BLACKSCREEN_H
#define BLACKSCREEN_H

#include "GameObject.h"	// Inherits from GameObject

class BlackScreen : public GameObject
{
protected:
	bool is_fading_;				// True if screen is in the process of fading in or out
	bool render_type_;				// Set to true to let object manager render, else set to false to let pause state render. Object manager only renders when fading out.
	float transparency_;			// Transparency amount. 1 is opaque, 2 is transparent
	float transparency_modifier_;	// Amount to alter transparency by every frame when fading

public:

	BlackScreen(
		// GameObject variables
		SIDES side,					// Grandma or Kid?
		float x, float y,			// Spawn position
		float scale_x,				// Scale of the unit (x)
		float scale_y,				// Scale of the unit (y)
		OBJECT_TYPES object_type,	// What kind of object it is
		UNIT_TYPES unit_type,		// What type of unit it is
		f32 angle_ = 0.0f
	);

	void Update();

	void Draw();
	
	// Fades the entire screen, true to fade to black, false to fade out from black
	void Initiate_Fade_Black_Screen(bool);

	// Sets the screen to be tinted black, true to tint, false to untint
	void Set_Black_Tint_Screen(bool pause_type);

	bool Get_Is_Fading() const;
	bool Get_Render_Type() const;
	float Get_Transparency() const;
};

#endif
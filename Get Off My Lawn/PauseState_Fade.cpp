/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   PauseState_Fade.cpp
\author Wong Zhihao			(100%)
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the algorithmn to show a fading screen whenever needed

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "PauseState_Fade.h"
#include "LogicComponents.h"
#include "BlackScreen.h"

/******************************************************************************/
/*!
				Loads the Graphics for Fade
*/
/******************************************************************************/
void PauseStateFade_Load()
{
	logic_components.object_manager->Initiate_Fade_Black_Screen(true);
}
/******************************************************************************/
/*!
				Update for Fade
*/
/******************************************************************************/

void PauseStateFade_Update()
{
	if (logic_components.object_manager->Get_Black_Screen(true)->Get_Is_Fading() == false)
	{
		logic_components.pause_state_manager->Set_Unpause();
	}

	logic_components.object_manager->Update_Black_Screens();
}
/******************************************************************************/
/*!
			Draws for Defeat
*/
/******************************************************************************/

void PauseStateFade_Draw()
{
	logic_components.object_manager->Draw_Black_Screens();
	logic_components.object_manager->Get_Cursor()->Draw();
}

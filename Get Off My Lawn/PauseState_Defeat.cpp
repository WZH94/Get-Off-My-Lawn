/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   PauseState_Deafeat.cpp
\author Ngm Hui Min, Lois (100%)
\par    email: lois.ngm\@digipen.edu
\par    DigiPen login: lois.ngm
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the algorithmn for when the player gets defeated by
the enemies/kids

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "PauseState_Defeat.h"
#include "LogicComponents.h"
#include "SystemComponents.h"
#include "RenderManager.h"
#include "Button.h"
#include "Input.h"
#include "GameStateList.h"

/******************************************************************************/
/*!
				Loads the Graphics for Defeat
*/
/******************************************************************************/
void PauseStateDefeat_Load()
{
	logic_components.object_manager->Set_Black_Tint_Screen(true);
	system_components.audio_manager->Set_Pause_Volume(true);
	GameObject * game_stat = new GameObject{ NONE, 0.0f, 0.0f, 500.0f, 500.0f, GENERAL, GAME_STAT };
	logic_components.object_manager->Insert_Pause_Object(game_stat);
	game_stat->Set_Texture_Change(0.25f);
	GameObject * button_level_select = new Button{ -100.0f, -125.0f, 75.0f, 75.0f, BUTTON_LEVEL_SELECT, 0.25f };
	logic_components.object_manager->Insert_Pause_Object(button_level_select);
	GameObject * button_restart = new Button{ 0.0f , -125.0f, 75.0f, 75.0f, BUTTON_RESTART_2, 0.25f };
	logic_components.object_manager->Insert_Pause_Object(button_restart);
	GameObject * button_shop = new Button{ 100.0f , -125.0f, 75.0f, 75.0f, BUTTON_SHOP, 0.25f };
	logic_components.object_manager->Insert_Pause_Object(button_shop);

}

/******************************************************************************/
/*!
			Updates for Defeat
*/
/******************************************************************************/
void PauseStateDefeat_Update()
{
	logic_components.object_manager->Update_Pause_Objects();
	for (unsigned i = 0; i < logic_components.object_manager->Get_Size_Pause_Object_List(); ++i)
	{
		GameObject * all_type_button = logic_components.object_manager->Get_Pause_Object(i);
		Button * button = dynamic_cast<Button*>(all_type_button);
		if (button != nullptr)
		{
			if (Cursor_Box_Collision(button))
			{
				if (button->Get_Active() != CLICK)
					button->Set_Active(HOVER);
				if (AEInputCheckCurr(AEVK_LBUTTON))
					button->Set_Active(CLICK);
				if (AEInputCheckReleased(AEVK_LBUTTON))
				{
					switch (button->Get_Unit_Type())
					{
					case BUTTON_LEVEL_SELECT:
					{
						gAEGameStateNext = GS_LEVELSELECT;
						break;
					}
					case BUTTON_RESTART_2:
						gAEGameStateCurr = AE_GS_RESTART;
						break;
					case BUTTON_SHOP:
						gAEGameStateNext = GS_SHOP;
						break;
					}
					system_components.audio_manager->Play_Sound(SFX_BUTTON_CLICK);
					logic_components.object_manager->Set_Black_Tint_Screen(false);
					system_components.audio_manager->Set_Pause_Volume(false);
					logic_components.pause_state_manager->Set_Pause(PAUSE_FADE);
				}
			}
			else
				button->Set_Active(INACTIVE);
		}
	}

}
/******************************************************************************/
/*!
				Draws for Defeat
*/
/******************************************************************************/

void PauseStateDefeat_Draw()
{
	logic_components.object_manager->Draw_Black_Screens();
	logic_components.object_manager->Draw_Pause_Objects();
}

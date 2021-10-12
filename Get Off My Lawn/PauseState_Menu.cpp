/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   PauseState_Menu.cpp
\author Wong Zhihao						(50%)| Ngm Hui Min, Lois(50%)
\par    email: zhihao.wong\@digipen.edu | lois.ngm\@digipen.edu
\par    DigiPen login: zhihao.wong		| lois.ngm
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the algorithmn to show the pause menu when pause is clicked
or when pause is invoked by keyboard shortcuts

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "PauseState_Menu.h"
#include "LogicComponents.h"
#include "SystemComponents.h"
#include "RenderManager.h"
#include "Button.h"
#include "Input.h"
#include "GameStateList.h"

/******************************************************************************/
/*!
Loads the Graphics for Pause Menu
*/
/******************************************************************************/
void PauseStateMenu_Load()
{
	// black tint screen
	logic_components.object_manager->Set_Black_Tint_Screen(true);
	// mute volume
	system_components.audio_manager->Set_Pause_Volume(true);

	// pause menu window
	GameObject * game_stat = new GameObject{ NONE, 0.0f, 0.0f, 500.0f, 500.0f, GENERAL, GAME_STAT };
	game_stat->Set_Texture_Change(0.5f);
	logic_components.object_manager->Insert_Pause_Object(game_stat);

	// buttons
	GameObject * button_resume = new Button{ -100.0f, -90.0f, 150.0f, 75.0f, BUTTON_RESUME, 0.25f };
	logic_components.object_manager->Insert_Pause_Object(button_resume);

	GameObject * button_restart = new Button{ 100.0f, -90.0f, 150.0f, 75.0f, BUTTON_RESTART, 0.25f };
	logic_components.object_manager->Insert_Pause_Object(button_restart);

	GameObject * button_quit = new Button{ 0.0f, -190.0f, 150.0f, 75.0f, BUTTON_QUIT, 0.25f };
	logic_components.object_manager->Insert_Pause_Object(button_quit);

	GameObject * button_music = new Button{ -60.0f, 45.0f, 50.0f, 50.0f, BGM_BUTTON, 1.0f / 6.0f };
	logic_components.object_manager->Insert_Pause_Object(button_music);
	GameObject * button_sfx = new Button{ 60.0f, 45.0f, 50.0f, 50.0f, SFX_BUTTON, 1.0f / 6.0f };
	logic_components.object_manager->Insert_Pause_Object(button_sfx);
	GameObject * button_fullscreen = new Button{ 60.0f, -10.0f, 50.0f, 50.0f, FULLSCREEN_BUTTON, 1.0f / 6.0f };
	logic_components.object_manager->Insert_Pause_Object(button_fullscreen);


	// confirmation window (for when "quit game" is clicked)
	GameObject * confirmation = new GameObject{ NONE, 0.0f, 0.0f, 300.0f, 300.0f, GENERAL, CONFIRMATION };
	confirmation->Set_Alive(false);
	logic_components.object_manager->Insert_Pause_Object(confirmation);

	// buttons
	GameObject * button_y = new Button{ -100.0f, -50.0f, 50.0f, 50.0f, BUTTON_Y, 0.25f};
	button_y->Set_Alive(false);
	Button * button = dynamic_cast<Button *>(button_y);
	button->Set_Active(PAUSED);
	logic_components.object_manager->Insert_Pause_Object(button_y);
	GameObject * button_n = new Button{ 100.0f, -50.0f, 50.0f, 50.0f, BUTTON_N, 0.25f };
	button_n->Set_Alive(false);
	button = dynamic_cast<Button *>(button_n);
	button->Set_Active(PAUSED);
	logic_components.object_manager->Insert_Pause_Object(button_n);
}

/******************************************************************************/
/*!
				Updates for pause Menu
*/
/******************************************************************************/
void PauseStateMenu_Update()
{
	logic_components.object_manager->Update_Pause_Objects();

	if (AEInputCheckTriggered(AEVK_P) || AEInputCheckTriggered(AEVK_ESCAPE))
	{
		logic_components.pause_state_manager->Set_Unpause();
		logic_components.object_manager->Set_Black_Tint_Screen(false);
		system_components.audio_manager->Set_Pause_Volume(false);
		system_components.audio_manager->Play_Sound(SFX_BUTTON_CLICK);
	}

	for (unsigned i = 0; i < logic_components.object_manager->Get_Size_Pause_Object_List(); ++i)
	{
		GameObject * all_type_button = logic_components.object_manager->Get_Pause_Object(i);
		Button * button = dynamic_cast<Button*>(all_type_button);
		if (button != nullptr) 
		{
			// Set Textures accordingly
			if (button->Get_Unit_Type() == FULLSCREEN_BUTTON)
			{
				if (button->Get_Start_Texture() != 0.5f && full_screen)
					button->Set_Start_Texture(0.5f);
				else if (button->Get_Start_Texture() != 0.0f && !full_screen)
					button->Set_Start_Texture(0.0f);
			}
			if (button->Get_Unit_Type() == BGM_BUTTON)
			{
				if (button->Get_Start_Texture() != 0.5f && system_components.audio_manager->Get_Music_Mute())
					button->Set_Start_Texture(0.5f);
				else if (button->Get_Start_Texture() != 0.0f && !system_components.audio_manager->Get_Music_Mute())
					button->Set_Start_Texture(0.0f);
			}
			if (button->Get_Unit_Type() == SFX_BUTTON)
			{
				if (button->Get_Start_Texture() != 0.5f && system_components.audio_manager->Get_SFX_Mute())
					button->Set_Start_Texture(0.5f);
				else if (button->Get_Start_Texture() != 0.0f && !system_components.audio_manager->Get_SFX_Mute())
					button->Set_Start_Texture(0.0f);
			}
			// if button is paused do not enter
			if (button->Get_Active() != PAUSED)
			{
				// input handler
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
						case BUTTON_RESUME:
						{
							logic_components.pause_state_manager->Set_Unpause();
							logic_components.object_manager->Set_Black_Tint_Screen(false);
							system_components.audio_manager->Set_Pause_Volume(false);
							system_components.audio_manager->Play_Sound(SFX_BUTTON_CLICK);
							break;
						}
						case BUTTON_RESTART:
							gAEGameStateNext = AE_GS_RESTART;
							break;
						case BUTTON_QUIT:
						{
							for (unsigned j = 0; j < logic_components.object_manager->Get_Size_Pause_Object_List(); ++j)
							{
								GameObject * all_type = logic_components.object_manager->Get_Pause_Object(j);
								if (all_type->Get_Unit_Type() == CONFIRMATION) all_type->Set_Alive(true);
								Button * button2 = dynamic_cast<Button*>(all_type);
								if (button2) {
									if (button2->Get_Unit_Type() != BUTTON_Y && button2->Get_Unit_Type() != BUTTON_N)
									{
										button2->Set_Active(PAUSED);
										button2->Set_Alive(false);
										continue;

									}
									button2->Set_Active(UNPAUSE);
									button2->Set_Alive(true);
								}
							}
							break;
						}
						break;
						case BGM_BUTTON:
							if (button->Get_Start_Texture() == 0.0f)
								button->Set_Start_Texture(0.5f);
							else
								button->Set_Start_Texture(0.0f);
							system_components.audio_manager->Mute_Music();
							break;
						case SFX_BUTTON:
							if (button->Get_Start_Texture() == 0.0f)
								button->Set_Start_Texture(0.5f);
							else
								button->Set_Start_Texture(0.0f);
							system_components.audio_manager->Mute_SFX();
							break;
						case FULLSCREEN_BUTTON:
							if (button->Get_Start_Texture() == 0.0f)
							{
								button->Set_Start_Texture(0.5f);
								AEToogleFullScreen(true);
								full_screen = true;
							}
							else
							{
								button->Set_Start_Texture(0.0f);
								AEToogleFullScreen(false);
								full_screen = false;
							}
							break;
						case BUTTON_Y:
						{
							gAEGameStateNext = GS_LEVELSELECT;
							break;
						}
						case BUTTON_N:
						{
							for (unsigned j = 0; j < logic_components.object_manager->Get_Size_Pause_Object_List(); ++j)
							{
								GameObject * all_type = logic_components.object_manager->Get_Pause_Object(j);
								if (all_type->Get_Unit_Type() == CONFIRMATION) all_type->Set_Alive(false);
								Button * button2 = dynamic_cast<Button*>(all_type);
								if (button2)
								{
									if (button2->Get_Unit_Type() != BUTTON_Y && button2->Get_Unit_Type() != BUTTON_N)
									{
										button2->Set_Active(UNPAUSE);
										button2->Set_Alive(true);
										continue;

									}
									button2->Set_Active(PAUSED);
									button2->Set_Alive(false);
								}
							}
							break;
						}
						}
						if (button->Get_Unit_Type() == BUTTON_RESUME) {
							logic_components.pause_state_manager->Set_Unpause();
							logic_components.object_manager->Set_Black_Tint_Screen(false);
							system_components.audio_manager->Set_Pause_Volume(false);
						}
						else if (button->Get_Unit_Type() != FULLSCREEN_BUTTON &&
							button->Get_Unit_Type() != BGM_BUTTON &&
							button->Get_Unit_Type() != SFX_BUTTON && button->Get_Unit_Type() != BUTTON_QUIT && button->Get_Unit_Type() != BUTTON_N)
						{
							logic_components.object_manager->Set_Black_Tint_Screen(false);
							system_components.audio_manager->Set_Pause_Volume(false);
							system_components.audio_manager->Initiate_Fade_Music(MUSIC_LEVEL, false);
							logic_components.pause_state_manager->Set_Pause(PAUSE_FADE);
						}
						system_components.audio_manager->Play_Sound(SFX_BUTTON_CLICK);
					}
				}
				else
					button->Set_Active(INACTIVE);
			}
		}
	}
}

/******************************************************************************/
/*!
				Draws for Pause Menu
*/
/******************************************************************************/
void PauseStateMenu_Draw()
{
	logic_components.object_manager->Draw_Black_Screens();
	//logic_components.object_manager->Draw_Game_Stat();
	//Print_Text(system_components.font_manager_->Get_Font(F_GAME_UI_TEXT), "PAUSED", (int)AEGfxGetWinMaxX() - 600, (int)AEGfxGetWinMaxY() - 300, 1.0f, 1.0f, 0);

	// DRAW PAUSE OBJECTS
	logic_components.object_manager->Draw_Pause_Objects();
}

/******************************************************************************/
/*!
\game Get Off My Lawn!
\file   Input.h
\author Ngm Hui Min, Lois		(90%)			| Tan Zhi Quan (10%)
\par    email: lois.ngm\@digipen.edu			| zhiquan.tan\@digipen.edu
\par    DigiPen login: lois.ngm					| zhiquan.tan
\par    Course: GAM150
\date	13/04/18
\brief
This file handles all input in the game

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Input.h"
#include "LevelData.h"
#include "ObjectSpawner.h"
#include "Players.h"
#include "LogicComponents.h"
#include "ObjectList.h"
#include "RenderManager.h"
#include "TowerNode.h"
#include "main.h"
#include "SystemComponents.h"
#include "GameStateList.h"
#include "PlayerData.h"
#include "DescriptionButton.h"
#include "Button.h"
#include "MojoButton.h"
#include "SoldierButton.h"
#include "TowerNodeButton.h"
#include <Windows.h>
#include <vector>
void Input_Handle_Granny_Tower_Nodes()
{
	for (unsigned i = 0; i < logic_components.object_manager->Get_Size_Button_List(); ++i)
	{
		GameObject * game_object_button = logic_components.object_manager->Get_Button(i);
		TowerNodeButton * button = dynamic_cast<TowerNodeButton*>(game_object_button);
		if (!button) continue;
		if (button->Get_Active() != BOUGHT)
		{
			if (Cursor_Box_Collision_Camera(button))
			{
				// tower node
				if (button->Get_Alive())
				{
					if (button->Get_Active() != CLICK && button->Get_Active() != RELEASED)
						button->Set_Active(HOVER);
					if (AEInputCheckCurr(AEVK_LBUTTON) && button->Get_Active() != RELEASED)
						button->Set_Active(CLICK);
					if (AEInputCheckReleased(AEVK_LBUTTON))
					{
						button->Set_Active(RELEASED);
						system_components.audio_manager->Play_Sound(SFX_TOWER_NODE_SELECT);
					}
				}
			}
			else if (button->Get_Active() != RELEASED || AEInputCheckTriggered(AEVK_LBUTTON) && button->Get_Active() != INACTIVE)
			{
				button->Set_Active(INACTIVE);
				
			}
		}
	}
}

bool Input_Handle_Granny_Tower_Nodes(char tutorial)
{
	UNREFERENCED_PARAMETER(tutorial);
	for (unsigned i = 0; i < logic_components.object_manager->Get_Size_Button_List(); ++i)
	{
		GameObject * game_object_button = logic_components.object_manager->Get_Button(i);
		TowerNodeButton * button = dynamic_cast<TowerNodeButton*>(game_object_button);
		if (!button) continue;
		if (button->Get_Active() != BOUGHT)
		{
			if (Cursor_Box_Collision_Camera(button))
			{
				// tower node
				if (button->Get_Alive())
				{
					if (button->Get_Active() != CLICK && button->Get_Active() != RELEASED)
						button->Set_Active(HOVER);
					if (AEInputCheckCurr(AEVK_LBUTTON) && button->Get_Active() != RELEASED)
						button->Set_Active(CLICK);
					if (AEInputCheckReleased(AEVK_LBUTTON))
					{
						button->Set_Active(RELEASED);
						system_components.audio_manager->Play_Sound(SFX_BUTTON_CLICK);
					}
				}
			}
			else if (button->Get_Active() != RELEASED || AEInputCheckTriggered(AEVK_LBUTTON))
				button->Set_Active(INACTIVE);
		}
		if (button->Get_Active() == BOUGHT)
			return true;
	}
	return false;
}
bool Cursor_Box_Collision_Camera(Button* button)
{
	float cursorX = system_components.cursor_position_->Get_Cursor_Position().x;
	float cursorY = system_components.cursor_position_->Get_Cursor_Position().y;

	if (cursorY >= -122.0f || (cursorY >= -150.0f && cursorY <= -123.0f && (cursorX <= -550.0f || cursorX >= 550.0f)))
	{
		float buttonX = button->Get_x();
		float buttonY = button->Get_y();
		float scaleX = button->Get_Scale_X() / 2.0f;
		float scaleY = button->Get_Scale_Y() / 2.0f;

		if (button->Get_Unit_Type() >= G_TOWER_NODE1 && button->Get_Unit_Type() <= G_TOWER_NODE4)
		{
			scaleX = 50.0f;
			scaleY = 50.0f;
		}



		float cameraPosX = logic_components.camera->Get_Camera_Position().x;
		float cameraPosY = logic_components.camera->Get_Camera_Position().y;
		float camera_zoom = logic_components.camera->Get_Zoom();


		if (cursorX >= -cameraPosX + (buttonX - scaleX) * camera_zoom &&
			cursorX <= -cameraPosX + (buttonX + scaleX) * camera_zoom &&
			cursorY >= -cameraPosY + (buttonY - scaleY) * camera_zoom &&
			cursorY <= -cameraPosY + (buttonY + scaleY) * camera_zoom)
		{
			return true;
		}

		return false;
	}

	else return false;
}
bool Cursor_Box_Collision(Button* button)
{
	float cursorX = system_components.cursor_position_->Get_Cursor_Position().x;
	float cursorY = system_components.cursor_position_->Get_Cursor_Position().y;
	float buttonX = button->Get_x();
	float buttonY = button->Get_y();
	float scaleX = button->Get_Scale_X() / 2.0f;
	float scaleY = button->Get_Scale_Y() / 2.0f;

	if (cursorX >= buttonX - scaleX && cursorX <= buttonX + scaleX &&
		cursorY >= buttonY - scaleY && cursorY <= buttonY + scaleY)
		return true;
	else
		return false;
}

void Input_Handle_In_Game_Commands()
{
	if (AEInputCheckTriggered(AEVK_A))
	{
		Spawn_Object(K_S_SABOTEUR, 500.0f, 0.0f);
	}

	if (AEInputCheckCurr(AEVK_UP))
		logic_components.camera->Set_Zoom(true);

	if (AEInputCheckCurr(AEVK_DOWN))
		logic_components.camera->Set_Zoom(false);

	if (AEInputCheckTriggered(AEVK_P) || AEInputCheckTriggered(AEVK_ESCAPE))
	{
		system_components.audio_manager->Play_Sound(SFX_BUTTON_CLICK);
		logic_components.pause_state_manager->Set_Pause(PAUSE_MENU);
	}

	if (AEInputCheckTriggered(AEVK_TAB))
	{
		if (system_components.framerate_manager->Get_Time_Multiplier() == 1)
			system_components.framerate_manager->Set_Time_Multiplier(true);

		else system_components.framerate_manager->Set_Time_Multiplier(false);
	}

	if (AEInputCheckTriggered(AEVK_RBUTTON))
		Spawn_Object(K_P_ATTACKSPEEDUP, 0, 0);

	if (AEInputCheckTriggered(AEVK_COMMA))
	{
		logic_components.level_data->players->Damage_Grandma_Base();
		logic_components.object_manager->Activate_Particle_Emitter(PARTICLE_SMOKE, 0.0f, 0.0f, 100.0f, 0.3f);
		logic_components.object_manager->Activate_Particle_Emitter(PARTICLE_RUBBLE, 0.0f, 100.0f, 100.0f, 1.0f);
	}


	if (AEInputCheckTriggered(AEVK_U))
	{
		logic_components.level_data->players->Damage_Kid_Base(1);
		logic_components.object_manager->Activate_Particle_Emitter(PARTICLE_SMOKE, 0.0f, 0.0f, 100.0f, 0.3f);
		logic_components.object_manager->Activate_Particle_Emitter(PARTICLE_RUBBLE, 0.0f, 100.0f, 100.0f, 1.0f);
	}

//	if (AEInputCheckReleased(AEVK_RBUTTON))
//	{
//		Spawn_Object(G_S_SHOOTER, -400.0f, 0.0f);
//		Spawn_Object(K_S_SHOOTER, 450.0f, 0.0f);
//	}
}

void Input_Handle_Soldiers()
{
	for (unsigned i = 0; i < logic_components.object_manager->Get_Size_Button_List(); ++i)
	{
		GameObject * all_type_button = logic_components.object_manager->Get_Button(i);
		SoldierButton * button = dynamic_cast<SoldierButton*>(all_type_button);
		if (button == nullptr) continue;
		// Keyboard Input
		switch (button->Get_Unit_Type())
		{
		case G_BUTTON_1:
			if (button->Get_Active() == LOCKED && AEInputCheckTriggered(AEVK_1))
				system_components.audio_manager->Play_Sound(SFX_BUTTON_INVALID);

			else if (logic_components.level_data->players->Get_Granny_Mojo() >= 10 && AEInputCheckTriggered(AEVK_1) && button->Get_Active() != LOCKED)
			{
				Spawn_Object(G_S_SHOOTER, -400.0f, 0.0f);
				logic_components.level_data->players->Set_Granny_Mojo(-10);
				button->Set_Countdown_Timer(3.0f);
				system_components.audio_manager->Play_Sound(SFX_GRANDMA_BUTTON_SPAWN);
			}
			break;
		case G_BUTTON_2:
			if (button->Get_Active() == LOCKED && AEInputCheckTriggered(AEVK_2))
				system_components.audio_manager->Play_Sound(SFX_BUTTON_INVALID);

			else if (logic_components.level_data->players->Get_Granny_Mojo() >= 20 && AEInputCheckTriggered(AEVK_2) && button->Get_Active() != LOCKED)
			{
				Spawn_Object(G_S_TANK, -400.0f, 0.0f);
				logic_components.level_data->players->Set_Granny_Mojo(-20);
				button->Set_Countdown_Timer(5.0f);
				system_components.audio_manager->Play_Sound(SFX_GRANDMA_BUTTON_SPAWN);
			}
			break;
		case G_BUTTON_3:
			if (button->Get_Active() == LOCKED && AEInputCheckTriggered(AEVK_3))
				system_components.audio_manager->Play_Sound(SFX_BUTTON_INVALID);

			else if (logic_components.level_data->players->Get_Granny_Mojo() >= 20 && AEInputCheckTriggered(AEVK_3) && button->Get_Active() != LOCKED)
			{
				Spawn_Object(G_S_SPEED, -400.0f, 0.0f);
				logic_components.level_data->players->Set_Granny_Mojo(-20);
				button->Set_Countdown_Timer(3.0f);
				system_components.audio_manager->Play_Sound(SFX_GRANDMA_BUTTON_SPAWN);
			}
			break;
		case G_BUTTON_4:
			if (button->Get_Active() == LOCKED && AEInputCheckTriggered(AEVK_4))
				system_components.audio_manager->Play_Sound(SFX_BUTTON_INVALID);

			else if (logic_components.level_data->players->Get_Granny_Mojo() >= 35 && AEInputCheckTriggered(AEVK_4) && button->Get_Active() != LOCKED)
			{
				Spawn_Object(G_S_SABOTEUR, -400.0f, 0.0f);
				logic_components.level_data->players->Set_Granny_Mojo(-35);
				button->Set_Countdown_Timer(5.0f);
				system_components.audio_manager->Play_Sound(SFX_GRANDMA_BUTTON_SPAWN);
			}
			break;
		case G_BUTTON_5:
			if (button->Get_Active() == LOCKED && AEInputCheckTriggered(AEVK_5))
				system_components.audio_manager->Play_Sound(SFX_BUTTON_INVALID);

			else if (logic_components.level_data->players->Get_Granny_Mojo() >= 50 && AEInputCheckTriggered(AEVK_5) && button->Get_Active() != LOCKED)
			{
				Spawn_Object(G_S_SLOW, -400.0f, 0.0f);
				logic_components.level_data->players->Set_Granny_Mojo(-50);
				button->Set_Countdown_Timer(8.0f);
				system_components.audio_manager->Play_Sound(SFX_GRANDMA_BUTTON_SPAWN);
			}
			break;
		case G_BUTTON_6:
			if (button->Get_Active() == LOCKED && AEInputCheckTriggered(AEVK_6))
				system_components.audio_manager->Play_Sound(SFX_BUTTON_INVALID);

			else if (logic_components.level_data->players->Get_Granny_Mojo() >= 100 && AEInputCheckTriggered(AEVK_6) && button->Get_Active() != LOCKED)
			{
				Spawn_Object(G_S_ATTACKSPEEDUP, -400.0f, 0.0f);
				logic_components.level_data->players->Set_Granny_Mojo(-100);
				button->Set_Countdown_Timer(10.0f);
				system_components.audio_manager->Play_Sound(SFX_GRANDMA_BUTTON_SPAWN);
			}
			break;
		case G_BUTTON_7:
			if (button->Get_Active() == LOCKED && AEInputCheckTriggered(AEVK_7))
				system_components.audio_manager->Play_Sound(SFX_BUTTON_INVALID);

			else if (logic_components.level_data->players->Get_Granny_Mojo() >= 75 && AEInputCheckTriggered(AEVK_7) && button->Get_Active() != LOCKED)
			{
				Spawn_Object(G_S_STUN, -400.0f, 0.0f);
				logic_components.level_data->players->Set_Granny_Mojo(-75);
				button->Set_Countdown_Timer(8.0f);
				system_components.audio_manager->Play_Sound(SFX_GRANDMA_BUTTON_SPAWN);
			}
			break;
		case G_BUTTON_8:
			if (button->Get_Active() == LOCKED && AEInputCheckTriggered(AEVK_8))
				system_components.audio_manager->Play_Sound(SFX_BUTTON_INVALID);

			else if (logic_components.level_data->players->Get_Granny_Mojo() >= 80 && AEInputCheckTriggered(AEVK_8) && button->Get_Active() != LOCKED)
			{
				Spawn_Object(G_S_HEALER, -400.0f, 0.0f);
				logic_components.level_data->players->Set_Granny_Mojo(-80);
				button->Set_Countdown_Timer(12.0f);
				system_components.audio_manager->Play_Sound(SFX_GRANDMA_BUTTON_SPAWN);
			}
			break;
		case G_BUTTON_9:
			if (button->Get_Active() == LOCKED && AEInputCheckTriggered(AEVK_9))
				system_components.audio_manager->Play_Sound(SFX_BUTTON_INVALID);

			else if (logic_components.level_data->players->Get_Granny_Mojo() >= 50 && AEInputCheckTriggered(AEVK_9) && button->Get_Active() != LOCKED)
			{
				Spawn_Object(G_S_ATTACKBUFF, -400.0f, 0.0f);
				logic_components.level_data->players->Set_Granny_Mojo(-90);
				button->Set_Countdown_Timer(15.0f);
				system_components.audio_manager->Play_Sound(SFX_GRANDMA_BUTTON_SPAWN);
			}
			break;
		}

		// Mouse Input
		if (Cursor_Box_Collision(button))
		{
			if (button->Get_Active() == LOCKED && !button->Get_Description()->Get_Alive())
				button->Get_Description()->Set_Alive(true);

			if (button->Get_Active() == LOCKED)
			{
				if (AEInputCheckTriggered(AEVK_LBUTTON))
					system_components.audio_manager->Play_Sound(SFX_BUTTON_INVALID);
			}

			else if (button->Get_Active() != LOCKED)
			{
				if (button->Get_Active() != CLICK)
					button->Set_Active(HOVER);
				if (AEInputCheckCurr(AEVK_LBUTTON))
					button->Set_Active(CLICK);
				if (AEInputCheckReleased(AEVK_LBUTTON))
				{
					switch (button->Get_Unit_Type())
					{
					case G_BUTTON_1:
						if (logic_components.level_data->players->Get_Granny_Mojo() >= 10)
						{
							Spawn_Object(G_S_SHOOTER, -400.0f, 0.0f);
							logic_components.level_data->players->Set_Granny_Mojo(-10);
							button->Set_Countdown_Timer(3.0f);
						}
						break;
					case G_BUTTON_2:
						if (logic_components.level_data->players->Get_Granny_Mojo() >= 20) {
							Spawn_Object(G_S_TANK, -400.0f, 0.0f);
							logic_components.level_data->players->Set_Granny_Mojo(-20);
							button->Set_Countdown_Timer(5.0f);
						}
						break;
					case G_BUTTON_3:
						if (logic_components.level_data->players->Get_Granny_Mojo() >= 20) {
							Spawn_Object(G_S_SPEED, -400.0f, 0.0f);
							logic_components.level_data->players->Set_Granny_Mojo(-20);
							button->Set_Countdown_Timer(3.0f);
						}
						break;
					case G_BUTTON_4:
						if (logic_components.level_data->players->Get_Granny_Mojo() >= 35) {
							Spawn_Object(G_S_SABOTEUR, -400.0f, 0.0f);
							logic_components.level_data->players->Set_Granny_Mojo(-35);
							button->Set_Countdown_Timer(5.0f);
						}
						break;
					case G_BUTTON_5:
						if (logic_components.level_data->players->Get_Granny_Mojo() >= 50) {
							Spawn_Object(G_S_SLOW, -400.0f, 0.0f);
							logic_components.level_data->players->Set_Granny_Mojo(-50);
							button->Set_Countdown_Timer(8.0f);
						}
						break;
					case G_BUTTON_6:
						if (logic_components.level_data->players->Get_Granny_Mojo() >= 100) {
							Spawn_Object(G_S_ATTACKSPEEDUP, -400.0f, 0.0f);
							logic_components.level_data->players->Set_Granny_Mojo(-100);
							button->Set_Countdown_Timer(10.0f);
						}
						break;
					case G_BUTTON_7:
						if (logic_components.level_data->players->Get_Granny_Mojo() >= 75) {
							Spawn_Object(G_S_STUN, -400.0f, 0.0f);
							logic_components.level_data->players->Set_Granny_Mojo(-75);
							button->Set_Countdown_Timer(8.0f);
						}
						break;
					case G_BUTTON_8:
						if (logic_components.level_data->players->Get_Granny_Mojo() >= 80) {
							Spawn_Object(G_S_HEALER, -400.0f, 0.0f);
							logic_components.level_data->players->Set_Granny_Mojo(-80);
							button->Set_Countdown_Timer(12.0f);
						}
						break;
					case G_BUTTON_9:
						if (logic_components.level_data->players->Get_Granny_Mojo() >= 90) {
							Spawn_Object(G_S_ATTACKBUFF, -400.0f, 0.0f);
							logic_components.level_data->players->Set_Granny_Mojo(-90);
							button->Set_Countdown_Timer(15.0f);
						}
						break;
					}
					system_components.audio_manager->Play_Sound(SFX_GRANDMA_BUTTON_SPAWN);
				}
			}
		}
		else if (button->Get_Active() != LOCKED)
			button->Set_Active(INACTIVE);
		else if (button->Get_Description()->Get_Alive())
			button->Get_Description()->Set_Alive(false);
	}
}
void Input_Handle_In_Game_Buttons()
{
	for (unsigned i = 0; i < logic_components.object_manager->Get_Size_Button_List(); ++i)
	{
		GameObject * all_type_button = logic_components.object_manager->Get_Button(i);
		Button * button = dynamic_cast<Button*>(all_type_button);
		if (button != nullptr) 
		{
			if (button->Get_Unit_Type() == BUTTON_PAUSE || button->Get_Unit_Type() == BUTTON_TIME_ADJUST) 
			{
				if (Cursor_Box_Collision(button))
				{
					if (button->Get_Active() != CLICK)
						button->Set_Active(HOVER);
					if (AEInputCheckCurr(AEVK_LBUTTON))
						button->Set_Active(CLICK);
					if (AEInputCheckReleased(AEVK_LBUTTON) && button->Get_Active() != PAUSED)
					{
						switch (button->Get_Unit_Type())
						{
						case BUTTON_PAUSE:
							system_components.audio_manager->Play_Sound(SFX_BUTTON_CLICK);
							logic_components.pause_state_manager->Set_Pause(PAUSE_MENU);
							gAEGameStateNext = GS_MAINMENU;
							break;
						case BUTTON_TIME_ADJUST:
							system_components.audio_manager->Play_Sound(SFX_BUTTON_CLICK);

							if (system_components.framerate_manager->Get_Time_Multiplier() == 1)
								system_components.framerate_manager->Set_Time_Multiplier(true);

							else
								system_components.framerate_manager->Set_Time_Multiplier(false);

							break;
						}
					}
				}
				else
					button->Set_Active(INACTIVE);
			}

			// Handles the adjust time button texture change based on the current time multiplier.
			if (button->Get_Unit_Type() == BUTTON_TIME_ADJUST)
			{
				if (system_components.framerate_manager->Get_Time_Multiplier() == 1)
					button->Set_Start_Texture(0.0f);

				else
					button->Set_Start_Texture(0.5f);
			}
		}
	}
}

void Input_Handle_In_Game()
{
	Input_Handle_Soldiers();
	Input_Handle_Granny_Mojo();
	Input_Handle_Granny_Tower_Nodes();
	Input_Handle_In_Game_Commands();
	Input_Handle_In_Game_Buttons();
}

void Input_Handle_Main_Menu()
{
	for (unsigned i = 0; i < logic_components.object_manager->Get_Size_Button_List(); ++i)
	{
		GameObject * all_type_button = logic_components.object_manager->Get_Button(i);
		Button * button = dynamic_cast<Button*>(all_type_button);
		if (button != nullptr) {
			if (Cursor_Box_Collision(button))
			{
				if (button->Get_Active() != CLICK)
					button->Set_Active(HOVER);
				if (AEInputCheckCurr(AEVK_LBUTTON))
					button->Set_Active(CLICK);
				if (AEInputCheckReleased(AEVK_LBUTTON) && button->Get_Active() != PAUSED)
				{
					switch (button->Get_Unit_Type())
					{
					case START_BUTTON:
						gAEGameStateNext = GS_LOADPLAYER;
						break;
					case OPTIONS_BUTTON:
						gAEGameStateNext = GS_OPTIONS;
						break;
					case CREDITS_BUTTON:
						gAEGameStateNext = GS_CREDITS;
						break;
					case QUIT_BUTTON:
					{
						logic_components.object_manager->Set_Black_Tint_Screen(true);
						for (unsigned j = 0; j < logic_components.object_manager->Get_Size_General_List(); ++j)
						{
							GameObject * game_obj_button = logic_components.object_manager->Get_General(j);
							if (!game_obj_button) continue;
							if (game_obj_button->Get_Unit_Type() == GAME_STAT)
							{
								game_obj_button->Set_Alive(true);
								break;
							}

						}
						for (unsigned k = 0; k < logic_components.object_manager->Get_Size_Button_List(); ++k)
						{
							GameObject * all_type_button2 = logic_components.object_manager->Get_Button(k);
							Button * button2 = dynamic_cast<Button*>(all_type_button2);
							if (!button2) continue;
							if (button2->Get_Unit_Type() == BUTTON_YES || button2->Get_Unit_Type() == BUTTON_NO)
							{
								button2->Set_Alive(true);
								button2->Set_Active(UNPAUSE);
								button2->Set_Active(INACTIVE);
							}
							else
								button2->Set_Active(PAUSED);
						}
					}
					break;
					case BUTTON_YES:
						gAEGameStateNext = AE_GS_QUIT;
						break;
					case BUTTON_NO:
					{
						logic_components.object_manager->Set_Black_Tint_Screen(false);
						for (unsigned j = 0; j < logic_components.object_manager->Get_Size_General_List(); ++j)
						{
							GameObject * game_obj_button = logic_components.object_manager->Get_General(j);
							if (!game_obj_button) continue;
							if (game_obj_button->Get_Unit_Type() == GAME_STAT)
							{
								game_obj_button->Set_Alive(false);
								break;
							}

						}
						for (unsigned k = 0; k < logic_components.object_manager->Get_Size_Button_List(); ++k)
						{
							GameObject * all_type_button2 = logic_components.object_manager->Get_Button(k);
							Button * button2 = dynamic_cast<Button*>(all_type_button2);
							if (!button2) continue;
							if (button2->Get_Unit_Type() == BUTTON_YES || button2->Get_Unit_Type() == BUTTON_NO)
							{
								button2->Set_Alive(false);
								button2->Set_Active(PAUSED);
							}
							else {
								button2->Set_Active(UNPAUSE);
								button2->Set_Active(INACTIVE);
							}
						}
					}
					break;
					}
					system_components.audio_manager->Play_Sound(SFX_BUTTON_CLICK);
				}
			}
			else
				button->Set_Active(INACTIVE);
		}
	}
}

void Input_Handle_Load_Player()
{
	for (unsigned i = 0; i < logic_components.object_manager->Get_Size_Button_List(); ++i)
	{
		GameObject * all_type_button = logic_components.object_manager->Get_Button(i);
		Button *button = dynamic_cast<Button*>(all_type_button);
		if (!button) return;
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
				case BACK_BUTTON:
					gAEGameStateNext = GS_MAINMENU;
					break;
				case NEW_GAME:
					if (button->Get_x() == -350.0f)
					{
						playdata.Close_Current_Open_File();
						playdata.Make_New_Save(1);
						gAEGameStateNext = GS_LEVELSELECT;
					}
					else if (button->Get_x() == 0.0f)
					{
						playdata.Close_Current_Open_File();
						playdata.Make_New_Save(2);
						gAEGameStateNext = GS_LEVELSELECT;
					}
					else if (button->Get_x() == 350.0f)
					{
						playdata.Close_Current_Open_File();
						playdata.Make_New_Save(3);
						gAEGameStateNext = GS_LEVELSELECT;
					}
					break;
				case PLAYER_1:
					playdata.Close_Current_Open_File();
					playdata.Make_New_Save(1);
					gAEGameStateNext = GS_LEVELSELECT;
					break;
				case PLAYER_2:
					playdata.Close_Current_Open_File();
					playdata.Make_New_Save(2);
					gAEGameStateNext = GS_LEVELSELECT;
					break;
				case PLAYER_3:
					playdata.Close_Current_Open_File();
					playdata.Make_New_Save(3);
					gAEGameStateNext = GS_LEVELSELECT;
					break;
				}
				system_components.audio_manager->Play_Sound(SFX_BUTTON_CLICK);
			}
		}
		else
			button->Set_Active(INACTIVE);
	}
}


void Input_Handle_Options()
{
	for (unsigned i = 0; i < logic_components.object_manager->Get_Size_Button_List(); ++i)
	{
		GameObject * all_type_button = logic_components.object_manager->Get_Button(i);
		Button *button = dynamic_cast<Button*>(all_type_button);
		if (!button) continue;
		//if(button->Get_Unit_Type() == BGM_BUTTON && system_components.audio_manager
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
		if (Cursor_Box_Collision(button))
		{
			if (button->Get_Active() != CLICK)
				button->Set_Active(HOVER);
			if (AEInputCheckCurr(AEVK_LBUTTON))
				button->Set_Active(CLICK);
			if (AEInputCheckReleased(AEVK_LBUTTON))
			{
				switch (button->Get_Unit_Type()) {
				case BACK_BUTTON:
					gAEGameStateNext = GS_MAINMENU;
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
				case DECREASE_VOLUME_BUTTON:
					// BGM
					if (button->Get_y() == 50.0f)
					{
						for (unsigned j = 0; j < logic_components.object_manager->Get_Size_General_List(); ++j)
						{
							GameObject * volume_bar = logic_components.object_manager->Get_General(j);
							if (volume_bar->Get_y() == 50.0f)
							{
								float texture_change_value = volume_bar->Get_Texture_Change() - 1.0f / 6.0f;

								system_components.audio_manager->Adjust_Music_Volume(false);

								if (texture_change_value < 0.0f) {
									volume_bar->Set_Texture_Change(0.0f);
									break;
								}
								volume_bar->Set_Texture_Change(texture_change_value);
							}
						}
					}
					// SFX
					else if (button->Get_y() == -50.0f)
					{
						for (unsigned j = 0; j < logic_components.object_manager->Get_Size_General_List(); ++j)
						{
							GameObject * volume_bar = logic_components.object_manager->Get_General(j);
							if (volume_bar->Get_y() == -50.0f)
							{
								float texture_change_value = volume_bar->Get_Texture_Change() - 1.0f / 6.0f;

								system_components.audio_manager->Adjust_SFX_Volume(false);

								if (texture_change_value < 0.0f) {
									volume_bar->Set_Texture_Change(0.0f);
									break;
								}
								volume_bar->Set_Texture_Change(texture_change_value);
							}
						}
					}
					break;
				case INCREASE_VOLUME_BUTTON:
					// BGM
					if (button->Get_y() == 50.0f)
					{
						for (unsigned j = 0; j < logic_components.object_manager->Get_Size_General_List(); ++j)
						{
							GameObject * volume_bar = logic_components.object_manager->Get_General(j);
							if (volume_bar->Get_y() == 50.0f)
							{
								float texture_change_value = volume_bar->Get_Texture_Change() + 1.0f / 6.0f;

								system_components.audio_manager->Adjust_Music_Volume(true);

								if (texture_change_value > 5.0f / 6.0f) {
									volume_bar->Set_Texture_Change(5.0f / 6.0f);
									break;
								}
								volume_bar->Set_Texture_Change(texture_change_value);
							}
						}
					}
					// SFX
					else if (button->Get_y() == -50.0f)
					{
						for (unsigned j = 0; j < logic_components.object_manager->Get_Size_General_List(); ++j)
						{
							GameObject * volume_bar = logic_components.object_manager->Get_General(j);
							if (volume_bar->Get_y() == -50.0f)
							{
								float texture_change_value = volume_bar->Get_Texture_Change() + 1.0f / 6.0f;

								system_components.audio_manager->Adjust_SFX_Volume(true);

								if (texture_change_value > 5.0f / 6.0f) {
									volume_bar->Set_Texture_Change(5.0f / 6.0f);
									break;
								}
								volume_bar->Set_Texture_Change(texture_change_value);
							}
						}
					}
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
				}
				system_components.audio_manager->Play_Sound(SFX_BUTTON_CLICK);
			}
		}
		else
			button->Set_Active(INACTIVE);
	}
}




void Input_Handle_Shop_Button()
{
	for (unsigned i = 0; i < logic_components.object_manager->Get_Size_Button_List(); ++i)
	{
		GameObject * all_type_button = logic_components.object_manager->Get_Button(i);
		Button *button = dynamic_cast<Button*>(all_type_button);
		if (!button) continue;
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
				case BACK_BUTTON:
					gAEGameStateNext = GS_LEVELSELECT;
					break;
				}
				system_components.audio_manager->Play_Sound(SFX_BUTTON_CLICK);
			}
		}
		else
			button->Set_Active(INACTIVE);
	}
}


void Input_Handle_Shop_Description_Button()
{
	for (unsigned i = 0; i < logic_components.object_manager->Get_Size_Button_List(); ++i)
	{
		GameObject * all_type_button = logic_components.object_manager->Get_Button(i);
		DescriptionButton *button = dynamic_cast<DescriptionButton*>(all_type_button);
		if (!button) continue;
		if (Cursor_Box_Collision(button))
		{
			if ((button->Get_Active() == LOCKED || button->Get_Active() == BOUGHT) && !button->Get_Description()->Get_Alive())
			{
				button->Get_Description()->Set_Alive(true);
			}


			if (button->Get_Active() != CLICK) {
				button->Set_Active(HOVER);
			}
			if (AEInputCheckCurr(AEVK_LBUTTON))
				button->Set_Active(CLICK);
			if (AEInputCheckReleased(AEVK_LBUTTON))
			{
				if (!playdata.Get_Stars_Collected())continue;
				switch (button->Get_Unit_Type())
				{
				case BUTTON_HEALTH_INCREASE:
					// TANK TIER 1
					if (button->Get_x() == -420.0f)
					{
						playdata.Buy_Tier_1(Tank);
						button->Set_Active(BOUGHT);
					}
					// SPEED TIER 1
					if (button->Get_x() == -300.0f)
					{
						playdata.Buy_Tier_1(Speed);
						button->Set_Active(BOUGHT);
					}
					if (button->Get_x() == 60.0f)
					{
						playdata.Buy_Tier_1(Bruiser);
						button->Set_Active(BOUGHT);
					}
					if (button->Get_x() == 420.0f)
					{
						playdata.Buy_Tier_1(Buff);
						button->Set_Active(BOUGHT);
					}
					break;
				case BUTTON_RANGE_INCREASE:
					if (button->Get_x() == -540.0f)
					{
						playdata.Buy_Tier_1(Shooter);
						button->Set_Active(BOUGHT);
					}
					if (button->Get_x() == -60.0f)
					{
						playdata.Buy_Tier_1(Slow);
						button->Set_Active(BOUGHT);
					}
					if (button->Get_x() == 180.0f)
					{
						playdata.Buy_Tier_1(Stun);
						button->Set_Active(BOUGHT);
					}
					if (button->Get_x() == 300.0f)
					{
						playdata.Buy_Tier_1(Heal);
						button->Set_Active(BOUGHT);
					}
					break;
				case BUTTON_NINJA_ATTACKRATE_INCREASE:
					playdata.Buy_Tier_1(Saboteur);
					button->Set_Active(BOUGHT);
					break;
				case BUTTON_MAX_CAP:
					playdata.Buy_Tier_1(Money_Rate);
					button->Set_Active(BOUGHT);
					break;
				case BUTTON_COOKIE_ATTACKRATE_INCREASE:
					if (playdata.Get_Stars_Collected() >= 2)
					{
						playdata.Buy_Tier_2(Shooter);
						button->Set_Active(BOUGHT);
					}
					break;
				case BUTTON_SPEED_INCREASE:
					if (playdata.Get_Stars_Collected() >= 2)
					{
						playdata.Buy_Tier_2(Tank);
						button->Set_Active(BOUGHT);
					}
					break;
				case BUTTON_COOLDOWN_DECREASE:
					if (playdata.Get_Stars_Collected() >= 2)
					{
						if (button->Get_x() == -300.0f)
						{
							playdata.Buy_Tier_2(Speed);
							button->Set_Active(BOUGHT);
						}
						if (button->Get_x() == -180.0f)
						{
							playdata.Buy_Tier_2(Saboteur);
							button->Set_Active(BOUGHT);
						}
					}
					break;
				case BUTTON_DAMAGE_INCREASE:
					if (playdata.Get_Stars_Collected() >= 2)
					{
						if (button->Get_x() == -60.0f)
						{
							playdata.Buy_Tier_2(Slow);
							button->Set_Active(BOUGHT);
						}
						if (button->Get_x() == 60.0f)
						{
							playdata.Buy_Tier_2(Bruiser);
							button->Set_Active(BOUGHT);
						}
						if (button->Get_x() == 180.0f)
						{
							playdata.Buy_Tier_2(Stun);
							button->Set_Active(BOUGHT);
						}
					}
					break;
				case BUTTON_HEALING_INCREASE:
					if (playdata.Get_Stars_Collected() >= 2)
					{
						playdata.Buy_Tier_2(Heal);
						button->Set_Active(BOUGHT);
					}
					break;
				case BUTTON_RANGE_INCREASE_2:
					if (playdata.Get_Stars_Collected() >= 2)
					{
						playdata.Buy_Tier_2(Buff);
						button->Set_Active(BOUGHT);
					}
					break;
				case BUTTON_COST_DECREASE:
					if (playdata.Get_Stars_Collected() >= 2)
					{
						playdata.Buy_Tier_2(Money_Rate);
						button->Set_Active(BOUGHT);
					}
					break;
				}
				system_components.audio_manager->Play_Sound(SFX_BUTTON_CLICK);
			}
		}
		else if (button->Get_Active() != LOCKED && button->Get_Active() != BOUGHT)
			button->Set_Active(INACTIVE);
		else if (button->Get_Description()->Get_Alive())
			button->Get_Description()->Set_Alive(false);
	}
}




void Input_Handle_Shop()
{
	Input_Handle_Shop_Button();
	Input_Handle_Shop_Description_Button();

}



void Input_Handle_Credits()
{
	for (unsigned i = 0; i < logic_components.object_manager->Get_Size_Button_List(); ++i)
	{
		GameObject * all_type_button = logic_components.object_manager->Get_Button(i);
		Button *button = dynamic_cast<Button*>(all_type_button);
		if (!button) return;
		if (button->Get_Unit_Type() == BACK_BUTTON)
		{
			if (Cursor_Box_Collision(button))
			{
				if (button->Get_Active() != CLICK)
					button->Set_Active(HOVER);
				if (AEInputCheckCurr(AEVK_LBUTTON))
					button->Set_Active(CLICK);
				if (AEInputCheckReleased(AEVK_LBUTTON))
				{
					gAEGameStateNext = GS_MAINMENU;
					system_components.audio_manager->Play_Sound(SFX_BUTTON_CLICK);
				}
			}
			else
				button->Set_Active(INACTIVE);
		}
	}
}


void Input_Handle_Level_Selection()
{
	for (unsigned i = 0; i < logic_components.object_manager->Get_Size_Button_List(); ++i)
	{
		//		std::cout << i << std::endl;
		GameObject * button_game_object = logic_components.object_manager->Get_Button(i);
		Button * button = dynamic_cast<Button *>(button_game_object);
		if (!button) continue;
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
				case LEVEL_1_BUTTON:
					if (!playdata.Get_Tutorial_Completion())
						gAEGameStateNext = GS_LEVEL_0;
					else gAEGameStateNext = GS_LEVEL_1;
					break;
				case LEVEL_2_BUTTON:
					gAEGameStateNext = GS_LEVEL_2;
					break;
				case LEVEL_3_BUTTON:
					gAEGameStateNext = GS_LEVEL_3;
					break;
				case LEVEL_4_BUTTON:
					gAEGameStateNext = GS_LEVEL_4;
					break;
				case LEVEL_5_BUTTON:
					gAEGameStateNext = GS_LEVEL_5;
					break;
				case LEVEL_6_BUTTON:
					gAEGameStateNext = GS_LEVEL_6;
					break;
				case LEVEL_7_BUTTON:
					gAEGameStateNext = GS_LEVEL_7;
					break;
				case LEVEL_8_BUTTON:
					gAEGameStateNext = GS_LEVEL_8;
					break;
				case LEVEL_9_BUTTON:
					gAEGameStateNext = GS_LEVEL_9;
					break;
				case LEVEL_10_BUTTON:
					gAEGameStateNext = GS_LEVEL_10;
					break;
				case BACK_BUTTON:
					gAEGameStateNext = GS_LOADPLAYER;
					break;
				case SHOP_BUTTON:
					gAEGameStateNext = GS_SHOP;
					break;
				}
				system_components.audio_manager->Play_Sound(SFX_BUTTON_CLICK);
			}
		}
		else
			button->Set_Active(INACTIVE);
	}
}


bool Tutorial_G_S_Shooter()
{
	float cursorX = 0, cursorY = 0;
	float buttonX = 0, buttonY = 0;

	cursorX = system_components.cursor_position_->Get_Cursor_Position().x;
	cursorY = system_components.cursor_position_->Get_Cursor_Position().y;

	for (unsigned i = 0; i < logic_components.object_manager->Get_Size_Button_List(); ++i)
	{
		GameObject * all_type_button = logic_components.object_manager->Get_Button(i);
		SoldierButton * button = dynamic_cast<SoldierButton*>(all_type_button);
		if (button == nullptr) continue;

		buttonX = button->Get_x();
		buttonY = button->Get_y();

		if (button->Get_Unit_Type() == G_BUTTON_1)
		{
			if (logic_components.level_data->players->Get_Granny_Mojo() >= 10 && AEInputCheckTriggered(AEVK_1) && button->Get_Active() != LOCKED)
			{
				Spawn_Object(G_S_SHOOTER, -400.0f, 0.0f);
				logic_components.level_data->players->Set_Granny_Mojo(-10);
				button->Set_Countdown_Timer(3.0f);
				system_components.audio_manager->Play_Sound(SFX_GRANDMA_BUTTON_SPAWN);
			}
		}

		if (Cursor_Box_Collision(button))
		{
			if (button->Get_Active() == LOCKED && !button->Get_Description()->Get_Alive())
				button->Get_Description()->Set_Alive(true);
			if (button->Get_Active() != LOCKED)
			{
				if (button->Get_Active() != CLICK)
					button->Set_Active(HOVER);
				if (AEInputCheckCurr(AEVK_LBUTTON))
					button->Set_Active(CLICK);
				if (AEInputCheckReleased(AEVK_LBUTTON))
				{
					if (button->Get_Unit_Type() == G_BUTTON_1)
					{
						if (logic_components.level_data->players->Get_Granny_Mojo() >= 10)
						{
							Spawn_Object(G_S_SHOOTER, -400.0f, 0.0f);
							logic_components.level_data->players->Set_Granny_Mojo(-10);
							button->Set_Countdown_Timer(3.0f);
							system_components.audio_manager->Play_Sound(SFX_GRANDMA_BUTTON_SPAWN);
							return true;
						}
					}
				}

			}
		}
		else if (button->Get_Active() != LOCKED)
			button->Set_Active(INACTIVE);
		else if (button->Get_Description()->Get_Alive())
			button->Get_Description()->Set_Alive(false);
	}
	return false;
}

bool Tutorial_G_T_Shooting()
{
	float cursorX = 0, cursorY = 0;
	float nodeX = 0, nodeY = 0;

	cursorX = system_components.cursor_position_->Get_Cursor_Position().x;
	cursorY = system_components.cursor_position_->Get_Cursor_Position().y;

	for (unsigned i = 0; i < logic_components.object_manager->Get_Size_Tower_Node_List(); ++i)
	{
		float camera_zoom = logic_components.camera->Get_Zoom();
		AEVec2 camera_pos = logic_components.camera->Get_Camera_Position();

		TowerNode * node = logic_components.object_manager->Get_Tower_Node(i);
		nodeX = node->Get_x();
		nodeY = node->Get_y();

		// Middle
		if (node->Get_Active() != TOWER_PLACED) {
			if (cursorX >= -camera_pos.x + (nodeX - 0.5f*node->Get_Selection_Width_Height()) * camera_zoom &&
				cursorX <= -camera_pos.x + (nodeX + 0.5f*node->Get_Selection_Width_Height()) * camera_zoom &&
				cursorY >= -camera_pos.y + (nodeY - 0.5f*node->Get_Selection_Width_Height()) * camera_zoom &&
				cursorY <= -camera_pos.y + (nodeY + 0.5f*node->Get_Selection_Width_Height()) * camera_zoom)
			{
				if (AEInputCheckTriggered(AEVK_LBUTTON))
				{
					node->Set_Active(TOWER_CHOICE);
				}
				else if (node->Get_Active() != TOWER_CHOICE)
				{
					node->Set_Active(TOWER_HOVER);
				}
			}
			else if (node->Get_Active() != TOWER_CHOICE || AEInputCheckTriggered(AEVK_LBUTTON))
			{
				node->Set_Active(EMPTY);
			}

			if (node->Get_Unit_Type() == G_TOWER_NODE1)
				if (cursorX >= -camera_pos.x + (nodeX - 0.5f*node->Get_Selection_Width_Height() - 0.5f*node->Get_Selection_Width_Height()) * camera_zoom &&
					cursorX <= -camera_pos.x + (nodeX - 0.5f*node->Get_Selection_Width_Height() + 0.5f*node->Get_Selection_Width_Height()) * camera_zoom &&
					cursorY >= -camera_pos.y + (nodeY + node->Get_Selection_Width_Height() - 0.5f*node->Get_Selection_Width_Height()) * camera_zoom &&
					cursorY <= -camera_pos.y + (nodeY + node->Get_Selection_Width_Height() + 0.5f*node->Get_Selection_Width_Height()) * camera_zoom)
				{
					if (AEInputCheckTriggered(AEVK_LBUTTON) && logic_components.level_data->players->Get_Granny_Mojo() >= 100.0f)
					{
						node->Set_Active(TOWER_PLACED, G_T_SHOOTING);
						logic_components.level_data->players->Set_Granny_Mojo(-100.0f);
						return true;
					}
				}
		}
	}
	return false;
}

void Input_Handle_Tutorial()
{
	if (AEInputCheckCurr(AEVK_UP))
		logic_components.camera->Set_Zoom(true);

	if (AEInputCheckCurr(AEVK_DOWN))
		logic_components.camera->Set_Zoom(false);

	if (AEInputCheckTriggered(AEVK_V))
		logic_components.camera->Resume_Play();

	if (AEInputCheckTriggered(AEVK_P) || AEInputCheckTriggered(AEVK_ESCAPE))
	{
		system_components.audio_manager->Play_Sound(SFX_BUTTON_CLICK);
		logic_components.pause_state_manager->Set_Pause(PAUSE_MENU);
	}

	if (AEInputCheckTriggered(AEVK_BACKQUOTE))
		gAEGameStateNext = AE_GS_QUIT;

	if (AEInputCheckTriggered(AEVK_R))
		gAEGameStateNext = AE_GS_RESTART;


	if (AEInputCheckReleased(AEVK_BACK))
	{
		playdata.Set_Stage(1);
		gAEGameStateNext = GS_LEVELSELECT;
		system_components.audio_manager->Initiate_Fade_Music(MUSIC_LEVEL, false);
		logic_components.pause_state_manager->Set_Pause(PAUSE_FADE);
	}

	if (AEInputCheckTriggered(AEVK_M))
		system_components.audio_manager->Mute_Music();


}




void Input_Handle_Granny_Mojo()
{

	if (AEInputCheckTriggered(AEVK_I))
		logic_components.level_data->players->Set_Granny_Mojo(+100);
	for (unsigned i = 0; i < logic_components.object_manager->Get_Size_Button_List(); ++i)
	{
		GameObject * all_type_button = logic_components.object_manager->Get_Button(i);
		MojoButton * button = dynamic_cast<MojoButton*>(all_type_button);
		if (!button) continue;
		if (Cursor_Box_Collision(button))
		{
			if (AEInputCheckCurr(AEVK_LBUTTON) && button->Get_Active() != LOCKED)
				button->Set_Active(CLICK);
			if (AEInputCheckReleased(AEVK_LBUTTON) && button->Get_Active() != LOCKED)
			{
				logic_components.level_data->players->Set_Granny_Mojo(-(logic_components.level_data->players->Get_Max_Granny_Mojo() - (playdata.Get_Money_Rate_Upgrade() == 2 ? 30.f : 20.0f)));
				logic_components.level_data->players->Set_Max_Granny_Mojo(logic_components.level_data->players->Get_Max_Granny_Mojo() + 50.0f);
				logic_components.level_data->players->Set_Rate_Granny_Mojo(logic_components.level_data->players->Get_Rate_Granny_Mojo() + 0.5f);
				button->Set_Active(LOCKED);
			}

			else if (AEInputCheckReleased(AEVK_LBUTTON) && button->Get_Active() == LOCKED)
				system_components.audio_manager->Play_Sound(SFX_BUTTON_INVALID);
		}
	}
}
/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Players.cpp
\author Wong Zhihao		(80%)		| Zachary Sng Zhi Ren (20%)
\par    email: zhihao.wong\@digipen.edu | z.sng\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the implementation of the Player class. The Players class
holds the data of both the Grandma and Kids, such as their HP. For Grandma,
it holds data regarding currencies as well.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Players.h"			// Function declaration
#include "RenderManager.h"		// Printing of text
#include "GameStateList.h"		// Enums for GS
#include "SystemComponents.h"	// System components
#include "LogicComponents.h"	// Logic components
#include "PlayerData.h"			// Player data that affects granny mojo

/******************************************************************************/
/*!
Default player constructor
*/
/******************************************************************************/
Players::Players()
	:
	// Base variables for the players
	current_granny_mojo_{0.0f},
	max_granny_mojo_{100.0f},
	rate_granny_mojo_{1.5f},
	grandma_base_HP_{20},
	kid_base_HP_{20}
{
}

/******************************************************************************/
/*!
Reset the variables to the base variables in the constructor
*/
/******************************************************************************/
void Players::Reset_Player_Stats()
{
	current_granny_mojo_ = 0.0f;
	max_granny_mojo_ = 100.0f;
	rate_granny_mojo_ = 1.5f;
	grandma_base_HP_ = 20;
	kid_base_HP_ = 20;
}

/******************************************************************************/
/*!
Gets the current granny mojo amount
*/
/******************************************************************************/
float Players::Get_Granny_Mojo() const
{
	return current_granny_mojo_;
}

/******************************************************************************/
/*!
Adds to the current granny mojo amount
*/
/******************************************************************************/
void Players::Set_Granny_Mojo(float modifier)
{
	current_granny_mojo_ += modifier;
}

/******************************************************************************/
/*!
Gives the player mojo coins during the tutorial.
*/
/******************************************************************************/
void Players::Tutorial_Give_Granny_Mojo(float mojo)
{
	current_granny_mojo_ = mojo;
}

/******************************************************************************/
/*!
Gets the max mojo coins the player can earn currently.
*/
/******************************************************************************/
float Players::Get_Max_Granny_Mojo()
{
	return max_granny_mojo_;
}

/******************************************************************************/
/*!
Sets the max mojo coins the player can earn currently.
*/
/******************************************************************************/
void Players::Set_Max_Granny_Mojo(float modifier)
{
	max_granny_mojo_ = modifier;
}

/******************************************************************************/
/*!
Sets the rate at which the player earns mojo coins.
*/
/******************************************************************************/
void Players::Set_Rate_Granny_Mojo(float modifier)
{
	rate_granny_mojo_ = modifier;
}

/******************************************************************************/
/*!
Gets the rate at which the player earns mojo coins.
*/
/******************************************************************************/
float Players::Get_Rate_Granny_Mojo()
{
	return rate_granny_mojo_;
}

/******************************************************************************/
/*!
	Retrieves Player's Base Health
*/
/******************************************************************************/
int Players::Get_Grandma_Base_HP()
{
	return grandma_base_HP_;
}

/******************************************************************************/
/*!
	Retrieves the Kid's base Health
*/
/******************************************************************************/
int Players::Get_Kid_Base_HP()
{
	return kid_base_HP_;
}

/******************************************************************************/
/*!
Prints the player's currency
*/
/******************************************************************************/
void Players::Print_Currency()
{
	// Sets the string to print
	char strBuffer[100];
	memset(strBuffer, 0, 100 * sizeof(char));

	u32 font = 0;

	// Switches the font depending on whether the game is in full screen or not
	if (full_screen)
		font = system_components.font_manager_->Get_Font(F_FULLSCREEN_GAME_UI_TEXT);
	else
		font = system_components.font_manager_->Get_Font(F_GAME_UI_TEXT);
	sprintf_s(strBuffer, "%.0f / %.0f", current_granny_mojo_, max_granny_mojo_);

	// Prints the player's granny mojo
	Print_Text(font, strBuffer, (int)AEGfxGetWinMinX() + 80, (int)AEGfxGetWinMaxY() - 500);
	if(logic_components.level_data->players->Get_Max_Granny_Mojo() < (playdata.Get_Money_Rate_Upgrade() ? 500 : 300))
		sprintf_s(strBuffer, "%d", ((int)((playdata.Get_Money_Rate_Upgrade() == 2)?max_granny_mojo_ - 30: max_granny_mojo_ - 20)));
	else
		sprintf_s(strBuffer, "MAX");
	Print_Text(font, strBuffer, (int)AEGfxGetWinMinX() + 80, (int)AEGfxGetWinMaxY() - 560);

	sprintf_s(strBuffer, "%d", grandma_base_HP_);
	Print_Text(font, strBuffer, (int)AEGfxGetWinMaxX() - 70, (int)AEGfxGetWinMaxY() - 510);

	sprintf_s(strBuffer, "%d", kid_base_HP_);
	Print_Text(font, strBuffer, (int)AEGfxGetWinMaxX() - 70, (int)AEGfxGetWinMaxY() - 560);



}

/******************************************************************************/
/*!
	Handles granny mojo earning
*/
/******************************************************************************/
void Players::Granny_Mojo_Earn()
{
	// Check if current granny mojo is less than the max allowed
	if (current_granny_mojo_ < max_granny_mojo_)
	{
		// Increase granny mojo based on increase rate
		current_granny_mojo_ += rate_granny_mojo_ * system_components.framerate_manager->Get_Game_Time();

		// Removes excess increase above the allowed max
		if (current_granny_mojo_ > max_granny_mojo_)
		{
			float extra = current_granny_mojo_ - max_granny_mojo_;

			current_granny_mojo_ -= extra;
		}
	}
}

/******************************************************************************/
/*!
Handles granny mojo earned from defeating kids and towers
*/
/******************************************************************************/
void Players::Granny_Mojo_Drop(int loot)
{
	//Adds 10 mojo for each kid/tower defeated
	current_granny_mojo_ += loot;

	//Caps the Granny mojo earned if max number of granny mojo has been reached
	if (current_granny_mojo_ >= max_granny_mojo_)
		current_granny_mojo_ = max_granny_mojo_;
}

/******************************************************************************/
/*!
	Damages the Player's Base
*/
/******************************************************************************/
void Players::Damage_Grandma_Base()
{
	--grandma_base_HP_;
	std::cout << "Grandmas Hit! HP Left: " << grandma_base_HP_ << "\n";

	logic_components.camera->Initialise_Shake_Camera();

	system_components.audio_manager->Play_Sound(SFX_G_BASE_HIT_LAUGH_1);
	system_components.audio_manager->Play_Sound(SFX_G_BASE_HIT_RUMBLE_1);
	//Checks if the player's base has been destroyed
	if (grandma_base_HP_ == 0)
	{
		gAEGameStateNext = GS_GAMEOVER;
		system_components.audio_manager->Initiate_Fade_Music(MUSIC_LEVEL, false);
		system_components.audio_manager->Play_Sound(SFX_DEFEAT_STINGER);
		logic_components.pause_state_manager->Set_Pause(PAUSE_DEFEAT);
	}
}

/******************************************************************************/
/*!
	Damages the Kid's base
*/
/******************************************************************************/
void Players::Damage_Kid_Base(int level_no)
{
	--kid_base_HP_;
	std::cout << "Kids Hit! HP Left: " << kid_base_HP_ << "\n";
	//Checks if the Kid's base has been destroyed
	if (kid_base_HP_ == 0)
	{
		Victory(grandma_base_HP_, level_no);
	}
}

/******************************************************************************/
/*!
Handles player data updating when player wins.
*/
/******************************************************************************/
void Players::Victory(int grandma_base_HP, int level_no)
{
	playdata.Set_Levels_Complete(level_no);
	playdata.Set_Level_Stars(grandma_base_HP, level_no);
	playdata.Save_Save_File();
	//gAEGameStateNext = GS_VICTORY;
	system_components.audio_manager->Initiate_Fade_Music(MUSIC_LEVEL, false);
	system_components.audio_manager->Play_Sound(SFX_VICTORY_STINGER);
	logic_components.pause_state_manager->Set_Pause(PAUSE_VICTORY);
}

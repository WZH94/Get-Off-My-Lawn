/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   AudioManager.cpp
\author Wong Zhihao			(100%)
\par    email: zhihao.wong\@digipen.edu 
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the implementation of the Audio Manager, which can play
and stream audio and also put DSP into the sounds.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "AudioManager.h"		// Function and class declarations
#include "fmod_errors.h"		// FMOD Error checking
#include "LogicComponents.h"	// Components
#include "SystemComponents.h"	// Components

/******************************************************************************/
/*!
	Constructor for Audio Manager, sets default variables
*/
/******************************************************************************/
Audio_Manager::Audio_Manager()
	: 
	sfx_volume_{1},
	music_volume_{1},
	kid_laughter_time_{5},
	kid_laughter_counter_{0}
{
}

/******************************************************************************/
/*!
	FMOD Error Checking to wrap around every FMOD function
*/
/******************************************************************************/
void Audio_Manager::FMOD_Error_Check(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error: (" << result << ") " << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}
}

/******************************************************************************/
/*!
	Initialises the Audio Manager and the FMOD Systen at the start of the application.
*/
/******************************************************************************/
void Audio_Manager::Initialise_FMOD()
{
	// Checks the fmod version
	unsigned fmod_version;
	// Creates the FMOD system
	FMOD_Error_Check(FMOD_System_Create(&fmod_system_));
	FMOD_Error_Check(FMOD_System_GetVersion(fmod_system_, &fmod_version));

	// Exit application if versions do not match
	if (fmod_version < FMOD_VERSION)
	{
		std::cout << "Error! You are using an old version of FMOD " << fmod_version << ". This program requires " << FMOD_VERSION << std::endl;
		exit(-1);
	}

	// Initialise the system with 256 channels and a low pass filter
	FMOD_Error_Check(FMOD_System_Init(fmod_system_, 256, FMOD_INIT_CHANNEL_LOWPASS, 0));

	// Loads every audio file in the game
	Load_Audio();

	// Set the reverb properties to be used in the game
	level_reverb_ = new FMOD_REVERB_PROPERTIES(FMOD_PRESET_PARKINGLOT);

	FMOD_Error_Check(FMOD_System_SetReverbProperties(fmod_system_, 0, level_reverb_));

	// Initialise every music channel to not be fading
	for (unsigned i = 0; i < MUSIC_LAST; ++i)
		music_channel_fade_list_.at(i) = NO_FADE;
}

/******************************************************************************/
/*!
	Updates the system every loop, and checks various channels for specialised sounds.
*/
/******************************************************************************/
void Audio_Manager::Update_FMOD()
{
	FMOD_Error_Check(FMOD_System_Update(fmod_system_));

	// While kid is laughing, advance its timer
	if (kid_laughter_counter_ >= 0)
		kid_laughter_counter_ -= system_components.framerate_manager->Get_Delta_Time();

	FMOD_BOOL wave_spawn_cheer_is_playing = false;

	// No error checking wrapping, since this returns an error if the channel is not playing anything.
	// Update the kid laughing panning as the camera moves about the map
	FMOD_Channel_IsPlaying(sfx_channel_list.at(CHANNEL_WAVE_SPAWN), &wave_spawn_cheer_is_playing);

	if (wave_spawn_cheer_is_playing)		
		Calculate_Wave_Spawn_Filtering();

	// Check for music fading
	for (unsigned i = 0; i < MUSIC_LAST; ++i)
	{
		if (music_channel_fade_list_.at(i) == FADE_IN)
			Fade_Music((MUSIC_LIST)i, 0.05f);

		else if (music_channel_fade_list_.at(i) == FADE_OUT)
			Fade_Music((MUSIC_LIST)i, -0.05f);
	}
}

/******************************************************************************/
/*!
	Loads every audio file into memory
*/
/******************************************************************************/
void Audio_Manager::Load_Audio()
{
	// Create the master channel groups for music and sfx
	FMOD_Error_Check(FMOD_System_CreateChannelGroup(fmod_system_, nullptr, &music_channel_group_));
	FMOD_Error_Check(FMOD_System_CreateChannelGroup(fmod_system_, nullptr, &sfx_channel_group_));

	///////////////
	// Loads music
	FMOD_Error_Check(FMOD_System_CreateStream(fmod_system_, "Resources/Music/grannys_lament.ogg", FMOD_LOOP_NORMAL, 0, &music_list_.at(MUSIC_MAIN_MENU)));
	FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, music_list_.at(MUSIC_MAIN_MENU), music_channel_group_, 1, &music_channel_list_.at(MUSIC_MAIN_MENU)));
	FMOD_Error_Check(FMOD_Channel_SetReverbProperties(music_channel_list_.at(MUSIC_MAIN_MENU), 0, 0));

	FMOD_Error_Check(FMOD_System_CreateStream(fmod_system_, "Resources/Music/battle_of_the_lawn_full.ogg", FMOD_LOOP_NORMAL, 0, &music_list_.at(MUSIC_LEVEL)));
	FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, music_list_.at(MUSIC_LEVEL), music_channel_group_, 1, &music_channel_list_.at(MUSIC_LEVEL)));
	FMOD_Error_Check(FMOD_Channel_SetReverbProperties(music_channel_list_.at(MUSIC_LEVEL), 0, 0));
	FMOD_Error_Check(FMOD_Channel_SetLoopPoints(music_channel_list_.at(MUSIC_LEVEL), 4490846, FMOD_TIMEUNIT_PCM, 8981694, FMOD_TIMEUNIT_PCM));

	/////////////
	// Loads SFX

	// Stingers
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Stingers/victory_stinger.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_VICTORY_STINGER)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Stingers/defeat_stinger.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_DEFEAT_STINGER)));

	// UI Sounds
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/General/UI/button_hover.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_BUTTON_HOVER)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/General/UI/button_click.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_BUTTON_CLICK)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/UI/button_invalid.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_BUTTON_INVALID)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/UI/grandma_button_spawn.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_BUTTON_SPAWN)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/UI/level_button_up.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_LEVEL_BUTTON_UP)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/UI/tower_node_select.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_TOWER_NODE_SELECT)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/UI/tower_node_deselect.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_TOWER_NODE_DESELECT)));

	// Environmental Sounds
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Environmentals/tower_construct.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_TOWER_CONSTRUCT)));
	FMOD_Error_Check(FMOD_System_CreateStream(fmod_system_, "Resources/SFX/Level/Environmentals/tower_fire.ogg", FMOD_LOOP_NORMAL, 0, &sfx_list_.at(SFX_TOWER_FIRE)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Environmentals/tower_destroy.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_TOWER_DESTROY)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Environmentals/grandma_base_hit_laugh1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_G_BASE_HIT_LAUGH_1)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Environmentals/grandma_base_hit_laugh2.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_G_BASE_HIT_LAUGH_2)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Environmentals/grandma_base_hit_laugh3.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_G_BASE_HIT_LAUGH_3)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Environmentals/grandma_base_hit_laugh4.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_G_BASE_HIT_LAUGH_4)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Environmentals/grandma_base_hit_laugh5.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_G_BASE_HIT_LAUGH_5)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Environmentals/grandma_base_hit_rumble1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_G_BASE_HIT_RUMBLE_1)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Environmentals/grandma_base_hit_rumble2.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_G_BASE_HIT_RUMBLE_2)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Environmentals/grandma_base_hit_rumble3.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_G_BASE_HIT_RUMBLE_3)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Environmentals/wave_spawn_cheer1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_WAVE_SPAWN_CHEER_1)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Environmentals/wave_spawn_cheer2.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_WAVE_SPAWN_CHEER_2)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Environmentals/wave_spawn_cheer3.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_WAVE_SPAWN_CHEER_3)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/General/attack_slow.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_ATTACK_SLOW)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/General/attack_poison.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_ATTACK_POISON)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/grandma_faint_poof1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_FAINT_1)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/grandma_faint_poof2.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_FAINT_2)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/cookie_grandma_attack1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_SHOOTER_ATTACK_1)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/cookie_grandma_attack2.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_SHOOTER_ATTACK_2)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/cookie_grandma_hit1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_SHOOTER_HIT_1)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/cookie_grandma_hit2.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_SHOOTER_HIT_2)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/gangsta_grandma_hit1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_TANK_HIT_1)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/gangsta_grandma_hit2.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_TANK_HIT_2)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/ninja_grandma_attack1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_SABOTEUR_ATTACK_1)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/ninja_grandma_attack2.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_SABOTEUR_ATTACK_2)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/ninja_grandma_hit1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_SABOTEUR_HIT_1)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/ninja_grandma_hit2.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_SABOTEUR_HIT_2)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/cat_grandma_attack1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_SLOW_ATTACK_1)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/cat_grandma_attack2.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_SLOW_ATTACK_2)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/cat_grandma_hit1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_SLOW_HIT_1)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/cat_grandma_hit2.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_SLOW_HIT_2)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/kungfu_grandma_attack1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_ATTACKSPEEDUP_ATTACK_1)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/kungfu_grandma_attack2.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_ATTACKSPEEDUP_ATTACK_2)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/kungfu_grandma_hit1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_ATTACKSPEEDUP_HIT_1)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/kungfu_grandma_hit2.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_ATTACKSPEEDUP_HIT_2)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/sassy_grandma_attack1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_STUN_ATTACK_1)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/sassy_grandma_attack2.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_STUN_ATTACK_2)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/sassy_grandma_hit1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_STUN_HIT_1)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/sassy_grandma_hit2.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_STUN_HIT_2)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/kid_faint_poof1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_FAINT_1)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/kid_faint_poof2.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_FAINT_2)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/clown_kid_attack1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_SHOOTER_ATTACK_1)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/clown_kid_attack2.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_SHOOTER_ATTACK_2)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/clown_kid_hit1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_SHOOTER_HIT)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/nerd_kid_attack1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_SABOTEUR_ATTACK_1)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/nerd_kid_attack2.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_SABOTEUR_ATTACK_2)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/nerd_kid_hit1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_SABOTEUR_HIT_1)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/nerd_kid_hit2.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_SABOTEUR_HIT_2)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/bully_kid_attack1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_ATTACKSPEEDUP_ATTACK_1)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/bully_kid_attack2.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_ATTACKSPEEDUP_ATTACK_2)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/bully_kid_hit1.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_ATTACKSPEEDUP_HIT_1)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/bully_kid_hit2.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_ATTACKSPEEDUP_HIT_2)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/big_bob_spawn.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_BIGBOB_SPAWN)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/big_bob_attack.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_BIGBOB_ATTACK)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/big_bob_hit.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_BIGBOB_HIT)));

	// GRANDMA TOWERS
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/oven_tower_attack.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_OVEN_ATTACK)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/oven_tower_hit.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_OVEN_HIT)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/dentures_tower_attack.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_DENTURES_ATTACK)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/dentures_tower_hit.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_DENTURES_HIT)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/veggies_tower_attack.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_VEGGIES_ATTACK)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/veggies_tower_hit.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_VEGGIES_HIT)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/puppies_tower_attack.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_PUPPIES_ATTACK)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/puppies_tower_hit.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_PUPPIES_HIT)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/cake_tower_attack.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_CAKE_ATTACK)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Grandma/cake_tower_hit.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_GRANDMA_CAKE_HIT)));


	// KID TOWERS
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/slingshot_tower_attack.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_SLINGSHOT_ATTACK)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/slingshot_tower_hit.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_SLINGSHOT_HIT)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/pillow_tower_attack.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_PILLOW_ATTACK)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/pillow_tower_hit.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_PILLOW_HIT)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/whoopee_tower_attack.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_WHOOPEE_ATTACK)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/whoopee_tower_hit.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_WHOOPEE_HIT)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/mud_tower_attack.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_MUD_ATTACK)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/mud_tower_hit.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_MUD_HIT)));

	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/car_tower_attack.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_CAR_ATTACK)));
	FMOD_Error_Check(FMOD_System_CreateSound(fmod_system_, "Resources/SFX/Level/Kid/car_tower_hit.ogg", FMOD_DEFAULT, 0, &sfx_list_.at(SFX_KID_CAR_HIT)));
}

/******************************************************************************/
/*!
	Releases FMOD system and all its channels and sounds
*/
/******************************************************************************/
void Audio_Manager::Release_FMOD()
{
	// Release music
	for (unsigned i = 0; i < MUSIC_LAST; ++i)
		FMOD_Error_Check(FMOD_Sound_Release(music_list_.at(i)));

	for (unsigned i = 0; i < SFX_LAST; ++i)
	{
		FMOD_Error_Check(FMOD_Sound_Release(sfx_list_.at(i)));
	}
	
	delete level_reverb_;

	// Release channels
	FMOD_Error_Check(FMOD_ChannelGroup_Release(music_channel_group_));
	FMOD_Error_Check(FMOD_ChannelGroup_Release(sfx_channel_group_));

	// Release system
	FMOD_Error_Check(FMOD_System_Release(fmod_system_));
}

/********************************************* VOLUME CONTROL FUNCTIONS *********************************************/

/******************************************************************************/
/*!
	Mutes and unmutes the music channel group
*/
/******************************************************************************/
void Audio_Manager::Mute_Music()
{
	// Set mute to false
	if (music_mute_ == true)
	{
		music_mute_ = false;

		FMOD_Error_Check(FMOD_ChannelGroup_SetMute(music_channel_group_, false));
	}

	// Set mute to true
	else
	{
		music_mute_ = true;

		FMOD_Error_Check(FMOD_ChannelGroup_SetMute(music_channel_group_, true));
	}
}

/******************************************************************************/
/*!
	Mutes and unmutes the sfx channel group
*/
/******************************************************************************/
void Audio_Manager::Mute_SFX()
{
	// Set mute to false
	if (sfx_mute_ == true)
	{
		sfx_mute_ = false;

		FMOD_Error_Check(FMOD_ChannelGroup_SetMute(sfx_channel_group_, false));
	}

	// Set mute to true
	else
	{
		sfx_mute_ = true;

		FMOD_Error_Check(FMOD_ChannelGroup_SetMute(sfx_channel_group_, true));
	}
}

/******************************************************************************/
/*!
	Increases and decreases music channel group volume. True to increase, false to decrease.
*/
/******************************************************************************/
void Audio_Manager::Adjust_Music_Volume(bool modifier)
{
	// Check if volume is not at max
	if (modifier && music_volume_ < 1.0f)
	{
		if (music_mute_) 
			music_mute_ = false;
		music_volume_ += 0.2f;

		if (music_volume_ > 1.0f)
			music_volume_ = 1.0f;

		FMOD_Error_Check(FMOD_ChannelGroup_SetVolume(music_channel_group_, music_volume_));
	}

	// Check if volume is not at min
	else if (!modifier && music_volume_ > 0)
	{
		music_volume_ -= 0.2f;

		if (music_volume_ < EPSILON && music_volume_ > -EPSILON)
		{
			music_volume_ = 0;
			if(!music_mute_) 
				music_mute_ = true;
		}

		FMOD_Error_Check(FMOD_ChannelGroup_SetVolume(music_channel_group_, music_volume_));
	}
}

/******************************************************************************/
/*!
Increases and decreases sfx channel group volume. True to increase, false to decrease.
*/
/******************************************************************************/
void Audio_Manager::Adjust_SFX_Volume(bool modifier)
{
	if (modifier && sfx_volume_ < 1.0f)
	{
		if (sfx_mute_) 
			sfx_mute_ = false;
		sfx_volume_ += 0.2f;

		if (sfx_volume_ > 1.0f)
			sfx_volume_ = 1.0f;

		FMOD_Error_Check(FMOD_ChannelGroup_SetVolume(sfx_channel_group_, sfx_volume_));
	}

	else if (!modifier && sfx_volume_ > 0)
	{
		sfx_volume_ -= 0.2f;

		if (sfx_volume_ < EPSILON && sfx_volume_ > -EPSILON)
		{
			sfx_volume_ = 0;
			if(!sfx_mute_) 
				sfx_mute_ = true;
		}

		FMOD_Error_Check(FMOD_ChannelGroup_SetVolume(sfx_channel_group_, sfx_volume_));
	}
}

/******************************************************************************/
/*!
	Sets the music volume to half when state is paused. True to set to half, 
	false to set back to normal
*/
/******************************************************************************/
void Audio_Manager::Set_Pause_Volume(bool modifier)
{
	// Get volume
	FMOD_Error_Check(FMOD_ChannelGroup_GetVolume(music_channel_group_, &music_pause_volume_));

	if (modifier)
		FMOD_Error_Check(FMOD_ChannelGroup_SetVolume(music_channel_group_, music_pause_volume_ / 2));

	else FMOD_Error_Check(FMOD_ChannelGroup_SetVolume(music_channel_group_, music_volume_));
}

/********************************************* PLAYBACK FUNCTIONS *********************************************/

///////////////////
// MUSIC PLAYBACK

/******************************************************************************/
/*!
	Streams a looping music if it is not already playing.
*/
/******************************************************************************/
void Audio_Manager::Stream_Music(MUSIC_LIST music)
{
	// Find the position
	unsigned position;
	FMOD_Error_Check(FMOD_Channel_GetPosition(music_channel_list_.at(music), &position, FMOD_TIMEUNIT_MS));

	// If position is at the start, play the music by setting it unpaused
	if (position == 0)
	{
		FMOD_Error_Check(FMOD_Channel_SetPaused(music_channel_list_.at(music), false));

		if (music_channel_fade_list_.at(music) != NO_FADE)
			music_channel_fade_list_.at(music) = NO_FADE;
	}
}

/******************************************************************************/
/*!
	Stops music and set its position back to 0.
*/
/******************************************************************************/
void Audio_Manager::Stop_Music(MUSIC_LIST music)
{
	FMOD_Error_Check(FMOD_Channel_SetPaused(music_channel_list_.at(music), true));

	FMOD_Error_Check(FMOD_Channel_SetPosition(music_channel_list_.at(music), 0, FMOD_TIMEUNIT_MS));

	FMOD_Error_Check(FMOD_Channel_SetVolume(music_channel_list_.at(music), 1.0f));
}

/******************************************************************************/
/*!
	Initiate music to fade. True to fade in, false to fade out.
*/
/******************************************************************************/
void Audio_Manager::Initiate_Fade_Music(MUSIC_LIST music, bool fade_type)
{
	if (fade_type == true)
		music_channel_fade_list_.at(music) = FADE_IN;

	else music_channel_fade_list_.at(music) = FADE_OUT;
}

/******************************************************************************/
/*!
	Fades music while it is fading. Internal function
*/
/******************************************************************************/
void Audio_Manager::Fade_Music(MUSIC_LIST music, float modifier)
{
	float volume = 0;

	// Get the volume and add it with a modifier
	FMOD_Error_Check(FMOD_Channel_GetVolume(music_channel_list_.at(music), &volume));
	FMOD_Error_Check(FMOD_Channel_SetVolume(music_channel_list_.at(music), volume += modifier));

	// Once it has reached 0 or full volume, stop it and set it to not fade
	if (volume < 0 || volume > 1.0f)
	{
		Stop_Music(music);
		music_channel_fade_list_.at(music) = NO_FADE;
	}
}

/******************************************************************************/
/*!
	Plays a sound, functions defer on the sound
*/
/******************************************************************************/
void Audio_Manager::Play_Sound(SFX_LIST sfx, float x_pos, float y_pos)
{
	switch (sfx)
	{
	// Handles the pitching and mixing of the kids laughing
	case SFX_G_BASE_HIT_LAUGH_1:
	case SFX_G_BASE_HIT_LAUGH_2:
	case SFX_G_BASE_HIT_LAUGH_3:
	case SFX_G_BASE_HIT_LAUGH_4:
	case SFX_G_BASE_HIT_LAUGH_5:
		Play_Sinister_Laugh(Randomise_Sound(SFX_G_BASE_HIT_LAUGH_1, SFX_G_BASE_HIT_LAUGH_5));
		break;

	// Plays the sound with randomised pitch
	case SFX_G_BASE_HIT_RUMBLE_1:
	case SFX_G_BASE_HIT_RUMBLE_2:
	case SFX_G_BASE_HIT_RUMBLE_3:
		FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(Randomise_Sound(SFX_G_BASE_HIT_RUMBLE_1, SFX_G_BASE_HIT_RUMBLE_3)), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_RANDOM_PITCH)));
		Randomise_Pitch(sfx_channel_list.at(CHANNEL_RANDOM_PITCH), 0.25f);
		FMOD_Error_Check(FMOD_Channel_SetPaused(sfx_channel_list.at(CHANNEL_RANDOM_PITCH), false));
		break;

	// Plays the sound at the enemy base
	case SFX_WAVE_SPAWN_CHEER_1:
	case SFX_WAVE_SPAWN_CHEER_2:
	case SFX_WAVE_SPAWN_CHEER_3:
		Play_Wave_Spawn();
		break;

	// Play the sound as an in game location
	case SFX_TOWER_DESTROY:

	case SFX_ATTACK_SLOW:

	case SFX_GRANDMA_FAINT_1:
	case SFX_GRANDMA_FAINT_2:

	case SFX_GRANDMA_SHOOTER_ATTACK_1:
	case SFX_GRANDMA_SHOOTER_ATTACK_2:
	case SFX_GRANDMA_SHOOTER_HIT_1:
	case SFX_GRANDMA_SHOOTER_HIT_2:
	case SFX_GRANDMA_TANK_HIT_1:
	case SFX_GRANDMA_TANK_HIT_2:
	case SFX_GRANDMA_SABOTEUR_ATTACK_1:
	case SFX_GRANDMA_SABOTEUR_ATTACK_2:
	case SFX_GRANDMA_SABOTEUR_HIT_1:
	case SFX_GRANDMA_SABOTEUR_HIT_2:
	case SFX_GRANDMA_SLOW_ATTACK_1:
	case SFX_GRANDMA_SLOW_ATTACK_2:
	case SFX_GRANDMA_SLOW_HIT_1:
	case SFX_GRANDMA_SLOW_HIT_2:
	case SFX_GRANDMA_ATTACKSPEEDUP_ATTACK_1:
	case SFX_GRANDMA_ATTACKSPEEDUP_ATTACK_2:
	case SFX_GRANDMA_ATTACKSPEEDUP_HIT_1:
	case SFX_GRANDMA_ATTACKSPEEDUP_HIT_2:
	case SFX_GRANDMA_STUN_ATTACK_1:
	case SFX_GRANDMA_STUN_ATTACK_2:
	case SFX_GRANDMA_STUN_HIT_1:
	case SFX_GRANDMA_STUN_HIT_2:

	case SFX_KID_FAINT_1:
	case SFX_KID_FAINT_2:

	case SFX_KID_SHOOTER_ATTACK_1:
	case SFX_KID_SHOOTER_ATTACK_2:
	case SFX_KID_SHOOTER_HIT:
	case SFX_KID_SABOTEUR_ATTACK_1:
	case SFX_KID_SABOTEUR_ATTACK_2:
	case SFX_KID_SABOTEUR_HIT_1:
	case SFX_KID_SABOTEUR_HIT_2:
	case SFX_KID_ATTACKSPEEDUP_ATTACK_1:
	case SFX_KID_ATTACKSPEEDUP_ATTACK_2:
	case SFX_KID_ATTACKSPEEDUP_HIT_1:
	case SFX_KID_ATTACKSPEEDUP_HIT_2:

	case SFX_KID_BIGBOB_ATTACK:
	case SFX_KID_BIGBOB_HIT:

	case SFX_GRANDMA_OVEN_ATTACK:
	case SFX_GRANDMA_OVEN_HIT:
	case SFX_GRANDMA_DENTURES_ATTACK:
	case SFX_GRANDMA_DENTURES_HIT:
	case SFX_GRANDMA_VEGGIES_ATTACK:
	case SFX_GRANDMA_VEGGIES_HIT:
	case SFX_GRANDMA_PUPPIES_ATTACK:
	case SFX_GRANDMA_PUPPIES_HIT:
	case SFX_GRANDMA_CAKE_ATTACK:
	case SFX_GRANDMA_CAKE_HIT:
		Play_Game_Position_Sounds(sfx, x_pos, y_pos);
		break;

	// Play the sound normally
	default: 
		FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(sfx), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_DEFAULT)));
		FMOD_Error_Check(FMOD_Channel_SetReverbProperties(sfx_channel_list.at(CHANNEL_DEFAULT), 0, 0));
		FMOD_Error_Check(FMOD_Channel_SetPaused(sfx_channel_list.at(CHANNEL_DEFAULT), false));
	}
}

/******************************************************************************/
/*!
	Randomise sound if there are a few variations.
*/
/******************************************************************************/
SFX_LIST Audio_Manager::Randomise_Sound(SFX_LIST from, SFX_LIST to)
{
	return SFX_LIST(logic_components.Generate_Random_Integer(to - from) + from);
}

/******************************************************************************/
/*!
	Randomises pitch by a certain margin.
*/
/******************************************************************************/
void Audio_Manager::Randomise_Pitch(FMOD_CHANNEL* channel, float range)
{
	int integer = (int)range;
	int decimal = int(range - integer) * 100;	// Up to 2 decimal places

	float random_pitch = 0;

	// If number is 1 or more
	if (integer)
		random_pitch = float((logic_components.Generate_Random_Integer(integer * 2)) - integer);

	random_pitch += float(logic_components.Generate_Random_Integer(decimal * 2) - decimal) * 0.01f;

	FMOD_Error_Check(FMOD_Channel_SetPitch(channel, 1.0f + random_pitch));
}

/******************************************************************************/
/*!
	Plays sound but make it softer, more reverbarant and with less highs the further
	away it is from the center of the camera.
*/
/******************************************************************************/
void Audio_Manager::Play_Game_Position_Sounds(SFX_LIST sfx, float x_pos, float y_pos)
{
	// Get the position the sound plays from relative to camera zoom
	float x = x_pos * logic_components.camera->Get_Zoom();
	float y = y_pos * logic_components.camera->Get_Zoom();

	// Find the distance of the object from the center of the camera
	float x_diff = x - logic_components.camera->Get_Camera_Position().x;
	float y_diff = y - logic_components.camera->Get_Camera_Position().y;

	// Sets the differences to be positive numbers for calculations later on
	if (x_diff < 0)
		x_diff *= -1;

	if (y_diff < 0)
		y_diff *= -1;

	// Check if the object is inside the screen, plus 300 pixels leeway
	if (x_diff < HALF_SCREEN_WIDTH + 300.0f && y_diff < HALF_SCREEN_HEIGHT + 300.0f)
	{
		// Different sounds play differently
		switch (sfx)
		{
		case SFX_GRANDMA_FAINT_1:
		case SFX_GRANDMA_FAINT_2:
			FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(Randomise_Sound(SFX_GRANDMA_FAINT_1, SFX_GRANDMA_FAINT_2)), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_GAME_POSITION)));
			break;

		case SFX_GRANDMA_SHOOTER_ATTACK_1:
		case SFX_GRANDMA_SHOOTER_ATTACK_2:
			FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(Randomise_Sound(SFX_GRANDMA_SHOOTER_ATTACK_1, SFX_GRANDMA_SHOOTER_ATTACK_2)), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_GAME_POSITION)));
			break;

		case SFX_GRANDMA_SHOOTER_HIT_1:
		case SFX_GRANDMA_SHOOTER_HIT_2:
			FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(Randomise_Sound(SFX_GRANDMA_SHOOTER_HIT_1, SFX_GRANDMA_SHOOTER_HIT_2)), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_GAME_POSITION)));
			break;

		case SFX_GRANDMA_TANK_HIT_1:
		case SFX_GRANDMA_TANK_HIT_2:
			FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(Randomise_Sound(SFX_GRANDMA_TANK_HIT_1, SFX_GRANDMA_TANK_HIT_2)), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_GAME_POSITION)));
			break;

		case SFX_GRANDMA_SABOTEUR_ATTACK_1:
		case SFX_GRANDMA_SABOTEUR_ATTACK_2:
			FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(Randomise_Sound(SFX_GRANDMA_SABOTEUR_ATTACK_1, SFX_GRANDMA_SABOTEUR_ATTACK_2)), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_GAME_POSITION)));
			break;

		case SFX_GRANDMA_SABOTEUR_HIT_1:
		case SFX_GRANDMA_SABOTEUR_HIT_2:
			FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(Randomise_Sound(SFX_GRANDMA_SABOTEUR_HIT_1, SFX_GRANDMA_SABOTEUR_HIT_2)), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_GAME_POSITION)));
			break;

		case SFX_GRANDMA_SLOW_ATTACK_1:
		case SFX_GRANDMA_SLOW_ATTACK_2:
			FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(Randomise_Sound(SFX_GRANDMA_SLOW_ATTACK_1, SFX_GRANDMA_SLOW_ATTACK_2)), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_GAME_POSITION)));
			break;

		case SFX_GRANDMA_SLOW_HIT_1:
		case SFX_GRANDMA_SLOW_HIT_2:
			FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(Randomise_Sound(SFX_GRANDMA_SLOW_HIT_1, SFX_GRANDMA_SLOW_HIT_2)), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_GAME_POSITION)));
			break;

		case SFX_GRANDMA_ATTACKSPEEDUP_ATTACK_1:
		case SFX_GRANDMA_ATTACKSPEEDUP_ATTACK_2:
			FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(Randomise_Sound(SFX_GRANDMA_ATTACKSPEEDUP_ATTACK_1, SFX_GRANDMA_ATTACKSPEEDUP_ATTACK_2)), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_GAME_POSITION)));
			break;

		case SFX_GRANDMA_ATTACKSPEEDUP_HIT_1:
		case SFX_GRANDMA_ATTACKSPEEDUP_HIT_2:
			FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(Randomise_Sound(SFX_GRANDMA_ATTACKSPEEDUP_HIT_1, SFX_GRANDMA_ATTACKSPEEDUP_HIT_2)), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_GAME_POSITION)));
			break;

		case SFX_GRANDMA_STUN_ATTACK_1:
		case SFX_GRANDMA_STUN_ATTACK_2:
			FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(Randomise_Sound(SFX_GRANDMA_STUN_ATTACK_1, SFX_GRANDMA_STUN_ATTACK_2)), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_GAME_POSITION)));
			break;

		case SFX_GRANDMA_STUN_HIT_1:
		case SFX_GRANDMA_STUN_HIT_2:
			FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(Randomise_Sound(SFX_GRANDMA_STUN_HIT_1, SFX_GRANDMA_STUN_HIT_2)), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_GAME_POSITION)));
			break;

		case SFX_KID_FAINT_1:
		case SFX_KID_FAINT_2:
			FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(Randomise_Sound(SFX_KID_FAINT_1, SFX_KID_FAINT_2)), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_GAME_POSITION)));
			break;

		case SFX_KID_SHOOTER_ATTACK_1:
		case SFX_KID_SHOOTER_ATTACK_2:
			FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(Randomise_Sound(SFX_KID_SHOOTER_ATTACK_1, SFX_KID_SHOOTER_ATTACK_2)), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_GAME_POSITION)));
			break;

		case SFX_KID_SABOTEUR_ATTACK_1:
		case SFX_KID_SABOTEUR_ATTACK_2:
			FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(Randomise_Sound(SFX_KID_SABOTEUR_ATTACK_1, SFX_KID_SABOTEUR_ATTACK_2)), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_GAME_POSITION)));
			break;

		case SFX_KID_SABOTEUR_HIT_1:
		case SFX_KID_SABOTEUR_HIT_2:
			FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(Randomise_Sound(SFX_KID_SABOTEUR_HIT_1, SFX_KID_SABOTEUR_HIT_2)), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_GAME_POSITION)));
			break;

		case SFX_KID_ATTACKSPEEDUP_ATTACK_1:
		case SFX_KID_ATTACKSPEEDUP_ATTACK_2:
			FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(Randomise_Sound(SFX_KID_ATTACKSPEEDUP_ATTACK_1, SFX_KID_ATTACKSPEEDUP_ATTACK_2)), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_GAME_POSITION)));
			break;

		case SFX_KID_ATTACKSPEEDUP_HIT_1:
		case SFX_KID_ATTACKSPEEDUP_HIT_2:
			FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(Randomise_Sound(SFX_KID_ATTACKSPEEDUP_HIT_1, SFX_KID_ATTACKSPEEDUP_HIT_2)), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_GAME_POSITION)));
			break;

		default:
			FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(sfx), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_GAME_POSITION)));
			break;
		}

		///////////////////////////////////
		// Calculates panning of the sound

		// Finds the offset of the sound origin from the center of the screen
		float pan_position = (x - logic_components.camera->Get_Camera_Position().x) / HALF_SCREEN_WIDTH;

		// Limits the pan number between -1 to 1
		if (pan_position < -1.0f)
			pan_position = -1.0f;

		else if (pan_position > 1.0f)
			pan_position = 1.0f;

		//printf("Pan: %f\n", pan_position);

		// Pans the sound
		FMOD_Error_Check(FMOD_Channel_SetPan(sfx_channel_list.at(CHANNEL_GAME_POSITION), pan_position));

		///////////////////////////////////////////////////////
		// Calculates volume and attenuation based on distance
		x_diff = -(x_diff / (HALF_SCREEN_WIDTH + 300.0f)) + 1;
		y_diff = -(y_diff / (HALF_SCREEN_HEIGHT + 300.0f)) + 1;
		
		// The modifier for the volume
		float modifier = x_diff * y_diff * logic_components.camera->Get_Zoom();

		//printf("Modifier: %f\n", modifier);
		//printf("Volume Modifier: %f\n", modifier * logic_components.camera->Get_Zoom());

		FMOD_Error_Check(FMOD_Channel_SetVolume(sfx_channel_list.at(CHANNEL_GAME_POSITION), modifier));
		FMOD_Error_Check(FMOD_Channel_SetLowPassGain(sfx_channel_list.at(CHANNEL_GAME_POSITION), modifier * 1.5f));

		//modifier *= (logic_components.camera->Get_Zoom() - 0.4f);
		modifier = 1 - modifier;

		if (modifier > 1.0f)
			modifier = 1.0f;

		else if (modifier < 0)
			modifier = 0;

		//printf("Attenuation Modifier: %f\n", modifier);

		FMOD_Error_Check(FMOD_Channel_SetReverbProperties(sfx_channel_list.at(CHANNEL_GAME_POSITION), 0, modifier));
		//FMOD_Error_Check(FMOD_Channel_Set3DOcclusion(sfx_channel_list.at(CHANNEL_GAME_POSITION), modifier, modifier));

		Randomise_Pitch(sfx_channel_list.at(CHANNEL_GAME_POSITION));

		FMOD_Error_Check(FMOD_Channel_SetPaused(sfx_channel_list.at(CHANNEL_GAME_POSITION), false));

		//printf("\n");
	}
}

/******************************************************************************/
/*!
	Plays the sound panned towards the kids base location
*/
/******************************************************************************/
void Audio_Manager::Play_Wave_Spawn()
{
	FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(Randomise_Sound(SFX_WAVE_SPAWN_CHEER_1, SFX_WAVE_SPAWN_CHEER_3)), sfx_channel_group_, true, &sfx_channel_list.at(CHANNEL_WAVE_SPAWN)));

	Calculate_Wave_Spawn_Filtering();

	FMOD_Error_Check(FMOD_Channel_SetPaused(sfx_channel_list.at(CHANNEL_WAVE_SPAWN), false));
}

/******************************************************************************/
/*!
	Calculates panning
*/
/******************************************************************************/
void Audio_Manager::Calculate_Wave_Spawn_Filtering()
{
	float x_base = logic_components.level_data->Get_Enemy_Base_Location().x * logic_components.camera->Get_Zoom();

	// Find the distance of the object from the center of the camera
	float x_diff = x_base - logic_components.camera->Get_Camera_Position().x;


	///////////////////////////////////
	// Calculates panning of the sound

	// Finds the offset of the sound origin from the center of the screen
	float pan_position = x_diff / HALF_SCREEN_WIDTH;

	// Limits the pan number between -1 to 1
	if (pan_position < -1.0f)
		pan_position = -1.0f;

	else if (pan_position > 1.0f)
		pan_position = 1.0f;

	// Pans the sound
	FMOD_Error_Check(FMOD_Channel_SetPan(sfx_channel_list.at(CHANNEL_WAVE_SPAWN), pan_position));
}

/******************************************************************************/
/*!
	Sinister laughter for kids
*/
/******************************************************************************/
void Audio_Manager::Play_Sinister_Laugh(SFX_LIST sfx)
{
	// If no other kid laughing sound playing
	if (kid_laughter_counter_ <= 0)
	{
		kid_laughter_counter_ = kid_laughter_time_;

		FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(sfx), sfx_channel_group_, 0, nullptr));

		int grandma_base_hp = logic_components.level_data->players->Get_Grandma_Base_HP();

		// Pitch down function, only does this when grandma HP below 10
		if (grandma_base_hp < 10)
		{
			SFX_LIST second_laugh;

			// Loop until its playing another laughing sound
			do {
				second_laugh = Randomise_Sound(SFX_G_BASE_HIT_LAUGH_1, SFX_G_BASE_HIT_LAUGH_5);
			} while (second_laugh != sfx);

			// Pitch it down, make it louder the lower grandma hp
			FMOD_Error_Check(FMOD_System_PlaySound(fmod_system_, sfx_list_.at(sfx), sfx_channel_group_, 1, &sfx_channel_list.at(CHANNEL_KIDS_LAUGHTER_PITCHED)));

			FMOD_Error_Check(FMOD_Channel_SetVolume(sfx_channel_list.at(CHANNEL_KIDS_LAUGHTER_PITCHED), (10.0f - grandma_base_hp) * 0.02f));

			FMOD_Error_Check(FMOD_Channel_SetPitch(sfx_channel_list.at(CHANNEL_KIDS_LAUGHTER_PITCHED), 0.65f));

			FMOD_Error_Check(FMOD_Channel_SetReverbProperties(sfx_channel_list.at(CHANNEL_KIDS_LAUGHTER_PITCHED), 0, 0));

			FMOD_Error_Check(FMOD_Channel_SetPaused(sfx_channel_list.at(CHANNEL_KIDS_LAUGHTER_PITCHED), false));
		}
	}
}

bool Audio_Manager::Get_Music_Mute() const
{
	return music_mute_;
}
bool Audio_Manager::Get_SFX_Mute() const
{
	return sfx_mute_;
}
float Audio_Manager::Get_Music_Volume() const
{
	return music_volume_;
}
float Audio_Manager::Get_SFX_Volume() const
{
	return sfx_volume_;
}
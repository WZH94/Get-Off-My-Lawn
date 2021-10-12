/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   AudioManager.h
\author Wong Zhihao(100%)
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the declarations of the Audio Manager, which can play
and stream audio and also put DSP into the sounds.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "fmod.h"	// FMOD Library
#include <array>	// Array

// SFX Channel lists
enum SFX_CHANNEL_LIST
{
	CHANNEL_DEFAULT = 0,
	CHANNEL_GAME_POSITION,
	CHANNEL_RANDOM_PITCH,
	CHANNEL_WAVE_SPAWN,
	CHANNEL_KIDS_LAUGHTER_PITCHED,

	CHANNEL_LAST
};

// List of all sfx
enum SFX_LIST
{
	////////////
	// STINGERS
	SFX_VICTORY_STINGER = 0,
	SFX_DEFEAT_STINGER,


	///////////
	// UI SFX
	SFX_BUTTON_HOVER,
	SFX_BUTTON_CLICK,

	SFX_BUTTON_INVALID,
	SFX_GRANDMA_BUTTON_SPAWN,
	SFX_LEVEL_BUTTON_UP,

	SFX_TOWER_NODE_SELECT,
	SFX_TOWER_NODE_DESELECT,

	//////////////////////
	// ENVIRONMENTAL SFX
	SFX_TOWER_CONSTRUCT,
	SFX_TOWER_FIRE,
	SFX_TOWER_DESTROY,

	SFX_G_BASE_HIT_LAUGH_1,
	SFX_G_BASE_HIT_LAUGH_2,
	SFX_G_BASE_HIT_LAUGH_3,
	SFX_G_BASE_HIT_LAUGH_4,
	SFX_G_BASE_HIT_LAUGH_5,

	SFX_G_BASE_HIT_RUMBLE_1,
	SFX_G_BASE_HIT_RUMBLE_2,
	SFX_G_BASE_HIT_RUMBLE_3,

	SFX_WAVE_SPAWN_CHEER_1,
	SFX_WAVE_SPAWN_CHEER_2,
	SFX_WAVE_SPAWN_CHEER_3,

	////////////////////
	// GENERAL UNIT SFX
	SFX_ATTACK_SLOW,
	SFX_ATTACK_POISON,

	///////////////
	// GRANDMA SFX
	SFX_GRANDMA_FAINT_1,
	SFX_GRANDMA_FAINT_2,

	SFX_GRANDMA_SHOOTER_ATTACK_1,
	SFX_GRANDMA_SHOOTER_ATTACK_2,
	SFX_GRANDMA_SHOOTER_HIT_1,
	SFX_GRANDMA_SHOOTER_HIT_2,

	SFX_GRANDMA_TANK_HIT_1,
	SFX_GRANDMA_TANK_HIT_2,

	SFX_GRANDMA_SABOTEUR_ATTACK_1,
	SFX_GRANDMA_SABOTEUR_ATTACK_2,
	SFX_GRANDMA_SABOTEUR_HIT_1,
	SFX_GRANDMA_SABOTEUR_HIT_2,

	SFX_GRANDMA_SLOW_ATTACK_1,
	SFX_GRANDMA_SLOW_ATTACK_2,
	SFX_GRANDMA_SLOW_HIT_1,
	SFX_GRANDMA_SLOW_HIT_2,

	SFX_GRANDMA_ATTACKSPEEDUP_ATTACK_1,
	SFX_GRANDMA_ATTACKSPEEDUP_ATTACK_2,
	SFX_GRANDMA_ATTACKSPEEDUP_HIT_1,
	SFX_GRANDMA_ATTACKSPEEDUP_HIT_2,

	SFX_GRANDMA_STUN_ATTACK_1,
	SFX_GRANDMA_STUN_ATTACK_2,
	SFX_GRANDMA_STUN_HIT_1,
	SFX_GRANDMA_STUN_HIT_2,

	////////////
	// KID SFX
	SFX_KID_FAINT_1,
	SFX_KID_FAINT_2,

	SFX_KID_SHOOTER_ATTACK_1,
	SFX_KID_SHOOTER_ATTACK_2,
	SFX_KID_SHOOTER_HIT,

	SFX_KID_SABOTEUR_ATTACK_1,
	SFX_KID_SABOTEUR_ATTACK_2,
	SFX_KID_SABOTEUR_HIT_1,
	SFX_KID_SABOTEUR_HIT_2,

	SFX_KID_ATTACKSPEEDUP_ATTACK_1,
	SFX_KID_ATTACKSPEEDUP_ATTACK_2,
	SFX_KID_ATTACKSPEEDUP_HIT_1,
	SFX_KID_ATTACKSPEEDUP_HIT_2,

	SFX_KID_BIGBOB_SPAWN,
	SFX_KID_BIGBOB_ATTACK,
	SFX_KID_BIGBOB_HIT,

	/////////////////////
	// GRANDMA TOWER SFX
	SFX_GRANDMA_OVEN_ATTACK,
	SFX_GRANDMA_OVEN_HIT,
	SFX_GRANDMA_DENTURES_ATTACK,
	SFX_GRANDMA_DENTURES_HIT,
	SFX_GRANDMA_VEGGIES_ATTACK,
	SFX_GRANDMA_VEGGIES_HIT,
	SFX_GRANDMA_PUPPIES_ATTACK,
	SFX_GRANDMA_PUPPIES_HIT,
	SFX_GRANDMA_CAKE_ATTACK,
	SFX_GRANDMA_CAKE_HIT,

	/////////////////
	// KID TOWER SFX
	SFX_KID_SLINGSHOT_ATTACK,
	SFX_KID_SLINGSHOT_HIT,
	SFX_KID_PILLOW_ATTACK,
	SFX_KID_PILLOW_HIT,
	SFX_KID_WHOOPEE_ATTACK,
	SFX_KID_WHOOPEE_HIT,
	SFX_KID_MUD_ATTACK,
	SFX_KID_MUD_HIT,
	SFX_KID_CAR_ATTACK,
	SFX_KID_CAR_HIT,

	SFX_LAST
};

// List of all music
enum MUSIC_LIST
{
	MUSIC_MAIN_MENU = 0,
	MUSIC_LEVEL,

	MUSIC_LAST
};

// Fade modes for the music
enum FADE_MODE
{
	NO_FADE = 0,
	FADE_IN,
	FADE_OUT
};

class Audio_Manager
{
protected:
	FMOD_SYSTEM* fmod_system_;											// FMOD System

	// Channel group for sfx and music
	FMOD_CHANNELGROUP* sfx_channel_group_;
	FMOD_CHANNELGROUP* music_channel_group_;

	// Reverb type for in location sounds
	FMOD_REVERB_PROPERTIES* level_reverb_;

	// Various lists for sounds and their channels
	std::array <FMOD_SOUND*, SFX_LAST> sfx_list_;
	std::array <FMOD_SOUND*, MUSIC_LAST> music_list_;
	std::array <FMOD_CHANNEL*, MUSIC_LAST> music_channel_list_;
	std::array <FADE_MODE, FADE_OUT + 1> music_channel_fade_list_;
	std::array <FMOD_CHANNEL*, CHANNEL_LAST> sfx_channel_list;

	// Mute for the channel groups
	bool sfx_mute_;
	bool music_mute_;

	// Volume for the channel groups
	float sfx_volume_;
	float music_volume_;
	float music_pause_volume_;

	// Kid laughter timers
	float kid_laughter_counter_;
	const float kid_laughter_time_;

	/********************************************* INTERNAL PLAYBACK FUNCTIONS *********************************************/

	// Randomises pitch by a certain margin.
	SFX_LIST Randomise_Sound(SFX_LIST from, SFX_LIST to);

	// Randomise a pitch of the inputted channel to +- range. 0.5 = half pitch, 2.0 = double pitch
	void Randomise_Pitch(FMOD_CHANNEL * channel, float range = 0.2f);

	// Plays Sinister laughter for kids
	void Play_Sinister_Laugh(SFX_LIST sfx);

	// Plays sound but make it softer, more reverbarant and with less highs the further away it is from the center of the camera.
	void Play_Game_Position_Sounds(SFX_LIST sfx, float x_pos, float y_pos);

	// Plays the sound panned towards the kids base location
	void Play_Wave_Spawn();

	// Calculates panning for wave spawn
	void Calculate_Wave_Spawn_Filtering();


public:
	// Constructor for Audio Manager, sets default variables
	Audio_Manager();

	// FMOD Error Checking to wrap around every FMOD function
	void FMOD_Error_Check(FMOD_RESULT result);

	// Initialises the Audio Manager and the FMOD Systen at the start of the application.
	void Initialise_FMOD();

	// Updates the system every loop, and checks various channels for specialised sounds.
	void Update_FMOD();

	// Loads every audio file into memory
	void Load_Audio();

	// Releases FMOD system and all its channels and sounds
	void Release_FMOD();

	/********************************************* VOLUME CONTROL FUNCTIONS *********************************************/

	// Mutes and unmutes the music channel group
	void Mute_Music();

	// Mutes and unmutes the sfx channel group
	void Mute_SFX();

	// true to increase volume, false to decrease
	void Adjust_Music_Volume(bool modifier);

	// true to increase volume, false to decrease
	void Adjust_SFX_Volume(bool modifier);

	// Sets volume for music in pause menu.
	// True to set to half volume, false to set to full volume.
	void Set_Pause_Volume(bool modifier);

	/********************************************* PLAYBACK FUNCTIONS *********************************************/

	// Streams a looping music if it is not already playing.
	void Stream_Music(MUSIC_LIST);

	// Stops music and set its position back to 0.
	void Stop_Music(MUSIC_LIST music);

	// Initiate music to fade. True to fade in, false to fade out.
	void Initiate_Fade_Music(MUSIC_LIST music, bool fade_type);
	
	// Fades music while it is fading. Internal function
	void Fade_Music(MUSIC_LIST music, float modifier);

	// Plays a sound, functions defer on the sound
	void Play_Sound(SFX_LIST sfx, float x_pos = 0, float y_pos = 0);

	// Getters and setters
	bool Get_Music_Mute()const;

	bool Get_SFX_Mute()const;

	float Get_Music_Volume() const;

	float Get_SFX_Volume() const;



};

#endif
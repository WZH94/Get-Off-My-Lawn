/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Spawner.cpp
\author Ngm Hui Min, Lois	(100%)
\par    email: lois.ngm\@digipen.edu
\par    DigiPen login: lois.ngm
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the algorithmn to handle the spawning kid waves, both
trickling and big waves

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Spawner.h"
#include "ObjectManager.h"
#include "ObjectList.h"
#include "ObjectSpawner.h"
#include "SystemComponents.h"
#include "LogicComponents.h"

/******************************************************************************/
/*!
			Spawner Constructor
*/
/******************************************************************************/
Spawner::Spawner()
	: wave_interval_length_{60.0f},
	waves_completed_{false}
{}
/******************************************************************************/
/*!
			Loads Spawning waves
*/
/******************************************************************************/

void Spawner::Spawner_Load(const int maximum_wave, int wave_pattern[][NUMBER_OF_GRANNIES])
{
	max_wave_ = maximum_wave;
	wave_number_ = 0;
	wave_spawner_ = new int *[max_wave_];

	for (int i = 0; i < max_wave_; ++i)
	{
		wave_spawner_[i] = new int[NUMBER_OF_GRANNIES];
		for (int j = 0; j < NUMBER_OF_GRANNIES; ++j)
		{
			wave_spawner_[i][j] = wave_pattern[i][j];
		}
	}
}

/******************************************************************************/
/*!
					Update Spawner Wave
*/
/******************************************************************************/


void Spawner::Update_Spawner(int level_number)
{
	if (!level_number) return;
	// Check if there are any more waves to spawn, and there is no current wave in progress
	if (!waves_completed_ && !wave_in_progress_)
	{
		if (wave_timer_ < wave_interval_length_)
			wave_timer_ += system_components.framerate_manager->Get_Game_Time();

		else if (wave_timer_ >= wave_interval_length_)
		{
			wave_in_progress_ = true;
			system_components.audio_manager->Play_Sound(SFX_WAVE_SPAWN_CHEER_1);
		}
	}

	// Stops trickle spawn when last wave comes out (completely disables for tutorial)
	if (wave_number_ < (max_wave_ - 1) && level_number)
		Trickle_Spawner();

	if (wave_in_progress_)
		Wave_Spawner();

	if(waves_completed_)
		if(!logic_components.object_manager->Get_Size_Kid_Soldier_List())
			logic_components.level_data->players->Victory(logic_components.level_data->players->Get_Grandma_Base_HP(), logic_components.level_data->Get_Level_Number());
}
/******************************************************************************/
/*!
			Update Spawner Big waves
*/
/******************************************************************************/

void Spawner::Wave_Spawner()
{
	if (Check_Wave_Validity()) {

		unit_spawn_timer_ += system_components.framerate_manager->Get_Game_Time();

		if (unit_spawn_timer_ >= 1.0f) {
			Create_Wave();
			unit_spawn_timer_ = 0;
		}
	}

	else {
		if (wave_number_ < max_wave_ - 1)
			wave_number_++;

		else waves_completed_ = true;

		wave_in_progress_ = false;

		wave_timer_ = 0;
	}
}

/******************************************************************************/
/*!
		Update Spawner Trickle
*/
/******************************************************************************/
void Spawner::Trickle_Spawner()
{
	trickle_timer_ += system_components.framerate_manager->Get_Game_Time();

	if (trickle_timer_ >= 7.0f) {
		Spawn_Object(K_S_SHOOTER, 500.0f, 0.0f);
		trickle_timer_ = 0;
	}
}
/******************************************************************************/
/*!
			intialize spawner (for when restart)
*/
/******************************************************************************/

void Spawner::Init_Spawner(int wave_pattern[][NUMBER_OF_GRANNIES])
{
	wave_timer_ = 0;
	unit_spawn_timer_ = 0;	
	trickle_timer_ = 0;	

	waves_completed_ = false;

	if (wave_spawner_) {
		for (int i = 0; i < max_wave_; ++i)
		{
			for (int j = 0; j < NUMBER_OF_GRANNIES; ++j)
			{
				wave_spawner_[i][j] = wave_pattern[i][j];
			}
		}
	}
	else
	{
		wave_spawner_ = new int*[max_wave_];
		for (int i = 0; i < max_wave_; ++i)
		{
			wave_spawner_[i] = new int[NUMBER_OF_GRANNIES];
			for (int j = 0; j < NUMBER_OF_GRANNIES; ++j)
			{
				wave_spawner_[i][j] = wave_pattern[i][j];
			}
		}
	}

}
/******************************************************************************/
/*!
				Create Wave by randomly spawning kids
*/
/******************************************************************************/

void Spawner::Create_Wave() {

	int type = 0;
	do {
		type = rand() % 10;
	} while (!wave_spawner_[wave_number_][type]);

	switch (type) {
	case 0:
		Spawn_Object(K_S_SHOOTER, 500.0f, 0.0f);
		break;
	case 1:
		Spawn_Object(K_S_TANK, 500.0f, 0.0f);
		break;
	case 2:
		Spawn_Object(K_S_SPEED, 500.0f, 0.0f);
		break;
	case 3:
		Spawn_Object(K_S_SABOTEUR, 500.0f, 0.0f);
		break;
	case 4:
		Spawn_Object(K_S_ATTACKSPEEDUP, 500.0f, 0.0f);
		break;
	case 5:
		Spawn_Object(K_S_STUN, 500.0f, 0.0f);
		break;
	case 6:
		Spawn_Object(K_S_SLOW, 500.0f, 0.0f);
		break;
	case 7:
		Spawn_Object(K_S_HEALER, 500.0f, 0.0f);
		break;
	case 8:
		Spawn_Object(K_S_ATTACKBUFF, 500.0f, 0.0f);
		break;
	case 9:
		Spawn_Object(K_S_BIGBOB, 500.0f, 0.0f);
		logic_components.object_manager->Activate_Particle_Emitter(PARTICLE_EXPLOSION, logic_components.level_data->Get_Enemy_Base_Location().x, logic_components.level_data->Get_Enemy_Base_Location().y, 50.0f, 2.0f);
		system_components.audio_manager->Play_Sound(SFX_KID_BIGBOB_SPAWN);
	default:
		break;
	}
	wave_spawner_[wave_number_][type]--;
}
/******************************************************************************/
/*!
			Check if the big wave is in progress
*/
/******************************************************************************/

bool Spawner::Get_Wave_In_Progress() const
{
	return wave_in_progress_;
}
/******************************************************************************/
/*!
				Checks if the current big wave is empty or not
*/
/******************************************************************************/

bool Spawner::Check_Wave_Validity() {
	for (int i = 0; i < NUMBER_OF_GRANNIES; ++i)
	{
		if (wave_spawner_[wave_number_][i])
			return true;
	}
	return false;
}
/******************************************************************************/
/*!
	Destructor for spawner
*/
/******************************************************************************/
Spawner::~Spawner()
{
	if (wave_spawner_) {
		for (int i = 0; i < max_wave_; ++i)
		{
			delete[] wave_spawner_[i];
			wave_spawner_[i] = nullptr;
		}
		delete wave_spawner_;
		wave_spawner_ = nullptr;
	}
}
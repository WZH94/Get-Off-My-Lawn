/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Spawner.h
\author Ngm Hui Min, Lois			(100%)
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
#include "AEEngine.h"
#ifndef SPAWNER_H
#define SPAWNER_H

static const int NUMBER_OF_GRANNIES = 10;

class Spawner
{
private:
	bool wave_in_progress_;		// Checks if wave is already in progress
	bool waves_completed_;		// Flag for whether or not the current level still has waves to spawn
	f64 wave_timer_;			// Handles timing between waves
	f64 trickle_timer_;			// Handles timing between units in the trickle waves
	f64 unit_spawn_timer_;		// Handles timing between units in a single wave
	int wave_number_;			// the wave number in the level
	int max_wave_;				// the max number of waves in the level
	int** wave_spawner_;		// holder to hold all soldiers for every wave

	const float wave_interval_length_;

public:
	// constructor
	Spawner();
	// loads the spawner
	void Spawner_Load(const int, int[][NUMBER_OF_GRANNIES]);
	// updates the spawner
	void Update_Spawner(int level_number_);
	// creates trickles
	void Trickle_Spawner();
	// intiialize the spawner
	void Init_Spawner(int [][NUMBER_OF_GRANNIES]);
	// updates on the waves in general
	void Wave_Spawner();
	// checks if the current wave still has remaining kids
	bool Check_Wave_Validity();
	// spans big waves
	void Create_Wave();
	// checks if there is a wave in progress
	bool Get_Wave_In_Progress() const;
	// destructor
	~Spawner();
};


#endif SPAWNER_H
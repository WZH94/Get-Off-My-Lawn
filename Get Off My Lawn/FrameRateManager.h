/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   FrameRateManager.h
\author Wong Zhihao(100%)
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date
\brief
This file contains the declaration of the Frame Rate Manager class, which
calcalates time and frame based variables, and handles the space time continuum
of the universe.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef FRAMERATEMANAGER_H
#define FRAMERATEMANAGER_H

class Framerate_Manager
{
protected:
	const double application_start_time_;	// Start time of the entire application

	double current_time_;					// current time

	double delta_time_;						// Delta time

	double current_state_start_time_;		// Start time of current state
	double current_state_elapsed_time_;		// How long the current state has lasted

	double overall_time_;					// Overall time

	int time_multiplier_;					// Time speed multiplier
	
public:
	// Constructor for Frame Rate Manager, sets default values
	Framerate_Manager();

	// Updates Framerate Manager every frame, updates its variables
	void Update_Framerate_Manager();

	// Set the start time every new state change
	void Set_New_State_Start_Time();

	// Set the time multiplier. True to speed up, false for normal speed
	void Set_Time_Multiplier(bool speed);

	int Get_Time_Multiplier() const;

	double Get_Current_Time() const;
	double Get_Overall_Time() const;
	float Get_Delta_Time() const;
	// Game timem is delta time multiplied with time multiplier, which is the game flow of time
	float Get_Game_Time() const;
	double Get_Elapsed_Time() const;
};

#endif
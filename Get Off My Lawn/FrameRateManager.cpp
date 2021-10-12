/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   FrameRateManager.cpp
\author Wong Zhihao(100%)
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date
\brief
This file contains the implementation of the Frame Rate Manager class, which 
calcalates time and frame based variables, and handles the space time continuum
of the universe.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "FrameRateManager.h"	// Function and class declarations
#include "AEEngine.h"			// Alpha Enginer frame rate

/******************************************************************************/
/*!
Constructor for Frame Rate Manager, sets default values
*/
/******************************************************************************/
Framerate_Manager::Framerate_Manager()
	: 
	application_start_time_{ AEGetTime(nullptr) },
	time_multiplier_{1},
	overall_time_{ 0 }
{
}

/******************************************************************************/
/*!
	Updates Framerate Manager every frame, updates its variables
*/
/******************************************************************************/
void Framerate_Manager::Update_Framerate_Manager()
{
	// Find delta time and current time
	delta_time_ = AEFrameRateControllerGetFrameTime();
	AEGetTime(&current_time_);
	current_state_elapsed_time_ += delta_time_ * time_multiplier_;
	overall_time_ += current_state_elapsed_time_;
}

/******************************************************************************/
/*!
	Set the start time every new state change
*/
/******************************************************************************/
void Framerate_Manager::Set_New_State_Start_Time()
{
	AEGetTime(&current_state_start_time_);

	current_state_elapsed_time_ = 0;

	time_multiplier_ = 1;
}

/******************************************************************************/
/*!
	Set the time multiplier. True to speed up, false for normal speed
*/
/******************************************************************************/
void Framerate_Manager::Set_Time_Multiplier(bool speed)
{
	if (speed == true)
		time_multiplier_ = 2;

	else time_multiplier_ = 1;
}

int Framerate_Manager::Get_Time_Multiplier() const
{
	return time_multiplier_;
}

double Framerate_Manager::Get_Current_Time() const
{
	return current_time_;
}

double Framerate_Manager::Get_Overall_Time() const
{
	return overall_time_;
}

float Framerate_Manager::Get_Delta_Time() const
{
	return (float)delta_time_;
}

/******************************************************************************/
/*!
	Game timem is delta time multiplied with time multiplier, which is the game flow of time
*/
/******************************************************************************/
float Framerate_Manager::Get_Game_Time() const
{
	return (float)delta_time_ * time_multiplier_;
}

double Framerate_Manager::Get_Elapsed_Time() const
{
	return current_state_elapsed_time_;
}

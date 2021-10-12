/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   LogicComponents.h
\author Wong Zhihao				(100%)
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the declaration of the Logic Components. It handles
functions that will occur at every state of the level states, and holds
various logic components.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef LOGICCOMPONENTS_H
#define LOGICCOMPONENTS_H

#include "Camera.h"				// Contains a camera object
#include "ObjectManager.h"		// Contains the object manager
#include "LevelData.h"			// Contains the level data
#include "PauseStateManager.h"	// Contains the pause state manager
#include <random>				// For generating random numbers

// Forward declarations
typedef enum GS_STATES GS_STATES;

class Logic_Components
{
protected:
	std::minstd_rand RNG;	// Random number generator

public:
	///////////////
	// Components
	Camera* camera;
	Object_Manager* object_manager;
	Level* level_data;
	Pause_State_Manager* pause_state_manager;

	//////////////
	// Functions

	// Initialises the Logic Component at the start of the application.
	void Initialise_Logic_Components();

	// Loads the logic components at the Load function of every level
	void Load_Level_Components(int level_number);

	// Initialises the logic components at the Initialise function of every level
	void Initialise_Level_Components();

	// Updates the logic components at the Update function of every level
	void Update_Level_Components();

	// Resets the logic components at the Free function of every level, used when restarting the game.
	void Free_Level_Components();

	// Clears the level components, called in Unload(), and used when changing game states.
	void Unload_Level_Components();

	// Frees the Logic Components before the application shuts down
	void Free_Logic_Components();

	// Generates a random int up to a specified amount
	int Generate_Random_Integer(int up_to);
};

extern Logic_Components logic_components;

#endif
/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   LogicComponents.cpp
\author Wong Zhihao				(100%)
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the implementation of the Logic Components. It handles
functions that will occur at every state of the level states, and holds
various logic components.
*/
/******************************************************************************/

#include "LogicComponents.h"	// Function and class declarations
#include "ObjectList.h"			// Object enums
#include "GameStateList.h"		// Enums for game states
#include <ctime>				// Seed for Random Number Generator
#include "SystemComponents.h"	// System Components

/******************************************************************************/
/*!
	Initialises the Logic Component at the start of the application.
*/
/******************************************************************************/
void Logic_Components::Initialise_Logic_Components()
{
	// Allocates memory for its components
	camera = new Camera;
	object_manager = new Object_Manager;
	pause_state_manager = new Pause_State_Manager;
	// Level data created only at the start of levels
	level_data = nullptr;

	// Spawns the Black Screen objects
	Spawn_Object(BLACK_SCREEN, 0, 0);
	// Don't show cursor, show custom cursor
	AEInputShowCursor(false);
	// Spawn the cursor texture
	Spawn_Object(CURSOR, system_components.cursor_position_->Get_Cursor_Position().x, system_components.cursor_position_->Get_Cursor_Position().y);
	// Seed the RNG
	RNG.seed(clock());
}

/******************************************************************************/
/*!
Loads the logic components at the Load function of every level
*/
/******************************************************************************/
void Logic_Components::Load_Level_Components(int level_number)
{
	level_data = new Level;
	level_data->Load_Level_Data(level_number);
}

/******************************************************************************/
/*!
Initialises the logic components at the Initialise function of every level
*/
/******************************************************************************/
void Logic_Components::Initialise_Level_Components()
{
	// Initialise its components
	object_manager->Initalise_Level_Object_Manager();

	camera->Initialise_Camera();

	level_data->Initialise_Level_Data();

	// Reset time multiplier
	system_components.framerate_manager->Set_Time_Multiplier(false);
}

/******************************************************************************/
/*!
Updates the logic components at the Update function of every level
*/
/******************************************************************************/
void Logic_Components::Update_Level_Components()
{
	camera->Update_Camera();
	object_manager->Update_Objects();
	object_manager->Kill_Objects();
}

/******************************************************************************/
/*!
Resets the logic components at the Free function of every level, used when restarting the game.
*/
/******************************************************************************/
void Logic_Components::Free_Level_Components()
{
	camera->Reset_Camera();
	level_data->Reset_Level_Data();
	object_manager->Free_Spawnables();
}

/******************************************************************************/
/*!
Clears the level components, called in Unload(), and used when changing game states.
*/
/******************************************************************************/
void Logic_Components::Unload_Level_Components()
{
	level_data->Clear_Level_Data();
	object_manager->Clear_Object_Manager();

	delete level_data;
}

/******************************************************************************/
/*!
Frees the Logic Components before the application shuts down
*/
/******************************************************************************/
void Logic_Components::Free_Logic_Components()
{
	object_manager->Free_Black_Screens();
	object_manager->Free_Cursor();

	delete camera;
	delete object_manager;
	delete pause_state_manager;
}


/******************************************************************************/
/*!
Generates a random number
*/
/******************************************************************************/
int Logic_Components::Generate_Random_Integer(int up_to)
{
	return RNG() % (up_to + 1);
}

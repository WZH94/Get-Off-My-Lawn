/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   LevelData.h
\author Wong Zhihao(50%)				| Ngm Hui Min, Lois (50%)
\par    email: zhihao.wong\@digipen.edu | lois.ngm\@digipen.edu
\par    DigiPen login: zhihao.wong | lois.ngm
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the declaration of the Level class, which holds the
data unique to each level, and stats required to track Level variables.
Player, Wave Spawner and Cursor Postion will be ported into this class.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <vector>	// vector to store paths and tower nodes
#include "AEVec2.h"	// Vector coordinate position
#include "Players.h"
#include "ObjectSpawner.h"

// Forward declaration of classes and enums
typedef class TowerNode TowerNode;
typedef enum SIDES SIDES;
typedef enum UNIT_TYPES UNIT_TYPES;
typedef class Spawner Spawner;
typedef class TowerNodeButton TowerNodeButton;

// Declaration of the Level class
class Level
{
protected:
	int max_waves_;					// Max number of waves to spawn in a level
	int level_number_;				// Level number of this level
	f64 current_timer_;				// Current time of the current state
	f64 update_timer_;				// Update time of the current state

	// The map boundaries of the level based on position of paths and bases
	float positive_x_boundary_;
	float negative_x_boundary_;
	float positive_y_boundary_;
	float negative_y_boundary_;

	AEVec2 enemy_base_location_;	// The location of the enemy base

	// Spawn offset from the base the soldiers should spawn from
	AEVec2 grandma_spawn_modifier_;	
	AEVec2 kids_spawn_modifier_;

	// The lists that hold the path and the tower nodes
	std::vector <TowerNode*> kid_tower_list;
	std::vector <TowerNode*> granny_tower_list;
	std::vector <TowerNodeButton*> kid_tower_list_;
	std::vector <TowerNodeButton*>granny_tower_list_;

	// The spawner for the Kids soldiers
	Spawner* spawner;

public:
	// In-game players data like health etc.
	Players* players;

	// Default constructor for the Level
	Level();

	/********************** LEVEL FUNCTIONS **********************/

	// Creates the objects related to the level and initialises coordinates of bases
	void Load_Level_Data(int level_number);

	// Initialises level data so that the game is fresh every restart
	void Initialise_Level_Data();

	// Updates level data every frame.
	void Update_Level_Data();

	// Resets the level properties to default values
	void Reset_Level_Data();

	// Clears up the level data
	void Clear_Level_Data();

	/********************** HELPER FUNCTIONS **********************/

	// Creates the grandma tower nodes in the level
	void Create_Granny_Tower_Nodes(unsigned pos, Orientation orientation, SIDES side, UNIT_TYPES towertype);

	// Creates the Kids tower nodes in the level
	void Create_Tower_Nodes(unsigned pos, Orientation orientation, SIDES side, UNIT_TYPES towertype);

	// Sets the spawn location of the kid base based on where the path ends.
	void Set_Spawn_Base_Location();

	// Creates the tower nodes in the level
	void Find_Level_Boundaries();

	// Empties the lists holding the paths and tower nodes
	void Clear_Nodes();

	//
	void Spawn_Level_Selection_Buttons();

	//
	void Spawn_Granny_Buttons();

	//
	void Spawn_Level_Play_Data();
	
	//
	void Spawn_Upgrade_Panels();

	//
	void Spawn_Upgrade_Buttons();


	/******************** GETTERS ********************/

	// Gets right most boundary of the level
	float Get_Positive_X_Boundary() const;

	// Gets left most boundary of the level
	float Get_Negative_X_Boundary() const;

	// Gets top most boundary of the level
	float Get_Positive_Y_Boundary() const;

	// Gets bottom most boundary of the level
	float Get_Negative_Y_Boundary() const;

	// Gets grandma soldier spawn offset
	AEVec2 Get_Grandma_Spawn_Modifier() const;

	// Gets kid soldier spawn offset
	AEVec2 Get_Kids_Spawn_Modifier() const;

	// Returns the location of the enemy base
	AEVec2 Get_Enemy_Base_Location() const;

	// Gets number of waves in the level
	int Get_Max_Waves() const;

	// Gets current timer
	f64 Get_Current_Timer() const;

	// Gets update timer
	f64 Get_Update_Timer() const;
	
	// Sets update timer
	void Set_Update_Timer(f64 timer);

	// Gets level number
	int Get_Level_Number() const;

	bool Get_Wave_In_Progress() const;
};

#endif LEVELDATA_H
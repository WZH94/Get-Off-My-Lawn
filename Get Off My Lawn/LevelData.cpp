/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   LevelData.cpp
\author Wong Zhihao			(50%)| Ngm Hui Min, Lois(50%)
\par    email: zhihao.wong\@digipen.edu | lois.ngm\@digipen.edu
\par    DigiPen login: zhihao.wong | lois.ngm
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the implementation of the Level class, which holds the 
data unique to each level, and stats required to track Level variables.
Player, Wave Spawner and Cursor Postion will be ported into this class.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "LevelData.h"			// Function and class declarations
#include "TowerNode.h"			// Tower node class
#include "LogicComponents.h"	// Logic Components
#include "Path.h"				// Paths
#include "Spawner.h"			// Spawner
#include "PlayerData.h"			// Player Data
#include "TowerNodeButton.h"	// Tower Node Button class

/******************************************************************************/
/*!
	Default constructor for the Level, initialises values to 0
*/
/******************************************************************************/
Level::Level()
	: 
	positive_x_boundary_{0},
	negative_x_boundary_{0},
	positive_y_boundary_{0},
	negative_y_boundary_{0}
{
}

/********************** LEVEL FUNCTIONS **********************/

/******************************************************************************/
/*!
	Creates the objects related to the level and initialises coordinates of bases
*/
/******************************************************************************/
void Level::Load_Level_Data(int level_number)
{
	// Allocates the memory for the Level components
	players = new Players;
	spawner = new Spawner;
	// Initialise the level number
	level_number_ = level_number;
	// Sets the enemy base location based on paths
	Set_Spawn_Base_Location();
	// Finds the size of the map based on the paths and bases
	Find_Level_Boundaries();

	// Initialise level values based on which level it is.
	switch (level_number_)
	{
	case 0:
	{
		const int MAX_WAVE = 1;
		int wave_pattern[MAX_WAVE][10] = {
		{ } };
		spawner->Spawner_Load(MAX_WAVE, wave_pattern);
		max_waves_ = MAX_WAVE;
		break;
	}
	case 1: {
		const int MAX_WAVE = 3;
		int wave_pattern[MAX_WAVE][10] = { { 8, 0 },
										   { 5, 3 },
										   { 7, 5 } };
		spawner->Spawner_Load(MAX_WAVE, wave_pattern);
		max_waves_ = MAX_WAVE;
		break;}
	case 2: {
		const int MAX_WAVE = 4;
		int wave_pattern[MAX_WAVE][10] = { { 10, 0 },
										   { 10, 2, 0 },
										   { 10, 3, 0 },
										   { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 } };
		spawner->Spawner_Load(MAX_WAVE, wave_pattern);
		max_waves_ = MAX_WAVE;
		break;}
	case 3: {
		const int MAX_WAVE = 5;
		int wave_pattern[MAX_WAVE][10] = { { 8, 2, 2, 0 },
										   { 10, 3, 2, 0 },
										   { 10, 2, 2, 1, 0 },
										   { 10, 3, 3, 2, 0 },
										   { 10, 4, 3, 2, 0 } };
		spawner->Spawner_Load(MAX_WAVE, wave_pattern);
		max_waves_ = MAX_WAVE;
		break;}
	case 4: {
		const int MAX_WAVE = 5;
		int wave_pattern[MAX_WAVE][10] = { { 2, 6, 0 },
										   { 4, 6, 2, 1, 0 },
										   { 4, 6, 2, 2, 1, 0 },
										   { 6, 6, 2, 2, 2, 0 },
										   { 2, 1, 0, 0, 1, 0, 0, 0, 0, 1 } };
		spawner->Spawner_Load(MAX_WAVE, wave_pattern);
		max_waves_ = MAX_WAVE;
		break;}
	case 5: {
		const int MAX_WAVE = 6;
		int wave_pattern[MAX_WAVE][10] = { { 6, 2, 2, 1, 1, 1, 0 },
										   { 6, 6, 2, 1, 2, 1, 0 },
										   { 5, 4, 3, 2, 4, 2, 0 },
										   { 5, 4, 3, 2, 2, 4, 1 },
										   { 6, 5, 3, 3, 4, 4, 2 },
										   { 6, 6, 4, 4, 4, 4, 2 } };
		spawner->Spawner_Load(MAX_WAVE, wave_pattern);
		max_waves_ = MAX_WAVE;
		break;}
	case 6: {
		const int MAX_WAVE = 6;
		int wave_pattern[MAX_WAVE][10] = { { 7, 2, 2, 1, 1, 1, 1 },
										   { 4, 8, 2, 1, 2, 1, 1 },
										   { 5, 4, 3, 2, 4, 2, 1 },
										   { 5, 4, 3, 2, 2, 4, 2 },
										   { 6, 5, 3, 3, 4, 4, 2 },
										   { 2, 1, 0, 0, 0, 0, 2, 0, 0, 1 } };
		spawner->Spawner_Load(MAX_WAVE, wave_pattern);
		max_waves_ = MAX_WAVE;
		break;}
	case 7: {
		const int MAX_WAVE = 7;
		int wave_pattern[MAX_WAVE][10] = { { 5, 4, 2, 1, 1, 1, 1, 1, 0 },
										   { 4, 6, 2, 1, 2, 2, 1, 1, 0 },
										   { 5, 6, 3, 2, 4, 2, 1, 2, 0 },
										   { 3, 7, 3, 2, 2, 3, 1, 1, 1 },
										   { 4, 6, 3, 3, 4, 3, 1, 2, 1 },
										   { 5, 7, 4, 4, 4, 4, 1, 2, 2 },
										   { 6, 7, 4, 4, 4, 4, 2, 2, 2 } };
		spawner->Spawner_Load(MAX_WAVE, wave_pattern);
		max_waves_ = MAX_WAVE;
		break;}
	case 8: {
		const int MAX_WAVE = 7;
		int wave_pattern[MAX_WAVE][10] = { { 10, 2, 2, 1, 1, 1, 1, 1, 1 },
										   { 3, 8, 2, 2, 2, 2, 2, 1, 1 },
										   { 6, 6, 3, 3, 3, 3, 2, 2, 1 },
										   { 9, 5, 4, 4, 4, 4, 2, 2, 2 },
										   { 8, 6, 4, 4, 4, 4, 2, 3, 2 },
										   { 8, 4, 4, 4, 4, 6, 2, 3, 3 },
										   { 1, 0, 0, 0, 0, 1, 1, 1, 0, 1 } };
		spawner->Spawner_Load(MAX_WAVE, wave_pattern);
		max_waves_ = MAX_WAVE;
		break;}
	case 9: {
		const int MAX_WAVE = 8;
		int wave_pattern[MAX_WAVE][10] = { { 9, 3, 1, 1, 1, 1, 1, 1, 1 },
										   { 3, 8, 2, 1, 2, 1, 1, 1, 1 },
										   { 4, 4, 3, 2, 3, 6, 1, 1, 1 },
										   { 5, 5, 3, 2, 2, 3, 1, 3, 1 },
										   { 4, 6, 3, 2, 3, 3, 5, 2, 1 },
										   { 7, 7, 4, 4, 4, 4, 2, 2, 1 },
										   { 8, 6, 3, 3, 4, 6, 1, 2, 1 },
										   { 7, 7, 4, 4, 4, 4, 2, 2, 2 }, };
		spawner->Spawner_Load(MAX_WAVE, wave_pattern);
		max_waves_ = MAX_WAVE;
		break;}
	case 10: {
		const int MAX_WAVE = 10;
		int wave_pattern[MAX_WAVE][10] = { { 10, 1, 1, 1, 1, 1, 1, 1, 1 },
										   { 1, 10, 1, 1, 1, 1, 1, 1, 1 },
										   { 5, 5, 2, 2, 2, 4, 2, 2, 1 },
										   { 3, 7, 3, 2, 2, 4, 2, 1, 2 },
										   { 4, 5, 3, 3, 4, 3, 2, 2, 2 },
										   { 5, 7, 3, 3, 3, 3, 3, 2, 2 },
										   { 9, 5, 3, 3, 4, 3, 2, 2, 2 },
										   { 5, 6, 3, 3, 3, 7, 1, 2, 3 },
										   { 6, 6, 4, 4, 4, 4, 2, 2, 2 },
										   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };
		spawner->Spawner_Load(MAX_WAVE, wave_pattern);
		max_waves_ = MAX_WAVE;
		break;}
	default:
		break;
	}
}

/******************************************************************************/
/*!
	Initialises level data so that the game is fresh every restart
*/
/******************************************************************************/
void Level::Initialise_Level_Data()
{
	update_timer_ = AEGetTime(nullptr);

	// Sets all the kid tower nodes to be active, which spawns a tower at their location.
	for (unsigned i = 0; i < kid_tower_list.size(); ++i)
		kid_tower_list.at(i)->Set_Active(TOWER_PLACED, kid_tower_list.at(i)->Get_Tower_Type());

	switch (level_number_)
	{
	case 0:
	{
		const int MAX_WAVE = 1;
		int wave_pattern[MAX_WAVE][10] = {
			{} };
		spawner->Init_Spawner(wave_pattern);
		max_waves_ = MAX_WAVE;
		break;
	}
	case 1: {
		const int MAX_WAVE = 3;
		int wave_pattern[MAX_WAVE][10] = { { 8, 0 },
		{ 5, 3 },
		{ 7, 5 } };
		spawner->Init_Spawner(wave_pattern);
		max_waves_ = MAX_WAVE;
		break;}
	case 2: {
		const int MAX_WAVE = 4;
		int wave_pattern[MAX_WAVE][10] = { { 10, 0 },
		{ 10, 2, 0 },
		{ 10, 3, 0 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 } };
		spawner->Init_Spawner(wave_pattern);
		max_waves_ = MAX_WAVE;
		break;}
	case 3: {
		const int MAX_WAVE = 5;
		int wave_pattern[MAX_WAVE][10] = { { 8, 2, 2, 0 },
		{ 10, 3, 2, 0 },
		{ 10, 2, 2, 1, 0 },
		{ 10, 3, 3, 2, 0 },
		{ 10, 4, 3, 2, 0 } };
		spawner->Init_Spawner(wave_pattern);
		max_waves_ = MAX_WAVE;
		break;}
	case 4: {
		const int MAX_WAVE = 5;
		int wave_pattern[MAX_WAVE][10] = { { 2, 6, 0 },
		{ 4, 6, 2, 1, 0 },
		{ 4, 6, 2, 2, 1, 0 },
		{ 6, 6, 2, 2, 2, 0 },
		{ 2, 1, 0, 0, 1, 0, 0, 0, 0, 1 } };
		spawner->Init_Spawner(wave_pattern);
		max_waves_ = MAX_WAVE;
		break;}
	case 5: {
		const int MAX_WAVE = 6;
		int wave_pattern[MAX_WAVE][10] = { { 6, 2, 2, 1, 1, 1, 0 },
		{ 6, 6, 2, 1, 2, 1, 0 },
		{ 5, 4, 3, 2, 4, 2, 0 },
		{ 5, 4, 3, 2, 2, 4, 1 },
		{ 6, 5, 3, 3, 4, 4, 2 },
		{ 6, 6, 4, 4, 4, 4, 2 } };
		spawner->Init_Spawner(wave_pattern);
		max_waves_ = MAX_WAVE;
		break;}
	case 6: {
		const int MAX_WAVE = 6;
		int wave_pattern[MAX_WAVE][10] = { { 7, 2, 2, 1, 1, 1, 1 },
		{ 4, 8, 2, 1, 2, 1, 1 },
		{ 5, 4, 3, 2, 4, 2, 1 },
		{ 5, 4, 3, 2, 2, 4, 2 },
		{ 6, 5, 3, 3, 4, 4, 2 },
		{ 2, 1, 0, 0, 0, 0, 2, 0, 0, 1 } };
		spawner->Init_Spawner(wave_pattern);
		max_waves_ = MAX_WAVE;
		break;}
	case 7: {
		const int MAX_WAVE = 7;
		int wave_pattern[MAX_WAVE][10] = { { 5, 4, 2, 1, 1, 1, 1, 1, 0 },
		{ 4, 6, 2, 1, 2, 2, 1, 1, 0 },
		{ 5, 6, 3, 2, 4, 2, 1, 2, 0 },
		{ 3, 7, 3, 2, 2, 3, 1, 1, 1 },
		{ 4, 6, 3, 3, 4, 3, 1, 2, 1 },
		{ 5, 7, 4, 4, 4, 4, 1, 2, 2 },
		{ 6, 7, 4, 4, 4, 4, 2, 2, 2 } };
		spawner->Init_Spawner(wave_pattern);
		max_waves_ = MAX_WAVE;
		break;}
	case 8: {
		const int MAX_WAVE = 7;
		int wave_pattern[MAX_WAVE][10] = { { 10, 2, 2, 1, 1, 1, 1, 1, 1 },
		{ 3, 8, 2, 2, 2, 2, 2, 1, 1 },
		{ 6, 6, 3, 3, 3, 3, 2, 2, 1 },
		{ 9, 5, 4, 4, 4, 4, 2, 2, 2 },
		{ 8, 6, 4, 4, 4, 4, 2, 3, 2 },
		{ 8, 4, 4, 4, 4, 6, 2, 3, 3 },
		{ 1, 0, 0, 0, 0, 1, 1, 1, 0, 1 } };
		spawner->Init_Spawner(wave_pattern);
		max_waves_ = MAX_WAVE;
		break;}
	case 9: {
		const int MAX_WAVE = 8;
		int wave_pattern[MAX_WAVE][10] = { { 9, 3, 1, 1, 1, 1, 1, 1, 1 },
		{ 3, 8, 2, 1, 2, 1, 1, 1, 1 },
		{ 4, 4, 3, 2, 3, 6, 1, 1, 1 },
		{ 5, 5, 3, 2, 2, 3, 1, 3, 1 },
		{ 4, 6, 3, 2, 3, 3, 5, 2, 1 },
		{ 7, 7, 4, 4, 4, 4, 2, 2, 1 },
		{ 8, 6, 3, 3, 4, 6, 1, 2, 1 },
		{ 7, 7, 4, 4, 4, 4, 2, 2, 2 }, };
		spawner->Init_Spawner(wave_pattern);
		max_waves_ = MAX_WAVE;
		break;}
	case 10: {
		const int MAX_WAVE = 10;
		int wave_pattern[MAX_WAVE][10] = { { 10, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 10, 1, 1, 1, 1, 1, 1, 1 },
		{ 5, 5, 2, 2, 2, 4, 2, 2, 1 },
		{ 3, 7, 3, 2, 2, 4, 2, 1, 2 },
		{ 4, 5, 3, 3, 4, 3, 2, 2, 2 },
		{ 5, 7, 3, 3, 3, 3, 3, 2, 2 },
		{ 9, 5, 3, 3, 4, 3, 2, 2, 2 },
		{ 5, 6, 3, 3, 3, 7, 1, 2, 3 },
		{ 6, 6, 4, 4, 4, 4, 2, 2, 2 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } };
		spawner->Init_Spawner(wave_pattern);
		max_waves_ = MAX_WAVE;
		break;}
	default:
		break;
	}
	for (unsigned i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
	{
		GameObject * wave_filler = logic_components.object_manager->Get_Description(i);
		if (wave_filler->Get_Unit_Type() != WAVE_FILLER) continue;
		wave_filler->Set_x_pos(-540.0f);
		wave_filler->Set_y_pos(-140.0f);
		wave_filler->Set_Scale_X(0.0f);
	}
	for (unsigned i = 0; i < logic_components.object_manager->Get_Size_Button_List(); ++i)
	{
		TowerNodeButton * button = dynamic_cast<TowerNodeButton*>(logic_components.object_manager->Get_Button(i));
		if (button)
		{
			button->Set_Active(INACTIVE);
			button->Set_Alive(true);
		}
	}
}

/******************************************************************************/
/*!
	Updates level data every frame.
*/
/******************************************************************************/
void Level::Update_Level_Data()
{
	current_timer_ = AEGetTime(nullptr);
	// disables spawner for level 0 aka tutorial
	spawner->Update_Spawner(level_number_);
	players->Granny_Mojo_Earn();
}

/******************************************************************************/
/*!
	Resets the level properties to default values
*/
/******************************************************************************/
void Level::Reset_Level_Data()
{
	// Reset the players stats in game.
	players->Reset_Player_Stats();

	// Resets the tower nodes for both sides
	for (unsigned i = 0; i < kid_tower_list.size(); ++i)
	{
		kid_tower_list.at(i)->Reset_Tower_Node();
	}

	for (unsigned i = 0; i < granny_tower_list.size(); ++i)
	{
		granny_tower_list.at(i)->Reset_Tower_Node();
	}
}

/******************************************************************************/
/*!
	Clears up the level data
*/
/******************************************************************************/
void Level::Clear_Level_Data()
{
	// Empties the lists holding the tower nodes
 	Clear_Nodes();

	// Free the memory of the level data
	delete players;
	delete spawner;
}

/********************** HELPER FUNCTIONS **********************/

/******************************************************************************/
/*!
	Creates the grandma tower nodes in the level
*/
/******************************************************************************/
void Level::Create_Granny_Tower_Nodes(unsigned pos, Orientation orientation, SIDES side, UNIT_TYPES towertype)
{
	UNREFERENCED_PARAMETER(towertype);
	const Path* clipping_path = logic_components.object_manager->Get_Path(pos);
	float x = clipping_path->Get_Pos().x, y = clipping_path->Get_Pos().y;
	switch (orientation)
	{
	case(UP):
		y += 100.0f;
		break;
	case(DOWN):
		y -= 100.0f;
		break;
	case(LEFT):
		x -= 200.0f;
	case(RIGHT):
		x += 100.0f;
	}
	UNIT_TYPES t = G_TOWER_NODE4;
	switch (level_number_)
	{
	case 0:
	case 1:
	case 2:
		t = G_TOWER_NODE1;
		break;
	case 3:
		t = G_TOWER_NODE2;
		break;
	case 4:
	case 5:
	case 6:
		t = G_TOWER_NODE3;
		break;
	default:
		t = G_TOWER_NODE4;
		break;
	}
	TowerNodeButton * node = new TowerNodeButton(x, y, 30.0f, 30.0f, t, 0.25f, 0.0f, GRANDMA);
	(side == KIDS) ? kid_tower_list_.push_back(node) : granny_tower_list_.push_back(node);
	logic_components.object_manager->Insert_Object(node);
}


/******************************************************************************/
/*!
	Creates the Kids tower nodes in the level
*/
/******************************************************************************/
void Level::Create_Tower_Nodes(unsigned pos, Orientation orientation, SIDES side, UNIT_TYPES towertype){
	const Path* clipping_path = logic_components.object_manager->Get_Path(pos);
	float x = clipping_path->Get_Pos().x, y = clipping_path->Get_Pos().y;
	switch (orientation)
	{
	case(UP):
		y += 100.0f;
		break;
	case(DOWN):
		y -= 100.0f;
		break;
	case(LEFT):
		x -= 200.0f;
	case(RIGHT):
		x += 100.0f;
	}
	UNIT_TYPES t = G_TOWER_NODE4;
	switch (level_number_)
	{
	case 1:
	case 2:
		t = G_TOWER_NODE1;
		break;
	case 3:
		t = G_TOWER_NODE2;
		break;
	case 4:
	case 5:
	case 6:
		t = G_TOWER_NODE3;
		break;
	default:
		t = G_TOWER_NODE4;
		break;
	}
	TowerNode * node = (side == KIDS) ? new TowerNode(x, y, side, towertype) : new TowerNode(x, y, side, t);

	(side == KIDS) ? kid_tower_list.push_back(node) : granny_tower_list.push_back(node);

	// Object manager will handle destruction of this object
	logic_components.object_manager->Insert_Object(node);
}

/******************************************************************************/
/*!
	Sets the spawn location of the kid base based on where the path ends.
*/
/******************************************************************************/
void Level::Set_Spawn_Base_Location()
{
	// Number of paths in the level.
	unsigned number_of_paths = logic_components.object_manager->Get_Size_Path_List();

	// Gets the last path set down, this will be the location of the base
	Path* first_path = logic_components.object_manager->Get_Path(0);
	Path* last_path = logic_components.object_manager->Get_Path(number_of_paths - 1);

	float path_radius = first_path->Get_Radius();

	// Sets the last path to not have a texture so that it does not render behind the base
	last_path->Set_Texture(nullptr);

	// Sets the initial location of the base to the location of the last path
	enemy_base_location_ = last_path->Get_Pos();

	// Sets the spawn offset of the grandma soldiers so that they spawn towards the path
	switch (first_path->Get_Orientation())
	{
	case RIGHT:
		grandma_spawn_modifier_.x = path_radius;
		grandma_spawn_modifier_.y = 0;
		break;

	case LEFT:
		grandma_spawn_modifier_.x = -path_radius;
		grandma_spawn_modifier_.y = 0;
		break;

	case UP:
		grandma_spawn_modifier_.x = 0;
		grandma_spawn_modifier_.y = path_radius;
		break;

	case DOWN:
		grandma_spawn_modifier_.x = 0;
		grandma_spawn_modifier_.y = -path_radius;
		break;
	}

	// Shifts the location of the base based on the orientation of the last path 
	// so that it is centered with the path on one axis, and at the edge of the last path on the other
	// Also adjusts spawn offset of the kids
	switch (last_path->Get_Orientation())
	{
	case RIGHT:
		enemy_base_location_.x += path_radius;

		kids_spawn_modifier_.x = -path_radius;
		kids_spawn_modifier_.y = 0;
		break;

	case UP:
		enemy_base_location_.y += path_radius;

		kids_spawn_modifier_.x = 0;
		kids_spawn_modifier_.y = -path_radius;
		break;

	case DOWN:
		enemy_base_location_.y -= path_radius;

		kids_spawn_modifier_.x = 0;
		kids_spawn_modifier_.y = path_radius;
		break;
	}
}

/******************************************************************************/
/*!
	Creates the tower nodes in the level
*/
/******************************************************************************/
void Level::Find_Level_Boundaries()
{
	// Number of paths in the level.
	unsigned number_of_paths = logic_components.object_manager->Get_Size_Path_List();

	// Loops through every path
	for (unsigned i = 0; i < number_of_paths; ++i)
	{
		// Find the x and y of the current path.
		float node_x = logic_components.object_manager->Get_Path(i)->Get_Pos().x;
		float node_y = logic_components.object_manager->Get_Path(i)->Get_Pos().y;

		// Check if this node is the right most object in the level.
		if (node_x > positive_x_boundary_)
			positive_x_boundary_ = node_x;

		// Check if this node is the left most object in the level.
		else if (node_x < negative_x_boundary_)
			negative_x_boundary_ = node_x;

		// Check if this node is the top most object in the level.
		if (node_y > positive_y_boundary_)
			positive_y_boundary_ = node_y;

		// Check if this node is the bottom most object in the level.
		else if (node_y < negative_y_boundary_)
			negative_y_boundary_ = node_y;

		// By the end, the outermost object coordinates should be captured. These are the level boundaries used for the camera.
	}

	// Radius of each path.
	float path_radius = logic_components.object_manager->Get_Path(0)->Get_Radius();

	// Check if the right most path is on the kids base
	if (positive_x_boundary_ <= enemy_base_location_.x && positive_x_boundary_ + logic_components.object_manager->Get_Path(0)->Get_Radius() >= enemy_base_location_.x)
		// Set the boundary to take base location plus its radius instead, setting right most boundary to be the base coordinate instead.
		positive_x_boundary_ = enemy_base_location_.x + 100.0f;
	// Boundary takes path radius
	else positive_x_boundary_ += path_radius;

	// Check if the left most path is on the granny base
	if (negative_x_boundary_ == 0)
		// Set the boundary to take base location minus its radius instead, setting left most boundary to be the base coordinate instead.
		negative_x_boundary_ = -100.0f;
	// Boundary takes path radius
	else negative_x_boundary_ -= path_radius;

	positive_y_boundary_ += path_radius;
	negative_y_boundary_ -= path_radius;
}

/******************************************************************************/
/*!
	Empties the lists holding the paths and tower nodes
*/
/******************************************************************************/
void Level::Clear_Nodes()
{
	// Clear the pointers in the kids tower node list
	while (kid_tower_list.size())
	{
		kid_tower_list.back() = nullptr;
		kid_tower_list.pop_back();
	}

	// Clear the pointers in the grandma tower node list
	while (granny_tower_list.size())
	{
		granny_tower_list.back() = nullptr;
		granny_tower_list.pop_back();
	}
	while (granny_tower_list_.size())
	{
		granny_tower_list_.back() = nullptr;
		granny_tower_list_.pop_back();
	}
}

/******************************************************************************/
/*!

*/
/******************************************************************************/
void Level::Spawn_Level_Selection_Buttons()
{
	int levels = playdata.Get_Levels_Complete();
	float x = -376.0f;
	float x_increment = 185.5f;
	float y = 161.0f;
	float y_increment = -258.0f;
	switch(levels)
	{
	default:
	case 9:
		Spawn_Object(LEVEL_10_BUTTON, x + x_increment * 4.0f, y + y_increment);
	case 8:
		Spawn_Object(LEVEL_9_BUTTON, x + x_increment * 3.0f, y + y_increment);
	case 7:
		Spawn_Object(LEVEL_8_BUTTON, x + x_increment * 2.0f, y + y_increment);
	case 6:
		Spawn_Object(LEVEL_7_BUTTON, x + x_increment, y + y_increment);
	case 5:
		Spawn_Object(LEVEL_6_BUTTON, x, y + y_increment);
	case 4:
		Spawn_Object(LEVEL_5_BUTTON, x + x_increment * 4.0f, y);
	case 3:
		Spawn_Object(LEVEL_4_BUTTON, x + x_increment * 3.0f, y);
	case 2:
		Spawn_Object(LEVEL_3_BUTTON, x + x_increment * 2.0f, y);
	case 1:
		Spawn_Object(LEVEL_2_BUTTON, x + x_increment, y);
	case 0:
		Spawn_Object(LEVEL_1_BUTTON, x, y);
		break;
	}
	switch (levels)
	{
	default:
		break;
	case 0:
		Spawn_Object(LOCKED_LEVEL, x + x_increment, y);
	case 1:
		Spawn_Object(LOCKED_LEVEL, x + x_increment * 2.0f, y);
	case 2:
		Spawn_Object(LOCKED_LEVEL, x + x_increment * 3.0f, y);
	case 3:
		Spawn_Object(LOCKED_LEVEL, x + x_increment * 4.0f, y);
	case 4:
		Spawn_Object(LOCKED_LEVEL, x, y + y_increment);
	case 5:
		Spawn_Object(LOCKED_LEVEL, x + x_increment, y + y_increment);
	case 6:
		Spawn_Object(LOCKED_LEVEL, x + x_increment * 2.0f, y + y_increment);
	case 7:
		Spawn_Object(LOCKED_LEVEL, x + x_increment * 3.0f, y + y_increment);
	case 8:
		Spawn_Object(LOCKED_LEVEL, x + x_increment * 4.0f, y + y_increment);
		break;
	}
}

/******************************************************************************/
/*!
	
*/
/******************************************************************************/
void Level::Spawn_Granny_Buttons()
{
	int level = logic_components.level_data->Get_Level_Number();
	float x = -300.0f;
	float y = -230.0f;
	float x_increment = 75.0f;
	switch (level)
	{
	default:
	case 7:
		Spawn_Object(G_BUTTON_9, x + x_increment * 8.0f, y);
		Spawn_Object(G_BUTTON_8, x + x_increment * 7.0f, y);
	case 5:
	case 6:
		Spawn_Object(G_BUTTON_7, x + x_increment * 6.0f, y);
		Spawn_Object(G_BUTTON_6, x + x_increment * 5.0f, y);
	case 4:
		Spawn_Object(G_BUTTON_5, x + x_increment * 4.0f, y);
	case 3:
		Spawn_Object(G_BUTTON_4, x + x_increment * 3.0f, y);
		Spawn_Object(G_BUTTON_3, x + x_increment * 2.0f, y);
	case 1:
	case 2:
		Spawn_Object(G_BUTTON_2, x + x_increment, y);
	case 0:
		Spawn_Object(G_BUTTON_1, x, y);
		break;
	}
	switch (level)
	{
	default:
		break;
	case 0:
		Spawn_Object(LOCKED_GRANNY, x + x_increment, y);
	case 1:
	case 2:
		Spawn_Object(LOCKED_GRANNY, x + x_increment * 2.0f, y);
		Spawn_Object(LOCKED_GRANNY, x + x_increment * 3.0f, y);
	case 3:
		Spawn_Object(LOCKED_GRANNY, x + x_increment * 4.0f, y);
	case 4:
		Spawn_Object(LOCKED_GRANNY, x + x_increment * 5.0f, y);
		Spawn_Object(LOCKED_GRANNY, x + x_increment * 6.0f, y);
	case 5:
	case 6:
		Spawn_Object(LOCKED_GRANNY, x + x_increment * 7.0f, y);
		Spawn_Object(LOCKED_GRANNY, x + x_increment * 8.0f, y);
	}
}

/******************************************************************************/
/*!

*/
/******************************************************************************/
void Level::Spawn_Level_Play_Data()
{
	std::string player1 = playdata.Get_Path_Name() + "\\playerdata1.txt";
	std::string player2 = playdata.Get_Path_Name() + "\\playerdata2.txt";
	std::string player3 = playdata.Get_Path_Name() + "\\playerdata3.txt";

	Does_File_Exist(player1.c_str()) ? Spawn_Object(PLAYER_1, -350.0f, -100.0f) : Spawn_Object(NEW_GAME, -350.0f, -100.0f);
	Does_File_Exist(player2.c_str()) ? Spawn_Object(PLAYER_2, 0.0f, -100.0f) : Spawn_Object(NEW_GAME, 0.0f, -100.0f);
	Does_File_Exist(player3.c_str()) ? Spawn_Object(PLAYER_3, 350.0f, -100.0f) : Spawn_Object(NEW_GAME, 350.0f, -100.0f);
}

/******************************************************************************/
/*!

*/
/******************************************************************************/
void Level::Spawn_Upgrade_Panels()
{
	float x = -540.0f;
	float  incremenet_x = 120.0f;
	Spawn_Object(GENERAL_GRANNY_UPGRADE_1, x + (incremenet_x * 0), -50.0f);
	Spawn_Object(GENERAL_GRANNY_UPGRADE_2, x + (incremenet_x * 1), -50.0f);
	Spawn_Object(GENERAL_GRANNY_UPGRADE_3, x + (incremenet_x * 2), -50.0f);
	Spawn_Object(GENERAL_GRANNY_UPGRADE_4, x + (incremenet_x * 3), -50.0f);
	Spawn_Object(GENERAL_GRANNY_UPGRADE_5, x + (incremenet_x * 4), -50.0f);
	Spawn_Object(GENERAL_GRANNY_UPGRADE_6, x + (incremenet_x * 5), -50.0f);
	Spawn_Object(GENERAL_GRANNY_UPGRADE_7, x + (incremenet_x * 6), -50.0f);
	Spawn_Object(GENERAL_GRANNY_UPGRADE_8, x + (incremenet_x * 7), -50.0f);
	Spawn_Object(GENERAL_GRANNY_UPGRADE_9, x + (incremenet_x * 8), -50.0f);
	Spawn_Object(GENERAL_GRANNY_UPGRADE_10, x + (incremenet_x * 9), -50.0f);
}

/******************************************************************************/
/*!

*/
/******************************************************************************/
void Level::Spawn_Upgrade_Buttons()
{
	float x = -540.0f;
	float incremenet_x = 120.0f;
	float level_1 = -50.0f;
	float level_2 = 50.0f;

	// COOKIE
	Spawn_Object(BUTTON_RANGE_INCREASE, x + (incremenet_x * 0), level_1);
	Spawn_Object(BUTTON_COOKIE_ATTACKRATE_INCREASE, x + (incremenet_x * 0), level_2);

	// TANK
	Spawn_Object(BUTTON_HEALTH_INCREASE, x + (incremenet_x * 1), level_1);
	Spawn_Object(BUTTON_SPEED_INCREASE, x + (incremenet_x * 1), level_2);

	// RACER
	Spawn_Object(BUTTON_HEALTH_INCREASE, x + (incremenet_x * 2), level_1);
	Spawn_Object(BUTTON_COOLDOWN_DECREASE, x + (incremenet_x * 2), level_2);

	//NINJA
	Spawn_Object(BUTTON_NINJA_ATTACKRATE_INCREASE, x + (incremenet_x * 3), level_1);
	Spawn_Object(BUTTON_COOLDOWN_DECREASE, x + (incremenet_x * 3), level_2);

	// CAT
	Spawn_Object(BUTTON_RANGE_INCREASE, x + (incremenet_x * 4), level_1);
	Spawn_Object(BUTTON_DAMAGE_INCREASE, x + (incremenet_x * 4), level_2);

	// KUNGFU
	Spawn_Object(BUTTON_HEALTH_INCREASE, x + (incremenet_x * 5), level_1);
	Spawn_Object(BUTTON_DAMAGE_INCREASE, x + (incremenet_x * 5), 50.0f);

	// SASSY
	Spawn_Object(BUTTON_RANGE_INCREASE, x + (incremenet_x * 6), level_1);
	Spawn_Object(BUTTON_DAMAGE_INCREASE, x + (incremenet_x * 6), level_2);

	// HEAL
	Spawn_Object(BUTTON_RANGE_INCREASE, x + (incremenet_x * 7), level_1);
	Spawn_Object(BUTTON_HEALING_INCREASE, x + (incremenet_x * 7), level_2);

	// AOE
	Spawn_Object(BUTTON_HEALTH_INCREASE, x + (incremenet_x * 8), level_1);
	Spawn_Object(BUTTON_RANGE_INCREASE_2, x + (incremenet_x * 8), level_2);

	// GRANNY_MOJO
	Spawn_Object(BUTTON_MAX_CAP, x + (incremenet_x * 9), level_1);
	Spawn_Object(BUTTON_COST_DECREASE, x + (incremenet_x * 9), level_2);


}





/******************** GETTERS FOR VARIABLES ********************/

/******************************************************************************/
/*!
	Gets right most boundary of the level
*/
/******************************************************************************/
float Level::Get_Positive_X_Boundary() const
{
	return positive_x_boundary_;
}

/******************************************************************************/
/*!
Gets left most boundary of the level
*/
/******************************************************************************/
float Level::Get_Negative_X_Boundary() const
{
	return negative_x_boundary_;
}

/******************************************************************************/
/*!
Gets top most boundary of the level
*/
/******************************************************************************/
float Level::Get_Positive_Y_Boundary() const
{
	return positive_y_boundary_;
}

/******************************************************************************/
/*!
Gets bottom most boundary of the level
*/
/******************************************************************************/
float Level::Get_Negative_Y_Boundary() const
{
	return negative_y_boundary_;
}

/******************************************************************************/
/*!
Gets grandma soldier spawn offset
*/
/******************************************************************************/
AEVec2 Level::Get_Grandma_Spawn_Modifier() const
{
	return grandma_spawn_modifier_;
}

/******************************************************************************/
/*!
Gets kid soldier spawn offset
*/
/******************************************************************************/
AEVec2 Level::Get_Kids_Spawn_Modifier() const
{
	return kids_spawn_modifier_;
}

/******************************************************************************/
/*!
Gets enemy base location
*/
/******************************************************************************/
AEVec2 Level::Get_Enemy_Base_Location() const
{
	return enemy_base_location_;
}

/******************************************************************************/
/*!
Gets number of waves in the level
*/
/******************************************************************************/
int Level::Get_Max_Waves() const
{
	return max_waves_;
}

/******************************************************************************/
/*!
Gets current timer
*/
/******************************************************************************/
f64 Level::Get_Current_Timer() const
{
	return current_timer_;
}

/******************************************************************************/
/*!
Gets update timer
*/
/******************************************************************************/
f64 Level::Get_Update_Timer() const
{
	return update_timer_;
}

/******************************************************************************/
/*!
Sets update timer
*/
/******************************************************************************/
void Level::Set_Update_Timer(f64 timer)
{
	update_timer_ = timer;
}

/******************************************************************************/
/*!
Gets level number
*/
/******************************************************************************/
int Level::Get_Level_Number() const
{
	return level_number_;
}

bool Level::Get_Wave_In_Progress() const
{
	return spawner->Get_Wave_In_Progress();
}

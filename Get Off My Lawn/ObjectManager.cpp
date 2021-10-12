/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   ObjectManager.cpp
\author Wong Zhihao
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login: zhihao.wong 
\par    Course: GAM150
\date	13/04/18
\brief
	This file handles the object manager, which stores and handles every game
	object in the game. This also contains specialised lists that store individual
	object types as seperate lists.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.

*/
/******************************************************************************/

#include "ObjectManager.h"		// Function declarations
#include "GameObject.h"			// GameObject class
#include "Soldier.h"			// Soldier class
#include "Tower.h"				// Tower class
#include "TowerNode.h"			// Tower Node class
#include "Path.h"				// Path class
#include "Particle.h"			// Particle class
#include "SystemComponents.h"	// System components
#include "ObjectList.h"			// Object enums
#include "ObjectSpawner.h"		// Object spawner

// Default constructor of the Object List class
Object_Manager::Object_Manager()
	: current_ID_{0}
{
}

/******************************************************************************/
/*!
	Initialises the object manager for use in a level. Creates the memory
	for projectiles in the level and resets the ID.
*/
/******************************************************************************/
void Object_Manager::Initalise_Level_Object_Manager()
{
	current_ID_ = 0;

	for (unsigned i = 0; i < MAX_PROJECTILE_COUNT; ++i)
	{
		projectile_list_.at(i) = new Projectile;
		projectile_list_.at(i)->Set_ID(current_ID_);
		++current_ID_;
	}

	for (unsigned i = 0; i < MAX_PARTICLE_EMMITER_COUNT; ++i)
	{
		particle_emitter_list_.at(i) = new ParticleEmitter;
		particle_emitter_list_.at(i)->Set_ID(current_ID_);
		++current_ID_;
	}
}

/******************************************************************************/
/*!
Inserts an object at the back of its relevant specialised list
*/
/******************************************************************************/
void Object_Manager::Insert_Object(GameObject* object)
{
	// Gives every object a unique ID. Black screen has no ID.
	if (object->Get_Object_Type() != TYPE_BLACK_SCREEN_FADE && object->Get_Object_Type() != TYPE_BLACK_SCREEN_TINT)
	{
		object->Set_ID(current_ID_);
		++current_ID_;
	}

	// Puts the object into its specialised object list
	switch (object->Get_Object_Type())
	{
	case SOLDIER:
		if (object->Get_Side() == GRANDMA)
			grandma_soldier_list_.push_back((Soldier*)object);

		else if (object->Get_Side() == KIDS)
			kid_soldier_list_.push_back((Soldier*)object);
		break;

	case TOWER:
		tower_list_.push_back((Tower*)object);
		break;

	case BASE:
		base_list_.push_back(object);
		break;

	case GENERAL:
	case SCALABLE_GENERAL:
		general_list_.push_back(object);
		break;


	case BUTTONS:
	case SCALABLE_BUTTON:
		button_list_.push_back(object);
		break;

	case TOWER_NODES:
		tower_node_list_.push_back((TowerNode*)object);
		break;

	case PATH:
		path_list_.push_back((Path*)object);
		break;

	case BACKGROUND:
		background_ = object;
		break;

	case DESCRIPTION:
	case SCALABLE_DESCRIPTION:
		description_list_.push_back(object);
		break;

	case TYPE_BLACK_SCREEN_FADE:
		black_screen_list_.at(0) = (BlackScreen*)object;
		break;
	case TYPE_BLACK_SCREEN_TINT:
		black_screen_list_.at(1) = (BlackScreen*)object;
		break;

	case TYPE_CURSOR:
		cursor_ = object;
		break;
	}
}

/******************************************************************************/
/*!
Inserts pause objects seperately so they can be dealt with seperately
*/
/******************************************************************************/
void Object_Manager::Insert_Pause_Object(GameObject * object)
{
	pause_object_list_.push_back(object);
}

/******************************************************************************/
/*!
Finds an inactive projectile to set active in the game
*/
/******************************************************************************/
void Object_Manager::Create_Projectile(UNIT_TYPES type, float x, float y, int damage, GameObject & target)
{
	for (unsigned i = 0; i < MAX_PROJECTILE_COUNT; ++i)
	{
		if (!projectile_list_.at(i)->Get_Active())
		{
			projectile_list_.at(i)->Set_Active(type, x, y, damage, target);
			break;
		}
	}
}

/******************************************************************************/
/*!
Finds an inactive particle emitter to set active in the game
*/
/******************************************************************************/
void Object_Manager::Activate_Particle_Emitter(UNIT_TYPES particletype, float x, float y, float range, float lifetime)
{
	for (unsigned i = 0; i < MAX_PARTICLE_EMMITER_COUNT; ++i)
	{
		if (!particle_emitter_list_.at(i)->Get_Alive())
		{
			particle_emitter_list_.at(i)->Set_Active(x, y, particletype, range, lifetime);
			particle_emitter_list_[i]->Set_Alive(true);
			return;
		}
	}
}

//////////////////////////
// BLACK SCREEN FUNCTIONS

/******************************************************************************/
/*!
Initiates the game to fade to black
*/
/******************************************************************************/
void Object_Manager::Initiate_Fade_Black_Screen(bool fade_type)
{
	black_screen_list_.at(0)->Initiate_Fade_Black_Screen(fade_type);
}

/******************************************************************************/
/*!
Initiates the game to tint black
*/
/******************************************************************************/
void Object_Manager::Set_Black_Tint_Screen(bool fade_type)
{
	black_screen_list_.at(1)->Set_Black_Tint_Screen(fade_type);
}

/******************************************************************************/
/*!
Calls the update function of every game object with logic in the list
*/
/******************************************************************************/
void Object_Manager::Update_Objects()
{
	// Updates soldiers
	for (unsigned i = 0; i < grandma_soldier_list_.size(); ++i)
	{
		grandma_soldier_list_.at(i)->Update();
		grandma_soldier_list_.at(i)->Set_Matrix();
	}

	for (unsigned i = 0; i < kid_soldier_list_.size(); ++i)
	{
		kid_soldier_list_.at(i)->Update();
		kid_soldier_list_.at(i)->Set_Matrix();
	}

	// Updates towers
	for (unsigned i = 0; i < tower_list_.size(); ++i)
	{
		tower_list_.at(i)->Update();
		tower_list_.at(i)->Set_Matrix();
	}

	if (projectile_list_.front())
	{
		// Updates projectiles
		for (unsigned i = 0; i < MAX_PROJECTILE_COUNT; ++i)
		{
			if (projectile_list_[i]->Get_Active())
			{
				projectile_list_[i]->Update();
				projectile_list_[i]->Set_Matrix();
			}
		}
	}

	if (particle_emitter_list_.front())
	{
		// Updates particles
		for (unsigned i = 0; i < particle_emitter_list_.size(); ++i)
		{
			if (particle_emitter_list_.at(i)->Get_Alive())
			{
				particle_emitter_list_.at(i)->Update();
				particle_emitter_list_.at(i)->Set_Matrix();
			}
		}
	}

	// Updates generals
	for (unsigned i = 0; i < general_list_.size(); ++i)
	{
		general_list_.at(i)->Update();
		general_list_.at(i)->Set_Matrix();
	}


	// Updates buttons
	for (unsigned i = 0; i < button_list_.size(); ++i)
	{
		button_list_.at(i)->Update();
		button_list_.at(i)->Set_Matrix();
	}
	// Updates description boxes
	for (unsigned i = 0; i < description_list_.size(); ++i)
	{
		description_list_.at(i)->Update();
		description_list_.at(i)->Set_Matrix();
	}


	// Updates tower nodes
	for (unsigned i = 0; i < tower_node_list_.size(); ++i)
	{
		tower_node_list_.at(i)->Update();
		tower_node_list_.at(i)->Set_Matrix();
	}

	// Updates bases
	for (unsigned i = 0; i < base_list_.size(); ++i)
		base_list_.at(i)->Set_Matrix();

	// Updates paths
	for (unsigned i = 0; i < path_list_.size(); ++i)
		path_list_.at(i)->Set_Matrix();


	if (background_)
		background_->Set_Matrix();

	black_screen_list_.at(0)->Set_Matrix();

	black_screen_list_.at(0)->Update();

	black_screen_list_.at(1)->Set_Matrix();

	cursor_->Set_Matrix();
	cursor_->Update();
}

/******************************************************************************/
/*!
Updates the Black Screens individually
*/
/******************************************************************************/
void Object_Manager::Update_Black_Screens()
{
	black_screen_list_.at(0)->Set_Matrix();

	black_screen_list_.at(0)->Update();

	black_screen_list_.at(1)->Set_Matrix();
}

/******************************************************************************/
/*!
Updates the Black Screens individually
*/
/******************************************************************************/
void Object_Manager::Update_Pause_Objects()
{
	for (unsigned i = 0; i < pause_object_list_.size(); ++i)
	{
		pause_object_list_.at(i)->Update();
		pause_object_list_.at(i)->Set_Matrix();
	}
}

/******************************************************************************/
/*!
Calls the rendering function of every object in the list
*/
/******************************************************************************/
void Object_Manager::Draw_Objects()
{
	// Draw objects in order of which will be rendered behind the others in front

	// Render background first
	if (background_)
		background_->Draw();

	// Paths will render over the background
	for (unsigned i = 0; i < path_list_.size(); ++i)
		path_list_[i]->Draw();

	if (particle_emitter_list_.front())
	{
		// Some particles will render below other objects
		for (unsigned i = 0; i < particle_emitter_list_.size(); ++i)
		{
			if (particle_emitter_list_[i]->Get_Alive())
			{
				switch (particle_emitter_list_[i]->Get_Unit_Type())
				{
				case PARTICLE_ATTACK_AURA:
				case PARTICLE_SMOKE:
					particle_emitter_list_[i]->Draw();
					break;
				default:
					continue;
				}
			}
		}
	}

	// Tower Nodes will render over the background
	for (unsigned i = 0; i < tower_node_list_.size(); ++i)
		tower_node_list_[i]->Draw();

	for (unsigned i = 0; i < button_list_.size(); ++i)
	{
		if (button_list_[i]->Get_Object_Type() == SCALABLE_BUTTON)
			button_list_[i]->Draw();
	}

	// Towers will render over the nodes
	for (unsigned i = 0; i < tower_list_.size(); ++i)
		tower_list_[i]->Draw();

	// Soldiers will render over the towers
	for (unsigned i = 0; i < grandma_soldier_list_.size(); ++i)
		grandma_soldier_list_[i]->Draw();

	for (unsigned i = 0; i < kid_soldier_list_.size(); ++i)
		kid_soldier_list_[i]->Draw();

	if (projectile_list_.front())
	{
		// Projectils will render over the soldiers
		for (unsigned i = 0; i < MAX_PROJECTILE_COUNT; ++i)
		{
			if (projectile_list_[i]->Get_Active())
				projectile_list_[i]->Draw();
		}
	}

	// Base will render over projectiles
	for (unsigned i = 0; i < base_list_.size(); ++i)
		base_list_[i]->Draw();

	if (particle_emitter_list_.front())
	{
		// Remaining particles will render over the bases
		for (unsigned i = 0; i < particle_emitter_list_.size(); ++i)
		{
			if (particle_emitter_list_.at(i)->Get_Alive())
			{
				UNIT_TYPES type = particle_emitter_list_[i]->Get_Unit_Type();
				if (type == PARTICLE_ATTACK_AURA || type == PARTICLE_SMOKE)
					continue;
				else
					particle_emitter_list_[i]->Draw();
			}
		}
	}


	// general will render over everything else except buttons
	for (unsigned i = 0; i < general_list_.size(); ++i)
	{
		if(general_list_[i]->Get_Unit_Type() != GAME_STAT)
			general_list_[i]->Draw();
	}

	// Buttons will render over everything else
	for (unsigned i = 0; i < button_list_.size(); ++i)
	{
		if(!(button_list_[i]->Get_Unit_Type() >= BUTTON_YES && button_list_[i]->Get_Unit_Type() <= BUTTON_LEVEL_SELECT) && button_list_.at(i)->Get_Object_Type() != SCALABLE_BUTTON)
			button_list_[i]->Draw();
	}

	// descriptions will render over everything else except buttons
	for (unsigned i = 0; i < description_list_.size(); ++i)
		description_list_[i]->Draw();

	if (black_screen_list_.at(0)->Get_Render_Type())
		black_screen_list_.at(0)->Draw();

	if (black_screen_list_.at(1)->Get_Render_Type())
		black_screen_list_.at(1)->Draw();
	for (unsigned i = 0; i < general_list_.size(); ++i)
	{
		if (general_list_[i]->Get_Unit_Type() == GAME_STAT)
			general_list_[i]->Draw();
	}
	for (unsigned i = 0; i < button_list_.size(); ++i)
	{
		if (button_list_[i]->Get_Unit_Type() >= BUTTON_YES&& button_list_[i]->Get_Unit_Type() <= BUTTON_LEVEL_SELECT)
			button_list_[i]->Draw();
	}

	for (unsigned i = 0; i < button_list_.size(); ++i)
	{
		if (button_list_.at(i)->Get_Unit_Type() == WAVE_FILLER)
			button_list_.at(i)->Draw();
	}

	cursor_->Draw();
}

/******************************************************************************/
/*!
Draws the Pause objects individually
*/
/******************************************************************************/
void Object_Manager::Draw_Pause_Objects()
{
	for (unsigned i = 0; i < pause_object_list_.size(); ++i) 
	{
		pause_object_list_.at(i)->Set_Matrix();
		pause_object_list_.at(i)->Update();
		pause_object_list_.at(i)->Draw();
	}
	cursor_->Set_Matrix();
	cursor_->Update();
	cursor_->Draw();
}

/******************************************************************************/
/*!
Draws the Black Screens individually
*/
/******************************************************************************/
void Object_Manager::Draw_Black_Screens()
{
	// Draw the fade over the tint
	black_screen_list_.at(1)->Draw();
	black_screen_list_.at(0)->Draw();
}

/******************************************************************************/
/*!
Draw out the game stats
*/
/******************************************************************************/
void Object_Manager::Draw_Game_Stat()
{

	for (unsigned i = 0; i < general_list_.size(); ++i)
	{
		if (general_list_[i]->Get_Unit_Type() == GAME_STAT)
			general_list_[i]->Draw();
	}
	for (unsigned i = 0; i < button_list_.size(); ++i)
	{
		if (button_list_[i]->Get_Unit_Type() >= BUTTON_YES&& button_list_[i]->Get_Unit_Type() <= BUTTON_LEVEL_SELECT)
			button_list_[i]->Draw();
	}

	cursor_->Draw();
}

/******************************************************************************/
/*!
Frees every soldier, tower, base, projectile, dialogue, particle and button types in the game
Called during Free()
*/
/******************************************************************************/
void Object_Manager::Free_Spawnables()
{
	// Frees memory allocated and nullptr them and pop the lists till it's empty

	while (grandma_soldier_list_.size())
	{
		delete grandma_soldier_list_.back();
		grandma_soldier_list_.back() = nullptr;
		grandma_soldier_list_.pop_back();
	}

	while (kid_soldier_list_.size())
	{
		delete kid_soldier_list_.back();
		kid_soldier_list_.back() = nullptr;
		kid_soldier_list_.pop_back();
	}

	while (tower_list_.size())
	{
		delete tower_list_.back();
		tower_list_.back() = nullptr;
		tower_list_.pop_back();
	}

	if (projectile_list_.front())
	{
		for (unsigned i = 0; i < MAX_PROJECTILE_COUNT; ++i)
		{
			delete projectile_list_.at(i);
			projectile_list_.at(i) = nullptr;
		}
	}

	if (particle_emitter_list_.front())
	{
		for (unsigned i = 0; i < MAX_PARTICLE_EMMITER_COUNT; ++i)
		{
			particle_emitter_list_.at(i)->Free();
			delete particle_emitter_list_.at(i);
			particle_emitter_list_.at(i) = nullptr;
		}
	}
}

/******************************************************************************/
/*!
Frees Pause Objects only
*/
/******************************************************************************/
void Object_Manager::Free_Pause_Object_List()
{
	while (pause_object_list_.size())
	{
		delete pause_object_list_.back();
		pause_object_list_.back() = nullptr;
		pause_object_list_.pop_back();
	}
}

/******************************************************************************/
/*!
Frees every remaining object in the list. Called during Unload()
*/
/******************************************************************************/
void Object_Manager::Clear_Object_Manager()
{

	while (base_list_.size())
	{
		delete base_list_.back();
		base_list_.back() = nullptr;
		base_list_.pop_back();
	}

	while (general_list_.size())
	{
		delete general_list_.back();
		general_list_.back() = nullptr;
		general_list_.pop_back();
	}
	while (description_list_.size())
	{
		delete description_list_.back();
		description_list_.back() = nullptr;
		description_list_.pop_back();
	}

	while (button_list_.size())
	{
		delete button_list_.back();
		button_list_.back() = nullptr;
		button_list_.pop_back();
	}

	while (tower_node_list_.size())
	{
		delete tower_node_list_.back();
		tower_node_list_.back() = nullptr;
		tower_node_list_.pop_back();
	}

	while (path_list_.size())
	{
		delete path_list_.back();
		path_list_.back() = nullptr;
		path_list_.pop_back();
	}


	delete background_;
	background_ = nullptr;
}

////////////////////////
// Death List functions

/******************************************************************************/
/*!
Empties out the death list
*/
/******************************************************************************/
void Object_Manager::Queue_Kill_Object(GameObject* dead_object)
{
	death_list_.push_back(dead_object);
}

/******************************************************************************/
/*!
Kills and frees the objects in the Death List from the game
*/
/******************************************************************************/
void Object_Manager::Kill_Objects()
{
	// Loops through the whole list
	while (!death_list_.empty())
	{
		// Gets the ID of the object to kill
		long long ID = death_list_.back()->Get_ID();

		// Finds and frees the memory allocated and pops the object from its specialised object list
		if (death_list_.back()->Get_Object_Type() == SOLDIER)
		{
			if (death_list_.back()->Get_Side() == GRANDMA)
			{
				for (unsigned i = 0; i < grandma_soldier_list_.size(); ++i)
				{
					if (grandma_soldier_list_[i]->Get_ID() == ID)
					{
						delete grandma_soldier_list_.at(i);
						grandma_soldier_list_.erase(grandma_soldier_list_.begin() + i);
					}
				}
			}

			else if (death_list_.back()->Get_Side() == KIDS)
			{
				for (unsigned i = 0; i < kid_soldier_list_.size(); ++i)
				{
					if (kid_soldier_list_[i]->Get_ID() == ID)
					{
						delete kid_soldier_list_.at(i);
						kid_soldier_list_.erase(kid_soldier_list_.begin() + i);
					}
				}
			}
		}

		else if (death_list_.back()->Get_Object_Type() == TOWER)
		{
			for (unsigned i = 0; i < tower_list_.size(); ++i)
			{
				if (tower_list_[i]->Get_ID() == ID)
				{
					delete tower_list_.at(i);
					tower_list_.erase(tower_list_.begin() + i);
				}
			}
		}

		// Remove this object from the death list
		death_list_.pop_back();
	}
}


/******************************************************************************/
/*!
Free the black screens only
*/
/******************************************************************************/
void Object_Manager::Free_Black_Screens()
{
	delete black_screen_list_.at(0);
	delete black_screen_list_.at(1);
}

/******************************************************************************/
/*!
Free the cursor only
*/
/******************************************************************************/
void Object_Manager::Free_Cursor()
{
	delete cursor_;
}

/************************************** OBJECT LISTS GETTERS **************************************/

////////////////////////////////////////////
// Gets the number of object types in play

unsigned Object_Manager::Get_Size_Grandma_Soldier_List()
{
	return grandma_soldier_list_.size();
}

unsigned Object_Manager::Get_Size_Kid_Soldier_List()
{
	return kid_soldier_list_.size();
}

unsigned Object_Manager::Get_Size_Tower_List()
{
	return tower_list_.size();
}

unsigned Object_Manager::Get_Size_General_List()
{
	return general_list_.size();
}
unsigned Object_Manager::Get_Size_Description_List()
{
	return description_list_.size();
}
unsigned Object_Manager::Get_Size_Button_List()
{
	return button_list_.size();
}

unsigned Object_Manager::Get_Size_Tower_Node_List()
{
	return tower_node_list_.size();
}

unsigned Object_Manager::Get_Size_Path_List()
{
	return path_list_.size();
}

unsigned Object_Manager::Get_Size_Particle_Emitter_List()
{
	return particle_emitter_list_.size();
}

unsigned Object_Manager::Get_Size_Pause_Object_List()
{
	return pause_object_list_.size();
}

//////////////////////////////////////////////////////////
// Gets the object in the specified position in the list
// Use for looping through the entire list

/******************************************************************************/
/*!
Finds the object in the specified position in its specialised object list
*/
/******************************************************************************/
Soldier* Object_Manager::Get_Grandma_Soldier(unsigned index)
{
	return grandma_soldier_list_.at(index);
}

/******************************************************************************/
/*!
Finds the object in the specified position in its specialised object list
*/
/******************************************************************************/
Soldier* Object_Manager::Get_Kid_Soldier(unsigned index)
{
	return kid_soldier_list_.at(index);
}

/******************************************************************************/
/*!
Finds the object in the specified position in its specialised object list
*/
/******************************************************************************/
Tower* Object_Manager::Get_Tower(unsigned index)
{
	return tower_list_.at(index);
}

/******************************************************************************/
/*!
Finds the object in the specified position in its specialised object list
*/
/******************************************************************************/
GameObject* Object_Manager::Get_General(unsigned index)
{
	return general_list_.at(index);
}

/******************************************************************************/
/*!
Finds the object in the specified position in its specialised object list
*/
/******************************************************************************/
GameObject* Object_Manager::Get_Description(unsigned index)
{
	return description_list_.at(index);
}

/******************************************************************************/
/*!
Finds the object in the specified position in its specialised object list
*/
/******************************************************************************/
GameObject* Object_Manager::Get_Button(unsigned index)
{
	return button_list_.at(index);
}

/******************************************************************************/
/*!
Finds the object in the specified position in its specialised object list
*/
/******************************************************************************/
TowerNode* Object_Manager::Get_Tower_Node(unsigned index)
{
	return tower_node_list_.at(index);
}

/******************************************************************************/
/*!
Finds the object in the specified position in its specialised object list
*/
/******************************************************************************/
Path* Object_Manager::Get_Path(unsigned index)
{
	return path_list_.at(index);
}

/******************************************************************************/
/*!
Finds the object in the specified position in its specialised object list
*/
/******************************************************************************/
ParticleEmitter* Object_Manager::Get_Particle_Emitter(unsigned index)
{
	return particle_emitter_list_.at(index);
}

/******************************************************************************/
/*!
Finds the object in the specified position in its specialised object list
*/
/******************************************************************************/
BlackScreen * Object_Manager::Get_Black_Screen(bool type)
{
	if (type)
		return black_screen_list_.at(0);

	else return black_screen_list_.at(1);
}


/******************************************************************************/
/*!
Finds the object in the specified position in its specialised object list
*/
/******************************************************************************/
GameObject * Object_Manager::Get_Cursor()
{
	return cursor_;
}

/******************************************************************************/
/*!
Finds the object in the specified position in its specialised object list
*/
/******************************************************************************/
GameObject *Object_Manager::Get_Pause_Object(unsigned index)
{
	return pause_object_list_.at(index);
}

////////////////////////////////////////////
// Finds a specific object based on its ID 
// Use for searching for specific object

/******************************************************************************/
/*!
Finds the object by its ID in its specialised object list. Returns nullptr if not found.
*/
/******************************************************************************/
Soldier* Object_Manager::Find_Grandma_Soldier(long long ID)
{
	for (unsigned i = 0; i < grandma_soldier_list_.size(); ++i)
		if (grandma_soldier_list_.at(i)->Get_ID() == ID)
			return grandma_soldier_list_.at(i);

	return nullptr;
}

/******************************************************************************/
/*!
Finds the object by its ID in its specialised object list. Returns nullptr if not found.
*/
/******************************************************************************/
Soldier* Object_Manager::Find_Kid_Soldier(long long ID)
{
	for (unsigned i = 0; i < kid_soldier_list_.size(); ++i)
		if (kid_soldier_list_.at(i)->Get_ID() == ID)
			return kid_soldier_list_.at(i);

	return nullptr;
}

/******************************************************************************/
/*!
Finds the object by its ID in its specialised object list. Returns nullptr if not found.
*/
/******************************************************************************/
Tower* Object_Manager::Find_Tower(long long ID)
{
	for (unsigned i = 0; i < tower_list_.size(); ++i)
		if (tower_list_.at(i)->Get_ID() == ID)
			return tower_list_.at(i);

	return nullptr;
}


/******************************************************************************/
/*!
Sets the path rotation based on its orientation
*/
/******************************************************************************/
void Object_Manager::Set_Rotation()
{
	// If there's no path return
	if (path_list_.empty())
		return;

	// Go through the path list and check every single orientation
	for (unsigned i = 0; i < path_list_.size(); ++i)
	{
		if (path_list_.at(i)->Get_Unit_Type() == PATH_STRAIGHT)
		{
			if (path_list_.at(i)->Get_Orientation() == RIGHT || path_list_.at(i)->Get_Orientation() == LEFT)
			{
				path_list_.at(i)->Set_Angle(90.0f);
				continue;
			}
		}
		if (path_list_.at(i)->Get_Unit_Type() == PATH_TURN)
		{
			if (path_list_.at(i)->Get_Orientation() == DOWN && path_list_.at(i + 1)->Get_Orientation() == RIGHT)
			{
				path_list_.at(i)->Set_Angle(90.0f);
				continue;
			}
			if (path_list_.at(i)->Get_Orientation() == DOWN && path_list_.at(i + 1)->Get_Orientation() == LEFT)
			{
				path_list_.at(i)->Set_Angle(-180.0f);
				continue;
			}
			if (path_list_.at(i)->Get_Orientation() == UP && path_list_.at(i + 1)->Get_Orientation() == LEFT)
			{
				path_list_.at(i)->Set_Angle(-90.0f);
				continue;
			}
			if (path_list_.at(i)->Get_Orientation() == RIGHT && path_list_.at(i + 1)->Get_Orientation() == UP)
			{
				path_list_.at(i)->Set_Angle(180.0f);
				continue;
			}
			if (path_list_.at(i)->Get_Orientation() == RIGHT && path_list_.at(i + 1)->Get_Orientation() == DOWN)
			{
				path_list_.at(i)->Set_Angle(-90.0f);
				continue;
			}
			if (path_list_.at(i)->Get_Orientation() == LEFT && path_list_.at(i + 1)->Get_Orientation() == UP)
			{
				path_list_.at(i)->Set_Angle(90.0f);
				continue;
			}
		}
	}
}
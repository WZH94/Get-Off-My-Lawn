/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   ObjectManager.h
\author Wong Zhihao
\par    email: zhihao.wong\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
	This file contains the declaration of the Object Manager and all of its
	functions.

	Copyright (C) 2018 DigiPen Institute of Technology.
	Reproduction or disclosure of this file or its contents without the
	prior written consent of DigiPen Institute of Technology is prohibited.
	All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

// Containers
#include <vector>
#include <deque>
#include <array>

// Max amount of this type of objects that can exist at one time
const int MAX_PROJECTILE_COUNT = 256;
const int MAX_PARTICLE_EMMITER_COUNT = 256;

// Forward declarations
typedef class GameObject GameObject;

typedef class Combatant Combatant;

typedef class Soldier Soldier;
typedef class Tower Tower;
typedef class TowerNode TowerNode;
typedef class Projectile Projectile;
typedef class Path Path;
typedef class ParticleEmitter ParticleEmitter;
typedef class BlackScreen BlackScreen;

typedef enum UNIT_TYPES UNIT_TYPES;

class Object_Manager
{
protected:
	// Unique ID for every object created in the game
	long long current_ID_;

	////////////////////////////
	// Specialised Object Lists

	// Soldier lists
	std::deque <Soldier*> grandma_soldier_list_;
	std::deque <Soldier*> kid_soldier_list_;

	// Tower list
	std::deque <Tower*> tower_list_;

	// Projectile list
	std::array <Projectile*, MAX_PROJECTILE_COUNT> projectile_list_;

	// Particle list
	std::array <ParticleEmitter*, MAX_PARTICLE_EMMITER_COUNT> particle_emitter_list_;

	// Base list
	std::vector <GameObject*> base_list_;

	// Static object list
	std::vector <GameObject*> general_list_;

	// Button list
	std::vector <GameObject*> button_list_;

	// Static description list
	std::vector <GameObject*> description_list_;

	// Paths list
	std::vector <Path*> path_list_;

	// Tower nodes list
	std::vector <TowerNode*> tower_node_list_;

	// The background of the level
	GameObject* background_;

	// Used for fading and tinting screen
	std::array <BlackScreen*, 2> black_screen_list_;

	GameObject* cursor_;

	// Logic Lists, these lists hold objects that need to execute logic
	std::vector <GameObject*> death_list_;

	// Seperate list that holds game objects in the pause menu
	std::vector <GameObject*> pause_object_list_;
	
public:
	// Default constructor
	Object_Manager();

	// 	Initialises the object manager for use in a level. Creates the memory for projectiles in the level and resets the ID.
	void Initalise_Level_Object_Manager();

	// Inserts an object at the back of its relevant specialised list
	void Insert_Object(GameObject* object);

	// Finds an inactive projectile to set active in the game
	void Create_Projectile(UNIT_TYPES type, float x, float y, int damage, GameObject & target);

	//////////////////////////
	// BLACK SCREEN FUNCTIONS

	// Fades the entire screen, true to fade to black, false to fade out from black
	void Initiate_Fade_Black_Screen(bool fade_type);

	// Sets the screen to be tinted black, true to tint, false to untint
	void Set_Black_Tint_Screen(bool fade_type);

	// Inserts pause objects seperately so they can be dealt with seperately
	void Insert_Pause_Object(GameObject * object);

	// Calls the update function of every object in the list
	void Update_Objects();

	// Updates the Black Screens individually
	void Update_Black_Screens();

	// Updates the Black Screens individually
	void Update_Pause_Objects();

	// Calls the rendering function of every object in the list
	void Draw_Objects();

	// Draws the Pause objects individually
	void Draw_Pause_Objects();

	// Frees every soldier, tower, base, projectile, dialogue, particle and button types in the game
	// Called during Free()
	void Free_Spawnables();

	// Frees Pause Objects only
	void Free_Pause_Object_List();

	// Frees every object in the list
	void Clear_Object_Manager();

	// Draws the Black Screens individually
	void Draw_Black_Screens();

	// Draw out the game stats
	void Draw_Game_Stat();

	////////////////////////
	// Death List functions

	// Empties out the death list
	void Queue_Kill_Object(GameObject*);

	// Kills and frees the objects in the Death List from the game
	void Kill_Objects();

	// Free the black screens only
	void Free_Black_Screens();

	// Free the cursor only
	void Free_Cursor();

	/************************************** OBJECT LISTS GETTERS **************************************/

	////////////////////////////////////////////
	// Gets the number of object types in play

	// Gets the number of soldiers in play
	unsigned Get_Size_Grandma_Soldier_List();
	unsigned Get_Size_Kid_Soldier_List();
	// Gets the number of towers in play
	unsigned Get_Size_Tower_List();
	// Gets the number of general objects in play
	unsigned Get_Size_General_List();

	// Gets the number of description objects in play
	unsigned Get_Size_Description_List();

	// Gets the number of buttons in play
	unsigned Get_Size_Button_List();
	// Gets the number of tower nodes in play
	unsigned Get_Size_Tower_Node_List();
	// Gets the number of paths in the game
	unsigned Get_Size_Path_List();

	unsigned Get_Size_Particle_Emitter_List();
	// Gets the number of particles in play


	unsigned Get_Size_Pause_Object_List();

	//////////////////////////////////////////////////////////
	// Gets the object in the specified position in the list
	// Use for looping through the entire list

	// Gets the soldier in the specified position in the list
	Soldier* Get_Grandma_Soldier(unsigned);
	Soldier* Get_Kid_Soldier(unsigned);
	// Gets the tower in the specified position in the list
	Tower* Get_Tower(unsigned);
	// Gets the general object in the specified position in the list
	GameObject * Get_General(unsigned index);
	// Gets the description object in the specified position in the list
	GameObject * Get_Description(unsigned index);
	// Gets the button in the specified position in the list
	GameObject * Get_Button(unsigned index);
	// Gets the tower node in the specified position in the list
	TowerNode* Get_Tower_Node(unsigned index);
	// Gets the path in the specified position in the list
	Path * Get_Path(unsigned index);
	// Gets the particle in the specified position in the list
	ParticleEmitter* Get_Particle_Emitter(unsigned index);
	// Gets the black screen, true for fade screen, false for tint screen
	BlackScreen* Get_Black_Screen(bool);
	
	GameObject* Get_Cursor();

	GameObject* Get_Pause_Object(unsigned index);	////////////////////////////////////////////
	// Finds a specific object based on its ID 
	// Use for searching for specific object

	// Finds a specific soldier based on its ID 
	Soldier* Find_Grandma_Soldier(long long ID);
	Soldier* Find_Kid_Soldier(long long ID);
	// Finds a specific object based on its ID 
	Tower* Find_Tower(long long ID);

	// Activates a particle emiiter or creates a new one if none are free for use
	void Activate_Particle_Emitter(UNIT_TYPES particletype, float x, float y, float range, float lifetime);

	void Set_Rotation();

};

extern std::vector <Combatant*> Combat_List;
extern std::vector <Soldier*> Movement_List;

#endif OBJECTMANAGER_H